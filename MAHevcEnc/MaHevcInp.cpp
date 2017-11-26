#include <assert.h>
#include "MaHevcInp.h"

CHevcInp::CHevcInp()
{

}

CHevcInp::~CHevcInp()
{

}

uint8 CHevcInp::SearchOneCuBestIntraMode(uint32 uiCuX, uint32 uiCuY, 
										 uint8 uiDepth, uint8 uiCurCuIdx, uint8 uiCurLog2CuSize)
{
	assert(uiDepth <= 3);//the min cu size is 8x8
	//search cur cu best intra mode for no split
	SearchOneCuBestIntraMode(uiCuX, uiCuY, uiDepth, uiCurCuIdx, uiCurLog2CuSize);
	if(uiDepth < 3)
	{
		uint8 uiXOffset = 1<<( uiCurLog2CuSize-1);
		uint8 uiYOffset = uiXOffset;
		SearchOneCuBestIntraMode(uiCuX, uiCuY, uiDepth + 1, uiCurCuIdx, uiCurLog2CuSize-1);
		SearchOneCuBestIntraMode(uiCuX + uiXOffset, uiCuY, uiDepth + 1, uiCurCuIdx +1, uiCurLog2CuSize-1);
		SearchOneCuBestIntraMode(uiCuX, uiCuY + uiYOffset, uiDepth + 1, uiCurCuIdx + 2, uiCurLog2CuSize-1);
		SearchOneCuBestIntraMode(uiCuX + uiXOffset, uiCuY + uiYOffset, uiDepth + 1, uiCurCuIdx+ 3, uiCurLog2CuSize-1);
	}

	return 1;
}