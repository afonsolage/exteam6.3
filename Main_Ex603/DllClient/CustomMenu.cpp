#include "stdafx.h"
#include "CustomMenu.h"
#include "Interface.h"
#include "Configs.h"
#include "User.h"
#include "Protocol.h"
#include "ExLicense.h"
#include "PremiumSystemEx.h"
#include "ExTeleportEvo.h"

#if(CUSTOM_MENU)

CCustomMenu g_CustomMenu;

CCustomMenu::CCustomMenu()
{
	this->Init();
}

CCustomMenu::~CCustomMenu()
{
}

void CCustomMenu::Init()
{
	this->iChangeClassWcoinPrice = 0;
	this->iChangeClassCreditPrice = 0;
	this->bChangeClassWcoinActive = 0;
	this->bChangeClassCreditActive = 0;
}

void CCustomMenu::Load()
{
	this->Init();
}

void CCustomMenu::BindImages()
{
	gInterface.BindObject(eCUSTOM_MENU_MAIN, 0x7A5A, 222, 200+25, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_CHANGE_CLASS, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_RESET, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_GRANDRESET, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_PREMIUM, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_TELEPORT, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCUSTOM_MENU_ACCSECURITY, 0x7A5E, 108, 29, -1, -1);
	
	gInterface.BindObject(eCHANGECLASS_MAIN, 0x7A5A, 222, 290, -1, -1);
	gInterface.BindObject(eCHANGECLASS_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eCHANGECLASS_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eCHANGECLASS_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eCHANGECLASS_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eCHANGECLASS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eCHANGECLASS_DK, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCHANGECLASS_DW, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCHANGECLASS_AE, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCHANGECLASS_SU, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCHANGECLASS_MG, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCHANGECLASS_DL, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eCHANGECLASS_RF, 0x7A5E, 108, 29, -1, -1);

	gInterface.BindObject(eCHANGECLASS_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eCHANGECLASS_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eCHANGECLASS_LINE1, 0x7B67, 154, 3, -1, -1);

	gInterface.BindObject(eCHANGECLASS_POINT2, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eCHANGECLASS_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eCHANGECLASS_LINE2, 0x7B67, 154, 3, -1, -1);

}

