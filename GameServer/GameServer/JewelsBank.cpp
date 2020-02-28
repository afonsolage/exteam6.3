#include "StdAfx.h"
#include "JewelsBank.h"
#include "user.h"
#include "Message.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "ExUser.h"
#include "ExLicense.h"
#include "ExFunction.h"
#include "ExText.h"

JewelsBank gJewelsBank;

void JewelsBank::Load()
{
	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,JEWELSBANK_DIR); 
#ifdef PRIVATE_MODULE
#if _CONFLICT_
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea))
	{
		this->ExChaosTeen = GetPrivateProfileInt("ExTeam","ExChaosTeen",0,JEWELSBANK_DIR);
		this->ExChaosTwenty = GetPrivateProfileInt("ExTeam","ExChaosTwenty",0,JEWELSBANK_DIR);
		this->ExChaosThirty = GetPrivateProfileInt("ExTeam","ExChaosThirty",0,JEWELSBANK_DIR);
		this->ExChaosForty = GetPrivateProfileInt("ExTeam","ExChaosForty",0,JEWELSBANK_DIR);
		this->ExChaosFifty = GetPrivateProfileInt("ExTeam","ExChaosFifty",0,JEWELSBANK_DIR);
		this->ExChaosHundred = GetPrivateProfileInt("ExTeam","ExChaosHundred",0,JEWELSBANK_DIR);

		this->ExBlessTeen = GetPrivateProfileInt("ExTeam","ExBlessTeen",0,JEWELSBANK_DIR);
		this->ExBlessTwenty = GetPrivateProfileInt("ExTeam","ExBlessTwenty",0,JEWELSBANK_DIR);
		this->ExBlessThirty = GetPrivateProfileInt("ExTeam","ExBlessThirty",0,JEWELSBANK_DIR);
		this->ExBlessForty = GetPrivateProfileInt("ExTeam","ExBlessForty",0,JEWELSBANK_DIR);
		this->ExBlessFifty = GetPrivateProfileInt("ExTeam","ExBlessFifty",0,JEWELSBANK_DIR);
		this->ExBlessHundred = GetPrivateProfileInt("ExTeam","ExBlessHundred",0,JEWELSBANK_DIR);

		this->ExSoulTeen = GetPrivateProfileInt("ExTeam","ExSoulTeen",0,JEWELSBANK_DIR);
		this->ExSoulTwenty = GetPrivateProfileInt("ExTeam","ExSoulTwenty",0,JEWELSBANK_DIR);
		this->ExSoulThirty = GetPrivateProfileInt("ExTeam","ExSoulThirty",0,JEWELSBANK_DIR);
		this->ExSoulForty = GetPrivateProfileInt("ExTeam","ExSoulForty",0,JEWELSBANK_DIR);
		this->ExSoulFifty = GetPrivateProfileInt("ExTeam","ExSoulFifty",0,JEWELSBANK_DIR);
		this->ExSoulHundred = GetPrivateProfileInt("ExTeam","ExSoulHundred",0,JEWELSBANK_DIR);

		this->ExLifeTeen = GetPrivateProfileInt("ExTeam","ExLifeTeen",0,JEWELSBANK_DIR);
		this->ExLifeTwenty = GetPrivateProfileInt("ExTeam","ExLifeTwenty",0,JEWELSBANK_DIR);
		this->ExLifeThirty = GetPrivateProfileInt("ExTeam","ExLifeThirty",0,JEWELSBANK_DIR);
		this->ExLifeForty = GetPrivateProfileInt("ExTeam","ExLifeForty",0,JEWELSBANK_DIR);
		this->ExLifeFifty = GetPrivateProfileInt("ExTeam","ExLifeFifty",0,JEWELSBANK_DIR);
		this->ExLifeHundred = GetPrivateProfileInt("ExTeam","ExLifeHundred",0,JEWELSBANK_DIR);

		this->ExCreateonTeen = GetPrivateProfileInt("ExTeam","ExCreateonTeen",0,JEWELSBANK_DIR);
		this->ExCreateonTwenty = GetPrivateProfileInt("ExTeam","ExCreateonTwenty",0,JEWELSBANK_DIR);
		this->ExCreateonThirty = GetPrivateProfileInt("ExTeam","ExCreateonThirty",0,JEWELSBANK_DIR);
		this->ExCreateonForty = GetPrivateProfileInt("ExTeam","ExCreateonForty",0,JEWELSBANK_DIR);
		this->ExCreateonFifty = GetPrivateProfileInt("ExTeam","ExCreateonFifty",0,JEWELSBANK_DIR);
		this->ExCreateonHundred = GetPrivateProfileInt("ExTeam","ExCreateonHundred",0,JEWELSBANK_DIR);

	/**/
		this->ExGuardianTeen = GetPrivateProfileInt("ExTeam","ExGuardianTeen",0,JEWELSBANK_DIR);
		this->ExGuardianTwenty = GetPrivateProfileInt("ExTeam","ExGuardianTwenty",0,JEWELSBANK_DIR);
		this->ExGuardianThirty = GetPrivateProfileInt("ExTeam","ExGuardianThirty",0,JEWELSBANK_DIR);
		this->ExGuardianForty = GetPrivateProfileInt("ExTeam","ExGuardianForty",0,JEWELSBANK_DIR);
		this->ExGuardianFifty = GetPrivateProfileInt("ExTeam","ExGuardianFifty",0,JEWELSBANK_DIR);
		this->ExGuardianHundred = GetPrivateProfileInt("ExTeam","ExGuardianHundred",0,JEWELSBANK_DIR);

		this->ExHarmonyTeen = GetPrivateProfileInt("ExTeam","ExHarmonyTeen",0,JEWELSBANK_DIR);
		this->ExHarmonyTwenty = GetPrivateProfileInt("ExTeam","ExHarmonyTwenty",0,JEWELSBANK_DIR);
		this->ExHarmonyThirty = GetPrivateProfileInt("ExTeam","ExHarmonyThirty",0,JEWELSBANK_DIR);
		this->ExHarmonyForty = GetPrivateProfileInt("ExTeam","ExHarmonyForty",0,JEWELSBANK_DIR);
		this->ExHarmonyFifty = GetPrivateProfileInt("ExTeam","ExHarmonyFifty",0,JEWELSBANK_DIR);
		this->ExHarmonyHundred = GetPrivateProfileInt("ExTeam","ExHarmonyHundred",0,JEWELSBANK_DIR);

		this->ExLowStoneTeen = GetPrivateProfileInt("ExTeam","ExLowStoneTeen",0,JEWELSBANK_DIR);
		this->ExLowStoneTwenty = GetPrivateProfileInt("ExTeam","ExLowStoneTwenty",0,JEWELSBANK_DIR);
		this->ExLowStoneThirty = GetPrivateProfileInt("ExTeam","ExLowStoneThirty",0,JEWELSBANK_DIR);
		this->ExLowStoneForty = GetPrivateProfileInt("ExTeam","ExLowStoneForty",0,JEWELSBANK_DIR);
		this->ExLowStoneFifty = GetPrivateProfileInt("ExTeam","ExLowStoneFifty",0,JEWELSBANK_DIR);
		this->ExLowStoneHundred = GetPrivateProfileInt("ExTeam","ExLowStoneHundred",0,JEWELSBANK_DIR);

		this->ExHighStoneTeen = GetPrivateProfileInt("ExTeam","ExHighStoneTeen",0,JEWELSBANK_DIR);
		this->ExHighStoneTwenty = GetPrivateProfileInt("ExTeam","ExHighStoneTwenty",0,JEWELSBANK_DIR);
		this->ExHighStoneThirty = GetPrivateProfileInt("ExTeam","ExHighStoneThirty",0,JEWELSBANK_DIR);
		this->ExHighStoneForty = GetPrivateProfileInt("ExTeam","ExHighStoneForty",0,JEWELSBANK_DIR);
		this->ExHighStoneFifty = GetPrivateProfileInt("ExTeam","ExHighStoneFifty",0,JEWELSBANK_DIR);
		this->ExHighStoneHundred = GetPrivateProfileInt("ExTeam","ExHighStoneHundred",0,JEWELSBANK_DIR);

		this->ExGemStoneTeen = GetPrivateProfileInt("ExTeam","ExGemStoneTeen",0,JEWELSBANK_DIR);
		this->ExGemStoneTwenty = GetPrivateProfileInt("ExTeam","ExGemStoneTwenty",0,JEWELSBANK_DIR);
		this->ExGemStoneThirty = GetPrivateProfileInt("ExTeam","ExGemStoneThirty",0,JEWELSBANK_DIR);
		this->ExGemStoneForty = GetPrivateProfileInt("ExTeam","ExGemStoneForty",0,JEWELSBANK_DIR);
		this->ExGemStoneFifty = GetPrivateProfileInt("ExTeam","ExGemStoneFifty",0,JEWELSBANK_DIR);
		this->ExGemStoneHundred = GetPrivateProfileInt("ExTeam","ExGemStoneHundred",0,JEWELSBANK_DIR);
	/**/
	}
