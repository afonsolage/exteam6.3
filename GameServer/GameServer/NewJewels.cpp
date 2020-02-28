#include "StdAfx.h"
#include "user.h"
#include "NewJewels.h"
#include "Configs.h"
#include "LuckyItem.h"
#include "Functions.h"
#include "..\common\SetItemOption.h"
#include "logproc.h"
#include "ExFunction.h"
#include "ExLicense.h"
#include "ItemSystemFor380.h"
#include "ObjUseSkill.h"
#include "ExText.h"

cNewJewels gNewJewels;

/*
			if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x50;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x53;
			}

					if( (this->m_NewOption & 0x10) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x50;
			}
			else if( (this->m_NewOption & 0x20) != FALSE )
			{
				this->m_Special[this->m_SpecialNum] = 0x53;
			}

			1 - Ignore Defence
			2 - Return Attack
			3 - Recovery Life
			4 - Recovery Mana
			5 - 
			6 - 

*/


BYTE GetNewWingExlOpt(BYTE NOption)
{
	int iEmptyCount = 0;
	int iCount = 0;
	int arrOption[4] = { 0, 0, 0, 0 };
	// ----
	if((NOption&1) == 1)
	{
		iCount++;
	}
	else
	{
		arrOption[iEmptyCount] = 1;
		iEmptyCount++;
	}
	// ----
	if((NOption&2) == 2)
	{
		iCount++;
	}
	else
	{
		arrOption[iEmptyCount] = 2;
		iEmptyCount++;
	}
	// ----
	if((NOption&4) == 4)
	{
		iCount++;
	}
	else
	{
		arrOption[iEmptyCount] = 4;
		iEmptyCount++;
	}
	// ----
	if((NOption&8) == 8)
	{
		iCount++;
	}
	else
	{
		arrOption[iEmptyCount] = 8;
		iEmptyCount++;
	}
	// ----
	if(iEmptyCount == 0)
	{
		return 0;
	}
	// ----
	int iRand = rand()%iEmptyCount;
	// ----
	return arrOption[iRand];
}


BYTE NumOfExcOptions(int NOption)
{
	if(NOption == 0)
		return 0;

	int Cnt = 0;

	if ( (NOption & 1) == 1 )
		Cnt++;
	if ( (NOption & 2) == 2 )
		Cnt++;
	if ( (NOption & 4) == 4 )
		Cnt++;
	if ( (NOption & 8) == 8 )
		Cnt++;
	if ( (NOption & 16) == 16 )
		Cnt++;
	if ( (NOption & 32) == 32 )
		Cnt++;

	return Cnt;
}

BYTE NumOfWingExcOptions(int NOption)
{
	if(NOption == 0)
		return 0;

	int Cnt = 0;

	if ( (NOption & 1) == 1 )
		Cnt++;
	if ( (NOption & 2) == 2 )
		Cnt++;
	if ( (NOption & 4) == 4 )
		Cnt++;
	if ( (NOption & 8) == 8 )
		Cnt++;

	return Cnt;
}

BYTE GetExcWingOption(BYTE ExcellentOption)
{
	int arrayopt[4]	= { 0, 0, 0, 0 };
	int num			= 8;
	int amountopt	= 0;
	int added		= 0;
	// ----
	for( int i = 3; i >= 0; i-- )
	{
		if( ExcellentOption >= num )
		{
			arrayopt[i] = 1;
			amountopt++;
			ExcellentOption -= num;
		}
		num = num / 2;
	}
	// ----

	int iRand = (4-amountopt)+1;

	if(iRand == 0)
	{
		return 0;
	}

	int randomopt = rand()%iRand;

	amountopt = 0;

	for(int i=0; i<4; i++)
	{
		if(!arrayopt[i])
		{ 
			amountopt++;
			if( amountopt == randomopt )
			{
				arrayopt[i] = 1;
				break;
			}
		}
		else
		{
			continue;
		}
	}

	num = 1; 
	ExcellentOption = 0;

	for (int i=0 ; i<4; i++)
	{
		if (arrayopt[i])
		{
			ExcellentOption += num;
		}
		num = num * 2;
	}

	return ExcellentOption;
}

