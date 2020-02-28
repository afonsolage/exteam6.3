#include "StdAfx.h"
#include "ReferralSystem.h"
#include "..\\include\\Readscript.h"
#include "user.h"
#include "DBSockMng.h"
#include "GameMain.h"
#include "logproc.h"
#include "Message.h"
#include "ExUser.h"
#include "ExLicense.h"

#if(CUSTOM_REFERAL_SYSTEM)

CReferralSystem g_ReferralSystem;

CReferralSystem::CReferralSystem()
{
	this->m_bActive = true;

	this->m_Data.clear();
}

CReferralSystem::~CReferralSystem()
{
}

void CReferralSystem::Load()
{
	this->m_bActive = true;

	if(!g_ExLicense.user.ReferralSystem)
	{
		this->m_bActive = false;
		return;
	}

	this->m_Data.clear();

	this->Read(gDirPath.GetNewPath("ExData\\ReferralSystem.ini"));
}

void CReferralSystem::Read(char* FileName)
{
	SMDToken Token;

	SMDFile = fopen(FileName, "r");

	if(!SMDFile)
	{
		MsgBox("[Referral System] %s file not found", FileName);
		return;
	}

	while(true)
	{
		Token = GetToken();

		if(Token == END)
		{
			break;
		}

		int iGroup = (int)TokenNumber;

		while(true)
		{
			Token = GetToken();

			if(!strcmp("end", TokenString))
			{
				break;
			}

			REFERRAL_DATA Info;

			Info.UserNeedLevel = (int)TokenNumber;

			Token = GetToken();
			Info.UserNeedReset = (int)TokenNumber;

			Token = GetToken();
			Info.UserNeedGrand = (int)TokenNumber;

			Token = GetToken();
			Info.MasterRewardCredit = (int)TokenNumber;

			Token = GetToken();
			Info.MasterRewardWCoinC = (int)TokenNumber;

			Token = GetToken();
			Info.MasterRewardWCoinP = (int)TokenNumber;

			Token = GetToken();
			Info.MasterRewardWCoinG = (int)TokenNumber;

			Token = GetToken();
			Info.MasterRewardPremiumType = (int)TokenNumber;

			Token = GetToken();
			Info.MasterRewardPremiumTime = (int)TokenNumber;

			Token = GetToken();
			Info.MasterRewardBonus = (int)TokenNumber;

			Token = GetToken();
			Info.UserRewardCredit = (int)TokenNumber;

			Token = GetToken();
			Info.UserRewardWCoinC = (int)TokenNumber;

			Token = GetToken();
			Info.UserRewardWCoinP = (int)TokenNumber;

			Token = GetToken();
			Info.UserRewardWCoinG = (int)TokenNumber;

			Token = GetToken();
			Info.UserRewardPremiumType = (int)TokenNumber;

			Token = GetToken();
			Info.UserRewardPremiumTime = (int)TokenNumber;

			Token = GetToken();
			Info.UserRewardBonus = (int)TokenNumber;

			this->m_Data.push_back(Info);
		}
	}

	fclose(SMDFile);

	LogAdd("%s file load!", FileName);
}

void CReferralSystem::CGReqMasterInfo(PMSG_REQ_REFERRAL_MASTER_INFO* lpMsg, int aIndex)
{
	if(!this->m_bActive)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	this->GDReqMasterInfo(aIndex, lpMsg->PageNumber);
}

