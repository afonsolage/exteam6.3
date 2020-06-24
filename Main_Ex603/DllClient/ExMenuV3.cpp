#include "stdafx.h"
#include "MiniMenu.h"
#include "Interface.h"
#include "Console.h"
#include "DonateShop.h"
#include "PartySearch.h"
#include "User.h"
#include "Protocol.h"
#include "PersonalShopEx.h"
#include "Achievements.h"
#include "Configs.h"
#include "Ranking.h"
#include "EventTimer.h"
#include "AutoParty.h"
#include "ExLicense.h"
#include "NewParty.h"
#include "Settings.h"
#include "Camera.h"
#include "Configs.h"
#include "JewelsBank.h"
#include "QuestSystem.h"
#include "DataSend.h"
#include "ReferralSystem.h"
#include "ExText.h"
#include "ExMenuV3.h"
#include "PremiumSystemEx.h"
#include "ChatExpanded.h"
#include "AddPoints.h"
#include "TrayMode.h"
#include "HuntingSystem.h"

#if(DEV_EXMENU_V3)

CExMenuV3 g_ExMenuV3;

CExMenuV3::CExMenuV3()
{
	this->Init();
}

CExMenuV3::~CExMenuV3()
{
}

void CExMenuV3::Init()
{
	this->m_Enable = false;
	this->m_Version = EXMENU_NUMBER::eVERSION_NO;

	gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);
}

