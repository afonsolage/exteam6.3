#pragma once

#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_RESETSYSTEM)

struct GC_RESET_DATA
{
	PBMSG_HEAD2	h;
	BYTE Result;
	WORD Reset;
	WORD NeedLevel;
	DWORD NeedMoney;
	DWORD RewardPoint;
	WORD AddCredits;
	WORD AddWcoinC;
	WORD AddWcoinP;
	WORD AddWcoinG;
	DWORD ExFreePoint;
};

struct RESETSYSTEM_DATA
{
	BYTE Result;
	WORD Reset;
	WORD NeedLevel;
	DWORD NeedMoney;
	DWORD RewardPoint;
	WORD AddCredits;
	WORD AddWcoinC;
	WORD AddWcoinP;
	WORD AddWcoinG;
	DWORD ExFreePoint;
};

struct GC_RESET_RESULT
{
	PBMSG_HEAD2	h;
};

class CResetSystem
{
public:
		 CResetSystem();
		 ~CResetSystem();

	void Init();
	void Load();
	void BindImages();
	void DrawReset();
	void Button(DWORD Event);
	void GCDialogInfo(GC_RESET_DATA* aRecv);
	char* GetItemString(int Item, int Level, bool Skill, bool Luck, bool Opt, bool Exl, bool Anc);

	//void GCGrandDialogInfo(PMSG_GRAND_DIALOG* lpMsg);
	//void DrawGrand();
	//void GrandButton(DWORD Event);


	RESETSYSTEM_DATA m_reset;
	//GRANDSYSTEM_DATA m_Grand;

};
extern CResetSystem g_ResetSystem;

#endif