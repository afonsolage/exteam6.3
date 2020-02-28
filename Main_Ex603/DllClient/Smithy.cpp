#include "stdafx.h"
#include "Smithy.h"
#include "Interface.h"
#include "Configs.h"
#include "Console.h"
#include "Item.h"
#include "ReadScript.h"
#include "User.h"
#include "ExLicense.h"

#if(CUSTOM_SMITHY == TRUE)

CSmithy g_Smithy;

CSmithy::CSmithy()
{
	this->Init();
}

CSmithy::~CSmithy()
{
}

void CSmithy::Init()
{
	this->itemdata.clear();
	this->MainPage = 0;
	this->Class = 0;
	this->Category = 0;
	this->CategoryPage = 0;
	this->Item = 0;
	this->ItemLevel = 0;
	this->ItemLuck = false;
	this->ItemAdd = false;
	this->ItemOpt1 = false;
	this->ItemOpt2 = false;
	this->ItemOpt3 = false;
	this->ItemOpt4 = false;
	this->ItemOpt5 = false;
	this->ItemOpt6 = false;
	this->MaxLevel = 0;
	this->LevelPrice = 0;
	this->LuckPrice = 0;
	this->AddPrice = 0;
	this->Opt1Price = 0;
	this->Opt2Price = 0;
	this->Opt3Price = 0;
	this->Opt4Price = 0;
	this->Opt5Price = 0;
	this->Opt6Price = 0;
	this->MaxExlOpt = 0;
	this->License = false;
}

void CSmithy::Load()
{
	this->Init();
}

