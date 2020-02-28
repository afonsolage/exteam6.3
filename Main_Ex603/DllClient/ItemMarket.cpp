#include "stdafx.h"
#include "Interface.h"
#include "Protocol.h"
#include "Object.h"
#include "Controller.h"
#include "ItemMarket.h"
#include "Console.h"
#include "TMemory.h"

#if(DEV_PLAYERSHOP)

CItemMarket g_ItemMarket;

CItemMarket::CItemMarket()
{
	this->Init();
}

CItemMarket::~CItemMarket()
{
}

void CItemMarket::Init()
{
	this->m_Page = 0;
	this->m_ScrollY = 0;

	memset(this->m_Data, 0, sizeof(this->m_Data));

	BYTE ItemData[12];
	memset(ItemData, 0, sizeof(ItemData));

	ItemData[0] = 8;
	ItemData[1] = 30;

	for(int i = 0; i < MARKET_ITEM_MAX; i++)
	{
		this->AddItemList(ITEMGET(8, 30), 255.0, ItemData, this->m_Data[i]);
	}
}

void CItemMarket::Load()
{
	this->Init();

	//// -> 480px
	//SetByte((LPVOID)(0x004D9746+3), 0xE0);		//gl draw 480px
	//// -> 320px
	////SetByte((LPVOID)(0x004D9746+3), 0xF0);
	////SetByte((LPVOID)(0x004D9746+4), 0x00);

	//SetByte((LPVOID)(0x0080F683),   0xE9);	//disable userbar
	//SetByte((LPVOID)(0x0080F683+1), 0x97);
	//SetByte((LPVOID)(0x0080F683+2), 0x00);
	//SetByte((LPVOID)(0x0080F683+3), 0x00);
	//SetByte((LPVOID)(0x0080F683+4), 0x00);
}

void CItemMarket::LoadIMG()
{
	//gInterface.LoadImages("ExTeam\\Interface\\itembackpanel.tga", ex_ITEM_MARKET_BG, 0x2601, 0x2900, 1);
	gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\itembackpanel.tga", ex_ITEM_MARKET_BG, GL_LINEAR, GL_CLAMP, 1);

	gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\buy0.tga", ex_ITEM_MARKET_BUY0, GL_LINEAR, GL_CLAMP, 1);
	//gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\buy1.tga", ex_ITEM_MARKET_BUY1, GL_LINEAR, GL_CLAMP, 1);
	//gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\buy2.tga", ex_ITEM_MARKET_BUY2, GL_LINEAR, GL_CLAMP, 1);

	gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\page0.tga", ex_ITEM_MARKET_PAGE0, GL_LINEAR, GL_CLAMP, 1);
	//gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\page1.tga", ex_ITEM_MARKET_PAGE1, GL_LINEAR, GL_CLAMP, 1);
	//gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\page2.tga", ex_ITEM_MARKET_PAGE2, GL_LINEAR, GL_CLAMP, 1);
	//gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\page3.tga", ex_ITEM_MARKET_PAGE3, GL_LINEAR, GL_CLAMP, 1);
	//gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\page4.tga", ex_ITEM_MARKET_PAGE4, GL_LINEAR, GL_CLAMP, 1);
	//gInterface.LoadImages("ExTeam\\Interface\\ItemMarket\\page5.tga", ex_ITEM_MARKET_PAGE5, GL_LINEAR, GL_CLAMP, 1);
}

