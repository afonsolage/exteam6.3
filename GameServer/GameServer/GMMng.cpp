//GameServer 1.00.77 JPN - Completed
//GameServer JPN - Completed
#include "stdafx.h"
#include "GMMng.h"
#include "LogToFile.h"
#include "logproc.h"
#include "GameMain.h"
#include "protocol.h"
#include "..\common\winutil.h"
#include "MoveCommand.h"
#include "GuildClass.h"
#include "TNotice.h"
#include "BattleSoccerManager.h"
#include "giocp.h"
#include "Kanturu.h"
#include "SkillAdditionInfo.h"
#include "DSProtocol.h"
#include "BuffManager.h"
#include "NewMasterLevelSystem.h"
#include "ObjCalCharacter.h"
#include "NewMasterLevelSkillTreeSystem.h"
#include "MapClass.h"
#include "MonsterAttr.h"
#include "..\common\SetItemOption.h"
#include "ItemAddOption.h"
#include "DarkSpirit.h"
#include "IllusionTempleEvent.h"
#include "Raklion.h"
#include "RaklionBattleUserMng.h"
#include "ChaosCard.h"
#include "PCBangPointSystem.h"
#include "Configs.h"
#include "Message.h"
#include "PremiumSystem.h"
#include "ConnectEx.h"
#include "OffExp.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "JewelsBank.h"
#include "CreditDonate.h"
#include "ExLicense.h"
#ifdef IMPERIAL_CONFLICT_NEW
#include "ImperialGuardian.h"
#endif

#include "Brotherhood.h"
#include "ExFunction.h"
#include "ExUser.h"
#include "GMManager.h"
#include "BMQuest.h"
#include "SProtocol.h"
#include "Marriage.h"
#include "Shop.h"
#include "DungeonSiege.h"
#include "BloodCastle.h"
#include "BufferSystem.h"
#include "ExGDManager.h"
#include "ExText.h"
#include "PremiumSystemEx.h"
#include "AccountSecurity.h"
#include "CarnageEvent.h"
#include "BanSystem.h"
#include "QuestionAnswer.h"
#include "MUHelperOffline.h"
#include "DevilSquare.h"
#include "BloodCastle.h"
#include "ChaosCastle.h"
#include "DungeonSiege.h"
#include "PandoraBoxEvent.h"
#include "ZenGoblin.h"

CLogToFile KUNDUN_GM_LOG("KUNDUN_EVENT_GM_LOG", ".\\KUNDUN_EVENT_GM_LOG", 1);
CGMMng cManager;

CGMMng::CGMMng()
{
	this->ManagerInit();
}

CGMMng::~CGMMng()
{
	return;
}

void CGMMng::Init()
{
	this->cCommand.Init();

	this->cCommand.Add(lMsg.Get(MSGGET(11, 184)), CMD_DISCONNECT, 34);	// /segment
	this->cCommand.Add(lMsg.Get(MSGGET(11, 185)), CMD_MOVE, 35);	// /move

	this->cCommand.Add(lMsg.Get(MSGGET(11, 191)), CMD_GUILD_MOVE, 34);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 192)), CMD_GUILD_END, 34); //guild end
	this->cCommand.Add(lMsg.Get(MSGGET(11, 193)), CMD_WAR_END, 2); // warend

	this->cCommand.Add(lMsg.Get(MSGGET(11, 194)), CMD_WAR_START, 2); //warstart
	this->cCommand.Add(lMsg.Get(MSGGET(11, 195)), CMD_WAR_STOP, 2); //warstop

	this->cCommand.Add("/ability", CMD_ABILITY, 34);//
	this->cCommand.Add("/party", CMD_PARTY, 34);//
	this->cCommand.Add("/summonmonster", CMD_SUMMON_MONSTER, 34);//
	this->cCommand.Add("/clearmonster", CMD_CLEAR_MONSTER, 34);//
	this->cCommand.Add("/clearitem", CMD_CLEAR_ITEM, 34);//
	this->cCommand.Add("/clearinven", CMD_CLEAR_INVENTORY, 34);//
	this->cCommand.Add("/summonchar", CMD_SUMMON_CHAR, 34);//

	this->cCommand.Add("/zengoblinsummon", CMD_ZEN_GOBLIN_SUMMON, 34);
	this->cCommand.Add("/zengoblinunsummon", CMD_ZEN_GOBLIN_UNSUMMON, 34);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 198)), CMD_WAR, 33); //war

	this->cCommand.Add(lMsg.Get(MSGGET(11, 199)), CMD_SOCCER, 3); //soccer
	this->cCommand.Add(lMsg.Get(MSGGET(11, 200)), CMD_REQUEST, 33); //re

	this->cCommand.Add(lMsg.Get(MSGGET(11, 201)), CMD_USER_STATS, 34); //segment
	this->cCommand.Add(lMsg.Get(MSGGET(11, 202)), CMD_TRACE, 34); //trace
	this->cCommand.Add(lMsg.Get(MSGGET(11, 203)), CMD_MONITORING, 34); //monitoring

	this->cCommand.Add(lMsg.Get(MSGGET(11, 204)), CMD_DISCONNECT, 34); //disconnect
	this->cCommand.Add(lMsg.Get(MSGGET(11, 205)), CMD_MOVE, 35); //warp

	this->cCommand.Add(lMsg.Get(MSGGET(11, 211)), CMD_GUILD_MOVE, 34);	//GuildMove
	this->cCommand.Add(lMsg.Get(MSGGET(11, 212)), CMD_GUILD_END, 34);	//GuildDisconnect

	this->cCommand.Add(lMsg.Get(MSGGET(11, 213)), CMD_WAR_END, 2); //GuildWarEnd
	this->cCommand.Add(lMsg.Get(MSGGET(11, 214)), CMD_WAR_START, 2); //GuildWarStart
	this->cCommand.Add(lMsg.Get(MSGGET(11, 215)), CMD_WAR_STOP, 2); //GuildWarStop

	this->cCommand.Add(lMsg.Get(MSGGET(11, 218)), CMD_WAR, 33); //GuildWar

	this->cCommand.Add(lMsg.Get(MSGGET(11, 219)), CMD_SOCCER, 3); //BattleSoccer
	this->cCommand.Add(lMsg.Get(MSGGET(11, 220)), CMD_REQUEST, 33); //Request

	this->cCommand.Add(lMsg.Get(MSGGET(11, 221)), CMD_USER_STATS, 34); //ConnectionState
	this->cCommand.Add(lMsg.Get(MSGGET(11, 222)), CMD_TRACE, 34); //UserTracking
	this->cCommand.Add(lMsg.Get(MSGGET(11, 223)), CMD_MONITORING, 34); //UserWatching


