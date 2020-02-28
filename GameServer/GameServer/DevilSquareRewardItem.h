#pragma once

#include "StdAfx.h"
#define DS_REWARD_ITEM_DIR	"..\\Data\\ExData\\DevilSquareRewardItem.ini"
#define MAX_DS_REWARD_ITEM 200
struct REWARD_ITEM
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
class cDevilSquareRewardItem
{
public:
	
	void Load();
	void Main(int);

	int Enable;
	REWARD_ITEM Reward[MAX_DS_REWARD_ITEM][8];

	int Count[8];
	int m_iRewardItemCount;
};

extern cDevilSquareRewardItem gDevilSquareRewardItem;


