#pragma once

#include "StdAfx.h"
#include "user.h"

#define MAX_MOB_BONUS 100

#define MOB_BONUS_DIR "..\\Data\\ExData\\MonsterBonus.ini"

struct MonsterBonusData
{
	int MobID;
	int BonusType;
	int BonusCount;
	int MapNumber;
};

class cMonsterBonus
{
public:
	cMonsterBonus();
	~cMonsterBonus();
	void Load();
	void Main(LPOBJ lpMobObj, LPOBJ lpTargetObj);

private:
	bool Enable;
	MonsterBonusData MobData[MAX_MOB_BONUS];
	int Count;
};
extern cMonsterBonus gMonsterBonus;