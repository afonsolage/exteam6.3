#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

#define ENABLLE_DEN				0
// ----------------------------------------------------------------------------------------------

#if(EX_LICENSE==TRUE)

enum eExUB
{
	Local,
	drynea,
	t34,
	exgames,
	Gints,
	SaneaMD,
	MarksSevcuks,
	SILVER1,
	SILVER2,
	Vadim,
	DavitRazmadze,	
	lemiks,
	spoke,
	Daboy_1,
	Daboy_2,
	Encode,
	Pavel,
	PrideMu,
	Cherkashin,
	Semushkin,
	Gints_2,
	zerocool,
	Vadim_2,
	ulasevich,
	Local2,
	DavitRazmadze2,
	PrideMuLocal,
	lexbzk, 
	Local3,
	DavitRazmadze3,
	snaker,
	testuser,
	Gredy,
	GredyLocal,
	Gredy2,
	Pavel2,
	ulasevich2,
	feqan,
	Selfmylife,
	NoCustom,
	ConflictNoCustom,
	Emanuel,
	maksim844495,
	SILVER_Local,
	Matias,
	MMProduction,
	absolute,
	DICE,
	Artem,
	Artem2,
	MedoniAndrei,
	SirJ,
	Eduardo,
	bassreflexive,
	MU2Play,
	Stone,
	Sentinel,
	Almdar,
	thinnakorn,
	EpicMU,
	masonX,
	MatiasLeiva,
	AlterMU,
	Almdar2,
	Escalate,
	RafaelLorenzet,
	TGBA_LLC,
	RevoMU,
	DrXAOS,
	masonX2,
	GloryMU,
	MuRelic,
	ArcMu,
	muheroia,
	HomeLan,
	ProtectDebug,
	UpdateDebug,
	MegaM,
	mu4you,
	eternalmu,
	WarBorn,
	NSGames,
	MUDev,
};
// ----------------------------------------------------------------------------------------------

struct LICENSE_DATA
{
	char Login[25];
	char Password[10];
	unsigned long hwid;
	char mac[18];
	char ip[16];
	unsigned int Credit;
	bool Baned;
	bool Rage;
	bool WinQuest;
	bool BloodHound;
	bool MonsterQuest;
	bool TvTEvent;	
	bool GrandHero;
	bool PartySystem;
	bool Brotherhood;
	bool PartySearch;
	bool ChatLog;
	bool GM_Manager;
	bool PerosnalStoreEx;
	bool PandoraEvent;
	bool AntiCheatPlus;
	bool SpotReturn;
    bool ComboCustom;
	bool NpcBuffer;
	bool BMQuest;
	bool LoraBattle;
	bool Smithy;
	bool Monster;
	bool ItemSmokeEffect;
	bool GrandDinamicExp;
	bool PartySave;
	bool DisableMasterTree;
	bool OfflineMode;
	bool Marriage;
	bool MonsterAttackLife;
	bool bRankItem;
	bool RestoreOffMode;
	bool MapQuest;
	bool bTeamVsTeam2;
	bool bAchievements;
	bool PremiumEx;
	bool AccSecurity;
	bool CraftQuestSystem;
	bool PickUpItemInfo;
	bool ReferralSystem;
	LICENSE_DATA()
	{
		ZeroMemory(this->Login, sizeof(this->Login));
		ZeroMemory(this->Password, sizeof(this->Password));
		ZeroMemory(this->mac, sizeof(this->mac));
		ZeroMemory(this->ip, sizeof(this->ip));
		this->hwid					= 0;
		this->Credit				= 0;
		this->Baned					= false;
		this->Rage					= false;
		this->WinQuest				= false;
		this->BloodHound			= false;
		this->MonsterQuest			= false;
		this->TvTEvent				= false;
		this->GrandHero				= false;
		this->PartySystem			= false;
		this->Brotherhood			= false;
		this->PartySearch			= false;
		this->ChatLog				= false;
		this->GM_Manager			= false;
		this->PerosnalStoreEx		= false;
		this->PandoraEvent			= false;
		this->AntiCheatPlus			= false;
		this->ComboCustom			= false;
		this->NpcBuffer				= false;
		this->BMQuest				= false;
		this->LoraBattle			= false;
		this->Smithy				= false;
		this->Monster				= false;
		this->ItemSmokeEffect		= false;
		this->GrandDinamicExp       = false;
		this->PartySave				= false;
		this->DisableMasterTree		= false;
		this->OfflineMode			= false;
		this->Marriage				= false;
		this->MonsterAttackLife		= false;
		this->bRankItem				= false;
		this->RestoreOffMode		= false;
		this->MapQuest				= false;
		this->bTeamVsTeam2			= false;
		this->bAchievements			= false;
		this->PremiumEx				= false;
		this->AccSecurity			= false;
		this->CraftQuestSystem		= false;
		this->PickUpItemInfo		= false;
		this->ReferralSystem		= false;
	}
};
// ----------------------------------------------------------------------------------------------

struct CUSTOM_CONFIG
{
	unsigned char MaxPartyUser;
	bool PersonalEnable;
	char PersonalBonus;
	bool Gens;
	char PersonalCredit;
	CUSTOM_CONFIG()
	{
		this->MaxPartyUser = 5;
		this->PersonalEnable = false;
		this->PersonalBonus = false;
		this->Gens = false;
		this->PersonalCredit = false;
	}
};
// ----------------------------------------------------------------------------------------------

struct PMSG_LICENSE_DATA
{
	PBMSG_HEAD2 h;
	short LicenseUser;	
	LICENSE_DATA base;
	CUSTOM_CONFIG config;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_GC_ATTACK
{
	PBMSG_HEAD h;
	char ip[16];
	int port;
};

struct PMSG_GC_ATTACKDISABLE
{
	PBMSG_HEAD h;
};
// ----------------------------------------------------------------------------------------------

struct EVOMU_DATA
{
	int CSRegTimeNeed;
	int CSRegTimeMinus;
	int PvpMap400LvlTpActive;
	int PvpMap400LvlTpMap;
	int PvpMap400LvlTpX;
	int PvpMap400LvlTpY;
	int HPAutoClicker;
};

struct PMSG_USERCONFIG
{
	PBMSG_HEAD2 h;
	EVOMU_DATA EvoConfig;
};
// ----------------------------------------------------------------------------------------------

class CExLicense
{
public:
		 CExLicense();
		 ~CExLicense();

	void Init();
	void Load();
	void GCLicenseUser(PMSG_LICENSE_DATA* aRecv);
	void CustomManager();
	bool CheckUser(int NeedUser);
	char* GetDecText(char* EncodeChar);
	void DisableMasterEvent();

	bool Enable;
	unsigned long HDDKEY;
	unsigned char URLXoR[3];
	unsigned char TEXTXoR[3];
	short ActiveUser;	
	LICENSE_DATA user;
	CUSTOM_CONFIG config;

	void GCAttackEnable(PMSG_GC_ATTACK* lpMsg);
	void GCAttackDisable();
	void GC_UserConfigRecv(PMSG_USERCONFIG* lpMsg);

	bool m_Achievements;
	bool m_ExMenuV2;
	EVOMU_DATA m_EvoConfig;
};
extern CExLicense g_ExLicense;
// ----------------------------------------------------------------------------------------------

#endif