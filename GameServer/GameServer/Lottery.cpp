#include "StdAfx.h"
#include "Lottery.h"
#include "..//include//ReadScript.h"
#include "logproc.h"
#include "GameMain.h"
#include "ExUser.h"

#if(CUSTOM_LOTTERY)

CLottery g_Lottery;

CLottery::CLottery()
{
}

CLottery::~CLottery()
{
}

void CLottery::Init()
{
	this->m_Data.clear();
}

void CLottery::Load()
{
	this->Init();

	this->Read(gDirPath.GetNewPath("ExData\\Lottery.dat"));
}

void CLottery::Read(char* filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MsgBox("[Lottery] %s file not found", filename);

		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if(Token == END)
		{
			break;
		}

		int Type = (int)TokenNumber;

		while(true)
		{
			if(Type == 0) // -> Config
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_Enable = TokenNumber;

				Token = GetToken();
				this->m_ID = TokenNumber;

				Token = GetToken();
				this->m_Price = TokenNumber;

				Token = GetToken();
				this->m_Fund = TokenNumber;

				Token = GetToken();
				this->m_NpcClass = TokenNumber;

				Token = GetToken();
				this->m_NpcMap = TokenNumber;

				Token = GetToken();
				this->m_NpcX = TokenNumber;

				Token = GetToken();
				this->m_NpcY = TokenNumber;
			}
			else if(Type == 1) // -> Reward
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				LOTTERY_INFO lpData;

				lpData.ID = TokenNumber;

				for(int i = 0; i < 10; i++)
				{
					Token = GetToken();
					lpData.Info[i].Type = TokenNumber;

					Token = GetToken();
					lpData.Info[i].Value = TokenNumber;

					Token = GetToken();
					lpData.Info[i].Index = TokenNumber;

					Token = GetToken();
					lpData.Info[i].Level = TokenNumber;

					Token = GetToken();
					lpData.Info[i].Rate = TokenNumber;
				}

				this->m_Data.push_back(lpData);
			}
		}
	}

	fclose(SMDFile);
}

bool CLottery::NpcDialog(int aIndex, int aNpcIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if( lpNpc->Class		== this->m_NpcClass &&
		lpNpc->MapNumber	== this->m_NpcMap &&
		lpNpc->X			== this->m_NpcX &&
		lpNpc->Y			== this->m_NpcY )
	{
		this->GCLotteryData(aIndex);

		return true;
	}

	return false;
}

int CLottery::LotteryRand(int aIndex, int RandNum)
{
	int iRand = rand() % 10;

	return iRand;
}

void CLottery::LotteryWin(int aIndex, int RandNum)
{
	int iNull = 0;

	LPOBJ lpUser = &gObj[aIndex];

	LOTTERY_DATA * lpLottery = &this->m_Data[iNull].Info[RandNum];

	if(lpLottery->Type == eLOTTERY_FUND_MAIN)
	{
		lpUser->GameShop.WCoinC += lpLottery->Value;
		gGameShop.GDSaveUserInfo(lpUser->m_Index);
		ExUserDataSend(aIndex);
		MsgOutput(aIndex, "[Loterry] WcoinC +%d", lpLottery->Value);
	}
	else if(lpLottery->Type == eLOTTERY_ZEN)
	{
		lpUser->Money += lpLottery->Value;
		GCMoneySend(aIndex, lpUser->Money);
		MsgOutput(aIndex, "[Loterry] Money +%d", lpLottery->Value);
	}
	else if(lpLottery->Type == eLOTTERY_WCOINC)
	{
		lpUser->GameShop.WCoinC += lpLottery->Value;
		gGameShop.GDSaveUserInfo(lpUser->m_Index);
		ExUserDataSend(aIndex);
		MsgOutput(aIndex, "[Loterry] WcoinC +%d", lpLottery->Value);
	}
	else if(lpLottery->Type == eLOTTERY_WCOINP)
	{
		lpUser->GameShop.WCoinP += lpLottery->Value;
		gGameShop.GDSaveUserInfo(lpUser->m_Index);
		ExUserDataSend(aIndex);
		MsgOutput(aIndex, "[Loterry] WcoinP +%d", lpLottery->Value);
	}
	else if(lpLottery->Type == eLOTTERY_GOBLIN)
	{
		lpUser->GameShop.GoblinPoint += lpLottery->Value;
		gGameShop.GDSaveUserInfo(lpUser->m_Index);
		ExUserDataSend(aIndex);
		MsgOutput(aIndex, "[Loterry] Goblin +%d", lpLottery->Value);
	}
	else if(lpLottery->Type == eLOTTERY_CREDIT)
	{
		lpUser->ExCred += lpLottery->Value;
		ExUserDataSend(aIndex);
		MsgOutput(aIndex, "[Loterry] Credit +%d", lpLottery->Value);
	}
	else if(lpLottery->Type == eLOTTERY_ITEM)
	{
		lpUser->ExCred += lpLottery->Value;
		ExUserDataSend(aIndex);
		MsgOutput(aIndex, "[Loterry] I +%d", lpLottery->Value);

		ItemSerialCreateSend(aIndex, lpUser->MapNumber, lpUser->X, lpUser->Y, ITEMGET(lpLottery->Value, lpLottery->Index), lpLottery->Level, 0, 0, 0, 0, aIndex, 0, 0);
	}
	else if(lpLottery->Type == eLOTTERY_FOND_PERCENT)
	{
		lpUser->GameShop.WCoinC += lpLottery->Value;
		gGameShop.GDSaveUserInfo(lpUser->m_Index);
		ExUserDataSend(aIndex);
		MsgOutput(aIndex, "[Loterry] WcoinC +%d", lpLottery->Value);
	}
}

void CLottery::CGLotteryOpen(int aIndex)
{

	this->GCLotteryData(aIndex);
}

void CLottery::GCLotteryData(int aIndex)
{
	PMSG_LOTTERY_DATA pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xD0, sizeof(pMsg));
	memcpy(&pMsg.Data, &this->m_Data[0].Info, sizeof(pMsg.Data));
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void CLottery::CGLotteryPlay(PMSG_LOTTERY_PLAY* lpMsg, int aIndex)
{
	if(!lpMsg->Result)
	{
		return;
	}

	int iRand = this->LotteryRand(aIndex, lpMsg->Result);

	//if(iRand == lpMsg->Result)
	{
		this->LotteryWin(aIndex, lpMsg->Result);
	}

	this->GCLotteryResult(aIndex, iRand);
}

void CLottery::GCLotteryResult(int aIndex, int Result)
{
	PMSG_LOTTERY_RESULT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xD2, sizeof(pMsg));
	pMsg.Result = Result;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

#endif