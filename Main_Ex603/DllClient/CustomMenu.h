#pragma once

#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_MENU)

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

struct PMSG_RESET_RESULT
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

class CCustomMenu
{
public:

		 CCustomMenu();
		 ~CCustomMenu();
	void Init();
	void Load();
	void BindImages();
	void DrawMain();
	void Button(DWORD Event);

	void DrawChangeClass();
	void CGChangeClass(BYTE iClass);
	void GCChangeClassConfig(PMSG_GC_CHANGECLASS_CONFIG* aRecv);

	void CGResetMenu();
	void CGGrandMenu();

	int  iChangeClassWcoinPrice;
	int  iChangeClassCreditPrice;
	bool  bChangeClassWcoinActive;
	bool  bChangeClassCreditActive;


};
extern CCustomMenu g_CustomMenu;
//priem paketa s nastroikami
// kod servera
#endif