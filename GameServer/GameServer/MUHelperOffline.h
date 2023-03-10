#pragma once

#include "MUHelper.h"
#include "BuffManager.h"
#include "MagicDamage.h"
#include "../../Common/LCProtocol.h"

#define PRINT_DEBUG_LINE(str) char tmp[256] = { 0 }; \
								sprintf(tmp, "%s %d \n", ##str, __LINE__); \
								OutputDebugString(tmp);


#define QUARTER_SECOND 250
#define HALF_SECOND 500
#define ONE_SECOND 1000
#define ONE_MINUTE 60 * ONE_SECOND
#define MAX_BE_HIT 5
#define MAX_ITEM_DISTANCE 8
#define MAX_PICKUP_DISTANCE 1
#define MAX_SETTINGS_ITEMS 12
#define MAX_MOVE_FAILED_COUNT 10
#define MAX_BAR 0xA
#define MIN_SECOND_REBUFF 10
#define HP_POTION_CHECK_DELAY HALF_SECOND
#define HP_POTION_USE_DELAY ONE_SECOND * 3
#define NO_POTION_DELAY ONE_SECOND * 5
#define COMBO_SKILL_COUNT 3
#define COMBO_TIMEOUT ONE_SECOND * 3

#define EVIL_MAX_SAME_MOB_HIT_COUNT 2
#define FLAME_MAX_SAME_MOB_HIT_COUNT 3

//This const is located inside the client
#define SPEED_MULT 0.004000000189989805
#define MSPEED_MULT 0.002000000094994903
#define BASE_SPEED 0.25f
#define CLIENT_FPS 25
#define CLIENT_FRAME_DELTA 1.0f/CLIENT_FPS

struct MUHELPEROFF_ACTION
{
	PBMSG_HEAD2 h;
	BYTE Action;
};

struct MUHELPEROFF_DATA
{
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	BOOL Active;
	BOOL Offline;
	DWORD PcID;
	DWORD StartTimeOffline;
};

struct PMSG_SAVE_MUHELPEROFF_DATA
{
	PBMSG_HEAD2 h;
	MUHELPEROFF_DATA data;
};

struct PMSG_REQ_MUHELPEROFF_DATA
{
	PBMSG_HEAD2 h;
};

struct PMSG_RESTORE_DATA
{
	PBMSG_HEAD2 h;
	char AccountID[MAX_IDSTRING + 1];
	char Password[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	DWORD PcID;
	DWORD StartTime;
};

enum OFFLINE_RECONNECT_STATE
{
	OFF_NONE,
	OFF_AUTH_REQ,
	OFF_CHAR_REQ,
	OFF_PLAYING,
};

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
	MOVING_ATTACK,
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
	int frames;
	int speedType;
	int radius;
	int maxMobHitCount;
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
	BYTE DrainSelf;
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
	bool offline = false;
	DWORD startTimeOffline = 0;

	bool shouldDestroyVP = false;
	bool shouldCreateVP = false;
	bool shouldClearState = false;

	bool useDrainLife = false;

	BYTE comboNextSkillIndex;
	DWORD comboStartTime;

	DWORD lastSubSkill1Use;
	DWORD lastSubSkill2Use;

	DWORD nextAction;
	DWORD nextCheckSelfBuff;
	DWORD nextCheckPartyBuff;

	DWORD magicKey;

	bool useManaPotion;
	DWORD nextCheckManaPotion;
	DWORD nextCheckHPPotion;

	DWORD nextCheckPet;
	DWORD nextCheckRepair;
	DWORD nextCheckArrow;
	DWORD nextZenBilling;

	CMapItem* lpTargetItem;
	int targetItemIdx;

	LPOBJ lpTargetObj;
	int targetMagicCode;

	int moveFailedCount;

	int originX;
	int originY;

	OFFLINE_RECONNECT_STATE offReconectState;
	PLAYER_STATE playerState;
	SETTINGS_STATE settingsState;
	MUHELPER_SETTINGS settings;
};

class CMUHelperOffline
{
public:
	void Load();
	void Clear();

	void RequestAllPlayers();
	void DGRestorePlayer(PMSG_RESTORE_DATA* lpMsg);
	void GDSavePlayerState(LPOBJ lpObj);
	void GDReqCharInfo(int aIndex);

	void Tick();
	void Tick(LPOBJ lpObj);

	void MacroRes(int aIndex, MUHELPER_SETTINGS_PACKET settings);
	void MacroSave(int aIndex, LPBYTE settingsBuffer);

	void Start(int aIndex);
	void Stop(int aIndex);
	bool SwitchOffline(int aIndex);
	void SwitchOnline(int aIndex);

	void NoMana(int aIndex);

	BOOL IsActive(int aIndex);
	BOOL IsOffline(int aIndex);

	void CloseOfflineUser(int aIndex, bool saveState = true);

	OFFLINE_STATE* GetState(int aIndex);
	void ClearState(int aIndex, bool saveState = true);

	void PacketToSettings(MUHELPER_SETTINGS_PACKET& packet, MUHELPER_SETTINGS& settings);

private:
	void ChargeZen(LPOBJ lpObj, OFFLINE_STATE* lpState);

	void CheckPotions(LPOBJ lpObj, OFFLINE_STATE* lpState);
	void CheckPet(LPOBJ lpObj, OFFLINE_STATE* lpState);
	void CheckRepair(LPOBJ lpObj, OFFLINE_STATE* lpState);
	void CheckArrows(LPOBJ lpObj, OFFLINE_STATE* lpState);

	BOOL CheckHeal(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CheckItems(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CheckMoving(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CheckBuffs(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CheckAttack(LPOBJ lpObj, OFFLINE_STATE* lpState, std::set<int> excludeTargets = std::set<int>());

	int GetMagicDistance(int magicCode);

	DWORD DoAttack(LPOBJ lpObj, OFFLINE_STATE* lpState, LPOBJ lpTargetObj, int magicCode);
	void ApplyDamage(std::vector<LPOBJ> &targetList, const WORD &magicCode, const LPOBJ &lpObj, int interval, OFFLINE_STATE * lpState, const LPOBJ &lpTargetObj);
	DWORD DoPickup(LPOBJ lpObj, OFFLINE_STATE* lpState);
	void DoLookAt(LPOBJ lpObj, LPOBJ lpTargetObj);

	BOOL DoPartyBuff(LPOBJ lpObj, OFFLINE_STATE* lpState, WORD skillNumber);
	BOOL DoSelfBuff(LPOBJ lpObj, WORD skillNumber);

	WORD MoveTo(LPOBJ lpObj, OFFLINE_STATE* lpState, int x, int y);

	std::vector<LPOBJ> GetTargetSkillList(LPOBJ lpObj, SKILL_AREA_INFO skillInfo, LPOBJ lpTargetObj);
	std::vector<LPOBJ> ListTargetsTargetCircle(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets = MAX_BE_HIT);
	std::vector<LPOBJ> ListTargetsDirCone(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets = MAX_BE_HIT);
	std::vector<LPOBJ> ListTargetsDirLinear(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets = MAX_BE_HIT);
	std::vector<LPOBJ> ListTargetsDirSemiCircle(LPOBJ lpObj, LPOBJ lpTarget, int maxDist, int maxTargets = MAX_BE_HIT);

	int GetSkillEffect(int skill);

	LPOBJ SearchTargetNearby(LPOBJ lpObj, int maxDist, std::set<int> excludeTargets);
	BOOL SearchItemNearby(LPOBJ lpObj, int maxDist, OFFLINE_STATE* lpState);
	BOOL ShouldPickupItem(CMapItem* lpMapItem, MUHELPER_SETTINGS& settings);
	CItem* SearchItemInventory(LPOBJ lpObj, int type, int level, int& outPos);

	std::string BuildItemName(CMapItem* lpItem);

	CMagicInf* GetMagicInfo(LPOBJ lpObj, OFFLINE_STATE* lpState);
	int GetSettingsMagic(LPOBJ lpObj, OFFLINE_STATE* lpState);
	BOOL CanUseMagic(LPOBJ lpObj, OFFLINE_STATE* lpState, int magicCode);
	int CalcAttackInterval(LPOBJ lpObj, SKILL_AREA_INFO skillInfos);

	int GetFreeIndex();

	DWORD m_Now;
	DWORD m_NowEpoch;

	bool m_allPlayersRequestSent;

	bool m_Loaded;
	
	bool m_enabled;
	bool m_firstChargeZen;
	int m_chargeInterval;
	int m_pricePerLevel;
	int m_pricePerReset;
	int m_offlineTimeLimit;
	int m_vipOfflineTimeLimit;

	std::map<int, OFFLINE_STATE> m_states;
	std::map<int, SKILL_AREA_INFO> m_skillsAreaInfo;
	std::map<std::tuple<int, int>, std::string> m_extraNames;

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

	const std::set<int> m_ringPendantsIndexes =
	{
		ITEMGET(13,8),
		ITEMGET(13,9),
		ITEMGET(13,12),
		ITEMGET(13,13),
		ITEMGET(13,21),
		ITEMGET(13,22),
		ITEMGET(13,23),
		ITEMGET(13,24),
		ITEMGET(13,25),
		ITEMGET(13,26),
		ITEMGET(13,27),
	};

	const std::set<int> m_jewelsIndexes =
	{
		ITEMGET(12, 15), //Jewel of Chaos
		ITEMGET(14, 13), //Jewel of Bless
		ITEMGET(14, 14), //Jewel of Soul
		ITEMGET(14, 16), //Jewel of Life
		ITEMGET(14, 22), //Jewel of Creation
		ITEMGET(14, 31), //Jewel of Guardian
		ITEMGET(14, 41), //Gemstone
		ITEMGET(14, 42), //Jewel of Harmony
	};
};

extern CMUHelperOffline g_MUHelperOffline;