#endif
#endif
}

void JewelsBank::sendchaosbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(12,15),0) < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(147),Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(12,15),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->ChaosBank += Count;
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,g_ExText.GetText(148),Count);
}

void JewelsBank::sendblessbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,13),0) < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(149),Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,13),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->BlessBank += Count;
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,g_ExText.GetText(150),Count);
}

void JewelsBank::sendsoulbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,14),0) < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(151),Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,14),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->SoulBank += Count;
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,g_ExText.GetText(152),Count);
}

void JewelsBank::sendlifebank(int aIndex, int Count)
{
	if(!this->Enable) return;
#ifdef PRIVATE_MODULE
	if(g_ExLicense.CheckUser(eExUB::Vadim))
	{
		if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,187),0) < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] Need %d JoR",Count);
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,187),0,Count);
		LPOBJ lpObj = &gObj[aIndex];
		lpObj->LifeBank += Count;
		ExUserDataSend(aIndex);

		MsgNormal(aIndex,"[JewelsBank] Send %d JoR",Count);
	}
	else
	{
		if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,16),0) < Count)
		{
			MsgNormal(aIndex,g_ExText.GetText(153),Count);
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(14,16),0,Count);
		LPOBJ lpObj = &gObj[aIndex];
		lpObj->LifeBank += Count;
		ExUserDataSend(aIndex);

		MsgNormal(aIndex,g_ExText.GetText(154),Count);
	}
