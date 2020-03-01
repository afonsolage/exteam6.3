#include "stdafx.h"
#include "Object.h"
#include "TMemory.h"
#include "ConnectEx.h"
#include "NewHpBar.h"
#include "User.h"
#include "Interface.h"
#include "Console.h"
#include "ChatExpanded.h"
#include "Other.h"
#include "QuestSystem.h"
#include "Configs.h"
#include "NewParty.h"
#include "ExLicense.h"
#include "TeamVsTeam.h"
#include "ExText.h"

#ifdef NEW_HP_BAR

ViewePortInfo gViewePortInfo;

void ViewePortInfo::NewHpBarLoad()
{
}

int HpResMode()
{
	if(exWinWidth == 800 & exWinHeight == 600)
	{
		return 5;
	}
	else if (exWinWidth == 1024 & exWinHeight == 768)
	{
		return 10;
	}
	else if (exWinWidth == 1280 & exWinHeight == 720)
	{
		return 10;
	}
	else if (exWinWidth == 1280 & exWinHeight == 800)
	{
		return 10;
	}
	else if (exWinWidth == 1366 & exWinHeight == 768)
	{
		return 10;
	}
	else if (exWinWidth == 1440 & exWinHeight == 900)
	{
		return 13;
	}
	else if (exWinWidth == 1280 & exWinHeight == 1024)
	{
		return 14;
	}
	else if (exWinWidth == 1600 & exWinHeight == 1200)
	{
		return 16;
	}
	else if (exWinWidth == 1680 & exWinHeight == 1050)
	{
		return 13;
	}
	else if (exWinWidth == 1920 & exWinHeight == 1080)
	{
		return 13;
	}
	else if (exWinWidth == 1920 & exWinHeight == 1200)
	{
		return 16;
	}
	else
	{
		return 5;
	}
}

bool ViewePortInfo::CheckClass(int Number)
{
	if(Number > 6) return false;
	return true;
}

void ViewePortInfo::TargetMonsterHpBar()
{
	char LifeDisplay[30];
	VAngle Angle;
	int PosX, PosY, LifeProgress;

	float LifeBarWidth	= 38.0f;

	lpViewObj lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), gObjUser.VieweTargetID);

	if( !lpViewTarget || !lpViewTarget->m_Model.Unknown4 ) return;

	if(lpViewTarget->m_Model.ObjectType == emMonster)
	{
		int Life, MaxLife, Level, Def;

		bool Draw = false;
#ifdef VIEW_MONSTER
		char NewName[20];
#endif
		for(int n = 0; n < MAX_VIEWPORT;n++)
		{
			if(lpViewTarget->aIndex == gObjUser.ExViewe[n].aIndex)
			{
				Life = gObjUser.ExViewe[n].Life;
				MaxLife = gObjUser.ExViewe[n].MaxLife;
				Level = gObjUser.ExViewe[n].Level;
				Def = gObjUser.ExViewe[n].Defence;
				Draw = true;
				if(Life > MaxLife)
				{
					gObjUser.ExViewe[n].Life = MaxLife;
					Life = MaxLife;
				}
#ifdef VIEW_MONSTER
				memcpy(NewName,gObjUser.ExViewe[n].Name,sizeof(NewName));	
#endif
				break;
			}
		}

		if(Draw == false || Life <= 0)
		{
			return;
		}

		int DevX = 20;
		int Wind = 70;

		Angle.X = lpViewTarget->m_Model.VecPosX;
		Angle.Y = lpViewTarget->m_Model.VecPosY;
		Angle.Z = lpViewTarget->m_Model.VecPosZ + lpViewTarget->m_Model.Unknown216.Z + 100.0;

		pGetPosFromAngle(&Angle, &PosX, &PosY);

		//PosX -= (int)floor(LifeBarWidth / (double)2.0);
		PosX -= (int)floor((double)Wind / (double)4.0);

		sprintf(LifeDisplay, g_ExText.GetText(17), Level, Life);

		pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));

		pDrawText(pTextThis(), PosX-DevX, PosY - 19, LifeDisplay, Wind, 10, (LPINT)3, 0);		
#ifdef VIEW_MONSTER
		sprintf(LifeDisplay, "%s",NewName);
#else
		sprintf(LifeDisplay, "%s", lpViewTarget->Name);
