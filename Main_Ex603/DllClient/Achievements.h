#pragma once

#include "StdAfx.h"

#if(SYSTEM_ACHIEVEMENTS)
// ----------------------------------------------------------------------------------------------
// -> switch
#define EXTEAM_SERVER	0
#define EXGAME_SERVER	1
#define ZTEAM_SERVER	2
// ----------------------------------------------------------------------------------------------
#define GAMESERVER_ACHIVEMENTS	EXTEAM_SERVER
// -----------------------------------------------------------------------------------------------
#define ACH_PROTOCOL1	0x27
#define ACH_PANEL		1
// ----------------------------------------------------------------------------------------------
#if(GAMESERVER_ACHIVEMENTS == EXGAME_SERVER || GAMESERVER_ACHIVEMENTS == ZTEAM_SERVER)
#include "ProtocolDefine.h"
#else
#include "Protocol.h"
#endif
// ----------------------------------------------------------------------------------------------

struct ACHIEVEMENTS_DATA
{
	unsigned int i1_MonsterKill;
	unsigned int i2_GoldenKill;
	unsigned int i3_KalimaMonserKill;
	unsigned int i4_WhiteWizardKill; //
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
	void LoadImages();
	void BindImages();
	void Draw();
	void DrawMission(int ObjectID, float X, float Y, char* Name, int Start, int Need);
	void Button(DWORD Event);
	void GCConfigData(PMSG_GC_ACH_SETTINGS_DATA* aRecv);
	void GCPlayerData(PMSG_GC_ACH_PLAYER_DATA* aRecv);
	void CGWindowOpen();
	void DrawPanel();
	void DrawPower(int ObjectID, float X, float Y, char* Name, int Start, int Need);
	void GCCalculatorPower(PMSG_GC_ACH_POWER* aRecv);
	
private:
	bool bActive;
	ACHIEVEMENTS_DATA m_config;
	ACHIEVEMENTS_DATA m_user;

	int m_Damage;
	int m_DamageMax;
	int m_Defence;
	int m_DefenceMax;
	int m_Life;
	int m_LifeMax;
	int m_ExellentDamage;
	int m_ExellentDamageMax;
	int m_CriticalDamage;
	int m_CriticalDamageMax;
};
extern CAchievements  g_Achievements;
// ----------------------------------------------------------------------------------------------
#endif