void CItemMarket::Bind()
{
	/*
		7E54 - ingame_Bt03.ozt
		7BAE - ingame_pack_check
		ingame_Tab_Up
		ingame_Bt_Reset
	*/

	gInterface.BindObject(eITEM_MARKET_BG, ex_ITEM_MARKET_BG, 152, 124, -1, -1);
	gInterface.BindObject(eITEM_MARKET_BUY0, ex_ITEM_MARKET_BUY0, 72, 30, -1, -1);
	//gInterface.BindObject(eITEM_MARKET_BUY1, ex_ITEM_MARKET_BUY1, 72, 30, -1, -1);
	//gInterface.BindObject(eITEM_MARKET_BUY2, ex_ITEM_MARKET_BUY2, 72, 30, -1, -1);
	gInterface.BindObject(eITEM_MARKET_CHECK, 0x7BAE, 15, 15, -1, -1);
	gInterface.BindObject(eITEM_MARKET_L, 0x7BAA, 17, 17, -1, -1);
	gInterface.BindObject(eITEM_MARKET_R, 0x7BAB, 17, 17, -1, -1);

	gInterface.BindObject(eITEM_MARKET_PAGE0, ex_ITEM_MARKET_PAGE0, 23, 23, -1, -1);
	//gInterface.BindObject(eITEM_MARKET_BUY1, ex_ITEM_MARKET_PAGE1, 72, 30, -1, -1);
	//gInterface.BindObject(eITEM_MARKET_BUY2, ex_ITEM_MARKET_PAGE2, 72, 30, -1, -1);
	gInterface.BindObject(eITEM_MARKET_PAGE3, ex_ITEM_MARKET_PAGE3, 72, 30, -1, -1);
	//gInterface.BindObject(eITEM_MARKET_BUY1, ex_ITEM_MARKET_PAGE4, 72, 30, -1, -1);
	//gInterface.BindObject(eITEM_MARKET_BUY1, ex_ITEM_MARKET_PAGE5, 72, 30, -1, -1);
}

void CItemMarket::DrawMain()
{
	this->DrawShop();
	this->DrawPrice();
}

void CItemMarket::DrawShop()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinItemMarket))
	{
		//return;
	}

	pSetCursorFocus = true;

	float flStartX = 0;
	float flStartY = 0;

	//gInterface.DrawGUI(eACHIEVEMENTS_MAIN, flStartX, flStartY);
	//pDrawColorButton(0x7880, flStartX, flStartY, 640, 440, 0, 0, Color4f(0, 0, 0, 200));	

	gInterface.DrawBarForm(flStartX, flStartY, 640, 440, 0, 0, 0, 255);	
	//gInterface.DrawBarForm(flStartX, flStartY, 640, 480, 0, 0, 0, 255);	

	gInterface.DrawMiniBar(flStartX, flStartY, 30);

	gInterface.DrawFormat(eGold, 260, flStartY + 4, 100, 4, "ITEM MARKET");

	//gInterface.DrawGUI(eITEM_MARKET_CHECK, flStartX + 20, flStartY);
	gInterface.DrawGUIY(eITEM_MARKET_CHECK, flStartX + 20, flStartY, 0);
	gInterface.DrawGUIY(eITEM_MARKET_CHECK, flStartX + 50, flStartY, 1);

	// ----
	float flWhith = 125.0;	//90.0;	//100;	//125.0;	//152.0
	float flHigh  =	101.0;	//73.0;	//81;		//101.0;	//124.0
	float flDrawX = 0;
	float flDrawY = 0;
	float flLeftX = 110.0;
	float flAddX = flWhith + 6;//130;
	float flAddY = flHigh + 25;//140;

#if(MARKET_ITEM_VERSION == 1)

	flDrawY = 30;

	for(int i = 0; i < 3; i++)
	{
		flDrawX = flLeftX;
		
		for(int j = 0; j < 4; j++)
		{			
			this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);
			flDrawX += flAddX;
		}

		flDrawY += flAddY;
	}

#else

	flDrawX = flLeftX;
	//flDrawY = flStartY + 25;//50;
	flDrawY = this->m_ScrollY + 25;//50;
	
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	//flDrawX += flAddX;
	//this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	//flDrawX += flAddX;
	//this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	// ----

	flDrawX = flLeftX;
	flDrawY += flAddY;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	//flDrawX += flAddX;
	//this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	//flDrawX += flAddX;
	//this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	// ----

	flDrawX = flLeftX;
	flDrawY += flAddY;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	//flDrawX += flAddX;
	//this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	//flDrawX += flAddX;
	//this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	// ----

	flDrawX = flLeftX;
	flDrawY += flAddY;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	flDrawX += flAddX;
	this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	//flDrawX += flAddX;
	//this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

	//flDrawX += flAddX;
	//this->DrawItem(flWhith, flHigh, flDrawX, flDrawY, 8, 30, 15);