void CSmithy::LoadImg()
{
	gInterface.LoadImages("Custom\\Interface\\newui_cha_textbox03.tga", ex_SMITHY_TEXT, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\itembackpanel.tga", ex_SMITHY_ITEM, 0x2601, 0x2900, 1);
}

void CSmithy::BindImg()
{
	gInterface.BindObject(eSMITHY_MAIN, 0x7A5A, 222, 303 + 18, -1, -1);
	gInterface.BindObject(eSMITHY_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eSMITHY_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eSMITHY_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eSMITHY_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eSMITHY_DIV2, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eSMITHY_INFOBG, ex_NEWS_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eSMITHY_BACK, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT2, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT3, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT4, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT5, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT6, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT7, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT8, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT9, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_TEXT10, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_L, 0x7BAA, 17, 17, -1, -1);
	gInterface.BindObject(eSMITHY_R, 0x7BAB, 17, 17, -1, -1);
	gInterface.BindObject(eSMITHY_INFOBG2, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_INFOBG3, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eSMITHY_LINE, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eSMITHY_POINT, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eSMITHY_CHECK0, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_CHECK3, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_CHECK4, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_CHECK5, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_CHECK6, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_PAGEUP, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_PAGEDN, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_BT1, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eSMITHY_BT2, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eSMITHY_PAGEUP2, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eSMITHY_PAGEDN2, 0x7C0D, 15, 15, -1, -1);

	gInterface.BindObject(eSMITHY_CHECKWIN_MAIN, 0x7A5A, 222, 110, -1, -1);
	gInterface.BindObject(eSMITHY_CHECKWIN_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eSMITHY_CHECKWIN_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eSMITHY_CHECKWIN_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eSMITHY_CHECKWIN_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eSMITHY_CHECKWIN_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eSMITHY_CHECKWIN_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eSMITHY_ITEM_BG, ex_SMITHY_ITEM, 152, 124, -1, -1);
}

void CSmithy::Draw()
{
	if(!gInterface.CheckWindowEx(exWinSmithy))
	{
		return;
	}

	pSetCursorFocus = true;

	if( /*g_ExLicense.CheckUser(eExUB::Local)  ||*/ 
		g_ExLicense.CheckUser(eExUB::Gredy)			|| 
		g_ExLicense.CheckUser(eExUB::Gredy2)		|| 
		g_ExLicense.CheckUser(eExUB::GredyLocal)	||
		g_ExLicense.CheckUser(eExUB::SILVER1)		||
		g_ExLicense.CheckUser(eExUB::SILVER2)		||
		g_ExLicense.CheckUser(eExUB::SILVER_Local)	||
		THINNAKORN_MAC)
	{
		if(this->DrawCheckBuy() == true)
		{
			return;
		}
	}

	DWORD Color				= eGray100;
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	gInterface.DrawGUI(eSMITHY_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eSMITHY_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eSMITHY_FRAME, StartX, StartY + 67.0, 14);
	gInterface.DrawGUI(eSMITHY_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eSMITHY_CLOSE, StartX + MainWidth - gInterface.Data[eSMITHY_CLOSE].Width, gInterface.Data[eSMITHY_TITLE].Height + gInterface.Data[eSMITHY_CLOSE].Height + 2);
	if(gInterface.IsWorkZone(eSMITHY_CLOSE))
	{
		if(gInterface.Data[eSMITHY_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eSMITHY_CLOSE, gInterface.Data[eSMITHY_CLOSE].X, gInterface.Data[eSMITHY_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eSMITHY_CLOSE].X + 5, gInterface.Data[eSMITHY_CLOSE].Y + 25, "Close");
	}
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Smitch");

	float ContentX = StartX+30;
	float ContentY = 140;
	if(this->MainPage == SMITHY_CLASS)
	{
		for(int i=0; i < g_MaxCharacter; i++)
		{
			ContentY += 25;
			int objid = eSMITHY_TEXT+i;
			gInterface.DrawGUI(objid, ContentX, ContentY);
			if(gInterface.IsWorkZone(objid))
			{
				gInterface.DrawFormat(eGold, ContentX-20, ContentY+5, 210, 3, Menu1[i]);
			}
			else
			{
				gInterface.DrawFormat(eWhite, ContentX-20, ContentY+5, 210, 3, Menu1[i]);
			}
		}
	}
	else if(this->MainPage == SMITHY_CATEGORY)
	{
		ContentY -= 5;
		for(int i=0; i < 9; i++)
		{
			int objid = eSMITHY_TEXT+i;
			gInterface.DrawGUI(objid, ContentX, ContentY);
		
			if(gInterface.IsWorkZone(objid))
			{
				gInterface.DrawFormat(eGold, ContentX-20, ContentY+5, 210, 3, Menu2[i]);
			}
			else
			{
				gInterface.DrawFormat(eWhite, ContentX-20, ContentY+5, 210, 3, Menu2[i]);
			}
			ContentY += 25;
		}
	}
	else if(this->MainPage == SMITHY_ITEM)
	{
		ContentY -= 10;
		int n = 0;
		for(int i = 0; i < this->itemdata.size(); i++)
		{
			if(this->Class == this->itemdata[i].Class)
			{
				if(this->Category == this->GetCategory(this->itemdata[i].Type))
				{
					int max_n = this->CategoryPage * 10 + 10;
					int min_n = this->CategoryPage * 10;
					if(n >= min_n && n < max_n)
					{
						int objid = eSMITHY_TEXT+n-min_n;
						gInterface.DrawGUI(objid, ContentX, ContentY);		
						if(gInterface.IsWorkZone(objid))
						{
							gInterface.DrawFormat(eGold, ContentX-20, ContentY+5, 210, 3, gItem.GetItemName(ITEMGET(this->itemdata[i].Type, this->itemdata[i].Index)));
						}
						else
						{
							gInterface.DrawFormat(eWhite, ContentX-20, ContentY+5, 210, 3, gItem.GetItemName(ITEMGET(this->itemdata[i].Type, this->itemdata[i].Index)));
						}
						ContentY += 21;				
					}
					n++;
				}
			}
		}
		ContentY = 350;
		ContentX -= 30;
		gInterface.DrawGUI(eSMITHY_L, ContentX + 80, ContentY+2);
		gInterface.DrawGUI(eSMITHY_R, ContentX + 130, ContentY+2);
		if(gInterface.IsWorkZone(eSMITHY_L))
		{
			if(gInterface.Data[eSMITHY_L].OnClick)
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eSMITHY_L, gInterface.Data[eSMITHY_L].X, gInterface.Data[eSMITHY_L].Y, Color);
		}
		if(gInterface.IsWorkZone(eSMITHY_R))
		{
			if(gInterface.Data[eSMITHY_R].OnClick)
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eSMITHY_R, gInterface.Data[eSMITHY_R].X, gInterface.Data[eSMITHY_R].Y, Color);
		}
		gInterface.DrawFormat(eGold, ContentX+97, ContentY+6, 100, 1, "Page: %d/%d", this->CategoryPage+1,n/10+1);
	}
	else if(this->MainPage == SMITHY_OPTION)
	{
		gInterface.DrawGUI(eSMITHY_TEXT, ContentX, ContentY-10);		
		gInterface.DrawFormat(eExcellent, ContentX, ContentY-5, 170, 3, gItem.GetItemName(ITEMGET(this->itemdata[this->Item].Type, this->itemdata[this->Item].Index)));
		gInterface.DrawGUI(eSMITHY_DIV2, StartX, ContentY+5);

		ContentY += 25;

		gInterface.PartUPandDNEx(eSMITHY_POINT, eSMITHY_PAGEUP, eSMITHY_PAGEDN, eSMITHY_LINE, ContentX-30, ContentY, eWhite, this->ItemLevel, "Item Level");
		ContentY += 20;
		gInterface.DrawCheckLineEx(this->ItemLuck, eSMITHY_POINT, eSMITHY_CHECK0, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Luck Option +25%%");
		ContentY += 20;
		gInterface.PartUPandDNEx(eSMITHY_POINT, eSMITHY_PAGEUP2, eSMITHY_PAGEDN2, eSMITHY_LINE, ContentX-30, ContentY, eWhite, this->ItemAdd, "Add Option");
		ContentY += 20;
		// -> Wings
		if(this->CheckWingLevel() == 1)
		{

		}
		else if(this->CheckWingLevel() == 2)
		{
			gInterface.DrawCheckLineEx(this->ItemOpt2, eSMITHY_POINT, eSMITHY_CHECK2, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Attackin(Wizardy) speed +5");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt3, eSMITHY_POINT, eSMITHY_CHECK3, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Max Ag +50 Increased");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt4, eSMITHY_POINT, eSMITHY_CHECK4, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Ignor Optionent's defensive power by 3%%");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt5, eSMITHY_POINT, eSMITHY_CHECK5, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Mana +50 Increased");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt6, eSMITHY_POINT, eSMITHY_CHECK6, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "HP +50 Increased");
		}
		else if(this->CheckWingLevel() == 3)
		{
			gInterface.DrawCheckLineEx(this->ItemOpt3, eSMITHY_POINT, eSMITHY_CHECK3, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Complete reco of Mana in 5%% rate");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt4, eSMITHY_POINT, eSMITHY_CHECK4, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Complete recoy of Life in 5%% rate");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt5, eSMITHY_POINT, eSMITHY_CHECK5, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Return the enemy attack power in 5%%");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt6, eSMITHY_POINT, eSMITHY_CHECK6, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Ignor openent defensive power by 5%%");
		}
		else if(this->CheckPend() == true)
		{
			gInterface.DrawCheckLineEx(this->ItemOpt1, eSMITHY_POINT, eSMITHY_CHECK1, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Excellent Damage rate +10%%");
			ContentY += 20;
			//if(this->itemdata[this->Item].Type == 5)
			//{
			//	gInterface.DrawCheckLineEx(this->ItemOpt2, eSMITHY_POINT, eSMITHY_CHECK2, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Wizardry Damage +level/20");
			//	ContentY += 20;
			//	gInterface.DrawCheckLineEx(this->ItemOpt3, eSMITHY_POINT, eSMITHY_CHECK3, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Wizardry Damage +2%%");
			//}
			//else
			{
				gInterface.DrawCheckLineEx(this->ItemOpt2, eSMITHY_POINT, eSMITHY_CHECK2, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Damage +level/20");
				ContentY += 20;
				gInterface.DrawCheckLineEx(this->ItemOpt3, eSMITHY_POINT, eSMITHY_CHECK3, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Damage +2%%");
			}	
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt4, eSMITHY_POINT, eSMITHY_CHECK4, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Attacking(Wizardy)speed +7");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt5, eSMITHY_POINT, eSMITHY_CHECK5, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increases Life hunting monsters +life/8");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt6, eSMITHY_POINT, eSMITHY_CHECK6, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increases Mana hunting monsters +Mana/8");
		}
		else if(this->itemdata[this->Item].Type > 5 || this->CheckRing() == true)
		{
			gInterface.DrawCheckLineEx(this->ItemOpt1, eSMITHY_POINT, eSMITHY_CHECK1, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Max HP +4%%");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt2, eSMITHY_POINT, eSMITHY_CHECK2, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Max Mana +4%%");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt3, eSMITHY_POINT, eSMITHY_CHECK3, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Damage Decrease +4%%");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt4, eSMITHY_POINT, eSMITHY_CHECK4, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Reflect Damage +5%%");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt5, eSMITHY_POINT, eSMITHY_CHECK5, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Defense success rate +10%%");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt6, eSMITHY_POINT, eSMITHY_CHECK6, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increases Zen hunting monsters +30%%");
		}
		else
		{
			gInterface.DrawCheckLineEx(this->ItemOpt1, eSMITHY_POINT, eSMITHY_CHECK1, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Excellent Damage rate +10%%");
			ContentY += 20;
			if(this->itemdata[this->Item].Type == 5)
			{
				gInterface.DrawCheckLineEx(this->ItemOpt2, eSMITHY_POINT, eSMITHY_CHECK2, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Wizardry Damage +level/20");
				ContentY += 20;
				gInterface.DrawCheckLineEx(this->ItemOpt3, eSMITHY_POINT, eSMITHY_CHECK3, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Wizardry Damage +2%%");
			}
			else
			{
				gInterface.DrawCheckLineEx(this->ItemOpt2, eSMITHY_POINT, eSMITHY_CHECK2, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Damage +level/20");
				ContentY += 20;
				gInterface.DrawCheckLineEx(this->ItemOpt3, eSMITHY_POINT, eSMITHY_CHECK3, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Damage +2%%");
			}	
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt4, eSMITHY_POINT, eSMITHY_CHECK4, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increase Attacking(Wizardy)speed +7");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt5, eSMITHY_POINT, eSMITHY_CHECK5, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increases Life hunting monsters +life/8");
			ContentY += 20;
			gInterface.DrawCheckLineEx(this->ItemOpt6, eSMITHY_POINT, eSMITHY_CHECK6, eSMITHY_LINE, ContentX-30, ContentY, eWhite, "Increases Mana hunting monsters +Mana/8");
		}
		ContentY = 341;
		gInterface.DrawGUI(eSMITHY_INFOBG2, ContentX, ContentY);
		gInterface.DrawFormat(eWhite, ContentX+30, ContentY+5, 210, 1, "Price:");
		gInterface.DrawFormat(eGold, ContentX+120, ContentY+5, 210, 1, "%d", this->GetItemPrice());

		ContentY += 20;
		gInterface.DrawGUI(eSMITHY_INFOBG2, ContentX, ContentY);

		if(g_ExLicense.CheckUser(eExUB::Local)		  || 
		   g_ExLicense.CheckUser(eExUB::SILVER1)	  || 
		   g_ExLicense.CheckUser(eExUB::SILVER2)	  ||	
		   g_ExLicense.CheckUser(eExUB::SILVER_Local) )
		{
			gInterface.DrawFormat(eWhite, ContentX+30, ContentY+5, 210, 1, "Credit:");
			gInterface.DrawFormat(eGold, ContentX+120, ContentY+5, 210, 1, "%d", (int)gObjUser.ExCred);
		}
		else
		{
			gInterface.DrawFormat(eWhite, ContentX+30, ContentY+5, 210, 1, "WCoin:");
			gInterface.DrawFormat(eGold, ContentX+120, ContentY+5, 210, 1, "%d", gObjUser.WCoinC);
		}

		this->DrawItem();
	}

	gInterface.DrawGUI(eSMITHY_DIV, StartX, gInterface.Data[eSMITHY_FOOTER].Y - 5);
	if(this->MainPage == SMITHY_OPTION)
	{
		bool bPrice = true;

		if(g_ExLicense.CheckUser(eExUB::Local)		  || 
		   g_ExLicense.CheckUser(eExUB::SILVER1)	  || 
		   g_ExLicense.CheckUser(eExUB::SILVER2)	  ||	
		   g_ExLicense.CheckUser(eExUB::SILVER_Local) )
		{
			if(this->GetItemPrice() > gObjUser.ExCred)
			{
				bPrice = false;
			}
		}
		else
		{
			if(this->GetItemPrice() > gObjUser.WCoinC)
			{
				bPrice = false;
			}
		}


		gInterface.DrawButtonMini(eSMITHY_BT1, StartX+40, gInterface.Data[eSMITHY_FOOTER].Y + 10, true, "Back");
		gInterface.DrawButtonMini(eSMITHY_BT2, StartX+120, gInterface.Data[eSMITHY_FOOTER].Y + 10, bPrice, "Buy");
	}
	else
	{
		gInterface.DrawGUI(eSMITHY_BACK, ButtonX, gInterface.Data[eSMITHY_FOOTER].Y + 10);
		if(this->MainPage == SMITHY_CLASS)
		{
			gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eSMITHY_FOOTER].Y + 20, 210, 3, "Exit");
		}
		else if(this->MainPage == SMITHY_CATEGORY || this->MainPage == SMITHY_ITEM)
		{
			gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eSMITHY_FOOTER].Y + 20, 210, 3, "Back");
		}

		if(gInterface.IsWorkZone(eSMITHY_BACK))
		{
			if(gInterface.Data[eSMITHY_BACK].OnClick)
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eSMITHY_BACK, gInterface.Data[eSMITHY_BACK].X, gInterface.Data[eSMITHY_BACK].Y, Color);
		}
	}
}