void cNewJewels::Load()
{
	//CheckFile(NewJewels_DIR);
	this->Enable  = GetPrivateProfileInt("Common","Enable",0,NewJewels_DIR);

	this->JewelOfExellentType = GetPrivateProfileInt("Common","JewelOfExellentType",0,NewJewels_DIR);
	this->JewelOfExellentIndex = GetPrivateProfileInt("Common","JewelOfExellentIndex",0,NewJewels_DIR);
	this->JewelOfExellentEnable = GetPrivateProfileInt("Common","JewelOfExellentEnable",0,NewJewels_DIR);
	this->JewelOfExellentRate = GetPrivateProfileInt("Common","JewelOfExellentRate",0,NewJewels_DIR);
	this->JewelOfExellentMaxOpt = GetPrivateProfileInt("Common","JewelOfExellentMaxOpt",0,NewJewels_DIR);

	this->JewelOfMisticType = GetPrivateProfileInt("Common","JewelOfMisticType",0,NewJewels_DIR);
	this->JewelOfMisticIndex = GetPrivateProfileInt("Common","JewelOfMisticIndex",0,NewJewels_DIR);
	this->JewelOfMisticEnable = GetPrivateProfileInt("Common","JewelOfMisticEnable",0,NewJewels_DIR);
	this->JewelOfMisticMaxLvl = GetPrivateProfileInt("Common","JewelOfMisticMaxLvl",0,NewJewels_DIR);
	this->JewelOfMisticMinLvl = GetPrivateProfileInt("Common","JewelOfMisticMinLvl",0,NewJewels_DIR);
	this->JewelOfMisticRate = GetPrivateProfileInt("Common","JewelOfMisticRate",0,NewJewels_DIR);

	this->JewelOfLuckType = GetPrivateProfileInt("Common","JewelOfLuckType",0,NewJewels_DIR);
	this->JewelOfLuckIndex = GetPrivateProfileInt("Common","JewelOfLuckIndex",0,NewJewels_DIR);
	this->JewelOfLuckEnable = GetPrivateProfileInt("Common","JewelOfLuckEnable",0,NewJewels_DIR);
	this->JewelOfLuckEnable = GetPrivateProfileInt("Common","JewelOfLuckEnable",0,NewJewels_DIR);
	this->JewelOfLuckRate = GetPrivateProfileInt("Common","JewelOfLuckRate",0,NewJewels_DIR);

	this->JewelOfSkillType = GetPrivateProfileInt("Common","JewelOfSkillType",0,NewJewels_DIR);
	this->JewelOfSkillIndex = GetPrivateProfileInt("Common","JewelOfSkillIndex",0,NewJewels_DIR);
	this->JewelOfSkillEnable = GetPrivateProfileInt("Common","JewelOfSkillEnable",0,NewJewels_DIR);
	this->JewelOfSkillRate = GetPrivateProfileInt("Common","JewelOfSkillRate",0,NewJewels_DIR);

	this->JewelOfLevelType = GetPrivateProfileInt("Common","JewelOfLevelType",0,NewJewels_DIR);
	this->JewelOfLevelIndex = GetPrivateProfileInt("Common","JewelOfLevelIndex",0,NewJewels_DIR);
	this->JewelOfLevelEnable = GetPrivateProfileInt("Common","JewelOfLevelEnable",0,NewJewels_DIR);
	this->JewelOfLevelMax = GetPrivateProfileInt("Common","JewelOfLevelMax",0,NewJewels_DIR);
	this->JewelOfLevelMin = GetPrivateProfileInt("Common","JewelOfLevelMin",0,NewJewels_DIR);
	this->JewelOfLevelRate = GetPrivateProfileInt("Common","JewelOfLevelRate",0,NewJewels_DIR);

	this->JewelOfEvalutionType = GetPrivateProfileInt("Common","JewelOfEvalutionType",0,NewJewels_DIR); 
	this->JewelOfEvalutionIndex = GetPrivateProfileInt("Common","JewelOfEvalutionIndex",0,NewJewels_DIR); 
	this->JewelOfEvalutionEnable = GetPrivateProfileInt("Common","JewelOfEvalutionEnable",0,NewJewels_DIR); 
	this->JewelOfEvalutionRate = GetPrivateProfileInt("Common","JewelOfEvalutionRate",0,NewJewels_DIR);

	this->JewelOfAncentType = GetPrivateProfileInt("Common","JewelOfAncentType",0,NewJewels_DIR); 
	this->JewelOfAncentIndex = GetPrivateProfileInt("Common","JewelOfAncentIndex",0,NewJewels_DIR); 
	this->JewelOfAncentEnable = GetPrivateProfileInt("Common","JewelOfAncentEnable",0,NewJewels_DIR); 
	this->JewelOfAncentRate = GetPrivateProfileInt("Common","JewelOfAncentRate",0,NewJewels_DIR); 

	this->JewelOfOptionType = GetPrivateProfileInt("Common","JewelOfOptionType",0,NewJewels_DIR); 
	this->JewelOfOptionIndex = GetPrivateProfileInt("Common","JewelOfOptionIndex",0,NewJewels_DIR); 
	this->JewelOfOptionEnable = GetPrivateProfileInt("Common","JewelOfOptionEnable",0,NewJewels_DIR); 
	this->JewelOfOptionRate = GetPrivateProfileInt("Common","JewelOfOptionRate",0,NewJewels_DIR); 

	this->JewelOfPVPEnable = 0; 
	this->JewelOfPVPRate = 0; 

	if( g_ExLicense.CheckUser(eExUB::Local)			|| 
		g_ExLicense.CheckUser(eExUB::Gredy)			|| 
		g_ExLicense.CheckUser(eExUB::GredyLocal)	|| 
		g_ExLicense.CheckUser(eExUB::Gredy2)		|| 
		g_ExLicense.CheckUser(eExUB::ulasevich)		|| 
		g_ExLicense.CheckUser(eExUB::ulasevich2)	||
		g_ExLicense.CheckUser(eExUB::EpicMU)		||
		g_ExLicense.CheckUser(eExUB::Artem)			||
		g_ExLicense.CheckUser(eExUB::Artem2))
	{
		this->JewelOfPVPType = 14;
		this->JewelOfPVPIndex = 188;
		this->JewelOfPVPEnable = GetPrivateProfileInt("Common","JewelOfPVPEnable",0,NewJewels_DIR); 
		this->JewelOfPVPRate = GetPrivateProfileInt("Common","JewelOfPVPRate",0,NewJewels_DIR); 
	}

	this->JewelOfSocketType = GetPrivateProfileInt("Common","JewelOfSocketType",0,NewJewels_DIR);
	this->JewelOfSocketIndex = GetPrivateProfileInt("Common","JewelOfSocketIndex",0,NewJewels_DIR); 
	this->JewelOfSocketEnable = GetPrivateProfileInt("Common","JewelOfSocketEnable",0,NewJewels_DIR); 
	this->JewelOfSocketRate = GetPrivateProfileInt("Common","JewelOfSocketRate",0,NewJewels_DIR); 
	this->JewelOfSocketMaxOpt = GetPrivateProfileInt("Common","JewelOfSocketMaxOpt",0,NewJewels_DIR); 
	if(this->JewelOfSocketMaxOpt > 5)
	{
		this->JewelOfSocketMaxOpt = 5;
	}

	this->JewelOfWingEnable = false;

	if(g_ExLicense.CheckUser(eExUB::Local) || THINNAKORN_MAC || 
		g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal) ||
		g_ExLicense.CheckUser(eExUB::EpicMU))
	{
		this->JewelOfWingType = GetPrivateProfileInt("Common","JewelOfWingType",0,NewJewels_DIR);
		this->JewelOfWingIndex = GetPrivateProfileInt("Common","JewelOfWingIndex",0,NewJewels_DIR);
		this->JewelOfWingEnable = GetPrivateProfileInt("Common","JewelOfWingEnable",0,NewJewels_DIR);
		this->JewelOfWingRate = GetPrivateProfileInt("Common","JewelOfWingRate",0,NewJewels_DIR);
		this->JewelOfWingMaxOpt = GetPrivateProfileInt("Common","JewelOfWingMaxOpt",0,NewJewels_DIR);
	}
}

