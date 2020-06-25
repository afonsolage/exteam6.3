//GameServer 1.00.56 JPN - Completed -> Siege
//GameServer 1.00.67 JPN - Completed -> Common & Siege
//GameServer 1.00.77 JPN - Completed -> Common & Siege
//GameServer 1.00.90 JPN - Completed -> Common & Siege
#include "stdafx.h"
#include "ObjCalCharacter.h"
#include "Gamemain.h"
#include "DarkSpirit.h"
#include "ItemAddOption.h"
#include "..\common\SetItemOption.h"
#include "LogProc.h"
#include "ViewportSkillState.h" //Season 3.0 add-on
#include "SocketOption.h" //Season 4.0 add-on
#include "Configs.h"
#include "SystemOfRage.h"
#include "LuckyItem.h"
#include "WinQuestSystem.h"
#include "ExclusiveOptions.h"
#include "ExLicense.h"
#include "MaxPower.h"
#if(GRAND_HERO_DEV)
	#include "GrandHeroSystem.h"
#endif
#include "Brotherhood.h"
#include "BMQuest.h"
#include "Marriage.h"
//#include "BuffEffect.h"
#include "BuffManager.h"
#include "DungeonSiege.h"
#include "Achievements.h"
#include "PremiumSystemEx.h"
#include "WingsDamage.h"
#include "Voter.h"
#include "BalanceSystem.h"
#ifdef CALCULATOR_MANAGER
#include "CalculatorManager.h"
#endif
#include "StatsAdvance.h"
#include "PetEx.h"
#include "CustomSystem.h"

void gObjCalCharacter(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int Strength = 0;
	int Dexterity = 0;
	int Vitality = 0;
	int Energy = 0;
	CItem * Right = &lpObj->pInventory[0];
	CItem * Left  = &lpObj->pInventory[1];
	CItem * Gloves = &lpObj->pInventory[5];
	CItem * Amulet = &lpObj->pInventory[9];
	CItem * Helper = &lpObj->pInventory[8];
	lpObj->HaveWeaponInHand = true;

	if ( Right->IsItem() == FALSE && Left->IsItem() == FALSE )
	{
		lpObj->HaveWeaponInHand = false;
	}
	else if ( Left->IsItem() == FALSE && Right->m_Type == ITEMGET(4,15) )
	{
		lpObj->HaveWeaponInHand = false;
	}
	else if ( Right->IsItem() == FALSE )
	{
		int iType = Left->m_Type / MAX_SUBTYPE_ITEMS;

		if ( Left->m_Type == ITEMGET(4,7) )
		{
			lpObj->HaveWeaponInHand = false;
		}
		else if ( iType == 6 )
		{
			lpObj->HaveWeaponInHand = false;
		}
	}

	lpObj->AddLife = 0;
	lpObj->AddMana = 0;
	lpObj->MonsterDieGetMoney = 0;
	lpObj->MonsterDieGetLife = 0;
	lpObj->MonsterDieGetMana = 0;
	lpObj->DamageReflect = 0;
	lpObj->DamageMinus = 0;
	lpObj->SkillLongSpearChange = false;

	lpObj->RecoveryHp = 0;
	lpObj->RecoverySd = 0;
	lpObj->RecoveryMp = 0;
	lpObj->RecoveryAg = 0;



	if ( lpObj->m_iItemEffectValidTime > 0 )
	{
		g_ItemAddOption.PrevSetItemLastEffectForHallowin(lpObj); //clear previous halloween effect (apply again later)
	}

	int iItemIndex;
	BOOL bIsChangeItem;

	for ( iItemIndex=0; iItemIndex<MAX_PLAYER_EQUIPMENT;iItemIndex++)
	{
		if ( lpObj->pInventory[iItemIndex].IsItem() != FALSE )
		{
			lpObj->pInventory[iItemIndex].m_IsValidItem = true;
		}
	}

	do
	{
		lpObj->SetOpAddMaxAttackDamage = 0;
		lpObj->SetOpAddMinAttackDamage = 0;
		lpObj->SetOpAddDamage = 0;
		lpObj->SetOpIncAGValue = 0;
		lpObj->SetOpAddCriticalDamageSuccessRate = 0;
		lpObj->SetOpAddCriticalDamage = 0;
		lpObj->SetOpAddExDamageSuccessRate = 0;
		lpObj->SetOpAddExDamage = 0;
		lpObj->SetOpAddSkillAttack = 0;
		lpObj->AddStrength = 0;
		lpObj->AddDexterity = 0;
		lpObj->AddVitality = 0;
		lpObj->AddEnergy = 0;
		lpObj->AddLeadership = 0; //season4 add-on (wz fix o/)
		lpObj->AddBP = 0;
		lpObj->iAddShield = 0;
		lpObj->SetOpAddAttackDamage = 0;
		lpObj->SetOpAddDefence = 0;
		lpObj->SetOpAddMagicPower = 0;
		lpObj->SetOpAddDefenceRate = 0;
		lpObj->SetOpIgnoreDefense = 0;
		lpObj->SetOpDoubleDamage = 0;
		lpObj->SetOpTwoHandSwordImproveDamage = 0;
		lpObj->SetOpImproveSuccessAttackRate = 0;
		lpObj->SetOpReflectionDamage = 0;
		lpObj->SetOpImproveSheldDefence = 0;
		lpObj->SetOpDecreaseAG = 0;
		lpObj->SetOpImproveItemDropRate = 0;
		lpObj->IsFullSetItem = false;

		memset(lpObj->m_AddResistance, 0, sizeof(lpObj->m_AddResistance));

		bIsChangeItem = FALSE;

		g_ItemAddOption.PrevSetItemLastEffectForCashShop(lpObj); //Clear Active CashShop Attributes (Leap Effect most in any case)
		g_ViewportSkillState.PrevBuffLastEffect(lpObj); //Clear BuffEffect Attributes

		gObjCalcSetItemStat(lpObj);
		gObjCalcSetItemOption(lpObj);

		for (iItemIndex=0;iItemIndex<MAX_PLAYER_EQUIPMENT;iItemIndex++)
		{
			if ( lpObj->pInventory[iItemIndex].IsItem() != FALSE && lpObj->pInventory[iItemIndex].m_IsValidItem != false )
			{
				if ( gObjValidItem( lpObj, &lpObj->pInventory[iItemIndex], iItemIndex) != FALSE )
				{
					lpObj->pInventory[iItemIndex].m_IsValidItem = true;
				}
				else
				{
					lpObj->pInventory[iItemIndex].m_IsValidItem  = false;
					g_ViewportSkillState.CalCharacterRemoveBuffEffect(lpObj); //season4 add-on
					bIsChangeItem = TRUE;
				}
			}
		}
	}
	while ( bIsChangeItem != FALSE );

	if(g_CustomSystem.IsRage())
	{
		gSystemOfRage.CalcStats(aIndex);
	}

	Strength = lpObj->Strength + lpObj->AddStrength;
	Dexterity = lpObj->Dexterity + lpObj->AddDexterity;
	Vitality = lpObj->Vitality + lpObj->AddVitality;
	Energy = lpObj->Energy + lpObj->AddEnergy; //loc5

	if(g_bAbilityDebug == 1) //season3 add-on for GM
	{
		char szTemp[256];
		
		sprintf(szTemp, "Strength: %d,%d    Dexterity: %d,%d", lpObj->Strength, lpObj->AddStrength, lpObj->Dexterity, lpObj->AddDexterity);
		GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);

		memset(szTemp, 0, 256);

		sprintf(szTemp, "Vitality: %d,%d    Energy: %d,%d", lpObj->Vitality, lpObj->AddVitality, lpObj->Energy, lpObj->AddEnergy);
		GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);

		//season4 add-on
		memset(szTemp, 0, 256);

		sprintf(szTemp, "Leadership: %d,%d", lpObj->Leadership, lpObj->AddLeadership);
		GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
	}
	if ( lpObj->Class == CLASS_ELF )
	{
		if ( (Right->m_Type >= ITEMGET(4,8) && Right->m_Type < ITEMGET(4,15) ) ||
			 (Left->m_Type >= ITEMGET(4,0) && Left->m_Type < ITEMGET(4,7)) ||
			  Right->m_Type == ITEMGET(4,16) ||
			  Left->m_Type == ITEMGET(4,20) ||
			  Left->m_Type == ITEMGET(4,21) || Left->m_Type == ITEMGET(4,22) || //loc7 Item 4,22 Add-on Season 2.5 GS-CS 56 (Albatross Fix)
			  Left->m_Type == ITEMGET(4,23) || //season4 add-on
			  Right->m_Type == ITEMGET(4,18) ||
			  Right->m_Type == ITEMGET(4,19) ||
			  Left->m_Type == ITEMGET(4,17) )
		{
			if ( (Right->IsItem() != FALSE && Right->m_IsValidItem == false) || (Left->IsItem() != FALSE && Left->m_IsValidItem == false) )
			{
				//int DamageMax_Bow_StrDexRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_Bow_StrDexRight",4,"..\\Data\\ExData\\Character.ini");
				//int DamageMin_Bow_StrDexRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_Bow_StrDexRight",7,"..\\Data\\ExData\\Character.ini");
				//int DamageMax_Bow_StrDexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_Bow_StrDexLeft",4,"..\\Data\\ExData\\Character.ini");
				//int DamageMin_Bow_StrDexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_Bow_StrDexLeft",7,"..\\Data\\ExData\\Character.ini");
				lpObj->m_AttackDamageMinRight = (Dexterity + Strength ) / ExConfig.Character.ELFDamageMin_Bow_StrDexRight;	//7
				lpObj->m_AttackDamageMaxRight = (Dexterity + Strength ) / ExConfig.Character.ELFDamageMax_Bow_StrDexRight;	//4
				lpObj->m_AttackDamageMinLeft = (Dexterity + Strength ) / ExConfig.Character.ELFDamageMin_Bow_StrDexLeft;		//7
				lpObj->m_AttackDamageMaxLeft = (Dexterity + Strength ) / ExConfig.Character.ELFDamageMax_Bow_StrDexLeft;		//4
			}
			else
			{
				//int DamageMax_NoBow_StrRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_StrRight",8,"..\\Data\\ExData\\Character.ini");
				//int DamageMax_NoBow_DexRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_DexRight",4,"..\\Data\\ExData\\Character.ini");
				//int DamageMin_NoBow_StrRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_StrRight",14,"..\\Data\\ExData\\Character.ini");
				//int DamageMin_NoBow_DexRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_DexRight",7,"..\\Data\\ExData\\Character.ini");

				//int DamageMax_NoBow_StrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_StrLeft",8,"..\\Data\\ExData\\Character.ini");
				//int DamageMax_NoBow_DexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_DexLeft",4,"..\\Data\\ExData\\Character.ini");
				//int DamageMin_NoBow_StrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_StrLeft",14,"..\\Data\\ExData\\Character.ini");
				//int DamageMin_NoBow_DexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_DexLeft",7,"..\\Data\\ExData\\Character.ini");

				lpObj->m_AttackDamageMinRight = (Dexterity / ExConfig.Character.ELFDamageMin_NoBow_DexRight) + (Strength / ExConfig.Character.ELFDamageMin_NoBow_StrRight);
				lpObj->m_AttackDamageMaxRight = (Dexterity / ExConfig.Character.ELFDamageMax_NoBow_DexRight) + (Strength / ExConfig.Character.ELFDamageMax_NoBow_StrRight );
				lpObj->m_AttackDamageMinLeft = (Dexterity / ExConfig.Character.ELFDamageMin_NoBow_DexLeft) + (Strength / ExConfig.Character.ELFDamageMin_NoBow_StrLeft);
				lpObj->m_AttackDamageMaxLeft = (Dexterity / ExConfig.Character.ELFDamageMax_NoBow_DexLeft) + (Strength / ExConfig.Character.ELFDamageMax_NoBow_StrLeft );
			}
		}
		else
		{
			//int DamageMax_DexStrRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_DexStrRight",4,"..\\Data\\ExData\\Character.ini");
			//int DamageMin_DexStrRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_DexStrRight",7,"..\\Data\\ExData\\Character.ini");
			//int DamageMax_DexStrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_DexStrLeft",4,"..\\Data\\ExData\\Character.ini");
			//int DamageMin_DexStrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_DexStrLeft",7,"..\\Data\\ExData\\Character.ini");

			lpObj->m_AttackDamageMinRight = (Dexterity + Strength) / ExConfig.Character.ELFDamageMin_DexStrRight;	// 7
			lpObj->m_AttackDamageMaxRight = (Dexterity + Strength) / ExConfig.Character.ELFDamageMax_DexStrRight;	// 4
			lpObj->m_AttackDamageMinLeft = (Dexterity + Strength) / ExConfig.Character.ELFDamageMin_DexStrLeft;	// 7
			lpObj->m_AttackDamageMaxLeft = (Dexterity + Strength) / ExConfig.Character.ELFDamageMax_DexStrLeft;	// 4
		}

		

#ifdef CALCULATOR_MANAGER
		if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			lpObj->m_AttackDamageMinRight = (lpObj->m_AttackDamageMinRight * CalculatorManager.FE_MinDamagePercent) / 100;
			lpObj->m_AttackDamageMinLeft = (lpObj->m_AttackDamageMinLeft * CalculatorManager.FE_MinDamagePercent) / 100;

			lpObj->m_AttackDamageMaxRight = (lpObj->m_AttackDamageMaxRight * CalculatorManager.FE_MaxDamagePercent) / 100;
			lpObj->m_AttackDamageMaxLeft = (lpObj->m_AttackDamageMaxLeft * CalculatorManager.FE_MaxDamagePercent) / 100;
		}
