#include "stdafx.h"
#include "zMultiServer.h"
#include "ExDataServer.h"
#include "Window.h"
#include "winutil.h"
#include "Server.h"

EXDS_INFO g_ExDSInfo;
CQuery g_ExDataServerDB;

MAP_GUILD_INFO_STRUCT g_mapGuildManager;
MAP_UNION_DATA g_mapUnionManager;

void ExDataServerInit()
{
	g_bIsServer[ST_EXDATASERVER] = TRUE;

	g_ExDSInfo.TCPPort = GetPrivateProfileInt(EXDS_INISECTION,"TCPPort",55906,INI_FILE);
	GetPrivateProfileString(EXDS_INISECTION,"DSN","MuOnline",g_ExDSInfo.dbDSN,sizeof(g_ExDSInfo.dbDSN),INI_FILE);

	g_ExDataServerDB.S_TYPE = ST_EXDATASERVER;

	if(g_ExDataServerDB.Connect(3,g_ExDSInfo.dbDSN,SQLUser,SQLPass) == TRUE)
	{
		g_Window.LogAdd(Log::Info, "[ %s ] connection successful !",g_ExDSInfo.dbDSN);
	}

	if(CreateGIocp(g_ExDSInfo.TCPPort,ST_EXDATASERVER) != TRUE)
	{
		g_Window.LogAdd(Log::Error, "Failed to start [ ST_EXDATASERVER ] on port [ %d ]",g_ExDSInfo.TCPPort);
	}
	else
	{
		g_Window.LogAdd(Log::Info, "[ ExDataServer ] created on port [ %d ]",g_ExDSInfo.TCPPort);
	}

	g_mapGuildManager.clear();
	InitGuild("SELECT * FROM Guild WHERE Number = G_Union");
	InitGuild("SELECT * FROM Guild WHERE Number <> G_Union");
}

void EDSProtocolCore(int aIndex, DWORD headcode, LPBYTE aRecv, int Len)
{
	switch(headcode)
	{
		case 0x00:
			ExDataServerLogin(aIndex, (SDHP_SERVERINFO*)aRecv);
			break;
		case 0x02:
			GDCharCloseRecv((SDHP_USERCLOSE*)aRecv);
			break;
		case 0x30:
			GDGuildCreateSend(aIndex, (SDHP_GUILDCREATE *)aRecv);
			break;
		case 0x31:
			GDGuildDestroyRecv(aIndex, (SDHP_GUILDDESTROY *) aRecv);
			break;
		case 0x32:
			GDGuildMemberAdd(aIndex, (SDHP_GUILDMEMBERADD *) aRecv);
			break;
		case 0x33:
			GDGuildMemberDel(aIndex, (SDHP_GUILDMEMBERDEL *) aRecv);
			break;
		case 0x35:
			DGGuildMemberInfoRequest(aIndex, (SDHP_GUILDMEMBER_INFO_REQUEST *) aRecv);
			break;
		case 0x37:
			DGGuildScoreUpdate(aIndex, (SDHP_GUILDSCOREUPDATE *) aRecv);
			break;
		case 0x38:
			GDGuildNoticeSave(aIndex, (SDHP_GUILDNOTICE *) aRecv);
			break;
		case 0x50:
			GDGuildServerGroupChattingSend(aIndex,(EXSDHP_SERVERGROUP_GUILD_CHATTING_RECV *) aRecv);
			break;
		case 0x51:
			GDUnionServerGroupChattingSend(aIndex, (EXSDHP_SERVERGROUP_UNION_CHATTING_RECV *) aRecv);
			break;
		case 0xE1:
			GDGuildReqAssignStatus(aIndex, (EXSDHP_GUILD_ASSIGN_STATUS_REQ *) aRecv);
			break;
		case 0xE2:
			GDGuildReqAssignType(aIndex, (EXSDHP_GUILD_ASSIGN_TYPE_REQ *) aRecv);
			break;
		case 0xE5:
			DGRelationShipAnsJoin(aIndex, (EXSDHP_RELATIONSHIP_JOIN_REQ *)aRecv);
			break;
		case 0xE6:
			DGRelationShipAnsBreakOff(aIndex, (EXSDHP_RELATIONSHIP_BREAKOFF_REQ *)aRecv);
			break;
		case 0xE9:
			DGUnionListRecv(aIndex, (EXSDHP_UNION_LIST_REQ *)aRecv);
			break;
		case 0xEB:
		{
			PBMSG_HEAD2 * lpDef = (PBMSG_HEAD2 *)aRecv;
			switch (lpDef->subcode)
			{
				case 0x01:
					DGRelationShipAnsKickOutUnionMember(aIndex, (EXSDHP_KICKOUT_UNIONMEMBER_REQ *)aRecv);
					break;
			}
		}
		break;
	}
}

void ExDataServerLogin(int aIndex, SDHP_SERVERINFO * lpMsg)
{
	SDHP_RESULT pResult = {0};

	PHeadSetB((LPBYTE)&pResult, 0x00, sizeof(pResult));
	pResult.Result = 1;
	gSObj[aIndex].ServerCode = lpMsg->ServerCode;

	if(lpMsg->Type == 1)	// Case GameServer
	{
#if(ENABLE_MYFIXCODE)
		if(gSObjSetInfo(aIndex, lpMsg->Port, lpMsg->Type, lpMsg->ServerName) == FALSE)
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB] GameServer Not Connected");
			pResult.Result = 0;		
		}
		else
		{
			std::map<std::string, tagGUILD_INFO_STRUCT, strCmp>::iterator it, end;
			it = g_mapGuildManager.begin();
			end = g_mapGuildManager.end();
			for (; it != end; it++)
				it->second.m_bGSHasData = 0;

			g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB] GameServer with ServerCode[%d] connected.", lpMsg->ServerCode);
		}
#else
		if( gSObjSetInfo(aIndex, lpMsg->Port, lpMsg->Type, lpMsg->ServerName) == FALSE )
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[MuOnlineDB] GameServer Not Connected");
			pResult.Result = 0;		
		}

		g_mapGuildManager.clear();
		InitGuild("SELECT * FROM Guild WHERE Number = G_Union");
		InitGuild("SELECT * FROM Guild WHERE Number <> G_Union");
#endif
	}
	else if ( lpMsg->Type == 2 )	// Case ChatServer
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ChatServer] Chat Server Connected");
	}

	DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
}

void GDCharCloseRecv(SDHP_USERCLOSE* aRecv)
{
	if( aRecv->Type != 1 )
	{
		char szGuild[11] = {0};
        char szName[11] = {0};
        strncpy(szGuild, aRecv->GuildName, 8);
        strncpy(szName, aRecv->CharName, 10);

		LPGUILD_MEMBER lpMemb;
		lpMemb = GetGuildMember(aRecv->GuildName, aRecv->CharName);
		if(lpMemb)
		{
			lpMemb->m_btConnected = -1;
		}

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][ExDB] member close: [%s]", aRecv->CharName);

		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER && gSObj[i].ServerCode != (WORD)-1)
			{
				DataSend(i, (LPBYTE)aRecv, aRecv->h.size);
			}
		}
	}

	//AddReqToFriendQueue(aIndex, (LPBYTE)aRecv);
}

