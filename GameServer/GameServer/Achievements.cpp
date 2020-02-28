#include "StdAfx.h"
#include "Achievements.h"
#include "GameMain.h"
#include "DBSockMng.h"
#include "KalimaGate.h"
#include "TUnion.h"
#include "ExUser.h"
#include "ObjCalCharacter.h"
#include "ExLicense.h"
#include "Message.h"
#include "logproc.h"

#if(SYSTEM_ACHIEVEMENTS)

CAchievements g_Achievements;

CAchievements::CAchievements()
{
	this->Init();
}

CAchievements::~CAchievements()
{
}

void CAchievements::Init()
{
	this->bEnable = false;
	memset(&this->m_config, 0, sizeof(this->m_config));
	memset(&this->m_reward, 0, sizeof(this->m_reward));
}

void CAchievements::Load()
{
	if(!g_ExLicense.user.bAchievements)
	{
		return;
	}

	this->Init();
	this->Read(gDirPath.GetNewPath("ExData\\Achievements.ini"));

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];
		if(lpUser->Connected == PLAYER_PLAYING && lpUser->Type == OBJ_USER)
		{
			this->GCSettingsData(aIndex);
		}
	}
}

void CAchievements::Read(char* filename)
{
	this->bEnable = GetPrivateProfileInt("Common", "Enable", 0, filename);
	//-> mission config read
	this->m_config.i1_MonsterKill = GetPrivateProfileInt("Mission", "MonsterKill", 100, filename);
	this->m_config.i2_GoldenKill = GetPrivateProfileInt("Mission", "GoldenKill", 100, filename);
	this->m_config.i3_KalimaMonserKill = GetPrivateProfileInt("Mission", "KalimaMonserKill", 100, filename);
	this->m_config.i4_WhiteWizardKill = GetPrivateProfileInt("Mission", "WhiteWizardKill", 100, filename);
	this->m_config.i5_PlayerKill = GetPrivateProfileInt("Mission", "PlayerKill", 100, filename);
	this->m_config.i6_RedDragonKill = GetPrivateProfileInt("Mission", "RedDragonKill", 100, filename);
	this->m_config.i7_OrcKill = GetPrivateProfileInt("Mission", "OrcKill", 100, filename);
	this->m_config.i8_KillGateBC = GetPrivateProfileInt("Mission", "KillGateBC", 100, filename);
	this->m_config.i9_TakePartInCC = GetPrivateProfileInt("Mission", "TakePartInCC", 100, filename);
	this->m_config.i10_WinningTheCC = GetPrivateProfileInt("Mission", "WinningTheCC", 100, filename);
	this->m_config.i11_OnlineTime = GetPrivateProfileInt("Mission", "OnlineTime", 100, filename);
	this->m_config.i12_PickUpJewels = GetPrivateProfileInt("Mission", "PickUpJewels", 100, filename);
	this->m_config.i13_UsedJewels = GetPrivateProfileInt("Mission", "UsedJewels", 100, filename);
	this->m_config.i14_SuccessChaosMix = GetPrivateProfileInt("Mission", "SuccessChaosMix", 100, filename);
	this->m_config.i15_FailedChaosMix = GetPrivateProfileInt("Mission", "FailedChaosMix", 100, filename);
	this->m_config.i16_PickUpZen = GetPrivateProfileInt("Mission", "PickUpZen", 100, filename);
	this->m_config.i17_PickUpExellent = GetPrivateProfileInt("Mission", "PickUpExellent", 100, filename);
	this->m_config.i18_PickUpAncent = GetPrivateProfileInt("Mission", "PickUpAncent", 100, filename);
	this->m_config.i19_DuelWin = GetPrivateProfileInt("Mission", "DuelWin", 100, filename);
	this->m_config.i20_LevelUp = GetPrivateProfileInt("Mission", "LevelUp", 100, filename);
	this->m_config.i21_ResetUp = GetPrivateProfileInt("Mission", "ResetUp", 100, filename);
	this->m_config.i22_KanturuBossKill = GetPrivateProfileInt("Mission", "KanturuBossKill", 100, filename);
	this->m_config.i23_Monster100LvlKill = GetPrivateProfileInt("Mission", "Monster100LvlKill", 100, filename);
	this->m_config.i24_MootopVote = GetPrivateProfileInt("Mission", "MootopVote", 100, filename);
	this->m_config.i25_PhonomanKill = GetPrivateProfileInt("Mission", "PhonomanKill", 100, filename);
	this->m_config.i26_CryWolfEventMonster = GetPrivateProfileInt("Mission", "CryWolfEventMonster", 100, filename);
	this->m_config.i27_HellMainKill = GetPrivateProfileInt("Mission", "HellMainKill", 100, filename);
	this->m_config.i28_KillInSelf_Defense = GetPrivateProfileInt("Mission", "KillInSelf_Defense", 100, filename);
	this->m_config.i29_SelupanKill = GetPrivateProfileInt("Mission", "SelupanKill", 100, filename);
	this->m_config.i30_KundunKill = GetPrivateProfileInt("Mission", "KundunKill", 100, filename);
	this->m_config.i31_KillStatueBC = GetPrivateProfileInt("Mission", "KillStatueBC", 100, filename);
	this->m_config.i32_CompleteBC = GetPrivateProfileInt("Mission", "CompleteBC", 100, filename);
	this->m_config.i33_GrandResetUp = GetPrivateProfileInt("Mission", "GrandResetUp", 100, filename);
	this->m_config.i34_BlueRabbitKiller = GetPrivateProfileInt("Mission", "BlueRabbitKiller", 100, filename);
	this->m_config.i35_HappyPouchesKiller = GetPrivateProfileInt("Mission", "HappyPouchesKiller", 100, filename);
	this->m_config.i36_PheonixKill = GetPrivateProfileInt("Mission", "PheonixKill", 100, filename);
	this->m_config.i37_KanturuMonsterKill = GetPrivateProfileInt("Mission", "KanturuMonsterKill", 100, filename);
	this->m_config.i38_MovePlayerFromSwitch = GetPrivateProfileInt("Mission", "MovePlayerFromSwitch", 100, filename);
	this->m_config.i39_WithstandSwitch10min = GetPrivateProfileInt("Mission", "WithstandSwitch10min", 100, filename);
	this->m_config.i40_MovePlayerFromCrown = GetPrivateProfileInt("Mission", "MovePlayerFromCrown", 100, filename);
	this->m_config.i41_WinSiege = GetPrivateProfileInt("Mission", "WinSiege", 100, filename);
	this->m_config.i42_KillCastleSiegeNPC = GetPrivateProfileInt("Mission", "KillCastleSiegeNPC", 100, filename);
	this->m_config.i43_KillPlayerCastleSiege = GetPrivateProfileInt("Mission", "KillPlayerCastleSiege", 100, filename);
	this->m_config.i44_KillErohim = GetPrivateProfileInt("Mission", "KillErohim", 100, filename);
	this->m_config.i45_BuyDonateShopItem = GetPrivateProfileInt("Mission", "BuyDonateShopItem", 100, filename);
	this->m_config.i46_GuildWarWin = GetPrivateProfileInt("Mission", "GuildWarWin", 100, filename);
	this->m_config.i47_PartyNoobLevelUp = GetPrivateProfileInt("Mission", "PartyNoobLevelUp", 100, filename);
	this->m_config.i48_PickUpRena = GetPrivateProfileInt("Mission", "PickUpSing", 100, filename);
	this->m_config.i49_PickUpLuckyCoins = GetPrivateProfileInt("Mission", "PickUpLuckyCoins", 100, filename);
	this->m_config.i50_OfflineAttackTime = GetPrivateProfileInt("Mission", "OfflineAttackTime", 100, filename);
	//-> reward confg read
	this->m_reward.i1_MonsterKill = GetPrivateProfileInt("Reward", "MonsterKill", 100, filename);
	this->m_reward.i2_GoldenKill = GetPrivateProfileInt("Reward", "GoldenKill", 100, filename);
	this->m_reward.i3_KalimaMonserKill = GetPrivateProfileInt("Reward", "KalimaMonserKill", 100, filename);
	this->m_reward.i4_WhiteWizardKill = GetPrivateProfileInt("Reward", "WhiteWizardKill", 100, filename);
	this->m_reward.i5_PlayerKill = GetPrivateProfileInt("Reward", "PlayerKill", 100, filename);
	this->m_reward.i6_RedDragonKill = GetPrivateProfileInt("Reward", "RedDragonKill", 100, filename);
	this->m_reward.i7_OrcKill = GetPrivateProfileInt("Reward", "OrcKill", 100, filename);
	this->m_reward.i8_KillGateBC = GetPrivateProfileInt("Reward", "KillGateBC", 100, filename);
	this->m_reward.i9_TakePartInCC = GetPrivateProfileInt("Reward", "TakePartInCC", 100, filename);
	this->m_reward.i10_WinningTheCC = GetPrivateProfileInt("Reward", "WinningTheCC", 100, filename);
	this->m_reward.i11_OnlineTime = GetPrivateProfileInt("Reward", "OnlineTime", 100, filename);
	this->m_reward.i12_PickUpJewels = GetPrivateProfileInt("Reward", "PickUpJewels", 100, filename);
	this->m_reward.i13_UsedJewels = GetPrivateProfileInt("Reward", "UsedJewels", 100, filename);
	this->m_reward.i14_SuccessChaosMix = GetPrivateProfileInt("Reward", "SuccessChaosMix", 100, filename);
	this->m_reward.i15_FailedChaosMix = GetPrivateProfileInt("Reward", "FailedChaosMix", 100, filename);
	this->m_reward.i16_PickUpZen = GetPrivateProfileInt("Reward", "PickUpZen", 100, filename);
	this->m_reward.i17_PickUpExellent = GetPrivateProfileInt("Reward", "PickUpExellent", 100, filename);
	this->m_reward.i18_PickUpAncent = GetPrivateProfileInt("Reward", "PickUpAncent", 100, filename);
	this->m_reward.i19_DuelWin = GetPrivateProfileInt("Reward", "DuelWin", 100, filename);
	this->m_reward.i20_LevelUp = GetPrivateProfileInt("Reward", "LevelUp", 100, filename);
	this->m_reward.i21_ResetUp = GetPrivateProfileInt("Reward", "ResetUp", 100, filename);
	this->m_reward.i22_KanturuBossKill = GetPrivateProfileInt("Reward", "KanturuBossKill", 100, filename);
	this->m_reward.i23_Monster100LvlKill = GetPrivateProfileInt("Reward", "Monster100LvlKill", 100, filename);
	this->m_reward.i24_MootopVote = GetPrivateProfileInt("Reward", "MootopVote", 100, filename);
	this->m_reward.i25_PhonomanKill = GetPrivateProfileInt("Reward", "PhonomanKill", 100, filename);
	this->m_reward.i26_CryWolfEventMonster = GetPrivateProfileInt("Reward", "CryWolfEventMonster", 100, filename);
	this->m_reward.i27_HellMainKill = GetPrivateProfileInt("Reward", "HellMainKill", 100, filename);
	this->m_reward.i28_KillInSelf_Defense = GetPrivateProfileInt("Reward", "KillInSelf_Defense", 100, filename);
	this->m_reward.i29_SelupanKill = GetPrivateProfileInt("Reward", "SelupanKill", 100, filename);
	this->m_reward.i30_KundunKill = GetPrivateProfileInt("Reward", "KundunKill", 100, filename);
	this->m_reward.i31_KillStatueBC = GetPrivateProfileInt("Reward", "KillStatueBC", 100, filename);
	this->m_reward.i32_CompleteBC = GetPrivateProfileInt("Reward", "CompleteBC", 100, filename);
	this->m_reward.i33_GrandResetUp = GetPrivateProfileInt("Reward", "GrandResetUp", 100, filename);
	this->m_reward.i34_BlueRabbitKiller = GetPrivateProfileInt("Reward", "BlueRabbitKiller", 100, filename);
	this->m_reward.i35_HappyPouchesKiller = GetPrivateProfileInt("Reward", "HappyPouchesKiller", 100, filename);
	this->m_reward.i36_PheonixKill = GetPrivateProfileInt("Reward", "PheonixKill", 100, filename);
	this->m_reward.i37_KanturuMonsterKill = GetPrivateProfileInt("Reward", "KanturuMonsterKill", 100, filename);
	this->m_reward.i38_MovePlayerFromSwitch = GetPrivateProfileInt("Reward", "MovePlayerFromSwitch", 100, filename);
	this->m_reward.i39_WithstandSwitch10min = GetPrivateProfileInt("Reward", "WithstandSwitch10min", 100, filename);
	this->m_reward.i40_MovePlayerFromCrown = GetPrivateProfileInt("Reward", "MovePlayerFromCrown", 100, filename);
	this->m_reward.i41_WinSiege = GetPrivateProfileInt("Reward", "WinSiege", 100, filename);
	this->m_reward.i42_KillCastleSiegeNPC = GetPrivateProfileInt("Reward", "KillCastleSiegeNPC", 100, filename);
	this->m_reward.i43_KillPlayerCastleSiege = GetPrivateProfileInt("Reward", "KillPlayerCastleSiege", 100, filename);
	this->m_reward.i44_KillErohim = GetPrivateProfileInt("Reward", "KillErohim", 100, filename);
	this->m_reward.i45_BuyDonateShopItem = GetPrivateProfileInt("Reward", "BuyDonateShopItem", 100, filename);
	this->m_reward.i46_GuildWarWin = GetPrivateProfileInt("Reward", "GuildWarWin", 100, filename);
	this->m_reward.i47_PartyNoobLevelUp = GetPrivateProfileInt("Reward", "PartyNoobLevelUp", 100, filename);
	this->m_reward.i48_PickUpRena = GetPrivateProfileInt("Reward", "PickUpRena", 100, filename);
	this->m_reward.i49_PickUpLuckyCoins = GetPrivateProfileInt("Reward", "PickUpLuckyCoins", 100, filename);
	this->m_reward.i50_OfflineAttackTime = GetPrivateProfileInt("Reward", "OfflineAttackTime", 100, filename);
	//power cfg
	this->iDamageMax = GetPrivateProfileInt("Power", "DamageMax", 100, filename);
	this->iDefenceMax = GetPrivateProfileInt("Power", "DefenceMax", 100, filename);
	this->iLifeMax = GetPrivateProfileInt("Power", "LifeMax", 100, filename);
	this->iExellentDamageMax = GetPrivateProfileInt("Power", "ExellentDamageMax", 100, filename);
	this->iCriticalDamageMax = GetPrivateProfileInt("Power", "CriticalDamageMax", 100, filename);
	//power div
	this->m_DivDamage = GetPrivateProfileInt("Power", "DivDamage", 60, filename);
	this->m_DivDefence = GetPrivateProfileInt("Power", "DivDefence", 40, filename);
	this->m_DivLife = GetPrivateProfileInt("Power", "DivLife", 200, filename);
	this->m_DivExellentPercent = GetPrivateProfileInt("Power", "DivExellentPercent", 20, filename);
	this->m_DivCriticalPercent = GetPrivateProfileInt("Power", "DivCriticalPercent", 20, filename);
}

