#pragma once
// -------------------------------------------------------------------------------
#define ENABLE_PROTECT			0	//log add post item
#define ENABLE_CONSOLE			0
#define ENABLE_DEBUG			0
#define ENABLE_AUTOLOGIN		0
#define ENABLE_FILEMEMORY		0
#define ENABLE_TEST				0
#define ENABLE_START_MU			0
#define ENABLE_DEV				0
#define ENABLE_CHECK			0
#define ENABLE_ENCODER			1
#define ENGINE_DEBUGER			0
// -------------------------------------------------------------------------------
//	ine ENABLE_EXPROTECTOR		1
#define ENABLE_EXPROTECTOR1		0
#define ENABLE_EXPROTECTOR2		0
#define ENABLE_RAM_MIN			0
// -------------------------------------------------------------------------------
//#define ENABLE_IP_ADDRESS		0
#define TEXT_IP_ADDRESS			"192.168.99.1"
//#define TEXT_IP_ADDRESS			"131.153.30.158"
// -------------------------------------------------------------------------------
#define INTERFACE_LOGIN_IMG		0	//private
#define THINNAKORN_MAC			0	//private
#define BASSREFLEXIVE			0	//private
#define EPICMU					0
#define LANG_CHINA				0
#define ENABLE_CHANGE			0	//need 1
#define LICENSE_MUEVIL			0
//#define _SERIAL_				"G3qF7QqTS21ilL7b"
// -------------------------------------------------------------------------------
#define WINDOW_TITLE			"MuOnline"
// -------------------------------------------------------------------------------
#if(ENABLE_PROTECT)
#define PROTECT
#endif
// -------------------------------------------------------------------------------
typedef unsigned __int64 QWORD;

#include <Windows.h>
#include <WindowsX.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <stdarg.h>
#include <process.h>
#include <locale.h>
#include <WinBase.h>
#include <tlhelp32.h>
#include <WinSock.h>
#include <gl\GL.h>
#include "glext.h"
#include "..\\Cg\cg.h"
#include "..\\Cg\cgGL.h"
#include "AntiCheat.h"
#include "VMProtectSDK.h"
#include <vector>
// -------------------------------------------------------------------------------
#include "Text.h"
// -------------------------------------------------------------------------------
#pragma comment(lib,"ws2_32.lib") //<- we need this lib for winsock
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")
#ifdef PROTECT
#pragma comment(lib, "VMProtectSDK32.lib")
#endif
// -------------------------------------------------------------------------------
#if(ANTI_CHEAT_DEBUG==TRUE)
#define exCONSOLE				1
#endif
// -------------------------------------------------------------------------------
#if(ENABLE_CONSOLE)
#define exCONSOLE				1	//Консоль
#endif
#if(ENABLE_DEBUG)
#define exDEBUG_CODE			1	//Debug Режим
#endif
// -------------------------------------------------------------------------------
#define ANTI_CTRL				1
#define OLD_HP_BAR				0
#define NEW_HP_BAR				1
#define FULL_HD					1
#define NEW_GLOW_EFFECT			1
#define NEW_QUEST_SYSTEM		1
#define exRECONNECT				1
#define exRAGESYSTEM			1	//Система ярости, не работает без интерфейса
#define AUTO_PARTY				1
//#define _ANTI_HACK_			1
#define _LAUNCHER_				1
#define _ITEM_PRICE_MANAGER_	1
#define HPBAR_UPDATE			1
#define AUTO_LOGIN				1
#define ADD_NEW_EFFECT_WINGS	1
#define _NEW_MONSTER_			1
#define _PRIVATE_MODULE_		1
#define _COINS_					1
#define PRIVATE_MODULE			1
#define NEW_PARTY_BUFF			1
#define EX_SPEED_CALC			1
 // -------------------------------------------------------------------------------
