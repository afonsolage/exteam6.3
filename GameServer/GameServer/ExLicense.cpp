#include "StdAfx.h"
#include "ExLicense.h"
#include "VMProtectSDK.h"
#include "wininet.h"
#include "logproc.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "GameMain.h"
#include "PersonalShopEx.h"
#include "ExLicenseClient.h"
#include "UserConfig.h"
#include "CustomSystem.h"

CExLicense g_ExLicense;

CExLicense::CExLicense()
{
	VMBEGIN
	this->Init();
	VMEND
}

CExLicense::~CExLicense()
{
}

void CExLicense::Init()
{
	VMBEGIN
	this->m_Enable = true;
	this->ActiveUser = -1;
	this->Exit = false;
	this->ExitTime = 0;
	this->NewVersion = false;
	this->DrawVersion = false;
	this->m_WaitLicense = false;
	ZeroMemory(this->VersionNum,sizeof(this->VersionNum));
	ZeroMemory(this->VersionDate,sizeof(this->VersionDate));
	this->TextXoR[0] = 0x03;
	this->TextXoR[1] = 0x05;
	this->TextXoR[2] = 0x08;
	VMEND
}

void CExLicense::Load()
{
	VMBEGIN
	this->Init();

	if(!this->m_Enable)
	{
		return;
	}

#if(EXLICENSE_SERVER)
	g_ExLicenseClient.Start();

	int i = 0;

	while(!g_ExLicense.m_WaitLicense)
	{
		if(i == 10)
		{
			ExitProcess(0);
		}
		i++;
		Sleep(1000);
	}
#else
	this->AddList();
	this->CheckLicense();
#endif


	   VMEND
}

