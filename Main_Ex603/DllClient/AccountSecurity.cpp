#include "stdafx.h"
#include "AccountSecurity.h"
#include "Interface.h"
#include "ExLicense.h"

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
	this->m_bEnable = true;

	this->m_iTypeMessage = 0;

	this->m_bActivePCID = false;
	this->m_bChangePCID = false;
	memset(&this->m_szTempSecretNumber, 0, sizeof(this->m_szTempSecretNumber));
	sprintf(this->m_szTempSecretNumber, "0");

	this->m_bOnlyMyPC = false;
	this->m_bTrade = false;
	this->m_bInventory = false;
	this->m_bWerehouse = false;
	this->m_bDisconnectFriend = false;
	this->m_bSellChar = false;

	this->m_bCheckPCID = false;
	this->m_bNewSecretNumber = false;
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

	gInterface.BindObject(eACC_MENU_MAIN, 0x7A5A, 222, 200, -1, -1);
	gInterface.BindObject(eACC_MENU_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eACC_MENU_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eACC_MENU_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eACC_MENU_DIV1, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eACC_MENU_DIV2, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eACC_MENU_CLOSE, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eACC_MENU_PCSETTING, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eACC_MENU_OPTION, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eACC_MENU_INFOBG1, 0x7AA3, 170, 21, -1, -1);

	gInterface.BindObject(eACC_OPTION_MAIN, 0x7A5A, 222, 260, -1, -1);
	gInterface.BindObject(eACC_OPTION_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eACC_OPTION_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eACC_OPTION_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eACC_OPTION_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_OPTION_CLOSE, 0x7A5F, 62, 27, -1, -1);
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
	gInterface.BindObject(eACC_OPTION_INFOBG1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eACC_OPTION_DIV1, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eACC_OPTION_DIV2, 0x7A62, 223, 21, -1, -1);

	gInterface.BindObject(eACC_PC_MAIN, 0x7A5A, 222, 170, -1, -1);
	gInterface.BindObject(eACC_PC_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eACC_PC_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eACC_PC_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eACC_PC_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_PC_CLOSE, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_PC_INFOBG1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eACC_PC_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eACC_PC_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eACC_PC_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eACC_PC_LINE2, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eACC_PC_POINT2, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eACC_PC_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eACC_PC_DIV1, 0x7A62, 223, 21, -1, -1);

	gInterface.BindObject(eACC_MESSAGE_MAIN, 0x7A5A, 222, 140, -1, -1);
	gInterface.BindObject(eACC_MESSAGE_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eACC_MESSAGE_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eACC_MESSAGE_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eACC_MESSAGE_CLOSE, 0x7A5E, 108, 29, -1, -1);

	gInterface.BindObject(eACC_NUMBER_MAIN, 0x7A5A, 222, 110, -1, -1);
	gInterface.BindObject(eACC_NUMBER_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eACC_NUMBER_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eACC_NUMBER_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eACC_NUMBER_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_NUMBER_CLOSE, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eACC_NUMBER_INFOBG1, 0x7AA3, 170, 21, -1, -1);
}

void CAccountSecurity::DrawMain()
{
	if(!this->m_bEnable)
	{
		return;
	}

	this->DrawWarning();
	this->DrawMenu();
	this->DrawSettingPC();
	this->DrawOption();
	this->DrawMessage();
	this->DrawNumber();
}

void CAccountSecurity::DrawWarning()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccWarning))
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth = 230.0;
	float StartY = 100.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentX = StartX;
	float ContentY = 170;

	gInterface.DrawWindow(eACC_WARNGNG_MAIN, eACC_WARNGNG_TITLE, eACC_WARNGNG_FRAME, eACC_WARNGNG_FOOTER, 2, StartX, StartY, "Warning");

	gInterface.DrawFormat(eRed, StartX + 10, 110 + 35, 210, 3, "Atenção! Antes de usar \n essa função, leia as instruções \n em nosso fórum!");

	ContentY += 15;
	gInterface.DrawButtonMini(eACC_WARNGNG_OK, ContentX + 30, ContentY + 5, true, "Ok");

	ContentX += 105;
	gInterface.DrawButtonMini(eACC_WARNGNG_CLOSE, ContentX + 30, ContentY + 5, true, "Cancelar");
}

