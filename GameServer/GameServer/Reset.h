#include "StdAfx.h"
#include "user.h"

#define Reset_DIR "..\\Data\\ExData\\Reset.ini"
#define RESET_EXP_MAX_RES 1000

struct GC_RESET_DATA
{
	PBMSG_HEAD2	h;
	BYTE Result;
	WORD Reset;
	WORD MaxReset;
	WORD NeedLevel;
	DWORD NeedMoney;
	DWORD RewardPoint;
	WORD AddCredits;
	WORD AddWcoinC;
	WORD AddWcoinP;
	WORD AddWcoinG;
	DWORD ExFreePoint;

	bool AddEnableItem;
	int AddItem;
	BYTE AddItemLevel;
	bool AddItemSkill;
	bool AddItemLuck;
	bool AddItemOpt;
	bool AddItemExl;
	bool AddItemAnc;
	BYTE AddItemCount;

	bool RewardEnableItem;
	int RewardItem;
	int RewardLevel;
	bool RewardSkill;
	bool RewardLuck;
	bool RewardOpt;
	bool RewardExl;
	bool RewardAnc;

};

#if(ADD_RESET_WINDOW)
struct RESET_NEEDITEM_DATA
{
	int ResetNum;
	int Type;
	int Index;
	int Level;
	bool Skill;
	bool Luck;
	bool Opt;
	bool Exl;
	bool Anc;
	int Count;
};

struct RESET_REWARD_DATA
{
	int ResetNum;
	int WcoinC;
	bool EnableItem;
	int Type;
	int Index;
	int Level;
	bool Skill;
	bool Luck;
	bool Opt;
	bool Exl;
	bool Anc;
	int Credit;
};
#endif

class cResetSystem
{
public:

	int EnableResetSystem;
	int Maxres;
	int ZenForm;
	int NeedZen;
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

	int m_iMapForReset;

	bool DinamicExp;

	char CommandReset[100];

	int NeedWCoinToReset;
	int NeedCreditToReset;


	struct 
	{
		int Res;
		int Exp;
	} Number[RESET_EXP_MAX_RES];
	int rCount;

	struct 
	{
		int Res;
		int ItemType;
		int ItemIndex;
		int ItemCount;
	} ItemsRes[RESET_EXP_MAX_RES];
	int iCount;
	struct
	{
		int Res;
		int	Level;
	}LevelRes[RESET_EXP_MAX_RES];
	int lCount;

	void Load();
	void ExResetSystemFunciton(int aIndex);
	//void Main(LPOBJ lpObj, __int64 & Experience);
	int Main(LPOBJ lpObj);
#if(ADD_RESET_WINDOW)
	bool NpcDialog(int aIndex, int aNpcIndex);
	void GCDialogInfo(int aIndex);
	void CGResulInfo(int aIndex);
	bool SearchItem(int aIndex, int Type, int Index, int Level, bool Skill, bool Luck, bool Opt, bool Exl, bool Anc, int count, bool del);
	void CGResetMenu(int aIndex);

	int Reset_NPC_ID;
	int Reset_NPC_MAP;
	int Reset_NPC_X;
	int Reset_NPC_Y;

	std::vector<RESET_NEEDITEM_DATA> m_needitem;
	std::vector<RESET_REWARD_DATA> m_reward;
#endif
};
extern cResetSystem gResetSystem;