#endif
	/*
	flDrawX = 20.0;
	flDrawY = 50.0;

	gInterface.DrawSizeGUI(eITEM_MARKET_BUY0, 50, 21, ContentX + Width - 50, ContentY + Height + 3, 0.56, 0.94);	//0.59, 0.95);
	gInterface.DrawFormat(eGold, ContentX + Width - 50, ContentY + Height + 3 + 5, 50, 3, "Buy");
	*/
	// ----
	/*
	flDrawX = flLeftX;
	flDrawY += flAddY;
	gInterface.DrawPage(eITEM_MARKET_PAGE0, eITEM_MARKET_PAGE3, this->m_Page, 999, flDrawX, flDrawY);
	*/
//gInterface.DrawSizeGUI(eITEM_MARKET_PAGE0, 50, 21, ContentX + Width - 50, ContentY + Height + 3, 0.56, 0.94);	//0.59, 0.95);

}

float gflIncSizeW = 0.59;
float gflIncSizeH = 0.95;
//float gflIncSizeW = 0.71;
//float gflIncSizeH = 1.17;

void CItemMarket::DrawItem(int Width, int Height, int X, int Y, int Type, int Index, int Level)
{
	float ContentX = X;
	float ContentY = Y;
	const int WidthValue = 24;
	const int HeightValue = 26;

	if(gController.wKeyBord == VK_LEFT)
	{
		gflIncSizeW -= 0.01;
	}
	else if(gController.wKeyBord == VK_RIGHT)
	{
		gflIncSizeW += 0.01;
	}
	else if(gController.wKeyBord == VK_UP)
	{	
		gflIncSizeH += 0.01;
	}
	else if(gController.wKeyBord == VK_DOWN)
	{
		gflIncSizeH -= 0.01;
	}

	gController.wKeyBord = NULL;
	
	gInterface.DrawSizeGUI(eITEM_MARKET_BG, Width, Height, ContentX, ContentY, 0.59, 0.95);	//0.59, 0.95);

	gConsole.Output(cGREEN, "W: %f - H: %f", gflIncSizeW, gflIncSizeH);

	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(ITEM(Type, Index));

	float barWidth = WidthValue * ItemInfo->ItemWidth;
	float barHeight = HeightValue * ItemInfo->ItemHeight;
	float flItemX = ContentX + ( Width / 2 ) - ( WidthValue * ItemInfo->ItemWidth / 2 );
	float flItemY = ContentY + ( Height / 2 ) - ( HeightValue * ItemInfo->ItemHeight / 2 );

	gInterface.DrawItem(flItemX, flItemY, barWidth, barHeight, ITEMGET(Type, Index), SET_ITEMOPT_LEVEL(Level), 1, 0, 0);

	//gInterface.DrawGUI(eITEM_MARKET_BUY, ContentX + flWhith, ContentY + flHigh);
	//gInterface.DrawSizeGUI(eITEM_MARKET_BUY0, 72, 30, ContentX, ContentY + Height, gflIncSizeW, gflIncSizeH);	//0.59, 0.95);
	gInterface.DrawSizeGUI(eITEM_MARKET_BUY0, 50, 21, ContentX + Width - 50, ContentY + Height + 3, 0.56, 0.94);	//0.59, 0.95);
	gInterface.DrawFormat(eGold, ContentX + Width - 50, ContentY + Height + 3 + 5, 50, 3, "Buy");

	//if(gInterface.IsWorkZoneObj(eSMITHY_ITEM_BG))
	{
		//gInterface.DrawItemToolTipText((void*)&this->m_Data[0], pCursorX + 80, pCursorY - 80 );
	}
}

void CItemMarket::DrawPrice()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinItemMarket2))
	{
		//return;
	}

	pSetCursorFocus = true;