#if(!EXLICENSE_SERVER)
void CExLicense::AddList()
{
	if(!this->m_Enable)
	{
		return;
	}

	for(int i = 0; i < TOTAL_CLIENT; i++)
	{
		ZeroMemory(this->List[i].Login, sizeof(this->List[i].Login));
		ZeroMemory(this->List[i].Password, sizeof(this->List[i].Password));
		this->List[i].hwid				= 0;
		this->List[i].mac[0]		= NULL;
		this->List[i].Credit				= 0;
		this->List[i].Baned					= false;
		this->List[i].Rage					= false;
		this->List[i].WinQuest				= false;
		this->List[i].BloodHound			= false;
		this->List[i].MonsterQuest			= false;
		this->List[i].TvTEvent				= false;
		this->List[i].GrandHero				= false;
		this->List[i].PartySystem			= false;
		this->List[i].Brotherhood			= false;
		this->List[i].PartySearch			= false;
		this->List[i].ChatLog				= false;
		this->List[i].GM_Manager			= false;
		this->List[i].PerosnalStoreEx		= false;
		this->List[i].PandoraEvent			= false;
		this->List[i].AntiCheatPlus			= false;
		this->List[i].ComboCustom			= false;
		this->List[i].NpcBuffer				= false;
		this->List[i].BMQuest				= false;
		this->List[i].LoraBattle			= false;
		this->List[i].Smithy				= false;
		this->List[i].Monster				= false;
		this->List[i].ItemSmokeEffect		= false;
		this->List[i].GrandDinamicExp       = false;
		this->List[i].PartySave				= false;
		this->List[i].DisableMasterTree		= false;
		this->List[i].OfflineMode			= false;
		this->List[i].Marriage				= false;
		this->List[i].bRankItem				= false;
		this->List[i].RestoreOffMode		= false;
		this->List[i].MapQuest				= false;
		this->List[i].bTeamVsTeam2          = false;
		this->List[i].bAchievements			= false;
		this->List[i].PremiumEx				= false;
		this->List[i].AccSecurity			= false;
		this->List[i].CraftQuestSystem		= false;
		this->List[i].PickUpItemInfo		= false;
		this->List[i].ReferralSystem		= false;
	}

		strcpy(this->List[eExUB::Local].Login,			"Local");
	this->List[eExUB::Local].hwid					= 2349491840;	// Rusek Local;147494269;Rusek VPS;3595081207
	strcpy(this->List[eExUB::Local].mac,			"00-D8-61-18-B0-EA"); // Rusek Local;08-00-27-15-15-AD;Rusek VPS;00-25-22-A8-A2-9E
		this->List[eExUB::Local].Rage					= true;
		this->List[eExUB::Local].WinQuest				= true;
		this->List[eExUB::Local].BloodHound				= true;
		this->List[eExUB::Local].MonsterQuest			= true;
		this->List[eExUB::Local].TvTEvent				= true;
		this->List[eExUB::Local].GrandHero				= true;
		this->List[eExUB::Local].PartySystem			= true;
		this->List[eExUB::Local].Brotherhood			= true;
		this->List[eExUB::Local].PartySearch			= true;
		this->List[eExUB::Local].ChatLog				= true;
		this->List[eExUB::Local].GM_Manager				= true;
		this->List[eExUB::Local].PerosnalStoreEx		= true;
		this->List[eExUB::Local].PandoraEvent			= true;
		this->List[eExUB::Local].AntiCheatPlus			= true;
		this->List[eExUB::Local].ComboCustom			= true;
		this->List[eExUB::Local].NpcBuffer				= true;
		this->List[eExUB::Local].BMQuest				= true;
		this->List[eExUB::Local].LoraBattle				= true;
		this->List[eExUB::Local].Smithy					= true;
		this->List[eExUB::Local].Monster				= true;
		this->List[eExUB::Local].ItemSmokeEffect		= true;
		this->List[eExUB::Local].GrandDinamicExp		= true;
		this->List[eExUB::Local].PartySave				= true;
		this->List[eExUB::Local].DisableMasterTree		= true;
		this->List[eExUB::Local].OfflineMode			= true;
		this->List[eExUB::Local].Marriage				= true;
		this->List[eExUB::Local].bRankItem				= true;
		this->List[eExUB::Local].RestoreOffMode			= true;
		this->List[eExUB::Local].MapQuest				= true;
		this->List[eExUB::Local].bTeamVsTeam2			= true;
		this->List[eExUB::Local].bAchievements			= true;
		this->List[eExUB::Local].PremiumEx				= true;
		this->List[eExUB::Local].AccSecurity			= true;
		this->List[eExUB::Local].CraftQuestSystem		= true;
		this->List[eExUB::Local].PickUpItemInfo			= true;
		this->List[eExUB::Local].ReferralSystem			= true;
	// ----
	strcpy(this->List[eExUB::drynea].Login,			"drynea");
	this->List[eExUB::drynea].hwid				= 1922075450;
	this->List[eExUB::drynea].Rage					= true;
	this->List[eExUB::drynea].TvTEvent				= true;
	this->List[eExUB::drynea].Monster				= true;
	this->List[eExUB::drynea].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eExUB::t34].Login,			"t34");
	this->List[eExUB::t34].hwid					= 1352569343;
	// ----
	strcpy(this->List[eExUB::exgames].Login,		"exgames");
	this->List[eExUB::exgames].hwid				= 183346987;
	this->List[eExUB::exgames].Rage					= true;
	// ----
	strcpy(this->List[eExUB::Gints].Login,			"Gints");
	this->List[eExUB::Gints].hwid					= 524162253;//524162253;
	this->List[eExUB::Gints].Rage					= true;
	this->List[eExUB::Gints].PartySystem			= true;
	this->List[eExUB::Gints].MonsterQuest			= true;
	this->List[eExUB::Gints].AntiCheatPlus			= true;
	this->List[eExUB::Gints].ComboCustom			= true;
	this->List[eExUB::Gints].Brotherhood			= true;
	this->List[eExUB::Gints].NpcBuffer				= true;
	this->List[eExUB::Gints].Monster				= true;
	this->List[eExUB::Gints].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eExUB::SaneaMD].Login,		"SaneaMD");
	this->List[eExUB::SaneaMD].hwid				= 807882591;//3859230483;
	this->List[eExUB::SaneaMD].Rage					= true;
	// ----
	strcpy(this->List[eExUB::MarksSevcuks].Login,	"MarksSevcuks");
	this->List[eExUB::MarksSevcuks].hwid			= 3760116472;
	// ----
	strcpy(this->List[eExUB::SILVER1].Login,		"SILVER1");
	this->List[eExUB::SILVER1].hwid					= 2162254266; // 3237505581;
	this->List[eExUB::SILVER1].Rage					= true;
	this->List[eExUB::SILVER1].TvTEvent				= true;
	this->List[eExUB::SILVER1].Brotherhood			= true;
	this->List[eExUB::SILVER1].PartySearch			= true;
	this->List[eExUB::SILVER1].PartySystem			= true;
	this->List[eExUB::SILVER1].ChatLog				= true;
	this->List[eExUB::SILVER1].GM_Manager			= true;
	this->List[eExUB::SILVER1].PerosnalStoreEx		= true;
	this->List[eExUB::SILVER1].PartySave			= true;
	this->List[eExUB::SILVER1].Smithy				= true;
	this->List[eExUB::SILVER1].OfflineMode			= true;
	this->List[eExUB::SILVER1].bRankItem			= true;
	this->List[eExUB::SILVER1].bAchievements		= true;
	this->List[eExUB::SILVER1].bTeamVsTeam2			= true;
	this->List[eExUB::SILVER1].GrandDinamicExp		= true;
	this->List[eExUB::SILVER1].RestoreOffMode		= true;
	this->List[eExUB::SILVER1].PremiumEx			= true;
	// ----
	strcpy(this->List[eExUB::SILVER2].Login,		"SILVER2");
	//this->List[eExUB::SILVER2].hwid					= 2502590384;	
	this->List[eExUB::SILVER2].hwid					= 2082356317;	
	strcpy(this->List[eExUB::SILVER2].mac,		"00-0C-29-47-7B-90");
	this->List[eExUB::SILVER2].Rage					= true;
	this->List[eExUB::SILVER2].TvTEvent				= true;
	this->List[eExUB::SILVER2].Brotherhood			= true;
	this->List[eExUB::SILVER2].PartySearch			= true;
	this->List[eExUB::SILVER2].PartySystem			= true;
	this->List[eExUB::SILVER2].ChatLog				= true;
	this->List[eExUB::SILVER2].GM_Manager			= true;
	this->List[eExUB::SILVER2].PerosnalStoreEx		= true;
	this->List[eExUB::SILVER2].PartySave			= true;
	this->List[eExUB::SILVER2].Smithy				= true;
	this->List[eExUB::SILVER2].OfflineMode			= true;
	this->List[eExUB::SILVER2].bRankItem			= true;
	this->List[eExUB::SILVER2].bAchievements		= true;
	this->List[eExUB::SILVER2].bTeamVsTeam2			= true;
	this->List[eExUB::SILVER2].GrandDinamicExp		= true;
	this->List[eExUB::SILVER2].RestoreOffMode		= true;
	this->List[eExUB::SILVER2].PremiumEx			= true;
	// ----
	strcpy(this->List[eExUB::Vadim].Login,			"Vadim");
	this->List[eExUB::Vadim].hwid					= 99415930;
	this->List[eExUB::Vadim].Rage					= true;
	// ----
	strcpy(this->List[eExUB::DavitRazmadze].Login, "DavitRazmadze");
	this->List[eExUB::DavitRazmadze].hwid			= 620282224;//2494879713;
	strcpy(this->List[eExUB::thinnakorn].mac,		"00-0C-29-69-6F-EA");
	this->List[eExUB::DavitRazmadze].ItemSmokeEffect		= true;
	this->List[eExUB::DavitRazmadze].Monster		= true;
	this->List[eExUB::DavitRazmadze].AntiCheatPlus		= true;
	this->List[eExUB::DavitRazmadze].TvTEvent		= true;
	this->List[eExUB::DavitRazmadze].bAchievements		= true;
	// ----
	strcpy(this->List[eExUB::lemiks].Login,			"lemiks");
	this->List[eExUB::lemiks].hwid				= 3029767103;
	this->List[eExUB::lemiks].GrandHero				= true;
	this->List[eExUB::lemiks].Brotherhood			= true;
	this->List[eExUB::lemiks].Monster				= true;
	this->List[eExUB::lemiks].ItemSmokeEffect		= true;
	this->List[eExUB::lemiks].MonsterAttackLife		= true;
	this->List[eExUB::lemiks].GrandDinamicExp		= true;
	// ----
	strcpy(this->List[eExUB::spoke].Login,			"spoke");
	this->List[eExUB::spoke].hwid					= 2461314075;
	this->List[eExUB::spoke].Monster				= true;
	// ----
	strcpy(this->List[eExUB::Daboy_1].Login,		"Daboy_1");
	this->List[eExUB::Daboy_1].hwid				= 1081550485;
	// ----
	strcpy(this->List[eExUB::Daboy_2].Login,		"Daboy_2");
	this->List[eExUB::Daboy_2].hwid				= 3102437392;
	// ----
	strcpy(this->List[eExUB::Encode].Login,			"Encode");
	this->List[eExUB::Encode].hwid				= 2664824880;
	// ----
	strcpy(this->List[eExUB::Pavel].Login,			"Pavel");
	this->List[eExUB::Pavel].hwid					= 1745027016;
	// ----
	strcpy(this->List[eExUB::PrideMu].Login,		"PrideMu");
	this->List[eExUB::PrideMu].hwid				= 1;	//136373629
	//List[eExUB::PrideMu].Rage						= true;
	//List[eExUB::PrideMu].MonsterQuest				= true;
	//List[eExUB::PrideMu].TvTEvent					= true;
	//List[eExUB::PrideMu].GrandHero				= true;
	this->List[eExUB::PrideMu].Monster				= true;
	this->List[eExUB::PrideMu].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eExUB::Cherkashin].Login,		"Cherkashin");
	this->List[eExUB::Cherkashin].hwid			= 3422826830;
	this->List[eExUB::Cherkashin].Monster			= true;
	// ----
	strcpy(this->List[eExUB::Semushkin].Login,		"Semushkin");
	this->List[eExUB::Semushkin].hwid				= 2149325968;
	// ----
	strcpy(this->List[eExUB::Gints_2].Login,		"Gints_2");
	this->List[eExUB::Gints_2].hwid				= 2556587903;
	this->List[eExUB::Gints_2].Rage					= true;
	this->List[eExUB::Gints_2].GrandHero			= true;
	this->List[eExUB::Gints_2].PartySystem			= true;
	this->List[eExUB::Gints_2].MonsterQuest			= true;
	this->List[eExUB::Gints_2].AntiCheatPlus		= true;
	this->List[eExUB::Gints_2].ComboCustom			= true;
	this->List[eExUB::Gints_2].Brotherhood			= true;
	this->List[eExUB::Gints_2].NpcBuffer			= true;
	this->List[eExUB::Gints_2].Monster				= true;
	this->List[eExUB::Gints_2].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eExUB::zerocool].Login,		"zerocool");
	this->List[eExUB::zerocool].hwid				= 3358746164;
	// ----
	strcpy(this->List[eExUB::Vadim_2].Login,		"Vadim_2");
	this->List[eExUB::Vadim_2].hwid				= 1684392689;
	// ----
	strcpy(this->List[eExUB::ulasevich].Login,		"ulasevich");
	this->List[eExUB::ulasevich].hwid				= 471417973;// 3632441894;
	strcpy(this->List[eExUB::Artem].mac,			"00-25-22-C2-E0-AF");
	this->List[eExUB::ulasevich].BloodHound			= true;
	this->List[eExUB::ulasevich].Rage				= true;
	this->List[eExUB::ulasevich].MonsterQuest		= true;
	this->List[eExUB::ulasevich].Brotherhood		= true;
	this->List[eExUB::ulasevich].AntiCheatPlus		= true;
	this->List[eExUB::ulasevich].BMQuest			= true;
	this->List[eExUB::ulasevich].PandoraEvent		= true;
	this->List[eExUB::ulasevich].bRankItem			= true;
	this->List[eExUB::ulasevich].PremiumEx			= true;
	this->List[eExUB::ulasevich].Smithy				= true;
	this->List[eExUB::ulasevich].OfflineMode		= true;
	this->List[eExUB::ulasevich].PerosnalStoreEx	= true;
	// ----
	strcpy(this->List[eExUB::Local2].Login,			"Local2");
	this->List[eExUB::Local2].hwid					= 3962621275;
	this->List[eExUB::Local2].Rage					= true;
	this->List[eExUB::Local2].BloodHound			= true;
	this->List[eExUB::Local2].MonsterQuest			= true;
	this->List[eExUB::Local2].TvTEvent				= true;
	this->List[eExUB::Local2].GrandHero				= true;
	// ----
	strcpy(this->List[eExUB::DavitRazmadze2].Login, "DavitRazmadze2");
	this->List[eExUB::DavitRazmadze2].hwid		= 3496675938;
	this->List[eExUB::DavitRazmadze2].ItemSmokeEffect		= true;
	this->List[eExUB::DavitRazmadze2].Monster		= true;
	this->List[eExUB::DavitRazmadze2].AntiCheatPlus		= true;
	this->List[eExUB::DavitRazmadze2].TvTEvent		= true;
	this->List[eExUB::DavitRazmadze2].bAchievements		= true;
	// ----
	strcpy(this->List[eExUB::DavitRazmadze3].Login, "DavitRazmadze3");
	this->List[eExUB::DavitRazmadze3].hwid		= 2361010737;
	this->List[eExUB::DavitRazmadze3].ItemSmokeEffect		= true;
	this->List[eExUB::DavitRazmadze3].Monster		= true;
	this->List[eExUB::DavitRazmadze3].AntiCheatPlus		= true;
	this->List[eExUB::DavitRazmadze3].TvTEvent		= true;
	this->List[eExUB::DavitRazmadze3].bAchievements		= true;
	// ----
	strcpy(this->List[eExUB::PrideMuLocal].Login,	"PrideMuLocal");
	this->List[eExUB::PrideMuLocal].hwid			= 102821109;
	this->List[eExUB::PrideMuLocal].Rage			= true;
	this->List[eExUB::PrideMuLocal].MonsterQuest	= true;
	this->List[eExUB::PrideMuLocal].TvTEvent		= true;
	this->List[eExUB::PrideMuLocal].GrandHero		= true;
	this->List[eExUB::PrideMuLocal].Monster			= true;
	this->List[eExUB::PrideMuLocal].ItemSmokeEffect	= true;
	// ----
	strcpy(this->List[eExUB::lexbzk].Login,			"lexbzk");
	this->List[eExUB::lexbzk].hwid				= 308214326;
	// ----
	strcpy(this->List[eExUB::Local3].Login,			"Local3");
	this->List[eExUB::Local3].hwid				= 1518866620;
	this->List[eExUB::Local3].Rage					= true;
	this->List[eExUB::Local3].MonsterQuest			= true;
	this->List[eExUB::Local3].TvTEvent				= true;
	this->List[eExUB::Local3].GrandHero				= true;
	// ----
	//strcpy(this->List[eExUB::DavitRazmadze3].Login, "DavitRazmadze3");
	//this->List[eExUB::DavitRazmadze3].hwid		= 370104553;
	//this->List[eExUB::DavitRazmadze3].Monster		= true;
	//this->List[eExUB::DavitRazmadze3].AntiCheatPlus		= true;
	// ----
	strcpy(this->List[eExUB::snaker].Login,			"snaker");
	this->List[eExUB::snaker].hwid				= 4230177721;
	this->List[eExUB::snaker].Rage					= true;
	this->List[eExUB::snaker].MonsterQuest			= true;
	this->List[eExUB::snaker].TvTEvent				= true;
	this->List[eExUB::snaker].GrandHero				= true;
	this->List[eExUB::snaker].Monster				= true;
	this->List[eExUB::snaker].ItemSmokeEffect		= true;
	// ----
	strcpy(this->List[eExUB::testuser].Login,		"testuser");
	this->List[eExUB::testuser].hwid				= 3834831223;
	// ----
	strcpy(this->List[eExUB::Gredy].Login,			"Gredy");
	this->List[eExUB::Gredy].hwid					= 1009564418;	//1009564418
	this->List[eExUB::Gredy].TvTEvent				= true;
	this->List[eExUB::Gredy].PerosnalStoreEx		= true;
	this->List[eExUB::Gredy].GM_Manager				= true;
	this->List[eExUB::Gredy].AntiCheatPlus			= true;
	this->List[eExUB::Gredy].SpotReturn				= true;
	this->List[eExUB::Gredy].PandoraEvent			= true;
	this->List[eExUB::Gredy].LoraBattle				= true;
	this->List[eExUB::Gredy].Smithy					= true;
	this->List[eExUB::Gredy].GrandDinamicExp		= true;
	//this->List[eExUB::Gredy].DisableMasterTree		= true;
	this->List[eExUB::Gredy].Rage					= true;
	this->List[eExUB::Gredy].OfflineMode			= true;
	this->List[eExUB::Gredy].Monster				= true;
	this->List[eExUB::Gredy].Marriage				= true;
	this->List[eExUB::Gredy].NpcBuffer				= true;
	this->List[eExUB::Gredy].bRankItem				= true;
	this->List[eExUB::Gredy].RestoreOffMode			= true;
	this->List[eExUB::Gredy].PartySave				= true;
	this->List[eExUB::Gredy].PartySearch			= true;
	this->List[eExUB::Gredy].GrandHero				= true;
	this->List[eExUB::Gredy].MonsterQuest			= true;
	this->List[eExUB::Gredy].MapQuest				= true;
	this->List[eExUB::Gredy].bAchievements			= true;
	this->List[eExUB::Gredy].PremiumEx				= true;
	this->List[eExUB::Gredy].PartySystem			= true;
	this->List[eExUB::Gredy].bTeamVsTeam2			= true;
	this->List[eExUB::Gredy].ItemSmokeEffect		= true;
	this->List[eExUB::Gredy].AccSecurity			= true;
	this->List[eExUB::Gredy].CraftQuestSystem		= true;
	// ----
	strcpy(this->List[eExUB::GredyLocal].Login,		"GredyLocal");
	this->List[eExUB::GredyLocal].hwid				= 443216415;
	this->List[eExUB::GredyLocal].TvTEvent			= true;
	this->List[eExUB::GredyLocal].PerosnalStoreEx	= true;
	this->List[eExUB::GredyLocal].GM_Manager		= true;
	this->List[eExUB::GredyLocal].AntiCheatPlus		= true;
	this->List[eExUB::GredyLocal].SpotReturn		= true;
	this->List[eExUB::GredyLocal].PandoraEvent		= true;
	this->List[eExUB::GredyLocal].LoraBattle		= true;
	this->List[eExUB::GredyLocal].Smithy			= true;
	this->List[eExUB::GredyLocal].GrandDinamicExp	= true;
	//this->List[eExUB::GredyLocal].DisableMasterTree	= true;
	this->List[eExUB::GredyLocal].Rage				= true;
	this->List[eExUB::GredyLocal].OfflineMode		= true;
	this->List[eExUB::GredyLocal].Monster			= true;
	this->List[eExUB::GredyLocal].Marriage			= true;
	this->List[eExUB::GredyLocal].NpcBuffer			= true;
	this->List[eExUB::GredyLocal].bRankItem			= true;
	this->List[eExUB::GredyLocal].RestoreOffMode	= true;
	this->List[eExUB::GredyLocal].PartySave			= true;
	this->List[eExUB::GredyLocal].PartySearch		= true;
	this->List[eExUB::GredyLocal].GrandHero			= true;
	this->List[eExUB::GredyLocal].MonsterQuest		= true;
	this->List[eExUB::GredyLocal].MapQuest			= true;
	this->List[eExUB::GredyLocal].bAchievements		= true;
	this->List[eExUB::GredyLocal].PremiumEx			= true;
	this->List[eExUB::GredyLocal].PartySystem		= true;
	this->List[eExUB::GredyLocal].bTeamVsTeam2		= true;
	this->List[eExUB::GredyLocal].ItemSmokeEffect	= true;
	this->List[eExUB::GredyLocal].AccSecurity		= true;
	this->List[eExUB::GredyLocal].CraftQuestSystem	= true;
	// ----
	strcpy(this->List[eExUB::Gredy2].Login,			"Gredy2");
	this->List[eExUB::Gredy2].hwid					= 3761286172;	// 1309694294;
	this->List[eExUB::Gredy2].TvTEvent				= true;
	this->List[eExUB::Gredy2].PerosnalStoreEx		= true;
	this->List[eExUB::Gredy2].GM_Manager			= true;
	this->List[eExUB::Gredy2].AntiCheatPlus			= true;
	this->List[eExUB::Gredy2].SpotReturn			= true;
	this->List[eExUB::Gredy2].PandoraEvent			= true;
	this->List[eExUB::Gredy2].LoraBattle			= true;
	this->List[eExUB::Gredy2].Smithy				= true;
	this->List[eExUB::Gredy2].GrandDinamicExp		= true;
	//this->List[eExUB::Gredy2].DisableMasterTree		= true;
	this->List[eExUB::Gredy2].Rage					= true;
	this->List[eExUB::Gredy2].OfflineMode			= true;
	this->List[eExUB::Gredy2].Monster				= true;
	this->List[eExUB::Gredy2].Marriage				= true;
	this->List[eExUB::Gredy2].NpcBuffer				= true;
	this->List[eExUB::Gredy2].bRankItem				= true;
	this->List[eExUB::Gredy2].RestoreOffMode		= true;
	this->List[eExUB::Gredy2].PartySave				= true;
	this->List[eExUB::Gredy2].PartySearch			= true;
	this->List[eExUB::Gredy2].GrandHero				= true;
	this->List[eExUB::Gredy2].MonsterQuest			= true;
	this->List[eExUB::Gredy2].MapQuest				= true;
	this->List[eExUB::Gredy2].bAchievements			= true;
	this->List[eExUB::Gredy2].PremiumEx				= true;
	this->List[eExUB::Gredy2].PartySystem			= true;
	this->List[eExUB::Gredy2].bTeamVsTeam2			= true;
	this->List[eExUB::Gredy2].ItemSmokeEffect		= true;
	this->List[eExUB::Gredy2].AccSecurity			= true;
	this->List[eExUB::Gredy2].CraftQuestSystem		= true;
	// ----
	strcpy(this->List[eExUB::Pavel2].Login,			"Pavel2");
	this->List[eExUB::Pavel2].hwid					= 2691024834;
	// ----
	strcpy(this->List[eExUB::ulasevich2].Login,		"ulasevich2");
	this->List[eExUB::ulasevich2].hwid				= 71422912;
	this->List[eExUB::ulasevich2].BloodHound		= true;
	this->List[eExUB::ulasevich2].Rage				= true;
	this->List[eExUB::ulasevich2].MonsterQuest		= true;
	this->List[eExUB::ulasevich2].Brotherhood		= true;
	this->List[eExUB::ulasevich2].AntiCheatPlus		= true;
	this->List[eExUB::ulasevich2].BMQuest			= true;
	this->List[eExUB::ulasevich2].PandoraEvent		= true;
	this->List[eExUB::ulasevich2].bRankItem			= true;
	this->List[eExUB::ulasevich2].PremiumEx			= true;
	this->List[eExUB::ulasevich2].Smithy			= true;
	this->List[eExUB::ulasevich2].OfflineMode		= true;
	this->List[eExUB::ulasevich2].PerosnalStoreEx	= true;
	// ----
	//strcpy(this->List[eExUB::feqan].Login,			"feqan");
	//this->List[eExUB::feqan].hwid					= 1521036435;
	//this->List[eExUB::feqan].PartySystem			= true;
	// ----
	strcpy(this->List[eExUB::Selfmylife].Login,		"Selfmylife");
	this->List[eExUB::Selfmylife].hwid			= 3296873814;
	// ----
	strcpy(this->List[eExUB::NoCustom].Login,		"NoCustom");
	this->List[eExUB::NoCustom].hwid				= 1188528199;
	// ----
	strcpy(this->List[eExUB::ConflictNoCustom].Login,"ConflictNoCustom");
	this->List[eExUB::ConflictNoCustom].hwid		= 2492754898;
	this->List[eExUB::ConflictNoCustom].TvTEvent	= true;
	this->List[eExUB::ConflictNoCustom].PandoraEvent= true;
	// ----
	strcpy(List[eExUB::Emanuel].Login,				"Emanuel");
	List[eExUB::Emanuel].hwid						= 4196649766;
	// ----
	strcpy(this->List[eExUB::maksim844495].Login,	"maksim844495");
	this->List[eExUB::maksim844495].hwid			= 136373629;
	this->List[eExUB::maksim844495].AntiCheatPlus	= true;
	// ----
	strcpy(this->List[eExUB::SILVER_Local].Login,		"SILVER_Local");
	this->List[eExUB::SILVER_Local].hwid				= 0;	// 3237505581;
	this->List[eExUB::SILVER_Local].Rage				= true;
	this->List[eExUB::SILVER_Local].TvTEvent			= true;
	this->List[eExUB::SILVER_Local].Brotherhood			= true;
	this->List[eExUB::SILVER_Local].PartySearch			= true;
	this->List[eExUB::SILVER_Local].PartySystem			= true;
	this->List[eExUB::SILVER_Local].ChatLog				= true;
	this->List[eExUB::SILVER_Local].GM_Manager			= true;
	this->List[eExUB::SILVER_Local].PerosnalStoreEx		= true;
	this->List[eExUB::SILVER_Local].PartySave			= true;
	this->List[eExUB::SILVER_Local].Smithy				= true;
	this->List[eExUB::SILVER_Local].OfflineMode			= true;
	this->List[eExUB::SILVER_Local].bAchievements		= true;
	this->List[eExUB::SILVER_Local].GrandDinamicExp		= true;
	this->List[eExUB::SILVER_Local].RestoreOffMode		= true;


	// ----
	strcpy(this->List[eExUB::Matias].Login,				"Matias");
	this->List[eExUB::Matias].hwid					= 1578038406;
	// ----
	strcpy(this->List[eExUB::MMProduction].Login,		"MMProduction");
	this->List[eExUB::MMProduction].hwid				=	NULL;	//	37123;	<<-- License double disable
	
	//strcpy(this->List[eExUB::absolute].Login,			"absolute");
	//this->List[eExUB::absolute].hwid					= 2349598538;	//1578038406;
	//strcpy(this->List[eExUB::absolute].mac,	"00-15-5D-22-70-34");
	//this->List[eExUB::absolute].PartySearch				= true;
	//this->List[eExUB::absolute].PartySystem				= true;
	//this->List[eExUB::absolute].ChatLog					= true;
	//this->List[eExUB::absolute].GrandHero				= true;
	//this->List[eExUB::absolute].GM_Manager				= true;
	//this->List[eExUB::absolute].PerosnalStoreEx			= true;
	//this->List[eExUB::absolute].AntiCheatPlus			= true;
	////this->List[eExUB::absolute].Smithy				= true;
	//this->List[eExUB::absolute].Monster					= true;
	//this->List[eExUB::absolute].ItemSmokeEffect			= true;
	//this->List[eExUB::absolute].PartySave				= true;
	//this->List[eExUB::absolute].OfflineMode				= true;

	strcpy(this->List[eExUB::DICE].Login,			"DICE");
	this->List[eExUB::DICE].hwid					= 2730446961;	// 2730446961;	//1578038406;
	strcpy(this->List[eExUB::DICE].mac,		"0C-8B-FD-E3-98-05");

	strcpy(this->List[eExUB::Artem].Login,			"Artem");
	this->List[eExUB::Artem].hwid					= 1111188280;	//	 2529125018;	// |D5-C5-AC-A8-EF-C1 это с нового хостинга
	strcpy(this->List[eExUB::Artem].mac,			"D5-C5-AC-A8-EF-C1");
	this->List[eExUB::Artem].TvTEvent				= true;
	this->List[eExUB::Artem].PerosnalStoreEx		= true;
	this->List[eExUB::Artem].GM_Manager				= true;
	this->List[eExUB::Artem].AntiCheatPlus			= true;
	this->List[eExUB::Artem].SpotReturn				= true;
	this->List[eExUB::Artem].PandoraEvent			= true;
	this->List[eExUB::Artem].LoraBattle				= true;
	this->List[eExUB::Artem].Smithy					= true;
	this->List[eExUB::Artem].GrandDinamicExp		= true;
	this->List[eExUB::Artem].DisableMasterTree		= true;
	this->List[eExUB::Artem].Rage					= true;
	this->List[eExUB::Artem].OfflineMode			= true;
	this->List[eExUB::Artem].Monster				= true;
	this->List[eExUB::Artem].Marriage				= true;
	this->List[eExUB::Artem].PartySave				= true;
	this->List[eExUB::Artem].bTeamVsTeam2			= true;
	this->List[eExUB::Artem].bRankItem				= true;
	this->List[eExUB::Artem].MonsterAttackLife		= true;
	this->List[eExUB::Artem].RestoreOffMode			= true;
	this->List[eExUB::Artem].PartySearch			= true;
	this->List[eExUB::Artem].bAchievements			= true;
	this->List[eExUB::Artem].MonsterQuest			= true;
	this->List[eExUB::Artem].PremiumEx				= true;
	this->List[eExUB::Artem].PartySystem			= true;
	this->List[eExUB::Artem].Marriage				= true;
	this->List[eExUB::Artem].AccSecurity			= true;
	this->List[eExUB::Artem].ReferralSystem			= true;
	this->List[eExUB::Artem].NpcBuffer				= true;

	strcpy(this->List[eExUB::Artem2].Login,			"Artem2");
	this->List[eExUB::Artem2].hwid					= 37123;	//37123
	//strcpy(this->List[eExUB::Artem2].mac,			"FD-50-78-1A-FE-13");
	this->List[eExUB::Artem2].TvTEvent				= true;
	this->List[eExUB::Artem2].PerosnalStoreEx		= true;
	this->List[eExUB::Artem2].GM_Manager			= true;
	this->List[eExUB::Artem2].AntiCheatPlus			= true;
	this->List[eExUB::Artem2].SpotReturn			= true;
	this->List[eExUB::Artem2].PandoraEvent			= true;
	this->List[eExUB::Artem2].LoraBattle			= true;
	this->List[eExUB::Artem2].Smithy				= true;
	this->List[eExUB::Artem2].GrandDinamicExp		= true;
	this->List[eExUB::Artem2].DisableMasterTree		= true;
	this->List[eExUB::Artem2].Rage					= true;
	this->List[eExUB::Artem2].OfflineMode			= true;
	this->List[eExUB::Artem2].Monster				= true;
	this->List[eExUB::Artem2].Marriage				= true;
	this->List[eExUB::Artem2].PartySave				= true;
	this->List[eExUB::Artem2].bTeamVsTeam2			= true;
	this->List[eExUB::Artem2].bRankItem				= true;
	this->List[eExUB::Artem2].MonsterAttackLife		= true;
	this->List[eExUB::Artem2].RestoreOffMode		= true;
	this->List[eExUB::Artem2].PartySearch			= true;
	this->List[eExUB::Artem2].bAchievements			= true;
	this->List[eExUB::Artem2].MonsterQuest			= true;
	this->List[eExUB::Artem2].PremiumEx				= true;
	this->List[eExUB::Artem2].PartySystem			= true;
	this->List[eExUB::Artem2].Marriage				= true;
	this->List[eExUB::Artem2].AccSecurity			= true;
	this->List[eExUB::Artem2].ReferralSystem		= true;
	this->List[eExUB::Artem2].NpcBuffer				= true;


	strcpy(this->List[eExUB::MedoniAndrei].Login,	"MedoniAndrei");
	this->List[eExUB::MedoniAndrei].hwid			= 2630807982;// 2262655649;	//3760173629
	strcpy(this->List[eExUB::MedoniAndrei].mac,		"A9-40-37-E5-1B-8D");
	this->List[eExUB::MedoniAndrei].OfflineMode     = true;
	this->List[eExUB::MedoniAndrei].PerosnalStoreEx	= true;
	this->List[eExUB::MedoniAndrei].Monster			= true;
	this->List[eExUB::MedoniAndrei].MonsterAttackLife = true;
	this->List[eExUB::MedoniAndrei].Brotherhood		= true;
	this->List[eExUB::MedoniAndrei].AntiCheatPlus	= true;
	this->List[eExUB::MedoniAndrei].TvTEvent		= true;
	this->List[eExUB::MedoniAndrei].ItemSmokeEffect	= true;
	//this->List[eExUB::MedoniAndrei].Rage			= true;
	this->List[eExUB::MedoniAndrei].bTeamVsTeam2	= true;
	this->List[eExUB::MedoniAndrei].bRankItem		= true;
	this->List[eExUB::MedoniAndrei].PremiumEx		= true;
	this->List[eExUB::MedoniAndrei].AccSecurity		= true;
	this->List[eExUB::MedoniAndrei].PartySearch		= true;
	this->List[eExUB::MedoniAndrei].ReferralSystem  = true;
	this->List[eExUB::MedoniAndrei].GrandDinamicExp = true;
	this->List[eExUB::MedoniAndrei].PartySave		= true;
	this->List[eExUB::MedoniAndrei].CraftQuestSystem = true;
	this->List[eExUB::MedoniAndrei].PickUpItemInfo = true;

	//strcpy(this->List[eExUB::SirJ].Login,	"SirJ");
	//this->List[eExUB::SirJ].hwid			= 2349598538;

	strcpy(this->List[eExUB::Eduardo].Login,	"Eduardo");
	this->List[eExUB::Eduardo].hwid				= 3489763032;
	this->List[eExUB::Eduardo].AntiCheatPlus	= true;
	this->List[eExUB::Eduardo].NpcBuffer		= true;

	strcpy(this->List[eExUB::bassreflexive].Login,	"bassreflexive");
	this->List[eExUB::bassreflexive].hwid			= 176480702;// 3825993254;
	this->List[eExUB::bassreflexive].PerosnalStoreEx	= true;
	this->List[eExUB::bassreflexive].OfflineMode	= true;
	this->List[eExUB::bassreflexive].Rage		= true;

	strcpy(this->List[eExUB::MU2Play].Login,			"MU2Play");
	//this->List[eExUB::MU2Play].hwid						= 3324969216;	// 3324969216;	//2349598538;
	//strcpy(this->List[eExUB::MU2Play].mac,				"02-19-5D-22-71-D1");
	this->List[eExUB::MU2Play].PartySearch				= true;
	this->List[eExUB::MU2Play].PartySystem				= true;
	this->List[eExUB::MU2Play].GM_Manager				= true;
	this->List[eExUB::MU2Play].PerosnalStoreEx			= true;
	this->List[eExUB::MU2Play].AntiCheatPlus			= true;
	this->List[eExUB::MU2Play].Rage						= true;
	this->List[eExUB::MU2Play].Monster					= true;
	this->List[eExUB::MU2Play].PartySave				= true;
	this->List[eExUB::MU2Play].OfflineMode				= true;
	this->List[eExUB::MU2Play].bRankItem				= true;
	this->List[eExUB::MU2Play].MonsterAttackLife		= true;
	this->List[eExUB::MU2Play].GrandDinamicExp			= true;
	this->List[eExUB::MU2Play].RestoreOffMode			= true;
	this->List[eExUB::MU2Play].bTeamVsTeam2				= true;

	strcpy(this->List[eExUB::Stone].Login,	"Stone");
	this->List[eExUB::Stone].hwid			= 2628301467;	//370104553;
	strcpy(this->List[eExUB::Stone].mac,				"02-00-00-38-40-23");
	this->List[eExUB::Stone].bTeamVsTeam2				= true;

	strcpy(this->List[eExUB::Sentinel].Login,			"Sentinel");
	this->List[eExUB::Sentinel].hwid					= 1521036435;
	this->List[eExUB::Sentinel].PartySearch				= true;
	this->List[eExUB::Sentinel].PartySystem				= true;
	this->List[eExUB::Sentinel].ChatLog					= true;
	this->List[eExUB::Sentinel].GM_Manager				= true;
	this->List[eExUB::Sentinel].PerosnalStoreEx			= true;
	this->List[eExUB::Sentinel].AntiCheatPlus			= true;
	this->List[eExUB::Sentinel].Rage					= true;
	this->List[eExUB::Sentinel].Monster					= true;
	this->List[eExUB::Sentinel].ItemSmokeEffect			= true;
	this->List[eExUB::Sentinel].PartySave				= true;
	this->List[eExUB::Sentinel].OfflineMode				= true;
	this->List[eExUB::Sentinel].bRankItem				= true;
	this->List[eExUB::Sentinel].MonsterAttackLife		= true;
	this->List[eExUB::Sentinel].GrandDinamicExp			= true;
	this->List[eExUB::Sentinel].RestoreOffMode			= true;
	this->List[eExUB::Sentinel].GrandHero				= true;
	this->List[eExUB::Sentinel].bTeamVsTeam2			= true;

	strcpy(this->List[eExUB::Almdar].Login,				"Almdar");
	this->List[eExUB::Almdar].hwid						= 2764084540;	//2764084540
	this->List[eExUB::Almdar].AntiCheatPlus				= true;
	this->List[eExUB::Almdar].PerosnalStoreEx			= true;
	this->List[eExUB::Almdar].GM_Manager				= true;

	strcpy(this->List[eExUB::thinnakorn].Login,			"thinnakorn");
	this->List[eExUB::thinnakorn].hwid					= 2756002743;
	strcpy(this->List[eExUB::thinnakorn].mac,			"00-0C-29-A1-0B-3E");
	this->List[eExUB::thinnakorn].AntiCheatPlus			= true;
	this->List[eExUB::thinnakorn].Rage					= true;
	this->List[eExUB::thinnakorn].Smithy				= true;
	this->List[eExUB::thinnakorn].OfflineMode			= true;
	this->List[eExUB::thinnakorn].ComboCustom			= true;

	strcpy(this->List[eExUB::EpicMU].Login,				"EpicMU");
	this->List[eExUB::EpicMU].hwid						= 2633646976;	// 2633646976;// 2633646976;
	strcpy(this->List[eExUB::EpicMU].mac,				"00-15-5D-00-F1-9E");
	this->List[eExUB::EpicMU].Rage						= true;
	this->List[eExUB::EpicMU].PartySystem				= true;
	this->List[eExUB::EpicMU].PartySearch				= true;
	this->List[eExUB::EpicMU].ChatLog					= true;
	this->List[eExUB::EpicMU].GM_Manager				= true;
	this->List[eExUB::EpicMU].PerosnalStoreEx			= true;
	this->List[eExUB::EpicMU].AntiCheatPlus				= true;
	this->List[eExUB::EpicMU].LoraBattle				= true;
	this->List[eExUB::EpicMU].Monster					= true;
	this->List[eExUB::EpicMU].ItemSmokeEffect			= true;
	this->List[eExUB::EpicMU].PartySave					= true;
	//this->List[eExUB::EpicMU].DisableMasterTree			= true;
	this->List[eExUB::EpicMU].OfflineMode				= true;
	this->List[eExUB::EpicMU].MonsterAttackLife			= true;
	this->List[eExUB::EpicMU].bRankItem					= true;
	this->List[eExUB::EpicMU].RestoreOffMode			= true;
	this->List[eExUB::EpicMU].bTeamVsTeam2				= true;
	this->List[eExUB::EpicMU].bAchievements				= true;
	this->List[eExUB::EpicMU].MonsterQuest				= true;
	this->List[eExUB::EpicMU].PremiumEx					= true;
	this->List[eExUB::EpicMU].BMQuest					= true;
	this->List[eExUB::EpicMU].Brotherhood				= true;
	this->List[eExUB::EpicMU].Rage						= true;
	this->List[eExUB::EpicMU].Marriage					= true;
	this->List[eExUB::EpicMU].Smithy					= true;

	strcpy(this->List[eExUB::masonX].Login,				"masonX");
	this->List[eExUB::masonX].hwid						= 1356980851;
	//strcpy(this->List[eExUB::masonX].mac,			"DF-FE-FA-BB-AE-58");
	this->List[eExUB::masonX].PartySystem				= true;
	this->List[eExUB::masonX].PerosnalStoreEx				= true;
	this->List[eExUB::masonX].PartySearch				= true;
	this->List[eExUB::masonX].PremiumEx				= true;

	strcpy(this->List[eExUB::MatiasLeiva].Login,		"MatiasLeiva");
	this->List[eExUB::MatiasLeiva].hwid					= 3028269993;
	strcpy(this->List[eExUB::MatiasLeiva].mac,			"00-50-56-04-83-04");
	
	strcpy(this->List[eExUB::AlterMU].Login,		"AlterMU");
	this->List[eExUB::AlterMU].hwid					= 3324969216;
	strcpy(this->List[eExUB::AlterMU].mac,			"02-27-D6-00-02-0D");
	this->List[eExUB::AlterMU].PartySystem				= true;
	this->List[eExUB::AlterMU].PartySearch				= true;
	this->List[eExUB::AlterMU].ChatLog					= true;
	this->List[eExUB::AlterMU].GM_Manager				= true;
	this->List[eExUB::AlterMU].PerosnalStoreEx			= true;
	this->List[eExUB::AlterMU].AntiCheatPlus			= true;
	this->List[eExUB::AlterMU].Monster					= true;
	this->List[eExUB::AlterMU].ItemSmokeEffect			= true;
	this->List[eExUB::AlterMU].PartySave				= true;
	this->List[eExUB::AlterMU].DisableMasterTree		= true;
	this->List[eExUB::AlterMU].OfflineMode				= true;
	this->List[eExUB::AlterMU].MonsterAttackLife		= true;
	this->List[eExUB::AlterMU].RestoreOffMode			= true;
	this->List[eExUB::AlterMU].bAchievements			= true;	
	this->List[eExUB::AlterMU].GrandHero				= true;	

	strcpy(this->List[eExUB::Almdar2].Login,			"Almdar2");
	this->List[eExUB::Almdar2].hwid						= 2756002743;	//2764084540
	strcpy(this->List[eExUB::Almdar2].mac,				"74-D4-35-FE-B7-24");
	this->List[eExUB::Almdar2].AntiCheatPlus			= true;
	this->List[eExUB::Almdar2].PerosnalStoreEx			= true;
	this->List[eExUB::Almdar2].GM_Manager				= true;
	//1087360052

	strcpy(this->List[eExUB::Escalate].Login,			"Escalate");
	this->List[eExUB::Escalate].hwid					= 3302700294;	//2633646976;
	strcpy(this->List[eExUB::Escalate].mac,				"02-12-5D-00-45-90");
	this->List[eExUB::Escalate].PartySearch				= true;
	this->List[eExUB::Escalate].PartySystem				= true;
	this->List[eExUB::Escalate].GM_Manager				= true;
	this->List[eExUB::Escalate].PerosnalStoreEx			= true;
	this->List[eExUB::Escalate].AntiCheatPlus			= true;
	this->List[eExUB::Escalate].Rage					= true;
	this->List[eExUB::Escalate].Monster					= true;
	this->List[eExUB::Escalate].PartySave				= true;
	this->List[eExUB::Escalate].OfflineMode				= true;
	this->List[eExUB::Escalate].bRankItem				= true;
	this->List[eExUB::Escalate].MonsterAttackLife		= true;
	this->List[eExUB::Escalate].GrandDinamicExp			= true;
	this->List[eExUB::Escalate].RestoreOffMode			= true;
	this->List[eExUB::Escalate].bTeamVsTeam2			= true;
	this->List[eExUB::Escalate].LoraBattle				= true;	//OK
	//this->List[eExUB::Escalate].Smithy					= true;	//OK
	this->List[eExUB::Escalate].ItemSmokeEffect			= true;	//OK
	this->List[eExUB::Escalate].PandoraEvent			= true;	//OK
	this->List[eExUB::Escalate].OfflineMode				= true;
	this->List[eExUB::Escalate].bAchievements			= true;
	this->List[eExUB::Escalate].AccSecurity				= true;
	this->List[eExUB::Escalate].PremiumEx				= true;
	this->List[eExUB::Escalate].ComboCustom				= true;

	strcpy(this->List[eExUB::RafaelLorenzet].Login,		"RafaelLorenzet");
	this->List[eExUB::RafaelLorenzet].hwid				= 2282774568;	//2633646976;
	strcpy(this->List[eExUB::RafaelLorenzet].mac,		"00-15-5D-1E-17-05");

	strcpy(this->List[eExUB::TGBA_LLC].Login,			"TGBA_LLC");
	this->List[eExUB::TGBA_LLC].hwid					= 3324969216;	//2633646976;
	strcpy(this->List[eExUB::TGBA_LLC].mac,				"00-01-5D-D7-04-C1");
	this->List[eExUB::TGBA_LLC].Monster					= true;
	this->List[eExUB::TGBA_LLC].bAchievements			= true;
	this->List[eExUB::TGBA_LLC].MonsterQuest			= true;
	
	strcpy(this->List[eExUB::RevoMU].Login,				"RevoMU");
	//this->List[eExUB::RevoMU].hwid						= 1918130772;
	this->List[eExUB::RevoMU].hwid						= 3324969216;	//3324969216;	// 1918130772;
	strcpy(this->List[eExUB::RevoMU].mac,				"02-05-5D-CD-04-73");
	this->List[eExUB::RevoMU].bAchievements				= true;
	this->List[eExUB::RevoMU].OfflineMode				= true;
	this->List[eExUB::RevoMU].PerosnalStoreEx			= true;
	this->List[eExUB::RevoMU].PartySystem				= true;
	this->List[eExUB::RevoMU].PartySearch				= true;
	this->List[eExUB::RevoMU].ChatLog					= true;
	this->List[eExUB::RevoMU].GM_Manager				= true;
	this->List[eExUB::RevoMU].PartySave					= true;
	this->List[eExUB::RevoMU].RestoreOffMode			= true;
	this->List[eExUB::RevoMU].PremiumEx					= true;
	this->List[eExUB::RevoMU].AccSecurity				= true;
	this->List[eExUB::RevoMU].MonsterQuest				= true;

	strcpy(this->List[eExUB::DrXAOS].Login,				"DrXAOS");
	this->List[eExUB::DrXAOS].hwid						= 2153285885;
	strcpy(this->List[eExUB::DrXAOS].mac,				"97-67-23-65-5A-0A");

	strcpy(this->List[eExUB::masonX2].Login,				"masonX");
	this->List[eExUB::masonX2].hwid						= 473466670;
	strcpy(this->List[eExUB::masonX2].mac,				"A6-A1-04-8F-7C-F2");
	this->List[eExUB::masonX2].PartySystem				= true;
	this->List[eExUB::masonX2].PerosnalStoreEx			= true;
	this->List[eExUB::masonX2].PartySearch				= true;
	this->List[eExUB::masonX2].PremiumEx				= true;

	strcpy(this->List[eExUB::GloryMU].Login,				"GloryMU");
	//this->List[eExUB::GloryMU].hwid						= 3302700294;
	//strcpy(this->List[eExUB::GloryMU].mac,			"02-0E-5D-00-3E-4F");
	this->List[eExUB::GloryMU].GrandHero				= true;
	this->List[eExUB::GloryMU].PartySystem				= true;
	this->List[eExUB::GloryMU].PartySearch				= true;
	this->List[eExUB::GloryMU].ChatLog					= true;
	this->List[eExUB::GloryMU].GM_Manager				= true;
	this->List[eExUB::GloryMU].PerosnalStoreEx			= true;
	this->List[eExUB::GloryMU].ComboCustom				= false;
	this->List[eExUB::GloryMU].NpcBuffer				= false;
	this->List[eExUB::GloryMU].LoraBattle				= true;
	this->List[eExUB::GloryMU].Smithy					= true;
	this->List[eExUB::GloryMU].Monster					= true;
	this->List[eExUB::GloryMU].ItemSmokeEffect			= true;
	this->List[eExUB::GloryMU].GrandDinamicExp			= true;
	this->List[eExUB::GloryMU].PartySave				= true;
	this->List[eExUB::GloryMU].DisableMasterTree		= true;
	this->List[eExUB::GloryMU].OfflineMode				= true;
	this->List[eExUB::GloryMU].bRankItem				= false;
	this->List[eExUB::GloryMU].RestoreOffMode			= true;
	this->List[eExUB::GloryMU].bTeamVsTeam2				= false;
	this->List[eExUB::GloryMU].bAchievements			= true;
	this->List[eExUB::GloryMU].PremiumEx				= true;
	this->List[eExUB::GloryMU].AccSecurity				= true;
	this->List[eExUB::GloryMU].CraftQuestSystem			= true;
	this->List[eExUB::GloryMU].PickUpItemInfo			= false;
	this->List[eExUB::GloryMU].ReferralSystem			= 0;

	strcpy(this->List[eExUB::MuRelic].Login,				"MuRelic");	//vlad vlad
	this->List[eExUB::MuRelic].hwid						= 0;
	//strcpy(this->List[eExUB::MuRelic].mac,			"00-15-5D-06-41-F8");
	this->List[eExUB::MuRelic].GrandHero				= true;

	strcpy(this->List[eExUB::ArcMu].Login,				"ArcMu");
	this->List[eExUB::ArcMu].hwid						= 697983919;
	strcpy(this->List[eExUB::ArcMu].mac,				"A4-BF-01-23-8E-D3");
	this->List[eExUB::ArcMu].Rage						= true;
	this->List[eExUB::ArcMu].Monster					= true;
	this->List[eExUB::ArcMu].ItemSmokeEffect			= true;
	this->List[eExUB::ArcMu].MonsterQuest				= true;//
	this->List[eExUB::ArcMu].GrandHero					= true;
	this->List[eExUB::ArcMu].TvTEvent					= true;
	this->List[eExUB::ArcMu].PartySystem				= true;
	this->List[eExUB::ArcMu].Brotherhood				= false;
	this->List[eExUB::ArcMu].PartySearch				= true;
	this->List[eExUB::ArcMu].PerosnalStoreEx			= true;
	this->List[eExUB::ArcMu].CraftQuestSystem			= true;
	this->List[eExUB::ArcMu].NpcBuffer					= true;
	this->List[eExUB::ArcMu].ComboCustom				= false;
	this->List[eExUB::ArcMu].MonsterAttackLife			= true;
	this->List[eExUB::ArcMu].PandoraEvent				= true;
	this->List[eExUB::ArcMu].Smithy						= true;
	this->List[eExUB::ArcMu].bRankItem					= true;
	this->List[eExUB::ArcMu].bAchievements				= true;
	this->List[eExUB::ArcMu].RestoreOffMode				= true;
	this->List[eExUB::ArcMu].AccSecurity				= true;

