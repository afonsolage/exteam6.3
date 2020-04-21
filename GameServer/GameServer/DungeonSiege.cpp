#include "StdAfx.h"
#include "DungeonSiege.h"
#include "user.h"
#include "GameMain.h"
#include "DBSockMng.h"
#include "logproc.h"
#include "BloodCastle.h"
#include "BuffManager.h"
#include "DSProtocol.h"
#include "ExUser.h"
#include "ExLicense.h"
#include "MUHelperOffline.h"

#if(EVENT_DUNGEON_SIEGE)

CDungeonSiege g_DungeonSiege;

CDungeonSiege::CDungeonSiege()
{
	this->Init();
}

CDungeonSiege::~CDungeonSiege()
{
}

void CDungeonSiege::Init()
{
	this->iEventStatus = eEVENTDUNGEON_CLOSE;
	this->bCaptured = false;
	memset(this->szLordGuild, 0, sizeof(this->szLordGuild));
	this->iRegCount = 0;
	memset(this->reg_list, 0, sizeof(this->reg_list));
	this->iTickCount = 0;
	this->iTickRemain = 0;
	this->iTickWait = 0;
	this->iTickFinal1 = 0;
	this->iTickFinal2 = 0;
	this->aIndexFinal1 = -1;
	this->aIndexFinal2 = -1;
	this->aGuildFinal1 = -1;
	this->aGuildFinal2 = -1;
	this->bEnable = 0;
	this->iNpcClass = 0;
	this->iNpcMap = 0;
	this->iNpcX = 0;
	this->iNpcY = 0;
	this->iEventStartDay = 0;
	this->iEventStartHour = 0;
	this->iEventeStartMinut = 0;
	this->iEventDurationStage1 = 0;
	this->iEventDurationStage2 = 0;
	this->iEventDurationWait1 = 0;
	this->iEventDurationWait2 = 0;
	this->m_EventMapNumber = 1;
	this->m_EventStage1WaitX = 0;
	this->m_EventStage1WaitY = 0;
	this->m_EventStage1KillX = 0;
	this->m_EventStage1KillY = 0;
	this->m_EventStage2WaitX = 0;
	this->m_EventStage2WaitY = 0;
	this->m_EventStage2KillX = 0;
	this->m_EventStage2KillY = 0;
	this->m_EventPlayerDieMap = 0;
	this->m_EventPlayerDieX = 0;
	this->m_EventPlayerDieY = 0;
	this->m_BuffEnable = 0;
	this->m_BuffPlusAttackPercent = 0;
	this->m_BuffPlusDefencePercent = 0;
	this->m_RewardEnable = 0;
	this->m_RewardItemEnable = 0;
	this->m_RewardItemType = 0;
	this->m_RewardItemIndex = 0;
	this->m_RewardItemLevel = 0;
	this->m_RewardWCoinC = 0;
	this->m_RewardWcoinP = 0;
	this->m_RewardWgoinG = 0;
	this->m_RewardCredit = 0;
	this->m_FinalScoreForVictory = 10;
	this->m_MinPlayerGuildReg = 10;
	this->m_NpcTeleportMinusScore = 0;
	memset(this->m_EventName, 0, sizeof(this->m_EventName));
}

void CDungeonSiege::Load()
{
	if(g_ExLicense.CheckUser(eExUB::Local)		|| 
	   g_ExLicense.CheckUser(eExUB::Gredy)		|| 
	   g_ExLicense.CheckUser(eExUB::Gredy2)		|| 
	   g_ExLicense.CheckUser(eExUB::GredyLocal)	||
	   THINNAKORN_MAC == 1						||
	   g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
	   g_ExLicense.CheckUser(eExUB::ArcMu)		||
	   g_ExLicense.CheckUser(eExUB::ulasevich)	||
	   g_ExLicense.CheckUser(eExUB::ulasevich2) ||
	   g_ExLicense.CheckUser(eExUB::Escalate) ||
	   g_ExLicense.CheckUser(eExUB::mu4you)	||
	   g_ExLicense.CheckUser(eExUB::eternalmu) || 
	   g_ExLicense.CheckUser(eExUB::NSGames))
	{
		this->Read(gDirPath.GetNewPath("ExData\\Events\\DungeonSiege.ini"));
	}
}

void CDungeonSiege::Read(char* filename)
{
	this->bEnable					= GetPrivateProfileInt("ExTeam", "Enable", 0, filename);
	this->iNpcClass					= GetPrivateProfileInt("ExTeam", "NpcClass", 0, filename);
	this->iNpcMap					= GetPrivateProfileInt("ExTeam", "NpcMap", 0, filename);
	this->iNpcX						= GetPrivateProfileInt("ExTeam", "NpcX", 0, filename);
	this->iNpcY						= GetPrivateProfileInt("ExTeam", "NpcY", 0, filename);
	this->iEventStartDay			= GetPrivateProfileInt("ExTeam", "EventStartDay", 0, filename);
	this->iEventStartHour			= GetPrivateProfileInt("ExTeam", "EventStartHour", 0, filename);
	this->iEventeStartMinut			= GetPrivateProfileInt("ExTeam", "EventeStartMinut", 0, filename);
	this->iEventDurationStage1		= GetPrivateProfileInt("ExTeam", "EventDurationStage1", 0, filename);
	this->iEventDurationStage2		= GetPrivateProfileInt("ExTeam", "EventDurationStage2", 0, filename);
	this->iEventDurationWait1		= GetPrivateProfileInt("ExTeam", "EventDurationWait1", 0, filename);
	this->iEventDurationWait2		= GetPrivateProfileInt("ExTeam", "EventDurationWait2", 0, filename);
	this->m_EventMapNumber			= GetPrivateProfileInt("ExTeam", "EventMapNumber", 0, filename);
	this->m_EventStage1WaitX		= GetPrivateProfileInt("ExTeam", "EventStage1WaitX", 0, filename);
	this->m_EventStage1WaitY		= GetPrivateProfileInt("ExTeam", "EventStage1WaitY", 0, filename);
	this->m_EventStage1KillX		= GetPrivateProfileInt("ExTeam", "EventStage1KillX", 0, filename);
	this->m_EventStage1KillY		= GetPrivateProfileInt("ExTeam", "EventStage1KillY", 0, filename);
	this->m_EventStage2WaitX		= GetPrivateProfileInt("ExTeam", "EventStage2WaitX", 0, filename);
	this->m_EventStage2WaitY		= GetPrivateProfileInt("ExTeam", "EventStage2WaitY", 0, filename);
	this->m_EventStage2KillX		= GetPrivateProfileInt("ExTeam", "EventStage2KillX", 0, filename);
	this->m_EventStage2KillY		= GetPrivateProfileInt("ExTeam", "EventStage2KillY", 0, filename);
	this->m_EventPlayerDieMap		= GetPrivateProfileInt("ExTeam", "EventPlayerDieMap", 0, filename);
	this->m_EventPlayerDieX			= GetPrivateProfileInt("ExTeam", "EventPlayerDieX", 0, filename);
	this->m_EventPlayerDieY			= GetPrivateProfileInt("ExTeam", "EventPlayerDieY", 0, filename);
	this->m_BuffEnable				= GetPrivateProfileInt("ExTeam", "BuffEnable", 0, filename);
	this->m_BuffPlusAttackPercent	= GetPrivateProfileInt("ExTeam", "BuffPlusAttackPercent", 0, filename);
	this->m_BuffPlusDefencePercent	= GetPrivateProfileInt("ExTeam", "BuffPlusDefencePercent", 0, filename);
	this->m_RewardEnable			= GetPrivateProfileInt("ExTeam", "RewardEnable", 0, filename);
	this->m_RewardItemEnable		= GetPrivateProfileInt("ExTeam", "RewardItemEnable", 0, filename);
	this->m_RewardItemType			= GetPrivateProfileInt("ExTeam", "RewardItemType", 0, filename);
	this->m_RewardItemIndex			= GetPrivateProfileInt("ExTeam", "RewardItemIndex", 0, filename);
	this->m_RewardItemLevel			= GetPrivateProfileInt("ExTeam", "RewardItemLevel", 0, filename);
	this->m_RewardWCoinC			= GetPrivateProfileInt("ExTeam", "RewardWCoinC", 0, filename);
	this->m_RewardWcoinP			= GetPrivateProfileInt("ExTeam", "RewardWcoinP", 0, filename);
	this->m_RewardWgoinG			= GetPrivateProfileInt("ExTeam", "RewardWgoinG", 0, filename);
	this->m_RewardCredit			= GetPrivateProfileInt("ExTeam", "RewardCredit", 0, filename);
	this->m_FinalScoreForVictory	= GetPrivateProfileInt("ExTeam", "FinalScoreForVictory", 0, filename);
	this->m_MinPlayerGuildReg		= GetPrivateProfileInt("ExTeam", "MinPlayerGuildReg", 0, filename);
	this->m_NpcTeleportMinusScore	= GetPrivateProfileInt("ExTeam", "NpcTeleportMinusScore", 0, filename);
	GetPrivateProfileString("ExTeam", "EventName", "Dungeon Siege", this->m_EventName, sizeof(this->m_EventName), filename);
}

