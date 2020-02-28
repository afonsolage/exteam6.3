#include "stdafx.h"
#include "ExMenu.h"
#include "Interface.h"
#include "ExFunction.h"
#include "Controller.h"
#include "Camera.h"
#include "JewelsBank.h"
#include "Graphics.h"
#include "NewHpBar.h"
#include "QuestSystem.h"
#include "RageSystem.h"
#include "DataSend.h"
#include "Configs.h"
#include "AutoParty.h"
#include "Ranking.h"
#include "EventTimer.h"
#include "NewParty.h"
#include "PartySearch.h"
#include "Console.h"
#include "ExLicense.h"
#include "Smithy.h"
#include "ExText.h"
#include "ReferralSystem.h"
#include "ExMenuV3.h"

ExMenu gExMenu;

ExMenu::ExMenu()
{
	this->mWidth = 20;
	this->mHigh = 16;
	this->bWidth = 20;
	this->bHigh = 12;	
	this->StartX = 0;
	this->StartY = 0;
	this->DrawX = 620;
	this->DrawY = 0;
	this->ClickTime = 0;
	this->statX = 620;
	this->bPlusX = false;
	this->iStatus = 0;
	this->MoveStartX = 620;
}

void ExMenu::Load()
{
	gInterface.LoadImages("Custom\\Interface\\Menu\\rama.tga", 100050, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\CameraUI_Reset.tga", 100051, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\CameraUI_Switch.tga", 100052, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\JewelsBank.tga", 100053, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Glow.tga", 100054, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Party.tga", 100055, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\User.tga", 100056, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Monster.tga", 100057, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Right.tga", 100058, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Left.tga", 100059, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Rage.tga", 100060, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Quest.tga", 100061, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Qarch.tga", 100062, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\OffAfk.tga", 100063, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\AutoParty.tga", 100064, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\top100.tga", 100065, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\top100.tga", 100065, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Event.tga", 100066, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Party_On.tga", 100067, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Party_Off.tga", 100068, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\AutoParty2.tga", 100069, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Smith.tga", 100070, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Custom.tga", 100071, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Reset.tga", 100072, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Grand.tga", 100073, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\Menu\\Smith.tga", 100074, 0x2601, 0x2900, 1);
}

void ExMenu::MoveX()
{
	this->countX = 0;
	//3d Camera Restart
	//-----------------
	this->countX++;
	//3d Camera Switch
	//-----------------
	this->countX++;
	//Jewels Bank
	//-----------------
	this->countX++;
	//Glow Effect Grafics
	//-----------------
	this->countX++;
	//Party HP Bar
	//-----------------
	this->countX++;
	//User HP Bar
	//-----------------
	this->countX++;
	//Monster HP Bar
	//-----------------
	this->countX++;
	//Rage System
	//-----------------
	if(gRAGESYSTEM)
	{
		this->countX++;
	}
	//Quest
	//-----------------
	if(gWINQUEST)
	{
		this->countX++;
	//Quest Options System
	//-----------------
		this->countX++;
	}
	//OffAfk
	//-----------------
	this->countX++;
	//Top 100 List
	//-----------------
	if(gRanking.Active)
	{
		this->countX++;
	}
	//Events
	//-----------------
	if(gEventTimer.Active)
	{
		this->countX++;
	}
	//PT Menu
	//-----------------
#if _NEW_PARTY_SYSTEM_ == TRUE
	if(gPARTY_SYSTEM)
	{
		if(g_Party.PartyMemberCount > 0)
		{
			this->countX++;
		}
	}
#endif
	//Party Search
	//-----------------
#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		this->countX++;
	}
#endif
	//Auto Party List
	//-----------------
#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		this->countX++;
	}
	else
#endif
	{
		if(gAutoParty.Active)
		{
			this->countX++;
		}
	}

	if(g_ExLicense.user.Smithy == true)
	{
		this->countX++;
	}

#if(CUSTOM_REFERAL_SYSTEM)
	this->countX++;
#endif

	if(g_ExLicense.CheckUser(eExUB::Local) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
		THINNAKORN_MAC == 1 ||
		g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		this->countX++;
	}

	this->MenuWidth = this->bWidth * this->countX;

	if(this->iStatus == 1)
	{
		if(this->bPlusX == true)
		{
			this->DrawX += this->MenuWidth;
			this->bPlusX = false;
		}
		if(this->DrawX > this->MoveStartX)
		{
			this->DrawX -= 20;
			if(this->DrawX <=  this->MoveStartX)
			{
				this->DrawX = this->MoveStartX;
				this->iStatus = 2;
			}
		}
	}
	else if(this->iStatus == 3)
	{
		if(this->DrawX < this->MoveStartX + this->MenuWidth)
		{
			this->DrawX += 20;
			if(this->DrawX >= this->MoveStartX + this->MenuWidth)
			{
				this->iStatus = 0;
				this->DrawX = this->MoveStartX;
			}
		}
	}
}