void CAccountSecurity::DrawMenu()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccMenu))
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth = 230.0;
	float StartY = 100.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentX = StartX;
	float ContentY = StartY + 20;

	gInterface.DrawWindow(eACC_MENU_MAIN, eACC_MENU_TITLE, eACC_MENU_FRAME, eACC_MENU_FOOTER, 6, StartX, StartY, "Account Menu");

	ContentY += 15;
	gInterface.DrawGUI(eACC_MENU_INFOBG1, ContentX + 30, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Status:");

	if(this->m_bActivePCID)
	{
		gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "Protected");
	}
	else
	{
		gInterface.DrawFormat(eRed, ContentX + 95 + 30, ContentY + 5, 50, 3, "Not Protected");
	}

	ContentY += 15;
	gInterface.DrawGUI(eACC_MENU_DIV1, ContentX, ContentY);

	ContentY += 15;
	gInterface.DrawButtonBig(eACC_MENU_PCSETTING, true, ContentX + 60, ContentY + 5, "Setting PC ID");

	ContentY += 35;
	gInterface.DrawButtonBig(eACC_MENU_OPTION, true, ContentX + 60, ContentY + 5, "Account Option");

	ContentY += 30;
	gInterface.DrawGUI(eACC_MENU_DIV2, ContentX, ContentY);

	ContentY += 20;
	gInterface.DrawButtonBig(eACC_MENU_CLOSE, true, ContentX + 60, ContentY + 5, "Close");

}

void CAccountSecurity::DrawSettingPC()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccPC))
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth = 230.0;
	float StartY = 100.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentX = StartX;
	float ContentY = 120;

	gInterface.DrawWindow(eACC_PC_MAIN, eACC_PC_TITLE, eACC_PC_FRAME, eACC_PC_FOOTER, 4, StartX, StartY, "Scaning");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bActivePCID, eACC_PC_POINT1, eACC_PC_CHECK1, eACC_PC_LINE1, ContentX, ContentY, eWhite, "Active Protect");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bChangePCID, eACC_PC_POINT2, eACC_PC_CHECK2, eACC_PC_LINE2, ContentX, ContentY, eWhite, "Change PC ID");

	ContentY += 20;
	gInterface.DrawGUI(eACC_PC_INFOBG1, ContentX + 30, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Secret number:");
	gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "%u", atol(this->m_szTempSecretNumber));

	ContentY += 20;
	gInterface.DrawGUI(eACC_PC_DIV1, ContentX, ContentY);

	ContentY += 20;
	gInterface.DrawButtonMini(eACC_PC_OK, ContentX + 30, ContentY + 5, true, "Save");

	ContentX += 105;
	gInterface.DrawButtonMini(eACC_PC_CLOSE, ContentX + 30, ContentY + 5, true, "Cancel");
}

