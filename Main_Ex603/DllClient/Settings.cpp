#include "stdafx.h"
#include "Settings.h"
#include "Interface.h"
#include "Protocol.h"
#include "Camera.h"
#include "Graphics.h"
#include "Configs.h"
#include "NewParty.h"
#include "QuestSystem.h"
#include "Controller.h"

#if(CUSTOM_WIN_SETTINGS==TRUE)
// ----------------------------------------------------------------------------------------------

Settings g_Settings;
// ----------------------------------------------------------------------------------------------

Settings::Settings()
{
	this->Init();
}

Settings::~Settings()
{
}

void Settings::Init()
{

}
// ----------------------------------------------------------------------------------------------

void Settings::BindImages()
{
	gInterface.BindObject(eSETTINGS_MAIN, 0x7A5A, 222, 303, -1, -1);
	gInterface.BindObject(eSETTINGS_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eSETTINGS_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eSETTINGS_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eSETTINGS_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eSETTINGS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eSETTINGS_INFOBG, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eSETTINGS_FINISH, 0x7A5E, 108, 29, -1, -1);

	gInterface.BindObject(eSETTINGS_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eSETTINGS_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eSETTINGS_CHECK1, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eSETTINGS_LINE2, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eSETTINGS_POINT2, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eSETTINGS_CHECK2, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eSETTINGS_LINE3, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eSETTINGS_POINT3, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eSETTINGS_CHECK3, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eSETTINGS_LINE4, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eSETTINGS_POINT4, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eSETTINGS_CHECK4, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eSETTINGS_LINE5, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eSETTINGS_POINT5, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eSETTINGS_CHECK5, 0x7B69, 15, 15, -1, -1);

	gInterface.BindObject(eSETTINGS_LINE6, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eSETTINGS_POINT6, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eSETTINGS_CHECK6, 0x7B69, 15, 15, -1, -1);

}
// ----------------------------------------------------------------------------------------------

