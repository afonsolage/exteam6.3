#pragma once
// ----------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "Protocol.h"
#include "Defines.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PERONAL_EX==TRUE)

#define DEV_PERSONAL_CREDIT	1

#define sub_6684E0			((int(__cdecl*)(char a1, char a2, int a3)) 0x6684E0)
#define sub_790950			((int(__cdecl*)()) 0x790950)	//itempos navodyawego
#define sub_668930			((int(__thiscall*)(LPVOID This)) 0x668930)
#define sub_6D6AD0			((int(__cdecl*)(int a1, int a2, int a3)) 0x6D6AD0)
#define sub_8248E0			((LPVOID(__cdecl*)()) 0x8248E0)
#define sub_824B30			((int(__thiscall*)(LPVOID This, int a2, int a3)) 0x824B30)
#define sub_8612B0			((int(__thiscall*)(LPVOID This)) 0x8612B0)
#define sub_668720			((int(__thiscall*)(LPVOID This)) 0x668720)
#define sub_842440			((int(__thiscall*)(LPVOID This, char a2)) 0x842440)
#define sub_860FC0			((LPVOID(*)()) 0x860FC0)	
#define sub_7DCFA0			((int(__cdecl*)()) 0x7DCFA0)	
#define sub_7D92E0			((int(__thiscall*)(LPVOID This)) 0x7D92E0)
#define sub_840DF0			((int(__thiscall*)(LPVOID This, int a2)) 0x840DF0)
#define sub_58E3B0			((signed int(__cdecl*)(int a1, int a2)) 0x58E3B0)
#define sub_841200			((char(__thiscall*)(LPVOID This)) 0x841200)
#define sub_7D9390			((int(__thiscall*)(LPVOID This)) 0x7D9390)
#define sub_6688B0			((int(__thiscall*)(LPVOID This)) 0x6688B0)
#define sub_7D92C0			((int(__thiscall*)(LPVOID This)) 0x7D92C0)
#define sub_861110			((int(__thiscall*)(LPVOID This)) 0x861110)
#define sub_83C5C0			((int(__thiscall*)(LPVOID This, int a2)) 0x83C5C0)
#define sub_668700			((int(__thiscall*)(LPVOID This)) 0x668700)
#define sub_5BD850			((char(__cdecl*)(char a1, char a2, int a3, char a4, char a5)) 0x5BD850)
#define sub_83C330			((int(__stdcall*)(int a1, int a2)) 0x83C330)
#define sub_8612D0			((int(__thiscall*)(LPVOID This)) 0x8612D0)
#define sub_668930			((int(__thiscall*)(LPVOID This)) 0x668930)
// ----------------------------------------------------------------------------------------------

//#define PERSONAL_BONUS	FALSE
//#if(PERSONAL_BONUS == TRUE)
//#define TOTAL_PRICE		6
//#else
//#define TOTAL_PRICE		5
//#endif
// ----------------------------------------------------------------------------------------------

enum PSValue
{
	ePSzen = 1,
	ePSBonus,
	ePSBless,
	ePSSoul,
	ePSChaos,
	ePSLife,
	#if(DEV_PERSONAL_CREDIT)
	ePSCredit,
	#endif
};
// ----------------------------------------------------------------------------------------------

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

struct PMSG_REQ_BUYLIST_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
};
// ----------------------------------------------------------------------------------------------

struct PMSG_ANS_BUYLIST_FROM_PSHOP
{
	PWMSG_HEAD2 h;
	BYTE Result;
	BYTE NumberH;
	BYTE NumberL;
	BYTE btName[10];
	char szPShopText[36];
	BYTE btCount;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_REQ_BUYITEM_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
	BYTE btItemPos;	// 10
};
// ----------------------------------------------------------------------------------------------

struct PMSG_REQ_PSHOP_SETITEMPRICE
{
	PBMSG_HEAD2 h;
	BYTE btItemPos;	// 4
	BYTE sItemPrice1;	// 5
	BYTE sItemPrice2;	// 6
	BYTE sItemPrice3;	// 7
	BYTE sItemPrice4;	// 8
};