void CAccountSecurity::DrawOption()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccOption))
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth = 230.0;
	float StartY = 100.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentX = StartX;
	float ContentY = StartY + 20;

	gInterface.DrawWindow(eACC_OPTION_MAIN, eACC_OPTION_TITLE, eACC_OPTION_FRAME, eACC_OPTION_FOOTER, 10, StartX, StartY, "Account Option");

	ContentY += 15;
	gInterface.DrawGUI(eACC_MENU_INFOBG1, ContentX + 30, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Account:");

	if(this->m_bCheckPCID)
	{
		gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "Owner PC");
	}
	else
	{
		gInterface.DrawFormat(eRed, ContentX + 95 + 30, ContentY + 5, 50, 3, "Other PC");
	}

	ContentY += 15;
	gInterface.DrawGUI(eACC_OPTION_DIV1, ContentX, ContentY);

	ContentY += 25;
	gInterface.DrawCheckLineEx(this->m_bOnlyMyPC, eACC_OPTION_POINT1, eACC_OPTION_CHECK1, eACC_OPTION_LINE1, ContentX, ContentY, eWhite, "Access only from my PC");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bTrade, eACC_OPTION_POINT2, eACC_OPTION_CHECK2, eACC_OPTION_LINE2, ContentX, ContentY, eWhite, "Active Trade");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bInventory, eACC_OPTION_POINT3, eACC_OPTION_CHECK3, eACC_OPTION_LINE3, ContentX, ContentY, eWhite, "Active Inventory");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bWerehouse, eACC_OPTION_POINT4, eACC_OPTION_CHECK4, eACC_OPTION_LINE4, ContentX, ContentY, eWhite, "Active Warehouse");

	ContentY += 20;
	gInterface.DrawCheckLineEx(this->m_bDisconnectFriend, eACC_OPTION_POINT5, eACC_OPTION_CHECK5, eACC_OPTION_LINE5, ContentX, ContentY, eWhite, "Active Disconnect Friend");

	//ContentY += 20;
	//gInterface.DrawCheckLineEx(this->m_bSellChar, eACC_OPTION_POINT5, eACC_OPTION_CHECK6, eACC_OPTION_LINE5, ContentX, ContentY, eWhite, "Active Selling Character");

	ContentY += 20;
	gInterface.DrawGUI(eACC_OPTION_DIV2, ContentX, ContentY);

	ContentY += 20;
	gInterface.DrawButtonMini(eACC_OPTION_OK, ContentX + 30, ContentY + 5, this->m_bCheckPCID, "Save");

	ContentX += 105;
	gInterface.DrawButtonMini(eACC_OPTION_CLOSE, ContentX + 30, ContentY + 5, true, "Cancel");
}

void CAccountSecurity::DrawMessage()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccMessage))
	{
		return;
	}

	pSetCursorFocus = true;

	float StartY = 100.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MAX_BG_WIDTH / 2);

	gInterface.DrawWindow(eACC_MESSAGE_MAIN, eACC_MESSAGE_TITLE, eACC_MESSAGE_FRAME, eACC_MESSAGE_FOOTER, 2, StartX, StartY, "Error number");

	StartX += 10;
	StartY += 45;

	if(this->m_iTypeMessage == 0)
	{
		gInterface.DrawFormat(eRed, StartX, StartY, 210, 3, "Error!\n Secret number\n Entered incorrectly!");
	}
	else if(this->m_iTypeMessage == 1)
	{
		gInterface.DrawFormat(eExcellent, StartX, StartY, 210, 3, "Success!\n Secret number\n Entered correctly!");
	}

	StartX += 50;
	StartY += 40;
	gInterface.DrawButtonBig(eACC_MESSAGE_CLOSE, true, StartX, StartY + 5, "Close");
}

void CAccountSecurity::DrawNumber()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccNumber))
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth = 230.0;
	float StartY = 100.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentX = StartX;
	float ContentY = 120;

	gInterface.DrawWindow(eACC_NUMBER_MAIN, eACC_NUMBER_TITLE, eACC_NUMBER_FRAME, eACC_NUMBER_FOOTER, 0, StartX, StartY, "New Secret Number");

	ContentY += 20;
	gInterface.DrawGUI(eACC_NUMBER_INFOBG1, ContentX + 30, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15 + 30, ContentY + 5, 50, 3, "Secret number:");
	gInterface.DrawFormat(eExcellent, ContentX + 95 + 30, ContentY + 5, 50, 3, "%u", atol(this->m_szTempSecretNumber));

	bool bResultSave = true;

	if(atol(this->m_szTempSecretNumber) == 0)
	{
		bResultSave = false;
	}

	ContentY += 20;
	gInterface.DrawButtonMini(eACC_NUMBER_OK, ContentX + 30, ContentY + 5, bResultSave, "Save");

	ContentX += 105;
	gInterface.DrawButtonMini(eACC_NUMBER_CLOSE, ContentX + 30, ContentY + 5, true, "Cancel");
}

