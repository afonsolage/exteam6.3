// SkillAdditionInfo.h: interface for the CSkillAdditionInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKILLADDITIONINFO_H__6698BD5D_64C0_4EB5_8FE2_93B4993661F5__INCLUDED_)
#define AFX_SKILLADDITIONINFO_H__6698BD5D_64C0_4EB5_8FE2_93B4993661F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MagicDamage.h"

#define OTHER_SKILL_CM		"Skill"
#define OTHER_SKILL_DIR		"..\\Data\\ExData\\Skills.ini"

#define MASTER_SKILL_CM		"MasterSkill"
#define MASTER_SKILL_DIR	"..\\Data\\ExData\\MasterSkills.ini"


class CSkillAdditionInfo
{

public:

	CSkillAdditionInfo();
	virtual ~CSkillAdditionInfo();

	void Init();
	int Load(LPSTR lpszFileName);
	short GetSoulBarrierManaRateLevel(int iLevel);

	//Main CPP
	void SetInfinityArrowSkillTime(int iValue){this->m_iInfinityArrowSkillTime = iValue;}
	int GetInfinityArrowSkillTime(){return this->m_iInfinityArrowSkillTime;}
	void SetInfinityArrowUseLevel(int iValue){this->m_iInfinityArrowUseLevel = iValue;}
	int GetInfinityArrowUseLevel(){return this->m_iInfinityArrowUseLevel;}
	void SetInfinityArrowMPConsumptionPlus0(int iValue){this->m_iInfinityArrowMPConsumptionPlus0 = iValue;}
	int GetInfinityArrowMPConsumptionPlus0(){return this->m_iInfinityArrowMPConsumptionPlus0;}
	void SetInfinityArrowMPConsumptionPlus1(int iValue){this->m_iInfinityArrowMPConsumptionPlus1 = iValue;}
	int GetInfinityArrowMPConsumptionPlus1(){return this->m_iInfinityArrowMPConsumptionPlus1;}
	void SetInfinityArrowMPConsumptionPlus2(int iValue){this->m_iInfinityArrowMPConsumptionPlus2 = iValue;}
	int GetInfinityArrowMPConsumptionPlus2(){return this->m_iInfinityArrowMPConsumptionPlus2;}
	void SetInfinityArrowMPConsumptionPlus3(int iValue){this->m_iInfinityArrowMPConsumptionPlus3 = iValue;}
	int GetInfinityArrowMPConsumptionPlus3(){return this->m_iInfinityArrowMPConsumptionPlus3;}
	void SetFireScreamSkill(int iValue){this->m_bFireScreamSkill = iValue;}
	BOOL GetFireScreamSkill(){return this->m_bFireScreamSkill;}
	void SetFireScreamExplosionAttackDistance(int iValue){this->m_iFireScreamExplosionAttackDistance = iValue;}
	int GetFireScreamExplosionAttackDistance(){return this->m_iFireScreamExplosionAttackDistance;}
	void SetFireScreamExplosionRate(int iValue){this->m_iFireScreamExplosionRate = iValue;}
	int GetFireScreamExplosionRate(){return this->m_iFireScreamExplosionRate;}
	void SetFireScreamMaxAttackCountSameSerial(int iValue){this->m_iFireScreamMaxAttackCountSameSerial = iValue;}
	int GetFireScreamMaxAttackCountSameSerial(){return this->m_iFireScreamMaxAttackCountSameSerial;}
	void SetFireScreamSerialInitCount(int iValue){this->m_iFireScreamSerialInitCount = iValue;}
	int GetFireScreamSerialInitCount(){return this->m_iFireScreamSerialInitCount;}
	void SetCheckFireScreamSkill(int iValue){this->m_bCheckFireScreamSerial = iValue;}
	BOOL GetCheckFireScreamSkill(){return this->m_bCheckFireScreamSerial;}

private:

	int m_iInfinityArrowSkillTime;	// 4
	int m_iInfinityArrowUseLevel;	// 8
	int m_iInfinityArrowMPConsumptionPlus0;	// C
	int m_iInfinityArrowMPConsumptionPlus1;	// 10
	int m_iInfinityArrowMPConsumptionPlus2;	// 14
	int m_iInfinityArrowMPConsumptionPlus3;	// 18
	BOOL m_bFireScreamSkill;	// 1C
	int m_iFireScreamExplosionAttackDistance;	// 20
	int m_iFireScreamExplosionRate;	// 24
	int m_iFireScreamMaxAttackCountSameSerial;	// 28
	int m_iFireScreamSerialInitCount;	// 2C
	BOOL m_bCheckFireScreamSerial;	// 30

	short m_wSoulBarrierManaRateLevel[20];

public:
	int		m_SkillUseReqLevel[MAX_SKILL];

	WORD	SoulBarrierDefenseStart;
	WORD	SoulBarrierDefenseDiv1;
	WORD	SoulBarrierDefenseDiv2;
	DWORD	SoulBarrierDefenseMax;
	WORD	SoulBarrierTimeStart;
	WORD	SoulBarrierTimeDiv;
	DWORD	SoulBarrierTimeMax;
	WORD	WizardryEnchantDamageDiv;
	float	WizardryEnchantDamageFact;
	DWORD	WizardryEnchantDamageMax;
	DWORD	WizardryEnchantTime;
	WORD	SwellLifeEffectStart;
	WORD	SwellLifeEffectDiv1;
	WORD	SwellLifeEffectDiv2;
	DWORD	SwellLifeEffectMax;
	WORD	SwellLifeTimeStart;
	WORD	SwellLifeTimeDiv;
	DWORD	SwellLifeTimeMax;
	WORD	ElfDefenseEffectFact;
	WORD	ElfDefenseEffectDiv;
	DWORD	ElfDefenseEffectMax;
	DWORD	ElfDefenseTime;
	WORD	ElfAttackEffectFact;
	WORD	ElfAttackEffectDiv;
	DWORD	ElfAttackEffectMax;
	DWORD	ElfAttackTime;
	WORD	CriticalDamageEffectDiv1;
	WORD	CriticalDamageEffectDiv2;
	WORD	CriticalDamageEffectMax;
	WORD	CriticalDamageTimeStart;
	WORD	CriticalDamageTimeDiv;
	DWORD	CriticalDamageTimeMax;
	WORD	BerserkerManaIncDiv;
	WORD	BerserkerLifeDecDiv;
	WORD	BerserkerTimeStart;
	WORD	BerserkerTimeDiv;
	DWORD	BerserkerTimeMax;
	WORD	BerserkerProcentDamageMax;
	WORD	BerserkerDefenceDivProcent;
	WORD	ReflectEffectStart;
	WORD	ReflectEffectDiv;
	DWORD	ReflectEffectMax;
	WORD	ReflectTimeStart;
	WORD	ReflectTimeDiv;
	DWORD	ReflectTimeMax;
	WORD	IgnoreDefenseEffectStart;
	WORD	IgnoreDefenseEffectSub;
	WORD	IgnoreDefenseEffectDiv;
	DWORD	IgnoreDefenseEffectMax;
	WORD	IgnoreDefenseTimeStart;
	WORD	IgnoreDefenseTimeDiv;
	DWORD	IgnoreDefenseTimeMax;
	WORD	IncreaseHealthEffectStart;
	WORD	IncreaseHealthEffectSub;
	float	IncreaseHealthEffectDiv;
	DWORD	IncreaseHealthEffectMax;
	WORD	IncreaseHealthTimeStart;
	WORD	IncreaseHealthTimeDiv;
	DWORD	IncreaseHealthTimeMax;
	WORD	IncreaseBlockEffectStart;
	WORD	IncreaseBlockEffectSub;
	WORD	IncreaseBlockEffectDiv;
	DWORD	IncreaseBlockEffectMax;
	WORD	IncreaseBlockTimeStart;
	WORD	IncreaseBlockTimeDiv;
	DWORD	IncreaseBlockTimeMax;
	WORD	WeaknessEffectStartVsMob;
	WORD	WeaknessEffectDivVsMob;
	WORD	WeaknessEffectMaxVsMob;
	WORD	WeaknessTimeStartVsMob;
	WORD	WeaknessTimeDivVsMob;
	WORD	WeaknessTimeMaxVsMob;
	WORD	WeaknessEffectStartVsUser;
	WORD	WeaknessEffectDivVsUser;
	WORD	WeaknessEffectMaxVsUser;
	WORD	WeaknessTimeStartVsUser;
	WORD	WeaknessTimeDivVsUser;
	WORD	WeaknessTimeMaxVsUser;
	WORD	WeaknessMaxPower;
	WORD	InnovationEffectStartVsMob;
	WORD	InnovationEffectDivVsMob;
	WORD	InnovationEffectMaxVsMob;
	WORD	InnovationTimeStartVsMob;
	WORD	InnovationTimeDivVsMob;
	WORD	InnovationTimeMaxVsMob;
	WORD	InnovationEffectStartVsUser;
	WORD	InnovationEffectDivVsUser;
	WORD	InnovationEffectMaxVsUser;
	WORD	InnovationTimeStartVsUser;
	WORD	InnovationTimeDivVsUser;
	WORD	InnovationTimeMaxVsUser;
	WORD	InnovationMaxPower;
	WORD	SleepRateStartVsMob;
	WORD	SleepRateDivVsMob;
	WORD	SleepRateMaxVsMob;
	WORD	SleepTimeStartVsMob;
	WORD	SleepTimeDivVsMob;
	WORD	SleepTimeMaxVsMob;
	WORD	SleepRateStartVsUser;
	WORD	SleepRateDivVsUser;
	WORD	SleepRateMaxVsUser;
	WORD	SleepTimeStartVsUser;
	WORD	SleepTimeDivVsUser;
	WORD	SleepTimeMaxVsUser;
	// ----
	WORD	m_SoulBarrierDefenseStart;
	WORD	m_SoulBarrierDefenseDiv1;
	WORD	m_SoulBarrierDefenseDiv2;
	DWORD	m_SoulBarrierDefenseMax;
	WORD	m_SoulBarrierTimeStart;
	WORD	m_SoulBarrierTimeDiv;
	DWORD	m_SoulBarrierTimeMax;
	WORD	m_WizardryEnchantDamageDiv;
	float	m_WizardryEnchantDamageFact;
	DWORD	m_WizardryEnchantDamageMax;
	DWORD	m_WizardryEnchantTime;
	WORD	m_SwellLifeEffectStart;
	WORD	m_SwellLifeEffectDiv1;
	WORD	m_SwellLifeEffectDiv2;
	DWORD	m_SwellLifeEffectMax;
	WORD	m_SwellLifeTimeStart;
	WORD	m_SwellLifeTimeDiv;
	DWORD	m_SwellLifeTimeMax;
	WORD	m_ElfDefenseEffectFact;
	WORD	m_ElfDefenseEffectDiv;
	DWORD	m_ElfDefenseEffectMax;
	DWORD	m_ElfDefenseTime;
	WORD	m_ElfAttackEffectFact;
	WORD	m_ElfAttackEffectDiv;
	DWORD	m_ElfAttackEffectMax;
	DWORD	m_ElfAttackTime;
	WORD	m_CriticalDamageEffectDiv1;
	WORD	m_CriticalDamageEffectDiv2;
	WORD	m_CriticalDamageEffectMax;
	WORD	m_CriticalDamageTimeStart;
	WORD	m_CriticalDamageTimeDiv;
	DWORD	m_CriticalDamageTimeMax;
	WORD	m_BerserkerManaIncDiv;
	WORD	m_BerserkerLifeDecDiv;
	WORD	m_BerserkerTimeStart;
	WORD	m_BerserkerTimeDiv;
	DWORD	m_BerserkerTimeMax;
	WORD	m_BerserkerProcentDamageMax;
	WORD	m_BerserkerDefenceDivProcent;
	WORD	m_ReflectEffectStart;
	WORD	m_ReflectEffectDiv;
	DWORD	m_ReflectEffectMax;
	WORD	m_ReflectTimeStart;
	WORD	m_ReflectTimeDiv;
	DWORD	m_ReflectTimeMax;
	WORD	m_IgnoreDefenseEffectStart;
	WORD	m_IgnoreDefenseEffectSub;
	WORD	m_IgnoreDefenseEffectDiv;
	DWORD	m_IgnoreDefenseEffectMax;
	WORD	m_IgnoreDefenseTimeStart;
	WORD	m_IgnoreDefenseTimeDiv;
	DWORD	m_IgnoreDefenseTimeMax;
	WORD	m_IncreaseHealthEffectStart;
	WORD	m_IncreaseHealthEffectSub;
	float	m_IncreaseHealthEffectDiv;
	DWORD	m_IncreaseHealthEffectMax;
	WORD	m_IncreaseHealthTimeStart;
	WORD	m_IncreaseHealthTimeDiv;
	DWORD	m_IncreaseHealthTimeMax;
	WORD	m_IncreaseBlockEffectStart;
	WORD	m_IncreaseBlockEffectSub;
	WORD	m_IncreaseBlockEffectDiv;
	DWORD	m_IncreaseBlockEffectMax;
	WORD	m_IncreaseBlockTimeStart;
	WORD	m_IncreaseBlockTimeDiv;
	DWORD	m_IncreaseBlockTimeMax;
	//WORD	m_WeaknessEffectStartVsMob;
	//WORD	m_WeaknessEffectDivVsMob;
	//WORD	m_WeaknessEffectMaxVsMob;
	//WORD	m_WeaknessTimeStartVsMob;
	//WORD	m_WeaknessTimeDivVsMob;
	//WORD	m_WeaknessTimeMaxVsMob;
	//WORD	m_WeaknessEffectStartVsUser;
	//WORD	m_WeaknessEffectDivVsUser;
	//WORD	m_WeaknessEffectMaxVsUser;
	//WORD	m_WeaknessTimeStartVsUser;
	//WORD	m_WeaknessTimeDivVsUser;
	//WORD	m_WeaknessTimeMaxVsUser;
	//WORD	m_InnovationEffectStartVsMob;
	//WORD	m_InnovationEffectDivVsMob;
	//WORD	m_InnovationEffectMaxVsMob;
	//WORD	m_InnovationTimeStartVsMob;
	//WORD	m_InnovationTimeDivVsMob;
	//WORD	m_InnovationTimeMaxVsMob;
	//WORD	m_InnovationEffectStartVsUser;
	//WORD	m_InnovationEffectDivVsUser;
	//WORD	m_InnovationEffectMaxVsUser;
	//WORD	m_InnovationTimeStartVsUser;
	//WORD	m_InnovationTimeDivVsUser;
	//WORD	m_InnovationTimeMaxVsUser;
	WORD	m_SleepRateStartVsMob;
	WORD	m_SleepRateDivVsMob;
	WORD	m_SleepRateMaxVsMob;
	WORD	m_SleepTimeStartVsMob;
	WORD	m_SleepTimeDivVsMob;
	WORD	m_SleepTimeMaxVsMob;
	WORD	m_SleepRateStartVsUser;
	WORD	m_SleepRateDivVsUser;
	WORD	m_SleepRateMaxVsUser;
	WORD	m_SleepTimeStartVsUser;
	WORD	m_SleepTimeDivVsUser;
	WORD	m_SleepTimeMaxVsUser;
};


extern CSkillAdditionInfo g_SkillAdditionInfo;

#endif // !defined(AFX_SKILLADDITIONINFO_H__6698BD5D_64C0_4EB5_8FE2_93B4993661F5__INCLUDED_)
