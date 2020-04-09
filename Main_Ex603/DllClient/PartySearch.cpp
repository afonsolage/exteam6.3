#include "stdafx.h"
#include "PartySearch.h"
#include "Interface.h"
#include "NewParty.h"
#include "Protocol.h"
#include "User.h"
#include "Console.h"
#include "Configs.h"
#include "ExText.h"
// ----------------------------------------------------------------------------------------------

PartySearch g_PartySearch;
// ----------------------------------------------------------------------------------------------

void PartySearch::Init()
{
	ZeroMemory(&this->Party,sizeof(this->Party));

	this->Active = false;	//Enable System

	this->Page = 0;

	this->InfoDraw = false;
	this->InfoX = 0;
	this->InfoY = 0;
	this->InfoUP = 0;

	this->ActiveSystem = false;
	this->MaxLevel = 400;
	this->MaxParty = 0;

	this->bAllClass = false;
	this->bOnlyOneClass = false;
	this->bDarkWizard = false;
	this->bDarkKnight = false;
	this->bElf = false;
	this->bMagicGladiator = false;
	this->bDarkLord = false;
	this->bSummoner = false;
}
// ----------------------------------------------------------------------------------------------

void PartySearch::Load()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

void PartySearch::LoadImages()
{
	pLoadImage("Custom\\Interface\\PartySearch_Title.tga", ex_PT_SEARCH_TITLE, 0x2601, 0x2900, 1, 0);
}
// ----------------------------------------------------------------------------------------------

