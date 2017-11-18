#include <stdio.h>
#include <string>
#include <tchar.h>
#include <iostream>
#include <assert.h>
#include <math.h>
#include <memory.h>
#include "Common.h"
#include "Command.h"
#include "HevcEntropy.h"
#include "MaDpbMan.h"
#include "MaHevc.h"


const char *globalParam[][2] = 
{
	{"-YuvInPut", "str"},
	{"-ReconPath", "str"},
	{"-OutPut", "str"},
	{"-Width", "num"},
	{"-Height", "num"},
	{"-EncFrmNum", "num"},
	{"-IntraPeriod", "num"},
	{"-SearchRng", "num"},
	{"-SearchPace", "num"},
	{"-EnFracSearch", "num"},
	{"-EnDbk", "num"},
	{"-EnSao", "num"},
	{"-EnTuSplit","num"},
	//add more here
};
void Help()
{
	printf("Please input some parameters, and the parameter's defination is below\n");
	printf("-YuvInPut: the path of yuv file\n");
	printf("-Width: the width of input yuv file\n");
	printf("-Height: the height of input yuv file\n");
	printf("-ReconPath: the output path of recon yuv\n");
	printf("-OutPut: the path of bit stream\n");
	printf("-EncFrmNum: the number of frame to be coded\n");
	printf("-IntraPeriod: the period of I frame\n");
	printf("-SearchRng: the me search range\n");
	printf("-SearchPace: the me search pace\n");
	printf("-EnFracSearch: 1: enable frac search 0: disable frac search\n");
	printf("-EnDbk: 1: enable dbk 0: disable dbk\n");
	printf("-EnSao: 1: enable sao 0: disable sao\n");
	printf("-EnTuSplit: 1: enable tu spilit 0: disable tu spilit\n");
}

void ParseSingleParam(GlobalParam& param)
{

}
void ParseParam(int argc, _TCHAR* argv[], GlobalParam& param)
{
	int iArgNum;//0 means no this parameter 1 means this parameter exsist
	Utility::CommandLine *pCmdLine = new Utility::CommandLine;
	if (pCmdLine->SplitLine(argc, argv) < 1)
	{
		Help();
		exit(-1);
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-YuvInPut"));
	if(iArgNum == 1)
	{
		tstring yuvPath = pCmdLine->GetArgument(_T("-YuvInPut"), 0);
		strcpy_s(param.inpuYuvPath, yuvPath.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-ReconPath"));
	if(iArgNum == 1)
	{
		tstring reconPath = pCmdLine->GetArgument(_T("-ReconPath"), 0);
		strcpy_s(param.recPath, reconPath.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-OutPut"));
	if(iArgNum == 1)
	{
		tstring outPut = pCmdLine->GetArgument(_T("-OutPut"), 0);
		strcpy_s(param.outPutPath, outPut.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-Width"));
	if(iArgNum == 1)
	{
		tstring width = pCmdLine->GetArgument(_T("-Width"), 0);
		param.uiOriWidth = atoi(width.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-Height"));
	if(iArgNum == 1)
	{
		tstring height = pCmdLine->GetArgument(_T("-Height"), 0);
		param.uiOriHeight = atoi(height.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-EncFrmNum"));
	if(iArgNum == 1)
	{
		tstring encFrmNum = pCmdLine->GetArgument(_T("-EncFrmNum"), 0);
		param.uiEncFrameNum = atoi(encFrmNum.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-IntraPeriod"));
	if(iArgNum == 1)
	{
		tstring intraPeriod = pCmdLine->GetArgument(_T("-IntraPeriod"), 0);
		param.uiIntraPeriod = atoi(intraPeriod.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-SearchRng"));
	if(iArgNum == 1)
	{
		tstring SearchRng = pCmdLine->GetArgument(_T("-SearchRng"), 0);
		param.uiMeSearchRng = atoi(SearchRng.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-SearchPace"));
	if(iArgNum == 1)
	{
		tstring SearchPace = pCmdLine->GetArgument(_T("-SearchPace"), 0);
		param.uiMeSearchPace = atoi(SearchPace.c_str());
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-EnFracSearch"));
	if(iArgNum == 1)
	{
		tstring EnFracSearch = pCmdLine->GetArgument(_T("-EnFracSearch"), 0);
		param.bEnFracSearch = (atoi(EnFracSearch.c_str()) == 1);
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-EnDbk"));
	if(iArgNum == 1)
	{
		tstring EnDbk = pCmdLine->GetArgument(_T("-EnDbk"), 0);
		param.bEnDbk = (atoi(EnDbk.c_str()) == 1);
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-EnSaok"));
	if(iArgNum == 1)
	{
		tstring EnSaok = pCmdLine->GetArgument(_T("-EnSaok"), 0);
		param.bEnSao = (atoi(EnSaok.c_str()) == 1);
	}

	iArgNum = pCmdLine->GetArgumentCount(_T("-EnTuSplit"));
	if(iArgNum == 1)
	{
		tstring EnTuSplit = pCmdLine->GetArgument(_T("-EnTuSplit"), 0);
		param.bEnTuSplit = (atoi(EnTuSplit.c_str()) == 1);
	}

}
int _tmain(int argc, _TCHAR* argv[])
{
	GlobalParam inputParam;
	ParseParam(argc, argv, inputParam);
	CHevcEnc *pHevcEnc = new CHevcEnc();
	pHevcEnc->SetGloParams(&inputParam);
	return 0;
}