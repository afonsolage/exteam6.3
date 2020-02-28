// ViewportSkillState.cpp: implementation of the CViewportSkillState class.
//	GS	1.00.77	JPN	0xXXXXXXXX	- Completed
//	GS	1.00.90	JPN	0xXXXXXXXX	- Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ViewportSkillState.h"
#include "user.h"
#include "protocol.h"
#include "ItemAddOption.h"
#include "logproc.h"

CViewportSkillState g_ViewportSkillState;

CViewportSkillState::CViewportSkillState()
{

}

CViewportSkillState::~CViewportSkillState()
{

}

void CViewportSkillState::AddBuffEffect(LPOBJ lpObj, BYTE btEffectType, int iValue) //0063D4D0
{
	if(lpObj == NULL || btEffectType < 0)
	{
		return;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}

//	switch(btEffectType)
//	{
//	case 1:
//		{
//			lpObj->m_AttackSpeed += iValue;
//			lpObj->m_MagicSpeed += iValue;
//		}
//		break;
//	case 3:
//		{
//			lpObj->m_Defense += iValue;
//			lpObj->m_MagicDefense += iValue;
//		}
//		break;
//	case 4:
//		{
//			lpObj->AddLife += iValue;
//			GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), -2, 0, (lpObj->iMaxShield + lpObj->iAddShield));
//			GCReFillSend(lpObj->m_Index, lpObj->Life, -1, 0, lpObj->iShield);
//		}
//		break;
//	case 5:
//		{
//			lpObj->AddMana += iValue;
//			GCManaSend(lpObj->m_Index, (lpObj->MaxMana + lpObj->AddMana), -2, 0, (lpObj->MaxBP + lpObj->AddBP));
//			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
//		}
//		break;
//	case 21:
//		{
//			lpObj->m_iSoulBarrierDefense = iValue;
//		}
//		break;
//	case 22:
//		{
//			lpObj->m_MagicDefense += iValue;
//		}
//		break;
//	case 24:
//		{
//			lpObj->DamageReflect += iValue;
//		}
//		break;
//	case 26:
//		{
//			lpObj->m_AttackRating -= iValue;
//		}
//		break;
//	case 28:
//		{
//			lpObj->m_sSoulBarrierDuration = iValue;
//		}
//		break;
//		//Season 4 add-on
//	case 31: //good
//		{
//			lpObj->AddMana += (int)( (((float)(iValue) * (float)(lpObj->MaxMana))) / 100.0f);
//#ifdef DEBUG_CODE
//			LogAddC(2,"lpObj->AddMana: %d | lpObj->Mana: %d",lpObj->AddMana,lpObj->Mana);
//#endif
//			GCManaSend(lpObj->m_Index, (lpObj->MaxMana + lpObj->AddMana), -2, 0, (lpObj->MaxBP + lpObj->AddBP));
//			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
//		}
//		break;
//	case 32: //good :)
//		{
//			float loc2 = 0; //loc2
//
//			float loc3 = (((float)(40.0f) - (float)(iValue))/100.0f); //good
//
//			loc3 = (loc3 > 0.1f)?loc3:0.1f; //good
//			
//			loc2 = loc3 * lpObj->MaxLife; //good
//
//			lpObj->AddLife -= (int)((float)(loc2)); //good
//
//			lpObj->Life = ( (float)(lpObj->Life) < ( (float)(lpObj->AddLife) + (float)(lpObj->MaxLife) ) )?( (float)(lpObj->Life) ):( ( (float)(lpObj->AddLife) + (float)(lpObj->MaxLife) ) ); //good
//
//			GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), -2, 0, (lpObj->iMaxShield + lpObj->iAddShield)); //good
//			GCReFillSend(lpObj->m_Index, lpObj->Life, -1, 0, lpObj->iShield); //good
//		}
//		break;
//	case 33: //Wizardry Expansion ??
//		{
//			lpObj->m_MagicDamageMin += iValue;
//			lpObj->m_MagicDamageMax += iValue;
//		}
//		break;
//	case 57: //XMas Attack ??
//		{
//			lpObj->m_AttackDamageMaxLeft += iValue;
//			lpObj->m_AttackDamageMinLeft += iValue;
//			lpObj->m_AttackDamageMaxRight += iValue;
//			lpObj->m_AttackDamageMinRight += iValue;
//
//			lpObj->m_MagicDamageMin += iValue;
//			lpObj->m_MagicDamageMax += iValue;
//
//			lpObj->m_iSummonerBookSpellDamageMin += iValue;
//			lpObj->m_iSummonerBookSpellDamageMax += iValue;
//		}
//		break;
//	case 58: //XMas Defense??
//		{
//			lpObj->m_Defense += iValue;
//		}
//		break;
//	case ADD_OPTION_LEVEL_BP:
//		lpObj->AddBP += iValue * (lpObj->MLevel + lpObj->Level);
//		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
//        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
//		break;
//	case ADD_OPTION_LEVEL_SD:
//		lpObj->iAddShield += iValue * (lpObj->MLevel + lpObj->Level);
//		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
//        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
//		break;
//	case ADD_OPTION_BP:
//		lpObj->AddBP += iValue;
//		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
//        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
//		break;
//	case ADD_OPTION_SD:
//		lpObj->iAddShield += iValue;
//		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
//        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
//		break;
//	case ADD_OPTION_IGNOREDEFENSE:
//		lpObj->SetOpIgnoreDefense += iValue;
//		break;
//	case ADD_OPTION_SUCCESSFULBLOCKING:
//		lpObj->m_SuccessfulBlocking += iValue;
//		break;
//	case SUB_OPTION_SUCCESSFULBLOCKING:
//        lpObj->m_SuccessfulBlocking -= iValue;
//        if ( lpObj->m_SuccessfulBlocking < 0 )
//          lpObj->m_SuccessfulBlocking = 0;
//        break;
//	default:
//		return;
//	}
	switch( btEffectType )
	{
	case ADD_OPTION_SPEED:
		lpObj->m_AttackSpeed += iValue;
		lpObj->m_MagicSpeed += iValue;
		break;
	case ADD_OPTION_DEFENSE:
		lpObj->m_Defense += iValue;
		lpObj->m_MagicDefense += iValue;
		break;
	case ADD_OPTION_LIFE:
		lpObj->AddLife += iValue;
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFF, 0, lpObj->iShield);
		break;
	case ADD_OPTION_MANA:
		lpObj->AddMana += iValue;
		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFF, 0, lpObj->BP);
		break;
	case ADD_OPTION_STRENGTH:
		lpObj->AddStrength += iValue;
		break;
	case ADD_OPTION_DEXTERITY:
		lpObj->AddDexterity += iValue;
		break;
	case ADD_OPTION_VITALITY:
		lpObj->AddVitality += iValue;
		break;
	case ADD_OPTION_ENERGY:
		lpObj->AddEnergy += iValue;
		break;
	case ADD_OPTION_LEADERSHIP:
		lpObj->AddLeadership += iValue;
		break;
	case ADD_OPTION_WIZARD_DEFENSE:
        lpObj->m_iSoulBarrierDefense = iValue;
        break;
	case ADD_OPTION_MAGIC_DEFENSE:
		lpObj->m_MagicDefense += iValue;
		break;
	case ADD_OPTION_REFLECT:
		lpObj->DamageReflect += iValue;
		break;
	case ADD_OPTION_ATTACK_RATE:
		lpObj->m_AttackRating -= iValue;
		break;
	case ADD_OPTION_WIZARD_DEFENSE_DURATION:
		lpObj->m_sSoulBarrierDuration = iValue;
		break;
	case ADD_OPTION_CRITICAL_DAMAGE:
		lpObj->m_CriticalDamage += iValue;
		break;
	case ADD_OPTION_EXCELLENT_DAMAGE:
		lpObj->m_ExcelentDamage += iValue;
		break;
	case ADD_OPTION_BERSERKMANA:
        lpObj->AddMana += (int)(iValue * lpObj->MaxMana / 100.0);
        GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
        break;
	case ADD_OPTION_BERSERKLIFE:
		{
			float fAddLife = 0;
			float fPer = (((float)(40.0f) - (float)(iValue))/100.0f);

			fPer = (fPer > 0.1f)?fPer:0.1f;
			fAddLife = fPer * lpObj->MaxLife;

			lpObj->AddLife -= (int)((float)(fAddLife));
			lpObj->Life = ( (float)(lpObj->Life) < ( (float)(lpObj->AddLife) + (float)(lpObj->MaxLife) ) )?( (float)(lpObj->Life) ):( ( (float)(lpObj->AddLife) + (float)(lpObj->MaxLife) ) );

			GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
			GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
		}
		break;
	case ADD_OPTION_MAGICDAMAGEMIN:
		lpObj->m_MagicDamageMin += iValue;
		break;
	case ADD_OPTION_MAGICDAMAGEMAX:
		lpObj->m_MagicDamageMax += iValue;
		break;
	case ADD_OPTION_XMASATTACK:
		lpObj->m_AttackDamageMaxLeft += iValue;
		lpObj->m_AttackDamageMinLeft += iValue;
		lpObj->m_AttackDamageMaxRight += iValue;
		lpObj->m_AttackDamageMinRight += iValue;
		lpObj->m_MagicDamageMin += iValue;
		lpObj->m_MagicDamageMax += iValue;
		lpObj->m_iSummonerBookSpellDamageMin += iValue;
		lpObj->m_iSummonerBookSpellDamageMax += iValue;
		break;
	case ADD_OPTION_XMASDEFENSE:
		lpObj->m_Defense += iValue;
		break;
	case ADD_OPTION_LEVEL_BP:
		lpObj->AddBP += iValue * (lpObj->MLevel + lpObj->Level);
		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
		break;
	case ADD_OPTION_LEVEL_SD:
		lpObj->iAddShield += iValue * (lpObj->MLevel + lpObj->Level);
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
		break;
	case ADD_OPTION_BP:
		lpObj->AddBP += iValue;
		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
		break;
	case ADD_OPTION_SD:
		lpObj->iAddShield += iValue;
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
		break;
	case ADD_OPTION_IGNOREDEFENSE:
		lpObj->SetOpIgnoreDefense += iValue;
		break;
	case ADD_OPTION_SUCCESSFULBLOCKING:
		lpObj->m_SuccessfulBlocking += iValue;
		break;
	case SUB_OPTION_SUCCESSFULBLOCKING:
        lpObj->m_SuccessfulBlocking -= iValue;
        if ( lpObj->m_SuccessfulBlocking < 0 )
          lpObj->m_SuccessfulBlocking = 0;
        break;
	default:
		return;
	}
}