#else
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,16),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Life",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,16),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->LifeBank += Count;
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d Life",Count);
#endif
}

void JewelsBank::sendcreateonbank(int aIndex, int Count)
{
	if(!this->Enable) return;

	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,22),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Createon",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,22),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->CreateonBank += Count;
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d Createon",Count);
}

//-----------------------------------------------------

void JewelsBank::recvchaosbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->ChaosBank < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(155),Count);
		return;
	}

	//if(CheckInventoryEmptySpace(lpObj,4,2) == false )
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(156),Count);
		return;
	}
	lpObj->ChaosBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(12,15),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,g_ExText.GetText(157),Count);
}

void JewelsBank::recvblessbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->BlessBank < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(158),Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(156),Count);
		return;
	}
	lpObj->BlessBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,13),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,g_ExText.GetText(159),Count);
}

void JewelsBank::recvsoulbank(int aIndex, int Count)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->SoulBank < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(160),Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,g_ExText.GetText(156),Count);
		return;
	}
	lpObj->SoulBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,14),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);
	MsgNormal(aIndex,g_ExText.GetText(161),Count);
}

void JewelsBank::recvlifebank(int aIndex, int Count)
{
	if(!this->Enable) return;

#ifdef PRIVATE_MODULE
	if(g_ExLicense.CheckUser(eExUB::Vadim))
	{
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->LifeBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d JoR",Count);
			return;
		}
		if(ExCheckInventoryEmptySpace(aIndex) < Count)
		{
			MsgNormal(aIndex,g_ExText.GetText(156),Count);
			return;
		}
		lpObj->LifeBank -= Count;
		for(int i=0;i<Count;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,187),0,0,0,0,0,aIndex,0,0);
		}
		ExUserDataSend(aIndex);

		MsgNormal(aIndex,"[JewelsBank] Recv %d JoR",Count);
	}
	else
	{
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->LifeBank < Count)
		{
			MsgNormal(aIndex,g_ExText.GetText(162),Count);
			return;
		}
		if(ExCheckInventoryEmptySpace(aIndex) < Count)
		{
			MsgNormal(aIndex,g_ExText.GetText(156),Count);
			return;
		}
		lpObj->LifeBank -= Count;
		for(int i=0;i<Count;i++)
		{
			ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,16),0,0,0,0,0,aIndex,0,0);
		}
		ExUserDataSend(aIndex);

		MsgNormal(aIndex,g_ExText.GetText(163),Count);
	}