bool cNewJewels::IsAccessory(int ItemID)
{
	if(		ItemID >= ITEMGET(13, 21) && ItemID <= ITEMGET(13, 29)
		||	ItemID == ITEMGET(13, 8)
		||	ItemID == ITEMGET(13, 9)
		||	ItemID == ITEMGET(13, 12)
		||	ItemID == ITEMGET(13, 13) )
	{
		return true;
	}
	// ----
	return false;

}

bool cNewJewels::IsWings(int ItemID)
{
	if((ItemID < ITEMGET(12,0) || ItemID > ITEMGET(12,6)) &&
		ItemID != ITEMGET(13,30) &&
		ItemID != ITEMGET(12,41) &&
		ItemID != ITEMGET(12,42) &&
		ItemID != ITEMGET(12,43) &&
		ItemID != ITEMGET(12, 49) &&//Season 6 addon
		ItemID != ITEMGET(12, 50) &&//Season 6 addon
#ifdef NEWWINGS_2_5
		!IS_NEWWINGS_2_5(ItemID) &&
#endif
#ifdef NEWWINGS_4
		!IS_NEWWINGS_4(ItemID) &&
#endif
#ifdef NEWWINGS_5
		!IS_NEWWINGS_5(ItemID) &&
#endif
#ifdef NEWWINGS_6
		!IS_NEWWINGS_6(ItemID) &&
#endif
		//Season 2.5 add-on
		(ItemID < ITEMGET(12,36) || ItemID > ITEMGET(12,40))) 
	{
		return false;
	}

	return true;
}

