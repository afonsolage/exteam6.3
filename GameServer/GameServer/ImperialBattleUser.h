#pragma once

class CImperialBattleUser
{

public:

	CImperialBattleUser()
	{
		this->ResetData();
	}

	virtual ~CImperialBattleUser(){return;}
	
	void ResetData()
	{
		this->m_iIndex = -1;
		this->m_bIsUse = FALSE;
	}

	int GetIndex()
	{
		return this->m_iIndex;
	}

	void SetIndex(int iIndex)
	{
		this->m_iIndex = iIndex;
		this->m_bIsUse = TRUE;
	}

	BOOL IsUseData()
	{
		return this->m_bIsUse;
	}

private:

	int m_iIndex;	// 4
	BOOL m_bIsUse;	// 8

};