#else
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LifeBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Life",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->LifeBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,16),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d Life",Count);
#endif
}

void JewelsBank::recvcreateonbank(int aIndex, int Count)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->CreateonBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Createon",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->CreateonBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,22),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d Createon",Count);

}

#ifdef PRIVATE_MODULE
#if _CONFLICT_
void JewelsBank::exchaos(int aIndex, int Count)
{
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea))
	{
		if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->ChaosBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Chaos",Count);
			return;
		}

		if (Count == 10)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ExCred += ExChaosTeen;
			CountExChaos = ExChaosTeen;
		}
		else if (Count == 20)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ExCred += ExChaosTwenty;
			CountExChaos = ExChaosTwenty;
		}
		else if (Count == 30)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ExCred += ExChaosThirty;
			CountExChaos = ExChaosThirty;
		}
		else if (Count == 40)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ExCred += ExChaosForty;
			CountExChaos = ExChaosForty;
		}
		else if (Count == 50)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ExCred += ExChaosFifty;
			CountExChaos = ExChaosFifty;
		}
		else if (Count == 100)
		{
			lpObj->ChaosBank -= Count;
			lpObj->ExCred += ExChaosHundred;
			CountExChaos = ExChaosHundred;
		}
		else
		{
			MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
			return;
		}
		
		/*int ExChaosForty;
	int ExChaosFifty;
	int ExChaosHundred;*/

		ExUserDataSend(aIndex);
		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Chaos Added %d Credits" ,Count, CountExChaos);
	}
}

void JewelsBank::exbless(int aIndex, int Count)
{
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea))
	{
		if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->BlessBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Bless",Count);
			return;
		}
		if (Count == 10)
		{
			lpObj->BlessBank -= Count;
			lpObj->ExCred += ExBlessTeen;
			CountExBless = ExBlessTeen;
		}
		else if (Count == 20)
		{
			lpObj->BlessBank -= Count;
			lpObj->ExCred += ExBlessTwenty;
			CountExBless = ExBlessTwenty;
		}
		else if (Count == 30)
		{
			lpObj->BlessBank -= Count;
			lpObj->ExCred += ExBlessThirty;
			CountExBless = ExBlessThirty;
		}		
		else if (Count == 40)
		{
			lpObj->BlessBank -= Count;
			lpObj->ExCred += ExBlessForty;
			CountExBless = ExBlessForty;
		}
		else if (Count == 50)
		{
			lpObj->BlessBank -= Count;
			lpObj->ExCred += ExBlessFifty;
			CountExBless = ExBlessFifty;
		}
		else if (Count == 100)
		{
			lpObj->BlessBank -= Count;
			lpObj->ExCred += ExBlessHundred;
			CountExBless = ExBlessHundred;
		}
		else{
			MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
			return;
		}

		ExUserDataSend(aIndex);
		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Bless Added %d Credits" ,Count, CountExBless);
	}
}