#if(GS_CASTLE==1 || CS_SERVER)
	// CASTLESIEGE Commands
	this->cCommand.Add("/cschangeowner", CMD_CS_CHANGE_OWNER, 34);
	this->cCommand.Add("/cssetregsiege", CMD_CS_REG_SIEGE, 34);
	this->cCommand.Add("/cssetregmark", CMD_CS_REG_MARK, 34);
	this->cCommand.Add("/cssetnotify", CMD_CS_NOTIFY, 34);
	this->cCommand.Add("/cssetstart", CMD_CS_START, 34);
	this->cCommand.Add("/cssetend", CMD_CS_END, 34);
	this->cCommand.Add("/cscurowner", CMD_CS_CUR_OWNER, 34);
	this->cCommand.Add("/cscurstate", CMD_CS_CUR_STATE, 34);
	this->cCommand.Add("/cschangeside", CMD_CS_CHANGE_SIDE, 34);
	//// CRYWOLF Commands
	this->cCommand.Add(lMsg.Get(3338), CMD_CRYWOLF_NOTIFY, 34);
	this->cCommand.Add(lMsg.Get(3339), CMD_CRYWOLF_READY, 34);
	this->cCommand.Add(lMsg.Get(3340), CMD_CRYWOLF_START, 34);
	this->cCommand.Add(lMsg.Get(3341), CMD_CRYWOLF_END, 34);
#endif

	this->cCommand.Add("/hide_on", CMD_HIDE_ON, 32); //season 2.5 add-on //Ехён
	this->cCommand.Add("/hide_off", CMD_HIDE_OFF, 32); //season 2.5 add-on //ЕхёнЗШБ¦
	this->cCommand.Add("/partyleader", CMD_PARTY_LEADER, 1);

	this->cCommand.Add("/gmove", CMD_GMOVE, 32);
	//this->cCommand.Add("/vault", 601, 1);

#if(_BAN_SYSTEM_)
	this->cCommand.Add("/banchat", CMD_BAN_CHAT, 32);
	this->cCommand.Add("/banpost", CMD_BAN_POST, 32);
	this->cCommand.Add("/banchar", CMD_BAN_CHAR, 32);
	this->cCommand.Add("/banallchat", CMD_BAN_ALLCHAT, 32);
	this->cCommand.Add("/unbanchat", CMD_UNBAN_CHAT, 32);
	this->cCommand.Add("/unbanpost", CMD_UNBAN_POST, 32);
	this->cCommand.Add("/unbanallchat", CMD_UNBAN_ALLCHAT, 32);
	this->cCommand.Add("/unbanchar", CMD_UNBAN_CHAR, 32);
#endif

	this->cCommand.Add("/item", CMD_ITEM, 32);


	this->cCommand.Add("/dsopen", CMD_DS_OPEN, 32);
	this->cCommand.Add("/dsstart", CMD_DS_START, 32);
	this->cCommand.Add("/dsend", CMD_DS_END, 32);

	this->cCommand.Add("/bcopen", CMD_BC_OPEN, 32);
	this->cCommand.Add("/bcstart", CMD_BC_START, 32);
	this->cCommand.Add("/bcend", CMD_BC_END, 32);

	this->cCommand.Add("/ccopen", CMD_CC_OPEN, 32);
	this->cCommand.Add("/ccstart", CMD_CC_START, 32);
	this->cCommand.Add("/ccend", CMD_CC_END, 32);

	this->cCommand.Add("/dsiegeopen", CMD_DSIEGE_OPEN, 32);
	this->cCommand.Add("/dsiegestart", CMD_DSIEGE_START, 32);
	this->cCommand.Add("/dsiegeend", CMD_DSIEGE_END, 32);

	this->cCommand.Add("/pandorastart", CMD_PANDORA_START, 32);
	this->cCommand.Add("/pandoraend", CMD_PANDORA_END, 32);

	this->cCommand.Add("/hsexp", CMD_HS_EXP, 32);
	this->cCommand.Add("/hsup", CMD_HS_LVLUP, 32);
	this->cCommand.Add("/hsreset", CMD_HS_RESET, 32);

	this->WatchTargetIndex = -1;
}


void CGMMng::ManagerInit()
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		this->ManagerIndex[n] = -1;
	}
}


int CGMMng::ManagerAdd(char* name, int aIndex)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] == -1)
		{
			strcpy(this->szManagerName[n], name);
			this->ManagerIndex[n] = aIndex;
			return n;
		}
	}

	return -1;
}


void CGMMng::ManagerDel(char* name)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] != -1)
		{
			if (strcmp(this->szManagerName[n], name) == 0)
			{
				this->ManagerIndex[n] = -1;
				//break;
				return; //Original Code (GS 0.65)
			}
		}
	}
}


void CGMMng::ManagerSendData(LPSTR szMsg, int size)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] != -1)
		{
			GCServerMsgStringSend(szMsg, this->ManagerIndex[n], 0);
		}
	}
}

void CGMMng::DataSend(LPBYTE szMsg, int size)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] != -1)
		{
			::DataSend(this->ManagerIndex[n], szMsg, size);
		}
	}
}


void CGMMng::BattleInfoSend(char* Name1, BYTE score1, char* Name2, BYTE score2)
{
	for (int n = 0; n < MAX_GAME_MASTER; n++)
	{
		if (this->ManagerIndex[n] != -1)
		{
			GCGoalSend(this->ManagerIndex[n], Name1, score1, Name2, score2);
		}
	}
}


int CGMMng::GetCmd(char* szCmd)
{
	for (int n = 0; n < MAX_GM_COMMAND; n++)
	{
		if (this->cCommand.nCmdCode[n] > 0)
		{
			if (stricmp(szCmd, this->cCommand.szCmd[n]) == 0)
			{
				return this->cCommand.nCmdCode[n];
			}
		}
	}

	return 0;
}

// 005708B0 -> calls 1x from ManagementProc
BYTE CGMMng::GetData(char *szCmd, int &command_code, int &gamemaster_code)
{
	for (int n = 0; n < MAX_GM_COMMAND; n++)
	{
		if (this->cCommand.nCmdCode[n] > 0)
		{
			if (stricmp(szCmd, this->cCommand.szCmd[n]) == 0)
			{
				command_code = this->cCommand.nCmdCode[n];
				gamemaster_code = this->cCommand.nGMCode[n];

				return TRUE;
			}
		}
	}

	return 0;
}

char* CGMMng::GetTokenString()
{
	//Original Code (GS 0.65)
	char seps[] = " ";
	return strtok(NULL, seps);
}

int CGMMng::GetTokenNumber()
{
	char seps[] = " ";
	char * szToken;

	szToken = strtok(NULL, seps);

	if (szToken != NULL)
	{
		return atoi(szToken);
	}
	return 0;
}

wchar_t *CodePageToUnicode(int codePage, char* src)
{
	if (!src) return 0;
	int srcLen = strlen(src);
	if (!srcLen)
	{
		wchar_t *w = new wchar_t[1];
		w[0] = 0;
		return w;
	}

	int requiredSize = MultiByteToWideChar(codePage,
		0,
		src, srcLen, 0, 0);

	if (!requiredSize)
	{
		return 0;
	}

	wchar_t *w = new wchar_t[requiredSize + 1];
	w[requiredSize] = 0;

	int retval = MultiByteToWideChar(codePage,
		0,
		src, srcLen, w, requiredSize);
	if (!retval)
	{
		delete[] w;
		return 0;
	}

	return w;
}

