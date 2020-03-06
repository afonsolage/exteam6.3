#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"
#include "user.h"

#define CQ_MAX_MISSION		5
#define CQ_MAX_REWARD		3

#define CQ_UNIQUE_QUEST		0
#define CQ_DAILY_QUEST		1
#define CQ_GUILD_QUEST		2
#define CQ_QUEST_TP_CNT		3

#define MAX_DAILY_QUEST_ID	10000

enum RewardType
{
	ZEN = 1,
	ITEM = 3,
};

struct CustomQuestReward
{
	int Type;
	int Count;
	int ItemType;
	int ItemIdx;
	int ItemLvl;
};

struct CustomQuestMission
{
	int MobID;
	int MobCount;
};

struct CustomQuestData
{
	int	id;
	char NameQuest[25];
	int NeedLevel;
	int MaxLevel;
	int NeedReset;
	BOOL AllowDW;
	BOOL AllowDK;
	BOOL AllowELF;
	BOOL AllowSUM;
	BOOL AllowMG;
	BOOL AllowDL;
	BOOL AllowRF;
	std::vector<CustomQuestMission> missions;
	std::vector<CustomQuestReward> rewards;
};

struct CQ_Mission
{
	char NameQuest[25];
	BYTE Start;
	WORD ExWQuestCount[EW_MAX_MISSION];
	BYTE MissionType[EW_MAX_MISSION];
	WORD MissionID[EW_MAX_MISSION];
	WORD MissionIndex[EW_MAX_MISSION];
	BYTE MissionLevel[EW_MAX_MISSION];
	BYTE MissionLuck[EW_MAX_MISSION];
	BYTE MissionOpt[EW_MAX_MISSION];
	BYTE MissionExl[EW_MAX_MISSION];
	WORD MissionCount[EW_MAX_MISSION];
};

struct GC_CQMiniInfo
{
	PWMSG_HEAD2 h;
	CQ_Mission cqQuest[EW_MAX_ACT];
};
// ----------------------------------------------------------------------------------------------

struct GC_CQMiniInfoEx
{
	PBMSG_HEAD2 h;
	BYTE a;
	BYTE m;
};
// ----------------------------------------------------------------------------------------------

struct CG_CQAcceptDone
{
	PBMSG_HEAD2 h;
	BYTE Result;
};
// ----------------------------------------------------------------------------------------------

struct GC_CQStart
{
	PBMSG_HEAD2 h;
	BYTE Act;
	BYTE Start;
};
// ----------------------------------------------------------------------------------------------

class CCustomQuestSystem
{
public:
	CCustomQuestSystem(void);
	virtual ~CCustomQuestSystem(void);

	void Init();
	void Load();

	void UserConnect(int aIndex);
	bool Dialog(int aIndex, int aNpcIndex);
	BOOL IsEnabled() const {return m_bEnabled;}
	int	GetNpcClass() const {return m_iNpcClass;}

	void CG_AcceptQuest(int aIndex, CG_CQAcceptDone* aRecv);
	void GC_MiniInfoEx(int aIndex, int type, int mission);

	bool MonsterKiller(int aIndexMonster, int aIndexUser);

private:
	void LoadQuests(int type, char* path);
	
	void GC_MainInfo(LPOBJ lpUser);
	void GC_Start(int aIndex, int type, bool start);
	
	void RewardQuest(int aIndex, int type);
	int FindNextQuestDaily(LPOBJ lpUser, int current_id = 0);
	int FindNextQuestUnique(LPOBJ lpUser, int current_id = 0);
	CustomQuestData FindQuestData(int type, int id);
	int GetTodayDaysCount() const { time_t s = time(NULL); return (s/(60*60*24)); }
	bool IsDailyQuestAvailable(LPOBJ lpUser);

	BOOL m_bEnabled;
	int	m_iNpcClass;
	std::vector<CustomQuestData> m_vUniqueQuests;
	std::vector<CustomQuestData> m_vDailyQuests;
	std::vector<CustomQuestData> m_vGuildQuests;

	std::vector<CustomQuestData>& FindQuestList(int type) {return (type == CQ_UNIQUE_QUEST) ? this->m_vUniqueQuests : (type == CQ_DAILY_QUEST) ? this->m_vDailyQuests : this->m_vGuildQuests;}
};

extern CCustomQuestSystem g_CustomQuestSystem;