void CExMenuV3::LoadIMG()
{
	gInterface.LoadImages("Custom\\Interface\\newui_btn_mini.tga", ex_EXMENU3_BUTTON_01, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\server_menu_b_all.tga", ex_EXMENU3_BUTTON_02, 0x2601, 0x2900, 1);
}

void CExMenuV3::Bind()
{
	//gInterface.BindObject(eEXMENU3_MENU, 0x7BAC, 168, 18, -1, -1);

	gInterface.BindObject(eEXMENU3_MAIN, 0x7A5A, 222, 435, -1, -1);	//230
	gInterface.BindObject(eEXMENU3_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eEXMENU3_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eEXMENU3_FOOTER, 0x7A59, 230, 50, -1, -1);

	gInterface.BindObject(eEXMENU3_BUTTON_01, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_02, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_03, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_04, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_05, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_06, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_07, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_08, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_09, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_10, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_11, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_12, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_13, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_14, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_15, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_16, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_17, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_18, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_19, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_20, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_21, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_22, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	gInterface.BindObject(eEXMENU3_BUTTON_23, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
	//gInterface.BindObject(eEXMENU3_BUTTON_24, ex_EXMENU3_BUTTON_01, 108, 24, -1, -1);
}

void CExMenuV3::Load(EXMENU_NUMBER Number)
{
	this->m_Enable = true;
	this->m_Version = Number;

	if(this->m_Version == EXMENU_NUMBER::eVERSION_NS)
	{
		gInterface.BindObject(eEXMENU3_MENU, 0x7BAC, 168, 18, -1, -1);
	}
	else if(this->m_Version == EXMENU_NUMBER::eVERSION_ET)
	{
		gInterface.BindObject(eEXMENU3_MENU, ex_EXMENU3_BUTTON_02, 53, 27, -1, -1);
	}	
	else if(this->m_Version == EXMENU_NUMBER::eVERSION_WB)
	{
		// ----
	}	
}

void CExMenuV3::DrawMain()
{
	if(!this->m_Enable)
	{
		return;
	}

	if(pPlayerState != GameProcess)
	{
		return;
	}

	if(gInterface.CheckWindow(ObjWindow::CashShop)  || 
	   gInterface.CheckWindow(ObjWindow::FullMap)   || 
	   gInterface.CheckWindow(ObjWindow::SkillTree) || 
	   gInterface.CheckWindow(ObjWindow::MoveList)	||
	   gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievements))
	{
		return;
	}

	if(this->m_Version == EXMENU_NUMBER::eVERSION_NS)
	{
		this->DrawWindow();
		this->DrawMenu();
	}
	else if(this->m_Version == EXMENU_NUMBER::eVERSION_ET)
	{
		#if(USERPANEL)
		gInterface.DrawUsersPanel();
		#endif
		this->DrawWindow2();
		//this->DrawMenu2();

		
	}	
	else if(this->m_Version == EXMENU_NUMBER::eVERSION_WB)
	{
		// ----
	}	
}

void CExMenuV3::DrawMenu()
{
	float StartY			= 16.0;
	float StartX			= 20;

	gInterface.DrawGUI(eEXMENU3_MENU, StartX , StartY);

	if(gInterface.IsWorkZone(eEXMENU3_MENU))
	{
		gInterface.DrawFormat(eYellow, StartX, StartY + 3, 168, 3, "Menu [F11]");
	}
	else
	{
		gInterface.DrawFormat(eAncient, StartX, StartY + 3, 168, 3, "Menu [F11]");
	}
}

void CExMenuV3::DrawWindow()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMenuV3))
	{
		return;
	}

	pSetCursorFocus = true;

	float StartY = 18.0;
	float StartX = 42.5;

	//pDrawColorButton(0x7880, StartX, StartY, 190, 420, NULL, NULL, Color4f(0, 0, 0, 150));
	pDrawColorButton(0x7880, StartX, StartY, 118, 330, NULL, NULL, Color4f(0, 0, 0, 150));

	float flDrawX = StartX + 5;
	float flDrawY = StartY + 20;

	// ====
	/*
	flDrawY = this->DrawButon("New button 1", eEXMENU3_BUTTON_01, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 2", eEXMENU3_BUTTON_02, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 3", eEXMENU3_BUTTON_03, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 4", eEXMENU3_BUTTON_04, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 5", eEXMENU3_BUTTON_05, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 6", eEXMENU3_BUTTON_06, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 7", eEXMENU3_BUTTON_07, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 8", eEXMENU3_BUTTON_08, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 9", eEXMENU3_BUTTON_09, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 10", eEXMENU3_BUTTON_10, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 11", eEXMENU3_BUTTON_11, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 12", eEXMENU3_BUTTON_12, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 13", eEXMENU3_BUTTON_13, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 14", eEXMENU3_BUTTON_14, flDrawX, flDrawY);

	flDrawY = this->DrawButon("New button 15", eEXMENU3_BUTTON_15, flDrawX, flDrawY);
	*/
	// ====

	// =====================================================================

	if(g_ExLicense.CheckUser(eExUB::NSGames))
	{
		flDrawY = this->DrawButton("Vote for Server", eEXMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eEXMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	if(g_ExLicense.CheckUser(eExUB::GloryMU))
	{
		flDrawY = this->DrawButton("Buy Credits", eEXMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eEXMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	//flDrawY = this->DrawButton(g_ExText.GetText(183), eEXMENU3_BUTTON_01, flDrawX, flDrawY);

	if(g_ExLicense.m_Achievements)
	{
		flDrawY = this->DrawButton("Achievements", eEXMENU3_BUTTON_02, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Power", eEXMENU3_BUTTON_03, flDrawX, flDrawY);
	}

	if(g_ExLicense.user.AccSecurity)
	{
		flDrawY = this->DrawButton("Account Security", eEXMENU3_BUTTON_18, flDrawX, flDrawY);
	}

	if(g_ExLicense.user.PremiumEx)
	{
		flDrawY = this->DrawButton("VIP [J]", eEXMENU3_BUTTON_19, flDrawX, flDrawY);
	}

	//flDrawY = this->DrawButton("Add Points", eEXMENU3_BUTTON_24, flDrawX, flDrawY, !gObjUser.IsVIP());

	flDrawY = this->DrawButton("Options", eEXMENU3_BUTTON_04, flDrawX, flDrawY);

	if (g_ExLicense.user.Enable3DCamera)
		flDrawY = this->DrawButton("3D Camera [Reset]", eEXMENU3_BUTTON_05, flDrawX, flDrawY);

	if (g_ExLicense.user.JewelBank)
		flDrawY = this->DrawButton("Jewels Bank", eEXMENU3_BUTTON_06, flDrawX, flDrawY);

	//if(gRAGESYSTEM)
	//{
	//	flDrawY = this->DrawButton("Rage System", eEXMENU3_BUTTON_07, flDrawX, flDrawY);
	//}

	flDrawY = this->DrawButton("Hunting System", eEXMENU3_BUTTON_07, flDrawX, flDrawY);

	if(gWINQUEST)
	{
		flDrawY = this->DrawButton("Quest", eEXMENU3_BUTTON_08, flDrawX, flDrawY);
		flDrawY = this->DrawButton("Quest Options", eEXMENU3_BUTTON_09, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Offline Attack [H]", eEXMENU3_BUTTON_10, flDrawX, flDrawY);
	flDrawY = this->DrawButton("Offline Shop", eEXMENU3_BUTTON_23, flDrawX, flDrawY);

	if(gRanking.Active)
	{
		flDrawY = this->DrawButton("Top 100 Player", eEXMENU3_BUTTON_11, flDrawX, flDrawY);
	}

	if(gEventTimer.Active)
	{
		flDrawY = this->DrawButton("Events Timer [Y]", eEXMENU3_BUTTON_12, flDrawX, flDrawY);
	}

	#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Auto Party [K]", eEXMENU3_BUTTON_13, flDrawX, flDrawY);
	}
	#endif

	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Party Search List [L]", eEXMENU3_BUTTON_14, flDrawX, flDrawY);
	}
	else
	{
		if(gAutoParty.Active)
		{
			flDrawY = this->DrawButton("Auto Party List", eEXMENU3_BUTTON_15, flDrawX, flDrawY);
		}
	}

	flDrawY = this->DrawButton("Minimizer [F12]", eEXMENU3_BUTTON_16, flDrawX, flDrawY);

	if(g_ExLicense.user.Smithy == true)
	{
		flDrawY = this->DrawButton("Smithy", eEXMENU3_BUTTON_16, flDrawX, flDrawY);
	}

	//if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || 
	//	g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
	//	THINNAKORN_MAC == 1 || g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	//{
	//	flDrawY = this->DrawButton("Custom", eEXMENU3_BUTTON_17, flDrawX, flDrawY);
	//}
}

float CExMenuV3::DrawButton(char* Text, int ID, float X, float Y, bool disabled)
{
	float flResult = 0;
	float flButtonX = X;
	float flButtonY = Y;
	DWORD dwColor = eGray100;

	gInterface.DrawGUI(ID, flButtonX, flButtonY);

	if(disabled || gInterface.IsWorkZone(ID))
	{
		if(gInterface.Data[ID].OnClick)
		{
			dwColor = eGray150;
		}

		gInterface.DrawColoredGUI(ID, gInterface.Data[ID].X, gInterface.Data[ID].Y, dwColor);

		dwColor = (disabled ? eWhite : eYellow);
		gInterface.DrawFormat(dwColor, flButtonX, flButtonY + 7, 108, 3, Text);
	}
	else
	{
		gInterface.DrawFormat(eWhite, flButtonX, flButtonY + 7, 108, 3, Text);
	}

	flResult = Y + gInterface.Data[ID].Height + 1.5;

	return flResult;
}

void CExMenuV3::CursorButton(DWORD Event)
{
	if(pPlayerState != GameProcess)
	{
		return;
	}

	if(gInterface.CheckWindow(ObjWindow::CashShop)  || 
	   gInterface.CheckWindow(ObjWindow::FullMap)   || 
	   gInterface.CheckWindow(ObjWindow::SkillTree) || 
	   gInterface.CheckWindow(ObjWindow::MoveList))
	{
		return;
	}

	//if(gInterface.Data[eEXMENU3_MENU].X == -1 || gInterface.Data[eEXMENU3_MENU].Y == -1)
	//{
	//	return;
	//}

	if(gInterface.IsWorkZone(eEXMENU3_MENU))
	{
		pSetCursorFocus = true;
	}

	if(gInterface.CheckWindowEx(ObjWindowsEx::exWinMenuV3))
	{
		if(gInterface.ButtonEx(Event, eEXMENU3_MENU, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);
			return;
		}
	}
	else
	{
		if(gInterface.ButtonEx(Event, eEXMENU3_MENU, false))
		{
			gInterface.OpenWindowEx(ObjWindowsEx::exWinMenuV3);
			return;
		}
	}

	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMenuV3))
	{
		return;
	}

	/*if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMenuV3))
	{
		g_Settings.Button(Event);
		return;
	}*/

	if(g_ExLicense.CheckUser(eExUB::NSGames))
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_20,  false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			ShellExecute(NULL, "open", "https://mu.mmotop.ru/servers/32190", NULL, NULL, SW_MAXIMIZE);		
		}

		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_21,  false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			#if(DONATE_SHOP==TRUE)
			if(!gInterface.CheckWindow(Shop))
			{
				g_DonateShop.CG_CashSend();
			}
			#endif
		}
	}

	if(g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_20,  false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			ShellExecute(NULL, "open", "https://mu.mmotop.ru/servers/32083", NULL, NULL, SW_MAXIMIZE);		
		}

		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_21,  false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			#if(DONATE_SHOP==TRUE)
			if(!gInterface.CheckWindow(Shop))
			{
				g_DonateShop.CG_CashSend();
			}
			#endif
		}

	}

	if(g_ExLicense.CheckUser(eExUB::GloryMU))
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_20,  false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			ShellExecute(NULL, "open", "http://glorymu.org/cabinet/pay", NULL, NULL, SW_MAXIMIZE);		
		}

		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_21,  false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			#if(DONATE_SHOP==TRUE)
			if(!gInterface.CheckWindow(Shop))
			{
				g_DonateShop.CG_CashSend();
			}
			#endif
		}
	}

