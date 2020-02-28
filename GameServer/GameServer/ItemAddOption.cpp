//GameServer 1.00.77 JPN - Completed
#include "stdafx.h"
#include "ItemAddOption.h"
#include "LogProc.h"
#include "ObjCalCharacter.h"
#include "CashItemPeriodSystem.h"
#include "..\include\Readscript.h"

CItemAddOption g_ItemAddOption;

CItemAddOption::CItemAddOption()
{
	this->Initialize();
}

CItemAddOption::~CItemAddOption()
{
	return;
}

void CItemAddOption::Load(char* chFileName)
{
	SMDToken Token;

	this->Initialize();

	SMDFile = fopen(chFileName, "r");

	if ( SMDFile == NULL )
	{
		return;
	}

	int iItemAddOptionIndex = 0;

	while ( true )
	{
		Token = (SMDToken)GetToken();

		if ( Token == END )
		{
			break;
		}

		if ( Token == NUMBER )
		{
			int iType = (int)TokenNumber;

			while ( true )
			{
				if ( iType == 0 )
				{
					Token = (SMDToken)GetToken();

					if ( strcmp("end", TokenString) == 0 )
					{
						break;
					}
				}

				if ( iType == 1 )
				{
					int iItemNumber = 0;
					int iItemType = 0;
					int iItemIndex = 0;
					int iItemOption1 = 0;
					int iItemValue1 = 0;
					int iItemOption2 = 0;
					int iItemValue2 = 0;
					int iItemValidTime = 0;

					Token = (SMDToken)GetToken();

					if ( !strcmp("end", TokenString))
						break;

					iItemType = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemIndex = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemOption1 = (int)TokenNumber;					

					Token = (SMDToken)GetToken();
					iItemValue1 = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemOption2 = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemValue2 = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemValidTime = (int)TokenNumber;

					iItemNumber = ITEMGET(iItemType, iItemIndex);
					this->m_ItemAddOption[iItemAddOptionIndex].wOptionType = iType;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemNumber = iItemNumber;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemType = iItemType;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemIndex = iItemIndex;
					this->m_ItemAddOption[iItemAddOptionIndex].wEffectType1 = iItemOption1;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValue1 = iItemValue1;
					this->m_ItemAddOption[iItemAddOptionIndex].wEffectType2 = iItemOption2;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValue2 = iItemValue2;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValidTime = iItemValidTime;

					iItemAddOptionIndex++;

					if (iItemAddOptionIndex > MAX_ITEM_ADD_OPTION )
					{
						MsgBox("[ItemAddOption] Overflow ItemAddOption Table Index");
					}
				}
				else if ( iType >= 2 )
				{
					int iItemNumber = 0;
					int iItemType = 0;
					int iItemIndex = 0;
					int iItemOption1 = 0;
					int iItemValue1 = 0;
					int iItemOption2 = 0;
					int iItemValue2 = 0;
					int iItemValidTime = 0;

					Token = (SMDToken)GetToken();

					if ( !strcmp("end", TokenString))
						break;

					iItemType = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemIndex = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemOption1 = (int)TokenNumber;					

					Token = (SMDToken)GetToken();
					iItemValue1 = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemOption2 = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemValue2 = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iItemValidTime = (int)TokenNumber;

					iItemNumber = ITEMGET(iItemType, iItemIndex);
					this->m_ItemAddOption[iItemAddOptionIndex].wOptionType = iType;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemNumber = iItemNumber;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemType = iItemType;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemIndex = iItemIndex;
					this->m_ItemAddOption[iItemAddOptionIndex].wEffectType1 = iItemOption1;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValue1 = iItemValue1;
					this->m_ItemAddOption[iItemAddOptionIndex].wEffectType2 = iItemOption2;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValue2 = iItemValue2;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValidTime = iItemValidTime;

					iItemAddOptionIndex++;

					if (iItemAddOptionIndex > MAX_ITEM_ADD_OPTION )
					{
						MsgBox("[ItemAddOption] Overflow ItemAddOption Table Index");
					}
				}
			}
		}
	}

	fclose(SMDFile);
}