#if(LICENSE_ARCMU)
	this->List[eExUB::ArcMu].bTeamVsTeam2				= true;
	this->List[eExUB::ArcMu].LoraBattle					= true;
	this->List[eExUB::ArcMu].GM_Manager					= true;
	this->List[eExUB::ArcMu].MapQuest					= true;
	this->List[eExUB::ArcMu].PremiumEx					= true;
	this->List[eExUB::ArcMu].BloodHound					= true;
	this->List[eExUB::ArcMu].Brotherhood				= true;
	this->List[eExUB::ArcMu].Marriage					= true;
	this->List[eExUB::ArcMu].PartySave					= true;
	this->List[eExUB::ArcMu].OfflineMode				= true;
#endif

	strcpy(this->List[eExUB::muheroia].Login,				"muheroia");
	this->List[eExUB::muheroia].hwid						= 3302700294;
	strcpy(this->List[eExUB::muheroia].mac,			"02-12-5D-00-45-DF");

	strcpy(this->List[eExUB::HomeLan].Login,				"HomeLan");
	//this->List[eExUB::HomeLan].hwid						= 3302700294;
	//strcpy(this->List[eExUB::HomeLan].mac,			"02-12-5D-00-45-DF");

	strcpy(this->List[eExUB::ProtectDebug].Login,				"ProtectDebug");
	//this->List[eExUB::ProtectDebug].hwid						= ProtectDebug;
	//strcpy(this->List[eExUB::ProtectDebug].mac,			"02-12-5D-00-45-DF");
	this->List[eExUB::ProtectDebug].OfflineMode				= true;
	this->List[eExUB::ProtectDebug].RestoreOffMode			= true;
	this->List[eExUB::ProtectDebug].PerosnalStoreEx			= true;

	strcpy(this->List[eExUB::UpdateDebug].Login,		"UpdateDebug");
	//this->List[eExUB::UpdateDebug].hwid					= 0;
	//strcpy(this->List[eExUB::UpdateDebug].mac,			"60-A4-4C-2B-45-03");
	this->List[eExUB::UpdateDebug].Credit				= 0;
	this->List[eExUB::UpdateDebug].Baned				= false;
	this->List[eExUB::UpdateDebug].Rage					= true;
	this->List[eExUB::UpdateDebug].WinQuest				= 0;
	this->List[eExUB::UpdateDebug].BloodHound			= true;
	this->List[eExUB::UpdateDebug].MonsterQuest			= true;
	this->List[eExUB::UpdateDebug].TvTEvent				= true;
	this->List[eExUB::UpdateDebug].GrandHero			= true;
	this->List[eExUB::UpdateDebug].PartySystem			= true;
	this->List[eExUB::UpdateDebug].Brotherhood			= true;
	this->List[eExUB::UpdateDebug].PartySearch			= true;
	this->List[eExUB::UpdateDebug].ChatLog				= true;
	this->List[eExUB::UpdateDebug].GM_Manager			= true;
	this->List[eExUB::UpdateDebug].PerosnalStoreEx		= true;
	this->List[eExUB::UpdateDebug].PandoraEvent			= true;
	this->List[eExUB::UpdateDebug].AntiCheatPlus		= true;
	this->List[eExUB::UpdateDebug].ComboCustom			= true;
	this->List[eExUB::UpdateDebug].NpcBuffer			= true;
	this->List[eExUB::UpdateDebug].BMQuest				= true;
	this->List[eExUB::UpdateDebug].LoraBattle			= true;
	this->List[eExUB::UpdateDebug].Smithy				= true;
	this->List[eExUB::UpdateDebug].Monster				= true;
	this->List[eExUB::UpdateDebug].ItemSmokeEffect		= true;
	this->List[eExUB::UpdateDebug].GrandDinamicExp      = true;
	this->List[eExUB::UpdateDebug].PartySave			= true;
	this->List[eExUB::UpdateDebug].DisableMasterTree	= true;
	this->List[eExUB::UpdateDebug].OfflineMode			= true;
	this->List[eExUB::UpdateDebug].Marriage				= true;
	this->List[eExUB::UpdateDebug].bRankItem			= true;
	this->List[eExUB::UpdateDebug].RestoreOffMode		= true;
	this->List[eExUB::UpdateDebug].MapQuest				= true;
	this->List[eExUB::UpdateDebug].bTeamVsTeam2         = true;
	this->List[eExUB::UpdateDebug].bAchievements		= true;
	this->List[eExUB::UpdateDebug].PremiumEx			= true;
	this->List[eExUB::UpdateDebug].AccSecurity			= true;
	this->List[eExUB::UpdateDebug].CraftQuestSystem		= true;
	this->List[eExUB::UpdateDebug].PickUpItemInfo		= true;
	this->List[eExUB::UpdateDebug].ReferralSystem		= true;
	
	strcpy(this->List[eExUB::MegaM].Login,		"MegaM");
	this->List[eExUB::MegaM].hwid					= 3226014109;
	strcpy(this->List[eExUB::MegaM].mac,			"02-11-5D-00-6B-C4");
	this->List[eExUB::MegaM].MonsterQuest			= true;
	this->List[eExUB::MegaM].bTeamVsTeam2			= true;

	strcpy(this->List[eExUB::mu4you].Login,			"mu4you");
	this->List[eExUB::mu4you].hwid					= 3302700294;
	strcpy(this->List[eExUB::mu4you].mac,			"02-0E-5D-00-3E-4F");
	this->List[eExUB::mu4you].PartySearch			= true;
	this->List[eExUB::mu4you].PartySystem			= true;
	this->List[eExUB::mu4you].GM_Manager			= true;
	this->List[eExUB::mu4you].PerosnalStoreEx		= true;
	this->List[eExUB::mu4you].AntiCheatPlus			= true;
	this->List[eExUB::mu4you].Rage					= true;
	this->List[eExUB::mu4you].Monster				= true;
	this->List[eExUB::mu4you].PartySave				= true;
	this->List[eExUB::mu4you].OfflineMode			= true;
	this->List[eExUB::mu4you].bRankItem				= true;
	this->List[eExUB::mu4you].MonsterAttackLife		= true;
	this->List[eExUB::mu4you].GrandDinamicExp		= true;
	this->List[eExUB::mu4you].RestoreOffMode		= true;
	this->List[eExUB::mu4you].bTeamVsTeam2			= true;
	this->List[eExUB::mu4you].LoraBattle			= true;
	this->List[eExUB::mu4you].ItemSmokeEffect		= true;
	this->List[eExUB::mu4you].PandoraEvent			= true;
	this->List[eExUB::mu4you].OfflineMode			= true;
	this->List[eExUB::mu4you].bAchievements			= true;
	this->List[eExUB::mu4you].AccSecurity			= true;
	this->List[eExUB::mu4you].PremiumEx				= true;
	this->List[eExUB::mu4you].ComboCustom			= true;

	strcpy(this->List[eExUB::eternalmu].Login,			"eternalmu");
	this->List[eExUB::eternalmu].hwid					= 3302700294;
	strcpy(this->List[eExUB::eternalmu].mac,		"00-15-5D-04-F0-D3");
	this->List[eExUB::eternalmu].PartySearch				= true;
	this->List[eExUB::eternalmu].PartySystem				= true;
	this->List[eExUB::eternalmu].GM_Manager				= true;
	this->List[eExUB::eternalmu].PerosnalStoreEx			= true;
	this->List[eExUB::eternalmu].AntiCheatPlus			= true;
	this->List[eExUB::eternalmu].Rage					= true;
	this->List[eExUB::eternalmu].Monster					= true;
	this->List[eExUB::eternalmu].PartySave				= true;
	this->List[eExUB::eternalmu].OfflineMode				= true;
	this->List[eExUB::eternalmu].bRankItem				= true;
	this->List[eExUB::eternalmu].MonsterAttackLife		= true;
	this->List[eExUB::eternalmu].GrandDinamicExp			= true;
	this->List[eExUB::eternalmu].RestoreOffMode			= true;
	this->List[eExUB::eternalmu].bTeamVsTeam2			= true;
	this->List[eExUB::eternalmu].LoraBattle				= true;	//OK
	//this->List[eExUB::eternalmu].Smithy					= true;	//OK
	this->List[eExUB::eternalmu].ItemSmokeEffect			= true;	//OK
	this->List[eExUB::eternalmu].PandoraEvent			= true;	//OK
	this->List[eExUB::eternalmu].OfflineMode				= true;
	this->List[eExUB::eternalmu].bAchievements			= true;
	this->List[eExUB::eternalmu].AccSecurity				= true;
	this->List[eExUB::eternalmu].PremiumEx				= true;
	this->List[eExUB::eternalmu].ComboCustom				= true;

	strcpy(this->List[eExUB::WarBorn].Login,			"WarBorn");
	this->List[eExUB::WarBorn].hwid					= 3971232786;
	strcpy(this->List[eExUB::WarBorn].mac,			"02-0E-5D-00-3E-58");
	this->List[eExUB::WarBorn].PartySearch			= true;
	this->List[eExUB::WarBorn].PartySystem			= true;
	this->List[eExUB::WarBorn].GM_Manager			= true;
	this->List[eExUB::WarBorn].PerosnalStoreEx		= true;
	this->List[eExUB::WarBorn].AntiCheatPlus		= true;
	this->List[eExUB::WarBorn].Rage					= true;
	this->List[eExUB::WarBorn].Monster				= true;
	this->List[eExUB::WarBorn].PartySave			= true;
	this->List[eExUB::WarBorn].OfflineMode			= true;
	this->List[eExUB::WarBorn].bRankItem			= true;
	this->List[eExUB::WarBorn].MonsterAttackLife	= true;
	this->List[eExUB::WarBorn].GrandDinamicExp		= true;
	this->List[eExUB::WarBorn].RestoreOffMode		= true;
	this->List[eExUB::WarBorn].bTeamVsTeam2			= true;
	this->List[eExUB::WarBorn].LoraBattle			= true;
	this->List[eExUB::WarBorn].ItemSmokeEffect		= true;
	this->List[eExUB::WarBorn].PandoraEvent			= true;
	this->List[eExUB::WarBorn].OfflineMode			= true;
	this->List[eExUB::WarBorn].bAchievements		= true;
	this->List[eExUB::WarBorn].AccSecurity			= true;
	this->List[eExUB::WarBorn].PremiumEx			= true;
	this->List[eExUB::WarBorn].ComboCustom			= true;

	strcpy(this->List[eExUB::NSGames].Login,			"NSGames");
	this->List[eExUB::NSGames].hwid					= 3971232786;
	strcpy(this->List[eExUB::NSGames].mac,			"00-15-5D-05-84-FA");
	this->List[eExUB::NSGames].PartySearch			= true;
	this->List[eExUB::NSGames].PartySystem			= true;
	this->List[eExUB::NSGames].GM_Manager			= true;
	this->List[eExUB::NSGames].PerosnalStoreEx		= true;
	this->List[eExUB::NSGames].AntiCheatPlus			= true;
	this->List[eExUB::NSGames].Rage					= true;
	this->List[eExUB::NSGames].Monster				= true;
	this->List[eExUB::NSGames].PartySave				= true;
	this->List[eExUB::NSGames].OfflineMode			= true;
	this->List[eExUB::NSGames].bRankItem				= true;
	this->List[eExUB::NSGames].MonsterAttackLife		= true;
	this->List[eExUB::NSGames].GrandDinamicExp		= true;
	this->List[eExUB::NSGames].RestoreOffMode		= true;
	this->List[eExUB::NSGames].bTeamVsTeam2			= true;
	this->List[eExUB::NSGames].LoraBattle			= true;
	this->List[eExUB::NSGames].ItemSmokeEffect		= true;
	this->List[eExUB::NSGames].PandoraEvent			= true;
	this->List[eExUB::NSGames].OfflineMode			= true;
	this->List[eExUB::NSGames].bAchievements			= true;
	this->List[eExUB::NSGames].AccSecurity			= true;
	this->List[eExUB::NSGames].PremiumEx				= true;
	this->List[eExUB::NSGames].ComboCustom			= true;
	this->List[eExUB::NSGames].DisableMasterTree			= true;
}

