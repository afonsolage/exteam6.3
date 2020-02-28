#pragma once
// -------------------------------------------------------------------------------

#include "StdAfx.h"
#include "protocol.h"
#include <rpcdce.h>
#pragma comment(lib, "rpcrt4.lib")
// -------------------------------------------------------------------------------

//extern bool g_ExLicense.user.Rage;
//extern bool g_ExLicense.user.WinQuest;
//extern bool g_ExLicense.user.BloodHound;
//extern bool g_ExLicense.user.MonsterQuest;
//extern bool g_ExLicense.user.TvTEvent;
//extern bool g_ExLicense.user.GrandHero;
//extern bool g_ExLicense.user.PartySystem;
//extern bool g_ExLicense.user.Brotherhood;
//extern bool g_ExLicense.user.PartySearch;
//extern bool g_ExLicense.user.ChatLog;
//extern bool g_ExLicense.user.GM_Manager;
//extern bool g_ExLicense.user.PerosnalStoreEx;
//extern bool g_ExLicense.user.PandoraEvent;
//// -------------------------------------------------------------------------------
//
//#define TOTAL_CLIENT	100
//#define EXNEW_VERISON	"New Update:"
//#define DISK_DIR		"c:\\"
//// -------------------------------------------------------------------------------
//
//enum eExUB
//{
//	Local,
//	drynea,
//	t34,
//	exgames,
//	Gints,
//	SaneaMD,
//	MarksSevcuks,
//	SILVER1,
//	SILVER2,
//	Vadim,
//	DavitRazmadze,	
//	lemiks,
//	spoke,
//	Daboy_1,
//	Daboy_2,
//	Encode,
//	Pavel,
//	PrideMu,
//	Cherkashin,
//	Semushkin,
//	Gints_2,
//	zerocool,
//	Vadim_2,
//	ulasevich,
//	Local2,
//	DavitRazmadze2,
//	PrideMuLocal,
//	lexbzk, 
//	Local3,
//	DavitRazmadze3,
//	snaker,
//	testuser,
//	Gredy,
//	GredyLocal,
//	Pavel2,
//	ulasevich2,
//	feqan,
//	Selfmylife,
//	NoCustom,
//	ConflictNoCustom,
//	Emanuel
//};
//// -------------------------------------------------------------------------------
//
//struct USER_BASE
//{
//	DWORD hdd_id;
//	bool Rage;
//	bool WinQuest;
//	bool BloodHound;
//	bool MonsterQuest;
//	bool TvTEvent;	
//	bool GrandHero;
//	bool PartySystem;
//	bool Brotherhood;
//	bool PartySearch;
//	bool ChatLog;
//	bool GM_Manager;
//	bool PerosnalStoreEx;
//	bool PandoraEvent;
//};
// // -------------------------------------------------------------------------------
//
//struct EX_CG_PRIVATE_USER
//{
//	PBMSG_HEAD2 h;
//	BYTE exUser;	
//};
//// -------------------------------------------------------------------------------
//
//class exSecurity
//{
//public:
//	exSecurity();
//	~exSecurity();
//	// ----
//	bool Active;
//	int ActiveUser;
//	void Main();
//	// ----
//	bool NewVersion;
//	char VersionNum[50];
//	char VersionDate[50];
//	char VersionInfo[50];
//	bool DrawVersion;
//	void ReedURLVerisoun();
//	bool CheckUser(int NeedUser);
//	void SendUserClient(int aIndex);
//	bool Exit;
//	int ExitTime;
//
//private:
//	DWORD		HDDKEY;
//	USER_BASE	Client[TOTAL_CLIENT];
//};
//// -------------------------------------------------------------------------------
//
//extern exSecurity g_ExLicense;
//// -------------------------------------------------------------------------------