bool CSmithy::DrawCheckBuy()
{
	if(!gInterface.CheckWindowEx(exWinSmithyCheck))
	{
		return false;
	}

	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 130;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	gInterface.DrawGUI(eSMITHY_CHECKWIN_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eSMITHY_CHECKWIN_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eSMITHY_CHECKWIN_FRAME, StartX, StartY + 67.0, 0);
	gInterface.DrawGUI(eSMITHY_CHECKWIN_FOOTER, StartX, StartY);
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Check Buy");
	// ---- 
	gInterface.DrawFormat(eWhite, StartX + 10, 110 + 50 - 20, 210, 3, "Check Buy Item?");
	gInterface.DrawGUI(eSMITHY_CHECKWIN_OK, StartX+30, StartY /*- 5*/);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5 + 5, 50, 3, "Yes");

	if( gInterface.IsWorkZone(eSMITHY_CHECKWIN_OK) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eSMITHY_CHECKWIN_OK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eSMITHY_CHECKWIN_OK, gInterface.Data[eSMITHY_CHECKWIN_OK].X, gInterface.Data[eSMITHY_CHECKWIN_OK].Y, Color);
	}
	// ---- 
	gInterface.DrawGUI(eSMITHY_CHECKWIN_CLOSE, StartX + 70 + 62, StartY /*- 5*/ );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5 + 5, 50, 3, "No");

	if( gInterface.IsWorkZone(eSMITHY_CHECKWIN_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eSMITHY_CHECKWIN_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eSMITHY_CHECKWIN_CLOSE, gInterface.Data[eSMITHY_CHECKWIN_CLOSE].X, gInterface.Data[eSMITHY_CHECKWIN_CLOSE].Y, Color);
	}

	return true;
}