//	DWORD ItemNameColor		= eWhite;
//	float MainWidth			= 230.0;
//	float MainHeight		= 250.0;
//	float StartY			= 100;
//	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
//	float MainCenter		= StartX + (MainWidth / 3);
//	float ButtonX			= MainCenter - (29.0 / 2);
//
//	float ContentX          = StartX;
//	float ContentY			= StartY;
//	// ----
//	gInterface.DrawGUI(ePS_PRICE_MAIN, StartX, StartY + 2);
//	gInterface.DrawGUI(ePS_PRICE_TITLE, StartX, StartY);
//	#if(DEV_PERSONAL_CREDIT)
//	StartY = gInterface.DrawRepeatGUI(ePS_PRICE_FRAME, StartX, StartY + 67.0, 8);
//	#else
//	StartY = gInterface.DrawRepeatGUI(ePS_PRICE_FRAME, StartX, StartY + 67.0, 6);
//	#endif
//	gInterface.DrawGUI(ePS_PRICE_FOOTER, StartX, StartY);
//	// ----
//	gInterface.DrawFormat(eGold, ContentX + 10, ContentY + 10, 210, 3, g_ExText.GetText(139));
//	// ----
//	ContentY += 40;
//	gInterface.DrawGUI(ePS_PRICE_ZEN, ContentX + 30, ContentY);
//	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ExText.GetText(47));
//	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->ZenText);
//	// ----
////#if(PERSONAL_BONUS==TRUE)
//	if(g_PersonalShopEx.iPERSONAL_BONUS == 1)
//	{
//		ContentY += 20;
//		gInterface.DrawGUI(ePS_PRICE_BONUS, ContentX + 30, ContentY);
//		gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ExText.GetText(46));
//		gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->BonusText);
//	}
//	else if(g_PersonalShopEx.iPERSONAL_BONUS == 2)
//	{
//		ContentY += 20;
//		gInterface.DrawGUI(ePS_PRICE_BONUS, ContentX + 30, ContentY);
//		gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ExText.GetText(140));
//		gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->BonusText);
//	}
////#endif
//	// ----
//	ContentY += 20;
//	gInterface.DrawGUI(ePS_PRICE_BLESS, ContentX + 30, ContentY);
//	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ExText.GetText(42));
//	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->BlessText);
//	// ----
//	ContentY += 20;
//	gInterface.DrawGUI(ePS_PRICE_SOUL, ContentX + 30, ContentY);
//	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ExText.GetText(43));
//	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->SoulText);
//	// ----
//	ContentY += 20;
//	gInterface.DrawGUI(ePS_PRICE_CHAOS, ContentX + 30, ContentY);
//	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ExText.GetText(41));
//	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->ChaosText);
//
//	ContentY += 20;
//	gInterface.DrawGUI(ePS_PRICE_LIFE, ContentX + 30, ContentY);
//	gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, g_ExText.GetText(44));
//	gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->LifeText);
//
//	#if(DEV_PERSONAL_CREDIT)
//	if(g_PersonalShopEx.iPERSONAL_CREDIT)
//	{
//		ContentY += 20;
//		gInterface.DrawGUI(ePS_PRICE_CREDIT, ContentX + 30, ContentY);
//		gInterface.DrawFormat(eGold, ContentX + 35, ContentY + 5, 70, 3, "Credit:");
//		gInterface.DrawFormat(eWhite, ContentX + 135, ContentY + 5, 70, 1, this->CreditText);
//	}
//	#endif
//
//	if(this->ActivePrice == ePSzen)
//	{
//		DWORD Color = eGray100;
//		gInterface.DrawColoredGUI(ePS_PRICE_ZEN, gInterface.Data[ePS_PRICE_ZEN].X, gInterface.Data[ePS_PRICE_ZEN].Y, Color);
//	}
////#if(PERSONAL_BONUS==TRUE)
//	if(g_PersonalShopEx.iPERSONAL_BONUS)
//	{
//		if(this->ActivePrice == ePSBonus)
//		{
//			DWORD Color = eGray100;
//			gInterface.DrawColoredGUI(ePS_PRICE_BONUS, gInterface.Data[ePS_PRICE_BONUS].X, gInterface.Data[ePS_PRICE_BONUS].Y, Color);
//		}
//	}
////#endif
//	if(this->ActivePrice == ePSBless)
//	{
//		DWORD Color = eGray100;
//		gInterface.DrawColoredGUI(ePS_PRICE_BLESS, gInterface.Data[ePS_PRICE_BLESS].X, gInterface.Data[ePS_PRICE_BLESS].Y, Color);
//	}
//	if(this->ActivePrice == ePSSoul)
//	{
//		DWORD Color = eGray100;
//		gInterface.DrawColoredGUI(ePS_PRICE_SOUL, gInterface.Data[ePS_PRICE_SOUL].X, gInterface.Data[ePS_PRICE_SOUL].Y, Color);
//	}
//	if(this->ActivePrice == ePSChaos)
//	{
//		DWORD Color = eGray100;
//		gInterface.DrawColoredGUI(ePS_PRICE_CHAOS, gInterface.Data[ePS_PRICE_CHAOS].X, gInterface.Data[ePS_PRICE_CHAOS].Y, Color);
//	}
//	if(this->ActivePrice == ePSLife)
//	{
//		DWORD Color = eGray100;
//		gInterface.DrawColoredGUI(ePS_PRICE_LIFE, gInterface.Data[ePS_PRICE_LIFE].X, gInterface.Data[ePS_PRICE_LIFE].Y, Color);
//	}
//	#if(DEV_PERSONAL_CREDIT)
//	if(g_PersonalShopEx.iPERSONAL_CREDIT)
//	{
//		if(this->ActivePrice == ePSCredit)
//		{
//			DWORD Color = eGray100;
//			gInterface.DrawColoredGUI(ePS_PRICE_CREDIT, gInterface.Data[ePS_PRICE_CREDIT].X, gInterface.Data[ePS_PRICE_CREDIT].Y, Color);
//		}
//	}
//	#endif
//
//	// -> Button
//	ContentY += 30;
//	gInterface.DrawGUI(ePS_PRICE_OK, StartX+30, ContentY - 5);
//	gInterface.DrawFormat(eWhite, StartX + 35, ContentY+5, 50, 3, g_ExText.GetText(120));
//
//	if( gInterface.IsWorkZone(ePS_PRICE_OK) )
//	{
//		DWORD Color = eGray100;
//		// ----
//		if( gInterface.Data[ePS_PRICE_OK].OnClick )
//		{
//			Color = eGray150;
//		}
//		// ----
//		gInterface.DrawColoredGUI(ePS_PRICE_OK, gInterface.Data[ePS_PRICE_OK].X, gInterface.Data[ePS_PRICE_OK].Y, Color);
//	}
//	// ---- 
//	gInterface.DrawGUI(ePS_PRICE_CLOSE, StartX + 70 + 62, ContentY - 5 );
//	gInterface.DrawFormat(eWhite, StartX + 75 + 62, ContentY+5, 50, 3, g_ExText.GetText(129));
//
//	if( gInterface.IsWorkZone(ePS_PRICE_CLOSE) )
//	{
//		DWORD Color = eGray100;
//		// ----
//		if( gInterface.Data[ePS_PRICE_CLOSE].OnClick )
//		{
//			Color = eGray150;
//		}
//		// ----
//		gInterface.DrawColoredGUI(ePS_PRICE_CLOSE, gInterface.Data[ePS_PRICE_CLOSE].X, gInterface.Data[ePS_PRICE_CLOSE].Y, Color);
//	}
}