char* UnicodeToCodePage(int codePage, wchar_t *src)
{
	if (!src) return 0;
	int srcLen = wcslen(src);
	if (!srcLen)
	{
		char *x = new char[1];
		x[0] = '\0';
		return x;
	}

	int requiredSize = WideCharToMultiByte(codePage,
		0,
		src, srcLen, 0, 0, 0, 0);

	if (!requiredSize)
	{
		return 0;
	}

	char *x = new char[requiredSize + 1];
	x[requiredSize] = 0;

	int retval = WideCharToMultiByte(codePage,
		0,
		src, srcLen, x, requiredSize, 0, 0);
	if (!retval)
	{
		delete[] x;
		return 0;
	}

	return x;
}

void CirilicaFIX2(char* s)
{
	int i = 0;
	int k = 0;
	for (i = 0, k = 0; s[i]; k++)
	{
		if (s[i] < 0)
		{
			s[k] = (s[i] + 48) * 64 + s[i + 1] + 48;
			i += 2;
		}
		else
		{
			s[k] = s[i];
			i++;
		}
	}
	s[k] = NULL;
}


int CGMMng::ManagementProc(LPOBJ lpObj, char* szCmd, int aIndex) //00570A00
{
	//Original Code (GS 0.65)
	char seps[] = " ";
	char *szCmdToken;
	char string[256];
	char szId[20];
	char *pId = szId;

	int len = strlen(szCmd);
	if (len < 1 || len > 250) return FALSE;

	memset(szId, 0, 20);

	strcpy(string, szCmd);

	szCmdToken = strtok(string, seps);
	int command_number = GetCmd(szCmdToken);

	int command_code, gamemaster_code;//Season 4.5 addon

	if (this->GetData(szCmdToken, command_code, gamemaster_code) == FALSE)//Season 4.5 addon
	{
		return FALSE;
	}

	if (CheckAuthorityCondition(gamemaster_code, lpObj) == FALSE)//Season 4.5 addon
	{
		return FALSE;
	}

	switch (command_code)
	{
	case CMD_MONITORING:
	{
		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		LPOBJ lpTargetObj = gObjFind(pId);

		if (lpTargetObj == NULL)
		{
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]	[ %s ]	[ %s ] / Target : [%s][%s] : %s ",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
			lpTargetObj->Name, "User Watching");

		char szTemp[256];

		if (this->WatchTargetIndex == lpTargetObj->m_Index)
		{
			this->WatchTargetIndex = -1;

			wsprintf(szTemp, "%s : °ЁЅГЗШБ¦", lpTargetObj->Name);	// #translation
			GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
		}
		else
		{
			wsprintf(szTemp, "%s : °ЁЅГЅГАЫ", lpTargetObj->Name);	// #translation
			GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
			this->WatchTargetIndex = lpTargetObj->m_Index;
		}
	}
	break;
	case CMD_TRACE:
	{
		// ----
		if (!g_GMManager.CheckCommand(aIndex, egm_cmd_trace))
		{
			return false;
		}
		// ----
		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		int map;
		int iX;
		int iY;
		LPOBJ lpTargetObj = gObjFind(pId);
		int iIndex;

		if (lpTargetObj == NULL)
		{
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
			lpTargetObj->Name, "User Tracking");
		map = lpTargetObj->MapNumber;
		iX = lpTargetObj->X;
		iY = lpTargetObj->Y;
		iIndex = lpObj->m_Index;

		if (iIndex >= 0)
		{
			gObjTeleport(iIndex, map, iX, iY);
		}
	}
	break;
	case CMD_USER_STATS:
	{
		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
			"User Stat (connection)");

		int lc151 = 0;
		int lc152 = 400;
		int iTokenNumber = this->GetTokenNumber();

		if (iTokenNumber > 0)
		{
			lc151 = iTokenNumber;
		}

		int iTokenNumber2 = this->GetTokenNumber();

		if (iTokenNumber2 > 0)
		{
			lc152 = iTokenNumber2;
		}

		gObjSendUserStatistic(lpObj->m_Index, lc151, lc152);
	}
	break;
	case CMD_DISCONNECT:
	{
		// ----
		if (!g_GMManager.CheckCommand(aIndex, egm_cmd_disconnect))
		{
			return false;
		}
		// ----
		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		int iTargetIndex = gObjGetIndex(pId);

		if (iTargetIndex >= 0)
		{
			LPOBJ lpTargetObj = gObjFind(pId);

			if (lpTargetObj == NULL)
			{
				return 0;
			}

			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
				lpTargetObj->Name, "User Disconnect");
			LogAdd(lMsg.Get(MSGGET(1, 191)), pId);

#if(_RECONNECT_)
			g_ConnectEx.SendClose(lpTargetObj->m_Index, NORM_DC);
#else
			CloseClient(iTargetIndex);
#endif
		}
	}
	break;
	case CMD_GUILD_END:
	{
		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
			"Guild Disconnect");

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		_GUILD_INFO_STRUCT * lpGuild = Guild.SearchGuild(pId);
		int iIndex;

		if (lpGuild != NULL)
		{
			for (int i = 0; i < MAX_USER_GUILD; i++)
			{
				if (lpGuild->Index[i] >= 0)
				{
					iIndex = lpGuild->Index[i];

					if (iIndex >= 0)
					{
						LogAdd(lMsg.Get(MSGGET(1, 191)), pId);
						CloseClient(iIndex);
					}
				}
			}
		}
	}
	break;
	case CMD_MOVE:
	{
		pId = this->GetTokenString();

		if (pId != NULL)
		{
			int lc165 = -1;
			int lc166 = 0;
			int lc167 = 0;

			if (lpObj->Teleport != 0)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
				return 0;
			}

			if ((lpObj->m_IfState.use) != 0)
			{
				if (lpObj->m_IfState.type == 3)
				{
					lpObj->TargetShopNumber = -1;
					lpObj->m_IfState.type = 0;
					lpObj->m_IfState.use = 0;
				}
			}

			if (lpObj->m_IfState.use > 0)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
				return 0;
			}

			if (gObj[aIndex].IsInBattleGround != false)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
				return 0;
			}

			BOOL bPlayerKiller = FALSE; //Season 2.5 add-on

			if (ExConfig.PvP.ExPkPartySystem && gObj[aIndex].PartyNumber >= 0) //Season 2.5 add-on
			{
				if (gParty.GetPkLevel(gObj[aIndex].PartyNumber) >= 5)
				{
					bPlayerKiller = TRUE;
				}
			}

			if (gObj[aIndex].m_PK_Level >= 5)
			{
				bPlayerKiller = TRUE;
			}

			if (bPlayerKiller == TRUE)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(4, 101)), lpObj->m_Index, 1);
				return 0;
			}

			gMoveCommand.Move(lpObj, pId);
		}
	}
	break;
	case CMD_GUILD_MOVE:
	{
		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
			"Guild SetPosition");

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		int iTokenNumber1 = this->GetTokenNumber();
		int iTokenNumber2 = this->GetTokenNumber();
		int iTokenNumber3 = this->GetTokenNumber();
		_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(pId);
		int iIndex;

		if (lpGuild != NULL)
		{
			for (int i = 0; i < MAX_USER_GUILD; i++)
			{
				if (lpGuild->Index[i] >= 0)
				{
					iIndex = lpGuild->Index[i];
					gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2++, iTokenNumber3);
				}
			}
		}
	}
	break;
	case CMD_WAR_START:
	{
		if ((lpObj->Authority & 2) == 2)
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
				"Start BattleSoccer");

			BattleSoccerGoalStart(0);
		}
	}
	break;
	case CMD_WAR_STOP:
	{
		if ((lpObj->Authority & 2) == 2)
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
				"Stop BattleSoccer");

			BattleSoccerGoalEnd(0);
		}
		else
		{
			if (gObj[aIndex].lpGuild != NULL)
			{
				if (gObj[aIndex].lpGuild->WarType == 1)
				{
					if (strcmp(gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0]) == 0)
					{
						if (gObj[aIndex].lpGuild->BattleGroundIndex >= 0)
						{
							//BattleSoccerGoalEnd(gObj[aIndex].lpGuild->BattleGroundIndex);
							//GCServerMsgStringSend("GuildMaster їдГ»Аё·О 3ГК ИД °ж±в°Ў АЪµїАё·О Бѕ·бµЛґПґЩ.", aIndex, 0);
						}
					}
				}
			}
		}
	}
	break;
	case CMD_WAR_END:
	{
		if ((lpObj->Authority & 2) == 2)
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "End GuildWar");

			char * szGuild = this->GetTokenString();

			if (szGuild != NULL)
			{
				GCManagerGuildWarEnd(szGuild);
			}
		}
		else
		{
			if (gObj[aIndex].lpGuild != NULL && gObj[aIndex].lpGuild->lpTargetGuildNode != NULL)
			{
				if (strcmp(gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0]) == 0)
				{
					if (gObj[aIndex].lpGuild->BattleGroundIndex >= 0 && gObj[aIndex].lpGuild->WarType == 1)
					{
						::gObjAddMsgSendDelay(&gObj[aIndex], 7, aIndex, 10000, 0);

						char szTemp[100];

						wsprintf(szTemp, lMsg.Get(MSGGET(4, 129)), gObj[aIndex].lpGuild->Names[0]);
						::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild, szTemp, 1);
						::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild->lpTargetGuildNode, szTemp, 1);
					}
				}
			}
		}
	}
	break;
	case CMD_WAR:
	{
		pId = this->GetTokenString();

		if (pId != NULL)
		{
			if (strlen(pId) >= 1)
			{
				::GCGuildWarRequestResult(pId, aIndex, 0);
			}
		}
	}
	break;
	case CMD_SOCCER:
	{
		if ((lpObj->Authority & 2) == 2)
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "Set GuildWar");

			pId = this->GetTokenString();

			if (pId != NULL)
			{
				char * Rival = this->GetTokenString();

				if (Rival != NULL)
				{
					if (strlen(pId) >= 1)
					{
						if (strlen(Rival) >= 1)
						{
							::GCManagerGuildWarSet(pId, Rival, 1);
						}
					}
				}
			}
		}
		else
		{
			if (gEnableBattleSoccer != FALSE)
			{
				pId = this->GetTokenString();

				if (pId != NULL)
				{
					if (strlen(pId) >= 1)
					{
						::GCGuildWarRequestResult(pId, aIndex, 1);
					}
				}
			}
		}
	}
	break;
	case CMD_REQUEST:
	{
		pId = this->GetTokenString();

		if (pId != NULL)
		{
			BOOL bState;

			if (strcmp(pId, "on") == 0)
			{
				bState = TRUE;
			}
			else if (strcmp(pId, "off") == 0)
			{
				bState = FALSE;
			}

			if (bState >= FALSE && bState <= TRUE)
			{
				::gObjSetTradeOption(aIndex, bState);
				::gObjSetDuelOption(aIndex, bState);
			}
		}
	}
	break;
