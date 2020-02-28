#include "StdAfx.h"
#include "DungeonSiege.h"
#include "MainFrm.h"

#if(EVENT_DUNGEON_SIEGE)

CDungeonSiege g_DungeonSiege;

CDungeonSiege::CDungeonSiege()
{
}

CDungeonSiege::~CDungeonSiege()
{
}

bool CDungeonSiege::Connect()
{
	bool Result = this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass);

	if(Result)
	{
		this->CreateTable();
	}

	return Result;
}

void CDungeonSiege::CreateTable()
{
	this->m_DBQuery.WriteLog = false;
	this->m_DBQuery.Exec("ALTER TABLE [GameServerInfo] ADD [DungeonOwner] varchar(8)");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();
	this->m_DBQuery.Exec("CREATE TABLE DungeonSiegeList(GuildName varchar(8))");
	this->m_DBQuery.Fetch();
	this->m_DBQuery.Clear();
	this->m_DBQuery.WriteLog = true;
}

void CDungeonSiege::GDRegSiegeList(int uIndex)
{
	CString Query;
	int iQcount = 0;

	PMSG_DG_DUNGEON_SIEGE_REG_LIST pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x03, sizeof(pMsg));

	if(this->m_DBQuery.Exec("SELECT * FROM DungeonSiegeList"))
	{
		short iFetch = m_DBQuery.Fetch();

		while(iFetch != SQL_NO_DATA && iFetch != SQL_NULL_DATA)
		{
			char GuildName[9];
			GuildName[8] = 0;
			this->m_DBQuery.GetStr("GuildName", GuildName);
			memcpy(pMsg.szGuildName[iQcount],GuildName,8);

			iQcount++;
			if(iQcount >= 10)
			{
				break;
			}

			iFetch = this->m_DBQuery.Fetch();
		}
	}

	this->m_DBQuery.Clear();
	
	pMsg.iCount = iQcount;

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CDungeonSiege::GDRegSiege(PMSG_GD_DUNGEON_SIEGE_GUILD_REG* lpMsg, int uIndex)
{
	CString Query;

	PMSG_GD_DUNGEON_SIEGE_GUILD_REG_RESULT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x04, sizeof(pMsg));
	pMsg.bResult = true;
	pMsg.aIndex = lpMsg->aIndex;

	char szGName[9];
	memcpy(szGName, lpMsg->szGuildName, sizeof(szGName)-1);
	szGName[8] = 0;

	Query.Format("INSERT INTO DungeonSiegeList (GuildName) VALUES ('%s')", szGName);

	if(!this->m_DBQuery.Exec(Query))
	{
		LogAdd("[%s] Failed to insert DungeonSiegeList values", __FUNCTION__);
		pMsg.bResult = false;
	}

	this->m_DBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CDungeonSiege::GDSiegeClearList()
{
	this->m_DBQuery.Exec("DELETE FROM DungeonSiegeList");
	this->m_DBQuery.Clear();
}

void CDungeonSiege::GDSiegeOwner(int uIndex)
{
	PMSG_DG_DUNGEON_SIEGE_SELECT_OENER pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x06, sizeof(pMsg));
	pMsg.bResult = false;
	memset(pMsg.szGuildOwner, 0, sizeof(pMsg.szGuildOwner));

	if(this->m_DBQuery.Exec("SELECT DungeonOwner FROM GameServerInfo WHERE Number = 0"))
	{
		if(this->m_DBQuery.Fetch() != SQL_NO_DATA)
		{
			char szGName[9];
			szGName[8] = 0;
			this->m_DBQuery.GetStr("DungeonOwner", szGName);

			if(szGName[0] == NULL)
			{
				pMsg.bResult = false;
			}
			else
			{
				memcpy(pMsg.szGuildOwner, szGName, sizeof(szGName)-1);
				pMsg.bResult = true;
			}
		}
	}

	this->m_DBQuery.Clear();

	wsjServer.DataSend(uIndex, (char*)&pMsg, pMsg.h.size);
}

void CDungeonSiege::GDSiegeOwnerUpdate(PMSG_GD_DUNGEON_SIEGE_UPDATE_OENER* lpMsg, int aIndex)
{
	CString Query;

	char GuildName[9];
	GuildName[8] = 0;
	memcpy(GuildName, lpMsg->szGuildOwner, 8);

	Query.Format("UPDATE GameServerInfo SET DungeonOwner = '%s' WHERE Number = 0", GuildName);
	this->m_DBQuery.Exec(Query);
	this->m_DBQuery.Clear();
}

#endif