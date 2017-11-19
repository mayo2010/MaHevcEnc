#include "MaDpbMan.h"

CDpbManage::CDpbManage()
{
	m_uiCurFrmIdx = 0;
	m_uiIdrPeriod = 0;

	//init the m_DpbState

	for(uint32 i = 0; i < MAX_REF_NUM; i++)
	{
		m_DpbState.refList[i].bUsed = false;
		m_DpbState.refList[i].uiBufIdx = i;
		m_DpbState.refList[i].uiFrmIdx = 0;
		m_DpbState.refList[i].uiPoc = 0;
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
		if(m_DpbState.refList[i].bUsed == false)
			return i;
	}
}

//construct refList
// get img data by uiBufIdx from DPB
void CDpbManage::UpDateDpb(uint32 uiSliceType)
{
	uint32 uiCurFrmBufIdx = GetCurFrmBufIdx();
	uint32 uiCurFrmPoc = GetCurFrmPoc(m_uiCurFrmIdx);
	uint32 uiRefIdx = 0;//we only consider one ref frame

	if(uiSliceType != HEVC_I_SLICE)
	{
		//descending order the refList in order to POC
		for(uint32 i = 0; i < MAX_REF_NUM; i++)
		{
			RefListInfo tempRefList = m_DpbState.refList[i];
			uint32 uiRefPoc = m_DpbState.refList[i].uiPoc;
			m_DpbState.uiForwardRefList[uiRefIdx] = m_DpbState.refList[i].uiBufIdx;
			for(uint32 j = i + 1; j < MAX_REF_NUM; j++)
			{
				if(m_DpbState.refList[j].uiPoc > uiRefPoc && m_DpbState.refList[j].uiPoc < uiCurFrmPoc \
					&& m_DpbState.refList[j].bUsed == true)//changing i and j
				{
					uiRefPoc = m_DpbState.refList[j].uiPoc;
					m_DpbState.refList[i] = m_DpbState.refList[j];
					m_DpbState.refList[j] = tempRefList;
					tempRefList = m_DpbState.refList[i];
					m_DpbState.uiForwardRefList[uiRefIdx] = m_DpbState.refList[i].uiBufIdx;
				}
			}
			uiRefIdx++;
		}
	}

	m_DpbState.refList[uiCurFrmBufIdx].bUsed = true;
	m_DpbState.refList[uiCurFrmBufIdx].uiFrmIdx = m_uiCurFrmIdx;
	m_DpbState.refList[uiCurFrmBufIdx].uiPoc = uiCurFrmPoc;
}