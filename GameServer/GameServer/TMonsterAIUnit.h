#pragma once

#include "TmonsterAIAutomata.h"
#include "TMonsterAIElement.h"

#define MAX_MONSTER_AI_UNIT	(100)

class TMonsterAIUnit  
{

public:

	TMonsterAIUnit();
	virtual ~TMonsterAIUnit();

	int RunAIUnit(int iIndex);
	void Reset();

	static int LoadData(char* lpszFileName);
	static int DelAllAIUnit();
	static TMonsterAIUnit* FindAIUnit(int iUnitNumber);

public:

	char m_szUnitName[50];	// 4
	int m_iUnitNumber;	// 38
	int m_iDelayTime;	// 3C
	TMonsterAIAutomata* m_lpAutomata;	// 40
	TMonsterAIElement* m_lpAIClassNormal;	// 44
	TMonsterAIElement* m_lpAIClassMove;	// 48
	TMonsterAIElement* m_lpAIClassAttack;	// 4C
	TMonsterAIElement* m_lpAIClassHeal;	// 50
	TMonsterAIElement* m_lpAIClassAvoid;	// 54
	TMonsterAIElement* m_lpAIClassHelp;	// 58
	TMonsterAIElement* m_lpAIClassSpecial;	// 5C
	TMonsterAIElement* m_lpAIClassEvent;	// 60
	TMonsterAIElement** m_lppAIClassMap[8];	// 64

	static BOOL s_bDataLoad;
	static TMonsterAIUnit s_MonsterAIUnitArray[MAX_MONSTER_AI_UNIT];
};