#if(GS_CASTLE==1 || CS_SERVER)
	case CMD_CS_CHANGE_OWNER:
		char *szNewOwnerGuild;
		szNewOwnerGuild = this->GetTokenString();
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 0, szNewOwnerGuild);
		break;
	case CMD_CS_REG_SIEGE:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 1, 0);
		break;
	case CMD_CS_REG_MARK:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 2, 0);
		break;
	case CMD_CS_NOTIFY:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 3, 0);
		break;
	case CMD_CS_START:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 4, 0);
		break;
	case CMD_CS_END:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 5, 0);
		break;
	case CMD_CS_CUR_OWNER:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 6, 0);
		break;
	case CMD_CS_CUR_STATE:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 7, 0);
		break;
	case CMD_CS_CHANGE_SIDE:
		char *szGuildName;
		szGuildName = this->GetTokenString();
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 8, szGuildName);
		break;
	case CMD_CRYWOLF_NOTIFY:
		g_Crywolf.OperateGmCommand(lpObj->m_Index, 1);
		break;
	case CMD_CRYWOLF_READY:
		g_Crywolf.OperateGmCommand(lpObj->m_Index, 2);
		break;
	case CMD_CRYWOLF_START:
		g_Crywolf.OperateGmCommand(lpObj->m_Index, 3);
		break;
	case CMD_CRYWOLF_END:
		g_Crywolf.OperateGmCommand(lpObj->m_Index, 0);
		break;
#endif
	case CMD_HIDE_ON:
	{
		if ((lpObj->Authority & 32) != 32)
		{
			return FALSE;
		}

		gObjApplyBuffEffectDuration(lpObj, AT_INVISIBILITY, 0, 0, 0, 0, -10);
		gObjViewportListProtocolDestroy(lpObj);
	}
	break;
	case CMD_HIDE_OFF:
	{
		if ((lpObj->Authority & 32) != 32)
		{
			return FALSE;
		}
		gObjRemoveBuffEffect(lpObj, AT_INVISIBILITY);
		gObjViewportListProtocolCreate(lpObj);
	}
	break;
	case CMD_ABILITY:
		this->CmdAbility(lpObj, this->GetTokenString());
		break;
	case CMD_PARTY:
		this->CmdParty(lpObj, this->GetTokenString());
		break;
	case CMD_SUMMON_MONSTER:
	{
		int cls = this->GetTokenNumber();
		int ct = this->GetTokenNumber();
		this->CmdSummonMonster(lpObj, cls, ct);
	}
	break;
	case CMD_CLEAR_MONSTER:
		this->CmdClearMonster(lpObj, this->GetTokenNumber());
		break;
	case CMD_CLEAR_ITEM:
		this->CmdClearItem(lpObj, this->GetTokenNumber());
		break;
	case CMD_CLEAR_INVENTORY:
		this->CmdClearInven(lpObj);
		break;
	case CMD_SUMMON_CHAR:
		this->CmdSummonChar(lpObj, this->GetTokenString());
		break;
		//PCBang Related
	case CMD_GMOVE:
	{
		//if(CheckAuthorityCondition(34,lpObj) == 1)//Season 4.5 addon
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_gmove))
			{
				return false;
			}
			// ----
			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			int iTokenNumber1 = this->GetTokenNumber();
			int iTokenNumber2 = this->GetTokenNumber();
			int iTokenNumber3 = this->GetTokenNumber();
			int iIndex = gObjGetIndex(pId);
			LPOBJ lpTargetObj;

			if (iIndex >= 0)
			{
				lpTargetObj = gObjFind(pId);

				if (lpTargetObj == NULL)
				{
					return 0;
				}

				LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
					lpTargetObj->Name, "User SetPosition");

				gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2, iTokenNumber3);
			}
		}
	}
	break;
