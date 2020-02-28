//-------------------------------------------------------------------------------------------------------------------------------
#pragma once /* DoubleGoer.h */
//-------------------------------------------------------------------------------------------------------------------------------

#define MAX_MONSTER_PER_GOER_FLOOR	512
#define GOER_BOSSCOUNT				3
#define	GOER_MAX_PASS_PORTAL		3
#define MAX_DG_OBJ_INDEX			800

#define DG_RESULT_SUCCESS			0
#define DG_RESULT_DEAD_PLAYER		1
#define DG_RESULT_DEFENSE_FAIL		2

//-------------------------------------------------------------------------------------------------------------------------------

#define DG_MAP_RANGE(mapnumber) ( ((mapnumber) < MAP_INDEX_DOUBLE_GOER1)?FALSE:((mapnumber) > MAP_INDEX_DOUBLE_GOER4 )?FALSE:TRUE )
//-------------------------------------------------------------------------------------------------------------------------------

enum
{
	DG_STATE_NONE,
	DG_STATE_OPEN,
	DG_STATE_WAITING,
	DG_STATE_STARTED,
	DG_STATE_ENDED
};
//-------------------------------------------------------------------------------------------------------------------------------

enum
{
	DG_PHAZE_NORMAL,
	DG_PHAZE_BUTCHER,
	DG_PHAZE_ANGRYBUTCHER,
	DG_PHAZE_ICEWALKER
};
//-------------------------------------------------------------------------------------------------------------------------------

struct DOPPELGANGEREVENT
{
	void Clear()
	{
		this->PlayerCount	= 0;
		this->BossCount		= 0;
		this->MonsterCount	= 0;
		this->CreateMonsterDelay = 0;
		this->MoveProcDelay = 0;
		this->GoldBoxIndex  = -1;
		this->PhazesPassed	= 0;
		this->eDuration = 0;
		this->IceWalkerPhazeTime = 0;
		this->btPhaze = 0;
		this->btPlayState = 0;
		this->TickCount = 0;
		// ----
		memset(PlayerIndex, -1, sizeof(PlayerIndex));
		memset(MonsterIndex, -1, sizeof(MonsterIndex));	
		memset(SilverBoxIndex,-1,sizeof(SilverBoxIndex));
		// ----
		IceWalkerLive		= 0;
		this->MapNumber = -1;
		this->PartyNumber = -1;
		this->HalfTimeInfoSent = false;
		this->IceWalkerIndex = -1;
		this->AngryButcherIndex = -1;
		this->ButcherIndex = -1;


	};
	// ----
	BYTE	PlayerCount;
	BYTE	BossCount;
	BYTE	MonsterCount;
	BYTE	MonsterPassed;
	BYTE	CreateMonsterDelay;
	BYTE	MoveProcDelay;
	BYTE btPlayState;
	BYTE btPhaze;
	// ----
	short	GoldBoxIndex;
	short	ButcherIndex;
	short	AngryButcherIndex;
	short	IceWalkerIndex;
	int		PlayerIndex[5];
	short	MonsterIndex[205];
	short	SilverBoxIndex[3];
	int eDuration;
	int CaterpillarIndex;
	int		MapNumber;
	int		PartyNumber;
	int		TickCount;
	bool	HalfTimeInfoSent;
	short	IceWalkerPhazeTime;
	short	EventLevel;
	// ----
	BYTE	IceWalkerLive;
	BYTE	PhazesPassed;

};

struct DG_MONSTER_STAT
{
	short	EventLevel;
	short	Class;
	short	Level;
	int		HP;
	int		DmgMin;
	int		DmgMax;
	int		Defense;
};
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------

class CDoppelGanger
{
protected:

	// ----
	int m_iCount;
	// ----
	int POSX[4];
	int POSY[4];
	int MPOSX[4];
	int MPOSY[4];
	// ----

	DOPPELGANGEREVENT m_DGData;
	std::vector<DG_MONSTER_STAT> m_vtDGMobStat;

public:	