void CAchievements::GDPlayerLoad(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	PMSG_GDREQ_ACH_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0D, sizeof(pMsg));
	pMsg.aIndex = aIndex;
	pMsg.szName[10] = 0;
	memcpy(pMsg.szName, lpUser->Name, sizeof(pMsg.szName)-1);
	cDBSMng.Send((char*)&pMsg, sizeof(pMsg));
}

void CAchievements::DGPlayerLoad(PMSG_DGANS_ACH_LOAD* aRecv)
{
	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	memcpy(&lpUser->ach.mission, &aRecv->usr, sizeof(aRecv->usr));

	lpUser->ach.bLoaded = true;

	this->GCPlayerData(aIndex, false);

	gObjCalCharacter(aIndex);
}

void CAchievements::GDPlayerSave(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}


	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	PMSG_GDREQ_ACH_SAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEA, 0x0E, sizeof(pMsg));
	pMsg.szName[10] = 0;
	memcpy(pMsg.szName, lpUser->Name, sizeof(pMsg.szName)-1);
	memcpy(&pMsg.usr, &lpUser->ach.mission, sizeof(pMsg.usr));
	cDBSMng.Send((char*)&pMsg, sizeof(pMsg));
}

void CAchievements::GCSettingsData(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	PMSG_GC_ACH_SETTINGS_DATA pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x90, sizeof(pMsg));
	memcpy(&pMsg.cfg, &this->m_config, sizeof(this->m_config));

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CAchievements::GCPlayerData(int aIndex, bool bWin)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_GC_ACH_PLAYER_DATA pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x91, sizeof(pMsg));
	pMsg.bWinOpen = bWin;
	memcpy(&pMsg.usr, &lpUser->ach.mission, sizeof(pMsg.usr));
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CAchievements::CGWindowOpen(PMSG_CG_ACH_WINOPEN* aRecv, int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	this->GCPlayerData(aIndex, true);
}