void JewelsBank::exsoul(int aIndex, int Count)
{
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea))
	{
	if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->SoulBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Soul",Count);
			return;
		}
		
		if (Count == 10)
		{
			lpObj->SoulBank -= Count;
			lpObj->ExCred += ExSoulTeen;
			CountExSoul = ExSoulTeen;
		}
		else if (Count == 20)
		{
			lpObj->SoulBank -= Count;
			lpObj->ExCred += ExSoulTwenty;
			CountExSoul = ExSoulTwenty;
		}
		else if (Count == 30)
		{
			lpObj->SoulBank -= Count;
			lpObj->ExCred += ExSoulThirty;
			CountExSoul = ExSoulThirty;
		}
		else if (Count == 40)
		{
			lpObj->SoulBank -= Count;
			lpObj->ExCred += ExSoulForty;
			CountExSoul = ExSoulForty;
		}
		else if (Count == 50)
		{
			lpObj->SoulBank -= Count;
			lpObj->ExCred += ExSoulFifty;
			CountExSoul = ExSoulFifty;
		}
		else if (Count == 100)
		{
			lpObj->SoulBank -= Count;
			lpObj->ExCred += ExSoulHundred;
			CountExSoul = ExSoulHundred;
		}
		else{
			MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
			return;
		}
		
		
		ExUserDataSend(aIndex);
		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Soul Added %d Credits" ,Count, CountExSoul);
	}
}

void JewelsBank::exlife(int aIndex, int Count)
{
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea))
	{
		if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->LifeBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Life",Count);
			return;
		}
		if (Count == 10)
			{
				lpObj->LifeBank -= Count;
				lpObj->ExCred += ExLifeTeen;
				CountExLife = ExLifeTeen;
			}
			else if (Count == 20)
			{
				lpObj->LifeBank -= Count;
				lpObj->ExCred += ExLifeTwenty;
				CountExLife = ExLifeTwenty;
			}
			else if (Count == 30)
			{
				lpObj->LifeBank -= Count;
				lpObj->ExCred += ExLifeThirty;
				CountExLife = ExLifeThirty;
			}
		else if (Count == 40)
		{
			lpObj->LifeBank -= Count;
			lpObj->ExCred += ExLifeForty;
			CountExLife = ExLifeForty;
		}
		else if (Count == 50)
		{
			lpObj->LifeBank -= Count;
			lpObj->ExCred += ExLifeFifty;
			CountExLife = ExLifeFifty;
		}
		else if (Count == 100)
		{
			lpObj->LifeBank -= Count;
			lpObj->ExCred += ExLifeHundred;
			CountExLife = ExLifeHundred;
		}
		else{
				MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
				return;
			}

		ExUserDataSend(aIndex);

		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Life Added %d Credits " ,Count, CountExLife);
	}
}

void JewelsBank::excreateon(int aIndex, int Count)
{
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea))
	{
		if(!this->Enable) return;
		LPOBJ lpObj = &gObj[aIndex];
		if(lpObj->CreateonBank < Count)
		{
			MsgNormal(aIndex,"[JewelsBank] No %d Createon",Count);
			return;
		}
		if (Count == 10)
			{
				lpObj->CreateonBank -= Count;
				lpObj->ExCred += ExCreateonTeen;
				CountExCreateon = ExCreateonTeen;
			}
			else if (Count == 20)
			{
				lpObj->CreateonBank -= Count;
				lpObj->ExCred += ExCreateonTwenty;
				CountExCreateon = ExCreateonTwenty;
			}
			else if (Count == 30)
			{
				lpObj->CreateonBank -= Count;
				lpObj->ExCred += ExCreateonThirty;
				CountExCreateon = ExCreateonThirty;
			}
		else if (Count == 40)
		{
			lpObj->CreateonBank -= Count;
			lpObj->ExCred += ExCreateonForty;
			CountExCreateon = ExCreateonForty;
		}
		else if (Count == 50)
		{
			lpObj->CreateonBank -= Count;
			lpObj->ExCred += ExCreateonFifty;
			CountExCreateon = ExCreateonFifty;
		}
		else if (Count == 100)
		{
			lpObj->CreateonBank -= Count;
			lpObj->ExCred += ExCreateonHundred;
			CountExCreateon = ExCreateonHundred;
		}
		else{
				MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
				return;
			}

		ExUserDataSend(aIndex);

		MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Createon Added %d Credits " ,Count, CountExCreateon);
	}
}