void GDGuildCreateSend(int aIndex,  SDHP_GUILDCREATE * aRecv)
{
	SDHP_GUILDCREATE_RESULT Result;

	PHeadSetB((LPBYTE)&Result, 0x30, sizeof(Result));

	memcpy(Result.Master, aRecv->Master, sizeof(Result.Master));
	memcpy(Result.GuildName, aRecv->GuildName, sizeof(Result.GuildName));
	memcpy(Result.Mark, aRecv->Mark, sizeof(Result.Mark));
	Result.NumberL = aRecv->NumberL;
	Result.NumberH = aRecv->NumberH;

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] Guild [%s], GuildMaster [%s].", Result.GuildName, Result.Master);

	Result.Result = 0;
	Result.Flag = 1;

	if(strlen(aRecv->GuildName) < 4)
	{
		Result.Result = 2;
		Result.Flag = 1;
		g_Window.ServerLogAdd(ST_EXDATASERVER, "GuildName is too short [%s]", aRecv->GuildName);

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] Send Result [%d].", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, sizeof(Result));
		return;
	}

	if(strlen(aRecv->Master) < 3)
	{
		Result.Result = 2;
		Result.Flag = 1;
		g_Window.ServerLogAdd(ST_EXDATASERVER, "GuildMaster Name is too short [%s]", aRecv->Master);

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] Send Result [%d].", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, sizeof(Result));
		return;
	}

	if(!SpaceSyntexCheck(aRecv->GuildName))
	{
		Result.Result = 4;
		Result.Flag = 1;

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] Send Result [%d].", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}
	else if(!QuoteSpaceSyntexCheck(aRecv->GuildName))
	{
		Result.Result = 5;
		Result.Flag = 1;

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] Send Result [%d].", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}
	else
	{
		int res = CreateDBGuild(aRecv->GuildName, aRecv->Master, aRecv->Mark);
		
		switch(res)
		{
			case 1:
				Result.Result = 0;
			break;
			
			case 2:
				Result.Result = 3;
			break;

			case 3:
				Result.Result = -1;
			break;
		}

		if(res == 0)
		{
			Result.GuildNumber = GetDBGuildNumber(aRecv->GuildName);
			if(Result.GuildNumber != -1)
			{
				AddGuild(aRecv->GuildName, aRecv->Master, Result.GuildNumber, NULL, 0, aRecv->Mark, aRecv->btGuildType);
				if(UpdateGuildMemberStatus(aRecv->GuildName, aRecv->Master, 128))
				{
					if(UpdateGuildType(aRecv->GuildName, aRecv->btGuildType))
					{			
						Result.Result = 1;

						for(int i = 0; i < MAX_SERVEROBJECT; i++)
						{
							if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
							{
								if(i == aIndex)
									Result.Flag = 1;
								else
									Result.Flag = 0;
								g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] Send Result [%d] to Server [%d]", Result.Result, gSObj[i].ServerCode);			
								DataSend(i, (LPBYTE)&Result, Result.h.size);
							}
						}
						
						SendGuildMemberInfo(aIndex, aRecv->Master);
						g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] Create Guild [%s] Master [%s]", aRecv->GuildName, aRecv->Master);
						return;
					}
					else
					{
						g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] [ERROR] UpdateGuildType: Guild:%s, Type:%d", aRecv->GuildName, aRecv->btGuildType);
					}
				}
				else
				{
					g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] [ERROR] UpdateGuildMemberStatus: Guild:%s, Member:%s", aRecv->GuildName, aRecv->Master);
				}
			}
		}
		else
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][Guild Create Request] Send Result [%d].", Result.Result);
			DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
			return;
		}
	}
}

void GDGuildDestroyRecv(int aIndex,  SDHP_GUILDDESTROY * aRecv)
{
	SDHP_GUILDDESTROY_RESULT DelResult;
	ZeroMemory(&DelResult, sizeof(DelResult));
	PHeadSetB((LPBYTE)&DelResult, 0x31, sizeof(DelResult));

	strncpy(DelResult.GuildName, aRecv->GuildName, 8);
	strncpy(DelResult.Master, aRecv->Master, 10);
	DelResult.NumberH = aRecv->NumberH;
	DelResult.NumberL = aRecv->NumberL;

	DelResult.Flag = 1;
	DelResult.Result = 0;

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] GuildName [%s], GuildMaster [%s].", DelResult.GuildName, DelResult.Master);

	if(strlen(DelResult.Master) < 3)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L3 MasterName < 3: %s", DelResult.Master);
		DelResult.Result = 3;
	}

	if(strlen(DelResult.GuildName) < 2)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L3 GuildName < 2: %s", DelResult.GuildName);
		DelResult.Result = 3;
	}

	if(DelResult.Result == 3)
	{
		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] Send Result [%d] to Server [%d].", DelResult.Result, gSObj[i].ServerCode);
				DataSend(i, (LPBYTE)&DelResult, DelResult.h.size);
			}
		}
		return;
	}

	if(IsCSGuild(aRecv->GuildName))
	{
		DelResult.Result = 3;

		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] Send Result [%d] to Server [%d].", DelResult.Result, gSObj[i].ServerCode);
				DataSend(i, (LPBYTE)&DelResult, DelResult.h.size);
			}
		}
		return;
	}

	DelResult.Result = 2;


	LPGUILD_INFO_STRUCT lpGuild;
	lpGuild = GetGuild(DelResult.GuildName);
	if(lpGuild)
	{
		if(lpGuild->m_iUnionGuild != 0)
		{		
			if(lpGuild->m_iUnionGuild != lpGuild->m_iNumber)
			{
				if(UnionBreak(GetGuild(lpGuild->m_iUnionGuild), lpGuild) == 0)
					DelResult.Result = 3;
			}
			else
				DelResult.Result = 3;
		}


		if(lpGuild->m_iRivalGuild != 0)
		{
			if(RivalBreak(lpGuild, GetGuild(lpGuild->m_iRivalGuild)) == 0)
				DelResult.Result = 3;
		}

	}
	else
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] Guild [%s] not found.", DelResult.Result);


	if(DelResult.Result == 3)
	{
		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				if(i == aIndex)
					DelResult.Flag = 1;
				else
					DelResult.Flag = 0;
				g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] Send Result [%d] to Server [%d].", DelResult.Result, gSObj[i].ServerCode);
				DataSend(i, (LPBYTE)&DelResult, DelResult.h.size);
			}
		}

		return;
	}

	if(MasterDBExists(DelResult.Master))
	{
		if(DelAllDBGuildMember(DelResult.GuildName))
		{
			if(DelDBGuild(DelResult.GuildName))
			{
				DelGuild(DelResult.GuildName);
				DelResult.Result = 4;
			}
			else
			{
				g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] [DelAllDBGuildMember] Failed to delete All GuildMember in DB : %s", DelResult.GuildName);
			}
		}
		else
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] [DelDBGuild] Failed to delete Guild in DB : %s", DelResult.GuildName);
		}
	}
	else
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] GuildMaster [%s] not found in g_ExDataServerDB.", DelResult.Result);


	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
		{
			if(i == aIndex)
				DelResult.Flag = 1;
			else
				DelResult.Flag = 0;
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Destroy Request] Send Result [%d] to Server [%d].", DelResult.Result, gSObj[i].ServerCode);
			DataSend(i, (LPBYTE)&DelResult, DelResult.h.size);
		}
	}
}

void GDGuildMemberAdd(int aIndex,  SDHP_GUILDMEMBERADD * aRecv)
{
	SDHP_GUILDMEMBERADD_RESULT Result;
	ZeroMemory(&Result, sizeof(Result));

	PHeadSetB((LPBYTE)&Result, 0x32, sizeof(Result));

	Result.NumberH = aRecv->NumberH;
	Result.NumberL = aRecv->NumberL;
	strncpy(Result.GuildName, aRecv->GuildName, 8);
	strncpy(Result.MemberID, aRecv->MemberID, 10);

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Join Request] GuildName [%s], Member [%s].", Result.GuildName, Result.MemberID);

	Result.pServer = gSObj[aIndex].ServerCode;
	Result.Flag = 1;

	if(strlen(Result.GuildName) < 4)
	{
		Result.Result = 0;
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L2: %s Guild Name is short", Result.GuildName);

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Join Request] Send Result [%d].", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}

	if(strlen(Result.MemberID) < 4)
	{
		Result.Result = 0;
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L2: %s Member Name is short", Result.MemberID);

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Join Request] Send Result [%d].", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}

	if(DBGuildMemberExists(Result.MemberID))
	{
		Result.Result = 4;
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Join Request] [DBGuildMemberExists] Member [%s] is already in guild", Result.MemberID);

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Join Request] Send Result [%d].", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}

	if(AddDBGuildMember(Result.GuildName, Result.MemberID) == FALSE)
	{
		Result.Result = 4;
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Join Request] [AddDBGuildMember] failed to add [%s] in guild [%s]", Result.MemberID, Result.GuildName);

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Join Request] Send Result [%d].", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}
	else
		Result.Result = 1;

	if(AddGuildMember(Result.GuildName, Result.MemberID, 0, gSObj[aIndex].ServerCode) == FALSE)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L3: Failed to add member [%s] to guild [%s]", Result.MemberID, Result.GuildName);
	}

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
		{
			if(i == aIndex)
				Result.Flag = 1;
			else
				Result.Flag = 0;

			g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Join Request] Send Result [%d] to Server [%d]", Result.Result, gSObj[i].ServerCode);

			DataSend(i, (LPBYTE)&Result, Result.h.size);
		}
	}
}

void GDGuildMemberDel(int aIndex,  SDHP_GUILDMEMBERDEL * aRecv)
{
	SDHP_GUILDMEMBERDEL_RESULT Result;
	ZeroMemory(&Result, sizeof(Result));

	PHeadSetB((LPBYTE)&Result, 0x33, sizeof(Result));

	Result.NumberH = aRecv->NumberH;
	Result.NumberL = aRecv->NumberL;
	strncpy(Result.GuildName, aRecv->GuildName, 8);
	strncpy(Result.MemberID, aRecv->MemberID, 10);

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Member Withdraw Request] GuildName [%s], Member [%s].", Result.GuildName, Result.MemberID);

	Result.Flag = 1;
	Result.Result = 3;

	if(strlen(Result.GuildName) < 4)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L2: %s Guild Name is short", Result.GuildName);
		
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Member Withdraw Request] Send Result [%d]", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}

	if(strlen(Result.MemberID) < 4)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L2: %s Member Name is short", Result.MemberID);

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Member Withdraw Request] Send Result [%d]", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}

	if(DelDBGuildMember(Result.MemberID) == FALSE)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Member Withdraw Request] [DelDBGuildMember] Failed delete member [%s] from guild [%s]", Result.MemberID, Result.GuildName);

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Member Withdraw Request] Send Result [%d]", Result.Result);
		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
		return;
	}

	if(DelGuildMember(Result.GuildName, Result.MemberID) == FALSE)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Member Withdraw Request] [DelGuildMember] Guild[%s] Member[%s] delete fail.", Result.GuildName, Result.MemberID);
	}
	else
		Result.Result = 1;


	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
		{
			if(i == aIndex)
				Result.Flag = 1;
			else
				Result.Flag = 0;
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Member Withdraw Request] Send Result [%d] to Server[%d]", Result.Result, gSObj[i].ServerCode);
			DataSend(i, (LPBYTE)&Result, Result.h.size);
		}
	}
}

