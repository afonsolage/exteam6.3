#pragma once

#if(CUSTOM_LOTTERY)

#include "..\include\prodef.h"

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

struct LOTTERY_INFO
{
	int ID;
	LOTTERY_DATA Info[10];
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
	void Read(char* filename);
	bool NpcDialog(int aIndex, int aNpcIndex);
	int LotteryRand(int aIndex, int RandNum);
	void LotteryWin(int aIndex, int RandNum);

	void CGLotteryOpen(int aIndex);
	void GCLotteryData(int aIndex);
	void CGLotteryPlay(PMSG_LOTTERY_PLAY* lpMsg, int aIndex);
	void GCLotteryResult(int aIndex, int Result);
	


	int m_Enable;
	int m_ID;
	int m_Price;
	int m_Fund;

	int m_NpcClass;
	int m_NpcMap;
	int m_NpcX;
	int m_NpcY;

	std::vector<LOTTERY_INFO> m_Data;

};

extern CLottery g_Lottery;

#endif