void CItemMarket::DrawToolTip(BYTE* Buffer, float X, float Y)
{

}

void CItemMarket::Button(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinItemMarket))
	{
		//return;
	}
}

void CItemMarket::Scroll(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinItemMarket))
	{
		//return;
	}

	if(wParam != WM_MOUSEWHEEL)
	{
		return;
	}

	if((int)Mouse->mouseData > 0)
	{
		//if(this->m_ScrollY < 480)
		{
			this->m_ScrollY -= 10;
		}
	}
	else if((int)Mouse->mouseData < 0)
	{
		//if(this->m_ScrollY > 0)
		{
			this->m_ScrollY += 10;
		}
	}
}

void CItemMarket::RecvItemList(PMSG_SEND_MARKET_ITEM* lpMsg)
{
	if(lpMsg->Result == 0)
	{
		//this->m_dwItemRecv = false;
		return;
	}

	for(int i = 0; i < MARKET_ITEM_MAX; i++)
	{
		//this->AddItemList(ITEMGET(8, 30), 255.0, lpMsg->Info[i].ItemData, this->m_Data[i]);

		this->AddItemList(lpMsg->Info[i].ItemType, lpMsg->Info[i].ItemDurability, lpMsg->Info[i].ItemData, this->m_Data[i]);
	
		//pSetItemOption(&this->m_Data[i], Data[1], Data[3], Data[4]);
	}
}