void Settings::Draw()
{
	if(!gInterface.CheckWindowEx(exWinSettings))
	{
		return;
	}
	// ----
	pSetCursorFocus			= true;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentY = StartY;

	// ----
	gInterface.DrawGUI(eSETTINGS_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eSETTINGS_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eSETTINGS_FRAME, StartX, StartY + 67.0, 13);
	gInterface.DrawGUI(eSETTINGS_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eSETTINGS_CLOSE, StartX + MainWidth - gInterface.Data[eSETTINGS_CLOSE].Width, gInterface.Data[eSETTINGS_TITLE].Height + gInterface.Data[eSETTINGS_CLOSE].Height + 2);
	// ----
	if( gInterface.IsWorkZone(eSETTINGS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eSETTINGS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eSETTINGS_CLOSE, gInterface.Data[eSETTINGS_CLOSE].X, gInterface.Data[eSETTINGS_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eSETTINGS_CLOSE].X + 5, gInterface.Data[eSETTINGS_CLOSE].Y + 25, "Close");
	}
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Settings");
	// ---- 

	// -> Content
	ContentY += 40;

	//gInterface.DrawGUI(eSETTINGS_POINT1, StartX + 35, /*233*/ContentY+2);
	//gInterface.DrawFormat(eWhite, StartX + 60, /*235*/ContentY + 4, 100, 1, "3D Camera [Switch]");
	//if(gCamera.IsActive == TRUE)
	//{
	//	gInterface.DrawGUIY(eSETTINGS_CHECK1, StartX + 175, /*231*/ContentY, 0);
	//}
	//else
	//{
	//	gInterface.DrawGUIY(eSETTINGS_CHECK1, StartX + 175, ContentY, 1);
	//}
	//gInterface.DrawGUI(eSETTINGS_LINE1, StartX + 35, /*245*/ ContentY+14);
	//// --
	//ContentY += 20;

	gInterface.DrawGUI(eSETTINGS_POINT2, StartX + 35, /*233*/ContentY+2);
	gInterface.DrawFormat(eWhite, StartX + 60, /*235*/ContentY + 4, 100, 1, "Graphics Effect");
	if(g_bGlowGraphic == TRUE)
	{
		gInterface.DrawGUIY(eSETTINGS_CHECK2, StartX + 175, /*231*/ContentY, 0);
	}
	else
	{
		gInterface.DrawGUIY(eSETTINGS_CHECK2, StartX + 175, ContentY, 1);
	}
	gInterface.DrawGUI(eSETTINGS_LINE2, StartX + 35, /*245*/ ContentY+14);
	// --
	ContentY += 20;

	gInterface.DrawGUI(eSETTINGS_POINT3, StartX + 35, /*233*/ContentY+2);
	gInterface.DrawFormat(eWhite, StartX + 60, /*235*/ContentY + 4, 100, 1, "Party Hp Bar");
	if(iPartyHpBar == TRUE)
	{
		gInterface.DrawGUIY(eSETTINGS_CHECK3, StartX + 175, /*231*/ContentY, 0);
	}
	else
	{
		gInterface.DrawGUIY(eSETTINGS_CHECK3, StartX + 175, ContentY, 1);
	}
	gInterface.DrawGUI(eSETTINGS_LINE3, StartX + 35, /*245*/ ContentY+14);
	// --

	ContentY += 20;

	gInterface.DrawGUI(eSETTINGS_POINT4, StartX + 35, /*233*/ContentY+2);
	gInterface.DrawFormat(eWhite, StartX + 60, /*235*/ContentY + 4, 100, 1, "User Hp Bar");
	if(iUserHpBar == true)
	{
		gInterface.DrawGUIY(eSETTINGS_CHECK4, StartX + 175, /*231*/ContentY, 0);
	}
	else
	{
		gInterface.DrawGUIY(eSETTINGS_CHECK4, StartX + 175, ContentY, 1);
	}
	gInterface.DrawGUI(eSETTINGS_LINE4, StartX + 35, /*245*/ ContentY+14);

	// --

	ContentY += 20;

	gInterface.DrawGUI(eSETTINGS_POINT5, StartX + 35, /*233*/ContentY+2);
	gInterface.DrawFormat(eWhite, StartX + 60, /*235*/ContentY + 4, 100, 1, "Monster Hp Bar");
	if(iMonsterHPBar == true)
	{
		gInterface.DrawGUIY(eSETTINGS_CHECK5, StartX + 175, /*231*/ContentY, 0);
	}
	else
	{
		gInterface.DrawGUIY(eSETTINGS_CHECK5, StartX + 175, ContentY, 1);
	}
	gInterface.DrawGUI(eSETTINGS_LINE5, StartX + 35, /*245*/ ContentY+14);


	if(gPARTY_SYSTEM && g_Party.PartyMemberCount > 0)
	{
		ContentY += 20;

		gInterface.DrawGUI(eSETTINGS_POINT6, StartX + 35, /*233*/ContentY+2);
		gInterface.DrawFormat(eWhite, StartX + 60, /*235*/ContentY + 4, 100, 1, "Party Show");
		if(g_Party.PartyShow == true)
		{
			gInterface.DrawGUIY(eSETTINGS_CHECK6, StartX + 175, /*231*/ContentY, 0);
		}
		else
		{
			gInterface.DrawGUIY(eSETTINGS_CHECK6, StartX + 175, ContentY, 1);
		}
		gInterface.DrawGUI(eSETTINGS_LINE6, StartX + 35, /*245*/ ContentY+14);
	}

	///////////////////////////////////////////

	ContentY += 20;

	// -> End Content

	gInterface.DrawGUI(eSETTINGS_FINISH, ButtonX, gInterface.Data[eSETTINGS_FOOTER].Y + 10);
	gInterface.DrawFormat(eWhite, StartX + 8, gInterface.Data[eSETTINGS_FOOTER].Y + 20, 210, 3, "Save");
	gInterface.DrawGUI(eSETTINGS_DIV, StartX, gInterface.Data[eSETTINGS_FOOTER].Y - 10);

	if( gInterface.IsWorkZone(eSETTINGS_FINISH) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eSETTINGS_FINISH].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eSETTINGS_FINISH, gInterface.Data[eSETTINGS_FINISH].X, gInterface.Data[eSETTINGS_FINISH].Y, Color);
	}
}
// ----------------------------------------------------------------------------------------------

void Settings::Button(DWORD Event)
{
	if( gInterface.Button(Event, exWinSettings, eSETTINGS_CLOSE, false ) )
	{
		gInterface.CloseWindowEx(exWinSettings);
		return;
	}

	if( gInterface.Button(Event,exWinSettings, eSETTINGS_FINISH, false ) )
	{
		gInterface.CloseWindowEx(exWinSettings);
		//this->Save();
		//this->CG_ExSettings();
		return;
	}

	if( gInterface.Button(Event, exWinSettings, eSETTINGS_CHECK1, false ) )
	{
		gCamera.Switch();
		return;
	}

	if( gInterface.Button(Event, exWinSettings, eSETTINGS_CHECK2, false ) )
	{
		g_bGlowGraphic = !g_bGlowGraphic;
		return;
	}

	if( gInterface.Button(Event, exWinSettings, eSETTINGS_CHECK3, false ) )
	{
		iPartyHpBar = !iPartyHpBar;
		return;
	}

	if( gInterface.Button(Event, exWinSettings, eSETTINGS_CHECK4, false ) )
	{
		iUserHpBar = !iUserHpBar;
		return;
	}


	if( gInterface.Button(Event, exWinSettings, eSETTINGS_CHECK5, false ) )
	{
		iMonsterHPBar = !iMonsterHPBar;
	}

#if(NEW_GLOW_EFFECT==TRUE)
	if( gPARTY_SYSTEM && g_Party.PartyMemberCount > 0 && gInterface.Button(Event, exWinSettings, eSETTINGS_CHECK6, false ) )
	{
		g_Party.PartyShow = !g_Party.PartyShow;
	}
#endif
}
// ----------------------------------------------------------------------------------------------
#endif