#endif
		pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
		pDrawText(pTextThis(), PosX - DevX, PosY - 8, LifeDisplay, Wind, 14, (LPINT)3, 0);

		pSetBlend(true);
		pGLSwitchBlend();

		int pHP = (Life * 100) / MaxLife;

		if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
		{
			if(Life > 0 && MaxLife > 100000000)
			{
				 pHP = Life / (MaxLife / 100);
			}
		}

		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2), (Wind * pHP) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
	}
}

void ViewePortInfo::AllMonsterHpBar()
{
	char LifeDisplay[30];
	VAngle Angle;
	int PosX, PosY, LifeProgress;

	float LifeBarWidth	= 38.0f;

	for(int i = 0; i < 400; i++)
	{
		lpViewObj lpObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if( !lpObj || !lpObj->m_Model.Unknown4 )
		{
			continue;
		}

		if(lpObj->m_Model.ObjectType == emMonster)
		{
			int Life, MaxLife, Level, Shield, MaxShield, Reset, GRand;

			bool Draw = false;
#ifdef VIEW_MONSTER
			char NewName[20];
#endif
			for(int n = 0; n < MAX_VIEWPORT;n++)
			{
				if(lpObj->aIndex == gObjUser.ExViewe[n].aIndex)
				{
				
					Life = gObjUser.ExViewe[n].Life;
					MaxLife = gObjUser.ExViewe[n].MaxLife;
					Level = gObjUser.ExViewe[n].Level;
					Draw = true;
					if(Life > MaxLife)
					{
						gObjUser.ExViewe[n].Life = MaxLife;
						Life = MaxLife;
					}
#ifdef VIEW_MONSTER
					memcpy(NewName,gObjUser.ExViewe[n].Name,sizeof(NewName));
#endif
					break;
				}
			}

			if(Draw == false || Life <= 0)
			{
				continue;
			}

			int DevX = 20;
			int Wind = 70;

			Angle.X = lpObj->m_Model.VecPosX;
			Angle.Y = lpObj->m_Model.VecPosY;
			Angle.Z = lpObj->m_Model.VecPosZ + lpObj->m_Model.Unknown216.Z + 100.0;

			pGetPosFromAngle(&Angle, &PosX, &PosY);
			PosX -= (int)floor((double)Wind / (double)4.0);

			if(gObjUser.VieweTargetID == i)
			{
				sprintf(LifeDisplay, g_ExText.GetText(17),Level, Life);

				pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
				pDrawText(pTextThis(), PosX-DevX, PosY - 19, LifeDisplay, Wind, 10, (LPINT)3, 0);		
			}

#ifdef VIEW_MONSTER
			sprintf(LifeDisplay, "%s", NewName);
#else
			sprintf(LifeDisplay, "%s", lpObj->Name);
#endif
			
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
#ifdef exDEBUG_CODE
			pDrawColorText(LifeDisplay, PosX-DevX, PosY - 8, Wind, 0, eWhite, 1, 3);
			//gInterface.DrawFormat(eAncient,PosX-DevX,  PosY - 8 , 50, 3, LifeDisplay);
#else
			pDrawText(pTextThis(), PosX - DevX, PosY - 8, LifeDisplay, Wind, 14, (LPINT)3, 0);
#endif

			pSetBlend(true);
			pGLSwitchBlend();

			int pHP = (Life * 100) / MaxLife;
			//pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2), (Wind * pHP) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));
			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
			{
				if(Life > 0 && MaxLife > 100000000)
				{
					 pHP = Life / (MaxLife / 100);
				}
			}
			pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2), (Wind * pHP) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));
			
			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
		}
	}
#ifdef exDEBUG_CODE
	//pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
#endif
}


void ViewePortInfo::TargetUserHpBar()
{
	char LifeDisplay[30];
#ifdef PREM_TYPE
		char PremType[25];
#endif
	VAngle Angle;
	int PosX, PosY, LifeProgress;

	float LifeBarWidth	= 38.0f;

	lpViewObj lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), gObjUser.VieweTargetID);
	//return;
	if( !lpViewTarget || !lpViewTarget->m_Model.Unknown4 ) return;
	//return;
#ifdef exDEBUG_CODE
	//gConsole.Output(cGREEN,"%d",lpViewTarget->Class);
