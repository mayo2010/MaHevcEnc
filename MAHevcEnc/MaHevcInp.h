#ifndef _HEVC_INP_H
#define _HEVC_INP_H
#include "Common.h"
class CHevcInp
{
public:
	CHevcInp();
	~CHevcInp();
public:
	uint8 SearchOneCuBestIntraMode(uint32 uiCuX, uint32 uiCuY, 
		uint8 uiDepth, uint8 uiCurCuIdx,uint8 uiCurLog2CuSize);
};



#endif