#include <stdio.h>
#include "Common.h"
#include "MaDpbMan.h"
class CHevcEnc
{
public:
	CHevcEnc();
	~CHevcEnc();

	void SetDpbMan(CDpbManage* pDpbMan);
	void KickOffEnc();

public:
	CDpbManage *m_pDpbMan;
	GlobalParam *m_pGlobalParam;
	

};