#endif

	if(lpViewTarget->m_Model.ObjectType == emPlayer)
	{
		bool Result = false;
#if _NEW_PARTY_SYSTEM_ == TRUE
		if( g_Party.PartyMemberCount > 0 )
#else
		if( pPartyMemberCount > 0 )
#endif
		{
#if _NEW_PARTY_SYSTEM_ == TRUE
			for( int PartySlot = 0; PartySlot < g_Party.PartyMemberCount; PartySlot++ )
#else
			for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
#endif
			{
				PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
				if(gObjUser.VieweTargetID == PartyMember.ViewportID)
				{
					return;
				}
			}
		}
#ifdef PREM_TYPE
			int Life, MaxLife, Shield, MaxShield, Def, Reset, Level, GrandReset, AutoPt, PremTypeInt;
#else
		int Life, MaxLife, Shield, MaxShield, Def, Reset, Level, GrandReset, AutoPt;
#endif

		bool Draw = false;

		for(int n = 0; n < MAX_VIEWPORT;n++)
		{
			if(lpViewTarget->aIndex == gObjUser.ExViewe[n].aIndex && CheckClass(gObjUser.ExViewe[n].Class))
			{
				Life = gObjUser.ExViewe[n].Life;
				MaxLife = gObjUser.ExViewe[n].MaxLife;
				Level = gObjUser.ExViewe[n].Level;
				Def = gObjUser.ExViewe[n].Defence;
				Shield = gObjUser.ExViewe[n].SD;
				MaxShield = gObjUser.ExViewe[n].MaxSD;
				Reset = gObjUser.ExViewe[n].Reset;
				GrandReset = gObjUser.ExViewe[n].GrandReset;
				AutoPt = gObjUser.ExViewe[n].AutoParty;
#ifdef PREM_TYPE
				if(g_ExLicense.CheckUser(eExUB::ulasevich)  || 
				   g_ExLicense.CheckUser(eExUB::ulasevich2)	||	   
				   g_ExLicense.CheckUser(eExUB::Local3))
				{
					PremTypeInt = gObjUser.ExViewe[n].PremType;
				}
#endif	

				if(Life > MaxLife)
				{
					gObjUser.ExViewe[n].Life = MaxLife;
					Life = MaxLife;
				}
				Draw = true;
				break;
			}
		}

		if(Draw == false || Life <= 0)
		{
			return;
		}

		int DevX = 20;
		int Wind = 70;
		int DevY = 0;

		Angle.X = lpViewTarget->m_Model.VecPosX;
		Angle.Y = lpViewTarget->m_Model.VecPosY;
		Angle.Z = lpViewTarget->m_Model.VecPosZ + lpViewTarget->m_Model.Unknown216.Z + 100.0;

		pGetPosFromAngle(&Angle, &PosX, &PosY);
		PosX -= (int)floor((double)Wind / (double)4.0);

		PosY -= 10 - HpResMode();

		//return;

		if(gObjUser.BattleCursor == true)
		{
			sprintf(LifeDisplay, g_ExText.GetText(18), Life);
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
		}
		else
		{
			sprintf(LifeDisplay, g_ExText.GetText(19), Level, Reset/*,GrandReset*/);
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
#ifdef PREM_TYPE
			if(g_ExLicense.CheckUser(eExUB::ulasevich)	|| 
				g_ExLicense.CheckUser(eExUB::ulasevich2) ||	   
				g_ExLicense.CheckUser(eExUB::Local3))
			{

				if (PremTypeInt == 1)
				{
					sprintf(PremType, "Vip Type: Bronze");
					pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
					pDrawText(pTextThis(), PosX-DevX, PosY - DevY-9, PremType, Wind, 16, (LPINT)3, 0);	
				}
				if (PremTypeInt == 2)
				{
					sprintf(PremType, "Vip Type: Silver");
					pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
					pDrawText(pTextThis(), PosX-DevX, PosY - DevY-9, PremType, Wind, 16, (LPINT)3, 0);	
				}
				if (PremTypeInt == 3)
				{
					sprintf(PremType, "Vip Type: Gold");
					pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
					pDrawText(pTextThis(), PosX-DevX, PosY - DevY-9, PremType, Wind, 16, (LPINT)3, 0);	
				}
			}
#endif
		}

		pSetBlend(true);
		pGLSwitchBlend();

		int pSD = (Shield * 100) / MaxShield;

		/*if(Shield > 0 && MaxShield > 1000000)
		{
			 pSD = Shield / (MaxShield / 100);
		}*/

		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2 - DevY + 7), (Wind * pSD) / 100, 2, 0, 0, (int)Color4f(255, 255, 0, 130));

		int pHP = (Life * 100) / MaxLife;

		/*if(Life > 0 && MaxLife > 1000000)
		{
			pHP = Life / (MaxLife / 100);
		}*/

		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 4 - DevY + 9), (Wind * pHP) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

		if(AutoPt > 0)
		{
			pDrawGUI(0x7B41,PosX-DevX+Wind+1,PosY-DevY,9,11);
		}

		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
	}
}