void CItemAddOption::Initialize()
{
	for ( int i=0;i<MAX_ITEM_ADD_OPTION;i++)
	{
		this->m_ItemAddOption[i].iItemNumber = 0;
		this->m_ItemAddOption[i].iItemType = 0;
		this->m_ItemAddOption[i].iItemIndex = 0;
		this->m_ItemAddOption[i].wEffectType1 = 0;
		this->m_ItemAddOption[i].iEffectValue1 = 0;
		this->m_ItemAddOption[i].wEffectType2 = 0;
		this->m_ItemAddOption[i].iEffectValue2 = 0;
		this->m_ItemAddOption[i].iEffectValidTime = 0;
	}
}

BYTE CItemAddOption::ClearItemEffect2(LPOBJ lpObj, int iItemNumber, int iEffectOption)
{
	LPITEMEFFECT lpItemEffect = NULL;

	lpItemEffect = this->_SearchItemEffect(iItemNumber);

	if(lpItemEffect == NULL)
	{
		return 0;
	}

	this->_ClearItemEffect(lpObj, iEffectOption, lpItemEffect->wOptionType, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
	this->_ClearItemEffect(lpObj, iEffectOption, lpItemEffect->wOptionType, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2);

	return 1;
}

bool CItemAddOption::PrevSetItemLastEffectForCashShop(LPOBJ lpObj)
{
	ITEMPERIOD_INFO* lpItemPeriodInfo = NULL;
	LPITEMEFFECT lpItemEffect = NULL;

	lpItemPeriodInfo = ::g_CashItemPeriodSystem.GetItemPeriodInfo(lpObj);

	if( lpItemPeriodInfo == NULL )
	{
		return false;
	}

	for( int i = 0; i < MAX_ITEM_PERIOD_EFFECT; i++ )
	{
		if( lpItemPeriodInfo->vItemEffect[i].bInUse == true )
		{
			lpItemEffect = this->_SearchItemEffect(lpItemPeriodInfo->vItemEffect[i].iItemCode);
			
			if( lpItemEffect != NULL )
			{
#ifdef DEBUG_CODE
				LogAddC(1,"lpItemEffect->wEffectType1: %d",lpItemEffect->wEffectType1);
#endif

				switch( lpItemEffect->wEffectType1 )
				{
					case ADD_OPTION_LIFE: //4
					case ADD_OPTION_MANA: //5
					case ADD_OPTION_STRENGTH: //9
					case ADD_OPTION_DEXTERITY: //10
					case ADD_OPTION_VITALITY: //11
					case ADD_OPTION_ENERGY: //12
					case ADD_OPTION_LEADERSHIP: //13
						this->_SetItemEffect(lpObj,lpItemEffect->wEffectType1,lpItemEffect->iEffectValue1);
						break;

					default :
						break;
				}

				switch( lpItemEffect->wEffectType2 )
				{
					case ADD_OPTION_LIFE: //4
					case ADD_OPTION_MANA: //5
					case ADD_OPTION_STRENGTH: //9
					case ADD_OPTION_DEXTERITY: //10
					case ADD_OPTION_VITALITY: //11
					case ADD_OPTION_ENERGY: //12
					case ADD_OPTION_LEADERSHIP: //13
						this->_SetItemEffect(lpObj,lpItemEffect->wEffectType2,lpItemEffect->iEffectValue2);
						break;
					
					default :
						break;
				}
			}
		}	
	}
	return true;
}

//0051DEC0  /> \55            PUSH EBP
bool CItemAddOption::NextSetItemLastEffectForCashShop(LPOBJ lpObj)
{
	ITEMPERIOD_INFO* lpItemPeriodInfo = NULL;
	LPITEMEFFECT lpItemEffect = NULL;

	lpItemPeriodInfo = ::g_CashItemPeriodSystem.GetItemPeriodInfo(lpObj);

	if( lpItemPeriodInfo == NULL )
	{
		return false;
	}

	for( int i = 0; i < MAX_ITEM_PERIOD_EFFECT; i++ )
	{
		if( lpItemPeriodInfo->vItemEffect[i].bInUse == true )
		{
			lpItemEffect = this->_SearchItemEffect(lpItemPeriodInfo->vItemEffect[i].iItemCode);
			
			if( lpItemEffect != NULL )
			{
				switch( lpItemEffect->wEffectType1 )
				{
					case ADD_OPTION_SPEED: //1 -> Season3.5 add-on
					case ADD_OPTION_LIFE: //4
					case ADD_OPTION_MANA: //5
					case ADD_OPTION_STRENGTH: //9
					case ADD_OPTION_DEXTERITY: //10
					case ADD_OPTION_VITALITY: //11
					case ADD_OPTION_ENERGY: //12
					case ADD_OPTION_LEADERSHIP: //13
						break;

					default :
						this->_SetItemEffect(lpObj,lpItemEffect->wEffectType1,lpItemEffect->iEffectValue1);
						break;
				}

				switch( lpItemEffect->wEffectType2 )
				{
					case ADD_OPTION_SPEED: //1 -> Season3.5 add-on
					case ADD_OPTION_LIFE: //4
					case ADD_OPTION_MANA: //5
					case ADD_OPTION_STRENGTH: //9
					case ADD_OPTION_DEXTERITY: //10
					case ADD_OPTION_VITALITY: //11
					case ADD_OPTION_ENERGY: //12
					case ADD_OPTION_LEADERSHIP: //13
						break;
					
					default :
						this->_SetItemEffect(lpObj,lpItemEffect->wEffectType2,lpItemEffect->iEffectValue2);
						break;
				}
			}
		}	
	}
	return true;
}

bool CItemAddOption::PrevSetItemLastEffectForHallowin(LPOBJ lpObj)
{
	LPITEMEFFECT lpItemEffect = NULL;
	int iItemEffectType = lpObj->m_wItemEffectType;

	lpItemEffect = this->_SearchItemEffect(iItemEffectType);

	if ( lpItemEffect == NULL )
	{
		return false;
	}

	if ( lpItemEffect->wEffectType1 == ADD_OPTION_LIFE || lpItemEffect->wEffectType1 == ADD_OPTION_MANA )
	{
		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
	}

	return true;
}

bool CItemAddOption::NextSetItemLastEffectForHallowin(LPOBJ lpObj)
{
	LPITEMEFFECT lpItemEffect = NULL;
	int iItemEffectType = lpObj->m_wItemEffectType;

	lpItemEffect = this->_SearchItemEffect(iItemEffectType);

	if ( lpItemEffect == NULL )
	{
		return false;
	}

	if ( lpItemEffect->wEffectType1 != ADD_OPTION_LIFE && lpItemEffect->wEffectType1 != ADD_OPTION_MANA )
	{
		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
	}

	return true;
}

void CItemAddOption::SendItemUse(LPOBJ lpObj, int iItemNumber, int iOptionType, int iEffectType, int iEffectValue, int iValidTime)
{
	if ( lpObj == NULL )
	{
		return;
	}
	
	if ( iItemNumber== 0 || iEffectType == 0 )
	{
		return;
	}

	GCUseEffectItem(lpObj, 0, iOptionType, iEffectType, iValidTime);
}

bool CItemAddOption::SetItemEffect(LPOBJ lpObj, int iItemNumber, int iItemUseTime)
{
	LPITEMEFFECT lpItemEffectBefore = NULL;
	LPITEMEFFECT lpItemEffect = NULL;

	if ( lpObj == NULL )
	{
		return false;
	}

	if ( lpObj->Type != OBJ_USER )
	{
		return false;
	}

	lpItemEffect = this->_SearchItemEffect(iItemNumber);

	if ( lpItemEffect == NULL )
	{
		return false;
	}

	lpItemEffectBefore = this->GetCurrentEffectType(lpObj);

	if ( lpItemEffectBefore != NULL )
	{
		if ( lpItemEffectBefore->wOptionType == lpItemEffect->wOptionType )
		{
			this->ClearItemEffect(lpObj, 2);
		}
	}

	if ( iItemUseTime > 0 )
	{
		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
		this->SendItemUse(lpObj, iItemNumber, lpItemEffect->wOptionType, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1, iItemUseTime * 60);

		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2);
		this->SendItemUse(lpObj, iItemNumber, lpItemEffect->wOptionType, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2, iItemUseTime * 60);
	}
	else
	{
		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
		this->SendItemUse(lpObj, iItemNumber, lpItemEffect->wOptionType, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1, lpItemEffect->iEffectValidTime);

		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2);
		this->SendItemUse(lpObj, iItemNumber, lpItemEffect->wOptionType, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2, lpItemEffect->iEffectValidTime);
	}
	
	if( lpItemEffect->wOptionType == 1 )
	{
		if ( iItemUseTime > 0 )
		{
			lpObj->m_wItemEffectType = lpItemEffect->iItemNumber;
			lpObj->m_iItemEffectValidTime = iItemUseTime * 60;
		}
		else
		{
			lpObj->m_wItemEffectType = lpItemEffect->iItemNumber;
			lpObj->m_iItemEffectValidTime = lpItemEffect->iEffectValidTime;
		}
	}

	return true;
}