#if(ENABLE_DONATE_BUTTON==TRUE)
	if( gInterface.ButtonEx(Event, eEXMENU3_BUTTON_01, false ) )
	{
		lpViewObj lpViewPlayer = &*(ObjectPreview*)oUserPreviewStruct;

		if(lpViewPlayer->InSafeZone)
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			gInterface.m_bCashShopOpen = true;
		}
		return;
	}
#endif

	if (gInterface.ButtonEx(Event, eEXMENU3_BUTTON_23, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

		PMSG_CHATDATA data;
		data.h.set((LPBYTE)&data, 0x00, sizeof(data));
		sprintf(data.chatmsg, "/offshop");
		gProtocol.DataSend((LPBYTE)&data, data.h.size);
	}

	//if (gInterface.ButtonEx(Event, eEXMENU3_BUTTON_24, false))
	//{
	//	gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);
	//	
	//	g_AddPoints.Open(0);
	//}

#if(SYSTEM_ACHIEVEMENTS)
	if(gInterface.ButtonEx(Event, eEXMENU3_BUTTON_02, false))
	{
		g_Achievements.CGWindowOpen();

		gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);
	}

	if(gInterface.ButtonEx(Event, eEXMENU3_BUTTON_03, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);	

		if(gInterface.CheckWindowEx(exWinAchievementsPower))
		{
			gInterface.CloseWindowEx(exWinAchievementsPower);
		}
		else
		{
			gInterface.OpenWindowEx(exWinAchievementsPower);
		}
	}
