#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\\common\\winutil.h"

#if(CUSTOM_NPC_BUFFER==TRUE)
// ----------------------------------------------------------------------------------------------

enum eBufferPrice
{
	ebufferZen = 1,
	ebufferBless = 2,
	ebufferSoul = 3,
	ebufferBonus = 4,
};
// ----------------------------------------------------------------------------------------------

struct GC_BuffNpcOpen
{
	PBMSG_HEAD2 h;
	BYTE Result1;
	DWORD Zen1;
	WORD Bless1;
	WORD Soul1;
	WORD Bonus1;
	BYTE Result2;
	DWORD Zen2;
	WORD Bless2;
	WORD Soul2;
	WORD Bonus2;
	BYTE Result3;
	DWORD Zen3;
	WORD Bless3;
	WORD Soul3;
	WORD Bonus3;
	BYTE Result4;
	DWORD Zen4;
	WORD Bless4;
	WORD Soul4;
	WORD Bonus4;
	BYTE Result5;
	DWORD Zen5;
	WORD Bless5;
	WORD Soul5;
	WORD Bonus5;
	BYTE Result6;
	DWORD Zen6;
	WORD Bless6;
	WORD Soul6;
	WORD Bonus6;
};
// ----------------------------------------------------------------------------------------------

struct CG_BuffNpcResult
{
	PBMSG_HEAD2 h;
	BYTE Result;
};
// ----------------------------------------------------------------------------------------------

struct GD_BUFFERSYSTEM_LOAD
{
	PBMSG_HEAD2 h;
	bool Result;
};

class BufferSystem
{
public:
	void Init();
	void Load();
	void Read(char* File);
	bool Dialog(int aIndex, int aNpcIndex);
	void GC_OpenWindow(int aIndex);
	bool Check(int aIndex, int type);
	void CG_ResultRecv(int aIndex, CG_BuffNpcResult* aRecv);
	void Timer(int aIndex);
	void UserConnect(int aIndex);

	void DBLoad();
	void DBSave();

	bool Enable;
	int NPC_Class;
	int NPC_Map;
	int NPC_X;
	int NPC_Y;

	int Buff1_ZenMoney;
	int Buff1_JewelOfBless;
	int Buff1_JewelOfSoul;
	int Buff1_Bonus;

	int Buff2_ZenMoney;
	int Buff2_JewelOfBless;
	int Buff2_JewelOfSoul;
	int Buff2_Bonus;

	int Buff3_ZenMoney;
	int Buff3_JewelOfBless;
	int Buff3_JewelOfSoul;
	int Buff3_Bonus;

	int Buff4_ZenMoney;
	int Buff4_JewelOfBless;
	int Buff4_JewelOfSoul;
	int Buff4_Bonus;

	int Buff5_ZenMoney;
	int Buff5_JewelOfBless;
	int Buff5_JewelOfSoul;
	int Buff5_Bonus;

	int Buff6_ZenMoney;
	int Buff6_JewelOfBless;
	int Buff6_JewelOfSoul;
	int Buff6_Bonus;

};
extern BufferSystem g_BufferSystem;
// ----------------------------------------------------------------------------------------------
#endif