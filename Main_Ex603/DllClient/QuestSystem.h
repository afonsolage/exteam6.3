#pragma once

// -------------------------------------------------------------------------------------------

#include "Protocol.h"

// -------------------------------------------------------------------------------------------

#define MAX_WIN_QUEST		10
#define MAX_USE_QUEST		5
#define MAX_WIN_QUEST_NUM	1000

// -------------------------------------------------------------------------------------------



// -------------------------------------------------------------------------------------------

#define MAX_QXoR	8
//#define QUESTBUFFER			"%d %d %d %d %d %d %d %d %d %d %d %d"

#define QUESTBUFFER			"%d %d"

#define QUESTINFO_DIR		"Data/Custom/Configs/Util/Quest.ex"

struct WinDataQuest
{
	BYTE reward;
	BYTE accept;
	BYTE start;
	int n;
	int e;
	BYTE Finish;
	char Name[50];
	int  MissionType[5];	//0 - off; 1 - kill; 2 - drop; 3 - item;
	char MissionName[5][20];
	int  MissionMain[5];
	int  MissionLvL[5];
	int  MissionLuck[5];
	int  MissionExl[5];
	int  MissionAnc[5];
	int  MissionCheck[5];
	int  RewardType[5];		//0-off;1-zen;2-ExFreePoints;3-WcoinC;4-WcoinP;5-Goblin;6-Cred;7-Damage;8-Defence;9-Life;10-SD;11-CritDmg;12-ExlDmg;13-Double;14-Ignore;15-Ref;16-Exp;17-Drop;7-Item
	int  RewardMain[5];
	int  RewardLvL[5];
	int  RewardLuck[5];
	int  RewardExl[5];
	int  RewardAnc[5];
	int  PriceType[5];		//0 - off; 1 - zen; 2 - WcoinC; 3 - WcoinP; 4 - Goblin; 5 - Cred; 6 - Item
	int  PriceMain[5];
	int  PriceLvL[5];
	int  PriceDone[5];
	int PriceCheck[5];
	int  NeedLevel;
	int  LevelDone;
	int  NeedReset;
	int  ResetDone;
	int  NeedGrand;
	int  GrandDone;
	char Info[256];
	int Count[5];
	int PCount[5];
};

// -------------------------------------------------------------------------------------------

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
	BYTE  RewardType[5];		//0-off;1-zen;2-ExFreePoints;3-WcoinC;4-WcoinP;5-Goblin;6-Cred;7-Damage;8-Defence;9-Life;10-SD;11-CritDmg;12-ExlDmg;13-Double;14-Ignore;15-Ref;16-Exp;17-Drop;7-Item
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

// -------------------------------------------------------------------------------------------

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

// -------------------------------------------------------------------------------------------

struct CGSendQuestResult
{
	PBMSG_HEAD2 h;
	BYTE Result;
	BYTE Num;
};

// -------------------------------------------------------------------------------------------

struct CGWinQuestProcess
{
	PWMSG_HEAD2 h;
	short Count[MAX_WIN_QUEST][5];
	BYTE  Check[MAX_WIN_QUEST][5];
};

// -------------------------------------------------------------------------------------------

struct CGWinClose
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

// -------------------------------------------------------------------------------------------

class cQuestSystem
{
private:
	
	int QMainTableHigh;
	int QMainTableWidth;
	int DrawStartX;
	int DrawStartY;
	int MenuOpen;
	bool DrawQuestTable;

	BYTE InfoColor;
	int InfoStartY;
	int InfoWidth;
	int InfoHigh;	
	int InfoStartX;
	bool DrawInfoTable;
	DWORD InfoClickTime;

	BYTE InfoColor2;
	int InfoStartY2;
	int InfoWidth2;
	int InfoHigh2;	
	int InfoStartX2;
	bool DrawInfoTable2;
	DWORD InfoClickTime2;

	bool MoveAct;
	bool MoveAct2;

public:
		 cQuestSystem();
		 ~cQuestSystem();

	void Init();
	void LoadTGA();
	void Draw();
	void DrawMainTable();
	void DrawInfo();
	void DrawInfoAchievements();
	void MouseRun();
	void Protocol(DWORD Case, LPBYTE Data, int Len, int aIndex);
	void RestartQuest();
	void Encode(char* buffer, int size);
	void SaveGame();
	void LoadGame();
	void Keyboard(WPARAM Click);
	void Switcher(BYTE type);
	bool GetActive(BYTE type);

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

	WinDataQuest Quest[MAX_WIN_QUEST];
};
extern cQuestSystem gQuestSystem;