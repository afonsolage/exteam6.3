#include "StdAfx.h"
#include "..\common\winutil.h"
#include "..\include\prodef.h"
#include "..\include\ReadScript.h"
#include "GameMain.h"
#include "user.h"
#include "logproc.h"
#include "DBSockMng.h"
#include "MUHelper.h"
#include "ExFunction.h"
#include "ObjUseSkill.h"
#include "ExUser.h"
#include "MUHelperOffline.h"

#ifdef MUHELPER
// -------------------------------------------------------------------------------

MUHelper	g_MUHelper;
// -------------------------------------------------------------------------------

MUHelper::MUHelper()
{
	this->Init();
}
// -------------------------------------------------------------------------------

MUHelper::~MUHelper()
{
	// ----
}
// -------------------------------------------------------------------------------

void MUHelper::Init()
{
	m_FirstPayInterval = 0;
	m_PayInterval = 0;
	m_PricePerLevel = 0;
	m_PricePerReset = 0;
}
// -------------------------------------------------------------------------------

void MUHelper::Load()
{
	m_FirstPayInterval = GetPrivateProfileInt("MuHelper", "FirstPayInterval", 1, gDirPath.GetNewPath("MuHelper.ini"));
	m_PayInterval = GetPrivateProfileInt("MuHelper", "PayInterval", 5, gDirPath.GetNewPath("MuHelper.ini"));;
	m_PricePerLevel = GetPrivateProfileInt("MuHelper", "PricePerLevel", 100, gDirPath.GetNewPath("MuHelper.ini"));;
	m_PricePerReset = GetPrivateProfileInt("MuHelper", "PricePerReset", 20000, gDirPath.GetNewPath("MuHelper.ini"));;
}
// -------------------------------------------------------------------------------

void MUHelper::Manager(int UserIndex, MUHELPER_REQ_ACTION * lpRequest)
{
	LPOBJ lpUser = &gObj[UserIndex];
	// ----
	if( !gObjIsConnected(UserIndex) || lpUser->Connected != PLAYER_PLAYING )
	{
		return;
	}
	// ----
	switch(lpRequest->Mode)
	{
	case 0:
		{
			this->Start(lpUser);
		}
		break;
		// --
	case 1:
		{
			this->Close(lpUser);
		}
		break;
	}
}
// -------------------------------------------------------------------------------

void MUHelper::Start(LPOBJ lpUser)
{
	if( !gObjIsConnected(lpUser) || lpUser->Connected != PLAYER_PLAYING || !this->CheckMoney(lpUser) )
	{
		return;
	}
	// ----
	MUHELPER_ANS_DATA pAnswer = { 0 };
	PHeadSubSetB((LPBYTE)&pAnswer, 0xBF, 0x51, sizeof(pAnswer));
	// ----
	pAnswer.Mode = 0;
	// ----
	lpUser->m_MUHelperOn		= true;
	lpUser->m_MUHelperReadyPay	= false;
	lpUser->m_MUHelperFirstPay	= true;
	lpUser->m_MUHelperStage		= 1;
	lpUser->m_MUHelperTick		= GetTickCount();
	// ----
	DataSend(lpUser->m_Index, (LPBYTE)&pAnswer, pAnswer.h.size);
	LogAddTD("[MUHelper] [%s] [%s] has been started", lpUser->AccountID, lpUser->Name);
}
// -------------------------------------------------------------------------------

