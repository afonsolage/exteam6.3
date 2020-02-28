#include "StdAfx.h"
#include "PKClear.h"
#include "GameMain.h"
#include "ExFunction.h"
#include "Functions.h"
#include "ExLicense.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PKCLEAR_NPC==TRUE)

PKClear g_PKClear;
// ----------------------------------------------------------------------------------------------

void PKClear::Init()
{
	this->Enable = false;

	this->NPC_Class = 0;
	this->NPC_Map = 0;
	this->NPC_X = 0;
	this->NPC_Y = 0;

	this->ZenMoney = 0;
	this->JewelOfChaos = 0;
	this->JewelOfBless = 0;
	this->JewelOfChaos = 0;
}
// ----------------------------------------------------------------------------------------------

void PKClear::Load()
{
	this->Init();

	if(g_ExLicense.CheckUser(Local) || g_ExLicense.CheckUser(Artem)	|| g_ExLicense.CheckUser(eExUB::Artem2))
	{
		this->Read(gDirPath.GetNewPath("ExData\\PKClear.ini"));
	}
}
// ----------------------------------------------------------------------------------------------

void PKClear::Read(char* File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 0, File);

	this->NPC_Class = GetPrivateProfileInt("ExTeam", "NPC_Class", 0, File);
	this->NPC_Map = GetPrivateProfileInt("ExTeam", "NPC_Map", 0, File);
	this->NPC_X = GetPrivateProfileInt("ExTeam", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("ExTeam", "NPC_Y", 0, File);

	this->ZenFormula = GetPrivateProfileInt("ExTeam", "ZenFormula", 0, File);

	this->ZenMoney = GetPrivateProfileInt("ExTeam", "ZenMoney", 0, File);
	this->JewelOfChaos = GetPrivateProfileInt("ExTeam", "JewelOfChaos", 0, File);
	this->JewelOfBless = GetPrivateProfileInt("ExTeam", "JewelOfBless", 0, File);
	this->JewelOfSoul = GetPrivateProfileInt("ExTeam", "JewelOfSoul", 0, File);

	CheckAndFixMinNumber(ZenMoney, 0);
	CheckAndFixMinNumber(JewelOfChaos, 0);
	CheckAndFixMinNumber(JewelOfBless, 0);
	CheckAndFixMinNumber(JewelOfSoul, 0);
}
// ----------------------------------------------------------------------------------------------

bool PKClear::NPCDialog(int aIndex, int aNpcIndex)
{
	if(!this->Enable)
	{
 		return false;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(		lpNpc->Class		== this->NPC_Class 
		&&	lpNpc->MapNumber	== this->NPC_Map
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{
		this->GC_Price(aIndex);
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool PKClear::Check(int aIndex, int &iZen)
{
	LPOBJ lpUser = &gObj[aIndex];

	BYTE bResult = 1;
	int iPkLevel = lpUser->m_PK_Level;

	int iZenMoney = this->ZenMoney;
	int iChaosMoney = this->JewelOfChaos;
	int iBlessMoney = this->JewelOfBless;
	int iSoulMoney = this->JewelOfSoul;

	if(this->ZenMoney)
	{
		if(this->ZenFormula == 0)
		{
			if(iPkLevel > 3)
			{
				iZenMoney = this->ZenMoney;
			}
		}
		else
		{
			if(iPkLevel > 3)
			{
				iZenMoney = this->ZenMoney * ( iPkLevel - 3 );
			}
		}
	}

	if(iZenMoney > lpUser->Money)
	{
		bResult = 0;
	}

	if(iChaosMoney > 0)
	{
		if(gObjGetItemCountInInventory(aIndex, ITEMGET(12,15), 0) < iChaosMoney)
		{
			bResult = 0;
		}
	}

	if(iBlessMoney > 0)
	{
		if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,13), 0) < iBlessMoney)
		{
			bResult = 0;
		}
	}

	if(iSoulMoney > 0)
	{
		if(gObjGetItemCountInInventory(aIndex, ITEMGET(14,14), 0) < iSoulMoney)
		{
			bResult = 0;
		}
	}

	if(iPkLevel <= 3)
	{
		bResult = 0;
	}

	iZen = iZenMoney;

	return bResult;
}
// ----------------------------------------------------------------------------------------------

void PKClear::GC_Price(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	
	int iZenMoney = 0;
	int iPkLevel = lpUser->m_PK_Level;
	int iChaosMoney = this->JewelOfChaos;
	int iBlessMoney = this->JewelOfBless;
	int iSoulMoney = this->JewelOfSoul;

	BYTE bResult = this->Check(aIndex, iZenMoney);

	GC_PKCLEAR_PRICE pSend;
	pSend.h.set((LPBYTE)&pSend, 0xFB, 0xAC, sizeof(pSend));
	pSend.Result = bResult;
	pSend.PkLevel = iPkLevel;
	pSend.Zen = iZenMoney;
	pSend.Chaos = iChaosMoney;
	pSend.Bless = iBlessMoney;
	pSend.Soul = iSoulMoney;
	DataSend(aIndex, (LPBYTE)&pSend, pSend.h.size);
}
// ----------------------------------------------------------------------------------------------

void PKClear::CG_ResultRecv(int aIndex, CG_PKCLEAR_RESULT* aRecv)
{
	if(!this->Enable)
	{
 		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	if(aRecv->Result != 1)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int iZenMoney = 0;
	int iChaosMoney = this->JewelOfChaos;
	int iBlessMoney = this->JewelOfBless;
	int iSoulMoney = this->JewelOfSoul;

	if(!this->Check(aIndex, iZenMoney))
	{
		return;
	}

	if(iZenMoney > 0)
	{
		lpUser->Money -= iZenMoney;
	}
	if(iChaosMoney > 0)
	{
		gObjDeleteItemsCount(aIndex, ITEMGET(12,15), 0, iChaosMoney);
	}
	if(iBlessMoney > 0)
	{
		gObjDeleteItemsCount(aIndex, ITEMGET(14,13), 0, iBlessMoney);
	}
	if(iSoulMoney > 0)
	{
		gObjDeleteItemsCount(aIndex, ITEMGET(14,14), 0, iSoulMoney);
	}

	lpUser->m_PK_Level = 3;
	lpUser->m_PK_Count = 0;

	if(iZenMoney > 0)
	{
		GCMoneySend(aIndex,lpUser->Money);
	}

	GCPkLevelSend(aIndex,lpUser->m_PK_Level);
}
// ----------------------------------------------------------------------------------------------

#endif