#pragma once
#include "stdafx.h"
#include "..\\common\\zzzitem.h"
#include "..\\include\\prodef.h"

#ifdef _WINGS_DAMAGE_

#define WingsDamage_DIR "..\\Data\\ExData\\WingsDamage.ini"

#define MAX_WINGS_ITEM 50

struct WING_INFO
{
	DWORD ItemType;
	DWORD Damage;
	DWORD Absord;
};

struct PMSG_WINGS_INFO
{
	PWMSG_HEAD2 h;
	WING_INFO Wing[MAX_WINGS_ITEM];
};

struct WingsData {
	int Type;
	int Index;
	int IncreaseDamage;
	int IncreaseDefence;
};

struct WINGSCHAR_DATA
{
	int Type;
	int Index;
	int AttackPercent;
	int AbsurdPercent;
};

class cWingsDamage 
{
private:
	WingsData Data[MAX_WINGS_ITEM];
	int Enable;
	int Count;

public:
	void Init();
	void Load();
	void Attack(int Wing, int& Damage);
	void Defence(int Wing, int& Damage);

	void SetCharWingAttack(int aIndex, int ItemType,  int ItemLevel, int& AttackDamage);
	void SetCharWingAbsurd(int aIndex, int ItemType, int ItemLevel, int& AttackDamage);
	void SetCharHorseAttack(int aIndex, int ItemType,  int ItemLevel, int& AttackDamage);

	void PlayerCalculator(int aIndex);
	
	bool m_bWingsCharacter;

	WINGSCHAR_DATA m_Wing[MAX_TYPE_PLAYER][MAX_WINGS_ITEM];
	int m_iWingCount[MAX_TYPE_PLAYER];

};

extern cWingsDamage gWingsDamage;

#endif