#endif
	}
	else if ( lpObj->Class == CLASS_KNIGHT )
	{
		//int DamageMax_StrRight = GetPrivateProfileInt("Dark_Knight","DamageMax_StrRight",4,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrRight = GetPrivateProfileInt("Dark_Knight","DamageMin_StrRight",6,"..\\Data\\ExData\\Character.ini");
		//int DamageMax_StrLeft = GetPrivateProfileInt("Dark_Knight","DamageMax_StrLeft",4,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrLeft = GetPrivateProfileInt("Dark_Knight","DamageMin_StrLeft",6,"..\\Data\\ExData\\Character.ini");

		lpObj->m_AttackDamageMinRight = Strength / ExConfig.Character.DKDamageMin_StrRight;	// 6
		lpObj->m_AttackDamageMaxRight = Strength / ExConfig.Character.DKDamageMax_StrRight;	// 4
		lpObj->m_AttackDamageMinLeft = Strength / ExConfig.Character.DKDamageMin_StrLeft;	// 6
		lpObj->m_AttackDamageMaxLeft = Strength / ExConfig.Character.DKDamageMax_StrLeft;	// 4

#ifdef CALCULATOR_MANAGER
		if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			lpObj->m_AttackDamageMinRight = (lpObj->m_AttackDamageMinRight * CalculatorManager.DK_MinDamagePercent) / 100;
			lpObj->m_AttackDamageMinLeft = (lpObj->m_AttackDamageMinLeft * CalculatorManager.DK_MinDamagePercent) / 100;

			lpObj->m_AttackDamageMaxRight = (lpObj->m_AttackDamageMaxRight * CalculatorManager.DK_MaxDamagePercent) / 100;
			lpObj->m_AttackDamageMaxLeft = (lpObj->m_AttackDamageMaxLeft * CalculatorManager.DK_MaxDamagePercent) / 100;
		}
#endif
	}
	else if (lpObj->Class == CLASS_MAGUMSA )
	{
		//int DamageMax_StrRight = GetPrivateProfileInt("Magic_Gladiator","DamageMax_StrRight",4,"..\\Data\\ExData\\Character.ini");
		//int DamageMax_EneRight = GetPrivateProfileInt("Magic_Gladiator","DamageMax_EneRight",8,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrRight = GetPrivateProfileInt("Magic_Gladiator","DamageMin_StrRight",6,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_EneRight = GetPrivateProfileInt("Magic_Gladiator","DamageMin_EneRight",12,"..\\Data\\ExData\\Character.ini");

		//int DamageMax_StrLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMax_StrLeft",4,"..\\Data\\ExData\\Character.ini");
		//int DamageMax_EneLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMax_EneLeft",8,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMin_StrLeft",6,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_EneLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMin_EneLeft",12,"..\\Data\\ExData\\Character.ini");

		lpObj->m_AttackDamageMinRight = (Strength / ExConfig.Character.MGDamageMin_StrRight) + (Energy / ExConfig.Character.MGDamageMin_EneRight);
		lpObj->m_AttackDamageMaxRight = (Strength / ExConfig.Character.MGDamageMax_StrRight) + (Energy / ExConfig.Character.MGDamageMax_EneRight);
		lpObj->m_AttackDamageMinLeft = (Strength / ExConfig.Character.MGDamageMin_StrLeft) + (Energy / ExConfig.Character.MGDamageMin_EneLeft);
		lpObj->m_AttackDamageMaxLeft = (Strength / ExConfig.Character.MGDamageMax_StrLeft) + (Energy / ExConfig.Character.MGDamageMax_EneLeft);


#ifdef CALCULATOR_MANAGER
		if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			lpObj->m_AttackDamageMinRight = (lpObj->m_AttackDamageMinRight * CalculatorManager.MG_MinDamagePercent) / 100;
			lpObj->m_AttackDamageMinLeft = (lpObj->m_AttackDamageMinLeft * CalculatorManager.MG_MinDamagePercent) / 100;

			lpObj->m_AttackDamageMaxRight = (lpObj->m_AttackDamageMaxRight * CalculatorManager.MG_MaxDamagePercent) / 100;
			lpObj->m_AttackDamageMaxLeft = (lpObj->m_AttackDamageMaxLeft * CalculatorManager.MG_MaxDamagePercent) / 100;
		}
#endif
	}
	else if ( lpObj->Class == CLASS_DARKLORD )
	{
		//int DamageMax_StrRight = GetPrivateProfileInt("Dark_Lord","DamageMax_StrRight",5,"..\\Data\\ExData\\Character.ini");
		//int DamageMax_EneRight = GetPrivateProfileInt("Dark_Lord","DamageMax_EneRight",10,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrRight = GetPrivateProfileInt("Dark_Lord","DamageMin_StrRight",7,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_EneRight = GetPrivateProfileInt("Dark_Lord","DamageMin_EneRight",14,"..\\Data\\ExData\\Character.ini");

		//int DamageMax_StrLeft = GetPrivateProfileInt("Dark_Lord","DamageMax_StrLeft",5,"..\\Data\\ExData\\Character.ini");
		//int DamageMax_EneLeft = GetPrivateProfileInt("Dark_Lord","DamageMax_EneLeft",10,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrLeft = GetPrivateProfileInt("Dark_Lord","DamageMin_StrLeft",7,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_EneLeft = GetPrivateProfileInt("Dark_Lord","DamageMin_EneLeft",14,"..\\Data\\ExData\\Character.ini");

		lpObj->m_AttackDamageMinRight = (Strength / ExConfig.Character.DLDamageMin_StrRight) + (Energy / ExConfig.Character.DLDamageMin_EneRight);
		lpObj->m_AttackDamageMaxRight = (Strength / ExConfig.Character.DLDamageMax_StrRight) + (Energy / ExConfig.Character.DLDamageMax_EneRight);
		lpObj->m_AttackDamageMinLeft = (Strength / ExConfig.Character.DLDamageMin_StrLeft) + (Energy / ExConfig.Character.DLDamageMin_EneLeft);
		lpObj->m_AttackDamageMaxLeft = (Strength / ExConfig.Character.DLDamageMax_StrLeft) + (Energy / ExConfig.Character.DLDamageMax_EneLeft);


#ifdef CALCULATOR_MANAGER
		if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			lpObj->m_AttackDamageMinRight = (lpObj->m_AttackDamageMinRight * CalculatorManager.DL_MinDamagePercent) / 100;
			lpObj->m_AttackDamageMinLeft = (lpObj->m_AttackDamageMinLeft * CalculatorManager.DL_MinDamagePercent) / 100;

			lpObj->m_AttackDamageMaxRight = (lpObj->m_AttackDamageMaxRight * CalculatorManager.DL_MaxDamagePercent) / 100;
			lpObj->m_AttackDamageMaxLeft = (lpObj->m_AttackDamageMaxLeft * CalculatorManager.DL_MaxDamagePercent) / 100;
		}
#endif
	}
	else if ( lpObj->Class == CLASS_SUMMONER )
	{
		//int DamageMax_StrRight = GetPrivateProfileInt("Summoner","DamageMax_StrRight",4,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrRight = GetPrivateProfileInt("Summoner","DamageMin_StrRight",7,"..\\Data\\ExData\\Character.ini");
		//int DamageMax_StrLeft = GetPrivateProfileInt("Summoner","DamageMax_StrLeft",4,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrLeft = GetPrivateProfileInt("Summoner","DamageMin_StrLeft",7,"..\\Data\\ExData\\Character.ini");

		lpObj->m_AttackDamageMinRight = ((Strength + Dexterity) / ExConfig.Character.SUMDamageMin_StrRight);	// 7
		lpObj->m_AttackDamageMaxRight = ((Strength + Dexterity) / ExConfig.Character.SUMDamageMax_StrRight);	// 4
		lpObj->m_AttackDamageMinLeft = ((Strength + Dexterity) / ExConfig.Character.SUMDamageMin_StrLeft);	// 7
		lpObj->m_AttackDamageMaxLeft = ((Strength + Dexterity) / ExConfig.Character.SUMDamageMax_StrLeft);	// 4
	}
	else if (lpObj->Class == CLASS_WIZARD)
	{
		//int DamageMax_StrRight = GetPrivateProfileInt("Dark_Wizard","DamageMax_StrRight",4,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrRight = GetPrivateProfileInt("Dark_Wizard","DamageMin_StrRight",6,"..\\Data\\ExData\\Character.ini");
		//int DamageMax_StrLeft = GetPrivateProfileInt("Dark_Wizard","DamageMax_StrLeft",4,"..\\Data\\ExData\\Character.ini");
		//int DamageMin_StrLeft = GetPrivateProfileInt("Dark_Wizard","DamageMin_StrLeft",6,"..\\Data\\ExData\\Character.ini");

		lpObj->m_AttackDamageMinRight = (Strength / ExConfig.Character.DWDamageMin_StrRight);
		lpObj->m_AttackDamageMaxRight = (Strength / ExConfig.Character.DWDamageMax_StrRight);
		lpObj->m_AttackDamageMinLeft = (Strength / ExConfig.Character.DWDamageMin_StrLeft);
		lpObj->m_AttackDamageMaxLeft = (Strength / ExConfig.Character.DWDamageMax_StrLeft);
	}
#ifdef MONK
	else if( lpObj->Class == CLASS_MONK )
	{
		lpObj->m_AttackDamageMinRight	= Vitality / ExConfig.Character.RFDamageMin_VitRight /*15*/ + Strength / ExConfig.Character.RFDamageMin_StrRight;
		lpObj->m_AttackDamageMaxRight	= Vitality / ExConfig.Character.RFDamageMax_VitRight + Strength / ExConfig.Character.RFDamageMax_StrRight;
		lpObj->m_AttackDamageMinLeft	= Vitality / ExConfig.Character.RFDamageMin_VitLeft + Strength / ExConfig.Character.RFDamageMin_StrLeft;
		lpObj->m_AttackDamageMaxLeft	= Vitality / ExConfig.Character.RFDamageMax_VitLeft + Strength / ExConfig.Character.RFDamageMax_StrLeft;

#ifdef CALCULATOR_MANAGER
		if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			lpObj->m_AttackDamageMinRight = (lpObj->m_AttackDamageMinRight * CalculatorManager.RF_DamageMinPercent) / 100;
			lpObj->m_AttackDamageMinLeft = (lpObj->m_AttackDamageMinLeft * CalculatorManager.RF_DamageMinPercent) / 100;

			lpObj->m_AttackDamageMaxRight = (lpObj->m_AttackDamageMaxRight * CalculatorManager.RF_DamageMaxPercent) / 100;
			lpObj->m_AttackDamageMaxLeft = (lpObj->m_AttackDamageMaxLeft * CalculatorManager.RF_DamageMaxPercent) / 100;
		}
#endif

	}
#endif
	else
	{
		lpObj->m_AttackDamageMinRight = (Strength / 8);
		lpObj->m_AttackDamageMaxRight = (Strength / 4);
		lpObj->m_AttackDamageMinLeft = (Strength / 8);
		lpObj->m_AttackDamageMaxLeft = (Strength / 4);
	}
	if(lpObj->Class == CLASS_KNIGHT || lpObj->Class == CLASS_ELF || lpObj->Class == CLASS_DARKLORD)
	{
		lpObj->m_AttackDamageMaxRight += lpObj->m_MPSkillOpt.MpsMaxAttackInc;
		lpObj->m_AttackDamageMaxLeft += lpObj->m_MPSkillOpt.MpsMaxAttackInc;
		lpObj->m_AttackDamageMinRight += lpObj->m_MPSkillOpt.MpsMinAttackInc;
		lpObj->m_AttackDamageMinLeft += lpObj->m_MPSkillOpt.MpsMinAttackInc;
	}

	lpObj->pInventory[7].PlusSpecial(&lpObj->m_AttackDamageMinRight, 80);
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_AttackDamageMaxRight, 80);
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_AttackDamageMinLeft, 80);
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_AttackDamageMaxLeft, 80);

	int AddLeadership = 0;

	if ( lpObj->pInventory[7].IsItem() != FALSE && lpObj->pInventory[7].m_IsValidItem != false)
	{
		AddLeadership += lpObj->pInventory[7].m_Leadership;
	}

	if ( Right->m_Type != -1 )
	{
		if ( Right->m_IsValidItem != false )
		{
			if ( Right->m_Type >= ITEMGET(5,0) && Right->m_Type <= ITEMGET(6,0) )
			{
				lpObj->m_AttackDamageMinRight += Right->m_DamageMin / 2; //check?
				lpObj->m_AttackDamageMaxRight += Right->m_DamageMax / 2; //check?
			}
			else
			{
				lpObj->m_AttackDamageMinRight += Right->m_DamageMin;
				lpObj->m_AttackDamageMaxRight += Right->m_DamageMax;
			}
		}

		if ( lpObj->pInventory[0].m_SkillChange != FALSE )
		{
			lpObj->SkillLongSpearChange = true;
		}

		lpObj->pInventory[0].PlusSpecial(&lpObj->m_AttackDamageMinRight, 80);
		lpObj->pInventory[0].PlusSpecial(&lpObj->m_AttackDamageMaxRight, 80);
	}
		
	if ( Left->m_Type != -1 )
	{
		if ( Left->m_IsValidItem != false)
		{
			lpObj->m_AttackDamageMinLeft += Left->m_DamageMin;
			lpObj->m_AttackDamageMaxLeft += Left->m_DamageMax;
		}

		lpObj->pInventory[1].PlusSpecial(&lpObj->m_AttackDamageMinLeft, 80);
		lpObj->pInventory[1].PlusSpecial(&lpObj->m_AttackDamageMaxLeft, 80);
	}

	lpObj->m_CriticalDamage = 0;
	lpObj->m_ExcelentDamage = 0;

	lpObj->pInventory[0].PlusSpecial(&lpObj->m_CriticalDamage, 84);
	lpObj->pInventory[1].PlusSpecial(&lpObj->m_CriticalDamage, 84);
	lpObj->pInventory[2].PlusSpecial(&lpObj->m_CriticalDamage, 84);
	lpObj->pInventory[3].PlusSpecial(&lpObj->m_CriticalDamage, 84);
	lpObj->pInventory[4].PlusSpecial(&lpObj->m_CriticalDamage, 84);
	lpObj->pInventory[5].PlusSpecial(&lpObj->m_CriticalDamage, 84);
	lpObj->pInventory[6].PlusSpecial(&lpObj->m_CriticalDamage, 84);
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_CriticalDamage, 84);



	lpObj->m_MagicDamageMin = Energy / 9;
	lpObj->m_MagicDamageMax = Energy / 4;



	if(lpObj->Class == CLASS_SUMMONER) //stronger!!!
	{
		//int MagicDamageMax = GetPrivateProfileInt("Summoner","MagicDamageMax",4,"..\\Data\\ExData\\Character.ini");
		//int MagicDamageMin = GetPrivateProfileInt("Summoner","MagicDamageMin",9,"..\\Data\\ExData\\Character.ini");

		lpObj->m_MagicDamageMin = Energy / ExConfig.Character.SUMMagicDamageMin;	// 9
		lpObj->m_MagicDamageMax = Energy / ExConfig.Character.SUMMagicDamageMax;	// 4

		lpObj->m_iSummonerBookSpellDamageMin = Energy / ExConfig.Character.SUMMagicDamageMin;	// Energy / 9
		lpObj->m_iSummonerBookSpellDamageMax = Energy / ExConfig.Character.SUMMagicDamageMax;	// (Energy / 4) + 0.015

		
#ifdef CALCULATOR_MANAGER
		if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			lpObj->m_MagicDamageMin = (lpObj->m_MagicDamageMin * CalculatorManager.SUM_MinimumWizardryDamagePercent) / 100;
			lpObj->m_MagicDamageMax = (lpObj->m_MagicDamageMax * CalculatorManager.SUM_MaximumWizardryDamagePercent) / 100;

			lpObj->m_iSummonerBookSpellDamageMin = (lpObj->m_iSummonerBookSpellDamageMin * CalculatorManager.SUM_MinimumCurseDamagePercent) / 100;
			lpObj->m_iSummonerBookSpellDamageMax = (lpObj->m_iSummonerBookSpellDamageMax * CalculatorManager.SUM_MaximumCurseDamagePercent) / 100;
		}
