#include "stdafx.h"
#include "ReferralSystem.h"
#include "Interface.h"
#include "Protocol.h"
#include "User.h"
#include "ExLicense.h"

#if(CUSTOM_REFERAL_SYSTEM)

CReferralSystem g_ReferralSystem;

CReferralSystem::CReferralSystem()
{
	this->m_iDraw = 0;
	this->m_iPage = 0;
	this->m_iOpen = 0;
	this->m_iMaxStage = 0;
	memset(this->m_Data, 0, sizeof(this->m_Data));
}

CReferralSystem::~CReferralSystem()
{
}

void CReferralSystem::Load()
{

}

void CReferralSystem::BindImages()
{
	//gInterface.BindObject(eREFERRAL_ICON, ex_ICON_REFFERAL, 16, 11.4, -1, -1);
	//gInterface.BindObject(eREFERRAL_BORDER, ex_BORDER_REFFERAL, 19, 15, -1, -1);

	gInterface.BindObject(eREFERRAL_MENU_MAIN, 0x7A5A, 222, 170, -1, -1);
	gInterface.BindObject(eREFERRAL_MENU_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eREFERRAL_MENU_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eREFERRAL_MENU_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eREFERRAL_MENU_DIV1, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_MENU_CLOSE, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eREFERRAL_MENU_REWARD, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eREFERRAL_MENU_REFERRAL, 0x7A5E, 108, 29, -1, -1);

	gInterface.BindObject(eREFERRAL_MAIN, 0x7A5A, 222, 450, -1, -1);
	gInterface.BindObject(eREFERRAL_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eREFERRAL_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eREFERRAL_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eREFERRAL_DIV1, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_CLOSE, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eREFERRAL_L, 0x7BAA, 17, 17, -1, -1);
	gInterface.BindObject(eREFERRAL_R, 0x7BAB, 17, 17, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP2, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP3, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP4, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP5, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP6, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP7, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP8, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP9, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_PAGEUP10, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL_BT1, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT2, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT3, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT4, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT5, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT6, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT7, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT8, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT9, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_BT10, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eREFERRAL_LINE2, 0x7B67, 154, 3, -1, -1);

	gInterface.BindObject(eREFERRAL2_MAIN, 0x7A5A, 222, 200, -1, -1);
	gInterface.BindObject(eREFERRAL2_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eREFERRAL2_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eREFERRAL2_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eREFERRAL2_DIV1, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eREFERRAL2_CLOSE, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eREFERRAL2_PAGEUP1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eREFERRAL2_BT1, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eREFERRAL2_LINE1, 0x7B67, 154, 3, -1, -1);
}