//0055D060  /> \55            PUSH EBP
BYTE CItemAddOption::SetManualItemEffect(LPOBJ lpObj,int iEffectType,int iEffectValue,int iLeftTime)//calls 1x from GMMng.cpp
{
	if(iEffectType <= 0)
	{
		return FALSE;
	}

	if(iLeftTime <= 0)
	{
		iLeftTime = 60;
	}

	this->_SetItemEffect(lpObj,iEffectType,iEffectValue);

	GCUseEffectItem(lpObj,0,1,iEffectType,iLeftTime);
    this->SendItemUse(lpObj,iEffectType,1,iEffectType,iEffectValue,iLeftTime);

	return TRUE;

}

//0051E4F0  /> \55            PUSH EBP
bool CItemAddOption::_SetItemEffect(LPOBJ lpObj, int iEffectType, int iEffectValue)//51E310
{
	if ( iEffectType <= 0 )
		return false;

	switch ( iEffectType )
	{
		case ADD_OPTION_LIFE:
			lpObj->AddLife += iEffectValue;
			GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), -2, 0, (lpObj->iMaxShield + lpObj->iAddShield));
			GCReFillSend(lpObj->m_Index, (lpObj->Life), -1, 0, (lpObj->iShield));
			break;

		case ADD_OPTION_MANA:
			lpObj->AddMana += iEffectValue;
			GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), -2, 0, (lpObj->MaxBP + lpObj->AddBP));
			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
			break;

		case ADD_OPTION_ATTACK_DAMAGE:
			lpObj->m_AttackDamageMaxLeft += iEffectValue;
			lpObj->m_AttackDamageMinLeft += iEffectValue;
			lpObj->m_AttackDamageMaxRight += iEffectValue;
			lpObj->m_AttackDamageMinRight += iEffectValue;
			lpObj->m_MagicDamageMin += iEffectValue;
			lpObj->m_MagicDamageMax += iEffectValue;
			break;

		/*case ADD_OPTION_SPEED:
			lpObj->m_AttackSpeed += iEffectValue;
			lpObj->m_MagicSpeed += iEffectValue;
			break;*/

		case ADD_OPTION_DEFENSE:
			lpObj->m_Defense += iEffectValue * 10 / 20;
			break;

		case ADD_OPTION_STRENGTH:
			lpObj->AddStrength += iEffectValue;
			break;

		case ADD_OPTION_DEXTERITY:
			lpObj->AddDexterity += iEffectValue;
			break;

		case ADD_OPTION_VITALITY:
			lpObj->AddVitality += iEffectValue;
			break;

		case ADD_OPTION_ENERGY:
			lpObj->AddEnergy += iEffectValue;
			break;

		case ADD_OPTION_LEADERSHIP:
			lpObj->AddLeadership += iEffectValue;
			break;

		case ADD_OPTION_WRATH:
			lpObj->m_AttackDamageMaxLeft += iEffectValue;
			lpObj->m_AttackDamageMinLeft += iEffectValue;
			lpObj->m_AttackDamageMaxRight += iEffectValue;
			lpObj->m_AttackDamageMinRight += iEffectValue;
			break;

		case ADD_OPTION_WIZARDRY:
			lpObj->m_MagicDamageMin += iEffectValue;
			lpObj->m_MagicDamageMax += iEffectValue;
			break;

		case ADD_OPTION_MOBILITY:
			break;

		default:
			return false;
	}

	return true;
}

