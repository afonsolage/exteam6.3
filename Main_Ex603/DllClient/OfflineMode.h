#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

//Need
//Add RF Skill
//Add Master Skill
//Add GS function skill and pick up

/*
master skill id:
*/

#if(OFFLINE_MODE==TRUE)

enum eIconSkill
{
	eTwistingSlash			= 40,
	eRagefulBlow			= 41,
	eStrikeofDestruction	= 31,
	eEvilSpirit				= 8,
	eInferno				= 13,
	eIceStorm				= 38,
	eTripleShot				= 23,
	eMultiShot				= 96,
	eIceArrow				= 50,
	eChainLightning			= 37,
	eLightningShock			= 38,
	eSpellofPursuit			= 47,
	ePowerSlash				= 55,
	eFireBurst				= 4,
	eFireScream				= 29,
	eChaoticDiseier			= 99,
	eLightingShtorm			= 98,

	//eDragonRoar			= 100,
	//eDarkSide				= 101,
};
// ----------------------------------------------------------------------------------------------

struct CG_OFFMODE_RESULT
{
	PBMSG_HEAD2 h;
	WORD Result;
	BYTE BuffResult;
#if(ADD_OFFMODE_PICKUP==TRUE)
	BYTE bPickZen;
	BYTE bPickJewel;
	BYTE bPickExel;
	BYTE bPickAnc;
#endif
	#if(ADD_OFFMODE_TIMER)
	DWORD TimerMax;
	#endif
};
// ----------------------------------------------------------------------------------------------

struct GC_OFFMODE_CONFIG
{
	PBMSG_HEAD2 h;
	int PriceZen;
	int PriceWcoin;
	int iHourCredit;
	#if(ADD_OFFMODE_TIMER)
	int StandartPlayerTime;
	int OtherPlayerMaxTime;
	int PremiumPlayerMaxTime;
	#endif
};
// ----------------------------------------------------------------------------------------------

class OfflineMode
{
public:
	OfflineMode();
	~OfflineMode();

	void Init();
	void Load();
	void BindImages();
	void Draw();
	void Click(DWORD Event);
	void GCResult();

	void Knight(float sX, float sY);
	void Wizard(float sX, float sY);
	void Elf(float sX, float sY);
	void Summoner(float sX, float sY);
	void Magic(float sX, float sY);
	void Lord(float sX, float sY);
	void Fighter(float sX, float sY);
	int DefaultSkill();
	void ClearSettings();

	int SendSkill;
	int ActiveSkill;
	float ActiveX;
	float ActiveY;
	float TempX;
	float TempY;
	int TempSkill;
	bool bClick;
	DWORD EventTick;

	float High;
	float Whith;
	float standartWhith;
	float standartHight;

	bool AutoBuff;

#if(ADD_OFFMODE_PICKUP==TRUE)
	bool PickZen;
	bool PickJewel;
	bool PickExel;
	bool PickAnc;
#endif

	int PriceZen;
	int PriceWcoin;
	int iHourCredit;


	#if(ADD_OFFMODE_TIMER)
	int m_PlayerTimeHour;
	int m_OtherPlayerMaxTime;
	int m_PremiumPlayerMaxTime;
	#endif

	void GCConfig(GC_OFFMODE_CONFIG* aRecv);
};
// ----------------------------------------------------------------------------------------------
extern OfflineMode g_OfflineMode;
// ----------------------------------------------------------------------------------------------
#endif