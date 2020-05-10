#include "stdafx.h"
#include "VisualFix.h"
#include "TMemory.h"
#include "Protocol.h"
#include "Other.h"
#include "Defines.h"
#include "Console.h"
#include "User.h"
#include "Configs.h"
#include "ExLicense.h"
#include "InfoLog.h"
#include "ExText.h"
#include "Inter3.h"

cVisualFix gVisualFix;

void cVisualFix::InitVisualFix()
{
	this->aIndex = 0;
	this->AttackHP = 0;
	this->AttackSD = 0;
	this->Life = 0;
	this->SD = 0;
	this->Mana = 0;
	this->AG = 0;
	this->MaxLife = 0;
	this->MaxSD = 0;
	this->MaxMana = 0;
	this->MaxAG = 0;
	this->UpPoint = 0;
	this->PlayerKill = TRUE;
	this->Exp = 0;
	this->AttackRate = 0;
	this->DamageRate = 0;

	#if(DEV_INTERFASE_SEASON3)
	if (interCustom == 1 || interCustom == 2 || interCustom == 3)
	{
		InitInter3();
	}
#endif

	SetOp((LPVOID)oDrawDamageHP, (LPVOID)this->DrawDamageHP, ASM::CALL);
	SetOp((LPVOID)oDrawDamageSD, (LPVOID)this->DrawDamageSD, ASM::CALL);
	//SetOp((LPVOID)0x0064A779, (LPVOID)this->DrawFinalDamage, ASM::CALL);
	SetOp((LPVOID)0x0064AB1C, (LPVOID)this->DrawFinalDamage, ASM::CALL);
	SetOp((LPVOID)0x0064A779, (LPVOID)this->DrawFinalDamage, ASM::CALL);

	//rf dmg?
	
		
	//SetByte((LPVOID)0x00644178, 0x90);// 00644179 - nop
	//SetByte((LPVOID)0x00644179, 0x90);
	////SetOp((LPVOID)0x00510FEB, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//SetOp((LPVOID)0x0051100D, (LPVOID)this->DrawDamageHP, ASM::CALL);
	//SetOp((LPVOID)0x0051107B, (LPVOID)this->DrawDamageHP, ASM::CALL);	//per4i

	//DrawFinalDamage(int a1, int a2, int a3, float a4, char a5, char a6)

	SetOp((LPVOID)oDrawHp, (LPVOID)this->DrawHp, ASM::CALL);
	SetOp((LPVOID)oDrawMp, (LPVOID)this->DrawMp, ASM::CALL);
	SetOp((LPVOID)oDrawAg, (LPVOID)this->DrawAg, ASM::CALL);
	SetOp((LPVOID)oDrawSd, (LPVOID)this->DrawSd, ASM::CALL);

	SetOp((LPVOID)oDrawTabHP, (LPVOID)this->DrawTabHP, ASM::CALL);
	SetOp((LPVOID)oDrawTabMP, (LPVOID)this->DrawTabMP, ASM::CALL);
	SetOp((LPVOID)oDrawTabSD, (LPVOID)this->DrawTabSD, ASM::CALL);
	SetOp((LPVOID)oDrawTabAG, (LPVOID)this->DrawTabAG, ASM::CALL);

	SetOp((LPVOID)oInfoHp, (LPVOID)this->InfoHp, ASM::CALL);
	SetOp((LPVOID)oInfoHpM, (LPVOID)this->InfoHp, ASM::CALL);
	SetOp((LPVOID)oInfoMp, (LPVOID)this->InfoMp, ASM::CALL);
	SetOp((LPVOID)oInfoMpM, (LPVOID)this->InfoMp, ASM::CALL);

	SetOp((LPVOID)oInfoPoint, (LPVOID)this->InfoPoint, ASM::CALL);

	SetOp((LPVOID)oDrawCircleHp, (LPVOID)this->DrawCircle, ASM::CALL);	// - hp
	SetOp((LPVOID)oDrawCircleHp2, (LPVOID)this->DrawCircle, ASM::CALL);	// - hp
	SetOp((LPVOID)oDrawCircleMp, (LPVOID)this->DrawCircle, ASM::CALL);	// - mp
	SetOp((LPVOID)oDrawCircleAg, (LPVOID)this->DrawCircle, ASM::CALL);	// - ag
	SetOp((LPVOID)oDrawCircleSd, (LPVOID)this->DrawCircle, ASM::CALL);	// - sd

	//SetOp((LPVOID)0x00595BB0, (LPVOID)this->CalculateAttackRate, ASM::CALL);
	//SetOp((LPVOID)0x00595B78, (LPVOID)this->CalculateDamageRate, ASM::CALL);

	//SetRange((LPVOID)0x007801AC, 9, ASM::NOP);
	//SetOp((LPVOID)0x007801AC, (LPVOID)this->GetAttackRate, ASM::CALL);
	//SetByte((LPVOID)0x007801B1, 0x89);
	//SetByte((LPVOID)(0x007801B1 + 1), 0xC6);

	//SetRange((LPVOID)0x00780231, 10, ASM::NOP);
	//SetOp((LPVOID)0x00780231, (LPVOID)this->GetAttackRate, ASM::CALL);
	//SetByte((LPVOID)0x00780236, 0x89);
	//SetByte((LPVOID)(0x00780236 + 1), 0xC6);

	//SetRange((LPVOID)0x00780180, 10, ASM::NOP);
	//SetOp((LPVOID)0x00780180, (LPVOID)this->GetDamageRate, ASM::CALL);
	//SetByte((LPVOID)0x00780185, 0x89);
	//SetByte((LPVOID)(0x00780185 + 1), 0xC6);

	//SetRange((LPVOID)0x00780205, 10, ASM::NOP);
	//SetOp((LPVOID)0x00780205, (LPVOID)this->GetDamageRate, ASM::CALL);
	//SetByte((LPVOID)0x0078020A, 0x89);
	//SetByte((LPVOID)(0x0078020A + 1), 0xC6);

}


