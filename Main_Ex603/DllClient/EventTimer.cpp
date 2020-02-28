#include "stdafx.h"
#include "EventTimer.h"
#include "Import.h"
#include "Interface.h"
#include "Defines.h"
#include "ExLicense.h"
#include "ExText.h"

cEventTimer gEventTimer;

cEventTimer::cEventTimer()
{
	this->StartX = 2;
	this->StartY = 23;
	this->Width	 = 80;
	this->High	 = 75;	

	this->Active = false;
	this->Show = false;
}

void cEventTimer::Load()
{
	gInterface.LoadImages("Custom\\Interface\\EventTimer.tga", 100038, 0x2601, 0x2900, 1);
}

void cEventTimer::Draw()
{
	if(!this->Active) return;

	if(!this->Show) return;

	if( /*gInterface.CheckWindow(ObjWindow::ChatWindow) ||*/ gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::MoveList) /*|| gObjUser.m_MapNumber == 34 || gObjUser.m_MapNumber == 30*/ )
	{
		return;
	}

	int DrewY = StartY;
	int ipluxX = 7;

	if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		//pDrawColorButton(0x7880, StartX, DrewY+10, 100, 200, NULL, NULL, Color4f(0, 0, 0, 255));
		pDrawColorButton(0x7880, StartX, DrewY+10, 100+ipluxX, 260, NULL, NULL, Color4f(0, 0, 0, 255));
	}
	else if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
	{
		pDrawColorButton(0x7880, StartX, DrewY+10, 100, 200-45, NULL, NULL, Color4f(0, 0, 0, 255));
	}
	else
	{
		pDrawGUI(100038, StartX , DrewY , 150, 150);
	}

	

	int BC_H = (BCStart/3600)%24;
	int BC_M = (BCStart/60)%60;
	int BC_C = (BCStart)%60;

	gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, g_ExText.GetText(35));

	if(BCStart > 300)
	{
		gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	else
	{
		gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	
	DrewY += 15;
	// ----

	BC_H = (DSStart/3600)%24;
	BC_M = (DSStart/60)%60;
	BC_C = (DSStart)%60;

	gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, g_ExText.GetText(36));

	if(DSStart > 300)
	{
		gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	else
	{
		gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}

	DrewY += 15;
	// ----

	BC_H = (CCStart/3600)%24;
	BC_M = (CCStart/60)%60;
	BC_C = (CCStart)%60;

	gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, g_ExText.GetText(37));
	if(CCStart > 300)
	{
		gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	else
	{
		gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	DrewY += 15;
	// ----

	BC_H = (GDStart/3600)%24;
	BC_M = (GDStart/60)%60;
	BC_C = (GDStart)%60;

	gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, g_ExText.GetText(38));
	if(GDStart > 300)
	{
		gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	else
	{
		gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	DrewY += 15;
	// ----
	if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		BC_H = (this->m_dwTimeRedDragon/3600)%24;
		BC_M = (this->m_dwTimeRedDragon/60)%60;
		BC_C = (this->m_dwTimeRedDragon)%60;

		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Red Dragon:");
		if(this->m_dwTimeRedDragon > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
		}
		DrewY += 15;
	}
	// 000
	BC_H = (WWStart/3600)%24;
	BC_M = (WWStart/60)%60;
	BC_C = (WWStart)%60;

	gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, g_ExText.GetText(39));
	if(WWStart > 300)
	{
		gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	else
	{
		gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",BC_H,BC_M,BC_C);
	}
	DrewY += 15;

	// ------------------
	// ---- > Next Custom
	// ------------------
	int TimeMain;
	int TimeD;
	int TimeH;
	int TimeM;
	int TimeC;

	if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) ||
		g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
	{
		// --> Lorencia Battle
		TimeMain = TimeLora;
		TimeH = (TimeMain/3600)%24;
		TimeM = (TimeMain/60)%60;
		TimeC = (TimeMain)%60;
		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Lora Battle:");
		if(TimeMain > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		DrewY += 15;
		// --> Devias Battle
		if(!g_ExLicense.CheckUser(eExUB::Artem) && !g_ExLicense.CheckUser(eExUB::Artem2))
		{
			TimeMain = TimeDevias;
			TimeH = (TimeMain/3600)%24;
			TimeM = (TimeMain/60)%60;
			TimeC = (TimeMain)%60;
			gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Devias Battle:");
			if(TimeMain > 300)
			{
				gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
			}
			else
			{
				gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
			}
			DrewY += 15;
		}
		// --> Team vs Team
		TimeMain = TimeTvT;
		TimeH = (TimeMain/3600)%24;
		TimeM = (TimeMain/60)%60;
		TimeC = (TimeMain)%60;
		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Team vs Team:");
		if(TimeMain > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		DrewY += 15;
		// --> Pandora
		TimeMain = TimePandora;
		TimeH = (TimeMain/3600)%24;
		TimeM = (TimeMain/60)%60;
		TimeC = (TimeMain)%60;
		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Pandora Box:");
		if(TimeMain > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		DrewY += 15;
		// --> Evangelion
		TimeMain = TimeEvengelion;
		TimeH = (TimeMain/3600)%24;
		TimeM = (TimeMain/60)%60;
		TimeC = (TimeMain)%60;
		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Evangelion:");
		if(TimeMain > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		DrewY += 15;
		// --> Shop Event
		if(!g_ExLicense.CheckUser(eExUB::Artem) && !g_ExLicense.CheckUser(eExUB::Artem2))
		{
			TimeMain = TimeShop;
			TimeH = (TimeMain/3600)%24;
			TimeM = (TimeMain/60)%60;
			TimeC = (TimeMain)%60;
			gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Teleport Shop:");
			if(TimeMain > 300)
			{
				gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
			}
			else
			{
				gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
			}
			DrewY += 15;
		}
		// --> Happy Hour
		TimeMain = TimeHappy;
		TimeH = (TimeMain/3600)%24;
		TimeM = (TimeMain/60)%60;
		TimeC = (TimeMain)%60;
		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Happy Hour:");
		if(TimeMain > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
		}
		DrewY += 15;
		// --> Drop Event
		if(!g_ExLicense.CheckUser(eExUB::Artem) && !g_ExLicense.CheckUser(eExUB::Artem2))
		{
			TimeMain = TimeDropEvent;
			TimeH = (TimeMain/3600)%24;
			TimeM = (TimeMain/60)%60;
			TimeC = (TimeMain)%60;
			gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Drop Event:");
			if(TimeMain > 300)
			{
				gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
			}
			else
			{
				gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%2d:%02d:%02d",TimeH,TimeM,TimeC);
			}
			DrewY += 15;
		}
	}

	if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		// --> Cry Wolf Event
		TimeMain = this->m_dwTimeCryWolf;
		TimeD = (TimeMain/86400)%7;
		TimeH = (TimeMain/3600)%24;
		TimeM = (TimeMain/60)%60;
		TimeC = (TimeMain)%60;
		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Cry Wolf:");
		if(TimeMain > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%d:%2d:%02d:%02d",TimeD,TimeH,TimeM,TimeC);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%d:%2d:%02d:%02d",TimeD,TimeH,TimeM,TimeC);
		}
		DrewY += 15;

		// --> Castle Siege Event
		TimeMain = this->m_dwTimeCastleSiege;
		TimeD = (TimeMain/86400)%7;
		TimeH = (TimeMain/3600)%24;
		TimeM = (TimeMain/60)%60;
		TimeC = (TimeMain)%60;
		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Castle Siege:");
		if(TimeMain > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%d:%2d:%02d:%02d",TimeD,TimeH,TimeM,TimeC);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%d:%2d:%02d:%02d",TimeD,TimeH,TimeM,TimeC);
		}
		DrewY += 15;

		// --> Dungeon Siege Event
		TimeMain = this->m_dwTimeDungeonSiege;
		TimeD = (TimeMain/86400)%7;
		TimeH = (TimeMain/3600)%24;
		TimeM = (TimeMain/60)%60;
		TimeC = (TimeMain)%60;
		gInterface.DrawFormat(eGold, StartX + 10, DrewY + 10 + 5, 60, 1, "Dungeon Siege:");
		if(TimeMain > 300)
		{
			gInterface.DrawFormat(eWhite, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%d:%2d:%02d:%02d",TimeD,TimeH,TimeM,TimeC);
		}
		else
		{
			gInterface.DrawFormat(eExcellent, StartX + 60+ipluxX, DrewY + 10 + 5, 60, 1, "%d:%2d:%02d:%02d",TimeD,TimeH,TimeM,TimeC);
		}
		DrewY += 15;
	}
}