#pragma once

#include "StdAfx.h"
#define BC_REWARD_ITEM_DIR	"..\\Data\\ExData\\BloodCastleRewardItem.ini"
#define MAX_BC_REWARD_ITEM 200
struct REWARD_BC_ITEM
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
class cBloodCastleRewardItem
{
public:
	
	void Load();
	bool Main(int);

	int Enable;
	REWARD_BC_ITEM Reward[MAX_BC_REWARD_ITEM][9];

	int Count[9];
	int m_iRewardItemCount;
};

extern cBloodCastleRewardItem gBloodCastleRewardItem;
