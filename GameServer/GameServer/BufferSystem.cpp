#include "StdAfx.h"
#include "BufferSystem.h"
#include "GameMain.h"
#include "logproc.h"
#include "ExUser.h"
//#include "BuffEffectSlot.h"
#include "ObjCalCharacter.h"
//#include "BuffManagerEx.h"
#include "Functions.h"
#include "BuffManager.h"
#include "ExLicense.h"

#if(CUSTOM_NPC_BUFFER==TRUE)
// ----------------------------------------------------------------------------------------------

BufferSystem g_BufferSystem;
// ----------------------------------------------------------------------------------------------

void BufferSystem::Init()
{
	this->Enable = false;
	this->NPC_Class = 0;
	this->NPC_Map = 0;
	this->NPC_X = 0;
	this->NPC_Y = 0;

	this->Buff1_ZenMoney = 0;
	this->Buff1_JewelOfBless = 0;
	this->Buff1_JewelOfSoul = 0;
	this->Buff1_Bonus = 0;

	this->Buff2_ZenMoney = 0;
	this->Buff2_JewelOfBless = 0;
	this->Buff2_JewelOfSoul = 0;
	this->Buff2_Bonus = 0;

	this->Buff3_ZenMoney = 0;
	this->Buff3_JewelOfBless = 0;
	this->Buff3_JewelOfSoul = 0;
	this->Buff3_Bonus = 0;

	this->Buff4_ZenMoney = 0;
	this->Buff4_JewelOfBless = 0;
	this->Buff4_JewelOfSoul = 0;
	this->Buff4_Bonus = 0;

	this->Buff5_ZenMoney = 0;
	this->Buff5_JewelOfBless = 0;
	this->Buff5_JewelOfSoul = 0;
	this->Buff5_Bonus = 0;

	this->Buff6_ZenMoney = 0;
	this->Buff6_JewelOfBless = 0;
	this->Buff6_JewelOfSoul = 0;
	this->Buff6_Bonus = 0;
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::Load()
{
	this->Init();
	if(!g_ExLicense.user.NpcBuffer)
	{
		return;
	}
	this->Read(gDirPath.GetNewPath("ExData\\BufferSystem.ini"));
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::Read(char* File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 0, File);
	this->NPC_Class = GetPrivateProfileInt("ExTeam", "NPC_Class", 0, File);
	this->NPC_Map = GetPrivateProfileInt("ExTeam", "NPC_Map", 0, File);
	this->NPC_X = GetPrivateProfileInt("ExTeam", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("ExTeam", "NPC_Y", 0, File);

	this->Buff1_ZenMoney = GetPrivateProfileInt("ExTeam", "Buff1_ZenMoney", 0, File);
	this->Buff1_JewelOfBless = GetPrivateProfileInt("ExTeam", "Buff1_JewelOfBless", 0, File);
	this->Buff1_JewelOfSoul = GetPrivateProfileInt("ExTeam", "Buff1_JewelOfSoul", 0, File);
	this->Buff1_Bonus = GetPrivateProfileInt("ExTeam", "Buff1_Bonus", 0, File);

	this->Buff2_ZenMoney = GetPrivateProfileInt("ExTeam", "Buff2_ZenMoney", 0, File);
	this->Buff2_JewelOfBless = GetPrivateProfileInt("ExTeam", "Buff2_JewelOfBless", 0, File);
	this->Buff2_JewelOfSoul = GetPrivateProfileInt("ExTeam", "Buff2_JewelOfSoul", 0, File);
	this->Buff2_Bonus = GetPrivateProfileInt("ExTeam", "Buff2_Bonus", 0, File);

	this->Buff3_ZenMoney = GetPrivateProfileInt("ExTeam", "Buff3_ZenMoney", 0, File);
	this->Buff3_JewelOfBless = GetPrivateProfileInt("ExTeam", "Buff3_JewelOfBless", 0, File);
	this->Buff3_JewelOfSoul = GetPrivateProfileInt("ExTeam", "Buff3_JewelOfSoul", 0, File);
	this->Buff3_Bonus = GetPrivateProfileInt("ExTeam", "Buff3_Bonus", 0, File);

	this->Buff4_ZenMoney = GetPrivateProfileInt("ExTeam", "Buff4_ZenMoney", 0, File);
	this->Buff4_JewelOfBless = GetPrivateProfileInt("ExTeam", "Buff4_JewelOfBless", 0, File);
	this->Buff4_JewelOfSoul = GetPrivateProfileInt("ExTeam", "Buff4_JewelOfSoul", 0, File);
	this->Buff4_Bonus = GetPrivateProfileInt("ExTeam", "Buff4_Bonus", 0, File);

	this->Buff5_ZenMoney = GetPrivateProfileInt("ExTeam", "Buff5_ZenMoney", 0, File);
	this->Buff5_JewelOfBless = GetPrivateProfileInt("ExTeam", "Buff5_JewelOfBless", 0, File);
	this->Buff5_JewelOfSoul = GetPrivateProfileInt("ExTeam", "Buff5_JewelOfSoul", 0, File);
	this->Buff5_Bonus = GetPrivateProfileInt("ExTeam", "Buff5_Bonus", 0, File);

	this->Buff6_ZenMoney = GetPrivateProfileInt("ExTeam", "Buff6_ZenMoney", 0, File);
	this->Buff6_JewelOfBless = GetPrivateProfileInt("ExTeam", "Buff6_JewelOfBless", 0, File);
	this->Buff6_JewelOfSoul = GetPrivateProfileInt("ExTeam", "Buff6_JewelOfSoul", 0, File);
	this->Buff6_Bonus = GetPrivateProfileInt("ExTeam", "Buff6_Bonus", 0, File);
}
// ----------------------------------------------------------------------------------------------

bool BufferSystem::Dialog(int aIndex, int aNpcIndex)
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
		this->GC_OpenWindow(aIndex);
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::GC_OpenWindow(int aIndex)
{
	if(!this->Enable)
	{
 		return;
	}

	// ----

	GC_BuffNpcOpen pSend = { NULL };
	pSend.h.set((LPBYTE)&pSend, 0xFB, 0x20, sizeof(pSend));

	pSend.Result1 = this->Check(aIndex, 1);
	pSend.Zen1 = this->Buff1_ZenMoney;
	pSend.Bless1 = this->Buff1_JewelOfBless;
	pSend.Soul1 = this->Buff1_JewelOfSoul;
	pSend.Bonus1 = this->Buff1_Bonus;

	pSend.Result2 = this->Check(aIndex, 2);
	pSend.Zen2 = this->Buff2_ZenMoney;
	pSend.Bless2 = this->Buff2_JewelOfBless;
	pSend.Soul2 = this->Buff2_JewelOfSoul;
	pSend.Bonus2 = this->Buff2_Bonus;

	pSend.Result3 = this->Check(aIndex, 3);
	pSend.Zen3 = this->Buff3_ZenMoney;
	pSend.Bless3 = this->Buff3_JewelOfBless;
	pSend.Soul3 = this->Buff3_JewelOfSoul;
	pSend.Bonus3 = this->Buff3_Bonus;

	pSend.Result4 = this->Check(aIndex, 4);
	pSend.Zen4 = this->Buff4_ZenMoney;
	pSend.Bless4 = this->Buff4_JewelOfBless;
	pSend.Soul4 = this->Buff4_JewelOfSoul;
	pSend.Bonus4 = this->Buff4_Bonus;

	pSend.Result5 = this->Check(aIndex,5);
	pSend.Zen5 = this->Buff5_ZenMoney;
	pSend.Bless5 = this->Buff5_JewelOfBless;
	pSend.Soul5 = this->Buff5_JewelOfSoul;
	pSend.Bonus5 = this->Buff5_Bonus;

	pSend.Result6 = this->Check(aIndex,6);
	pSend.Zen6 = this->Buff6_ZenMoney;
	pSend.Bless6 = this->Buff6_JewelOfBless;
	pSend.Soul6 = this->Buff6_JewelOfSoul;
	pSend.Bonus6 = this->Buff6_Bonus;

	DataSend(aIndex, (LPBYTE)&pSend, pSend.h.size);
}
// ----------------------------------------------------------------------------------------------

bool BufferSystem::Check(int aIndex, int type)
{
	LPOBJ lpUser = &gObj[aIndex];

	BYTE bResult = 1;

	int iZenMoney = 0;
	int iBlessMoney = 0;
	int iSoulMoney = 0;
	int iBonusMoney = 0;

	int idBuffer = AT_NPC_BUFF_EXP;

	if(type == 1)
	{
		iZenMoney = this->Buff1_ZenMoney;
		iBlessMoney = this->Buff1_JewelOfBless;
		iSoulMoney = this->Buff1_JewelOfSoul;
		iBonusMoney = this->Buff1_Bonus;
		idBuffer = AT_NPC_BUFF_EXP;
	}
	if(type == 2)
	{
		iZenMoney = this->Buff2_ZenMoney;
		iBlessMoney = this->Buff2_JewelOfBless;
		iSoulMoney = this->Buff2_JewelOfSoul;
		iBonusMoney = this->Buff2_Bonus;
		idBuffer = AT_NPC_BUFF_DAMAGE;
	}
	if(type == 3)
	{
		iZenMoney = this->Buff3_ZenMoney;
		iBlessMoney = this->Buff3_JewelOfBless;
		iSoulMoney = this->Buff3_JewelOfSoul;
		iBonusMoney = this->Buff3_Bonus;
		idBuffer = AT_NPC_BUFF_DEFENCE;
	}
	if(type == 4)
	{
		iZenMoney = this->Buff4_ZenMoney;
		iBlessMoney = this->Buff4_JewelOfBless;
		iSoulMoney = this->Buff4_JewelOfSoul;
		iBonusMoney = this->Buff4_Bonus;
		idBuffer = AT_NPC_BUFF_EXL_CRIT;
	}
	if(type == 5)
	{
		iZenMoney = this->Buff5_ZenMoney;
		iBlessMoney = this->Buff5_JewelOfBless;
		iSoulMoney = this->Buff5_JewelOfSoul;
		iBonusMoney = this->Buff5_Bonus;
		idBuffer = AT_NPC_BUFF_DROP;
	}
	if(type == 6)
	{
		iZenMoney = this->Buff6_ZenMoney;
		iBlessMoney = this->Buff6_JewelOfBless;
		iSoulMoney = this->Buff6_JewelOfSoul;
		iBonusMoney = this->Buff6_Bonus;
		idBuffer = AT_NPC_BUFF_DOUBLE;
	}

	if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		if(iZenMoney > 0 && iZenMoney > lpUser->ExCred)
		{
			bResult = 0;
		}
	}
	else
	{
		if(iZenMoney > 0 && iZenMoney > lpUser->Money)
		{
			bResult = 0;
		}
	}

	if(iBlessMoney > 0)
	{
		if( iBlessMoney > gObjGetItemCountInInventory(aIndex, ITEMGET(14,13), 0))
		{
			bResult = 0;
		}
	}

	if(iSoulMoney > 0)
	{
		if(iSoulMoney > gObjGetItemCountInInventory(aIndex, ITEMGET(14,14), 0))
		{
			bResult = 0;
		}
	}

	if(iBonusMoney > 0 && iBonusMoney > lpUser->GameShop.WCoinC)
	{
		bResult = 0;
	}

	//if(g_BuffManagerEx.CheckExBuffData(aIndex, idBuffer) == TRUE )
	if( gObjSearchActiveEffect(lpUser,idBuffer) == TRUE)
	{
		bResult = 0;
	}

	return bResult;
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::CG_ResultRecv(int aIndex, CG_BuffNpcResult* aRecv)
{
	if(!this->Enable)
	{
 		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	if(aRecv->Result < 1 || aRecv->Result > 6)
	{
		return;
	}

	int type = aRecv->Result;

	if(!this->Check(aIndex, type))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	BYTE bResult = 1;

	int iZenMoney = 0;
	int iBlessMoney = 0;
	int iSoulMoney = 0;
	int iBonusMoney = 0;
	int idBuffer = AT_NPC_BUFF_EXP;


	if(type == 1)
	{
		iZenMoney = this->Buff1_ZenMoney;
		iBlessMoney = this->Buff1_JewelOfBless;
		iSoulMoney = this->Buff1_JewelOfSoul;
		iBonusMoney = this->Buff1_Bonus;
		idBuffer = AT_NPC_BUFF_EXP;
	}
	if(type == 2)
	{
		iZenMoney = this->Buff2_ZenMoney;
		iBlessMoney = this->Buff2_JewelOfBless;
		iSoulMoney = this->Buff2_JewelOfSoul;
		iBonusMoney = this->Buff2_Bonus;
		idBuffer = AT_NPC_BUFF_DAMAGE;
	}
	if(type == 3)
	{
		iZenMoney = this->Buff3_ZenMoney;
		iBlessMoney = this->Buff3_JewelOfBless;
		iSoulMoney = this->Buff3_JewelOfSoul;
		iBonusMoney = this->Buff3_Bonus;
		idBuffer = AT_NPC_BUFF_DEFENCE;
	}
	if(type == 4)
	{
		iZenMoney = this->Buff4_ZenMoney;
		iBlessMoney = this->Buff4_JewelOfBless;
		iSoulMoney = this->Buff4_JewelOfSoul;
		iBonusMoney = this->Buff4_Bonus;
		idBuffer = AT_NPC_BUFF_EXL_CRIT;
	}
	if(type == 5)
	{
		iZenMoney = this->Buff5_ZenMoney;
		iBlessMoney = this->Buff5_JewelOfBless;
		iSoulMoney = this->Buff5_JewelOfSoul;
		iBonusMoney = this->Buff5_Bonus;
		idBuffer = AT_NPC_BUFF_DROP;
	}
	if(type == 6)
	{
		iZenMoney = this->Buff6_ZenMoney;
		iBlessMoney = this->Buff6_JewelOfBless;
		iSoulMoney = this->Buff6_JewelOfSoul;
		iBonusMoney = this->Buff6_Bonus;
		idBuffer = AT_NPC_BUFF_DOUBLE;
	}

	if(iZenMoney > 0)
	{
		if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
		{
			lpUser->ExCred -= iZenMoney;
			ExUserDataSend(aIndex);
		}
		else
		{
			lpUser->Money -= iZenMoney;
			GCMoneySend(aIndex,lpUser->Money);
		}
	}
	if(iBlessMoney > 0)
	{
		gObjDeleteItemsCount(aIndex, ITEMGET(14,13), 0, iBlessMoney);
	}
	if(iSoulMoney > 0)
	{
		gObjDeleteItemsCount(aIndex, ITEMGET(14,14), 0, iSoulMoney);
	}
	if(iBonusMoney > 0)
	{
		lpUser->GameShop.WCoinC -= iBonusMoney;
		gGameShop.GDSaveUserInfo(aIndex);
		ExUserDataSend(aIndex);
	}

	//if(g_BuffManagerEx.CheckExBuffData(aIndex, idBuffer) == FALSE )
	if( gObjSearchActiveEffect(lpUser,idBuffer) == FALSE)
	{
		// --
		if(idBuffer == AT_NPC_BUFF_EXP)
		{
			lpUser->ExpBuffTime = 86400;
		}
		// --
		if(idBuffer == AT_NPC_BUFF_DAMAGE)
		{
			lpUser->DamageBuffTime = 86400;
		}
		// --
		if(idBuffer == AT_NPC_BUFF_DEFENCE)
		{
			lpUser->DefenceBuffTime = 86400;
		}
		// --
		if(idBuffer == AT_NPC_BUFF_EXL_CRIT)
		{
			lpUser->BattleBuffTime = 86400;
		}
		// --
		if(idBuffer == AT_NPC_BUFF_DROP)
		{
			lpUser->DropBuffTime = 86400;
		}
		// --
		if(idBuffer == AT_NPC_BUFF_DOUBLE)
		{
			lpUser->DoubleBuffTime = 86400;
		}
		// --

		//g_BuffManagerEx.AddExBuffData(aIndex, idBuffer, 86400);
		gObjApplyBuffEffectDuration(lpUser, idBuffer, 0, 0, 0, 0, 86400);

		this->GC_OpenWindow(aIndex);
	}

	gObjCalCharacter(aIndex);

	//g_ExUser.UpdateCharEx(aIndex);

}
// ----------------------------------------------------------------------------------------------

void BufferSystem::Timer(int aIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}
	// --
	if(lpUser->ExpBuffTime > 0)
	{
		lpUser->ExpBuffTime--;
	}
	// --
	if(lpUser->DamageBuffTime > 0)
	{
		lpUser->DamageBuffTime--;
	}
	// --
	if(lpUser->DefenceBuffTime > 0)
	{
		lpUser->DefenceBuffTime--;
	}
	// --
	if(lpUser->BattleBuffTime > 0)
	{
		lpUser->BattleBuffTime--;
	}
	// --
	if(lpUser->DropBuffTime > 0)
	{
		lpUser->DropBuffTime--;
	}
	// --
	if(lpUser->DoubleBuffTime > 0)
	{
		lpUser->DoubleBuffTime--;
	}
	// --
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::UserConnect(int aIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}
	
	// --
	if(lpUser->ExpBuffTime > 0)
	{
		//g_BuffManagerEx.AddExBuffData(aIndex, AT_NPC_BUFF_EXP, lpUser->ExpBuffTime);
		gObjApplyBuffEffectDuration(lpUser, AT_NPC_BUFF_EXP, 0, 0, 0, 0, lpUser->ExpBuffTime);
	}
	// --
	if(lpUser->DamageBuffTime > 0)
	{
		//g_BuffManagerEx.AddExBuffData(aIndex, AT_NPC_BUFF_DAMAGE, lpUser->DamageBuffTime);
		gObjApplyBuffEffectDuration(lpUser, AT_NPC_BUFF_DAMAGE, 0, 0, 0, 0, lpUser->DamageBuffTime);
	}
	// --
	if(lpUser->DefenceBuffTime > 0)
	{
		//g_BuffManagerEx.AddExBuffData(aIndex, AT_NPC_BUFF_DEFENCE, lpUser->DefenceBuffTime);
		gObjApplyBuffEffectDuration(lpUser, AT_NPC_BUFF_DEFENCE, 0, 0, 0, 0, lpUser->DefenceBuffTime);
	}
	// --
	if(lpUser->BattleBuffTime > 0)
	{
		//g_BuffManagerEx.AddExBuffData(aIndex, AT_NPC_BUFF_EXL_CRIT, lpUser->BattleBuffTime);
		gObjApplyBuffEffectDuration(lpUser, AT_NPC_BUFF_EXL_CRIT, 0, 0, 0, 0, lpUser->BattleBuffTime);
	}
	// --
	if(lpUser->DropBuffTime > 0)
	{
		//g_BuffManagerEx.AddExBuffData(aIndex, AT_NPC_BUFF_DROP, lpUser->DropBuffTime);
		gObjApplyBuffEffectDuration(lpUser, AT_NPC_BUFF_DROP, 0, 0, 0, 0, lpUser->DropBuffTime);
	}
	// --
	if(lpUser->DoubleBuffTime > 0)
	{
		//g_BuffManagerEx.AddExBuffData(aIndex, AT_NPC_BUFF_DOUBLE, lpUser->DoubleBuffTime);
		gObjApplyBuffEffectDuration(lpUser, AT_NPC_BUFF_DOUBLE, 0, 0, 0, 0, lpUser->DoubleBuffTime);
	}
	// --
}
// ----------------------------------------------------------------------------------------------


#endif