bool CDungeonSiege::NpcDialog(int aIndex, int aNpcIndex)
{
	if(!this->bEnable)
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(!(lpNpc->Class == this->iNpcClass && lpNpc->MapNumber == this->iNpcMap && lpNpc->X == this->iNpcX && lpNpc->Y == this->iNpcY))
	{
		lpUser->DSiege.bNpcClick = false;
		return false;
	}

	lpUser->DSiege.bNpcClick = true;

	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		this->GCNpcNnfo(aIndex);
	}
	else
	{
		this->TeleportInSiege(aIndex);
	}

	return true;
}

void CDungeonSiege::Run()
{
	if(!this->bEnable)
	{
		return;
	}

	GetLocalTime(&this->systime);

	switch(this->iEventStatus)
	{
		case eEVENTDUNGEON_CLOSE:			this->ProcessStatusClose();			break;
		case eEVENTDUNGEON_WAIT:			this->PrecessStatusWait();			break;
		case eEVENTDUNGEON_START_STAGE1:	this->ProcessStatusStartStage1();	break;
		case eEVENTDUNGEON_WAIT_STAGE2:		this->PrecessStatusWaitStage2();	break;
		case eEVENTDUNGEON_START_STAGE2:	this->ProcessStatusStartStage2();	break;
	}

	this->ReturnPlayerRing();
}

void CDungeonSiege::GCNpcNnfo(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	char szOwName[9];
	char szGName[9];
	PMSG_GC_DUNGEON_SIEGE_NPC pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x44, sizeof(pMsg));
	pMsg.bResultReg = true;
	pMsg.iMsgCode = 0;
	pMsg.Captured = this->bCaptured;

	szOwName[8] = 0;
	memcpy(szOwName, this->szLordGuild, 8);
	memcpy(pMsg.szGuildOwner, szOwName, 8);

	_GUILD_INFO_STRUCT * lpGuildUser = lpUser->lpGuild;

	if(!lpGuildUser)
	{
		pMsg.iMsgCode = 1;
	}
	else if(lpUser->GuildStatus != GUILD_MASTER)
	{
		pMsg.iMsgCode = 2;
	}
	else if(!strcmp(lpGuildUser->Name, this->szLordGuild))
	{
		pMsg.iMsgCode = 3;
	}
	else if(this->iRegCount >= 10)
	{
		pMsg.iMsgCode = 4;
	}	
	else if(lpGuildUser->Count < this->m_MinPlayerGuildReg)
	{
		pMsg.iMsgCode = 5;
	}

	pMsg.iCountGuild = this->iRegCount;

	for(int i = 0; i < this->iRegCount; i++)
	{
		szGName[8] = 0;
		memcpy(szGName, this->reg_list[i].szGuildName, 8);

		if(lpGuildUser)
		{
			if(!strcmp(szGName, lpGuildUser->Name))
			{
				pMsg.iMsgCode = 6;
			}
		}

		pMsg.szGuildName[i][8] = 0;
		memcpy(pMsg.szGuildName[i], szGName, 8);
	}

	if(pMsg.iMsgCode != 0)
	{
		pMsg.bResultReg = false;
	}
	
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CDungeonSiege::GDReqRegSiegeList()
{
	if(!this->bEnable)
	{
		return;
	}

	PMSG_PROTOCOL_RESULT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x03, sizeof(pMsg));
	pMsg.Result = true;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CDungeonSiege::DGRegSiegeList(PMSG_DG_DUNGEON_SIEGE_REG_LIST* lpMsg)
{
	memset(this->reg_list, 0, sizeof(this->reg_list));

	this->iRegCount = lpMsg->iCount;

	for(int i = 0; i < this->iRegCount; i++)
	{
		char szGName[9];
		szGName[8] = 0;
		memcpy(szGName, lpMsg->szGuildName[i], 8);
		memcpy(this->reg_list[i].szGuildName, szGName, 8);
	}

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpTempObj = &gObj[aIndex];

		if(lpTempObj->Connected < PLAYER_PLAYING || 
		   lpTempObj->Type != OBJ_USER)
		{
			continue;
		}	

		if(lpTempObj->DSiege.bNpcClick)
		{
			this->GCNpcNnfo(aIndex);
		}
	}
}

void CDungeonSiege::CGDRegSiege(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	_GUILD_INFO_STRUCT * lpGuildUser = lpUser->lpGuild;

	if(!lpGuildUser)
	{
		return;
	}
	else if(!strcmp(lpGuildUser->Name, this->szLordGuild))
	{
		return;
	}
	else if(this->iRegCount >= 10)
	{
		return;
	}	
	else if(lpGuildUser->Count < this->m_MinPlayerGuildReg)
	{
		return;
	}

	for(int i = 0; i < this->iRegCount; i++)
	{
		if(lpGuildUser)
		{
			if(!strcmp(this->reg_list[i].szGuildName, lpGuildUser->Name))
			{
				return;
			}
		}
	}

	PMSG_GD_DUNGEON_SIEGE_GUILD_REG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x04, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.szGuildName[8] = 0;
	memcpy(pMsg.szGuildName, lpGuildUser->Name, sizeof(pMsg.szGuildName)-1);
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CDungeonSiege::DGRegSiegeResult(PMSG_GD_DUNGEON_SIEGE_GUILD_REG_RESULT* lpMsg)
{
	if(!lpMsg->bResult)
	{
		return;
	}

	int aIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	this->GDReqRegSiegeList();
}

void CDungeonSiege::GDSiegeClearList()
{
	PMSG_PROTOCOL_RESULT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x05, sizeof(pMsg));
	pMsg.Result = true;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);

	this->iRegCount = 0;
	memset(this->reg_list, 0, sizeof(this->reg_list));
}