void PartySearch::BindImages()
{
	gInterface.BindObject(ePT_SEARCH_USER_MAIN, 0x7A5A, 222, 345.0, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_FINISH, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_L, 0x7BAA, 17, 17, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_R, 0x7BAB, 17, 17, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_INFO, 0x07ABE, 15, 13, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_INFOBG, ex_PT_SEARCH_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP1, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP2, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP3, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP4, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP5, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP6, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP7, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP8, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP9, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_USER_PAGEUP10, 0x7AA4, 15, 15, -1, -1);

	// ----

	gInterface.BindObject(ePT_SEARCH_MASTER_MAIN, 0x7A5A, 222, 303, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_FINISH, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_LINE, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_POINT, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_PAGEUP, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_PAGEDN, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK3, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK4, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK5, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK6, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK7, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK8, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(ePT_SEARCH_MASTER_CHECK9, 0x7B69, 15, 15, -1, -1);
}
// ----------------------------------------------------------------------------------------------

void PartySearch::DrawMaster()
{
	if(!gInterface.CheckWindowEx(exWinPTSearchMaster))
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

	float ContentY = StartY;
	float ContentX = StartX;

	// ----
	gInterface.DrawGUI(ePT_SEARCH_MASTER_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(ePT_SEARCH_MASTER_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ePT_SEARCH_MASTER_FRAME, StartX, StartY + 67.0, 13);
	gInterface.DrawGUI(ePT_SEARCH_MASTER_FOOTER, StartX, StartY);
	gInterface.DrawGUI(ePT_SEARCH_MASTER_CLOSE, StartX + MainWidth - gInterface.Data[ePT_SEARCH_MASTER_CLOSE].Width, gInterface.Data[ePT_SEARCH_MASTER_TITLE].Height + gInterface.Data[ePT_SEARCH_MASTER_CLOSE].Height + 2);
	// ----
	if( gInterface.IsWorkZone(ePT_SEARCH_MASTER_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_SEARCH_MASTER_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_SEARCH_MASTER_CLOSE, gInterface.Data[ePT_SEARCH_MASTER_CLOSE].X, gInterface.Data[ePT_SEARCH_MASTER_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[ePT_SEARCH_MASTER_CLOSE].X + 5, gInterface.Data[ePT_SEARCH_MASTER_CLOSE].Y + 25, g_ExText.GetText(24));
	}
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, g_ExText.GetText(118));
	// ---- 

	// -> Content

	ContentY += 35;
	gInterface.DrawCheckLine(this->ActiveSystem, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK1, NULL, ContentX, ContentY, eWhite, g_ExText.GetText(116));

	ContentY += 10;
	gInterface.DrawGUI(ePT_SEARCH_MASTER_DIV, ContentX, ContentY);

	ContentY += 20; 
	gInterface.PartUPandDN(ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_PAGEUP, ePT_SEARCH_MASTER_PAGEDN, NULL, ContentX, ContentY, eWhite, this->MaxLevel, g_ExText.GetText(117));

	ContentY += 10;
	gInterface.DrawGUI(ePT_SEARCH_MASTER_DIV, ContentX, ContentY);

	ContentY += 20;
	gInterface.DrawCheckLine(this->bOnlyOneClass, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK3, NULL, ContentX, ContentY, eWhite, g_ExText.GetText(119));

	ContentY += 10;
	gInterface.DrawGUI(ePT_SEARCH_MASTER_DIV, ContentX, ContentY);

	ContentY += 20;
	gInterface.DrawCheckLine(this->bDarkWizard, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK4, ePT_SEARCH_MASTER_LINE, ContentX, ContentY, eWhite, g_ExText.GetText(60));

	ContentY += 20;
	gInterface.DrawCheckLine(this->bDarkKnight, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK5, ePT_SEARCH_MASTER_LINE, ContentX, ContentY, eWhite, g_ExText.GetText(63));

	ContentY += 20;
	gInterface.DrawCheckLine(this->bElf, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK6, ePT_SEARCH_MASTER_LINE, ContentX, ContentY, eWhite, g_ExText.GetText(66));

	ContentY += 20;
	gInterface.DrawCheckLine(this->bMagicGladiator, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK7, ePT_SEARCH_MASTER_LINE, ContentX, ContentY, eWhite, g_ExText.GetText(69));

	ContentY += 20;
	gInterface.DrawCheckLine(this->bDarkLord, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK8, ePT_SEARCH_MASTER_LINE, ContentX, ContentY, eWhite, g_ExText.GetText(71));

	if(gObjUser.SUM)
	{
		ContentY += 20;
		gInterface.DrawCheckLine(this->bSummoner, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK9, NULL, ContentX, ContentY, eWhite, g_ExText.GetText(73));
	}

	if(gObjUser.RF)
	{
		ContentY += 20;
		gInterface.DrawCheckLine(this->bAllClass, ePT_SEARCH_MASTER_POINT, ePT_SEARCH_MASTER_CHECK2, ePT_SEARCH_MASTER_LINE, ContentX, ContentY, eWhite, g_ExText.GetText(76));
	}

	// -> End
	gInterface.DrawGUI(ePT_SEARCH_MASTER_FINISH, ButtonX, gInterface.Data[ePT_SEARCH_MASTER_FOOTER].Y + 10);
	gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[ePT_SEARCH_MASTER_FOOTER].Y + 20, 210, 3, g_ExText.GetText(120));
	gInterface.DrawGUI(ePT_SEARCH_MASTER_DIV, StartX, gInterface.Data[ePT_SEARCH_MASTER_FOOTER].Y - 10);
	// ----
	if( gInterface.IsWorkZone(ePT_SEARCH_MASTER_FINISH) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_SEARCH_MASTER_FINISH].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_SEARCH_MASTER_FINISH, gInterface.Data[ePT_SEARCH_MASTER_FINISH].X, gInterface.Data[ePT_SEARCH_MASTER_FINISH].Y, Color);
	}
}
// ----------------------------------------------------------------------------------------------
void PartySearch::DrawUser()
{
	if(!gInterface.CheckWindowEx(exWinPTSearchUser))
	{
		return;
	}
	pSetCursorFocus = true;

	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 350.0;
	float StartY			= 50;	//100
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentX          = StartX;
	float ContentY			= StartY;

	// ----
	gInterface.DrawGUI(ePT_SEARCH_USER_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(ePT_SEARCH_USER_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ePT_SEARCH_USER_FRAME, StartX, StartY + 67.0, 16);
	gInterface.DrawGUI(ePT_SEARCH_USER_FOOTER, StartX, StartY);
	gInterface.DrawGUI(ePT_SEARCH_USER_CLOSE, StartX + MainWidth - gInterface.Data[ePT_SEARCH_USER_CLOSE].Width, ContentY);
	// ----
	if( gInterface.IsWorkZone(ePT_SEARCH_USER_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_SEARCH_USER_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_SEARCH_USER_CLOSE, gInterface.Data[ePT_SEARCH_USER_CLOSE].X, gInterface.Data[ePT_SEARCH_USER_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[ePT_SEARCH_USER_CLOSE].X + 5, gInterface.Data[ePT_SEARCH_USER_CLOSE].Y + 25, g_ExText.GetText(24));
	}
	// ----

	gInterface.DrawFormat(eGold, ContentX + 10, ContentY + 10, 210, 3, g_ExText.GetText(141));

	// -> Content

	gInterface.DrawGUI(ePT_SEARCH_USER_DIV, ContentX, ContentY + 50);

	float ListDrawX = ContentX + 20;
	float ListDrawY = ContentY + 10 + 38;

	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, g_ExText.GetText(28));

	ListDrawX += 50;
	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, g_ExText.GetText(30));

	ListDrawX += 50;
	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, g_ExText.GetText(31));

	ListDrawX += 15;
	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, g_ExText.GetText(32));

	ListDrawX += 20;
	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, g_ExText.GetText(33));

	ListDrawX += 35;
	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, g_ExText.GetText(142));

	gInterface.DrawGUI(ePT_SEARCH_USER_DIV, ContentX, ListDrawY + 23);

	// ----------

	// -> Draw Listing

	this->InfoDraw = false;
	this->InfoX = 0;
	this->InfoY = 0;

	for(int i = 0; i < 10; i++)
	{
		int up = i + (  this->Page  * 10 );

		if(this->Party[up].Name[0] == NULL) break;

		int PartyCount = 1;

		if(this->Party[up].Count > 0 )
		{
			PartyCount = this->Party[up].Count;
		}

		gInterface.DrawGUI(ePT_SEARCH_USER_INFOBG, ContentX + 10, ContentY + 92 + i * 20);

		ListDrawX = ContentX + 20;
		ListDrawY = ContentY + 77 + i * 20;

		gInterface.DrawFormat(eYellow, ListDrawX - 7, ListDrawY + 20, 100, 1, this->Party[up].Name);

		ListDrawX += 50;
		gInterface.DrawFormat(eWhite, ListDrawX, ListDrawY + 20, 100, 1, pGetMapName(this->Party[up].Map));

		ListDrawX += 50;
		gInterface.DrawFormat(eWhite, ListDrawX, ListDrawY + 20, 100, 1, "%d", this->Party[up].X);

		ListDrawX += 15;
		gInterface.DrawFormat(eWhite, ListDrawX, ListDrawY + 20, 100, 1, "%d", this->Party[up].Y);

		ListDrawX += 20;
		gInterface.DrawFormat(eWhite, ListDrawX, ListDrawY + 20, 100, 1, "%d / %d", PartyCount, g_MaxPartyMember);

		ListDrawX += 27;
		gInterface.DrawGUI(ePT_SEARCH_USER_INFO, ListDrawX, ListDrawY + 18);

		// -> My Class
		char MyClass = gObjUser.Class;
		lpCharObj lpPlayer			= pUserObjectStruct;
		int MyLevel = lpPlayer->Level;
		int NeedLevel = this->Party[up].Level;
		// -----------

		ListDrawX += 19;

		// -> Check

		BYTE AtributeON = true;

		if(pGameIndex == this->Party[up].Index)
		{
			AtributeON = false;
		}
		if(g_Party.PartyMemberCount > 0)
		{
			AtributeON = false;
		}
		if(MyLevel > this->Party[up].Level)
		{
			AtributeON = false;
		}
		if(MyClass == CLASS_WIZARD && this->Party[up].dw == false)
		{
			AtributeON = false;
		}
		if(MyClass == CLASS_KNIGHT && this->Party[up].dk == false)
		{
			AtributeON = false;
		}
		if(MyClass == CLASS_ELF && this->Party[up].ee == false)
		{
			AtributeON = false;
		}
		if(MyClass == CLASS_MAGUMSA && this->Party[up].mg == false)
		{
			AtributeON = false;
		}
		if(MyClass == CLASS_DARKLORD && this->Party[up].dl == false)
		{
			AtributeON = false;
		}
		if(MyClass == CLASS_SUMMONER && this->Party[up].su == false && gObjUser.SUM)
		{
			AtributeON = false;
		}
		if(MyClass == CLASS_MONK && this->Party[up].rf == false && gObjUser.RF)
		{
			AtributeON = false;
		}

		gInterface.Data[ePT_SEARCH_USER_PAGEUP1 + i].Attribute = AtributeON;

		if(gInterface.Data[ePT_SEARCH_USER_PAGEUP1 + i].Attribute ) // Need Atribute
		{
			gInterface.DrawGUI(ePT_SEARCH_USER_PAGEUP1 + i, ListDrawX, ListDrawY + 17);

			if(gInterface.IsWorkZone(ePT_SEARCH_USER_PAGEUP1 + i))
			{
				DWORD Color = eGray100;
				// ----
				if( gInterface.Data[ePT_SEARCH_USER_PAGEUP1 + i].OnClick )
				{
					Color = eGray150;
				}
				// ----
				gInterface.DrawColoredGUI(ePT_SEARCH_USER_PAGEUP1 + i, gInterface.Data[ePT_SEARCH_USER_PAGEUP1 + i].X, gInterface.Data[ePT_SEARCH_USER_PAGEUP1 + i].Y, Color);
			}
		}

		if(gInterface.IsWorkZone(ePT_SEARCH_USER_INFO))
		{
			InfoDraw = true;
			InfoX = gInterface.Data[ePT_SEARCH_USER_INFO].X +5;
			InfoY = gInterface.Data[ePT_SEARCH_USER_INFO].Y + 25;
			this->InfoUP = up;
		}
	}

	gInterface.DrawGUI(ePT_SEARCH_USER_DIV, ContentX, gInterface.Data[ePT_SEARCH_USER_FOOTER].Y - 10);

	gInterface.DrawGUI(ePT_SEARCH_USER_L, ContentX + 80, ContentY + 325);
	gInterface.DrawGUI(ePT_SEARCH_USER_R, ContentX + 130, ContentY + 325);

	if(gInterface.IsWorkZone(ePT_SEARCH_USER_L))
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_SEARCH_USER_L].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_SEARCH_USER_L, gInterface.Data[ePT_SEARCH_USER_L].X, gInterface.Data[ePT_SEARCH_USER_L].Y, Color);
	}

	if(gInterface.IsWorkZone(ePT_SEARCH_USER_R))
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_SEARCH_USER_R].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_SEARCH_USER_R, gInterface.Data[ePT_SEARCH_USER_R].X, gInterface.Data[ePT_SEARCH_USER_R].Y, Color);
	}

	gInterface.DrawFormat(eGold, ContentX+97, ContentY + 329, 100, 1, g_ExText.GetText(34), this->Page+1,this->MaxParty/10+1);

	// -> Draw Info
	if(this->InfoDraw)
	{
		char NeedInfoText[256] = { 0 };
	
		sprintf(NeedInfoText, g_ExText.GetText(143));
		strcat(NeedInfoText, "\n");
		strcat(NeedInfoText, g_ExText.GetText(161));
		strcat(NeedInfoText, "\n");

		int BrCount = 2;

		if(this->Party[this->InfoUP].dw)
		{
			strcat(NeedInfoText, g_ExText.GetText(144));
			strcat(NeedInfoText, "\n");
			BrCount++;
		}
		if(this->Party[this->InfoUP].dk)
		{
			strcat(NeedInfoText,g_ExText.GetText(145));
			strcat(NeedInfoText, "\n");
			BrCount++;
		}
		if(this->Party[this->InfoUP].ee)
		{
			strcat(NeedInfoText,g_ExText.GetText(146));
			strcat(NeedInfoText, "\n");
			BrCount++;
		}
		if(this->Party[this->InfoUP].mg)
		{
			strcat(NeedInfoText,g_ExText.GetText(147));
			strcat(NeedInfoText, "\n");
			BrCount++;
		}
		if(this->Party[this->InfoUP].dl)
		{
			strcat(NeedInfoText,g_ExText.GetText(148));
			strcat(NeedInfoText, "\n");
			BrCount++;
		}
		if(this->Party[this->InfoUP].su && gObjUser.SUM)
		{
			strcat(NeedInfoText,g_ExText.GetText(149));
			strcat(NeedInfoText, "\n");
			BrCount++;
		}
		if(this->Party[this->InfoUP].rf && gObjUser.RF)
		{
			strcat(NeedInfoText,g_ExText.GetText(150));
			strcat(NeedInfoText, "\n");
			BrCount++;
		}

		int Br = BrCount * 10;
		int Wind = 60;

		if(pGameResolutionMode > 5)
		{
			Wind = 50;
		}

		pDrawColorButton(0x7880, this->InfoX, this->InfoY, Wind, Br, 0, 0, Color4f(0, 0, 0, 255));	

		gInterface.DrawFormat(eWhite, this->InfoX, this->InfoY, 60, 3, NeedInfoText, this->Party[this->InfoUP].Level);
	}
}
// ----------------------------------------------------------------------------------------------

