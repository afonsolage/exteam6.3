#include "StdAfx.h"
#include "user.h"

#define Reset_DIR "..\\Data\\ExData\\Reset.ini"
#define RESET_EXP_MAX_RES 1000

struct GC_RESET_DATA
{
	PBMSG_HEAD2	h;
	BYTE Result;
	WORD Reset;
	WORD NeedLevel;
	DWORD NeedMoney;
	DWORD RewardPoint;
	WORD AddCredits;
	WORD AddWcoinC;
	WORD AddWcoinP;
	WORD AddWcoinG;
	DWORD ExFreePoint;
};

class cResetSystem
{
public:

	int EnableResetSystem;
	int Maxres;
	int NeedLevel;
	//int NeedLevelVip;

	int AddCredits;
	int AddWcoinC;
	int AddWcoinP;
	int AddGoblinPoint;

	char CommandReset[100];

	struct 
	{
		int Res;
		int Exp;
	}ExpRes[RESET_EXP_MAX_RES];
	int expCount;

	struct
	{
		int Res;
		int	Point;
	}PointRes[RESET_EXP_MAX_RES];
	int pointCount;

	struct
	{
		int Res;
		int	Zen;
	}ZenRes[RESET_EXP_MAX_RES];
	int zenCount;

	void Load();
	void ExResetSystemFunciton(int aIndex);
	int Main(LPOBJ lpObj);
#if(ADD_RESET_WINDOW)
	bool NpcDialog(int aIndex, int aNpcIndex);
	void GCDialogInfo(int aIndex);
	void CGResulInfo(int aIndex);
	void CGResetMenu(int aIndex);

	int GetExpRate(int aIndex);
	int GetNeedZen(int aIndex);
	int GetNeedLevel(int aIndex);
	int GetAddPoints(int aIndex);

	int Reset_NPC_ID;
	int Reset_NPC_MAP;
	int Reset_NPC_X;
	int Reset_NPC_Y;
#endif
};
extern cResetSystem gResetSystem;
