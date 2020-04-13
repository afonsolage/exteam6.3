#pragma once

#include "TMonsterAIState.h"

#define MAX_MONSTER_AI_AUTOMATA	300
#define MAX_AI_STATE			8
#define MAX_AI_PRIORITY			30

#define MAX_AI_STATE_RANGE(x) ( ( (x)< 0)?FALSE:((x) > MAX_AI_STATE-1 )? FALSE : TRUE  )

class TMonsterAIAutomata  
{

public:

	TMonsterAIAutomata();
	virtual ~TMonsterAIAutomata();

	TMonsterAIState* RunAutomata(int iIndex);
	void Reset();

	static BOOL LoadData(char* lpszFileName);
	static BOOL DelAllAutomata();
	static TMonsterAIAutomata* FindAutomata(int iAutomataNumber);
	static BOOL s_bDataLoad;
	static TMonsterAIAutomata s_MonsterAIAutomataArray[MAX_MONSTER_AI_AUTOMATA];

private:

	int m_iAutomataNumber;	// 4
	TMonsterAIState m_AIState[MAX_AI_STATE][MAX_AI_PRIORITY];	// 8
	int m_AIStateTransCount[MAX_AI_STATE];	// 7BC8


};