void CReferralSystem::LoadFileImage()
{
	pLoadImage("Custom\\Interface\\referral.jpg", ex_ICON_REFFERAL, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\rama.tga", ex_BORDER_REFFERAL, GL_LINEAR, GL_CLAMP, 1, 0);
}

void CReferralSystem::DrawMain()
{
	if(!g_ExLicense.user.ReferralSystem)
	{
		return;
	}

	if(pPlayerState != GameProcess)
	{
		return;
	}

	if( gInterface.CheckWindow(ObjWindow::CashShop) ||
		gInterface.CheckWindow(ObjWindow::FullMap)  || 
		gInterface.CheckWindow(ObjWindow::SkillTree)|| 
		gInterface.CheckWindow(ObjWindow::MoveList) )
	{
		this->m_iDraw = 0;
		return;
	}

	this->DrawIco();
	this->DrawMenu();
	this->Draw();
	this->Draw2();

	this->m_iDraw = 1;
}

void CReferralSystem::DrawIco()
{
	float flIcoX = 0;
	float flIcoY = 18;

	//right icon
	//flIcoX = 620;
	//flIcoY = 20;

	flIcoX = 0;
	flIcoY = 85;

	gInterface.DrawGUI(eREFERRAL_BORDER, flIcoX, flIcoY);

	flIcoX += 2;
	flIcoY += 2;
	gInterface.DrawGUI(eREFERRAL_ICON, flIcoX, flIcoY);

	if(gInterface.IsWorkZone(eREFERRAL_ICON))
	{
		pSetCursorFocus = true;

		DWORD Color = eGray100;

		if(gInterface.Data[eREFERRAL_ICON].OnClick)
		{
			Color = eGray150;
		}

		//gInterface.DrawColoredGUI(eREFERRAL_ICON, gInterface.Data[eREFERRAL_ICON].X, gInterface.Data[eREFERRAL_ICON].Y, Color);
		gInterface.DrawColoredGUIObj(eREFERRAL_ICON, gInterface.Data[eREFERRAL_ICON].X, gInterface.Data[eREFERRAL_ICON].Y, Color);

		gInterface.DrawToolTip(gInterface.Data[eREFERRAL_ICON].X + 25, gInterface.Data[eREFERRAL_ICON].Y + 2, "Referral System");
	}
}

void CReferralSystem::DrawMenu()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinReferralMenu))
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth = 230.0;
	float StartY = 250;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentX = StartX;
	float ContentY = StartY + 20;

	gInterface.DrawWindow(eREFERRAL_MENU_MAIN, eREFERRAL_MENU_TITLE, eREFERRAL_MENU_FRAME, eREFERRAL_MENU_FOOTER, 4, StartX, StartY, "Referral Menu");

	ContentY += 15;
	gInterface.DrawButtonBig(eREFERRAL_MENU_REWARD, true, ContentX + 60, ContentY + 5, "My Reward");

	ContentY += 35;
	gInterface.DrawButtonBig(eREFERRAL_MENU_REFERRAL, true, ContentX + 60, ContentY + 5, "My Referrals");

	ContentY += 35;
	gInterface.DrawGUI(eREFERRAL_MENU_DIV1, ContentX, ContentY);

	ContentY += 15;
	gInterface.DrawButtonBig(eREFERRAL_MENU_CLOSE, true, ContentX + 60, ContentY + 5, "Close");

}

