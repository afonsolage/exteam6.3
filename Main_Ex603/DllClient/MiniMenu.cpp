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
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_MINIMENU==TRUE)

MiniMenu g_MiniMenu;
// ----------------------------------------------------------------------------------------------

MiniMenu::MiniMenu()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

MiniMenu::~MiniMenu()
{
}
// ----------------------------------------------------------------------------------------------

void MiniMenu::Init()
{
	ZeroMemory(&this->szUrlQtop, sizeof(this->szUrlQtop));
}
// ----------------------------------------------------------------------------------------------

void MiniMenu::Load()
{
}
// ----------------------------------------------------------------------------------------------

void MiniMenu::BindImage()
{
	int bindY = 78 + 17;
#if(SYSTEM_ACHIEVEMENTS)
	bindY += 17;
	bindY += 17;
#endif
#if(ENABLE_DONATE_BUTTON==TRUE)
	bindY += 17;
#endif
	//gInterface.BindObject(eMINIMENU_MAIN, 0x7A5A, 110, bindY , -1, -1);
	gInterface.BindObject(eMINIMENU_TITLE, 0x7B5B, 110, 40, -1, -1);	
	gInterface.BindObject(eMINIMENU_FRAME, 0x7B5C, 110, 13, -1, -1);	
	gInterface.BindObject(eMINIMENU_FOOTER, 0x7B5D, 110, 40, -1, -1);

	gInterface.BindObject(eMINIMENU_LINE, 0x7B5E, 80, 3, -1, -1);
	gInterface.BindObject(eMINIMENU_BT1, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT2, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT3, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT4, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT5, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT6, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT7, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT8, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT9, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT10, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT11, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT12, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT13, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT14, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT15, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT16, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT17, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT18, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT19, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT20, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT21, NULL, 80, 16, -1, -1);
	gInterface.BindObject(eMINIMENU_BT22, NULL, 80, 16, -1, -1);

	gInterface.BindObject(eMINIMENU_ARROW_L, 0x7B5F, 6, 9, -1, -1);
	gInterface.BindObject(eMINIMENU_ARROW_R, 0x7B60, 6, 9, -1, -1);

	g_Settings.BindImages();
}
// ----------------------------------------------------------------------------------------------

