#pragma once

#include "Protocol.h"

#define pMUHelperClass			*(int*)0xE8CB7C
#define pMUHelperTick			((LPVOID(*)()) 0x0095DC90)

#pragma pack(push, 1)
typedef struct
{
BYTE gap01[172];
/*+172*/	DWORD	HuntingRange;
/*+176*/	bool	RecoveryPotionOn;
/*+177*/	BYTE	RecoveryPotionPercent;
/*+178*/	bool	RecoveryHealOn;			//-> CLASS_ELF
/*+179*/	BYTE	RecoveryHealPercent;	//-> CLASS_ELF
/*+180*/	bool	RecoveryDrainOn;		//-> CLASS_SUMMONER
/*+181*/	BYTE	RecoveryDrainPercent;	//-> CLASS_SUMMONER
/*+182*/	bool	DistanceLongOn;
/*+183*/	bool	DistanceReturnOn;
/*+184*/	DWORD	DistanceMin;
/*+188*/	DWORD	SkillBasicID;
/*+192*/	DWORD	SkillSecond1ID;
/*+196*/	BOOL	SkillSecond1DelayOn;
/*+200*/	DWORD	SkillSecond1DelayTime;
/*+204*/	BOOL	SkillSecond1CounterOn;
/*+208*/	int		SkillSecond1CounterPre;
/*+212*/	int		SkillSecond1CounterSub;
/*+216*/	DWORD	SkillSecond2ID;
/*+220*/	BOOL	SkillSecond2DelayOn;
/*+224*/	DWORD	SkillSecond2DelayTime;
/*+228*/	BOOL	SkillSecond2CounterOn;
/*+232*/	int		SkillSecond2CounterPre;
/*+236*/	int		SkillSecond2CounterSub;
/*+240*/	bool	ComboOn;				//-> CLASS_KNIGHT
/*+241*/	bool	PartyModeOn;
/*+242*/	bool	PartyModeHealOn;		//-> CLASS_ELF
/*+243*/	BYTE	PartyModeHealPercent;	//-> CLASS_ELF
/*+244*/	BOOL	PartyModeBuffOn;
/*+248*/	DWORD	PartyModeBuffInterval;
/*+252*/	BOOL	DarkSpiritOn;			//-> CLASS_DARKLORD
/*+256*/	DWORD	DarkSpiritMode;			//-> CLASS_DARKLORD
/*+260*/	BOOL	BuffOn;
/*+264*/	DWORD	BuffSkill[3];
/*+276*/	DWORD	BuffExtra[3];
/*+288*/	DWORD	ObtainRange;
/*+292*/	bool	ObtainRepairOn;
/*+293*/	bool	ObtainPickNear;
/*+294*/	bool	ObtainPickSelected;
/*+295*/	bool	ObtainPickJewels;
/*+296*/	bool	ObtainPickAncient;
/*+297*/	bool	ObtainPickMoney;
/*+298*/	bool	ObtainPickExcellent;
/*+299*/	bool	ObtainPickExtra;
/*+300*/	BYTE	ObtainPickItemList[28][12];
/*+636*/	BYTE	Unknown636;
/*+637*/	BYTE	Unknown637;
/*+638*/	BYTE	Unknown638;
} MUHelper, * lpMUHelper;
#pragma pack(pop)

//0xBF, 0x51
struct MUHELPER_ANS_DATA	//-> Complete (from 6.3 GMO)
{
	PBMSG_HEAD2 h;			//-> 0	(4)
	WORD	Time;			//-> 4	(2)
	DWORD	Money;			//-> 8	(4)
	BYTE	Mode;			//-> 12 (1)
};

//0xBF, 0x51
struct MUHELPER_REQ_ACTION	//-> Complete
{
	PBMSG_HEAD2 h;			//-> 0	(4)
	BYTE	Mode;			//-> 4	(1)
};

class CMuHelper
{
public:
	CMuHelper(void);
	virtual ~CMuHelper(void);

	void GCData(LPBYTE Data);

	bool	IsActive() {return m_Mode == 0;}
	WORD	GetTime() {return m_Time;}
	DWORD	GetMoney() {return m_Money;}

	void Start();
	void Stop();
	void RestoreState();

#ifdef ENABLE_CONSOLE
	void PrintInfo();
#endif

private:
	WORD	m_Time;
	DWORD	m_Money;
	BYTE	m_Mode;
};

extern CMuHelper gMuHelper;
