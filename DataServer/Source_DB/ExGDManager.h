#pragma once

#include "StdAfx.h"
#include ".\\DbSet\\DBConBase.h"

#define SYSTEM_ACHIEVEMENTS		1

#define EX_QUEST_SYSTEM_SIZE	39
#define EW_MAX_ACT				3
#define EW_MAX_MISSION			5

struct PMSG_REQ_PARTYSEARCH_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char Name[11];
};

struct PMSG_ANS_PARTYSEARCH_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
	unsigned char btPartySearch[PARTY_SEARCH_SIZE];
};

struct PMSG_REQ_PARTYSEARCH_SAVE
{
	PBMSG_HEAD2 h;
	char Name[11];
	BYTE btPartySearch[PARTY_SEARCH_SIZE];
};
// -------------------------------------------------------------------------------

struct PMSG_REQ_EXBUFF_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char Name[11];
};

struct PMSG_ANS_EXBUFF_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
	DWORD ExpBuffTime;
	DWORD DamageBuffTime;
	DWORD DefenceBuffTime;
	DWORD BattleBuffTime;
	DWORD DropBuffTime;
	DWORD DoubleBuffTime;
};

struct PMSG_REQ_EXBUFF_SAVE
{
	PBMSG_HEAD2 h;
	char Name[11];
	DWORD ExpBuffTime;
	DWORD DamageBuffTime;
	DWORD DefenceBuffTime;
	DWORD BattleBuffTime;
	DWORD DropBuffTime;
	DWORD DoubleBuffTime;
};
// -------------------------------------------------------------------------------

struct PMSG_REQ_BMQUEST_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char Name[11];
};

struct PMSG_ANS_BMQUEST_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
	int BMQuest_num;
	int BMQuest_kill;
	int BMQuest_start;
	int BMDamageReflect;
	int BMDamage;
	int BMDefense;
	int BMCriticalDamage;
	int BMExcelentDamage;
	int BMLife;
};

struct PMSG_REQ_BMQUEST_SAVE
{
	PBMSG_HEAD2 h;
	char Name[11];
	int BMQuest_num;
	int BMQuest_kill;
	int BMQuest_start;
	int BMDamageReflect;
	int BMDamage;
	int BMDefense;
	int BMCriticalDamage;
	int BMExcelentDamage;
	int BMLife;
};
// -------------------------------------------------------------------------------

struct PMSG_REQ_MONSTERQUEST_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char Name[11];
};

struct PMSG_ANS_MONSTERQUEST_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
	WORD QuestNum;
	int QuestKill_1;
	int QuestKill_2;
	int QuestKill_3;
	int QuestKill_4;
	int QuestKill_5;
};

struct PMSG_REQ_MONSTERQUEST_SAVE
{
	PBMSG_HEAD2 h;
	char Name[11];
	WORD QuestNum;
	int QuestKill_1;
	int QuestKill_2;
	int QuestKill_3;
	int QuestKill_4;
	int QuestKill_5;
};
// -------------------------------------------------------------------------------

struct PMSG_REQ_RAGESYSTEM_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char AccountID[11];
	char Name[11];
};

struct PMSG_ANS_RAGESYSTEM_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
	unsigned short rLevel;
	unsigned short rPoints;
	unsigned int rExperience;
	unsigned char Damage;
	unsigned char FreePoints;
	unsigned char SummonPet;
	unsigned char WingsDamagePlus;
	unsigned char FinalMana;
	unsigned char IgnoreDefence;
	unsigned char ResetLevel;
	unsigned char Teleport;
	unsigned char CriticalDamageRate;
	unsigned char AbsordDamage;
	unsigned char PetDamageBonus;
	unsigned char FinalLife;
	unsigned char Strength;
	unsigned char DefenceRate;
	unsigned char FireDamage;
	unsigned char Energy;
	unsigned char Agility;
	unsigned char DoubleDamage;
	unsigned char FinalSD;
	unsigned char FinalDefence;
	unsigned char ZenDrop;
	unsigned char GuildBonus;
	unsigned char ReflectDamage;
	unsigned char ExellentDamageRate;
	unsigned char PvPBonusPlus;
	unsigned char MinDefence;
	unsigned char Experience;
	unsigned char StartSD;
	unsigned char PartyBonus;
	unsigned char IceDamage;
	unsigned char DistanceAttack;
	unsigned char AttackRate;
	unsigned char WeaponBonus;
	unsigned char ExellentDamage;
	unsigned char CriticalDamage;
};

struct PMSG_REQ_RAGESYSTEM_SAVE
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	unsigned short rLevel;
	unsigned short rPoints;
	unsigned int rExperience;
	unsigned char Damage;
	unsigned char FreePoints;
	unsigned char SummonPet;
	unsigned char WingsDamagePlus;
	unsigned char FinalMana;
	unsigned char IgnoreDefence;
	unsigned char ResetLevel;
	unsigned char Teleport;
	unsigned char CriticalDamageRate;
	unsigned char AbsordDamage;
	unsigned char PetDamageBonus;
	unsigned char FinalLife;
	unsigned char Strength;
	unsigned char DefenceRate;
	unsigned char FireDamage;
	unsigned char Energy;
	unsigned char Agility;
	unsigned char DoubleDamage;
	unsigned char FinalSD;
	unsigned char FinalDefence;
	unsigned char ZenDrop;
	unsigned char GuildBonus;
	unsigned char ReflectDamage;
	unsigned char ExellentDamageRate;
	unsigned char PvPBonusPlus;
	unsigned char MinDefence;
	unsigned char Experience;
	unsigned char StartSD;
	unsigned char PartyBonus;
	unsigned char IceDamage;
	unsigned char DistanceAttack;
	unsigned char AttackRate;
	unsigned char WeaponBonus;
	unsigned char ExellentDamage;
	unsigned char CriticalDamage;
};
// -------------------------------------------------------------------------------