void CViewportSkillState::RemoveBuffEffect(LPOBJ lpObj, BYTE btEffectType, int iValue) //0063DBB0
{
	if(lpObj == NULL || btEffectType < 0)
	{
		return;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}

//	switch(btEffectType)
//	{
//	case 1:
//		{
//			lpObj->m_AttackSpeed -= iValue;
//			lpObj->m_MagicSpeed -= iValue;
//		}
//		break;
//	case 3:
//		{
//			lpObj->m_Defense -= iValue;
//			lpObj->m_MagicDefense -= iValue;
//		}
//		break;
//	case 4:
//		{
//			lpObj->AddLife -= iValue;
//			GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), -2, 0, (lpObj->iMaxShield + lpObj->iAddShield));
//			GCReFillSend(lpObj->m_Index, lpObj->Life, -1, 0, lpObj->iShield);
//		}
//		break;
//	case 5:
//		{
//			lpObj->AddMana -= iValue;
//			GCManaSend(lpObj->m_Index, (lpObj->MaxMana + lpObj->AddMana), -2, 0, (lpObj->MaxBP + lpObj->AddBP));
//			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
//		}
//		break;
//	case 21:
//		{
//			lpObj->m_iSoulBarrierDefense -= iValue;
//		}
//		break;
//	case 22:
//		{
//			lpObj->m_MagicDefense -= iValue;
//		}
//		break;
//	case 24:
//		{
//			lpObj->DamageReflect -= iValue;
//		}
//		break;
//	case 26:
//		{
//			lpObj->m_AttackRating += iValue;
//		}
//		break;
//	case 28:
//		{
//			lpObj->m_sSoulBarrierDuration = 0;
//		}
//		break;
//		//Season 4 add-on
//	case 31: //good
//		{
//			lpObj->AddMana -= (int)( (((iValue) * (lpObj->MaxMana))) / 100.0f);
//			lpObj->Mana = ( (lpObj->Mana) < ( (lpObj->AddMana) + (lpObj->MaxMana) ) )?( (lpObj->Mana) ):( ( (lpObj->AddMana) + (lpObj->MaxMana) ) ); //good
//#ifdef DEBUG_CODE
//			LogAddC(2,"lpObj->AddMana: %d | lpObj->Mana: %d",lpObj->AddMana,lpObj->Mana);
//#endif
//			GCManaSend(lpObj->m_Index, (lpObj->MaxMana + lpObj->AddMana), -2, 0, (lpObj->MaxBP + lpObj->AddBP));
//			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
//		}
//		break;
//	case 32: //good :)
//		{
//			float loc2 = 0; //loc2
//
//			float loc3 = (((float)(40.0f) - (float)(iValue))/100.0f); //good
//
//			loc3 = (loc3 > 0.1f)?loc3:0.1f; //good
//			
//			loc2 = loc3 * lpObj->MaxLife; //good
//
//			lpObj->AddLife += (int)(loc2); //good
//
//			GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), -2, 0, (lpObj->iMaxShield + lpObj->iAddShield)); //good
//			GCReFillSend(lpObj->m_Index, lpObj->Life, -1, 0, lpObj->iShield); //good
//		}
//		break;
//	case 33: //Wizardry Expansion ??
//		{
//			lpObj->m_MagicDamageMin -= iValue;
//			lpObj->m_MagicDamageMax -= iValue;
//		}
//		break;
//	case 57: //XMas Attack ??
//		{
//			lpObj->m_AttackDamageMaxLeft -= iValue;
//			lpObj->m_AttackDamageMinLeft -= iValue;
//			lpObj->m_AttackDamageMaxRight -= iValue;
//			lpObj->m_AttackDamageMinRight -= iValue;
//
//			lpObj->m_MagicDamageMin -= iValue;
//			lpObj->m_MagicDamageMax -= iValue;
//
//			lpObj->m_iSummonerBookSpellDamageMin -= iValue;
//			lpObj->m_iSummonerBookSpellDamageMax -= iValue;
//		}
//		break;
//	case 58: //XMas Defense??
//		{
//			lpObj->m_Defense -= iValue;
//		}
//		break;
//	case ADD_OPTION_LEVEL_BP:
//		lpObj->AddBP -= iValue * (lpObj->MLevel + lpObj->Level);
//		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
//        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
//		break;
//	case ADD_OPTION_LEVEL_SD:
//		lpObj->iAddShield -= iValue * (lpObj->MLevel + lpObj->Level);
//		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
//        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
//		break;
//	case ADD_OPTION_BP:
//		lpObj->AddBP -= iValue;
//		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
//        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
//		break;
//	case ADD_OPTION_SD:
//		lpObj->iAddShield -= iValue;
//		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
//        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
//		break;
//	case ADD_OPTION_IGNOREDEFENSE:
//		lpObj->SetOpIgnoreDefense -= iValue;
//		break;
//	case ADD_OPTION_SUCCESSFULBLOCKING:
//		lpObj->m_SuccessfulBlocking -= iValue;
//		break;
//	case SUB_OPTION_SUCCESSFULBLOCKING:
//        lpObj->m_SuccessfulBlocking += iValue;
//        break;
//	default:
//		return;
//	}
	switch( btEffectType )
	{
	case ADD_OPTION_SPEED:
		lpObj->m_AttackSpeed -= iValue;
		lpObj->m_MagicSpeed -= iValue;
		break;
	case ADD_OPTION_DEFENSE:
		lpObj->m_Defense -= iValue;
		lpObj->m_MagicDefense -= iValue;
		break;
	case ADD_OPTION_LIFE:
#ifdef FIX_DEATH_HP_BAF
		if (lpObj->AddLife < iValue)
		{

		}
		else
		{
			lpObj->AddLife -= iValue;
		}

#else
		lpObj->AddLife -= iValue;
#endif

		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
		break;
	case ADD_OPTION_MANA:
		lpObj->AddMana -= iValue;
		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
		break;
	case ADD_OPTION_STRENGTH:
		lpObj->AddStrength -= iValue;
		break;
	case ADD_OPTION_DEXTERITY:
		lpObj->AddDexterity -= iValue;
		break;
	case ADD_OPTION_VITALITY:
		lpObj->AddVitality -= iValue;
		break;
	case ADD_OPTION_ENERGY:
		lpObj->AddEnergy -= iValue;
		break;
	case ADD_OPTION_LEADERSHIP:
		lpObj->AddLeadership -= iValue;
		break;
	case ADD_OPTION_WIZARD_DEFENSE:
        lpObj->m_iSoulBarrierDefense -= iValue;
        break;
	case ADD_OPTION_MAGIC_DEFENSE:
		lpObj->m_MagicDefense -= iValue;
		break;
	case ADD_OPTION_REFLECT:
		lpObj->DamageReflect -= iValue;
		break;
	case ADD_OPTION_ATTACK_RATE:
		lpObj->m_AttackRating += iValue;
		break;
	case ADD_OPTION_WIZARD_DEFENSE_DURATION:
		lpObj->m_sSoulBarrierDuration = 0;
		break;
	case ADD_OPTION_CRITICAL_DAMAGE:
		lpObj->m_CriticalDamage -= iValue;
		break;
	case ADD_OPTION_EXCELLENT_DAMAGE:
		lpObj->m_ExcelentDamage -= iValue;
		break;
	case ADD_OPTION_BERSERKMANA:
        lpObj->AddMana -= (int)(iValue * lpObj->MaxMana / 100.0);
		lpObj->Mana = ((lpObj->AddMana + lpObj->MaxMana) <= lpObj->Mana) ? lpObj->Mana : (lpObj->AddMana + lpObj->MaxMana);

        GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
        break;
	case ADD_OPTION_BERSERKLIFE:
		{
			float fAddLife = 0;
			float fPer = (((float)(40.0f) - (float)(iValue))/100.0f);

			fPer = (fPer > 0.1f)?fPer:0.1f;
			fAddLife = fPer * lpObj->MaxLife;

			lpObj->AddLife += (int)((float)(fAddLife));
			lpObj->Life = ( (float)(lpObj->Life) < ( (float)(lpObj->AddLife) + (float)(lpObj->MaxLife) ) )?( (float)(lpObj->Life) ):( ( (float)(lpObj->AddLife) + (float)(lpObj->MaxLife) ) );

			GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
			GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
		}
		break;
	case ADD_OPTION_MAGICDAMAGEMIN:
		lpObj->m_MagicDamageMin -= iValue;
		break;
	case ADD_OPTION_MAGICDAMAGEMAX:
		lpObj->m_MagicDamageMax -= iValue;
		//lpObj->m_MPSkillOpt.Ukn[43] = 0; --  need to update this when ML structs done
		break;
	case ADD_OPTION_XMASATTACK:
		lpObj->m_AttackDamageMaxLeft -= iValue;
		lpObj->m_AttackDamageMinLeft -= iValue;
		lpObj->m_AttackDamageMaxRight -= iValue;
		lpObj->m_AttackDamageMinRight -= iValue;
		lpObj->m_MagicDamageMin -= iValue;
		lpObj->m_MagicDamageMax -= iValue;
		lpObj->m_iSummonerBookSpellDamageMin -= iValue;
		lpObj->m_iSummonerBookSpellDamageMax -= iValue;
		break;
	case ADD_OPTION_XMASDEFENSE:
		lpObj->m_Defense -= iValue;
		break;
	case ADD_OPTION_LEVEL_BP:
		lpObj->AddBP -= iValue * (lpObj->MLevel + lpObj->Level);
		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
		break;
	case ADD_OPTION_LEVEL_SD:
		lpObj->iAddShield -= iValue * (lpObj->MLevel + lpObj->Level);
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
		break;
	case ADD_OPTION_BP:
		lpObj->AddBP -= iValue;
		GCManaSend(lpObj->m_Index,(int)(lpObj->AddMana + lpObj->MaxMana),0xFEu,0,lpObj->AddBP + lpObj->MaxBP);
        GCManaSend(lpObj->m_Index, (int)lpObj->Mana, 0xFFu, 0, lpObj->BP);
		break;
	case ADD_OPTION_SD:
		lpObj->iAddShield -= iValue;
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife),0xFEu,0,lpObj->iAddShield + lpObj->iMaxShield);
        GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFFu, 0, lpObj->iShield);
		break;
	case ADD_OPTION_IGNOREDEFENSE:
		lpObj->SetOpIgnoreDefense -= iValue;
		break;
	case ADD_OPTION_SUCCESSFULBLOCKING:
		lpObj->m_SuccessfulBlocking -= iValue;
		break;
	case SUB_OPTION_SUCCESSFULBLOCKING:
        lpObj->m_SuccessfulBlocking += iValue;
        break;
	default:
		return;
	}
}