void ViewePortInfo::AllUserHpBar()
{
	char LifeDisplay[30];
	VAngle Angle;
	int PosX, PosY, LifeProgress;

	float LifeBarWidth	= 38.0f;
	for(int i = 0; i < 400; i++)
	{
		lpViewObj lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if( !lpViewTarget || !lpViewTarget->m_Model.Unknown4 ) continue;

		if(lpViewTarget->m_Model.ObjectType == emPlayer)
		{
			/*bool Result = false;
#if _NEW_PARTY_SYSTEM_ == TRUE
			if( g_Party.PartyMemberCount > 0 )
#else
			if( pPartyMemberCount > 0 )
#endif
			{
#if _NEW_PARTY_SYSTEM_ == TRUE
				for( int PartySlot = 0; PartySlot < g_Party.PartyMemberCount; PartySlot++ )
#else
				for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
#endif
				{
					PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
					if(pViewAttackTargetID == PartyMember.ViewportID)
					{
						return;
					}
				}
			}*/

			int Life, MaxLife, Shield, MaxShield, Def, Reset, Level, GrandReset;

			int iTeam;
			DWORD ColorHPBar;
			DWORD ColorSDBar;

			bool Draw = false;

			for(int n = 0; n < MAX_VIEWPORT;n++)
			{
				if(lpViewTarget->aIndex == gObjUser.ExViewe[n].aIndex)
				{
					Life = gObjUser.ExViewe[n].Life;
					MaxLife = gObjUser.ExViewe[n].MaxLife;
					Level = gObjUser.ExViewe[n].Level;
					Def = gObjUser.ExViewe[n].Defence;
					Shield = gObjUser.ExViewe[n].SD;
					MaxShield = gObjUser.ExViewe[n].MaxSD;
					Reset = gObjUser.ExViewe[n].Reset;
					GrandReset = gObjUser.ExViewe[n].GrandReset;
					iTeam = gObjUser.ExViewe[n].TvTTeam;

					if(Life > MaxLife)
					{
						gObjUser.ExViewe[n].Life = MaxLife;
						Life = MaxLife;
					}
					Draw = true;
					break;
				}
			}

			if(Draw == false || Life <= 0)
			{
				continue;
			}

			int DevX = 20;
			int Wind = 70;
			int DevY = 0;

			Angle.X = lpViewTarget->m_Model.VecPosX;
			Angle.Y = lpViewTarget->m_Model.VecPosY;
			Angle.Z = lpViewTarget->m_Model.VecPosZ + lpViewTarget->m_Model.Unknown216.Z + 100.0;

			pGetPosFromAngle(&Angle, &PosX, &PosY);
			PosX -= (int)floor((double)Wind / (double)4.0);

			PosY -= 10 - HpResMode();

			if(CheckBattleCursor() == true)
			{
				sprintf(LifeDisplay, g_ExText.GetText(18), Life);
				pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
				pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
			}
			else
			{
				sprintf(LifeDisplay, g_ExText.GetText(19), Level, Reset/*,GrandReset*/);
				pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
				pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
			}
			//
			if(!g_TeamVsTeam.CheckStatus(eEVENT_TEAMVSTEAM_START) || gObjUser.m_MapNumber != TEAMVSTEAM_MAP)
			{
				ColorSDBar = Color4f(255, 255, 0, 130);
				ColorHPBar = Color4f(255, 0, 0, 130);
			}
			else
			{
				if(iTeam == g_TeamVsTeam.m_Team)
				{
					ColorSDBar = Color4f(0, 255, 0, 130);
					ColorHPBar = Color4f(0, 0, 255, 130);	
				}
				else
				{
					ColorSDBar = Color4f(255, 0, 0, 130);
					ColorHPBar = Color4f(255, 0, 0, 130);
				}
			}
			//
			pSetBlend(true);

			pGLSwitchBlend();

			int pSD = (Shield * 100) / MaxShield;

			/*if(Shield > 0 && MaxShield > 1000000)
			{
				 pSD = Shield / (MaxShield / 100);
			}*/

			pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2 - DevY + 7), (Wind * pSD) / 100, 2, 0, 0, ColorSDBar);

			int pHP = (Life * 100) / MaxLife;

			/*if(Life > 0 && MaxLife > 1000000)
			{
				 pHP = Life / (MaxLife / 100);
			}*/

			pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 4 - DevY + 9), (Wind * pHP) / 100, 2, 0, 0, ColorHPBar);

			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
		}
	}
}

