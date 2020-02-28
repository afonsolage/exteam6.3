#include "stdafx.h"
#include "AccountSecurity.h"
#include "Interface.h"

#if(CUSTOM_ACCOUNT_SECURITY)

CAccountSecurity g_AccountSecurity;

CAccountSecurity::CAccountSecurity()
{
	this->Init();
}

CAccountSecurity::~CAccountSecurity()
{

}

void CAccountSecurity::Init()
{
	this->m_bAccountStatus = false;
	this->m_dwAccountPCID = 0x00;
	this->m_dwUserPCID = 0x00;
	this->m_bOnlyMyPC = false;
	this->m_bTrade = false;
	this->m_bInventory = false;
	this->m_bWerehouse = false;
	this->m_bDisconnectFriend = false;
	this->m_bSellChar = false;
}

void CAccountSecurity::Load()
{
	this->Init();
}

void CAccountSecurity::BindImage()
{
	gInterface.BindObject(eACC_WARNGNG_MAIN, 0x7A5A, 222, 140, -1, -1);
	gInterface.BindObject(eACC_WARNGNG_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eACC_WARNGNG_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eACC_WARNGNG_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eACC_WARNGNG_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_WARNGNG_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eACC_OPTION_MAIN, 0x7A5A, 222, 200 + 150, -1, -1);
	gInterface.BindObject(eACC_OPTION_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eACC_OPTION_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eACC_OPTION_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eACC_OPTION_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eACC_OPTION_DIV2, 0x7A62, 223, 21, -1, -1);

	//gInterface.BindObject(eACC_OPTION_OK, 0x7A5F, 62, 27, -1, -1);
	//gInterface.BindObject(eACC_OPTION_CLOSE, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_OPTION_OK, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eACC_OPTION_CLOSE, 0x7A5E, 108, 29, -1, -1);

	gInterface.BindObject(eACC_OPTION_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eACC_OPTION_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eACC_OPTION_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eACC_OPTION_LINE2, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eACC_OPTION_POINT2, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eACC_OPTION_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eACC_OPTION_LINE3, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eACC_OPTION_POINT3, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eACC_OPTION_CHECK3, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eACC_OPTION_LINE4, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eACC_OPTION_POINT4, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eACC_OPTION_CHECK4, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eACC_OPTION_LINE5, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eACC_OPTION_POINT5, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eACC_OPTION_CHECK5, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eACC_OPTION_LINE6, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eACC_OPTION_POINT6, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eACC_OPTION_CHECK6, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eACC_OPTION_SETTING, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eACC_OPTION_INFOBG1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eACC_OPTION_INFOBG2, 0x7AA3, 170, 21, -1, -1);

	gInterface.BindObject(eACC_SCAN_MAIN, 0x7A5A, 222, 120, -1, -1);
	gInterface.BindObject(eACC_SCAN_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eACC_SCAN_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eACC_SCAN_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eACC_SCAN_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_SCAN_CLOSE, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_SCAN_INFOBG1, 0x7AA3, 170, 21, -1, -1);
}

void CAccountSecurity::DrawMain()
{
	this->DrawWarning();
	this->DrawOption();
	this->DrawScan();
	this->DrawCheckNumber();
}

void CAccountSecurity::DrawWarning()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccWarning))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color				= eWhite;
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

	float ContentX = StartX;
	float ContentY = 170;

	gInterface.DrawWindow(eACC_WARNGNG_MAIN, eACC_WARNGNG_TITLE, eACC_WARNGNG_FRAME, eACC_WARNGNG_FOOTER, 2, StartX, StartY, "Warning");

	gInterface.DrawFormat(eRed, StartX + 10, 110 + 35, 210, 3, "Warning! Before usethis\n function readinstructions\n on our forum and remember!");

	ContentY += 15;
	gInterface.DrawButtonMini(eACC_WARNGNG_OK, ContentX + 30, ContentY + 5, true, "Ok");

	ContentX += 105;
	gInterface.DrawButtonMini(eACC_WARNGNG_CLOSE, ContentX + 30, ContentY + 5, true, "Cancel");
}