void CReferralSystem::GDReqMasterInfo(int aIndex, int Page)
{
	if(!this->m_bActive)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_GDREQ_REFERRAL_INFO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x14, sizeof(pMsg));
	pMsg.aIndex = aIndex;

	char szName[11] = { 0 };
	memcpy(szName, lpUser->Name, sizeof(szName));
	szName[10] = 0;

	memcpy(pMsg.Name, szName, sizeof(szName)-1);
	pMsg.PageNumber = Page;

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CReferralSystem::DGAnsMasterInfo(PMSG_DGANS_REFERRAL_MASTER_INFO* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_ANS_REFERRAL_MASTER_INFO pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xFA, 0xAE, sizeof(pMsg));
	pMsg.RefferalMaxStage = this->m_Data.size();
	pMsg.ReferralCount = lpMsg->Count;
	pMsg.ReferralTotal = lpMsg->TotalCount;

	for(int i = 0; i < REFERRAL_MAXDATA; i++)
	{
		lpUser->RefferalMaster[i] = lpMsg->Player[i].RefferalMaster;
		lpUser->RefferalUserLevel[i] = lpMsg->Player[i].RefferalUserLevel;
		lpUser->RefferalUserReset[i] = lpMsg->Player[i].RefferalUserReset;
		lpUser->RefferalUserGrand[i] = lpMsg->Player[i].RefferalUserGrand;

		memcpy(pMsg.Data[i].RefferalName, lpMsg->Player[i].RefferalName, sizeof(lpMsg->Player[i].RefferalName)-1);

		pMsg.Data[i].RefferalMaster = lpMsg->Player[i].RefferalMaster;
		pMsg.Data[i].UserOnline = 0;

		int ReferralIndex = gObjGetIndex(pMsg.Data[i].RefferalName);

		if(OBJMAX_RANGE(ReferralIndex))
		{
			LPOBJ lpReferral = &gObj[ReferralIndex];

			if(lpReferral->Connected == PLAYER_PLAYING)
			{
				pMsg.Data[i].UserOnline = 1;
			}
		}

		pMsg.Data[i].UserLevel = lpMsg->Player[i].RefferalUserLevel;
		pMsg.Data[i].UserReset = lpMsg->Player[i].RefferalUserReset;
		pMsg.Data[i].UserGrand = lpMsg->Player[i].RefferalUserGrand;

		int iStage = pMsg.Data[i].RefferalMaster;

		if(pMsg.RefferalMaxStage < iStage)
		{
			continue;
		}

		REFERRAL_DATA * pData = &this->m_Data[iStage];

		pMsg.Data[i].UserNeedLevel = pData->UserNeedLevel;
		pMsg.Data[i].UserNeedReset = pData->UserNeedReset;
		pMsg.Data[i].UserNeedGrand = pData->UserNeedGrand;
		pMsg.Data[i].MasterRewardCredit = pData->MasterRewardCredit;
		pMsg.Data[i].MasterRewardWCoinC = pData->MasterRewardWCoinC;
		pMsg.Data[i].MasterRewardWCoinP = pData->MasterRewardWCoinP;
		pMsg.Data[i].MasterRewardWcoinG = pData->MasterRewardWCoinG;
		pMsg.Data[i].MasterRewardBonus = pData->MasterRewardBonus;
		pMsg.Data[i].MasterRewardPremiumType = pData->MasterRewardPremiumType;
		pMsg.Data[i].MasterRewardPremiumTime = pData->MasterRewardPremiumTime;
	}

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CReferralSystem::CGMasterResult(PMSG_CGREQ_REFERRAL_MASTER_REWARD* lpMsg, int aIndex)
{
	if(!this->m_bActive)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int iNumber = lpMsg->ReferralNumber;

	if(!CHECK_LIMIT(iNumber, REFERRAL_MAXDATA))
	{
		return;
	}

	int iStage = lpUser->RefferalMaster[iNumber];

	bool bResult = true;

	if(iStage >= this->m_Data.size())
	{
		MsgOutput(aIndex, "[Referral] Master Stage Error");
		return;
	}

	REFERRAL_DATA * pData = &this->m_Data[iStage];

	if(lpUser->RefferalUserLevel[iNumber] < pData->UserNeedLevel)
	{
		bResult = false;
	}

	if(lpUser->RefferalUserReset[iNumber] < pData->UserNeedReset)
	{
		bResult = false;
	}

	if(lpUser->RefferalUserGrand[iNumber] < pData->UserNeedGrand)
	{
		bResult = false;
	}

	if(bResult == false)
	{
		MsgOutput(aIndex, "[Referral] Master Check Error");
	}

	this->GDReqMasterUpdate(aIndex, lpMsg->ReferalName, iNumber);
}