void JewelsBank::exGuardian(int aIndex, int Count)
{
	if( !g_ExLicense.CheckUser(eExUB::Local3)  && 
		!g_ExLicense.CheckUser(eExUB::SILVER1) &&
		!g_ExLicense.CheckUser(eExUB::SILVER2) && 
		!g_ExLicense.CheckUser(eExUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->GuardianBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Guardian",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ExCred += this->ExGuardianTeen;
		CountJewels = this->ExGuardianTeen;
	}
	else if (Count == 20)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ExCred += this->ExGuardianTwenty;
		CountJewels = this->ExGuardianTwenty;
	}
	else if (Count == 30)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ExCred += this->ExGuardianThirty;
		CountJewels = this->ExGuardianThirty;
	}
	else if (Count == 40)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ExCred += this->ExGuardianForty;
		CountJewels = this->ExGuardianForty;
	}
	else if (Count == 50)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ExCred += this->ExGuardianFifty;
		CountJewels = this->ExGuardianFifty;
	}
	else if (Count == 100)
	{
		lpObj->GuardianBank -= Count;
		lpObj->ExCred += this->ExGuardianHundred;
		CountJewels = this->ExGuardianHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Guardian Added %d Credits " ,Count, CountJewels);
}

void JewelsBank::exHarmony(int aIndex, int Count)
{
	if( !g_ExLicense.CheckUser(eExUB::Local3)  && 
		!g_ExLicense.CheckUser(eExUB::SILVER1) &&
		!g_ExLicense.CheckUser(eExUB::SILVER2) && 
		!g_ExLicense.CheckUser(eExUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->HarmonyBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Harmony",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ExCred += this->ExHarmonyTeen;
		CountJewels = this->ExHarmonyTeen;
	}
	else if (Count == 20)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ExCred += this->ExHarmonyTwenty;
		CountJewels = this->ExHarmonyTwenty;
	}
	else if (Count == 30)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ExCred += this->ExHarmonyThirty;
		CountJewels = this->ExHarmonyThirty;
	}
	else if (Count == 40)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ExCred += this->ExHarmonyForty;
		CountJewels = this->ExHarmonyForty;
	}
	else if (Count == 50)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ExCred += this->ExHarmonyFifty;
		CountJewels = this->ExHarmonyFifty;
	}
	else if (Count == 100)
	{
		lpObj->HarmonyBank -= Count;
		lpObj->ExCred += this->ExHarmonyHundred;
		CountJewels = this->ExHarmonyHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of Harmony Added %d Credits " ,Count, CountJewels);
}

void JewelsBank::exLowStone(int aIndex, int Count)
{
	if( !g_ExLicense.CheckUser(eExUB::Local3)  && 
		!g_ExLicense.CheckUser(eExUB::SILVER1) &&
		!g_ExLicense.CheckUser(eExUB::SILVER2) && 
		!g_ExLicense.CheckUser(eExUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->LowStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d LowStone",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ExCred += this->ExLowStoneTeen;
		CountJewels = this->ExLowStoneTeen;
	}
	else if (Count == 20)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ExCred += this->ExLowStoneTwenty;
		CountJewels = this->ExLowStoneTwenty;
	}
	else if (Count == 30)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ExCred += this->ExLowStoneThirty;
		CountJewels = this->ExLowStoneThirty;
	}
	else if (Count == 40)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ExCred += this->ExLowStoneForty;
		CountJewels = this->ExLowStoneForty;
	}
	else if (Count == 50)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ExCred += this->ExLowStoneFifty;
		CountJewels = this->ExLowStoneFifty;
	}
	else if (Count == 100)
	{
		lpObj->LowStoneBank -= Count;
		lpObj->ExCred += this->ExLowStoneHundred;
		CountJewels = this->ExLowStoneHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of LowStone Added %d Credits " ,Count, CountJewels);
}