BYTE cNewJewels::GetExcUnusedOption(BYTE ExcellentOption)
{
	int arrayopt[6]	= { 0, 0, 0, 0, 0, 0};
	int num			= 32;
	int amountopt	= 0;
	int added		= 0;
	// ----
	for( int i = 5; i >= 0; i-- )
	{
		if( ExcellentOption >= num )
		{
			arrayopt[i] = 1;
			amountopt++;
			ExcellentOption -= num;
		}
		num = num / 2;
	}
	// ----
	int iRate = (6-amountopt)+1;
	if(iRate == 0)
	{
		return 0;
	}
	int randomopt = rand()%iRate;
	amountopt = 0;

	for(int i=0; i<6; i++)
	{
		if(!arrayopt[i])
		{ 
			amountopt++;
			if( amountopt == randomopt )
			{
				arrayopt[i] = 1;
				break;
			}
		}
		else
		{
			continue;
		}
	}

	num = 1; 
	ExcellentOption = 0;

	for (int i=0 ; i<6; i++)
	{
		if (arrayopt[i])
		{
			ExcellentOption += num;
		}
		num = num * 2;
	}

	return ExcellentOption;
}

bool cNewJewels::CheckJewel(int iType)
{
	if(iType == ITEMGET(this->JewelOfExellentType,this->JewelOfExellentIndex) && this->JewelOfExellentEnable) return true;
	else if(iType == ITEMGET(this->JewelOfMisticType,this->JewelOfMisticIndex) && this->JewelOfMisticEnable) return true;
	else if(iType == ITEMGET(this->JewelOfLuckType,this->JewelOfLuckIndex) && this->JewelOfLuckEnable) return true;
	else if(iType == ITEMGET(this->JewelOfSkillType,this->JewelOfSkillIndex) && this->JewelOfSkillEnable) return true;
	else if(iType == ITEMGET(this->JewelOfLevelType,this->JewelOfLevelIndex) && this->JewelOfLevelEnable) return true;
	else if(iType == ITEMGET(this->JewelOfEvalutionType,this->JewelOfEvalutionIndex) && this->JewelOfEvalutionEnable) return true;
	else if(iType == ITEMGET(this->JewelOfAncentType,this->JewelOfAncentIndex) && this->JewelOfAncentEnable) return true;
	else if(iType == ITEMGET(this->JewelOfOptionType,this->JewelOfOptionIndex) && this->JewelOfOptionEnable) return true;

	if( g_ExLicense.CheckUser(eExUB::Local)			|| 
		g_ExLicense.CheckUser(eExUB::Gredy)			|| 
		g_ExLicense.CheckUser(eExUB::GredyLocal)	|| 
		g_ExLicense.CheckUser(eExUB::Gredy2)		|| 
		g_ExLicense.CheckUser(eExUB::ulasevich)		|| 
		g_ExLicense.CheckUser(eExUB::ulasevich2)	||
		g_ExLicense.CheckUser(eExUB::EpicMU)		||
		g_ExLicense.CheckUser(eExUB::Artem)			||
		g_ExLicense.CheckUser(eExUB::Artem2))
	{
		if(iType == ITEMGET(this->JewelOfPVPType,this->JewelOfPVPIndex) || iType == ITEMGET(this->JewelOfPVPType,189) && this->JewelOfPVPEnable) return true;
	}

	if(iType == ITEMGET(this->JewelOfSocketType,this->JewelOfSocketIndex) && this->JewelOfSocketEnable) return true;

	if(g_ExLicense.CheckUser(eExUB::Local) || THINNAKORN_MAC ||
	   g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		if(iType == ITEMGET(this->JewelOfWingType,this->JewelOfWingIndex) && this->JewelOfWingEnable) 
		{
			return true;
		}
	}

	return false;
}