void ViewePortInfo::PartyHPBar()
{
#if _NEW_PARTY_SYSTEM_ == TRUE
	if( g_Party.PartyMemberCount <= 0 )
#else
    if( pPartyMemberCount <= 0 )
#endif
    {
        return;
    }

    float LifeBarWidth = 38.0f;
    char LifeDisplay[30];
    VAngle Angle;
    int PosX, PosY, LifeProgress;

#if _NEW_PARTY_SYSTEM_ == TRUE
	for( int PartySlot = 0; PartySlot < g_Party.PartyMemberCount; PartySlot++ )
#else
    for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
#endif
    {
#if _NEW_PARTY_SYSTEM_ == TRUE
		lpViewObj lpPartyObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), g_Party.PartyData[PartySlot].ViewportID);
#else
        PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
		lpViewObj lpPartyObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), PartyMember.ViewportID);
#endif

        if( !lpPartyObj || !lpPartyObj->m_Model.Unknown4 )
        {
            continue;
        }
#ifdef PREM_TYPE
			int Life, MaxLife, Shield, MaxShield, Def, Reset, Level, GrandReset,AutoPt, PremTypeInt;
		
#else
		int Life, MaxLife, Shield, MaxShield, Def, Reset, Level, GrandReset,AutoPt;
#endif

		bool Draw = false;

		for(int n = 0; n < MAX_VIEWPORT;n++)
		{
			if(lpPartyObj->aIndex == gObjUser.ExViewe[n].aIndex)
			{
				Life = gObjUser.ExViewe[n].Life;
				MaxLife = gObjUser.ExViewe[n].MaxLife;
				Level = gObjUser.ExViewe[n].Level;
				Def = gObjUser.ExViewe[n].Defence;
				Shield = gObjUser.ExViewe[n].SD;
				MaxShield = gObjUser.ExViewe[n].MaxSD;
				Reset = gObjUser.ExViewe[n].Reset;
				GrandReset = gObjUser.ExViewe[n].GrandReset;
				AutoPt = gObjUser.ExViewe[n].AutoParty;
				if(Life > MaxLife)
				{
					gObjUser.ExViewe[n].Life = MaxLife;
					Life = MaxLife;
				}
#ifdef PREM_TYPE
				if(g_ExLicense.CheckUser(eExUB::ulasevich)	|| 
				   g_ExLicense.CheckUser(eExUB::ulasevich2)	|| 
				   g_ExLicense.CheckUser(eExUB::Local3))
				{
					PremTypeInt = gObjUser.ExViewe[n].PremType;
				}
#endif
				Draw = true;
				break;
			}
		}

		if(Draw == false || Life <= 0)
		{
			return;
		}

		int DevX = 20;
		int Wind = 70;
		int DevY = 0;

		Angle.X = lpPartyObj->m_Model.VecPosX;
		Angle.Y = lpPartyObj->m_Model.VecPosY;
		Angle.Z = lpPartyObj->m_Model.VecPosZ + lpPartyObj->m_Model.Unknown216.Z + 100.0;
		// ----
		pGetPosFromAngle(&Angle, &PosX, &PosY);
		PosX -= (int)floor((double)Wind / (double)4.0);

		PosY -= 10 - HpResMode();
		char PremType[25];

#if _NEW_PARTY_SYSTEM_ == TRUE
		if(gObjUser.VieweTargetID == g_Party.PartyData[PartySlot].ViewportID && gObjUser.BattleCursor == false)
#else
		if(gObjUser.VieweTargetID == PartyMember.ViewportID && gObjUser.BattleCursor == false)
#endif
		{	
			sprintf(LifeDisplay, g_ExText.GetText(19), Level, Reset/*, GrandReset*/);

			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);
