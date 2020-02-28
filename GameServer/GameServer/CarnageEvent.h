#pragma once

#if(EVENT_CARNAGE)

#define CARNAGE_DEBUG		1

#define CARNAGE_MONSTER_MAX	500
#define CARNAGE_TIME_END	5000

enum
{
	eCARNAGE_STATUS_CLOSE	= 0,
	eCARNAGE_STATUS_WAIT	= 1,
	eCARNAGE_STATUS_START	= 2,
	eCARNAGE_STATUS_END		= 3,
};

struct CARNAGE_TIME
{
	int Hour;
	int Min;
};

struct CARNAGE_ITEM
{
	int Type;
	int Index;
	int MinLevel;
	int MaxLevel;
	int Skill;
	int Luck;
	int Add;
	int Exc;
};

struct CARNAGE_MONSTER_DATA
{
	int MobClass;
	int MobX;
	int MobY;
	int MobCount;
	int BossActive;
	int BossClass;
	int BossX;
	int BossY;
	char BossDie[64];
};

struct CARNAGE_MONSTER_BASE
{
	int Stage;
	int Type;
	int aIndex;
	int Pos;
	int Class;
};

class CCarnageEvent
{
public:
		 CCarnageEvent();
		 ~CCarnageEvent();

	void Load();
	void Read(char* filename);
	void Run();

	void ProcessStateClose();
	void ProcessStateWait();
	void ProcessStateStart();
	void ProcessStateEnd();
	void SetStateClose();
	void SetStateWait();
	void SetStateStart();
	void SetStateEnd();

	bool NpcDialog(int aIndex, int aNpcIndex);

	int GetMonsterPos(WORD Type, BYTE Map, BYTE X, BYTE Y);
	void LoadMonster();
	void AddMonster(int Stage, int Type);
	void DelMonster();
	void DieMonster(int aIndex, int aMonsterIndex);
	void RewardMonster(int aIndex, int aMonsterIndex, int MonsterType);
	void MessageMonster(int aMonsterIndex, int MonsterType);
	void StageMonster(int aMonsterIndex, int MonsterType);

	void GCMapAttribute(int aIndex, int maptype);

	int m_EventStatus;
	int m_EventStage;
	int m_TickCount;
	int m_TickRemain;
	int m_TickWait;

	int m_Enable;
	int m_MapNumber;
	int m_MapX;
	int m_MapY;
	int m_OpenTime;
	int m_PlayTime;
	int m_EndTime;

	int m_NpcClass;
	int m_NpcMap;
	int m_NpcX;
	int m_NpcY;

	int m_TicketActive;
	int m_TicketType;
	int m_TicketIndex;
	int m_TicketLevel;

	int m_RewardItemCount;
	int m_RewardAncentRate;

	int m_MonsterCount;
	int m_StageMonsterCount;

	std::vector<CARNAGE_TIME> m_TimeData;
	std::vector<CARNAGE_MONSTER_DATA> m_MonsterData;
	std::vector<CARNAGE_ITEM> m_ItemData;

	CARNAGE_MONSTER_BASE m_MonsterBase[CARNAGE_MONSTER_MAX];
};

extern CCarnageEvent g_CarnageEvent;

#endif