void CSmithy::DrawItem()
{
	float MainWidth	 = 230.0;
	float ContentX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentY = 100.0;

	//ContentX += MainWidth;
	//gInterface.DrawWindow(eSMITHY_ITEM_MAIN, eSMITHY_ITEM_TITLE, eSMITHY_ITEM_FRAME, eSMITHY_ITEM_FOOTER, 0, ContentX, ContentY, "Item");

	ContentX += MainWidth;
	gInterface.DrawGUI(eSMITHY_ITEM_BG, ContentX, ContentY);

	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(ITEM(this->itemdata[this->Item].Type, this->itemdata[this->Item].Index));

	const int WidthValue = 24;	//24
	const int HeightValue = 26;	//26
	float barWidth = WidthValue * ItemInfo->ItemWidth;
	float barHeight = HeightValue * ItemInfo->ItemHeight;

	float flDrawItemX;// = ContentX - (WidthValue * (float)(ItemInfo->ItemWidth / 2.0f) + 10) + 80;
	float flDrawItemY;// = ContentY + 20;

	flDrawItemX = ContentX + ( 152 / 2 ) - ( WidthValue * ItemInfo->ItemWidth / 2 );
	flDrawItemY = ContentY + ( 124 / 2 ) - ( HeightValue * ItemInfo->ItemHeight / 2 );

	gInterface.DrawItem(
		flDrawItemX,
		flDrawItemY,
		barWidth,
		barHeight,
		ITEMGET(this->itemdata[this->Item].Type,this->itemdata[this->Item].Index),
		SET_ITEMOPT_LEVEL(ItemLevel),
		1,0,0);

}