bool CItemAddOption::_ClearItemEffect(LPOBJ lpObj, int iEffectOption, int iOptionType, int iEffectType, int iEffectValue)
{
	if ( iEffectType <= 0 )
		return false;

	switch ( iEffectType )
	{
		case ADD_OPTION_LIFE:
			lpObj->AddLife -= iEffectValue;

			if ( (lpObj->AddLife + lpObj->MaxLife ) < lpObj->Life )
			{
				lpObj->Life = lpObj->AddLife + lpObj->MaxLife;
			}

			GCReFillSend(lpObj->m_Index, (lpObj->Life), 0xFF, 0, (lpObj->iShield));
			GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), 0xFE, 0, (lpObj->iMaxShield + lpObj->iAddShield));
			break;

		case ADD_OPTION_MANA:
			lpObj->AddMana -= iEffectValue;

			if ( (lpObj->AddMana + lpObj->MaxMana ) < lpObj->Mana )
			{
				lpObj->Mana = lpObj->AddMana + lpObj->MaxMana;
			}

			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
			GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, (lpObj->MaxBP + lpObj->AddBP));
			break;

		case ADD_OPTION_ATTACK_DAMAGE:
			lpObj->m_AttackDamageMaxLeft -= iEffectValue;
			lpObj->m_AttackDamageMinLeft -= iEffectValue;
			lpObj->m_AttackDamageMaxRight -= iEffectValue;
			lpObj->m_AttackDamageMinRight -= iEffectValue;
			lpObj->m_MagicDamageMin -= iEffectValue;
			lpObj->m_MagicDamageMax -= iEffectValue;
			break;

		/*case ADD_OPTION_SPEED:
			lpObj->m_AttackSpeed -= iEffectValue;
			lpObj->m_MagicSpeed -= iEffectValue;
			break;*/

		case ADD_OPTION_DEFENSE:
			lpObj->m_Defense -= iEffectValue * 10 / 20;
			break;

		case ADD_OPTION_STRENGTH:
			lpObj->AddStrength -= iEffectValue;
			break;

		case ADD_OPTION_DEXTERITY:
			lpObj->AddDexterity -= iEffectValue;
			break;

		case ADD_OPTION_VITALITY:
			lpObj->AddVitality -= iEffectValue;
			break;

		case ADD_OPTION_ENERGY:
			lpObj->AddEnergy -= iEffectValue;
			break;

		case ADD_OPTION_LEADERSHIP:
			lpObj->AddLeadership -= iEffectValue;
			break;

		case ADD_OPTION_WRATH:

			lpObj->m_AttackDamageMaxLeft -= iEffectValue;
			lpObj->m_AttackDamageMinLeft -= iEffectValue;
			lpObj->m_AttackDamageMaxRight -= iEffectValue;
			lpObj->m_AttackDamageMinRight -= iEffectValue;
			break;

		case ADD_OPTION_WIZARDRY:
			lpObj->m_MagicDamageMin -= iEffectValue;
			lpObj->m_MagicDamageMax -= iEffectValue;
			break;

		case ADD_OPTION_MOBILITY:
			break;

		default:
			return false;
	}

	GCUseEffectItem(lpObj, iEffectOption, iOptionType, iEffectType, 0);

	return true;
}