#ifdef PREM_TYPE
			if(g_ExLicense.CheckUser(eExUB::ulasevich)  || 
			   g_ExLicense.CheckUser(eExUB::ulasevich2) ||	   
			   g_ExLicense.CheckUser(eExUB::Local3))
			{
				if (PremTypeInt == 1)
				{
					sprintf(PremType, "Vip Type: Bronze");
					pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
					pDrawText(pTextThis(), PosX-DevX, PosY - DevY-9, PremType, Wind, 16, (LPINT)3, 0);	
				}
				if (PremTypeInt == 2)
				{
					sprintf(PremType, "Vip Type: Silver");
					pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
					pDrawText(pTextThis(), PosX-DevX, PosY - DevY-9, PremType, Wind, 16, (LPINT)3, 0);	
				}
				if (PremTypeInt == 3)
				{
					sprintf(PremType, "Vip Type: Gold");
					pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
					pDrawText(pTextThis(), PosX-DevX, PosY - DevY-9, PremType, Wind, 16, (LPINT)3, 0);	
				}
			}
#endif
		}
		else
		{
			sprintf(LifeDisplay, g_ExText.GetText(18), Life);

			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
		}

		pSetBlend(true);
		pGLSwitchBlend();

		int pSD = (Shield * 100) / MaxShield;

		/*if(Shield > 0 && MaxShield > 1000000)
		{
			pSD = Shield / (MaxShield / 100);
		}*/

		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2 - DevY + 7), (Wind * pSD) / 100, 2, 0, 0, (int)Color4f(255, 255, 0, 130));

		int pHP = (Life * 100) / MaxLife;

		/*if(Life > 0 && MaxLife > 1000000)
		{
			pHP = Life / (MaxLife / 100);
		}*/

		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 4 - DevY + 9), (Wind * pHP) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

		if(AutoPt > 0)
		{
			pDrawGUI(0x7B41,PosX-DevX+Wind+1,PosY-DevY,9,11);
		}

		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
    }
}

void ViewePortInfo::DrawPartyHP()
{
#ifdef exDEBUG_CODE
	pSetBlend(true);
	pGLSwitchBlend();

	//int pHP = (Life * 100) / MaxLife;
	//pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2), (Wind * pHP/*100*/) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
#endif

	if(CC_MAP_RANGE(pMapNumber))
	{
		return;
	}

	#if(DEV_PLAYERINFO)
	gInterface.DrawTargetInfo();
	#endif

#if(CUSTOM_PLAYERTITLE)
	gViewePortInfo.PlayerTitle();
#endif

	if(g_TeamVsTeam.CheckStatus(eEVENT_TEAMVSTEAM_START) && gObjUser.m_MapNumber == TEAMVSTEAM_MAP)
	{
		gViewePortInfo.AllUserHpBar();
		return;
	}
	if(iMonsterHPBar == 1)
	{
		gViewePortInfo.AllMonsterHpBar();
	}
	else if(iMonsterHPBar == 2)
	{
		gViewePortInfo.TargetMonsterHpBar();
	}

	if(iUserHpBar)
	{
		gViewePortInfo.TargetUserHpBar();
	}
	if(iPartyHpBar)
	{
		gViewePortInfo.PartyHPBar();
	}
	else
	{
#if _NEW_PARTY_SYSTEM_ == TRUE
		if( g_Party.PartyMemberCount > 0 )
#else
		if( pPartyMemberCount > 0 )
#endif
		{
			float LifeBarWidth = 38.0f;
			char LifeDisplay[30];
			VAngle Angle;
			int PosX, PosY, LifeProgress;
#if _NEW_PARTY_SYSTEM_ == TRUE
			for( int PartySlot = 0; PartySlot < g_Party.PartyMemberCount; PartySlot++ )
#else
			for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
#endif
			{
#if _NEW_PARTY_SYSTEM_ == TRUE
				lpViewObj lpPartyObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), g_Party.PartyData[PartySlot].ViewportID);
#else
				PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
				lpViewObj lpPartyObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), PartyMember.ViewportID);
#endif

				if( !lpPartyObj )
				{
					continue;
				}

				Angle.X = lpPartyObj->m_Model.VecPosX;
				Angle.Y = lpPartyObj->m_Model.VecPosY;
				Angle.Z = lpPartyObj->m_Model.VecPosZ + lpPartyObj->m_Model.Unknown216.Z + 100.0;
 
				pGetPosFromAngle(&Angle, &PosX, &PosY);
