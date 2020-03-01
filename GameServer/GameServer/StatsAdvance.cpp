#include "StdAfx.h"
#include "user.h"
#include "protocol.h"
#include "StatsAdvance.h"
#include "CustomSystem.h"

#if(DEV_STATS_ADVANCE)

CStatsAdvance g_StatsAdvance;

CStatsAdvance::CStatsAdvance()
{
	this->m_Enable = false;
}

CStatsAdvance::~CStatsAdvance()
{
}

void CStatsAdvance::Load()
{
	this->m_Enable = false;

	if(g_CustomSystem.IsStatsAdvance())
	{
		this->m_Enable = true;
	}
}

void CStatsAdvance::Send(int aIndex)
{
	if(!this->m_Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_STATS_ADVANCE pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xDA, sizeof(pMsg));

	pMsg.Result = true;

	pMsg.StatInfo.Level = lpUser->Level;
	pMsg.StatInfo.MasterLevel = 0;
	pMsg.StatInfo.Reset = lpUser->Reset;
	pMsg.StatInfo.GrandReset = lpUser->GReset;
	pMsg.StatInfo.TotalDamageReflect = lpUser->DamageReflect;
	pMsg.StatInfo.FullDamageReflectRate = lpUser->DamageReflect;
	pMsg.StatInfo.CriticalDamageRate = lpUser->m_CriticalDamage;
	pMsg.StatInfo.CriticalDamagePower = lpUser->m_CriticalDamage;
	pMsg.StatInfo.ExellentDamageRate = lpUser->m_ExcelentDamage;
	pMsg.StatInfo.ExellentDamagePower = lpUser->m_ExcelentDamage;
	pMsg.StatInfo.DoubleDamageRate = lpUser->SetOpDoubleDamage;
	pMsg.StatInfo.TripleDamageRate = 0;
	pMsg.StatInfo.DamageReductionRate = lpUser->DamageMinus;
	pMsg.StatInfo.ShieldSkillDamageReductionRate = 0;
	pMsg.StatInfo.SDDamageReductionRate = 0;
	pMsg.StatInfo.SDDecreaseDamageRate = 0;
	pMsg.StatInfo.IgnoreDefenceRate = lpUser->SetOpIgnoreDefense;
	pMsg.StatInfo.IgnoreSDRate = 0;
	pMsg.StatInfo.IncreaseDamagePvP = 0;
	pMsg.StatInfo.IncreaseDefencePvP = 0;
	pMsg.StatInfo.ResistDoubleDamageRate = 0;
	pMsg.StatInfo.ResistIgnoreDefenceRate = 0;
	pMsg.StatInfo.ResistIgnoreSDRate = 0;
	pMsg.StatInfo.ResistCriticalDamageRate = 0;
	pMsg.StatInfo.ResistExellentDamageRate = 0;
	pMsg.StatInfo.ResistStumRate = 0;
	pMsg.StatInfo.ResistIce = lpUser->m_Resistance[R_ICE];
	pMsg.StatInfo.ResistPoison = lpUser->m_Resistance[R_POISON];
	pMsg.StatInfo.ResistLighting = lpUser->m_Resistance[R_LIGHTNING];
	pMsg.StatInfo.ResistFire = lpUser->m_Resistance[R_FIRE];
	pMsg.StatInfo.ResistEarth = lpUser->m_Resistance[R_EARTH];
	pMsg.StatInfo.ResistWind = lpUser->m_Resistance[R_WIND];
	pMsg.StatInfo.ResistWater = lpUser->m_Resistance[R_WATER];
	pMsg.StatInfo.FullHPRestoreRate = 0;
	pMsg.StatInfo.FullMPRestoreRate = 0;
	pMsg.StatInfo.FullSDRestoreRate = 0;

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

#endif