bool CItemAddOption::ClearItemEffect(LPOBJ lpObj, int iEffectOption)//51ECB0
{
	LPITEMEFFECT lpItemEffect = NULL;
	
	lpItemEffect = this->GetCurrentEffectType(lpObj);

	if ( lpItemEffect == NULL )
	{
		return false;
	}

	this->_ClearItemEffect(lpObj, iEffectOption, lpItemEffect->wOptionType,	lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
	this->_ClearItemEffect(lpObj, iEffectOption, lpItemEffect->wOptionType,	lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2);

	lpObj->m_wItemEffectType = 0; //Season3 add-on
	lpObj->m_iItemEffectValidTime = 0; //Season3 add-on

	return true;
}

LPITEMEFFECT CItemAddOption::GetCurrentEffectType(LPOBJ lpObj)
{
	if ( lpObj->m_wItemEffectType <= 0 )
	{
		return NULL;
	}

	return this->_SearchItemEffect(lpObj->m_wItemEffectType);
}

LPITEMEFFECT CItemAddOption::_SearchItemEffect(int iItemNumber)
{
	for ( int i=0;i<MAX_ITEM_ADD_OPTION;i++)
	{
		if ( this->m_ItemAddOption[i].iItemNumber == iItemNumber )
		{
			return &this->m_ItemAddOption[i];
		}
	}

	return NULL;
}

bool CItemAddOption::SearchItemEffectType(int iItemNumber, int * iEffectType1, int * iEffectType2, int *iEffectValidTime)
{
	LPITEMEFFECT lpItemEffect = NULL;

	lpItemEffect = this->_SearchItemEffect(iItemNumber);

	if ( lpItemEffect == NULL )
	{
		return false;
	}

	*iEffectType1 = lpItemEffect->wEffectType1;
	*iEffectType2 = lpItemEffect->wEffectType2;
	*iEffectValidTime = lpItemEffect->iEffectValidTime;

	return true;
}

int CItemAddOption::SearchItemOptionType(int iItemNumber)
{
	LPITEMEFFECT lpItemEffect = NULL;
	int iOptionType = -1;

	lpItemEffect = this->_SearchItemEffect(iItemNumber);

	if ( lpItemEffect == NULL )
	{
		return iOptionType;
	}

	iOptionType = lpItemEffect->wOptionType;

	return iOptionType;
}

BYTE CItemAddOption::SearchForClearItemEffect(int iItemNumber)
{
	if ( this->_SearchItemEffect(iItemNumber) == NULL )
	{
		return 0;
	}

	return 1;
}

LPITEMEFFECT CItemAddOption::SearchItemEffectType1(int iItemNumber)
{
	return this->_SearchItemEffect(iItemNumber);
}

bool CItemAddOption::ApplyForEquipment(LPOBJ lpObj)	//Code Equipment
{
	//ITEMOPTION_FOR380ITEM_EFFECT * pItemEffect = &lpObj->m_ItemOptionExFor380;
	//this->InitEffectValue(pItemEffect);
	int iItemIndex = 0;

	for ( iItemIndex = 0; iItemIndex < INVETORY_WEAR_SIZE ; iItemIndex++)
	{
		CItem * pItem = &lpObj->pInventory[iItemIndex];

		if ( pItem->IsItem()
			/* pItem->m_IsValidItem &&*/
			 )
		{
			LPITEMEFFECT lpItemEffect = NULL;
			lpItemEffect = this->_SearchItemEffect(pItem->m_Type); 

			if ( lpItemEffect == NULL )
			{
				continue;
			}

			if(lpItemEffect->iEffectValidTime == 0)
			{
				this->SetItemEquipment(lpObj,lpItemEffect->wEffectType1,lpItemEffect->iEffectValue1);
				this->SetItemEquipment(lpObj,lpItemEffect->wEffectType2,lpItemEffect->iEffectValue2);
			}
		}
	}

	return TRUE;
}

bool CItemAddOption::SetItemEquipment(LPOBJ lpObj, int iEffectType, int iEffectValue)//51E310
{
	if ( iEffectType <= 0 )
		return false;

// 1) Increase Speed
// 2) Increase Attack Damage
// 3) Increase Defence
// 4) Increase MaxLife
// 5) Increase MaxMana
// 6) Increase Experience Percent
// 7) Increase Drop Rate Percent
// 8) +%d Remove Extra Experience
// 9) Increase Strength
//10) Increase Agility
//11) Increase Vitality
//12) Increase Energy
//13) Increase Leadership
//51) Increase Attack Power Percent
//52) Increase Dmg Absorbtion Percent
//60) Increase Experience Rate (20 = +20x in %)
//61) Increase Drop Rate (1 = 1000*1/100 = 10)
//64) Increase Increase Damage Percentage

	switch ( iEffectType )
	{
		case ADD_OPTION_LIFE_AUTO_RECOVERY: 
			lpObj->RecoveryHp += iEffectValue; 
			break;

		case ADD_OPTION_MANA_AUTO_RECOVERY:
			lpObj->RecoveryMp += iEffectValue;
			break;

		case ADD_OPTION_ATTACK_NORMAL_DAMAGE:
			lpObj->m_AttackDamageMaxLeft += iEffectValue;
			lpObj->m_AttackDamageMinLeft += iEffectValue;
			lpObj->m_AttackDamageMaxRight += iEffectValue;
			lpObj->m_AttackDamageMinRight += iEffectValue;
			lpObj->m_MagicDamageMin += iEffectValue;
			lpObj->m_MagicDamageMax += iEffectValue;
			break;

		case ADD_OPTION_LIFE:
			lpObj->AddLife += ( (lpObj->MaxLife + lpObj->AddLife) * iEffectValue ) /100;
			GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), -2, 0, (lpObj->iMaxShield + lpObj->iAddShield));
			GCReFillSend(lpObj->m_Index, (lpObj->Life), -1, 0, (lpObj->iShield));
			break;

		case ADD_OPTION_EXCELLENT_DAMAGE:
			lpObj->m_ExcelentDamage += iEffectValue;
			break;

		case ADD_OPTION_CRITICAL_DAMAGE:
			lpObj->m_CriticalDamage += iEffectValue;
			break;

		case ADD_OPTION_MANA:
			lpObj->AddMana += ( (lpObj->AddMana + lpObj->MaxMana) * iEffectValue ) / 100;
			GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), -2, 0, (lpObj->MaxBP + lpObj->AddBP));
			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
			break;

		case ADD_OPTION_ATTACK_DAMAGE:
			lpObj->m_AttackDamageMaxLeft += iEffectValue;
			lpObj->m_AttackDamageMinLeft += iEffectValue;
			lpObj->m_AttackDamageMaxRight += iEffectValue;
			lpObj->m_AttackDamageMinRight += iEffectValue;
			lpObj->m_MagicDamageMin += iEffectValue;
			lpObj->m_MagicDamageMax += iEffectValue;
			break;

		/*case ADD_OPTION_SPEED:
			lpObj->m_AttackSpeed += iEffectValue;
			lpObj->m_MagicSpeed += iEffectValue;
			break;*/

		case ADD_OPTION_DEFENSE:
			lpObj->m_Defense += iEffectValue * 10 / 20;
			break;

		case ADD_OPTION_STRENGTH:
			lpObj->AddStrength += iEffectValue;
			break;

		case ADD_OPTION_DEXTERITY:
			lpObj->AddDexterity += iEffectValue;
			break;

		case ADD_OPTION_VITALITY:
			lpObj->AddVitality += iEffectValue;
			break;

		case ADD_OPTION_ENERGY:
			lpObj->AddEnergy += iEffectValue;
			break;

		case ADD_OPTION_LEADERSHIP:
			lpObj->AddLeadership += iEffectValue;
			break;

		case ADD_OPTION_WRATH:
			lpObj->m_AttackDamageMaxLeft += iEffectValue;
			lpObj->m_AttackDamageMinLeft += iEffectValue;
			lpObj->m_AttackDamageMaxRight += iEffectValue;
			lpObj->m_AttackDamageMinRight += iEffectValue;
			break;

		case ADD_OPTION_WIZARDRY:
			lpObj->m_MagicDamageMin += iEffectValue;
			lpObj->m_MagicDamageMax += iEffectValue;
			break;

		case ADD_IncreaseIncreaseDamagePercentage:
			lpObj->m_AttackDamageMaxLeft +=  (( lpObj->m_AttackDamageMaxLeft * iEffectValue ) / 100 );
			lpObj->m_AttackDamageMinLeft +=  (( lpObj->m_AttackDamageMinLeft * iEffectValue ) / 100 );
			lpObj->m_AttackDamageMaxRight += (( lpObj->m_AttackDamageMaxRight* iEffectValue ) / 100 );
			lpObj->m_AttackDamageMinRight += (( lpObj->m_AttackDamageMinRight* iEffectValue ) / 100 );
	
			lpObj->m_MagicDamageMax += (( gObj->m_MagicDamageMax * iEffectValue ) / 100 );
			lpObj->m_MagicDamageMin += (( gObj->m_MagicDamageMin * iEffectValue ) / 100 );
			break;

		case ADD_OPTION_MONSTER_DAMAGE_ABSORB:
			lpObj->DamageMinus += iEffectValue;
			break;
	}

	return true;
}