#if(_NEW_PT_SYSTEM_==1)
	case CMD_PARTY_LEADER:
	{
		if (!ExConfig.CommonServer.CommandSetLeader)return false;
		char * TargetName = this->GetTokenString();
		if (TargetName == NULL) return false;
		int TargetIndex = gObjGetIndex(TargetName);
		// ----
		if (!gParty.SetLeader(lpObj->m_Index, TargetIndex))
		{
			return false;
		}
	}
	break;
#endif
#if(_BAN_SYSTEM_)
	case CMD_BAN_CHAT:	//BanChat
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
			{
				return false;
			}
			// ----
			char * TargetName = this->GetTokenString();
			int iTokenNumber1 = this->GetTokenNumber();
			if (TargetName == NULL) return 0;
			int TargetIndex = gObjGetIndex(TargetName);
			if (TargetIndex == -1) return 0;
			LPOBJ lpTargetObj = &gObj[TargetIndex];
			lpTargetObj->BanChat = time(NULL) + (iTokenNumber1 * 3600);
			MsgNormal(aIndex, "[BanChat]: %s %d Hour", lpTargetObj->Name, iTokenNumber1);
			MsgNormal(TargetIndex, "[BanChat]: %d Hour", iTokenNumber1);
		}
	}
	break;
	// ---
	case CMD_BAN_POST:	//BanPost
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
			{
				return false;
			}
			// ----
			char * TargetName = this->GetTokenString();
			int iTokenNumber1 = this->GetTokenNumber();
			if (TargetName == NULL) return 0;
			int TargetIndex = gObjGetIndex(TargetName);
			if (TargetIndex == -1) return 0;
			LPOBJ lpTargetObj = &gObj[TargetIndex];
			lpTargetObj->BanPost = time(NULL) + (iTokenNumber1 * 3600);
			MsgNormal(aIndex, "[BanPost]: %s %d Hour", lpTargetObj->Name, iTokenNumber1);
			MsgNormal(TargetIndex, "[BanPost]: %d Hour", iTokenNumber1);
		}
	}
	break;
	// ---
	case CMD_BAN_CHAR:	//BanChar
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_banchar))
			{
				return false;
			}
			// ----
			char * TargetName = this->GetTokenString();
			int iTokenNumber1 = this->GetTokenNumber();
			if (TargetName == NULL) return 0;
			int TargetIndex = gObjGetIndex(TargetName);
			if (TargetIndex == -1) return 0;
			LPOBJ lpTargetObj = &gObj[TargetIndex];
			lpTargetObj->BanChar = time(NULL) + (iTokenNumber1 * 3600);
			MsgNormal(aIndex, "[BanChar]: %s %d Hour", lpTargetObj->Name, iTokenNumber1);
			MsgNormal(TargetIndex, "[BanChar]: %d Hour", iTokenNumber1);
#ifdef _RECONNECT_
			g_ConnectEx.SendClose(TargetIndex, 0);
#else
			CloseClient(TargetIndex);
#endif
		}
	}
	break;
	case CMD_BAN_ALLCHAT:	//Ban All Chat
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
			{
				return false;
			}
			// ----
			char * TargetName = this->GetTokenString();
			int iTokenNumber1 = this->GetTokenNumber();
			if (TargetName == NULL) return 0;
			int TargetIndex = gObjGetIndex(TargetName);
			if (TargetIndex == -1) return 0;
			LPOBJ lpTargetObj = &gObj[TargetIndex];
			lpTargetObj->BanChat = time(NULL) + (iTokenNumber1 * 3600);
			lpTargetObj->BanPost = time(NULL) + (iTokenNumber1 * 3600);
			MsgNormal(aIndex, "[BanAllChat]: %s %d Hour", lpTargetObj->Name, iTokenNumber1);
			MsgNormal(TargetIndex, "[BanAllChat]: %d Hour", iTokenNumber1);
		}
	}
	break;
	// ---

	case CMD_UNBAN_CHAT:	//UnBanChat
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
			{
				return false;
			}
			// ----
			char * TargetName = this->GetTokenString();
			if (TargetName == NULL) return 0;
			int TargetIndex = gObjGetIndex(TargetName);
			if (TargetIndex == -1) return 0;
			LPOBJ lpTargetObj = &gObj[TargetIndex];
			lpTargetObj->BanChat = 0;
			MsgNormal(aIndex, "[UnBanChat]: %s", lpTargetObj->Name);
			MsgNormal(TargetIndex, "[UnBanChat]");
		}
	}
	break;
	// ---
	case CMD_UNBAN_POST:	//UnBanPost
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
			{
				return false;
			}
			// ----
			char * TargetName = this->GetTokenString();
			if (TargetName == NULL) return 0;
			int TargetIndex = gObjGetIndex(TargetName);
			if (TargetIndex == -1) return 0;
			LPOBJ lpTargetObj = &gObj[TargetIndex];
			lpTargetObj->BanPost = 0;
			MsgNormal(aIndex, "[UnBanPost]: %s", lpTargetObj->Name);
			MsgNormal(TargetIndex, "[UnBanPost]");
		}
	}
	break;
	// ---
	case CMD_UNBAN_ALLCHAT:	//UnBan All Chat
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
			{
				return false;
			}
			// ----
			char * TargetName = this->GetTokenString();
			if (TargetName == NULL) return 0;
			int TargetIndex = gObjGetIndex(TargetName);
			if (TargetIndex == -1) return 0;
			LPOBJ lpTargetObj = &gObj[TargetIndex];
			lpTargetObj->BanChat = 0;
			lpTargetObj->BanPost = 0;
			MsgNormal(aIndex, "[UnBanAllChat]: %s", lpTargetObj->Name);
			MsgNormal(TargetIndex, "[UnBanAllChat]");
		}
	}
	break;
	// ---
	case CMD_UNBAN_CHAR: //UnBan Char
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			// ----
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_banchar))
			{
				return false;
			}
			// ----
			char * TargetName = this->GetTokenString();
			if (TargetName == NULL) return 0;
			BAN_CHAR_GS pMsg;
			pMsg.h.set((LPBYTE)&pMsg, 0xE2, 0x00, sizeof(BAN_CHAR_GS));
			pMsg.Result = 1;
			pMsg.Type = 3;
			pMsg.aIndex = aIndex;
			memcpy(pMsg.Name, TargetName, 11);
			cDBSMng.Send((char*)&pMsg, pMsg.h.size);
		}
	}
	break;
#endif
#if(COMMAND_DROP)
	case CMD_ITEM:
	{
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			if (!g_GMManager.CheckCommand(aIndex, egm_cmd_item))
			{
				return false;
			}

			int type = GetTokenNumber();
			int index = GetTokenNumber();
			int ItemLevel = GetTokenNumber();
			int ItemSkill = GetTokenNumber();
			int ItemLuck = GetTokenNumber();
			int ItemOpt = GetTokenNumber();
			int ItemExc = GetTokenNumber();
			int ItemAncient = GetTokenNumber();
			int dur = 0;
			dur = GetTokenNumber();

			if ((type >= 0 && type <= 15))
			{
				int Item = ItemGetNumberMake(type, index);

				if (Item == -1)
				{
					GCServerMsgStringSend("[Make] no item", lpObj->m_Index, 1);
					return FALSE;
				}

				if (Item == ITEMGET(13, 4) || Item == ITEMGET(13, 5))
				{
					PetItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, ItemLevel, dur, ItemSkill, ItemLuck, ItemOpt, aIndex, ItemExc, ItemAncient);
				}
				else
				{
					ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item, ItemLevel, dur, ItemSkill, ItemLuck, ItemOpt, aIndex, ItemExc, ItemAncient);
				}
			}
		}
	}
	break;