void CCustomMenu::DrawMain()
{
	if( !g_ExLicense.CheckUser(eExUB::Local) && 
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!THINNAKORN_MAC &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!g_ExLicense.CheckUser(eExUB::Artem) &&
		!g_ExLicense.CheckUser(eExUB::Artem2)
		)
	{
		return;
	}

	if(!gInterface.CheckWindowEx(exWinCustomMenu))
	{
		this->DrawChangeClass();
		return;
	}

	pSetCursorFocus = true;

	DWORD Color				= eWhite;
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	float ButtonY			= 110;

	gInterface.DrawGUI(eCUSTOM_MENU_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eCUSTOM_MENU_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eCUSTOM_MENU_FRAME, StartX, StartY + 67.0, 8);//6
	gInterface.DrawGUI(eCUSTOM_MENU_FOOTER, StartX, StartY);

	gInterface.DrawGUI(eCUSTOM_MENU_CLOSE, StartX + MainWidth - gInterface.Data[eCUSTOM_MENU_CLOSE].Width, gInterface.Data[eCUSTOM_MENU_TITLE].Height + gInterface.Data[eCUSTOM_MENU_CLOSE].Height + 2);
	if( gInterface.IsWorkZone(eCUSTOM_MENU_CLOSE) )
	{
		Color = eGray100;
		if( gInterface.Data[eCUSTOM_MENU_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eCUSTOM_MENU_CLOSE, gInterface.Data[eCUSTOM_MENU_CLOSE].X, gInterface.Data[eCUSTOM_MENU_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eCUSTOM_MENU_CLOSE].X + 5, gInterface.Data[eCUSTOM_MENU_CLOSE].Y + 25, "Close");
	}

	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Menu");

	ButtonY += 30;
	gInterface.DrawGUI(eCUSTOM_MENU_RESET, ButtonX, ButtonY);
	gInterface.DrawFormat(eWhite, ButtonX+4, ButtonY+10, 100, 3, "Reset");

	ButtonY += 30;
	gInterface.DrawGUI(eCUSTOM_MENU_GRANDRESET, ButtonX, ButtonY);
	gInterface.DrawFormat(eWhite, ButtonX+4, ButtonY+10, 100, 3, "Grand Reset");

	ButtonY += 30;
	gInterface.DrawGUI(eCUSTOM_MENU_CHANGE_CLASS, ButtonX, ButtonY);
	gInterface.DrawFormat(eWhite, ButtonX+4, ButtonY+10, 100, 3, "Change Class");

	ButtonY += 30;
	gInterface.DrawGUI(eCUSTOM_MENU_PREMIUM, ButtonX, ButtonY);
	gInterface.DrawFormat(eWhite, ButtonX+4, ButtonY+10, 100, 3, "Premium");

	ButtonY += 30;
	gInterface.DrawGUI(eCUSTOM_MENU_TELEPORT, ButtonX, ButtonY);
	gInterface.DrawFormat(eWhite, ButtonX+4, ButtonY+10, 100, 3, "Teleport");

	if(!g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		ButtonY += 30;
		gInterface.DrawGUI(eCUSTOM_MENU_ACCSECURITY, ButtonX, ButtonY);
		gInterface.DrawFormat(eWhite, ButtonX+4, ButtonY+10, 100, 3, "Account Security");
	}

	if( gInterface.IsWorkZone(eCUSTOM_MENU_RESET) )
	{
		Color = eGray100;
		if( gInterface.Data[eCUSTOM_MENU_RESET].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eCUSTOM_MENU_RESET, gInterface.Data[eCUSTOM_MENU_RESET].X, gInterface.Data[eCUSTOM_MENU_RESET].Y, Color);
	}

	if( gInterface.IsWorkZone(eCUSTOM_MENU_GRANDRESET) )
	{
		Color = eGray100;
		if( gInterface.Data[eCUSTOM_MENU_GRANDRESET].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eCUSTOM_MENU_GRANDRESET, gInterface.Data[eCUSTOM_MENU_GRANDRESET].X, gInterface.Data[eCUSTOM_MENU_GRANDRESET].Y, Color);
	}

	if( gInterface.IsWorkZone(eCUSTOM_MENU_CHANGE_CLASS) )
	{
		Color = eGray100;
		if( gInterface.Data[eCUSTOM_MENU_CHANGE_CLASS].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eCUSTOM_MENU_CHANGE_CLASS, gInterface.Data[eCUSTOM_MENU_CHANGE_CLASS].X, gInterface.Data[eCUSTOM_MENU_CHANGE_CLASS].Y, Color);
	}

	if( gInterface.IsWorkZone(eCUSTOM_MENU_PREMIUM) )
	{
		Color = eGray100;
		if( gInterface.Data[eCUSTOM_MENU_PREMIUM].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eCUSTOM_MENU_PREMIUM, gInterface.Data[eCUSTOM_MENU_PREMIUM].X, gInterface.Data[eCUSTOM_MENU_PREMIUM].Y, Color);
	}

	if( gInterface.IsWorkZone(eCUSTOM_MENU_TELEPORT) )
	{
		Color = eGray100;
		if( gInterface.Data[eCUSTOM_MENU_TELEPORT].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eCUSTOM_MENU_TELEPORT, gInterface.Data[eCUSTOM_MENU_TELEPORT].X, gInterface.Data[eCUSTOM_MENU_TELEPORT].Y, Color);
	}

	if(!g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		if( gInterface.IsWorkZone(eCUSTOM_MENU_ACCSECURITY) )
		{
			Color = eGray100;
			if( gInterface.Data[eCUSTOM_MENU_ACCSECURITY].OnClick )
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eCUSTOM_MENU_ACCSECURITY, gInterface.Data[eCUSTOM_MENU_ACCSECURITY].X, gInterface.Data[eCUSTOM_MENU_ACCSECURITY].Y, Color);
		}
	}
}

