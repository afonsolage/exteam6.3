#include "stdafx.h"
#include "WingsDamage.h"
#include "Functions.h"
#include "user.h"
#include "ExLicense.h"
#include "logproc.h"

cWingsDamage gWingsDamage;

void cWingsDamage::Init()
{
	for (int i = 0; i < MAX_WINGS_ITEM; i++)
	{
		this->Data[i].Type = 0;
		this->Data[i].Index = 0;
		this->Data[i].IncreaseDamage = 0;
		this->Data[i].IncreaseDefence = 0;
	}

	for(int i = 0; i < MAX_TYPE_PLAYER; i++)
	{
		for(int n = 0; n < MAX_WINGS_ITEM; n++)
		{
			this->m_Wing[i][n].Type = -1;
			this->m_Wing[i][n].Index = -1;
			this->m_Wing[i][n].AttackPercent = 0;
			this->m_Wing[i][n].AbsurdPercent = 0;
		}

		this->m_iWingCount[i] = 0;
	}

	this->m_bWingsCharacter = false;
};

void cWingsDamage::Load()
{
	this->Init();

	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,WingsDamage_DIR);
	
	if(g_ExLicense.CheckUser(eExUB::Local) || 
	   g_ExLicense.CheckUser(eExUB::ulasevich) || 
	   g_ExLicense.CheckUser(eExUB::ulasevich2) ||
	   g_ExLicense.CheckUser(eExUB::Gredy) ||
	   g_ExLicense.CheckUser(eExUB::Gredy2) ||
	   g_ExLicense.CheckUser(eExUB::GredyLocal) ||
	   g_ExLicense.CheckUser(eExUB::SILVER1) ||
	   g_ExLicense.CheckUser(eExUB::SILVER2) ||
	   g_ExLicense.CheckUser(eExUB::SILVER_Local)
	   )
	{
		this->m_bWingsCharacter = true;
	}

	FILE * file = fopen(WingsDamage_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,WingsDamage_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
	}
	
	char Buff[256];
	int Flag = 0;

	this->Count = 0;

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if(Flag == 1)
		{
			if(this->Count >= MAX_WINGS_ITEM)	
				continue;

			int n[4];
			sscanf(Buff, "%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);
			this->Data[this->Count].Type				= n[0];
			this->Data[this->Count].Index				= n[1];
			this->Data[this->Count].IncreaseDamage		= n[2];
			this->Data[this->Count].IncreaseDefence		= n[3];
			this->Count++;
		}
		else if(Flag >= 2 && Flag < (MAX_TYPE_PLAYER + 2))
		{
			int iClass = Flag - 2;
			int iCount = this->m_iWingCount[iClass];

			if(this->m_iWingCount[iClass] >= MAX_WINGS_ITEM)
			{
				continue;
			}

			int n[4];

			sscanf(Buff, "%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);

			this->m_Wing[iClass][iCount].Type			= n[0];
			this->m_Wing[iClass][iCount].Index			= n[1];
			this->m_Wing[iClass][iCount].AttackPercent	= n[2];
			this->m_Wing[iClass][iCount].AbsurdPercent	= n[3];

			this->m_iWingCount[iClass]++;
		}
	}

	fclose(file);
};

void cWingsDamage::Attack(int Wing, int& Damage)
{
	if (!this->Enable)
	{
		return;
	}
	for (int i = 0; i < this->Count; i++)
	{
		if ( Wing == ITEMGET(Data[i].Type,Data[i].Index) ) 
		{
			Damage = Damage * Data[i].IncreaseDamage / 100;
		}
	}
};

void cWingsDamage::Defence(int Wing, int& Damage)
{
	if (!this->Enable)
	{
		return;
	}
	for (int i = 0; i < this->Count; i++)
	{
		if ( Wing == ITEMGET(Data[i].Type,Data[i].Index) ) 
		{
			Damage = Damage * Data[i].IncreaseDefence / 100;
		}
	}
}

