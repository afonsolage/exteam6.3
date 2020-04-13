#pragma once

class TMonsterAIGroupMember  
{

public:

	TMonsterAIGroupMember();
	virtual ~TMonsterAIGroupMember();

	void Reset();

public:

	int m_iGroupNumber;	// 4
	int m_iGuid;	// 8
	int m_iClass;	// C
	int m_iRank;	// 10
	int m_iStartAI;	// 14
	int m_iAI01;	// 18
	int m_iAI02;	// 1C
	int m_iAI03;	// 20
	int m_iCreateType;	// 24
	int m_iMapNumber;	// 28
	int m_iStartX;	// 2C
	int m_iStartY;	// 30
	int m_iStartDir;	// 34
	int m_iRegenType;	// 38
	int m_iObjIndex;	// 3C

};