void CReferralSystem::Draw()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinReferralSystem))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color				= eGray100;
	float MainWidth			= 230.0;
	float MainHeight		= 350.0;
	float StartY			= 0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentX          = StartX;
	float ContentY			= StartY;

	gInterface.DrawWindow(eREFERRAL_MAIN, eREFERRAL_TITLE, eREFERRAL_FRAME, eREFERRAL_FOOTER, 21, StartX, StartY, "Referral System");

	float ListDrawX = ContentX + 35;
	float ListDrawY = ContentY + 30;

	for(int i = 0; i < this->m_iReferralCount; i++)
	{
		REFERRAL_DATA * pData = &this->m_Data[i];

		if(pData->Name[0] == NULL) 
		{
			continue;
		}

		gInterface.DrawGUI(eREFERRAL_PAGEUP1 + i, ListDrawX - 5, ListDrawY);
		gInterface.DrawFormat(eYellow, ListDrawX - 20, ListDrawY + 5, 100, 3, pData->Name);

		if(pData->UserOnline)
		{
			gInterface.DrawFormat(eExcellent, ListDrawX + 65, ListDrawY + 5, 100, 3, "Online");
		}
		else
		{
			gInterface.DrawFormat(eRed, ListDrawX + 65, ListDrawY + 5, 100, 3, "Offline");
		}

		ListDrawY += 23;

		if(this->m_iOpen == i)
		{
			if(pData->RefferalMaster < this->m_iMaxStage)
			{
				gInterface.DrawGUI(eREFERRAL_LINE1, ListDrawX + 2,  ListDrawY + 10);

				int iOlxY = ListDrawY;

				//if(pData->ReferralNeedLevel > 0 || pData->ReferralNeedReset > 0 || pData->ReferralNeedGrand > 0)
				{
					gInterface.DrawFormat(eWhite, ListDrawX + 20, ListDrawY, 100, 1, "- Need");
					ListDrawY += 5;
				}

				bool bNeedResult = true;

				//if(pData->ReferralNeedLevel > 0)
				{
					ListDrawY += 10;
					Color = eAncient;
					if(pData->UserLevel < pData->ReferralNeedLevel)
					{
						bNeedResult = false;
						Color = eRed;
					}
					gInterface.DrawFormat(Color, ListDrawX + 10, ListDrawY, 100, 1, "- Level: %d / %d", pData->UserLevel, pData->ReferralNeedLevel);
				}

				//if(pData->ReferralNeedReset > 0)
				{
					ListDrawY += 10;
					Color = eAncient;
					if(pData->UserReset < pData->ReferralNeedReset)
					{
						bNeedResult = false;
						Color = eRed;
					}
					gInterface.DrawFormat(Color, ListDrawX + 10, ListDrawY, 100, 1, "- Reset: %d / %d", pData->UserReset, pData->ReferralNeedReset);
				}

				//if(pData->ReferralNeedGrand > 0)
				{
					ListDrawY += 10;
					Color = eAncient;
					if(pData->UserGrand < pData->ReferralNeedGrand)
					{
						bNeedResult = false;
						Color = eRed;
					}
					gInterface.DrawFormat(Color, ListDrawX + 10, ListDrawY, 100, 1, "- Grand: %d / %d", pData->UserGrand, pData->ReferralNeedGrand);
				}

				int iNeedY = ListDrawY;
				ListDrawY = iOlxY;
				gInterface.DrawFormat(eWhite, ListDrawX + 95, ListDrawY, 100, 1, "- Reward");
				ListDrawY += 5;

				if(pData->MasterRewardCredit > 0)
				{
					ListDrawY += 10;
					gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Credits: %d", pData->MasterRewardCredit);
				}

				if(pData->MasterRewardWCoinC > 0)
				{
					ListDrawY += 10;
					gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Wcoin(C): %d", pData->MasterRewardWCoinC);
				}

				if(pData->MasterRewardWCoinP > 0)
				{
					ListDrawY += 10;
					gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Wcoin(P): %d", pData->MasterRewardWCoinP);
				}

				if(pData->MasterRewardWCoinG > 0)
				{
					ListDrawY += 10;
					gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Goblin Point: %d", pData->MasterRewardWCoinG);
				}

				if(pData->MasterRewardPremiumType == 1)
				{
					ListDrawY += 10;
					gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Silver Premium: %dh", pData->MasterRewardPremiumTime);
				}
				if(pData->MasterRewardPremiumType == 2)
				{
					ListDrawY += 10;
					gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Bronze Premium: %dh", pData->MasterRewardPremiumTime);
				}
				if(pData->MasterRewardPremiumType == 3)
				{
					ListDrawY += 10;
					gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Gold Premium: %dh", pData->MasterRewardPremiumTime);
				}
			
				int iRewardY = ListDrawY;

				if(iNeedY > iRewardY)
				{
					ListDrawY = iNeedY;
				}
				else
				{
					ListDrawY = iRewardY;
				}
			
				ListDrawY += 10;
				gInterface.DrawGUI(eREFERRAL_LINE2, ListDrawX + 2, ListDrawY);

				ListDrawY += 5;
				gInterface.DrawFormat(eSocket, ListDrawX - 16, ListDrawY + 7, 100, 3, "Stage: %d / %d", pData->RefferalMaster, this->m_iMaxStage);
				gInterface.DrawButtonMini(eREFERRAL_BT1 + i, ListDrawX + 95, ListDrawY, bNeedResult, "Reward");
				ListDrawY += 30;
			}
			else
			{
				gInterface.DrawGUI(eREFERRAL_LINE1, ListDrawX + 2,  ListDrawY + 10);

				int iOlxY = ListDrawY;

				gInterface.DrawFormat(eYellow, ListDrawX + 20 + 50, ListDrawY, 100, 1, "- Finish");
				ListDrawY += 5;
			}

		}

		if(gInterface.IsWorkZone(eREFERRAL_PAGEUP1 + i) || this->m_iOpen == i)
		{
			Color = eGray100;

			if(gInterface.Data[eREFERRAL_PAGEUP1 + i].OnClick)
			{
				Color = eGray150;
			}

			gInterface.DrawColoredGUI(eREFERRAL_PAGEUP1 + i, gInterface.Data[eREFERRAL_PAGEUP1 + i].X, gInterface.Data[eREFERRAL_PAGEUP1 + i].Y, Color);
		}
	}

	gInterface.DrawPage(eREFERRAL_L, eREFERRAL_R, this->m_iPage, this->m_iReferralTotal / REFERRAL_MAXDATA + 1, ContentX, ContentY + 35);

	gInterface.DrawGUI(eREFERRAL_DIV1, ContentX, gInterface.Data[eREFERRAL_FOOTER].Y - 10);

	gInterface.DrawButtonBig(eREFERRAL_CLOSE, true, ContentX + 60, gInterface.Data[eREFERRAL_FOOTER].Y + 8, "Close");
}