void cVisualFix::RecvIndex(PMSG_JOINRESULT * Data)
{
	this->aIndex = MAKE_NUMBERW(Data->NumberH,Data->NumberL);
	this->PlayerKill = FALSE;
}

void cVisualFix::RecvDamage(PMSG_ATTACKRESULT * Data)
{
	this->AttackHP = Data->AttackDamage;
	this->AttackSD = Data->iShieldDamage;
	short tIndex =  MAKE_NUMBERW(Data->NumberH,Data->NumberL);
	if (this->aIndex == tIndex)
	{
		this->Life -= this->AttackHP;
		this->SD -= this->AttackSD;
		if(0 > this->Life)
		{
			this->Life = 0;
		}
	}
}

void cVisualFix::RecvHPSD(PMSG_REFILL * Data)
{
	if(Data->IPos == 0xFF)
	{
		this->Life = Data->Life;
		this->SD = Data->Shield;
	}
	else if(Data->IPos == 0xFE)
	{
		this->MaxLife = Data->Life;
		this->MaxSD = Data->Shield;
	}
	if(this->Life > this->MaxLife)
	{
		this->Life = this->MaxLife;
	}
	if(this->SD > this->MaxSD)
	{
		this->SD = this->MaxSD;
	}
	if(this->PlayerKill == TRUE)
	{
		this->Life = 0;
		this->SD = 0;
	}
}

void cVisualFix::RecvMPAG(PMSG_MANASEND * Data)
{
	if(Data->IPos == 0xFF)
	{
		if(Data->Mana < 0)
		{
			return;
		}

		this->Mana = Data->Mana;
		this->AG = Data->BP;
	}
	else if(Data->IPos == 0xFE)
	{
		this->MaxMana = Data->Mana;
		this->MaxAG = Data->BP;
	}
	if(this->Mana > this->MaxMana)
	{
		this->Mana = this->MaxMana;
	}
	if(this->AG > this->MaxAG)
	{
		this->AG = this->MaxAG;
	}
}

void cVisualFix::RecvUpPoint(PMSG_CHARMAPJOINRESULT * Data)
{
	this->UpPoint = Data->UpPoint;
	gObjUser.Reset = Data->Reset;
	gObjUser.GReset = Data->GReset;

	this->Life = Data->dwLife;
	this->MaxLife = Data->dwMaxLife;
	this->Mana = Data->dwMana;
	this->MaxMana = Data->dwMaxMana;
	this->SD = Data->dwShield;
	this->MaxSD = Data->dwMaxShield;
	this->AG = Data->dwBP;
	this->MaxAG = Data->dwMaxBP;

	gObjUser.Money = Data->Money;
}