void CCustomMenu::Button(DWORD Event)
{
	// -> Custom Menu
	if(gInterface.CheckWindowEx(exWinCustomMenu))
	{
		if(gInterface.ButtonEx(Event, eCUSTOM_MENU_CLOSE, false))
		{
			gInterface.CloseWindowEx(exWinCustomMenu);
			return;
		}

		if(gInterface.ButtonEx(Event, eCUSTOM_MENU_CHANGE_CLASS, false))
		{
			gInterface.CloseWindowEx(exWinCustomMenu);
			gInterface.OpenWindowEx(exWinCustomMenuChangeClass);
			return;
		}

		if(gInterface.ButtonEx(Event, eCUSTOM_MENU_RESET, false))
		{
			gInterface.CloseWindowEx(exWinCustomMenu);
			this->CGResetMenu();
			return;
		}

		if(gInterface.ButtonEx(Event, eCUSTOM_MENU_GRANDRESET, false))
		{
			gInterface.CloseWindowEx(exWinCustomMenu);
			this->CGGrandMenu();
			return;
		}

		if(gInterface.ButtonEx(Event, eCUSTOM_MENU_PREMIUM, false))
		{
			gInterface.CloseWindowEx(exWinCustomMenu);
#if(CUSTOM_PREMIUM_SYSTEM)
			g_PremiumSystemEx.CG_SendOpenWindows();
#endif
			return;
		}

		if(gInterface.ButtonEx(Event, eCUSTOM_MENU_TELEPORT, false))
		{
			gInterface.CloseWindowEx(exWinCustomMenu);
			g_ExTeleportEvo.CGDialog();
			return;
		}

		if(gInterface.ButtonEx(Event, eCUSTOM_MENU_ACCSECURITY, false))
		{
			gInterface.CloseWindowEx(exWinCustomMenu);
			gInterface.OpenWindowEx(ObjWindowsEx::exWinAccWarning);
			return;
		}
	}

	// -> Change Class
	if(gInterface.CheckWindowEx(exWinCustomMenuChangeClass))
	{
		if(gInterface.ButtonEx(Event, eCHANGECLASS_CLOSE, false))
		{
			gInterface.CloseWindowEx(exWinCustomMenuChangeClass);
			return;
		}
		// ----
		if(gInterface.ButtonEx(Event, eCHANGECLASS_CHECK1, false))
		{
			if(gObjUser.WCoinC >= this->iChangeClassWcoinPrice)
			{
				this->bChangeClassWcoinActive = true;
				this->bChangeClassCreditActive = false;
			}
		}
		if(gInterface.ButtonEx(Event, eCHANGECLASS_CHECK2, false))
		{
			if(gObjUser.ExCred >= this->iChangeClassCreditPrice)
			{
				this->bChangeClassWcoinActive = false;
				this->bChangeClassCreditActive = true;
			}
		}
		// ----
		if(gInterface.ButtonEx(Event, eCHANGECLASS_DK, true))
		{
			this->CGChangeClass(CLASS_KNIGHT);
		}
		else if(gInterface.ButtonEx(Event, eCHANGECLASS_DW, true))
		{
			this->CGChangeClass(CLASS_WIZARD);
		}
		else if(gInterface.ButtonEx(Event, eCHANGECLASS_AE, true))
		{
			this->CGChangeClass(CLASS_ELF);
		}
		else if(gInterface.ButtonEx(Event, eCHANGECLASS_MG, true))
		{
			this->CGChangeClass(CLASS_MAGUMSA);
		}
		else if(gInterface.ButtonEx(Event, eCHANGECLASS_DL, true))
		{
			this->CGChangeClass(CLASS_DARKLORD);
		}

		if(gObjUser.SUM)
		{
			if(gInterface.ButtonEx(Event, eCHANGECLASS_SU, true))
			{
				this->CGChangeClass(CLASS_SUMMONER);
			}
		}

		if(gObjUser.RF)
		{
			if(gInterface.ButtonEx(Event, eCHANGECLASS_RF, true))
			{
				this->CGChangeClass(CLASS_MONK);
			}
		}
	}

	// -> Next

}