void CReferralSystem::Draw2()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinReferralSystem2))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color				= eGray100;
	float MainWidth			= 230.0;
	float MainHeight		= 350.0;
	float StartY			= 220;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	float ContentX          = StartX;
	float ContentY			= StartY;

	gInterface.DrawWindow(eREFERRAL2_MAIN, eREFERRAL2_TITLE, eREFERRAL2_FRAME, eREFERRAL2_FOOTER, 6, StartX, StartY, "Referral System");

	float ListDrawX = ContentX + 35;
	float ListDrawY = ContentY + 30;

	REFERRAL_USER * pUser = &this->m_User;

	//if(pUser->RefferalActive) 
	if(pUser->RefferalUser < this->m_iMaxStage)
	{
		lpCharObj lpPlayer = pUserObjectStruct;

		gInterface.DrawGUI(eREFERRAL2_PAGEUP1, ListDrawX - 5, ListDrawY);
		gInterface.DrawFormat(eYellow, ListDrawX - 20, ListDrawY + 5, 100, 3, lpPlayer->Name);
		gInterface.DrawFormat(eExcellent, ListDrawX + 65, ListDrawY + 5, 100, 3, "Message");

		ListDrawY += 25;
		gInterface.DrawGUI(eREFERRAL2_LINE1, ListDrawX + 2,  ListDrawY + 10);

		int iOlxY = ListDrawY;

		//if(pData->ReferralNeedLevel > 0 || pData->ReferralNeedReset > 0 || pData->ReferralNeedGrand > 0)
		{
			gInterface.DrawFormat(eWhite, ListDrawX + 20, ListDrawY, 100, 1, "- Need");
			ListDrawY += 5;
		}

		bool bNeedResult = true;

		//if(pUser->ReferralNeedLevel > 0)
		{
			ListDrawY += 10;
			Color = eAncient;

			if(lpPlayer->Level < pUser->ReferralNeedLevel)
			{
				bNeedResult = false;
				Color = eRed;
			}
			gInterface.DrawFormat(Color, ListDrawX + 10, ListDrawY, 100, 1, "- Level: %d / %d", lpPlayer->Level, pUser->ReferralNeedLevel);
		}

		//if(pUser->ReferralNeedReset > 0)
		{
			ListDrawY += 10;
			Color = eAncient;
			if(gObjUser.Reset < pUser->ReferralNeedReset)
			{
				bNeedResult = false;
				Color = eRed;
			}
			gInterface.DrawFormat(Color, ListDrawX + 10, ListDrawY, 100, 1, "- Reset: %d / %d", gObjUser.Reset, pUser->ReferralNeedReset);
		}

		//if(pUser->ReferralNeedGrand > 0)
		{
			ListDrawY += 10;
			Color = eAncient;
			if(gObjUser.GReset < pUser->ReferralNeedGrand)
			{
				bNeedResult = false;
				Color = eRed;
			}
			gInterface.DrawFormat(Color, ListDrawX + 10, ListDrawY, 100, 1, "- Grand: %d / %d", gObjUser.GReset, pUser->ReferralNeedGrand);
		}

		int iNeedY = ListDrawY;
		ListDrawY = iOlxY;
		gInterface.DrawFormat(eWhite, ListDrawX + 95, ListDrawY, 100, 1, "- Reward");
		ListDrawY += 5;


		if(pUser->ReferralRewardCredit > 0)
		{
			ListDrawY += 10;
			gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Credits: %d", pUser->ReferralRewardCredit);
		}

		if(pUser->ReferralRewardWCoinC > 0)
		{
			ListDrawY += 10;
			gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Wcoin(C): %d", pUser->ReferralRewardWCoinC);
		}

		if(pUser->ReferralRewardWCoinP > 0)
		{
			ListDrawY += 10;
			gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Wcoin(P): %d", pUser->ReferralRewardWCoinP);
		}

		if(pUser->ReferralRewardWcoinG > 0)
		{
			ListDrawY += 10;
			gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Goblin Point: %d", pUser->ReferralRewardWCoinP);
		}

		if(pUser->ReferralRewardPremiumType == 1)
		{
			ListDrawY += 10;
			gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Silver Premium: %dh", pUser->ReferralRewardPremiumTime);
		}
		else if(pUser->ReferralRewardPremiumType == 2)
		{
			ListDrawY += 10;
			gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Bronze Premium: %dh", pUser->ReferralRewardPremiumTime);
		}
		else if(pUser->ReferralRewardPremiumType == 3)
		{
			ListDrawY += 10;
			gInterface.DrawFormat(eExcellent, ListDrawX + 85, ListDrawY, 100, 1, "- Gold Premium: %dh", pUser->ReferralRewardPremiumTime);
		}
			
		int iRewardY = ListDrawY;

		if(iNeedY > iRewardY)
		{
			ListDrawY = iNeedY;
		}
		else
		{
			ListDrawY = iRewardY;
		}
			
		ListDrawY += 10;
		gInterface.DrawGUI(eREFERRAL2_LINE1, ListDrawX + 2, ListDrawY);

		ListDrawY += 5;
		//gInterface.DrawFormat(eSocket, ListDrawX - 16, ListDrawY + 7, 100, 3, "Stage: %d / %d", pUser->RefferalUser + 1, this->m_iMaxStage / REFERRAL_MAXDATA + 1);
		gInterface.DrawFormat(eSocket, ListDrawX - 16, ListDrawY + 7, 100, 3, "Stage: %d / %d", pUser->RefferalUser, this->m_iMaxStage);
		gInterface.DrawButtonMini(eREFERRAL2_BT1, ListDrawX + 95, ListDrawY, bNeedResult, "Reward");
		ListDrawY += 30;
	}
	else
	{
		lpCharObj lpPlayer = pUserObjectStruct;

		gInterface.DrawGUI(eREFERRAL2_PAGEUP1, ListDrawX - 5, ListDrawY);
		gInterface.DrawFormat(eYellow, ListDrawX - 20, ListDrawY + 5, 100, 3, lpPlayer->Name);
		gInterface.DrawFormat(eExcellent, ListDrawX + 65, ListDrawY + 5, 100, 3, "Finish");
	}

	gInterface.DrawGUI(eREFERRAL2_DIV1, ContentX, gInterface.Data[eREFERRAL2_FOOTER].Y - 10);

	gInterface.DrawButtonBig(eREFERRAL2_CLOSE, true, ContentX + 60, gInterface.Data[eREFERRAL2_FOOTER].Y + 8, "Close");
}

