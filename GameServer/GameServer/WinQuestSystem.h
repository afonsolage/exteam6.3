#pragma once

#include "StdAfx.h"
#include "user.h"

// ---------------------------------------------------------------------------------------------

//#ifdef WIN_QUEST_SYSTEM

// ---------------------------------------------------------------------------------------------

#define WIN_QUEST_SYSTEM_CFG  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystemConfig.ini"

#define WIN_QUEST_SYSTEM_DIR1  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem1.ini"
#define WIN_QUEST_SYSTEM_DIR2  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem2.ini"
#define WIN_QUEST_SYSTEM_DIR3  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem3.ini"
#define WIN_QUEST_SYSTEM_DIR4  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem4.ini"
#define WIN_QUEST_SYSTEM_DIR5  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem5.ini"
#define WIN_QUEST_SYSTEM_DIR6  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem6.ini"
#define WIN_QUEST_SYSTEM_DIR7  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem7.ini"
#define WIN_QUEST_SYSTEM_DIR8  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem8.ini"
#define WIN_QUEST_SYSTEM_DIR9  "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem9.ini"
#define WIN_QUEST_SYSTEM_DIR10 "..\\Data\\ExData\\WinQuestSystem\\WinQuestSystem10.ini"

// ---------------------------------------------------------------------------------------------

#define MAX_WIN_QUEST		10
#define MAX_USE_QUEST		5
#define MAX_WIN_QUEST_NUM	1000

#define WIN_QUEST_DEBUG		0

// ---------------------------------------------------------------------------------------------

struct WinDataQuest
{
	int n;
	int e;
	char Name[50];
	int  MissionType[5];	//0 - off; 1 - kill; 2 - drop; 3 - item;
	int  MissionMain[5];
	int  MissionLvL[5];
	int  MissionLuck[5];
	int  MissionExl[5];
	int  MissionAnc[5];
	int  RewardType[5];		//0-off;1-zen;2-ExFreePoints;3-WcoinC;4-WcoinP;5-Goblin;6-Cred;7-Damage;8-Defence;9-Life;10-SD;11-CritDmg;12-ExlDmg;13-Double;14-Ignore;15-Ref;16-Exp;17-Drop;7-Item
	int  RewardMain[5];
	int  RewardLvL[5];
	int  RewardLuck[5];
	int  RewardExl[5];
	int  RewardAnc[5];
	int  PriceType[5];		//0 - off; 1 - zen; 2 - WcoinC; 3 - WcoinP; 4 - Goblin; 5 - Cred; 6 - Item
	int  PriceMain[5];
	int  PriceLvL[5];
	int  NeedLevel;
	int  NeedReset;
	int  NeedGrand;
	char Info[256];
};

// ---------------------------------------------------------------------------------------------

struct CGWinQuestNumber
{
	BYTE reward;
	BYTE accept;
	BYTE start;
	short n;
	short e;
	BYTE Finish;
	char Name[40];
	BYTE  MissionType[5];	//0 - off; 1 - kill; 2 - drop; 3 - item;
	char MissionName[5][20];
	short  MissionMain[5];
	short  MissionLvL[5];
	BYTE  MissionLuck[5];
	BYTE  MissionExl[5];
	BYTE  MissionAnc[5];
	BYTE  MissionCheck[5];
	BYTE  RewardType[5];		//0-off;1-zen;2-ExFreePoints;3-WcoinC;4-WcoinP;5-Goblin;6-Cred;7-Damage;8-Defence;9-Life;10-SD;11-CritDmg;12-ExlDmg;13-Double;14-Ignore;15-Ref;16-Exp;17-Drop;18-Item
	int  RewardMain[5];
	short  RewardLvL[5];
	BYTE  RewardLuck[5];
	BYTE  RewardExl[5];
	BYTE  RewardAnc[5];
	BYTE  PriceType[5];		//0 - off; 1 - zen; 2 - WcoinC; 3 - WcoinP; 4 - Goblin; 5 - Cred; 6 - Item
	int  PriceMain[5];
	short  PriceLvL[5];
	int  PriceDone[5];
	BYTE PriceCheck[5];
	short  NeedLevel;
	short  LevelDone;
	short  NeedReset;
	short  ResetDone;
	short  NeedGrand;
	short  GrandDone;
	char Info[200];
	short Count[5];
	int PCount[5];
};