void CSmithy::Button(DWORD Event)
{
	if( /*g_ExLicense.CheckUser(eExUB::Local)  ||*/ 
		g_ExLicense.CheckUser(eExUB::Gredy)			|| 
		g_ExLicense.CheckUser(eExUB::Gredy2)		|| 
		g_ExLicense.CheckUser(eExUB::GredyLocal)	||
		g_ExLicense.CheckUser(eExUB::SILVER1)		||
		g_ExLicense.CheckUser(eExUB::SILVER2)		||
		g_ExLicense.CheckUser(eExUB::SILVER_Local)	||
		THINNAKORN_MAC)
	{
		if(gInterface.CheckWindowEx(exWinSmithyCheck))
		{
			if(gInterface.ButtonEx(Event, eSMITHY_CHECKWIN_OK, false))
			{
				this->CGCreateItem();		
				gInterface.CloseWindowEx(exWinSmithyCheck);
			}
			if(gInterface.ButtonEx(Event, eSMITHY_CHECKWIN_CLOSE, false))
			{		
				gInterface.CloseWindowEx(exWinSmithyCheck);
			}
			return;
		}
	}

	if(!gInterface.CheckWindowEx(exWinSmithy))
	{
		return;
	}

	if(this->MainPage == SMITHY_CLASS)
	{
		for(int i=0; i < g_MaxCharacter; i++)
		{
			int objid = eSMITHY_TEXT+i;
			if(gInterface.ButtonEx(Event, objid, false))
			{
				this->Class = i;
				this->MainPage = SMITHY_CATEGORY;
			}
		}
	}
	else if(this->MainPage == SMITHY_CATEGORY)
	{
		for(int i=0; i < 9; i++)
		{
			int objid = eSMITHY_TEXT+i;
			if(gInterface.ButtonEx(Event, objid, false))
			{
				this->Category = i;
				this->MainPage = SMITHY_ITEM;
			}
		}
	}
	else if(this->MainPage == SMITHY_ITEM)
	{
		int n = 0;
		for(int i = 0; i < this->itemdata.size(); i++)
		{
			if(this->Class == this->itemdata[i].Class)
			{
				if(this->Category == this->GetCategory(this->itemdata[i].Type))
				{
					int max_n = this->CategoryPage * 10 + 10;
					int min_n = this->CategoryPage * 10;
					if(n >= min_n && n < max_n)
					{
						int objid = eSMITHY_TEXT+n-min_n;
						if(gInterface.ButtonEx(Event, objid, false))
						{
							this->Item = i;
							this->MainPage = SMITHY_OPTION;							
						}
					}
					n++;
				}
			}
		}
		if(gInterface.ButtonEx(Event, eSMITHY_L, false))
		{
			if(this->CategoryPage > 0)
			{
				this->CategoryPage--;
			}
		}
		if(gInterface.ButtonEx(Event, eSMITHY_R, false))
		{
			if(this->CategoryPage < this->GetMaxItemCategory()/10)
			{
				 this->CategoryPage++;
			}
		}
	}
	else if(this->MainPage == SMITHY_OPTION)
	{
		if(gInterface.ButtonEx(Event, eSMITHY_PAGEUP, false) && this->ItemLevel < this->MaxLevel)
		{
			this->ItemLevel++;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_PAGEDN, false) && this->ItemLevel > 0)
		{
			this->ItemLevel--;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_PAGEUP2, false) && this->ItemAdd < 7)
		{
			this->ItemAdd++;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_PAGEDN2, false) && this->ItemAdd > 0)
		{
			this->ItemAdd--;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_CHECK0, false))
		{
			if(!this->CheckRing() && !this->CheckPend())
			{
				this->ItemLuck = !this->ItemLuck;
			}
		}
		if(gInterface.ButtonEx(Event, eSMITHY_CHECK1, false))
		{
			if(!this->ItemOpt1 && !this->CheckExlOpt())
			{
				return;
			}

			this->ItemOpt1 = !this->ItemOpt1;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_CHECK2, false))
		{
			if(!this->ItemOpt2 && !this->CheckExlOpt())
			{
				return;
			}

			this->ItemOpt2 = !this->ItemOpt2;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_CHECK3, false))
		{
			if(!this->ItemOpt3 && !this->CheckExlOpt())
			{
				return;
			}

			this->ItemOpt3 = !this->ItemOpt3;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_CHECK4, false))
		{
			if(!this->ItemOpt4 && !this->CheckExlOpt())
			{
				this->ItemOpt4 = !this->ItemOpt4;
			}

			this->ItemOpt4 = !this->ItemOpt4;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_CHECK5, false))
		{
			if(!this->ItemOpt5 && !this->CheckExlOpt())
			{
				return;
			}

			this->ItemOpt5 = !this->ItemOpt5;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_CHECK6, false))
		{
			if(!this->ItemOpt6 && !this->CheckExlOpt())
			{
				return;
			}

			this->ItemOpt6 = !this->ItemOpt6;
		}
	}

	if(this->MainPage == SMITHY_OPTION)
	{
		if(gInterface.ButtonEx(Event, eSMITHY_BT1, false))
		{
			this->MainPage--;
		}
		if(gInterface.ButtonEx(Event, eSMITHY_BT2, true))
		{
			if( /*g_ExLicense.CheckUser(eExUB::Local)  ||*/ 
				g_ExLicense.CheckUser(eExUB::Gredy)			|| 
				g_ExLicense.CheckUser(eExUB::Gredy2)		|| 
				g_ExLicense.CheckUser(eExUB::GredyLocal)	||
				g_ExLicense.CheckUser(eExUB::SILVER1)		||
				g_ExLicense.CheckUser(eExUB::SILVER2)		||
				g_ExLicense.CheckUser(eExUB::SILVER_Local)	||
				THINNAKORN_MAC)
			{
				gInterface.OpenWindowEx(exWinSmithyCheck);
			}
			else
			{
				this->CGCreateItem();
			}		
		}
	}
	else
	{
		if(gInterface.ButtonEx(Event, eSMITHY_BACK, false))
		{
			if(this->MainPage == SMITHY_CLASS)
			{
				gInterface.CloseWindowEx(exWinSmithy);
				this->CloseWindow();
			}
			else if(this->MainPage > 0)
			{
				this->MainPage--;
			}
		}
	}

	if(gInterface.ButtonEx(Event, eSMITHY_CLOSE, false))
	{
		this->MainPage = SMITHY_CLASS;
		gInterface.CloseWindowEx(exWinSmithy);
		this->CloseWindow();
	}
}

