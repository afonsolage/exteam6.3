#include "stdafx.h"
#ifdef BOSS_REWARD_ITEM


#define BOSS_REWARD_DIR	"..\\Data\\ExData\\BossRewardItem.ini"
#define MAX_DROP_ITEM	1000

#include "User.h"

class cBossRewardItem
{
public:
	void Init();
	bool ProccessItemDrop(LPOBJ lpMobObj);
	
private:
	int Enable;
	
	int DropCount;
	struct 
	{
		int MonsterID;
		int Type;
		int Index;
		int MinLevel;
		int MaxLevel;
		int Dur;
		int OptionRate;
		int MaxOption;
		int LuckRate;
		int LuckOption;
		int SkillRate;
		int SkillOption;
		int ExlRate;
		int ExlOption;
		int AncRate;
		int AncOption;
		int ItemDropRate;
	}Drop[MAX_DROP_ITEM];

	int BlockCount;
	struct
	{
		int Type;
		int Index;
	}Block[MAX_DROP_ITEM];
};

extern cBossRewardItem gBossRewardItem;


#endif // BOSS_REWARD_ITEM
