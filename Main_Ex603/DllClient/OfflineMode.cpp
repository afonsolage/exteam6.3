#include "stdafx.h"
#include "OfflineMode.h"
#include "Interface.h"
#include "Protocol.h"
#include "Console.h"
#include "User.h"
//#include "PremiumSystem.h"
//#include "Console.h"
#include "PremiumSystemEx.h"
#include "ExLicense.h"
// ----------------------------------------------------------------------------------------------

#if(OFFLINE_MODE==TRUE)

OfflineMode g_OfflineMode;
// ----------------------------------------------------------------------------------------------

OfflineMode::OfflineMode()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

OfflineMode::~OfflineMode()
{
	// ----
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Init()
{
	this->SendSkill = 0;
	this->ActiveSkill = 0;
	this->ActiveX = 0;
	this->ActiveY = 0;
	this->AutoBuff = 0;
	this->TempX = 0;
	this->TempY = 0;

	this->High	= 28.0;
	this->Whith = 20.0;

	this->standartWhith = this->Whith / 256;
	this->standartHight = this->High / 256;

#if(ADD_OFFMODE_PICKUP==TRUE)
	this->PickZen = false;
	this->PickJewel = false;
	this->PickExel = false;
	this->PickAnc = false;
#endif
	
	this->PriceZen = 0;
	this->PriceWcoin = 0;
	this->iHourCredit = 0;

	#if(ADD_OFFMODE_TIMER)
	this->m_PlayerTimeHour = 0;
	this->m_OtherPlayerMaxTime = 24;
	this->m_PremiumPlayerMaxTime = 72;
	#endif


}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Load()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::BindImages()
{
#if(ADD_OFFMODE_PICKUP==TRUE)
	#if(ADD_OFFMODE_TIMER)
	gInterface.BindObject(eCHECKWIN_MAIN, 0x7A5A, 222, 270, -1, -1);
	#else
	gInterface.BindObject(eCHECKWIN_MAIN, 0x7A5A, 222, 240, -1, -1);
	#endif
#else
	gInterface.BindObject(eCHECKWIN_MAIN, 0x7A5A, 222, 170, -1, -1);
#endif
	gInterface.BindObject(eCHECKWIN_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eCHECKWIN_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eCHECKWIN_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eCHECKWIN_DIV, 0x7A62, 223, 21, -1, -1);

	gInterface.BindObject(eCHECKWIN_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eCHECKWIN_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eCHECKWIN_POINT, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eCHECKWIN_CHECK, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eCHECKWIN_LINE, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eCHECKWIN_LINE2, 0x7B67, 154, 3, -1, -1);

#if(ADD_OFFMODE_PICKUP==TRUE)
	gInterface.BindObject(eOFFMODE_INFOLINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eOFFMODE_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eOFFMODE_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eOFFMODE_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eOFFMODE_POINT2, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eOFFMODE_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eOFFMODE_LINE2, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eOFFMODE_POINT3, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eOFFMODE_CHECK3, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eOFFMODE_LINE3, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eOFFMODE_POINT4, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eOFFMODE_CHECK4, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eOFFMODE_LINE4, 0x7B67, 154, 3, -1, -1);
#endif

	#if(ADD_OFFMODE_TIMER)
	gInterface.BindObject(eOFFMODE_POINT5, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eOFFMODE_PAGEUP, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eOFFMODE_PAGEDN, 0x7C0D, 15, 15, -1, -1);
	#endif
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Draw()
{
	if(!gInterface.CheckWindowEx(exWinCheckOffAfk))
	{
		this->SendSkill = 0;
		this->ActiveSkill = 0;
		return;
	}

	pSetCursorFocus = true;

	// ----
	float MainWidth			= 230.0;
	float MainHeight		= 110;
	float StartY			= 100;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	float ContentX			= StartX + 50;
	float ContentY			= StartY + 22 + 20 + 10;
	this->TempX				= 0;
	this->TempY				= 0;
	// ----
	gInterface.DrawGUI(eCHECKWIN_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eCHECKWIN_TITLE, StartX, StartY);
	#if(ADD_OFFMODE_TIMER)
	StartY = gInterface.DrawRepeatGUI(eCHECKWIN_FRAME, StartX, StartY + 67.0, 11);
	#else
	StartY = gInterface.DrawRepeatGUI(eCHECKWIN_FRAME, StartX, StartY + 67.0, 9);
	#endif
	gInterface.DrawGUI(eCHECKWIN_FOOTER, StartX, StartY);
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Offline Mode");
	// ---- 

	if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
	{
		if(g_PremiumSystemEx.m_iOfflineModeAttackFreePremiumRang > 0)
		{
			gInterface.DrawFormat(eYellow, StartX + 10, 110 + 50 - 25, 210, 3, "Attack free only %s premium players", 
				g_PremiumSystemEx.GetName(g_PremiumSystemEx.m_iOfflineModeAttackFreePremiumRang));
		}
		else
		{
			gInterface.DrawFormat(eYellow, StartX + 10, 110 + 50 - 25, 210, 3, "Leave your character in Offline mode?");
		}
	}
	else
	{
		gInterface.DrawFormat(eYellow, StartX + 10, 110 + 50 - 25, 210, 3, "Leave your character in Offline mode?");
	}
	
	// ---- 
	/*
	gInterface.DrawGUI(eCHECKWIN_LINE, StartX + 35, 110 + 50 - 25 + 10);
	gInterface.DrawFormat(eYellow, StartX + 10, 148, 210, 3, "Offline Trade in Safe Zone free" );
	//gInterface.DrawFormat(eYellow, StartX + 10, 158, 210, 3, "Offline Attack Pay in hour 1 bonus");
	gInterface.DrawFormat(eYellow, StartX + 10, 158, 210, 3, "1 bonus to start, subsequent payment of 500 000 Zen/Hour.");

	gInterface.DrawFormat(eYellow, StartX + 10, 168, 210, 3, "Gold Premium players free Offline Attack");
	*/
	gInterface.DrawGUI(eCHECKWIN_LINE, StartX + 35, 110 + 50 - 25 + 10);
	// ---- a
	// -> Skill Icon
	switch(gObjUser.Class)
	{
		case CLASS_KNIGHT:		this->Knight(ContentX, ContentY);		break;
		case CLASS_WIZARD:		this->Wizard(ContentX, ContentY);		break;
		case CLASS_ELF:			this->Elf(ContentX, ContentY);			break;
		case CLASS_SUMMONER:	this->Summoner(ContentX, ContentY);		break;
		case CLASS_MAGUMSA:		this->Magic(ContentX, ContentY);		break;
		case CLASS_DARKLORD:	this->Lord(ContentX, ContentY);			break;
		case CLASS_MONK:		this->Fighter(ContentX + 30, ContentY);	break;
	}
	// -> Auto Buff
	float lineX = ContentX - 15;
	float lineY = ContentY + 31;
	gInterface.DrawGUI(eCHECKWIN_LINE, lineX, lineY);
	// --
	ContentX -= 50;
	ContentY += 37;
	gInterface.DrawCheckLine(this->AutoBuff, eCHECKWIN_POINT, eCHECKWIN_CHECK, eCHECKWIN_LINE2, ContentX, ContentY, eWhite, "Auto Buff");
	// ----
#if(ADD_OFFMODE_PICKUP==TRUE)
	ContentX += 10;
	ContentY += 20;

	if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
	{
		if(g_PremiumSystemEx.m_iOfflineModePickUpPremiumRang > 0)
		{
			gInterface.DrawFormat(eYellow, ContentX, ContentY, 210, 3, "Pick up options only %s premium players", 
				g_PremiumSystemEx.GetName(g_PremiumSystemEx.m_iOfflineModePickUpPremiumRang));
		}
		else
		{
			gInterface.DrawFormat(eYellow, ContentX, ContentY, 210, 3, "Pick up options");
		}	
	}
	else
	{
		gInterface.DrawFormat(eYellow, ContentX, ContentY, 210, 3, "Pick up options only premium players");
	}

	ContentX += 25;
	ContentY += 10;
	gInterface.DrawGUI(eOFFMODE_INFOLINE1, ContentX, ContentY);

	ContentX -= 35;
	ContentY += 5;
	gInterface.DrawCheckLine(this->PickZen, eOFFMODE_POINT1, eOFFMODE_CHECK1, eOFFMODE_LINE1, ContentX, ContentY, eWhite, "Pick up Zen");

	ContentY += 20;
	gInterface.DrawCheckLine(this->PickJewel, eOFFMODE_POINT2, eOFFMODE_CHECK2, eOFFMODE_LINE2, ContentX, ContentY, eWhite, "Pick up Jewels");

	ContentY += 20;
	gInterface.DrawCheckLine(this->PickExel, eOFFMODE_POINT3, eOFFMODE_CHECK3, eOFFMODE_LINE3, ContentX, ContentY, eWhite, "Pick up Exellent Items");

	ContentY += 20;
	gInterface.DrawCheckLine(this->PickAnc, eOFFMODE_POINT4, eOFFMODE_CHECK4, eOFFMODE_LINE4, ContentX, ContentY, eWhite, "Pick up Ancent Items");

	#if(ADD_OFFMODE_TIMER)
	//if(g_ExLicense.CheckUser(eExUB::eternalmu))
	//{
		ContentY += 20;
		gInterface.PartUPandDN(eOFFMODE_POINT5, eOFFMODE_PAGEUP, eOFFMODE_PAGEDN, NULL, ContentX, ContentY, eWhite, (gObjUser.IsVIP() ? this->m_PremiumPlayerMaxTime : this->m_PlayerTimeHour), "Offline Mode Timer");
	//}
	#endif

#endif
	// ----
	gInterface.DrawGUI(eCHECKWIN_OK, StartX+30, StartY /*- 5*/);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5 + 5, 50, 3, "Start");
	// ----
	gConsole.Output(cGREEN, "gObjUser.Money: %d", gObjUser.Money);
	if(gObjUser.InSafeZone())
	{
		//gConsole.Output(cGREEN, "InSafeZone");
		gInterface.Data[eCHECKWIN_OK].Attribute = true;
		if( gInterface.IsWorkZone(eCHECKWIN_OK) )
		{
			DWORD Color = eGray100;
			if( gInterface.Data[eCHECKWIN_OK].OnClick )
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eCHECKWIN_OK, gInterface.Data[eCHECKWIN_OK].X, gInterface.Data[eCHECKWIN_OK].Y, Color);
		}
	}
	else if( this->ActiveSkill && 
		gObjUser.Money >= this->PriceZen && 
		gObjUser.WCoinC >= this->PriceWcoin &&
		gObjUser.ExCred >= this->iHourCredit
		/*gObjUser.Premium || (this->ActiveSkill && gObjUser.m_Bonus >= 1) || gObjUser.InSafeZone()*/)
	{
		//gConsole.Output(cGREEN, "%d %d %d %d %d", this->ActiveSkill , this->PriceZen , gObjUser.Zen , this->PriceWcoin , gObjUser.WCoinC);
		gInterface.Data[eCHECKWIN_OK].Attribute = true;
		if( gInterface.IsWorkZone(eCHECKWIN_OK) )
		{
			DWORD Color = eGray100;
			if( gInterface.Data[eCHECKWIN_OK].OnClick )
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eCHECKWIN_OK, gInterface.Data[eCHECKWIN_OK].X, gInterface.Data[eCHECKWIN_OK].Y, Color);
		}
	}
	else
	{
		gInterface.Data[eCHECKWIN_OK].Attribute = false;
		gInterface.DrawColoredGUI(eCHECKWIN_OK, gInterface.Data[eCHECKWIN_OK].X, gInterface.Data[eCHECKWIN_OK].Y, eGray150);
	}
	// ---- 
	gInterface.DrawGUI(eCHECKWIN_CLOSE, StartX + 70 + 62, StartY /*- 5*/ );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5 + 5, 50, 3, "Cancel");
	if( gInterface.IsWorkZone(eCHECKWIN_CLOSE) )
	{
		DWORD Color = eGray100;
		if( gInterface.Data[eCHECKWIN_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eCHECKWIN_CLOSE, gInterface.Data[eCHECKWIN_CLOSE].X, gInterface.Data[eCHECKWIN_CLOSE].Y, Color);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Click(DWORD Event)
{
	if(!gInterface.CheckWindowEx(exWinCheckOffAfk))
	{
		return;
	}

	if( gInterface.Button(Event, exWinCheckOffAfk, eCHECKWIN_OK, true ))
	{
		gInterface.CloseWindowEx(exWinCheckOffAfk);
		this->GCResult();
		return;
	}

	if( gInterface.Button(Event, exWinCheckOffAfk, eCHECKWIN_CLOSE, false ) )
	{
		gInterface.CloseWindowEx(exWinCheckOffAfk);
		return;
	}

	// -> Skill Button

	if(gInterface.ButtonCord(Event, this->TempX, this->TempY, 20, 28, this->bClick, this->EventTick))
	{
		if(this->SendSkill > 0 && gObjUser.InSafeZone() == false)
		{
			this->ActiveSkill = this->TempSkill;
			this->ActiveX =	this->TempX;
			this->ActiveY =	this->TempY;
		}
	}

	// ----

	if(gInterface.Button(Event, exWinCheckOffAfk, eCHECKWIN_CHECK, 0))
	{
		this->AutoBuff = !this->AutoBuff;

		if(gObjUser.Class == CLASS_ELF)
		{
			 this->ActiveSkill = this->AutoBuff;
		}
	}

#if(ADD_OFFMODE_PICKUP==TRUE)

	bool PremiumResult = true;

	//if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
	//{
	//	if(gObjUser.PremiumType == g_PremiumSystemEx.m_iOfflineModePickUpPremiumRang && gObjUser.Premium > 0)
	//	{
	//		PremiumResult = true;
	//	}		
	//}
	//else
	//{
	//	if(gObjUser.Premium)
	//	{
	//		PremiumResult = true;
	//	}
	//}

	//if(gObjUser.Premium)
	if(PremiumResult)
	{
		if(gInterface.Button(Event, exWinCheckOffAfk, eOFFMODE_CHECK1, 0))
		{
			this->PickZen = !this->PickZen;
		}
		if(gInterface.Button(Event, exWinCheckOffAfk, eOFFMODE_CHECK2, 0))
		{
			this->PickJewel = !this->PickJewel;
		}
		if(gInterface.Button(Event, exWinCheckOffAfk, eOFFMODE_CHECK3, 0))
		{
			this->PickExel = !this->PickExel;
		}
		if(gInterface.Button(Event, exWinCheckOffAfk, eOFFMODE_CHECK4, 0))
		{
			this->PickAnc = !this->PickAnc;
		}
	}

	#if(ADD_OFFMODE_TIMER)
	//if(g_ExLicense.CheckUser(eExUB::eternalmu))
	//{
		if(gInterface.ButtonEx(Event, eOFFMODE_PAGEUP, 0))
		{
			int iMaxTime = this->m_OtherPlayerMaxTime;

			if(gObjUser.IsVIP())
			{
				iMaxTime = this->m_PremiumPlayerMaxTime;
			}

			if(this->m_PlayerTimeHour < iMaxTime)
			{
				this->m_PlayerTimeHour++;
			}
		}
		else if(gInterface.ButtonEx(Event, eOFFMODE_PAGEDN, 0))
		{
			if(this->m_PlayerTimeHour > 0)
			{
				this->m_PlayerTimeHour--;
			}
		}
	//}
	#endif

#endif


}
// ----------------------------------------------------------------------------------------------

void OfflineMode::GCResult()
{
	if(this->SendSkill == 0)
	{
		//return;
		//this->SendSkill = this->DefaultSkill();
	}

	//gConsole.Output(cGREY, "Send Skill: %d", this->SendSkill);

	CG_OFFMODE_RESULT pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x3D, sizeof(pRequest));
	pRequest.Result = this->SendSkill;
	pRequest.BuffResult = this->AutoBuff;

#if(ADD_OFFMODE_PICKUP==TRUE)
	pRequest.bPickZen = this->PickZen;
	pRequest.bPickJewel = this->PickJewel;
	pRequest.bPickExel = this->PickExel;
	pRequest.bPickAnc = this->PickAnc;
#endif

	#if(ADD_OFFMODE_TIMER)
	pRequest.TimerMax = this->m_PlayerTimeHour;
	#endif

	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Knight(float sX, float sY)
{
	float X = sX;
	float Y = sY;
	// -- NEXT 1
	int NumSkill = eTwistingSlash;
	float CritX = (double)(NumSkill % 8) * this->Whith / 256;
	float CritY = (double)(NumSkill / 8) * this->High / 256;

	int iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(SKILL_WHEEL))
	{
		iSearchSkill = SKILL_WHEEL;
	}
	else if(gObjUser.GetCheckSkill(330))
	{
		iSearchSkill = 330;
	}
	else if(gObjUser.GetCheckSkill(332))
	{
		iSearchSkill = 332;
	}
	else if(gObjUser.GetCheckSkill(481))
	{
		iSearchSkill = 481;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 1;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 2
	NumSkill = eRagefulBlow;
	CritX = (double)(NumSkill % 8) * this->Whith / 256;
	CritY = (double)(NumSkill / 8) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(SKILL_BLOWOFFURY))
	{
		iSearchSkill = SKILL_BLOWOFFURY;
	}
	else if(gObjUser.GetCheckSkill(331))
	{
		iSearchSkill = 331;
	}
	else if(gObjUser.GetCheckSkill(333))
	{
		iSearchSkill = 333;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 2;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 3
	NumSkill = eStrikeofDestruction;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(232))
	{
		iSearchSkill = 232;
	}
	else if(gObjUser.GetCheckSkill(337))
	{
		iSearchSkill = 337;
	}
	else if(gObjUser.GetCheckSkill(340))
	{
		iSearchSkill = 340;
	}
	else if(gObjUser.GetCheckSkill(343))
	{
		iSearchSkill = 343;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;
			this->TempSkill = 3;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- BORDER
	if(this->ActiveSkill)
	{
		gInterface.DrawBorder(this->ActiveX, this->ActiveY, this->Whith, this->High, 1, eRed);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Wizard(float sX, float sY)
{
	float X = sX;
	float Y = sY;
	// -- NEXT 1
	int NumSkill = eEvilSpirit;
	float CritX = (double)(NumSkill % 8) * this->Whith / 256;
	float CritY = (double)(NumSkill / 8) * this->High / 256;

	int iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(9))
	{
		iSearchSkill = 9;
	}
	else if(gObjUser.GetCheckSkill(385))
	{
		iSearchSkill = 385;
	}

	if(iSearchSkill == -1)	//385
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 1;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 2
	NumSkill = eInferno;
	CritX = (double)(NumSkill % 8) * this->Whith / 256;
	CritY = (double)(NumSkill / 8) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(14))
	{
		iSearchSkill = 14;
	}
	else if(!gObjUser.GetCheckSkill(381))
	{
		iSearchSkill = 381;
	}

	if(iSearchSkill == -1)	//381
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 2;
			this->SendSkill = 14;
		}
	}
	// -- NEXT 3
	NumSkill = eIceStorm;
	CritX = (double)(NumSkill % 8) * this->Whith / 256;
	CritY = (double)(NumSkill / 8) * this->High / 256;
	X += 50;

	if(!gObjUser.GetCheckSkill(39))
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 3;
			this->SendSkill = 39;
		}
	}
	// -- BORDER
	if(this->ActiveSkill)
	{
		gInterface.DrawBorder(this->ActiveX, this->ActiveY, this->Whith, this->High, 1, eRed);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Elf(float sX, float sY)
{
	float X = sX;
	float Y = sY;
	// -- NEXT 1
	int NumSkill = eTripleShot;
	float CritX = (double)(NumSkill % 8) * this->Whith / 256;
	float CritY = (double)(NumSkill / 8) * this->High / 256;

	bool DrResult = false;

	int iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(24))
	{
		iSearchSkill = 24;
	}
	else if(gObjUser.GetCheckSkill(414))
	{
		iSearchSkill = 414;
	}
	else if(gObjUser.GetCheckSkill(418))
	{
		iSearchSkill = 418;
	}

	if(iSearchSkill == -1)	//414	418
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 1;
			this->SendSkill = iSearchSkill;
		}
		DrResult = true;
	}
	// -- NEXT 2
	NumSkill = eMultiShot;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;
	if(!gObjUser.GetCheckSkill(235))
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 2;
			this->SendSkill = 235;
		}
		DrResult = true;
	}
	// -- NEXT 3
	NumSkill = eIceArrow;
	CritX = (double)(NumSkill % 8) * this->Whith / 256;
	CritY = (double)(NumSkill / 8) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(51))
	{
		iSearchSkill = 51;
	}
	if(gObjUser.GetCheckSkill(424))
	{
		iSearchSkill = 424;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 3;
			this->SendSkill = iSearchSkill;
		}
		DrResult = true;
	}
	// -- BORDER
	if(this->ActiveSkill || DrResult)
	{
		gInterface.DrawBorder(this->ActiveX, this->ActiveY, this->Whith, this->High, 1, eRed);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Summoner(float sX, float sY)
{
	float X = sX;
	float Y = sY;
	// -- NEXT 1
	int NumSkill = eChainLightning;
	float CritX = (double)(NumSkill % 12) * this->Whith / 256;
	float CritY = (double)(NumSkill / 12) * this->High / 256;

	int iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(215))
	{
		iSearchSkill = 215;
	}
	else if(gObjUser.GetCheckSkill(455))
	{
		iSearchSkill = 455;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 1;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 2
	NumSkill = eLightningShock;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(230))
	{
		iSearchSkill = 230;
	}
	else if(gObjUser.GetCheckSkill(456))
	{
		iSearchSkill = 456;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 2;
			this->SendSkill = 230;
		}
	}
	// -- NEXT 3
	NumSkill = eSpellofPursuit;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;
	if(!gObjUser.GetCheckSkill(225))
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 3;
			this->SendSkill = 225;
		}
	}
	// -- BORDER
	if(this->ActiveSkill)
	{
		gInterface.DrawBorder(this->ActiveX, this->ActiveY, this->Whith, this->High, 1, eRed);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Magic(float sX, float sY)
{
	sX -= 25;
	float X = sX;
	float Y = sY;
	// -- NEXT 1
	int NumSkill = eEvilSpirit;
	float CritX = (double)(NumSkill % 8) * this->Whith / 256;
	float CritY = (double)(NumSkill / 8) * this->High / 256;

	int iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(9))
	{
		iSearchSkill = 9;
	}
	else if(gObjUser.GetCheckSkill(487))
	{
		iSearchSkill = 487;//
	}

	if(iSearchSkill ==-1)
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 1;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 2
	NumSkill = eTwistingSlash;
	CritX = (double)(NumSkill % 8) * this->Whith / 256;
	CritY = (double)(NumSkill / 8) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(SKILL_WHEEL))
	{
		iSearchSkill = SKILL_WHEEL;
	}
	else if(gObjUser.GetCheckSkill(330))
	{
		iSearchSkill = 330;
	}
	else if(gObjUser.GetCheckSkill(332))
	{
		iSearchSkill = 332;
	}
	else if(gObjUser.GetCheckSkill(481))
	{
		iSearchSkill = 481;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 2;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 3
	NumSkill = ePowerSlash;
	CritX = (double)(NumSkill % 8) * this->Whith / 256;
	CritY = (double)(NumSkill / 8) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(56))
	{
		iSearchSkill = 56;
	}
	else if(gObjUser.GetCheckSkill(482))
	{
		iSearchSkill = 482;
	}
	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff1, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4C, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 3;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 4
	NumSkill = eLightingShtorm;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;
	if(!gObjUser.GetCheckSkill(237))
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 4;
			this->SendSkill = 237;
		}
	}
	// -- BORDER
	if(this->ActiveSkill)
	{
		gInterface.DrawBorder(this->ActiveX, this->ActiveY, this->Whith, this->High, 1, eRed);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Lord(float sX, float sY)
{
	float X = sX;
	float Y = sY;
	// -- NEXT 1
	int NumSkill = eFireBurst;
	float CritX = (double)(NumSkill % 12) * this->Whith / 256;
	float CritY = (double)(NumSkill / 12) * this->High / 256;

	int iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(61))
	{
		iSearchSkill = 61;
	}
	else if(gObjUser.GetCheckSkill(508))
	{
		iSearchSkill = 508;
	}
	else if(gObjUser.GetCheckSkill(514))
	{
		iSearchSkill = 514;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 1;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 2
	NumSkill = eFireScream;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(78))
	{
		iSearchSkill = 78;
	}
	else if(gObjUser.GetCheckSkill(518))
	{
		iSearchSkill = 518;
	}

	if(iSearchSkill == -1)
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 2;
			this->SendSkill = 78;
		}
	}
	// -- NEXT 3
	NumSkill = eChaoticDiseier;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;
	if(!gObjUser.GetCheckSkill(238))
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 3;
			this->SendSkill = 238;
		}
	}
	// -- BORDER
	if(this->ActiveSkill)
	{
		gInterface.DrawBorder(this->ActiveX, this->ActiveY, this->Whith, this->High, 1, eRed);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Fighter(float sX, float sY)
{
	float X = sX;
	float Y = sY;
	// -- NEXT 1
	int NumSkill = eFireBurst;
	float CritX = (double)(NumSkill % 12) * this->Whith / 256;
	float CritY = (double)(NumSkill / 12) * this->High / 256;

	int iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(264))
	{
		iSearchSkill = 264;
	}
	else if(gObjUser.GetCheckSkill(560))
	{
		iSearchSkill = 560;
	}

	if(iSearchSkill == -1)//560
	{
		pDrawGUFULL(eImgSkillOff3, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(eImgSkillOn3, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 1;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 2
	NumSkill = 3;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;

	iSearchSkill = -1;

	if(gObjUser.GetCheckSkill(263))//559
	{
		iSearchSkill = 263;
	}
	else if(gObjUser.GetCheckSkill(559))//559
	{
		iSearchSkill = 559;
	}

	if(iSearchSkill == -1)//559
	{
		pDrawGUFULL(eImgSkillOff3, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(eImgSkillOn3, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 2;
			this->SendSkill = iSearchSkill;
		}
	}
	// -- NEXT 3
	/*NumSkill = eChaoticDiseier;
	CritX = (double)(NumSkill % 12) * this->Whith / 256;
	CritY = (double)(NumSkill / 12) * this->High / 256;
	X += 50;
	if(!gObjUser.GetCheckSkill(238))
	{
		pDrawGUFULL(eImgSkillOff2, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x7A4D, X, Y, this->Whith, this->High, CritX, CritY, this->standartWhith, this->standartHight, 1, 1, 0.0);
		if(gInterface.IsWorkZone(X, Y, X + this->Whith, Y + this->High))
		{
			this->TempX = X;
			this->TempY = Y;	
			this->TempSkill = 3;
			this->SendSkill = 238;
		}
	}*/
	// -- BORDER
	if(this->ActiveSkill)
	{
		gInterface.DrawBorder(this->ActiveX, this->ActiveY, this->Whith, this->High, 1, eRed);
	}
}
// ----------------------------------------------------------------------------------------------

int OfflineMode::DefaultSkill()
{
	switch(gObjUser.Class)
	{
		case CLASS_KNIGHT:		return 41;
		case CLASS_WIZARD:		return 9;
		case CLASS_ELF:			return 24;
		case CLASS_SUMMONER:	return 215;
		case CLASS_MAGUMSA:		return 9;
		case CLASS_DARKLORD:	return 61;
		case CLASS_MONK:		return 264;
	}

	return 0;
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::GCConfig(GC_OFFMODE_CONFIG * aRecv)
{
	//gConsole.Output(cGREEN, "cfg: %d %d", aRecv->PriceZen, aRecv->PriceWcoin);
	this->PriceZen = aRecv->PriceZen;
	this->PriceWcoin = aRecv->PriceWcoin;
	this->iHourCredit = aRecv->iHourCredit;

	#if(ADD_OFFMODE_TIMER)
	this->m_PlayerTimeHour = aRecv->StandartPlayerTime;
	this->m_OtherPlayerMaxTime = aRecv->OtherPlayerMaxTime;
	this->m_PremiumPlayerMaxTime = aRecv->PremiumPlayerMaxTime;
	#endif
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::ClearSettings()
{
	this->SendSkill = 0;
	this->ActiveSkill = 0;
	this->AutoBuff = false;
#if(ADD_OFFMODE_PICKUP==TRUE)
	this->PickZen = false;
	this->PickJewel = false;
	this->PickExel = false;
	this->PickAnc = false;
#endif
}
#endif