#endif

		lpObj->m_MagicDamageMax += lpObj->m_MPSkillOpt.MpsMaxMagicDamage;
		lpObj->m_MagicDamageMin += lpObj->m_MPSkillOpt.MpsMinMagicDamage;
	}

	if(lpObj->Class == CLASS_MAGUMSA) //season4 add-on
	{
		//int MagicDamageMax = GetPrivateProfileInt("Magic_Gladiator","MagicDamageMax",4,"..\\Data\\ExData\\Character.ini");
		//int MagicDamageMin = GetPrivateProfileInt("Magic_Gladiator","MagicDamageMin",9,"..\\Data\\ExData\\Character.ini");

		lpObj->m_MagicDamageMin = Energy / ExConfig.Character.MGMagicDamageMin;
		lpObj->m_MagicDamageMax = Energy / ExConfig.Character.MGMagicDamageMax;

		
#ifdef CALCULATOR_MANAGER
		if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			lpObj->m_MagicDamageMin = (lpObj->m_MagicDamageMin * CalculatorManager.MG_MinWizDamagePercent) / 100;
			lpObj->m_MagicDamageMax = (lpObj->m_MagicDamageMax * CalculatorManager.MG_MaxWizDamagePercent) / 100;

		}
#endif

		lpObj->m_MagicDamageMax += lpObj->m_MPSkillOpt.MpsMagicMastery;
		lpObj->m_MagicDamageMin += lpObj->m_MPSkillOpt.MpsMagicMastery;
	}

	if(lpObj->Class == CLASS_WIZARD) //season4 add-on
	{
		//int MagicDamageMax = GetPrivateProfileInt("Dark_Wizard","MagicDamageMax",4,"..\\Data\\ExData\\Character.ini");
		//int MagicDamageMin = GetPrivateProfileInt("Dark_Wizard","MagicDamageMin",9,"..\\Data\\ExData\\Character.ini");

		lpObj->m_MagicDamageMin = Energy / ExConfig.Character.DWMagicDamageMin;
		lpObj->m_MagicDamageMax = Energy / ExConfig.Character.DWMagicDamageMax;


#ifdef CALCULATOR_MANAGER
		if (g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ConflictNoCustom) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			lpObj->m_MagicDamageMin = (lpObj->m_MagicDamageMin * CalculatorManager.DW_MinWizDamagePercent) / 100;
			lpObj->m_MagicDamageMax = (lpObj->m_MagicDamageMax * CalculatorManager.DW_MaxWizDamagePercent) / 100;
		}
#endif

		lpObj->m_MagicDamageMax += lpObj->m_MPSkillOpt.MpsMaxMagicDamage;
		lpObj->m_MagicDamageMin += lpObj->m_MPSkillOpt.MpsMinMagicDamage;
		lpObj->m_MagicDamageMax += lpObj->m_MPSkillOpt.MpsMagicMastery;
		lpObj->m_MagicDamageMin += lpObj->m_MPSkillOpt.MpsMagicMastery;
	}

	lpObj->pInventory[7].PlusSpecial(&lpObj->m_MagicDamageMin, 81);
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_MagicDamageMax, 81);

	lpObj->pInventory[7].PlusSpecial(&lpObj->m_iSummonerBookSpellDamageMin, 113); //summoner wings
	lpObj->pInventory[7].PlusSpecial(&lpObj->m_iSummonerBookSpellDamageMax, 113); //summoner wings

	if ( Right->m_Type != -1 )
	{
		if ( lpObj->pInventory[0].m_Type == ITEMGET(0,31) ||
			 lpObj->pInventory[0].m_Type == ITEMGET(0,21) ||
			 lpObj->pInventory[0].m_Type == ITEMGET(0,23) ||
			 lpObj->pInventory[0].m_Type == ITEMGET(0,25) ||
			 lpObj->pInventory[0].m_Type == ITEMGET(0,28)) //season4 add-on 
		{
			lpObj->pInventory[0].PlusSpecial(&lpObj->m_MagicDamageMin, 80);
			lpObj->pInventory[0].PlusSpecial(&lpObj->m_MagicDamageMax, 80);
		}
		else
		{
			lpObj->pInventory[0].PlusSpecial(&lpObj->m_MagicDamageMin, 81);
			lpObj->pInventory[0].PlusSpecial(&lpObj->m_MagicDamageMax, 81);
		}
	}

	if ( Left->m_Type != -1 ) //season3 add-on
	{
		lpObj->pInventory[1].PlusSpecial(&lpObj->m_iSummonerBookSpellDamageMin, 113); //summoner book
		lpObj->pInventory[1].PlusSpecial(&lpObj->m_iSummonerBookSpellDamageMax, 113); //summoner book
	}

	lpObj->m_AttackRating = (Strength + Dexterity) / 2;
	lpObj->m_AttackRating += lpObj->pInventory[5].ItemDefense();

	if ( lpObj->Class == CLASS_ELF )
	{
		lpObj->m_AttackSpeed = Dexterity / 50;
		lpObj->m_MagicSpeed = Dexterity / 50;
	}
	else if ( lpObj->Class == CLASS_KNIGHT || lpObj->Class == CLASS_MAGUMSA)
	{
		lpObj->m_AttackSpeed = Dexterity / 15;
		lpObj->m_MagicSpeed = Dexterity / 20;
	}
	else if ( lpObj->Class == CLASS_DARKLORD )
	{
		lpObj->m_AttackSpeed = Dexterity / 10;
		lpObj->m_MagicSpeed = Dexterity / 10;
	}
	else if ( lpObj->Class == CLASS_SUMMONER ) //strong!
	{
		lpObj->m_AttackSpeed = Dexterity / 20;
		lpObj->m_MagicSpeed = Dexterity / 20;
	}
#ifdef MONK
	else if( lpObj->Class == CLASS_MONK )
	{
		lpObj->m_AttackSpeed	= Dexterity / 9;
		lpObj->m_MagicSpeed		= Dexterity / 9;
	}
#endif
	else
	{
		lpObj->m_AttackSpeed = Dexterity / 20;
		lpObj->m_MagicSpeed = Dexterity / 10;
	}


	bool bRight = false;
	bool bLeft = false;

	if ( Right->m_Type != ITEMGET(4,7) && Right->m_Type != ITEMGET(4,15) && Right->m_Type >= ITEMGET(0,0) && Right->m_Type < ITEMGET(6,0) )
	{
		if ( Right->m_IsValidItem != false && Right->m_Durability > 0.0f)
		{
			bRight = true;
		}
	}

	if ( Left->m_Type != ITEMGET(4,7) && Left->m_Type != ITEMGET(4,15) && Left->m_Type >= ITEMGET(0,0) && Left->m_Type < ITEMGET(6,0) )
	{
		if ( Left->m_IsValidItem != false && Left->m_Durability > 0.0f)
		{
			bLeft = true;
		}
	}

	if ( bRight != false && bLeft != false )
	{
		lpObj->m_AttackSpeed += (Right->m_AttackSpeed + Left->m_AttackSpeed)/2;
		lpObj->m_MagicSpeed += (Right->m_AttackSpeed + Left->m_AttackSpeed)/2;
	}
	else if ( bRight!= false )
	{
		lpObj->m_AttackSpeed += Right->m_AttackSpeed;
		lpObj->m_MagicSpeed += Right->m_AttackSpeed;
	}
	else if ( bLeft != false )
	{
		lpObj->m_AttackSpeed += Left->m_AttackSpeed;
		lpObj->m_MagicSpeed += Left->m_AttackSpeed;
	}

	if ( Gloves->m_Type != -1 )
	{
		if ( Gloves->m_IsValidItem != false )
		{
			lpObj->m_AttackSpeed += Gloves->m_AttackSpeed;
			lpObj->m_MagicSpeed += Gloves->m_AttackSpeed;
		}
	}

	if ( Helper->m_Type != -1 )
	{
		if ( Helper->m_IsValidItem != false )
		{
			lpObj->m_AttackSpeed += Helper->m_AttackSpeed;
			lpObj->m_MagicSpeed += Helper->m_AttackSpeed;
		}
	}

	if ( Amulet->m_Type != -1 )
	{
		if ( Amulet->m_IsValidItem != false )
		{
			lpObj->m_AttackSpeed += Amulet->m_AttackSpeed;
			lpObj->m_MagicSpeed += Amulet->m_AttackSpeed;
		}
	}

	// Wizard Ring effect
	if ( (lpObj->pInventory[10].IsItem() == TRUE && lpObj->pInventory[10].m_Type == ITEMGET(13,20) && lpObj->pInventory[10].m_Level == 0 && lpObj->pInventory[10].m_Durability > 0.0f ) || (lpObj->pInventory[11].IsItem() == TRUE && lpObj->pInventory[11].m_Type == ITEMGET(13,20) && lpObj->pInventory[11].m_Level == 0 && lpObj->pInventory[11].m_Durability > 0.0f ) )
	{
		lpObj->m_AttackDamageMinRight += lpObj->m_AttackDamageMinRight * 10 / 100;
		lpObj->m_AttackDamageMaxRight += lpObj->m_AttackDamageMaxRight * 10 / 100;
		lpObj->m_AttackDamageMinLeft += lpObj->m_AttackDamageMinLeft * 10 / 100;
		lpObj->m_AttackDamageMaxLeft += lpObj->m_AttackDamageMaxLeft * 10 / 100;
		lpObj->m_MagicDamageMin += lpObj->m_MagicDamageMin * 10 / 100;
		lpObj->m_MagicDamageMax += lpObj->m_MagicDamageMax * 10 / 100;
		lpObj->m_AttackSpeed += 10;
		lpObj->m_MagicSpeed += 10;
	}

	if ( lpObj->Class == CLASS_WIZARD )
	{
		lpObj->m_DetectSpeedHackTime = (int)(gAttackSpeedTimeLimit - (lpObj->m_MagicSpeed*2 * gDecTimePerAttackSpeed) );
	}
	else
	{
		lpObj->m_DetectSpeedHackTime = (int)(gAttackSpeedTimeLimit - (lpObj->m_AttackSpeed * gDecTimePerAttackSpeed) );
	}

	if ( lpObj->m_DetectSpeedHackTime < gMinimumAttackSpeedTime )
	{
		lpObj->m_DetectSpeedHackTime = gMinimumAttackSpeedTime;
	}


	if ( lpObj->Class == CLASS_ELF )
	{
		//int SuccessfulBlocking = GetPrivateProfileInt("Fairy_Elf","SuccessfulBlocking",4,"..\\Data\\ExData\\Character.ini");
		lpObj->m_SuccessfulBlocking = Dexterity / ExConfig.Character.ELFSuccessfulBlocking;	// 4
	}
	else if ( lpObj->Class == CLASS_DARKLORD )
	{
		//int SuccessfulBlocking = GetPrivateProfileInt("Dark_Lord","SuccessfulBlocking",7,"..\\Data\\ExData\\Character.ini");
		lpObj->m_SuccessfulBlocking = Dexterity / ExConfig.Character.DLSuccessfulBlocking;	// 7
	}
	else if ( lpObj->Class == CLASS_SUMMONER ) //Not much but its alot
	{
		//int SuccessfulBlocking = GetPrivateProfileInt("Summoner","SuccessfulBlocking",4,"..\\Data\\ExData\\Character.ini");
		lpObj->m_SuccessfulBlocking = Dexterity / ExConfig.Character.SUMSuccessfulBlocking;	 // 4
	}
	else if ( lpObj->Class == CLASS_WIZARD )
	{
		//int SuccessfulBlocking = GetPrivateProfileInt("Dark_Wizard","SuccessfulBlocking",3,"..\\Data\\ExData\\Character.ini");
		lpObj->m_SuccessfulBlocking = Dexterity / ExConfig.Character.DWSuccessfulBlocking;	 // 3
	}
	else if ( lpObj->Class == CLASS_KNIGHT )
	{
		//int SuccessfulBlocking = GetPrivateProfileInt("Dark_Knight","SuccessfulBlocking",3,"..\\Data\\ExData\\Character.ini");
		lpObj->m_SuccessfulBlocking = Dexterity / ExConfig.Character.DKSuccessfulBlocking;	 // 3
	}
	else if ( lpObj->Class == CLASS_MAGUMSA )
	{
		//int SuccessfulBlocking = GetPrivateProfileInt("Magic_Gladiator","SuccessfulBlocking",3,"..\\Data\\ExData\\Character.ini");
		lpObj->m_SuccessfulBlocking = Dexterity / ExConfig.Character.MGSuccessfulBlocking;	 // 3
	}
