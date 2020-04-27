#pragma once

#define WIN32_LEAN_AND_MEAN

#define WINVER _WIN32_WINNT_WIN7

//#pragma warning(disable: 4786)
//#pragma comment(lib, "../lua/lib/lua5-1.lib")
// -------------------------------------------------------------------------------
//https://youtu.be/3r6QVWmdNrM?t=14m47s
// -------------------------------------------------------------------------------
//	Define
// -------------------------------------------------------------------------------
#define ENABLE_PROTECT			0
#define EXLICENSE_SELECT		0
#define ENABLE_DEBUG			0
#define EXLICENSE_SERVER		0
#define ENABLE_HIDEWINDOW		0
#define ENABLE_DEV				0
#define ENABLE_FIX				1
// -------------------------------------------------------------------------------
#define ENABLE_EXPROTECTOR		1
// -------------------------------------------------------------------------------
#define THINNAKORN_MAC			0
#define LICENSE_EVOMU			0
#define LICENSE_MUEVIL			0
#define LICENSE_ARCMU			0
// -------------------------------------------------------------------------------
#define ENABLE_OPTIMIZATION		0
#define ENABLE_PROTOCOL_QUEUE	0
#define ENABLE_RAM_MIN			0
#define DEV_SOCKET_MANAGER		0
#define FIX_SOCKET_MAXBUFFER	0
// -------------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7
// -------------------------------------------------------------------------------
#if(ENABLE_PROTECT)
#define VMPROTECT
#endif
#define exVERSION				"0.4.9.4"
// -------------------------------------------------------------------------------
#define ENABLE_UPPSOCCER		0	//Need delete?
// -------------------------------------------------------------------------------
#define LOG_INMEDIATLY			0
#define REMOVE_CHECKSUM			0
#define DEBUG_IT				0
#define DEBUG_BUFF_EFFECT		0
#define DEBUG_SUMMONER_SKILL	0
#define DEBUG_EVENT_COUNTER		0
#define USE_M_DRIVE				0
#define TESTSERVER				0
// ----
#if (USE_M_DRIVE == 1)
#define FINAL_PATH				"..\\DataFull\\"
#define COMMONSERVER_PATH		"..\\DataFull\\commonserver.cfg"
#define SERVER_INFO_PATH		"DATA\\Serverinfo.dat"
#else
#define FINAL_PATH				"..\\Data\\"
#define COMMONSERVER_PATH		"..\\Data\\commonserver.cfg"
#define SERVER_INFO_PATH		"DATA\\Serverinfo.dat"
#endif
// -------------------------------------------------------------------------------
#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>
#include <windows.h>
#include <winbase.h>
#include <winsock2.h>
#include "COMMCTRL.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <process.h>
#include <map>
#include <string>
#include <ios>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <afx.h>
#include <rpcdce.h>

#include "VMProtectSDK.h"
#include "MuMsg.h"
#include "Text.h"

#include <lua.hpp>
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "lua52.lib")

// -------------------------------------------------------------------------------
extern CMsg lMsg;
#define MSGGET(x,y)				(x*256)+y
// -------------------------------------------------------------------------------
#define NEW_WINDOW				TRUE
#define GAMESERVER_WIDTH		950
#define GAMESERVER_HEIGHT		650
// -------------------------------------------------------------------------------
#define _LUA_					1
// ----
//#define DEBUG_CODE			1
//#define DEBUG_CODE2			1 
#define _FIX_					1
#define _DUEL_FIX_				1
#define _NEW_CHAT_FIX_			1
#define _DC_FIX_				1
// ----

#ifdef GS_CS
#define GS_CASTLE				1
#endif