void CDungeonSiege::GDSiegeOwner()
{
	if(!this->bEnable)
	{
		return;
	}

	PMSG_PROTOCOL_RESULT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x06, sizeof(pMsg));
	pMsg.Result = true;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CDungeonSiege::DGSiegeOwner(PMSG_DG_DUNGEON_SIEGE_SELECT_OENER* lpMsg)
{
	if(!lpMsg->bResult)
	{
		this->bCaptured = false;
		memset(this->szLordGuild, 0, sizeof(this->szLordGuild));
		return;
	}

	char szGName[9];
	szGName[8] = 0;
	memcpy(szGName, lpMsg->szGuildOwner, sizeof(szGName)-1);

	this->bCaptured = true;
	memcpy(this->szLordGuild, szGName, sizeof(this->szLordGuild)-1);
}

void CDungeonSiege::GDSiegeOwnerUpdate()
{
	PMSG_GD_DUNGEON_SIEGE_UPDATE_OENER pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x07, sizeof(pMsg));
	pMsg.szGuildOwner[8] = 0;
	memcpy(pMsg.szGuildOwner, this->szLordGuild, sizeof(this->szLordGuild)-1);
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CDungeonSiege::CGHWID(PMSG_CG_DUNBEON_SIEGE_HWID* lpMsg, int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	lpUser->DSiege.dwHWID = lpMsg->dwHWID;
}

void CDungeonSiege::SetStatus(int States)
{
	if(!this->bEnable)
	{
		return;
	}

	this->iEventStatus = States;

	switch(this->iEventStatus)
	{
		case eEVENTDUNGEON_CLOSE:			this->StatusClose();		break;
		case eEVENTDUNGEON_WAIT:			this->StatusWait();			break;
		case eEVENTDUNGEON_START_STAGE1:	this->StatusStartStage1();	break;
		case eEVENTDUNGEON_WAIT_STAGE2:		this->StatusWaitStage2();	break;
		case eEVENTDUNGEON_START_STAGE2:	this->StatusStartStage2();	break;
	}

	this->GCEventState();
}

bool CDungeonSiege::CheckStatus(int Status)
{
	if(this->iEventStatus == Status)
	{
		return true;
	}

	return false;
}

void CDungeonSiege::StatusClose()
{
	this->GDSiegeOwnerUpdate();
	this->GDSiegeClearList();
	this->SiegeClearScore();

	char szText[256];
	sprintf(szText, "[%s] End", this->m_EventName);
	AllSendServerMsg(szText);

	this->MonsterEventEnable();
}

void CDungeonSiege::StatusWait()
{
	this->iTickCount = GetTickCount();
	this->iTickRemain = 60000 * this->iEventDurationWait1;
	this->MonsterEventDisable();
	this->GCSiegeScore();
}

void CDungeonSiege::StatusStartStage1()
{
	char szText[256];
	sprintf(szText, "[%s] First stage has started", this->m_EventName);
	AllSendServerMsg(szText);
	this->iTickCount = GetTickCount();
	this->iTickRemain = 60000 * this->iEventDurationStage1;

	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected < PLAYER_PLAYING || lpTempObj->Type != OBJ_USER || lpTempObj->MapNumber != this->m_EventMapNumber)
		{
			continue;
		}	

		this->GCMapAttribute(n, 1);
	}
}

void CDungeonSiege::StatusWaitStage2()
{
	this->iTickCount = GetTickCount();
	this->iTickRemain = 60000 * this->iEventDurationWait2;

	this->GCSiegeScore();

	gObjTeleport(this->aIndexFinal1, this->m_EventMapNumber, this->m_EventStage2WaitX, this->m_EventStage2WaitY);
	gObjTeleport(this->aIndexFinal2, this->m_EventMapNumber, this->m_EventStage2WaitX, this->m_EventStage2WaitY);

	this->GCMapAttribute(this->aIndexFinal1, 0);
	this->GCMapAttribute(this->aIndexFinal2, 0);
}	

void CDungeonSiege::StatusStartStage2()
{
	char szText[256];
	sprintf(szText, "[%s] Second stage has started", this->m_EventName);
	AllSendServerMsg(szText);
	this->iTickCount = GetTickCount();
	this->iTickRemain = 60000 * this->iEventDurationStage2;
}

void CDungeonSiege::ProcessStatusClose()
{
	if(this->iEventStartDay == this->systime.wDayOfWeek	&&
	   this->iEventStartHour == this->systime.wHour		&& 
	   this->iEventeStartMinut == this->systime.wMinute	&&
	   this->systime.wSecond == 0)
	{
		this->ProcessStatusStart();
		/*
		if(this->iRegCount >= 2)
		{
			this->SetStatus(eEVENTDUNGEON_WAIT);
		}
		else if(this->iRegCount == 1)
		{
			for(int i = 0; i < this->iRegCount; i++)
			{
				_GUILD_INFO_STRUCT* lpGuild1 = Guild.SearchGuild(this->reg_list[i].szGuildName);

				if(!lpGuild1)
				{
					continue;
				}
				char szTemp[256];
				this->bCaptured = true;
				memcpy(this->szLordGuild, lpGuild1->Name, sizeof(this->szLordGuild)-1);
				sprintf(szTemp, "[%s] %s are new owners of the Dungeon", this->m_EventName, this->szLordGuild);
				AllSendServerMsg(szTemp);
				this->SetStatus(eEVENTDUNGEON_CLOSE);	
			}
		}
		else if(this->iRegCount == 0)
		{
			this->bCaptured = false;
			memcpy(this->szLordGuild, "", sizeof(this->szLordGuild)-1);
			this->SetStatus(eEVENTDUNGEON_CLOSE);	
		}
		*/
	}
}

void CDungeonSiege::ProcessStatusStart()
{
	if(!this->bEnable)
	{
		return;
	}

	this->SiegeClearScore();

	if(this->iRegCount >= 2)
	{
		this->SetStatus(eEVENTDUNGEON_WAIT);
	}
	else if(this->iRegCount == 1)
	{
		for(int i = 0; i < this->iRegCount; i++)
		{
			_GUILD_INFO_STRUCT* lpGuild1 = Guild.SearchGuild(this->reg_list[i].szGuildName);

			if(!lpGuild1)
			{
				continue;
			}
			char szTemp[256];
			this->bCaptured = true;
			memcpy(this->szLordGuild, lpGuild1->Name, sizeof(this->szLordGuild)-1);
			sprintf(szTemp, "[%s] %s are new owners of the Dungeon", this->m_EventName, this->szLordGuild);
			AllSendServerMsg(szTemp);
			this->SetStatus(eEVENTDUNGEON_CLOSE);	
		}
	}
	else if(this->iRegCount == 0)
	{
		this->bCaptured = false;
		memcpy(this->szLordGuild, "", sizeof(this->szLordGuild)-1);
		this->SetStatus(eEVENTDUNGEON_CLOSE);	
	}
}

