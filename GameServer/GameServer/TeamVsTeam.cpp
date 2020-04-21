#include "stdafx.h"
#include "TeamVsTeam.h"
#include "..\\include\\ReadScript.h"
#include "GameMain.h"
#include "logproc.h"
#include "DSProtocol.h"
#include "BloodCastle.h"
#include "DBSockMng.h"
#include "ExUser.h"
#include "ExLicense.h"
#include "TimerEx.h"
#include "MUHelperOffline.h"

#if(EVENT_TEAM_VS_TEAM==TRUE)

CTeamVsTeam g_TeamVsTeam;

CTeamVsTeam::CTeamVsTeam()
{
	this->Init();
}

CTeamVsTeam::~CTeamVsTeam()
{
}

void CTeamVsTeam::Init()
{
	this->m_Enable				= false;
	this->m_EventStartDay		= -1;
	this->m_EventStartHour		= 0;
	this->m_EventeStartMin		= 0;
	this->m_EventDurationTime	= 0;
	this->m_EventStatus			= eEVENT_TEAMVSTEAM_CLOSE;
	this->m_TeamScore1			= 0;
	this->m_TeamScore2			= 0;
	this->m_TickCount			= 0;
	this->m_TickRemain			= 0;
	this->m_TickWait			= 0;
	this->m_NpcClass			= 0;
	this->m_NpcMap				= 0;
	this->m_NpcX				= 0;
	this->m_NpcY				= 0;
	this->m_RewardBonusEnable	= false;
	this->m_RewardBonusCount    = 0;
	this->m_RewardItemEnable	= false;
	this->m_RewardItemType		= 0;
	this->m_RewardItemIndex		= 0;
	this->m_RewardItemLevel		= 0;
	this->m_MinReset            = 0;
}

void CTeamVsTeam::Load()
{
	if(!g_ExLicense.user.bTeamVsTeam2)
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ExData\\Events\\TeamVsTeam.dat"));
}

void CTeamVsTeam::Read(char* filename)
{
	this->m_Enable				= GetPrivateProfileInt("ExTeam", "Enable", 0, filename);
	this->m_EventStartDay		= GetPrivateProfileInt("ExTeam", "EventStartDay", 0, filename);
	this->m_EventStartHour		= GetPrivateProfileInt("ExTeam", "EventStartHour", 0, filename);
	this->m_EventeStartMin		= GetPrivateProfileInt("ExTeam", "EventeStartMin", 0, filename);
	this->m_EventDurationTime	= GetPrivateProfileInt("ExTeam", "EventDurationTime", 0, filename);
	this->m_NpcClass			= GetPrivateProfileInt("ExTeam", "NpcClass", 0, filename);
	this->m_NpcMap				= GetPrivateProfileInt("ExTeam", "NpcMap", 0, filename);
	this->m_NpcX				= GetPrivateProfileInt("ExTeam", "NpcX", 0, filename);
	this->m_NpcY				= GetPrivateProfileInt("ExTeam", "NpcY", 0, filename);
	this->m_RewardBonusEnable	= GetPrivateProfileInt("ExTeam", "RewardBonusEnable", 0, filename);
	this->m_RewardBonusCount    = GetPrivateProfileInt("ExTeam", "RewardBonusCount", 0, filename);
	this->m_RewardItemEnable	= GetPrivateProfileInt("ExTeam", "RewardItemEnable", 0, filename);
	this->m_RewardItemType		= GetPrivateProfileInt("ExTeam", "RewardItemType", 0, filename);
	this->m_RewardItemIndex		= GetPrivateProfileInt("ExTeam", "RewardItemIndex", 0, filename);
	this->m_RewardItemLevel		= GetPrivateProfileInt("ExTeam", "RewardItemLevel", 0, filename);
	this->m_MinReset			= GetPrivateProfileInt("ExTeam", "MinReset", 0, filename);

	if(!this->m_Enable/* && this->CheckStatus(eEVENT_TEAMVSTEAM_WAIT) || this->CheckStatus(eEVENT_TEAMVSTEAM_START)*/)
	{
		this->SetStatus(eEVENT_TEAMVSTEAM_CLOSE);
	}

	LogAdd("%s file load!", filename);
}

