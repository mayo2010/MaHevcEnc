#include <stdlib.h>
#include <memory.h>
#include "Common.h"

CYuvReader::CYuvReader()
{
	m_pSrcImg = NULL;
}

CYuvReader::~CYuvReader()
{

}

void CYuvReader::SetCommonParam(const GlobalParam *pGloParams)
{
	m_uiImgWidth = pGloParams->uiOriWidth;
	m_uiImgHeight = pGloParams->uiOriHeight;
	memcpy(&m_InpuYuvPath[0], &pGloParams->inpuYuvPath[0], sizeof(char)*MAX_LENGTH);
}

void CYuvReader::SetSrcImgPtr(Pel *pSrcImg)
{
	m_pSrcImg = pSrcImg;
}

void CYuvReader::ReadOneFrmData(uint32 uiFrmIdx)
{

}