#endif
	case CMD_DS_OPEN:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			g_DevilSquare.SetState(eDevilSquareState::DevilSquare_OPEN);
		}
		break;
	case CMD_DS_START:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			g_DevilSquare.SetState(eDevilSquareState::DevilSquare_PLAYING);
		}
		break;
	case CMD_DS_END:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			g_DevilSquare.SetState(eDevilSquareState::DevilSquare_CLOSE);
		}
		break;
	case CMD_BC_OPEN:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			int idx = GetTokenNumber();
			g_BloodCastle.m_BridgeData[idx].m_iBC_REMAIN_MSEC = g_BloodCastle.m_iBC_TIME_MIN_OPEN * 60 * 1000;
			g_BloodCastle.m_BridgeData[idx].m_iBC_STATE = BC_STATE_CLOSED;
		}
		break;
	case CMD_BC_START:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			int idx = GetTokenNumber();
			g_BloodCastle.SetState(idx, BC_STATE_PLAYING);
		}
		break;
	case CMD_BC_END:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			int idx = GetTokenNumber();
			g_BloodCastle.SetState(idx, BC_STATE_PLAYEND);
		}
		break;
	case CMD_CC_OPEN:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			int idx = GetTokenNumber();
			g_ChaosCastle.m_stChaosCastleData[idx].m_iCC_REMAIN_MSEC = g_BloodCastle.m_iBC_TIME_MIN_OPEN * 60 * 1000;
			g_ChaosCastle.m_stChaosCastleData[idx].m_iCC_STATE = BC_STATE_CLOSED;
		}
		break;
	case CMD_CC_START:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			int idx = GetTokenNumber();
			g_ChaosCastle.SetState(idx, CC_STATE_PLAYING);
		}
		break;
	case CMD_CC_END:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			int idx = GetTokenNumber();
			g_ChaosCastle.SetState(idx, CC_STATE_PLAYEND);
		}
		break;
	case CMD_PANDORA_START:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			gPandoraBoxEvent.Start();
		}
		break;
	case CMD_PANDORA_END:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			gPandoraBoxEvent.End();
		}
		break;
	case CMD_ZEN_GOBLIN_SUMMON:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			g_ZenGoblin.Summon(lpObj);
		}
		break;
	case CMD_ZEN_GOBLIN_UNSUMMON:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
		}
		break;
	case CMD_HS_EXP:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			auto exp = this->GetTokenNumber();
			g_HuntingSystem.AddExp(lpObj->m_Index, exp);
		}
		break;
	case CMD_HS_LVLUP:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			auto lvlCount = this->GetTokenNumber();
			
			if (lvlCount == 0)
				lvlCount = 1;

			lpObj->m_HuntingLevel += lvlCount;
			lpObj->m_HuntingPoints += lvlCount;
			lpObj->m_HuntingExp = 0;

			g_HuntingSystem.SendData(lpObj->m_Index);
		}
		break;
	case CMD_HS_RESET:
		if (lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			lpObj->m_HuntingLevel = 0;
			lpObj->m_HuntingPoints = 0;
			lpObj->m_HuntingExp = 0;
			memset(lpObj->m_HuntingSkillLevel, 0, sizeof(lpObj->m_HuntingSkillLevel));

			g_HuntingSystem.SendData(lpObj->m_Index);

		}
		break;
	}
	return 0;
}