void CTeamVsTeam::Run()
{
	if(!this->m_Enable)
	{
		return;
	}

	switch(this->m_EventStatus)
	{
		case eEVENT_TEAMVSTEAM_CLOSE:	
			this->ProcessStatusClose();		
			break;
		case eEVENT_TEAMVSTEAM_WAIT:	
			this->PrecessStatusWait();		
			break;
		case eEVENT_TEAMVSTEAM_START:	
			this->ProcessStatusStart();		
			break;
	}

	this->GCViewePortTvT();
}

void CTeamVsTeam::ProcessStatusClose()
{
	GetLocalTime(&this->systime);

	if(this->m_EventStartDay == -1)
	{
		if(this->m_EventStartHour == this->systime.wHour		&&
		   this->m_EventeStartMin == this->systime.wMinute		&&
#if(NEWTIMEREX)
			g_TimerEx.GetSecond() == 00)
#else
		   this->systime.wSecond == 0)
#endif
		{
			this->SetStatus(eEVENT_TEAMVSTEAM_WAIT);
		}
	}
	else
	{
		if(this->m_EventStartDay == this->systime.wDayOfWeek	&&
		   this->m_EventStartHour == this->systime.wHour		&&
		   this->m_EventeStartMin == this->systime.wMinute		&&
#if(NEWTIMEREX)
			g_TimerEx.GetSecond() == 00)
#else
		   this->systime.wSecond == 0)
#endif
		{
			this->SetStatus(eEVENT_TEAMVSTEAM_WAIT);
		}
	}
}

void CTeamVsTeam::PrecessStatusWait()
{
	int iTickMsec = (GetTickCount() - this->m_TickCount);

	if(iTickMsec >= 1000)
	{
		this->m_TickRemain -= iTickMsec;			
		this->m_TickCount = GetTickCount();

		if(this->m_TickRemain <= (60000 * TEAMVSTEAM_WAIT))
		{
			if((this->m_TickCount - this->m_TickWait) > 60000)
			{
				int iWaitMin = (this->m_TickRemain/60000) + 1;
				char szTemp[256];
				sprintf(szTemp, "[Team vs Team] start after %d minute(s)", iWaitMin);
				AllSendServerMsg(szTemp);
				this->m_TickWait = GetTickCount();
			}
		}
	}

	if(this->m_TickRemain <= 0)
	{
		int iTotalPlayer = this->DivTeam();

		if(iTotalPlayer >= TEAMVSTEAM_MINPLAYER)
		{
			this->SetStatus(eEVENT_TEAMVSTEAM_START);
		}
		else
		{
			this->SetStatus(eEVENT_TEAMVSTEAM_CLOSE);
		}
	}
}

void CTeamVsTeam::ProcessStatusStart()
{
	int iTickMsec = (GetTickCount() - this->m_TickCount);

	if(iTickMsec >= 1000)
	{
		this->m_TickRemain -= iTickMsec;			
		this->m_TickCount = GetTickCount();

	/*	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
		{
			LPOBJ lpUser = &gObj[aIndex];

			if(lpUser->Connected < PLAYER_PLAYING)
			{
				continue;
			}

			if(lpUser->MapNumber != TEAMVSTEAM_MAP)
			{
				continue;
			}
			this->GCEventTimer(aIndex);
		}*/
	}

	if(this->m_TickRemain <= 0)
	{
		this->SetStatus(eEVENT_TEAMVSTEAM_CLOSE);
	}
}

void CTeamVsTeam::SetStatus(int States)
{
	this->m_EventStatus = States;

	switch(this->m_EventStatus)
	{
		case eEVENT_TEAMVSTEAM_CLOSE:	
			this->StatusClose();	
			break;
		case eEVENT_TEAMVSTEAM_WAIT:	
			this->StatusWait();		
			break;
		case eEVENT_TEAMVSTEAM_START:	
			this->StatusStart();	
			break;
	}

	this->GCEventStatusAll();
}

