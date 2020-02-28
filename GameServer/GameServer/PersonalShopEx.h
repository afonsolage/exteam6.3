#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\include\prodef.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PERSONAL_SHOP==TRUE)

#define DEV_PERSONAL_CREDIT	1

struct GC_PersonalShopInfo
{
	WORD aIndex;
	char Name[11];
	char PersonalText[36];
	BYTE Value;
};
// ----------------------------------------------------------------------------------------------

struct CG_PersonalPage
{
	PBMSG_HEAD2 h;
	BYTE Page;
};
// ----------------------------------------------------------------------------------------------

struct GC_PSInventoryValue
{
	WORD ItemPos;
	DWORD Zen;
	DWORD Bonus;
	WORD Bless;
	WORD Soul;
	WORD Chaos;
	WORD Life;
	#if(DEV_PERSONAL_CREDIT)
	DWORD Credit;
	#endif
};
// ----------------------------------------------------------------------------------------------

class PersonalShopEx
{
public:
	void Init();
	void Load();
	void Read(char* File);

	bool NPC_Dialog(int aIndex, int aIndexNPC);
	
	void Search(int aIndex, CG_PersonalPage* aRecv);
	void UpdatePSInventoryUser(int aIndex);
	void UpdatePSInventoryTarget(int aIndex, int aTargetIndex);
	int GetMoney(int aIndex, int Pos);
	bool CheckPrice(int Zen, int Bonus, int Bless, int Soul, int Chaos, int Life, int Credit);
	bool PShop_CheckInventoryPrice(short aIndex);

	bool Enable;
	int NPC_CLASS;
	int NPC_MAP;
	int NPC_X;
	int NPC_Y;

	int BonusPrice;
	int CreditPrice;
};
extern PersonalShopEx g_PersonalShopEx;
// ----------------------------------------------------------------------------------------------
#endif