void CViewportSkillState::SetDamageType(LPOBJ lpObj, BYTE DamageType, int iDamageValue)
{
	if(DamageType <= 0)
	{
		return;
	}

	switch(DamageType)
	{
	case 18: //Reflect?
		this->ReflectDamage(lpObj, iDamageValue);
		break;
	case 19: //Poison?
		this->PoisonDamage(lpObj, iDamageValue);
		break;
	}
}

void CViewportSkillState::ReflectDamage(LPOBJ lpObj, int iDamageValue)
{
	int iDamage = 0;
	int iShieldDamage = 0;

	iDamage = iDamageValue;
	iShieldDamage = iDamage;

	if(lpObj->Live == false)
	{
		return;
	}

	if(lpObj->lpAttackObj != 0 && lpObj->Type == OBJ_USER && lpObj->lpAttackObj->Type == OBJ_USER)
	{
		iShieldDamage = 90 * iDamage / 100;
		iDamage -= iShieldDamage;

		if(lpObj->iShield-iShieldDamage > 0) //Shield Damage
		{
			lpObj->iShield -= iShieldDamage;
			lpObj->Life -= iDamage;
		}
		else
		{
			iDamage += iShieldDamage - lpObj->iShield;
			iShieldDamage = lpObj->iShield;
			lpObj->Life -= iDamage;
			lpObj->iShield = 0;
		}
	}
	else
	{
		iShieldDamage = 0;
		lpObj->Life -= iDamage;
	}

	if(lpObj->Life < 0.0f)
	{
		lpObj->Life = 0.0f;
	}

	if(lpObj->lpAttackObj != 0)
	{
		gObjLifeCheck(lpObj, lpObj->lpAttackObj, iDamage, 3, 0, 0, 0, iShieldDamage);
	}
}