void CAchievements::PlayerReward(int aIndex,int mission_need, int mission, int ireward)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(mission >= mission_need)
	{
		char szReward[64];
#if(GAMESERVER_ACHIVEMENTS==EXGAME_SERVER)
		if(ireward > 0)
		{
			lpUser->Bonus += ireward;
			g_ExUser.UpdateCharEx(aIndex);
			sprintf(szReward, "[Achievements]: +%d Bonus", ireward);
			MessageSendUser(aIndex, 6, "", szReward);
		}
#endif
#if(GAMESERVER_ACHIVEMENTS==EXTEAM_SERVER)
		if(ireward > 0)
		{
			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal) || 
				g_ExLicense.CheckUser(eExUB::AlterMU) || g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2) ||
				g_ExLicense.CheckUser(eExUB::RevoMU) || g_ExLicense.CheckUser(eExUB::GloryMU) || g_ExLicense.CheckUser(eExUB::mu4you) || g_ExLicense.CheckUser(eExUB::Escalate) ||
				g_ExLicense.CheckUser(eExUB::eternalmu) || g_ExLicense.CheckUser(eExUB::NSGames))
			{
				lpUser->GameShop.WCoinC += ireward;
				gGameShop.GDSaveUserInfo(aIndex);
				sprintf(szReward, "[Achievements]: +%d WCoin", ireward);
				MessageSendEx(aIndex, 6, "", szReward);
			}
			else if(g_ExLicense.CheckUser(eExUB::EpicMU))
			{
				lpUser->GameShop.GoblinPoint += ireward;
				gGameShop.GDSaveUserInfo(aIndex);
				sprintf(szReward, "[Achievements]: +%d Goblin", ireward);
				MessageSendEx(aIndex, 6, "", szReward);
			}
			else
			{
				lpUser->ExCred += ireward;
				sprintf(szReward, "[Achievements]: +%d Credits", ireward);
				MessageSendEx(aIndex, 6, "", szReward);
			}

			ExUserDataSend(aIndex);
		}
#endif
	}
}

