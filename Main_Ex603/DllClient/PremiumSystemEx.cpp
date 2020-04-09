#include "stdafx.h"
#include "PremiumSystemEx.h"
#include "Interface.h"
#include "User.h"
#include "Protocol.h"
#include "ExUtils.h"
#include "ExLicense.h"
#include "ExText.h"
#include "Console.h"
// ----------------------------------------------------------------------------------------------

PremiumSystemEx g_PremiumSystemEx;
// ----------------------------------------------------------------------------------------------

void PremiumSystemEx::Init()
{
	this->PremiumSwitch = eVip1;
	this->PremiumDay = 1;

	this->PriceSwitch = 0;

	this->NeedCredit = 0;
	this->NeedWCoin = 0;
	this->CurrentWCoin = 0;
	this->Buy1CreditDay = 0;
	this->Buy2CreditDay = 0;
	this->Buy3CreditDay = 0;
	this->Buy1WCoinDay = 0;
	this->Buy2WCoinDay = 0;
	this->Buy3WCoinDay = 0;

	this->m_VIPDaysLeft = 0;
}
// ----------------------------------------------------------------------------------------------

void PremiumSystemEx::Load()
{

	this->Init();

	//gInterface.OpenWindowEx(exWinPremium);

	//newui_Bt_scroll_dn.OZJ
	//newui_Bt_scroll_up.OZJ
	/*
	newui_Bt_skill_scroll_dn.OZJ
	newui_Bt_skill_scroll_up.OZJ

	op2_ch.OZT -> ãàëî÷êà
	newui_option_check.OZT - ãàëî÷êà 2 - 0x7B69

	newui_commamd_Line.OZJ - ëèíèÿ
	newui_option_line.OZJ - ëèíèÿ ïî äëèíüøå

	newui_ctminmap_Hero.tga


	newui_item_money.tga
	newui_item_money2.OZT - !

	newui_option_point.OZT



	newui_chainfo_btn_level.tga
	*/
}
// ----------------------------------------------------------------------------------------------