void PartySearch::Button(DWORD Event)
{
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CLOSE, 0))
	{
		gInterface.CloseWindowEx(exWinPTSearchMaster);
	}
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_FINISH, 0))
	{
		// -> Send Auto Party Data to GS
		CG_AutoPartyInfo pRequest;
		pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x1B, sizeof(pRequest));	//0x0B
		pRequest.ActiveSystem = this->ActiveSystem;
		pRequest.MaxLevel = this->MaxLevel;
		pRequest.bAllClass = this->bAllClass;
		pRequest.bOnlyOneClass = this->bOnlyOneClass;
		pRequest.bDarkWizard = this->bDarkWizard;
		pRequest.bDarkKnight = this->bDarkKnight;
		pRequest.bElf = this->bElf;
		pRequest.bMagicGladiator = this->bMagicGladiator;
		pRequest.bDarkLord = this->bDarkLord;
		pRequest.bSummoner = this->bSummoner;
		gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
		// ----
		gInterface.CloseWindowEx(exWinPTSearchMaster);
	}
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_PAGEUP, 0))
	{
		if(this->ActiveSystem)
		{
			this->MaxLevel +=10;
			if(this->MaxLevel > 400)
			{
				this->MaxLevel = 400;
			}
		}
	}
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_PAGEDN, 0))
	{
		if(this->ActiveSystem)
		{
			this->MaxLevel -= 10;
			if(this->MaxLevel <= 10)
			{
				this->MaxLevel = 10;
			}
		}
	}
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK1, 0))
	{
		this->ActiveSystem = !this->ActiveSystem;
		this->bAllClass = false;
		//this->bOnlyOneClass = false;
		this->bDarkWizard = false;
		this->bDarkKnight = false;
		this->bElf = false;
		this->bMagicGladiator = false;
		this->bDarkLord = false;
		this->bSummoner = false;
		this->bAllClass = false;
		if(this->ActiveSystem)
		{
			this->bOnlyOneClass = true;	// true;
		}
	}
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK2, 0))	// All Classs
	{
		if(this->ActiveSystem)
		{
			this->bAllClass = !this->bAllClass;	//false;	//!this->bAllClass;
			this->bOnlyOneClass = false;
			/*
			this->bDarkWizard = false;
			this->bDarkKnight = false;
			this->bElf = false;
			this->bMagicGladiator = false;
			this->bDarkLord = false;
			this->bSummoner = false;*/
		}
	}		
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK3, 0))	// Only Gold Party
	{
		if(this->ActiveSystem)
		{
			this->bOnlyOneClass = !this->bOnlyOneClass;	//false;	//!this->bOnlyOneClass;
			this->bAllClass = false;
			this->bDarkWizard = false;
			this->bDarkKnight = false;
			this->bElf = false;
			this->bMagicGladiator = false;
			this->bDarkLord = false;
			this->bSummoner = false;
		}
	}	
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK4, 0))	// Dark Wizard
	{
		if(this->ActiveSystem)
		{
			this->bOnlyOneClass = false;
			//this->bAllClass = false;
			this->bDarkWizard = !this->bDarkWizard;
		}
	}	
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK5, 0))	// Dark Knight
	{
		if(this->ActiveSystem)
		{
			this->bOnlyOneClass = false;
			//this->bAllClass = false;
			this->bDarkKnight = !this->bDarkKnight;
		}
	}	
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK6, 0))	// Elf
	{
		if(this->ActiveSystem)
		{
			this->bOnlyOneClass = false;
			//this->bAllClass = false;
			this->bElf = !this->bElf;
		}
	}
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK7, 0))	// Magic
	{
		if(this->ActiveSystem)
		{
			this->bOnlyOneClass = false;
			//this->bAllClass = false;
			this->bMagicGladiator = !this->bMagicGladiator;
		}
	}	
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK8, 0))	// dl
	{
		if(this->ActiveSystem)
		{
			this->bOnlyOneClass = false;
			//this->bAllClass = false;
			this->bDarkLord = !this->bDarkLord;
		}
	}	
	// --
	if(gInterface.Button(Event, exWinPTSearchMaster, ePT_SEARCH_MASTER_CHECK9, 0))	// sum
	{
		if(this->ActiveSystem)
		{
			this->bOnlyOneClass = false;
			//this->bAllClass = false;
			this->bSummoner = !this->bSummoner;
		}
	}
	// --------
	if(gInterface.CheckWindowEx(exWinPTSearchUser))
	{
		for(int i = 0; i < 10; i++)
		{
			if(gInterface.Button(Event, exWinPTSearchUser, ePT_SEARCH_USER_PAGEUP1 + i, true))
			{
				int up = i + (  this->Page  * 10 );
				//Packet send	
				CG_PartyRecv pRequest;
				pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x1C, sizeof(pRequest));
				pRequest.UserIndex = this->Party[up].Index;
				gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
			}
		}
	}

	if( gInterface.Button(Event, exWinPTSearchUser, ePT_SEARCH_USER_L, false ) )
	{
		if(this->Page != 0)
		{
			this->Page--;
		}
		return;
	}
	else if( gInterface.Button(Event, exWinPTSearchUser, ePT_SEARCH_USER_R, false ) )
	{
		if(this->Page != this->MaxParty/10)
		{
			 this->Page++;
		}
		return;
	}

	if(gInterface.Button(Event, exWinPTSearchUser, ePT_SEARCH_USER_CLOSE, 0))
	{
		gInterface.CloseWindowEx(exWinPTSearchUser);
	}
}
// ----------------------------------------------------------------------------------------------