#endif

	if(g_ExLicense.user.AccSecurity)
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_18, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			gInterface.OpenWindowEx(ObjWindowsEx::exWinAccWarning);
		}
	}

	if(g_ExLicense.user.PremiumEx)
	{
		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::MedoniAndrei))
		{
		}
		else
		{
			if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_19, false))
			{
				gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

				//gInterface.OpenWindowEx(ObjWindowsEx::exWinPremium);
				g_PremiumSystemEx.CG_SendOpenWindows();
			}
		}
	}

	if( gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_04, false ) )
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

		gInterface.OpenWindowEx(exWinSettings);
	}

	if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_05, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

		gCamera.Init();
	}

	if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_06, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

		gJewelsBank.Active = !gJewelsBank.Active;
	}

	//if(gRAGESYSTEM)
	//{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_07, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			//gInterface.Data[eRageTable].OnShow = !gInterface.Data[eRageTable].OnShow;
			gInterface.OpenWindowEx(ObjWindowsEx::exWinHuntingSystem);
		}
	//}

	if(gWINQUEST)
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_08, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			gQuestSystem.Switcher(0);
		}
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_09, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			gQuestSystem.Switcher(1);
		}
	}

	if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_10, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

		//if(g_ExLicense.user.OfflineMode)
		//{
			if(gInterface.CheckWindowEx(exWinCheckOffAfk))
			{
				gInterface.CloseWindowEx(exWinCheckOffAfk);
			}
			else
			{
				gInterface.OpenWindowEx(exWinCheckOffAfk);
			}
		//}
		//else
		//{
		//	gDataSend.SendOfflineAttack();
		//}
	}
	if(gRanking.Active)
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_11, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			if(!gInterface.CheckWindowEx(exWinRanking))
			{
				gInterface.OpenWindowEx(exWinRanking);
			}
			else if(gInterface.CheckWindowEx(exWinRanking))
			{
				gInterface.CloseWindowEx(exWinRanking);
			}
		}
	}

	if(gEventTimer.Active)
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_12, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			gEventTimer.Show = !gEventTimer.Show;
		}
	}

	#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_13, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			if(!gInterface.CheckWindowEx(exWinPTSearchMaster) && !gInterface.CheckWindowEx(exWinPTSearchUser))
			{
				gInterface.OpenWindowEx(exWinPTSearchMaster);
			}
			else if(gInterface.CheckWindowEx(exWinPTSearchMaster))
			{
				gInterface.CloseWindowEx(exWinPTSearchMaster);
			}
		}
	}
	#endif

	if(g_PartySearch.Active)
	{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_14, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);

			if(!gInterface.CheckWindowEx(exWinPTSearchMaster) && !gInterface.CheckWindowEx(exWinPTSearchUser))
			{
				g_PartySearch.CG_SendOpenUserList();
			}
			else if(gInterface.CheckWindowEx(exWinPTSearchUser))
			{
				gInterface.CloseWindowEx(exWinPTSearchUser);
			}
		}
	}
	else
	{
		if(gAutoParty.Active)
		{
			if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_15,  false))
			{
				gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);
				gDataSend.SendOpenAutoPartyList();
			}
		}
	}

	//if(g_ExLicense.user.Smithy == true)
	//{
		if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_16,  false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);
			gTrayMode.SwitchState();
		}
	//}

	//if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
	//	THINNAKORN_MAC == 1 || g_ExLicense.CheckUser(eExUB::MedoniAndrei) )
	{
		//if(gInterface.Button(Event, ObjWindowsEx::exWinMenuV3, eEXMENU3_BUTTON_17,  false))
		//{
		//	gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);
		//	//if(!gInterface.CheckWindowEx(exWinCustomMenu))
		//	//{
		//	//	gInterface.OpenWindowEx(exWinCustomMenu);
		//	//}
		//	//else
		//	//{
		//	//	gInterface.CloseWindowEx(exWinCustomMenu);
		//	//}

		//	if(!gInterface.CheckWindowEx(exWinReferralSystem))
		//	{
		//		g_ReferralSystem.CGReqMasterInfo();
		//		g_ReferralSystem.CGReqUserInfo();

		//		gInterface.OpenWindowEx(exWinReferralMenu);
		//	}
		//}
	}
}

