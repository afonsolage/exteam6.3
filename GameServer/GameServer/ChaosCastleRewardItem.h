#pragma once

#include "StdAfx.h"
#include "ChaosCastle.h"

#define CC_REWARD_ITEM_DIR	"..\\Data\\ExData\\ChaosCastleRewardItem.ini"

#define MAX_CC_REWARD_ITEM 200

struct REWARD_CC_ITEM
{
	int Type;
	int Index;
	int Level;
	int Skill;
	int Luck;
	int Opt;
	int Exl;
	int Anc;
};

class CChaosCastleRewardItem
{
public:
	void Load();
	bool Main(int aIndex, int ChaosCastleIndex);

	int Enable;

	REWARD_CC_ITEM Reward[MAX_CC_REWARD_ITEM][MAX_CHAOSCASTLE_LEVEL];
	int Count[MAX_CHAOSCASTLE_LEVEL];
};

extern CChaosCastleRewardItem gChaosCastleRewardItem;
