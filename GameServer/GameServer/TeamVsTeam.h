#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"
//NEED TEST SWITCH ON EVENT
#if(EVENT_TEAM_VS_TEAM==TRUE)
#if(ENABLE_DEBUG)
#define TEAMVSTEAM_WAIT			1
#else
#define TEAMVSTEAM_WAIT			5
#endif
#define TEAMVSTEAM_MAP			82
#define TEAMVSTEAM_X			72
#define TEAMVSTEAM_Y			46
#define TEAMVSTEAM_MINPLAYER	2	//2
#define TEAMVSTEAM_X1			36
#define TEAMVSTEAM_Y1			28
#define TEAMVSTEAM_X2			93
#define TEAMVSTEAM_Y2			80
#define MAX_VIEWPORT_TVT		75

enum eTvTStatus
{
	eEVENT_TEAMVSTEAM_CLOSE  = 0,
	eEVENT_TEAMVSTEAM_WAIT	 = 1,
	eEVENT_TEAMVSTEAM_START	 = 2,
};

enum eTvTTeam
{
	eEVENT_TVT_TEAM_1	= 1,
	eEVENT_TVT_TEAM_2	= 2,
};

struct PMSG_TVTGC_RESULT
{
	PBMSG_HEAD2 h;
};

struct PMSG_TVTGC_STATUS
{
	PBMSG_HEAD2 h;
	char Status;
};

struct PMSG_TVTGC_WINOPEN
{
	PBMSG_HEAD2 h;
	int MinLevel;
	int MinReset;
};

struct PMSG_TVTGC_SCORE
{
	PBMSG_HEAD2 h;
	int TeamScore1;
	int TeamScore2;
};

struct PMSG_TVTGC_TEAM
{
	PBMSG_HEAD2 h;
	BYTE Team;
};

struct PMSG_TVTGD_INFO
{
	PBMSG_HEAD2 h;
	char Name[11];
	int KillCount;
};

struct PMSG_TVTGC_KILL
{
	PBMSG_HEAD2 h;
	int KillCount;
	int DieCount;
};

struct PMSG_TVTGC_TIME
{
	PBMSG_HEAD2 h;
	DWORD EventTime;
};

struct VIEWEPORT_TVT
{
	WORD aIndex;
	DWORD Life;
	DWORD MaxLife;
	BYTE TvTTeam;
};

#if(TEAM_VS_TEAM_INFO)
struct TvT_Statistic
{
	char Name[11];
	WORD Kill;
	WORD Die;
};

struct PMSG_TVT_STATISTIC
{
	PWMSG_HEAD2 h;
	BYTE Count;
	BYTE Count2;
	TvT_Statistic stat[10];
	TvT_Statistic stat2[10];
};
#endif

class CTeamVsTeam
{
public:
		 CTeamVsTeam();
		 ~CTeamVsTeam();

	void Init();
	void Load();
	void Read(char* filename);
	void Run();
	void ProcessStatusClose();
	void PrecessStatusWait();
	void ProcessStatusStart();
	void SetStatus(int States);
	bool CheckStatus(int Status);
	void StatusClose();
	void StatusWait();
	void StatusStart();
	bool NpcDialog(int aIndex, int aNpcIndex);
	int  DivTeam();
	bool PlayerKill(int aIndex, int aTargetIndex);
	bool AttackCheck(int aIndex, int aTargetIndex);
	bool PKCheck(int aIndex, int aTargetIndex);
	bool PlayerRegen(int aIndex);
	void PlayerReward(int WinTeam);
	void GCEventStatusAll();
	void GCOpenWindow(int aIndex);
	void CGTeleportEvent(int aIndex);
	void GCEventScoreAll();
	void GCMapAttribute(int aIndex, int maptype);
	void GCViewePortTvT();
	void GCTeam(int aIndex);
	bool CheckDLTeleport(int aIndex);
	void PlayerConnect(int aIndex);
	void GDEventInfo();
	void GCUserKillCount(int aIndex);
	void GCEventTimer(int aIndex);
#if(TEAM_VS_TEAM_INFO)
	void GCEventStatistic();
#endif

private:
	bool m_Enable;
	int m_EventStatus;
	int m_TeamScore1;
	int m_TeamScore2;
	int m_TickCount;
	int m_TickRemain;
	int m_TickWait;
	int m_NpcClass;
	int m_NpcMap;
	int m_NpcX;
	int m_NpcY;
	int m_EventStartDay;
	int m_EventStartHour;
	int m_EventeStartMin;
	int m_EventDurationTime;
	int m_MinLevel;
	int m_MinReset;
	int m_RewardBonusEnable;
	int m_RewardBonusCount;
	int m_RewardItemEnable;
	int m_RewardItemType;
	int m_RewardItemIndex;
	int m_RewardItemLevel;

	SYSTEMTIME systime;
};
extern CTeamVsTeam g_TeamVsTeam;

#endif