#include "stdafx.h"
#include "Controller.h"
#include "Interface.h"
#include "ExFunction.h"
#include "EventTimer.h"
#include "CustomInterfaceMenu.h"
#include "Settings.h"
#include "Achievements.h"
#include "JewelsBank.h"
#include "DataSend.h"
#include "Ranking.h"
#include "PartySearch.h"
#include "ExTeleportEvo.h"
#include "ExText.h"
#include "DonateShop.h"
#include "Camera.h"
#include "Console.h"

cCustomMenuInterface gCustomMenuInterface;

cCustomMenuInterface::cCustomMenuInterface()
{
	this->MainTableHigh = 300;
	this->MainTableWidth = 300;
	this->DrawStartX = 640/2 - MainTableWidth/2;
	this->DrawStartY = 50;
	this->DrawTable = false;
	this->MenuOpen = 0;
}


//---------------------------------------------------------------------------------

void cCustomMenuInterface::ImageLoad()
{
	gInterface.LoadImages("Custom\\Interface\\MenuInterface\\MenuTable.tga", 100100, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\MenuInterface\\Buttons\\B1On.tga", 100101, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\MenuInterface\\Buttons\\B1Off.tga", 100102, 0x2601, 0x2900, 1);
	
	gInterface.LoadImages("Custom\\Interface\\MenuInterface\\Buttons\\B15On.tga", 100134, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\MenuInterface\\Buttons\\B15Off.tga", 100144, 0x2601, 0x2900, 1);
	}


void DrawGuiWithText(DWORD ModelID, float X, float Y, float Width, float Height, DWORD Color, char* Text)
{
	pDrawGUI(ModelID, X, Y, Width, Height);

	gInterface.DrawFormatEx(Color, (int)(X+(Width/2)), (int)(Y+6), 0, 8, Text );
}

//---------------------------------------------------------------------------------

void cCustomMenuInterface::Draw()
{

	if(!this->DrawTable) return;
	pSetCursorFocus = true;

	//-----------------------------------------------------------------------------------
	//	Draw Quest Icons
	//-----------------------------------------------------------------------------------

	pDrawGUI(100100, DrawStartX, DrawStartY, MainTableWidth, MainTableHigh);
	gInterface.DrawFormatEx(eGold, DrawStartX + 140, DrawStartY + 20, 140, 1, "Menu" );

	// ----

	int DrawButtonX = DrawStartX +15;
	int DrawButtonY = DrawStartY +50;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 0;
			DrawTable = false;
			g_Achievements.CGWindowOpen();
			return;
		}
		//pDrawGUI(100101, DrawButtonX, DrawButtonY, 130, 23);
		//gInterface.DrawFormatEx(eWhite, DrawButtonX+40, DrawButtonY+6, 130, 1, "Achievements" );
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Achievements");
	}
	//else if(MenuOpen == 0)
	//{
	//	pDrawGUI(100101, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		//pDrawGUI(100102, DrawButtonX, DrawButtonY, 130, 23);
		//gInterface.DrawFormatEx(eWhite180, DrawButtonX+40, DrawButtonY+6, 130, 1, "Achievements" );
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Achievements");
	}

	// ----

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 1;
			DrawTable = false;
			gInterface.OpenWindowEx(exWinAchievementsPower);
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Achievements Power");
	}
	//else if(MenuOpen == 1)
	//{
	//	pDrawGUI(100102, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		pDrawGUI(100102, DrawButtonX, DrawButtonY, 130, 23);
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Achievements Power");
	}

	// ----

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 2;
			DrawTable = false;
			gInterface.Data[eRageTable].OnShow = !gInterface.Data[eRageTable].OnShow;
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Rage System");
	}
	//else if(MenuOpen == 2)
	//{
	//	pDrawGUI(100103, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Rage System");
	}

	// ----

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 3;
			DrawTable = false;
			gInterface.OpenWindowEx(exWinPTSearchMaster);
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Party Search");
	}
	//else if(MenuOpen == 3)
	//{
	//	pDrawGUI(100104, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Party Search");
	}

	// ----

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 4;
			DrawTable = false;
			g_PartySearch.CG_SendOpenUserList();
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Party Search List");
	}
	//else if(MenuOpen == 4)
	//{
	//	pDrawGUI(100105, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
	DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Party Search List");
	}

	// ----

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 5;
			DrawTable = false;
			gInterface.OpenWindowEx(exWinCheckOffAfk);
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Offline Mode");
	}
	//else if(MenuOpen == 5)
	//{
	//	pDrawGUI(100106, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Offline Mode");
	}

	// ----

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 6;
			DrawTable = false;
			gJewelsBank.Active = !gJewelsBank.Active;
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Jewels Bank");
	}
	//else if(MenuOpen == 6)
	//{
	//	pDrawGUI(100107, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Jewels Bank");
	}

	DrawButtonY += 25;
	//Referral System
	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 15;
			DrawTable = false;
			g_DonateShop.CG_CashSend();
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Donate Shop");
	}
	//else if(MenuOpen == 15)
	//{
	//	pDrawGUI(100135, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
	DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Donate Shop");
	}

	// ----
	
	DrawButtonX += 140;
	DrawButtonY -= 175;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 7;
			DrawTable = false;
			//gRanking.Show = !gRanking.Show;
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Ranking");
	}
	//else if(MenuOpen == 7)
	//{
	//	pDrawGUI(100108, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Ranking");
	}

	// ----


	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 8;
			DrawTable = false;
			gEventTimer.Show = !gEventTimer.Show;
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Events Time");
	}
	//else if(MenuOpen == 8)
	//{
	//	pDrawGUI(100109, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Events Time");
	}

	// ----

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 9;
			DrawTable = false;
			gInterface.OpenWindowEx(exWinCustomMenuChangeClass);
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Change Class");
	}
	//else if(MenuOpen == 9)
	//{
	//	pDrawGUI(100110, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Change Class");
	}

	/*DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 10;
			DrawTable = false;
			g_ExTeleportEvo.CGDialog();
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Teleport System");
	}
	//else if(MenuOpen == 10)
	//{
	//	pDrawGUI(100130, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Teleport System");
	}*/

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 11;
			DrawTable = false;
			gInterface.OpenWindowEx(ObjWindowsEx::exWinAccWarning);
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Account Security");
	}
	//else if(MenuOpen == 11)
	//{
	//	pDrawGUI(100131, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Account Security");
	}

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 12;
			DrawTable = false;
			gInterface.m_bCashShopOpen = true;
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Cash Shop");
	}
	//else if(MenuOpen == 12)
	//{
	//	pDrawGUI(100132, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Cash Shop");
	}

	DrawButtonY += 25;
	
	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 16;
			DrawTable = false;
			gInterface.OpenWindowEx(exWinSmithy);
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Smithy");
	}
	//else if(MenuOpen == 16)
	//{
	//	pDrawGUI(100136, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Smithy");
	}

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 12;
			DrawTable = false;
			gCamera.Init();
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"3D Camera [Reset]");
	}
	//else if(MenuOpen == 12)
	//{
	//	pDrawGUI(100132, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"3D Camera [Reset]");
	}

	DrawButtonY += 25;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 130, DrawButtonY + 23))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 13;
			DrawTable = false;
			gInterface.OpenWindowEx(exWinSettings);
			return;
		}
		DrawGuiWithText(100101,DrawButtonX,DrawButtonY,130,23,eWhite,"Settings");
	}
	//else if(MenuOpen == 13)
	//{
	//	pDrawGUI(100133, DrawButtonX, DrawButtonY, 130, 23);
	//}
	else
	{
		DrawGuiWithText(100102,DrawButtonX,DrawButtonY,130,23,eWhite180,"Settings");
	}

	DrawButtonY -= 220;
	DrawButtonX += 120;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 20, DrawButtonY + 20))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 14;
			DrawTable = false;
			return;
		}
		pDrawGUI(100134, DrawButtonX, DrawButtonY, 20, 20);
	}
	//else if(MenuOpen == 14)
	//{
	//	pDrawGUI(100134, DrawButtonX, DrawButtonY, 20, 20);
	//}
	else
	{
		pDrawGUI(100144, DrawButtonX, DrawButtonY, 20, 20);
	}
}

// -------------------------------------------------------------------------------------------