	void Init();
	void SetState(int iState);
	void Run();
	void SetState_OPEN();
	void SetState_WAITING();
	void SetState_STARTED();
	void SetState_ENDED();
	void ProcState_OPEN();
	void ProcState_WAITING();
	void ProcState_STARTED();
	void ProcState_ENDED();
	void EnterEvent(LPOBJ lpObj);
	bool AddPlayer(LPOBJ lpObj);
	void SetMapAttr(bool Block, LPOBJ lpObj);
	void SendHalfTimeInfo(int Type);
	void SendDoppelGangerPlayer(LPBYTE lpMsg, int iSize);
	char GetEventTime(LPOBJ lpObj);
	int SetMapNumber();
	void SetEventInterface();
	void SetMonsterCountOnInterface();
	void SendPlayerPos();
	void SendMonsterPos();
	void SendIceWalkerPos();
	int CalcPos(int player, bool MonsterCalc);
	void CreateMonster();
	void DeleteMonster();
	void MoveProc(LPOBJ lpObj);
	void RegenProc(LPOBJ lpObj);
	void DeadUserProc(LPOBJ lpObj);
	bool IsDGMonster(LPOBJ lpObj);
	void CheckPosition();
	void SendResultMessage(BYTE Result, bool SendForAll, int aIndex);
	void CreateButcher();
	void CreateAngryButcher();
	void CreateIceWalker();
	bool CreateSilverChest(LPOBJ lpObj);
	void CreateFinalChest();
	void CreateGoldenLarva(LPOBJ lpObj);
	void SilverChestOpen(LPOBJ lpChest);
	void FinalChestOpen(LPOBJ lpChest);
	void CheckUsers();
	bool LoadConfigFile(LPSTR hFile);
	bool SetEventLevel();
	void SetMonsterStats(LPOBJ lpObj);

}; 
//-------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DGOER_EVENT_INFO // 0x23
{
	PBMSG_HEAD2 h;
	BYTE Minutes;
};
//-------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DGOER_TIMER_INIT // 0x10
{
	PBMSG_HEAD2 h;	
	BYTE Timer;
};
//-------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DGOER_MONSTER_COUNT // 0x14
{
	PBMSG_HEAD2 h;
	BYTE Total;
	BYTE Killed;
};
//-------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DGOER_TRIANG_POS // 0x0F
{
	PBMSG_HEAD2 h;
	BYTE Pos;
};
//-------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DGOER_RTRIANG_POS // 0x11
{
	PBMSG_HEAD2 h;
	BYTE Unk;
	BYTE Pos;
};
//-------------------------------------------------------------------------------------------------------------------------------

struct PMSG_DGOER_END
{
	PBMSG_HEAD2 h;
	BYTE Status;
};
//-------------------------------------------------------------------------------------------------------------------------------
#pragma pack (1)
struct PMSG_DGOER_UPDATE_BAR
{
	PBMSG_HEAD2 h;

	//Time
	BYTE TimerL;
	BYTE TimerH;

	//Users
	BYTE UserCount;
	BYTE Unk;
};

struct PLAYER_BAR_INFO
{
	BYTE UserL;
	BYTE UserH;
	BYTE Visible;
	BYTE Pos;
};
#pragma pack ()
static const struct DoppelGangerEntrancePos
{
	int iStartX;
	int iStartY;
	int iEndX;
	int iEndY;
} g_DGEntrance[4] = {
	195, 34, 199, 40,
	134, 78, 139, 84,
	106, 65, 111, 71,
	93, 23, 97, 25
};

static const struct DG_PORTALPOS
{
	BYTE StartX;
	BYTE StartY;
} g_DGPortal[4] = {
	197, 30,
	133, 68,
	110, 60,
	95, 15
};



//-------------------------------------------------------------------------------------------------------------------------------

extern int			DGEnabled;
extern int			DGCooldown;
extern int			DGEnterMoney;
extern CDoppelGanger g_DoppelGanger;
//-------------------------------------------------------------------------------------------------------------------------------