void MiniMenu::Draw()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMiniMenu))
	{
		return;
	}

	#if(DEV_EXMENU_V3)
	if(g_ExMenuV3.m_Enable)
	{
		return;
	}
	#endif

	pSetCursorFocus			= true;
	float MainWidth			= 110;
	float StartX			= 410;
	float StartY			= 150;
	int iRepeat				= this->GetCountButton();
	float MainCenter		= StartX + (MainWidth / 3);

	StartY -= iRepeat * 20;

	pDrawGUI(gInterface.Data[eMINIMENU_MAIN].ModelID, StartX, StartY, gInterface.Data[eMINIMENU_MAIN].Width, (iRepeat+1) * 20);
	gInterface.DrawGUI(eMINIMENU_TITLE, StartX, StartY);

	// =====================================================================

	//if(g_ExLicense.CheckUser(eExUB::GloryMU))
	//{
		StartY = this->DrawButton("Buy Credits", eMINIMENU_BT20, StartX, StartY);

		StartY = this->DrawButton("Donate Shop", eMINIMENU_BT21, StartX, StartY);
	//}

	StartY = this->DrawButton(g_ExText.GetText(183), eMINIMENU_BT1, StartX, StartY);

	if(g_ExLicense.m_Achievements)
	{
		StartY = this->DrawButton("Achievements", eMINIMENU_BT2, StartX, StartY);
		StartY = this->DrawButton("Power", eMINIMENU_BT3, StartX, StartY);
	}

	//if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
	if(g_ExLicense.user.AccSecurity)
	{
		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
		{
		}
		else
		{
			StartY = this->DrawButton("Account Security", eMINIMENU_BT18, StartX, StartY);
		}
	}

	if(g_ExLicense.user.PremiumEx)
	{
		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::MedoniAndrei))
		{
		}
		/*else if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
		{
			StartY = this->DrawButton("Custom", eMINIMENU_BT17, StartX, StartY);
		}*/
		else
		{
			StartY = this->DrawButton("Premium System", eMINIMENU_BT19, StartX, StartY);
		}
	}

	//if(g_ExLicense.m_ExMenuV2)
	//{
		StartY = this->DrawButton("Options", eMINIMENU_BT4, StartX, StartY);

		StartY = this->DrawButton("3D Camera [Reset]", eMINIMENU_BT5, StartX, StartY);

		StartY = this->DrawButton("Jewels Bank", eMINIMENU_BT6, StartX, StartY);

		if(gRAGESYSTEM)
		{
			StartY = this->DrawButton("Rage System", eMINIMENU_BT7, StartX, StartY);
		}

		//if(gWINQUEST)
		//{
		//	StartY = this->DrawButton("Quest", eMINIMENU_BT8, StartX, StartY);
		//	StartY = this->DrawButton("Quest Options", eMINIMENU_BT9, StartX, StartY);
		//}

		StartY = this->DrawButton("Offline Attack", eMINIMENU_BT10, StartX, StartY);

		if(gRanking.Active)
		{
			StartY = this->DrawButton("Top 100 Player", eMINIMENU_BT11, StartX, StartY);
		}

		if(gEventTimer.Active)
		{
			StartY = this->DrawButton("Events Timer", eMINIMENU_BT12, StartX, StartY);
		}

		#if(CUSTOM_PARTY_SEARCH==TRUE)
		if(g_PartySearch.Active)
		{
			StartY = this->DrawButton("Auto Party", eMINIMENU_BT13, StartX, StartY);
		}
		#endif

		if(g_PartySearch.Active)
		{
			StartY = this->DrawButton("Party Search List", eMINIMENU_BT14, StartX, StartY);
		}
		else
		{
			if(gAutoParty.Active)
			{
				StartY = this->DrawButton("Auto Party List", eMINIMENU_BT15, StartX, StartY);
			}
		}

		if(g_ExLicense.user.Smithy == true)
		{
			StartY = this->DrawButton("Smithy", eMINIMENU_BT16, StartX, StartY);
		}

		//if(g_ExLicense.CheckUser(eExUB::Local) || 
		//	g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
		//	THINNAKORN_MAC == 1 ||
		//	g_ExLicense.CheckUser(eExUB::MedoniAndrei) /*||
		//	g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2)*/)
		{
//#if(CUSTOM_REFERAL_SYSTEM)
			//StartY = this->DrawButton("Referral System", eMINIMENU_BT17, StartX, StartY);
//#else
			StartY = this->DrawButton("Custom", eMINIMENU_BT17, StartX, StartY);
//#endif
		}
	//}

	// =====================================================================

	gInterface.DrawGUI(eMINIMENU_FOOTER, StartX, StartY-20);
}
// ----------------------------------------------------------------------------------------------

void MiniMenu::Botton(DWORD Event)
{
	#if(DEV_EXMENU_V3)
	if(g_ExMenuV3.m_Enable)
	{
		return;
	}
	#endif
	
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMiniMenu))
	{
		return;
	}

	//if(g_ExLicense.CheckUser(eExUB::GloryMU))
	//{
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT20,  false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			ShellExecute(NULL, "open", "http://glorymu.org/cabinet/pay", NULL, NULL, SW_MAXIMIZE);		
		}

		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT21,  false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			#if(DONATE_SHOP==TRUE)
			if(!gInterface.CheckWindow(Shop))
			{
				g_DonateShop.CG_CashSend();
			}
			#endif
		}
	//}

#if(ENABLE_DONATE_BUTTON==TRUE)
	if( gInterface.ButtonEx(Event, eMINIMENU_BT1, false ) )
	{
		lpViewObj lpViewPlayer = &*(ObjectPreview*)oUserPreviewStruct;

		if(lpViewPlayer->InSafeZone)
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			gInterface.m_bCashShopOpen = true;
		}
		return;
	}
#endif

