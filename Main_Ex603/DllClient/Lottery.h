#pragma once

#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_LOTTERY)

#define MAX_LOTERRY_NUM	10

enum
{
	eLOTTERY_FUND_MAIN,
	eLOTTERY_ZEN,
	eLOTTERY_WCOINC,
	eLOTTERY_WCOINP,
	eLOTTERY_GOBLIN,
	eLOTTERY_CREDIT,
	eLOTTERY_ITEM,
	eLOTTERY_FOND_PERCENT,
};

struct LOTTERY_DATA
{
	int Type;
	int Value;
	int Index;
	int Level;
	int Rate;
};

struct PMSG_LOTTERY_DATA
{
	PBMSG_HEAD2 h;
	LOTTERY_DATA Data[10];
};

struct PMSG_LOTTERY_PLAY
{
	PBMSG_HEAD2 h;
	int Result;
};

struct PMSG_LOTTERY_RESULT
{
	PBMSG_HEAD2 h;
	int Result;
};

class CLottery
{
public:
		CLottery();
		~CLottery();

	void Init();
	void Load();
	void LoadIMG();
	void BindIMG();
	void DrawMain();
	void DrawMain2();
	void Button(DWORD Event);
	char* GetRewardText(int Number);
	void DrawItem(int Type, int Index, int Level);
	void ClearDraw();

	void CGLotteryOpen(int aIndex);
	void GCLotteryData(PMSG_LOTTERY_DATA* lpMsg);
	void CGLotteryPlay();
	void GCLotteryResult(PMSG_LOTTERY_RESULT* lpMsg);

	int m_Slot[MAX_LOTERRY_NUM];
	LOTTERY_DATA m_Data[MAX_LOTERRY_NUM];

	int m_RandomNumber;
	int m_SelectNumber;
	
};

extern CLottery g_Lottery;

#endif