void CSmithy::GCItemInit(GC_SmithyInit* aRecv)
{
	if(aRecv->result)
	{
		this->itemdata.clear();
	}
}

void CSmithy::GCItemSend(GC_SmithyDATA* aRecv)
{
	SmithyDATA pData;
	pData.Class = aRecv->Class;
	pData.Type = aRecv->Type;
	pData.Index = aRecv->Index;
	pData.Price = aRecv->Price;
	this->itemdata.push_back(pData);
}

void CSmithy::GCSettingsRecv(GC_SmithySettings* aRecv)
{
	this->MaxLevel = aRecv->MaxLevel;
	this->LevelPrice = aRecv->LevelPrice;
	this->LuckPrice = aRecv->LuckPrice;
	this->AddPrice = aRecv->AddPrice;
	this->Opt1Price = aRecv->Opt1Price;
	this->Opt2Price = aRecv->Opt2Price;
	this->Opt3Price = aRecv->Opt3Price;
	this->Opt4Price = aRecv->Opt4Price;
	this->Opt5Price = aRecv->Opt5Price;
	this->Opt6Price = aRecv->Opt6Price;
	this->MaxExlOpt = aRecv->MaxExlOpt;
}

void CSmithy::CGCreateItem()
{
	CG_SmithyCreateItem pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x21,  sizeof(pMsg));
	pMsg.Item = this->Item;
	pMsg.ItemLevel = this->ItemLevel;
	pMsg.ItemAdd = this->ItemAdd;
	pMsg.ItemLuck = this->ItemLuck;
	pMsg.ItemOpt1 = this->ItemOpt1;
	pMsg.ItemOpt2 = this->ItemOpt2;
	pMsg.ItemOpt3 = this->ItemOpt3;
	pMsg.ItemOpt4 = this->ItemOpt4;
	pMsg.ItemOpt5 = this->ItemOpt5;
	pMsg.ItemOpt6 = this->ItemOpt6;
	gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));
}

