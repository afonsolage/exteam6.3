#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\\include\\prodef.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PKCLEAR_NPC==TRUE)

struct GC_PKCLEAR_PRICE
{
	PBMSG_HEAD2 h;
	BYTE Result;
	WORD PkLevel;
	DWORD Zen;
	WORD Chaos;
	WORD Bless;
	WORD Soul;
};
// ----------------------------------------------------------------------------------------------

struct CG_PKCLEAR_RESULT
{
	PBMSG_HEAD2 h;
	BYTE Result;
};
// ----------------------------------------------------------------------------------------------

class PKClear
{
public:
	void Init();
	void Load();
	void Read(char* File);

	bool NPCDialog(int aIndex, int aNPCIndex);
	void GC_Price(int aIndex);
	void CG_ResultRecv(int aIndex, CG_PKCLEAR_RESULT* aRecv);
	bool Check(int aIndex, int &iZen);

	bool Enable;

	int NPC_Class;
	int NPC_Map;
	int NPC_X;
	int NPC_Y;

	int ZenFormula;
	int ZenMoney;
	int JewelOfChaos;
	int JewelOfBless;
	int JewelOfSoul;
};
extern PKClear g_PKClear;
// ----------------------------------------------------------------------------------------------
#endif