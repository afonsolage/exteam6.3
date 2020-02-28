#include "StdAfx.h"

#define GrandReset_DIR "..\\Data\\ExData\\GrandReset.ini"

#if(ADD_GRAND_EXP)
struct GrandResetEXP
{
	short GrandReset;
	bool TypeExp;
	int MinusExp;
	GrandResetEXP()
	{
		this->GrandReset = 0;
		this->TypeExp = false;
		this->MinusExp = 0;
	}
};
#endif

struct PMSG_GRAND_DIALOG
{
	PBMSG_HEAD2	h;
	BYTE Result;
	WORD GrandNum;
	WORD GrandMax;
	WORD NeedReset;
	WORD NeedLevel;
	DWORD NeedMoney;
	DWORD RewardPoint;
	DWORD RewardWCoin;
	DWORD RewardCredit;
};

struct GRANDSYSTEM_DATA
{
	BYTE Result;
	WORD GrandNum;
	WORD GrandMax;
	WORD NeedReset;
	WORD NeedLevel;
	DWORD NeedMoney;
	DWORD RewardPoint;
};

struct GRANDSYSTEM_REWARD_DATA
{
	int ResetNum;
	int WcoinC;
	int Credit;
	bool EnableItem;
	int Type;
	int Index;
	int Level;
	bool Skill;
	bool Luck;
	bool Opt;
	bool Exl;
	bool Anc;
};

class cGrandReset
{
public:

	int EnableGrandResetSystem;	
	int MaxGrandRes;
	int ZenForm;
	int NeedZen;
	int NeedRes;
	int NeedLevel;
	int AddForm;
	int AddPointsDW;
	int AddPointsDK;
	int AddPointsELF;
	int AddPointsSUM;
	int AddPointsMG;
	int AddPointsDL;
	int AddPointsRF;
	int NeedEmptyInv;

	int AddCredits;
	int AddWcoinC;
	int AddWcoinP;
	int AddGoblinPoint;

	char CommandGrandReset[100];

	int AddWcoin;

	void Load();
	void ExGrandResetSystemFunciton(int aIndex);
#if(ADD_GRAND_EXP)
	bool EnableGrandDinamic;
	std::vector<GrandResetEXP> DataExp;
	int DinamicExp(int aIndex, int Experience);
#endif
	void CGGrandMenu(int aIndex);
	void GCDialogInfo(int aIndex);
	void CGGrandStart(int aIndex);

	int m_NpcClass;
	int m_NpcMap;
	int m_NpcX;
	int m_NpcY;

	int m_iMapForGrand;

	bool NpcDialog(int aIndex, int aNpcIndex);

	std::vector<GRANDSYSTEM_REWARD_DATA> m_reward;
};
extern cGrandReset gGrandReset;