void cVisualFix::RecvUpLevel(PMSG_LEVELUP * Data)
{
	this->UpPoint = Data->exUpPoint;
	this->MaxLife = Data->exMaxLife;
	this->MaxMana = Data->exMaxMana;
	this->MaxSD = Data->exMaxShield;
	this->MaxAG = Data->exMaxAG;
}

void cVisualFix::RecvDownPoint(PMSG_LVPOINTADDRESULT * Data)
{
	if(Data->ResultType != 0)
	{
		this->UpPoint--;
	}
}

void cVisualFix::RecvExp(PMSG_KILLPLAYER * Data)
{
	//gConsole.Output(cGREY,"DAMGE: %d",Data->ExDamage);
	this->FinalDamage = Data->ExDamage;
	this->Exp = Data->Exp;
}

void cVisualFix::RecvMasterExp(PMSG_KILLPLAYER_EXT * Data)
{
	this->Exp = MAKE_NUMBERDW(Data->ExpH,Data->ExpL);
	this->FinalDamage = Data->ExDamage;
}

void cVisualFix::RecvRespawn()
{
	this->PlayerKill = FALSE;
	this->Life = this->MaxLife;
	this->SD = this->MaxSD;
}

void cVisualFix::RecvKilledObject(PMSG_DIEPLAYER * Data)
{
	short tIndex =  MAKE_NUMBERW(Data->NumberH,Data->NumberL);
	if(this->aIndex == tIndex)
	{
		this->Life = 0;
		this->SD = 0;
		this->PlayerKill = TRUE;
	}


	short iKillerIndex =  MAKE_NUMBERW(Data->KillerNumberH, Data->KillerNumberL);

	if(pGameIndex == iKillerIndex)
	{
		return;
	}

	for(int i = 0; i < 400; i++)
	{
		lpViewObj lpObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if( !lpObj || !lpObj->m_Model.Visible )
		{
			continue;
		}

		if(lpObj->m_Model.ObjectType != emPlayer) 
		{
			continue;
		}

		if(lpObj->aIndex == iKillerIndex && pGameIndex == tIndex)
		{
#if(CUSTOM_EX_CHAT)
			g_InfoLog.Output("Killers", "Killers", "[KILL] [%s]", lpObj->Name);
#endif
			return;
		}
	}
}

void cVisualFix::DrawDamageHP(int a1, int a2, int a3, float a4, char a5, char a6)
{
	pDrawDamage(a1, gVisualFix.AttackHP, a3, a4, a5, a6);
}

void cVisualFix::DrawFinalDamage(int a1, int a2, int a3, float a4, char a5, char a6)
{
	if( g_ExLicense.CheckUser(eExUB::Local)   ||  
		g_ExLicense.CheckUser(eExUB::SILVER1) ||
	    g_ExLicense.CheckUser(eExUB::SILVER2) )
		//gObjUser.Class == CLASS_MONK )
	{
		//pDrawDamage(a1, gVisualFix.AttackHP, a3, a4, a5, a6);
	}
	else
	{
		pDrawDamage(a1, gVisualFix.FinalDamage, a3, a4, a5, a6);
	}
}

void cVisualFix::DrawDamageSD(int a1, int a2, int a3, float a4, char a5, char a6)
{
	pDrawDamage(a1, gVisualFix.AttackSD, a3, a4, a5, a6);
}

void cVisualFix::DrawHp(float a1, float a2, int a3, float a4)
{
	if(gVisualFix.Life > gVisualFix.MaxLife)
	{
		gVisualFix.Life = gVisualFix.MaxLife;
	}
	else if(gVisualFix.Life < 0)
	{
		gVisualFix.Life = 0;
	}

	pDrawBar(a1, a2, gVisualFix.Life, 0.9);
}

void cVisualFix::DrawMp(float a1, float a2, int a3, float a4)
{
	if(gVisualFix.Mana > gVisualFix.MaxMana)
	{
		gVisualFix.Mana = gVisualFix.MaxMana;
	}
	else if(gVisualFix.Mana < 0)
	{
		gVisualFix.Mana = 0;
		//return;
	}

	pDrawBar(a1, a2, gVisualFix.Mana, 0.9);//450.00 - centr	462 - def
}

