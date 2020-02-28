#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
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
	void BindImages();

	void GC_Price(GC_PKCLEAR_PRICE* aRecv);
	void CG_Result();

	void Draw();
	void EventButton(DWORD Event);

	int Result;
	int PKLevel;
	int Zen;
	int JewelOfChaos;
	int JewelOfBless;
	int JewelOfSoul;
};
extern PKClear g_PKClear;
// ----------------------------------------------------------------------------------------------
#endif