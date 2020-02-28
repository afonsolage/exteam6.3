#pragma once

#include "StdAfx.h"
#include "..\include\prodef.h"
#include "MapClass.h"

#if(CUSTOM_MAPQUEST)

struct MAPQUEST_DATA
{
	int MapNum;
	int MonsterCount;
	int BossClass;
	int BossX;
	int BossY;
	int OrcClass;
	int OrcCount;
};

struct PMSG_DUNGEON_SYSTEM
{
	PBMSG_HEAD2 h;
	bool Show;
	int Count;
	int MaxCount;
};

struct MAPQUEST_MONSTER
{
	short sIndex;
	short sPos;
	bool bDie;
};

class CMapQuest
{
public:
	     CMapQuest();
		 ~CMapQuest();

	void Load();
	void Read(char* filename);
	void MonsterKill(int aIndex, int aTargetIndex);
	void AddBoss(int Map, int BossClass, int BossX, int BossY, int OrcClass, int OrcCount);
	void GCInfo(int aIndex, bool Show, int Count, int MaxCount);
	void ReloadMonster();
	void TeleportMap(int aIndex, int Map);	

	void LoadMonsterPos();
	int GetMonsterPos(WORD Type, BYTE Map, BYTE X, BYTE Y);
	void AddBossEx(int Map, int BossClass, int BossX, int BossY, int OrcClass, int OrcCount);
	void DelMonster(int aIndex, int Map);
	void DelMonsterMap(int Map);
	bool GetMapMonster(int aIndex);

	std::vector<MAPQUEST_DATA> m_Data;
	int m_MapKillCount[MAX_NUMBER_MAP];
	bool m_BossStart[MAX_NUMBER_MAP];

	MAPQUEST_MONSTER m_Boss[MAX_NUMBER_MAP];
	MAPQUEST_MONSTER m_Monster[MAX_NUMBER_MAP][100];


	bool m_MonsterPosLoaded;
};
extern CMapQuest g_MapQuest;

#endif