#ifdef exDEBUG_CODE
			//	gConsole.Output(cGREEN,"PartySlot: %d ,PosX: %d, PosY: %d",PartySlot,PosX,PosY);
#endif
				PosX -= (int)floor(LifeBarWidth / (double)2.0);
 
				if(        pCursorX >= PosX
					&&    (float)pCursorX <= (float)PosX + LifeBarWidth
					&&    pCursorY >= PosY - 2
					&&    pCursorY < PosY + 6 )
				{
#if _NEW_PARTY_SYSTEM_ == TRUE
						sprintf(LifeDisplay, g_ExText.GetText(20), g_Party.PartyData[PartySlot].LifePercent);
#else
						sprintf(LifeDisplay, g_ExText.GetText(20), PartyMember.LifePercent);
#endif
					pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
					pDrawText(pTextThis(), PosX, PosY - 6, LifeDisplay, 0, 0, (LPINT)1, 0);
				}

				pSetBlend(true);

				glColor4f(0.0, 0.0, 0.0, 0.5);
				pDrawBarForm((float)(PosX + 1), (float)(PosY + 1), LifeBarWidth + 4.0, 5.0, 0.0, 0);
				pGLSwitchBlend();

				glColor3f(0.2, 0.0, 0.0);
				pDrawBarForm((float)PosX, (float)PosY, LifeBarWidth + 4.0, 5.0, 0.0, 0);

				glColor3f(0.19607843, 0.039215688, 0.0);
				pDrawBarForm((float)(PosX + 2), (float)(PosY + 2), LifeBarWidth, 1.0, 0.0, 0);

#if _NEW_PARTY_SYSTEM_ == TRUE
				if( g_Party.PartyData[PartySlot].LifePercent > 10 )   
#else
				if( PartyMember.LifePercent > 10 )    
#endif
				{
					LifeProgress = 10;
				}
				else
				{
#if _NEW_PARTY_SYSTEM_ == TRUE
					LifeProgress = g_Party.PartyData[PartySlot].LifePercent;
#else
					LifeProgress = PartyMember.LifePercent;
#endif
				}

				glColor3f(0.98039216, 0.039215688, 0.0);

				for( int i = 0; i < LifeProgress; i++ )
				{
					pDrawBarForm((float)(i * 4 + PosX + 2), (float)(PosY + 2), 3.0, 2.0, 0.0, 0);
				}

				pGLSwitch();
			}
			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
		}
	}

#ifdef exDEBUG_CODE
			pSetBlend(true);
			pGLSwitchBlend();

			//int pHP = (Life * 100) / MaxLife;
			//pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2), (Wind * pHP/*100*/) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
#endif



//#if(NEW_QUEST_SYSTEM)
//	gQuestSystem.Draw();
//#endif
}

void ViewePortInfo::InitNewHpBar()
{
//#if _NEW_PARTY_DEV_ == FALSE
	SetOp((LPVOID)0x005B96E8, this->DrawPartyHP, ASM::CALL);
//#endif
}

void ViewePortInfo::PlayerTitle()
{
	VAngle Angle;
	int PosX, PosY;

	for(int i = 0; i < 400; i++)
	{
		lpViewObj lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if( !lpViewTarget || !lpViewTarget->m_Model.Unknown4 ) continue;

		if(lpViewTarget->m_Model.ObjectType == emPlayer)
		{

			bool Draw = false;

			for(int n = 0; n < MAX_VIEWPORT;n++)
			{
				if(lpViewTarget->aIndex == gObjUser.ExViewe[n].aIndex)
				{
					Draw = true;
					break;
				}
			}

			if(Draw == false)
			{
				continue;
			}

			int DevX = 20;
			int Wind = 70;
			int DevY = 0;

			Angle.X = lpViewTarget->m_Model.VecPosX;
			Angle.Y = lpViewTarget->m_Model.VecPosY;
			Angle.Z = lpViewTarget->m_Model.VecPosZ + lpViewTarget->m_Model.Unknown216.Z + 100.0;

			pGetPosFromAngle(&Angle, &PosX, &PosY);

			PosX -= (int)floor((double)Wind / (double)4.0);

			PosY -= 10 - HpResMode();

			pDrawGUI(ex_PLAYERTITLE_A, (float)PosX - 57, (float)PosY - 0, 48, 53);
		}
	}


	//pLoadImage("ExData\\Title\\a.tga", ex_PLAYERTITLE_A, 0x2601, 0x2900, 1, 0);
}

#endif