void CDungeonSiege::PrecessStatusWait()
{
	int iTickMsec = (GetTickCount() - this->iTickCount);

	if(iTickMsec >= 1000)
	{
		this->iTickRemain -= iTickMsec;			
		this->iTickCount = GetTickCount();

		if(this->iTickRemain <= (60000 * this->iEventDurationWait1))
		{
			if((GetTickCount() - this->iTickWait) > 60000)
			{
				int iWaitMin = (this->iTickRemain/60000) + 1;
				char szTemp[256];
				sprintf(szTemp, "[%s] First stage will start after %d minute(s)", this->m_EventName, iWaitMin);
				AllSendServerMsg(szTemp);
				this->iTickWait = GetTickCount();
				if(iWaitMin == 1)
				{
					this->GCMapAttributeAll(1);
				}
			}
		}		
	}

	if(this->iTickRemain <= 0)
	{
		this->SetStatus(eEVENTDUNGEON_START_STAGE1);
	}
}

void CDungeonSiege::ProcessStatusStartStage1()
{
	int iTickMsec = (GetTickCount() - this->iTickCount);

	if(iTickMsec >= 1000)
	{
		this->iTickRemain -= iTickMsec;			
		this->iTickCount = GetTickCount();
	}

	if(this->iTickRemain <= 0)
	{
		if(!this->TeleportInFinal())
		{
			this->SetStatus(eEVENTDUNGEON_CLOSE);
			return;
		}

		this->SetStatus(eEVENTDUNGEON_WAIT_STAGE2);
	}
}

void CDungeonSiege::PrecessStatusWaitStage2()
{
	int iTickMsec = (GetTickCount() - this->iTickCount);

	if(iTickMsec >= 1000)
	{
		this->iTickRemain -= iTickMsec;			
		this->iTickCount = GetTickCount();

		if(this->iTickRemain <= (60000 * this->iEventDurationWait2))
		{
			if((GetTickCount() - this->iTickWait) > 60000)
			{
				int iWaitMin = (this->iTickRemain/60000) + 1;
				char szTemp[256];
				sprintf(szTemp, "[%s] Second stage will start after %d minute(s)", this->m_EventName, iWaitMin);
				AllSendServerMsg(szTemp);
				this->iTickWait = GetTickCount();
				if(iWaitMin == 1)
				{
					this->GCMapAttributeAll(1);
				}
			}
		}		
	}

	if(this->iTickRemain <= 0)
	{
		this->SetStatus(eEVENTDUNGEON_START_STAGE2);
	}
}

void CDungeonSiege::ProcessStatusStartStage2()
{
	int iTickMsec = (GetTickCount() - this->iTickCount);

	if(iTickMsec >= 1000)
	{
		this->iTickRemain -= iTickMsec;			
		this->iTickCount = GetTickCount();
	}

	if(this->iTickRemain <= 0)
	{
		if(OBJMAX_RANGE(this->aIndexFinal1) && OBJMAX_RANGE(this->aIndexFinal2))
		{
			LPOBJ lpUser1 = &gObj[this->aIndexFinal1];
			LPOBJ lpUser2 = &gObj[this->aIndexFinal2];

			if(lpUser1->DSiege.iScore2 > lpUser2->DSiege.iScore2)
			{
				char szTemp[256];
				sprintf(szTemp, "[%s] %s hero of Dungeon!", this->m_EventName, lpUser1->Name);
				AllSendServerMsg(szTemp);

				this->bCaptured = true;
				memcpy(this->szLordGuild, lpUser1->GuildName, sizeof(this->szLordGuild)-1);

				sprintf(szTemp, "[%s] %s are new owners of the Dungeon", this->m_EventName, this->szLordGuild);
				AllSendServerMsg(szTemp);

				this->MapKick(lpUser2->m_Index);

				this->RewardSiege(lpUser1->m_Index);
			}
			else if(lpUser2->DSiege.iScore2 > lpUser1->DSiege.iScore2)
			{
				char szTemp[256];
				sprintf(szTemp, "[%s] %s hero of Dungeon!", this->m_EventName, lpUser2->Name);
				AllSendServerMsg(szTemp);

				this->bCaptured = true;
				memcpy(this->szLordGuild, lpUser1->GuildName, sizeof(this->szLordGuild)-1);

				sprintf(szTemp, "[%s] %s are new owners of the Dungeon", this->m_EventName, this->szLordGuild);
				AllSendServerMsg(szTemp);

				this->MapKick(lpUser1->m_Index);

				this->RewardSiege(lpUser2->m_Index);
			}
			else
			{
				this->iTickRemain = 60000;
				return;
			}
		}

		this->SetStatus(eEVENTDUNGEON_CLOSE);
	}
}

bool CDungeonSiege::ChangePkLevel(int aIndex, int aTargetIndex)
{
	if(!this->bEnable)
	{
		return true;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];	

	if(lpUser->Connected < PLAYER_PLAYING || lpTarget->Connected < PLAYER_PLAYING)
	{
		return true;
	}

	if(lpUser->MapNumber != this->m_EventMapNumber)
	{
		return true;
	}

	if(this->CheckStatus(eEVENTDUNGEON_CLOSE) || this->CheckStatus(eEVENTDUNGEON_WAIT) || this->CheckStatus(eEVENTDUNGEON_WAIT_STAGE2))
	{
		return true;
	}

	return false;
}