void CItemMarket::AddItemList(short Type, float Durability, LPBYTE Data, ObjectItem Item)
{
	//memset(&this->m_Data, 0, sizeof(this->m_Data));

	DWORD dwAddress = (DWORD)&Item;

	*(WORD *)dwAddress = Type;
	int a5 = Durability;
	*(BYTE *)(dwAddress + 22) = a5;
	int a6 = Data[3];
	*(BYTE *)(dwAddress + 23) = a6;
	int a7 = Data[4];
	*(BYTE *)(dwAddress + 24) = a7;
	int a8 = Data[5];
	*(BYTE *)(dwAddress + 97) = (a8 & 2) >> 1 > 0;
	*(BYTE *)(dwAddress + 98) = (a8 & 4) >> 2 > 0;
	*(BYTE *)(dwAddress + 73) = 16 * (a8 & 8) >> 7 > 0;
	int a9 = Data[6];
	*(WORD *)(dwAddress + 69) = (a9 & 0xF0) >> 4;
	*(WORD *)(dwAddress + 71) = a9 & 0xF;

	DWORD a10 = (DWORD)&Data[7];

	if ( a10 )
	{
		*(BYTE *)(dwAddress + 79) = 5;

		for (int i = 0; i < 5; ++i )
			*(BYTE *)(i + dwAddress + 74) = *(BYTE *)(i + a10);

		for (int j = 0; j < 5; ++j )
		{
			if ( *(BYTE *)(j + a10) == 255 )
			{
				*(BYTE *)(dwAddress + 79) = j;
				break;
			}

			if ( *(BYTE *)(j + a10) == 254 )
			{
				*(BYTE *)(j + dwAddress + 80) = -1;
			}
			else
			{
				*(BYTE *)(j + dwAddress + 80) = *(BYTE *)(j + a10) % 50;
				*(BYTE *)(j + dwAddress + 85) = *(BYTE *)(j + a10) / 50 + 1;
			}
		}

		if ( this->CheckItemInfo(*(WORD *)dwAddress) )
		{
			*(BYTE *)(dwAddress + 90) = a9;
			*(WORD *)(dwAddress + 69) = 0;
			*(WORD *)(dwAddress + 71) = 0;
		}
		else
		{
			*(BYTE *)(dwAddress + 90) = -1;
		}
	}
	else
	{
		*(BYTE *)(dwAddress + 79) = 0;
	}

	*(BYTE *)(dwAddress + 96) = 0;
    *(DWORD *)(dwAddress + 103) = 1;

	pSetItemOption(&Item, Data[1], Data[3], Data[4]);

	//this->m_dwItemRecv = true;
}

int CItemMarket::CheckItemInfo(signed int a1)
{
	if ( a1 > 3092 )
	{
		if ( a1 > 4661 )
		{
			if ( a1 > 5685 || a1 < 5676 && (a1 < 5164 || a1 > 5173) )
				return 0;
		}
		else if ( a1 < 4652 && (a1 > 4149 || a1 < 4140 && (a1 < 3628 || a1 > 3637)) )
		{
			return 0;
		}

		return 1;
	}

	if ( a1 >= 3089 )
		return 1;

	if ( a1 > 2071 )
	{
		if ( a1 != 2580 && (a1 <= 2589 || a1 > 2592) )
			return 0;
		return 1;
	}

	if ( a1 == 2071 || a1 <= 1041 && (a1 >= 1040 || a1 >= 26 && a1 <= 28) )
		return 1;

	return 0;
}

#endif