void CReferralSystem::GDReqMasterUpdate(int aIndex, char* Name, int Num)
{
	if(!this->m_bActive)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_GD_REFERRAL_MASTER_UPDATE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x15, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.Number = Num;

	char szName[11] = { 0 };
	memcpy(szName, lpUser->Name, sizeof(szName));
	szName[10] = 0;
	memcpy(pMsg.Name, szName, sizeof(szName)-1);

	char szAccount[11] = { 0 };
	memcpy(szAccount, Name, sizeof(szAccount));
	szAccount[10] = 0;
	memcpy(pMsg.ReferalName, szAccount, sizeof(szAccount)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CReferralSystem::DGAnsMasterUpdate(PMSG_GDANS_REFERRAL_MASTER_UPDATE* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!lpMsg->Result)
	{
		MsgOutput(aIndex, "[Referral Update Error]");
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int iNumber = lpMsg->Number;

	if(!CHECK_LIMIT(iNumber, REFERRAL_MAXDATA))
	{
		return;
	}

	int iStage = lpUser->RefferalMaster[iNumber];

	REFERRAL_DATA * pData = &this->m_Data[iStage];

	if(pData->MasterRewardCredit > 0)
	{
		lpUser->ExCred += pData->MasterRewardCredit;
		MessageChat(aIndex, "@[Referral] Master Crecit +%d", pData->MasterRewardCredit);
	}

	if(pData->MasterRewardWCoinC > 0)
	{
		lpUser->GameShop.WCoinC += pData->MasterRewardWCoinC;
		gGameShop.GDSaveUserInfo(aIndex);
		MessageChat(aIndex, "@[Referral] Master WCoinC +%d", pData->MasterRewardWCoinC);
	}

	if(pData->MasterRewardWCoinP > 0)
	{
		lpUser->GameShop.WCoinP += pData->MasterRewardWCoinP;
		gGameShop.GDSaveUserInfo(aIndex);
		MessageChat(aIndex, "@[Referral] Master WCoinP +%d", pData->MasterRewardWCoinP);
	}

	if(pData->MasterRewardWCoinG > 0)
	{
		lpUser->GameShop.GoblinPoint += pData->MasterRewardWCoinG;
		gGameShop.GDSaveUserInfo(aIndex);
		MessageChat(aIndex, "@[Referral] Master WCoinG +%d", pData->MasterRewardWCoinG);
	}

	if(pData->MasterRewardPremiumType > 0 && pData->MasterRewardPremiumTime > 0)
	{
		lpUser->PremiumTimeType = pData->MasterRewardPremiumType;
		lpUser->PremiumTime += pData->MasterRewardPremiumTime * 3600;
		MessageChat(aIndex, "@[Referral] Master Premium Type: %d Time: +%d h", pData->MasterRewardPremiumType, pData->MasterRewardPremiumTime);
	}

	ExUserDataSend(aIndex);

	lpUser->RefferalMaster[iNumber]++;
	iStage = lpUser->RefferalMaster[iNumber];

	pData = &this->m_Data[iStage];

	PMSG_CGANS_REFERRAL_MASTER_REWARD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xAE, sizeof(pMsg));
	pMsg.ReferralNumber = iNumber;
	pMsg.UserNeedLevel = pData->UserNeedLevel;
	pMsg.UserNeedReset = pData->UserNeedReset;
	pMsg.UserNeedGrand = pData->UserNeedGrand;
	pMsg.MasterRewardCredit = pData->MasterRewardCredit;
	pMsg.MasterRewardWCoinC = pData->MasterRewardWCoinC;
	pMsg.MasterRewardWCoinP = pData->MasterRewardWCoinP;
	pMsg.MasterRewardWcoinG = pData->MasterRewardWCoinG;
	pMsg.MasterRewardBonus = pData->MasterRewardBonus;
	pMsg.MasterRewardPremiumType = pData->MasterRewardPremiumType;
	pMsg.MasterRewardPremiumTime = pData->MasterRewardPremiumTime;
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CReferralSystem::CGReqUserInfo(PMSG_REQ_REFERRAL_USER_INFO* lpMsg, int aIndex)
{
	if(!this->m_bActive)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	this->GDReqUserInfo(aIndex);
}

void CReferralSystem::GDReqUserInfo(int aIndex)
{
	if(!this->m_bActive)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_GDREQ_REFERRAL_USER_INFO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x16, sizeof(pMsg));
	pMsg.aIndex = aIndex;

	char szName[11] = { 0 };
	memcpy(szName, lpUser->AccountID, sizeof(szName));
	szName[10] = 0;

	memcpy(pMsg.Name, szName, sizeof(szName)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CReferralSystem::DGAnsUserInfo(PMSG_DGANS_REFERRAL_USER_INFO* lpMsg)
{
	if(!lpMsg->Result)
	{
		return;
	}

	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->RefferalUser = lpMsg->RefferalUser;

	int iStage = lpUser->RefferalUser;

	PMSG_ANS_REFERRAL_USER_INFO pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xAF, sizeof(pMsg));

	if(iStage < this->m_Data.size())
	{
		REFERRAL_DATA * pData = &this->m_Data[iStage];
		pMsg.RefferalMaxStage = this->m_Data.size();
		pMsg.User.RefferalUser = lpUser->RefferalUser;
		pMsg.User.ReferralNeedLevel = pData->UserNeedLevel;
		pMsg.User.ReferralNeedReset = pData->UserNeedReset;
		pMsg.User.ReferralNeedGrand = pData->UserNeedGrand;
		pMsg.User.ReferralRewardCredit = pData->UserRewardCredit;
		pMsg.User.ReferralRewardWCoinC = pData->UserRewardWCoinC;
		pMsg.User.ReferralRewardWCoinP = pData->UserRewardWCoinP;
		pMsg.User.ReferralRewardWcoinG = pData->UserRewardWCoinG;
		pMsg.User.ReferralRewardBonus = pData->UserRewardBonus;
		pMsg.User.ReferralRewardPremiumType = pData->UserRewardPremiumType;
		pMsg.User.ReferralRewardPremiumTime = pData->UserRewardPremiumTime;
	}

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CReferralSystem::CGUserResult(PMSG_CGREQ_REFERRAL_USER_REWARD* lpMsg, int aIndex)
{
	if(!this->m_bActive)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	bool bResult = true;

	int iStage = lpUser->RefferalUser;

	if(iStage >= this->m_Data.size())
	{
		MsgOutput(aIndex, "[Referral] User Stage Error");
		return;
	}

	REFERRAL_DATA * pData = &this->m_Data[iStage];

	if(lpUser->Level < pData->UserNeedLevel)
	{
		bResult = false;
	}

	if(lpUser->Reset < pData->UserNeedReset)
	{
		bResult = false;
	}

	if(lpUser->GReset < pData->UserNeedGrand)
	{
		bResult = false;
	}

	if(bResult == false)
	{
		MsgOutput(aIndex, "[Referral] User Check Error");
	}

	this->GDReqUserUpdate(aIndex);
}

void CReferralSystem::GDReqUserUpdate(int aIndex)
{
	if(!this->m_bActive)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_GD_REFERRAL_USER_UPDATE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x17, sizeof(pMsg));
	pMsg.aIndex = aIndex;

	char szAccount[11] = { 0 };
	memcpy(szAccount, lpUser->AccountID, sizeof(szAccount));
	szAccount[10] = 0;
	memcpy(pMsg.ReferalName, szAccount, sizeof(szAccount)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CReferralSystem::DGAnsUserUpdate(PMSG_GDANS_REFERRAL_USER_UPDATE* lpMsg)
{
	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!lpMsg->Result)
	{
		MsgOutput(aIndex, "[Referral] User Update Error");
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int iStage = lpUser->RefferalUser;

	if(iStage >= this->m_Data.size())
	{
		MsgOutput(aIndex, "[Referral] User Stage Error");
		return;
	}

	REFERRAL_DATA * pData = &this->m_Data[iStage];

	if(pData->UserRewardCredit > 0)
	{
		lpUser->ExCred += pData->UserRewardCredit;
		MessageChat(aIndex, "@[Referral] User Crecit +%d", pData->UserRewardCredit);
	}

	if(pData->UserRewardWCoinC > 0)
	{
		lpUser->GameShop.WCoinC += pData->UserRewardWCoinC;
		gGameShop.GDSaveUserInfo(aIndex);
		MessageChat(aIndex, "@[Referral] User WCoinC +%d", pData->UserRewardWCoinC);
	}

	if(pData->UserRewardWCoinP > 0)
	{
		lpUser->GameShop.WCoinP += pData->UserRewardWCoinP;
		gGameShop.GDSaveUserInfo(aIndex);
		MessageChat(aIndex, "@[Referral] User WCoinP +%d", pData->UserRewardWCoinP);
	}

	if(pData->UserRewardWCoinG > 0)
	{
		lpUser->GameShop.GoblinPoint += pData->UserRewardWCoinG;
		gGameShop.GDSaveUserInfo(aIndex);
		MessageChat(aIndex, "@[Referral] User WCoinG +%d", pData->UserRewardWCoinG);
	}

	if(pData->UserRewardPremiumType > 0 && pData->UserRewardPremiumTime > 0)
	{
		lpUser->PremiumTimeType = pData->UserRewardPremiumType;
		lpUser->PremiumTime += pData->UserRewardPremiumTime * 3600;
		MessageChat(aIndex, "@[Referral] User Premium Type: %d Time: +%d h", pData->UserRewardPremiumType, pData->UserRewardPremiumTime);
	}

	ExUserDataSend(aIndex);

	PMSG_GCANS_REFERRAL_USER_REWARD pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB3, sizeof(pMsg));

	if(iStage < this->m_Data.size())
	{
		iStage++;
		pData = &this->m_Data[iStage];
	}

	pMsg.UserNeedLevel = pData->UserNeedLevel;
	pMsg.UserNeedReset = pData->UserNeedReset;
	pMsg.UserNeedGrand = pData->UserNeedGrand;
	pMsg.UserRewardCredit = pData->UserRewardCredit;
	pMsg.UserRewardWCoinC = pData->UserRewardWCoinC;
	pMsg.UserRewardWCoinP = pData->UserRewardWCoinP;
	pMsg.UserRewardWcoinG = pData->UserRewardWCoinG;
	pMsg.UserRewardBonus = pData->UserRewardBonus;
	pMsg.UserRewardPremiumType = pData->UserRewardPremiumType;
	pMsg.UserRewardPremiumTime = pData->UserRewardPremiumTime;
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));

	lpUser->RefferalUser++;
}

#endif