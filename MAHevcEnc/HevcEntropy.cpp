#include "HevcEntropy.h"
#include "Context.h"
//3 means initType(0, 1, 2)
const uint8 INIT_SAO_MERGE[3][NUM_SAO_MERGE_FLAG_CTX] = {{153}, {153}, {153}};

const uint8 INIT_SAO_TYPE_IDX[3] = {{200}, {185}, {160}};

const uint8 INIT_SPLIT_CU[3][NUM_SPLIT_FLAG_CTX] = 
{
	{139, 141, 157},
	{107, 139, 126},
	{107, 139, 126}
};

const uint8 INIT_CU_TS_QUANT_BYPASS[3][NUM_TQUANT_BYPASS_FLAG_CTX] = {{154}, {154}, {154}};

const uint8 INIT_CU_SKIP[3][NUM_SKIP_FLAG_CTX] = 
{
	{CNU, CNU, CNU},
	{197, 185, 201},
	{197, 185, 201},
};
CHevcEntropy::CHevcEntropy()
{

}

CHevcEntropy::~CHevcEntropy()
{

}

void CHevcEntropy::ResetHevcEntropy()
{

}

void CHevcEntropy::InitBuffer(HEVC_SLICE_TYPE sliceType, uint8* contextModel, int qp, uint8* ctxModel, int size)
{
	//consider cabac_init_flag is 0
	int ctxOffset = sliceType * size;
	ctxModel += ctxOffset;

	//each ctx has a init value
	for(uint32 uiCtxIdx = 0; uiCtxIdx < size; uiCtxIdx++)
	{
		uint32 uiInitValue = ctxModel[uiCtxIdx];
		uint32 uiSlopeIdx = uiInitValue >> 4;
		uint32 uiOffsetIdx = uiInitValue & 15;
		uint32 uiM = uiSlopeIdx * 5 - 45;
		uint32 uiN = (uiOffsetIdx << 3) - 16;
		int uiTmp = (((uiM * x265_clip3(0, 51, qp)) >> 4) + uiN);
		int uiPreCtxState = x265_clip3(1, 126, uiTmp);
		uint32 uiMpsValue = (uiPreCtxState <= 63) ? 0 : 1;
		contextModel[uiCtxIdx] = uiMpsValue ? (uiPreCtxState - 64) : (63 - uiPreCtxState);
	}
}