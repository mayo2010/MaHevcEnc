#include "MaDpbMan.h"

CDpbManage::CDpbManage()
{
	m_uiCurFrmIdx = 0;
	m_uiIdrPeriod = 0;

	//init the m_DpbState

	for(uint32 i = 0; i < MAX_DPB_SIZE; i++)
	{
		m_DpbState.refListInfo[i].bUsed = false;
		m_DpbState.refListInfo[i].uiBufIdx = i;
		m_DpbState.refListInfo[i].uiFrmIdx = 0;
		m_DpbState.refListInfo[i].uiPoc = 0;
	}
	m_DpbState.uiCurBufIdx = 0;//cur frame
	memset(&m_DpbState.uiForwardRefList[0], 0x0, sizeof(uint32) * MAX_REF_NUM);
	m_DpbState.uiForwardRefNum = 1;//only support IPPPPP....mode
}

CDpbManage::~CDpbManage()
{

}

void CDpbManage::SetCurFrmIdx(uint32 uiFrmIdx)
{
	m_uiCurFrmIdx = uiFrmIdx;
}

void CDpbManage::SetIdrPeriod(uint32 uiPeriod)
{
	m_uiIdrPeriod = uiPeriod;
}

uint32 CDpbManage::GetCurFrmPoc(uint32 uiFrmIdx)
{
	return (m_uiIdrPeriod == 0)? uiFrmIdx : (uiFrmIdx % m_uiIdrPeriod);
}

uint32 CDpbManage::GetCurFrmBufIdx()
{
	for(uint32 i = 0; i < MAX_DPB_SIZE;i++)
	{
		if(m_DpbState.refListInfo[i].bUsed == false)
			return i;
	}
}

void CDpbManage::UpDateDpb(uint32 uiSliceType)
{
	uint32 uiCurFrmBufIdx = GetCurFrmBufIdx();
	uint32 uiCurFrmPoc = GetCurFrmPoc(m_uiCurFrmIdx);
	m_DpbState.refListInfo[uiCurFrmBufIdx].bUsed = true;
	m_DpbState.refListInfo[uiCurFrmBufIdx].uiFrmIdx = m_uiCurFrmIdx;
	m_DpbState.refListInfo[uiCurFrmBufIdx].uiPoc = uiCurFrmPoc;

	if(uiSliceType != HEVC_I_SLICE)
	{

	}


}