bool CTeamVsTeam::CheckStatus(int Status)
{
	if(this->m_EventStatus == Status)
	{
		return true;
	}

	return false;
}

void CTeamVsTeam::StatusClose()
{
	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(lpUser->MapNumber != TEAMVSTEAM_MAP)
		{
			continue;
		}

		this->GCMapAttribute(aIndex, 0);
		GCPkLevelSend(aIndex, lpUser->m_PK_Level);
	}

	if(this->m_TeamScore1 > this->m_TeamScore2)
	{
		AllSendServerMsg("[Team vs Team] BLUE Team Win");
		this->PlayerReward(eEVENT_TVT_TEAM_1);
	}
	else if(this->m_TeamScore2 > this->m_TeamScore1)
	{
		AllSendServerMsg("[Team vs Team] GREEN Team Win");
		this->PlayerReward(eEVENT_TVT_TEAM_2);
	}	

	this->GDEventInfo();
	this->GCEventStatistic();

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		lpUser->m_TvTTeam = 0;
		lpUser->m_TvTKill = 0;
		lpUser->m_TvTDie = 0;
	}

	this->m_TeamScore1 = 0;
	this->m_TeamScore2 = 0;

	AllSendServerMsg("[Team vs Team] End");
}

void CTeamVsTeam::StatusWait()
{
	this->m_TickCount = GetTickCount();
	this->m_TickRemain = (60000 * TEAMVSTEAM_WAIT);
}

void CTeamVsTeam::StatusStart()
{
	AllSendServerMsg("[Team vs Team] Start");
	this->m_TickCount = GetTickCount();
	this->m_TickRemain = 60000 * this->m_EventDurationTime;

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(lpUser->MapNumber != TEAMVSTEAM_MAP)
		{
			continue;
		}

		this->GCTeam(aIndex);

		this->GCEventTimer(aIndex);
		
		if(lpUser->m_TvTTeam == eEVENT_TVT_TEAM_1)
		{
			gObjTeleport(aIndex, TEAMVSTEAM_MAP, TEAMVSTEAM_X1+(rand()%6-3), TEAMVSTEAM_Y1+(rand()%6-3));
		}
		else if(lpUser->m_TvTTeam == eEVENT_TVT_TEAM_2)
		{
			gObjTeleport(aIndex, TEAMVSTEAM_MAP, TEAMVSTEAM_X2+(rand()%6-3), TEAMVSTEAM_Y2+(rand()%6-3));
		}

		this->GCMapAttribute(aIndex, 1);
		ExUserVieweport(aIndex);
	}
}

bool CTeamVsTeam::NpcDialog(int aIndex, int aNpcIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(lpNpc->Class == this->m_NpcClass && lpNpc->MapNumber == this->m_NpcMap && lpNpc->X == this->m_NpcX && lpNpc->Y == this->m_NpcY)
	{
		//if(!this->CheckStatus(eEVENT_TEAMVSTEAM_WAIT))
		//{
		//	return true;
		//}

		//if(this->m_MinReset > lpUser->Reset)
		//{
		//	MsgOutput(aIndex, "[Team Vs Team] Min reset %d", this->m_MinReset);
		//	return true;
		//}

		this->GCOpenWindow(aIndex);
		return true;
	}

	return false;
}