void DGGuildMemberInfoRequest(int aIndex,  SDHP_GUILDMEMBER_INFO_REQUEST * aRecv)
{
	char szName[11] = {0};
	strncpy(szName, aRecv->MemberID, 10);

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Member Info Request] Member [%s].",szName);

	SendGuildMemberInfo(aIndex, szName);
}

void DGGuildScoreUpdate(int aIndex,  SDHP_GUILDSCOREUPDATE * aRecv)
{

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Score Update Request] GuildName [%s], Score [%d]", aRecv->GuildName, aRecv->Score);

	if(strlen(aRecv->GuildName) < 4)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L2: %s guild name is short", aRecv->GuildName);
		return;
	}

	if(UpdateScore(aRecv->GuildName, aRecv->Score))
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Score Update Request] Score updated.");

		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				DataSend(i, (LPBYTE)aRecv, aRecv->h.size);
			}
		}
	}
	else
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Score Update Request] Failed to update guild score.");
}

void GDGuildNoticeSave(int aIndex,  SDHP_GUILDNOTICE * aRecv)
{
	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Notice Save Request] GuildName [%s].", aRecv->GuildName);
	if(strlen(aRecv->GuildName) < 4)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L2: %s guild name is short", aRecv->GuildName);
		return;
	}

	if(SaveNotice(aRecv->GuildName, aRecv->szGuildNotice))
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Notice Save Request] Notice Saved.");

		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				DataSend(i, (LPBYTE)aRecv, aRecv->h.size);
			}
		}
	}
	else
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Notice Save Request] Failed to save.");
	}

}

void GDGuildServerGroupChattingSend(int aIndex,  EXSDHP_SERVERGROUP_GUILD_CHATTING_RECV * aRecv)
{
	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
		{
			if(i != aIndex)
			{
				DataSend(i, (LPBYTE)aRecv, aRecv->h.size);
			}
		}
	}
}

void GDUnionServerGroupChattingSend(int aIndex, EXSDHP_SERVERGROUP_UNION_CHATTING_RECV * aRecv)
{
	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
		{
			if(i != aIndex)
			{
				DataSend(i, (LPBYTE)aRecv, aRecv->h.size);
			}
		}
	}
}

void GDGuildReqAssignStatus(int aIndex,  EXSDHP_GUILD_ASSIGN_STATUS_REQ * aRecv)
{
	EXSDHP_GUILD_ASSIGN_STATUS_RESULT Result;
	ZeroMemory(&Result, sizeof(Result));
	PHeadSetB((LPBYTE)&Result, 0xE1, sizeof(Result));

	Result.btGuildStatus = aRecv->btGuildStatus;
	Result.btType = aRecv->btType;
	strncpy(Result.szGuildName, aRecv->szGuildName, 8);
	strncpy(Result.szTargetName, aRecv->szTargetName, 10);
	Result.wUserIndex = aRecv->wUserIndex;

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[GuildMember Assign Status Request] GuildName [%s], Member [%s], Status [%d].",
		Result.szGuildName, Result.szTargetName, Result.btGuildStatus);

	Result.btFlag = 1;
	Result.btResult = 0;

	if(UpdateGuildMemberStatus(aRecv->szGuildName, aRecv->szTargetName, aRecv->btGuildStatus))
	{
		Result.btResult = 1;
	}

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[GuildMember Assign Status Request] Send Result [%d].", Result.btResult);
	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	if(Result.btResult)
	{
		Result.btFlag = 0;
		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				if(i != aIndex)
				{
					g_Window.ServerLogAdd(ST_EXDATASERVER, "[GuildMember Assign Status Request] Send Result [%d] to Server [%d].", Result.btResult, gSObj[i].ServerCode);
					DataSend(i, (LPBYTE)&Result, Result.h.size);
				}
			}
		}	
	}
}

void GDGuildReqAssignType(int aIndex,  EXSDHP_GUILD_ASSIGN_TYPE_REQ * aRecv)
{
	EXSDHP_GUILD_ASSIGN_TYPE_RESULT Result;
	ZeroMemory(&Result, sizeof(Result));
	PHeadSetB((LPBYTE)&Result, 0xE2, sizeof(Result));

	Result.btGuildType = aRecv->btGuildType;
	strncpy(Result.szGuildName, aRecv->szGuildName, 8);
	Result.wUserIndex = aRecv->wUserIndex;

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Assign Type Request] GuildName [%s], Type [%d].", Result.szGuildName, Result.btGuildType);

	Result.btFlag = 1;
	Result.btResult = 0;

	if(UpdateGuildType(aRecv->szGuildName, aRecv->btGuildType))
	{
		Result.btResult = 1;
	}

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Assign Type Request] Send Result [%d].", Result.btResult);
	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	if(Result.btResult)
	{
		Result.btFlag = 0;
		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				if(i != aIndex)
				{
					g_Window.ServerLogAdd(ST_EXDATASERVER, "[Guild Assign Type Request] Send Result [%d] to Server [%d].", Result.btResult, gSObj[i].ServerCode);
					DataSend(i, (LPBYTE)&Result, Result.h.size);
				}
			}
		}	
	}

}

void DGRelationShipAnsJoin(int aIndex,  EXSDHP_RELATIONSHIP_JOIN_REQ * aRecv)
{
	EXSDHP_RELATIONSHIP_JOIN_RESULT Result;

	PHeadSetB((LPBYTE)&Result, 0xE5, sizeof(Result));

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Join Request] RelationShipType [%d], RequestGuild [%d], TargetGuild [%d].",
		aRecv->btRelationShipType, aRecv->iRequestGuildNum, aRecv->iTargetGuildNum);

	Result.btRelationShipType = aRecv->btRelationShipType;
	Result.iRequestGuildNum = aRecv->iRequestGuildNum;
	Result.iTargetGuildNum = aRecv->iTargetGuildNum;
	Result.wRequestUserIndex = aRecv->wRequestUserIndex;
	Result.wTargetUserIndex = aRecv->wTargetUserIndex;
	Result.btFlag = 1;
	LPGUILD_INFO_STRUCT lpRG, lpTG;

	lpRG = GetGuild(aRecv->iRequestGuildNum);
	lpTG = GetGuild(aRecv->iTargetGuildNum);

	if(lpRG && lpTG)
	{
		strncpy(Result.szRequestGuildName, lpRG->m_szGuildName, 10);
		strncpy(Result.szTargetGuildName, lpTG->m_szGuildName, 10);
		Result.btResult = RelationShipOperation(aRecv->iRequestGuildNum, aRecv->iTargetGuildNum, aRecv->btRelationShipType, 0);
	}
	else
	{
		if(lpRG == NULL)
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Join Request] RequestGuild with number [%d] not found.", aRecv->iRequestGuildNum);

		if(lpTG == NULL)
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Join Request] TargetGuild with number [%d] not found.", aRecv->iTargetGuildNum);

	}

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Join Request] Send Result [%d]", Result.btResult);
	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	if(Result.btResult != 0 && Result.btResult != 0x10)
	{
		Result.btFlag = 0;
		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				if(i != aIndex)
				{
					g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Join Request] Send Result [%d] to Server [%d]", Result.btResult, gSObj[i].ServerCode);
					DataSend(i, (LPBYTE)&Result, Result.h.size);
				}
			}
		}
	}
}