void CExLicense::CheckLicense()
{
#if(_DISABLE_LICENSE)
	//return;
#endif
#if(EXLICENSE_SELECT)
	//this->SelectLicense(eExUB::NSGames);
	//this->SelectLicense(eExUB::eternalmu);
	return;
#endif

//#if(THINNAKORN_MAC)
	strcpy(this->user.Login,		"CustomSystem");
	strcpy(this->user.Password,		"");
	this->user.hwid					= 0;
	this->user.mac[0]				= NULL;
	this->user.Credit				= 0;
	this->user.Baned				= false;
	this->user.Rage					= g_CustomSystem.IsRage();
	this->user.WinQuest				= g_CustomSystem.IsWinQuest();
	this->user.BloodHound			= g_CustomSystem.IsBloodHound();
	this->user.MonsterQuest			= g_CustomSystem.IsMonsterQuest();
	this->user.TvTEvent				= g_CustomSystem.IsTvTEvent();
	this->user.GrandHero			= g_CustomSystem.IsGrandHero();
	this->user.PartySystem			= g_CustomSystem.IsPartySystem();
	this->user.Brotherhood			= g_CustomSystem.IsBrotherhood();
	this->user.PartySearch			= g_CustomSystem.IsPartySearch();
	this->user.ChatLog				= g_CustomSystem.IsChatLog();
	this->user.GM_Manager			= g_CustomSystem.IsGM_Manager();
	this->user.PerosnalStoreEx		= g_CustomSystem.IsPerosnalStoreEx();
	this->user.PandoraEvent			= g_CustomSystem.IsPandoraEvent();
	this->user.AntiCheatPlus		= g_CustomSystem.IsAntiCheatPlus();
	this->user.ComboCustom			= g_CustomSystem.IsComboCustom();
	this->user.NpcBuffer			= g_CustomSystem.IsNpcBuffer();
	this->user.BMQuest				= g_CustomSystem.IsBMQuest();
	this->user.LoraBattle			= g_CustomSystem.IsLoraBattle();
	this->user.Smithy				= g_CustomSystem.IsSmithy();
	this->user.Monster				= g_CustomSystem.IsMonster();
	this->user.ItemSmokeEffect		= g_CustomSystem.IsItemSmokeEffect();
	this->user.GrandDinamicExp		= g_CustomSystem.IsGrandDinamicExp();
	this->user.PartySave			= g_CustomSystem.IsPartySave();
	this->user.DisableMasterTree	= g_CustomSystem.IsDisableMasterTree();
	this->user.OfflineMode			= g_CustomSystem.IsOfflineMode();
	this->user.Marriage				= g_CustomSystem.IsMarriage();
	this->user.bRankItem			= g_CustomSystem.IsbRankItem();
	this->user.RestoreOffMode		= g_CustomSystem.IsRestoreOffMode();
	this->user.MapQuest				= g_CustomSystem.IsMapQuest();
	this->user.bTeamVsTeam2			= g_CustomSystem.IsbTeamVsTeam2();
	this->user.bAchievements		= g_CustomSystem.IsbAchievements();
	this->user.PremiumEx			= g_CustomSystem.IsPremiumEx();
	this->user.AccSecurity			= g_CustomSystem.IsAccSecurity();
	this->user.CraftQuestSystem		= g_CustomSystem.IsCraftQuestSystem();
	this->user.PickUpItemInfo		= g_CustomSystem.IsPickUpItemInfo();
	this->user.ReferralSystem		= g_CustomSystem.IsReferralSystem();
	this->user.Enable3DCamera		= g_CustomSystem.Is3DCamera();

	return;
//#endif

#if(LICENSE_EVOMU)
	this->ActiveUser = eExUB::Gredy;
	memcpy(&this->user, &this->List[this->ActiveUser], sizeof(g_ExLicense.user));
	return;
#endif


	VMBEGIN

	bool Result = false; 

	unsigned char MACData[6];
	UUID uuid;
	UuidCreateSequential(&uuid);

	for(int i = 2; i < 8; i++)
	{
		MACData[i-2] = uuid.Data4[i];
	}

	char szMac[18];
	sprintf(szMac, "%02X-%02X-%02X-%02X-%02X-%02X", MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);

	for(int i = 0; i < TOTAL_CLIENT; i++)
	{
		if(this->List[i].mac[0] != NULL)
		{
			if(!strcmp(this->List[i].mac, szMac))
			{
				if(this->List[i].Baned)
				{
					ExitProcess(0);
				}
				this->ActiveUser = i;
				Result = true;
				break;
			}
		}
	}

	if(Result == false)
	{
		unsigned long HDDKEY;
		GetVolumeInformationA(this->GetDecText(DISK_DIR),0,0,&HDDKEY,0,0,0,0); 

		for(int i = 0; i < TOTAL_CLIENT; i++)
		{
			if(HDDKEY == this->List[i].hwid)
			{
				if(this->List[i].Baned)
				{
					ExitProcess(0);
				}
				this->ActiveUser = i;
				Result = true;
				break;
			}
		}
	}

	if(!Result)
	{
		ExitProcess(0);
		return;
	}

	memcpy(&this->user, &this->List[this->ActiveUser], sizeof(g_ExLicense.user));
	VMEND
}
#endif