void PartySearch::GC_Recv(LPBYTE aRecv)
{
	ZeroMemory(&this->Party,sizeof(this->Party));
	int datasize = 6;
	int excount = aRecv[datasize-1];

	this->MaxParty = excount;

	for (int n = 0; n < excount; n++)
	{
		AutoParty_DATA ap;
		memcpy(&ap,&aRecv[datasize],sizeof(ap));

		this->Party[n].Index = ap.Index;

		strncpy(this->Party[n].Name, ap.Name, 10);

		this->Party[n].Level = ap.Level;
		this->Party[n].Map = ap.Map;
		this->Party[n].X = ap.X;
		this->Party[n].Y = ap.Y;
		this->Party[n].dw = ap.dw;
		this->Party[n].dk = ap.dk;
		this->Party[n].ee = ap.ee;
		this->Party[n].mg = ap.mg;
		this->Party[n].dl = ap.dl;
		this->Party[n].su = ap.su;
		this->Party[n].rf = ap.rf;
		this->Party[n].Count = ap.Count;
		datasize += sizeof(ap);

		if(n >= 200-1)
		{
			break;
		}
	}

	if(!gInterface.CheckWindowEx(exWinPTSearchUser))
	{
		gInterface.OpenWindowEx(exWinPTSearchUser);
	}
}
// ----------------------------------------------------------------------------------------------

void PartySearch::GC_InfoRecv(CG_AutoPartyInfo* aRecv)
{
	this->ActiveSystem = aRecv->ActiveSystem;
	this->MaxLevel = aRecv->MaxLevel;
	this->bAllClass = aRecv->bAllClass;
	this->bOnlyOneClass = aRecv->bOnlyOneClass;
	this->bDarkWizard = aRecv->bDarkWizard;
	this->bDarkKnight = aRecv->bDarkKnight;
	this->bElf = aRecv->bElf;
	this->bMagicGladiator = aRecv->bMagicGladiator;
	this->bDarkLord = aRecv->bDarkLord;
	this->bSummoner = aRecv->bSummoner;
}
// ----------------------------------------------------------------------------------------------

void PartySearch::CG_SendOpenUserList()
{
	GC_OPEN_SEND pRequest = { 0 };
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x1D, sizeof(pRequest));
	pRequest.Result = 1;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------