void DGRelationShipAnsBreakOff(int aIndex,  EXSDHP_RELATIONSHIP_BREAKOFF_REQ * aRecv)
{
	EXSDHP_RELATIONSHIP_BREAKOFF_RESULT Result;
	ZeroMemory(&Result, sizeof(Result));

	PHeadSetB((LPBYTE)&Result, 0xE6, sizeof(Result));

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Break Request] RelationShipType [%d], RequestGuild [%d], TargetGuild [%d].", aRecv->btRelationShipType, aRecv->iRequestGuildNum, aRecv->iTargetGuildNum);

	Result.btRelationShipType = aRecv->btRelationShipType;
	Result.iRequestGuildNum = aRecv->iRequestGuildNum;
	Result.iTargetGuildNum = aRecv->iTargetGuildNum;
	Result.wRequestUserIndex = aRecv->wRequestUserIndex;
	Result.wTargetUserIndex = aRecv->wTargetUserIndex;
	Result.btFlag = 1;

	LPGUILD_INFO_STRUCT lpRG, lpTG;

	lpRG = GetGuild(aRecv->iRequestGuildNum);
	lpTG = GetGuild(aRecv->iTargetGuildNum);

	if(lpRG && lpTG)
	{
		Result.btResult = RelationShipOperation(aRecv->iRequestGuildNum, aRecv->iTargetGuildNum, aRecv->btRelationShipType, 1);
	}
	else
	{
		if(lpRG == NULL)
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Break Request] RequestGuild with number [%d] not found.", aRecv->iRequestGuildNum);

		if(lpTG == NULL)
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Break Request] TargetGuild with number [%d] not found.", aRecv->iTargetGuildNum);

	}

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Break Request] Send Result [%d]", Result.btResult);
	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	if(Result.btResult != 0 && Result.btResult != 0x10)
	{
		Result.btFlag = 0;
		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				if(i != aIndex)
				{
					g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Break Request] Send Result [%d] to Server [%d]", Result.btResult, gSObj[i].ServerCode);
					DataSend(i, (LPBYTE)&Result, Result.h.size);
				}
			}
		}
	}
}

void DGUnionListRecv(int aIndex,  EXSDHP_UNION_LIST_REQ * aRecv)
{
	EXSDHP_UNION_LIST *lpList;
	EXSDHP_UNION_LIST_COUNT *lpListCnt;

	LPUNION_DATA lpUD = NULL;
	int cnt = 0, size, res = 0;


	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Union List Request] UnionMasterGuild Number: [%d]", aRecv->iUnionMasterGuildNumber);

	LPGUILD_INFO_STRUCT lpGuild, lpG;

	if(aRecv->iUnionMasterGuildNumber != 0)
	{
		lpGuild = GetGuild(aRecv->iUnionMasterGuildNumber);
		if(lpGuild)
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[Union List Request] UnionMasterGuild Name: [%s]", lpGuild->m_szGuildName);
		else
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[Union List Request] Guild with number [%d] not found.", aRecv->iUnionMasterGuildNumber);
		lpUD = GetUnionData(aRecv->iUnionMasterGuildNumber);
		cnt = lpUD->m_vecUnionMember.size();
	}
	
	size = sizeof(*lpListCnt)+sizeof(*lpList)*cnt;
	LPBYTE lpData = new BYTE[size];
	ZeroMemory(lpData, size);

	lpListCnt = (EXSDHP_UNION_LIST_COUNT *)lpData;
	lpList = (EXSDHP_UNION_LIST *)(lpData+sizeof(*lpListCnt));
	
	PHeadSetW((LPBYTE)lpListCnt, 0xE9, size);

	lpListCnt->iTimeStamp = GetTickCount();
	lpListCnt->wRequestUserIndex = aRecv->wRequestUserIndex;

	if(lpGuild && cnt != 0)
	{
		if(!lpUD)
		{
			LPUNION_DATA lpUD;
			if(lpGuild->m_iUnionGuild)
				lpUD = GetUnionData(lpGuild->m_iUnionGuild);
			else
				lpUD = GetUnionData(lpGuild->m_iNumber);
		}
		if(lpUD)
		{
			int s1 = lpUD->m_vecUnionMember.size();
			lpListCnt->btUnionMemberNum = s1;

			for(int j=0; j < s1; j++)
			{
				lpG = GetGuild(lpUD->m_vecUnionMember[j]);
				if(lpG == NULL)
					continue;

				if(lpG->m_iRivalGuild == 0)
					continue;


				lpG = GetGuild(lpG->m_iRivalGuild);
				if(lpG == NULL)
					continue;

				LPUNION_DATA lpUD2;
				if(lpG->m_iUnionGuild)
					lpUD2 = GetUnionData(lpG->m_iUnionGuild);
				else
					lpUD2 = GetUnionData(lpG->m_iNumber);

				if(lpUD2 == NULL)
					continue;

				lpListCnt->btRivalMemberNum += lpUD2->m_vecUnionMember.size();
			}
		}

		
		lpListCnt->btCount = cnt;
		for(int i=0; i < cnt; i++)
		{
			lpG = GetGuild(lpUD->m_vecUnionMember[i]);
			if(lpG)
			{
				lpList[i].btMemberNum = lpG->m_mapGuildMember.size();
				memcpy(lpList[i].Mark, lpG->m_Mark, 32);
				strncpy(lpList[i].szGuildName, lpG->m_szGuildName, 8);
				g_Window.ServerLogAdd(ST_EXDATASERVER, "[Union List Request] Send GuildName: [%s].", lpG->m_szGuildName);
			}
		}

		lpListCnt->btResult = 1;
	}

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Union List Request] Send UnionList with result: [%d]", lpListCnt->btResult);

	DataSend(aIndex, lpData, size);

	delete [] lpData;
}

void DGRelationShipAnsKickOutUnionMember(int aIndex,  EXSDHP_KICKOUT_UNIONMEMBER_REQ *aRecv)
{
	EXSDHP_KICKOUT_UNIONMEMBER_RESULT Result;
	ZeroMemory(&Result, sizeof(Result));

	PHeadSubSetB((LPBYTE)&Result, 0xEB, 1, sizeof(Result));
	Result.btRelationShipType = aRecv->btRelationShipType;
	Result.btResult = 0;
	strncpy(Result.szUnionMasterGuildName, aRecv->szUnionMasterGuildName, 8);
	strncpy(Result.szUnionMemberGuildName, aRecv->szUnionMemberGuildName, 8);
	Result.wRequestUserIndex = aRecv->wRequestUserIndex;
	Result.btResult = 0;
	Result.btFlag = 1;

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Kick Union Member Request] UnionMasterGuild [%s], UnionMemberGuild [%s]", Result.szUnionMasterGuildName, Result.szUnionMemberGuildName);

	LPGUILD_INFO_STRUCT lpMasterGuild, lpKickGuild;
	lpMasterGuild = GetGuild(Result.szUnionMasterGuildName);
	lpKickGuild = GetGuild(Result.szUnionMemberGuildName);
	
	if(lpMasterGuild && lpKickGuild)
	{
		Result.btResult = RelationShipOperation(lpKickGuild->m_iNumber, lpMasterGuild->m_iNumber, aRecv->btRelationShipType, 1);
	}
	else
	{
		if(lpMasterGuild == NULL)
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[Kick Union Member Request] error: UnionMasterGuild [%s] not found.", Result.szUnionMasterGuildName);

		if(lpKickGuild)
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[Kick Union Member Request] error: UnionMemberGuild [%s] not found.", Result.szUnionMemberGuildName);
	}

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Kick Union Member Request] Send Result [%d].", Result.btResult);
	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	if(Result.btResult != 0 && Result.btResult != 0x10)
	{
		Result.btFlag = 0;
		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				if(i != aIndex)
				{
					g_Window.ServerLogAdd(ST_EXDATASERVER, "[Kick Union Member Request] Send Result [%d] to Server [%d]", Result.btResult, gSObj[i].ServerCode);
					DataSend(i, (LPBYTE)&Result, Result.h.size);
				}
			}
		}
	}
}

//--------------------------
// ---- ExDataServerDB -----
//--------------------------

BOOL InitGuild(char * Query)
{
	CQuery TempGuild;
	CQuery TempMember;
	CQuery TempMark;

	TempGuild.Connect(3,g_ExDSInfo.dbDSN,SQLUser,SQLPass);
	TempMember.Connect(3,g_ExDSInfo.dbDSN,SQLUser,SQLPass);
	TempMark.Connect(3,g_ExDSInfo.dbDSN,SQLUser,SQLPass);

	if(TempGuild.ExecQuery(Query) == FALSE)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[MuOnlineDB] Guild Info is missing");
		TempGuild.Clear();
		return FALSE;
	}

	if(TempGuild.Fetch() != SQL_NO_DATA)
	{
		do
		{
			char szMsg[128];

			char szGuildName[11] = {0};
			char szMaster[11] = {0};
			int iNumber, iType, iScore;
			char szNotice[128] = {0};
			BYTE Mark[32] = {0};

			tagGUILD_INFO_STRUCT* lpGuildInfo = NULL;
			
			iNumber = TempGuild.GetInt("Number");
			TempGuild.GetStr("G_Name", szGuildName);
			TempGuild.GetStr("G_Master", szMaster);
			TempGuild.GetStr("G_Notice", szNotice);
			
			iScore = TempGuild.GetInt("G_Score");
			iType = TempGuild.GetInt("G_Type");

			wsprintf(szMsg,"SELECT G_Mark FROM Guild WHERE G_Name = '%s'",szGuildName);
			TempMark.ReadBlob(szMsg, Mark);

			if(AddGuild(szGuildName, szMaster, iNumber, szNotice, iScore, Mark, iType))
			{
				lpGuildInfo = GetGuild(szGuildName);
				lpGuildInfo->m_iRivalGuild = TempGuild.GetInt("G_Rival");
				lpGuildInfo->m_iUnionGuild = TempGuild.GetInt("G_Union");

				AddUnion(iNumber, lpGuildInfo->m_iUnionGuild);
			}
			else
			{
				g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB]Can't add guild [%s][%s]", szGuildName, szMaster);
			}

			TempMember.ExecQuery("SELECT * FROM GuildMember WHERE G_Name = '%s'",szGuildName);

			int iMember = 0;

			while(iMember < MAX_MEMBER_GUILD && TempMember.Fetch() != SQL_NO_DATA)
			{
				int iStatus;
				char szMembName[11] = {0};
				
				iStatus = TempMember.GetInt("G_Status");
				TempMember.GetStr("Name", szMembName);

				AddGuildMember(szGuildName, szMembName, iStatus);
				iMember++;
			}

			TempMark.Clear();
			TempMember.Clear();
		}
		while(TempGuild.Fetch() != SQL_NO_DATA);
	}

	TempGuild.Clear();

	return TRUE;
}

