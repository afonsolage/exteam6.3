#pragma once

#include "stdafx.h"
#include "Protocol.h"
//#include "ProtocolDefine.h"

#if(EVENT_TEAM_VS_TEAM)

#define TEAMVSTEAM_MAP			82
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

struct TEAM_STAT_DATA
{
	char Name[11];
	WORD Kill;
	WORD Die;
};

class CTeamVsTeam
{
public:
		 CTeamVsTeam();
		~CTeamVsTeam();

	void Init();
	void Load();
	void BindImage();
	void DrawMain();
	void DrawUserScore();
	void DrawWindow();
	void DrawBattle();
#if(TEAM_VS_TEAM_INFO)
	void DrawStatistic();
	void GCEventStatistic(PMSG_TVT_STATISTIC* lpMsg);
#endif
	void Button(DWORD Event);
	bool CheckStatus(int Status);
	void GCEventStatus(PMSG_TVTGC_STATUS* lpMsg);
	void GCOpenWindow(PMSG_TVTGC_WINOPEN* lpMsg);
	void GCEventScore(PMSG_TVTGC_SCORE* lpMsg);
	void GCViewePortTvT(LPBYTE lpMsg);
	bool HPBar();
	void GCTeam(PMSG_TVTGC_TEAM* lpMsg);
	void PKLevelTeam();
	void GCUserKillCount(PMSG_TVTGC_KILL* lpMsg);
	void GCEventiTimer(PMSG_TVTGC_TIME* lpMsg);
	int m_EventStatus;
	int m_MinLevel;
	int m_MinReset;
	int m_TeamScore1;
	int m_TeamScore2;
	int m_Team;
	int m_UserScore;
	int m_UserDie;
	DWORD m_dwEventTime;
	DWORD m_dwTickCount;

	VIEWEPORT_TVT m_Viewe[MAX_VIEWPORT_TVT];
	TEAM_STAT_DATA m_Data1[10];
	TEAM_STAT_DATA m_Data2[10];

	int m_iDataCount1;
	int m_iDataCount2;
};
extern CTeamVsTeam g_TeamVsTeam;

#endif