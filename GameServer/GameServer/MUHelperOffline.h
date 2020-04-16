#pragma once

#include "MUHelper.h"
#include "BuffManager.h"
#include "MagicDamage.h"

#define QUARTER_SECOND 250
#define HALF_SECOND 500
#define ONE_SECOND 1000
#define ONE_MINNUTE 60 * ONE_SECOND
#define MAX_BE_HIT 5
#define MAX_ITEM_DISTANCE 8
#define MAX_PICKUP_DISTANCE 1
#define MAX_SETTINGS_ITEMS 12
#define MAX_MOVE_FAILED_COUNT 10
#define MAX_BAR 0xA
#define MIN_SECOND_REBUFF 2
#define HP_POTION_CHECK_DELAY HALF_SECOND
#define HP_POTION_USE_DELAY ONE_SECOND * 3
#define NO_POTION_DELAY ONE_SECOND * 5

enum SETTINGS_STATE
{
	NONE,
	REQUESTED,
	RECEIVED,
};

enum PLAYER_STATE
{
	STANDING,
	ATTACKING,
	PICKINGUP,
	BUFFING,
	MOVING_PICKUP,
	MOVING_BACK,
};

enum SKILL_AREA_TYPE
{
	SINGLE,
	TARGET_CIRCLE,
	DIR_LINEAR,
	SELF_CIRCLE,
	DIR_CONE,
	DIR_SEMI_CIRCLE,
	DURATION,
};

struct SKILL_AREA_INFO
{
	SKILL_AREA_TYPE type;
	int radius;
	int interval;
	std::string name;
};


struct MUHELPER_SETTINGS
{
	BYTE PickupJewel;
	BYTE PickupSetItem;
	BYTE PickupExcItem;
	BYTE PickupZen;
	BYTE PickupExtra;

	BYTE PickupRange;
	BYTE AttackRange;

	WORD MaxDistance;
	WORD MainSkill;
	WORD SubSkill1;
	WORD SubSkill1Dur;
	WORD SubSkill2;
	WORD SubSkill2Dur;
	WORD PartyBuffDur;
	WORD BuffSkill1;
	WORD BuffSkill2;
	WORD BuffSkill3;

	BYTE HealBar;
	BYTE PotionBar;
	BYTE PartyBar;
	BYTE DrainBar;

	BYTE PotionEnabled;
	BYTE HealSelf;
	BYTE CounterEnabled;
	BYTE OriginalPos;
	BYTE ComboEnabled;
	BYTE BuffParty;
	BYTE HealParty;

	BYTE BuffPartyDelay;
	BYTE DarkRavenEnabled;
	BYTE BuffSelfEnabled;
	BYTE SubSkill1Delay;
	BYTE SubSkill1Cond;
	BYTE SubSkill1PreCond;
	BYTE SubSkill1SubCond;

	BYTE SubSkill2Delay;
	BYTE SubSkill2Cond;
	BYTE SubSkill2PreCond;
	BYTE SubSkill2SubCond;
	BYTE RepairItem;
	BYTE PickupAllItems;
	BYTE PickupSeletectedItems;

	BYTE RavenAttackMode;

	std::string ItemNames[MAX_SETTINGS_ITEMS];
};

struct OFFLINE_STATE
{
	bool active = false;

	DWORD nextAction;
	DWORD nextCheckSelfBuff;
	DWORD nextCheckPartyBuff;

	DWORD magicKey;

	bool useManaPotion;
	DWORD nextCheckManaPotion;
	DWORD nextCheckHPPotion;

	CMapItem* lpTargetItem;
	int targetItemIdx;

	int moveFailedCount;

	int originX;
	int originY;

	PLAYER_STATE playerState;
	SETTINGS_STATE settingsState;
	MUHELPER_SETTINGS settings;
};

class CMUHelperOffline
{
public:
	void Load();
	void Clear();

	void Tick();
	void Tick(LPOBJ lpObj);

	void MacroRes(int aIndex, MUHELPER_SETTINGS_PACKET settings);
	void MacroSave(int aIndex, LPBYTE settingsBuffer);