void cVisualFix::DrawAg(float a1, float a2, int a3, float a4)
{
	if(gVisualFix.AG > gVisualFix.MaxAG)
	{
		gVisualFix.AG = gVisualFix.MaxAG;
	}
	else if(gVisualFix.AG < 0)
	{
		gVisualFix.AG = 0;
	}

	pDrawBar(a1, a2, gVisualFix.AG, 0.9);
}

void cVisualFix::DrawSd(float a1, float a2, int a3, float a4)
{
	if(gVisualFix.SD > gVisualFix.MaxSD)
	{
		gVisualFix.SD = gVisualFix.MaxSD;
	}
	else if(gVisualFix.SD < 0)
	{
		gVisualFix.SD = 0;
	}

	pDrawBar(a1+5, a2, gVisualFix.SD, 0.9);
}

void cVisualFix::DrawTabHP(signed int a1, signed int a2, LPCSTR lpMultiByteStr)
{
	sprintf(gVisualFix.LifeTab, g_ExText.GetText(80), gVisualFix.Life,gVisualFix.MaxLife);
	pDrawTab(a1,a2,gVisualFix.LifeTab);
}

void cVisualFix::DrawTabMP(signed int a1, signed int a2, LPCSTR lpMultiByteStr)
{
	sprintf(gVisualFix.ManaTab, g_ExText.GetText(81), gVisualFix.Mana,gVisualFix.MaxMana);
	pDrawTab(a1,a2,gVisualFix.ManaTab);
}

void cVisualFix::DrawTabSD(signed int a1, signed int a2, LPCSTR lpMultiByteStr)
{
	sprintf(gVisualFix.SDTab, g_ExText.GetText(82), gVisualFix.SD,gVisualFix.MaxSD);
	pDrawTab(a1,a2,gVisualFix.SDTab);
}

void cVisualFix::DrawTabAG(signed int a1, signed int a2, LPCSTR lpMultiByteStr)
{
	sprintf(gVisualFix.AGTab, g_ExText.GetText(83), gVisualFix.AG,gVisualFix.MaxAG);
	pDrawTab(a1,a2,gVisualFix.AGTab);
}

void cVisualFix::InfoHp(int a1, const char *a2, ...)
{
	pInfo(a1,a2,gVisualFix.Life,gVisualFix.MaxLife);
}

void cVisualFix::InfoMp(int a1, const char *a2, ...)
{
	pInfo(a1,a2,gVisualFix.Mana,gVisualFix.MaxMana);
}

void cVisualFix::InfoPoint(int a1, const char *a2, ...)
{
	pInfo(a1,a2,gVisualFix.UpPoint);
}

void cVisualFix::DrawCircle(DWORD ModelID, float Arg2, float Arg3, float Arg4, float Arg5, float Arg6, float Arg7, float Arg8, float Arg9, int Arg10, int Arg11, int Arg12)
{
    float Height    = 39.0f;
    float PosY		= 432.0f;
    float LifeFill  = (float)(gVisualFix.MaxLife - gVisualFix.Life) / (float)gVisualFix.MaxLife;
	float ManaFill  = (float)(gVisualFix.MaxMana - gVisualFix.Mana) / (float)gVisualFix.MaxMana;
	float AgFill	= (float)(gVisualFix.MaxAG - gVisualFix.AG) / (float)gVisualFix.MaxAG;
	float SdFill	= (float)(gVisualFix.MaxSD - gVisualFix.SD) / (float)gVisualFix.MaxSD;
    // ----
    if( ModelID == ModelID_HP || ModelID == ModelID_HP2 )
    {
        float StartY        = LifeFill * Height + PosY;
        float StartHeight   = Height - LifeFill * Height;
        float SourceY       = LifeFill * Height / 64.0f;
        float SouceHeight   = (1.0 - LifeFill) * Height / 64.0f;
        return pDrawCircle(ModelID, Arg2, StartY, Arg4, StartHeight, 0, SourceY, Arg8, SouceHeight, 1, 1, 0);
    }
    // ----
    if( ModelID == ModelID_MP )
    {
        float StartY        = ManaFill * Height + PosY;
        float StartHeight   = Height - ManaFill * Height;
        float SourceY       = ManaFill * Height / 64.0f;
        float SouceHeight   = (1.0 - ManaFill) * Height / 64.0f;
        return pDrawCircle(ModelID, Arg2, StartY, Arg4, StartHeight, 0, SourceY, Arg8, SouceHeight, 1, 1, 0);
    }
    // ----
	if( ModelID == ModelID_AG )
	{
        float StartY        = AgFill * Height + PosY;
        float StartHeight   = Height - AgFill * Height;
        float SourceY       = AgFill * Height / 64.0f;
        float SouceHeight   = (1.0 - AgFill) * Height / 64.0f;
        return pDrawCircle(ModelID, Arg2, StartY, Arg4, StartHeight, 0, SourceY, Arg8, SouceHeight, 1, 1, 0);
	}
	// ----
	if( ModelID == ModelID_SD )
	{
        float StartY        = SdFill * Height + PosY;
        float StartHeight   = Height - SdFill * Height;
        float SourceY       = SdFill * Height / 64.0f;
        float SouceHeight   = (1.0 - SdFill) * Height / 64.0f;
        return pDrawCircle(ModelID, Arg2, StartY, Arg4, StartHeight, 0, SourceY, Arg8, SouceHeight, 1, 1, 0);
	}
	// ----
    pDrawCircle(ModelID, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12);
}