int CTeamVsTeam::DivTeam()
{
	int iTeam = eEVENT_TVT_TEAM_1;
	int iCountPlayer = 0;

	while(true)
	{
		int aIndex = -1;
		int iMaxReset = 0;

		for(int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
		{
			LPOBJ lpUser = &gObj[i];

			if(lpUser->Connected < PLAYER_PLAYING)
			{
				continue;
			}

			if(lpUser->m_TvTTeam != 0 || lpUser->MapNumber != TEAMVSTEAM_MAP)
			{
				continue;
			}

			if(lpUser->Reset >= iMaxReset)
			{
				iMaxReset = lpUser->Reset;
				aIndex = i;
			}
		}

		if(aIndex == -1)
		{
			break;
		}

		LPOBJ lpUser = &gObj[aIndex];
		lpUser->m_TvTTeam = iTeam;
		iCountPlayer++;

		if(iTeam == eEVENT_TVT_TEAM_1)
		{
			iTeam = eEVENT_TVT_TEAM_2;
		}
		else
		{
			iTeam = eEVENT_TVT_TEAM_1;
		}
	}

	return iCountPlayer;
}

bool CTeamVsTeam::PlayerKill(int aIndex, int aTargetIndex)
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
	{
		return false;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];

	if(lpUser->Type != OBJ_USER || lpTarget->Type != OBJ_USER)
	{
		return false;
	}

	if(lpUser->Connected < PLAYER_PLAYING || lpTarget->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if(lpUser->MapNumber != TEAMVSTEAM_MAP)
	{
		return false;
	}

	if(lpTarget->m_TvTTeam == eEVENT_TVT_TEAM_1 && lpUser->m_TvTTeam == eEVENT_TVT_TEAM_2)
	{
		lpTarget->m_TvTKill++;
		lpUser->m_TvTDie++;
		this->m_TeamScore1++;	
		GCUserKillCount(lpTarget->m_Index);
	}
	else if(lpTarget->m_TvTTeam == eEVENT_TVT_TEAM_2 && lpUser->m_TvTTeam == eEVENT_TVT_TEAM_1)
	{
		lpTarget->m_TvTKill++;
		lpUser->m_TvTDie++;
		this->m_TeamScore2++;
		GCUserKillCount(lpTarget->m_Index);
	}

	this->GCEventScoreAll();

	return true;
}

bool CTeamVsTeam::AttackCheck(int aIndex, int aTargetIndex)
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
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

	if(lpUser->MapNumber != TEAMVSTEAM_MAP)
	{
		return true;
	}

	if(lpUser->m_TvTTeam == 0)
	{
		return true;
	}

	if(lpUser->m_TvTTeam != lpTarget->m_TvTTeam)
	{
		return true;
	}

	return false;
}

bool CTeamVsTeam::PKCheck(int aIndex, int aTargetIndex)
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
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

	if(lpUser->MapNumber != TEAMVSTEAM_MAP)
	{
		return true;
	}

	return false;
}

bool CTeamVsTeam::PlayerRegen(int aIndex)
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
	{
		return false;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if(lpUser->MapNumber != TEAMVSTEAM_MAP)
	{
		return false;
	}
	
	if(lpUser->m_TvTTeam == eEVENT_TVT_TEAM_1)
	{
		lpUser->X = TEAMVSTEAM_X1+(rand()%6-3);
		lpUser->Y = TEAMVSTEAM_Y1+(rand()%6-3);
	}
	else if(lpUser->m_TvTTeam == eEVENT_TVT_TEAM_2)
	{
		lpUser->X = TEAMVSTEAM_X2+(rand()%6-3);
		lpUser->Y = TEAMVSTEAM_Y2+(rand()%6-3);
	}

	return true;
}

void CTeamVsTeam::PlayerReward(int WinTeam)
{
	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(lpUser->m_TvTTeam == WinTeam)
		{
			if(this->m_RewardBonusEnable)
			{
				lpUser->GameShop.WCoinC += this->m_RewardBonusCount;
				gGameShop.GDSavePoint(aIndex);
				//g_ExUser.UpdateCharEx(aIndex);
				MsgOutput(aIndex, "[Team Vs Team]: +%d WCoin", this->m_RewardBonusCount);
			}

			if(this->m_RewardItemEnable)
			{
				int iItem = ITEMGET(this->m_RewardItemType, this->m_RewardItemIndex);
				ItemSerialCreateSend(aIndex, lpUser->MapNumber, lpUser->X, lpUser->Y, iItem, this->m_RewardItemLevel, 0, 0, 0, 0, aIndex, 0, 0);
			}
		}
	}
}

void CTeamVsTeam::GCEventStatusAll()
{
	if(!this->m_Enable)
	{
		return;
	}

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		if(gObj[aIndex].Connected < PLAYER_PLAYING)
		{
			continue;
		}

		PMSG_TVTGC_STATUS pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x80, sizeof(pMsg));
		pMsg.Status = this->m_EventStatus;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
}