void CReferralSystem::ButtonIco(DWORD Event)
{
	if(!g_ExLicense.user.ReferralSystem || pPlayerState != GameProcess)
	{
		return;
	}





}

void CReferralSystem::Button(DWORD Event)
{
	if(!g_ExLicense.user.ReferralSystem)
	{
		return;
	}

	if( pPlayerState != GameProcess )
	{
		return;
	}

	if(!this->m_iDraw)
	{
		return;
	}

	if(gInterface.ButtonEx(Event, eREFERRAL_ICON, false))
	{
		if(gInterface.CheckWindowEx(ObjWindowsEx::exWinReferralMenu))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinReferralMenu);
		}
		else
		{
			gInterface.OpenWindowEx(ObjWindowsEx::exWinReferralMenu);
		}

		return;
	}

	if(gInterface.CheckWindowEx(ObjWindowsEx::exWinReferralMenu))
	{
		if(gInterface.ButtonEx(Event, eREFERRAL_MENU_CLOSE, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinReferralMenu);

			return;
		}

		if(gInterface.ButtonEx(Event, eREFERRAL_MENU_REWARD, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinReferralMenu);
			g_ReferralSystem.CGReqUserInfo();
			
			return;
		}

		if(gInterface.ButtonEx(Event, eREFERRAL_MENU_REFERRAL, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinReferralMenu);
			this->m_iPage = 0;
			g_ReferralSystem.CGReqMasterInfo();

			return;
		}
	}
	else if(gInterface.CheckWindowEx(ObjWindowsEx::exWinReferralSystem))
	{
		if(gInterface.ButtonEx(Event, eREFERRAL_CLOSE, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinReferralSystem);
		}

		if(this->m_iPage > 0)
		{
			if(gInterface.ButtonEx(Event, eREFERRAL_L, false))
			{
				this->m_iOpen = 0;
				this->m_iPage--;
				this->CGReqMasterInfo();
			}
		}
		
		if(this->m_iReferralCount >= REFERRAL_MAXDATA)
		{
			if(gInterface.ButtonEx(Event, eREFERRAL_R, false))
			{
				this->m_iOpen = 0;
				this->m_iPage++;
				this->CGReqMasterInfo();
			}
		}

		for(int i = 0; i < REFERRAL_MAXDATA; i++)
		{
			if(gInterface.ButtonEx(Event, eREFERRAL_PAGEUP1 + i, false))
			{
				this->m_iOpen = i;
				break;
			}

			if(gInterface.ButtonEx(Event, eREFERRAL_BT1 + i, true))
			{
				this->CGReqMasterResult(i);
				break;
			}
		}
	}
	else if(gInterface.CheckWindowEx(ObjWindowsEx::exWinReferralSystem2))
	{
		if(gInterface.ButtonEx(Event, eREFERRAL2_CLOSE, false))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinReferralSystem2);
		}

		if(gInterface.ButtonEx(Event, eREFERRAL2_BT1, true))
		{
			this->CGReqUserResult();
		}
	}
}