bool CDungeonSiege::PlayerScore(int aIndex, int aTargetIndex)
{
	if(!this->bEnable)
	{
		return false;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];	

	if(lpUser->Connected < PLAYER_PLAYING || lpTarget->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if(lpUser->Type != OBJ_USER || lpTarget->Type != OBJ_USER)
	{
		return false;
	}

	if(lpUser->MapNumber != this->m_EventMapNumber)
	{
		return false;
	}

	if(this->CheckStatus(eEVENTDUNGEON_START_STAGE1))
	{
		if(lpUser->GuildNumber != lpTarget->GuildNumber)
		{
			lpTarget->DSiege.iScore++;
			lpTarget->lpGuild->DungeonSiege.iScore++;
			MsgOutput(aTargetIndex, "[%s] Score: %d", this->m_EventName, lpTarget->DSiege.iScore);
			MsgOutput(aTargetIndex, "[%s] Guild Score: %d", this->m_EventName, lpTarget->lpGuild->DungeonSiege.iScore);
			this->GCSiegeScore();
		}
	}
	else if(this->CheckStatus(eEVENTDUNGEON_START_STAGE2))
	{
		lpTarget->DSiege.iScore2++;
		MsgOutput(aTargetIndex, "[%s] Score: %d", this->m_EventName, lpTarget->DSiege.iScore2);

		if(lpTarget->DSiege.iScore2 >= this->m_FinalScoreForVictory)
		{
			char szTemp[256];
			sprintf(szTemp, "[%s] %s hero of Dungeon!", this->m_EventName, lpTarget->Name);
			AllSendServerMsg(szTemp);
			this->bCaptured = true;
			memcpy(this->szLordGuild, lpTarget->GuildName, sizeof(this->szLordGuild)-1);
			sprintf(szTemp, "[%s] %s are new owners of the Dungeon", this->m_EventName, this->szLordGuild);
			AllSendServerMsg(szTemp);
			this->MapKick(lpUser->m_Index);
			this->RewardSiege(lpTarget->m_Index);
			this->SetStatus(eEVENTDUNGEON_CLOSE);
		}
		this->GCSiegeScore();
	}

	return true;
}

void CDungeonSiege::PlayerCheck(int aIndex)
{
	if(!this->bEnable)
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

	if(lpUser->X != lpUser->TX || lpUser->Y != lpUser->TY)
	{
		lpUser->DSiege.bNpcClick = false;
	}

	this->GuildBuff(aIndex);

	this->GCVieweSiege(aIndex);

	if(lpUser->MapNumber != this->m_EventMapNumber)
	{
		return;
	}

	if(lpUser->GuildNumber < 1)
	{
		this->MapKick(aIndex);
		return;
	}
	
	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))	
	{
		if(!this->bCaptured)
		{
			this->MapKick(aIndex);
			return;
		}

		if(strcmp(lpUser->GuildName, this->szLordGuild))
		{
			this->MapKick(aIndex);
			return;
		}
	}
	else
	{
		if(lpUser->GuildName[0] == this->szLordGuild[0])
		{
			if(!strcmp(lpUser->GuildName, this->szLordGuild))
			{
				this->MapKick(aIndex);
				return;
			}
		}

		if(!this->PlayerGuildRegCheck(aIndex))
		{
			this->MapKick(aIndex);
			return;
		}
	}
	
	if(!this->CheckStatus(eEVENTDUNGEON_CLOSE))	
	{
		int iHWIDCount = 0;

		for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
		{
			LPOBJ lpTempObj = &gObj[n];

			if(lpTempObj->Connected < PLAYER_PLAYING || lpTempObj->Type != OBJ_USER || lpTempObj->MapNumber != this->m_EventMapNumber)
			{
				continue;
			}	

			if(lpUser->DSiege.dwHWID == lpTempObj->DSiege.dwHWID)
			{
				iHWIDCount++;
			}
#if(DUNGEON_SIEGE_DEBUG)
			if(iHWIDCount > 1)
			{
				this->MapKick(n);
			}
#endif
		}
	}
	
	if(this->CheckStatus(eEVENTDUNGEON_WAIT_STAGE2) || this->CheckStatus(eEVENTDUNGEON_START_STAGE2))	
	{
		if(aIndex != this->aIndexFinal1 && aIndex != this->aIndexFinal2)
		{
			this->MapKick(aIndex);
			return;
		}
	}


}

bool CDungeonSiege::PlayerGuildRegCheck(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if(lpUser->GuildNumber < 1)
	{
		return false;
	}

	for(int i = 0; i < this->iRegCount; i++)
	{
		if(lpUser->GuildName[0] == this->reg_list[i].szGuildName[0])
		{
			if(!strcmp(lpUser->GuildName, this->reg_list[i].szGuildName))
			{
				return true;
			}
		}
	}

	return false;
}

void CDungeonSiege::MapKick(int aIndex)
{
	gObjTeleport(aIndex, this->m_EventPlayerDieMap, this->m_EventPlayerDieX, this->m_EventPlayerDieY);
}

void CDungeonSiege::GCMapAttribute(int aIndex, int maptype)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	int iSizePacket = 0;
	unsigned char btPacket[256];
	
	PMSG_SETMAPATTR_COUNT pMsg;
	PMSG_SETMAPATTR pBodyMsg;

	iSizePacket += sizeof(pMsg);

	pMsg.btType = 0;
	pMsg.btMapAttr = 1;
	pMsg.btMapSetType = maptype;
	pMsg.btCount = 1;

	pBodyMsg.btX = 0;
	pBodyMsg.btY = 0;
	memcpy(&btPacket[iSizePacket], &pBodyMsg, sizeof(pBodyMsg));
	iSizePacket += sizeof(pBodyMsg);
	pBodyMsg.btX   = 255;
	pBodyMsg.btY   = 255;
	memcpy(&btPacket[iSizePacket], &pBodyMsg, sizeof(pBodyMsg));
	iSizePacket += sizeof(pBodyMsg);

	pMsg.h.c = 0xC1;
	pMsg.h.size = iSizePacket;
	pMsg.h.headcode = 0x46;
	memcpy(&btPacket, &pMsg, sizeof(pMsg));
	
	DataSend(aIndex, (LPBYTE)&btPacket, iSizePacket);
}

void CDungeonSiege::TeleportInSiege(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	_GUILD_INFO_STRUCT * lpGuildUser = lpUser->lpGuild;

	if(!lpGuildUser)
	{
		return;
	}

	if(this->PlayerGuildRegCheck(aIndex))
	{
		if(this->CheckStatus(eEVENTDUNGEON_WAIT))
		{
			this->GCSiegeScore();
			gObjTeleport(aIndex, this->m_EventMapNumber, this->m_EventStage1WaitX, this->m_EventStage1WaitY);
			if(this->iTickRemain > 60000)
			{
				this->GCMapAttribute(aIndex, 0);
			}
		}
		else if(this->CheckStatus(eEVENTDUNGEON_START_STAGE1))
		{
			if(this->m_NpcTeleportMinusScore > 0)
			{
				if(lpUser->DSiege.iScore > this->m_NpcTeleportMinusScore)
				{
					lpUser->DSiege.iScore -= this->m_NpcTeleportMinusScore;
				}
				else
				{
					lpUser->DSiege.iScore = 0;
				}
				if(lpUser->lpGuild->DungeonSiege.iScore > this->m_NpcTeleportMinusScore)
				{
					lpUser->lpGuild->DungeonSiege.iScore -= this->m_NpcTeleportMinusScore;
				}
				else
				{
					lpUser->lpGuild->DungeonSiege.iScore = 0;
				}
				this->GCSiegeScore();
			}
			gObjTeleport(aIndex, this->m_EventMapNumber, this->m_EventStage1KillX, this->m_EventStage1KillY);
		}
		else if(this->CheckStatus(eEVENTDUNGEON_WAIT_STAGE2))
		{
			if(lpUser->m_Index == this->aIndexFinal1 || lpUser->m_Index == this->aIndexFinal2)
			{
				this->GCSiegeScore();
				gObjTeleport(aIndex, this->m_EventMapNumber, this->m_EventStage2WaitX, this->m_EventStage2WaitY);
				if(this->iTickRemain > 60000)
				{
					this->GCMapAttribute(aIndex, 0);
				}
			}			
		}
		else if(this->CheckStatus(eEVENTDUNGEON_START_STAGE2))
		{
			if(lpUser->m_Index == this->aIndexFinal1 || lpUser->m_Index == this->aIndexFinal2)
			{
				this->GCSiegeScore();
				gObjTeleport(aIndex, this->m_EventMapNumber, this->m_EventStage2KillX, this->m_EventStage2KillY);
			}
		}
	}
}