void CViewportSkillState::PoisonDamage(LPOBJ lpObj, BYTE btDamageValue)
{
	int iDamage = 0;
	int iShieldDamage = 0;

	int loc4 = btDamageValue; //useless

	iDamage = (int)(loc4 * lpObj->Life / 100);

	iShieldDamage = iDamage;

	if(lpObj->lpAttackObj != 0 && lpObj->Type == OBJ_USER && lpObj->lpAttackObj->Type == OBJ_USER)
	{
		if(lpObj->iShield-iShieldDamage > 0) //Shield Damage
		{
			lpObj->iShield -= iShieldDamage;
			iDamage = 0;
		}
		else
		{
			iDamage = iShieldDamage - lpObj->iShield;
			iShieldDamage = lpObj->iShield;
			lpObj->Life -= iDamage;
			lpObj->iShield = 0;
		}
	}
	else
	{
		lpObj->Life -= iDamage;
		iShieldDamage = 0;
	}
	
	if(lpObj->Life < 0.0f)
	{
		lpObj->Life = 0.0f;
	}

	if(lpObj->lpAttackObj != 0)
	{
		gObjLifeCheck(lpObj, lpObj->lpAttackObj, iDamage, 2, 0, 0, 1, iShieldDamage);
	}
}

void CViewportSkillState::PrevBuffLastEffect(LPOBJ lpObj)
{
	if(lpObj == 0)
	{
		return;
	}

	int BuffCount = 0;

	for(int States = 0; States < MAX_STATE_COUNT; States++)
	{
		if(lpObj->m_BuffEffectState[States].btBuffIndex == NULL)
		{
			continue;
		}

		switch(lpObj->m_BuffEffectState[States].btEffectType1)
		{
		case ADD_OPTION_LIFE:
		case ADD_OPTION_MANA:
		case ADD_OPTION_STRENGTH:
		case ADD_OPTION_DEXTERITY:
		case ADD_OPTION_VITALITY:
		case ADD_OPTION_ENERGY:
		case ADD_OPTION_LEADERSHIP:
		case ADD_OPTION_REFLECT:
			BuffCount++;
			this->AddBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType1, lpObj->m_BuffEffectState[States].iValue1);
			break;
		default:
			break;
		}

		switch(lpObj->m_BuffEffectState[States].btEffectType2)
		{
		case ADD_OPTION_LIFE:
		case ADD_OPTION_MANA:
		case ADD_OPTION_STRENGTH:
		case ADD_OPTION_DEXTERITY:
		case ADD_OPTION_VITALITY:
		case ADD_OPTION_ENERGY:
		case ADD_OPTION_LEADERSHIP:
		case ADD_OPTION_REFLECT:
			BuffCount++;
			this->AddBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType2, lpObj->m_BuffEffectState[States].iValue2);
			break;
		default:
			break;
		}
	}
}

