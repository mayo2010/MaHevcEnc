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


#endif