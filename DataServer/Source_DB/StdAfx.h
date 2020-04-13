#pragma once

#pragma warning ( disable : 4786 )

#define DATASERVER_VERSION				"3.0"
#define DATASERVER_DATE					__DATE__

#define WIN32_LEAN_AND_MEAN
#define WINVER _WIN32_WINNT_WIN7

#include <afxwin.h>

#include <windows.h>
#include <winsock2.h>
#include <commctrl.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

#define PARTY_SEARCH_SIZE		11

#include "..\\Include\\define.h"
#include "Logproc.h"
#include "LogToFile.h"

//#include "..\include\Sprodef.h"

#define DB_CONNECT_DSN			"MuOnline"
#define DB_CONNECT_UID			"MuOnlineAdmin"
#define DB_CONNECT_PWD			"wkfwkRnfRnf"

extern char szDbConnectID[]; // idb 
extern char szDbConnectPass[]; // idb
extern char szDbConnectDsn[]; // idb
extern char szDbConnectMemb[]; // idb

#include "CQuery.h"

extern char g_szDBID_DESC[];

#define DS_SEND_CUSTOM_USER
#define S6E3	1
#define GAMESHOP
//#define DEBUG_CODE		1
#define _BAN_SYSTEM_	1 
#define _RAGE_SYSTEM_
#define _CR_MEMB_INFO_	1
// -------------------------------------------------------------------------------
#include "ExLicense.h"
#define CONFLICT_PREM  //drynea
#define CONFLICT_PREM_TYPE //Makarka
//******************** 
//	Client List
//********************
//#define _LOCAL_	1
//#define _DANGER_ 2
//#define _MuIlisium_	3
//#define _EmeraldMU_	4
//#define _Espada_Legend_net_ 5
//#define _PRIMEMU_
//#define _EXGAMES_	6
//#define _Mu_MD_	7
#ifdef _LOCAL_
//#define _MULTI_VAULT_	1	//Несколько сундуков
#define _RAGE_SYSTEM_
#define _CR_MEMB_INFO_	1
#endif
//********************
#ifdef _EmeraldMU_
#define _RESET_SYSTEM_
#endif
//********************
#ifdef _Espada_Legend_net_
#define _RESET_SYSTEM_
#define _GRAND_RESET_
#define _EX_QUEST_SYSTEM_
#define _CR_MEMB_INFO_	1
#define _MULTI_VAULT_	1	//Несколько сундуков
#endif
//********************
#ifdef _PRIMEMU_
#define _RAGE_SYSTEM_
#define _MULTI_VAULT_	1	//Несколько сундуков
#endif
#ifdef _EXGAMES_
#define _RAGE_SYSTEM_
#define _MULTI_VAULT_	1	//Несколько сундуков
#endif
#ifdef _Mu_MD_
#define _MULTI_VAULT_	1	//Несколько сундуков
#define _RAGE_SYSTEM_
#endif
//********************
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#define _RESET_SYSTEM_
//#define _GRAND_RESET_
//#define _EX_QUEST_SYSTEM_
//#define _RAGE_SYSTEM_
//#define _CR_MEMB_INFO_	1

//#define _MULTI_VAULT_	1	//Несколько сундуков
#define UPGRADE_QUEST	1

#define FIX_INVENTORY_BUG	1

// -> Syte Custom
#define CUSTOM_RETURNSPOT		0		//NO WORK
#define CUSTOM_NPC_BUFFER		TRUE
#define CUSTOM_SAVE_PT			TRUE

#define NEW_WIN			1
#define NEW_WIN_WIDTH	750
#define NEW_WIN_HEIGHT	480

#define FIX_TEST		1
#define DS_INFO			0
#define THREAD_FIFTH	1		//добовляем пятый поток

#define RECODE_GIIOCP	1

#define ENABLE_RAM_MIN	0