#pragma once

#include "ImperialBattleUser.h"

#define MAX_IMPERIAL_BATTLE_USER	5

class CImperialBattleUserMng
{

public:

	CImperialBattleUserMng();
	virtual ~CImperialBattleUserMng();

	void ResetAllData();
	int AddUserData(int iIndex);
	int DeleteUserData(int iIndex);
	void CheckUserState();
	int MoveAllUser(int iGateNumber);
	int GetUserCount();
	int IsEmpty();
	int IsOverMaxUser();
	//int __thiscall IsBattleUser(int);
	void SetMaxUser(int iMaxUser);
	int GetMaxUser();
	BOOL CheckUserIsInEvent(int iIndex);
	void LogBattleWinnerUserInfo(BYTE btFlag, int iElapsedTime);

public:

	CImperialBattleUser m_BattleUser[MAX_IMPERIAL_BATTLE_USER];	// 4
	int m_iBattleUserCount;	// B8
	int m_iBattleMaxUser;	// BC

};


extern CImperialBattleUserMng g_ImperialBattleUserMng;