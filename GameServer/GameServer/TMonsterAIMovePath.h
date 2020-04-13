#pragma once

#define MAX_MONSTER_AI_MOVE_PATH	(300)

class TMonsterAIMovePathInfo
{

public:

	int m_iType;	// 0
	int m_iMapNumber;	// 4
	int m_iPathX;	// 8
	int m_iPathY;	// C

public:

	TMonsterAIMovePathInfo()
	{
		this->Reset();
	}

	void Reset()
	{
		this->m_iType = -1;
		this->m_iMapNumber = -1;
		this->m_iPathX = -1;
		this->m_iPathY = -1;
	}
};


class TMonsterAIMovePath  
{
public:

	TMonsterAIMovePath();
	virtual ~TMonsterAIMovePath();

	int LoadData(char* lpszFileName);
	int DelAllAIMonsterMovePath();

public:

	BOOL m_bDataLoad;	// 4
	TMonsterAIMovePathInfo m_MovePathInfo[MAX_MONSTER_AI_MOVE_PATH];	// 8
	int m_iMovePathSpotCount;	// 12C8


};