void MUHelper::Work(LPOBJ lpUser)
{
	if( !lpUser->m_MUHelperOn )
	{
		return;
	}
	// ----
	DWORD CurrentTick	= GetTickCount();
	DWORD WorkTime		= (CurrentTick - lpUser->m_MUHelperTick) / 60000;
	// ----
	if(!this->CheckMoney(lpUser) )
	{
		this->Close(lpUser);
		return;
	}
	// ----
	this->SetStage(lpUser, WorkTime);
	// ----
	if( WorkTime == this->m_FirstPayInterval && lpUser->m_MUHelperFirstPay)	//The first charge of MuHelper will be whitin 1 minute
	{
		lpUser->m_MUHelperReadyPay = true;
	} else if( WorkTime > 0 && WorkTime % this->m_PayInterval == this->m_PayInterval - 1 )
	{
		lpUser->m_MUHelperReadyPay = true;
	}
	// ----
	if((lpUser->m_MUHelperFirstPay || (WorkTime > 0 && WorkTime % this->m_PayInterval == 0)) && lpUser->m_MUHelperReadyPay)
	{
		this->SendMoney(lpUser, WorkTime);
	}

#if(FIX_HELPER_EE_BUFF==TRUE)
	if(ExUserInSafeZone(lpUser->m_Index))
	{
		return;
	}

	int dis;
	int SearchSkill = 0;
	CMagicInf * lpMagic;
	SYSTEMTIME time;
	GetLocalTime(&time);
	if( time.wSecond == 0  || 
	    time.wSecond == 10 ||
	    time.wSecond == 20 ||
	    time.wSecond == 30 ||
	    time.wSecond == 40 ||
	    time.wSecond == 50 
	)
	{
		int partynum = -1;
		int partycount;
		int number;

		LPOBJ lpPartyObj;

		partynum = lpUser->PartyNumber;

		if(partynum != -1)
		{
			partycount = gParty.m_PartyS[partynum].Count;

			for(int j = 0; j < MAX_USER_IN_PARTY; j++)
			{
				number = gParty.m_PartyS[partynum].Number[j];

				if ( OBJMAX_RANGE(number) == TRUE )
				{
					lpPartyObj = &gObj[number];

					if(lpUser->MapNumber == lpPartyObj->MapNumber)
					{
						dis = gObjCalDistance(lpUser,&gObj[number]);

						if(dis < 6)
						{
							//Defence Baf
							if(gObjGetMagicSearch( lpUser, 27) != NULL) SearchSkill = 27;
							//else if(gObjGetMagicSearch( lpUser, 480) != NULL) SearchSkill = 480;
							//else if(gObjGetMagicSearch( lpUser, 481) != NULL) SearchSkill = 481;
							//else if(gObjGetMagicSearch( lpUser, 482) != NULL) SearchSkill = 482;
							//else if(gObjGetMagicSearch( lpUser, 483) != NULL) SearchSkill = 483;
							//else if(gObjGetMagicSearch( lpUser, 484) != NULL) SearchSkill = 484;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpUser, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							//Damage Baf
							if(gObjGetMagicSearch( lpUser, 28) != NULL) SearchSkill = 28;
							//else if(gObjGetMagicSearch( lpUser, 485) != NULL) SearchSkill = 485;
							//else if(gObjGetMagicSearch( lpUser, 486) != NULL) SearchSkill = 486;
							//else if(gObjGetMagicSearch( lpUser, 487) != NULL) SearchSkill = 487;
							//else if(gObjGetMagicSearch( lpUser, 488) != NULL) SearchSkill = 488;
							//else if(gObjGetMagicSearch( lpUser, 489) != NULL) SearchSkill = 489;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpUser, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							//Heal Baf
							if(gObjGetMagicSearch( lpUser, 26) != NULL) SearchSkill = 26;
							//else if(gObjGetMagicSearch( lpUser, 475) != NULL) SearchSkill = 475;
							//else if(gObjGetMagicSearch( lpUser, 476) != NULL) SearchSkill = 476;
							//else if(gObjGetMagicSearch( lpUser, 477) != NULL) SearchSkill = 477;
							//else if(gObjGetMagicSearch( lpUser, 478) != NULL) SearchSkill = 478;
							//else if(gObjGetMagicSearch( lpUser, 479) != NULL) SearchSkill = 479;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpUser, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
							}
						}
					}
				}
			}
		}
		else
		{
			//Defence Baf
			if(gObjGetMagicSearch( lpUser, 27) != NULL) SearchSkill = 27;
			//else if(gObjGetMagicSearch( lpUser, 480) != NULL) SearchSkill = 480;
			//else if(gObjGetMagicSearch( lpUser, 481) != NULL) SearchSkill = 481;
			//else if(gObjGetMagicSearch( lpUser, 482) != NULL) SearchSkill = 482;
			//else if(gObjGetMagicSearch( lpUser, 483) != NULL) SearchSkill = 483;
			//else if(gObjGetMagicSearch( lpUser, 484) != NULL) SearchSkill = 484;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpUser, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
			//Damage Baf
			if(gObjGetMagicSearch( lpUser, 28) != NULL) SearchSkill = 28;
			//else if(gObjGetMagicSearch( lpUser, 485) != NULL) SearchSkill = 485;
			//else if(gObjGetMagicSearch( lpUser, 486) != NULL) SearchSkill = 486;
			//else if(gObjGetMagicSearch( lpUser, 487) != NULL) SearchSkill = 487;
			//else if(gObjGetMagicSearch( lpUser, 488) != NULL) SearchSkill = 488;
			//else if(gObjGetMagicSearch( lpUser, 489) != NULL) SearchSkill = 489;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpUser, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
			//Heal Baf
			if(gObjGetMagicSearch( lpUser, 26) != NULL) SearchSkill = 26;
			//else if(gObjGetMagicSearch( lpUser, 475) != NULL) SearchSkill = 475;
			//else if(gObjGetMagicSearch( lpUser, 476) != NULL) SearchSkill = 476;
			//else if(gObjGetMagicSearch( lpUser, 477) != NULL) SearchSkill = 477;
			//else if(gObjGetMagicSearch( lpUser, 478) != NULL) SearchSkill = 478;
			//else if(gObjGetMagicSearch( lpUser, 479) != NULL) SearchSkill = 479;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpUser, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
		}
	}