#if(SYSTEM_ACHIEVEMENTS)
	if(gInterface.ButtonEx(Event, eMINIMENU_BT2, false))
	{
		g_Achievements.CGWindowOpen();
		gInterface.CloseWindowEx(exWinMiniMenu);
	}

	if(gInterface.ButtonEx(Event, eMINIMENU_BT3, false))
	{
		gInterface.CloseWindowEx(exWinMiniMenu);	

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

	//if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
	if(g_ExLicense.user.AccSecurity)
	{
		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
		{
		}
		else
		{
			if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT18, false))
			{
				gInterface.CloseWindowEx(exWinMiniMenu);
				gInterface.OpenWindowEx(ObjWindowsEx::exWinAccWarning);
			}
		}
	}

	if(g_ExLicense.user.PremiumEx)
	{
		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::MedoniAndrei))
		{
		}
		else
		{
			if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT19, false))
			{
				gInterface.CloseWindowEx(exWinMiniMenu);
				gInterface.OpenWindowEx(ObjWindowsEx::exWinPremium);
			}
		}
	}

	if( gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT4, false ) )
	{
		gInterface.CloseWindowEx(exWinMiniMenu);
		gInterface.OpenWindowEx(exWinSettings);
	}

	if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT5, false))
	{
		gInterface.CloseWindowEx(exWinMiniMenu);
		gCamera.Init();
	}

	if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT6, false))
	{
		gInterface.CloseWindowEx(exWinMiniMenu);
		gJewelsBank.Active = !gJewelsBank.Active;
	}

	if(gRAGESYSTEM)
	{
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT7, false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			gInterface.Data[eRageTable].OnShow = !gInterface.Data[eRageTable].OnShow;
		}
	}

	if(gWINQUEST)
	{
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT8, false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			gQuestSystem.Switcher(0);
		}
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT9, false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			gQuestSystem.Switcher(1);
		}
	}

	if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT10, false))
	{
		gInterface.CloseWindowEx(exWinMiniMenu);

		if(g_ExLicense.user.OfflineMode)
		{
			if(gInterface.CheckWindowEx(exWinCheckOffAfk))
			{
				gInterface.CloseWindowEx(exWinCheckOffAfk);
			}
			else
			{
				gInterface.OpenWindowEx(exWinCheckOffAfk);
			}
		}
		else
		{
			gDataSend.SendOfflineAttack();
		}
	}
	if(gRanking.Active)
	{
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT11, false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			gRanking.Show = !gRanking.Show;
		}
	}

	if(gEventTimer.Active)
	{
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT12, false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			gEventTimer.Show = !gEventTimer.Show;
		}
	}

	#if(CUSTOM_PARTY_SEARCH==TRUE)
	if(g_PartySearch.Active)
	{
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT13, false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
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
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT14, false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
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
			if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT15,  false))
			{
				gInterface.CloseWindowEx(exWinMiniMenu);
				gDataSend.SendOpenAutoPartyList();
			}
		}
	}

	if(g_ExLicense.user.Smithy == true)
	{
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT16,  false))
		{
			gInterface.CloseWindowEx(exWinMiniMenu);
			if(!gInterface.CheckWindowEx(exWinSmithy))
			{
				gInterface.OpenWindowEx(exWinSmithy);
			}
		}
	}

	//if(g_ExLicense.CheckUser(eExUB::Local) || 
	//	g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
	//	THINNAKORN_MAC == 1 ||
	//	g_ExLicense.CheckUser(eExUB::MedoniAndrei) /*|| 
	//	g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2)*/)
	{
		if(gInterface.Button(Event, exWinMiniMenu, eMINIMENU_BT17,  false))
		{
#if(CUSTOM_REFERAL_SYSTEM)
			gInterface.CloseWindowEx(exWinMiniMenu);
			if(!gInterface.CheckWindowEx(exWinReferralSystem))
			{
				g_ReferralSystem.CGReqMasterInfo();
				g_ReferralSystem.CGReqUserInfo();

				gInterface.OpenWindowEx(exWinReferralMenu);
			}
#else
			gInterface.CloseWindowEx(exWinMiniMenu);
			if(!gInterface.CheckWindowEx(exWinCustomMenu))
			{
				gInterface.OpenWindowEx(exWinCustomMenu);
			}
			else
			{
				gInterface.CloseWindowEx(exWinCustomMenu);
			}
#endif
		}
	}
}
// ----------------------------------------------------------------------------------------------

void MiniMenu::GC_RecvMMOTOP(GC_MMOTOPURL* pData)
{
	if(pData->Result == 1)
	{
		memcpy(this->UrlMootop, pData->mmotopurl, 64);
	}
}
// ----------------------------------------------------------------------------------------------