void cNewJewels::JewelMain(LPOBJ lpObj, int source, int target)
{
	if( source < 0 || source > MAIN_INVENTORY_SIZE - 1 )
	{
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		return;
	}
	// ----
	if( target < 0 || target > MAIN_INVENTORY_SIZE - 1 )
	{
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		return;
	}
	// ----
	if( !lpObj->pInventory[source].IsItem() || !lpObj->pInventory[target].IsItem() )
	{
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		return;
	}
#ifdef LUCKYITEM
	if(g_LuckyItemManager.IsLuckyItemEquipment(lpObj->pInventory[target].m_Type))
	{
		return;
	}
#endif

	int JewelIndex = lpObj->pInventory[source].m_Type;
	int TargetIndex = lpObj->pInventory[target].m_Type;
	int TargetLevel = lpObj->pInventory[target].m_Level;

	if(TargetLevel > 15)
	{
		GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		return;
	}

	//srand(time(NULL));

	int iRate = rand()%100;

	bool JewelAdded = false;
//*************************************
//	Jewel Of Exellent
//*************************************
	if( JewelIndex == ITEMGET(this->JewelOfExellentType,this->JewelOfExellentIndex) )
	{
		if( this->JewelOfExellentRate > iRate )
		{
			if( lpObj->pInventory[target].m_Type < ITEMGET(12,0) || this->IsAccessory(lpObj->pInventory[target].m_Type) == true )
			{
				if( lpObj->pInventory[target].m_NewOption > 0)
				{
					if( GetExcOptionCount(lpObj->pInventory[target].m_NewOption) < this->JewelOfExellentMaxOpt )
					{
						if(5 > GetExcOptionCount(lpObj->pInventory[target].m_NewOption) )
						{
							BYTE NewOption = this->GetExcUnusedOption(lpObj->pInventory[target].m_NewOption);
						
							lpObj->pInventory[target].m_NewOption = NewOption;
							gObjInventoryItemSet(lpObj->m_Index, source, -1);
							lpObj->pInventory[source].Clear();
							GCInventoryItemOneSend(lpObj->m_Index, target);
							GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);

							return;
						}
						else if(5 == GetExcOptionCount(lpObj->pInventory[target].m_NewOption) )
						{
							BYTE NewOption = 63;
						
							lpObj->pInventory[target].m_NewOption = NewOption;
							gObjInventoryItemSet(lpObj->m_Index, source, -1);
							lpObj->pInventory[source].Clear();
							GCInventoryItemOneSend(lpObj->m_Index, target);
							GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);

							return;
						}
						else
						{
							MsgOutput(lpObj->m_Index, g_ExText.GetText(19), this->JewelOfExellentMaxOpt);
						}
					}
				}
				else
				{
					MsgOutput(lpObj->m_Index, g_ExText.GetText(20));
				}
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Mistic
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfMisticType,this->JewelOfMisticIndex) ) //
	{
		if( this->JewelOfMisticRate > iRate )
		{
			if(this->IsAccessory(TargetIndex) == true )
			{
				if(TargetLevel >= this->JewelOfMisticMinLvl ) 
				{
					if(TargetLevel <= this->JewelOfMisticMaxLvl)
					{
						lpObj->pInventory[target].m_Level++;
						gObjInventoryItemSet(lpObj->m_Index, source, -1);
						lpObj->pInventory[source].Clear();
						GCInventoryItemOneSend(lpObj->m_Index, target);
						GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
						return;
					}
					else
					{
						MsgOutput(lpObj->m_Index, g_ExText.GetText(21),this->JewelOfMisticMaxLvl);
					}
				}
				else
				{
					MsgOutput(lpObj->m_Index, g_ExText.GetText(22),this->JewelOfMisticMinLvl);
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index, g_ExText.GetText(23));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Luck
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfLuckType,this->JewelOfLuckIndex) ) 
	{
		if( this->JewelOfLuckRate > iRate )
		{
			if(lpObj->pInventory[target].m_Type < ITEMGET(12,0)
#ifdef NEW_JEWEL_FROM_WINGS
				|| (lpObj->pInventory[target].m_Type >= ITEMGET(12,0) && lpObj->pInventory[target].m_Type <= ITEMGET(12,6)) || lpObj->pInventory[target].m_Type <= ITEMGET(13,30) || 
				 (lpObj->pInventory[target].m_Type >= ITEMGET(12,36) && lpObj->pInventory[target].m_Type <= ITEMGET(12,40)) || //Season 2.5 Third Wing add-on
				 lpObj->pInventory[target].m_Type == ITEMGET(12,41) || lpObj->pInventory[target].m_Type == ITEMGET(12,42) || lpObj->pInventory[target].m_Type == ITEMGET(12,43)
				 || lpObj->pInventory[target].m_Type == ITEMGET(12, 49)
				 || lpObj->pInventory[target].m_Type == ITEMGET(12, 50)
				|| IS_NEWWINGS(lpObj->pInventory[target].m_Type)
				|| IS_NEWWINGS_6(lpObj->pInventory[target].m_Type)
#endif // NEW_JEWEL_FROM_WINGS
				)
			{
				if(lpObj->pInventory[target].m_Option2 == 0)
				{
					lpObj->pInventory[target].m_Option2++;
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index, g_ExText.GetText(24));
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index, g_ExText.GetText(25));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Skill
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfSkillType,this->JewelOfSkillIndex) )
	{
		if( this->JewelOfSkillRate > iRate )
		{
			if(ItemAttribute[lpObj->pInventory[target].m_Type].SkillType != 0)
			{
				if(lpObj->pInventory[target].m_Option1 == 0)
				{
					lpObj->pInventory[target].m_Option1 = TRUE;
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);

					//GCMagicListMultiSend(lpObj, 0);//
	//GCMagicListMultiSend(lpObj, 0);
	//gObjUseSkill.SkillChangeUse(lpObj->m_Index);

					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index, g_ExText.GetText(26));
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index, g_ExText.GetText(27));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Level
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfLevelType,this->JewelOfLevelIndex) ) 
	{
		if( this->JewelOfLevelRate > iRate )
		{
			if(lpObj->pInventory[target].m_Type < ITEMGET(12,0)
#ifdef NEW_JEWEL_FROM_WINGS
				|| (lpObj->pInventory[target].m_Type >= ITEMGET(12,0) && lpObj->pInventory[target].m_Type <= ITEMGET(12,6)) || lpObj->pInventory[target].m_Type <= ITEMGET(13,30) || 
				 (lpObj->pInventory[target].m_Type >= ITEMGET(12,36) && lpObj->pInventory[target].m_Type <= ITEMGET(12,40)) || //Season 2.5 Third Wing add-on
				 lpObj->pInventory[target].m_Type == ITEMGET(12,41) || lpObj->pInventory[target].m_Type == ITEMGET(12,42) || lpObj->pInventory[target].m_Type == ITEMGET(12,43)
				 || lpObj->pInventory[target].m_Type == ITEMGET(12, 49)
				 || lpObj->pInventory[target].m_Type == ITEMGET(12, 50)
				|| IS_NEWWINGS(lpObj->pInventory[target].m_Type)
				|| IS_NEWWINGS_6(lpObj->pInventory[target].m_Type)
#endif // NEW_JEWEL_FROM_WINGS
				)
			{
				if(TargetLevel >= this->JewelOfLevelMin)
				{
					if(TargetLevel < this->JewelOfLevelMax)
					{
						lpObj->pInventory[target].m_Level++;
						gObjInventoryItemSet(lpObj->m_Index, source, -1);
						lpObj->pInventory[source].Clear();
						GCInventoryItemOneSend(lpObj->m_Index, target);
						GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
						return;
					}
					else
					{
						MsgOutput(lpObj->m_Index,g_ExText.GetText(28),this->JewelOfLevelMax);
					}
				}
				else
				{
					MsgOutput(lpObj->m_Index,g_ExText.GetText(29),this->JewelOfLevelMin);
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,g_ExText.GetText(30));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}		
//*************************************
//	Jewel Of Evalution
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfEvalutionType,this->JewelOfEvalutionIndex) )
	{
		if( this->JewelOfEvalutionRate > iRate )
		{
			if(lpObj->pInventory[target].m_Type < ITEMGET(12,0) || this->IsAccessory(lpObj->pInventory[target].m_Type) == true)
			{
				if(lpObj->pInventory[target].m_NewOption == 0)
				{
						int ExcellentOpt[6] = { 1, 2, 4, 8, 16, 32 };
						srand(time(NULL));
						lpObj->pInventory[target].m_NewOption = ExcellentOpt[rand()%6];
						gObjInventoryItemSet(lpObj->m_Index, source, -1);
						lpObj->pInventory[source].Clear();
						GCInventoryItemOneSend(lpObj->m_Index, target);
						GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
						return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,g_ExText.GetText(31));
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,g_ExText.GetText(32));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Ancent
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfAncentType,this->JewelOfAncentIndex) )
	{
		if( this->JewelOfAncentRate > iRate )
		{
			if(lpObj->pInventory[target].m_SetOption == 0)
			{
				if(gSetItemOption.IsSetItem(TargetIndex) != FALSE)
				{
					lpObj->pInventory[target].m_SetOption = gSetItemOption.ExGenSetOption(TargetIndex);
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,g_ExText.GetText(33));
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,g_ExText.GetText(34));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Option
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfOptionType,this->JewelOfOptionIndex) ) //JewelOfOption
	{
		if( this->JewelOfOptionRate > iRate )
		{
			if(lpObj->pInventory[target].m_Type < ITEMGET(12,0)
#ifdef NEW_JEWEL_FROM_WINGS
				|| (lpObj->pInventory[target].m_Type >= ITEMGET(12,0) && lpObj->pInventory[target].m_Type <= ITEMGET(12,6)) || lpObj->pInventory[target].m_Type <= ITEMGET(13,30) || 
				 (lpObj->pInventory[target].m_Type >= ITEMGET(12,36) && lpObj->pInventory[target].m_Type <= ITEMGET(12,40)) || //Season 2.5 Third Wing add-on
				 lpObj->pInventory[target].m_Type == ITEMGET(12,41) || lpObj->pInventory[target].m_Type == ITEMGET(12,42) || lpObj->pInventory[target].m_Type == ITEMGET(12,43)
				 || lpObj->pInventory[target].m_Type == ITEMGET(12, 49)
				 || lpObj->pInventory[target].m_Type == ITEMGET(12, 50)
				|| IS_NEWWINGS(lpObj->pInventory[target].m_Type)
				|| IS_NEWWINGS_6(lpObj->pInventory[target].m_Type)
#endif // NEW_JEWEL_FROM_WINGS
				)
			{
				if(lpObj->pInventory[target].m_Option3 != 7)
				{
					lpObj->pInventory[target].m_Option3 = 7;
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,g_ExText.GetText(35));
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,g_ExText.GetText(32));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}	
//*************************************
//	Jewel Of PVP
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfPVPType,this->JewelOfPVPIndex) || JewelIndex == ITEMGET(this->JewelOfOptionType,189))
	{
		if( this->JewelOfPVPRate > iRate )
		{
			if( g_kItemSystemFor380.m_bSystemFor380ItemOption == TRUE &&
				g_kItemSystemFor380.Is380OptionItem(&lpObj->pInventory[target]) == FALSE)
			{
				if(g_kItemSystemFor380.Is380Item(&lpObj->pInventory[target]) != FALSE)
				{
					g_kItemSystemFor380._SetOption(&lpObj->pInventory[target], TRUE);
					gObjInventoryItemSet(lpObj->m_Index, source, -1);
					lpObj->pInventory[source].Clear();
					GCInventoryItemOneSend(lpObj->m_Index, target);
					GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
					return;
				}
				else
				{
					MsgOutput(lpObj->m_Index,g_ExText.GetText(36));
				}
			}
			else
			{
				MsgOutput(lpObj->m_Index,g_ExText.GetText(37));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Socket
//*************************************
	else if( JewelIndex == ITEMGET(this->JewelOfSocketType,this->JewelOfSocketIndex) )
	{
		if( this->JewelOfSocketRate > iRate )
		{
			if( g_SocketOption.CheckItemType(lpObj->pInventory[target].m_Type) == true)
			{
				int iCount = 0;
				for(int i = 0; i < 5; i++)
				{
					//0xFF - no option
					//0xFE - empty option

					if(lpObj->pInventory[target].m_SocketOption[i] != 0xFF)
					{
						iCount++;
					}
				}

				if(iCount >= this->JewelOfSocketMaxOpt)
				{
					MsgOutput(lpObj->m_Index,g_ExText.GetText(38), this->JewelOfSocketMaxOpt);
					GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
					return;
				}

				for(int i = 0; i < 5; i++)
				{
					if(lpObj->pInventory[target].m_SocketOption[i] == 0xFF)
					{
						lpObj->pInventory[target].m_SocketOption[i] = 0xFE;
						break;
					}
				}		
				
				gObjInventoryItemSet(lpObj->m_Index, source, -1);
				lpObj->pInventory[source].Clear();
				GCInventoryItemOneSend(lpObj->m_Index, target);
				GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
				return;
			}
			else
			{
				MsgOutput(lpObj->m_Index,g_ExText.GetText(39));
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
//*************************************
//	Jewel Of Wings Exellent
//*************************************
	if(JewelIndex == ITEMGET(this->JewelOfWingType,this->JewelOfWingIndex))
	{
		if(this->JewelOfWingRate > iRate)
		{
			if(this->IsWings(lpObj->pInventory[target].m_Type) == true)
			{
				if(lpObj->pInventory[target].m_NewOption == 0)
				{
						int ExcellentOpt[4] = { 1, 2, 4, 8 };
						srand(time(NULL));
						
						//lpObj->pInventory[target].m_NewOption |= 32;
						//lpObj->pInventory[target].m_NewOption |= 16;
						lpObj->pInventory[target].m_NewOption |= ExcellentOpt[rand()%4];

						

						gObjInventoryItemSet(lpObj->m_Index, source, -1);
						lpObj->pInventory[source].Clear();
						GCInventoryItemOneSend(lpObj->m_Index, target);
						GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
						return;
				}
				else if(lpObj->pInventory[target].m_NewOption > 0)
				{
					if(NumOfWingExcOptions(lpObj->pInventory[target].m_NewOption) < this->JewelOfWingMaxOpt)
					{
						if(5 > NumOfWingExcOptions(lpObj->pInventory[target].m_NewOption))
						{
							//BYTE NewOption = GetExcWingOption(lpObj->pInventory[target].m_NewOption);
							//BYTE NewOption = this->GetExcUnusedOption(lpObj->pInventory[target].m_NewOption);
							//lpObj->pInventory[target].m_NewOption = NewOption;

							BYTE NewOption = GetNewWingExlOpt(lpObj->pInventory[target].m_NewOption);
							lpObj->pInventory[target].m_NewOption |= NewOption;

							gObjInventoryItemSet(lpObj->m_Index, source, -1);
							lpObj->pInventory[source].Clear();
							GCInventoryItemOneSend(lpObj->m_Index, target);
							GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);

							return;
						}
						/*else if(5 == NumOfExcOptions(lpObj->pInventory[target].m_NewOption))
						{
							BYTE NewOption = 63;
						
							lpObj->pInventory[target].m_NewOption = NewOption;
							gObjInventoryItemSet(lpObj->m_Index, source, -1);
							lpObj->pInventory[source].Clear();
							GCInventoryItemOneSend(lpObj->m_Index, target);
							GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);

							return;
						}*/
						else
						{
							MsgOutput(lpObj->m_Index,g_ExText.GetText(40),this->JewelOfExellentMaxOpt);
						}
					}
				}
				else
				{
					MsgOutput(lpObj->m_Index,g_ExText.GetText(41));
				}
			}
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFD, 1, lpObj->iShield);
		}
		else
		{
			gObjInventoryItemSet(lpObj->m_Index, source, -1);
			lpObj->pInventory[source].Clear();
			GCInventoryItemDeleteSend(lpObj->m_Index, source, 1);
		}
	}
}
