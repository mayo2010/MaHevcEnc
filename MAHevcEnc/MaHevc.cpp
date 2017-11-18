#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include "MaHevc.h"

CHevcEnc::CHevcEnc()
{
	m_pHevcEntropy = NULL;
	m_pHevcMe      = NULL;
	m_pDpbMan      = NULL;
	m_pYuvReader   = NULL;
}

CHevcEnc::~CHevcEnc()
{
	if(m_pDpbMan)
	{
		delete m_pDpbMan;
		m_pDpbMan = NULL;
	}
	if(m_pHevcEntropy)
	{
		delete m_pHevcEntropy;
		m_pHevcEntropy = NULL;
	}
	if(m_pHevcMe)
	{
		delete m_pHevcMe;
		m_pHevcMe = NULL;
	}
}

void CHevcEnc::SetGloParams(GlobalParam *pGloParams)
{
	assert(pGloParams != NULL);
	memcpy(&m_gGloParams, pGloParams, sizeof(GlobalParam));
}

//start encoding
void CHevcEnc::KickOffEnc()
{
	uint32 uiSliceType = 0;
	EncInit();
	uint32 uiEncFrmNum = GetEncFrmNum();

	//here coding VPS
	//here coding SPS
	for(uint32 uiFrmIdx = 0; uiFrmIdx < uiEncFrmNum; uiFrmIdx++)
	{
		uiSliceType = (uiFrmIdx == 0) ? HEVC_I_SLICE : HEVC_P_SLICE;
		m_pDpbMan->SetCurFrmIdx(uiFrmIdx);
		m_pDpbMan->UpDateDpb(uiSliceType);
		m_pYuvReader->ReadOneFrmData(uiFrmIdx);
		//here coding pps
		for(uint32 uiSlcIdx = 0; uiSlcIdx < 1; uiSlcIdx++)//currently, only support one slice
		{
			//here coding slice header
			for(uint32 y = 0; y < m_uiPicHeightInCtu; y++)
			{
				for(uint32 x = 0; x < m_uiPicWidthInCtu; x++)
				{
					//here encode one CTU as raster order
				}
			}
		}
	}
}

void CHevcEnc::EncInit()
{
	uint32 uiWidth = GetImgWidth();
	uint32 uiHeight = GetImgHeight();
	assert(uiWidth != 0 && uiHeight != 0);
	for(uint32 i = 0; i < MAX_DPB_SIZE; i++)
	{
		m_pDpbBuffer[i] = (Pel*)malloc(sizeof(Pel) * uiWidth * uiHeight * 1.5);
		assert(m_pDpbBuffer[i] != NULL);
	}
	m_pSrcImg = (Pel*)malloc(sizeof(Pel) * uiWidth * uiHeight * 1.5);

	m_uiPicWidthInCtu = (uiWidth + (MAX_CU_SIZE >> 1)) >> LOG2_MAX_CU_SIZE;
	m_uiPicHeightInCtu = (uiHeight + (MAX_CU_SIZE >> 1)) >> LOG2_MAX_CU_SIZE;

	m_pYuvReader = new CYuvReader();
	m_pYuvReader->SetCommonParam(&m_gGloParams);
	m_pYuvReader->SetSrcImgPtr(m_pSrcImg);
}

uint32 CHevcEnc::GetImgWidth()
{
	return m_gGloParams.uiOriWidth;
}

uint32 CHevcEnc::GetImgHeight()
{
	return m_gGloParams.uiOriHeight;
}

uint32 CHevcEnc::GetEncFrmNum()
{
	return m_gGloParams.uiEncFrameNum;
}

void CHevcEnc::GetRefImg()
{
	m_pRefImg = m_pDpbBuffer[m_pDpbMan->m_DpbState.uiForwardRefList[0]];//refIdxL0=0
}

void CHevcEnc::GetCurFrmBuf()
{
	m_pCurReconImg = m_pDpbBuffer[m_pDpbMan->m_DpbState.uiCurBufIdx];
}