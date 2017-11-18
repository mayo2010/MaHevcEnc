#include <stdio.h>
#include "Common.h"
#include "MaDpbMan.h"
#include "HevcEntropy.h"
#include "MaHevcDbk.h"
#include "MaHevcInp.h"
#include "MaHevcMe.h"
class CHevcEnc
{
public:
	CHevcEnc();
	~CHevcEnc();

	void SetGloParams(GlobalParam *pGloParams);
	void KickOffEnc();
	void EncInit();
	void GetRefImg();
	void GetCurFrmBuf();
	uint32 GetImgWidth();
	uint32 GetImgHeight();
	uint32 GetEncFrmNum();


public:
	CDpbManage   *m_pDpbMan;
	CHevcEntropy *m_pHevcEntropy;
	CHevcMe      *m_pHevcMe; 
	CYuvReader   *m_pYuvReader;
public:
	Pel *m_pDpbBuffer[MAX_DPB_SIZE];
	Pel *m_pCurReconImg;
	Pel *m_pRefImg;
	Pel *m_pSrcImg;//store original img read from file
	GlobalParam m_gGloParams;
	uint32 m_uiPicWidthInCtu;
	uint32 m_uiPicHeightInCtu;
};