LPGUILD_INFO_STRUCT GetGuild(char *szGuild)
{
	MAP_GUILD_INFO_STRUCT::iterator it;
	it = g_mapGuildManager.find(szGuild);

	if(it == g_mapGuildManager.end())
		return NULL;

	return &it->second;
}

LPGUILD_MEMBER GetGuildMember(char *szGuild, char *szName)
{
	LPGUILD_INFO_STRUCT lpGuild;

	lpGuild = GetGuild(szGuild);
	if( lpGuild == FALSE )
		return NULL;

	MAP_GUILD_MEMBER::iterator it;
	it = lpGuild->m_mapGuildMember.find(szName);

	if(it == lpGuild->m_mapGuildMember.end())
		return NULL;

	return &it->second;
}

BOOL GuildExists(char *szGuild)
{
	if(GetGuild(szGuild) != NULL)
		return TRUE;
	else
		return FALSE;
}

int CreateDBGuild(char* szGuild, char* szMaster, LPBYTE pMark)
{
	if(GuildExists(szGuild))
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "Guild [%s] already exists.", szGuild);
		return 1;
	}

	g_ExDataServerDB.ExecQuery("SELECT Name FROM GuildMember where Name='%s'", szMaster);

	if(g_ExDataServerDB.Fetch() != SQL_NO_DATA)
	{
		g_ExDataServerDB.Clear();
		g_Window.ServerLogAdd(ST_EXDATASERVER, "%s is already in guild", szMaster);
		return 2;
	}
	g_ExDataServerDB.Clear();

	if(g_ExDataServerDB.ExecQuery("EXEC WZ_GuildCreate '%s', '%s'", szGuild, szMaster) == FALSE)
	{
		g_ExDataServerDB.Clear();
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB]Error executing WZ_GuildCreate");
		return 3;
	}
	
	if(g_ExDataServerDB.Fetch() == SQL_NO_DATA)
	{
		g_ExDataServerDB.Clear();
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB]Error executing WZ_GuildCreate");
		return 3;
	}

	int res = g_ExDataServerDB.GetResult(0);
	g_ExDataServerDB.Clear();

	if( res != 0)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB]WZ_GuildCreate error: %d", res);
		return 3;
	}

	char szTmp[128]={0};
	wsprintf(szTmp, "UPDATE Guild SET G_Mark=? where G_Name='%s'", szGuild);
	g_ExDataServerDB.WriteBlob(szTmp, pMark, 32);
	g_ExDataServerDB.Clear();

	return 0;
}

int GetDBGuildNumber(char *szGuild)
{
	g_ExDataServerDB.ExecQuery("SELECT Number FROM Guild where G_Name='%s'", szGuild);

	g_ExDataServerDB.Fetch();
	int num = g_ExDataServerDB.GetInt("Number");

	g_ExDataServerDB.Clear();

	return num;
}

BOOL AddGuild(char *szGuild, char *szMaster, int iNumber, char *lpNotice, int iScore, LPBYTE pMark, int iType)
{
	if(GuildExists(szGuild))
		return FALSE;

	tagGUILD_INFO_STRUCT Guild;
	Guild.m_iNumber = iNumber;
	strcpy(Guild.m_szGuildName, szGuild);
	strcpy(Guild.m_szGuildMaster, szMaster);
	memcpy(Guild.m_Mark, pMark, 32);
	if(lpNotice)
		strncpy(Guild.m_Notice, lpNotice, 128);
	Guild.m_Score = iScore;
	Guild.m_btGuildType = iType;

#if(ENABLE_MYFIXCODE)
	Guild.m_bGSHasData = FALSE;
#endif
	
	GUILD_MEMBER memb;
	memb.m_btConnected = -1;
	memb.m_btStatus = 128;
	strncpy(memb.m_szMemberName, szMaster, 10);
	
	Guild.m_mapGuildMember[szMaster] = memb;
	g_mapGuildManager[szGuild] = Guild;

	CreateRelationShipData(iNumber);

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[ExDB][AddGuild] Guild [%s] Create Guild Master: [%s]", Guild.m_szGuildName, Guild.m_szGuildMaster);


	return TRUE;
}

BOOL CreateRelationShipData(int iGuild)
{

	if(GetUnionData(iGuild))
		return FALSE;

	UNION_DATA ud;
	ud.m_vecUnionMember.push_back(iGuild);

	g_mapUnionManager[iGuild] = ud;

	return TRUE;
}

LPUNION_DATA GetUnionData(int iGuild)
{
	MAP_UNION_DATA::iterator it;
	it = g_mapUnionManager.find(iGuild);
	if(it == g_mapUnionManager.end())
		return NULL;

	return &it->second;
}

BOOL UpdateGuildMemberStatus(char *szGuild, char *szName, BYTE btStatus)
{
	if( g_ExDataServerDB.ExecQuery("UPDATE GuildMember SET G_Status=%d WHERE Name='%s'", btStatus, szName) == FALSE)
	{
		g_ExDataServerDB.Clear();
		return FALSE;
	}
	
	g_ExDataServerDB.Fetch();
	g_ExDataServerDB.Clear();

	LPGUILD_MEMBER lpMemb;
	lpMemb = GetGuildMember(szGuild, szName);
	if(lpMemb == NULL)
	{
		if(GuildExists(szGuild))
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[ERROR] Guild Member Status: member [%s] doesn't exist in guild [%s]", szName, szGuild);
			return FALSE;
		}
		else
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[ERROR] Guild Member Status: guild [%s] doesn't exist", szGuild);
			return FALSE;
		}
	}

	lpMemb->m_btStatus = btStatus;

	return TRUE;
}

BOOL UpdateGuildType(char *szGuild, BYTE btType)
{
	if( g_ExDataServerDB.ExecQuery("UPDATE Guild SET G_Type=%d WHERE G_Name='%s'", 
		btType, szGuild) == FALSE)
	{
		g_ExDataServerDB.Clear();
		return FALSE;
	}
	
	g_ExDataServerDB.Fetch();
	g_ExDataServerDB.Clear();

	LPGUILD_INFO_STRUCT lpGuild;
	lpGuild = GetGuild(szGuild);
	
	if(lpGuild == NULL)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[ERROR] Guild Type: guild [%s] doesn't exist", szGuild);
		return FALSE;
	}

	lpGuild->m_btGuildType = btType;

	return TRUE;
}

void SendGuildMemberInfo(int aIndex,  char *szName)
{
	char szGuild[11] = {0};
	int iLevel, iStatus;
	if(GetGuildMemberInfo(szName, szGuild, iLevel, iStatus) == FALSE)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Send Guild Member Info] No info returned from g_ExDataServerDB.");
		return;
	}

	LPGUILD_INFO_STRUCT lpGuild;
	LPGUILD_MEMBER lpMemb;

	lpGuild = GetGuild(szGuild);
	if(lpGuild == NULL)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Send Guild Member Info] error: Guild [%s] not found.", szGuild );
		return;
	}

	lpMemb = GetGuildMember(szGuild, szName);
	if(lpMemb == NULL)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[Send Guild Member Info] error: Member [%s] not found in Guild [%s].", szName, szGuild );
		return;
	}

	lpMemb->m_btConnected = gSObj[aIndex].ServerCode;

	DGGuildMasterListSend(szGuild);

	DGRelationShipListSend(aIndex, lpGuild->m_iNumber, 1, 0);
	DGRelationShipListSend(aIndex, lpGuild->m_iNumber, 2, 0);

	SDHP_GUILDMEMBER_INFO GuildMembInfo;
	ZeroMemory(&GuildMembInfo, sizeof(GuildMembInfo));
	PHeadSetB((LPBYTE)&GuildMembInfo, 0x35, sizeof(GuildMembInfo));

	GuildMembInfo.btGuildStatus = lpMemb->m_btStatus;
	strncpy(GuildMembInfo.MemberID, lpMemb->m_szMemberName, 10);
	GuildMembInfo.pServer = lpMemb->m_btConnected;
	GuildMembInfo.btGuildType = lpGuild->m_btGuildType;
	strncpy(GuildMembInfo.GuildName, lpGuild->m_szGuildName, 8);

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[Send Guild Member Info] Guild informaion send: Name[%s] Guild[%s]", szName, szGuild);

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
		{
			DataSend(i, (LPBYTE)&GuildMembInfo, GuildMembInfo.h.size);
		}
	}
}