void CExMenuV3::DrawMenu2()
{
	//if(    gInterface.CheckWindow(Party)
	//	|| gInterface.CheckWindow(Guild)
	//	|| gInterface.CheckWindow(Trade)
	//	|| gInterface.CheckWindow(Warehouse)
	//	|| gInterface.CheckWindow(ChaosBox)
	//	|| gInterface.CheckWindow(CommandWindow)
	//	|| gInterface.CheckWindow(PetInfo)
	//	|| gInterface.CheckWindow(Shop)
	//	|| gInterface.CheckWindow(Inventory)
	//	|| gInterface.CheckWindow(Store)
	//	|| gInterface.CheckWindow(OtherStore)
	//	|| gInterface.CheckWindow(Character)
	//	|| gInterface.CheckWindow(FastMenu)
	//	|| gInterface.CheckWindow(SkillTree)
	//	|| gInterface.CheckWindow(NPC_Titus)
	//	|| gInterface.CheckWindow(CashShop)
	//	|| gInterface.CheckWindow(FullMap)
	//	|| gInterface.CheckWindow(NPC_Dialog)
	//	|| gInterface.CheckWindow(GensInfo)
	//	|| gInterface.CheckWindow(NPC_Julia)
	//	|| gInterface.CheckWindow(ExpandInventory)
	//	|| gInterface.CheckWindow(ExpandWarehouse) 
	//	|| gInterface.CheckWindow(Helper) 
	//	|| gInterface.CheckWindow(Quest) 
	//	|| gInterface.CheckWindow(QuestDevin) 
	//	|| gInterface.CheckWindow(DevilSquery) 
	//	|| gInterface.CheckWindow(GuardNPC) 
	//	|| gInterface.CheckWindow(VorotaCS) 
	//	|| gInterface.CheckWindow(Rena) 
	//	|| gInterface.CheckWindow(LuckyCoins)
	//	|| gInterface.CheckWindow(Titus)
	//	|| gInterface.CheckWindow(BloodCastle) )
	//{
	//	return;
	//}

	//if( gInterface.CheckWindowEx(exWinRanking)		  ||
	//	gInterface.CheckWindowEx(exWinPersonalPrice) )
	//{
	//	return;
	//}

	float StartY = 379;
	float StartX = 0;//MAX_WIN_WIDTH - 100;
	//float StartY = 0;
	//float StartX = MAX_WIN_WIDTH - 125;

	gInterface.DrawGUI(eEXMENU3_MENU, StartX , StartY);

	if(gInterface.IsWorkZone(eEXMENU3_MENU))
	{
		pSetCursorFocus = true;
		
		DWORD dwColor = eGray100;

		if(gInterface.Data[eEXMENU3_MENU].OnClick)
		{
			dwColor = eGray150;
		}

		gInterface.DrawColoredGUI(eEXMENU3_MENU, gInterface.Data[eEXMENU3_MENU].X, gInterface.Data[eEXMENU3_MENU].Y, dwColor);
	}

	//if(gInterface.IsWorkZone(eEXMENU3_MENU))
	//{
	//	gInterface.DrawFormat(eWhite, StartX, StartY + 3, 168, 3, "Eternal");
	//	gInterface.DrawFormat(eYellow, StartX, StartY + 13, 168, 3, "Menu");
	//}
	//else
	//{
	//	gInterface.DrawFormat(eWhite, StartX, StartY + 3, 168, 3, "Eternal");
	//	gInterface.DrawFormat(eAncient, StartX, StartY + 13, 168, 3, "Menu");
	//}
}

