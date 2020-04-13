#pragma once

enum MONSTER_AI_RULEINFO_CONDITION {
  MAR_CONDITION_SPECIFIC_DATE = 0x1,
  MAR_CONDITION_CRYWOLF_START = 0x47,
  MAR_CONDITION_CRYWOLF_END = 0x48,
};

class TMonsterAIRuleInfo  
{

public:

	TMonsterAIRuleInfo();
	void Reset();
	int IsValid();
	int CheckConditionSpecificDate();
	int CheckConditionCrywolfStart();
	int CheckConditionCrywolfEnd();

public:

	int m_iRuleNumber;	// 0
	int m_iMonsterClass;	// 4
	int m_iMonsterAIUnit;	// 8
	int m_iRuleCondition;	// C
	int m_iWaitTime;	// 10
	int m_iContinuanceTime;	// 14
	int m_iMonth;	// 18
	int m_iDay;	// 1C
	int m_iWeekDay;	// 20
	int m_iHour;	// 24
	int m_iMinute;	// 28
	int m_iAppliedTime;	// 2C
	int m_iApplyingTime;	// 30
	char m_szRuleDesc[100];	// 34


};
