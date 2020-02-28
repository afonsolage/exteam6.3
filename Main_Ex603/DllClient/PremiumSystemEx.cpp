#include "stdafx.h"
#include "PremiumSystemEx.h"
#include "Interface.h"
#include "User.h"
#include "Protocol.h"
#include "ExUtils.h"
#include "ExLicense.h"
#include "ExText.h"
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

	this->Buy1CreditDay = 0;
	this->Buy2CreditDay = 0;
	this->Buy3CreditDay = 0;
	this->Buy1WCoinDay = 0;
	this->Buy2WCoinDay = 0;
	this->Buy3WCoinDay = 0;

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

	op2_ch.OZT -> галочка
	newui_option_check.OZT - галочка 2 - 0x7B69

	newui_commamd_Line.OZJ - линия
	newui_option_line.OZJ - линия по длиньше

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
	gInterface.BindObject(ePREMIUM_FINISH, 0x7A5E, 108, 29, -1, -1);

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
	gInterface.DrawGUI(ePREMIUM_INFOBG, StartX + 30, 140);

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		if(this->PriceSwitch == 0)
		{
			gInterface.DrawFormat(eGold, StartX + 35, 145, 70, 3, g_ExText.GetText(46));
			gInterface.DrawFormat(eWhite, StartX + 115, 145, 70, 3, "%d", (int)gObjUser.ExCred); // if full reset
		}
		else
		{
			gInterface.DrawFormat(eGold, StartX + 35, 145, 70, 3, g_ExText.GetText(141));
			gInterface.DrawFormat(eWhite, StartX + 115, 145, 70, 3, "%d", (int)gObjUser.WCoinC); // if full reset
		}
	}
	else
	{
		if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
		{
			gInterface.DrawFormat(eGold, StartX + 35, 145, 70, 3, g_ExText.GetText(140));
			gInterface.DrawFormat(eWhite, StartX + 115, 145, 70, 3, "%d", (int)gObjUser.WCoinC); // if full reset
		}
		else
		{
			gInterface.DrawFormat(eGold, StartX + 35, 145, 70, 3, g_ExText.GetText(46));
			gInterface.DrawFormat(eWhite, StartX + 115, 145, 70, 3, "%d", (int)gObjUser.ExCred); // if full reset
		}

	}
	
	gInterface.DrawGUI(ePREMIUM_INFOBG, StartX + 30, 160);
	gInterface.DrawFormat(eGold, StartX + 35, 165, 70, 3, g_ExText.GetText(152));
	gInterface.DrawFormat(eWhite, StartX + 115, 165, 70, 3, "%s", this->GetName(gObjUser.PremiumType));

	gInterface.DrawGUI(ePREMIUM_INFOBG, StartX + 30, 180);
	gInterface.DrawFormat(eGold, StartX + 35, 185, 70, 3, g_ExText.GetText(153));

	char Buff[256] = { 0 };
	strncpy(Buff, GetDate(gObjUser.Premium, 2), 256);

	gInterface.DrawFormat(eWhite, StartX + 115, 185, 70, 3, "%s", Buff);


	// ----
	gInterface.DrawGUI(ePREMIUM_DIV, StartX, 205);
	// ----
	
	gInterface.DrawGUI(ePREMIUM_POINT1, StartX + 35, 233);
	gInterface.DrawFormat(eWhite, StartX + 60, 235, 70, 1, g_ExText.GetText(154));
	if(this->PremiumSwitch == eVip1)
	{
		gInterface.DrawGUIY(ePREMIUM_CHECK1, StartX + 175, 231, 0);
	}
	else
	{
		gInterface.DrawGUIY(ePREMIUM_CHECK1, StartX + 175, 231, 1);
	}
	gInterface.DrawGUI(ePREMIUM_LINE1, StartX + 35, 245);
	// --
	/* */
	if(!g_ExLicense.CheckUser(eExUB::SILVER1) && !g_ExLicense.CheckUser(eExUB::SILVER2))
	{
		gInterface.DrawGUI(ePREMIUM_POINT2, StartX + 35, 253);
		gInterface.DrawFormat(eWhite, StartX + 60, 255, 70, 1, g_ExText.GetText(155));
		if(this->PremiumSwitch == eVip2)
		{
			gInterface.DrawGUIY(ePREMIUM_CHECK2, StartX + 175, 251, 0);
		}
		else
		{
			gInterface.DrawGUIY(ePREMIUM_CHECK2, StartX + 175, 251, 1);
		}
		gInterface.DrawGUI(ePREMIUM_LINE2, StartX + 35, 265);
		// --
		gInterface.DrawGUI(ePREMIUM_POINT3, StartX + 35, 273);
		gInterface.DrawFormat(eWhite, StartX + 60, 275, 70, 1, g_ExText.GetText(156));
		if(this->PremiumSwitch == eVip3)
		{
			gInterface.DrawGUIY(ePREMIUM_CHECK3, StartX + 175, 271, 0);
		}
		else
		{
			gInterface.DrawGUIY(ePREMIUM_CHECK3, StartX + 175, 271, 1);
		}
		gInterface.DrawGUI(ePREMIUM_LINE3, StartX + 35, 285);
	}
	/* */
	// --
	gInterface.DrawGUI(ePREMIUM_POINT3, StartX + 35, 293);
	gInterface.DrawFormat(eWhite, StartX + 60, 295, 70, 1, g_ExText.GetText(157));

	if( gInterface.Data[ePREMIUM_PAGEDN].OnClick )
	{
		gInterface.DrawGUIY(ePREMIUM_PAGEDN, StartX + 130, 291, 1);
	}
	else
	{
		gInterface.DrawGUIY(ePREMIUM_PAGEDN, StartX + 130, 291, 0);
	}
	
	pDrawColorButton(0x7880, StartX + 150, 293, 20, 13, 0, 0, Color4f(0, 0, 0, 255));	

	gInterface.DrawFormat(eWhite, StartX + 125, 295, 70, 3, "%d", this->PremiumDay);

	if( gInterface.Data[ePREMIUM_PAGEUP].OnClick )
	{
		gInterface.DrawGUIY(ePREMIUM_PAGEUP, StartX + 175, 291, 1);
	}
	else
	{
		gInterface.DrawGUIY(ePREMIUM_PAGEUP, StartX + 175, 291, 0);
	}
	
	gInterface.DrawGUI(ePREMIUM_LINE3, StartX + 35, 305);
	// ----

	//================

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		/*gInterface.DrawFormat(eGold, StartX + 60, 315, 210, 1, "Credit");
		gInterface.DrawFormat(eGold, StartX + 140, 315, 210, 1, "WCoin");

		if(this->PriceSwitch == 0)
		{
			gInterface.DrawGUIY(ePREMIUM_CHECK4, StartX + 40, 310, 0);
			gInterface.DrawGUIY(ePREMIUM_CHECK5, StartX + 120, 310, 1);
		}
		else
		{
			gInterface.DrawGUIY(ePREMIUM_CHECK4, StartX + 40, 310, 1);
			gInterface.DrawGUIY(ePREMIUM_CHECK5, StartX + 120, 310, 0);
		}*/

		gInterface.DrawGUI(ePREMIUM_MONEYBG, StartX + 30, 327-10);

		gInterface.DrawFormat(eGold, StartX + 40, 332-10, 210, 1, g_ExText.GetText(46));


		gInterface.DrawGUI(ePREMIUM_MONEYBG, StartX + 30, 327+10);

		gInterface.DrawFormat(eGold, StartX + 40, 332+10, 210, 1, g_ExText.GetText(140));


		if(this->PremiumSwitch == eVip1)
		{
			this->NeedWCoin = this->Buy1WCoinDay * this->PremiumDay;
		}
		else if(this->PremiumSwitch == eVip2)
		{
			this->NeedWCoin = this->Buy2WCoinDay * this->PremiumDay;
		}	
		else
		{
			this->NeedWCoin = this->Buy3WCoinDay * this->PremiumDay;
		}

		if(this->PremiumSwitch == eVip1)
		{
			this->NeedCredit = this->Buy1CreditDay * this->PremiumDay;
		}
		else if(this->PremiumSwitch == eVip2)
		{
			this->NeedCredit = this->Buy2CreditDay * this->PremiumDay;
		}	
		else
		{
			this->NeedCredit = this->Buy3CreditDay * this->PremiumDay;
		}

		//if(this->PriceSwitch == 0)
		{
			char MoneyBuff[50];
			pGetMoneyFormat((double)this->NeedCredit, MoneyBuff, 0);

			if( this->NeedCredit > gObjUser.ExCred )
			{
				gInterface.DrawFormat(eRed, StartX + 100, 332-10, 50, 3, "%s", MoneyBuff);
			}
			else
			{
				gInterface.DrawFormat(eGold, StartX + 100, 332-10, 50, 3, "%s", MoneyBuff);
			}
		}
		//else if(this->PriceSwitch == 1)
		{
			char MoneyBuff[50];
			pGetMoneyFormat((double)this->NeedWCoin, MoneyBuff, 0);

			if( this->NeedWCoin > gObjUser.WCoinC )
			{
				gInterface.DrawFormat(eRed, StartX + 100, 332+10, 50, 3, "%s", MoneyBuff);
			}
			else
			{
				gInterface.DrawFormat(eGold, StartX + 100, 332+10, 50, 3, "%s", MoneyBuff);
			}
		}

	}
	else
	{
		if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
		{
			gInterface.DrawFormat(eGold, StartX + 60, 315, 210, 1, g_ExText.GetText(158));
		}
		else
		{
			gInterface.DrawFormat(eGold, StartX + 60, 315, 210, 1, g_ExText.GetText(159));
		}

		gInterface.DrawGUI(ePREMIUM_MONEYBG, StartX + 30, 325);

		if(this->PremiumSwitch == eVip1)
		{
			this->NeedCredit = this->Buy1CreditDay * this->PremiumDay;
		}
		else if(this->PremiumSwitch == eVip2)
		{
			this->NeedCredit = this->Buy2CreditDay * this->PremiumDay;
		}	
		else
		{
			this->NeedCredit = this->Buy3CreditDay * this->PremiumDay;
		}

		if(this->PriceSwitch == 0)
		{
			char MoneyBuff[50];
			pGetMoneyFormat((double)this->NeedCredit, MoneyBuff, 0);

			if( this->NeedCredit > gObjUser.ExCred )
			{
				gInterface.DrawFormat(eRed, StartX + 100, 332, 50, 3, "%s", MoneyBuff);
			}
			else
			{
				gInterface.DrawFormat(eGold, StartX + 100, 332, 50, 3, "%s", MoneyBuff);
			}
		}
		else if(this->PriceSwitch == 1)
		{
			char MoneyBuff[50];
			pGetMoneyFormat((double)this->NeedWCoin, MoneyBuff, 0);

			if( this->NeedWCoin > gObjUser.WCoinC )
			{
				gInterface.DrawFormat(eRed, StartX + 100, 332, 50, 3, "%s", MoneyBuff);
			}
			else
			{
				gInterface.DrawFormat(eGold, StartX + 100, 332, 50, 3, "%s", MoneyBuff);
			}
		}
	}

	//===============

	// ----
	gInterface.DrawGUI(ePREMIUM_FINISH, ButtonX, gInterface.Data[ePREMIUM_FOOTER].Y + 10);
	gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[ePREMIUM_FOOTER].Y + 20, 210, 3, g_ExText.GetText(160));
	gInterface.DrawGUI(ePREMIUM_DIV, StartX, gInterface.Data[ePREMIUM_FOOTER].Y - 10);
	// ----

	if(this->PriceSwitch == 0)
	{
		if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
		{
			if(gObjUser.WCoinC <= 0 || this->NeedCredit > gObjUser.WCoinC)
			{
				gInterface.Data[ePREMIUM_FINISH].Attribute = false;
				gInterface.DrawColoredGUI(ePREMIUM_FINISH, gInterface.Data[ePREMIUM_FINISH].X, gInterface.Data[ePREMIUM_FINISH].Y, eGray150);
				return;
			}
		}
		else
		{
			if(gObjUser.ExCred <= 0 || this->NeedCredit > gObjUser.ExCred)
			{
				gInterface.Data[ePREMIUM_FINISH].Attribute = false;
				gInterface.DrawColoredGUI(ePREMIUM_FINISH, gInterface.Data[ePREMIUM_FINISH].X, gInterface.Data[ePREMIUM_FINISH].Y, eGray150);
				return;
			}

			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
			{
				if(gObjUser.WCoinC <= 0 || this->NeedWCoin > gObjUser.WCoinC)
				{
					gInterface.Data[ePREMIUM_FINISH].Attribute = false;
					gInterface.DrawColoredGUI(ePREMIUM_FINISH, gInterface.Data[ePREMIUM_FINISH].X, gInterface.Data[ePREMIUM_FINISH].Y, eGray150);
					return;
				}
			}
		}

	}
	else if(this->PriceSwitch == 1)
	{
		if(gObjUser.WCoinC <= 0 || this->NeedWCoin > gObjUser.WCoinC)
		{
			gInterface.Data[ePREMIUM_FINISH].Attribute = false;
			gInterface.DrawColoredGUI(ePREMIUM_FINISH, gInterface.Data[ePREMIUM_FINISH].X, gInterface.Data[ePREMIUM_FINISH].Y, eGray150);
			return;
		}
	}
	// ----
	gInterface.Data[ePREMIUM_FINISH].Attribute = true;
	// ----
	if( gInterface.IsWorkZone(ePREMIUM_FINISH) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePREMIUM_FINISH].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePREMIUM_FINISH, gInterface.Data[ePREMIUM_FINISH].X, gInterface.Data[ePREMIUM_FINISH].Y, Color);
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