void CExMenuV3::DrawWindow2()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMenuV3))
	{
		return;
	}

	pSetCursorFocus = true;

	float StartY = 0;
	float StartX = MAX_WIN_WIDTH - 225;

	gInterface.DrawWindow(eEXMENU3_MAIN, eEXMENU3_TITLE, eEXMENU3_FRAME, eEXMENU3_FOOTER, 21, StartX, StartY, "Menu");
	//pDrawColorButton(0x7880, StartX, StartY, 190, 430, NULL, NULL, Color4f(0, 0, 0, 255));

	float flDrawX = StartX + 42.5 + 15;	//42.5;
	float flDrawY = StartY + 20 + 20;

	// =====================================================================

	/*if(g_ExLicense.CheckUser(eExUB::NSGames))
	{
		flDrawY = this->DrawButton("Vote for Server", eEXMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eEXMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	if(g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		flDrawY = this->DrawButton("Vote for Server", eEXMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eEXMENU3_BUTTON_21, flDrawX, flDrawY);
	}

	if(g_ExLicense.CheckUser(eExUB::GloryMU))
	{
		flDrawY = this->DrawButton("Buy Credits", eEXMENU3_BUTTON_20, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Donate Shop", eEXMENU3_BUTTON_21, flDrawX, flDrawY);
	}*/


	if(g_ExLicense.m_Achievements)
	{
		flDrawY = this->DrawButton("Achievements", eEXMENU3_BUTTON_02, flDrawX, flDrawY);

		flDrawY = this->DrawButton("Power", eEXMENU3_BUTTON_03, flDrawX, flDrawY);
	}

	if(g_ExLicense.user.AccSecurity)
	{
		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
		{
		}
		else
		{
			flDrawY = this->DrawButton("Account Security", eEXMENU3_BUTTON_18, flDrawX, flDrawY);
		}
	}

	if(g_ExLicense.user.PremiumEx)
	{
		flDrawY = this->DrawButton("Premium System", eEXMENU3_BUTTON_19, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Options", eEXMENU3_BUTTON_04, flDrawX, flDrawY);

	if (g_ExLicense.user.Enable3DCamera)
		flDrawY = this->DrawButton("3D Camera [Reset]", eEXMENU3_BUTTON_05, flDrawX, flDrawY);

	if (g_ExLicense.user.JewelBank)
		flDrawY = this->DrawButton("Jewels Bank", eEXMENU3_BUTTON_06, flDrawX, flDrawY);

	if(gRAGESYSTEM)
	{
		flDrawY = this->DrawButton("Rage System", eEXMENU3_BUTTON_07, flDrawX, flDrawY);
	}

	if(gWINQUEST)
	{
		flDrawY = this->DrawButton("Quest", eEXMENU3_BUTTON_08, flDrawX, flDrawY);
		flDrawY = this->DrawButton("Quest Options", eEXMENU3_BUTTON_09, flDrawX, flDrawY);
	}

	flDrawY = this->DrawButton("Offline Attack", eEXMENU3_BUTTON_10, flDrawX, flDrawY);

	if(gRanking.Active)
	{
		flDrawY = this->DrawButton("Top 100 Player", eEXMENU3_BUTTON_11, flDrawX, flDrawY);
	}

	if(gEventTimer.Active)
	{
		flDrawY = this->DrawButton("Events Timer", eEXMENU3_BUTTON_12, flDrawX, flDrawY);
	}

	#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Auto Party", eEXMENU3_BUTTON_13, flDrawX, flDrawY);
	}
	#endif

	if(g_PartySearch.Active)
	{
		flDrawY = this->DrawButton("Party Search List", eEXMENU3_BUTTON_14, flDrawX, flDrawY);
	}
	else
	{
		if(gAutoParty.Active)
		{
			flDrawY = this->DrawButton("Auto Party List", eEXMENU3_BUTTON_15, flDrawX, flDrawY);
		}
	}

	if(g_ExLicense.user.Smithy == true)
	{
		flDrawY = this->DrawButton("Smithy", eEXMENU3_BUTTON_16, flDrawX, flDrawY);
	}

	if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || 
		g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
		THINNAKORN_MAC == 1 || g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		flDrawY = this->DrawButton("Custom", eEXMENU3_BUTTON_17, flDrawX, flDrawY);
	}
}

#endif