int CSmithy::GetCategory(int Type)
{
	switch(Type)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5: return 0;
	case 6: return 1;
	case 7: return 2;
	case 8: return 3;
	case 9: return 4;
	case 10:return 5;
	case 11:return 6;
	case 12:return 7;
	case 13:return 8;
	}
	return -1;
}

int CSmithy::GetMaxItemCategory()
{
	int n = 0;
	for(int i = 0; i < this->itemdata.size(); i++)
	{
		if(this->Class == this->itemdata[i].Class)
		{
			if(this->Category == this->GetCategory(this->itemdata[i].Type))
			{
				n++;
			}
		}
	}
	return n;
}

int CSmithy::GetItemPrice()
{
	unsigned int result = 0;

	result = this->itemdata[this->Item].Price;
	result += this->ItemLevel * this->LevelPrice;
	result += this->ItemAdd * this->AddPrice;

	if(this->ItemLuck)
	{
		result += this->LuckPrice;
	}
	/*if(this->ItemAdd)
	{
		//result += this->AddPrice;Û
	}*/
	if(this->ItemOpt1)
	{
		result += this->Opt1Price;
	}
	if(this->ItemOpt2)
	{
		result += this->Opt2Price;
	}
	if(this->ItemOpt3)
	{
		result += this->Opt3Price;
	}
	if(this->ItemOpt4)
	{
		result += this->Opt4Price;
	}
	if(this->ItemOpt5)
	{
		result += this->Opt5Price;
	}
	if(this->ItemOpt6)
	{
		result += this->Opt6Price;
	}

	return result;
}

