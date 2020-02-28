#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

#define MAX_MISSION_QUEST	5
#define MAX_REWARD_QUEST	3
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
	char Mission[20];
	//BYTE Procent;
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

struct MonsterExQuest
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
	WORD KillCount[MAX_MISSION_QUEST];
	MonsterQuest_GC	MonsterDataGC[MAX_MISSION_QUEST];
	RewardQuest_GC	RewardDataGC[MAX_REWARD_QUEST];	
};
// -------------------------------------------------------------------------------

struct GCMonsterQuestConnect
{
	PBMSG_HEAD2 h;
	MonsterExQuest UserQuest;
};
// -------------------------------------------------------------------------------

struct GCQuestWindowsOpen
{
	PBMSG_HEAD2 h;
	BYTE Open;
};
// -------------------------------------------------------------------------------

struct CGFinishMonsterQuest
{
	PBMSG_HEAD2 h;
	BYTE Reward;
};
// -------------------------------------------------------------------------------

class MonsterQuest
{
public:
	MonsterQuest();
	~MonsterQuest();
	// ----
	int MyQuest;
	int MaxQuest;

	void InterfaceLoad();

	void RecvKill(GCMonsterQuestKill * aRecv);	//17
	void RecvMission(GCMonsterQuestDialog * aRecv);	//18
	void RecvWindowsOpen(GCQuestWindowsOpen *aRecv);

	bool DoneQuest();

	void OpenQuestMainWindow();
	void CloseQuestMainWindow();
	bool CheckQuestMainWindow();

	void DrawMainTable();
	bool EventCloseMainTable(DWORD Event);
	bool EventFinishMainTable(DWORD Event);

	bool DrawInfoTable;
	void DrawInfo();

	void SendFinish();

	short KillCount[MAX_MISSION_QUEST];

	int MaxMonsterMission;
	int MaxRewardMission;

	MonsterQuest_DATA	MonsterData[MAX_MISSION_QUEST];
	RewardQuest_DATA	RewardData[MAX_REWARD_QUEST];
private:


};
extern MonsterQuest gMonsterQuest;
// -------------------------------------------------------------------------------