void JewelsBank::exHighStone(int aIndex, int Count)
{
	if( !g_ExLicense.CheckUser(eExUB::Local3)  && 
		!g_ExLicense.CheckUser(eExUB::SILVER1) &&
		!g_ExLicense.CheckUser(eExUB::SILVER2) && 
		!g_ExLicense.CheckUser(eExUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->HighStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d HighStone",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ExCred += this->ExHighStoneTeen;
		CountJewels = this->ExHighStoneTeen;
	}
	else if (Count == 20)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ExCred += this->ExHighStoneTwenty;
		CountJewels = this->ExHighStoneTwenty;
	}
	else if (Count == 30)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ExCred += this->ExHighStoneThirty;
		CountJewels = this->ExHighStoneThirty;
	}
	else if (Count == 40)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ExCred += this->ExHighStoneForty;
		CountJewels = this->ExHighStoneForty;
	}
	else if (Count == 50)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ExCred += this->ExHighStoneFifty;
		CountJewels = this->ExHighStoneFifty;
	}
	else if (Count == 100)
	{
		lpObj->HighStoneBank -= Count;
		lpObj->ExCred += this->ExHighStoneHundred;
		CountJewels = this->ExHighStoneHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of HighStone Added %d Credits " ,Count, CountJewels);
}

void JewelsBank::exGemStone(int aIndex, int Count)
{
	if( !g_ExLicense.CheckUser(eExUB::Local3)  && 
		!g_ExLicense.CheckUser(eExUB::SILVER1) &&
		!g_ExLicense.CheckUser(eExUB::SILVER2) && 
		!g_ExLicense.CheckUser(eExUB::drynea) )
	{
		return;
	}

	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->GemStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d GemStone",Count);
		return;
	}

	int CountJewels = 0;

	if (Count == 10)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ExCred += this->ExGemStoneTeen;
		CountJewels = this->ExGemStoneTeen;
	}
	else if (Count == 20)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ExCred += this->ExGemStoneTwenty;
		CountJewels = this->ExGemStoneTwenty;
	}
	else if (Count == 30)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ExCred += this->ExGemStoneThirty;
		CountJewels = this->ExGemStoneThirty;
	}
	else if (Count == 40)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ExCred += this->ExGemStoneForty;
		CountJewels = this->ExGemStoneForty;
	}
	else if (Count == 50)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ExCred += this->ExGemStoneFifty;
		CountJewels = this->ExGemStoneFifty;
	}
	else if (Count == 100)
	{
		lpObj->GemStoneBank -= Count;
		lpObj->ExCred += this->ExGemStoneHundred;
		CountJewels = this->ExGemStoneHundred;
	}
	else
	{
		MsgNormal(aIndex,"[JewelsBank] Exchange Only 10 20 30 40 50 100");
		return;
	}

	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Exchange %d Jewel of GemStone Added %d Credits " ,Count, CountJewels);
}


#endif
#endif

void JewelsBank::sendzen(int aIndex, int Count)
{
	LPOBJ lpUser = &gObj[aIndex];
	unsigned int M = 1000000 * Count;
	if(M > lpUser->Money) return;
	lpUser->Money -= M;
	lpUser->Zen += Count;
	GCMoneySend(aIndex,lpUser->Money);
	ExUserDataSend(aIndex);
}

void JewelsBank::recvzen(int aIndex, int Count)
{
	LPOBJ lpUser = &gObj[aIndex];
	int M = 1000000;
	unsigned long long totalzen = M + lpUser->Money;
	if(totalzen > MAX_ZEN) return;
	if(Count > lpUser->Zen) return;
	lpUser->Money += M;
	lpUser->Zen -= Count;
	GCMoneySend(aIndex,lpUser->Money);
	ExUserDataSend(aIndex);
}