struct PMSG_REQ_PSHOP_SETITEMPRICE_EX
{
	PBMSG_HEAD2 h;
	BYTE btItemPos;		// 4
	BYTE sItemPrice1;	// 5
	BYTE sItemPrice2;	// 6
	BYTE sItemPrice3;	// 7
	BYTE sItemPrice4;	// 8
	BYTE sBonusPrice1;	// 5
	BYTE sBonusPrice2;	// 6
	BYTE sBonusPrice3;	// 7
	BYTE sBonusPrice4;	// 8
	BYTE sBlessCnt1;	// 9
	BYTE sBlessCnt2;	// A
	BYTE sSoulCnt1;		// B
	BYTE sSoulCnt2;		// C
	BYTE sChaosCnt1;	// D
	BYTE sChaosCnt2;	// E
	BYTE sLifeCnt1;	// D
	BYTE sLifeCnt2;	// E
	#if(DEV_PERSONAL_CREDIT)
	BYTE sCreditPrice1;	// 5
	BYTE sCreditPrice2;	// 6
	BYTE sCreditPrice3;	// 7
	BYTE sCreditPrice4;	// 8
	#endif
};
// ----------------------------------------------------------------------------------------------

struct PMSG_BUYLIST_FROM_PSHOP_EX
{
	BYTE Pos;	// 0
	BYTE ItemInfo[MAX_ITEM_INFO];	// 1
	int PShopItemValue;	// 8
	short PShopBlessValue;
	short PShopSoulValue;
	short PShopChaosValue;
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

struct PMSG_ANS_PSHOP_SETITEMPRICE
{
	PBMSG_HEAD2 h;
	BYTE btResult;
	BYTE btItemPos;
};
// ----------------------------------------------------------------------------------------------

struct PersonalShop_DATA
{
	WORD aIndex;
	char Name[11];
	char PersonalText[36];
	BYTE Value;
};
// ----------------------------------------------------------------------------------------------

struct PersonalInvenory_DATA
{
	bool Item;
	int Zen;	// 8
	int Bonus;
	short Bless;
	short Soul;
	short Chaos;
	short Life;
	#if(DEV_PERSONAL_CREDIT)
	int Credit;
	#endif
};
// ----------------------------------------------------------------------------------------------

class PersonalShopEx
{
public:
	// -> Load
	void Init();
	void Load();
	void LoadImages();
	void BindImages();
	// Draw Interface
	void Draw();
	void DrawPrice();
	// -> Controller
	void Button(DWORD Event);
	void ButtonPrice(DWORD Event);
	void Key(DWORD Event);
	// -> Protocol
	void GC_Recv(LPBYTE aRecv);
	void CG_Send();
	void GC_PSRecv(PMSG_ANS_BUYLIST_FROM_PSHOP* aRecv);
	void GC_RecvUpdatePSInvValue(LPBYTE aRecv);
	void GC_RecvUpdatePSInvTargetValue(LPBYTE aRecv);
	void GC_ResultPrice(PMSG_ANS_PSHOP_SETITEMPRICE* aRecv);
	// -> Hook
	static char _CD RightClickItemPersonalStore(LPVOID a1);
	static char _CD GetPSItemPos(int a1, int a2, int a3);
	static char _CD CheckPersonalPrice();
	static void ShowPrice(DWORD a1, const char *a2, char *Price);
	// -> Other
	void PriceInvenory(int itempos, int zen, int bonus, short bless, short soul, short chaos, short life, int credit);
	void PriceInvTarget(int itempos, int zen, int bonus, short bless, short soul, short chaos, short life, int credit);
	void SendPrice(int itempos, int zen, int bonus, short bless, short soul, short chaos, short life, int credit);
	void PStorePrice();
	int ReturnPos();

	int Page;
	int TotalShop;
	int aTargetIndex;
	char TargetName[11];
	int ActivePrice;
	char ZenText[10];
	char BonusText[10];
	char BlessText[10];
	char SoulText[10];
	char ChaosText[10];
	char LifeText[10];
	#if(DEV_PERSONAL_CREDIT)
	char CreditText[10];
	#endif
	int ItemShowPos;
	int TotalPrice;
	#if(DEV_PERSONAL_CREDIT)
	bool bDPrice[7];
	#else
	bool bDPrice[6];
	#endif
	int PriceBek;

	PersonalShop_DATA PShop[10];
	PersonalInvenory_DATA PSInvetrory[32];
	PersonalInvenory_DATA PSInvTarget[32];

	bool ACTIVE;
	int iPERSONAL_BONUS;
	int iPERSONAL_CREDIT;
};
extern PersonalShopEx g_PersonalShopEx;
// ----------------------------------------------------------------------------------------------

#endif