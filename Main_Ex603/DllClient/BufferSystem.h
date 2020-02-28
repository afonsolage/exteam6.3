#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_NPC_BUFFER==TRUE)

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

struct BUFF_DATA
{
	BYTE Index;
	char Name[50];
	char Text[200];
};
// ----------------------------------------------------------------------------------------------

class BufferSystem
{
public:
	void Init();
	void Load();
	void BindImages();
	void GC_OpenWindow();
	void Draw();
	void BuffDraw(int BuffID, int X, int Y);
	void RecvData(GC_BuffNpcOpen* aRecv);
	void ButtonEvent(DWORD Event);
	void CG_SendResult(int id);
	void BindIcon(BYTE Index, char* Name, char* Text);
	void DrawBuffInfoEx(int BuffIndex, float iX, float iY, int iTime);

	int Buff1_Result;
	int Buff1_ZenMoney;
	int Buff1_JewelOfBless;
	int Buff1_JewelOfSoul;
	int Buff1_Bonus;

	int Buff2_Result;
	int Buff2_ZenMoney;
	int Buff2_JewelOfBless;
	int Buff2_JewelOfSoul;
	int Buff2_Bonus;

	int Buff3_Result;
	int Buff3_ZenMoney;
	int Buff3_JewelOfBless;
	int Buff3_JewelOfSoul;
	int Buff3_Bonus;

	int Buff4_Result;
	int Buff4_ZenMoney;
	int Buff4_JewelOfBless;
	int Buff4_JewelOfSoul;
	int Buff4_Bonus;

	int Buff5_Result;
	int Buff5_ZenMoney;
	int Buff5_JewelOfBless;
	int Buff5_JewelOfSoul;
	int Buff5_Bonus;

	int Buff6_Result;
	int Buff6_ZenMoney;
	int Buff6_JewelOfBless;
	int Buff6_JewelOfSoul;
	int Buff6_Bonus;

	int LoadBuffCount;
	BUFF_DATA	DataBuff[MAX_BUFF_INDEX];
};
extern BufferSystem g_BufferSystem;
// ----------------------------------------------------------------------------------------------
#endif