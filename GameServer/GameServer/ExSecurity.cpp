#include "StdAfx.h"
#include "ExLicense.h"
#include "VMProtectSDK.h"
#include "wininet.h"
// -------------------------------------------------------------------------------
//
//bool g_CustomSystem.IsRage()			= false;
//bool g_ExLicense.user.WinQuest			= false;
//bool g_ExLicense.user.BloodHound			= false;
//bool g_ExLicense.user.MonsterQuest = false;
//bool g_ExLicense.user.TvTEvent			= false;
//bool g_ExLicense.user.GrandHero			= false;
//bool g_ExLicense.user.PartySystem			= false;
//bool g_ExLicense.user.Brotherhood			= false;
//bool g_ExLicense.user.PartySearch			= false;
//bool g_ExLicense.user.ChatLog				= false;
//bool g_ExLicense.user.GM_Manager			= false;
//bool g_ExLicense.user.PerosnalStoreEx		= false;
//bool g_ExLicense.user.PandoraEvent			= false;
//
//// -------------------------------------------------------------------------------
//
//exSecurity g_ExLicense;
//// -------------------------------------------------------------------------------
//
//exSecurity::exSecurity()
//{
//	this->Active = FALSE;
//	this->Exit = FALSE;
//	this->ExitTime = 0;
//	// ----
//	ZeroMemory(this->Client,sizeof(this->Client));
//	// ----
//	for(int i=0; i < TOTAL_CLIENT; i++)
//	{
//		this->Client[i].BloodHound = false;
//		this->Client[i].MonsterQuest = false;
//		this->Client[i].TvTEvent = false;
//		this->Client[i].GrandHero = false;
//		this->Client[i].PartySystem = false;
//		this->Client[i].Brotherhood = false;
//		this->Client[i].PartySearch = false;
//		this->Client[i].ChatLog = false;
//		this->Client[i].GM_Manager = false;
//		this->Client[i].PerosnalStoreEx = false;
//		this->Client[i].PandoraEvent = false;
//	}
//	// ----
//	this->NewVersion = false;
//	this->DrawVersion = false;
//	ZeroMemory(this->VersionNum,sizeof(this->VersionNum));
//	ZeroMemory(this->VersionDate,sizeof(this->VersionDate));
//	ZeroMemory(this->VersionInfo,sizeof(this->VersionInfo));
//	// ----
//	GetVolumeInformationA(DISK_DIR,0,0,&this->HDDKEY,0,0,0,0); 
//	// -> Client List
//	this->Client[eExUB::Local].hdd_id = 3089297256;
//	this->Client[eExUB::Local].Rage = true;
//	this->Client[eExUB::Local].WinQuest = false;
//	this->Client[eExUB::Local].BloodHound = true;
//	this->Client[eExUB::Local].MonsterQuest = true;
//	this->Client[eExUB::Local].TvTEvent = true;
//	this->Client[eExUB::Local].GrandHero = true;
//	this->Client[eExUB::Local].Brotherhood = true;
//	this->Client[eExUB::Local].PartySystem = true;
//	this->Client[eExUB::Local].PartySearch = true;
//	this->Client[eExUB::Local].ChatLog = true;
//	this->Client[eExUB::Local].GM_Manager = true;
//	this->Client[eExUB::Local].PerosnalStoreEx  = true;
//	// ----
//	this->Client[eExUB::drynea].hdd_id = 1922075450;
//	this->Client[eExUB::drynea].Rage = true;
//	this->Client[eExUB::drynea].WinQuest = false;
//	this->Client[eExUB::drynea].TvTEvent = true;
//	//-----
//	this->Client[eExUB::t34].hdd_id = 1352569343;
//	this->Client[eExUB::t34].Rage = false;
//	this->Client[eExUB::t34].WinQuest = false;
//	// ----
//	this->Client[eExUB::exgames].hdd_id = 183346987;
//	this->Client[eExUB::exgames].Rage = true;
//	this->Client[eExUB::exgames].WinQuest = false;
//	// ----
//	this->Client[eExUB::Gints].hdd_id = 524162253;
//	this->Client[eExUB::Gints].Rage = true;
//	this->Client[eExUB::Gints].WinQuest = false;
//	this->Client[eExUB::Gints].PartySystem = true;
//	this->Client[eExUB::Gints].MonsterQuest = true;
//	// ----
//	this->Client[eExUB::SaneaMD].hdd_id = 3859230483;
//	this->Client[eExUB::SaneaMD].Rage = true;
//	this->Client[eExUB::SaneaMD].WinQuest = false;
//	// ----
//	this->Client[eExUB::MarksSevcuks].hdd_id = 3760116472;
//	this->Client[eExUB::MarksSevcuks].Rage = false;
//	this->Client[eExUB::MarksSevcuks].WinQuest = false;
//	// ----
//	this->Client[eExUB::SILVER1].hdd_id = 1288505913;
//	this->Client[eExUB::SILVER1].Rage = true;
//	this->Client[eExUB::SILVER1].WinQuest = false;
//	this->Client[eExUB::SILVER1].TvTEvent = true;
//	this->Client[eExUB::SILVER1].Brotherhood = true;
//	this->Client[eExUB::SILVER1].PartySearch = true;
//	this->Client[eExUB::SILVER1].PartySystem = true;
//	this->Client[eExUB::SILVER1].ChatLog = true;
//	this->Client[eExUB::SILVER1].GM_Manager = true;
//	this->Client[eExUB::SILVER1].PerosnalStoreEx  = true;
//	// ----
//	this->Client[eExUB::SILVER2].hdd_id = 673163226;
//	this->Client[eExUB::SILVER2].Rage =  true;
//	this->Client[eExUB::SILVER2].WinQuest = false;
//	this->Client[eExUB::SILVER2].TvTEvent = true;
//	this->Client[eExUB::SILVER2].Brotherhood = true;
//	this->Client[eExUB::SILVER2].PartySearch = true;
//	this->Client[eExUB::SILVER2].PartySystem = true;
//	this->Client[eExUB::SILVER2].ChatLog = true;
//	this->Client[eExUB::SILVER2].GM_Manager = true;
//	this->Client[eExUB::SILVER2].PerosnalStoreEx  = true;
//	// ----
//	this->Client[eExUB::Vadim].hdd_id = 99415930;
//	this->Client[eExUB::Vadim].Rage = true;
//	this->Client[eExUB::Vadim].WinQuest = false;
//	// ----
//	this->Client[eExUB::DavitRazmadze].hdd_id = 738563841;
//	this->Client[eExUB::DavitRazmadze].Rage = false;
//	this->Client[eExUB::DavitRazmadze].WinQuest = false;
//	// ----
//	this->Client[eExUB::lemiks].hdd_id = 3029767103;
//	this->Client[eExUB::lemiks].Rage = false;
//	this->Client[eExUB::lemiks].WinQuest = false;
//	this->Client[eExUB::lemiks].GrandHero = true;
//	// ----
//	this->Client[eExUB::spoke].hdd_id = 2461314075;
//	this->Client[eExUB::spoke].Rage = false;
//	this->Client[eExUB::spoke].WinQuest = false;	
//	// ----
//	this->Client[eExUB::Daboy_1].hdd_id = 1081550485;
//	this->Client[eExUB::Daboy_1].Rage = false;
//	this->Client[eExUB::Daboy_1].WinQuest = false;
//	// ----
//	this->Client[eExUB::Daboy_2].hdd_id = 3102437392;
//	this->Client[eExUB::Daboy_2].Rage = false;
//	this->Client[eExUB::Daboy_2].WinQuest = false;
//	// ----
//	this->Client[eExUB::Encode].hdd_id = 2664824880;
//	this->Client[eExUB::Encode].Rage = false;
//	this->Client[eExUB::Encode].WinQuest = false;
//	// ----
//	this->Client[eExUB::Pavel].hdd_id = 1745027016;
//	this->Client[eExUB::Pavel].Rage = false;
//	this->Client[eExUB::Pavel].WinQuest = false;
//	// ----
//	this->Client[eExUB::PrideMu].hdd_id = 136373629;
//	this->Client[eExUB::PrideMu].Rage = true;
//	this->Client[eExUB::PrideMu].WinQuest = false;
//	this->Client[eExUB::PrideMu].MonsterQuest = true;
//	this->Client[eExUB::PrideMu].TvTEvent = true;
//	this->Client[eExUB::PrideMu].GrandHero = true;
//	// ----
//	this->Client[eExUB::Cherkashin].hdd_id = 3422826830;
//	this->Client[eExUB::Cherkashin].Rage = false;
//	this->Client[eExUB::Cherkashin].WinQuest = false;
//	// ----
//	this->Client[eExUB::Semushkin].hdd_id = 2149325968;
//	this->Client[eExUB::Semushkin].Rage = false;
//	this->Client[eExUB::Semushkin].WinQuest = false;
//	// ----
//	this->Client[eExUB::Gints_2].hdd_id = 2556587903;
//	this->Client[eExUB::Gints_2].Rage = true;
//	this->Client[eExUB::Gints_2].WinQuest = false;
//	this->Client[eExUB::Gints_2].GrandHero = true;
//	this->Client[eExUB::Gints_2].PartySystem = true;
//	this->Client[eExUB::Gints_2].MonsterQuest = true;
//	this->Client[eExUB::zerocool].hdd_id = 3358746164;
//	this->Client[eExUB::zerocool].Rage = false;
//	this->Client[eExUB::zerocool].WinQuest = false;
//	// ----
//	this->Client[eExUB::Vadim_2].hdd_id = 1684392689;
//	this->Client[eExUB::Vadim_2].Rage = false;
//	this->Client[eExUB::Vadim_2].WinQuest = false;
//	// ----
//	this->Client[eExUB::ulasevich].hdd_id = 2157970567;
//	this->Client[eExUB::ulasevich].Rage = false;
//	this->Client[eExUB::ulasevich].WinQuest = false;
//	this->Client[eExUB::ulasevich].BloodHound = true;
//	this->Client[eExUB::ulasevich].Rage = true;
//	this->Client[eExUB::ulasevich].MonsterQuest = true;
//	this->Client[eExUB::ulasevich].Brotherhood = true;
//	// ----
//	this->Client[eExUB::Local2].hdd_id = 576700642;
//	this->Client[eExUB::Local2].Rage = true;
//	this->Client[eExUB::Local2].WinQuest = false;
//	this->Client[eExUB::Local2].BloodHound = true;
//	this->Client[eExUB::Local2].MonsterQuest = true;
//	this->Client[eExUB::Local2].TvTEvent = true;
//	this->Client[eExUB::Local2].GrandHero = true;
//	// ----
//	this->Client[eExUB::DavitRazmadze2].hdd_id = 2264191357;
//	this->Client[eExUB::DavitRazmadze2].Rage = false;
//	this->Client[eExUB::DavitRazmadze2].WinQuest = false;
//	// ----
//	this->Client[eExUB::PrideMuLocal].hdd_id = 102821109;
//	this->Client[eExUB::PrideMuLocal].Rage = true;
//	this->Client[eExUB::PrideMuLocal].WinQuest = false;
//	this->Client[eExUB::PrideMuLocal].MonsterQuest = true;
//	this->Client[eExUB::PrideMuLocal].TvTEvent = true;
//	this->Client[eExUB::PrideMuLocal].GrandHero = true;
//	// ----
//	this->Client[eExUB::lexbzk].hdd_id = 308214326;
//	this->Client[eExUB::lexbzk].Rage = false;
//	this->Client[eExUB::lexbzk].WinQuest = false;
//	// ----
//	this->Client[eExUB::Local3].hdd_id = 1518866620;
//	this->Client[eExUB::Local3].Rage = true;
//	this->Client[eExUB::Local3].WinQuest = false;
//	this->Client[eExUB::Local3].MonsterQuest = true;
//	this->Client[eExUB::Local3].TvTEvent = true;
//	this->Client[eExUB::Local3].GrandHero = true;
//	// ----
//	this->Client[eExUB::snaker].hdd_id = 4230177721;
//	this->Client[eExUB::snaker].Rage = true;
//	this->Client[eExUB::snaker].WinQuest = false;
//	this->Client[eExUB::snaker].BloodHound = false;
//	this->Client[eExUB::snaker].MonsterQuest = true;
//	this->Client[eExUB::snaker].TvTEvent = true;
//	this->Client[eExUB::snaker].GrandHero = true;
//	// ----
//	this->Client[eExUB::testuser].hdd_id = 3834831223;
//	this->Client[eExUB::testuser].Rage = false;
//	this->Client[eExUB::testuser].WinQuest = false;
//	// ----
//	this->Client[eExUB::Gredy].hdd_id = 1223984258;
//	this->Client[eExUB::Gredy].Rage = false;
//	this->Client[eExUB::Gredy].WinQuest = false;
//	// ----
//	this->Client[eExUB::GredyLocal].hdd_id = 1748593463;
//	this->Client[eExUB::GredyLocal].Rage = false;
//	this->Client[eExUB::GredyLocal].WinQuest = false;
//	// ----
//	this->Client[eExUB::Pavel2].hdd_id = 2691024834;
//	this->Client[eExUB::Pavel2].Rage = false;
//	this->Client[eExUB::Pavel2].WinQuest = false;
//	// ----
//	this->Client[eExUB::ulasevich2].hdd_id = 71422912;
//	this->Client[eExUB::ulasevich2].Rage = false;
//	this->Client[eExUB::ulasevich2].WinQuest = false;
//	this->Client[eExUB::ulasevich2].BloodHound = true;
//	this->Client[eExUB::ulasevich2].Rage = true;
//	this->Client[eExUB::ulasevich2].MonsterQuest = true;
//	this->Client[eExUB::ulasevich2].Brotherhood = true;
//	// ----
//	this->Client[eExUB::feqan].hdd_id = 1521036435;
//	this->Client[eExUB::feqan].Rage = false;
//	this->Client[eExUB::feqan].WinQuest = false;
//	this->Client[eExUB::feqan].PartySystem = true;
//	// ----
//	this->Client[eExUB::Selfmylife].hdd_id = 3296873814;
//	// ----
//	this->Client[eExUB::NoCustom].hdd_id = 1188528199;
//
//	this->Client[eExUB::ConflictNoCustom].hdd_id = 2492754898;
//	this->Client[eExUB::ConflictNoCustom].TvTEvent = true;
//	this->Client[eExUB::ConflictNoCustom].PandoraEvent = true;	
//
//	this->Client[eExUB::Emanuel].hdd_id = 4196649766;
//}
//// -------------------------------------------------------------------------------
//
//exSecurity::~exSecurity()
//{
//	// ----
//}
//// -------------------------------------------------------------------------------
//
//void exSecurity::Main()
//{
//	if(!this->Active) return;
//
//	for(int i=0;i<TOTAL_CLIENT;i++)
//	{
//		if(this->HDDKEY == this->Client[i].hdd_id)
//		{
//			g_CustomSystem.IsRage() = this->Client[i].Rage;
//			g_ExLicense.user.WinQuest = this->Client[i].WinQuest;
//			g_ExLicense.user.BloodHound = this->Client[i].BloodHound;
// 			g_ExLicense.user.MonsterQuest = this->Client[i].MonsterQuest;
//			g_ExLicense.user.TvTEvent = this->Client[i].TvTEvent;
//			g_ExLicense.user.GrandHero = this->Client[i].GrandHero;
//			g_ExLicense.user.PartySystem = this->Client[i].PartySystem;
//			g_ExLicense.user.Brotherhood = this->Client[i].Brotherhood;
//			g_ExLicense.user.PartySearch = this->Client[i].PartySearch;
//			g_ExLicense.user.ChatLog = this->Client[i].ChatLog;
//			g_ExLicense.user.GM_Manager = this->Client[i].GM_Manager;
//			g_ExLicense.user.PerosnalStoreEx = this->Client[i].PerosnalStoreEx;
//			g_ExLicense.user.PandoraEvent = this->Client[i].PandoraEvent;
//			this->ActiveUser = i;
//			this->ReedURLVerisoun();
//			return;
//		}
//	}
//	MessageBoxA(NULL, "License Error", "Error", ERROR);	
//	ExitProcess(0);
//}
//// -------------------------------------------------------------------------------
//
//void exSecurity::ReedURLVerisoun()
//{
//	if(!strcmp(exVERSION,VersionNum))
//	{
//		this->NewVersion = false;
//		return;
//	}
//	// ----
//	HINTERNET hSession	= InternetOpenA("ExTeam", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
//	HINTERNET hHandle	= InternetOpenUrlA(hSession, "http://ex-team.net/server/update.txt", NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
//	// ----
//	if( hSession == NULL || hHandle == NULL )
//	{
//		this->NewVersion = false;
//		return;
//	}
//	// ----
//	DWORD Number;
//	char Hash[100];
//	ZeroMemory(Hash, sizeof(Hash));
//	// ----
//	InternetReadFile(hHandle, Hash, 32, &Number);
//	// ----
//	sscanf(Hash,"%s %s",&VersionNum, &VersionDate);
//	// ----
//	if(strcmp(exVERSION,VersionNum))
//	{
//		this->NewVersion = true;
//	}
//	// ----
//	InternetCloseHandle(hSession);
//	InternetCloseHandle(hHandle);
//}
//// -------------------------------------------------------------------------------
//
//bool exSecurity::CheckUser(int NeedUser)
//{
//	if(this->ActiveUser == NeedUser)
//	{
//		return true;
//	}
//	return false;
//}
//// -------------------------------------------------------------------------------
//
//void exSecurity::SendUserClient(int aIndex)
//{
//	EX_CG_PRIVATE_USER rSend;
//	rSend.h.set((LPBYTE)&rSend, 0xFB, 17, sizeof(rSend));
//	rSend.exUser = this->ActiveUser;
//	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
//}
//// -------------------------------------------------------------------------------