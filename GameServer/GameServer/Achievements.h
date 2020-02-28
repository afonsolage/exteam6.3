#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"

#if(SYSTEM_ACHIEVEMENTS)
// ----------------------------------------------------------------------------------------------
// -> switch
#define EXTEAM_SERVER	0
#define EXGAME_SERVER	1
#define ZTEAM_SERVER	2
// ----------------------------------------------------------------------------------------------
#define GAMESERVER_ACHIVEMENTS	EXTEAM_SERVER
// ----------------------------------------------------------------------------------------------
#define DEBUG_ARCH	1
// ----------------------------------------------------------------------------------------------
#define ACH_PROTOCOL1	0x27
// ----------------------------------------------------------------------------------------------

struct ACHIEVEMENTS_DATA
{
	unsigned int i1_MonsterKill;
	unsigned int i2_GoldenKill;
	unsigned int i3_KalimaMonserKill;
	unsigned int i4_WhiteWizardKill;
	unsigned int i5_PlayerKill;
	unsigned int i6_RedDragonKill;
	unsigned int i7_OrcKill;
	unsigned int i8_KillGateBC;
	unsigned int i9_TakePartInCC;
	unsigned int i10_WinningTheCC;
	unsigned int i11_OnlineTime;
	unsigned int i12_PickUpJewels;
	unsigned int i13_UsedJewels;
	unsigned int i14_SuccessChaosMix;
	unsigned int i15_FailedChaosMix;
	unsigned int i16_PickUpZen;
	unsigned int i17_PickUpExellent;
	unsigned int i18_PickUpAncent;
	unsigned int i19_DuelWin;
	unsigned int i20_LevelUp;
	unsigned int i21_ResetUp;
	unsigned int i22_KanturuBossKill;
	unsigned int i23_Monster100LvlKill;
	unsigned int i24_MootopVote;
	unsigned int i25_PhonomanKill;
	unsigned int i26_CryWolfEventMonster;
	unsigned int i27_HellMainKill;
	unsigned int i28_KillInSelf_Defense;
	unsigned int i29_SelupanKill;
	unsigned int i30_KundunKill;
	unsigned int i31_KillStatueBC;
	unsigned int i32_CompleteBC;
	unsigned int i33_GrandResetUp;
	unsigned int i34_BlueRabbitKiller;
	unsigned int i35_HappyPouchesKiller;
	unsigned int i36_PheonixKill;
	unsigned int i37_KanturuMonsterKill;
	unsigned int i38_MovePlayerFromSwitch;
	unsigned int i39_WithstandSwitch10min;
	unsigned int i40_MovePlayerFromCrown;
	unsigned int i41_WinSiege;
	unsigned int i42_KillCastleSiegeNPC;
	unsigned int i43_KillPlayerCastleSiege;
	unsigned int i44_KillErohim;
	unsigned int i45_BuyDonateShopItem;
	unsigned int i46_GuildWarWin;
	unsigned int i47_PartyNoobLevelUp;
	unsigned int i48_PickUpRena;
	unsigned int i49_PickUpLuckyCoins;
	unsigned int i50_OfflineAttackTime;
};
// ----------------------------------------------------------------------------------------------
// User
struct ACHIEVEMENTS_USER_DATA
{
	bool bLoaded;
	int InGameTime;
	int InOfflineAttackTime;
	int CSSwitchTime;
	ACHIEVEMENTS_DATA mission;
};
// ----------------------------------------------------------------------------------------------
// GameServer <-> Client
struct PMSG_GC_ACH_SETTINGS_DATA
{
	PBMSG_HEAD2 h;
	ACHIEVEMENTS_DATA cfg;
};

struct PMSG_GC_ACH_PLAYER_DATA
{
	PBMSG_HEAD2 h;
	bool bWinOpen;
	ACHIEVEMENTS_DATA usr;
};

// ----------------------------------------------------------------------------------------------
// GameServer <-> DataServer
struct PMSG_GDREQ_ACH_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char szName[11];
};

struct PMSG_DGANS_ACH_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
	ACHIEVEMENTS_DATA usr;
};

struct PMSG_GDREQ_ACH_SAVE
{
	PBMSG_HEAD2 h;
	char szName[11];
	ACHIEVEMENTS_DATA usr;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_CG_ACH_WINOPEN
{
	PBMSG_HEAD2 h;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_GC_ACH_POWER
{
	PBMSG_HEAD2 h;
	int iDamage;
	int iDamageMax;
	int iDefence;
	int iDefenceMax;
	int iLife;
	int iLifeMax;
	int iExellentDamage;
	int iExellentDamageMax;
	int iCriticalDamage;
	int iCriticalDamageMax;
};
// ----------------------------------------------------------------------------------------------

class CAchievements
{
public:
		 CAchievements();
		 ~CAchievements();

	void Init();
	void Load();
	void Read(char* filename);
	void GDPlayerLoad(int aIndex);
	void DGPlayerLoad(PMSG_DGANS_ACH_LOAD* aRecv);
	void GDPlayerSave(int aIndex);
	void GCSettingsData(int aIndex);
	void GCPlayerData(int aIndex, bool bWin);
	void CGWindowOpen(PMSG_CG_ACH_WINOPEN* aRecv, int aIndex);
	void PlayerReward(int aIndex, int mission_need, int mission, int ireward);

	void MonsterKill(int aIndex, int aMonsterIndex);
	void PlayerKill(int aIndex, int aTargetIndex);
	void PickUp(int aIndex, int iItemNum, int iLevel, int iExl, int iAnc, int iDur);
	void UsedJewel(int aIndex);
	void TimeInGame(int aIndex);
	void SuccessChaosMix(int aIndex);
	void FailedChaosMix(int aIndex);
	void LevelUp(int aIndex);
	void ResetUp(int aIndex);
	void GrandResetUp(int aIndex);
	void MootopVoteUp(int aIndex);
	void TeleportInCC(int aIndex);
	void WinCastleSiege(char* szGuildName);
	void BuyDonateShopItem(int aIndex, int iCost);
	void GuildWarWin(int aIndex);
	void DuelWin(int aIndex);
	void CompleteBC(int aIndex);
	void WinCC(int aIndex);
	void PickUpZen(int aIndex, int money);
	bool GetItemDrop(int aIndex, int ItemNumber);

	void CalculatorPower(int aIndex);

	int m_DivDamage;
	int m_DivDefence;
	int m_DivLife;
	int m_DivExellentPercent;
	int m_DivCriticalPercent;

private:
	bool bEnable;
	ACHIEVEMENTS_DATA m_config;
	ACHIEVEMENTS_DATA m_reward;

	int iDamageMax;
	int iDefenceMax;
	int iLifeMax;
	int iExellentDamageMax;
	int iCriticalDamageMax;
};
extern CAchievements  g_Achievements;
// ----------------------------------------------------------------------------------------------

#endif
