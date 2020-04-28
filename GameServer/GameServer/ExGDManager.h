#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"
#include "PartySearch.h"
#include "ExWinQuestSystem.h"
// -------------------------------------------------------------------------------

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
	BYTE btPartySearch[PARTY_SEARCH_SIZE];
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

struct PMSG_REQ_SERVERINFO_EX
{
	PBMSG_HEAD2 h;
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
#if(CUSTOM_EX_QUEST_SYSTEM)
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
#endif
// -------------------------------------------------------------------------------

class CExGDManager
{
public:
		 CExGDManager();
		 ~CExGDManager();

	void Protocol(BYTE protoNum, BYTE *aRecv);

	void DB_Start();
	void DB_Load(int aIndex);
	void DB_Save(int aIndex);

	void GD_PartySearchLoad(int aIndex);
	void DG_PartySearchLoad(PMSG_ANS_PARTYSEARCH_LOAD *aRecv);
	void GD_PartySearchSave(int aIndex);
			
#if(CUSTOM_NPC_BUFFER==TRUE)
	void GD_ExBuffLoad(int aIndex);
	void DG_ExBuffLoad(PMSG_ANS_EXBUFF_LOAD *aRecv);
	void GD_ExBuffSave(int aIndex);
#endif
	void GD_BMQuestLoad(int aIndex);
	void DG_BMQuestLoad(PMSG_ANS_BMQUEST_LOAD *aRecv);
	void GD_BMQuestSave(int aIndex);

	void GD_MonsterQuestLoad(int aIndex);
	void DG_MonsterQuestLoad(PMSG_ANS_MONSTERQUEST_LOAD *aRecv);
	void GD_MonsterQuestSave(int aIndex);

	void GD_RageSystemLoad(int aIndex);
	void DG_RageSystemLoad(PMSG_ANS_RAGESYSTEM_LOAD *aRecv);
	void GD_RageSystemSave(int aIndex);

	void GD_CreateonBankLoad(int aIndex);
	void DG_CreateonBankLoad(PMSG_ANS_CREATEON_LOAD *aRecv);
	void GD_CreateonBankSave(int aIndex);

	void GD_OfflineAfk(int aIndex, BYTE ConnectType, BYTE OfflineType);

	void GD_VoteBuffLoad(int aIndex);
	void DG_VoteBuffLoad(PMSG_ANS_VOTEBUFF_LOAD *aRecv);
	void GD_VoteBuffSave(int aIndex);
#if(CUSTOM_EX_QUEST_SYSTEM)
	void GD_ExQuestSystemLoad(int aIndex);
	void DG_ExQuestSystemLoad(PMSG_ANS_EXQUESTSYSTEM_LOAD *aRecv);
	void GD_ExQuestSystemSave(int aIndex);
#endif
};
extern CExGDManager	g_ExGDManager;