#define _GRAND_SYSTEM_
#define NEWWINGS6
#define PREM_TYPE
#define EXCLUSIVE_AMYLET
#define VIEW_MONSTER
#define CUSTOM_PARTY_SEARCH		TRUE
#define SECURITY_SCRIPT			FALSE
#define CUSTOM_PERONAL_EX		TRUE
// -------------------------------------------------------------------------------
#define DLL_EX_ANTI_CHEAT		TRUE	// HERE
// -------------------------------------------------------------------------------
#define _SPEED_FIX_				TRUE
// -------------------------------------------------------------------------------
#define ACHIEVEMENTS_SYSTEM
#define CUSTOM_NEWS				TRUE
#define CUSTOM_NEWS				TRUE
#define ANTI_CHEAT_PLUS			TRUE	// 
#define CUSTOM_NPC_BUFFER		FALSE
// -------------------------------------------------------------------------------
#define SPEED_BUG_FIX			0	// <== need recode ExGames normal code
// -------------------------------------------------------------------------------
#define CONNECT_IP_ENCRYPT		0
// -------------------------------------------------------------------------------
#define JEWEL_OF_PVP			0
#define CUSTOM_SMITHY			0
#define EX_LICENSE				TRUE
#define OFFLINE_MODE			1
#define ADD_OFFMODE_PICKUP		1
// -------------------------------------------------------------------------------
#define FIX_MINIMAP				1
#define CUSTOM_MARRIAGE			1	//Свадьба
#define CUSTOM_EX_CHAT			1
#define ADD_JEWELBANK_CREATEON	1
#define CUSTOM_ADD_POINTS		1
#define ADD_ADD_POINT			1	//?
#define ADD_ADD_RESETPOINT		1
#define CUSTOM_MENU				1
#define ADD_PARTY_LEADER		1
#define CUSTOM_RESETSYSTEM		1
#define DONATE_SHOP				TRUE
// -------------------------------------------------------------------------------
#define EVENT_DUNGEON_SIEGE		1
#define CUSTOM_ITEM_RANK		TRUE
#define FIX_GUILD_CRASH			1
#define CUSTOM_SERVER_TIME		1
#define ANTI_CHEAT_PLUS_CRC		0
#define EVENT_TEAM_VS_TEAM		1
#define TEAM_VS_TEAM_INFO		1
#define CUSTOM_SOUND			1
#define CUSTOM_NEW_MAP			1
// -------------------------------------------------------------------------------
#define SYSTEM_ACHIEVEMENTS		1
#define CUSTOM_MINIMENU			1
#define CUSTOM_SERVERINFO		1
// -------------------------------------------------------------------------------
// 04.09.2017
// -------------------------------------------------------------------------------
#define CUSTOM_EX_TELEPORT		TRUE
#define CUSTOM_WINGSEFFECT		1
#define CUSTOM_AUTOCTRL			1
#define CUSTOM_WIN_SETTINGS		1
#define CUSTOM_PLAYERTITLE		0
#define FIX_AGM_REQVALLIANCE	TRUE
// -------------------------------------------------------------------------------
#define CUSTOM_NEW_MAP			1
#define CUSTOM_MAP_MANAGER		0	//Disable not work
#define CUSTOM_EXTEXT			1
#define CUSTOM_PREMIUM_SYSTEM	1
#define CUSTOM_EX_TELEPORT_EVO	TRUE
#define CUSTOM_PKCLEAR_NPC		TRUE
#define CUSTOM_ACCOUNT_SECURITY	TRUE
// -------------------------------------------------------------------------------
#define CUSTOM_REFERAL_SYSTEM	1
#define ENABLE_ITEMSETOPTION	1
#define ENABLE_CHATCOLOR		1
#define CUSTOM_POSTITEM			1
#define CUSTOM_MINIMAP			1
#define CUSTOM_AUTOHP			1
#define USER_BUFF_ICON_EX		1
#define CUSTOM_BUFF_INFO		1
#define CUSTOM_EX_QUEST_SYSTEM	1		// [-] Оконная квест система
// --------------------------------
#define RF_NEW_GLOV				0	//ОТКЛЮЧАЕТ ГРАНД ХИРО ИТЕМ
#define GLOV1					0x610	//620
#define GLOV2					0x611	//621
#define GLOV3					0x612	//620
#define GLOV4					0x613	//621
// -------------------------------------------------------------------------------
// 23.06.2018
// -------------------------------------------------------------------------------
#define CUSTOM_PICKUP_ITEM_INFO	1
#define FIX_CORD_ITEM_TEXT		1
#define CUSTOM_MINIMAP_PARTY	1
// -------------------------------------------------------------------------------
#define CUSTOM_EMULATOR_KEY		1
#define CUSTOM_MUHELPER_INV		1
#define CUSTOM_LOTTERY			0	//...
#define DEV_PACKET_ITEM			0
#define DEV_USERSHOP			0
// itemPos
#define ADD_CTRL_KEY			1
#define FIX_MONSTER_HP			1
#define DEV_GUILDBANK			1
#define DEV_STORAGE				1
// -------------------------------------------------------------------------------
#define INTERFACE_JEWELBANK		1
// -------------------------------------------------------------------------------
#define DEV_EFFECT				0
#define DEV_EFFECT2				0
#define DEV_FPS					1
#define DEV_SKILL				0
// -------------------------------------------------------------------------------
#define CUSTOM_DINAMIC_EFFECT	0
// -------------------------------------------------------------------------------
#define DEBUG_FPS				0
// -------------------------------------------------------------------------------
// -> New Dev
#define DEV_EXMENU_V3			1
#define DEV_STATS_ADVANCE		1
#define DEV_PLAYERINFO			0
#define DEV_DAMAGE_TABLE		1
#define ADD_OFFMODE_TIMER		1
// -------------------------------------------------------------------------------
#define NEXT_INTERFACE_MANAGER	0
#define ENABLE_PETEX			0
#define USERPANEL				1
// -------------------------------------------------------------------------------
#define ENABLE_AGMASTER			1
#define DEV_INTERFASE_SEASON3	1

#define BLOCK_VM_RUN			1

/*	АГМ
	0078F41E - прием в клан
*/