// ----
//#define S3E1					1
//#define S4E6					1
//#define S5E3					1
//#define S5E4					1
#define S6E3					1
// ----
//#define MSSQL2008				1
// -------------------------------------------------------------------------------
#if(S3E1)
#define PROTOCOL_MOVE			0xD3
#define PROTOCOL_POSITION		0xDF
#define PROTOCOL_ATTACK			0xD7
#define PROTOCOL_BEATTACK		0x10
#endif
// ----
#if(S4E6||S5E3)
#define PROTOCOL_MOVE			0x1D
#define PROTOCOL_POSITION		0xD6
#define PROTOCOL_ATTACK			0xDC
#define PROTOCOL_BEATTACK		0xD7
#endif
// ----
#if(S5E4||S6E3)
#define PROTOCOL_MOVE			0xD4
#define PROTOCOL_POSITION		0x15
#define PROTOCOL_ATTACK			0x11
#define PROTOCOL_BEATTACK		0xDB
#endif
// ----
#if(S5E4||S6E3)
#define GENS
#define PERIOD							// Period System
#define GAMESHOP
// --
#define DB_MAX_INVENTORY_SIZE	3776
#define DB_MAX_VAULT_SIZE		3840
// --
#define MAX_IDSTRING			10
#define PMHC_BYTE				0xC1
#define PMHC_WORD				0xC2
#define PMHCE_BYTE				0xC3
#define PMHCE_WORD				0xC4
#endif
// ----
#if(S6E3)
#define CHARCREATE_TEMP
#define MONK
#define MUHELPER
#define NO_WORK
#define NEW_MASTER_SYSTEM
#define LUCKYITEM
#define EN_RINGS				1
#define EXPINV
#ifdef EXPINV
#define MAX_INVENTORY_H			24
#define MAX_INVENTORY_H2		28
#define MAX_INVENTORY_LEN		192
#define MAX_WAREHOUSE_H			30
#else
//#define DB_MAX_INVENTORY_SIZE	1728
//#define DB_MAX_VAULT_SIZE		1920
#define MAX_INVENTORY_H			8
#define MAX_INVENTORY_H2		12
#define MAX_INVENTORY_LEN		64
#define MAX_WAREHOUSE_H			15
#endif
#endif
// -------------------------------------------------------------------------------
#define MAX_PACKET_SERVER		1000	//Default: 100
// ----
#define PRIVATE_MODULE			TRUE
// -------------------------------------------------------------------------------
// -> Custom List
// -------------------------------------------------------------------------------
#define _NEW_JEWELS_				//Переписать
#define _OFFTRADE_					//Дописать
#define _PRICE_MANAGER_				//Дописать покупку
#define _PREMIUM_SYSTEM_			//Дописать
#define _CR_COIN_				1	//Дописать функцию активации
#define _ZEN_COIN_				1	//Дописать функцию активации
#define _MULTI_VAULT_			1	//несколько сундуков
#define _NEW_PT_SYSTEM_			1	//Новая система партии
#define _ARENA_ITEM_			1	//стоит на арене пока есть вещь(после смерти)	+нужно дописать
#define _BAN_SYSTEM_			1	//Система банов
#define _RECONNECT_				1	//Система переподключения при разрыве связи
#define NEW_HP_BAR				1
#define WIN_QUEST_SYSTEM		1	//100$
#define _SYSTEM_OF_RAGE_		1	//70$
#define TELEPORT_MANAGER		1
#define AUTO_PARTY				1
// ----
#define PC_BANG_POINT_SYSTEM	FALSE
// ----
#define IS_NEWWINGS(x)			((x < ITEMGET(12, 180)) ? FALSE : (x > ITEMGET(12, 194)) ? FALSE : TRUE)
#define NEWWINGS_2_5			TRUE
#define IS_NEWWINGS_2_5(x)		((x < ITEMGET(12, 186)) ? FALSE : (x > ITEMGET(12, 188)) ? FALSE : TRUE)
#define NEWWINGS_4				TRUE
#define IS_NEWWINGS_4(x)		((x < ITEMGET(12, 180)) ? FALSE : (x > ITEMGET(12, 185)) ? FALSE : TRUE)
#define NEWWINGS_5				TRUE
#define IS_NEWWINGS_5(x)		((x < ITEMGET(12, 189)) ? FALSE : (x > ITEMGET(12, 194)) ? FALSE : TRUE)
#define NEWWINGS_6				TRUE	//30
//#define IS_NEWWINGS_6(x)		((x < ITEMGET(12, 195)) ? FALSE : (x > ITEMGET(12, 196)) ? FALSE : TRUE)
#define IS_NEWWINGS_6(x)		((x < ITEMGET(12, 195)) ? FALSE : (x > ITEMGET(12, 220)) ? FALSE : TRUE)
// -------------------------------------------------------------------------------
// -> InDev
#define _VOTER_					1
#define HPBAR_UPDATE			1
#define UPDATE_FIX				1
#define BloodHoundEvent			1
#define GRAND_HERO_DEV			1
#define EXP_FIX					1
// -------------------------------------------------------------------------------
// -> Conflict Developed
#define _CONFLICT_				TRUE
#ifdef _CONFLICT_
#define _UPDATE8_
#define _POST_CONFIG_			1
#define _FIX_PK_IN_DUEL_
#define _RF_GENS_MAP_DARK_SIDE_
#define _MESSAGE_CONFIG_
#define _BALANS_SYSTEM_
#define GRANG_HERO_MIX_REPEAT
#define PRIDEMU_CONFIG
#define FENRIR_CONFIG
#define DRYNEA_LIST_CUSTOM			//if Start NEED Config
#define HP_CONFIG
#define UPDATE_PVP				1
#define DRYNEA_NEW_CONFIG
#ifdef DRYNEA_NEW_CONFIG			//Balance +
#define FLOOD_IN_POST
#endif
#define DED_MAKAR
#ifdef DED_MAKAR
#define PREM_TYPE 
#define EXCLUSIVE_AMYLET
#define TEST_OFFAFF_DARK_SIDE
#endif
#endif
// -------------------------------------------------------------------------------
#define IMPERIAL_CONFLICT_OLD
//#define IMPERIAL_CONFLICT_NEW
#define _EX_DEV_BUFF_PT_
// -------------------------------------------------------------------------------
// -> Update 09.2015
#define UPDATE_SEPTEMBER
#ifdef UPDATE_SEPTEMBER
#define UPDATE_PVP				1
#define _WINGS_DAMAGE_
#define FIX_BERSERK_SUM
#define FIX_MIX_CONDOR
#define FIX_DEATH_HP_BAF
#endif
// -------------------------------------------------------------------------------
#define DRYNEA_27_10
#ifdef DRYNEA_27_10
#define FREE_OFF_AFK
#define OFF_AFK_DUR
#define BC_LVL_DROP
#endif
// -------------------------------------------------------------------------------
#define SNAKER_CHN_LANG
#define DRYNEA_31_10
#define SEND_CREDIT_SILVER
#define EX_RELOAD_RAGE_SILVER
#define SNAKER_CMD_NAME
#define DRYNEA_13_11
// -------------------------------------------------------------------------------
#define UPDATE_0112
#ifdef UPDATE_0112
#define VIEW_MONSTER
#define LVL_UP_POINTS
#define FIX_DC_DISTANCE_OBJ_VIEWE
#define DS_REWARD_ITEM
#define BOSS_REWARD_ITEM
#endif 
// -------------------------------------------------------------------------------
#define BLOCK_MOVE_DROP_FIX
#define PK_CLEAR_TO_CREDITS
#define FIX_CRASH_PROCENT_IN_PRIVATE_CHAT
#define SKILL_ELF_ADD_DAMAGE
#define PARTY_BONUS
#define FIX_CREATE_GUILD
#define ADD_NPC
#define FIX_BAF_RELOGIN_DB
#define CFIX_INV
#define TWO_IP_CONNECT  
#define DISCONECT_FRIEND
#define _NEW_PARTY_SYSTEM_		TRUE
// -------------------------------------------------------------------------------
//#define IMPERIAL_REPEAT_CONFLICT
/*[9:47:48] snaker: 大龙
  [9:47:57] snaker: 用汉字你能看到吗*/