struct CGWinQuestSystemTable
{
	PWMSG_HEAD2 h;
	BYTE OpenWind;
	int Damage;
	int Defence;
	int Life;
	int SD;
	int Crit;
	int Exel;
	int Double;
	int Ignore;
	int Ref;
	int Exp;
	int Drop;	
	CGWinQuestNumber exQuest[MAX_WIN_QUEST];
};

// ---------------------------------------------------------------------------------------------

struct QuestUser
{
	short Start[MAX_WIN_QUEST];
	short Num[MAX_WIN_QUEST];
	short Count[MAX_WIN_QUEST][5];
	// ----
	int Damage;
	int Defence;
	int Life;
	int SD;
	int Crit;
	int Exel;
	int Double;
	int Ignore;
	int Ref;
	int Exp;
	int Drop;
};

// ---------------------------------------------------------------------------------------------

struct GDQuestUser
{
	PBMSG_HEAD2 h;	// C1:XX
	char Name[10];
	short Start[MAX_WIN_QUEST];
	short Num[MAX_WIN_QUEST];
	short Count[MAX_WIN_QUEST][5];
	// ----
	int Damage;
	int Defence;
	int Life;
	int SD;
	int Crit;
	int Exel;
	int Double;
	int Ignore;
	int Ref;
	int Exp;
	int Drop;
};

// ---------------------------------------------------------------------------------------------

struct CGSendQuestResult
{
	PBMSG_HEAD2 h;
	BYTE Result;
	BYTE Num;
};

// ---------------------------------------------------------------------------------------------

struct CGWinQuestProcess
{
	PWMSG_HEAD2 h;
	short Count[MAX_WIN_QUEST][5];
	BYTE  Check[MAX_WIN_QUEST][5];
};

// ---------------------------------------------------------------------------------------------

struct CGWinClose
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

// ---------------------------------------------------------------------------------------------

struct GDSelectQuest
{
	PBMSG_HEAD2 h;
	short aIndex;
	char Name[10];
};

// ---------------------------------------------------------------------------------------------

struct DGQuestUserInfo
{
	PBMSG_HEAD2 h;	// C1:XX
	short aIndex;
	char Name[10];
	short Start[MAX_WIN_QUEST];
	short Num[MAX_WIN_QUEST];
	short Count[MAX_WIN_QUEST][5];
	// ----
	int Damage;
	int Defence;
	int Life;
	int SD;
	int Crit;
	int Exel;
	int Double;
	int Ignore;
	int Ref;
	int Exp;
	int Drop;
};

// ---------------------------------------------------------------------------------------------

class cWinQuestSystem
{
public:
	cWinQuestSystem();
	// ----
	void Init();
	void Load(int iQuest, char *Dir);
	// ----
	void NPCClicker(LPOBJ lpNpc, LPOBJ lpObj);
	void MonsterKiller(LPOBJ lpObj, LPOBJ lpTargetObj);	//lpTargetObj - тот кто убивает
	bool MonsterDrop(int aIndex, short ItemType);
	// ----
	void SendPacket(int aIndex, BYTE OpenWind);
	void SendInfoPacket(int aIndex);
	void SendWindowsClose(int aIndex);
	void RecvPacket(int aIndex, CGSendQuestResult * Date);
	// ----
	bool CheckItemUser(int aIndex, int QuestNum, int k);
	// ----
	void DGSendInformation(int aIndex);
	void ReqQuestInfo(LPOBJ lpObj);
	void RecvQuestInfo(DGQuestUserInfo * Recv);
	// ----
	void CharOptions(int aIndex);
	void ExpOption(int aIndex, __int64 & Exp);
	void ZenOption(int aIndex, float & Money);

	// ----
	WinDataQuest Data[MAX_WIN_QUEST][MAX_WIN_QUEST_NUM];
	QuestUser	 WinQ[OBJMAX];
	int Count[MAX_WIN_QUEST];

	bool GetActive();
	// ----
private:
	bool Enable;

	int NPC;
	// ----
};
extern cWinQuestSystem gWinQuestSystem;

// ---------------------------------------------------------------------------------------------

//#endif