#endif
}
// -------------------------------------------------------------------------------

void MUHelper::Close(LPOBJ lpUser)
{
#if(FIX_MUHELPER_TP == TRUE)
	if(lpUser->MuHelperTeleportFix)
	{
		lpUser->MuHelperTeleportFix = false;
		return;
	}
#endif
	MUHELPER_ANS_DATA pAnswer = { 0 };
	PHeadSubSetB((LPBYTE)&pAnswer, 0xBF, 0x51, sizeof(pAnswer));
	// ----
	pAnswer.Mode = 1;
	// ----
	lpUser->m_MUHelperOn		= false;
	lpUser->m_MUHelperReadyPay	= false;
	lpUser->m_MUHelperFirstPay	= true;
	lpUser->m_MUHelperStage		= 1;
	lpUser->m_MUHelperTick		= 0;
	// ----
	DataSend(lpUser->m_Index, (LPBYTE)&pAnswer, pAnswer.h.size);
	// ----
	LogAddTD("[MUHelper] [%s] [%s] has been closed", lpUser->AccountID, lpUser->Name);
}
// -------------------------------------------------------------------------------

void MUHelper::SetStage(LPOBJ lpUser, WORD WorkTime)
{
	lpUser->m_MUHelperStage = 1;
}
// -------------------------------------------------------------------------------

int MUHelper::GetMoney(LPOBJ lpUser)
{
	int Level = lpUser->Level + lpUser->MLevel;
	return Level * this->m_PricePerLevel + lpUser->Reset * this->m_PricePerReset;
}
// -------------------------------------------------------------------------------

bool MUHelper::CheckMoney(LPOBJ lpUser)
{
	MUHELPER_ANS_DATA pAnswer = { 0 };
	PHeadSubSetB((LPBYTE)&pAnswer, 0xBF, 0x51, sizeof(pAnswer));
	// ----
	pAnswer.Mode = 2;
	// ----
	if( lpUser->Money < this->GetMoney(lpUser) )
	{
		DataSend(lpUser->m_Index, (LPBYTE)&pAnswer, pAnswer.h.size);
		return false;
	}
	// ----
	return true;
}
// -------------------------------------------------------------------------------