BOOL GetGuildMemberInfo(char *szName, OUT char *szGuild, OUT int& riLevel, OUT int& riStatus)
{
	g_ExDataServerDB.ExecQuery("SELECT G_Name, G_Level, G_Status FROM GuildMember where Name='%s'",szName);

	SQLRETURN res = g_ExDataServerDB.Fetch();
	if(res == SQL_NO_DATA && res != SQL_SUCCESS && res != SQL_SUCCESS_WITH_INFO)
	{
		g_ExDataServerDB.Clear();
		return FALSE;
	}

	g_ExDataServerDB.GetStr("G_Name", szGuild/*,8*/);
	riLevel = g_ExDataServerDB.GetInt("G_Level");
	riStatus = g_ExDataServerDB.GetInt("G_Status");

	g_ExDataServerDB.Clear();

	return TRUE;
}

void DGGuildMasterListSend(char *szGuild)
{
	LPGUILD_INFO_STRUCT lpGuild;
	lpGuild = GetGuild(szGuild);
	if(lpGuild == NULL)
		return;

#if(ENABLE_MYFIXCODE)
	if(lpGuild->m_bGSHasData)
		return;
#endif

	int bufsize = sizeof(SDHP_GUILDALL_COUNT)+sizeof(SDHP_GUILDALL)*MAX_MEMBER_GUILD;
	BYTE *lpData = new BYTE[bufsize];
	ZeroMemory(lpData, bufsize);

	SDHP_GUILDALL_COUNT* lpGuildAllCnt;
	lpGuildAllCnt = (SDHP_GUILDALL_COUNT*)lpData;

	SDHP_GUILDALL* lpGuildAll;
	lpGuildAll = (SDHP_GUILDALL*)(lpData+sizeof(SDHP_GUILDALL_COUNT));

	lpGuildAllCnt->btGuildType = lpGuild->m_btGuildType;
	strncpy(lpGuildAllCnt->GuildName, lpGuild->m_szGuildName, 8);
	strncpy(lpGuildAllCnt->Master, lpGuild->m_szGuildMaster, 10);

	lpGuildAllCnt->iGuildRival = lpGuild->m_iRivalGuild;
	if(lpGuild->m_iRivalGuild)
	{
		LPGUILD_INFO_STRUCT lpG;
		lpG = GetGuild(lpGuild->m_iRivalGuild);
		if(lpG)
			strncpy(lpGuildAllCnt->szGuildRivalName, lpG->m_szGuildName, 8);

	}
	lpGuildAllCnt->iGuildUnion = lpGuild->m_iUnionGuild;

	memcpy(lpGuildAllCnt->Mark, lpGuild->m_Mark, 32);
	lpGuildAllCnt->Number = lpGuild->m_iNumber;
	lpGuildAllCnt->score = lpGuild->m_Score;

	MAP_GUILD_MEMBER::iterator it, end;
	it = lpGuild->m_mapGuildMember.begin();
	end = lpGuild->m_mapGuildMember.end();

	int i;
	for(i=0; i < MAX_MEMBER_GUILD && it != end; it++, i++)
	{
		strncpy(lpGuildAll[i].MemberID, it->second.m_szMemberName, 10);
		lpGuildAll[i].btGuildStatus = it->second.m_btStatus;
		lpGuildAll[i].pServer = it->second.m_btConnected;

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[GuildMasterListSend] Guild [%s] Member send[%s]", szGuild, it->second.m_szMemberName);
	}

	lpGuildAllCnt->Count = i;

	int datasize = sizeof(SDHP_GUILDALL_COUNT)+ i*sizeof(SDHP_GUILDALL);

	PHeadSetW((LPBYTE)lpGuildAllCnt, 0x36, datasize);

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
		{
			DataSend(i, (LPBYTE)lpData, datasize);
		}
	}

	delete [] lpData;

#if(ENABLE_MYFIXCODE)
	lpGuild->m_bGSHasData = TRUE;
#endif
}

LPGUILD_INFO_STRUCT GetGuild(int iNumber)
{
	MAP_GUILD_INFO_STRUCT::iterator it, end;
	it = g_mapGuildManager.begin();
	end = g_mapGuildManager.end();

	for(; it != end; it++)
	{
		if(it->second.m_iNumber == iNumber)
			break;
	}
	
	if(it == end)
		return NULL;

	return &it->second;
}

void DGRelationShipListSend(int aIndex,  int iGuild, int relation_type, BOOL snd_all)
{
	EXSDHP_UNION_RELATIONSHIP_LIST List;
	ZeroMemory(&List, sizeof(List));

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] RelationShipType [%d], GuildNumber [%d].", relation_type, iGuild);

	PHeadSetW((LPBYTE)&List, 0xE7, sizeof(List));
	List.btRelationShipType = relation_type;
	LPGUILD_INFO_STRUCT lpGuild;

	lpGuild = GetGuild(iGuild);
	if(lpGuild == NULL)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] error: Guild with number [%d] not found.", iGuild);
		return;
	}

	LPUNION_DATA lpGtmp = GetUnionData(iGuild);
	if(lpGtmp != NULL && lpGtmp->m_vecUnionMember.size() > 1)
	{
		if(lpGtmp->m_vecUnionMember[0] == iGuild)
			iGuild = lpGuild->m_iNumber;
	}else
	{
		if(lpGuild->m_iUnionGuild == 0)
			iGuild = lpGuild->m_iNumber;
		else 
			iGuild = lpGuild->m_iUnionGuild;
	}

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] UnionMasterGuild: %d", iGuild);

	lpGuild = GetGuild(iGuild);
	if(lpGuild == NULL)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] error: Guild with number [%d] not found.", iGuild);
		return;
	}

	List.iUnionMasterGuildNumber = lpGuild->m_iNumber;

	if(lpGuild->m_iUnionGuild)
		strncpy(List.szUnionMasterGuildName, lpGuild->m_szGuildName, 8);

	if(relation_type == 1)
	{
		LPUNION_DATA lpUD = GetUnionData(lpGuild->m_iNumber);
		if(lpUD == NULL)
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] error: No union data for Guild [%s].", lpGuild->m_szGuildName);
			return;
		}

		int size = lpUD->m_vecUnionMember.size();
		int i;
		for(i=0; i < size; i++)
			List.iRelationShipMember[i] = lpUD->m_vecUnionMember[i];	
		
		List.btRelationShipMemberCount = size;
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] RelationShipMemberCount[%d] send.", size);
	}
	else if(relation_type == 2)
	{

		LPUNION_DATA lpUD = GetUnionData(lpGuild->m_iNumber);
		if(lpUD == NULL)
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] error: No union data for Guild [%s].", lpGuild->m_szGuildName);
			return;
		}

		int size = lpUD->m_vecUnionMember.size();
		int i, j;
		LPGUILD_INFO_STRUCT lpG = NULL;
		int cnt = 0;

		for(i=0; i < size; i++)
		{
			lpG = GetGuild(lpUD->m_vecUnionMember[i]);
			if(lpG == NULL)
				continue;

			if(lpG->m_iRivalGuild == 0)
				continue;

			lpG = GetGuild(lpG->m_iRivalGuild);

			if(lpG == NULL)
				continue;

			LPUNION_DATA lpUD2 = NULL;

			if(lpG->m_iUnionGuild)
				lpG = GetGuild(lpG->m_iUnionGuild);
						
			if(lpG == NULL)
				continue;

			lpUD2 = GetUnionData(lpG->m_iNumber);
			if(lpUD2 == NULL)
				continue;

			int s2 = lpUD2->m_vecUnionMember.size();
			for(j=0; j < s2; j++)
			{
				List.iRelationShipMember[cnt] = lpUD2->m_vecUnionMember[j];
				cnt++;
			}
		}

		List.btRelationShipMemberCount = cnt;

		g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] RelationShipMemberCount[%d] send.", cnt);
	}

	if(snd_all)
	{
		for(int i = 0; i < MAX_SERVEROBJECT; i++)
		{
			if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
			{
				g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] List Send to Server [%d].", gSObj[i].ServerCode);
				DataSend(i, (LPBYTE)&List, sizeof(List));
			}
		}
	}
	{
		if(aIndex != -1)
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] List Send.");
			DataSend(aIndex, (LPBYTE)&List, sizeof(List));
		}
		else
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip List Send] error: ServerIndex = -1.");
	}
}