// -------------------------------------------------------------------------------
#define SYSTEMOF_BROTHER		TRUE
#define TELEPORT_SHOP			TRUE
#define CUSTOM_PARTY_SEARCH		TRUE	//Система поиска партии
// -------------------------------------------------------------------------------
// -> Update 03.2016
#define MART_FIX
// -------------------------------------------------------------------------------
// -> New Custom List
#define CUSTOM_CHAT_LOG			TRUE
// -------------------------------------------------------------------------------
#define FIX_CRASH				TRUE
#define LORA_BATTLE_EVENT
#define CUSTOM_PERSONAL_SHOP	TRUE
#define LVL_TO_CREATE_CHAR
#define PANDORA_EVENT
#define NEW_JEWEL_FROM_WINGS
#define CUSTOM_NEWS				TRUE
#define ANTI_CHEAT_PLUS			TRUE
#define SWENG_FIX				TRUE	//Fixs Sweng
#define DANGER_FIX				TRUE
#define DEV_COMBO_CUSTOM		TRUE
#define EVOMU_CASTLE_SEGE		TRUE
#define FIX_REQSTR_ITEM			TRUE
#define FIX_ZEN_MOVE			TRUE
#define CUSTOM_RETURNSPOT		1		//No Work
#define CUSTOM_NPC_BUFFER		TRUE
#define CUSTOM_SMITHY			1
#define CUSTOM_SAVE_PT			1
// -------------------------------------------------------------------------------
// NEED BM QUEST ADDED
// -------------------------------------------------------------------------------
#define FIX_DL_HORSE_IN_CROWN	TRUE
#define FIX_FINAL_DMG_COLOR		TRUE
// -------------------------------------------------------------------------------
// FIX LIST
// -------------------------------------------------------------------------------
#define FIX_MUHELPER_TP			TRUE
#define FIX_HELPER_EE_BUFF		TRUE
#define FIX_MONSTERDROP_MSG		TRUE
// -------------------------------------------------------------------------------
// DEV AND TESTED
// -------------------------------------------------------------------------------
#define EVOMU_DLSKILLCHANGE		1		//10
// -------------------------------------------------------------------------------
// -> Add for custom
// -------------------------------------------------------------------------------
#define ADD_TVTHDDCHECK			1
#define ADD_GRAND_EXP			1
#define OFFLINE_MODE			1
#define ADD_OFFMODE_PICKUP		1
// -------------------------------------------------------------------------------
// NO WORK
// -------------------------------------------------------------------------------
#define FIX_REF_ON_REF			0

