#include "StdAfx.h"
#include "ExclusiveOptions.h"
#include "user.h"
#include "Functions.h"
#ifdef EXCLUSIVE_AMYLET
#include "ExLicense.h"
#include "Message.h"

#endif

cExclusiveOptions gExclusiveOptions;

void cExclusiveOptions::Load()
{
	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,ExclusiveOptions_DIR);

	ZeroMemory(this->Exclusive,sizeof(Exclusive));
	ZeroMemory(this->ExclusiveInv,sizeof(ExclusiveInv));

	FILE * file = fopen(ExclusiveOptions_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,ExclusiveOptions_DIR,"LOAD ERROR",0);
		this->Enable = false;
	}

	if(!this->Enable) return;

	char Buff[256];
	int Flag = 0;

	this->Count = 0;
	this->CountInv = 0;
#ifdef EXCLUSIVE_AMYLET
	if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		this->CountInvTime = 0;
	}
#endif

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			int n[4];
			sscanf(Buff, "%d %d %d %d" , &n[0], &n[1], &n[2], &n[3]);
			this->Exclusive[this->Count].Type = n[0];
			this->Exclusive[this->Count].Index = n[1];
			this->Exclusive[this->Count].Options = n[2];
			this->Exclusive[this->Count].Value = n[3];
			this->Count++;
		}
		if(Flag == 2)
		{
			int n[3];
			sscanf(Buff, "%d %d %d %d" , &n[0], &n[1], &n[2], &n[3]);
			this->ExclusiveInv[this->CountInv].Type = n[0];
			this->ExclusiveInv[this->CountInv].Index = n[1];
			this->ExclusiveInv[this->CountInv].Options = n[2];
			this->ExclusiveInv[this->CountInv].Value = n[3];
			this->CountInv++;
		}
		
#ifdef EXCLUSIVE_AMYLET
		if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			if(Flag == 3)
			{
				int n[3];
				sscanf(Buff, "%d %d %d %d" , &n[0], &n[1], &n[2], &n[3]);		
				this->ExclusiveInvTime[this->CountInvTime].Type = n[0];
				this->ExclusiveInvTime[this->CountInvTime].Index = n[1];
				this->ExclusiveInvTime[this->CountInvTime].Options = n[2];
				this->ExclusiveInvTime[this->CountInvTime].Value = n[3];
				this->CountInvTime++;
			}
		}
		
#endif
	}
	fclose(file);
}

/*
	0 - Damage
	1 - MinDefence
	2 - IgnoreDefence
	3 - CriticalDamageRate
	4 - ExellentDamageRate
	5 - DoubleDamage
	6 - AbsordDamage
	7 - ReflectDamage
	8 - SD
	9 - Life
	10 - Wizard Damage
	11 - Exp
	12 - Zen
*/