bool CDungeonSiege::TeleportInFinal()
{
	int iMaxScoreGuild1 = 0;
	int iMaxScoreGuild2 = 0;
	int iMaxScorePlayer1 = 0;
	int iMaxScorePlayer2 = 0;
	int iGuildRegID1 = -1;
	int iGuildRegID2 = -1;
	int aIndex1 = -1;
	int aIndex2 = -1;
	int iSiegeGuild1 = -1;
	int iSiegeGuild2 = -1;

	for(int i = 0; i < this->iRegCount; i++)
	{
		_GUILD_INFO_STRUCT* lpGuild1 = Guild.SearchGuild(this->reg_list[i].szGuildName);

		if(!lpGuild1)
		{
			continue;
		}

		if(lpGuild1->DungeonSiege.iScore > iMaxScoreGuild1)
		{
			iMaxScoreGuild1 = lpGuild1->DungeonSiege.iScore;
			iGuildRegID1 = lpGuild1->Number;
			iSiegeGuild1 = i;
		}
	}

	if(iGuildRegID1 == -1)
	{
		this->bCaptured = false;
		memcpy(this->szLordGuild, "", sizeof(this->szLordGuild)-1);
		return false;
	}

	for(int i = 0; i < this->iRegCount; i++)
	{
		_GUILD_INFO_STRUCT* lpGuild2 = Guild.SearchGuild(this->reg_list[i].szGuildName);

		if(!lpGuild2)
		{
			continue;
		}

		if(iGuildRegID1 == lpGuild2->Number)
		{
			continue;
		}

		if(lpGuild2->DungeonSiege.iScore > iMaxScoreGuild2)
		{
			iMaxScoreGuild2 = lpGuild2->DungeonSiege.iScore;
			iGuildRegID2 = lpGuild2->Number;
			iSiegeGuild2 = i;
		}
	}

	if(iGuildRegID2 == -1)
	{
		_GUILD_INFO_STRUCT* lpWinGuild = Guild.SearchGuild_Number(iGuildRegID1);

		if(lpWinGuild)
		{
			this->bCaptured = true;
			memcpy(this->szLordGuild, lpWinGuild->Name, sizeof(this->szLordGuild)-1);

			char szTemp[256];
			sprintf(szTemp, "[%s] %s are new owners of the Dungeon Dungeon", this->m_EventName, this->szLordGuild);
			AllSendServerMsg(szTemp);
		}

		return false;
	}

	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ sObj = &gObj[n];

		if(sObj->Connected < PLAYER_PLAYING || sObj->Type != OBJ_USER)
		{
			continue;
		}

		if(sObj->GuildNumber < 1)
		{
			continue;
		}

		if(iGuildRegID1 == sObj->GuildNumber)
		{
			if(sObj->DSiege.iScore > iMaxScorePlayer1)
			{
				iMaxScorePlayer1 = sObj->DSiege.iScore;
				aIndex1 = n;
			}
		}

		if(iGuildRegID2 == sObj->GuildNumber)
		{
			if(sObj->DSiege.iScore > iMaxScorePlayer2)
			{
				iMaxScorePlayer2 = sObj->DSiege.iScore;
				aIndex2 = n;
			}
		}
	}

	if(aIndex1 == -1)
	{
		this->bCaptured = false;
		memcpy(this->szLordGuild, "", sizeof(this->szLordGuild)-1);
		return false;
	}

	if(aIndex2 == -1)
	{
		this->bCaptured = true;
		memcpy(this->szLordGuild, gObj[aIndex1].GuildName, sizeof(this->szLordGuild)-1);
		return false;
	}

	LPOBJ lpUserFinal1 = &gObj[aIndex1];
	LPOBJ lpUserFinal2 = &gObj[aIndex2];

	this->aIndexFinal1 = aIndex1;
	this->aIndexFinal2 = aIndex2;

	this->aGuildFinal1 = iSiegeGuild1;
	this->aGuildFinal2 = iSiegeGuild2;

	return true;
}

void CDungeonSiege::PlayerGameClose(int aIndex)	
{
	if(!this->CheckStatus(eEVENTDUNGEON_START_STAGE2))
	{
		return;
	}

	int iWinIndex = -1;

	if(aIndex == this->aIndexFinal1)
	{
		iWinIndex = this->aIndexFinal2;
	}
	if(aIndex == this->aIndexFinal2)
	{
		iWinIndex = this->aIndexFinal1;
	}

	if(iWinIndex == -1)
	{
		return;
	}

	LPOBJ lpUser = &gObj[iWinIndex];
	char szTemp[256];
	sprintf(szTemp, "[%s] %s hero of Dungeon!", this->m_EventName, lpUser->Name);
	AllSendServerMsg(szTemp);
	this->bCaptured = true;
	memcpy(this->szLordGuild, lpUser->GuildName, sizeof(this->szLordGuild)-1);
	sprintf(szTemp, "[%s] %s are new owners of the Dungeon", this->m_EventName, this->szLordGuild);
	AllSendServerMsg(szTemp);
	this->RewardSiege(lpUser->m_Index);
	this->SetStatus(eEVENTDUNGEON_CLOSE);
}

bool CDungeonSiege::PlayerWaitAttack(int aIndex, int aTargetIndex)
{
	if(!this->bEnable)
	{
		return true;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];

	if(lpUser->Connected < PLAYER_PLAYING || lpTarget->Connected < PLAYER_PLAYING)
	{
		return true;
	}

	if(lpUser->Type != OBJ_USER || lpTarget->Type != OBJ_USER)
	{
		return true;
	}

	if(this->CheckStatus(eEVENTDUNGEON_WAIT) || this->CheckStatus(eEVENTDUNGEON_WAIT_STAGE2))	
	{
		if(lpUser->MapNumber == this->m_EventMapNumber)
		{
			return false;
		}
	}

	return true;
}

void CDungeonSiege::GuildBuff(int aIndex)
{
	if(!this->m_BuffEnable)
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

	if(lpUser->GuildNumber > 0 && this->bCaptured)
	{
		if(lpUser->GuildName[0] == this->szLordGuild[0])
		{
			if(!strcmp(lpUser->GuildName, this->szLordGuild))
			{
				if(gObjSearchActiveEffect(lpUser,AT_DUNGEON_BUFF) == FALSE)
				{
					gObjApplyBuffEffectDuration(lpUser,AT_DUNGEON_BUFF,0,0,0,0,600);
				}
				return;
			}
		}
	}

	if(gObjSearchActiveEffect(lpUser,AT_DUNGEON_BUFF) == TRUE)
	{
		gObjRemoveBuffEffect(lpUser,AT_DUNGEON_BUFF);
	}
}

