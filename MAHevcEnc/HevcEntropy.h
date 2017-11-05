#ifndef _HEVC_ENTROPY_
#define _HEVC_ENTROPY_

#include "Common.h"


class CHevcEntropy
{
public:
	CHevcEntropy();
	~CHevcEntropy();
	void ResetHevcEntropy();//entropy init
	void InitBuffer(HEVC_SLICE_TYPE sliceType, uint8* contextModel, int qp, uint8* ctxModel, int size);

private:
	int m_iVlLow;
	int m_iVlCurrRange;
	int m_iBitsOutStanding;
	BOOL m_bFirstBitFlag;
	uint8       m_contextState[160]; // MAX_OFF_CTX_MOD + padding
	

};



#endif