#ifdef MONK
	else if( lpObj->Class == CLASS_MONK )
	{
		lpObj->m_SuccessfulBlocking = Dexterity / ExConfig.Character.RFSuccessfulBlocking;
	}
#endif
	else
	{
		lpObj->m_SuccessfulBlocking = Dexterity / 3;
	}
	if ( Left->m_Type != -1 )
	{
		if ( Left->m_IsValidItem != false )
		{
			lpObj->m_SuccessfulBlocking += Left->m_SuccessfulBlocking;
			lpObj->pInventory[1].PlusSpecial(&lpObj->m_SuccessfulBlocking, 82);
		}
	}

	bool Success = true;

	if ( lpObj->Class == CLASS_MAGUMSA )
	{
		for ( int j=3;j<=6;j++)
		{
			if ( lpObj->pInventory[j].m_Type == -1 )
			{
				Success = false;
				break;
			}

			if ( lpObj->pInventory[j].m_IsValidItem == false )
			{
				Success = false;
				break;
			}
		}
	}
	else
	{
		for  ( int k=2;k<=6;k++)
		{
			if ( lpObj->pInventory[k].m_Type == -1 )
			{
				Success = false;
				break;
			}

			if ( lpObj->pInventory[k].m_IsValidItem == false )
			{
				Success = false;
				break;
			}
		}
	}

	int Level11Count = 0;
	int Level10Count = 0;
	int Level12Count = 0;
	int Level13Count = 0;
	//Season 5 +15 Items
	int Level14Count = 0;
	int Level15Count = 0;

	if ( Success != false )
	{
		int in;

		if ( lpObj->Class == CLASS_MAGUMSA )
		{
			in = lpObj->pInventory[3].m_Type % MAX_SUBTYPE_ITEMS;

			if ( in != ITEMGET(0,15) &&
				 in != ITEMGET(0,20) &&
				 in != ITEMGET(0,23) &&
				 in != ITEMGET(0,33) &&
				 in != ITEMGET(0,32) &&
				 in != ITEMGET(0,37) &&
				 //season4 add-on
				 in != ITEMGET(0,47) &&
				 in != ITEMGET(0,48))
			{
				Success = false;
			}
			else
			{
				Level13Count++;

				for (int m=3;m<=6;m++)
				{
					if ( in != ( lpObj->pInventory[m].m_Type % MAX_SUBTYPE_ITEMS) )
					{
						Success = false;
					}
					//Season 5 +15 Items
					if ( lpObj->pInventory[m].m_Level > 14 )
					{
						Level15Count++;
					}
					else if ( lpObj->pInventory[m].m_Level > 13 )
					{
						Level14Count++;
					}
					else if ( lpObj->pInventory[m].m_Level > 12 )
					{
						Level13Count++;
					}
					else if ( lpObj->pInventory[m].m_Level > 11 )
					{
						Level12Count++;
					}
					else if ( lpObj->pInventory[m].m_Level > 10 )
					{
						Level11Count++;
					}
					else if ( lpObj->pInventory[m].m_Level > 9 )
					{
						Level10Count++;
					}
				}
			}
		}
		else
		{
			in = lpObj->pInventory[2].m_Type % MAX_SUBTYPE_ITEMS;

			for (int m=2;m<=6;m++)
			{
				if ( in !=  ( lpObj->pInventory[m].m_Type % MAX_SUBTYPE_ITEMS) )
				{
					Success = false;
				}
				//Season 5 +15 Items
				if ( lpObj->pInventory[m].m_Level > 14 )
				{
					Level15Count++;
				}
				else if ( lpObj->pInventory[m].m_Level > 13 )
				{
					Level14Count++;
				}
				else if ( lpObj->pInventory[m].m_Level > 12 )
				{
					Level13Count++;
				}
				else if ( lpObj->pInventory[m].m_Level > 11 )
				{
					Level12Count++;
				}
				else if ( lpObj->pInventory[m].m_Level > 10 )
				{
					Level11Count++;
				}
				else if ( lpObj->pInventory[m].m_Level > 9 )
				{
					Level10Count++;
				}
			}
		}

		if ( Success != false )
		{
			lpObj->m_SuccessfulBlocking += lpObj->m_SuccessfulBlocking / 10;
		}
	}

	if( lpObj->m_MPSkillOpt.MpsBlockingRate > 0.0f )
	{
		lpObj->m_SuccessfulBlocking += lpObj->m_SuccessfulBlocking / 100.0f * lpObj->m_MPSkillOpt.MpsBlockingRate;
	}

	lpObj->m_SuccessfulBlocking += lpObj->m_MPSkillOpt.MpsShieldMastery;
	//lpObj->m_SuccessfulBlocking += lpObj->m_MPSkillOpt.MpsShieldMastery2;
	lpObj->m_SuccessfulBlocking += lpObj->m_MPSkillOpt.MpsShieldMastery3;

	if ( lpObj->Class == CLASS_ELF )
	{
		//int Defense = GetPrivateProfileInt("Fairy_Elf","Defense",10,"..\\Data\\ExData\\Character.ini");
		lpObj->m_Defense = Dexterity / ExConfig.Character.ELFDefense;
	}
	else if ( lpObj->Class == CLASS_KNIGHT )
	{
		//int Defense = GetPrivateProfileInt("Dark_Knight","Defense",3,"..\\Data\\ExData\\Character.ini");
		lpObj->m_Defense = Dexterity / ExConfig.Character.DKDefense;
	}
	else if ( lpObj->Class == CLASS_DARKLORD )
	{
		//int Defense = GetPrivateProfileInt("Dark_Lord","Defense",7,"..\\Data\\ExData\\Character.ini");
		lpObj->m_Defense = Dexterity / ExConfig.Character.DLDefense;
	}
	else if ( lpObj->Class == CLASS_SUMMONER ) //strong like BK
	{
		//int Defense = GetPrivateProfileInt("Summoner","Defense",3,"..\\Data\\ExData\\Character.ini");
		lpObj->m_Defense = Dexterity / ExConfig.Character.SUMDefense;
	}
	else if ( lpObj->Class == CLASS_MAGUMSA ) //MG
	{
		//int Defense = GetPrivateProfileInt("Magic_Gladiator","Defense",4,"..\\Data\\ExData\\Character.ini");
		lpObj->m_Defense = Dexterity / ExConfig.Character.MGDefense;
	}
	else if ( lpObj->Class == CLASS_WIZARD ) //DW
	{
		//int Defense = GetPrivateProfileInt("Dark_Wizard","Defense",4,"..\\Data\\ExData\\Character.ini");
		lpObj->m_Defense = Dexterity / ExConfig.Character.DWDefense;
	}
#ifdef MONK
	else if( lpObj->Class == CLASS_MONK )
	{
		lpObj->m_Defense = Dexterity / ExConfig.Character.RFDefense;
	}
