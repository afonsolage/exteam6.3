#pragma once

#include "MUHelper.h"

#define ONE_SECOND 1000
#define ONE_MINNUTE 60 * ONE_SECOND
#define MAX_BE_HIT 5

enum SETTINGS_STATE
{
	NONE,
	REQUESTED,
	RECEIVED,
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
	std::string name;
};


struct MUHELPER_SETTINGS
{
	BYTE PickupJewel;
	BYTE PickupSetItem;
	BYTE PickkupExcItem;
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

	std::string ItemName1;
	std::string ItemName2;
	std::string ItemName3;
	std::string ItemName4;
	std::string ItemName5;
	std::string ItemName6;
	std::string ItemName7;
	std::string ItemName8;
	std::string ItemName9;
	std::string ItemName10;
	std::string ItemName11;
	std::string ItemName12;
};

struct OFFLINE_STATE
{
	bool active = false;

	DWORD nextAction;

	DWORD magicKey;

	SETTINGS_STATE settings_state;
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

	OFFLINE_STATE* GetState(int aIndex);

	void PacketToSettings(MUHELPER_SETTINGS_PACKET& packet, MUHELPER_SETTINGS& settings);

private:
	void CheckAttack(LPOBJ lpObj, OFFLINE_STATE* lpState);
	void DoAttack(LPOBJ lpObj, OFFLINE_STATE* lpState, LPOBJ lpTargetObj);

	std::vector<LPOBJ> GetTargetSkillList(LPOBJ lpObj, SKILL_AREA_INFO skillInfo, LPOBJ lpTargetObj);
	std::vector<LPOBJ> ListTargetsTargetCircle(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets = MAX_BE_HIT);


	LPOBJ SearchTarget(LPOBJ lpObj, int maxDist);
	int CalcAttackInterval(LPOBJ lpObj);

	DWORD m_Now;

	bool m_Loaded;
	std::map<int, OFFLINE_STATE> m_states;
	std::map<int, SKILL_AREA_INFO> m_skillsAreaInfo;
};

extern CMUHelperOffline g_MUHelperOffline;