//void cVisualFix::CalculateAttackRate(lpCharObj lpUser, LPVOID EDX)
//{
//	float AttackRate	= 0.0f;
//	int Dexterity		= lpUser->Dexterity + lpUser->AddDexterity;
//	// ----
//	switch(lpUser->Class & 7)
//	{
//	case DarkWizard:
//	case DarkLord:
//		AttackRate = (float)(lpUser->Level * 3 + Dexterity * 4);
//		break;
//	case DarkKnight:
//		AttackRate = (float)(lpUser->Level * 3 + (Dexterity * 45) / 10);
//		break;
//	case Elf:
//		AttackRate = (float)(lpUser->Level * 3 + (Dexterity * 6) / 10);
//		break;
//	case MagicGladiator:
//	case Summoner:
//		AttackRate = (float)(lpUser->Level * 3 + (Dexterity * 35) / 10);
//		break;
//	case Monk:
//		AttackRate = (float)(lpUser->Level * 2.6f + (Dexterity * 36) / 10);
//		break;
//	}
//	// ----
//	gVisualFix.AttackRate	= (int)AttackRate;
//	lpUser->AttackRate		= (WORD)gVisualFix.AttackRate;
//}
//
//void cVisualFix::CalculateDamageRate(lpCharObj lpUser, LPVOID EDX)
//{
//	WORD Strength	= lpUser->Strength + lpUser->AddStrength;
//	WORD Dexterity	= lpUser->Dexterity + lpUser->AddDexterity;
//	WORD Leadership	= lpUser->Leadership + lpUser->AddLeadership;
//	// ----
//	switch(lpUser->Class & 7)
//	{
//	case DarkLord:
//		gVisualFix.DamageRate = (Leadership / 10) + (Strength / 6) + (5 * Dexterity / 2) + (5 * lpUser->Level);
//		break;
//	case Monk:
//		gVisualFix.DamageRate = (Strength / 6) + (5 * Dexterity / 4) + (3 * lpUser->Level);
//		break;
//	default:
//		gVisualFix.DamageRate = ((int)Strength >> 2) + (3 * Dexterity / 2) + (5 * lpUser->Level);
//		break;
//	}
//	// ----
//	pUpdateUserStat(pUserStat(), gVisualFix.DamageRate, 177);
//	gVisualFix.DamageRate	+= *(DWORD*)0x986C1C4;
//	lpUser->DamageRate		= (WORD)gVisualFix.DamageRate;
//}
//
//int cVisualFix::GetAttackRate()
//{
//	return gVisualFix.AttackRate;
//}
//
//int cVisualFix::GetDamageRate()
//{
//	return gVisualFix.DamageRate;
//}


void cVisualFix::GCVisualInit()
{
	SetByte((LPVOID)0x00644178, 0x90);
	SetByte((LPVOID)0x00644179, 0x90);
	SetOp((LPVOID)0x0051100D, (LPVOID)this->DrawDamageHP, ASM::CALL);
	SetOp((LPVOID)0x0051107B, (LPVOID)this->DrawDamageHP, ASM::CALL);	//per4i

	//SetOp((LPVOID)0x00510FEB, (LPVOID)this->DrawDamageHP, ASM::CALL);

}