void CAccountSecurity::ButtonMain(DWORD Event)
{
	if(!this->m_bEnable)
	{
		return;
	}

	this->ButtonWarning(Event);
	this->ButtonMenu(Event);
	this->ButtonPC(Event);
	this->ButtonOption(Event);
	this->ButtonMessage(Event);
	this->ButtonNumber(Event);
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

		if(this->m_bNewSecretNumber == true)
		{
			gInterface.OpenWindowEx(ObjWindowsEx::exWinAccNumber);
		}
		else
		{
			gInterface.OpenWindowEx(ObjWindowsEx::exWinAccMenu);
		}		
	}
	else if(gInterface.ButtonEx(Event, eACC_WARNGNG_CLOSE, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccWarning);
	}
}

void CAccountSecurity::ButtonMenu(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccMenu))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, eACC_MENU_CLOSE, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccMenu);
	}
	else if(gInterface.ButtonEx(Event, eACC_MENU_PCSETTING, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccMenu);
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccPC);
	}
	else if(gInterface.ButtonEx(Event, eACC_MENU_OPTION, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccMenu);
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccOption);
	}
}

void CAccountSecurity::ButtonPC(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccPC))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, eACC_PC_CLOSE, false))
	{
		this->RestoreTempData();
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccPC);
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccMenu);
	}
	else if(gInterface.ButtonEx(Event, eACC_PC_OK, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccPC);
		this->CGSendSettingPC();
	}
	else if(gInterface.ButtonEx(Event, eACC_PC_CHECK1, false))
	{
		this->m_bActivePCID = !this->m_bActivePCID;
	}
	else if(gInterface.ButtonEx(Event, eACC_PC_CHECK2, false))
	{
		this->m_bChangePCID = !this->m_bChangePCID;
	}
}

void CAccountSecurity::ButtonOption(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccOption))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, eACC_OPTION_CLOSE, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccOption);
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccMenu);
		this->RestoreTempData();
	}
	else if(gInterface.ButtonEx(Event, eACC_OPTION_OK, true))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccOption);
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccMenu);
		this->CGSendAccountOption();
	}

	if(this->m_bActivePCID && this->m_bCheckPCID)
	{
		if(gInterface.ButtonEx(Event, eACC_OPTION_CHECK1, false))
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
}

void CAccountSecurity::ButtonMessage(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccMessage))
	{
		return;
	}

	else if(gInterface.ButtonEx(Event, eACC_MESSAGE_CLOSE, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccMessage);

		if(this->m_iTypeMessage == 1)
		{
			gInterface.OpenWindowEx(ObjWindowsEx::exWinAccMenu);
		}
	}
}

void CAccountSecurity::ButtonNumber(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccNumber))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, eACC_NUMBER_OK, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccNumber);
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAccMenu);
		this->CGSendSaveNumber();
		this->RestoreTempData();
	}
	else if(gInterface.ButtonEx(Event, eACC_NUMBER_CLOSE, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAccNumber);
		this->RestoreTempData();
	}
}

void CAccountSecurity::KeyboardPC(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAccPC) && !gInterface.CheckWindowEx(ObjWindowsEx::exWinAccNumber))
	{
		return;
	}

	gInterface.KeyBoxEvent(Event, this->m_szTempSecretNumber, 8);
}