void CReferralSystem::CGReqMasterInfo()
{
	PMSG_REQ_REFERRAL_MASTER_INFO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB5, sizeof(pMsg));
	pMsg.PageNumber = this->m_iPage;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CReferralSystem::GCAnsMasterInfo(PMSG_ANS_REFERRAL_MASTER_INFO* lpMsg)
{
	memset(this->m_Data, 0, sizeof(this->m_Data));

	this->m_iMaxStage = lpMsg->RefferalMaxStage;
	this->m_iReferralCount = lpMsg->ReferralCount;
	this->m_iReferralTotal = lpMsg->ReferralTotal;

	for(int i = 0; i < this->m_iReferralCount; i++)
	{
		memcpy(this->m_Data[i].Name, lpMsg->Data[i].RefferalName, sizeof(lpMsg->Data[i].RefferalName));
		this->m_Data[i].UserOnline = lpMsg->Data[i].UserOnline;
		this->m_Data[i].RefferalMaster = lpMsg->Data[i].RefferalMaster;
		this->m_Data[i].UserLevel = lpMsg->Data[i].UserLevel;
		this->m_Data[i].UserReset = lpMsg->Data[i].UserReset;
		this->m_Data[i].UserGrand = lpMsg->Data[i].UserGrand;
		this->m_Data[i].ReferralNeedLevel = lpMsg->Data[i].UserNeedLevel;
		this->m_Data[i].ReferralNeedReset = lpMsg->Data[i].UserNeedReset;
		this->m_Data[i].ReferralNeedGrand = lpMsg->Data[i].UserNeedGrand;
		this->m_Data[i].MasterRewardCredit = lpMsg->Data[i].MasterRewardCredit;
		this->m_Data[i].MasterRewardWCoinC = lpMsg->Data[i].MasterRewardWCoinC;
		this->m_Data[i].MasterRewardWCoinP = lpMsg->Data[i].MasterRewardWCoinP;
		this->m_Data[i].MasterRewardWCoinG = lpMsg->Data[i].MasterRewardWcoinG;
		this->m_Data[i].MasterRewardBonus = lpMsg->Data[i].MasterRewardBonus;
		this->m_Data[i].MasterRewardPremiumType = lpMsg->Data[i].MasterRewardPremiumType;
		this->m_Data[i].MasterRewardPremiumTime = lpMsg->Data[i].MasterRewardPremiumTime;
	}

	gInterface.OpenWindowEx(ObjWindowsEx::exWinReferralSystem);
}

