#pragma once

#include "user.h"

#define CRYWOLF_STATUE_CHECK(iClass) ( ( ((iClass)) == 204 )?TRUE:FALSE)

class CCrywolfShield
{
public:
	CCrywolfShield()
	{
		this->Reset();
	}

	void Reset()
	{
		this->m_iPriestNumber = 0;
		this->m_iShieldHP = 0;	
		this->m_iShieldMaxHP = 0;	
		this->m_iShieldState = 0;	
	}
		
	int GetHPPercentage()
	{
		if ( this->m_iShieldMaxHP )
		{
			return (this->m_iShieldHP * 100) / this->m_iShieldMaxHP;
		}

		return 0;
	}

public:
	int m_iShieldMaxHP;	// 0
	int m_iShieldHP;	// 4
	int m_iShieldState;	// 8
	int m_iPriestNumber;	// C
};

class CCrywolfStatue 
{
	
public:
	CCrywolfStatue();
	virtual ~CCrywolfStatue();

	void CrywolfStatueAct(int iIndex);
	int GetStatueViewState(int iPriestNumber);
	void SetStatueViewState(LPOBJ lpObj, int iAltarNumber);

public:

	CCrywolfShield m_Shield;	// 4

};

extern CCrywolfStatue g_CrywolfNPC_Statue;

