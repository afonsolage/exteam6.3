#include "StdAfx.h"
#include "user.h"

#if(SYSTEMOF_BROTHER==TRUE)
//Experience +10%%/Drop Zen +10%%/Damage +10%%/Defence +10%%/Ignore Defence +5%%/Double Damage + 5%%
//#define BR_DEBUG

#define Brotherhood_DIR "..\\Data\\ExData\\Brotherhood.txt"

struct GD_CheckBrother
{
	PBMSG_HEAD2 h;
	int aIndex;
	int aTargetIndex;
	char BrName[11];
};

struct DG_CheckBrother
{
	PBMSG_HEAD2 h;
	int aIndex;
	int aTargetIndex;
	int Count;
	
};

class Brotherhood
{
private:
	bool Enable;
	int PlusExp;
	int PlusZen;

	int PlusDamage;
	int PlusDefence;
	int PlusIgnore;
	int PlusDoubleDamage;

	int BuyType;
	int BuyCost;

	int TeleportActive;
	int ExitActive;

	int DropCount;
	struct 
	{
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
		int MonsterMinLevel;
		int MonsterMaxLevel;
		int MonsterMap;
		int ItemDropRate;
	}Drop[1000];

public:
	void Load();
	bool ActiveBrother(LPOBJ lpObj);
	void UserExp(LPOBJ lpObj, __int64 & Exp);
	void UserBonusZen(LPOBJ lpObj, float & money);
	bool ProccessItemDrop(LPOBJ lpMobObj, LPOBJ lpTargetObj);
	void CharacterAdded(LPOBJ lpObj);

	void Teleport(LPOBJ lpObj, int TargetIndex);
	void UserConnect(int aIndex);
	bool CheckSimbol(char* String);
	void UserAddedBrother(int aIndex, char* BrName);
	void UserExitBrother(int aIndex);
	void TickTime(int aIndex);
	bool NewAddBrother(int aIndex, int TargetIndex);
	void DG_RecvBrotherCount(DG_CheckBrother* Recv);
	#if(BROTHER_PAYTELEPORT)
	int m_TeleportWCoin;
	#endif
};
extern Brotherhood gBrotherhood;

#endif