void MiniMenu::GC_RecvQTOP(PMSG_GC_QTOPURL* pData)
{
	if(pData->Result == 1)
	{
		memcpy(this->szUrlQtop, pData->szUrl, 64);
	}
}
// ----------------------------------------------------------------------------------------------

int MiniMenu::GetCountButton()
{
	int iCount = 0;

	if(g_ExLicense.CheckUser(eExUB::GloryMU))
	{
		iCount++;

		iCount++;
	}
	//Cash Shop
	iCount++;

	//***AchLicense***//
	if(g_ExLicense.m_Achievements)
	{
		//Achievements
		iCount++;
		//Power
		iCount++;
	}

	//if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
	//{
	//	iCount++;
	//	iCount++;
	//}
	if(g_ExLicense.user.AccSecurity)
	{
		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
		{
		}
		else
		{
			iCount++;
		}
	}

	if(g_ExLicense.user.PremiumEx)
	{
		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::MedoniAndrei))
		{
		}
		else
		{
			iCount++;
		}
	}

	if(g_ExLicense.m_ExMenuV2)
	{
		//Option
		iCount++;

		//3d Camera Restart
		//-----------------
		iCount++;
		//3d Camera Switch
		//-----------------
		//iCount++;
		//Jewels Bank
		//-----------------
		iCount++;
		//Glow Effect Grafics
		//-----------------
		//iCount++;
		//Party HP Bar
		//-----------------
		//iCount++;
		//User HP Bar
		//-----------------
		//iCount++;
		//Monster HP Bar
		//-----------------
		//iCount++;
		//Rage System
		//-----------------
		if(gRAGESYSTEM)
		{
			iCount++;
		}
		//Quest
		//-----------------
		if(gWINQUEST)
		{
			iCount++;
			//Quest Options System
			//-----------------
			iCount++;
		}
		//OffAfk
		//-----------------
		iCount++;
		//Top 100 List
		//-----------------
		if(gRanking.Active)
		{
			iCount++;
		}
		//Events
		//-----------------
		if(gEventTimer.Active)
		{
			iCount++;
		}
		//PT Menu
		//-----------------
	#if _NEW_PARTY_SYSTEM_ == TRUE
		if(gPARTY_SYSTEM)
		{
			if(g_Party.PartyMemberCount > 0)
			{
				//iCount++;
			}
		}
	#endif
		//Party Search
		//-----------------
	#if(CUSTOM_PARTY_SEARCH==TRUE)
		if(g_PartySearch.Active)
		{
			iCount++;
		}
	#endif
		//Auto Party List
		//-----------------
	#if(CUSTOM_PARTY_SEARCH==TRUE)
		if(g_PartySearch.Active)
		{
			iCount++;
		}
		else
	#endif
		{
			if(gAutoParty.Active)
			{
				iCount++;
			}
		}

		if(g_ExLicense.user.Smithy == true)
		{
			iCount++;
		}

	if(g_ExLicense.CheckUser(eExUB::Local) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
		THINNAKORN_MAC == 1 ||
		g_ExLicense.CheckUser(eExUB::MedoniAndrei)/* ||
		g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2)*/)
		{
			iCount++;
		}
	}

	return iCount;
}
// ----------------------------------------------------------------------------------------------

float MiniMenu::DrawButton(char* Name, int ButtonID, float X, float Y)
{
	pDrawGUI(gInterface.Data[eMINIMENU_FRAME].ModelID, X, Y, gInterface.Data[eMINIMENU_FRAME].Width, 10);
	pDrawGUI(gInterface.Data[eMINIMENU_FRAME].ModelID, X, Y+10, gInterface.Data[eMINIMENU_FRAME].Width, 10);

	Y += 20;
	gInterface.DrawGUIText(ButtonID, X+17, Y-2, Name);
	if( gInterface.IsWorkZone(ButtonID) )
	{
		gInterface.DrawGUI(eMINIMENU_ARROW_L, gInterface.Data[ButtonID].X , gInterface.Data[ButtonID].Y );
		gInterface.DrawGUI(eMINIMENU_ARROW_R, gInterface.Data[ButtonID].MaxX-6, gInterface.Data[ButtonID].Y );
	}
	gInterface.DrawGUI(eMINIMENU_LINE, X + 17, Y + 10);

	return Y;
}
#endif