void cExclusiveOptions::Options(int aIndex)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	for(int a = 0; a < this->Count; a++)
	{
		if(CheckInCharacterItem(aIndex,ITEMGET(this->Exclusive[a].Type,this->Exclusive[a].Index)))
		{
			switch(this->Exclusive[a].Options)
			{
			case eExclusiveOpt::Damage:
				lpObj->m_AttackDamageMinRight += this->Exclusive[a].Value;
				lpObj->m_AttackDamageMaxRight += this->Exclusive[a].Value;
				lpObj->m_AttackDamageMinLeft += this->Exclusive[a].Value;
				lpObj->m_AttackDamageMaxLeft += this->Exclusive[a].Value;
/*				lpObj->m_MagicDamageMin += this->Exclusive[a].Value;
				lpObj->m_MagicDamageMax += this->Exclusive[a].Value;	*/	
				break;
			case eExclusiveOpt::MinDefence:
				lpObj->m_Defense += this->Exclusive[a].Value;
				break;
			case eExclusiveOpt::IgnoreDefence:
				lpObj->SetOpIgnoreDefense += this->Exclusive[a].Value;
				Max90Procent((int&)lpObj->SetOpIgnoreDefense);
				break;
			case eExclusiveOpt::CriticalDamageRate:
				lpObj->m_CriticalDamage += this->Exclusive[a].Value;
				Max90Procent((int&)lpObj->m_CriticalDamage);
				break;
			case eExclusiveOpt::ExellentDamageRate:
				lpObj->m_ExcelentDamage += this->Exclusive[a].Value;
				Max90Procent((int&)lpObj->m_ExcelentDamage);
				break;
			case eExclusiveOpt::DoubleDamage:
				lpObj->SetOpDoubleDamage += this->Exclusive[a].Value;
				Max90Procent((int&)lpObj->SetOpDoubleDamage);
				break;
			case eExclusiveOpt::AbsordDamage:
				lpObj->DamageMinus += this->Exclusive[a].Value;
				Max90Procent((int&)lpObj->DamageMinus);
				break;
			case eExclusiveOpt::ReflectDamage:
				lpObj->DamageReflect += this->Exclusive[a].Value;
				Max90Procent((int&)lpObj->DamageReflect);
				break;
			case eExclusiveOpt::SD:
				lpObj->iAddShield += this->Exclusive[a].Value;
				break;
			case eExclusiveOpt::Life:
				lpObj->AddLife += this->Exclusive[a].Value;
				break;
			case eExclusiveOpt::WizardDamage:
				lpObj->m_MagicDamageMin += this->Exclusive[a].Value;
				lpObj->m_MagicDamageMax += this->Exclusive[a].Value;
				break;
			}
		}
	}

	for(int a = 0; a < this->CountInv; a++)
	{
		if(CheckInventoryItem(aIndex,ITEMGET(this->ExclusiveInv[a].Type,this->ExclusiveInv[a].Index)))
		{
			switch(this->ExclusiveInv[a].Options)
			{
			case eExclusiveOpt::Damage:
				lpObj->m_AttackDamageMinRight += this->ExclusiveInv[a].Value;
				lpObj->m_AttackDamageMaxRight += this->ExclusiveInv[a].Value;
				lpObj->m_AttackDamageMinLeft += this->ExclusiveInv[a].Value;
				lpObj->m_AttackDamageMaxLeft += this->ExclusiveInv[a].Value;
				lpObj->m_MagicDamageMin += this->ExclusiveInv[a].Value;
				lpObj->m_MagicDamageMax += this->ExclusiveInv[a].Value;		
				break;
			case eExclusiveOpt::MinDefence:
				lpObj->m_Defense += this->ExclusiveInv[a].Value;
				break;
			case eExclusiveOpt::IgnoreDefence:
				lpObj->SetOpIgnoreDefense += this->ExclusiveInv[a].Value;
				Max90Procent((int&)lpObj->SetOpIgnoreDefense);
				break;
			case eExclusiveOpt::CriticalDamageRate:
				lpObj->m_CriticalDamage += this->ExclusiveInv[a].Value;
				Max90Procent((int&)lpObj->m_CriticalDamage);
				break;
			case eExclusiveOpt::ExellentDamageRate:
				lpObj->m_ExcelentDamage += this->ExclusiveInv[a].Value;
				Max90Procent((int&)lpObj->m_ExcelentDamage);
				break;
			case eExclusiveOpt::DoubleDamage:
				lpObj->SetOpDoubleDamage += this->ExclusiveInv[a].Value;
				Max90Procent((int&)lpObj->SetOpDoubleDamage);
				break;
			case eExclusiveOpt::AbsordDamage:
				lpObj->DamageMinus += this->ExclusiveInv[a].Value;
				Max90Procent((int&)lpObj->DamageMinus);
				break;
			case eExclusiveOpt::ReflectDamage:
				lpObj->DamageReflect += this->ExclusiveInv[a].Value;
				Max90Procent((int&)lpObj->DamageReflect);
				break;
			case eExclusiveOpt::SD:
				lpObj->iAddShield += this->ExclusiveInv[a].Value;
				break;
			case eExclusiveOpt::Life:
				lpObj->AddLife += this->ExclusiveInv[a].Value;
				break;
			case eExclusiveOpt::WizardDamage:
				lpObj->m_MagicDamageMin += this->ExclusiveInv[a].Value;
				lpObj->m_MagicDamageMax += this->ExclusiveInv[a].Value;
				break;
			}
		}
	}

}

