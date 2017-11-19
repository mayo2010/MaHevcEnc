#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <assert.h>
#include "Common.h"

CYuvReader::CYuvReader()
{
	m_pSrcImg = NULL;
	m_pYuvFile = NULL;
}

CYuvReader::~CYuvReader()
{

}

void CYuvReader::SetCommonParam(const GlobalParam *pGloParams)
{
	m_uiImgWidth = pGloParams->uiOriWidth;
	m_uiImgHeight = pGloParams->uiOriHeight;
	m_pYuv = pGloParams->inpuYuvPath;
}

void CYuvReader::SetSrcImgPtr(Pel *pSrcImg)
{
	m_pSrcImg = pSrcImg;
}

void CYuvReader::ReadOneFrmData(uint32 uiFrmIdx)
{
	m_pYuvFile = fopen(m_pYuv, "rb");
	if(m_pYuvFile == NULL)
	{
		printf("Open input yuv fail!!\n");
		return ;
	}
	uint32 uiOneFrmSize = m_uiImgWidth * m_uiImgHeight * 1.5;
	long lSeekSize = uiOneFrmSize * uiFrmIdx;
	fseek(m_pYuvFile, lSeekSize, SEEK_SET);
	fread(m_pSrcImg, uiOneFrmSize, 1, m_pYuvFile);
	fclose(m_pYuvFile);
}