void CViewportSkillState::NextSetBuffLastEffect(LPOBJ lpObj)
{
	if(lpObj == 0)
	{
		return;
	}

	int BuffCount = 0;

	for(int States = 0; States < MAX_STATE_COUNT; States++)
	{
		if(lpObj->m_BuffEffectState[States].btBuffIndex == NULL)
		{
			continue;
		}

		switch(lpObj->m_BuffEffectState[States].btEffectType1)
		{
		case ADD_OPTION_LIFE:
		case ADD_OPTION_MANA:
		case ADD_OPTION_STRENGTH:
		case ADD_OPTION_DEXTERITY:
		case ADD_OPTION_VITALITY:
		case ADD_OPTION_ENERGY:
		case ADD_OPTION_LEADERSHIP:
		case ADD_OPTION_REFLECT:
			break;
		default:
			BuffCount++;
			this->AddBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType1, lpObj->m_BuffEffectState[States].iValue1);
			break;
		}

		switch(lpObj->m_BuffEffectState[States].btEffectType2)
		{
		case ADD_OPTION_LIFE:
		case ADD_OPTION_MANA:
		case ADD_OPTION_STRENGTH:
		case ADD_OPTION_DEXTERITY:
		case ADD_OPTION_VITALITY:
		case ADD_OPTION_ENERGY:
		case ADD_OPTION_LEADERSHIP:
		case ADD_OPTION_REFLECT:
			break;
		default:
			BuffCount++;
			this->AddBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType2, lpObj->m_BuffEffectState[States].iValue2);
			break;
		}
	}
}

void CViewportSkillState::CalCharacterRemoveBuffEffect(LPOBJ lpObj) //0063EA80 identical
{
	for(int States = 0; States < MAX_STATE_COUNT; States++)
	{
		if(lpObj->m_BuffEffectState[States].btBuffIndex == NULL)
		{
			continue;
		}

		this->RemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType1, lpObj->m_BuffEffectState[States].iValue1);
		this->RemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[States].btEffectType2, lpObj->m_BuffEffectState[States].iValue2);
	}
}