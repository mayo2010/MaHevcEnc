#ifndef _COMMON_
#define _COMMON_
#include <memory.h>
#include <stdio.h>
typedef unsigned int uint32;
typedef unsigned int BOOL;
typedef unsigned char uint8;
typedef unsigned char Pel;
#define MAX_DPB_SIZE 16
#define MAX_REF_NUM  8

#define MAX_CU_SIZE 64
#define LOG2_MAX_CU_SIZE 6
#define MAX_LENGTH 1024
typedef short coeff_t;
template<typename T>
inline T x265_min(T a, T b) { return a < b ? a : b; }

template<typename T>
inline T x265_max(T a, T b) { return a > b ? a : b; }

template<typename T>
inline T x265_clip3(T minVal, T maxVal, T a) { return x265_min(x265_max(minVal, a), maxVal); }

enum HEVC_SLICE_TYPE
{
	HEVC_I_SLICE = 0,
	HEVC_P_SLICE,
	HEVC_B_SLICE,
	HEVC_INVALID_SLICE
};

enum CU_PART_MODE
{
	PART_2Nx2N = 0,
	PART_2NxN,
	PART_Nx2N,
	PART_NxN,
	MAX_PART_TYPE
};

typedef struct _GlobalParam
{
	_GlobalParam()
	{
		memset(this, 0x0, sizeof(_GlobalParam));
	}
	char	inpuYuvPath[MAX_LENGTH];//input yuv
	char	recPath[MAX_LENGTH];//recon yuv
	char	outPutPath[MAX_LENGTH];//bit stream
	uint32	uiOriWidth;
	uint32	uiOriHeight;
	uint32	uiEncFrameNum;//how many frames to be coded
	uint32	uiIntraPeriod;
	uint32	uiMeSearchRng;
	uint8	uiMeSearchPace;
	bool	bEnFracSearch;//
	bool	bEnDbk;
	bool	bEnSao;
	bool	bEnTuSplit;
}GlobalParam;

typedef struct _TuInfo
{

}TuInfo;
typedef struct _PuInfo
{
	uint8 uMergeIdx : 3;
	uint8 bMergeFlag : 1;
	uint8 bMvpL0Flag : 1;

}PuInfo;

typedef struct _TuCoeff8x8
{
	coeff_t tuCoeff[8][8];
}TuCoeff8x8;

typedef struct _CuInfo
{
	uint8 uCuIdxInCtu;
	uint8 uIntraPredMode;
	uint8 bSplitCuFlag : 1;
	uint8 uLog2CuSize  : 6;//support 64x64 cu
	uint8 bCuSkipFlag  : 1;

	uint8 bCuTransByPass : 1;
	uint8 bPredModeFlag : 1;
	uint8 UCuPartMode : 2;
	uint8 bPcmFlag : 1;


	PuInfo puInfos[4];
	TuInfo tuInfos[4];//only when PART_MODE != PART_2Nx2N,one cu can split into 4 tu in P slice
}CuInfo;
//store all the info need to be coded
typedef struct _CtuInfo
{
	CuInfo cuInfos[64];
	TuCoeff8x8 allTuCoeff[64];//
}CtuInfo;

class CYuvReader
{
public:
	CYuvReader();
	~CYuvReader();
	void SetCommonParam(const GlobalParam *pGloParams);
	void SetSrcImgPtr(Pel *pSrcImg);
	void ReadOneFrmData(uint32 uiFrmIdx);
public:
	char   m_InpuYuvPath[MAX_LENGTH];
	Pel *m_pSrcImg;
	uint32 m_uiImgWidth;
	uint32 m_uiImgHeight;
	FILE *m_pYuvFile;
	const char *m_pYuv;

};
#endif