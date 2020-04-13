#pragma once

#include "StdAfx.h"
#include "user.h"

#ifdef MUHELPER
// -------------------------------------------------------------------------------

#define MUHELPER_DEBUG			0

// -------------------------------------------------------------------------------

struct MUHELPER_ANS_DATA	//-> Complete (from 6.3 GMO)
{
	PBMSG_HEAD2 h;			//-> 0	(4)
	WORD	Time;			//-> 4	(2)
	DWORD	Money;			//-> 8	(4)
	BYTE	Mode;			//-> 12 (1)
};
// -------------------------------------------------------------------------------

struct MUHELPER_REQ_ACTION	//-> Complete
{
	PBMSG_HEAD2 h;			//-> 0	(4)
	BYTE	Mode;			//-> 4	(1)
};
// -------------------------------------------------------------------------------

#pragma pack(push, 1)
struct MUHELPER_SETTINGS_PACKET
{
	BYTE Unkown1;					//0-1
	BYTE Unkown2 : 1;				//1-1
	BYTE Unkown3 : 2;				//1-1
	BYTE PickupJewel : 1;			//1-1
	BYTE PickupSetItem : 1;			//1-1
	BYTE PickkupExcItem : 1;		//1-1
	BYTE PickupZen : 1;				//1-1
	BYTE PickupExtra : 1;			//1-1

	BYTE PickupRange : 4;			//2-1
	BYTE AttackRange : 4;			//2-1

	WORD MaxDistance;				//3-2
	WORD MainSkill;					//5-2
	WORD SubSkill1;					//7-2
	WORD SubSkill1Dur;				//9-2
	WORD SubSkill2;					//11-2
	WORD SubSkill2Dur;				//13-2
	WORD PartyBuffDur;				//15-2
	WORD BuffSkill1;				//17-2
	WORD BuffSkill2;				//19-2
	WORD BuffSkill3;				//21-2

	BYTE HealBar : 4;				//23-1 Same On Elf and Summoner
	BYTE PotionBar : 4;				//23-1
	BYTE PartyBar : 4;				//24-1
	BYTE DrainBar : 4;				//24-1 Same On Elf and Summoner

	BYTE PotionEnabled : 1;			//25-1
	BYTE HealSelf : 2;				//25-1
	BYTE CounterEnabled : 1;		//25-1
	BYTE OriginalPos : 1;			//25-1
	BYTE ComboEnabled : 1;			//25-1
	BYTE BuffParty : 1;				//25-1
	BYTE HealParty : 1;				//25-1

	BYTE BuffPartyDelay : 1;		//26-1
	BYTE DarkRavenEnabled : 1;		//26-1
	BYTE BuffSelfEnabled : 1;		//26-1
	BYTE SubSkill1Delay : 1;		//26-1
	BYTE SubSkill1Cond : 1;			//26-1
	BYTE SubSkill1PreCond : 1;		//26-1
	BYTE SubSkill1SubCond : 2;		//26-1

	BYTE SubSkill2Delay : 1;		//27-1
	BYTE SubSkill2Cond : 1;			//27-1
	BYTE SubSkill2PreCond : 1;		//27-1
	BYTE SubSkill2SubCond : 2;		//27-1
	BYTE RepairItem : 1;			//27-1
	BYTE PickupAllItems : 1;		//27-1
	BYTE PickupSeletectedItems : 1;	//27-1

	BYTE RavenAttackMode;			//28-1

	BYTE Unnused[36];

	CHAR ItemName1[16];
	CHAR ItemName2[16];
	CHAR ItemName3[16];
	CHAR ItemName4[16];
	CHAR ItemName5[16];
	CHAR ItemName6[16];
	CHAR ItemName7[16];
	CHAR ItemName8[16];
	CHAR ItemName9[16];
	CHAR ItemName10[16];
	CHAR ItemName11[16];
	CHAR ItemName12[16];
};
#pragma pack(pop)
// ------------------------------------------------------------------------------

struct MUHELPER_MACRO_CLIENT//-> Complete
{
	PWMSG_HEAD h;			//-> 0	(4)
	MUHELPER_SETTINGS_PACKET MacroBind;
	//BYTE	MacroBind[257];	//-> 4	(257)
};
// -------------------------------------------------------------------------------

struct MUHELPER_MACRO_DS	//-> Complete
{
	PWMSG_HEAD h;
	int		aIndex;
	char	AccountID[MAX_IDSTRING+1];
	char	Name[MAX_IDSTRING+1];
	BYTE	btResult;
	BYTE	btMacroData[256];
};
// -------------------------------------------------------------------------------

class MUHelper
{
public:
				MUHelper();
	virtual		~MUHelper();
	// ----
	void		Init();
	void		Load();
	// ----
	bool		AddUserData(LPOBJ lpUser);
	// ----
	void		Manager(int UserIndex, MUHELPER_REQ_ACTION * lpRequest);
	void		Start(LPOBJ lpUser);
	void		Work(LPOBJ lpUser);
	void		Close(LPOBJ lpUser);
	// ----
	void		SetStage(LPOBJ lpUser, WORD WorkTime);
	int			GetMoney(LPOBJ lpUser);
	bool		CheckMoney(LPOBJ lpUser);
	void		SendMoney(LPOBJ lpUser, WORD WorkTime);
	// ----
	void		SaveMacro(int UserIndex, MUHELPER_MACRO_CLIENT * lpRequest);
	void		ReqMacro(int UserIndex, bool offlineReq = false);
	void		SendMacro(MUHELPER_MACRO_DS * lpRequest);
	// ----
private:
	short				m_FirstPayInterval;
	short				m_PayInterval;
	short				m_PricePerLevel;
	short				m_PricePerReset;

	std::set<int>		m_OfflineRequested;

	// ----
}; extern MUHelper g_MUHelper;
// -------------------------------------------------------------------------------
#endif