void CAchievements::MonsterKill(int aIndex, int aMonsterIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex) || !gObjIsConnected(aMonsterIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[aMonsterIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i1_MonsterKill
	if(this->m_config.i1_MonsterKill > lpUser->ach.mission.i1_MonsterKill)
	{
		lpUser->ach.mission.i1_MonsterKill++;
		this->PlayerReward(aIndex, this->m_config.i1_MonsterKill, lpUser->ach.mission.i1_MonsterKill, this->m_reward.i1_MonsterKill);

	}
	//i2_GoldenKill
	if(this->m_config.i2_GoldenKill > lpUser->ach.mission.i2_GoldenKill)
	{
		if( lpMonster->Class == 78  || lpMonster->Class == 53  || lpMonster->Class == 79  || lpMonster->Class == 80  || lpMonster->Class == 82  || 
			lpMonster->Class == 502 || lpMonster->Class == 493 || lpMonster->Class == 494 || lpMonster->Class == 495 || lpMonster->Class == 496 || 
			lpMonster->Class == 497 || lpMonster->Class == 498 || lpMonster->Class == 499 || lpMonster->Class == 500 || lpMonster->Class == 501 ||
			lpMonster->Class == 42  ||	//??
			lpMonster->Class == 43	||	//GoldenBudgeDragon
			lpMonster->Class == 44	||	//Dragon
			lpMonster->Class == 54	||	//GoldenBudgeDragon
			lpMonster->Class == 81		//GoldenVepar
			)	
		{
			lpUser->ach.mission.i2_GoldenKill++;
			this->PlayerReward(aIndex, this->m_config.i2_GoldenKill, lpUser->ach.mission.i2_GoldenKill, this->m_reward.i2_GoldenKill);
		}
	}
	//i3_KalimaMonserKill
	if(this->m_config.i3_KalimaMonserKill > lpUser->ach.mission.i3_KalimaMonserKill)
	{
		if(KALIMA_MAP_RANGE(lpUser->MapNumber))
		{
			lpUser->ach.mission.i3_KalimaMonserKill++;
			this->PlayerReward(aIndex, this->m_config.i3_KalimaMonserKill, lpUser->ach.mission.i3_KalimaMonserKill, this->m_reward.i3_KalimaMonserKill);
		}
	}
	//i4_WhiteWizardKill
	if(this->m_config.i4_WhiteWizardKill > lpUser->ach.mission.i4_WhiteWizardKill)
	{
		if(lpMonster->Class == 135)
		{
			lpUser->ach.mission.i4_WhiteWizardKill++;
			this->PlayerReward(aIndex, this->m_config.i4_WhiteWizardKill, lpUser->ach.mission.i4_WhiteWizardKill, this->m_reward.i4_WhiteWizardKill);
		}
	}
	//i6_RedDragonKill
	if(this->m_config.i6_RedDragonKill > lpUser->ach.mission.i6_RedDragonKill)
	{
		if(lpMonster->Class == 42)
		{
			lpUser->ach.mission.i6_RedDragonKill++;
			this->PlayerReward(aIndex, this->m_config.i6_RedDragonKill, lpUser->ach.mission.i6_RedDragonKill, this->m_reward.i6_RedDragonKill);
		}
	}
	//i7_OrcKill
	if(this->m_config.i7_OrcKill > lpUser->ach.mission.i7_OrcKill)
	{
		if(lpMonster->Class == 136 || lpMonster->Class == 137)
		{
			lpUser->ach.mission.i7_OrcKill++;
			this->PlayerReward(aIndex, this->m_config.i7_OrcKill, lpUser->ach.mission.i7_OrcKill, this->m_reward.i7_OrcKill);
		}
	}
	//i8_KillGateBC
	if(this->m_config.i8_KillGateBC > lpUser->ach.mission.i8_KillGateBC)
	{
		if(lpMonster->Class == 131)
		{
			lpUser->ach.mission.i8_KillGateBC++;
			this->PlayerReward(aIndex, this->m_config.i8_KillGateBC, lpUser->ach.mission.i8_KillGateBC, this->m_reward.i8_KillGateBC);
		}
	}
	//i22_KanturuBossKill
	if(this->m_config.i22_KanturuBossKill > lpUser->ach.mission.i22_KanturuBossKill)
	{
		if(lpMonster->Class == 361 || lpMonster->Class == 362 || lpMonster->Class == 363)
		{
			lpUser->ach.mission.i22_KanturuBossKill++;
			this->PlayerReward(aIndex, this->m_config.i22_KanturuBossKill, lpUser->ach.mission.i22_KanturuBossKill, this->m_reward.i22_KanturuBossKill);
		}
	}
	//i23_Monster100LvlKill
	if(this->m_config.i23_Monster100LvlKill > lpUser->ach.mission.i23_Monster100LvlKill)
	{
		if(lpMonster->Level >= 100)
		{
			lpUser->ach.mission.i23_Monster100LvlKill++;
			this->PlayerReward(aIndex, this->m_config.i23_Monster100LvlKill, lpUser->ach.mission.i23_Monster100LvlKill, this->m_reward.i23_Monster100LvlKill);
		}
	}
	//i26_CryWolfEventMonster
	if(this->m_config.i26_CryWolfEventMonster > lpUser->ach.mission.i26_CryWolfEventMonster)
	{
		if(lpMonster->Class == 349 || lpMonster->Class == 340)
		{
			lpUser->ach.mission.i26_CryWolfEventMonster++;
			this->PlayerReward(aIndex, this->m_config.i26_CryWolfEventMonster, lpUser->ach.mission.i26_CryWolfEventMonster, this->m_reward.i26_CryWolfEventMonster);
		}
	}
	//i27_HellMainKill
	if(this->m_config.i27_HellMainKill > lpUser->ach.mission.i27_HellMainKill)
	{
		if(lpMonster->Class == 309)
		{
			lpUser->ach.mission.i27_HellMainKill++;
			this->PlayerReward(aIndex, this->m_config.i27_HellMainKill, lpUser->ach.mission.i27_HellMainKill, this->m_reward.i27_HellMainKill);
		}
	}
	//i29_SelupanKill
	if(this->m_config.i29_SelupanKill > lpUser->ach.mission.i29_SelupanKill)
	{
		if(lpMonster->Class == 459)
		{
			lpUser->ach.mission.i29_SelupanKill++;
			this->PlayerReward(aIndex, this->m_config.i29_SelupanKill, lpUser->ach.mission.i29_SelupanKill, this->m_reward.i29_SelupanKill);
		}
	}
	//i30_KundunKill
	if(this->m_config.i30_KundunKill > lpUser->ach.mission.i30_KundunKill)
	{
		if(lpMonster->Class == 275)
		{
			lpUser->ach.mission.i30_KundunKill++;
			this->PlayerReward(aIndex, this->m_config.i30_KundunKill, lpUser->ach.mission.i30_KundunKill, this->m_reward.i30_KundunKill);
		}
	}
	//i31_KillStatueBC
	if(this->m_config.i31_KillStatueBC > lpUser->ach.mission.i31_KillStatueBC)
	{
		if(lpMonster->Class == 131)
		{
			lpUser->ach.mission.i31_KillStatueBC++;
			this->PlayerReward(aIndex, this->m_config.i31_KillStatueBC, lpUser->ach.mission.i31_KillStatueBC, this->m_reward.i31_KillStatueBC);
		}
	}
	//i34_BlueRabbitKiller
	if(this->m_config.i34_BlueRabbitKiller > lpUser->ach.mission.i34_BlueRabbitKiller)
	{
		if(lpMonster->Class == 413)
		{
			lpUser->ach.mission.i34_BlueRabbitKiller++;
			this->PlayerReward(aIndex, this->m_config.i34_BlueRabbitKiller, lpUser->ach.mission.i34_BlueRabbitKiller, this->m_reward.i34_BlueRabbitKiller);
		}
	}
	//i35_HappyPouchesKiller
	if(this->m_config.i35_HappyPouchesKiller > lpUser->ach.mission.i35_HappyPouchesKiller)
	{
		if(lpMonster->Class == 463)
		{
			lpUser->ach.mission.i35_HappyPouchesKiller++;
			this->PlayerReward(aIndex, this->m_config.i35_HappyPouchesKiller, lpUser->ach.mission.i35_HappyPouchesKiller, this->m_reward.i35_HappyPouchesKiller);
		}
	}
	//i36_PheonixKill
	if(this->m_config.i36_PheonixKill > lpUser->ach.mission.i36_PheonixKill)
	{
		if(lpMonster->Class == 77)
		{
			lpUser->ach.mission.i36_PheonixKill++;
			this->PlayerReward(aIndex, this->m_config.i36_PheonixKill, lpUser->ach.mission.i36_PheonixKill, this->m_reward.i36_PheonixKill);
		}
	}
	//i37_KanturuMonsterKill
	if(this->m_config.i37_KanturuMonsterKill > lpUser->ach.mission.i37_KanturuMonsterKill)
	{
		if(lpMonster->MapNumber == MAP_INDEX_KANTURU_BOSS)
		{
			lpUser->ach.mission.i37_KanturuMonsterKill++;
			this->PlayerReward(aIndex, this->m_config.i37_KanturuMonsterKill, lpUser->ach.mission.i37_KanturuMonsterKill, this->m_reward.i37_KanturuMonsterKill);
		}
	}
	//i42_KillCastleSiegeNPC
	if(this->m_config.i42_KillCastleSiegeNPC > lpUser->ach.mission.i42_KillCastleSiegeNPC)
	{
		if(lpMonster->Class == 283 || lpMonster->Class == 277 || lpMonster->Class == 288 || lpMonster->Class == 222 || lpMonster->Class == 221)
		{
			lpUser->ach.mission.i42_KillCastleSiegeNPC++;
			this->PlayerReward(aIndex, this->m_config.i42_KillCastleSiegeNPC, lpUser->ach.mission.i42_KillCastleSiegeNPC, this->m_reward.i42_KillCastleSiegeNPC);
		}
	}
	//i44_KillErohim
	if(this->m_config.i44_KillErohim > lpUser->ach.mission.i44_KillErohim)
	{
		if(lpMonster->Class == 295)
		{
			lpUser->ach.mission.i44_KillErohim++;
			this->PlayerReward(aIndex, this->m_config.i44_KillErohim, lpUser->ach.mission.i44_KillErohim, this->m_reward.i44_KillErohim);
		}
	}
}

void CAchievements::PlayerKill(int aIndex, int aTargetIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex) || !gObjIsConnected(aTargetIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i5_PlayerKill
	if(this->m_config.i5_PlayerKill > lpUser->ach.mission.i5_PlayerKill)
	{
		lpUser->ach.mission.i5_PlayerKill++;
		this->PlayerReward(aIndex, this->m_config.i5_PlayerKill, lpUser->ach.mission.i5_PlayerKill, this->m_reward.i5_PlayerKill);
	}
	//i25_PhonomanKill
	if(this->m_config.i25_PhonomanKill > lpUser->ach.mission.i25_PhonomanKill)
	{
		if(lpTarget->m_PK_Level >= 6)
		{
			lpUser->ach.mission.i25_PhonomanKill++;
			this->PlayerReward(aIndex, this->m_config.i25_PhonomanKill, lpUser->ach.mission.i25_PhonomanKill, this->m_reward.i25_PhonomanKill);
		}
	}
	//i28_KillInSelf_Defense
	if(this->m_config.i28_KillInSelf_Defense > lpUser->ach.mission.i28_KillInSelf_Defense)
	{
		for(int n = 0; n < MAX_SELF_DEFENSE;n++)
		{
			if(lpUser->SelfDefense[n] >= 0)
			{
				if(lpUser->SelfDefense[n] == aTargetIndex)
				{
					lpUser->ach.mission.i28_KillInSelf_Defense++;
					this->PlayerReward(aIndex, this->m_config.i28_KillInSelf_Defense, lpUser->ach.mission.i28_KillInSelf_Defense, this->m_reward.i28_KillInSelf_Defense);
				}
			}
		}
	}
	//i38_MovePlayerFromSwitch
	if(this->m_config.i38_MovePlayerFromSwitch > lpUser->ach.mission.i38_MovePlayerFromSwitch)
	{
		int iCrownIndex1 = g_CastleSiege.GetCrownSwitchUserIndex(217);
		int iCrownIndex2 = g_CastleSiege.GetCrownSwitchUserIndex(218);

		if(gObjIsConnected(iCrownIndex1))
		{
			if(aTargetIndex == iCrownIndex1)
			{
				lpUser->ach.mission.i38_MovePlayerFromSwitch++;
				this->PlayerReward(aIndex, this->m_config.i38_MovePlayerFromSwitch, lpUser->ach.mission.i38_MovePlayerFromSwitch, this->m_reward.i38_MovePlayerFromSwitch);
			}
		}
		else if(gObjIsConnected(iCrownIndex2))
		{
			if(aTargetIndex == iCrownIndex2)
			{
				lpUser->ach.mission.i38_MovePlayerFromSwitch++;
				this->PlayerReward(aIndex, this->m_config.i38_MovePlayerFromSwitch, lpUser->ach.mission.i38_MovePlayerFromSwitch, this->m_reward.i38_MovePlayerFromSwitch);
			}
		}
	}	
	//i40_MovePlayerFromCrownkill
	if(this->m_config.i40_MovePlayerFromCrown > lpUser->ach.mission.i40_MovePlayerFromCrown)
	{
		int iCrownIndex = g_CastleSiege.GetCrownUserIndex();
		if(gObjIsConnected(iCrownIndex))
		{
			if(iCrownIndex == aTargetIndex)
			{
				lpUser->ach.mission.i40_MovePlayerFromCrown++;
				this->PlayerReward(aIndex, this->m_config.i40_MovePlayerFromCrown, lpUser->ach.mission.i40_MovePlayerFromCrown, this->m_reward.i40_MovePlayerFromCrown);
			}
		}
	}
	//i43_KillPlayerCastleSiege
	if(this->m_config.i43_KillPlayerCastleSiege > lpUser->ach.mission.i43_KillPlayerCastleSiege)
	{
#if(GAMESERVER_ACHIVEMENTS==EXTEAM_SERVER || GAMESERVER_ACHIVEMENTS==ZTEAM_SERVER)
		if(lpUser->MapNumber == MAP_INDEX_CASTLESIEGE)
		{
			if(g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
			{
				lpUser->ach.mission.i43_KillPlayerCastleSiege++;
				this->PlayerReward(aIndex, this->m_config.i43_KillPlayerCastleSiege, lpUser->ach.mission.i43_KillPlayerCastleSiege, this->m_reward.i43_KillPlayerCastleSiege);
			}
		}
#else
#if(GS_CASTLE==1)
		if(lpUser->MapNumber == MAP_INDEX_CASTLESIEGE)
		{
			if(g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
			{
				lpUser->ach.mission.i43_KillPlayerCastleSiege++;
				this->PlayerReward(aIndex, this->m_config.i43_KillPlayerCastleSiege, lpUser->ach.mission.i43_KillPlayerCastleSiege, this->m_reward.i43_KillPlayerCastleSiege);
			}
		}
#endif
#endif
	}
}

void CAchievements::PickUp(int aIndex, int iItemNum, int iLevel, int iExl, int iAnc, int iDur)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i12_PickUpJewels
	if(this->m_config.i12_PickUpJewels > lpUser->ach.mission.i12_PickUpJewels)
	{
		if( iItemNum == ITEMGET(12, 15) ||
			iItemNum == ITEMGET(14, 13) ||
			iItemNum == ITEMGET(14, 14) ||
			iItemNum == ITEMGET(14, 16) ||
			iItemNum == ITEMGET(14, 22) ||
			iItemNum == ITEMGET(14, 31) ||
			iItemNum == ITEMGET(14, 42))
		{
			lpUser->ach.mission.i12_PickUpJewels++;
			this->PlayerReward(aIndex, this->m_config.i12_PickUpJewels, lpUser->ach.mission.i12_PickUpJewels, this->m_reward.i12_PickUpJewels);
		}
	}
	//i16_PickUpZen
	if(this->m_config.i16_PickUpZen > lpUser->ach.mission.i16_PickUpZen)
	{
		if(iItemNum == ITEMGET(14,15))
		{
			lpUser->ach.mission.i16_PickUpZen++;
			this->PlayerReward(aIndex, this->m_config.i16_PickUpZen, lpUser->ach.mission.i16_PickUpZen, this->m_reward.i16_PickUpZen);
		}
	}
	//i17_PickUpExellent
	if(this->m_config.i17_PickUpExellent > lpUser->ach.mission.i17_PickUpExellent)
	{
		if(iExl > 0)
		{
			lpUser->ach.mission.i17_PickUpExellent++;
			this->PlayerReward(aIndex, this->m_config.i17_PickUpExellent, lpUser->ach.mission.i17_PickUpExellent, this->m_reward.i17_PickUpExellent);
		}
	}
	//i18_PickUpAncent
	if(this->m_config.i18_PickUpAncent > lpUser->ach.mission.i18_PickUpAncent)
	{
		if(iAnc > 0)
		{
			lpUser->ach.mission.i18_PickUpAncent++;
			this->PlayerReward(aIndex, this->m_config.i18_PickUpAncent, lpUser->ach.mission.i18_PickUpAncent, this->m_reward.i18_PickUpAncent);
		}
	}
	//i48_PickUpSing
	if(this->m_config.i48_PickUpRena > lpUser->ach.mission.i48_PickUpRena)
	{
		if(iItemNum == ITEMGET(14,21) && iLevel == 0)
		{
			lpUser->ach.mission.i48_PickUpRena++;
			this->PlayerReward(aIndex, this->m_config.i48_PickUpRena, lpUser->ach.mission.i48_PickUpRena, this->m_reward.i48_PickUpRena);
		}
	}
	//i49_PickUpLuckyCoins Sing of lord
	if(this->m_config.i49_PickUpLuckyCoins > lpUser->ach.mission.i49_PickUpLuckyCoins)
	{
		//if(iItemNum == ITEMGET(14,100))
		if(iItemNum == ITEMGET(14,21) && iLevel == 3)
		{
			//lpUser->ach.mission.i49_PickUpLuckyCoins++;
			lpUser->ach.mission.i49_PickUpLuckyCoins += iDur;

			if(lpUser->ach.mission.i49_PickUpLuckyCoins > this->m_config.i49_PickUpLuckyCoins)
			{
				lpUser->ach.mission.i49_PickUpLuckyCoins = this->m_config.i49_PickUpLuckyCoins;
			}

			this->PlayerReward(aIndex, this->m_config.i49_PickUpLuckyCoins, lpUser->ach.mission.i49_PickUpLuckyCoins, this->m_reward.i49_PickUpLuckyCoins);
		}
	}
}

void CAchievements::UsedJewel(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i13_UsedJewels
	if(this->m_config.i13_UsedJewels > lpUser->ach.mission.i13_UsedJewels)
	{
		lpUser->ach.mission.i13_UsedJewels++;
		this->PlayerReward(aIndex, this->m_config.i13_UsedJewels, lpUser->ach.mission.i13_UsedJewels, this->m_reward.i13_UsedJewels);
	}
}

void CAchievements::TimeInGame(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i11_OnlineTime
	if(this->m_config.i11_OnlineTime > lpUser->ach.mission.i11_OnlineTime)
	{
		lpUser->ach.InGameTime++;
		if(lpUser->ach.InGameTime >= 3600)
		{
			lpUser->ach.mission.i11_OnlineTime++;
			this->PlayerReward(aIndex, this->m_config.i11_OnlineTime, lpUser->ach.mission.i11_OnlineTime, this->m_reward.i11_OnlineTime);
			lpUser->ach.InGameTime = 0;
		}
	}
	//i39_WithstandSwitch10min
	if(this->m_config.i39_WithstandSwitch10min > lpUser->ach.mission.i39_WithstandSwitch10min)
	{
		int iCrownIndex1 = g_CastleSiege.GetCrownSwitchUserIndex(217);
		int iCrownIndex2 = g_CastleSiege.GetCrownSwitchUserIndex(218);

		if(gObjIsConnected(iCrownIndex1) || gObjIsConnected(iCrownIndex2))
		{
			if(aIndex == iCrownIndex1 || aIndex == iCrownIndex2)
			{
				lpUser->ach.CSSwitchTime++;
				if(lpUser->ach.CSSwitchTime >= 60)
				{
					lpUser->ach.mission.i39_WithstandSwitch10min++;
					this->PlayerReward(aIndex, this->m_config.i39_WithstandSwitch10min, lpUser->ach.mission.i39_WithstandSwitch10min, this->m_reward.i39_WithstandSwitch10min);
					lpUser->ach.CSSwitchTime = 0;
				}
			}
		}
	}
	//i50_OfflineAttackTime
	if(this->m_config.i50_OfflineAttackTime > lpUser->ach.mission.i50_OfflineAttackTime)
	{
#if(GAMESERVER_ACHIVEMENTS==EXTEAM_SERVER)
		if(lpUser->m_OfflineMode || lpUser->OffExp)
#endif
#if(GAMESERVER_ACHIVEMENTS==EXGAME_SERVER)
		if(lpUser->m_OfflineMode)
#endif
#if(GAMESERVER_ACHIVEMENTS==ZTEAM_SERVER)
		if(lpUser->OffExp)
#endif
		{
			lpUser->ach.InOfflineAttackTime++;
			if(lpUser->ach.InOfflineAttackTime >= 3600)
			{
				lpUser->ach.mission.i50_OfflineAttackTime++;
				this->PlayerReward(aIndex, this->m_config.i50_OfflineAttackTime, lpUser->ach.mission.i50_OfflineAttackTime, this->m_reward.i50_OfflineAttackTime);
				lpUser->ach.InOfflineAttackTime = 0;
			}
		}
	}
}

void CAchievements::SuccessChaosMix(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i14_SuccessChaosMix
	if(this->m_config.i14_SuccessChaosMix > lpUser->ach.mission.i14_SuccessChaosMix)
	{
		lpUser->ach.mission.i14_SuccessChaosMix++;
		this->PlayerReward(aIndex, this->m_config.i14_SuccessChaosMix, lpUser->ach.mission.i14_SuccessChaosMix, this->m_reward.i14_SuccessChaosMix);
	}
}

void CAchievements::FailedChaosMix(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i15_FailedChaosMix
	if(this->m_config.i15_FailedChaosMix > lpUser->ach.mission.i15_FailedChaosMix)
	{
		lpUser->ach.mission.i15_FailedChaosMix++;
		this->PlayerReward(aIndex, this->m_config.i15_FailedChaosMix, lpUser->ach.mission.i15_FailedChaosMix, this->m_reward.i15_FailedChaosMix);
	}
}

void CAchievements::LevelUp(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i20_LevelUp
	if(this->m_config.i20_LevelUp > lpUser->ach.mission.i20_LevelUp)
	{
		lpUser->ach.mission.i20_LevelUp++;
		this->PlayerReward(aIndex, this->m_config.i20_LevelUp, lpUser->ach.mission.i20_LevelUp, this->m_reward.i20_LevelUp);
	}
	//i47_PartyNoobLevelUp
	if(this->m_config.i47_PartyNoobLevelUp > lpUser->ach.mission.i47_PartyNoobLevelUp)
	{
		if(lpUser->PartyNumber >= 0)
		{
			int iPartyNumber = lpUser->PartyNumber;
			for(int i = 0; i < MAX_USER_IN_PARTY; i++ )
			{
				int aUserIndex = gParty.m_PartyS[iPartyNumber].Number[i];
				if (gObjIsConnected(aUserIndex))
				{
					LPOBJ PartyUser = &gObj[aUserIndex];
					if(lpUser->Level > (PartyUser->Level+100))
					{
						lpUser->ach.mission.i47_PartyNoobLevelUp++;
						this->PlayerReward(aIndex, this->m_config.i47_PartyNoobLevelUp, lpUser->ach.mission.i47_PartyNoobLevelUp, this->m_reward.i47_PartyNoobLevelUp);
						break;
					}		
				}
			}
		}
	}
}

void CAchievements::ResetUp(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i21_ResetUp
	if(this->m_config.i21_ResetUp > lpUser->ach.mission.i21_ResetUp)
	{
		lpUser->ach.mission.i21_ResetUp++;
		this->PlayerReward(aIndex, this->m_config.i21_ResetUp, lpUser->ach.mission.i21_ResetUp, this->m_reward.i21_ResetUp);
	}
}

void CAchievements::GrandResetUp(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i33_GrandResetUp
	if(this->m_config.i33_GrandResetUp > lpUser->ach.mission.i33_GrandResetUp)
	{
		lpUser->ach.mission.i33_GrandResetUp++;
		this->PlayerReward(aIndex, this->m_config.i33_GrandResetUp, lpUser->ach.mission.i33_GrandResetUp, this->m_reward.i33_GrandResetUp);
	}
}

void CAchievements::MootopVoteUp(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i24_MootopVote
	if(this->m_config.i24_MootopVote > lpUser->ach.mission.i24_MootopVote)
	{
		lpUser->ach.mission.i24_MootopVote++;
		this->PlayerReward(aIndex, this->m_config.i24_MootopVote, lpUser->ach.mission.i24_MootopVote, this->m_reward.i24_MootopVote);
	}
}

void CAchievements::TeleportInCC(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i9_TakePartInCC
	if(this->m_config.i9_TakePartInCC > lpUser->ach.mission.i9_TakePartInCC)
	{
		lpUser->ach.mission.i9_TakePartInCC++;
		this->PlayerReward(aIndex, this->m_config.i9_TakePartInCC, lpUser->ach.mission.i9_TakePartInCC, this->m_reward.i9_TakePartInCC);
	}
}

void CAchievements::WinCastleSiege(char* szGuildName)
{
	if(!this->bEnable)
	{
		return;
	}

	if(strlen(szGuildName) < 1)
	{
		return;
	}

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected == PLAYER_PLAYING && lpUser->Type == OBJ_USER)
		{
			if(!lpUser->ach.bLoaded)
			{
				continue;
			}

			_GUILD_INFO_STRUCT * lpGuildUser = lpUser->lpGuild;

			if(!lpGuildUser)
			{
				continue;
			}

			if(!strcmp(lpGuildUser->Name, szGuildName))
			{
				//i41_WinSiege
				if(this->m_config.i41_WinSiege > lpUser->ach.mission.i41_WinSiege)
				{
					lpUser->ach.mission.i41_WinSiege++;
					this->PlayerReward(aIndex, this->m_config.i41_WinSiege, lpUser->ach.mission.i41_WinSiege, this->m_reward.i41_WinSiege);
				}
				continue;
			}

			TUnionInfo * pUnionUser = UnionManager.SearchUnion(lpGuildUser->iGuildUnion);

			if(!pUnionUser)
			{
				continue;
			}

			if(!strcmp(pUnionUser->m_szMasterGuild, szGuildName))
			{
				//i41_WinSiege
				if(this->m_config.i41_WinSiege > lpUser->ach.mission.i41_WinSiege)
				{
					lpUser->ach.mission.i41_WinSiege++;
					this->PlayerReward(aIndex, this->m_config.i41_WinSiege, lpUser->ach.mission.i41_WinSiege, this->m_reward.i41_WinSiege);
				}
			}
		}
	}
}