BOOL IsCSGuild(char *szGuild)
{
	if(g_ExDataServerDB.ExecQuery("EXEC WZ_CS_CheckSiegeGuildList '%s'", szGuild) == FALSE)
	{
		g_ExDataServerDB.Clear();
		g_Window.ServerLogAdd(ST_EXDATASERVER, "WZ_CS_CheckSiegeList = 1");
		return TRUE;
	}
	else
	{
		BOOL res;
		if(g_ExDataServerDB.Fetch() == SQL_NO_DATA)
			res = TRUE;
		else
			res = g_ExDataServerDB.GetResult(0);

		g_ExDataServerDB.Clear();

		g_Window.ServerLogAdd(ST_EXDATASERVER, "WZ_CS_CheckSiegeList = %d", res);

		return res;
	}
}

int UnionBreak(LPGUILD_INFO_STRUCT lpMasterGuild, LPGUILD_INFO_STRUCT lpKickGuild)
{
	if(lpMasterGuild == NULL || lpKickGuild == NULL)
		return 0;

	if(KickUnion(lpMasterGuild, lpKickGuild) == FALSE)
		return 0;


	if(UpdateDBUnion(lpKickGuild->m_iNumber, 0) == FALSE)
		return 0;

	if(lpMasterGuild->m_iUnionGuild == 0)
	{
		if(UpdateDBUnion(lpMasterGuild->m_iNumber, 0) == FALSE)
			return 0;

		DGRelationShipNotificationSend(lpMasterGuild->m_iNumber, 0x10);
	}

	DGRelationShipListSend(-1, lpMasterGuild->m_iNumber, 1, 1);
	DGRelationShipListSend(-1, lpMasterGuild->m_iNumber, 2, 1);
	DGRelationShipNotificationSend(lpMasterGuild->m_iNumber, 1);


	DGRelationShipListSend(-1, lpKickGuild->m_iNumber, 1, 1);
	DGRelationShipListSend(-1, lpKickGuild->m_iNumber, 2, 1);
	DGRelationShipNotificationSend(lpKickGuild->m_iNumber, 1);


	SendListToAllRivals(lpMasterGuild);
	SendListToAllRivals(lpKickGuild);

	return 1;
}

BOOL KickUnion(LPGUILD_INFO_STRUCT lpMasterGuild, LPGUILD_INFO_STRUCT lpKickGuild)
{
	if(lpMasterGuild == NULL || lpKickGuild == NULL)
		return FALSE;

	if(lpMasterGuild->m_iNumber == lpKickGuild->m_iNumber)
		return FALSE;


	LPUNION_DATA lpUD = GetUnionData(lpMasterGuild->m_iNumber);
	if(lpUD == NULL)
		return FALSE;
	
	int size = lpUD->m_vecUnionMember.size();
	int i;
	for(i=0; i < size; i++)
	{
		if(lpUD->m_vecUnionMember[i] == lpKickGuild->m_iNumber)
			break;
	}

	if(i == size)
		return FALSE;

	lpUD->m_vecUnionMember.erase(lpUD->m_vecUnionMember.begin()+i);

	lpKickGuild->m_iUnionGuild = 0;
	if(lpUD->m_vecUnionMember.size() < 2)
		lpMasterGuild->m_iUnionGuild = 0;

	return TRUE;
}

BOOL UpdateDBUnion(int iGuild, int iUnion)
{
	BOOL res = g_ExDataServerDB.ExecQuery("UPDATE Guild SET G_Union=%d WHERE Number=%d", iUnion, iGuild);
	g_ExDataServerDB.Fetch();
	g_ExDataServerDB.Clear();

	return res;
}

void DGRelationShipNotificationSend(int iGuild, int iUpdateFlag)
{
	LPGUILD_INFO_STRUCT lpGuild;
	lpGuild = GetGuild(iGuild);

	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Notification Send] Guild[%d].", iGuild);

	if(lpGuild == NULL)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Notification Send] error: Guild[%d] not found.", iGuild);
		return;
	}

	LPUNION_DATA lpUDs = GetUnionData(lpGuild->m_iNumber);
	
	int sizes = 0;
	if(lpUDs != NULL)
	{
		sizes=lpUDs->m_vecUnionMember.size();
	}

	if(sizes > 1)
		if(lpGuild->m_iUnionGuild == 0)
			iGuild = lpGuild->m_iUnionGuild;


	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Notification Send] UnionMasterGuild[%d].", iGuild);

	LPUNION_DATA lpUD;

	lpUD = GetUnionData(iGuild);
	if(lpUD == NULL)
	{
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Notification Send] error: No union data for Guild [%d].", iGuild);
		return;
	}

	EXSDHP_NOTIFICATION_RELATIONSHIP List;
	ZeroMemory(&List, sizeof(List));

	PHeadSetW((LPBYTE)&List, 0xE8, sizeof(List));
	List.btUpdateFlag = iUpdateFlag;
	int size = lpUD->m_vecUnionMember.size();
	List.btGuildListCount = size;
	
	g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Notification Send] Guild List Count [%d].", size);

	int i;
	for(i=0; i < size; i++)
	{
		List.iGuildList[i] = lpUD->m_vecUnionMember[i];
	}

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if(gSObj[i].Connected == 2 && gSObj[i].SType == ST_EXDATASERVER)
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "[RelationShip Notification Send] Send to Server [%d].", gSObj[i].ServerCode);
			DataSend(i, (LPBYTE)&List, sizeof(List));
		}
	}
}

void SendListToAllRivals(LPGUILD_INFO_STRUCT lpGuild)
{
	if(lpGuild == NULL)
		return;

	if(lpGuild->m_iUnionGuild)
		lpGuild = GetGuild(lpGuild->m_iUnionGuild);

	if(lpGuild == NULL)
		return;

	LPUNION_DATA lpUD = GetUnionData(lpGuild->m_iNumber);
	if(lpUD == NULL)
		return;


	int size = lpUD->m_vecUnionMember.size();
	for(int i=0; i < size; i++)
	{
		LPGUILD_INFO_STRUCT lpG;
		lpG = GetGuild(lpUD->m_vecUnionMember[i]);
		if(lpG == NULL)
			continue;

		if(lpG->m_iRivalGuild)
		{
			DGRelationShipListSend(-1, lpG->m_iRivalGuild, 2, 1);
			DGRelationShipNotificationSend(lpG->m_iRivalGuild, 1);
		}
	}
}

int RivalBreak(LPGUILD_INFO_STRUCT lpMasterGuild, LPGUILD_INFO_STRUCT lpKickGuild)
{
	if(lpMasterGuild == NULL || lpKickGuild == NULL)
		return 0;

	if(lpMasterGuild->m_iRivalGuild != lpKickGuild->m_iNumber ||
		lpKickGuild->m_iRivalGuild != lpMasterGuild->m_iNumber)
		return 0;


	if(UpdateDBRival(lpMasterGuild->m_iNumber, 0) == FALSE)
		return 0;

	if(UpdateDBRival(lpKickGuild->m_iNumber, 0) == FALSE)
		return 0;

	lpMasterGuild->m_iRivalGuild = 0;
	lpKickGuild->m_iRivalGuild = 0;

	DGRelationShipListSend(-1, lpMasterGuild->m_iNumber, 2, 1);
	DGRelationShipListSend(-1, lpKickGuild->m_iNumber, 2, 1);

	return 1;
}

BOOL UpdateDBRival(int iGuild, int iRival)
{
	BOOL res = g_ExDataServerDB.ExecQuery("UPDATE Guild SET G_Rival=%d WHERE Number=%d", iRival, iGuild);
	g_ExDataServerDB.Fetch();
	g_ExDataServerDB.Clear();

	return res;
}

BOOL MasterDBExists(char *szMaster)
{
	BOOL res = FALSE;

	if(g_ExDataServerDB.ExecQuery("SELECT G_Master FROM Guild where G_Master='%s'", szMaster))
	{
		if(g_ExDataServerDB.Fetch() == SQL_NO_DATA)
			res = FALSE;
		else
			res = TRUE;
	}

	g_ExDataServerDB.Clear();

	return TRUE;
}

BOOL DelAllDBGuildMember(char *szGuild)
{
	BOOL res;

	res = g_ExDataServerDB.ExecQuery("DELETE FROM GuildMember where G_Name='%s'", szGuild);
	g_ExDataServerDB.Fetch();
	g_ExDataServerDB.Clear();

	return res;
}

BOOL DelDBGuild(char *szGuild)
{
	BOOL res;

	res = g_ExDataServerDB.ExecQuery("DELETE FROM Guild where G_Name='%s'", szGuild);
	g_ExDataServerDB.Fetch();
	g_ExDataServerDB.Clear();

	return res;
}

BOOL DelGuild(char *szGuild)
{
	MAP_GUILD_INFO_STRUCT::iterator it;
	it = g_mapGuildManager.find(szGuild);
	if(it == g_mapGuildManager.end())
		return FALSE;

	it->second.m_mapGuildMember.clear();
	g_mapGuildManager.erase(it);

	return TRUE;
}

