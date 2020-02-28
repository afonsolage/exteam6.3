//GameServer 1.00.90 JPN - Completed
#include "stdafx.h"
#include "ComboAttack.h"
#include "user.h"
#include "NewMasterLevelSkillTreeSystem.h"
#include "logproc.h"
#include "ComboCustom.h"

CComboAttack gComboAttack;

CComboAttack::CComboAttack()
{
	return;
}

CComboAttack::~CComboAttack()
{
	return;
}

int CComboAttack::GetSkillPos(int aIndex, int skillnum)
{
#if(DEV_COMBO_CUSTOM==TRUE)
	//LogAddC(2, "skillnum: %d", skillnum);
	int Result = g_ComboCustom.Main(aIndex, skillnum);
	if(Result != -2)
	{
		return Result;
	}
#endif

	if(		g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 326	//-> Cyclone
		||	g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 327	//-> Slash
		||	g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 328	//-> Falling Slash
		||	g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 329 )	//-> Lunge	
	{
		return 0;
	}
	else if(	g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 330
		||		g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 332 )	//-> Twisting
	{
		return 1;
	}
	else if( g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 333 
		|| g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 331 )	//-> Rageful Blow
	{
		return 1;
	}
	else if( g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 336 )	//-> Slash *
	{
		return 1;
	}
	else if( g_MasterSkillSystem.GetBaseMasterLevelSkill(skillnum) == 337 )	//-> Strike Of Destruction
	{
		return 1;
	}

	// ----
	switch(skillnum)
	{
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		{
			return 0;
		}
		break;
		// --
	case 41:
	case 42:
	case 43:
	case 232:
		{
			return 1;
		}
		break;
		// --
	default:
		{
			return -1;
		}
		break;
	}
}

BOOL CComboAttack::CheckCombo(int aIndex, int skillnum)
{
	LPOBJ lpObj = &gObj[aIndex];

#if(DEV_COMBO_CUSTOM==TRUE)
	if( lpObj->Class == CLASS_KNIGHT && lpObj->ComboSkillquestClear == true || 
		lpObj->Class == CLASS_WIZARD && lpObj->PlusStatQuestClear == true ||
		lpObj->Class == CLASS_ELF && lpObj->PlusStatQuestClear == true ||
		lpObj->Class == CLASS_MAGUMSA ||
		lpObj->Class == CLASS_DARKLORD ||
		lpObj->Class == CLASS_SUMMONER && lpObj->PlusStatQuestClear == true ||
		lpObj->Class == CLASS_MONK )
#else
	if ( lpObj->ComboSkillquestClear  != false )
#endif
	{
		int sp = this->GetSkillPos(aIndex,skillnum);

		if ( sp == 0 )
		{
			lpObj->comboSkill.ProgressIndex  = 0;
			lpObj->comboSkill.dwTime = GetTickCount() + 3000;
			lpObj->comboSkill.Skill[0]  = skillnum;
		}
		else if ( sp == 1 )
		{
			if ( lpObj->comboSkill.Skill[0]  == 0xFF )
			{
				lpObj->comboSkill.Init();
				return 0;
			}

			int Time =GetTickCount();

			if (lpObj->comboSkill.dwTime < GetTickCount() )
			{
				lpObj->comboSkill.Init();
				return 0;
			}

			if ( lpObj->comboSkill.ProgressIndex == 0 )
			{
				lpObj->comboSkill.ProgressIndex = 1;
				lpObj->comboSkill.dwTime = GetTickCount() + 3000;
				lpObj->comboSkill.Skill[1] = skillnum;
			}
			else if ( lpObj->comboSkill.Skill[1]  != skillnum )
			{
				lpObj->comboSkill.Init();
				return 1;
			}
			else
			{
				lpObj->comboSkill.Init();
			}
		}
		else
		{
			lpObj->comboSkill.ProgressIndex= -1;
			lpObj->comboSkill.dwTime = 0;
			lpObj->comboSkill.Skill[0] = -1;
		}
	}

	return 0;
}