void CAchievements::BuyDonateShopItem(int aIndex, int iCost)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i45_BuyDonateShopItem
	if(this->m_config.i45_BuyDonateShopItem > lpUser->ach.mission.i45_BuyDonateShopItem)
	{
		lpUser->ach.mission.i45_BuyDonateShopItem += iCost;
		if(lpUser->ach.mission.i45_BuyDonateShopItem > this->m_config.i45_BuyDonateShopItem)
		{
			lpUser->ach.mission.i45_BuyDonateShopItem = this->m_config.i45_BuyDonateShopItem;
			this->PlayerReward(aIndex, this->m_config.i45_BuyDonateShopItem, lpUser->ach.mission.i45_BuyDonateShopItem, this->m_reward.i45_BuyDonateShopItem);
		}
	}
}

void CAchievements::GuildWarWin(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i46_GuildWarWin
	if(this->m_config.i46_GuildWarWin > lpUser->ach.mission.i46_GuildWarWin)
	{
		lpUser->ach.mission.i46_GuildWarWin++;
		this->PlayerReward(aIndex, this->m_config.i46_GuildWarWin, lpUser->ach.mission.i46_GuildWarWin, this->m_reward.i46_GuildWarWin);
	}
}

void CAchievements::DuelWin(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i19_DuelWin
	if(this->m_config.i10_WinningTheCC > lpUser->ach.mission.i10_WinningTheCC)
	{
		lpUser->ach.mission.i19_DuelWin++;
		this->PlayerReward(aIndex, this->m_config.i19_DuelWin, lpUser->ach.mission.i19_DuelWin, this->m_reward.i19_DuelWin);
	}
}

