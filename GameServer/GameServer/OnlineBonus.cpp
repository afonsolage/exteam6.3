#include "stdafx.h"
#include "user.h"
#include "OnlineBonus.h"
#include "DSProtocol.h"
#include "Message.h"
#include "ExUser.h"
#include "ExFunction.h"
#include "ExText.h"
#include "VIPSystem.h"

OnlineBonus gOnlineBonus;

void OnlineBonus::Load()
{
	//CheckFile(ONLINEBONUS_DIR);

	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,ONLINEBONUS_DIR); 

	this->WCoinCActive = GetPrivateProfileInt("ExTeam","WCoinCActive",0,ONLINEBONUS_DIR);
	this->WCoinCTime = GetPrivateProfileInt("ExTeam","WCoinCTime",0,ONLINEBONUS_DIR) * 60;
	this->WCoinCBonus = GetPrivateProfileInt("ExTeam","WCoinCBonus",0,ONLINEBONUS_DIR);

	this->WCoinPActive = GetPrivateProfileInt("ExTeam","WCoinPActive",0,ONLINEBONUS_DIR);
	this->WCoinPTime = GetPrivateProfileInt("ExTeam","WCoinPTime",0,ONLINEBONUS_DIR) * 60;
	this->WCoinPBonus = GetPrivateProfileInt("ExTeam","WCoinPBonus",0,ONLINEBONUS_DIR);

	this->GoblinActive = GetPrivateProfileInt("ExTeam","GoblinActive",0,ONLINEBONUS_DIR);
	this->GoblinTime = GetPrivateProfileInt("ExTeam","GoblinTime",0,ONLINEBONUS_DIR) * 60;
	this->GoblinBonus = GetPrivateProfileInt("ExTeam","GoblinBonus",0,ONLINEBONUS_DIR);
	this->GoblinBonusVIP = GetPrivateProfileInt("ExTeam","GoblinBOnusVIP",0,ONLINEBONUS_DIR);

	this->ExCredActive = GetPrivateProfileInt("ExTeam","ExCredActive",0,ONLINEBONUS_DIR);
	this->ExCredTime = GetPrivateProfileInt("ExTeam","ExCredTime",0,ONLINEBONUS_DIR) * 60;
	this->ExCredBonus = GetPrivateProfileInt("ExTeam","ExCredBonus",0,ONLINEBONUS_DIR);
}

void OnlineBonus::TickTime(int aIndex)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->OffExp > 0 || lpObj->OffTrade > 0)
	{
		return;
	}

	if(lpObj->m_OfflineMode)
	{
		return;
	}

	if(this->WCoinCActive)
	{
		lpObj->WCoinCTick++;
		if(lpObj->WCoinCTick >= this->WCoinCTime)
		{
			lpObj->WCoinCTick = 0;
			lpObj->GameShop.WCoinC += this->WCoinCBonus;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex, g_ExText.GetText(88), this->WCoinCBonus);
		}
	}

	if(this->WCoinPActive)
	{
		lpObj->WCoinPTick++;
		if(lpObj->WCoinPTick >= this->WCoinPTime)
		{
			lpObj->WCoinPTick = 0;
			lpObj->GameShop.WCoinP += this->WCoinPBonus;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex, g_ExText.GetText(89), this->WCoinPBonus);
		}
	}

	if(this->GoblinActive)
	{
		lpObj->GoblinTick++;
		if(lpObj->GoblinTick == this->GoblinTime)
		{
			int bonus = (g_VIPSystem.VipTimeLeft(lpObj->PremiumTime) > 0) ? this->GoblinBonusVIP : this->GoblinBonus;

			lpObj->GoblinTick = 0;
			lpObj->GameShop.GoblinPoint += bonus;
			gGameShop.GDSaveUserInfo(aIndex);
			MessageChat(aIndex, g_ExText.GetText(90), bonus);
		}
	}

	if(this->ExCredActive)
	{
		lpObj->ExCredTick++;
		if(lpObj->ExCredTick >= this->ExCredTime)
		{
			lpObj->ExCredTick = 0;
			lpObj->ExCred += this->ExCredBonus;
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ExUserDataSend(aIndex);
			MessageChat(aIndex, g_ExText.GetText(91),this->ExCredBonus);
		}
	}
}