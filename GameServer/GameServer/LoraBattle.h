#include "user.h"
#include "StdAfx.h"

#define LORABATTLE_DIR "..\\Data\\ExData\\Events\\LoraBattleEvent.ini"

class cLoraBattle
{
public:
		cLoraBattle();
		~cLoraBattle();
	int Enable;
	int Start;

	
	int RewardItem;

	int RewardWCoinC;
	int RewardWCoinP;
	int RewardGoblin;
	int RewardExCred;

	int RewardItemDropType;
	int RewardItemDropID;
	int RewardItemDropLevel;
	int RewardItemDropSkill;
	int RewardItemDropLuck;
	int RewardItemDropOpt;
	int RewardItemDropExcOpt;
	int RewardItemDropAncOpt;

	int Fallen_DROP;

	int FallenItemDropType;
	int FallenItemDropID;
	int FallenItemDropLevel;
	int FallenItemDropSkill;
	int FallenItemDropLuck;
	int FallenItemDropOpt;
	int FallenItemDropExcOpt;
	int FallenItemDropAncOpt;

	int KillSocer[OBJMAX];

	bool BattleRing[OBJMAX];

	int m_PK_Level[OBJMAX];

	int MaxSocer;
	int MaxIndex;

	char MSG[256];

	void LoadConfigs();
	void StartEvent();
	void EndEvent();
	void TickTime();
	void Process(int aIndex);
	void BattleKillSocer(int aIndex,int aIndex2);
	void Reward(int aIndex);
	void Start1min();
	bool PkCheck(LPOBJ lpObj, LPOBJ lpTarget);
	int ReturnStatus(int aIndex, int TargetIndex);
	bool CheckStartEvent();
	bool CheckGateEvent(int aIndex);

	struct
	{
		int StrHour;
		int StrMin;
		int Hour;
		int Min;
		int EndHour;
		int EndMin;
	}Time[128];

	int Count;
	int EndCount;
};
extern cLoraBattle LoraBattle;