void CReferralSystem::CGReqMasterResult(int Number)
{
	REFERRAL_DATA * pData = &this->m_Data[Number];

	PMSG_CGREQ_REFERRAL_MASTER_REWARD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB6, sizeof(pMsg));

	char szName[11] = { 0 };
	memcpy(szName, pData->Name, sizeof(pData->Name));
	szName[10] = 0;

	pMsg.ReferralNumber = Number;

	memcpy(pMsg.ReferalName, szName, sizeof(szName)-1);
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CReferralSystem::GCAnsMasterResult(PMSG_CGANS_REFERRAL_MASTER_REWARD* lpMsg)
{
	int iNumber = lpMsg->ReferralNumber;

	this->m_Data[iNumber].RefferalMaster++;
	this->m_Data[iNumber].UserOnline = lpMsg->UserNeedLevel;
	this->m_Data[iNumber].ReferralNeedLevel = lpMsg->UserNeedLevel;
	this->m_Data[iNumber].ReferralNeedReset = lpMsg->UserNeedReset;
	this->m_Data[iNumber].ReferralNeedGrand = lpMsg->UserNeedGrand;
	this->m_Data[iNumber].MasterRewardCredit = lpMsg->MasterRewardCredit;
	this->m_Data[iNumber].MasterRewardWCoinC = lpMsg->MasterRewardWCoinC;
	this->m_Data[iNumber].MasterRewardWCoinP = lpMsg->MasterRewardWCoinP;
	this->m_Data[iNumber].MasterRewardWCoinG = lpMsg->MasterRewardWcoinG;
	this->m_Data[iNumber].MasterRewardBonus = lpMsg->MasterRewardBonus;
	this->m_Data[iNumber].MasterRewardPremiumType = lpMsg->MasterRewardPremiumType;
	this->m_Data[iNumber].MasterRewardPremiumTime = lpMsg->MasterRewardPremiumTime;
}

void CReferralSystem::CGReqUserInfo()
{
	PMSG_REQ_REFERRAL_USER_INFO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB7, sizeof(pMsg));
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CReferralSystem::GCAnsUserInfo(PMSG_ANS_REFERRAL_USER_INFO* lpMsg)
{
	this->m_User.RefferalActive = 1;

	this->m_iMaxStage = lpMsg->RefferalMaxStage;

	this->m_User.RefferalUser = lpMsg->User.RefferalUser;
	this->m_User.ReferralNeedLevel = lpMsg->User.ReferralNeedLevel;
	this->m_User.ReferralNeedReset = lpMsg->User.ReferralNeedReset;
	this->m_User.ReferralNeedGrand = lpMsg->User.ReferralNeedGrand;
	this->m_User.ReferralRewardCredit = lpMsg->User.ReferralRewardCredit;
	this->m_User.ReferralRewardWCoinC = lpMsg->User.ReferralRewardWCoinC;
	this->m_User.ReferralRewardWCoinP = lpMsg->User.ReferralRewardWCoinP;
	this->m_User.ReferralRewardWcoinG = lpMsg->User.ReferralRewardWcoinG;
	this->m_User.ReferralRewardBonus = lpMsg->User.ReferralRewardBonus;
	this->m_User.ReferralRewardPremiumType = lpMsg->User.ReferralRewardPremiumType;
	this->m_User.ReferralRewardPremiumTime = lpMsg->User.ReferralRewardPremiumTime;

	gInterface.OpenWindowEx(ObjWindowsEx::exWinReferralSystem2);
}

void CReferralSystem::CGReqUserResult()
{
	PMSG_CGREQ_REFERRAL_USER_REWARD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xB8, sizeof(pMsg));
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CReferralSystem::GCAnsUserResult(PMSG_GCANS_REFERRAL_USER_REWARD* lpMsg)
{
	this->m_User.RefferalActive = 1;
	this->m_User.RefferalUser++;
	this->m_User.ReferralNeedLevel = lpMsg->UserNeedLevel;
	this->m_User.ReferralNeedReset = lpMsg->UserNeedReset;
	this->m_User.ReferralNeedGrand = lpMsg->UserNeedGrand;
	this->m_User.ReferralRewardCredit = lpMsg->UserRewardCredit;
	this->m_User.ReferralRewardWCoinC = lpMsg->UserRewardWCoinC;
	this->m_User.ReferralRewardWCoinP = lpMsg->UserRewardWCoinP;
	this->m_User.ReferralRewardWcoinG = lpMsg->UserRewardWcoinG;
	this->m_User.ReferralRewardBonus = lpMsg->UserRewardBonus;
	this->m_User.ReferralRewardPremiumType = lpMsg->UserRewardPremiumType;
	this->m_User.ReferralRewardPremiumTime = lpMsg->UserRewardPremiumTime;

	gInterface.OpenWindowEx(ObjWindowsEx::exWinReferralSystem2);
}

#endif