void CSmithy::CloseWindow()
{
	this->MainPage = 0;
	this->Class = 0;
	this->Category = 0;
	this->CategoryPage = 0;
	this->Item = 0;
	this->ItemLevel = 0;
	this->ItemLuck = false;
	this->ItemAdd = false;
	this->ItemOpt1 = false;
	this->ItemOpt2 = false;
	this->ItemOpt3 = false;
	this->ItemOpt4 = false;
	this->ItemOpt5 = false;
	this->ItemOpt6 = false;
}

bool CSmithy::CheckRing()
{
	short iType = ITEMGET(this->itemdata[this->Item].Type, this->itemdata[this->Item].Index);
	switch(iType)
	{
	case ITEMGET(13, 8):
	case ITEMGET(13, 9):
	case ITEMGET(13, 21):
	case ITEMGET(13, 22):
	case ITEMGET(13, 23):
	case ITEMGET(13, 24):
		return true;
	}
	return false;
}

bool CSmithy::CheckPend()
{
	short iType = ITEMGET(this->itemdata[this->Item].Type, this->itemdata[this->Item].Index);
	switch(iType)
	{
	case ITEMGET(13, 12):
	case ITEMGET(13, 13):
	case ITEMGET(13, 25):
	case ITEMGET(13, 26):
	case ITEMGET(13, 27):
	case ITEMGET(13, 28):
		return true;
	}
	return false;
}

unsigned char CSmithy::CheckWingLevel()
{
	short iType = ITEMGET(this->itemdata[this->Item].Type, this->itemdata[this->Item].Index);
	switch(iType)
	{
	case ITEMGET(12, 0):
	case ITEMGET(12, 1):
	case ITEMGET(12, 2):
	case ITEMGET(12, 41):
		return 1;
	case ITEMGET(12, 3):
	case ITEMGET(12, 4):
	case ITEMGET(12, 5):
	case ITEMGET(12, 6):
	case ITEMGET(12, 52):
	case ITEMGET(13, 30):
		return 2;
	case ITEMGET(12, 36):
	case ITEMGET(12, 37):
	case ITEMGET(12, 38):
	case ITEMGET(12, 39):
	case ITEMGET(12, 40):
	case ITEMGET(12, 43):
	case ITEMGET(12, 180):
	case ITEMGET(12, 181):
	case ITEMGET(12, 182):
	case ITEMGET(12, 183):
	case ITEMGET(12, 184):
	case ITEMGET(12, 185):
	case ITEMGET(12, 186):
	case ITEMGET(12, 187):
	case ITEMGET(12, 188):
	case ITEMGET(12, 189):
	case ITEMGET(12, 190):
	case ITEMGET(12, 191):
	case ITEMGET(12, 192):
	case ITEMGET(12, 193):
	case ITEMGET(12, 194):
		return 3;
	}
	return 0;
}

bool CSmithy::CheckExlOpt()
{
	int iTotalExlOpt = this->ItemOpt1 + this->ItemOpt2 + this->ItemOpt3 + this->ItemOpt4 + this->ItemOpt5 + this->ItemOpt6;

	if(iTotalExlOpt >= this->MaxExlOpt)
	{
		return false;
	}

	return true;
}

#endif