void CTeamVsTeam::GCOpenWindow(int aIndex)
{
	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	PMSG_TVTGC_WINOPEN pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x81, sizeof(pMsg));
	pMsg.MinLevel = this->m_MinLevel;
	pMsg.MinReset = this->m_MinReset;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void CTeamVsTeam::CGTeleportEvent(int aIndex)
{
	if(!this->m_Enable)
	{
		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	gObjTeleport(aIndex, TEAMVSTEAM_MAP, TEAMVSTEAM_X+(rand()%10-5), TEAMVSTEAM_Y+(rand()%10-5));

	this->GCMapAttribute(aIndex, 0);

	PMSG_TVTGC_STATUS pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x80, sizeof(pMsg));
	pMsg.Status = this->m_EventStatus;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void CTeamVsTeam::GCEventScoreAll()
{
	if(!this->m_Enable)
	{
		return;
	}

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		if(gObj[aIndex].Connected < PLAYER_PLAYING && gObj[aIndex].MapNumber != TEAMVSTEAM_MAP)
		{
			continue;
		}

		PMSG_TVTGC_SCORE pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x82, sizeof(pMsg));
		pMsg.TeamScore1 = this->m_TeamScore1;
		pMsg.TeamScore2 = this->m_TeamScore2;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
}

void CTeamVsTeam::GCMapAttribute(int aIndex, int maptype)
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

void CTeamVsTeam::GCViewePortTvT()
{
	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
	{
		return;
	}

	for (int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		if(!OBJMAX_RANGE(aIndex))
		{
			continue;
		}

		BYTE SendBuff[5000];
		int datasize = 6;
		BYTE icount = 0;

		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

#if(OFFLINE_MODE == TRUE)
		if(lpUser->m_OfflineMode == true)
		{
			continue;
		}
#endif

		if (g_MUHelperOffline.IsOffline(aIndex))
		{
			continue;
		}

		if(lpUser->MapNumber != TEAMVSTEAM_MAP)
		{
			continue;
		}

		for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
		{
			LPOBJ lpTempObj = &gObj[n];

			if(lpTempObj->Connected == PLAYER_PLAYING)
			{
				if(lpTempObj->m_State == 1 || lpTempObj->m_State == 2)
				{
					if(lpUser->MapNumber == lpTempObj->MapNumber)
					{
						if(gObjCheckViewport(aIndex,lpTempObj->X,lpTempObj->Y) == 1)
						{
							if(lpTempObj->Type != OBJ_USER) continue;

							VIEWEPORT_TVT Vp;

							Vp.aIndex = n;
							Vp.Life = (DWORD)lpTempObj->Life;
							Vp.MaxLife = (DWORD)(lpTempObj->MaxLife + lpTempObj->AddLife);
							Vp.TvTTeam = lpTempObj->m_TvTTeam;

							memcpy(&SendBuff[datasize],&Vp,sizeof(Vp));
							datasize += sizeof(Vp);

							icount++;

							if(icount >= MAX_VIEWPORT-1)
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
			SendBuff[0]=0xC2;
			SendBuff[1]=SET_NUMBERH(datasize);
			SendBuff[2]=SET_NUMBERL(datasize);
			SendBuff[3]=0xFA;
			SendBuff[4]=0x10;
			SendBuff[5]=icount;

			DataSend(aIndex,SendBuff,datasize);
		}

		this->GCEventTimer(aIndex);
	}
}

void CTeamVsTeam::GCTeam(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_TVTGC_TEAM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x83, sizeof(pMsg));
	pMsg.Team = gObj[aIndex].m_TvTTeam;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

bool CTeamVsTeam::CheckDLTeleport(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return false;
	}

	if(!this->CheckStatus(eEVENT_TEAMVSTEAM_START))
	{
		return true;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if(lpUser->MapNumber != TEAMVSTEAM_MAP)
	{
		return true;
	}

	return false;
}

void CTeamVsTeam::PlayerConnect(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

#if(!DEBUG_MAP_MANAGER)
	if(lpUser->MapNumber == TEAMVSTEAM_MAP)
	{
		lpUser->MapNumber = MAP_INDEX_RORENCIA;
		MapC[lpUser->MapNumber].GetMapPos(lpUser->MapNumber, lpUser->X, lpUser->Y);
	}
#endif

	PMSG_TVTGC_STATUS pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x80, sizeof(pMsg));
	pMsg.Status = this->m_EventStatus;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void CTeamVsTeam::GDEventInfo()
{
	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(lpUser->m_TvTTeam == 0)
		{
			continue;
		}

		PMSG_TVTGD_INFO pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0C, sizeof(pMsg));
		memset(pMsg.Name, 0, sizeof(pMsg.Name));
		memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name));
		pMsg.KillCount = lpUser->m_TvTKill;
		cDBSMng.Send((char*)&pMsg, pMsg.h.size);
	}
}

