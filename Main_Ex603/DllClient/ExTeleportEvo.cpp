#include "stdafx.h"
#include "ExTeleportEvo.h"
#include "Interface.h"
#include "Protocol.h"

#if(CUSTOM_EX_TELEPORT_EVO==TRUE)

ExTeleportEvo g_ExTeleportEvo;
// ----------------------------------------------------------------------------------------------

ExTeleportEvo::ExTeleportEvo()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

ExTeleportEvo::~ExTeleportEvo()
{
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::Init()
{
	ZeroMemory(this->data, sizeof(this->data));
	this->iLoadedCount = 0;
	this->ClickPage = -1;

	this->LenCount = 0;
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::LoadImages()
{
	//pLoadImage("ExData\\Interface\\PartySearch_Title.tga", ex_PEROSNAL_SEATCH_TITLE, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\newui_cha_textbox03.tga", ex_EXTELEPORT_TITLE, 0x2601, 0x2900, 1, 0);
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::BindImages()
{
	gInterface.BindObject(eTELEPORT_MAIN, 0x7A5A, 222, 273, -1, -1);
	gInterface.BindObject(eTELEPORT_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eTELEPORT_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eTELEPORT_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eTELEPORT_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eTELEPORT_LINE, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eTELEPORT_POINT, 0x7B68, 10, 10, -1, -1);

	gInterface.BindObject(eTELEPORT_BT1, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT2, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT3, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT4, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT5, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT6, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT7, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT8, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT9, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eTELEPORT_BT10, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eTELEPORT_BT_CANCELE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eTELEPORT_PAGEUP1, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP2, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP3, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP4, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP5, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP6, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP7, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP8, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP9, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_PAGEUP10, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);

	gInterface.BindObject(eTELEPORT_MAPNAME, ex_EXTELEPORT_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eTELEPORT_INFOBG, 0x7AA3, 170, 21, -1, -1);
	
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::Draw()
{
	if(!gInterface.CheckWindowEx(exWinTeleportEvo))
	{
		return;
	}

	pSetCursorFocus = true;

	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100;	//100
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentX          = StartX;
	float ContentY			= StartY;

	int RepDiv = 11;//this->iLoadedCount * 2 + 1 ;
	//gInterface.BindObject(eTELEPORT_MAIN, 0x7A5A, 222, RepDiv * 23.30769, -1, -1);

	// ----
	gInterface.DrawGUI(eTELEPORT_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eTELEPORT_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eTELEPORT_FRAME, StartX, StartY + 67.0, RepDiv);
	gInterface.DrawGUI(eTELEPORT_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eTELEPORT_CLOSE, StartX + MainWidth - gInterface.Data[eTELEPORT_CLOSE].Width, ContentY);
	// ----
	if( gInterface.IsWorkZone(eTELEPORT_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eTELEPORT_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eTELEPORT_CLOSE, gInterface.Data[eTELEPORT_CLOSE].X, gInterface.Data[eTELEPORT_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eTELEPORT_CLOSE].X + 5, gInterface.Data[eTELEPORT_CLOSE].Y + 25, "Close");
	}
	// ----
	gInterface.DrawFormat(eGold, ContentX + 10, ContentY + 10, 210, 3, "Teleport Master");
	// -> Draw Listing
	
	float ListX = ContentX;
	float ListY = ContentY;
	DWORD ListColor = eWhite;
	
	if(this->ClickPage >= 0 && this->ClickPage < MAXEXTELEPORT)
	{
		int i = this->ClickPage;

		int iLenPlus = 21;

		float PlusY = (7 - this->LenCount) * 10.5;
		PlusY += 27/2;
		//PlusY = -5;
		ListY = 130;
		gInterface.DrawGUI(eTELEPORT_MAPNAME, ListX + 30, ListY + PlusY);
		gInterface.DrawFormat(eAncient, ListX + 63, ListY + 5 + PlusY, 100, 3, pGetMapName(this->data[i].map));
		// -> level
		PlusY += 25;
		if(this->data[i].min_level > 0 || this->data[i].max_level > 0)
		{
			ListColor = eWhite;
			if(!this->data[i].ok_level)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, ListX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, ListX + 35, ListY + 5 + PlusY, 70, 3, "Level:");
			gInterface.DrawFormat(ListColor, ListX + 135, ListY + 5 + PlusY, 70, 1, "%d - %d", this->data[i].min_level, this->data[i].max_level);
		}
		// -> reset
		if(this->data[i].min_reset >= 0 || this->data[i].max_reset > 0)
		{
			PlusY += iLenPlus;
			ListColor = eWhite;
			if(!this->data[i].ok_reset)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, StartX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, StartX + 35, ListY + 5 + PlusY, 70, 3, "Reset:");
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "%d - %d", this->data[i].min_reset, this->data[i].max_reset);
		}
		// -> grand
		if(this->data[i].min_grand >= 0 || this->data[i].max_grand > 0)
		{
			PlusY += iLenPlus;
			ListColor = eWhite;
			if(!this->data[i].ok_grand)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, StartX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, StartX + 35, ListY + 5 + PlusY, 70, 3, "Grand Reset:");
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "%d - %d", this->data[i].min_grand, this->data[i].max_grand);
		}
		// -> premium
		if(this->data[i].premium > 0)
		{
			PlusY += 22;
			ListColor = eWhite;
			if(!this->data[i].ok_premium)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, StartX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, StartX + 35, ListY + 5 + PlusY, 70, 3, "Premium:");
#if(LICENSE_MUEVIL)
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "Vip %d level", this->data[i].premium);
#else
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "On");
#endif
		}
		// -> zen
		if(this->data[i].zen > 0)
		{
			PlusY += iLenPlus;
			ListColor = eWhite;
			if(!this->data[i].ok_zen)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, StartX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, StartX + 35, ListY + 5 + PlusY, 70, 3, "Zen:");
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "%d", this->data[i].zen);
		}
		// -> bonus
		if(this->data[i].bonus > 0)
		{
			PlusY += iLenPlus;
			ListColor = eWhite;
			if(!this->data[i].ok_bonus)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, StartX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, StartX + 35, ListY + 5 + PlusY, 70, 3, "WCoin:");
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "%d", this->data[i].bonus);
		}
		// -> credit
		if(this->data[i].credit > 0)
		{
			PlusY += iLenPlus;
			ListColor = eWhite;
			if(!this->data[i].ok_credit)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, StartX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, StartX + 35, ListY + 5 + PlusY, 70, 3, "Credits:");
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "%d", this->data[i].credit);
		}
		// -> master
		if(this->data[i].Master > 0)
		{
			PlusY += iLenPlus;
			ListColor = eWhite;
			if(!this->data[i].ok_Master)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, StartX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, StartX + 35, ListY + 5 + PlusY, 70, 3, "Class:");
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "Master");
		}
		// -> EmptyInv
		if(this->data[i].EmptyInv > 0)
		{
			PlusY += iLenPlus;
			ListColor = eWhite;
			if(!this->data[i].ok_EmptyInv)
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_INFOBG, StartX + 30, ListY + PlusY);
			gInterface.DrawFormat(eYellow, StartX + 35, ListY + 5 + PlusY, 70, 3, "Inventory:");
			gInterface.DrawFormat(ListColor, StartX + 135, ListY + 5 + PlusY, 70, 1, "Empty");
		}
		// -> next 
		PlusY += 25;
		ContentX += 35;
		ContentY = ListY + PlusY;

		//gInterface.DrawGUI(eTELEPORT_LINE, ContentX,  ContentY);

		//ContentY += 10;
		gInterface.DrawButtonMini(eTELEPORT_BT1 + this->ClickPage, ContentX, ContentY, this->data[i].result, "Ok");
		gInterface.DrawButtonMini(eTELEPORT_BT_CANCELE, ContentX+95, ContentY, TRUE, "Cancel");



		//gInterface.DrawPriceEx(ContentX+10, ContentY - 5, this->data[i].zen, this->data[i].ok_zen, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
		//	this->data[i].bonus, this->data[i].ok_bonus, this->data[i].credit, this->data[i].ok_credit, this->data[i].premium, this->data[i].ok_premium);
		//gInterface.DrawGUI(eTELEPORT_LINE, ContentX,  ContentY + 40);
		ContentY += 45;


		//----------------------------------------
		/*
		int i = this->ClickPage;
		DWORD ListColor = 0;
		ContentX += 20 + 15;
		ContentY += 77;	//30
		// -> Teleport Name
		gInterface.DrawGUI(eTELEPORT_POINT, ContentX +45, ContentY + 10);
		gInterface.DrawFormat(eGold, ContentX + 60, ContentY + 10, 210, 1, pGetMapName(this->data[i].map));	
		gInterface.DrawGUI(eTELEPORT_LINE, ContentX,  ContentY + 21);
		// -> Need Info
		float plusX = 15;
		float plusY = 32;
		// -> Level
		if(this->data[i].ok_level == true)
		{
			ListColor = eYellow;
		}
		else
		{
			ListColor = eRed;
		}
		gInterface.DrawGUI(eTELEPORT_POINT, ContentX + plusX, ContentY + plusY);
		gInterface.DrawFormat(ListColor, ContentX + plusX + 15, ContentY + plusY, 210, 1, "Level: %d", this->data[i].level);	
		// -> Reset
		if(this->data[i].ok_reset == true)
		{
			ListColor = eYellow;
		}
		else
		{
			ListColor = eRed;
		}
		plusY += 15;
		gInterface.DrawGUI(eTELEPORT_POINT, ContentX + plusX, ContentY + plusY);
		gInterface.DrawFormat(ListColor, ContentX + plusX + 15, ContentY + plusY, 210, 1, "Reset: %d", this->data[i].reset);	
		// -> Grand
		if(this->data[i].ok_grand == true)
		{
			ListColor = eYellow;
		}
		else
		{
			ListColor = eRed;
		}
		plusY += 15;
		gInterface.DrawGUI(eTELEPORT_POINT, ContentX + plusX, ContentY + plusY);
		gInterface.DrawFormat(ListColor, ContentX + plusX + 15, ContentY + plusY, 210, 1, "Grand: %d", this->data[i].grand);	

		// -> Need Buy
		float plus_X = 75;
		float plus_Y = 25;

		int total = 0;

		if(this->data[i].zen > 0)
		{
			total++;
		}
		if(this->data[i].bonus > 0)
		{
			total++;
		}
		if(this->data[i].credit > 0)
		{
			total++;
		}
		if(this->data[i].premium > 0)
		{
			total++;
		}

		if(total == 1)
		{
			plus_Y += 22.5;
		}
		else if(total == 2)
		{
			plus_Y += 15;
		}
		else if(total == 3)
		{
			plus_Y += 7.5;
		}

		// -> Zen
		if(this->data[i].zen > 0)
		{
			if(this->data[i].ok_zen == true)
			{
				ListColor = eYellow;
			}
			else
			{
				ListColor = eRed;
			}
			gInterface.DrawGUI(eTELEPORT_POINT, ContentX + plus_X, ContentY + plus_Y);
			gInterface.DrawFormat(ListColor, ContentX + plus_X + 15, ContentY + plus_Y, 210, 1, "Zen: %d", this->data[i].zen);	
		}
		// -> Bonus
		if(this->data[i].bonus > 0)
		{
			if(this->data[i].ok_bonus == true)
			{
				ListColor = eYellow;
			}
			else
			{
				ListColor = eRed;
			}
			plus_Y += 15;
			gInterface.DrawGUI(eTELEPORT_POINT, ContentX + plus_X, ContentY + plus_Y);
			gInterface.DrawFormat(ListColor, ContentX + plus_X + 15, ContentY + plus_Y, 210, 1, "Bonus: %d", this->data[i].bonus);	
		}
		// -> Credits
		if(this->data[i].credit > 0 )
		{
			if(this->data[i].ok_credit == true)
			{
				ListColor = eYellow;
			}
			else
			{
				ListColor = eRed;
			}
			plus_Y += 15;
			gInterface.DrawGUI(eTELEPORT_POINT, ContentX + plus_X, ContentY + plus_Y);
			gInterface.DrawFormat(ListColor, ContentX + plus_X + 15, ContentY + plus_Y, 210, 1, "Credits: %d", this->data[i].credit);	
		}
		// -> Premium
		if(this->data[i].premium > 0)
		{
			if(this->data[i].ok_premium == true)
			{
				ListColor = eYellow;
			}
			else
			{
				ListColor = eRed;
			}
			plus_Y += 15;
			gInterface.DrawGUI(eTELEPORT_POINT, ContentX + plus_X, ContentY + plus_Y);
			gInterface.DrawFormat(ListColor, ContentX + plus_X + 15, ContentY + plus_Y, 210, 1, "Premium Status", this->data[i].premium);	
		}
		// -> Master
		if(this->data[i].Master > 0)
		{
			if(this->data[i].ok_Master == true)
			{
				ListColor = eYellow;
			}
			else
			{
				ListColor = eRed;
			}
			plus_Y += 15;
			gInterface.DrawGUI(eTELEPORT_POINT, ContentX + plus_X, ContentY + plus_Y);
			gInterface.DrawFormat(ListColor, ContentX + plus_X + 15, ContentY + plus_Y, 210, 1, "Class: Master");	
		}
		// -> next 

		gInterface.DrawGUI(eTELEPORT_LINE, ContentX,  ContentY + 80);

		gInterface.DrawButtonMini(eTELEPORT_BT1 + this->ClickPage, ContentX, ContentY+90, this->data[i].result, "Ok");
		gInterface.DrawButtonMini(eTELEPORT_BT_CANCELE, ContentX+89, ContentY+90, TRUE, "Cancel");



		//gInterface.DrawPriceEx(ContentX+10, ContentY - 5, this->data[i].zen, this->data[i].ok_zen, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
		//	this->data[i].bonus, this->data[i].ok_bonus, this->data[i].credit, this->data[i].ok_credit, this->data[i].premium, this->data[i].ok_premium);
		//gInterface.DrawGUI(eTELEPORT_LINE, ContentX,  ContentY + 40);
		ContentY += 45;
		*/
	}
	else
	{
		for(int i = 0; i < this->iLoadedCount; i++)
		{
			int ply = 37;
			gInterface.DrawGUI(eTELEPORT_PAGEUP1 + i, ListX + 10 + 18, ListY + ply + i * 22);
			gInterface.DrawFormat(eAncient, ListX  + 63, ListY + ply + 4 + i * 22, 100, 3, pGetMapName(this->data[i].map));
			if(gInterface.IsWorkZone(eTELEPORT_PAGEUP1 + i))
			{
				DWORD Color = eGray100;
				if( gInterface.Data[eTELEPORT_PAGEUP1 + i].OnClick )
				{
					Color = eGray150;
				}
				gInterface.DrawColoredGUI(eTELEPORT_PAGEUP1 + i, gInterface.Data[eTELEPORT_PAGEUP1 + i].X, gInterface.Data[eTELEPORT_PAGEUP1 + i].Y, Color);
			}
		}
	}
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::GCWindows(PMSG_GC_TELEPORTWINEVO* aRecv)
{
	this->Init();

	this->iLoadedCount = aRecv->count;

	for(int i=0; i < this->iLoadedCount; i++)
	{
		this->data[i].result = aRecv->tdata[i].result;
		this->data[i].map = aRecv->tdata[i].map;
		this->data[i].x = aRecv->tdata[i].x;
		this->data[i].y = aRecv->tdata[i].y;
		this->data[i].min_level = aRecv->tdata[i].min_level;
		this->data[i].min_reset = aRecv->tdata[i].min_reset;
		this->data[i].min_grand = aRecv->tdata[i].min_grand;
		this->data[i].max_level = aRecv->tdata[i].max_level;
		this->data[i].max_reset = aRecv->tdata[i].max_reset;
		this->data[i].max_grand = aRecv->tdata[i].max_grand;
		this->data[i].premium = aRecv->tdata[i].premium;
		this->data[i].zen = aRecv->tdata[i].zen;
		this->data[i].bonus = aRecv->tdata[i].bonus;
		this->data[i].credit = aRecv->tdata[i].credit;
		this->data[i].Master = aRecv->tdata[i].Master;
		this->data[i].ok_level = aRecv->tdata[i].ok_level;
		this->data[i].ok_reset = aRecv->tdata[i].ok_reset;
		this->data[i].ok_grand = aRecv->tdata[i].ok_grand;
		this->data[i].ok_premium = aRecv->tdata[i].ok_premium;
		this->data[i].ok_zen = aRecv->tdata[i].ok_zen;
		this->data[i].ok_bonus = aRecv->tdata[i].ok_bonus;
		this->data[i].ok_credit = aRecv->tdata[i].ok_credit;
		this->data[i].ok_Master = aRecv->tdata[i].ok_Master;
		this->data[i].EmptyInv = aRecv->tdata[i].EmptyInv;
		this->data[i].ok_EmptyInv = aRecv->tdata[i].ok_EmptyInv;

		this->LenCount = 0;
		this->SpeedCalc(this->data[i].min_level, this->LenCount);
		this->SpeedCalc(this->data[i].min_reset, this->LenCount);
		this->SpeedCalc(this->data[i].min_grand, this->LenCount);
		this->SpeedCalc(this->data[i].max_level, this->LenCount);
		this->SpeedCalc(this->data[i].max_reset, this->LenCount);
		this->SpeedCalc(this->data[i].max_grand, this->LenCount);
		this->SpeedCalc(this->data[i].premium, this->LenCount);
		this->SpeedCalc(this->data[i].zen, this->LenCount);
		this->SpeedCalc(this->data[i].bonus, this->LenCount);
		this->SpeedCalc(this->data[i].credit, this->LenCount);
		this->SpeedCalc(this->data[i].Master, this->LenCount);
		this->SpeedCalc(this->data[i].EmptyInv, this->LenCount);
	}

	if(this->iLoadedCount == 1)
	{
		this->ClickPage = this->iLoadedCount-1;
	}

	if(this->iLoadedCount > 0)
	{
		gInterface.OpenWindowEx(exWinTeleportEvo);
	}
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::CGResult(BYTE num)
{
	PMSG_CG_TELEPORTWINRESEVO pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0xA3, sizeof(pRequest));
	pRequest.result = (BYTE)num;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
	gInterface.CloseWindowEx(exWinTeleportEvo);
	this->ClickPage = -1;
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::Button(DWORD Event)
{
	if(!gInterface.CheckWindowEx(exWinTeleportEvo))
	{
		return;
	}

	if( gInterface.ButtonEx(Event, eTELEPORT_CLOSE, false ) )
	{
		gInterface.CloseWindowEx(exWinTeleportEvo);
		return;
	}

	if( gInterface.ButtonEx(Event, eTELEPORT_BT_CANCELE, false ) )
	{
		if(this->iLoadedCount == 1)
		{
			gInterface.CloseWindowEx(exWinTeleportEvo);
		}
		else
		{
			this->ClickPage = -1;
		}
		return;
	}

	if(this->ClickPage >= 0 && this->ClickPage < MAXEXTELEPORT)
	{
		if( gInterface.ButtonEx(Event, eTELEPORT_BT1 + this->ClickPage, true ) )
		{
			this->CGResult(this->ClickPage);
			return;
		}
	}
	else
	{
		for(int i = 0; i < this->iLoadedCount; i++)
		{
			if( gInterface.ButtonEx(Event, eTELEPORT_PAGEUP1+i, false ) )
			{
				this->ClickPage = i;
				return;
			}
		}
	}

	return;
}
// ----------------------------------------------------------------------------------------------

void ExTeleportEvo::SpeedCalc(int number, int &countplus)
{
	if(number > 0)
	{
		countplus++;
	}
}

char* ExTeleportEvo::ActiveText(int status)
{
	if(status)
	{
		
	}

	return "Active";

}

void ExTeleportEvo::CGDialog()
{
	PMSG_CG_DIALOGEVO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xA4, sizeof(pMsg));
	pMsg.result = 1;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}
#endif