void MUHelper::SendMoney(LPOBJ lpUser, WORD WorkTime)
{
	MUHELPER_ANS_DATA pAnswer = { 0 };
	PHeadSubSetB((LPBYTE)&pAnswer, 0xBF, 0x51, sizeof(pAnswer));
	// ----
	pAnswer.Money	= this->GetMoney(lpUser);
	pAnswer.Mode	= 0;
	pAnswer.Time	= WorkTime;
	// ----
	lpUser->Money -= pAnswer.Money;
	GCMoneySend(lpUser->m_Index, lpUser->Money);
	// ----
	lpUser->m_MUHelperReadyPay = false;
	lpUser->m_MUHelperFirstPay = false;
	DataSend(lpUser->m_Index, (LPBYTE)&pAnswer, pAnswer.h.size);
}
// -------------------------------------------------------------------------------

void MUHelper::SaveMacro(int UserIndex, MUHELPER_MACRO_CLIENT * lpRequest)
{
	LPOBJ lpUser = &gObj[UserIndex];
	// ----
	MUHELPER_MACRO_DS	pRequest = { 0 };
	PHeadSetW((LPBYTE)&pRequest, 0x18, sizeof(MUHELPER_MACRO_DS));
	// ----
	memcpy(pRequest.AccountID, lpUser->AccountID, MAX_IDSTRING);
	memcpy(pRequest.Name, lpUser->Name, MAX_IDSTRING);
	pRequest.aIndex = UserIndex;
	memcpy(pRequest.btMacroData, &lpRequest->MacroBind, sizeof(pRequest.btMacroData));
	// ----



	cDBSMng.Send((char*)&pRequest, sizeof(MUHELPER_MACRO_DS));
}
// -------------------------------------------------------------------------------

void MUHelper::ReqMacro(int UserIndex, bool offlineReq)
{
	LPOBJ lpUser = &gObj[UserIndex];
	// ----
	MUHELPER_MACRO_DS	pRequest = { 0 };
	PHeadSetW((LPBYTE)&pRequest, 0x17, sizeof(MUHELPER_MACRO_DS));
	// ----
	memcpy(pRequest.AccountID, lpUser->AccountID, MAX_IDSTRING);
	memcpy(pRequest.Name, lpUser->Name, MAX_IDSTRING);
	pRequest.aIndex = UserIndex;
	// ----
	cDBSMng.Send((char*)&pRequest, sizeof(MUHELPER_MACRO_DS));

	if (offlineReq)
	{
		m_OfflineRequested.insert(UserIndex);
	}

}
// -------------------------------------------------------------------------------

void MUHelper::SendMacro(MUHELPER_MACRO_DS * lpRequest)
{
	if( lpRequest->btResult || !gObjIsConnected(lpRequest->aIndex) )
	{
		return;
	}
	// ----
	MUHELPER_MACRO_CLIENT pAnswer = { 0 };
	PHeadSetW((LPBYTE)&pAnswer, 0xAE, sizeof(MUHELPER_MACRO_CLIENT));
	// ----
	memcpy(&pAnswer.MacroBind, lpRequest->btMacroData, sizeof(lpRequest->btMacroData));
	// ----

	bool offlineReq = m_OfflineRequested.find(lpRequest->aIndex) != m_OfflineRequested.end();

	if (offlineReq)
	{
		m_OfflineRequested.erase(m_OfflineRequested.find(lpRequest->aIndex));

		MUHELPER_SETTINGS_PACKET settings;
		memcpy(&settings, &lpRequest->btMacroData, sizeof(settings));

		g_MUHelperOffline.MacroRes(lpRequest->aIndex, settings);
	}
	else
	{
		DataSend(lpRequest->aIndex, (LPBYTE)&pAnswer, sizeof(MUHELPER_MACRO_CLIENT));
	}
}
// ------------------------------------------------------------------------------
#endif