#endif
	else
	{
		lpObj->m_Defense = Dexterity / 4;
	}



	lpObj->m_Defense += lpObj->pInventory[2].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[3].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[4].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[5].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[6].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[1].ItemDefense();
	lpObj->m_Defense += lpObj->pInventory[7].ItemDefense();

	if ( lpObj->pInventory[8].IsItem() != FALSE )
	{
		if ( lpObj->pInventory[8].m_Type == ITEMGET(13,4) && lpObj->pInventory[8].m_Durability > 0.0f )
		{
			lpObj->m_Defense += INT( Dexterity / 20 + 5 + Helper->m_PetItem_Level * 2 );
		}
	}

	if ( lpObj->pInventory[8].IsItem() != FALSE )
	{
		if ( lpObj->pInventory[8].m_Type == ITEMGET(13,37) && lpObj->pInventory[8].m_Durability > 0.0f ) // Golden Fenrir (Season 2.5 add-on)
		{
			if ( lpObj->pInventory[8].IsFenrirSpecial() != FALSE )
			{

				int BaseLevel = lpObj->Level + lpObj->MLevel;

				lpObj->AddLife += BaseLevel/2; //season3 changed
				lpObj->AddMana += BaseLevel/2; //season3 changed


				lpObj->m_AttackDamageMinRight += BaseLevel/12;
				lpObj->m_AttackDamageMaxRight += BaseLevel/12;

				lpObj->m_AttackDamageMinLeft += BaseLevel/12;
				lpObj->m_AttackDamageMaxLeft += BaseLevel/12;

				lpObj->m_MagicDamageMax += BaseLevel/25;
				lpObj->m_MagicDamageMin += BaseLevel/25;
#ifdef FENRIR_CONFIG
				//illusian

				if(g_ExLicense.CheckUser(eExUB::PrideMuLocal) || g_ExLicense.CheckUser(eExUB::PrideMu) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::Local))
				{
					lpObj->AddLife += ExConfig.PrideMu.AddLife; 
					lpObj->AddMana += ExConfig.PrideMu.AddMana; 


					lpObj->m_AttackDamageMinRight += ExConfig.PrideMu.AttackDamageMin;
					lpObj->m_AttackDamageMaxRight += ExConfig.PrideMu.AttackDamageMax;

					lpObj->m_AttackDamageMinLeft += ExConfig.PrideMu.AttackDamageMin;
					lpObj->m_AttackDamageMaxLeft += ExConfig.PrideMu.AttackDamageMax;

					lpObj->m_MagicDamageMax += ExConfig.PrideMu.MagicDamageMax;
					lpObj->m_MagicDamageMin += ExConfig.PrideMu.MagicDamageMin;
				}
#endif
			}

			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) ||
				g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
			{
				if ( lpObj->pInventory[8].IsFenrirIncLastAttackDamage() != FALSE )	// Black Fenrir
				{
					lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * ExConfig.Pet.BlackFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * ExConfig.Pet.BlackFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * ExConfig.Pet.BlackFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * ExConfig.Pet.BlackFenrirProcDamage ) / 100; 
					lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMax * ExConfig.Pet.BlackFenrirProcDamage ) / 100; 
					lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * ExConfig.Pet.BlackFenrirProcDamage ) / 100; 
					lpObj->DamageMinus += ExConfig.Pet.BlackFenrirProcAbsurd;
					lpObj->AddLife += ( lpObj->MaxLife * ExConfig.Pet.BlackFenrirProcLife ) / 100; 
				}
				else if ( lpObj->pInventory[8].IsFenrirDecLastAttackDamage() != FALSE )	// Blue Fenrir
				{
					lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * ExConfig.Pet.BlueFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * ExConfig.Pet.BlueFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * ExConfig.Pet.BlueFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * ExConfig.Pet.BlueFenrirProcDamage ) / 100; 
					lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMax * ExConfig.Pet.BlueFenrirProcDamage ) / 100; 
					lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * ExConfig.Pet.BlueFenrirProcDamage ) / 100; 
					lpObj->DamageMinus += ExConfig.Pet.BlueFenrirProcAbsurd;
					lpObj->AddLife += ( lpObj->MaxLife * ExConfig.Pet.BlueFenrirProcLife ) / 100; 				 
				}
				else if ( lpObj->pInventory[8].IsFenrirSpecial() != FALSE )	// Illusion Fenrir
				{
					lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * ExConfig.Pet.GoldFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * ExConfig.Pet.GoldFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * ExConfig.Pet.GoldFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * ExConfig.Pet.GoldFenrirProcDamage ) / 100; 
					lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMax * ExConfig.Pet.GoldFenrirProcDamage ) / 100; 
					lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * ExConfig.Pet.GoldFenrirProcDamage ) / 100; 
					lpObj->DamageMinus += ExConfig.Pet.GoldFenrirProcAbsurd;
					lpObj->AddLife += ( lpObj->MaxLife * ExConfig.Pet.GoldFenrirProcLife ) / 100; 				
				}
				else	//red 
				{
					lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * ExConfig.Pet.RedFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * ExConfig.Pet.RedFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * ExConfig.Pet.RedFenrirProcDamage ) / 100; 
					lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * ExConfig.Pet.RedFenrirProcDamage ) / 100; 
					lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMax * ExConfig.Pet.RedFenrirProcDamage ) / 100; 
					lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * ExConfig.Pet.RedFenrirProcDamage ) / 100; 
					lpObj->DamageMinus += ExConfig.Pet.RedFenrirProcAbsurd;
					lpObj->AddLife += ( lpObj->MaxLife * ExConfig.Pet.RedFenrirProcLife ) / 100; 
				}

			}
		}
	}
	//Season 5 +15 Items

	auto res = g_HuntingSystem.GetSkillIncValue(aIndex, EHuntingSkill::eHS_SETDEF);

	if ( (Level15Count + Level14Count + Level13Count + Level12Count + Level11Count + Level10Count) >= 5 )
	{
		if ( Success != false )
		{
			if ( Level15Count == 5 )
			{
				lpObj->m_Defense += (lpObj->m_Defense * 30 / 100) * (1 + res);
			}
			else if ( Level14Count == 5 )
			{
				lpObj->m_Defense += (lpObj->m_Defense * 25 / 100) * (1 + res);
			}
			else if ( Level13Count == 5 )
			{
				lpObj->m_Defense += (lpObj->m_Defense * 20 / 100) * (1 + res);
			}
			else if ( Level12Count == 5 || (Level12Count + Level13Count) == 5 )
			{
				lpObj->m_Defense += (lpObj->m_Defense * 15 / 100) * (1 + res);
			}
			else if ( Level11Count == 5 || (Level11Count + Level12Count + Level13Count) == 5 )
			{
				lpObj->m_Defense += (lpObj->m_Defense * 10 / 100) * (1 + res);
			}
			else if ( Level10Count == 5 || (Level10Count + Level11Count + Level12Count + Level13Count) == 5)
			{
				lpObj->m_Defense += (lpObj->m_Defense * 5 / 100) * (1 + res);
			}
		}
	}

	lpObj->m_Defense += lpObj->m_MPSkillOpt.MpsDefence;

	lpObj->m_Defense = lpObj->m_Defense * 10 / 20;

	if ( lpObj->m_Change == 9 )
	{
		//Empty
	}
	else if ( lpObj->m_Change == 41 )
	{
		lpObj->AddLife = ((int)(lpObj->MaxLife * 20.0f))/100;
	}
	else if ( lpObj->m_Change == 372 )
	{
		lpObj->m_Defense += lpObj->m_Defense / 10;
		lpObj->AddLife += lpObj->Level + lpObj->MLevel;
	}
	else if ( lpObj->m_Change == 374 ) //Santa Girl Polymorph Ring (Season 2.5 Add-on)
	{
		lpObj->m_AttackDamageMaxLeft += 20;
		lpObj->m_AttackDamageMinLeft += 20;
		lpObj->m_AttackDamageMaxRight += 20;
		lpObj->m_AttackDamageMinRight += 20;
		lpObj->m_MagicDamageMin += 20;
		lpObj->m_MagicDamageMax += 20;
	}
	else if ( lpObj->m_Change == 503 ) //Panda Ring (Season 4.6 Add-on)
	{
		//int Ex_PandaRingAttack = GetPrivateProfileInt("PandaRing","AttackDamage",30,"..\\Data\\ExData\\Pets.ini");
		//int Ex_PandaRingAttack = ExConfig.Pet.Ex_PandaRingAttack;
		lpObj->m_AttackDamageMaxLeft += ExConfig.Pet.Ex_PandaRingAttack;
		lpObj->m_AttackDamageMinLeft += ExConfig.Pet.Ex_PandaRingAttack;
		lpObj->m_AttackDamageMaxRight += ExConfig.Pet.Ex_PandaRingAttack;
		lpObj->m_AttackDamageMinRight += ExConfig.Pet.Ex_PandaRingAttack;
		lpObj->m_MagicDamageMin += ExConfig.Pet.Ex_PandaRingAttack;
		lpObj->m_MagicDamageMax += ExConfig.Pet.Ex_PandaRingAttack;
	}
	else if ( lpObj->m_Change == 548 ) //Season 5 Skeleton Ring
	{
		lpObj->m_AttackDamageMaxLeft += 40;
		lpObj->m_AttackDamageMinLeft += 40;
		lpObj->m_AttackDamageMaxRight += 40;
		lpObj->m_AttackDamageMinRight += 40;
		lpObj->m_MagicDamageMin += 40;
		lpObj->m_MagicDamageMax += 40;
	}
	if(gObjDemonSprite(lpObj) == TRUE) //CashShop Demon Pet (Season 3.5 Add-on)
	{
		//season4 changed (all these removed... Why? :|)
		/*lpObj->m_AttackDamageMinRight += lpObj->m_AttackDamageMinRight * 40 / 100;
		lpObj->m_AttackDamageMaxRight += lpObj->m_AttackDamageMaxRight * 40 / 100;

		lpObj->m_AttackDamageMinLeft += lpObj->m_AttackDamageMinLeft * 40 / 100;
		lpObj->m_AttackDamageMaxLeft += lpObj->m_AttackDamageMaxLeft * 40 / 100;

		lpObj->m_MagicDamageMin += lpObj->m_MagicDamageMin * 40 / 100;
		lpObj->m_MagicDamageMax += lpObj->m_MagicDamageMax * 40 / 100;*/

		lpObj->m_AttackSpeed += 10;
		lpObj->m_MagicSpeed += 10;
	}

	if(gObjSkeletonSprite(lpObj) == TRUE) //Season 5 Skeleton Pet
	{
		lpObj->m_AttackSpeed += 10;
		lpObj->m_MagicSpeed += 10;
	}

	if(gObjSpiritGuardianSprite(lpObj) == TRUE) //CashShop Spirit Guardian Pet (Season 3.5 Add-on) Sucks like Angel
	{
		lpObj->AddLife += 50;
	}

	if(gObjPandaSprite(lpObj) == TRUE) //Panda
	{
		//int Ex_PandaDef = GetPrivateProfileInt("Panda","Defense",50,"..\\Data\\ExData\\Pets.ini");
		lpObj->m_Defense += ExConfig.Pet.Ex_PandaDef;
	}

	//if( gObjUnicornSprite(lpObj) == TRUE ) // Season 5 Episode 2 JPN
	//{
	//	lpObj->m_Defense				+= 50;
	//}

	if ( lpObj->pInventory[8].m_Type == ITEMGET(13,0) )
	{
		lpObj->AddLife += 50;
	}

	int addlife = 0;
	int addmana = 0;

	lpObj->pInventory[7].PlusSpecial(&addlife, 100);
	lpObj->pInventory[7].PlusSpecial(&addmana, 101);

	lpObj->pInventory[7].PlusSpecial(&AddLeadership, 105);

	lpObj->AddLeadership += AddLeadership; //season4 changed (wz fix o/)

	lpObj->AddLife += addlife;
	lpObj->AddMana += addmana;

	if ( lpObj->pInventory[8].m_Type == ITEMGET(13,3) )
	{
		lpObj->pInventory[8].PlusSpecial(&lpObj->AddBP, 103 );
	}

	if ( lpObj->Type == OBJ_USER )
	{
		gDarkSpirit[lpObj->m_Index].Set(lpObj->m_Index, &lpObj->pInventory[1]);
	}

	if ( gObjCheckUserPCBang(lpObj) != 0 ) //season 4.5 add-on (LanHouse Bonus)
	{
		lpObj->AddLife += 40;
		lpObj->AddMana += 40;
		lpObj->AddBP += 20;
		lpObj->m_Defense += 40;
	}

	lpObj->pInventory[9].PlusSpecialPercentEx(&lpObj->AddBP, lpObj->MaxBP, 173);
	lpObj->pInventory[10].PlusSpecialPercentEx(&lpObj->AddMana, (int)lpObj->MaxMana, 172);
	lpObj->pInventory[11].PlusSpecialPercentEx(&lpObj->AddMana, (int)lpObj->MaxMana, 172);

	if(lpObj->Class == CLASS_SUMMONER) //Season 3 add-on (Summoning Book Skills Value)
	{
		lpObj->m_iSummonerBookSpellDamageMax = lpObj->pInventory[1].BookSpellDmg(); //
	}

	CItem * rItem[3];
	int comparecount = 0;
	
	rItem[0] = &lpObj->pInventory[10];
	rItem[1] = &lpObj->pInventory[11];
	rItem[2] = &lpObj->pInventory[9];

	#define GET_MAX_RESISTANCE(x,y,z) ( ( ( ( (x) > (y) ) ? (x) : (y) ) > (z) ) ? ( ( (x) > (y) ) ? (x) : (y) ) : (z) )	

	lpObj->m_Resistance[1] = GET_MAX_RESISTANCE(rItem[0]->m_Resistance[1], rItem[1]->m_Resistance[1], rItem[2]->m_Resistance[1]); //Poison
	lpObj->m_Resistance[0] = GET_MAX_RESISTANCE(rItem[0]->m_Resistance[0], rItem[1]->m_Resistance[0], rItem[2]->m_Resistance[0]); //Cold
	lpObj->m_Resistance[2] = GET_MAX_RESISTANCE(rItem[0]->m_Resistance[2], rItem[1]->m_Resistance[2], rItem[2]->m_Resistance[2]); //Thunder
	lpObj->m_Resistance[3] = GET_MAX_RESISTANCE(rItem[0]->m_Resistance[3], rItem[1]->m_Resistance[3], rItem[2]->m_Resistance[3]); //Fire

	lpObj->m_Resistance[4] = GET_MAX_RESISTANCE(rItem[0]->m_Resistance[4], rItem[1]->m_Resistance[4], rItem[2]->m_Resistance[4]);
	lpObj->m_Resistance[5] = GET_MAX_RESISTANCE(rItem[0]->m_Resistance[5], rItem[1]->m_Resistance[5], rItem[2]->m_Resistance[5]);
	lpObj->m_Resistance[6] = GET_MAX_RESISTANCE(rItem[0]->m_Resistance[6], rItem[1]->m_Resistance[6], rItem[2]->m_Resistance[6]);

	lpObj->m_Resistance[1] += lpObj->m_MPSkillOpt.MpsResistancePoison;//m_MLPassiveSkill.m_iML_ResistanceIncrease_Poison;
	lpObj->m_Resistance[2] += lpObj->m_MPSkillOpt.MpsResistanceThunder;//m_MLPassiveSkill.m_iML_ResistanceIncrease_Lightning;
	lpObj->m_Resistance[0] += lpObj->m_MPSkillOpt.MpsResistanceIce;//m_MLPassiveSkill.m_iML_ResistanceIncrease_Ice;

	g_kItemSystemFor380.ApplyFor380Option(lpObj);
	g_kJewelOfHarmonySystem.SetApplyStrengthenItem(lpObj);
	g_SocketOption.CalCharacterSocketOption(lpObj); //season4 add-on

	lpObj->AddLife		+= lpObj->m_MPSkillOpt.MpsMaxHP;
	lpObj->AddBP		+= lpObj->m_MPSkillOpt.MpsMaxBP;
	lpObj->iAddShield	+= lpObj->m_MPSkillOpt.MpsMaxSD;
	lpObj->AddMana		+= lpObj->m_MPSkillOpt.MpsMaxMP;

	gObjInventoryEquipment(lpObj);


	GObjExtItemApply(lpObj);
	gObjSetItemApply(lpObj);
	gObjNextExpCal(lpObj);
#if(GRAND_HERO_DEV)
	GrandHero.ItemOption(aIndex);
#endif

	if ( (Left->m_Type >= ITEMGET(4,0) && Left->m_Type < ITEMGET(4,7) ) || Left->m_Type == ITEMGET(4,17) || Left->m_Type == ITEMGET(4,20) || Left->m_Type == ITEMGET(4,21) || Left->m_Type == ITEMGET(4,22) ||
		Left->m_Type == ITEMGET(4,23)) //season4 add-on
	{
		if ( Right->m_Type == ITEMGET(4,15) && Right->m_Level == 1 )
		{
			lpObj->m_AttackDamageMinLeft += (WORD)(lpObj->m_AttackDamageMinLeft * 0.03f + 1.0f);
			lpObj->m_AttackDamageMaxLeft += (WORD)(lpObj->m_AttackDamageMaxLeft * 0.03f + 1.0f);
		}
		else if ( Right->m_Type == ITEMGET(4,15) && Right->m_Level == 2 )
		{
			lpObj->m_AttackDamageMinLeft += (WORD)(lpObj->m_AttackDamageMinLeft * 0.05f + 1.0f);
			lpObj->m_AttackDamageMaxLeft += (WORD)(lpObj->m_AttackDamageMaxLeft * 0.05f + 1.0f);
		}
		else if ( Right->m_Type == ITEMGET(4,15) && Right->m_Level == 3 ) //season4 add-on
		{
			lpObj->m_AttackDamageMinLeft += (WORD)(lpObj->m_AttackDamageMinLeft * 0.07f + 1.0f);
			lpObj->m_AttackDamageMaxLeft += (WORD)(lpObj->m_AttackDamageMaxLeft * 0.07f + 1.0f);
		}
	}
	else if ( (Right->m_Type >= ITEMGET(4,8) && Right->m_Type < ITEMGET(4,15) ) || (Right->m_Type >= ITEMGET(4,16) && Right->m_Type < ITEMGET(5,0)) )
	{
		if ( Left->m_Type == ITEMGET(4,7) && Left->m_Level == 1 )
		{
				lpObj->m_AttackDamageMinRight += (WORD)(lpObj->m_AttackDamageMinRight * 0.03f + 1.0f);
				lpObj->m_AttackDamageMaxRight += (WORD)(lpObj->m_AttackDamageMaxRight * 0.03f + 1.0f);
		}
		else if ( Left->m_Type == ITEMGET(4,7) && Left->m_Level == 2 )
		{
				lpObj->m_AttackDamageMinRight += (WORD)(lpObj->m_AttackDamageMinRight * 0.05f + 1.0f);
				lpObj->m_AttackDamageMaxRight += (WORD)(lpObj->m_AttackDamageMaxRight * 0.05f + 1.0f);
		}
		else if ( Left->m_Type == ITEMGET(4,7) && Left->m_Level == 3 ) //season4 add-on
		{
				lpObj->m_AttackDamageMinRight += (WORD)(lpObj->m_AttackDamageMinRight * 0.07f + 1.0f);
				lpObj->m_AttackDamageMaxRight += (WORD)(lpObj->m_AttackDamageMaxRight * 0.07f + 1.0f);
		}
	}

	if ( lpObj->Class == CLASS_KNIGHT || lpObj->Class == CLASS_MAGUMSA || lpObj->Class == CLASS_DARKLORD  )
	{
		if ( Right->m_Type != -1 && Left->m_Type != -1 )
		{
			if ( Right->m_Type >= ITEMGET(0,0) && Right->m_Type < ITEMGET(4,0) && Left->m_Type >= ITEMGET(0,0) && Left->m_Type < ITEMGET(4,0) )
			{
				lpObj->m_AttackDamageMinRight = lpObj->m_AttackDamageMinRight * 55 / 100;
				lpObj->m_AttackDamageMaxRight = lpObj->m_AttackDamageMaxRight * 55 / 100;
				lpObj->m_AttackDamageMinLeft = lpObj->m_AttackDamageMinLeft * 55 / 100;
				lpObj->m_AttackDamageMaxLeft = lpObj->m_AttackDamageMaxLeft * 55 / 100;
			}
		}
	}

