#ifndef _MA_DPB_MAN
#define _MA_DPB_MAN
#include "Common.h"

typedef struct _RefListInfo
{
	uint32 uiPoc;//
	uint32 uiFrmIdx;//
	uint32 uiBufIdx;//
	bool   bUsed;
}RefListInfo;
typedef struct _DPBState
{
	uint32      uiCurBufIdx;
	uint32      uiForwardRefNum;
	uint32      uiForwardRefList[MAX_REF_NUM];//L0
	RefListInfo refListInfo[MAX_DPB_SIZE];
}DPBState;

class CDpbManage
{
public:
	CDpbManage();
	~CDpbManage();
	uint32 GetCurFrmPoc(uint32 uiFrmIdx);
	uint32 GetCurFrmBufIdx();
	void UpDateDpb(uint32 uiSliceType);//
	void SetCurFrmIdx(uint32 uiFrmIdx);
	void SetIdrPeriod(uint32 uiPeriod);
public:
	DPBState m_DpbState;
	uint32 m_uiIdrPeriod;//used for calculating poc
	uint32 m_uiCurFrmIdx;
};



#endif