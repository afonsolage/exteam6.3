#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"

#if(EVENT_DUNGEON_SIEGE)

#define DUNGEON_SIEGE_DEBUG		1

enum DungeonState
{
	eEVENTDUNGEON_CLOSE,
	eEVENTDUNGEON_WAIT,
	eEVENTDUNGEON_START_STAGE1,
	eEVENTDUNGEON_WAIT_STAGE2,
	eEVENTDUNGEON_START_STAGE2,
};

struct DUNGEON_SIEGE_REG_LIST
{
	char szGuildName[9];
};

struct PMSG_DG_DUNGEON_SIEGE_REG_LIST
{
	PBMSG_HEAD2 h;
	int  iCount;
	char szGuildName[10][9];
};

struct PMSG_GC_DUNGEON_SIEGE_NPC
{
	PBMSG_HEAD2 h;
	bool bResultReg;
	int  iMsgCode;
	bool Captured;
	int  iCountGuild;
	char szGuildOwner[9];
	char szGuildName[10][9];
};

struct PMSG_GD_DUNGEON_SIEGE_GUILD_REG
{
	PBMSG_HEAD2 h;
	bool bResult;
	int  aIndex;
	char szGuildName[9];
};

struct PMSG_GD_DUNGEON_SIEGE_GUILD_REG_RESULT
{
	PBMSG_HEAD2 h;
	bool bResult;
	int  aIndex;
};

struct PMSG_GD_DUNGEON_SIEGE_UPDATE_OENER
{
	PBMSG_HEAD2 h;
	char szGuildOwner[9];
};

struct PMSG_DG_DUNGEON_SIEGE_SELECT_OENER
{
	PBMSG_HEAD2 h;
	bool bResult;
	char szGuildOwner[9];
};

struct PMSG_CG_DUNBEON_SIEGE_HWID
{
	PBMSG_HEAD2 h;
	DWORD dwHWID;
};

struct DUNGEON_SIEGE_USER
{
	bool  bNpcClick;
	DWORD dwHWID;
	int   iScore;
	int   iScore2;
};

struct DUNGEON_SIEGE_GUILD
{
	int iScore;
};

struct PMSG_GC_GUILD_INDEX
{
	PBMSG_HEAD2 h;
	int GuildNumber;
};

struct DUNGEON_VIEWE
{
	int aIndex;
	int GuildNumber;
};

struct PMSG_DUNGEON_SIEGE_SCORE
{
	PBMSG_HEAD2 h;
	int MyScore;
	int GuildCount;
	int GuildScore[10];
	int FinalGuildID1;
	int FinalGuildID2;
	int FinalScore1;
	int FinalScore2;
	char Name1[11];
	char Name2[11];
	bool InSiege;
};

struct PMSG_DUNGEON_SIEGE_PLAYER_CONNECT
{
	PBMSG_HEAD2 h;
	bool Captured;
	char szGuildOwner[9];
	int  iCountGuild;
	char szGuildName[10][9];
	char EventName[50];
};

struct PMSG_DUNGEON_SIEGE_STATE
{
	PBMSG_HEAD2 h;
	int EventState;
};

class CDungeonSiege
{
public:
		 CDungeonSiege();
		 ~CDungeonSiege();

	void Init();
	void Load();
	void Read(char* filename);
	bool NpcDialog(int aIndex, int aNpcIndex);
	void Run();
	void GCNpcNnfo(int aIndex);
	void GDReqRegSiegeList();
	void DGRegSiegeList(PMSG_DG_DUNGEON_SIEGE_REG_LIST* lpMsg);
	void CGDRegSiege(int aIndex);
	void DGRegSiegeResult(PMSG_GD_DUNGEON_SIEGE_GUILD_REG_RESULT* lpMsg);
	void GDSiegeClearList();
	void GDSiegeOwner();
	void DGSiegeOwner(PMSG_DG_DUNGEON_SIEGE_SELECT_OENER* lpMsg);
	void GDSiegeOwnerUpdate();
	void CGHWID(PMSG_CG_DUNBEON_SIEGE_HWID* lpMsg, int aIndex);
	void SetStatus(int States);
	bool CheckStatus(int Status);
	void StatusClose();
	void StatusWait();
	void StatusStartStage1();
	void StatusWaitStage2();
	void StatusStartStage2();
	void ProcessStatusClose();
	void ProcessStatusStart();
	void PrecessStatusWait();
	void ProcessStatusStartStage1();
	void PrecessStatusWaitStage2();
	void ProcessStatusStartStage2();
	bool ChangePkLevel(int aIndex, int aTargetIndex);
	bool PlayerScore(int aIndex, int aTargetIndex);
	void PlayerCheck(int aIndex);
	bool PlayerGuildRegCheck(int aIndex);
	void MapKick(int aIndex);
	void GCMapAttribute(int aIndex, int maptype);
	void TeleportInSiege(int aIndex);
	bool TeleportInFinal();
	void PlayerGameClose(int aIndex);
	bool PlayerWaitAttack(int aIndex, int aTargetIndex);
	void GuildBuff(int aIndex);
	bool CheckMoveGateSiege(int aIndex, int map);
	void GCVieweSiege(int aIndex);
	void GCGuildNumber(int aIndex);
	void GCSiegeScore();
	void GCPlayerConnect(int aIndex);
	void GCEventState();
	void SiegeClearScore();
	void GuildBuffCharacter(int aIndex);
	void RewardSiege(int aIndex);
	bool SiegeDarkLordSummon(int aIndex);
	void GCMapAttributeAll(int type);
	void GCPlayerScore(int aIndex);
	void MonsterEventDisable();
	void MonsterEventEnable();
	bool CheckEventStart(int aIndex);

	bool DeleteGuildUser(int aIndex);	//NEED CHECK
	void ReturnPlayerRing();

//private:
	int  iEventStatus;
	SYSTEMTIME systime;
	bool bCaptured;
	char szLordGuild[9];
	int iRegCount;
	int iTickCount;
	int iTickRemain;
	int iTickWait;
	int iTickFinal1;
	int iTickFinal2;
	int aIndexFinal1;
	int aIndexFinal2;
	int aGuildFinal1;
	int aGuildFinal2;
	bool bEnable;
	int iNpcClass;
	int iNpcMap;
	int iNpcX;
	int iNpcY;
	int iEventStartDay;
	int iEventStartHour;
	int iEventeStartMinut;
	int iEventDurationStage1;
	int iEventDurationStage2;
	int iEventDurationWait1;
	int iEventDurationWait2;
	int m_EventMapNumber;
	int m_EventStage1WaitX;
	int m_EventStage1WaitY;
	int m_EventStage1KillX;
	int m_EventStage1KillY;
	int m_EventStage2WaitX;
	int m_EventStage2WaitY;
	int m_EventStage2KillX;
	int m_EventStage2KillY;
	int m_EventPlayerDieMap;
	int m_EventPlayerDieX;
	int m_EventPlayerDieY;
	int m_BuffEnable;
	int m_BuffPlusAttackPercent;
	int m_BuffPlusDefencePercent;
	int m_RewardEnable;
	int m_RewardItemEnable;
	int m_RewardItemType;
	int m_RewardItemIndex;
	int m_RewardItemLevel;
	int m_RewardWCoinC;
	int m_RewardWcoinP;
	int m_RewardWgoinG;
	int m_RewardCredit;
	int m_FinalScoreForVictory;
	int m_MinPlayerGuildReg;
	int m_NpcTeleportMinusScore;
	char m_EventName[50];
	DUNGEON_SIEGE_REG_LIST reg_list[10];
};

extern CDungeonSiege g_DungeonSiege;

#endif