void CAccountSecurity::DrawOption()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccOption))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color = eWhite;
	float MainWidth = 230.0;
	float StartY = 70.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

	StartX -= (MainWidth / 2);

	float ContentX = StartX;
	float ContentY = StartY + 20;

	gInterface.DrawWindow(eACC_OPTION_MAIN, eACC_OPTION_TITLE, eACC_OPTION_FRAME, eACC_OPTION_FOOTER, 16, StartX, StartY, "Account Security");

	/*
	ContentY += 25;
	gInterface.DrawGUI(eACC_OPTION_INFOBG1, ContentX + 30, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Status:");

	if(this->m_bAccountStatus)
	{
		gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "Protected");
	}
	else
	{
		gInterface.DrawFormat(eRed, ContentX + 95 + 30, ContentY + 5, 50, 3, "Not Protected");
	}

	ContentY += 25;
	gInterface.DrawButtonBig(eACC_OPTION_SETTING, true, ContentX + 60, ContentY + 5, "Setting");
	*/

	//****

	ContentY += 25;
	gInterface.DrawCheckLineEx(this->m_bAccountStatus, eACC_OPTION_POINT1, eACC_OPTION_CHECK1, eACC_OPTION_LINE1, ContentX, ContentY, eWhite, "Account Security");

	ContentY += 15;
	gInterface.DrawGUI(eACC_OPTION_DIV, ContentX, ContentY);

	ContentY += 20;
	gInterface.DrawFormat(eWhite, ContentX + 10, ContentY, 210, 3, "Change the Account PC ID to the current PC ID");

	ContentY += 15;
	gInterface.DrawButtonBig(eACC_OPTION_SETTING, true, ContentX + 60, ContentY + 5, "Change PC ID");

	//****

	ContentY += 30;
	gInterface.DrawGUI(eACC_OPTION_DIV, ContentX, ContentY);

	ContentY += 20;
	gInterface.DrawGUI(eACC_OPTION_INFOBG1, ContentX + 30, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Account:");

	if(this->m_dwAccountPCID == this->m_dwUserPCID)
	{
		gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "Owner PC");
	}
	else
	{
		gInterface.DrawFormat(eRed, ContentX + 95 + 30, ContentY + 5, 50, 3, "Other PC");
	}

	ContentY += 25;
	gInterface.DrawCheckLineEx(this->m_bOnlyMyPC, eACC_OPTION_POINT1, eACC_OPTION_CHECK1, eACC_OPTION_LINE1, ContentX, ContentY, eWhite, "Access only from my PC");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bTrade, eACC_OPTION_POINT2, eACC_OPTION_CHECK2, eACC_OPTION_LINE2, ContentX, ContentY, eWhite, "Trade");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bInventory, eACC_OPTION_POINT3, eACC_OPTION_CHECK3, eACC_OPTION_LINE3, ContentX, ContentY, eWhite, "Inventory");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bWerehouse, eACC_OPTION_POINT4, eACC_OPTION_CHECK4, eACC_OPTION_LINE4, ContentX, ContentY, eWhite, "Warehouse");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bDisconnectFriend, eACC_OPTION_POINT5, eACC_OPTION_CHECK5, eACC_OPTION_LINE5, ContentX, ContentY, eWhite, "Disconnect Friend");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bSellChar, eACC_OPTION_POINT5, eACC_OPTION_CHECK6, eACC_OPTION_LINE5, ContentX, ContentY, eWhite, "Selling Character");

	//ContentY += 20;
	//gInterface.DrawGUI(eACC_OPTION_DIV2, ContentX, ContentY);

	//ContentY += 15;
	//gInterface.DrawButtonMini(eACC_OPTION_OK, ContentX + 30, ContentY + 5, true, "Save");

	//ContentX += 105;
	//gInterface.DrawButtonMini(eACC_OPTION_CLOSE, ContentX + 30, ContentY + 5, true, "Cancel");

	ContentY += 20;
	gInterface.DrawButtonBig(eACC_OPTION_OK, true, ContentX + 60, ContentY + 5, "Save Option");

	ContentY += 30;
	gInterface.DrawGUI(eACC_OPTION_DIV2, ContentX, ContentY);

	ContentY += 15;
	gInterface.DrawButtonBig(eACC_OPTION_CLOSE, true, ContentX + 60, ContentY + 5, "Close");

}

void CAccountSecurity::DrawScan()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccOption) || !gInterface.CheckWindowEx(ObjWindowsEx::exWinAccScan))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color				= eWhite;
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

	StartX += (MainWidth / 2);

	float ContentX = StartX;
	float ContentY = 120;

	gInterface.DrawWindow(eACC_SCAN_MAIN, eACC_SCAN_TITLE, eACC_SCAN_FRAME, eACC_SCAN_FOOTER, 1, StartX, StartY, "Scaning");

	ContentY += 25;
	gInterface.DrawGUI(eACC_SCAN_INFOBG1, ContentX + 30, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "PC ID:");
	gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "0x%11X", this->m_dwUserPCID);

	ContentY += 25;
	gInterface.DrawButtonMini(eACC_SCAN_OK, ContentX + 30, ContentY + 5, true, "Change");

	ContentX += 105;
	gInterface.DrawButtonMini(eACC_SCAN_CLOSE, ContentX + 30, ContentY + 5, true, "Cancel");
}

void CAccountSecurity::DrawCheckNumber()
{

}

void CAccountSecurity::ButtonMain(DWORD Event)
{
	this->ButtonWarning(Event);
	this->ButtonOption(Event);
	this->ButtonScan(Event);
	this->ButtonCheckNumber(Event);
}

void CAccountSecurity::ButtonWarning(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccWarning))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, eACC_WARNGNG_OK, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccWarning);
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccOption);
	}
	else if(gInterface.ButtonEx(Event, eACC_WARNGNG_CLOSE, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccWarning);
	}
}

void CAccountSecurity::ButtonOption(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccOption))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, eACC_OPTION_OK, false))
	{
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccOption);
	}
	else if(gInterface.ButtonEx(Event, eACC_OPTION_CLOSE, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccOption);
	}
	else if(gInterface.ButtonEx(Event, eACC_OPTION_SETTING, false))
	{
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccScan);
	}
	else if(gInterface.ButtonEx(Event, eACC_OPTION_CHECK1, false))
	{
		this->m_bOnlyMyPC = !this->m_bOnlyMyPC;
	}
	else if(gInterface.ButtonEx(Event, eACC_OPTION_CHECK2, false))
	{
		this->m_bTrade = !this->m_bTrade;
	}
	else if(gInterface.ButtonEx(Event, eACC_OPTION_CHECK3, false))
	{
		this->m_bInventory = !this->m_bInventory;
	}
	else if(gInterface.ButtonEx(Event, eACC_OPTION_CHECK4, false))
	{
		this->m_bWerehouse = !this->m_bWerehouse;
	}		
	else if(gInterface.ButtonEx(Event, eACC_OPTION_CHECK5, false))
	{
		this->m_bDisconnectFriend = !this->m_bDisconnectFriend;
	}		
	else if(gInterface.ButtonEx(Event, eACC_OPTION_CHECK6, false))
	{
		this->m_bSellChar = !this->m_bSellChar;
	}		
}

void CAccountSecurity::ButtonScan(DWORD Event)
{

}

void CAccountSecurity::ButtonCheckNumber(DWORD Event)
{

}

#endif