bool CExLicense::CheckUser(int NeedUser)
{
	if(this->ActiveUser == NeedUser)
	{
		return true;
	}
	return false;
}

void CExLicense::GCLicenseUser(int aIndex)
{
	VMBEGIN
	PMSG_LICENSE_DATA rSend;
	rSend.h.set((LPBYTE)&rSend, 0xFB, 17, sizeof(rSend));
	rSend.LicenseUser = this->ActiveUser;
	memcpy(&rSend.base, &this->user, sizeof(g_ExLicense.user));
	rSend.config.MaxPartyUser = g_MaxPartyMember;
	rSend.config.PersonalEnable = g_PersonalShopEx.Enable;
	rSend.config.PersonalBonus = g_PersonalShopEx.BonusPrice;
	rSend.config.PersonalCredit = g_PersonalShopEx.CreditPrice;
	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
	g_UserConfig.GC_SettingsSend(aIndex);
	VMEND
}
// ----------------------------------------------------------------------------------------------

void CExLicense::GDLicenseUser()
{
	VMBEGIN
	PMSG_LICENSE_DATA rSend;
	rSend.h.set((LPBYTE)&rSend, 0xE3, 0x00, sizeof(rSend));
	rSend.LicenseUser = this->ActiveUser;
	rSend.base = this->user;
	rSend.config.Gens = gGENS;
	cDBSMng.Send((char*)&rSend, sizeof(rSend));
	VMEND
}

char* CExLicense::GetDecText(char* EncodeChar)
{
	int len = strlen(EncodeChar);	
	char* Line = new char[len+1];
	for(int i = 0; i < len; i++)
	{
		Line[i] = char(EncodeChar[i] ^ this->TextXoR[i % 3]);
	}
	Line[len] = 0;
	return Line;
}

void CExLicense::SelectLicense(int UserID)
{
	this->ActiveUser = UserID;
	memcpy(&this->user, &this->List[UserID], sizeof(this->user));
	return;
}

char* CExLicense::GetLicenseName()
{
	if(this->ActiveUser == -1)
	{
		return "Unknown";
	}

	return this->user.Login;
}