BOOL DBGuildMemberExists(char *szName)
{
	BOOL res = FALSE;

	if(g_ExDataServerDB.ExecQuery("SELECT Name FROM GuildMember where Name='%s'", szName))
	{
		if(g_ExDataServerDB.Fetch() == SQL_NO_DATA)
			res = FALSE;
		else
			res = TRUE;
	}

	g_ExDataServerDB.Clear();

	return res;
}

BOOL AddDBGuildMember(char *szGuild, char *szName)
{
	BOOL res = g_ExDataServerDB.ExecQuery("INSERT GuildMember (Name, G_Name) VALUES ('%s','%s')", szName, szGuild);
	g_ExDataServerDB.Fetch();
	g_ExDataServerDB.Clear();

	return res;
}

BOOL AddGuildMember(char *szGuild, char *szName, BYTE btStatus, BYTE btConnected)
{
	LPGUILD_INFO_STRUCT lpGuild;
	lpGuild = GetGuild(szGuild);
	if(lpGuild == NULL)
		return FALSE;

	if(GuildMemberExists(szGuild, szName))
		return FALSE;

	GUILD_MEMBER Memb;
	strcpy(Memb.m_szMemberName, szName);
	Memb.m_btStatus = btStatus;
	Memb.m_btConnected = btConnected;

	lpGuild->m_mapGuildMember[szName] = Memb;
	
	g_Window.ServerLogAdd(ST_EXDATASERVER, "[AddGuildMember] Guild [%s] Member Add: [%s]", szGuild, Memb.m_szMemberName);
	return TRUE;
}

BOOL GuildMemberExists(char *szGuild, char *szName)
{
	if(GetGuildMember(szGuild, szName) != NULL)
		return TRUE;
	else
		return FALSE;
}

BOOL DelDBGuildMember(char *szName)
{
	BOOL res = g_ExDataServerDB.ExecQuery("DELETE FROM GuildMember where Name='%s'", szName);
	g_ExDataServerDB.Fetch();
	g_ExDataServerDB.Clear();

	return res;
}

BOOL DelGuildMember(char *szGuild, char *szName)
{
	LPGUILD_INFO_STRUCT lpGuild;
	lpGuild = GetGuild(szGuild);
	if(lpGuild == NULL)
		return FALSE;

	MAP_GUILD_MEMBER::iterator it, end;
	it = lpGuild->m_mapGuildMember.find(szName);
	end = lpGuild->m_mapGuildMember.end();

	if(it == end)
		return FALSE;

	lpGuild->m_mapGuildMember.erase(it);

	return TRUE;
}

BOOL UpdateScore(char *szGuild, int iScore)
{
	if(g_ExDataServerDB.ExecQuery("UPDATE Guild SET G_Score=%d WHERE G_Name='%s'", iScore, szGuild))
	{
		g_ExDataServerDB.Fetch();
		g_ExDataServerDB.Clear();
		LPGUILD_INFO_STRUCT lpGuild;
		lpGuild = GetGuild(szGuild);
		if(lpGuild == NULL)
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L2: %s Guild not found", szGuild);
			return FALSE;
		}

		lpGuild->m_Score = iScore;
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[%s] Guild Score Update: %d", szGuild, iScore);
		return TRUE;
	}
	else
	{
		g_ExDataServerDB.Clear();
		return FALSE;
	}
}

BOOL SaveNotice(char *szGuild, char *szNotice)
{
	if(g_ExDataServerDB.ExecQuery("UPDATE Guild SET G_Notice='%s' WHERE G_Name='%s'", szNotice, szGuild))
	{
		g_ExDataServerDB.Fetch();
		g_ExDataServerDB.Clear();
		LPGUILD_INFO_STRUCT lpGuild;
		lpGuild = GetGuild(szGuild);

		if(lpGuild == NULL)
		{
			g_Window.ServerLogAdd(ST_EXDATASERVER, "error-L2: %s Guild not found", szGuild);
			return FALSE;
		}

		strcpy(lpGuild->m_Notice, szNotice);
		g_Window.ServerLogAdd(ST_EXDATASERVER, "[%s] Guild Notice Update: %s", szGuild, szNotice);
		return TRUE;
	}
	else
	{
		g_ExDataServerDB.Clear();
		return FALSE;
	}
}

int RelationShipOperation(int iReqGuild, int iTargGuild, int relation_type, int operation)
{
	LPGUILD_INFO_STRUCT lpReqGuild;
	LPGUILD_INFO_STRUCT lpTargGuild;

	lpReqGuild = GetGuild(iReqGuild);
	lpTargGuild = GetGuild(iTargGuild);

	if(lpReqGuild == NULL || lpTargGuild == NULL)
		return 0;

	if(IsCSGuild(lpReqGuild->m_szGuildName))
		return 0x10;

	if(IsCSGuild(lpTargGuild->m_szGuildName))
		return 0x10;

	switch(operation)
	{
		case 0:
			return RelationShipJoin(lpReqGuild, lpTargGuild, relation_type);

		case 1:
			return RelationShipBreak(lpTargGuild, lpReqGuild, relation_type);

		default:
			return 0;
	}
}

int RelationShipJoin(LPGUILD_INFO_STRUCT lpReqGuild, LPGUILD_INFO_STRUCT lpTargGuild, int type)
{
	switch(type)
	{
		case 1:
			return UnionJoin(lpReqGuild, lpTargGuild);

		case 2:
			return RivalJoin(lpReqGuild, lpTargGuild);

		default:
			return 0;
	}
}

int RelationShipBreak(LPGUILD_INFO_STRUCT lpMasterGuild, LPGUILD_INFO_STRUCT lpKickGuild, int type)
{
	switch(type)
	{
		case 1:
			return UnionBreak(lpMasterGuild, lpKickGuild);
		case 2:
			return RivalBreak(lpMasterGuild, lpKickGuild);
		default:
			return 0;
	}
}

int UnionJoin(LPGUILD_INFO_STRUCT lpReqGuild, LPGUILD_INFO_STRUCT lpTargGuild)
{
	if(AddUnion(lpReqGuild, lpTargGuild) == FALSE)
		return 0;

	if(UpdateDBUnion(lpReqGuild->m_iNumber, lpTargGuild->m_iNumber) == FALSE)
		return 0;

	if(lpTargGuild->m_iUnionGuild != lpTargGuild->m_iNumber)
	{
		if(UpdateDBUnion(lpTargGuild->m_iNumber, lpTargGuild->m_iNumber) == FALSE)
			return 0;
	}
	
	DGRelationShipListSend(-1, lpTargGuild->m_iNumber, 1, 1);
	DGRelationShipListSend(-1, lpTargGuild->m_iNumber, 2, 1);
	DGRelationShipNotificationSend(lpTargGuild->m_iNumber, 1);

	SendListToAllRivals(lpTargGuild);
	return 1;
}

BOOL AddUnion(LPGUILD_INFO_STRUCT lpReqGuild, LPGUILD_INFO_STRUCT lpTargGuild)
{
	if(lpReqGuild == NULL || lpTargGuild == NULL)
		return FALSE;

	if( lpReqGuild->m_iUnionGuild != 0)
		return FALSE;

	if( lpTargGuild->m_iUnionGuild != 0 && lpTargGuild->m_iNumber == lpTargGuild->m_iUnionGuild)
		return FALSE;


	if(AddUnion(lpReqGuild->m_iNumber, lpTargGuild->m_iNumber))
	{
		lpReqGuild->m_iUnionGuild = lpTargGuild->m_iNumber;
		lpTargGuild->m_iUnionGuild = lpReqGuild->m_iNumber;
		return TRUE;
	}

	return FALSE;
}

BOOL AddUnion(int iReqGuild, int iTargGuild)
{
	if(iReqGuild == iTargGuild)
		return FALSE;

	LPUNION_DATA lpUD = GetUnionData(iTargGuild);
	if(lpUD == NULL)
		return FALSE;

	lpUD->m_vecUnionMember.push_back(iReqGuild);

	return TRUE;
}

int RivalJoin(LPGUILD_INFO_STRUCT lpReqGuild, LPGUILD_INFO_STRUCT lpTargGuild)
{
	if(lpReqGuild->m_iRivalGuild != 0 || lpTargGuild->m_iRivalGuild != 0)
		return 0;


	if(UpdateDBRival(lpReqGuild->m_iNumber, lpTargGuild->m_iNumber) == FALSE)
		return 0;

	if(UpdateDBRival(lpTargGuild->m_iNumber, lpReqGuild->m_iNumber) == FALSE)
		return 0;

	lpReqGuild->m_iRivalGuild = lpTargGuild->m_iNumber;
	lpTargGuild->m_iRivalGuild = lpReqGuild->m_iNumber;

	DGRelationShipListSend(-1, lpReqGuild->m_iNumber, 2, 1);
	DGRelationShipListSend(-1, lpTargGuild->m_iNumber, 2, 1);

	SendListToAllRivals(lpTargGuild);

	return 1;
}

//--------------------------
// ---- FriendSererDB -----
//--------------------------