void CTeamVsTeam::GCUserKillCount(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_TVTGC_KILL pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x84, sizeof(pMsg));
	pMsg.KillCount = gObj[aIndex].m_TvTKill;
	pMsg.DieCount = gObj[aIndex].m_TvTDie;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void CTeamVsTeam::GCEventTimer(int aIndex)
{
	PMSG_TVTGC_TIME pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x85, sizeof(pMsg));

	if(this->CheckStatus(eEVENT_TEAMVSTEAM_START))
	{
		pMsg.EventTime = this->m_TickRemain;
	}
	else
	{
		pMsg.EventTime = 0;
	}
	
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

#if(TEAM_VS_TEAM_INFO)
void CTeamVsTeam::GCEventStatistic()
{
	PMSG_TVT_STATISTIC pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFA, 0x11, sizeof(pMsg));
	pMsg.Count = 0;
	pMsg.Count2 = 0;

	bool iObjUser[OBJMAX];
	memset(iObjUser, 0, sizeof(iObjUser));
	
	int iCount = 0;
	int iCount2 = 0;

	while(true)
	{
		int aIndex = -1;
		int iMaxKill = 0;

		for(int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
		{
			LPOBJ lpUser = &gObj[i];

			if(lpUser->Connected < PLAYER_PLAYING)
			{
				continue;
			}

			if(lpUser->MapNumber == TEAMVSTEAM_MAP && iObjUser[i] == false)
			{
				if(lpUser->m_TvTTeam == eEVENT_TVT_TEAM_1)
				{
					if(lpUser->m_TvTKill >= iMaxKill)
					{
						iMaxKill = lpUser->m_TvTKill;
						aIndex = i;
					}
				}
				else if(lpUser->m_TvTTeam == eEVENT_TVT_TEAM_2)
				{
					if(lpUser->m_TvTKill >= iMaxKill)
					{
						iMaxKill = lpUser->m_TvTKill;
						aIndex = i;
					}
				}
			}
		}

		if(aIndex == -1)
		{
			break;
		}

		if(gObj[aIndex].m_TvTTeam == eEVENT_TVT_TEAM_1)
		{
			pMsg.stat[iCount].Name[10] = 0;
			memcpy(pMsg.stat[iCount].Name, gObj[aIndex].Name, 10);
			pMsg.stat[iCount].Kill = gObj[aIndex].m_TvTKill;
			pMsg.stat[iCount].Die = gObj[aIndex].m_TvTDie;

			iCount++;
		}
		else if(gObj[aIndex].m_TvTTeam == eEVENT_TVT_TEAM_2)
		{
			pMsg.stat2[iCount2].Name[10] = 0;
			memcpy(pMsg.stat2[iCount2].Name, gObj[aIndex].Name, 10);
			pMsg.stat2[iCount2].Kill = gObj[aIndex].m_TvTKill;
			pMsg.stat2[iCount2].Die = gObj[aIndex].m_TvTDie;

			iCount2++;
		}

		iObjUser[aIndex] = true;

		if(iCount >= 10 || iCount2 >= 10)
		{
			continue;
		}
	}

	pMsg.Count = (BYTE)iCount;
	pMsg.Count2 = (BYTE)iCount2;

	for(int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if(iObjUser[i] == true)
		{
			DataSend(i, (LPBYTE)&pMsg, sizeof(pMsg));
		}
	}
}
#endif

#endif