bool CDungeonSiege::CheckMoveGateSiege(int aIndex, int map)
{
	if(!this->bEnable)
	{
		return true;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->DSiege.bNpcClick = false;

	if(map != this->m_EventMapNumber)
	{
		return true;
	}

	if(lpUser->GuildNumber < 1)
	{
		return false;
	}

	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		if(bCaptured == false)
		{
			return false;
		}

		if(this->szLordGuild[0] == lpUser->GuildName[0])
		{
			if(!strcmp(this->szLordGuild, lpUser->GuildName))
			{
				return true;
			}
		}

		return false;
	}
	else // -> Wait & Start Battle 
	{
		if(map == this->m_EventMapNumber)
		{
			//CheckMultiWindow
			int WindowCount = 0;

			for(int n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
			{
				LPOBJ lpTempObj = &gObj[n];

				if(lpTempObj->Connected < PLAYER_PLAYING)
				{
					continue;
				}	

				if(lpUser->hdd_id == lpTempObj->hdd_id)
				{
					WindowCount++;
				}
			}

			if(WindowCount > 1)
			{
				return false;
			}

			//Check reg list guild teleport
			if(bCaptured == true)
			{
				if(this->szLordGuild[0] == lpUser->GuildName[0])
				{
					if(!strcmp(this->szLordGuild, lpUser->GuildName))
					{
						return true;
					}
				}
			}
			else
			{
				for(int i = 0; i < this->iRegCount; i++)
				{
					_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(this->reg_list[i].szGuildName);

					if(!lpGuild)
					{
						continue;
					}

					if(!strcmp(this->reg_list[i].szGuildName, lpGuild->Name))
					{
						return true;
					}
				}
			}

			return false;
		}
	}

	return true;
}

void CDungeonSiege::GCVieweSiege(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		return;
	}

	BYTE SendBuff[5000];
	int datasize = 6;
	BYTE icount = 0;

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(lpObj->MapNumber != this->m_EventMapNumber)
	{
		return;
	}

#if(OFFLINE_MODE == TRUE)
	if(lpObj->m_OfflineMode == true)
	{
		return;
	}
#endif

	if (g_MUHelperOffline.IsOffline(aIndex))
		return;

	if(lpObj->OffExp != 0 || lpObj->OffTrade != 0)
	{
		return;
	}

	for(int n = 0; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected == PLAYER_PLAYING)
		{
			if(lpTempObj->m_State == 1 || lpTempObj->m_State == 2)
			{
				if(lpObj->MapNumber == lpTempObj->MapNumber)
				{
					if(gObjCheckViewport(aIndex,lpTempObj->X,lpTempObj->Y) == 1)
					{
						if(lpTempObj->Type != OBJ_USER || lpTempObj->GuildNumber < 1) 
						{
							continue;
						}

						if(lpTempObj->MapNumber != this->m_EventMapNumber)
						{
							continue;
						}

						DUNGEON_VIEWE Vp;
		
						Vp.aIndex = n;
						Vp.GuildNumber = lpTempObj->GuildNumber;

						memcpy(&SendBuff[datasize],&Vp,sizeof(Vp));
						datasize += sizeof(Vp);

						icount++;

						if(icount == 75) 
						{
							break;
						}
					}
				}
			}
		}
	}

	if(icount > 0)
	{
		SendBuff[0] = 0xC2;
		SendBuff[1] = SET_NUMBERH(datasize);
		SendBuff[2] = SET_NUMBERL(datasize);
		SendBuff[3] = 0xFA;
		SendBuff[4] = 0x0C;
		SendBuff[5] = icount;
		DataSend(aIndex, SendBuff, datasize);
	}
}

void CDungeonSiege::GCGuildNumber(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	PMSG_GC_GUILD_INDEX pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x54, sizeof(pMsg));
	pMsg.GuildNumber = lpUser->GuildNumber;
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));

	if(!this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		this->GCPlayerScore(aIndex);
	}
}

void CDungeonSiege::GCSiegeScore()
{
	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected < PLAYER_PLAYING || lpTempObj->Type != OBJ_USER)
		{
			continue;
		}	

		this->GCPlayerScore(n);
	}
}

void CDungeonSiege::GCPlayerConnect(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	char szOwName[9];
	char szGName[9];

	PMSG_DUNGEON_SIEGE_PLAYER_CONNECT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x56, sizeof(pMsg));
	szOwName[8] = 0;
	memcpy(szOwName, this->szLordGuild, 8);
	memcpy(pMsg.szGuildOwner, szOwName, 8);
	memset(pMsg.EventName, 0, sizeof(pMsg.EventName));
	memcpy(pMsg.EventName, this->m_EventName, sizeof(pMsg.EventName));
	pMsg.iCountGuild = this->iRegCount;
	for(int i = 0; i < this->iRegCount; i++)
	{
		szGName[8] = 0;
		memcpy(szGName, this->reg_list[i].szGuildName, 8);
		pMsg.szGuildName[i][8] = 0;
		memcpy(pMsg.szGuildName[i], szGName, 8);
	}
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));

	PMSG_DUNGEON_SIEGE_STATE pMsg2;
	pMsg2.h.set((LPBYTE)&pMsg2, 0xFB, 0x57, sizeof(pMsg2));
	pMsg2.EventState = this->iEventStatus;
	DataSend(aIndex, (LPBYTE)&pMsg2, sizeof(pMsg2));

	if(!this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		this->GCPlayerScore(aIndex);
		//this->MapKick(aIndex);
	}
}

void CDungeonSiege::GCEventState()
{
	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected < PLAYER_PLAYING || lpTempObj->Type != OBJ_USER)
		{
			continue;
		}	

		PMSG_DUNGEON_SIEGE_STATE pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x57, sizeof(pMsg));
		pMsg.EventState = this->iEventStatus;
		DataSend(n, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}

void CDungeonSiege::SiegeClearScore()
{
	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected < PLAYER_PLAYING || lpTempObj->Type != OBJ_USER)
		{
			continue;
		}	

		lpTempObj->DSiege.iScore = 0;
		lpTempObj->DSiege.iScore2 = 0;

		for(int i = 0; i < this->iRegCount; i++)
		{
			_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(this->reg_list[i].szGuildName);

			if(!lpGuild)
			{
				continue;
			}

			lpGuild->DungeonSiege.iScore = 0;
		}
	}

	this->aIndexFinal1 = -1;
	this->aIndexFinal2 = -1;
	this->aGuildFinal1 = -1;
	this->aGuildFinal2 = -1;
}

void CDungeonSiege::GuildBuffCharacter(int aIndex)
{
	if(!this->m_BuffEnable)
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

	if(gObjSearchActiveEffect(lpUser, AT_DUNGEON_BUFF) == FALSE)
	{
		return;
	}

	int AddProcentDamage = this->m_BuffPlusAttackPercent;
	
	if(AddProcentDamage > 0)
	{
		lpUser->m_AttackDamageMaxLeft += ( lpUser->m_AttackDamageMaxLeft * AddProcentDamage ) / 100;
		lpUser->m_AttackDamageMinLeft += ( lpUser->m_AttackDamageMinLeft * AddProcentDamage ) / 100;
		lpUser->m_AttackDamageMaxRight += ( lpUser->m_AttackDamageMaxRight * AddProcentDamage ) / 100;
		lpUser->m_AttackDamageMinRight += ( lpUser->m_AttackDamageMinRight * AddProcentDamage ) / 100;
		lpUser->m_MagicDamageMin += ( lpUser->m_MagicDamageMin * AddProcentDamage ) / 100;
		lpUser->m_MagicDamageMax += ( lpUser->m_MagicDamageMin * AddProcentDamage ) / 100;
	}

	int AddProcentDefence = this->m_BuffPlusDefencePercent;

	if(AddProcentDefence > 0)
	{
		lpUser->m_Defense += ( lpUser->m_Defense * AddProcentDefence ) / 100;
		lpUser->m_MagicDefense += ( lpUser->m_MagicDefense * AddProcentDefence ) / 100;
	}
}

