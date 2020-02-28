#pragma once

#include "StdAfx.h"

#define EVENT_DUNGEON_SIEGE		1

#if(EVENT_DUNGEON_SIEGE)

struct PMSG_DG_DUNGEON_SIEGE_REG_LIST
{
	PBMSG_HEAD2 h;
	int  iCount;
	char szGuildName[10][9];
};

struct PMSG_GD_DUNGEON_SIEGE_GUILD_REG
{
	PBMSG_HEAD2 h;
	bool bResult;
	int  aIndex;
	char szGuildName[9];
};

struct PMSG_GD_DUNGEON_SIEGE_GUILD_REG_RESULT
{
	PBMSG_HEAD2 h;
	bool bResult;
	int  aIndex;
};

struct PMSG_GD_DUNGEON_SIEGE_UPDATE_OENER
{
	PBMSG_HEAD2 h;
	char szGuildOwner[9];
};

struct PMSG_DG_DUNGEON_SIEGE_SELECT_OENER
{
	PBMSG_HEAD2 h;
	bool bResult;
	char szGuildOwner[9];
};

class CDungeonSiege
{
public:
		 CDungeonSiege();
		 ~CDungeonSiege();

	bool Connect();
	void CreateTable();
	void GDRegSiegeList(int uIndex);
	void GDRegSiege(PMSG_GD_DUNGEON_SIEGE_GUILD_REG* lpMsg, int uIndex);
	void GDSiegeClearList();
	void GDSiegeOwner(int uIndex);
	void GDSiegeOwnerUpdate(PMSG_GD_DUNGEON_SIEGE_UPDATE_OENER* loMsg, int aIndex);

	CQuery m_DBQuery;
};

extern CDungeonSiege g_DungeonSiege;

#endif