void CAccountSecurity::CGSendAccountConnect()
{
	PMSG_ANS_ACC_CONNECT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB0, sizeof(pMsg));
	GetVolumeInformationA("c:\\", 0, 0, &pMsg.PCID, 0, 0, 0, 0);
	pMsg.PCID ^= 76347634761;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CAccountSecurity::CGSendSettingPC()
{
	PMSG_REQ_ACC_SETTING_PC pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB1, sizeof(pMsg));
	pMsg.ActivePCID = this->m_bActivePCID;
	pMsg.ChangePCID = this->m_bChangePCID;
	pMsg.SecretNumber = atol(this->m_szTempSecretNumber);
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CAccountSecurity::GCRecvSettingPC(PMSG_ANS_ACC_SETTING_PC* lpMsg)
{
	if(lpMsg->Result == 1)
	{
		this->m_iTypeMessage = 1;
	}
	else
	{
		this->m_iTypeMessage = 0;
	}

	gInterface.OpenWindowEx(ObjWindowsEx::exWinAccMessage);
}

void CAccountSecurity::CGSendAccountOption()
{
	PMSG_REQ_ACC_OPTION pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB2, sizeof(pMsg));
	pMsg.OnlyMyPC = this->m_bOnlyMyPC;
	pMsg.Trade = this->m_bTrade;
	pMsg.Inventory = this->m_bInventory;
	pMsg.Werehouse = this->m_bWerehouse;
	pMsg.DisconnectFriend = this->m_bDisconnectFriend;
	pMsg.SellChar = this->m_bSellChar;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CAccountSecurity::GCRecvAccountInfo(PMSG_REQ_ACC_INFO* lpMsg)
{
	this->m_bActivePCID = lpMsg->ActivePCID;
	this->m_bNewSecretNumber = lpMsg->NewSecretNumber;
	this->m_bCheckPCID = lpMsg->CheckPCID;
	this->m_bOnlyMyPC = lpMsg->OnlyMyPC;
	this->m_bTrade = lpMsg->Trade;
	this->m_bInventory = lpMsg->Inventory;
	this->m_bWerehouse = lpMsg->Werehouse;
	this->m_bDisconnectFriend = lpMsg->DisconnectFriend;
	this->m_bSellChar = lpMsg->SellChar;

	this->SetTempData();
}

void CAccountSecurity::CGSendSaveNumber()
{
	PMSG_REQ_ACC_SAVENUMBER pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB3, sizeof(pMsg));
	pMsg.SecretNumber = atol(this->m_szTempSecretNumber);
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CAccountSecurity::GCRecvConnectLogin(PMSG_REQ_ACC_LOGIN* lpMsg)
{
	if(lpMsg->Result)
	{
		this->CGSendAccountConnect();
	}
}

void CAccountSecurity::SetTempData()
{
	this->m_bTempActivePCID = this->m_bActivePCID;
	this->m_bTempChangePCID = false;
	memset(&this->m_szTempSecretNumber, 0, sizeof(this->m_szTempSecretNumber));
	sprintf(this->m_szTempSecretNumber, "0");

	this->m_bTempOnlyMyPC = this->m_bOnlyMyPC;
	this->m_bTempTrade = this->m_bTrade;
	this->m_bTempInventory = this->m_bInventory;
	this->m_bTempWerehouse = this->m_bWerehouse;
	this->m_bTempDisconnectFriend = this->m_bDisconnectFriend;
	this->m_bTempSellChar = this->m_bSellChar;
}

void CAccountSecurity::RestoreTempData()
{
	this->m_bActivePCID = this->m_bTempActivePCID;
	this->m_bChangePCID = false;
	memset(this->m_szTempSecretNumber, 0, sizeof(this->m_szTempSecretNumber));
	sprintf(this->m_szTempSecretNumber, "0");

	this->m_bOnlyMyPC = this->m_bTempOnlyMyPC;
	this->m_bTrade = this->m_bTempTrade;
	this->m_bInventory = this->m_bTempInventory;
	this->m_bWerehouse = this->m_bTempWerehouse;
	this->m_bDisconnectFriend = this->m_bTempDisconnectFriend;
	this->m_bSellChar = this->m_bTempSellChar;
}

#endif