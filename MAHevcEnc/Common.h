#ifndef _COMMON_
#define _COMMON_

typedef unsigned int uint32;
typedef unsigned int BOOL;
typedef unsigned char uint8;
#define MAX_DPB_SIZE 16
#define MAX_REF_NUM  8

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
#endif