void ExMenu::Draw()
{
	if(g_ExLicense.m_ExMenuV2)
	{
		return;
	}

	#if(DEV_EXMENU_V3)
	if(g_ExMenuV3.m_Enable)
	{
		return;
	}
	#endif

	//-----------------------------------------
	this->MoveX();
	//-----------------------------------------

	int PosX = this->DrawX;
	int PosY = this->DrawY;

	DWORD Delay = (GetTickCount() - this->ClickTime);

	if(CursorZoneButton(StartX, DrawY, 640, mWidth))
	{
		pSetCursorFocus = true;
	}
	else
	{
		pSetCursorFocus = false;
	}

	PosX -= mWidth;

	// Check Status
	//-----------------
	if(!this->iStatus)
	{
		pDrawGUI(100050, this->statX, PosY, mWidth, mHigh);

		int BottonX = this->statX + 2;
		int BottonY = PosY + 1;

		int ButtonXEnd = BottonX + bWidth-1;
		int ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100059, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				this->bPlusX = true;
				this->iStatus = 1;
			}
			gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(0));
			pDrawColorButton(100059, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		StartX = PosX;
		return;
	}

	//3d Camera Restart
	//-----------------

	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	int BottonX = PosX + 2;
	int BottonY = PosY + 1;

	int ButtonXEnd = BottonX + bWidth-1;
	int ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100051, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();
			gCamera.Init();
		}
		if(this->iStatus != 1 && this->iStatus != 3)
		gInterface.DrawToolTip(BottonX-50, BottonY+20, g_ExText.GetText(1));
		pDrawColorButton(100051, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	PosX -= mWidth; 

	//3d Camera Switch
	//-----------------

	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	BottonX = PosX + 2;
	BottonY = PosY + 1;

	ButtonXEnd = BottonX + bWidth-1;
	ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100052, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();
			gCamera.Switch();
		}
		if(this->iStatus != 1 && this->iStatus != 3)
		gInterface.DrawToolTip(BottonX-50, BottonY+20, g_ExText.GetText(2));
		pDrawColorButton(100052, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}
	else if(gCamera.IsActive)
	{
		pDrawColorButton(100052, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	PosX -= mWidth;

	//Jewels Bank
	//-----------------

	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	BottonX = PosX + 2;
	BottonY = PosY + 1;

	ButtonXEnd = BottonX + bWidth-1;
	ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100053, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();
			gJewelsBank.Active = !gJewelsBank.Active;
		}
		if(this->iStatus != 1 && this->iStatus != 3)
		gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(3));
		pDrawColorButton(100053, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}
	else if(gJewelsBank.Active)
	{
		pDrawColorButton(100053, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	PosX -= mWidth;

	//Glow Effect Grafics
	//-----------------

	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	BottonX = PosX + 2;
	BottonY = PosY + 1;

	ButtonXEnd = BottonX + bWidth-1;
	ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100054, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();
			g_bGlowGraphic = !g_bGlowGraphic;
		}
		if(this->iStatus != 1 && this->iStatus != 3)
		gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(4));
		pDrawColorButton(100054, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}
	else if(g_bGlowGraphic)
	{
		pDrawColorButton(100054, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	PosX -= mWidth;

	//Party HP Bar
	//-----------------

	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	BottonX = PosX + 2;
	BottonY = PosY + 1;

	ButtonXEnd = BottonX + bWidth-1;
	ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100055, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();
			iPartyHpBar = !iPartyHpBar;
		}
		if(this->iStatus != 1 && this->iStatus != 3)
		gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(5));
		pDrawColorButton(100055, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}
	else if(iPartyHpBar)
	{
		pDrawColorButton(100055, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	PosX -= mWidth;
	
	//User HP Bar
	//-----------------

	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	BottonX = PosX + 2;
	BottonY = PosY + 1;

	ButtonXEnd = BottonX + bWidth-1;
	ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100056, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();
			iUserHpBar = !iUserHpBar;
		}
		if(this->iStatus != 1 && this->iStatus != 3)
		gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(6));
		pDrawColorButton(100056, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}
	else if(iUserHpBar)
	{
		pDrawColorButton(100056, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	PosX -= mWidth;	

	//Monster HP Bar
	//-----------------

	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	BottonX = PosX + 2;
	BottonY = PosY + 1;

	ButtonXEnd = BottonX + bWidth-1;
	ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100057, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();
			iMonsterHPBar = !iMonsterHPBar;
		}
		if(this->iStatus != 1 && this->iStatus != 3)
		gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(7));
		pDrawColorButton(100057, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}
	else if(iMonsterHPBar)
	{
		pDrawColorButton(100057, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	PosX -= mWidth;	

	//Rage System
	//-----------------
	if(gRAGESYSTEM)
	{
		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100060, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				gInterface.Data[eRageTable].OnShow = !gInterface.Data[eRageTable].OnShow;
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(8));
			pDrawColorButton(100060, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}
		else if(gInterface.Data[eRageTable].OnShow)
		{
			pDrawColorButton(100060, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	
	}

	//Quest System
	//-----------------
	if(gWINQUEST)
	{
		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100061, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				gQuestSystem.Switcher(0);
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, "Quest System");
			pDrawColorButton(100061, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}
		else if(gQuestSystem.GetActive(0))
		{
			pDrawColorButton(100061, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	

		//Quest Options System
		//-----------------

		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100062, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				gQuestSystem.Switcher(1);
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, "Quest Options");
			pDrawColorButton(100062, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}
		else if(gQuestSystem.GetActive(1))
		{
			pDrawColorButton(100062, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	
	}

	//OffAfk
	//-----------------

	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	BottonX = PosX + 2;
	BottonY = PosY + 1;

	ButtonXEnd = BottonX + bWidth-1;
	ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100063, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();

			if(g_ExLicense.user.OfflineMode)
			{
				if(gInterface.CheckWindowEx(exWinCheckOffAfk))
				{
					gInterface.CloseWindowEx(exWinCheckOffAfk);
				}
				else
				{
					gInterface.OpenWindowEx(exWinCheckOffAfk);
				}
			}
			else
			{
				gDataSend.SendOfflineAttack();
			}
		}
		if(this->iStatus != 1 && this->iStatus != 3)
		gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(9));
		pDrawColorButton(100063, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	PosX -= mWidth;	

	//Top 100 List
	//-----------------
	if(gRanking.Active)
	{
		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100065, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				gRanking.Show = !gRanking.Show;
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(10));
			pDrawColorButton(100065, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	
	}

	//Events
	//-----------------
	if(gEventTimer.Active)
	{
		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100066, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				gEventTimer.Show = !gEventTimer.Show;
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(11));
			pDrawColorButton(100065, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	
	}

	//PT Menu
	//-----------------
#if _NEW_PARTY_SYSTEM_ == TRUE
	if(gPARTY_SYSTEM)
	{
		if(g_Party.PartyMemberCount > 0)
		{
			pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

			BottonX = PosX + 2;
			BottonY = PosY + 1;

			ButtonXEnd = BottonX + bWidth-1;
			ButtonYEnd = BottonY + bHigh;

			if(g_Party.PartyShow)
			{
				pDrawGUI(100067, BottonX, BottonY, bWidth, bHigh);

				if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
				{
					if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
					{
						this->ClickTime = GetTickCount();
						g_Party.PartyShow = !g_Party.PartyShow;
					}
					if(this->iStatus != 1 && this->iStatus != 3)
					gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(12));
					pDrawColorButton(100067, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
				}
			}
			else
			{
				pDrawGUI(100068, BottonX, BottonY, bWidth, bHigh);

				if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
				{
					if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
					{
						this->ClickTime = GetTickCount();
						g_Party.PartyShow = !g_Party.PartyShow;
					}
					if(this->iStatus != 1 && this->iStatus != 3)
					gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(12));
					pDrawColorButton(100068, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
				}
			}

			PosX -= mWidth;	
		}
	}
#endif

	//Party Search
	//-----------------
#if(CUSTOM_PARTY_SEARCH==TRUE)

	if(g_PartySearch.Active)
	{
		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100069, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				if(!gInterface.CheckWindowEx(exWinPTSearchMaster) && !gInterface.CheckWindowEx(exWinPTSearchUser))
				{
					gInterface.OpenWindowEx(exWinPTSearchMaster);
				}
				else if(gInterface.CheckWindowEx(exWinPTSearchMaster))
				{
					gInterface.CloseWindowEx(exWinPTSearchMaster);
				}
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(13));
			pDrawColorButton(100069, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	
	}


#endif

	//Auto Party List	//-----------------

	if(g_PartySearch.Active)
	{
		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);	//100064

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100064, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				if(!gInterface.CheckWindowEx(exWinPTSearchMaster) && !gInterface.CheckWindowEx(exWinPTSearchUser))
				{
					g_PartySearch.CG_SendOpenUserList();
				}
				else if(gInterface.CheckWindowEx(exWinPTSearchUser))
				{
					gInterface.CloseWindowEx(exWinPTSearchUser);
				}
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(14));
			pDrawColorButton(100064, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	
	}
	else
	{
		if(gAutoParty.Active)
		{
			pDrawGUI(100050, PosX, PosY, mWidth, mHigh);	//100064

			BottonX = PosX + 2;
			BottonY = PosY + 1;

			ButtonXEnd = BottonX + bWidth-1;
			ButtonYEnd = BottonY + bHigh;

			pDrawGUI(100064, BottonX, BottonY, bWidth, bHigh);

			if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
			{
				if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
				{
					this->ClickTime = GetTickCount();
					gDataSend.SendOpenAutoPartyList();
				}
				if(this->iStatus != 1 && this->iStatus != 3)
				gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(14));
				pDrawColorButton(100064, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
			}

			PosX -= mWidth;	
		}
	}

	if(g_ExLicense.user.Smithy == true)
	{
		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100070, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				if(!gInterface.CheckWindowEx(exWinSmithy))
				{
					gInterface.OpenWindowEx(exWinSmithy);
				}
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, "Smithy");
			pDrawColorButton(100070, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	
	}

#if(CUSTOM_REFERAL_SYSTEM)
	//if(g_ExLicense.user.Smithy == true)
	//{
	//	pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

	//	BottonX = PosX + 2;
	//	BottonY = PosY + 1;

	//	ButtonXEnd = BottonX + bWidth-1;
	//	ButtonYEnd = BottonY + bHigh;

	//	pDrawGUI(100070, BottonX, BottonY, bWidth, bHigh);

	//	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	//	{
	//		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
	//		{
	//			this->ClickTime = GetTickCount();
	//			/*if(!gInterface.CheckWindowEx(exWinSmithy))
	//			{
	//				gInterface.OpenWindowEx(exWinSmithy);
	//			}*/
	//			g_ReferralSystem.CGReqMasterInfo();
	//		}
	//		if(this->iStatus != 1 && this->iStatus != 3)
	//		gInterface.DrawToolTip(BottonX-30, BottonY+20, "Refferal");
	//		pDrawColorButton(100074, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
	//	}

	//	PosX -= mWidth;	
	//}
#endif

	if(g_ExLicense.CheckUser(eExUB::Local) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
		THINNAKORN_MAC == 1 ||
		g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		pDrawGUI(100050, PosX, PosY, mWidth, mHigh);

		BottonX = PosX + 2;
		BottonY = PosY + 1;

		ButtonXEnd = BottonX + bWidth-1;
		ButtonYEnd = BottonY + bHigh;

		pDrawGUI(100071, BottonX, BottonY, bWidth, bHigh);

		if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
		{
			if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
			{
				this->ClickTime = GetTickCount();
				if(!gInterface.CheckWindowEx(exWinCustomMenu))
				{
					gInterface.OpenWindowEx(exWinCustomMenu);
				}
				else
				{
					gInterface.CloseWindowEx(exWinCustomMenu);
				}
			}
			if(this->iStatus != 1 && this->iStatus != 3)
			gInterface.DrawToolTip(BottonX-30, BottonY+20, "Custom");
			pDrawColorButton(100071, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		}

		PosX -= mWidth;	
	}

	// ----------------

	this->StartX = PosX;

	//Close Menu Button
	//-----------------
	pDrawGUI(100050, this->statX, PosY, mWidth, mHigh);

	BottonX = this->statX + 2;
	BottonY = PosY + 1;

	ButtonXEnd = BottonX + bWidth-1;
	ButtonYEnd = BottonY + bHigh;

	pDrawGUI(100058, BottonX, BottonY, bWidth, bHigh);

	if(CursorZoneButton(BottonX, BottonY, ButtonXEnd, ButtonYEnd))
	{
		gInterface.DrawToolTip(BottonX-30, BottonY+20, g_ExText.GetText(15));
		pDrawColorButton(100058, BottonX, BottonY, bWidth, bHigh, 0, 0, pMakeColor(255, 204, 20, 130));
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 200)
		{
			this->ClickTime = GetTickCount();
			this->iStatus = 3;
		}
	}
}