void cExclusiveOptions::DropZen(int aIndex, float & money)
{
	if(!this->Enable) return;

	for(int a = 0; a < this->Count; a++)
	{
		if(CheckInCharacterItem(aIndex,ITEMGET(this->Exclusive[a].Type,this->Exclusive[a].Index)) && this->Exclusive[a].Options == eExclusiveOpt::Zen)
		{
			if(this->Exclusive[a].Options)
			{
				if (g_ExLicense.CheckUser(eExUB::Cherkashin))
				{
					money += ( money * this->Exclusive[a].Value)/100;
				}
				else
				{
					money += ( money * 100 ) / this->Exclusive[a].Value;
				}
				
			}
		}
	}

	for(int a = 0; a < this->CountInv; a++)
	{
		if(CheckInventoryItem(aIndex,ITEMGET(this->ExclusiveInv[a].Type,this->ExclusiveInv[a].Index)) && this->ExclusiveInv[a].Options == eExclusiveOpt::Zen)
		{
			if(this->ExclusiveInv[a].Options)
			{
				if (g_ExLicense.CheckUser(eExUB::Cherkashin))
				{
					money += ( money * this->Exclusive[a].Value)/100;
				}
				else
				{
					money += ( money * 100 ) / this->Exclusive[a].Value;
				}
			}
		}
	}
}

void cExclusiveOptions::ExpFunction(int aIndex, __int64 & exp)
{
	if(!this->Enable) return;

	for(int a = 0; a < this->Count; a++)
	{
		if(CheckInCharacterItem(aIndex,ITEMGET(this->Exclusive[a].Type,this->Exclusive[a].Index)) && this->Exclusive[a].Options == eExclusiveOpt::Exp)
		{
			if(this->Exclusive[a].Options)
			{
				if (g_ExLicense.CheckUser(eExUB::Cherkashin))
				{
					exp += ( exp * this->Exclusive[a].Value)/100;
				}
				else
				{
					exp += ( exp * 100 ) / this->Exclusive[a].Value;
				}
				
			}
		}
	}

	for(int a = 0; a < this->CountInv; a++)
	{
		if(CheckInventoryItem(aIndex,ITEMGET(this->ExclusiveInv[a].Type,this->ExclusiveInv[a].Index)) && this->ExclusiveInv[a].Options == eExclusiveOpt::Exp)
		{
			if(this->ExclusiveInv[a].Options)
			{
				if (g_ExLicense.CheckUser(eExUB::Cherkashin))
				{
					exp += ( exp * this->Exclusive[a].Value)/100;
				}
				else
				{
					exp += ( exp * 100 ) / this->Exclusive[a].Value;
				}
			}
		}
	}
#ifdef EXCLUSIVE_AMYLET
	if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
	for(int a = 0; a < this->CountInvTime; a++)
	{
		if(CheckInventoryItem(aIndex,ITEMGET(this->ExclusiveInvTime[a].Type,this->ExclusiveInvTime[a].Index)) && this->ExclusiveInvTime[a].Options == eExclusiveOpt::Exp)
		{
			if(this->ExclusiveInvTime[a].Options)
			{
				exp += ( exp * 100 ) / this->ExclusiveInvTime[a].Value;
			}
		}
	}
	}
#endif
}


#ifdef EXCLUSIVE_AMYLET
void cExclusiveOptions::TickTime(int aIndex)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		for(int a = 0; a < this->CountInvTime; a++)
		{
			if(CheckInCharacterItem(aIndex,ITEMGET(this->ExclusiveInvTime[a].Type,this->ExclusiveInvTime[a].Index)))
			{
			//	switch(this->ExclusiveInv[a].Options)
				if(lpObj->pInventory[9].m_Type == ITEMGET(this->ExclusiveInvTime[a].Type,this->ExclusiveInvTime[a].Index))
				{
					if(lpObj->pInventory[9].m_Durability < 1.0f)
					{
						gObjInventoryDeleteItem(lpObj->m_Index,9);

						return;
					}	
					if(lpObj->ExclusiveItemTime[a] > 960)//16 minutes
					{
						lpObj->pInventory[9].m_Durability--;
						lpObj->ExclusiveItemTime[a] = 0;
					}
					else
					{
						lpObj->ExclusiveItemTime[a]++;
					}
				}
			}
		}
	}
}
#endif