void JewelsBank::sendGuardianBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,31),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Guardian",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,31),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->GuardianBank += Count;
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d Guardian",Count);
}

void JewelsBank::sendHarmonyBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,42),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d Harmony",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,42),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->HarmonyBank += Count;
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d Harmony",Count);
}

void JewelsBank::sendLowStoneBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,43),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d LowStone",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,43),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->LowStoneBank += Count;
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d LowStone",Count);
}

void JewelsBank::sendHighStoneBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,44),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d HighStone",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,44),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->HighStoneBank += Count;
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d HighStone",Count);
}

void JewelsBank::sendGemStoneBank(int aIndex, int Count)
{
	if(gObjGetItemCountInInventory(aIndex,ITEMGET(14,41),0) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Need %d GemStoneBank",Count);
		return;
	}
	gObjDeleteItemsCount(aIndex,ITEMGET(14,41),0,Count);
	LPOBJ lpObj = &gObj[aIndex];
	lpObj->GemStoneBank += Count;
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Send %d GemStoneBank",Count);
}

 // -> Recv

void JewelsBank::recvGuardianBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->GuardianBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Guardian",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->GuardianBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,31),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d Guardian",Count);
}

void JewelsBank::recvHarmonyBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->HarmonyBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d Harmony",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->HarmonyBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,42),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d Harmony",Count);
}

void JewelsBank::recvLowStoneBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LowStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d LowStone",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->LowStoneBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,43),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d LowStone",Count);
}

void JewelsBank::recvHighStoneBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->HighStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d HighStone",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->HighStoneBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,44),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d HighStone",Count);
}

void JewelsBank::recvGemStoneBank(int aIndex, int Count)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->GemStoneBank < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] No %d GemStone",Count);
		return;
	}
	if(ExCheckInventoryEmptySpace(aIndex) < Count)
	{
		MsgNormal(aIndex,"[JewelsBank] Inventory %d",Count);
		return;
	}
	lpObj->GemStoneBank -= Count;
	for(int i=0;i<Count;i++)
	{
		ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(14,41),0,0,0,0,0,aIndex,0,0);
	}
	ExUserDataSend(aIndex);

	MsgNormal(aIndex,"[JewelsBank] Recv %d GemStone",Count);
}

void JewelsBank::Packet(int aIndex, PMSG_JEWELBANK* lpMsg)
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	switch(lpMsg->Result)
	{
		case 0:		this->sendzen(aIndex, 1);				break;
		case 1:		this->sendchaosbank(aIndex, 1);			break;
		case 2:		this->sendblessbank(aIndex, 1);			break;
		case 3:		this->sendsoulbank(aIndex, 1);			break;
		case 4:		this->sendlifebank(aIndex, 1);			break;
		case 5:		this->sendcreateonbank(aIndex, 1);		break;
		case 6:		this->sendGuardianBank(aIndex, 1);		break;
		case 7:		this->sendHarmonyBank(aIndex, 1);		break;
		case 8:		this->sendLowStoneBank(aIndex, 1);		break;
		case 9:		this->sendHighStoneBank(aIndex, 1);		break;
		case 10:	this->sendGemStoneBank(aIndex, 1);		break;

		case 11:	this->recvzen(aIndex, 1);				break;
		case 12:	this->recvchaosbank(aIndex, 1);			break;
		case 13:	this->recvblessbank(aIndex, 1);			break;
		case 14:	this->recvsoulbank(aIndex, 1);			break;
		case 15:	this->recvlifebank(aIndex, 1);			break;
		case 16:	this->recvcreateonbank(aIndex, 1);		break;
		case 17:	this->recvGuardianBank(aIndex, 1);		break;
		case 18:	this->recvHarmonyBank(aIndex, 1);		break;
		case 19:	this->recvLowStoneBank(aIndex, 1);		break;
		case 20:	this->recvHighStoneBank(aIndex, 1);		break;
		case 21:	this->recvGemStoneBank(aIndex, 1);		break;
	}
}