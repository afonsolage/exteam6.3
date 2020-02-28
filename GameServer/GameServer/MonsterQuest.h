#pragma once
// -------------------------------------------------------------------------------

#include "StdAfx.h"
//#ifdef MONSTER_QUEST_DEV
//#include "user.h"
//#include "protocol.h"
// -------------------------------------------------------------------------------

#define MAX_MONSTER_QUEST	500
#define MAX_MISSION_QUEST	5
#define MAX_REWARD_QUEST	3

#define DEBUG_MQUEST		1
// -------------------------------------------------------------------------------

enum
{
	eOff,
	eZen,
	eFreePoints,
	eItem,
	eWCoin,
	eWCoinP,
	eGoblin,
	eCredit,
};
// -------------------------------------------------------------------------------

struct MonsterQuest_DATA
{
	BYTE Active;
	WORD Mission;
	BYTE Procent;
	DWORD Count;
};
// -------------------------------------------------------------------------------

struct RewardQuest_DATA
{
	BYTE Active;
	DWORD Reward;
	BYTE RewardID;
	BYTE Level;
	BYTE Skill;
	BYTE Luck;
	BYTE Option;
	BYTE Exellent;
	BYTE Ancent;
};
// -------------------------------------------------------------------------------

struct MonsterQuestUser
{
	WORD QuestNumber;
	DWORD KillCount[MAX_MISSION_QUEST];
};
// -------------------------------------------------------------------------------

struct GCMonsterQuestKill
{
	PBMSG_HEAD2 h;
	BYTE MissionNum;
	DWORD MissionKill;
};
// -------------------------------------------------------------------------------

struct MonsterQuest_GC
{
	BYTE Active;
	char Mission[20];
	//BYTE Procent;
	DWORD Count;
};
// -------------------------------------------------------------------------------

struct RewardQuest_GC
{
	BYTE Active;
	DWORD Reward;
	BYTE RewardID;
	BYTE Level;
	BYTE Skill;
	BYTE Luck;
	BYTE Option;
	BYTE Exellent;
	BYTE Ancent;
};
// -------------------------------------------------------------------------------

struct GCMonsterQuestDialog
{
	PBMSG_HEAD2 h;
	WORD NumQuest;
	WORD MaxQuest;
	WORD KillCount[MAX_MISSION_QUEST];	//18
	MonsterQuest_GC	MonsterDataGC[MAX_MISSION_QUEST];
	RewardQuest_GC	RewardDataGC[MAX_REWARD_QUEST];	
};
// -------------------------------------------------------------------------------

struct GCMonsterQuestConnect	//No Code
{
	PBMSG_HEAD2 h;
	MonsterQuestUser UserQuest;
};
// -------------------------------------------------------------------------------

struct GCQuestWindowsOpen
{
	PBMSG_HEAD2 h;
	BYTE Open;
};
// -------------------------------------------------------------------------------

class MonsterQuest
{
public:
	// ----
	MonsterQuest();
	~MonsterQuest();
	// ----
	void Init();
	void Load();
	void Read(char *File);
	// ----

	bool NPCDialog(int UserIndex, int NpcIndex);
	void MissionKill(int MonsterIndex, int UserIndex);
	void MissionReward(int UserIndex);
	bool CheckDoneQuest(int UserIndex);
	// ----
	void GCMonsterKill(int aIndex, int n);
	void GCMission(int UserIndex);
	void GCConnectUser(int UserIndex);
	void GCWindowsOpen(int UserIndex);

	// ----
	void DBLoad();
	void DBSave();
	// ----
private:
	bool Enable;
	WORD NPC_Class;
	BYTE NPC_Map;
	BYTE NPC_X;
	BYTE NPC_Y;
	// ----
	MonsterQuest_DATA	MonsterData[MAX_MONSTER_QUEST][MAX_MISSION_QUEST];
	RewardQuest_DATA	RewardData[MAX_MONSTER_QUEST][MAX_REWARD_QUEST];
	// ----
	DWORD QuestCount;
};
extern MonsterQuest gMonsterQuest;
// -------------------------------------------------------------------------------
//#endif