#ifndef DEVILSQUARE_H
#define DEVILSQUARE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DS_SQUARE_SIZE 35

#define DS_1_BEGIN_X 119
#define DS_1_BEGIN_Y 78
#define DS_1_END_X DS_1_BEGIN_X + DS_SQUARE_SIZE
#define DS_1_END_Y DS_1_BEGIN_Y + DS_SQUARE_SIZE

#define DS_2_BEGIN_X 123
#define DS_2_BEGIN_Y 150
#define DS_2_END_X DS_2_BEGIN_X + DS_SQUARE_SIZE
#define DS_2_END_Y DS_2_BEGIN_Y + DS_SQUARE_SIZE

#define DS_3_BEGIN_X 49
#define DS_3_BEGIN_Y 138
#define DS_3_END_X DS_3_BEGIN_X + DS_SQUARE_SIZE
#define DS_3_END_Y DS_3_BEGIN_Y + DS_SQUARE_SIZE

#define DS_4_BEGIN_X 53
#define DS_4_BEGIN_Y 74
#define DS_4_END_X DS_4_BEGIN_X + DS_SQUARE_SIZE
#define DS_4_END_Y DS_4_BEGIN_Y + DS_SQUARE_SIZE

#define DS_5_BEGIN_X 118
#define DS_5_BEGIN_Y 80
#define DS_5_END_X DS_5_BEGIN_X + DS_SQUARE_SIZE
#define DS_5_END_Y DS_5_BEGIN_Y + DS_SQUARE_SIZE

#define DS_6_BEGIN_X 120
#define DS_6_BEGIN_Y 151
#define DS_6_END_X DS_6_BEGIN_X + DS_SQUARE_SIZE
#define DS_6_END_Y DS_6_BEGIN_Y + DS_SQUARE_SIZE

#define DS_7_BEGIN_X 49
#define DS_7_BEGIN_Y 138
#define DS_7_END_X DS_7_BEGIN_X + DS_SQUARE_SIZE
#define DS_7_END_Y DS_7_BEGIN_Y + DS_SQUARE_SIZE

#include "DevilSquareGround.h"
#include "user.h"
#include "..\common\classdef.h"
#include <list>
#include "NewMasterLevelSystem.h"

enum eDevilSquareState
{
	DevilSquare_CLOSE = 0x0,
	DevilSquare_OPEN = 0x1,
	DevilSquare_PLAYING = 0x2,
};

#define MAX_DEVILSQUARE_USER	15


#define DS_MAP_RANGE(map) ( ( ((map)) == MAP_INDEX_DEVILSQUARE  )?TRUE:( ((map)) == MAP_INDEX_DEVILSQUARE2  )?TRUE:FALSE  )
#define DS_LEVEL_RANGE(level) ( ( ((level)) < 0  )?FALSE:( ((level)) > MAX_DEVILSQUARE_GROUND-1  )?FALSE:TRUE)

struct DEVILSQUARE_START_TIME
{
	int m_iHour;	// 0
	int m_iMinute;	// 4
};

class CDevilSquare
{

public:

	CDevilSquare();
	virtual ~CDevilSquare();

	void Init();
	void SetState(enum eDevilSquareState eState);
	enum eDevilSquareState GetState(){return this->m_eState;};
	int Run();
	int CheckCloseTime();
	int GetRemainTime(){return this->m_iRemainTime;}
	void SetMonster();
	void ClearMonstr();
	void gDevilSquareMonsterRegen(LPOBJ lpObj);
	void DieProcDevilSquare(LPOBJ lpObj);
	int gObjMonsterExpSingle(LPOBJ lpObj, LPOBJ lpTargetObj, int dmg, int tot_dmg);
	void gObjExpParty(LPOBJ lpObj, LPOBJ lpTargetObj, int AttackDamage, int MSBFlag);
	void gObjMonsterScoreDivision(LPOBJ lpMonObj, LPOBJ lpObj, int AttackDamage, int MSBFlag);
	void Load(LPSTR filename);
	void CalcScore();
	void SetClose();
	int GetDevilSquareIndex(int iGateNumber);
	int GetUserLevelToEnter(int iUserIndex, int& iMoveGate);

	int GetMonsterSquare(int x, int y, int mapNumber);

private:

	void SetOpen();
	void SetPlaying();
	void ProcClose();
	void ProcOpen();
	void ProcPlaying();
	void SendEventStartMsg();
	void ItemClear();
	void CheckSync();
	void SendLiveCall();
	void gObjScoreClear();
	void CheckInvalidUser();

public:
	enum eDevilSquareState m_eState;	// 4
	DWORD m_iTime;	// 8
	int m_iRemainTime;	// C
	int m_iremainTimeSec;	// 10
	BOOL m_bSendTimeCount;	// 14
	BOOL m_bQuit;	// 18
	BOOL m_bFlag;	// 1C
	UINT m_hThread;	// 20
	std::list<DEVILSQUARE_START_TIME> m_listDevilSquareOpenTime;	// 24
	int m_iCloseTime;	// 24 -> 30
	int m_iOpenTime;	// 28 -> 34
	int m_iPlaytime;	// 2C -> 38

	CDevilSquareGround m_DevilSquareGround[MAX_DEVILSQUARE_GROUND];	// 30 -> 3C
	int m_BonusScoreTable[MAX_TYPE_PLAYER][MAX_DEVILSQUARE_GROUND];	// 1BA8 -> 1BB4
};

extern CDevilSquare g_DevilSquare;

struct EVENT_LEVEL_LIMITATION_EX
{
	int NormalCharacterMinLevel; // Dark Knight, Dark Wizard, Elf
	int NormalCharacterMaxLevel; // Dark Knight, Dark Wizard, Elf
	int SpecialCharacterMinLevel; // Magic Gladiator, Dark Lord
	int SpecialCharacterMaxLevel; // Magic Gladitor, Dark Lord
	int MoveGate;	// Dest Gate
};

static EVENT_LEVEL_LIMITATION_EX g_sttDEVILSQUARE_LEVEL[MAX_DEVILSQUARE_GROUND] =
{
	// Devil Square 1
	15, 130, // DK, DW, Elf
	10, 110, // MG, DL
	58,	// Gate

	// Devil Square 2
	131, 180, // DK, DW, Elf
	111, 160, // MG, DL
	59,	// Gate

	// Devil Square 3
	181, 230, // DK, DW, Elf
	161, 210, // MG, DL
	60,	// Gate

	// Devil Square 4
	231, 280, // DK, DW, Elf
	211, 260, // MG, DL
	61,	// Gate

	// Devil Square 5
	281, 330, // DK, DW, Elf
	261, 310, // MG, DL
	111,	// Gate

	// Devil Square 6
	331, MAX_CHAR_LEVEL, // DK, DW, Elf
	311, MAX_CHAR_LEVEL, // MG, DL
	112,	// Gate

	// Devil Square 7
	15 /*MAX_CHAR_LEVEL*/, MAX_CHAR_LEVEL+MAX_MASTER_LEVEL-1, // DK, DW, Elf
	10 /*MAX_CHAR_LEVEL*/, MAX_CHAR_LEVEL+MAX_MASTER_LEVEL-1, // MG, DL
	270		// Gate
};


unsigned __stdcall DevilSquareThreadFunc(LPVOID p);
void DevilSquareProtocolCore(BYTE protoNum, LPBYTE aRecv, int  aLen);
void DataSendRank(char* pMsg, int size);

#endif