void PremiumSystemEx::BindImages()
{
	gInterface.BindObject(ePREMIUM_MAIN, 0x7A5A, 222, 303, -1, -1);
	gInterface.BindObject(ePREMIUM_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(ePREMIUM_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(ePREMIUM_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(ePREMIUM_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePREMIUM_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(ePREMIUM_INFOBG, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(ePREMIUM_MONEYBG, 0x7AA1 /*0x7A89*/, 170, 26, -1, -1);
	gInterface.BindObject(ePREMIUM_VIP, 0x7A5E, 108, 29, -1, -1);

	gInterface.BindObject(ePREMIUM_LINE1, 0x7B67, 154, 2, -1, -1);
	gInterface.BindObject(ePREMIUM_LINE2, 0x7B67, 154, 2, -1, -1);
	gInterface.BindObject(ePREMIUM_LINE3, 0x7B67, 154, 2, -1, -1);
	gInterface.BindObject(ePREMIUM_LINE4, 0x7B67, 154, 2, -1, -1);

	gInterface.BindObject(ePREMIUM_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(ePREMIUM_POINT2, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(ePREMIUM_POINT3, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(ePREMIUM_POINT4, 0x7B68, 10, 10, -1, -1);

	gInterface.BindObject(ePREMIUM_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePREMIUM_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePREMIUM_CHECK3, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePREMIUM_CHECK4, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePREMIUM_CHECK5, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(ePREMIUM_PAGEUP, 0x7AA4/*0x7ABD*/, 15, 15, -1, -1);
	gInterface.BindObject(ePREMIUM_PAGEDN, 0x7C0D/*0x7ABE*/, 15, 15, -1, -1);
	//7B69

	//pDrawGUI(0x7B67, StartX + 10 + 20, TitleY+10 , 150, 2);
	
}
// ----------------------------------------------------------------------------------------------

void PremiumSystemEx::DrawWindow()
{
	//return;
	if(!g_ExLicense.user.PremiumEx)
	{
		return;
	}

	//gInterface.OpenWindowEx(exWinPremium);

	if(!gInterface.CheckWindowEx(exWinPremium))
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

	if(gObjUser.PremiumType > 0 && gObjUser.PremiumType <=3 )
	{
		this->PremiumSwitch = gObjUser.PremiumType;
	}

	char tmp[100] = {0};
	sprintf_s(tmp, "%d dia(s)", m_VIPDaysLeft);

	bool hasCoins = CurrentWCoin >= NeedWCoin;

	// ----
	gInterface.DrawGUI(ePREMIUM_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(ePREMIUM_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ePREMIUM_FRAME, StartX, StartY + 67.0, 13);
	gInterface.DrawGUI(ePREMIUM_FOOTER, StartX, StartY);
	gInterface.DrawGUI(ePREMIUM_CLOSE, StartX + MainWidth - gInterface.Data[ePREMIUM_CLOSE].Width, gInterface.Data[ePREMIUM_TITLE].Height + gInterface.Data[ePREMIUM_CLOSE].Height + 2);
	// ----
	if( gInterface.IsWorkZone(ePREMIUM_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePREMIUM_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePREMIUM_CLOSE, gInterface.Data[ePREMIUM_CLOSE].X, gInterface.Data[ePREMIUM_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[ePREMIUM_CLOSE].X + 5, gInterface.Data[ePREMIUM_CLOSE].Y + 25, g_ExText.GetText(24));
	}
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, g_ExText.GetText(151));
	// ----

	gInterface.DrawFormat(eWhite, StartX + 35, 140, 70, 3, "Tempo restante: ");

	int color = (m_VIPDaysLeft < 1 ? eRed : (m_VIPDaysLeft < 10 ? eYellow : eShinyGreen));

	gInterface.DrawFormat(color, StartX + 115, 140, 70, 3, tmp);
	
	gInterface.DrawFormat(eWhite, StartX + 35, 160, 70, 3, "Benefícios: ");
	gInterface.DrawFormat(eGold, StartX + 90, 170, 120, 3, "- 25%% de Bônus de EXP");
	gInterface.DrawFormat(eGold, StartX + 90, 180, 120, 3, "- 50%% de Bônus de Goblin Points");
	gInterface.DrawFormat(eGold, StartX + 90, 190, 120, 3, "- 20%% Off loja LCoins [X]");
	gInterface.DrawFormat(eGold, StartX + 90, 200, 120, 3, "- Offline Attack ilimitado");

	gInterface.DrawFormat(eWhite, StartX + 40, 280, 150, 3, "Para mais informações, acesse o site ou o fórum");

	gInterface.DrawGUI(ePREMIUM_INFOBG, StartX + 30, 300);
	gInterface.DrawFormat(eGold, StartX + 35, 305, 70, 3, "Minhas LCoins");
	gInterface.DrawFormat((hasCoins ? eWhite : eRed), StartX + 115, 305, 70, 3, "%d", this->CurrentWCoin);

	gInterface.DrawGUI(ePREMIUM_INFOBG, StartX + 30, 320);
	gInterface.DrawFormat(eGold, StartX + 35, 325, 70, 3, "30 dias VIP LCoins");
	gInterface.DrawFormat(eWhite, StartX + 115, 325, 70, 3, "%d", this->NeedWCoin);

	gInterface.DrawGUI(ePREMIUM_VIP, ButtonX, gInterface.Data[ePREMIUM_FOOTER].Y + 10);
	gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[ePREMIUM_FOOTER].Y + 20, 210, 3, g_ExText.GetText(160));
	gInterface.DrawGUI(ePREMIUM_DIV, StartX, gInterface.Data[ePREMIUM_FOOTER].Y - 10);

	// ----
	gInterface.Data[ePREMIUM_VIP].Attribute = hasCoins;
	// ----
	if(!hasCoins || gInterface.IsWorkZone(ePREMIUM_VIP) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePREMIUM_VIP].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePREMIUM_VIP, gInterface.Data[ePREMIUM_VIP].X, gInterface.Data[ePREMIUM_VIP].Y, Color);
	}
}
// ----------------------------------------------------------------------------------------------

void PremiumSystemEx::Button(DWORD Event)
{
	if( gInterface.Button(Event, exWinPremium, ePREMIUM_CLOSE, false ) )
	{
		gInterface.CloseWindowEx(exWinPremium);
		return;
	}

	if( gInterface.Button(Event, exWinPremium, ePREMIUM_PAGEUP, false ) )
	{
		this->PremiumDay++;
		if(this->PremiumDay > 100)
		{
			this->PremiumDay = 100;
		}
		return;
	}

	if( gInterface.Button(Event, exWinPremium, ePREMIUM_PAGEDN, false ) )
	{
		this->PremiumDay--;
		if(this->PremiumDay <= 1)
		{
			this->PremiumDay = 1;
		}
		return;
	}

	if( gInterface.Button(Event, exWinPremium, ePREMIUM_CHECK1, false ) )
	{
		this->PremiumSwitch = eVip1;
	}

	if(!g_ExLicense.CheckUser(eExUB::SILVER1) && !g_ExLicense.CheckUser(eExUB::SILVER2))
	{
		if( gInterface.Button(Event, exWinPremium, ePREMIUM_CHECK2, false ) )
		{
			this->PremiumSwitch = eVip2;
		}

		if( gInterface.Button(Event, exWinPremium, ePREMIUM_CHECK3, false ) )
		{
			this->PremiumSwitch = eVip3;
		}
	}

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		if( gInterface.Button(Event, exWinPremium, ePREMIUM_CHECK4, false ) )
		{
			this->PriceSwitch = 0;
		}
		else if( gInterface.Button(Event, exWinPremium, ePREMIUM_CHECK5, false ) )
		{
			this->PriceSwitch = 1;
		}
	}

	if( gInterface.Button(Event,exWinPremium, ePREMIUM_FINISH, true ) )
	{
		CG_PREMIUM_BUY pRequest;
		pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x09, sizeof(pRequest));
		pRequest.PremiumType = this->PremiumSwitch;
		pRequest.PremiumDay = this->PremiumDay;
		pRequest.PriceType = this->PriceSwitch;
		gInterface.CloseWindowEx(exWinPremium);
		gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
		return;
	}

	if( gInterface.Button(Event,exWinPremium, ePREMIUM_VIP, true ) )
	{
		CG_PREMIUM_BUY pRequest;
		pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x16, sizeof(pRequest));
		gInterface.CloseWindowEx(exWinPremium);
		gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
		return;
	}
}
// ----------------------------------------------------------------------------------------------

void PremiumSystemEx::GC_RecvInfo(GC_PREMIUM_SEND* Recv)
{
	this->PremiumSwitch = eVip1;
	this->PremiumDay = 1;

	if(gObjUser.PremiumType > 0 && gObjUser.PremiumType <=3 )
	{
		this->PremiumSwitch = gObjUser.PremiumType;
	}

	this->Buy1CreditDay = Recv->Buy1CreditDay;
	this->Buy2CreditDay = Recv->Buy2CreditDay;
	this->Buy3CreditDay = Recv->Buy3CreditDay;
	gObjUser.ExCred = Recv->UserCredit;
	this->m_iOfflineModePickUpPremiumRang = Recv->OfflineModePickUpPremiumRang;
	this->Buy1WCoinDay = Recv->Buy1WCoinDay;
	this->Buy2WCoinDay = Recv->Buy2WCoinDay;
	this->Buy3WCoinDay = Recv->Buy3WCoinDay;

	gInterface.OpenWindowEx(exWinPremium);
}
// ----------------------------------------------------------------------------------------------

void PremiumSystemEx::CG_SendOpenWindows()
{
	if(gInterface.CheckWindowEx(exWinPremium))
	{
		return;
	}

	CG_SEND_OPEND_WIN pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x0A, sizeof(pRequest));
	pRequest.Result = 1;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

char* PremiumSystemEx::GetName(int Number)
{
	if(Number == eVip1)
	{
		return g_ExText.GetText(162);
	}
	if(Number == eVip2)
	{
		return g_ExText.GetText(163);
	}
	if(Number == eVip3)
	{
		return g_ExText.GetText(164);
	}

	return g_ExText.GetText(165);
}
// ----------------------------------------------------------------------------------------------

void PremiumSystemEx::GC_Config(GC_PREMIUM_CONFIG* lpMsg)
{
	this->m_iOfflineModeAttackFreePremiumRang = lpMsg->OfflineModeAttackFreePremiumRang;
	this->m_iOfflineModePickUpPremiumRang = lpMsg->OfflineModePickUpPremiumRang;
}
// ----------------------------------------------------------------------------------------------



void PremiumSystemEx::GC_RecvVIPInfo(GC_VIP_SEND* Recv)
{
	this->NeedWCoin = Recv->Price;
	this->CurrentWCoin = Recv->WCoin;

	this->m_VIPDaysLeft = (gObjUser.Premium > 0 ? (((gObjUser.Premium - 1) / ONE_VIP_DAY) + 1) : 0);

	gInterface.OpenWindowEx(exWinPremium);
}