#include "stdafx.h"
#include "ResetSystem.h"
#include "Interface.h"
#include "ExLicense.h"

#if(CUSTOM_RESETSYSTEM)

CResetSystem g_ResetSystem;

CResetSystem::CResetSystem()
{
	this->Init();
}

CResetSystem::~CResetSystem()
{
}

void CResetSystem::Init()
{
	memset(&this->m_reset, 0, sizeof(this->m_reset));
}

void CResetSystem::Load()
{
	this->Init();
}

void CResetSystem::BindImages()
{
	gInterface.BindObject(eRESETSYSTEM_MAIN, 0x7A5A, 222, 303, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_INFOBG, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_INFOBG2, 0x7AA1, 170, 21, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_INFOBG3, 0x7AA1, 170, 21, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_MONEYBG, 0x7A89, 170, 26, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_FINISH, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_COUNT, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(eRESETSYSTEM_TEXT, ex_SMITHY_TEXT, 170, 21, -1, -1);

	//gInterface.BindObject(eGRANDSYSTEM_MAIN, 0x7A5A, 222, 303, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_TITLE, 0x7A63, 230, 67, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_FRAME, 0x7A58, 230, 15, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_FOOTER, 0x7A59, 230, 50, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_DIV, 0x7A62, 223, 21, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_CLOSE, 0x7EC5, 36, 29, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_INFOBG, 0x7AA3, 170, 21, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_INFOBG2, 0x7AA1, 170, 21, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_INFOBG3, 0x7AA1, 170, 21, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_MONEYBG, 0x7A89, 170, 26, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_FINISH, 0x7A5E, 128, 29, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_COUNT, 0x7BAC, 168, 18, -1, -1);
	//gInterface.BindObject(eGRANDSYSTEM_TEXT, ex_SMITHY_TEXT, 170, 21, -1, -1);

	gInterface.Data[eRESETSYSTEM_MAIN].OnShow = false;
	//gInterface.Data[eGRANDSYSTEM_MAIN].OnShow = false;
}

void CResetSystem::DrawReset()
{
	if( !gInterface.Data[eRESETSYSTEM_MAIN].OnShow )
	{	
		return;
	}

	pSetCursorFocus = true;

	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	char szGetItem[150];
	// ----
	gInterface.DrawGUI(eRESETSYSTEM_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eRESETSYSTEM_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eRESETSYSTEM_FRAME, StartX, StartY + 67.0, 13);
	gInterface.DrawGUI(eRESETSYSTEM_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eRESETSYSTEM_CLOSE, StartX + MainWidth - gInterface.Data[eRESETSYSTEM_CLOSE].Width, gInterface.Data[eRESETSYSTEM_TITLE].Height + gInterface.Data[eRESETSYSTEM_CLOSE].Height + 2);
	// ----
	if( gInterface.IsWorkZoneObj(eRESETSYSTEM_CLOSE) )
	{
		DWORD Color = eGray100;
		if( gInterface.Data[eRESETSYSTEM_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUIObj(eRESETSYSTEM_CLOSE, gInterface.Data[eRESETSYSTEM_CLOSE].X, gInterface.Data[eRESETSYSTEM_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eRESETSYSTEM_CLOSE].X + 5, gInterface.Data[eRESETSYSTEM_CLOSE].Y + 25, "Close");
	}
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Reset System");

	RESETSYSTEM_DATA * res = &this->m_reset;

	//Reset Info Start
	gInterface.DrawGUI(eRESETSYSTEM_COUNT, StartX+30 , 127);
	gInterface.DrawFormat(eAncient, StartX + 10, 130, 210, 3, "Reset:  %d", res->Reset);

	// ----

	int CountMissionY = 160;

	gInterface.DrawFormat(eOrange, StartX + 10, CountMissionY - 10, 210, 3, "Need to reset");

	//Need Level
	gInterface.DrawGUI(eRESETSYSTEM_INFOBG, StartX + 30, CountMissionY);
	gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY + 5, 100, 1, "%s:", "Need Level");
	gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY + 5, 100, 3, "%d", res->NeedLevel);
	CountMissionY += 20;

	//Need Money
	gInterface.DrawGUI(eRESETSYSTEM_INFOBG2, StartX + 30, CountMissionY);
	gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY + 5, 100, 1, "Money Zen:");
	gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY + 5, 100, 3, "%d", res->NeedMoney);
	CountMissionY += 20;


	int CountMissionY2 = 260;
	gInterface.DrawGUI(eRESETSYSTEM_DIV, StartX, CountMissionY2);
	CountMissionY2 += 20;
	gInterface.DrawFormat(eOrange, StartX + 10, CountMissionY2, 210, 3, "Reward for reset");
	CountMissionY2 += 10;

	// Reward points
	gInterface.DrawGUI(eRESETSYSTEM_INFOBG, StartX + 30, CountMissionY2);
	gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Points:");
	gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", res->RewardPoint);
	CountMissionY2 += 20;

	// Reward Wcoin
	if(res->AddWcoinC > 0)
	{
		gInterface.DrawGUI(eRESETSYSTEM_INFOBG2, StartX + 30, CountMissionY2);
		gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "WCoin:");
		gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", res->AddWcoinC);
		CountMissionY2 += 20;
	}
	// Reward WCoicP
	if(res->AddWcoinP > 0)
	{
		gInterface.DrawGUI(eRESETSYSTEM_INFOBG3, StartX + 30, CountMissionY2);
		gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "WCoinP:");
		gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", res->AddWcoinP);
		CountMissionY2 += 20;
	}
	// Reward GoblinPoints
	if(res->AddWcoinG > 0)
	{
		gInterface.DrawGUI(eRESETSYSTEM_INFOBG3, StartX + 30, CountMissionY2);
		gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Goblin Points:");
		gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", res->AddWcoinG);
		CountMissionY2 += 20;
	}
	// Reward Credits
	if(res->AddCredits > 0)
	{
		gInterface.DrawGUI(eRESETSYSTEM_INFOBG3, StartX + 30, CountMissionY2);
		gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Credits:");
		gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", res->AddCredits);
		CountMissionY2 += 20;
	}
	//// Reward Item
	//if(res->RewardEnableItem)
	//{
	//	strcpy(szGetItem, this->GetItemString(res->RewardItem, res->RewardLevel, res->RewardSkill, res->RewardLuck, res->RewardOpt, res->RewardExl, res->RewardAnc));
	//	gInterface.DrawGUI(eSMITHY_TEXT, StartX + 30, CountMissionY2);
	//	gInterface.DrawFormat(ItemNameColor, StartX + 30 + 10, CountMissionY2 + 5, 300, 1, szGetItem);
	//}
	// -------------------
	// Reset Info End
	// -------------------
	gInterface.DrawGUI(eRESETSYSTEM_DIV, StartX, gInterface.Data[eRESETSYSTEM_FOOTER].Y - 10);
	
	gInterface.DrawGUI(eRESETSYSTEM_FINISH, ButtonX, gInterface.Data[eRESETSYSTEM_FOOTER].Y + 10);
	gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eRESETSYSTEM_FOOTER].Y + 20, 210, 3, "Reset");
	gInterface.DrawGUI(eRESETSYSTEM_DIV, StartX, gInterface.Data[eRESETSYSTEM_FOOTER].Y - 10);

	if( !this->m_reset.Result )
	{
		gInterface.Data[eRESETSYSTEM_FINISH].Attribute = false;
		gInterface.DrawColoredGUIObj(eRESETSYSTEM_FINISH, gInterface.Data[eRESETSYSTEM_FINISH].X, gInterface.Data[eRESETSYSTEM_FINISH].Y, eGray150);
		return;
	}

	gInterface.Data[eRESETSYSTEM_FINISH].Attribute = true;

	if( gInterface.IsWorkZoneObj(eRESETSYSTEM_FINISH) )
	{
		DWORD Color = eGray100;
		if( gInterface.Data[eRESETSYSTEM_FINISH].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUIObj(eRESETSYSTEM_FINISH, gInterface.Data[eRESETSYSTEM_FINISH].X, gInterface.Data[eRESETSYSTEM_FINISH].Y, Color);
	}
}

