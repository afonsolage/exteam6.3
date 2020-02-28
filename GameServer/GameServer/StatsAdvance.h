#pragma once

#if(DEV_STATS_ADVANCE)

struct STATS_ADVANCE_DATA
{
	int Level;
	int MasterLevel;
	int Reset;
	int GrandReset;
	int TotalDamageReflect;
	int FullDamageReflectRate;
	int CriticalDamageRate;
	int CriticalDamagePower;
	int ExellentDamageRate;
	int ExellentDamagePower;
	int DoubleDamageRate;
	int TripleDamageRate;
	int DamageReductionRate;
	int ShieldSkillDamageReductionRate;
	int SDDamageReductionRate;
	int SDDecreaseDamageRate;
	int IgnoreDefenceRate;
	int IgnoreSDRate;
	int IncreaseDamagePvP;
	int IncreaseDefencePvP;
	int ResistDoubleDamageRate;
	int ResistIgnoreDefenceRate;
	int ResistIgnoreSDRate;
	int ResistCriticalDamageRate;
	int ResistExellentDamageRate;
	int ResistStumRate;
	int ResistIce;
	int ResistPoison;
	int ResistLighting;
	int ResistFire;
	int ResistEarth;
	int ResistWind;
	int ResistWater;
	int FullHPRestoreRate;
	int FullMPRestoreRate;
	int FullSDRestoreRate;
};

struct PMSG_STATS_ADVANCE
{
	PBMSG_HEAD2 h;
	BYTE Result;
	STATS_ADVANCE_DATA StatInfo;
};


class CStatsAdvance
{
public:
		CStatsAdvance();
		~CStatsAdvance();

	void Load();
	void Send(int aIndex);

	int m_Enable;
};

extern CStatsAdvance g_StatsAdvance;

#endif