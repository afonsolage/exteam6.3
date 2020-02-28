#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"

#define CR_DONATE_DIR	"..\\Data\\ExData\\CreditDonate.ini"

#define MAX_DONATE_ITEM 2000

struct DONATE_ITEM
{
	char cmd[50];
	int Type;
	int Index;
	int Level;
	int Skill;
	int Luck;
	int Opt;
	int Exl;
	int Anc;
	int CrPrice;
};

struct PMSG_CG_CHANGECLASS
{
	PBMSG_HEAD2 h;
	BYTE iNewClass;
	BYTE PriceType;
};

struct PMSG_GC_CHANGECLASS_CONFIG
{
	PBMSG_HEAD2 h;
	int iChangeClassWcoinPrice;
	int iChangeClassCreditPrice;
};

class cCreditDonate
{
public:
	void Load();
	void Chat(int aIndex, char* Message, int Count);
	bool Sell(int aIndex, int Pos, int &iAddZen);

	int  SetItemCount(int Type);
	void exClass(int aIndex, char* Message);
	void GCChangeClassConfig(int aIndex);
	void CGChangeClass(PMSG_CG_CHANGECLASS* aRecv, int aIndex);
	int GetClassID(int aIndex, int NewClass);

//private:
	bool Enable;
	int SellProcent;

	bool BuyWcoinC;
	bool BuyWcoinP;
	bool BuyGoblin;
	bool BuyPremium;

	bool ChangeClass;
	int  ChangeCredit;
	int  ChangeWCoin;

	DONATE_ITEM Donate[MAX_DONATE_ITEM];

	int Count;

	int premium_price_1;
	int premium_price_7;
	int premium_price_30;

	// -> Evo
	int m_MinResetChange;
	int m_MinGrandChange;
	int m_ActiveDivResetChange;
	int m_MinusDivResetChange;
	int m_ActiveDivGrandChange;
	int m_MinusDivGrandChange;
	int m_StartDayChange;
	int m_EndDayChange;

};
extern cCreditDonate gCreditDonate;