#define FIX_DS_CRASH
#define CMD_DC_ALL				1

#define PK_PARTY_FIX			TRUE
#define CUSTOM_MONSTER_MESSAGE	TRUE
#define CUSTOM_MARRIAGE			1
#define ADD_JEWELBANK_CREATEON	1
#define FIX_PK_SELFDEFENCE		1
#define FIX_REF2				1
#define CUSTOM_ADD_POINTS		1
#define ADD_ADD_POINT			0
#define ADD_ADD_RESETPOINT		1
#define CUSTOM_MONSTER_EX		TRUE	//Расширитель настройки монстров
#define CUSTOM_PARTY_LEADER		1
#define USER_EVOMU				1
#define ITEM_NO_NAME_DROP_FIX	1
//GameShopPoint -> optimize DS
#define MMOTOP_LOG				TRUE
#define CONFIG_WAITOPEN			1
#define CUSTOM_NOOBBUFF			1
#define EVENT_DEVIASBATTLE		1
#define ADD_RESET_WINDOW		1
#define DONATE_SHOP				1
// -------------------------------------------------------------------------------
// 01.03.2017
// -------------------------------------------------------------------------------
#define EVENT_DUNGEON_SIEGE		1
#define CUSTOM_MONSTER_PREMIUM	1
#define CUSTOM_ITEM_RANK		TRUE	//need license
#define SILVER_DL_TP			1
#define FIX_SHIELD				1
#define CUSTOM_POTIONTICK		1
#define CUSTOM_CW_ALTERELFDMG	1
#define FIX_CASTLE_SIEGE_WAR	1
#define FIX_LAND_OWNDER			1
#define CUSTOM_SERVER_TIME		1
#define MARRI_BUFF				1
#define CUSTOM_MAPQUEST			1
// -------------------------------------------------------------------------------
// 19.07.2017
// -------------------------------------------------------------------------------
#define FIX_MONSTER_RELOAD		TRUE
#define ANTI_CHEAT_PLUS_CRC		0
#define CMD_ANTI_CHEAT_HDD		1
#define EVENT_TEAM_VS_TEAM		1
#define TEAM_VS_TEAM_INFO		1
// -------------------------------------------------------------------------------
// 13.08.2017
// -------------------------------------------------------------------------------
#define CUSTOM_DONATEMANAGER	1
#define SYSTEM_ACHIEVEMENTS		1
#define CUSTOM_NEWBUFF			1
// -------------------------------------------------------------------------------
// 04.09.2017
// -------------------------------------------------------------------------------
#define CUSTOM_EX_TELEPORT		1
#define COMMAND_DROP			1
#define ENABLE_TEXTCHANGE		0
#define FIX_IMPERIAL			1
// -------------------------------------------------------------------------------
// 12.10.2017
// -------------------------------------------------------------------------------
#define FIX_MEMLEAK				1
#define FIX_AGM_REQVALLIANCE	TRUE
#define NEWTIMEREX				1
#define PARTY_ZEN_DROP			1
#define FIX_PKLEVEL				1
#define FIX_HPSDBAR				1
#define FIX_BASSPARTY			1
#define CUSTOM_MAP_MANAGER		0
#define DEBUG_MAP_MANAGER		0
#define CUSTOM_EXTEXT			1
// -------------------------------------------------------------------------------
// 10.01.2018
// -------------------------------------------------------------------------------
#define CUSTOM_PREMIUM_SYSTEM	TRUE	//Премиум система
#define CUSTOM_EX_TELEPORT_EVO	1
#define CUSTOM_PKCLEAR_NPC		TRUE
#define CUSTOM_ACCOUNT_SECURITY	1
#define CUSTOM_REFERAL_SYSTEM	1
#define CUSTOM_POSTITEM			1
#define CUSTOM_CHATFILTER		1
#define CUSTOM_VOTE_BUFF		1
#define CUSTOM_AUTOHP			1
#define CUSTOM_MULTIWAREHOUSE	1
#define CUSTOM_EX_QUEST_SYSTEM	1
#define CALCULATOR_MANAGER		1		//Дед Макарка, Калькулятор менеджер, Developer: Conflict
#define RANDOM_BOX_CORD_PANDORA	1		//Дед Макарка, Рандомное появление сундука PandoraBox, Developer: Conflict
// -------------------------------------------------------------------------------
// 23.06.2018
// -------------------------------------------------------------------------------
#define CUSTOM_PICKUP_ITEM_INFO	1
#define CUSTOM_POST_SERVER		1
#define EVOMU_HOSTILITY_DEL		1
#define CUSTOM_LOTTERY			0	//...
#define CUSTOM_MINIMAP_PARTY	1	

