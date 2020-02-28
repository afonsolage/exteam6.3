#pragma once

#include "stdafx.h"

#if(NEW_HP_BAR)

#define MAX_MONSTER		1024

class ViewePortInfo
{
public:
	void Load();
	static void DrawPartyHP();
	void TargetMonsterHpBar();
	void AllMonsterHpBar();
	void TargetUserHpBar();
	void AllUserHpBar();
	void NewHpBarLoad();
	void InitNewHpBar();
	void PartyHPBar();
	bool CheckClass(int Number);
	void PlayerTitle();
};
extern ViewePortInfo gViewePortInfo;

#endif