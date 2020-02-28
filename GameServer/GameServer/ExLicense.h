#pragma once

#include "StdAfx.h"
#include "protocol.h"
#include "ExLicenseProtocolDefine.h"

//#define EXLICENSE_SERVER		1


#define TOTAL_CLIENT		200
#define EXNEW_VERISON		"New Update:"
#define DISK_DIR			"`?T"										//"c:\\"

/*
Premium Type Interface - 60
Button Reset Rage system - 30
Monster Balans system - 20
*/

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
	FinalMU,
	MUDev,
};

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

struct PMSG_LICENSE_DATA
{
	PBMSG_HEAD2 h;
	short LicenseUser;	
	LICENSE_DATA base;
	CUSTOM_CONFIG config;
};
// ----------------------------------------------------------------------------------------------

class CExLicense
{
public:
		  CExLicense();
		 ~CExLicense();

	void Init();
	void Load();
//#if(!EXLICENSE_SERVER)
	void AddList();
	void CheckLicense();
//#endif
	void GCLicenseUser(int aIndex);
	void GDLicenseUser();
	bool CheckUser(int NeedUser);
	char* GetDecText(char* EncodeChar);
	void SelectLicense(int UserID);

	bool m_WaitLicense;

	bool m_Enable;
	short ActiveUser;
	bool Exit;
	int	 ExitTime;
	bool NewVersion;
	bool DrawVersion;
	char VersionNum[50];
	char VersionDate[50];
	unsigned char TextXoR[3];
	
	LICENSE_DATA user;
//#if(!EXLICENSE_SERVER)
	LICENSE_DATA List[TOTAL_CLIENT];
//#endif

	char* GetLicenseName();
};

extern CExLicense g_ExLicense;