void CResetSystem::Button(DWORD Event)
{
	//this->GrandButton(Event);

	if(!gInterface.Data[eRESETSYSTEM_MAIN].OnShow)
	{	
		return;
	}

	if(gInterface.ButtonEx(Event, eRESETSYSTEM_FINISH, false))
	{
		GC_RESET_RESULT pMSg;
		pMSg.h.set((LPBYTE)&pMSg, 0xFB, 0x43, sizeof(pMSg));
		gProtocol.DataSend((LPBYTE)&pMSg, pMSg.h.size);
		gInterface.Data[eRESETSYSTEM_MAIN].OnShow = false;
	}

	if(gInterface.ButtonEx(Event, eRESETSYSTEM_CLOSE, false))
	{
		gInterface.Data[eRESETSYSTEM_MAIN].OnShow = false;
	}
}

void CResetSystem::GCDialogInfo(GC_RESET_DATA* aRecv)
{
	this->m_reset.Result = aRecv->Result;
	this->m_reset.Reset = aRecv->Reset;
	this->m_reset.NeedLevel = aRecv->NeedLevel;
	this->m_reset.NeedMoney = aRecv->NeedMoney;
	this->m_reset.RewardPoint = aRecv->RewardPoint;
	this->m_reset.AddCredits = aRecv->AddCredits;
	this->m_reset.AddWcoinC = aRecv->AddWcoinC;
	this->m_reset.AddWcoinP = aRecv->AddWcoinP;
	this->m_reset.AddWcoinG = aRecv->AddWcoinG;
	this->m_reset.ExFreePoint = aRecv->ExFreePoint;

	gInterface.Data[eRESETSYSTEM_MAIN].OnShow = true;
}
//
//char* CResetSystem::GetItemString(int Item, int Level, bool Skill, bool Luck, bool Opt, bool Exl, bool Anc)
//{
//	char szItem[150];
//	sprintf(szItem, "%s", (char*)(*(DWORD*)0x8128AC0 + 84 * Item));
//
//	char szOptions[64];
//	if(Level)
//	{
//		sprintf(szOptions, "+%d", Level);
//	}
//	if(Skill)
//	{
//		strcat(szOptions,"+Skill");
//	}
//	if(Luck)
//	{
//		strcat(szOptions,"+Luck");
//	}
//	if(Opt)
//	{
//		strcat(szOptions,"+Opt");
//	}
//	if(Exl)
//	{
//		strcat(szOptions,"+Exc");
//	}
//	if(Anc)
//	{
//		strcat(szOptions,"+Anc");
//	}
//
//	char szResult[150];
//	sprintf(szResult, "%s%s", szItem, szOptions);
//
//	return szResult;
//}
//
//void CResetSystem::GCGrandDialogInfo(PMSG_GRAND_DIALOG* lpMsg)
//{
//	this->m_Grand.Result = lpMsg->Result;
//	this->m_Grand.GrandNum = lpMsg->GrandNum;
//	this->m_Grand.GrandMax = lpMsg->GrandMax;
//	this->m_Grand.NeedReset = lpMsg->NeedReset;
//	this->m_Grand.NeedLevel = lpMsg->NeedLevel;
//	this->m_Grand.NeedMoney = lpMsg->NeedMoney;
//	this->m_Grand.RewardPoint = lpMsg->RewardPoint;
//	this->m_Grand.RewardWCoin = lpMsg->RewardWCoin;
//	this->m_Grand.RewardCredit = lpMsg->RewardCredit;
//
//	gInterface.Data[eGRANDSYSTEM_MAIN].OnShow = true;
//}
//
//void CResetSystem::DrawGrand()
//{
//	if( !gInterface.Data[eGRANDSYSTEM_MAIN].OnShow )
//	{	
//		return;
//	}
//
//	pSetCursorFocus = true;
//
//	// ----
//	DWORD ItemNameColor		= eWhite;
//	float MainWidth			= 230.0;
//	float MainHeight		= 313.0;
//	float StartY			= 100.0;
//	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
//	float MainCenter		= StartX + (MainWidth / 3);
//	float ButtonX			= MainCenter - (29.0 / 2);
//	char szGetItem[150];
//	// ----
//	gInterface.DrawGUI(eGRANDSYSTEM_MAIN, StartX, StartY + 2);
//	gInterface.DrawGUI(eGRANDSYSTEM_TITLE, StartX, StartY);
//	StartY = gInterface.DrawRepeatGUI(eGRANDSYSTEM_FRAME, StartX, StartY + 67.0, 13);
//	gInterface.DrawGUI(eGRANDSYSTEM_FOOTER, StartX, StartY);
//	gInterface.DrawGUI(eGRANDSYSTEM_CLOSE, StartX + MainWidth - gInterface.Data[eGRANDSYSTEM_CLOSE].Width, gInterface.Data[eGRANDSYSTEM_TITLE].Height + gInterface.Data[eGRANDSYSTEM_CLOSE].Height + 2);
//	
//	// ----
//	if( gInterface.IsWorkZoneObj(eGRANDSYSTEM_CLOSE) )
//	{
//		DWORD Color = eGray100;
//		if( gInterface.Data[eGRANDSYSTEM_CLOSE].OnClick )
//		{
//			Color = eGray150;
//		}
//		gInterface.DrawColoredGUIObj(eGRANDSYSTEM_CLOSE, gInterface.Data[eGRANDSYSTEM_CLOSE].X, gInterface.Data[eGRANDSYSTEM_CLOSE].Y, Color);
//		gInterface.DrawToolTip(gInterface.Data[eGRANDSYSTEM_CLOSE].X + 5, gInterface.Data[eGRANDSYSTEM_CLOSE].Y + 25, "Close");
//	}
//	// ----
//	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Grand System");
//
//
//	GRANDSYSTEM_DATA * pGrand = &this->m_Grand;
//
//	//Reset Info Start
//	gInterface.DrawGUI(eGRANDSYSTEM_COUNT, StartX+30 , 127);
//	gInterface.DrawFormat(eAncient, StartX + 10, 130, 210, 3, "Grand:  %d / %d", pGrand->GrandNum , pGrand->GrandMax);
//
//	// ----
//
//	int CountMissionY = 160;
//
//	gInterface.DrawFormat(eOrange, StartX + 10, CountMissionY - 10, 210, 3, "Need to Grand");
//
//	//Need Level
//	gInterface.DrawGUI(eGRANDSYSTEM_INFOBG, StartX + 30, CountMissionY);
//	gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY + 5, 100, 1, "%s:", "Need Level");
//	gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY + 5, 100, 3, "%d", pGrand->NeedLevel);
//	CountMissionY += 20;
//
//	//Need Reset
//	gInterface.DrawGUI(eGRANDSYSTEM_INFOBG, StartX + 30, CountMissionY);
//	gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY + 5, 100, 1, "%s:", "Need Reset");
//	gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY + 5, 100, 3, "%d", pGrand->NeedReset);
//	CountMissionY += 20;
//
//	//Need Money
//	gInterface.DrawGUI(eGRANDSYSTEM_INFOBG2, StartX + 30, CountMissionY);
//	gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY + 5, 100, 1, "Money Zen:");
//	gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY + 5, 100, 3, "%d", pGrand->NeedMoney);
//	CountMissionY += 20;
//
//	//Need Items
//	/*if(res->AddEnableItem)
//	{
//		strcpy(szGetItem, this->GetItemString(res->AddItem, res->AddItemLevel, res->AddItemSkill, res->AddItemLuck, res->AddItemOpt, res->AddItemExl, res->AddItemAnc));
//		gInterface.DrawGUI(eSMITHY_TEXT, StartX + 30, CountMissionY);
//		gInterface.DrawFormat(ItemNameColor, StartX + 30 + 5, CountMissionY + 5, 300, 1, "%s / %d", szGetItem, res->AddItemCount);
//		CountMissionY += 20;
//	}*/
//
//	int CountMissionY2 = 260;
//	gInterface.DrawGUI(eGRANDSYSTEM_DIV, StartX, CountMissionY2);
//	CountMissionY2 += 20;
//	gInterface.DrawFormat(eOrange, StartX + 10, CountMissionY2, 210, 3, "Reward for grand");
//	CountMissionY2 += 10;
//
//	// Reward points
//	gInterface.DrawGUI(eGRANDSYSTEM_INFOBG, StartX + 30, CountMissionY2);
//	gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Points:");
//	gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", pGrand->RewardPoint);
//	CountMissionY2 += 20;
//
//	// Reward Wcoin
//	if(pGrand->RewardWCoin)
//	{
//		gInterface.DrawGUI(eGRANDSYSTEM_INFOBG2, StartX + 30, CountMissionY2);
//		gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "WCoin:");
//		gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", pGrand->RewardWCoin);
//		CountMissionY2 += 20;
//	}
//
//	// Reward Credit
//	if(pGrand->RewardCredit)
//	{
//		if(g_ExLicense.CheckUser(eExUB::NSGames))
//		{
//			gInterface.DrawGUI(eGRANDSYSTEM_INFOBG2, StartX + 30, CountMissionY2);
//			gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "NSPoint:");
//			gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", pGrand->RewardCredit);
//			CountMissionY2 += 20;
//		}
//		else
//		{
//			gInterface.DrawGUI(eGRANDSYSTEM_INFOBG2, StartX + 30, CountMissionY2);
//			gInterface.DrawFormat(eWhite, StartX + 30 + 5, CountMissionY2 + 5, 100, 1, "Credit:");
//			gInterface.DrawFormat(eGold, StartX + 30 + 70, CountMissionY2 + 5, 100, 3, "%d", pGrand->RewardCredit);
//			CountMissionY2 += 20;
//		}
//	}
//
//
//	// Reward Item
//	/*if(res->RewardEnableItem)
//	{
//		strcpy(szGetItem, this->GetItemString(res->RewardItem, res->RewardLevel, res->RewardSkill, res->RewardLuck, res->RewardOpt, res->RewardExl, res->RewardAnc));
//		gInterface.DrawGUI(eSMITHY_TEXT, StartX + 30, CountMissionY2);
//		gInterface.DrawFormat(ItemNameColor, StartX + 30 + 10, CountMissionY2 + 5, 300, 1, szGetItem);
//	}*/
//	
//	// -------------------
//	// Reset Info End
//	// -------------------
//	gInterface.DrawGUI(eGRANDSYSTEM_DIV, StartX, gInterface.Data[eGRANDSYSTEM_FOOTER].Y - 10);
//	
//	gInterface.DrawGUI(eGRANDSYSTEM_FINISH, ButtonX, gInterface.Data[eGRANDSYSTEM_FOOTER].Y + 10);
//	gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eGRANDSYSTEM_FOOTER].Y + 20, 210, 3, "Grand reset");
//	gInterface.DrawGUI(eGRANDSYSTEM_DIV, StartX, gInterface.Data[eGRANDSYSTEM_FOOTER].Y - 10);
//
//	if( !this->m_Grand.Result )
//	{
//		gInterface.Data[eGRANDSYSTEM_FINISH].Attribute = false;
//		gInterface.DrawColoredGUIObj(eGRANDSYSTEM_FINISH, gInterface.Data[eGRANDSYSTEM_FINISH].X, gInterface.Data[eGRANDSYSTEM_FINISH].Y, eGray150);
//		return;
//	}
//
//	gInterface.Data[eGRANDSYSTEM_FINISH].Attribute = true;
//
//	if( gInterface.IsWorkZoneObj(eGRANDSYSTEM_FINISH) )
//	{
//		DWORD Color = eGray100;
//		if( gInterface.Data[eGRANDSYSTEM_FINISH].OnClick )
//		{
//			Color = eGray150;
//		}
//		gInterface.DrawColoredGUIObj(eGRANDSYSTEM_FINISH, gInterface.Data[eGRANDSYSTEM_FINISH].X, gInterface.Data[eGRANDSYSTEM_FINISH].Y, Color);
//	}
//}
//
//void CResetSystem::GrandButton(DWORD Event)
//{
//	if( !gInterface.Data[eGRANDSYSTEM_MAIN].OnShow )
//	{	
//		return;
//	}
//
//	if(gInterface.ButtonEx(Event, eGRANDSYSTEM_FINISH, false))
//	{
//		GC_RESET_RESULT pMSg;
//		pMSg.h.set((LPBYTE)&pMSg, 0xFB, 0xA2, sizeof(pMSg));
//		gProtocol.DataSend((LPBYTE)&pMSg, pMSg.h.size);
//		gInterface.Data[eGRANDSYSTEM_MAIN].OnShow = false;
//	}
//
//	if(gInterface.ButtonEx(Event, eGRANDSYSTEM_CLOSE, false))
//	{
//		gInterface.Data[eGRANDSYSTEM_MAIN].OnShow = false;
//	}
//}

#endif