void CAchievements::CompleteBC(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i32_CompleteBC
	if(this->m_config.i32_CompleteBC > lpUser->ach.mission.i32_CompleteBC)
	{
		lpUser->ach.mission.i32_CompleteBC++;
		this->PlayerReward(aIndex, this->m_config.i32_CompleteBC, lpUser->ach.mission.i32_CompleteBC, this->m_reward.i32_CompleteBC);
	}
}

void CAchievements::WinCC(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i10_WinningTheCC
	if(this->m_config.i10_WinningTheCC > lpUser->ach.mission.i10_WinningTheCC)
	{
		lpUser->ach.mission.i10_WinningTheCC++;
		this->PlayerReward(aIndex, this->m_config.i10_WinningTheCC, lpUser->ach.mission.i10_WinningTheCC, this->m_reward.i10_WinningTheCC);
	}
}

void CAchievements::PickUpZen(int aIndex, int money)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	//i16_PickUpZen
	if(this->m_config.i16_PickUpZen > lpUser->ach.mission.i16_PickUpZen)
	{
		lpUser->ach.mission.i16_PickUpZen += money;
		this->PlayerReward(aIndex, this->m_config.i16_PickUpZen, lpUser->ach.mission.i16_PickUpZen, this->m_reward.i16_PickUpZen);
	}
}