void CCustomMenu::DrawChangeClass()
{
	if(!gInterface.CheckWindowEx(exWinCustomMenuChangeClass))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color				= eWhite;
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	float ButtonY			= 110;

	gInterface.DrawGUI(eCHANGECLASS_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eCHANGECLASS_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eCHANGECLASS_FRAME, StartX, StartY + 67.0, 12);
	gInterface.DrawGUI(eCHANGECLASS_FOOTER, StartX, StartY);

	gInterface.DrawGUI(eCHANGECLASS_CLOSE, StartX + MainWidth - gInterface.Data[eCHANGECLASS_CLOSE].Width, gInterface.Data[eCHANGECLASS_TITLE].Height + gInterface.Data[eCHANGECLASS_CLOSE].Height + 2);
	if( gInterface.IsWorkZone(eCHANGECLASS_CLOSE) )
	{
		Color = eGray100;
		if( gInterface.Data[eCHANGECLASS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eCHANGECLASS_CLOSE, gInterface.Data[eCHANGECLASS_CLOSE].X, gInterface.Data[eCHANGECLASS_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eCHANGECLASS_CLOSE].X + 5, gInterface.Data[eCHANGECLASS_CLOSE].Y + 25, "Close");
	}

	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Change Class");

	// -> change pay
	float ContentX = StartX;
	float ContentY = ButtonY + 20;
	char szText[256];

	sprintf(szText, "Change Class for %d WCoin", this->iChangeClassWcoinPrice);
	gInterface.DrawCheckLine(this->bChangeClassWcoinActive, eCHANGECLASS_POINT1, eCHANGECLASS_CHECK1, eCHANGECLASS_LINE1, ContentX, ContentY, eWhite, szText);

	ContentY += 20;
	sprintf(szText, "Change Class for %d Credits", this->iChangeClassCreditPrice);
	gInterface.DrawCheckLine(this->bChangeClassCreditActive, eCHANGECLASS_POINT2, eCHANGECLASS_CHECK2, eCHANGECLASS_LINE2, ContentX, ContentY, eWhite, szText);
	
	//-> Class Button

	ButtonY = ContentY + 20;

	int plusY = 30;

	if(!gObjUser.SUM)
	{
		plusY += 5;
	}

	if(!gObjUser.RF)
	{
		plusY += 5;
	}

	bool Act = true;

	if(this->bChangeClassWcoinActive == 0 && this->bChangeClassCreditActive == 0)
	{
		Act = false;
	}

	gInterface.DrawButtonBig(eCHANGECLASS_DK, Act, ButtonX, ButtonY, "Dark Knight");
	ButtonY += plusY;
	gInterface.DrawButtonBig(eCHANGECLASS_DW, Act, ButtonX, ButtonY, "Dark Wizard");
	ButtonY += plusY;
	gInterface.DrawButtonBig(eCHANGECLASS_AE, Act, ButtonX, ButtonY, "Elf");
	ButtonY += plusY;
	gInterface.DrawButtonBig(eCHANGECLASS_MG, Act, ButtonX, ButtonY, "Magic Gladiator");
	ButtonY += plusY;
	gInterface.DrawButtonBig(eCHANGECLASS_DL, Act, ButtonX, ButtonY, "Dark Lord");

	if(gObjUser.SUM)
	{
		ButtonY += plusY;
		gInterface.DrawButtonBig(eCHANGECLASS_SU, Act, ButtonX, ButtonY, "Summoner");
	}

	if(gObjUser.RF)
	{
		ButtonY += plusY;
		gInterface.DrawButtonBig(eCHANGECLASS_RF, Act, ButtonX, ButtonY, "Rage Fighter");
	}
}

void CCustomMenu::CGChangeClass(BYTE iClass)
{
	PMSG_CG_CHANGECLASS pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x41,  sizeof(pMsg));
	pMsg.iNewClass = iClass;

	BYTE btType = 0;

	if(this->bChangeClassCreditActive == true)
	{
		btType = 0;
	}
	else if(this->bChangeClassWcoinActive == true)
	{
		btType = 1;
	}

	pMsg.PriceType = btType;

	gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));
	gInterface.CloseWindowEx(exWinCustomMenuChangeClass);
}

void CCustomMenu::GCChangeClassConfig(PMSG_GC_CHANGECLASS_CONFIG* aRecv)
{
	this->iChangeClassWcoinPrice = aRecv->iChangeClassWcoinPrice;
	this->iChangeClassCreditPrice = aRecv->iChangeClassCreditPrice;
}

void CCustomMenu::CGResetMenu()
{
	PMSG_RESET_RESULT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xA0,  sizeof(pMsg));
	pMsg.Result = 1;
	gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));
}

void CCustomMenu::CGGrandMenu()
{
	PMSG_RESET_RESULT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xA1,  sizeof(pMsg));
	pMsg.Result = 1;
	gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));
}

#endif