	void Start(int aIndex);
	void Stop(int aIndex);

	void NoMana(int aIndex);

	OFFLINE_STATE* GetState(int aIndex, bool newOne = false);
	void ClearState(int aIndex);

	void PacketToSettings(MUHELPER_SETTINGS_PACKET& packet, MUHELPER_SETTINGS& settings);

private:
	void CheckPotions(LPOBJ lpObj, OFFLINE_STATE* lpState);

	BOOL CheckHeal(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CheckItems(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CheckReturn(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CheckBuffs(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CheckAttack(LPOBJ lpObj, OFFLINE_STATE* lpState);

	DWORD DoAttack(LPOBJ lpObj, OFFLINE_STATE* lpState, LPOBJ lpTargetObj);
	DWORD DoPickup(LPOBJ lpObj, OFFLINE_STATE* lpState);
	
	BOOL DoPartyBuff(LPOBJ lpObj, OFFLINE_STATE* lpState, WORD skillNumber);
	BOOL DoSelfBuff(LPOBJ lpObj, WORD skillNumber);

	WORD MoveTo(LPOBJ lpObj, OFFLINE_STATE* lpState, int x, int y);

	std::vector<LPOBJ> GetTargetSkillList(LPOBJ lpObj, SKILL_AREA_INFO skillInfo, LPOBJ lpTargetObj);
	std::vector<LPOBJ> ListTargetsTargetCircle(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets = MAX_BE_HIT);

	int GetSkillEffect(int skill);

	LPOBJ SearchTargetNearby(LPOBJ lpObj, int maxDist);
	BOOL SearchItemNearby(LPOBJ lpObj, int maxDist, OFFLINE_STATE* lpState);
	BOOL ShouldPickupItem(CMapItem* lpMapItem, MUHELPER_SETTINGS& settings);
	CItem* SearchItemInventory(LPOBJ lpObj, int type, int level, int& outPos);

	int CalcAttackInterval(LPOBJ lpObj, SKILL_AREA_INFO skillInfos);

	DWORD m_Now;

	bool m_Loaded;
	std::map<int, OFFLINE_STATE> m_states;
	std::map<int, SKILL_AREA_INFO> m_skillsAreaInfo;

	const std::map<int, int> m_skillBuffMap = 
	{
		{AT_SKILL_MAGICDEFENSE, AT_WIZARD_DEFENSE},
		{AT_SKILL_DEFENSE, AT_INCREASE_DEFENSE},
		{AT_SKILL_ATTACK, AT_INCREASE_ATTACK},
		{AT_SKILL_KNIGHTADDLIFE, AT_SWELL_LIFE},
		{AT_SKILL_ADD_CRITICALDAMAGE, AT_INCREASE_CRITICAL_DMG},
		{AT_SKILL_INFINITY_ARROW, AT_INFINITY_ARROW},
		{AT_SKILL_DAMAGE_REFLECTION, AT_DAMAGE_REFLECTION},
		{AT_SKILL_BERSERKER, AT_BERSERKER},
		{AT_SKILL_EXPANSION_WIZARDRY, AT_EXPANSION_WIZARDRY},
		{AT_SKILL_IGNORE_DEFENSE, AT_IGNORE_DEFENSE},
		{AT_SKILL_INCREASE_VIT, AT_INCREASE_VIT},
		{AT_SKILL_INCREASE_DEFRATE, AT_INCREASE_DEFRATE},
	};

	const std::set<int> m_skillPartyBuffs = 
	{
		AT_SKILL_MAGICDEFENSE,
		AT_SKILL_ATTACK,
		AT_SKILL_DEFENSE,
	};

	const std::set<int> m_manaPotions =
	{
		ITEMGET(14,6),
		ITEMGET(14,5),
		ITEMGET(14,4),
	};

	const std::set<int> m_HPPotions =
	{
		ITEMGET(14,3),
		ITEMGET(14,2),
		ITEMGET(14,1),
		ITEMGET(14,0),
	};
};

extern CMUHelperOffline g_MUHelperOffline;