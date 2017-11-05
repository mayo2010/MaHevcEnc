#ifndef _MA_DPB_MAN
#define _MA_DPB_MAN
#include "Common.h"

typedef struct _RefListInfo
{
	uint32 uiPoc;
	uint32 uiFrmIdx;
	uint32 uiBufIdx;
	bool   bUsed;
}RefListInfo;
typedef struct _DPBState
{
	uint32      uiCurBufIdx;
	uint32      uiForwardRefNum;
	uint32      uiForwardRefList[MAX_REF_NUM];
	RefListInfo refListInfo[MAX_DPB_SIZE];
}DPBState;



#endif