void CDungeonSiege::RewardSiege(int aIndex)
{
	if(!this->m_RewardEnable)
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

	if(this->m_RewardItemEnable)
	{
		ItemSerialCreateSend(aIndex, lpUser->MapNumber, lpUser->X, lpUser->Y, ITEMGET(this->m_RewardItemType,this->m_RewardItemIndex), this->m_RewardItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
	}

	if(this->m_RewardWCoinC > 0)
	{
		lpUser->GameShop.WCoinC += this->m_RewardWCoinC;
	}
	if(this->m_RewardWcoinP > 0)
	{
		lpUser->GameShop.WCoinP += this->m_RewardWcoinP;
	}
	if(this->m_RewardWgoinG > 0)
	{
		lpUser->GameShop.GoblinPoint += this->m_RewardWgoinG;
	}

	if(this->m_RewardWCoinC > 0 || this->m_RewardWcoinP > 0 || this->m_RewardWgoinG > 0)
	{
		gGameShop.GDSaveUserInfo(aIndex);
	}	

	if(this->m_RewardCredit > 0)
	{
		lpUser->ExCred += this->m_RewardCredit;
	}

	ExUserDataSend(aIndex);
}

bool CDungeonSiege::SiegeDarkLordSummon(int aIndex)
{
	if(!this->bEnable)
	{
		return true;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return true;
	}

	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		return true;
	}

	if(lpUser->MapNumber == this->m_EventMapNumber)
	{
		return false;
	}

	return true;
}

void CDungeonSiege::GCMapAttributeAll(int type)
{
	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected < PLAYER_PLAYING || lpTempObj->Type != OBJ_USER)
		{
			continue;
		}	

		if(lpTempObj->MapNumber != this->m_EventMapNumber)
		{
			continue;
		}

		this->GCMapAttribute(n, type);
	}
}

void CDungeonSiege::GCPlayerScore(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	PMSG_DUNGEON_SIEGE_SCORE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x55, sizeof(pMsg));
	pMsg.MyScore = lpUser->DSiege.iScore;
	pMsg.GuildCount = this->iRegCount;
	pMsg.FinalGuildID1 = 0;
	pMsg.FinalGuildID2 = 0;
	pMsg.FinalScore1 = 0;
	pMsg.FinalScore2 = 0;
	pMsg.FinalGuildID1 = 0;
	pMsg.FinalGuildID2 = 0;
	pMsg.InSiege = false;

	memset(pMsg.Name1, 0, sizeof(pMsg.Name1));
	memset(pMsg.Name2, 0, sizeof(pMsg.Name2));

	if(this->CheckStatus(eEVENTDUNGEON_WAIT_STAGE2) || this->CheckStatus(eEVENTDUNGEON_START_STAGE2))	
	{
		if(OBJMAX_RANGE(this->aIndexFinal1))
		{
			LPOBJ lpUser1 = &gObj[this->aIndexFinal1];
			pMsg.FinalScore1 = lpUser1->DSiege.iScore2;
			memcpy(pMsg.Name1, lpUser1->Name, sizeof(pMsg.Name1)-1);
		}
		if(OBJMAX_RANGE(this->aIndexFinal2))
		{
			LPOBJ lpUser2 = &gObj[this->aIndexFinal2];
			pMsg.FinalScore2 = lpUser2->DSiege.iScore2;
			memcpy(pMsg.Name2, lpUser2->Name, sizeof(pMsg.Name2)-1);
		}
		if(this->aGuildFinal1 != -1)
		{
			pMsg.FinalGuildID1 = this->aGuildFinal1;
		}
		if(this->aGuildFinal2 != -1)
		{
			pMsg.FinalGuildID2 = this->aGuildFinal2;
		}
	}

	for(int i = 0; i < this->iRegCount; i++)
	{
		pMsg.GuildScore[i] = 0;

		_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(this->reg_list[i].szGuildName);
		
		if(!lpGuild)
		{		
			continue;
		}

		if(lpUser->GuildNumber > 0)
		{
			if(lpUser->GuildName[0] == this->reg_list[i].szGuildName[0])
			{
				if(!strcmp(lpUser->GuildName, this->reg_list[i].szGuildName))
				{
					pMsg.InSiege = true;
				}
			}
		}

		pMsg.GuildScore[i] = lpGuild->DungeonSiege.iScore;
	}

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CDungeonSiege::MonsterEventDisable()
{
	for(int n = 0; n < OBJ_MAXMONSTER ; n++)
	{
		if(gObj[n].MapNumber == this->m_EventMapNumber)
		{
			LPOBJ lpObj = &gObj[n];
			lpObj->Live = false;
			//gObjViewportListProtocolDestroy(lpObj);
			//gObjViewportClose(lpObj);
		}
	}
}

void CDungeonSiege::MonsterEventEnable()
{
	for(int n = 0; n < OBJ_MAXMONSTER ; n++)
	{
		if(gObj[n].MapNumber == this->m_EventMapNumber)
		{
			LPOBJ lpObj = &gObj[n];
			lpObj->Live = true;
			//CreateFrustrum(lpObj->X, lpObj->Y, lpObj->m_Index);
			//gObjClearViewport(lpObj);
			//gObjViewportListCreate(lpObj->m_Index);
			//gObjViewportListProtocolCreate(lpObj);
		}
	}
}

bool CDungeonSiege::CheckEventStart(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		return true;
	}

	if(lpUser->MapNumber == this->m_EventMapNumber)
	{
		return false;
	}

	return true;
}

bool CDungeonSiege::DeleteGuildUser(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	//Владельцам запретить распускать гильду
	if(lpUser->GuildNumber > 0 && this->bCaptured)
	{
		if(lpUser->GuildName[0] == this->szLordGuild[0])
		{
			if(!strcmp(lpUser->GuildName, this->szLordGuild))
			{
				MsgOutput(aIndex, "[Dungeon Siege] Owner No delete guild user");
				return false;
			}
		}
	}

	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		return true;
	}

	MsgOutput(aIndex, "[Dungeon Siege] No delete guild user");

	return false;
}

void CDungeonSiege::ReturnPlayerRing()
{
	if(this->CheckStatus(eEVENTDUNGEON_WAIT_STAGE2) || this->CheckStatus(eEVENTDUNGEON_START_STAGE2))	
	{
		if(OBJMAX_RANGE(this->aIndexFinal1) && OBJMAX_RANGE(this->aIndexFinal2))
		{
			LPOBJ lpUser1 = &gObj[this->aIndexFinal1];
			LPOBJ lpUser2 = &gObj[this->aIndexFinal2];

			if(!(lpUser1->MapNumber == this->m_EventMapNumber && lpUser1->X >= 9 && lpUser1->X <= 22 && lpUser1->Y >= 152 && lpUser1->Y <= 165))
			{
				this->iTickFinal1++;

				if(this->iTickFinal1 >= 10 * 20)
				{
					gObjTeleport(this->aIndexFinal1, this->m_EventMapNumber, this->m_EventStage2KillX, this->m_EventStage2KillY);

					this->iTickFinal1 = 0;
				}
			}
			else
			{
				this->iTickFinal1 = 0;
			}

			if(!(lpUser2->MapNumber == this->m_EventMapNumber && lpUser2->X >= 9 && lpUser2->X <= 22 && lpUser2->Y >= 152 && lpUser2->Y <= 165))
			{
				this->iTickFinal2++;

				if(this->iTickFinal2 >= 10 * 20)
				{
					gObjTeleport(this->aIndexFinal2, this->m_EventMapNumber, this->m_EventStage2KillX, this->m_EventStage2KillY);

					this->iTickFinal2 = 0;
				}
			}
			else
			{
				this->iTickFinal2 = 0;
			}
		}
	}
}

#endif