void CAchievements::CalculatorPower(int aIndex)
{
	if(!this->bEnable)
	{
		return;
	}

	if(!gObjIsConnected(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return;
	}

	int iAchCount = 0;

	if(lpUser->ach.mission.i1_MonsterKill >= this->m_config.i1_MonsterKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i2_GoldenKill >= this->m_config.i2_GoldenKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i3_KalimaMonserKill >= this->m_config.i3_KalimaMonserKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i4_WhiteWizardKill >= this->m_config.i4_WhiteWizardKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i5_PlayerKill >= this->m_config.i5_PlayerKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i6_RedDragonKill >= this->m_config.i6_RedDragonKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i7_OrcKill >= this->m_config.i7_OrcKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i8_KillGateBC >= this->m_config.i8_KillGateBC)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i9_TakePartInCC >= this->m_config.i9_TakePartInCC)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i10_WinningTheCC >= this->m_config.i10_WinningTheCC)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i11_OnlineTime >= this->m_config.i11_OnlineTime)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i12_PickUpJewels >= this->m_config.i12_PickUpJewels)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i13_UsedJewels >= this->m_config.i13_UsedJewels)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i14_SuccessChaosMix >= this->m_config.i14_SuccessChaosMix)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i15_FailedChaosMix >= this->m_config.i15_FailedChaosMix)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i16_PickUpZen >= this->m_config.i16_PickUpZen)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i17_PickUpExellent >= this->m_config.i17_PickUpExellent)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i18_PickUpAncent >= this->m_config.i18_PickUpAncent)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i19_DuelWin >= this->m_config.i19_DuelWin)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i20_LevelUp >= this->m_config.i20_LevelUp)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i21_ResetUp >= this->m_config.i21_ResetUp)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i22_KanturuBossKill >= this->m_config.i22_KanturuBossKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i23_Monster100LvlKill >= this->m_config.i23_Monster100LvlKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i24_MootopVote >= this->m_config.i24_MootopVote)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i25_PhonomanKill >= this->m_config.i25_PhonomanKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i26_CryWolfEventMonster >= this->m_config.i26_CryWolfEventMonster)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i27_HellMainKill >= this->m_config.i27_HellMainKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i28_KillInSelf_Defense >= this->m_config.i28_KillInSelf_Defense)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i29_SelupanKill >= this->m_config.i29_SelupanKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i30_KundunKill >= this->m_config.i30_KundunKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i31_KillStatueBC >= this->m_config.i31_KillStatueBC)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i32_CompleteBC >= this->m_config.i32_CompleteBC)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i33_GrandResetUp >= this->m_config.i33_GrandResetUp)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i34_BlueRabbitKiller >= this->m_config.i34_BlueRabbitKiller)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i35_HappyPouchesKiller >= this->m_config.i35_HappyPouchesKiller)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i36_PheonixKill >= this->m_config.i36_PheonixKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i37_KanturuMonsterKill >= this->m_config.i37_KanturuMonsterKill)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i38_MovePlayerFromSwitch >= this->m_config.i38_MovePlayerFromSwitch)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i39_WithstandSwitch10min >= this->m_config.i39_WithstandSwitch10min)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i40_MovePlayerFromCrown >= this->m_config.i40_MovePlayerFromCrown)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i41_WinSiege >= this->m_config.i41_WinSiege)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i42_KillCastleSiegeNPC >= this->m_config.i42_KillCastleSiegeNPC)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i43_KillPlayerCastleSiege >= this->m_config.i43_KillPlayerCastleSiege)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i44_KillErohim >= this->m_config.i44_KillErohim)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i45_BuyDonateShopItem >= this->m_config.i45_BuyDonateShopItem)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i46_GuildWarWin >= this->m_config.i46_GuildWarWin)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i47_PartyNoobLevelUp >= this->m_config.i47_PartyNoobLevelUp)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i48_PickUpRena >= this->m_config.i48_PickUpRena)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i49_PickUpLuckyCoins >= this->m_config.i49_PickUpLuckyCoins)
	{
		iAchCount++;
	}

	if(lpUser->ach.mission.i50_OfflineAttackTime >= this->m_config.i50_OfflineAttackTime)
	{
		iAchCount++;
	}

	int iAddDamage = 0;
	int iAddDefence = 0;
	int iAddLife = 0;
	int iAddExellentPercent = 0;
	int iAddCriticalPercent = 0;

	//iAddDamage = 60 * iAchCount;
	//iAddDefence = 40 * iAchCount;
	//iAddLife =  200 * iAchCount;
	//iAddExellentPercent = 0.2 * iAchCount;
	//iAddCriticalPercent = 0.2 * iAchCount;

	iAddDamage = this->m_DivDamage * iAchCount;
	iAddDefence = this->m_DivDefence * iAchCount;
	iAddLife =  this->m_DivLife * iAchCount;

	if(iAchCount > 0)
	{
		iAddExellentPercent = ( iAchCount * this->m_DivExellentPercent ) / 100;
		iAddCriticalPercent = ( iAchCount * this->m_DivCriticalPercent ) / 100;
	}

	if(iAddDamage > 0)
	{
		if(iAddDamage > this->iDamageMax)
		{
			iAddDamage = this->iDamageMax;
		}
		lpUser->m_AttackDamageMaxLeft += iAddDamage;
		lpUser->m_AttackDamageMinLeft += iAddDamage;
		lpUser->m_AttackDamageMaxRight += iAddDamage;
		lpUser->m_AttackDamageMinRight += iAddDamage;
		lpUser->m_MagicDamageMin += iAddDamage;
		lpUser->m_MagicDamageMax += iAddDamage;
	}

	if(iAddDefence > 0)
	{
		if(iAddDefence > this->iDefenceMax)
		{
			iAddDefence = this->iDefenceMax;
		}
		lpUser->m_Defense += iAddDefence;
		lpUser->m_MagicDefense += iAddDefence;
	}

	if(iAddLife > 0)
	{
		if(iAddLife > this->iLifeMax)
		{
			iAddLife = this->iLifeMax;
		}
		lpUser->AddLife += iAddLife;
	}

	if(iAddExellentPercent > 0)
	{
		if(iAddExellentPercent > this->iExellentDamageMax)
		{
			iAddExellentPercent = this->iExellentDamageMax;
		}
		lpUser->m_ExcelentDamage += iAddExellentPercent;
	}

	if(iAddCriticalPercent > 0)
	{
		if(iAddCriticalPercent > this->iCriticalDamageMax)
		{
			iAddCriticalPercent = this->iCriticalDamageMax;
		}
		lpUser->m_CriticalDamage += iAddCriticalPercent;
	}

	PMSG_GC_ACH_POWER pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x92, sizeof(pMsg));

	pMsg.iDamage = iAddDamage;
	pMsg.iDamageMax = this->iDamageMax;
	pMsg.iDefence = iAddDefence;
	pMsg.iDefenceMax = this->iDefenceMax;
	pMsg.iLife = iAddLife;
	pMsg.iLifeMax = this->iLifeMax;
	pMsg.iExellentDamage = iAddExellentPercent;
	pMsg.iExellentDamageMax = this->iExellentDamageMax;
	pMsg.iCriticalDamage = iAddCriticalPercent;
	pMsg.iCriticalDamageMax = this->iCriticalDamageMax;

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

bool CAchievements::GetItemDrop(int aIndex, int ItemNumber)
{
	if(!this->bEnable)
	{
		return true;
	}

	if(!gObjIsConnected(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->ach.bLoaded)
	{
		return true;
	}

	//if(this->m_config.i48_PickUpRena > lpUser->ach.mission.i48_PickUpRena || this->m_config.i49_PickUpLuckyCoins > lpUser->ach.mission.i49_PickUpLuckyCoins)
	{
		if(ItemNumber == ITEMGET(14,21))
		{
			return false;
		}
	}

	return true;
}

#endif