#ifdef MONK
	if( lpObj->Class == CLASS_MONK )
	{
		if( Right->m_Type != -1 && Left->m_Type != -1 )
		{
			if( Right->m_Type >= ITEMGET(0,0) && Right->m_Type < ITEMGET(4,0) && Left->m_Type >= ITEMGET(0,0) && Left->m_Type < ITEMGET(4,0) )
			{
				lpObj->m_AttackDamageMinRight	= lpObj->m_AttackDamageMinRight * 60 / 100;
				lpObj->m_AttackDamageMaxRight	= lpObj->m_AttackDamageMaxRight * 65 / 100;
				lpObj->m_AttackDamageMinLeft	= lpObj->m_AttackDamageMinLeft  * 60 / 100;
				lpObj->m_AttackDamageMaxLeft	= lpObj->m_AttackDamageMaxLeft  * 65 / 100;
			}
		}
	}
#endif
	
	g_ItemAddOption.NextSetItemLastEffectForCashShop(lpObj); //Apply again CashShop Attributes (Leaps and Scrolls)

#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
	g_PremiumSystemEx.UserCalculatorPlus(aIndex);
#endif

	g_ViewportSkillState.NextSetBuffLastEffect(lpObj); //season3 add-on for buffeffect (Set All attributes)

	if ( lpObj->m_iItemEffectValidTime > 0 )
	{
		g_ItemAddOption.NextSetItemLastEffectForHallowin(lpObj);
	}

#ifdef DEBUG_CODE2
	LogAddC(2,"DAMAGE: %d",lpObj->m_AttackDamageMaxRight);
#endif

#ifdef EN_RINGS
	g_ItemAddOption.ApplyForEquipment(lpObj);
#endif

	gObjCalcShieldPoint(lpObj);

	if(g_CustomSystem.IsRage())
	{
		gSystemOfRage.CalcCharacter(aIndex);
	}

	g_HuntingSystem.CalcCharacter(aIndex);

	if(g_ExLicense.user.WinQuest) gWinQuestSystem.CharOptions(aIndex);

	gExclusiveOptions.Options(aIndex);

	
#if(SYSTEMOF_BROTHER==TRUE)
	gBrotherhood.CharacterAdded(lpObj);
#endif

#if(CUSTOM_NPC_BUFFER==TRUE)
	if(g_ExLicense.user.NpcBuffer)
	{
		if(lpObj->DamageBuffTime > 0 )
		{
			int AddProcentDamage = 10;

			lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * AddProcentDamage ) / 100;
			lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * AddProcentDamage ) / 100;
			lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * AddProcentDamage ) / 100;
			lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * AddProcentDamage ) / 100;
			lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;
			lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;
		}
		// ----
		if( lpObj->DefenceBuffTime > 0 )
		{
			int AddProcentDefence = 10;

			lpObj->m_Defense += ( lpObj->m_Defense * AddProcentDefence ) / 100;
			lpObj->m_MagicDefense += ( lpObj->m_MagicDefense * AddProcentDefence ) / 100;
		}
		// ----
		if( lpObj->BattleBuffTime > 0 )
		{
			int AddProcentCriticalDamage = 5;
			int AddProcentExellentDamage = 5;

			lpObj->m_CriticalDamage += AddProcentCriticalDamage;
			lpObj->m_ExcelentDamage += AddProcentExellentDamage;
		}
		// ----
		if( lpObj->DoubleBuffTime > 0 )
		{
			int AddProcentDoubleDamage  = 5;

			lpObj->SetOpDoubleDamage += AddProcentDoubleDamage;
		}	
	}
#endif

	BMQuest.AddedCharacter(aIndex);	//BMQuest

#if(CUSTOM_MARRIAGE)
	g_Marriage.AddedCharacter(aIndex);
#endif
#if(CUSTOM_NOOBBUFF)
	if(gObjSearchActiveEffect(lpObj,AT_NOOB_BUFF) == TRUE)
	{
		int AddProcentDamage = ExConfig.CommonServer.m_NoobDamage;

		lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * AddProcentDamage ) / 100;
		lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;
		lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;

		int AddProcentDefence = ExConfig.CommonServer.m_NoobDefence;

		lpObj->m_Defense += ( lpObj->m_Defense * AddProcentDefence ) / 100;
		lpObj->m_MagicDefense += ( lpObj->m_MagicDefense * AddProcentDefence ) / 100;
	}
#endif

#if(CUSTOM_NEWBUFF)
	if(gObjSearchActiveEffect(lpObj,AT_NEWPREMIUM_BUFF) == TRUE)
	{
		int AddProcentDamage = ExConfig.m_iNewBuffPremiumDamage;

		lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * AddProcentDamage ) / 100;
		lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;
		lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;

		int AddProcentDefence = ExConfig.m_iNewBuffPremiumDefence;

		lpObj->m_Defense += ( lpObj->m_Defense * AddProcentDefence ) / 100;
		lpObj->m_MagicDefense += ( lpObj->m_MagicDefense * AddProcentDefence ) / 100;
	}

	if(gObjSearchActiveEffect(lpObj,AT_NEWGUILD_BUFF) == TRUE)
	{
		int AddProcentDamage = ExConfig.m_iNewBuffGuildDamage;

		lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * AddProcentDamage ) / 100;
		lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;
		lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;

		int AddProcentDefence = ExConfig.m_iNewBuffGuildDefence;

		lpObj->m_Defense += ( lpObj->m_Defense * AddProcentDefence ) / 100;
		lpObj->m_MagicDefense += ( lpObj->m_MagicDefense * AddProcentDefence ) / 100;
	}

	if(gObjSearchActiveEffect(lpObj,AT_NEWPARTY_BUFF) == TRUE)
	{
		int AddProcentDamage = ExConfig.m_iNewBuffPartyDamage;

		lpObj->m_AttackDamageMaxLeft += ( lpObj->m_AttackDamageMaxLeft * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMinLeft += ( lpObj->m_AttackDamageMinLeft * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMaxRight += ( lpObj->m_AttackDamageMaxRight * AddProcentDamage ) / 100;
		lpObj->m_AttackDamageMinRight += ( lpObj->m_AttackDamageMinRight * AddProcentDamage ) / 100;
		lpObj->m_MagicDamageMin += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;
		lpObj->m_MagicDamageMax += ( lpObj->m_MagicDamageMin * AddProcentDamage ) / 100;

		int AddProcentDefence = ExConfig.m_iNewBuffPartyDefence;

		lpObj->m_Defense += ( lpObj->m_Defense * AddProcentDefence ) / 100;
		lpObj->m_MagicDefense += ( lpObj->m_MagicDefense * AddProcentDefence ) / 100;
	}
#endif


	#if(EVENT_DUNGEON_SIEGE)
	g_DungeonSiege.GuildBuffCharacter(aIndex);
	#endif
	#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.CalculatorPower(aIndex);
	#endif
	#if(ENABLE_PETEX)
	g_PetEx.Calc(aIndex);
	#endif

	gMaxPower.Main(aIndex);	//check max parametrs char

#ifdef _VOTER_						
	gVoter.PlayerCalculator(lpObj->m_Index);
#endif

	gBalanceSystem.Refflect(lpObj);

	if ( lpObj->iShield > ( lpObj->iMaxShield + lpObj->iAddShield ) )
	{
		lpObj->iShield = lpObj->iMaxShield + lpObj->iAddShield ;
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0, lpObj->iShield);
	}

	GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), 0xFE, 0, (lpObj->iMaxShield + lpObj->iAddShield));
	GCManaSend(lpObj->m_Index, (lpObj->MaxMana + lpObj->AddMana), 0xFE, 0, (lpObj->MaxBP + lpObj->AddBP));

#ifdef DEBUG_CODE2
	LogAddC(2,"FINAL DAMAGE: %d",lpObj->m_AttackDamageMaxRight);
#endif

	gWingsDamage.PlayerCalculator(aIndex);

	#if(DEV_STATS_ADVANCE)
	g_StatsAdvance.Send(aIndex);
	#endif
}

void GObjExtItemApply(LPOBJ lpObj)
{

	int n;
	int i;
	int max_count = 0;
	int temp_n[3] = {0, 1, 9};
	int temp_n2[10] = {2, 3, 4, 5, 6, 7, 8, 10, 11, 1};
	int maxn2_loop = 9;

	for ( i=0;i<3;i++ )
	{
		n = temp_n[i];

		if ( lpObj->pInventory[n].m_Type >= ITEMGET(6, 0) && lpObj->pInventory[n].m_Type < ITEMGET(7, 0) )
		{
			continue;
		}

		if ( lpObj->pInventory[n].IsItem() == TRUE )
		{
			if ( lpObj->pInventory[n].m_Durability != 0.0f )
			{
				if ( lpObj->pInventory[n].m_IsValidItem == true )
				{
					if ( lpObj->pInventory[n].IsExtAttackRate() )
					{
						if ( ( lpObj->pInventory[n].m_Type >= ITEMGET(5, 0) && lpObj->pInventory[n].m_Type < ITEMGET(6, 0) ) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,12) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,25) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,27) )
						{
							lpObj->m_MagicDamageMax += (lpObj->Level + lpObj->MLevel) / 20;
							lpObj->m_MagicDamageMin += (lpObj->Level + lpObj->MLevel) / 20;
							/*lpObj->m_MagicDamageMax += (lpObj->Level + lpObj->MLevel) / lpObj->pInventory[n].IsExtAttackRate();
							lpObj->m_MagicDamageMin += (lpObj->Level + lpObj->MLevel) / lpObj->pInventory[n].IsExtAttackRate();*/
						}
						else 
						{
							if ( n == 0 || n == 9 )
							{
								lpObj->m_AttackDamageMinRight += (lpObj->Level + lpObj->MLevel) / 20;
								lpObj->m_AttackDamageMaxRight += (lpObj->Level + lpObj->MLevel) / 20;
								/*lpObj->m_AttackDamageMinRight += (lpObj->Level + lpObj->MLevel) / lpObj->pInventory[n].IsExtAttackRate();
								lpObj->m_AttackDamageMaxRight += (lpObj->Level + lpObj->MLevel) / lpObj->pInventory[n].IsExtAttackRate();*/
							}
							
							if ( n == 1 || n == 9 )
							{
								lpObj->m_AttackDamageMinLeft += (lpObj->Level + lpObj->MLevel) / 20;
								lpObj->m_AttackDamageMaxLeft += (lpObj->Level) / 20;
								/*lpObj->m_AttackDamageMinLeft += (lpObj->Level + lpObj->MLevel) / lpObj->pInventory[n].IsExtAttackRate();
								lpObj->m_AttackDamageMaxLeft += (lpObj->Level + lpObj->MLevel) / lpObj->pInventory[n].IsExtAttackRate();*/
							}
						}
					}

					if ( lpObj->pInventory[n].IsExtAttackRate2() )
					{
						if ( ( lpObj->pInventory[n].m_Type >= ITEMGET(5, 0) && lpObj->pInventory[n].m_Type < ITEMGET(6, 0) ) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,12) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,25) ||
							lpObj->pInventory[n].m_Type == ITEMGET(13,27) )
						{
							lpObj->m_MagicDamageMax += lpObj->m_MagicDamageMax * lpObj->pInventory[n].IsExtAttackRate2() / 100;
							lpObj->m_MagicDamageMin += lpObj->m_MagicDamageMin * lpObj->pInventory[n].IsExtAttackRate2() / 100;
						}
						else 
						{
							if ( n == 0 || n == 9 )
							{
								lpObj->m_AttackDamageMinRight += lpObj->m_AttackDamageMinRight * lpObj->pInventory[n].IsExtAttackRate2() / 100;
								lpObj->m_AttackDamageMaxRight += lpObj->m_AttackDamageMaxRight * lpObj->pInventory[n].IsExtAttackRate2() / 100;
							}
							
							if ( n == 1 || n == 9 )
							{
								lpObj->m_AttackDamageMinLeft += lpObj->m_AttackDamageMinLeft * lpObj->pInventory[n].IsExtAttackRate2() / 100;
								lpObj->m_AttackDamageMaxLeft += lpObj->m_AttackDamageMaxLeft * lpObj->pInventory[n].IsExtAttackRate2() / 100;
							}
						}
					}

					lpObj->m_ExcelentDamage += lpObj->pInventory[n].IsExtExcellentDamage();
					lpObj->m_AttackSpeed += lpObj->pInventory[n].IsExtAttackSpeed();
					lpObj->m_MagicSpeed += lpObj->pInventory[n].IsExtAttackSpeed();
					lpObj->MonsterDieGetLife += lpObj->pInventory[n].IsExtMonsterDieLife();
					lpObj->MonsterDieGetMana += lpObj->pInventory[n].IsExtMonsterDieMana();
				}
			}
		}
	}
		
	if ( lpObj->pInventory[1].IsItem() == TRUE )
	{
#if(FIX_SHIELD)
		if((lpObj->pInventory[1].m_Type >= ITEMGET(6, 0) && lpObj->pInventory[1].m_Type < ITEMGET(7, 0))) //season4 add-on
		{
			maxn2_loop = 10;
		}
#else
		if ( (lpObj->pInventory[1].m_Type >= ITEMGET(6, 0) && lpObj->pInventory[1].m_Type <= ITEMGET(6, 16)) || 
			lpObj->pInventory[1].m_Type == ITEMGET(6, 21)) //season4 add-on
		{
			maxn2_loop = 10;
		}
#endif
	}

	for ( i=0;i<maxn2_loop;i++)
	{
		n = temp_n2[i];

		if ( max_count < 8 )
		{
			if ( lpObj->pInventory[n].IsItem() == TRUE &&
				 lpObj->pInventory[n].IsExtItem() &&
				 lpObj->pInventory[n].m_Durability != 0.0f &&
				 lpObj->pInventory[n].m_IsValidItem == true )
			{
				if ( n != 7 )
				{
					lpObj->AddLife += (short)(lpObj->MaxLife * lpObj->pInventory[n].IsExtLifeAdd()  / 100.0f);
					lpObj->AddMana += (short)(lpObj->MaxMana * lpObj->pInventory[n].IsExtManaAdd() / 100.0f);
					lpObj->m_SuccessfulBlocking += lpObj->m_SuccessfulBlocking * lpObj->pInventory[n].IsExtDefenseSuccessfull() / 100;
					lpObj->MonsterDieGetMoney += lpObj->pInventory[n].IsExtMonsterMoney();
					lpObj->DamageMinus += lpObj->pInventory[n].IsExtDamageMinus();
					lpObj->DamageReflect += lpObj->pInventory[n].IsExtDamageReflect();
					max_count++;
				}
			}
		}
	}
}

