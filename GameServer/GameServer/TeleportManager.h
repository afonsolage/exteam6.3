#pragma once

#include "StdAfx.h"
#include "user.h"

/*
План работы
Телепорт через НПС
Телепорт через команды
Ограничение уровня на карту
*/

/*
1 - Zen
2 - ExCred
3 - WcoinC
4 - WcoinP
5 - Goblin Points
*/


#ifdef TELEPORT_MANAGER

#define TeleportManager_DIR "..\\Data\\ExData\\TeleportManager.ini"

#define MAX_TELEPORT	100

struct tNPC_DATA
{
	short NPC;
	short MAP;
	short X;
	short Y;
	short TeleportMap;
	short TeleportX;
	short TeleportY;
	short Level;
	short Reset;
	short GReset;
	short MaxReset;
	short MaxGReset;
	short Premium;
	int Price;
	int Value;
};

struct tCMD_DATA
{
	char Command[50];
	short TeleportMap;
	short TeleportX;
	short TeleportY;
	short Level;
	short Reset;
	short GReset;
	short MaxReset;
	short MaxGReset;
	short Premium;
	int Price;
	int Value;
};

struct DLTP_BLOCK_DATA
{
	int MapNumber;
};

class cTeleportManager
{
public:
	cTeleportManager();
	~cTeleportManager();

	void Load();

	void NPCClick(LPOBJ lpNpc, LPOBJ lpObj);
	void ChatDataSend(int aIndex, LPBYTE Protocol);

	bool CheckTeleoprtMap(int aIndex, int aTargetIndex);

private:

	bool Enable;

	tNPC_DATA	NpcBase[MAX_TELEPORT];
	tCMD_DATA	CmdBase[MAX_TELEPORT];

	int CountNPC;
	int CountCMD;

#if(SILVER_DL_TP)
public:
	bool CheckTeleportDL(int map);
	std::vector<DLTP_BLOCK_DATA> m_dlblock;
#endif


	bool CheckDLMasterTeleport(int Map);
	bool CheckDLMemberTeleport(int Map);
	std::vector<DLTP_BLOCK_DATA> m_DLMasterBlock;
	std::vector<DLTP_BLOCK_DATA> m_DLMemberBlock;
};
extern cTeleportManager gTeleportManager;

#endif