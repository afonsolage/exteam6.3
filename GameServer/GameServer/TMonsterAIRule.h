#pragma once

#include "TMonsterAIRuleInfo.h"

#define MAX_MONSTER_AI_RULE_INFO	(200)
#define MAX_MONSTER_AI_RULE_TABLE	(1000)	//(500)	//Season 5 ImperialFort

class TMonsterAIRule  
{

public:

	TMonsterAIRule();
	virtual ~TMonsterAIRule();

	static BOOL LoadData(char* lpszFileName);
	static BOOL DelAllAIRule();
	static int GetCurrentAIUnit(int iMonsterClass);
	static void MonsterAIRuleProc();

public:

	static BOOL s_bDataLoad;
	static int s_iMonsterCurrentAIUnitTable[MAX_MONSTER_AI_RULE_TABLE];
	static TMonsterAIRuleInfo s_MonsterAIRuleInfoArray[MAX_MONSTER_AI_RULE_INFO];
	static int s_iMonsterAIRuleInfoCount;

};