void gObjCalcSetItemStat(LPOBJ lpObj)
{
	for ( int i=0;i<INVETORY_WEAR_SIZE;i++)
	{
		if ( lpObj->pInventory[i].IsSetItem() && lpObj->pInventory[i].m_IsValidItem && lpObj->pInventory[i].m_Durability != 0.0f )
		{
			int AddStatType = lpObj->pInventory[i].GetAddStatType();

			switch ( AddStatType )
			{
				case 1:
					lpObj->pInventory[i].SetItemPlusSpecialStat(&lpObj->AddStrength, 196);
					break;
				case 2:
					lpObj->pInventory[i].SetItemPlusSpecialStat(&lpObj->AddDexterity, 197);
					break;
				case 3:
					lpObj->pInventory[i].SetItemPlusSpecialStat(&lpObj->AddEnergy, 198);
					break;
				case 4:
					lpObj->pInventory[i].SetItemPlusSpecialStat(&lpObj->AddVitality, 199);
					break;
			}
		}
	}
}

void gObjGetSetItemOption(LPOBJ lpObj, LPBYTE pSetOptionTable , LPBYTE pSetOptionCountTable , int * pSetOptionCount)
{
	*pSetOptionCount = 0;
	int RightSetOptionIndex = -1;
	int RightRingSetOptionIndex = -1;

	for ( int i=0;i<INVETORY_WEAR_SIZE;i++)
	{
#ifdef LUCKYITEM
		if( g_LuckyItemManager.IsLuckyItemEquipment(lpObj->pInventory[i].m_Type) 
			&& lpObj->pInventory[i].m_Durability == 0.0f )
		{
			continue;
		}
#endif
		int iSetItemType = lpObj->pInventory[i].IsSetItem();

		if ( iSetItemType )
		{
			if ( lpObj->pInventory[i].m_IsValidItem )
			{
				int iSetItemOption = gSetItemOption.GetOptionTableIndex(lpObj->pInventory[i].m_Type, iSetItemType );

				if ( iSetItemOption != -1 )
				{
					if ( i == 0 )
					{
						RightSetOptionIndex = iSetItemOption;
					}
					else if ( i == 1  )
					{
						if (  RightSetOptionIndex == iSetItemOption )
						{
							if ( lpObj->pInventory[0].GetWeaponType() == lpObj->pInventory[1].GetWeaponType() && lpObj->pInventory[0].IsSetItem() )
							{
								LogAddTD("양손에 같은 세트가 적용되었다 무시...");
								continue;
							}
						}
					}
					
					if ( i == 10 )
					{
						RightRingSetOptionIndex = iSetItemOption;
					}
					else if ( i == 11   )
					{
						if(RightRingSetOptionIndex == iSetItemOption) //season4 add-on (wz fix o/)
						{
							if ( lpObj->pInventory[10].m_Type == lpObj->pInventory[11].m_Type && lpObj->pInventory[10].IsSetItem() )
							{
								LogAddTD("반지에 같은 세트가 적용되었다 무시...");
								continue;
							}
						}
					}

					BOOL bFound = FALSE;

					for ( int n=0;n<*pSetOptionCount;n++)
					{
						if ( pSetOptionTable[n] == iSetItemOption )
						{
							pSetOptionCountTable[n]++;
							bFound = TRUE;

							LogAddTD("옵션 찾았다 %s, Count = %d", gSetItemOption.GetSetOptionName(iSetItemOption), pSetOptionCountTable[n]);

							break;
						}
					}

					if ( bFound == FALSE )
					{
						pSetOptionTable[*pSetOptionCount] = iSetItemOption;
						pSetOptionCountTable[*pSetOptionCount]++;

						LogAddTD("옵션 찾았다 %s, Count = %d", gSetItemOption.GetSetOptionName(iSetItemOption), pSetOptionCountTable[*pSetOptionCount]);

						*pSetOptionCount += 1;
					}
				}
			}
		}
	}
}

void gObjCalcSetItemOption(LPOBJ lpObj)
{
	BYTE SetOptionTable[29];
	BYTE SetOptionCountTable[29];
	int SetOptionCount = 0;
	int op1;
	int op2;
	int op3;
	int op4;
	int op5;
	int opvalue1;
	int opvalue2;
	int opvalue3;
	int opvalue4;
	int opvalue5;

	memset(SetOptionTable, 0, sizeof(SetOptionTable));
	memset(SetOptionCountTable, 0, sizeof(SetOptionCountTable));
	gObjGetSetItemOption(lpObj, SetOptionTable, SetOptionCountTable, &SetOptionCount);

	for ( int optioncount=0;optioncount<SetOptionCount;optioncount++)
	{
		int OptionTableIndex = SetOptionTable[optioncount];
		int OptionTableCount = SetOptionCountTable[optioncount];

		if ( OptionTableCount >= 2 )
		{
			gSetItemOption.IsRequireClass(OptionTableIndex, lpObj->Class, lpObj->ChangeUP);

			for ( int tablecnt=0;tablecnt<(OptionTableCount-1);tablecnt++)
			{
				if ( gSetItemOption.GetSetOption(OptionTableIndex, tablecnt,
					op1, op2, opvalue1, opvalue2, lpObj->Class, lpObj->ChangeUP) )
				{
					gObjSetItemStatPlusSpecial(lpObj, op1, opvalue1);
					gObjSetItemStatPlusSpecial(lpObj, op2, opvalue2);
				}
			}

			if ( gSetItemOption.GetMaxSetOptionCount(OptionTableIndex) < OptionTableCount )
			{
				lpObj->IsFullSetItem = true;
				LogAddC(2, "풀옵션 적용");

				gSetItemOption.GetGetFullSetOption(OptionTableIndex, op1, op2, op3, op4, op5, opvalue1, opvalue2, opvalue3, opvalue4, opvalue5,	lpObj->Class, lpObj->ChangeUP);

				gObjSetItemStatPlusSpecial(lpObj, op1, opvalue1);
				gObjSetItemStatPlusSpecial(lpObj, op2, opvalue2);
				gObjSetItemStatPlusSpecial(lpObj, op3, opvalue3);
				gObjSetItemStatPlusSpecial(lpObj, op4, opvalue4);
				gObjSetItemStatPlusSpecial(lpObj, op5, opvalue5);
			}		
		}
	}

	for (int optioncount=0;optioncount<SetOptionCount;optioncount++)
	{
		int OptionTableIndex = SetOptionTable[optioncount];
		int OptionTableCount = SetOptionCountTable[optioncount];

		if ( OptionTableCount >= 2 )
		{
			LogAdd("[%s][%s] 세트 %s옵션 적용",	lpObj->AccountID, lpObj->Name, gSetItemOption.GetSetOptionName(OptionTableIndex));

			for ( int tablecnt=0;tablecnt<(OptionTableCount-1);tablecnt++)
			{
				if ( gSetItemOption.GetSetOption(OptionTableIndex, tablecnt, op1, op2, opvalue1, opvalue2, lpObj->Class, lpObj->ChangeUP) )
				{
					gObjSetItemPlusSpecial(lpObj, op1, opvalue1);
					gObjSetItemPlusSpecial(lpObj, op2, opvalue2);
				}
			}
				
			if ( gSetItemOption.GetMaxSetOptionCount(OptionTableIndex) < OptionTableCount )
			{
				LogAddC(2, "풀옵션 적용");
				lpObj->IsFullSetItem = true;

				gSetItemOption.GetGetFullSetOption(OptionTableIndex, op1, op2, op3, op4, op5, opvalue1, opvalue2, opvalue3, opvalue4, opvalue5, lpObj->Class, lpObj->ChangeUP);

				gObjSetItemPlusSpecial(lpObj, op1, opvalue1);
				gObjSetItemPlusSpecial(lpObj, op2, opvalue2);
				gObjSetItemPlusSpecial(lpObj, op3, opvalue3);
				gObjSetItemPlusSpecial(lpObj, op4, opvalue4);
				gObjSetItemPlusSpecial(lpObj, op5, opvalue5);

				/*if(g_bAbilityDebug == 1)
				{
					char szTemp[256];
					strcpy(szTemp, "Apply FullSet Option");
					GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
				}*/
			}		
		}
	}
}

void gObjSetItemStatPlusSpecial(LPOBJ lpObj, int option, int ivalue)
{
	if ( option == -1 )
		return;

	if(ivalue <= 0)
	{
		return;
	}

	switch ( option )
	{
		case AT_SET_OPTION_IMPROVE_STRENGTH:
			lpObj->AddStrength += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_DEXTERITY:
			lpObj->AddDexterity += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_ENERGY:
			lpObj->AddEnergy += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_VITALITY:
			lpObj->AddVitality += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_LEADERSHIP: //season4 add-on
			lpObj->AddLeadership += ivalue;
			break;
	}
}

void gObjSetItemPlusSpecial(LPOBJ lpObj, int option, int ivalue)
{
	if ( option == -1 )
		return;

	if(ivalue <= 0)
	{
		return;
	}

	switch ( option )
	{
		case AT_SET_OPTION_DOUBLE_DAMAGE:
			lpObj->SetOpDoubleDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_SHIELD_DEFENCE:
			lpObj->SetOpImproveSheldDefence += ivalue;
			break;
		case AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE:
			lpObj->SetOpTwoHandSwordImproveDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MINATTACKDAMAGE:
			lpObj->SetOpAddMinAttackDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAXATTACKDAMAGE:
			lpObj->SetOpAddMaxAttackDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAGICDAMAGE:
			lpObj->SetOpAddMagicPower += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_DAMAGE:
			lpObj->SetOpAddDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_ATTACKRATE:
			lpObj->SetOpImproveSuccessAttackRate += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_DEFENCE:
			lpObj->SetOpAddDefence += ivalue;
			break;
		case AT_SET_OPTION_DEFENCE_IGNORE:
			lpObj->SetOpIgnoreDefense += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAXLIFE:
			lpObj->AddLife += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAXMANA:
			lpObj->AddMana += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAXAG:
			lpObj->AddBP += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_AG_VALUE:
			lpObj->SetOpIncAGValue += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_CRITICALDAMAGE:
			lpObj->SetOpAddCriticalDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_CRITICALDAMAGE_SUCCESS:
			lpObj->SetOpAddCriticalDamageSuccessRate += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_EX_DAMAGE:
			lpObj->SetOpAddExDamage += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_EX_DAMAGE_SUCCESS:
			lpObj->SetOpAddExDamageSuccessRate += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_SKILLDAMAGE:
			lpObj->SetOpAddSkillAttack += ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_ATTACKDAMAGE_WITH_DEX:
			lpObj->SetOpAddAttackDamage += ( lpObj->Dexterity + lpObj->AddDexterity ) / ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_ATTACKDAMAGE_WITH_STR:
			lpObj->SetOpAddAttackDamage += ( lpObj->Strength + lpObj->AddStrength ) / ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_MAGICDAMAGE_WITH_ENERGY:
			lpObj->SetOpAddMagicPower += ( lpObj->Energy + lpObj->AddEnergy ) / ivalue;
			break;
		case AT_SET_OPTION_IMPROVE_DEFENCE_WITH_DEX:
			lpObj->SetOpAddDefence += lpObj->Dexterity + ( lpObj->AddDexterity  / ivalue );
			break;
		case AT_SET_OPTION_IMPROVE_DEFENCE_WITH_VIT:
			lpObj->SetOpAddDefence += ( lpObj->Vitality + lpObj->AddVitality ) / ivalue;
			break;
		case AT_SET_OPTION_FIRE_MASTERY:
			lpObj->m_AddResistance[R_FIRE] += ivalue;
			break;
		case AT_SET_OPTION_ICE_MASTERY:
			lpObj->m_AddResistance[R_ICE] += ivalue;
			break;
		case AT_SET_OPTION_THUNDER_MASTERY:
			lpObj->m_AddResistance[R_LIGHTNING] += ivalue;
			break;
		case AT_SET_OPTION_POSION_MASTERY:
			lpObj->m_AddResistance[R_POISON] += ivalue;
			break;
		case AT_SET_OPTION_WATER_MASTERY:
			lpObj->m_AddResistance[R_WATER] += ivalue;
			break;
		case AT_SET_OPTION_WIND_MASTERY:
			lpObj->m_AddResistance[R_WIND] += ivalue;
			break;
		case AT_SET_OPTION_EARTH_MASTERY:
			lpObj->m_AddResistance[R_EARTH] += ivalue;
			break;
	}
}