void cWingsDamage::SetCharWingAttack(int aIndex, int ItemType, int ItemLevel, int& AttackDamage)
{
	if(this->m_bWingsCharacter)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int iClass = lpUser->Class;
	int iCount = this->m_iWingCount[iClass];
	int iDamagePercent = 100;

	for(int i = 0; i < MAX_TYPE_PLAYER; i++)
	{
		if(iClass = i)
		{
			for(int n = 0; n < iCount; n++)
			{
				if(ItemType == ITEMGET(this->m_Wing[i][n].Type, this->m_Wing[i][n].Index)) 
				{
					iDamagePercent += this->m_Wing[i][n].AttackPercent;
					break;
				}
			}
		}
	}

	if(iDamagePercent <= 100)
	{
		return;
	}

	AttackDamage = AttackDamage * (ItemLevel * 2 + iDamagePercent) / 100;
}

void cWingsDamage::SetCharWingAbsurd(int aIndex, int ItemType, int ItemLevel, int& AttackDamage)
{
	if(this->m_bWingsCharacter)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int iClass = lpUser->Class;
	int iCount = this->m_iWingCount[iClass];
	int iDefencePercent = 100;

	for(int i = 0; i < MAX_TYPE_PLAYER; i++)
	{
		if(iClass = i)
		{
			for(int n = 0; n < iCount; n++)
			{
				if(ItemType == ITEMGET(this->m_Wing[i][n].Type, this->m_Wing[i][n].Index)) 
				{
					iDefencePercent -= this->m_Wing[i][n].AbsurdPercent;
					break;
				}
			}
		}
	}

	if(iDefencePercent >= 100)
	{
		return;
	}

	int iDamage = AttackDamage * (iDefencePercent - (ItemLevel * 2)) / 100.0f;

	if(iDamage < 0)
	{
		return;
	}

	AttackDamage = iDamage;
}

void cWingsDamage::PlayerCalculator(int aIndex)
{
	if(!g_ExLicense.CheckUser(eExUB::Gredy) &&
	   !g_ExLicense.CheckUser(eExUB::Gredy2) &&
	   !g_ExLicense.CheckUser(eExUB::GredyLocal) &&
	   !g_ExLicense.CheckUser(eExUB::SILVER1) &&
	   !g_ExLicense.CheckUser(eExUB::SILVER2) &&
	   !g_ExLicense.CheckUser(eExUB::SILVER_Local))
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->m_OfflineMode)
	{
		return;
	}

	if(lpUser->m_iLoadConfigNumber < 4)
	{
		return;
	}

	CItem * Wing = &lpUser->pInventory[7];

	int iClass = lpUser->Class;
	int iCount = this->m_iWingCount[iClass];

	PMSG_WINGS_INFO pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.h.set((LPBYTE)&pMsg, 0xFA, 0xBF, sizeof(pMsg));


	if(iClass < 0 || iClass > MAX_TYPE_PLAYER)
	{
		return;
	}
	//for(int i = 0; i < MAX_TYPE_PLAYER; i++)
	{
		//if(iClass = i)
		{
			for(int n = 0; n < iCount; n++)
			{
				pMsg.Wing[n].ItemType = ITEMGET(this->m_Wing[iClass][n].Type, this->m_Wing[iClass][n].Index);
				pMsg.Wing[n].Damage = this->m_Wing[iClass][n].AttackPercent;
				pMsg.Wing[n].Absord = this->m_Wing[iClass][n].AbsurdPercent;

				if(6660 == pMsg.Wing[n].ItemType)
				{
					//CItem * Darkhorse = &lpUser->pInventory[8];

					//pMsg.Wing[n].Absord = Darkhorse->m_PetItem_Level * this->m_Wing[iClass][n].AbsurdPercent;
				}
				
			}

			//break;
		}
	}

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));

}

void cWingsDamage::SetCharHorseAttack(int aIndex, int ItemType,  int ItemLevel, int& AttackDamage)
{
	if(this->m_bWingsCharacter)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int iClass = lpUser->Class;
	int iCount = this->m_iWingCount[iClass];
	int iDefencePercent = 0;

	for(int i = 0; i < MAX_TYPE_PLAYER; i++)
	{
		if(iClass = i)
		{
			for(int n = 0; n < iCount; n++)
			{
				if(ItemType == ITEMGET(this->m_Wing[i][n].Type, this->m_Wing[i][n].Index)) 
				{
					iDefencePercent = this->m_Wing[i][n].AbsurdPercent;
					break;
				}
			}
		}
	}

	if(iDefencePercent == 0)
	{
		return;
	}

	int iDamage = 100 - ((ItemLevel + iDefencePercent) / 2 );

	if(iDamage < 0)
	{
		return;
	}

	AttackDamage = iDamage;
}