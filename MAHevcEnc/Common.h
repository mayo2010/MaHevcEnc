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

#define MAX_LENGTH 1024
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