void gObjSetItemApply(LPOBJ lpObj)
{
	lpObj->m_AttackDamageMinLeft += lpObj->SetOpAddAttackDamage;
	lpObj->m_AttackDamageMaxLeft += lpObj->SetOpAddAttackDamage;
	lpObj->m_AttackDamageMinRight += lpObj->SetOpAddAttackDamage;
	lpObj->m_AttackDamageMaxRight += lpObj->SetOpAddAttackDamage;

	lpObj->m_AttackDamageMinLeft += lpObj->SetOpAddMinAttackDamage;
	lpObj->m_AttackDamageMinRight += lpObj->SetOpAddMinAttackDamage;

	lpObj->m_AttackDamageMaxLeft += lpObj->SetOpAddMaxAttackDamage;
	lpObj->m_AttackDamageMaxRight += lpObj->SetOpAddMaxAttackDamage;

	lpObj->m_MagicDamageMin += lpObj->m_MagicDamageMin * lpObj->SetOpAddMagicPower / 100;
	lpObj->m_MagicDamageMax += lpObj->m_MagicDamageMax * lpObj->SetOpAddMagicPower / 100;

	lpObj->AddLife += INT(lpObj->AddVitality * DCInfo.DefClass[lpObj->Class].VitalityToLife);
	lpObj->AddMana += INT(lpObj->AddEnergy * DCInfo.DefClass[lpObj->Class].EnergyToMana);

	lpObj->m_CriticalDamage += lpObj->SetOpAddCriticalDamageSuccessRate;
	lpObj->m_ExcelentDamage += lpObj->SetOpAddExDamageSuccessRate;

	if ( lpObj->pInventory[10].IsSetItem() )
	{
		lpObj->pInventory[10].PlusSpecialSetRing((LPBYTE)lpObj->m_AddResistance);
	}

	if ( lpObj->pInventory[11].IsSetItem() )
	{
		lpObj->pInventory[11].PlusSpecialSetRing((LPBYTE)lpObj->m_AddResistance);
	}

	if ( lpObj->pInventory[9].IsSetItem() )
	{
		lpObj->pInventory[9].PlusSpecialSetRing((LPBYTE)lpObj->m_AddResistance);
	}

	if ( lpObj->SetOpTwoHandSwordImproveDamage )
	{
		if ( !lpObj->pInventory[1].IsItem() && !lpObj->pInventory[0].IsItem() )
		{
			lpObj->SetOpTwoHandSwordImproveDamage = 0;
		}

		if ( lpObj->pInventory[1].IsItem() && lpObj->pInventory[1].m_TwoHand == FALSE )
		{
			lpObj->SetOpTwoHandSwordImproveDamage = 0;
		}

		if ( lpObj->pInventory[0].IsItem() && lpObj->pInventory[0].m_TwoHand == FALSE )
		{
			lpObj->SetOpTwoHandSwordImproveDamage = 0;
		}
	}

	if(lpObj->MLInfoLoad == 1 && lpObj->ChangeUP3rd == 0) //season4.5 add-on
	{
		if ( (lpObj->MaxLife + lpObj->AddLife ) < lpObj->Life )
		{
			lpObj->Life = lpObj->MaxLife + lpObj->AddLife;
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0, lpObj->iShield);
		}
	}

	gObjSetBP(lpObj->m_Index);

	if ( (lpObj->MaxMana + lpObj->AddMana ) < lpObj->Mana )
	{
		lpObj->Mana = lpObj->MaxMana + lpObj->AddMana;
		GCManaSend(lpObj->m_Index, lpObj->Mana, 0xFF, 0, lpObj->BP);
	}

	lpObj->m_Defense += lpObj->SetOpAddDefence * 10 / 20;
	lpObj->m_Defense += lpObj->m_Defense * lpObj->SetOpAddDefenceRate / 100;

	if ( lpObj->pInventory[1].m_Type >= ITEMGET(6,0) && lpObj->pInventory[1].m_Type < ITEMGET(7,0) )
	{
		lpObj->m_Defense += lpObj->m_Defense * lpObj->SetOpImproveSheldDefence / 100;
	}

	//season4 removed... Why? :|
	//lpObj->m_Defense += lpObj->m_MLPassiveSkill.m_iML_DefenseIncrease; //season3 add-on
}

BOOL gObjValidItem(LPOBJ lpObj, CItem * lpItem, int pos)
{
	LPITEM_ATTRIBUTE p = &ItemAttribute[lpItem->m_Type];
	
	if ( p->RequireStrength != 0 )
	{
		if ( (lpObj->Strength + lpObj->AddStrength) < ( lpItem->m_RequireStrength - lpItem->m_HJOpStrength ) )
		{
			return FALSE;
		}
	}

	if ( p->RequireDexterity != 0 )
	{
		if ( (lpObj->Dexterity + lpObj->AddDexterity) < ( lpItem->m_RequireDexterity - lpItem->m_HJOpDexterity ) )
		{
			return FALSE;
		}
	}


	if ( p->RequireEnergy != 0 )
	{
		if ( (lpObj->Energy + lpObj->AddEnergy) < lpItem->m_RequireEnergy )
		{
			return FALSE;
		}
	}

	if ( p->RequireLeadership != 0 )
	{
		if ( (lpObj->Leadership + lpObj->AddLeadership ) < lpItem->m_RequireLeaderShip )
		{
			return FALSE;
		}
	}

	if ( p->RequireLevel != 0 )
	{
		if ( (lpObj->Level) < lpItem->m_RequireLevel )
		{
			return FALSE;
		}
	}

	if ( lpItem->m_Type >= ITEMGET(0,0) && lpItem->m_Type <= ITEMGET(11, 0) )
	{
		if ( p->RequireVitality )
		{
			if ( (lpObj->Vitality + lpObj->AddVitality ) < lpItem->m_RequireVitality )
			{
				return FALSE;
			}
		}

		if ( p->RequireLeadership )
		{
			if ( (lpObj->Leadership + lpObj->AddLeadership ) < lpItem->m_RequireLeaderShip )
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}
	
void gObjCalcShieldPoint(LPOBJ lpObj) //0040290F
{
	int iMaxShieldPoint = 0;
	int iExpressionA;
	int iExpressionB;
	int iBaseLevel;

	iExpressionA = ( lpObj->Strength + lpObj->AddStrength ) + ( lpObj->Dexterity + lpObj->AddDexterity ) + ( lpObj->Vitality + lpObj->AddVitality ) + (lpObj->Energy + lpObj->AddEnergy );

	if ( lpObj->Class == CLASS_DARKLORD )
	{
		iExpressionA += lpObj->Leadership + lpObj->AddLeadership;
	}

	if ( g_iShieldGageConstB == 0 )
	{
		g_iShieldGageConstB = 30;
	}

	iBaseLevel = lpObj->Level + lpObj->MLevel;

	iExpressionB = ( iBaseLevel * iBaseLevel) / g_iShieldGageConstB;

	if ( g_iShieldGageConstA == 0 )
	{
		g_iShieldGageConstA = 12;
	}

	iMaxShieldPoint = ( iExpressionA * g_iShieldGageConstA ) / 10 + iExpressionB  + lpObj->m_Defense;
	lpObj->iMaxShield = iMaxShieldPoint;
}

//0053aca0	-> Some missing
void gObjCalcMLSkillItemOption(LPOBJ lpObj)	//OK
{
	if( lpObj->m_MPSkillOpt.MpsTwoHandSwordStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() && lpObj->pInventory[1].GetDetailItemType() )
		{
			lpObj->m_MPSkillOpt.MpsTwoHandSwordStrength = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsTwoHandSwordMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() && lpObj->pInventory[1].GetDetailItemType() )
		{
			lpObj->m_MPSkillOpt.MpsTwoHandSwordMastery = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsTwoHandStaffStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 5 || lpObj->pInventory[1].GetDetailItemType() == 5 )
		{
			lpObj->m_MagicDamageMin += lpObj->m_MPSkillOpt.MpsTwoHandStaffStrength;
			lpObj->m_MagicDamageMax += lpObj->m_MPSkillOpt.MpsTwoHandStaffStrength;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsOneHandStaffStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 4 || lpObj->pInventory[1].GetDetailItemType() == 4 )
		{
			lpObj->m_MagicDamageMin += lpObj->m_MPSkillOpt.MpsOneHandStaffStrength;
			lpObj->m_MagicDamageMax += lpObj->m_MPSkillOpt.MpsOneHandStaffStrength;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsStickStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 9 || lpObj->pInventory[1].GetDetailItemType() == 9 )
		{
			lpObj->m_MagicDamageMin += lpObj->m_MPSkillOpt.MpsStickStrength;
			lpObj->m_MagicDamageMax += lpObj->m_MPSkillOpt.MpsStickStrength;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsShieldStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 6 || lpObj->pInventory[1].GetDetailItemType() == 6 )
		{
			lpObj->m_Defense += lpObj->m_MPSkillOpt.MpsShieldStrength;
			//lpObj->m_Defense +=
		}
	}
	// ----
	//
	// ----
	if( lpObj->m_MPSkillOpt.MpsShieldStrength3 > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 6 || lpObj->pInventory[1].GetDetailItemType() == 6 )
		{
			lpObj->m_Defense += lpObj->m_MPSkillOpt.MpsShieldStrength3;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsOneHandStaffMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 4 || lpObj->pInventory[1].GetDetailItemType() == 4 )
		{
			lpObj->m_AttackSpeed += lpObj->m_MPSkillOpt.MpsOneHandStaffMastery;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsTomeMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 10 || lpObj->pInventory[1].GetDetailItemType() == 10 )
		{
			lpObj->m_AttackSpeed += lpObj->m_MPSkillOpt.MpsTomeMastery;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsTomeStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 10 || lpObj->pInventory[1].GetDetailItemType() == 10 )
		{
			lpObj->m_iSummonerBookSpellDamageMin += lpObj->m_MPSkillOpt.MpsTomeStrength;
			lpObj->m_iSummonerBookSpellDamageMax += lpObj->m_MPSkillOpt.MpsTomeStrength;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsTwoHandStaffMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 5 && lpObj->pInventory[1].GetDetailItemType() != 5 )
		{
			lpObj->m_MPSkillOpt.MpsTwoHandStaffMastery = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsCrossbowMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 8 && lpObj->pInventory[1].GetDetailItemType() != 8 )
		{
			lpObj->m_MPSkillOpt.MpsCrossbowMastery = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsStickMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 9 && lpObj->pInventory[1].GetDetailItemType() != 9 )
		{
			lpObj->m_MPSkillOpt.MpsStickMastery = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsScepterMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 11 && lpObj->pInventory[1].GetDetailItemType() != 11 )
		{
			lpObj->m_MPSkillOpt.MpsScepterMastery = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsShieldMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 6 && lpObj->pInventory[1].GetDetailItemType() != 6 )
		{
			lpObj->m_MPSkillOpt.MpsShieldMastery = 0;
		}
	}
	// ----
	//
	// ----
	if( lpObj->m_MPSkillOpt.MpsShieldMastery3 > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 6 && lpObj->pInventory[1].GetDetailItemType() != 6 )
		{
			lpObj->m_MPSkillOpt.MpsShieldMastery3 = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsOneHandSwordMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() == 1 && lpObj->pInventory[1].GetDetailItemType() == 1 )
		{
			lpObj->m_AttackSpeed += lpObj->m_MPSkillOpt.MpsOneHandSwordMastery;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsOneHandSwordStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 1 && lpObj->pInventory[1].GetDetailItemType() != 1 )
		{
			lpObj->m_MPSkillOpt.MpsOneHandSwordStrength = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsMaceStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 2 && lpObj->pInventory[1].GetDetailItemType() != 2 )
		{
			lpObj->m_MPSkillOpt.MpsMaceStrength = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsMaceMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 2 && lpObj->pInventory[1].GetDetailItemType() != 2 )
		{
			lpObj->m_MPSkillOpt.MpsMaceMastery = 0;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsSpearStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 3 && lpObj->pInventory[1].GetDetailItemType() != 3 )
		{
			lpObj->m_MPSkillOpt.MpsSpearStrength = 0;
		} 
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsSpearMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 3 && lpObj->pInventory[1].GetDetailItemType() != 3 )
		{
			lpObj->m_MPSkillOpt.MpsSpearMastery = 0;
		} 
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsBowStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 7 && lpObj->pInventory[1].GetDetailItemType() != 7 )
		{
			lpObj->m_MPSkillOpt.MpsBowStrength = 0;
		} 
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsScepterStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 11 && lpObj->pInventory[1].GetDetailItemType() != 11 )
		{
			lpObj->m_MPSkillOpt.MpsScepterStrength = 0;
		} 
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsUseScepterPetStr > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 11 && lpObj->pInventory[1].GetDetailItemType() != 11 )
		{
			lpObj->m_MPSkillOpt.MpsUseScepterPetStr = 0;
		} 
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsFistMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 12 && lpObj->pInventory[1].GetDetailItemType() != 12 )
		{
			lpObj->m_MPSkillOpt.MpsFistMastery = 0;
		} 
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsFistStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 12 && lpObj->pInventory[1].GetDetailItemType() != 12 )
		{
			lpObj->m_MPSkillOpt.MpsFistStrength = 0;
		} 
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsCommandAttackInc > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 11 && lpObj->pInventory[1].GetDetailItemType() != 11 )
		{
			lpObj->m_MPSkillOpt.MpsCommandAttackInc = 0;
		} 
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsBowMastery > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 7 && lpObj->pInventory[1].GetDetailItemType() != 7 )
		{
			lpObj->m_AttackSpeed += lpObj->m_MPSkillOpt.MpsBowMastery;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsCrossbowStrength > 0.0f )
	{
		if( lpObj->pInventory[0].GetDetailItemType() != 8 && lpObj->pInventory[1].GetDetailItemType() != 8 )
		{
			lpObj->m_MPSkillOpt.MpsCrossbowStrength = 0;
		}
	}
	// ----
	//
}