struct PMSG_REQ_CREATEON_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char szName[11];
};

struct PMSG_ANS_CREATEON_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	int iCreateon;
	int iGuardian;
	int iHarmony;
	int iLowStone;
	int iHighStone;
	int iGemStone;
};

struct PMSG_REQ_CREATEON_SAVE
{
	PBMSG_HEAD2 h;
	char szName[11];
	int iCreateon;
	int iGuardian;
	int iHarmony;
	int iLowStone;
	int iHighStone;
	int iGemStone;
};
// -------------------------------------------------------------------------------

struct PMSG_TVTGD_INFO
{
	PBMSG_HEAD2 h;
	char Name[11];
	int KillCount;
};
// -------------------------------------------------------------------------------

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
// -------------------------------------------------------------------------------

struct PMSG_REQ_OFFLINE_AFK
{
	PBMSG_HEAD2 h;
	char Name[11];
	BYTE ConnectType;
	BYTE OfflineType;
};
// -------------------------------------------------------------------------------

struct PMSG_REQ_VOTEBUFF_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char szName[11];
};

struct PMSG_ANS_VOTEBUFF_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	int MTBuffTime;
	int QTBuffTime;
};

struct PMSG_REQ_VOTEBUFF_SAVE
{
	PBMSG_HEAD2 h;
	char szName[11];
	int MTBuffTime;
	int QTBuffTime;
};
// -------------------------------------------------------------------------------

struct PMSG_REQ_EXQUESTSYSTEM_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char Name[11];
};

struct PMSG_ANS_EXQUESTSYSTEM_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
	BYTE ExWQuestStart[EW_MAX_ACT];
	WORD ExWQuestNum[EW_MAX_ACT];
	WORD ExWQuestCount[EW_MAX_ACT][EW_MAX_MISSION];
};

struct PMSG_REQ_EXQUESTSYSTEM_SAVE
{
	PBMSG_HEAD2 h;
	char Name[11];
	BYTE ExWQuestStart[EW_MAX_ACT];
	WORD ExWQuestNum[EW_MAX_ACT];
	WORD ExWQuestCount[EW_MAX_ACT][EW_MAX_MISSION];
};
// -------------------------------------------------------------------------------

class CExGDManager
{
public:
			CExGDManager();
			~CExGDManager();

	bool	Connect();
	void	CreateTable();

	void	Protocol(BYTE protoNum, BYTE *aRecv, int uIndex);

	void	DG_PartySearchLoad(PMSG_REQ_PARTYSEARCH_LOAD *aRecv, int uIndex);
	void	GD_PartySearchSave(PMSG_REQ_PARTYSEARCH_SAVE *aRecv);

	void	DG_ExBuffLoad(PMSG_REQ_EXBUFF_LOAD *aRecv, int uIndex);
	void	GD_ExBuffSave(PMSG_REQ_EXBUFF_SAVE *aRecv);

	void	DG_BMQuestLoad(PMSG_REQ_BMQUEST_LOAD *aRecv, int uIndex);
	void	GD_BMQuestSave(PMSG_REQ_BMQUEST_SAVE *aRecv);

	void	DG_MonsterQuestLoad(PMSG_REQ_MONSTERQUEST_LOAD *aRecv, int uIndex);
	void	GD_MonsterQuestSave(PMSG_REQ_MONSTERQUEST_SAVE *aRecv);

	void	DG_RageSystemLoad(PMSG_REQ_RAGESYSTEM_LOAD *aRecv, int uIndex);
	void	GD_RageSystemSave(PMSG_REQ_RAGESYSTEM_SAVE *aRecv);

	void	DG_CreateonBankLoad(PMSG_REQ_CREATEON_LOAD *aRecv, int uIndex);
	void	GD_CreateonBankSave(PMSG_REQ_CREATEON_SAVE *aRecv);

	void	GD_TvTInfo(PMSG_TVTGD_INFO* aRecv);

	void	DG_AchievementsLoad(PMSG_GDREQ_ACH_LOAD* aRecv, int uIndex);
	void	GD_AchievementsSave(PMSG_GDREQ_ACH_SAVE* aRecv);

	void	GD_OfflineAfk(PMSG_REQ_OFFLINE_AFK* lpMsg);

	void	DG_VoteBuffLoad(PMSG_REQ_VOTEBUFF_LOAD *aRecv, int uIndex);
	void	GD_VoteBuffSave(PMSG_REQ_VOTEBUFF_SAVE *aRecv);

	void	DG_ExQuestSystemLoad(PMSG_REQ_EXQUESTSYSTEM_LOAD *aRecv, int uIndex);
	void	GD_ExQuestSystemSave(PMSG_REQ_EXQUESTSYSTEM_SAVE *aRecv);

	CQuery	m_DBQuery;
	CQuery  m_MEMBQuery;
};
extern CExGDManager g_ExGDManager;