void CGMMng::GetInfinityArrowMPConsumption(LPOBJ lpObj)
{
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·®[+0:%d] [+1:%d] [+2:%d]",
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus0(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus1(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus2());
}

void CGMMng::ControlInfinityArrowMPConsumption0(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus0(iValue);
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·® єЇ°ж(+0) : %d", iValue);

}

void CGMMng::ControlInfinityArrowMPConsumption1(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus1(iValue);
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·® єЇ°ж(+1) : %d", iValue);

}

void CGMMng::ControlInfinityArrowMPConsumption2(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus2(iValue);
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·® єЇ°ж(+2) : %d", iValue);

}

void CGMMng::ControlInfinityArrowMPConsumption3(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus3(iValue);
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·® єЇ°ж(+3) : %d", iValue);

}

void CGMMng::SetInfinityArrowTime(LPOBJ lpObj, int iValue)
{
	if (lpObj->Class == CLASS_ELF && lpObj->Type == OBJ_USER && lpObj->ChangeUP == 1)
	{
		MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм ЅГ°Ј °­Б¦ јіБ¤ : %dГК", iValue);
	}
	else
	{
		MsgOutput(lpObj->m_Index, "220·№є§ АМ»у №ВБої¤ЗБёё »зїл°ЎґЙЗХґПґЩ.");
	}
}

void CGMMng::ControlFireScreamDoubleAttackDistance(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetFireScreamExplosionAttackDistance(iValue);
	MsgOutput(lpObj->m_Index, "ЖДАМѕоЅєЕ©ёІ ґхєнµҐ№МБц Жш№Я°Её® єЇ°ж:%d", iValue);
}

// #Season 4.5 NEW FUNCS START
//00577CF0 
void CGMMng::CmdAbility(LPOBJ lpObj, char *szName)
{
	LPOBJ lpTargetObj = 0;
	int tIndex = -1;

	char szText[256];

	memset(szText, 0, sizeof(szText));

	if (szName == NULL)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	tIndex = gObjGetIndex(szName);

	if (tIndex <= 0)
	{
		GCServerMsgStringSend("Result-User Not Found", lpObj->m_Index, 1);
		return;
	}

	lpTargetObj = &gObj[tIndex];

	wsprintf(szText, "Result-Ability(%s)", szName);

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);

	int loc68 = 0;

	memset(szText, 0, sizeof(szText));

	if (lpTargetObj->Class >= 0 && lpTargetObj->Class <= 5)
	{
		char classname[6][20] = {
			"WIZARD",
			"KNIGHT",
			"ELF",
			"MAGUMSA",
			"DARKLORD",
			"SUMMONER"
		};

		wsprintf(szText, "Class:%s", classname[lpTargetObj->Class]);
		GCServerMsgStringSend(szText, lpObj->m_Index, 1);
	}

	memset(szText, 0, sizeof(szText));

	wsprintf(szText, "Strength[%d] Dexterity[%d] Vitality[%d] Energy[%d] Leadership[%d]",
		lpTargetObj->AddStrength + lpTargetObj->Strength,
		lpTargetObj->AddDexterity + lpTargetObj->Dexterity,
		lpTargetObj->AddVitality + lpTargetObj->Vitality,
		lpTargetObj->AddEnergy + lpTargetObj->Energy,
		lpTargetObj->AddLeadership + lpTargetObj->Leadership);

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdParty(LPOBJ lpObj, char *szName)
{
	LPOBJ lpTargetObj = 0;
	int tIndex = -1;

	char szText[256];

	memset(szText, 0, sizeof(szText));

	if (szName == NULL)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	tIndex = gObjGetIndex(szName);

	if (tIndex <= 0)
	{
		GCServerMsgStringSend("Result-User Not Found", lpObj->m_Index, 1);
		return;
	}

	if (gObj[tIndex].PartyNumber < 0)
	{
		GCServerMsgStringSend("Result-Party Not Found", lpObj->m_Index, 1);
		return;
	}

	PARTY_STRUCT * lpParty = &gParty.m_PartyS[gObj[tIndex].PartyNumber];//loc68

	if (lpParty == 0)
	{
		GCServerMsgStringSend("Result-Invalid Point", lpObj->m_Index, 1);
		return;
	}

	GCServerMsgStringSend("Result-Party", lpObj->m_Index, 1);

	int PartyCount = 0;
	int PartyNumber = -1;//loc70

	for (int i = 0; i < 5; i++)
	{
		PartyNumber = lpParty->Number[i];

		if (PartyNumber < 0)
		{
			continue;
		}

		LPOBJ lpPartyObj = &gObj[PartyNumber];

		if (lpPartyObj != NULL)
		{
			if (lpPartyObj->Connected >= PLAYER_PLAYING)
			{
				PartyCount++;

				strcat(szText, lpPartyObj->Name);

				if (i == 0)
				{
					strcat(szText, "(Leader)");
				}

				if (lpParty->Count > PartyCount)
				{
					strcat(szText, ", ");
				}
			}
		}
	}

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdSummonMonster(LPOBJ lpObj, int MonsterClass, int MonsterCount)
{
	char szText[256];

	memset(szText, 0, sizeof(szText));

	if (MonsterCount < 1)
	{
		MonsterCount = 1;
	}

	if (MonsterClass == 0)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	if (MonsterCount > 20)
	{
		GCServerMsgStringSend("Result-Too Manay Count", lpObj->m_Index, 1);
		return;
	}

	BYTE MapAttr = MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y);

	if ((MapAttr & 1) == 1)
	{
		GCServerMsgStringSend("Result-Is Safetyzone", lpObj->m_Index, 1);
		return;
	}

	LPMONSTER_ATTRIBUTE lpMonsterAttr = NULL;//loc68

	lpMonsterAttr = gMAttr.GetAttr(MonsterClass);

	if (lpMonsterAttr == NULL)
	{
		GCServerMsgStringSend("Result-Monster Not Found", lpObj->m_Index, 1);
		return;
	}

	//if(this->GetType(lpMonsterAttr->m_Index) != OBJ_MONSTER)
	//{
	//	GCServerMsgStringSend("Result-Monster Not Found", lpObj->m_Index, 1);
	//	return;	
	//}

	for (int i = 0; i < MonsterCount; i++)
	{
		BYTE X = lpObj->X;
		BYTE Y = lpObj->Y;

		int iMonsterIndex = gObjAddMonster(lpObj->MapNumber);

		if (iMonsterIndex >= 0)
		{
			gObj[iMonsterIndex].m_btSummonedbyGM = 1;//i think its m_btSummonedbyGM
			gObj[iMonsterIndex].m_PosNum = -1;
			gObj[iMonsterIndex].X = X;
			gObj[iMonsterIndex].Y = Y;
			gObj[iMonsterIndex].MapNumber = lpObj->MapNumber;
			gObj[iMonsterIndex].TX = gObj[iMonsterIndex].X;
			gObj[iMonsterIndex].TY = gObj[iMonsterIndex].Y;
			gObj[iMonsterIndex].m_OldX = gObj[iMonsterIndex].X;
			gObj[iMonsterIndex].m_OldY = gObj[iMonsterIndex].Y;
			gObj[iMonsterIndex].StartX = gObj[iMonsterIndex].X;
			gObj[iMonsterIndex].StartY = gObj[iMonsterIndex].Y;
			gObj[iMonsterIndex].Level = lpMonsterAttr->m_Level;
			gObj[iMonsterIndex].m_Attribute = 60;
			gObj[iMonsterIndex].MaxRegenTime = 0;
			gObj[iMonsterIndex].Dir = rand() % 8;
			gObjSetMonster(iMonsterIndex, MonsterClass, true);
		}
	}

	wsprintf(szText, "Result-SummonMonster(%s:%d)", lpMonsterAttr->m_Name, MonsterCount);
	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdClearMonster(LPOBJ lpObj, int Dis)
{
	char szText[256];

	memset(szText, 0, sizeof(szText));

	if (Dis <= 0)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	int MapNumber = lpObj->MapNumber;//loc66
	int DeletedMonCount = 0;

	for (int i = 0; i < OBJ_MAXMONSTER; i++)
	{
		LPOBJ lpMonObj = &gObj[i];//loc69

		if (lpMonObj->MapNumber == MapNumber &&
			gObj[i].Connected == PLAYER_PLAYING &&
			gObj[i].Type == OBJ_MONSTER &&
			lpMonObj->Live != 0 &&
			lpMonObj->m_State == 2)
		{
			if (gObjCalDistance(lpObj, lpMonObj) <= Dis)
			{
				if (lpMonObj->m_btSummonedbyGM == 1)
				{
					gObjDel(lpMonObj->m_Index);
				}
				else
				{
					lpMonObj->Live = 0;
					lpMonObj->m_State = 4;
					lpMonObj->RegenTime = GetTickCount();
					lpMonObj->DieRegen = 1;
					lpMonObj->PathCount = 0;
					GCDiePlayerSend(lpMonObj, lpMonObj->m_Index, 0, lpObj->m_Index);
				}

				DeletedMonCount++;
			}
		}
	}

	wsprintf(szText, "Result-ClearMonster(%d)", DeletedMonCount);
	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdClearItem(LPOBJ lpObj, int Dis)
{
	char szText[256];

	memset(szText, 0, sizeof(szText));

	if (Dis <= 0)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	int MapNumber = lpObj->MapNumber;//loc66
	MapClass * lpMap = &MapC[MapNumber];//loc67

	int ItemCount = lpMap->GetVisibleItemCount(lpObj, Dis);

	wsprintf(szText, "Result-ClearItem(%d)", ItemCount);
	GCServerMsgStringSend(szText, lpObj->m_Index, 1);

}

void CGMMng::CmdClearInven(LPOBJ lpObj)
{
	char szText[256];
	memset(szText, 0, sizeof(szText));

	int ItemCount = 0;

	for (int i = INVETORY_WEAR_SIZE; i < MAIN_INVENTORY_SIZE; i++)
	{
		if (lpObj->pInventory[i].IsItem() == 1)
		{
			gObjInventoryDeleteItem(lpObj->m_Index, i);
			ItemCount++;
		}
	}

	GCItemListSend(lpObj->m_Index);

	wsprintf(szText, "Result-ClearInven(%d)", ItemCount);

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdSummonChar(LPOBJ lpObj, char * szName)
{
	LPOBJ lpTargetObj = 0;
	int tIndex = -1;

	char szText[256];
	memset(szText, 0, sizeof(szText));

	if (szName == NULL)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	tIndex = gObjGetIndex(szName);

	if (tIndex <= 0)
	{
		GCServerMsgStringSend("Result-User Not Found", lpObj->m_Index, 1);
		return;
	}

	if (gObj[tIndex].Connected != PLAYER_PLAYING)
	{
		GCServerMsgStringSend("Result-Disconnect User", lpObj->m_Index, 1);
		return;
	}

	int MapNum = lpObj->MapNumber;//loc68
	int X = lpObj->X + 1;//loc69
	int Y = lpObj->Y + 1;//loc70

	BYTE MapAttr = MapC[MapNum].GetAttr(X, Y);

	if ((MapAttr & 4) == 4 || (MapAttr & 8) == 8)
	{
		GCServerMsgStringSend("Result-Invalid Area", lpObj->m_Index, 1);
		return;
	}

	wsprintf(szText, "Result-SummonCharacter(%s)", szName);

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);

	gObjTeleport(tIndex, MapNum, X, Y);

}

int CGMMng::GetType(WORD wClass)
{
	WORD Type = 0xFF;

	for (int i = 0; i < OBJ_MAXMONSTER; i++)
	{
		LPOBJ lpMonsterObj = &gObj[i];

		if (lpMonsterObj == NULL)
		{
			continue;
		}

		if (lpMonsterObj->Class == wClass)
		{
			Type = lpMonsterObj->Type;
			break;
		}
	}

	return Type;
}
#if(CUSTOM_MULTIWAREHOUSE)
void CGMMng::CmdWare(LPOBJ lpObj, int number)
{
	TNotice pNotice(1);

	if (!gObjIsConnected(lpObj->m_Index))
	{
		return;
	}

	if (g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		if (number == 2)
		{
			if (lpObj->PremiumTimeType < 1)
			{
				GCServerMsgStringSend("You need minimum premium level 1", lpObj->m_Index, 1);
				return;
			}
		}
		else if (number == 3)
		{
			if (lpObj->PremiumTimeType < 2)
			{
				GCServerMsgStringSend("You need minimum premium level 1", lpObj->m_Index, 1);
				return;
			}
		}
		else if (number == 4)
		{
			if (lpObj->PremiumTimeType < 3)
			{
				GCServerMsgStringSend("You need minimum premium level 1", lpObj->m_Index, 1);
				return;
			}
		}
	}

	/*if (!lpObj->bTemporaryUser)
	{
		GCServerMsgStringSend("You can't make ware, if you try exit the game", lpObj->m_Index, 1);
		return;
	}*/

	/*if (lpObj->MapNumber != 2)
	{
		GCServerMsgStringSend("You can do ware only in Capital Devias town", lpObj->m_Index, 1);
		return;
	}*/

	/*if (lpObj->m_PK_Level > 3)
	{
		GCServerMsgStringSend("PK Clear before make ware", lpObj->m_Index, 1);
		return;
	}*/

	BYTE attr = MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y);

	if ((attr & 1) == 0) //non safezone
	{
		GCServerMsgStringSend("You can do ware only in Capital Devias town safe zone!", lpObj->m_Index, 1);
		return;
	}

	if ((GetTickCount() - lpObj->MySelfDefenseTime) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), lpObj->m_Index, 1);
		GCCloseMsgSend(lpObj->m_Index, -1); //Season 2.5 add-on
		return;
	}

	/*if (lpObj->PartyNumber >= 0)
	{
		GCServerMsgStringSend("You cant do ware in party", lpObj->m_Index, 1);
		return;
	}

	if (lpObj->MapNumber != 2 && (lpObj->X >= 164 && lpObj->X <= 246)
		&& (lpObj->Y >= 2 && lpObj->Y <= 83))
	{
		GCServerMsgStringSend("You can do ware only in Capital Devias town", lpObj->m_Index, 1);
		return;
	}*/

	//lpObj->m_IfState.type = -1;
//	lpObj->m_IfState.state = -1;
//	lpObj->m_IfState.use = 0;

	//GDSetWarehouseList(lpObj->m_Index);

	//CGWarehouseUseEnd(lpObj->m_Index);

	// -----> CHECK

	if (lpObj->CloseCount >= 0)
	{
		pNotice.SendToUser(lpObj->m_Index, "[0] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.state == 1)
	{
		pNotice.SendToUser(lpObj->m_Index, "[1] Close NPC or Warehouse befor change number");
		return;
	}



	if (lpObj->m_IfState.use > 0)
	{
		pNotice.SendToUser(lpObj->m_Index, "[2] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.use == 1)
	{
		pNotice.SendToUser(lpObj->m_Index, "[3] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_ReqWarehouseOpen != false)
	{
		pNotice.SendToUser(lpObj->m_Index, "[4] Close Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.use == 1 && lpObj->m_IfState.type == 6)
	{
		//CGWarehouseUseEnd(lpObj->m_Index);
		pNotice.SendToUser(lpObj->m_Index, "[5] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.use && lpObj->m_IfState.type == 6)
	{
		//lpObj->m_IfState.use = 0;
		//lpObj->m_IfState.state = 0;
		//lpObj->WarehouseSave = FALSE;
		pNotice.SendToUser(lpObj->m_Index, "[6] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.type != 6)
	{
		pNotice.SendToUser(lpObj->m_Index, "[7] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.type == 6 && lpObj->m_IfState.state == 1)
	{
		pNotice.SendToUser(lpObj->m_Index, "[8] Close NPC or Warehouse befor change number");
		return;
	}



	/*
	if ( lpObj->m_IfState.type == 6 )
	{
		lpObj->m_IfState.state = 1;
		lpObj->WarehouseSave = TRUE;
	}*/

	/*if (lpObj->m_IfState.use > 1)
	{
		pNotice.SendToUser(lpObj->m_Index, "[8] Close NPC or Warehouse befor change number");
		return;
	}*/

	int WarehouseNumber = 0;
	if (number < 0 || number > 4)
	{
		pNotice.SendToUser(lpObj->m_Index, "Ware number: %d | Min: 0| Max: 4", number, WarehouseNumber);
		return;
	}

	//CGWarehouseUseEnd(lpObj->m_Index);//

	lpObj->WarehouseNumber = number;
	if (lpObj->WarehouseNumber >= 4)
	{
		lpObj->WarehouseNumber = 4;
	}
	if (lpObj->WarehouseNumber <= 0)
	{
		lpObj->WarehouseNumber = 0;
	}
	pNotice.SendToUser(lpObj->m_Index, "Ware number: %d", number);
	//lpObj->Money -= 1000000 + (25000 * lpObj->Reset) + (450000 * lpObj->GrandReset) + (1000000 * lpObj->GR);
	//GCMoneySend(lpObj->m_Index, lpObj->Money);
	//int iChaosTaxMoney = 1000000 + (25000 * lpObj->Reset) + (450000 * lpObj->GrandReset) + (1000000 * lpObj->GR) * g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100;
	//if (iChaosTaxMoney < 0)
	//{
	//	iChaosTaxMoney = 0;
	//}
	//g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);

	//GDGetWarehouseList(lpObj->m_Index, lpObj->AccountID, lpObj->WarehouseNumber);//
}
#endif