#define FIX_MONSTER_HP			1
#define CONFIG_PET_DURABILITY	1
#define FIX_TELEPORT_DIE		1
#define EVO_CREDITDONATE		1

#define EVENT_CARNAGE			1
#define CUSTOM_MANAGER			1
#define EVIL_SPIRIT_SUMMONER	1
#define ADD_CTRL_KEY			TRUE
#define DEV_CHATBAN_HDD			0
#define DEV_BANSYSTEM			1
#define DEV_GUILDBANK			1
#define DEV_MONSTERTIME			1
// -------------------------------------------------------------------------------
#define INTERFACE_JEWELBANK		1
// -------------------------------------------------------------------------------
#define DEV_SKILL				0
#define EVENT_QUESTIONANSWER	1
// -------------------------------------------------------------------------------
#define DEV_STATS_ADVANCE		1
#define DEV_PLAYERINFO			0
#define DEV_DAMAGE_TABLE		1
#define ADD_OFFMODE_TIMER		1
#define SCANER_ITEM_DUPE		1
// -------------------------------------------------------------------------------
#define NEXT_INTERFACE_MANAGER	0
#define ENABLE_PETEX			1
#define ENABLE_AGMASTER			1
// -------------------------------------------------------------------------------
#define REFIX_DROPZEN			1			// << == 
#define BROTHER_PAYTELEPORT		1
// -------------------------------------------------------------------------------

void ListFilesInDir(LPSTR dir_path, std::vector<std::string>& output);
DWORD GetEpoch();