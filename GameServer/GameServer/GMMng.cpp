//GameServer 1.00.77 JPN - Completed
//GameServer JPN - Completed
#include "stdafx.h"
#include "GMMng.h"
#include "LogToFile.h"
#include "logproc.h"
#include "GameMain.h"
#include "protocol.h"
#include "..\common\winutil.h"
#include "MoveCommand.h"
#include "GuildClass.h"
#include "TNotice.h"
#include "BattleSoccerManager.h"
#include "giocp.h"
#include "Kanturu.h"
#include "SkillAdditionInfo.h"
#include "DSProtocol.h"
#include "BuffManager.h"
#include "NewMasterLevelSystem.h"
#include "ObjCalCharacter.h"
#include "NewMasterLevelSkillTreeSystem.h"
#include "MapClass.h"
#include "MonsterAttr.h"
#include "..\common\SetItemOption.h"
#include "ItemAddOption.h"
#include "DarkSpirit.h"
#include "IllusionTempleEvent.h"
#include "Raklion.h"
#include "RaklionBattleUserMng.h"
#include "ChaosCard.h"
#include "PCBangPointSystem.h"
#include "Configs.h"
#include "Message.h"
#include "PremiumSystem.h"
#include "ConnectEx.h"
#include "OffExp.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "JewelsBank.h"
#include "CreditDonate.h"
#include "ExLicense.h"
#ifdef IMPERIAL_CONFLICT_NEW
#include "ImperialGuardian.h"
#endif

#include "Brotherhood.h"
#include "ExFunction.h"
#include "ExUser.h"
#include "GMManager.h"
#include "BMQuest.h"
#include "SProtocol.h"
#include "Marriage.h"
#include "Shop.h"
#include "DungeonSiege.h"
#include "BloodCastle.h"
#include "BufferSystem.h"
#include "ExGDManager.h"
#include "ExText.h"
#include "PremiumSystemEx.h"
#include "AccountSecurity.h"
#include "CarnageEvent.h"
#include "BanSystem.h"
#include "QuestionAnswer.h"

CLogToFile KUNDUN_GM_LOG( "KUNDUN_EVENT_GM_LOG", ".\\KUNDUN_EVENT_GM_LOG", 1);
CGMMng cManager;

CGMMng::CGMMng()
{
	this->ManagerInit();
}

CGMMng::~CGMMng()
{
	return;
}

void CGMMng::Init()
{
	this->cCommand.Init();

	this->cCommand.Add(lMsg.Get(MSGGET(11, 184)), 100, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 185)), 101, 35);

	//this->cCommand.Add("/move", 101); //season3 add-on lol
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 186)), 102);
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 187)), 103);
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 188)), 105);
	
	this->cCommand.Add(lMsg.Get(MSGGET(11, 189)), 104, 34);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 190)), 106, 34);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 191)), 108, 34);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 192)), 112, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 193)), 111, 2);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 194)), 109, 2);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 195)), 110, 2);

	this->cCommand.Add("/ґЙ·В", 501,34);//
	this->cCommand.Add("/ЖДЖј", 502,34);//
	this->cCommand.Add("/ВёГіВЅВєГ…ГЌВјГ’Г€ВЇ", 503,34);//
	this->cCommand.Add("/ВёГіВЅВєГ…ГЌГЃВ¦В°Г…", 504,34);//
	this->cCommand.Add("/ѕЖАМЕЫБ¦°Е", 505,34);//
	this->cCommand.Add("/АОєҐБ¦°Е", 506,34);//
	this->cCommand.Add("/ДіёЇЕНјТИЇ", 507,34);//

	this->cCommand.Add("/ability", 501,34);//
	this->cCommand.Add("/party", 502,34);//
	this->cCommand.Add("/summonmonster", 503,34);//
	this->cCommand.Add("/clearmonster", 504,34);//
	this->cCommand.Add("/clearitem", 505,34);//
	this->cCommand.Add("/clearinven", 506,34);//
	this->cCommand.Add("/summonchar", 507,34);//

	this->cCommand.Add(lMsg.Get(MSGGET(11, 197)), 201, 33);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 198)), 200, 33);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 199)), 202, 3);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 200)), 203, 33);


	this->cCommand.Add(lMsg.Get(MSGGET(11, 204)), 100, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 205)), 101, 35);
	
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 206)), 102);
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 207)), 103);
	//this->cCommand.Add(lMsg.Get(MSGGET(11, 208)), 105);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 209)), 104, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 210)), 106, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 211)), 108, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 212)), 112, 34);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 213)), 111, 2);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 214)), 109, 2);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 215)), 110, 2);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 217)), 201, 33);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 218)), 200, 33);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 219)), 202, 3);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 220)), 203, 33);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 201)), 214, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 202)), 215, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 203)), 216, 34);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 221)), 214, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 222)), 215, 34);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 223)), 216, 34);

	
/*#if(GS_CASTLE == 1)
	// CASTLESIEGE Commands
	this->cCommand.Add("/cschangeowner", 331);
	this->cCommand.Add("/cssetregsiege", 332);
	this->cCommand.Add("/cssetregmark", 333);
	this->cCommand.Add("/cssetnotify", 334);
	this->cCommand.Add("/cssetstart", 335);
	this->cCommand.Add("/cssetend", 336);
	this->cCommand.Add("/cscurowner", 337);
	this->cCommand.Add("/cscurstate", 338);
	this->cCommand.Add("/cschangeside", 340);
	// CRYWOLF Commands
	this->cCommand.Add(lMsg.Get(3338), 345);
	this->cCommand.Add(lMsg.Get(3339), 346);
	this->cCommand.Add(lMsg.Get(3340), 347);
	this->cCommand.Add(lMsg.Get(3341), 348);
#endif

#if(GS_CASTLE==0)
	// KANTURU Commands
	this->cCommand.Add("/Д­ЕхёЈґл±в»уЕВ", 369); //season 3.0 changed
	this->cCommand.Add("/Д­ЕхёЈё¶ѕЯАь", 370); //season 3.0 changed

	this->cCommand.Add("/ё¶ѕЯёуЅєЕН1", 371);
	this->cCommand.Add("/ё¶ѕЯ1", 372);
	this->cCommand.Add("/ё¶ѕЯёуЅєЕН2", 373);
	this->cCommand.Add("/ё¶ѕЯ2", 374);
	this->cCommand.Add("/ё¶ѕЯёуЅєЕН3", 375);
	this->cCommand.Add("/ё¶ѕЯ3", 376);
	this->cCommand.Add("/ё¶ѕЯ3јє°ш", 377);
	this->cCommand.Add(lMsg.Get(MSGGET(13, 60)), 378);
	this->cCommand.Add("/ё¶ѕЯЅЗЖР", 379);
	this->cCommand.Add("/Д­ЕхёЈіЄАМЖ®ёЮѕоАь", 380);
	this->cCommand.Add(lMsg.Get(MSGGET(13, 61)), 381);
	this->cCommand.Add("/іЄАМЖ®ёЮѕоЅЗЖР", 382);
	this->cCommand.Add("/Д­ЕхёЈБ¤Б¦АЗЕѕ", 383);
	this->cCommand.Add("/Б¤Б¦АЗЕѕї­±в", 384);
	this->cCommand.Add("/Б¤Б¦АЗЕѕґЭ±в", 385);
	this->cCommand.Add("/Д­ЕхёЈБѕ·б", 386);

	this->cCommand.Add(lMsg.Get(MSGGET(13, 57)), 387);
	this->cCommand.Add(lMsg.Get(MSGGET(13, 58)), 388);
	this->cCommand.Add(lMsg.Get(MSGGET(13, 59)), 389);
#endif*/

//	this->cCommand.Add("/templeready", 392); //season 2.5 add-on
//	this->cCommand.Add("/templestart", 393); //season 2.5 add-on
//	this->cCommand.Add("/templeend", 394); //season 2.5 add-on
//	this->cCommand.Add("/templereset", 395); //season 2.5 add-on
//	this->cCommand.Add("/masterlevel", 406); //season 3.5 add-on
//	this->cCommand.Add("/mlpoint", 407); //season 3.5 add-on
//	this->cCommand.Add("/ms_reset", 408); //season 3.5 add-on

	// KUNDUN Commands
	this->cCommand.Add("/ДпµР»уЕВ", 320, 2);
	this->cCommand.Add("/ДпµРЗЗ", 321, 2);
	this->cCommand.Add("/ДпµРИёє№·®", 322, 2);
	this->cCommand.Add("/ДпµРГКґзИёє№·®", 323, 2);
	this->cCommand.Add("/ДпµРИёє№ЅГ°Ј", 324, 2);

	if(g_ExLicense.CheckUser(eExUB::PrideMu) || g_ExLicense.CheckUser(eExUB::PrideMuLocal) || g_ExLicense.CheckUser(eExUB::Local3))
	{
		this->cCommand.Add("/cschangeowner", 331 ,1);
		this->cCommand.Add("/cssetregsiege", 332, 1);
		this->cCommand.Add("/cssetregmark", 333, 1);
		this->cCommand.Add("/cssetnotify", 334, 1);
		this->cCommand.Add("/cssetstart", 335, 1);
		this->cCommand.Add("/cssetend", 336, 1);
		this->cCommand.Add("/cscurowner", 337, 1);
		this->cCommand.Add("/cscurstate", 338, 1);
		this->cCommand.Add("/cschangeside", 340, 1);
	}

	this->cCommand.Add("/ЖшБЧ", 217, 34);
	this->cCommand.Add("/hide_on", 390, 32); //season 2.5 add-on //Ехён
	this->cCommand.Add("/hide_off", 391, 32); //season 2.5 add-on //ЕхёнЗШБ¦

	this->cCommand.Add("/gmove", 600, 1);
	//this->cCommand.Add("/vault", 601, 1);

	this->cCommand.Add("/partyleader", 602, 1);
#if(_BAN_SYSTEM_)
	this->cCommand.Add("/banchat", 604, 1);
	this->cCommand.Add("/banpost", 605, 1);
	this->cCommand.Add("/banchar", 606, 1);
	this->cCommand.Add("/banallchat", 607, 1);
	this->cCommand.Add("/unbanchat", 608, 1);
	this->cCommand.Add("/unbanpost", 609, 1);
	this->cCommand.Add("/unbanallchat", 610, 1);
	this->cCommand.Add("/unbanchar", 611, 1);
#endif
	this->cCommand.Add("/offafk", 612, 1);

	if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2) || g_ExLicense.CheckUser(eExUB::SILVER_Local))
	{
		this->cCommand.Add("/sendchaos", 613, 1);
		this->cCommand.Add("/sendbless", 614, 1);
		this->cCommand.Add("/sendsoul", 615, 1);		
	}
	else
	{
		this->cCommand.Add(g_ExText.GetText(139), 613, 1);
		this->cCommand.Add(g_ExText.GetText(140), 614, 1);
		this->cCommand.Add(g_ExText.GetText(141), 615, 1);
	}
	
#ifdef PRIVATE_MODULE
	if(g_ExLicense.CheckUser(eExUB::Vadim))
	{
		this->cCommand.Add("/sendjowbank", 616, 1);
	}
	else if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2) || g_ExLicense.CheckUser(eExUB::SILVER_Local))
	{
		this->cCommand.Add("/sendlife", 616, 1);
	}
	else
	{
		this->cCommand.Add(g_ExText.GetText(142), 616, 1);
	}
#else
	this->cCommand.Add("/sendlifebank", 616, 1);
#endif

	if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2) || g_ExLicense.CheckUser(eExUB::SILVER_Local))
	{
		this->cCommand.Add("/recvchaos", 617, 1);
		this->cCommand.Add("/recvbless", 618, 1);
		this->cCommand.Add("/recvsoul", 619, 1);
	}
	else
	{
		this->cCommand.Add(g_ExText.GetText(143), 617, 1);
		this->cCommand.Add(g_ExText.GetText(144), 618, 1);
		this->cCommand.Add(g_ExText.GetText(145), 619, 1);
	}

#ifdef PRIVATE_MODULE
	if(g_ExLicense.CheckUser(eExUB::Vadim))
	{
		this->cCommand.Add("/recvjowbank", 620, 1);
	}
	else if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2) || g_ExLicense.CheckUser(eExUB::SILVER_Local))
	{
		this->cCommand.Add("/recvlife", 620, 1);
	}
	else
	{
		this->cCommand.Add(g_ExText.GetText(146), 620, 1);
	}
#else
	this->cCommand.Add("/recvlifebank", 620, 1);
#endif

	this->cCommand.Add("/buy", 621, 1);
	this->cCommand.Add("/sellcredit", 622, 1);
	if (g_ExLicense.CheckUser(eExUB::snaker))
	{
		this->cCommand.Add("/寻求组队", 623, 1);
	}
	else
	{
		this->cCommand.Add("/autoparty", 623, 1);
	}

	this->cCommand.Add("/sendzen", 624, 1);
	this->cCommand.Add("/recvzen", 625, 1);

	this->cCommand.Add("/class", 626, 1);
	if (g_ExLicense.CheckUser(eExUB::snaker))
	{
		this->cCommand.Add("/关闭组队", 627, 1);
	}
	else
	{
		this->cCommand.Add("/autopartyoff", 627, 1);
	}

	this->cCommand.Add("/credit", 628, 1);
	this->cCommand.Add("/goblin-wcoin", 629, 1);
	
#ifdef PRIVATE_MODULE
#if _CONFLICT_
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2))
	{
		this->cCommand.Add("/exchaos", 630, 1);
		this->cCommand.Add("/exbless", 631, 1);
		this->cCommand.Add("/exsoul", 632, 1);
		this->cCommand.Add("/exlife", 633, 1);
	}
#endif


	if(g_ExLicense.CheckUser(eExUB::PrideMuLocal) || 
		g_ExLicense.CheckUser(eExUB::PrideMu) ||
		g_ExLicense.CheckUser(eExUB::drynea) || 
		g_ExLicense.CheckUser(eExUB::Local3) || 
		g_ExLicense.CheckUser(eExUB::feqan) || 
		g_ExLicense.CheckUser(eExUB::MU2Play) || 
		g_ExLicense.CheckUser(eExUB::bassreflexive) ||
		!g_ExLicense.CheckUser(eExUB::Escalate) ||
		!g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		this->cCommand.Add("/buypremium", 637, 1);
	}
#ifdef SEND_CREDIT_SILVER
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2))
	{
		this->cCommand.Add("/sendcredits", 638, 1);
	}
#endif
#ifdef DISCONECT_FRIEND
	if( g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(ulasevich) || g_ExLicense.CheckUser(ulasevich2) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) ||
		g_ExLicense.CheckUser(eExUB::MU2Play) || g_ExLicense.CheckUser(eExUB::Sentinel) || g_ExLicense.CheckUser(eExUB::Escalate) || 
		g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2) || g_ExLicense.CheckUser(eExUB::RevoMU) || g_ExLicense.CheckUser(eExUB::GloryMU) ||
		g_ExLicense.CheckUser(eExUB::mu4you) || g_ExLicense.CheckUser(eExUB::eternalmu) || g_ExLicense.CheckUser(eExUB::NSGames))
	{
		this->cCommand.Add("/dcfriend", 639, 1);
	}

	

#endif // DISCONECT_FRIEND


#endif

#if(SYSTEMOF_BROTHER==TRUE)
	this->cCommand.Add("/brteleport", 640, 1);
	this->cCommand.Add("/brstart", 641, 1);
	this->cCommand.Add("/brexit", 642, 1);
#endif

	this->cCommand.Add("/sendwcoinc", 643, 1);
	this->cCommand.Add("/sendwcoinp", 644, 1);
	this->cCommand.Add("/sendgoblin", 645, 1);

	this->cCommand.Add("/inventoryclear", 404, 1);
#if(SYSTEMOF_BROTHER==TRUE)
	this->cCommand.Add("/brnew", 646, 1);
#endif

	this->cCommand.Add("/bminfo", 647, 1);
#if(CMD_DC_ALL)
	this->cCommand.Add("/dcall", 648, 1);
#endif

#if(CUSTOM_MARRIAGE)
	this->cCommand.Add("/marriageoff", 649, 1);
#endif
	if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2) || g_ExLicense.CheckUser(eExUB::SILVER_Local))
	{
		this->cCommand.Add("/sendcreateon", 650, 1);
		this->cCommand.Add("/recvcreateon", 651, 1);
	}
	else if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		this->cCommand.Add("/sendcreation", 650, 1);
		this->cCommand.Add("/recvcreation", 651, 1);
	}
	this->cCommand.Add("/excreateon", 652, 1);

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		this->cCommand.Add("/autoptoff", 653, 1);
		this->cCommand.Add("/autopton", 654, 1);
	}
#if(DONATE_SHOP==TRUE)
	this->cCommand.Add("/donate", 655, 1);
#endif
#if(EVENT_DUNGEON_SIEGE)
	this->cCommand.Add("/dungeonstart", 656, 1);
#endif
	this->cCommand.Add("/debug", 657, 1);
	//this->cCommand.Add("/加力量", 657, 1);
	

#if(CMD_ANTI_CHEAT_HDD)
	this->cCommand.Add("/hdd", 658, 1);
#endif
#if(COMMAND_DROP)
	this->cCommand.Add("/item", 659, 1);
#endif

	this->cCommand.Add("/vipbronze", 660, 1);
	this->cCommand.Add("/vipsilver", 661, 1);
	this->cCommand.Add("/vipgold", 662, 1);

	this->cCommand.Add("/value", 663, 1);

#if(DEV_BANSYSTEM)
	this->cCommand.Add("/banhddchat", 664, 1);
	this->cCommand.Add("/unbanhddchat", 665, 1);
	this->cCommand.Add("/banhddchar", 666, 1);
	this->cCommand.Add("/unbanhddchar", 667, 1);
#endif

	this->cCommand.Add("/exguardian", 668, 1);
	this->cCommand.Add("/exharmony", 669, 1);
	this->cCommand.Add("/exlowstone", 670, 1);
	this->cCommand.Add("/exhighstone", 671, 1);
	this->cCommand.Add("/exgemstone", 672, 1);

	this->cCommand.Add("/devcmd", 690, 1);


	this->WatchTargetIndex = -1;
}


void CGMMng::ManagerInit()
{
	for ( int n = 0;n<MAX_GAME_MASTER ; n++ )
	{
		this->ManagerIndex[n] = -1;
	}
}


int CGMMng::ManagerAdd(char* name, int aIndex)
{
	for ( int n=0 ; n<MAX_GAME_MASTER ; n++ )
	{
		if ( this->ManagerIndex[n] == -1 )
		{
			strcpy(this->szManagerName[n], name);
			this->ManagerIndex[n] = aIndex;
			return n;
		}
	}

	return -1;
}


void CGMMng::ManagerDel(char* name)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++)
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			if ( strcmp(this->szManagerName[n], name) == 0 )
			{
				this->ManagerIndex[n] = -1;
				//break;
				return; //Original Code (GS 0.65)
			}
		}
	}
}


void CGMMng::ManagerSendData(LPSTR szMsg, int size)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			GCServerMsgStringSend(szMsg, this->ManagerIndex[n], 0);
		}
	}
}

void CGMMng::DataSend(LPBYTE szMsg, int size)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			::DataSend(this->ManagerIndex[n], szMsg, size);
		}
	}
}


void CGMMng::BattleInfoSend(char* Name1, BYTE score1, char* Name2, BYTE score2)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			GCGoalSend(this->ManagerIndex[n], Name1, score1, Name2, score2);
		}
	}
}


int CGMMng::GetCmd(char* szCmd)
{
	for ( int n	=0; n< MAX_GM_COMMAND ; n++ )
	{
		if ( this->cCommand.nCmdCode[n] > 0 )
		{
			if ( stricmp(szCmd, this->cCommand.szCmd[n]) == 0 )
			{
				return this->cCommand.nCmdCode[n];
			}
		}
	}

	return 0;
}

// 005708B0 -> calls 1x from ManagementProc
BYTE CGMMng::GetData(char *szCmd,int &command_code,int &gamemaster_code)
{
	for ( int n	=0; n< MAX_GM_COMMAND ; n++ )
	{
		if ( this->cCommand.nCmdCode[n] > 0 )
		{
			if ( stricmp(szCmd, this->cCommand.szCmd[n]) == 0 )
			{
				command_code = this->cCommand.nCmdCode[n];
				gamemaster_code = this->cCommand.nGMCode[n];

				return TRUE;
			}
		}
	}

	return 0;
}

char* CGMMng::GetTokenString()
{
	//Original Code (GS 0.65)
	char seps[] = " ";
	return strtok(NULL, seps);
}

int CGMMng::GetTokenNumber()
{
	char seps[] = " ";
	char * szToken;

	szToken = strtok(NULL, seps);

	if( szToken != NULL )
	{
		return atoi(szToken);
	}
	return 0;
}

wchar_t *CodePageToUnicode(int codePage, char* src)
    {
    if (!src) return 0;
    int srcLen = strlen(src);
    if (!srcLen)
	{
	wchar_t *w = new wchar_t[1];
	w[0] = 0;
	return w;
	}
	
    int requiredSize = MultiByteToWideChar(codePage,
        0,
        src,srcLen,0,0);
	
    if (!requiredSize)
        {
        return 0;
        }
	
    wchar_t *w = new wchar_t[requiredSize+1];
    w[requiredSize] = 0;
	
    int retval = MultiByteToWideChar(codePage,
        0,
        src,srcLen,w,requiredSize);
    if (!retval)
        {
        delete [] w;
        return 0;
        }
	
    return w;
    }

char* UnicodeToCodePage(int codePage, wchar_t *src)
    {
    if (!src) return 0;
    int srcLen = wcslen(src);
    if (!srcLen)
	{
	char *x = new char[1];
	x[0] = '\0';
	return x;
	}
	
    int requiredSize = WideCharToMultiByte(codePage,
        0,
        src,srcLen,0,0,0,0);
	
    if (!requiredSize)
        {
        return 0;
        }
	
    char *x = new char[requiredSize+1];
    x[requiredSize] = 0;
	
    int retval = WideCharToMultiByte(codePage,
        0,
        src,srcLen,x,requiredSize,0,0);
    if (!retval)
        {
        delete [] x;
        return 0;
        }
	
    return x;
    }

void CirilicaFIX2(char* s)
{
	int i = 0;
	int k = 0;
	for (i = 0, k = 0; s[i]; k ++)
	{
		if (s[i] < 0)
		{
			s[k] = (s[i] + 48) * 64 + s[i + 1] + 48;
			i += 2;
		}
		else
		{
			s[k] = s[i];
			i ++;
		}
	}
	s[k] = NULL;
}


int CGMMng::ManagementProc(LPOBJ lpObj, char* szCmd, int aIndex) //00570A00
{
	//Original Code (GS 0.65)
	char seps[] = " ";
	char *szCmdToken;
	char string[256];
	char szId[20];
	char *pId = szId;

	int len= strlen(szCmd);
	if( len < 1 || len > 250 ) return FALSE;

	memset(szId, 0, 20);

	strcpy(string, szCmd);
	
	szCmdToken = strtok(string, seps);
	int command_number = GetCmd(szCmdToken);

	int command_code,gamemaster_code;//Season 4.5 addon

	if(this->GetData(szCmdToken,command_code,gamemaster_code) == FALSE)//Season 4.5 addon
	{
		return FALSE;
	}
	
	if(CheckAuthorityCondition(gamemaster_code,lpObj) == FALSE)//Season 4.5 addon
	{
		return FALSE;
	}

	switch ( command_code )
	{
	case 230://Identical
		{
			for(int i = 0; i < 15; i++)
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,13), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
		}
		break;
	case 231://Identical
		{
			for(int i = 0; i < 15; i++)
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,14), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
		}
		break;
	case 233://Identical
		{
			for(int i = 0; i < 20; i++)
			{
				MakeRandomSetItem(aIndex); 
			}
		}
		break;
	case 232://Identical
		{
			char * szSetItemName = this->GetTokenString();

			if ( szSetItemName == NULL )
			{
				return 0;
			}

			int iLevel;
			int iOption1 = 0;
			int iOption2 = 0;
			int iOption3 = 0;
			BYTE NewOption = 0;
			int iDur = BYTE(-1);

			iLevel = this->GetTokenNumber();
			iDur = this->GetTokenNumber();
			iOption1 = this->GetTokenNumber();
			iOption2 = this->GetTokenNumber();

			int iOptionLevel = this->GetTokenNumber();
			int iOptionType = this->GetTokenNumber();

			int iSetOption;

			if(iOptionLevel == 4)
			{
				iOption3 = 1;
			}
			else if(iOptionLevel == 8)
			{
				iOption3 = 2;
			}
			else if(iOptionLevel == 12)
			{
				iOption3 = 3;
			}
			else if(iOptionLevel == 16)
			{
				iOption3 = 4;
			}

			for(int i = 0; i < MAX_ITEMS; i++)
			{
				if(strcmp(gSetItemOption.GetSetOptionName(i, 1), szSetItemName) == 0)
				{
					iSetOption = 1;

					if(iOptionType == 0)
					{
						if( rand()%100 < 80 ) 
								iSetOption |= 4;
							else 
								iSetOption |= 8;
					}
					else if(iOptionType == 1)
					{
						iSetOption |= 4;
					}
					else
					{
						iSetOption |= 8;
					}

					ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, i, (BYTE)iLevel, (BYTE)iDur, (BYTE)iOption1, (BYTE)iOption2, (BYTE)iOption3, -1, (BYTE)NewOption, (BYTE)iSetOption); 
				}

				if(strcmp(gSetItemOption.GetSetOptionName(i, 2), szSetItemName) == 0)
				{
					iSetOption = 2;

					if(iOptionType == 0)
					{
						if( rand()%100 < 80 ) 
								iSetOption |= 4;
							else 
								iSetOption |= 8;
					}
					else if(iOptionType == 1)
					{
						iSetOption |= 4;
					}
					else
					{
						iSetOption |= 8;
					}

					ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, i, (BYTE)iLevel, (BYTE)iDur, (BYTE)iOption1, (BYTE)iOption2, (BYTE)iOption3, -1, (BYTE)NewOption, (BYTE)iSetOption); 
				
				}
			}
		}
		break;
		case 330://identical
		{
			TNotice pNotice(1);
			pNotice.SendToUser(lpObj->m_Index, "PK»уЕВё¦ ГК±вИ­ ЗХґПґЩ.");
			lpObj->m_PK_Count = 0;
			lpObj->m_PK_Level = 3;
			lpObj->m_PK_Time = 0;

			if(lpObj->PartyNumber >= 0)
			{
				gParty.SetPkLevel(lpObj->PartyNumber, lpObj->m_Index, lpObj->DBNumber, lpObj->m_PK_Level);
				gParty.SetPkCount(lpObj->PartyNumber);
			}
		}
		break;
		case 319://Identical
		{
			int iTokenNumber = this->GetTokenNumber();

			if(iTokenNumber == 0)
			{
				TNotice pNotice(1);
				pNotice.SendToUser(lpObj->m_Index, "%d Е¬·ЎЅє ёуЅєЕН°Ў ѕшЅАґПґЩ.");
			}
			else
			{
				for(int n = 0; n < MAX_VIEWPORT; n++)
				{
					if(lpObj->VpPlayer[n].state != 0)
					{
						if(lpObj->VpPlayer[n].type == OBJ_MONSTER)
						{
							if ( lpObj->VpPlayer[n].number >= 0 )
							{
								LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

								if ( lpTarget->Class == iTokenNumber )
								{
									TNotice pNotice(1);
									pNotice.SendToUser(lpObj->m_Index, "%d Е¬·ЎЅє ёуЅєЕНАЗ HP = %7.0f / %7.0f",iTokenNumber, lpTarget->Life, lpTarget->MaxLife);
								}
							}
						}
					}
				}
			}
		}
		break;
		case 309://Identical
		{
			TNotice pNotice(0);
			pNotice.SendToAllUser("%s",this->GetTokenString());						
		}
		break;
		case 314://Identical
		{
			int iTokenNumber = this->GetTokenNumber();

			if(iTokenNumber == 0)
			{
				iTokenNumber = 3;
			}

			if(iTokenNumber == 1)
			{
				lpObj->m_PK_Level = 1;
			}
			else if(iTokenNumber == 2)
			{
				lpObj->m_PK_Level = 2;
			}
			else if(iTokenNumber == 3)
			{
				lpObj->m_PK_Time = 0;
				lpObj->m_PK_Level = 3;
			}
			else if(iTokenNumber == 4)
			{
				lpObj->m_PK_Level = 4;
				lpObj->m_PK_Count = 1;
			}
			else if(iTokenNumber == 5)
			{
				lpObj->m_PK_Level = 5;
				lpObj->m_PK_Count = 2;
			}
			else if(iTokenNumber == 6)
			{
				lpObj->m_PK_Level = 6;
				lpObj->m_PK_Count = 3;
			}
			else
			{
				lpObj->m_PK_Level = 3;
			}

			if(lpObj->m_PK_Level == 4)
			{
				GCServerMsgStringSend(lMsg.Get(1137), lpObj->m_Index, 1);
			}

			if(lpObj->m_PK_Level <= 6)
			{
				GCPkLevelSend(lpObj->m_Index, lpObj->m_PK_Level);
			}

			if(lpObj->PartyNumber >= 0)
			{
				gParty.SetPkLevel(lpObj->PartyNumber, lpObj->m_Index, lpObj->DBNumber, lpObj->m_PK_Level);
				gParty.SetPkCount(lpObj->PartyNumber);
			}						
		}
		break;
		case 318://
        {
            int iItemType;//5d0
            int iItemIndex;//5D4
            int iLevel;//5d8
            int iOption1 = 0;//5dc
            int iOption2 = 0;//5e0
            int iOption3 = 0;//5e4
            BYTE NewOption = 0;//5e8
            int iDur = (BYTE)255;//5ec
 
            char szText[100] = {0};
            char szItemName[20] = {0};
 
            try
			{
				memset(szItemName, 0, sizeof(szItemName));
				strcpy(szItemName, this->GetTokenString()); //local created automatically
			}
			catch(...)
			{
				wsprintf(szItemName, "Е©ё®Ѕє");
			}
 
            int iType;//668
            int iIndex;//66c
			int i = 0;
            for(i = 0; i < MAX_ITEMS; i++)//670
            {
                if(strcmp(szItemName, ItemAttribute[i].Name) == 0)
                {
                    iType = i / 512;
                    iIndex = i - (iType << 9) ;
                    sprintf(szItemName,"[ %s ] АЗ ѕЖАМЕЫ АОµ¦Ѕє = %d, %d",ItemAttribute[i].Name,iType,iIndex);//maybe need translation
                    break;
                }
            }
 
            if( i == MAX_ITEMS) //failure condition
            {
                sprintf(szText, "ѕЛјц ѕшґВ ѕЖАМЕЫ..");
                GCServerMsgStringSend(szText, lpObj->m_Index, 1);
                return FALSE;
            }
 
            GCServerMsgStringSend(szText, lpObj->m_Index, 1);
           
            iItemType = iType;//5d0
            iItemIndex = iIndex;//5d4
            iLevel = this->GetTokenNumber();//5d8
            iDur = this->GetTokenNumber();//5ec
            iOption1 = this->GetTokenNumber();//5dc
            iOption2 = this->GetTokenNumber();//5e0
            int iItemOption3 = this->GetTokenNumber();//674
       
            if(iItemType == 13 && iItemIndex == 3)
            {
                if(iItemOption3 < 8)
                {
                    iOption3 = iItemOption3;
                }
            }
            else
            {
                if(iItemOption3 == 4)
                {
                    iOption3 = 1;
                }
                else if(iItemOption3 == 8)
                {
                    iOption3 = 2;
                }
                else if(iItemOption3 == 12)
                {
                    iOption3 = 3;
                }
                else if (iItemOption3 == 16)
                {
                    iOption3 = 4;
                }
            }
 
            int EBP678 = this->GetTokenNumber();
            int EBP67C = this->GetTokenNumber();
 
            if(EBP678 != 0 )
            {
                if( EBP67C == 0)
                {
                    if((rand()%100) < 80)
                    {
                        EBP678 |= 4;
                    }
                    else
                    {
                        EBP678 |= 8;
                    }
                }
                else if (EBP67C == 1)
                {
                    EBP678 |= 4;
                }
                else
                {
                    EBP678 |= 8;
                }
            }
           
            int EBP680 = this->GetTokenNumber();
 
            if(EBP680 > 0)
            {
                NewOption |= 0x20;
            }
 
            int EBP684 = this->GetTokenNumber();
 
            if(EBP684 > 0)
            {
                NewOption |= 0x10;
            }
 
            int EBP688 = this->GetTokenNumber();
 
            if(EBP688 > 0)
            {
                NewOption |= 0x08;
            }
 
            int EBP68C = this->GetTokenNumber();
 
            if(EBP68C > 0)
            {
                NewOption |= 0x04;
            }
 
            int EBP690 = this->GetTokenNumber();
 
            if(EBP690 > 0)
            {
                NewOption |= 0x02;
            }
 
            int EBP694 = this->GetTokenNumber();
 
            if(EBP694 > 0)
            {
                NewOption |= 0x01;
            }
 
           
            if( iItemType >= 0 && iItemType < 512 &&
                iItemIndex >= 0 && iItemIndex < 512)
            {
                int iItemNumber = ItemGetNumberMake(iItemType,iItemIndex);
               
                if( iItemNumber == ITEMGET(0,19) ||
                    iItemNumber == ITEMGET(4,18) ||
                    iItemNumber == ITEMGET(5,10) ||
                    iItemNumber == ITEMGET(2,13))
                {
                    NewOption = 63;
                }
               
                if(iItemNumber == ITEMGET(13,4) || iItemNumber ==  ITEMGET(13,5))
                {
                    PetItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, iItemNumber, iLevel, iDur ,iOption1,  iOption2, iOption3, -1, NewOption, EBP678);
                }
                else
                {
                    ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, iItemNumber, (BYTE)iLevel, (BYTE)iDur ,(BYTE)iOption1,  (BYTE)iOption2, (BYTE)iOption3, -1, (BYTE)NewOption, (BYTE)EBP678);
                }
            }
        }
        break; 
		case 308:
		{
			char szText[100] = {0};//6fc
			char szItemName[20] = {0};//710

			strcpy(szItemName, this->GetTokenString());
			int i = 0;
			for(i = 0; i < MAX_ITEMS; i++)//714
			{
				if(strcmp(szItemName, ItemAttribute[i].Name) == 0)
				{
					int iType = i / 512;//718
					int iIndex = i - (iType << 9) ;//71c
					sprintf(szText,"[ %s ] АЗ ѕЖАМЕЫ АОµ¦Ѕє = %d, %d",ItemAttribute[i].Name,iType,iIndex);
					break;
				}
			}

			if(i == MAX_ITEMS) //failure condition
			{
				sprintf(szText, "ѕЛјц ѕшґВ ѕЖАМЕЫ..");
			}

			GCServerMsgStringSend(szText, lpObj->m_Index, 1);
		}
		break;
		case 305:
		{
			int iClass = lpObj->Class;//720
			int iStrength = this->GetTokenNumber();//ebp724
			int iDexterity = this->GetTokenNumber();//ebp728
			int iVitality = this->GetTokenNumber();//ebp72C
			int iEnergy = this->GetTokenNumber();//ebp730
			int iStandartPoints;//ebp734
			int iAllPoints = iStrength + iDexterity + iVitality + iEnergy;//ebp738

			if(lpObj->Class == CLASS_DARKLORD || lpObj->Class == CLASS_MAGUMSA)
			{
				iStandartPoints = 7 * (lpObj->Level -1 ) +
						 DCInfo.DefClass[iClass].Strength +
						 DCInfo.DefClass[iClass].Dexterity +
						 DCInfo.DefClass[iClass].Vitality +
						 DCInfo.DefClass[iClass].Energy;
			}
			else
			{
				iStandartPoints = 5 * (lpObj->Level -1 ) +
						 DCInfo.DefClass[iClass].Strength +
						 DCInfo.DefClass[iClass].Dexterity +
						 DCInfo.DefClass[iClass].Vitality +
						 DCInfo.DefClass[iClass].Energy; 
			}

			if( iStrength	< DCInfo.DefClass[iClass].Strength	||
				iDexterity  < DCInfo.DefClass[iClass].Dexterity ||
				iVitality	< DCInfo.DefClass[iClass].Vitality	||
				iEnergy		< DCInfo.DefClass[iClass].Energy)
			{
				
				GCServerMsgStringSend("ЅєЕИ јіБ¤АМ АЯёш µЖЅАґПґЩ.(±вє»°Є№Мёё)", lpObj->m_Index, 1);
				return FALSE;
			}

			if ( iAllPoints > iStandartPoints )
            {
				GCServerMsgStringSend("ЅєЕИ јіБ¤АМ АЯёш µЖЅАґПґЩ.(ЗХГК°ъ)", lpObj->m_Index, 1);
				return FALSE;
            }
			
			lpObj->ChangeUP = 0;
			lpObj->Experience = 0;

			lpObj->Strength = iStrength;
			lpObj->Dexterity = iDexterity;
			lpObj->Vitality = iVitality;
			lpObj->Energy = iEnergy;
		
			lpObj->Life = (iVitality - DCInfo.DefClass[iClass].Vitality) * DCInfo.DefClass[iClass].LevelLife + DCInfo.DefClass[iClass].Life;
			lpObj->MaxLife = (iVitality - DCInfo.DefClass[iClass].Vitality) * DCInfo.DefClass[iClass].LevelLife + DCInfo.DefClass[iClass].MaxLife;
			lpObj->Mana = (iVitality - DCInfo.DefClass[iClass].Energy) * DCInfo.DefClass[iClass].LevelMana + DCInfo.DefClass[iClass].Mana;
			lpObj->MaxMana = (iVitality - DCInfo.DefClass[iClass].Energy) * DCInfo.DefClass[iClass].LevelMana + DCInfo.DefClass[iClass].MaxMana;
	
			lpObj->LevelUpPoint = iStandartPoints - iAllPoints;
			
			GCServerMsgStringSend("АёИеИе ДіёЇЕН ЅєЕИ АзјіБ¤ їП·б!!", lpObj->m_Index, 1);
			
			gObjCloseSet(lpObj->m_Index, 1);
		}
		break;
		case 339:
		{
			int iClass = lpObj->Class;//73C
			int iStrength = this->GetTokenNumber();//740
			int iDexterity = this->GetTokenNumber();//744
			int iVitality = this->GetTokenNumber();//748
			int iEnergy = this->GetTokenNumber();//74C
			
			lpObj->ChangeUP = 0;
			lpObj->Experience = 0;
			lpObj->Strength = iStrength;
			lpObj->Dexterity = iDexterity;
			lpObj->Vitality = iVitality;
			lpObj->Energy = iEnergy;


			lpObj->Life = (iVitality - DCInfo.DefClass[iClass].Vitality) * DCInfo.DefClass[iClass].LevelLife + DCInfo.DefClass[iClass].Life;
			lpObj->MaxLife = (iVitality - DCInfo.DefClass[iClass].Vitality) * DCInfo.DefClass[iClass].LevelLife + DCInfo.DefClass[iClass].MaxLife;
			lpObj->Mana = (iVitality - DCInfo.DefClass[iClass].Energy) * DCInfo.DefClass[iClass].LevelMana + DCInfo.DefClass[iClass].Mana;
			lpObj->MaxMana = (iVitality - DCInfo.DefClass[iClass].Energy) * DCInfo.DefClass[iClass].LevelMana + DCInfo.DefClass[iClass].MaxMana;
	
			GCServerMsgStringSend("Modi.Stat Complete", lpObj->m_Index, 1);
			
			gObjCloseSet(lpObj->m_Index, 1);
		}
		break;
		case 341:
		{
			int iDbClass = lpObj->DbClass;//750
			
			if(iDbClass == 0)
			{
				lpObj->DbClass = 1;
			}
			else if(iDbClass == 16)
			{
				lpObj->DbClass = 17;
			}
			else if(iDbClass == 32)
			{
				lpObj->DbClass = 33;
			}
			else if(iDbClass == 80)
			{
				lpObj->DbClass = 81;
			}

			GCServerMsgStringSend("АьБч...", lpObj->m_Index, 1);
			
			gObjCloseSet(lpObj->m_Index, 1);
		}
		break;
		case 396:
		{
			if( lpObj->DbClass == 0 ||
				lpObj->DbClass == 16 ||
				lpObj->DbClass == 32 ||
				lpObj->DbClass == 80 )
			{
				lpObj->ChangeUP = 1;
				lpObj->DbClass |= 1;
			}

			lpObj->ChangeUP3rd = 1;
			lpObj->DbClass |= 2;

			GCServerMsgStringSend("3ВчАьБч јє°ш", lpObj->m_Index, 1);
			gObjCloseSet(lpObj->m_Index, 1);
		}
		break;
		case 397:
		{
			lpObj->ChangeUP = 0;
			lpObj->ChangeUP3rd = 0;

			switch(lpObj->DbClass)
			{
			case 1:
            case 3:
                lpObj->DbClass = 0;
				break;
            case 17:
            case 19:
				lpObj->DbClass = 16;
				break;
            case 33:
			case 35:
                lpObj->DbClass = 32;
                break;
			case 50:
                lpObj->DbClass = 48;
                break;
			case 66:
                lpObj->DbClass = 64;
                break;
			case 81:
			case 83:
                lpObj->DbClass = 80;
                break;
			}

			GCServerMsgStringSend("АьБчё®јВ", lpObj->m_Index, 1);
			gObjCloseSet(lpObj->m_Index, 1);
		}
		break;
		case 398:
		{
			int iTokenNumber = this->GetTokenNumber();//754

			if(iTokenNumber == 4)
			{
				for(int i = 0; i <= 3; i++)//758
				{
					ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,65), 0, 0, 0, 0, 0, -1, 0, 0); 
					ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,66), 0, 0, 0, 0, 0, -1, 0, 0); 
					ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,67), 0, 0, 0, 0, 0, -1, 0, 0); 
				}
			}
		}
		break;
		case 399:
		{
			int iType = this->GetTokenNumber();//75C
			int iIndex = this->GetTokenNumber();//760
			int iItemCount = this->GetTokenNumber();//764

			if(iItemCount <= 0)
			{
				iItemCount = 1;
			}
			else if(iItemCount > 50)
			{
				iItemCount = 50;
			}

			for(int i = 0; i <iItemCount; i++)//678
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(iType,iIndex), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
		}
		break;
		case 400:
		{
			int iQuestIndex = this->GetTokenNumber();

			if(iQuestIndex >= 0)
			{
				g_QuestInfo.QuestSuccessCommand(aIndex, iQuestIndex) ;
			}
		}
		break;
		case 401:
		{
			int iMoney = this->GetTokenNumber();
			gObj[aIndex].Money = iMoney;
			GCMoneySend(aIndex, gObj[aIndex].Money);
		}
		break;
		case 342:
		{
			int iTokenNumber = this->GetTokenNumber();

			MsgOutput(lpObj->m_Index, "[Жжё±±вє»і»±ё·В°ЁјТ] %d -> %d", g_iFenrirDefaultMaxDurSmall, iTokenNumber);

			g_iFenrirDefaultMaxDurSmall = iTokenNumber;
		}
		break;
		case 343: //??
		{
			int iTokenNumber = this->GetTokenNumber();

			MsgOutput(lpObj->m_Index, "[Жжё±їдБ¤і»±ё·В°ЁјТ] %d -> %d", g_iFenrirElfMaxDurSmall, iTokenNumber);

			g_iFenrirElfMaxDurSmall = iTokenNumber;
		}
		break;
		case 349: //??
		{
			int iShield = this->GetTokenNumber();

			MsgOutput(lpObj->m_Index, "[ЅЇµејцДЎјіБ¤] %d -> %d", lpObj->iShield, iShield);

			if(iShield > (lpObj->iMaxShield + lpObj->iAddShield))
			{
				iShield = lpObj->iMaxShield + lpObj->iAddShield;
			}

			lpObj->iShield = iShield;

			GCReFillSend(lpObj->m_Index, lpObj->Life, -1, 0, lpObj->iShield);
		}
		break;
		case 350: //??
		{
			MsgOutput(lpObj->m_Index, "HP:%7.1f/%7.1f , SD:%d/%d", lpObj->Life, lpObj->AddLife + lpObj->MaxLife, lpObj->iShield, lpObj->iMaxShield + lpObj->iAddShield);
		}
		break;
		case 352: //??
		{
			int iEffectType = this->GetTokenNumber();
			int iEffectValue = this->GetTokenNumber();
			int iEffectDur = this->GetTokenNumber();

			g_ItemAddOption.SetManualItemEffect(lpObj, iEffectType, iEffectValue, iEffectDur);

			GCReFillSend(lpObj->m_Index, (lpObj->MaxLife + lpObj->AddLife), 0xFE, 0, (lpObj->iMaxShield + lpObj->iAddShield));
			GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), -2, 0, (lpObj->MaxBP + lpObj->AddBP));
		}
		break;
		case 304:
		{
			for(int i = 0; i < 5; i++)
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(12,15), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
			for(int i = 0; i < 5; i++)
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,13), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
			for(int i = 0; i < 5; i++)
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,14), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
		}
		break;
		case 311:
		{
			int ItemType;
			int ItemIndex;
			int EBP798;
			int EBP79C = 0;
			int EBP7A0 = 0;
			int EBP7A4 = 0;
			BYTE EBP7A8 = 0;
			int iDur = (BYTE)-1;//7AC
			int EBP7B0;

			ItemType  = this->GetTokenNumber();//790
			ItemIndex  = this->GetTokenNumber();//794
			EBP798 = this->GetTokenNumber();
			iDur = this->GetTokenNumber();
			EBP79C = this->GetTokenNumber();
			EBP7A0 = this->GetTokenNumber();
			EBP7B0 = this->GetTokenNumber();

			if(ItemType == 13 && ItemIndex == 3)
			{
				if(	EBP7B0 < 8)
				{
					EBP7A4 = EBP7B0;
				}
			}
			else
			{
				if(EBP7B0 == 4)
				{
					EBP7A4 = 1;
				}
				else if(EBP7B0 == 8)
				{
					EBP7A4 = 2;
				}
				else if(EBP7B0 == 12)
				{
					EBP7A4 = 3;
				}
				else if(EBP7B0 == 16)
				{
					EBP7A4 = 4;
				}
			}

			int EBP7B4 = this->GetTokenNumber();
			int EBP7B8 = this->GetTokenNumber();
			
			if(EBP7B4 != 0 )
			{
				if( EBP7B8 == 0)
				{
					if((rand()%100) < 80)
					{
						EBP7B4 |= 4; 
					}
					else
					{
						EBP7B4 |= 8; 
					}
				}
				else if (EBP7B8 == 1) 
				{
					EBP7B4 |= 4; 
				}
				else
				{
					EBP7B4 |= 8; 
				}
			}
			
			int EBP7BC = this->GetTokenNumber();

			if(EBP7BC > 0)
			{
				EBP7A8 |= 0x20;
			}

			int EBP7C0 = this->GetTokenNumber();

			if(EBP7C0 > 0)
			{
				EBP7A8 |= 0x10;
			}

			int EBP7C4 = this->GetTokenNumber();

			if(EBP7C4 > 0)
			{
				EBP7A8 |= 0x08;
			}

			int EBP7C8 = this->GetTokenNumber();

			if(EBP7C8 > 0)
			{
				EBP7A8 |= 0x04;
			}

			int EBP7CC = this->GetTokenNumber();

			if(EBP7CC > 0)
			{
				EBP7A8 |= 0x02;
			}

			int EBP7D0 = this->GetTokenNumber();

			if(EBP7D0 > 0)
			{
				EBP7A8 |= 0x01;
			}

			if( ItemType >= 0 && ItemType < 512 &&
				ItemIndex >= 0 && ItemIndex < 512)
			{
				int iItemNumber = ItemGetNumberMake(ItemType,ItemIndex);//7d4
				
				if( iItemNumber == ITEMGET(0,19) || 
					iItemNumber == ITEMGET(4,18) || 
					iItemNumber == ITEMGET(5,10) || 
					iItemNumber == ITEMGET(2,13))
				{
					EBP7A8 = 63;	
				}

				for(int i =0;i < 15;i++)
				{
					ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, iItemNumber, (BYTE)EBP798, (BYTE)iDur, (BYTE)EBP79C, (BYTE)EBP7A0, (BYTE)EBP7A4, -1, (BYTE)EBP7A8, (BYTE)EBP7B4); 
				}
			}
		}
		break;
		case 301: //??
		{
			for(int i = 0; i < 15; i++)
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(12,15), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
		}
		break;
		case 302: //??
		{
			for(int i = 0; i < 15; i++)
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,16), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
		}
		break;
		case 303: //??
		{
			for(int i = 0; i < 15; i++)
			{
				ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, ITEMGET(14,22), 0, 0, 0, 0, 0, -1, 0, 0); 
			}
		}
		break;
		case 310: //??
		{
			gObj[aIndex].Money = 0;
			GCMoneySend(aIndex, 0);
		}
		break;
//#if(TESTSERVER == 1)
		case 406:
		{
			int iTokenNumber = this->GetTokenNumber();

			if(iTokenNumber < 0)
			{
				iTokenNumber = 0;
			}
			else if(iTokenNumber > 200)
			{
				iTokenNumber = 200;
			}

			if(g_MasterLevelSystem.CheckIsMasterLevelCharacter(lpObj) == 0 || (lpObj->MLevel >= 0 && iTokenNumber == 0))
			{
				LogAddTD("Use Test Command [%s][%s] /masterlevel %d -> Fail!!",lpObj->AccountID, lpObj->Name, iTokenNumber);
				return 0;
			}

			lpObj->MLevel = iTokenNumber;

			lpObj->MLExp = g_MasterLevelSystem.GetLevelExperienceTable(iTokenNumber);
			lpObj->MLNextExp = g_MasterLevelSystem.GetLevelExperienceTable(iTokenNumber+1);

			g_MasterLevelSystem.GCSendMasterLevelWindowStatus(lpObj);

			LogAddTD("Use Test Command [%s][%s] /masterlevel %d -> Success!!",lpObj->AccountID, lpObj->Name, iTokenNumber);		
		}
		break;
		case 407:
		{
			int iTokenNumber = this->GetTokenNumber();

			if(g_MasterLevelSystem.CheckIsMasterLevelCharacter(lpObj) == 0)
			{
				LogAddTD("Use Test Command [%s][%s] /mlpoint %d -> Fail!!",lpObj->AccountID, lpObj->Name, iTokenNumber);
				return 0;
			}

			lpObj->MLPoint = iTokenNumber;
			g_MasterLevelSystem.GCSendMasterLevelWindowStatus(lpObj);

			LogAddTD("Use Test Command [%s][%s] /mlpoint %d -> Success!!",lpObj->AccountID, lpObj->Name, iTokenNumber);
		}
		break;
		case 408:
		{
			for(int i = 0; i < MAX_MAGIC; i++)
			{
				if(lpObj->Magic[i].IsMagic() == TRUE)
				{
					if(g_MasterSkillSystem.CheckRequireStatus(lpObj->Magic[i].m_Skill) != 0)
					{
						lpObj->Magic[i].Clear();
					}
				}
			}

			GCServerMsgStringSend("Master Skill Reset", lpObj->m_Index, 1);
			LogAddTD("Use Test Command [%s][%s] /ms_reset %d",lpObj->AccountID, lpObj->Name, lpObj->MLPoint);
			gObjCloseSet(lpObj->m_Index, 1);
		}
		break;
		/*case 412:
		{
			int iTokenNumber = this->GetTokenNumber();

			if(iTokenNumber < 5 || iTokenNumber > 6)
			{
				return 0;
			}

			g_QuestInfo.QuestSuccessCommand(lpObj->m_Index, iTokenNumber);
		}
		break;
		case 411:
		{
			int iType = this->GetTokenNumber();
			int iMapIndex = this->GetTokenNumber();

			if((iType > 1 || iType < 0)?0:iType)
			{
				//empty
			}
			
			if(iMapIndex < 1) iMapIndex = 3;

			PMSG_SET_DEVILSQUARE pMsg;

			PHeadSetB((LPBYTE)&pMsg, 0x92, sizeof(pMsg));
			pMsg.Type = iType;

			AllSendSameMapMsg((LPBYTE)&pMsg, sizeof(pMsg), iMapIndex);
		}
		break;*/
//#endif
		case 439:
		{
			int iTokenNumber = this->GetTokenNumber();

			g_bAbilityDebug = (iTokenNumber == 1)?1:0; //wtf?

			char szTemp[256];
			wsprintf(szTemp, "Ability Debug: %s", (g_bAbilityDebug == TRUE) ? "On" : "Off");
			GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
		}
		break;
		case 436:
		{
			int iItemPos = this->GetTokenNumber();
			BYTE EBP8FC = this->GetTokenNumber();
			BYTE EBP900 = this->GetTokenNumber();
			BYTE iSocketSlot = this->GetTokenNumber();
			g_SocketOption.MakeManualOptionbyCalc(&lpObj->pInventory[iItemPos],EBP8FC,EBP900-1,iSocketSlot-1);
			::GCInventoryItemOneSend(lpObj->m_Index, iItemPos);
		}
		break;
		case 437:
		{
			int iItemPos= this->GetTokenNumber();
			BYTE iSocketSlot = this->GetTokenNumber();

			if(iSocketSlot == 0)
			{
				for(int i = 0;i < 5;i++)
				{
					g_SocketOption.RemakeSocketOption(&lpObj->pInventory[iItemPos],i);
				}
			}
			else
			{
				g_SocketOption.RemakeSocketOption(&lpObj->pInventory[iItemPos],iSocketSlot-1);
			}

			::GCInventoryItemOneSend(lpObj->m_Index, iItemPos);
		}
		break;
		case 438:
		{
			int iItemPos= this->GetTokenNumber();
			BYTE iSocketSlot = this->GetTokenNumber();
			g_SocketOption.ClearSlotOption(&lpObj->pInventory[iItemPos],iSocketSlot);
			::GCInventoryItemOneSend(lpObj->m_Index, iItemPos);
		}
		break;
		case 217:
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "FIRECRACK.");
			int x = lpObj->X;
			int y = lpObj->Y;
			PMSG_SERVERCMD pMsg;

			PHeadSubSetB((LPBYTE)&pMsg,0xF3,0x40, sizeof(pMsg));
			pMsg.CmdType = 0;

			for ( int i=0;i<15;i++)
			{
				pMsg.X = x+(rand() % 5)*2 - 4;
				pMsg.Y = y+(rand() % 5)*2 - 4;
				MsgSendV2(lpObj,(LPBYTE)&pMsg, sizeof(pMsg));
				::DataSend(lpObj->m_Index ,(LPBYTE)&pMsg, sizeof(pMsg));
			}
		}
		break;
		case 216:
		{
			pId = this->GetTokenString();

			if ( pId == NULL )
			{
				return 0;
			}

			LPOBJ lpTargetObj = gObjFind(pId);

			if ( lpTargetObj == NULL )
			{
				return 0;
			}

			LogAddTD("Use GM Command -> [ %s ]	[ %s ]	[ %s ] / Target : [%s][%s] : %s ",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
				lpTargetObj->Name, "User Watching");

			char szTemp[256];

			if ( this->WatchTargetIndex == lpTargetObj->m_Index )
			{
				this->WatchTargetIndex = -1;
				
				wsprintf(szTemp, "%s : °ЁЅГЗШБ¦", lpTargetObj->Name);	// #translation
				GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
			}
			else
			{
				wsprintf(szTemp, "%s : °ЁЅГЅГАЫ", lpTargetObj->Name);	// #translation
				GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
				this->WatchTargetIndex = lpTargetObj->m_Index;
			}
		}
		break;
		case 215:
		{
			// ----
			if(!g_GMManager.CheckCommand(aIndex, egm_cmd_trace))
			{
				return false;
			}
			// ----
			pId = this->GetTokenString();

			if ( pId == NULL )
			{
				return 0;
			}

			int map;
			int iX;
			int iY;
			LPOBJ lpTargetObj = gObjFind(pId);
			int iIndex;

			if ( lpTargetObj == NULL )
			{
				return 0;
			}

			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
				lpTargetObj->Name, "User Tracking");
			map = lpTargetObj->MapNumber;
			iX = lpTargetObj->X;
			iY = lpTargetObj->Y;
			iIndex = lpObj->m_Index;

			if ( iIndex >= 0 )
			{
				gObjTeleport(iIndex, map, iX, iY);
			}
		}
		break;
		case 214:
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, 
				"User Stat (connection)");

			int lc151 = 0;
			int lc152 = 400;
			int iTokenNumber = this->GetTokenNumber();

			if ( iTokenNumber > 0 )
			{
				lc151 = iTokenNumber;
			}

			int iTokenNumber2 = this->GetTokenNumber();

			if ( iTokenNumber2 > 0 )
			{
				lc152 = iTokenNumber2;
			}

			gObjSendUserStatistic(lpObj->m_Index, lc151, lc152);
		}
		break;
		case 100:
		{
			// ----
			if(!g_GMManager.CheckCommand(aIndex, egm_cmd_disconnect))
			{
				return false;
			}
			// ----
			pId = this->GetTokenString();

			if ( pId == NULL )
			{
				return 0;
			}

			int iTargetIndex = gObjGetIndex(pId);

			if ( iTargetIndex >= 0 )
			{
				LPOBJ lpTargetObj = gObjFind(pId);

				if ( lpTargetObj == NULL )
				{
					return 0;
				}

				LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
					lpTargetObj->Name, "User Disconnect");
				LogAdd(lMsg.Get(MSGGET(1, 191)), pId);

#if(_RECONNECT_)
				g_ConnectEx.SendClose(lpTargetObj->m_Index,NORM_DC);
#else
				CloseClient(iTargetIndex);
#endif
			}
		}
		break;
		case 112:
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
				"Guild Disconnect");

			pId = this->GetTokenString();

			if ( pId == NULL )
			{
				return 0;
			}

			_GUILD_INFO_STRUCT * lpGuild = Guild.SearchGuild(pId);
			int iIndex;

			if ( lpGuild != NULL )
			{
				for ( int i=0;i<MAX_USER_GUILD ; i++ )
				{
					if ( lpGuild->Index[i] >= 0 )
					{
						iIndex = lpGuild->Index[i];

						if ( iIndex >= 0 )
						{
							LogAdd(lMsg.Get(MSGGET(1, 191)), pId);
							CloseClient(iIndex);
						}
					}
				}
			}
		}
		break;
		case 101:
			{
				pId = this->GetTokenString();

				if ( pId != NULL )
				{
					int lc165 = -1;
					int lc166 = 0;
					int lc167 = 0;

					if ( lpObj->Teleport != 0 )
					{
						GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
						return 0;
					}

					if ( (lpObj->m_IfState.use) != 0 )
					{
						if ( lpObj->m_IfState.type  == 3 )
						{
							lpObj->TargetShopNumber = -1;
							lpObj->m_IfState.type = 0;
							lpObj->m_IfState.use = 0;
						}
					}

					if ( lpObj->m_IfState.use > 0 )
					{
						GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
						return 0;
					}

					if ( gObj[aIndex].IsInBattleGround != false )
					{
						GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
						return 0;
					}

					BOOL bPlayerKiller = FALSE; //Season 2.5 add-on

					if(ExConfig.PvP.ExPkPartySystem && gObj[aIndex].PartyNumber >= 0) //Season 2.5 add-on
					{
						if(gParty.GetPkLevel(gObj[aIndex].PartyNumber) >= 5)
						{
							bPlayerKiller = TRUE;
						}
					}

					if(gObj[aIndex].m_PK_Level >= 5)
					{
						bPlayerKiller = TRUE;
					}

					if ( bPlayerKiller == TRUE )
					{
						GCServerMsgStringSend(lMsg.Get(MSGGET(4, 101)), lpObj->m_Index, 1);
						return 0;
					}

					gMoveCommand.Move(lpObj, pId);
				}
			}
			break;
		case 108:
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, 
				"Guild SetPosition");

			pId = this->GetTokenString();

			if ( pId == NULL )
			{
				return 0;
			}

			int iTokenNumber1 = this->GetTokenNumber();
			int iTokenNumber2 = this->GetTokenNumber();
			int iTokenNumber3 = this->GetTokenNumber();
			_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(pId);
			int iIndex;

			if ( lpGuild != NULL )
			{
				for ( int i=0;i<MAX_USER_GUILD;i++)
				{
					if (lpGuild->Index[i] >= 0 )
					{
						iIndex = lpGuild->Index[i];
						gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2++, iTokenNumber3);
					}
				}
			}
		}
		break;
		case 109:
		{
			if ( (lpObj->Authority &2)== 2 )
			{
				LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
					"Start BattleSoccer");

				BattleSoccerGoalStart(0);
			}
		}
		break;
		case 110:
		{
			if ( (lpObj->Authority &2) == 2 )
			{
				LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
					"Stop BattleSoccer");

				BattleSoccerGoalEnd(0);
			}
			else
			{
				if ( gObj[aIndex].lpGuild != NULL )
				{
					if (gObj[aIndex].lpGuild->WarType == 1 )
					{
						if( strcmp( gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0] ) == 0 )
						{					
							if( gObj[aIndex].lpGuild->BattleGroundIndex >= 0 )
							{
								//BattleSoccerGoalEnd(gObj[aIndex].lpGuild->BattleGroundIndex);
								//GCServerMsgStringSend("GuildMaster їдГ»Аё·О 3ГК ИД °ж±в°Ў АЪµїАё·О Бѕ·бµЛґПґЩ.", aIndex, 0);
							}
						}
					}
				}
			}
		}
		break;
		case 111:
		{
			if ( (lpObj->Authority & 2) == 2 )
			{
				LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "End GuildWar");

				char * szGuild = this->GetTokenString();

				if ( szGuild != NULL )
				{
					GCManagerGuildWarEnd(szGuild);
				}
			}
			else
			{
				if ( gObj[aIndex].lpGuild != NULL && gObj[aIndex].lpGuild->lpTargetGuildNode != NULL)
				{
					if ( strcmp( gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0] ) ==  0)
					{
						if ( gObj[aIndex].lpGuild->BattleGroundIndex >= 0 && gObj[aIndex].lpGuild->WarType == 1 )
						{
							::gObjAddMsgSendDelay(&gObj[aIndex], 7, aIndex, 10000, 0);

							char szTemp[100];

							wsprintf(szTemp, lMsg.Get(MSGGET(4, 129)), gObj[aIndex].lpGuild->Names[0] );
							::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild, szTemp, 1);
							::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild->lpTargetGuildNode, szTemp, 1);
						}
					}
				}
			}
		}
		break;
		case 104:
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "Ban Chatting");

			pId = this->GetTokenString();

			if ( pId == NULL )
			{
				return FALSE;
			}

			int Index = ::gObjGetIndex(pId);

			if ( Index >= 0 )
			{
				gObj[Index].Penalty |= 2;
			}

		}
		break;
		case 106:
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "Free Ban-Chatting");

			pId = this->GetTokenString();

			if ( pId == NULL )
			{
				return FALSE;
			}

			int Index = ::gObjGetIndex(pId);

			if ( Index >= 0 )
			{
				gObj[Index].Penalty &= ~2;
			}
		}
		break;
		case 107:
		{
			if(CheckAuthorityCondition(64,&gObj[aIndex]) == 0)
			{
				break; //lol
			}
			
			int ItemType;
			int ItemIndex;
			int EBP798;
			int EBP79C = 0;
			int EBP7A0 = 0;
			int EBP7A4 = 0;
			BYTE EBP7A8 = 0;
			int iDur = (BYTE)-1;//7AC
			int EBP7B0;

			ItemType  = this->GetTokenNumber();//790
			ItemIndex  = this->GetTokenNumber();//794
			EBP798 = this->GetTokenNumber();
			iDur = this->GetTokenNumber();
			EBP79C = this->GetTokenNumber();
			EBP7A0 = this->GetTokenNumber();
			EBP7B0 = this->GetTokenNumber();

			if(ItemType == 13 && ItemIndex == 3)
			{
				if(	EBP7B0 < 8)
				{
					EBP7A4 = EBP7B0;
				}
			}
			else
			{
				if(EBP7B0 == 4)
				{
					EBP7A4 = 1;
				}
				else if(EBP7B0 == 8)
				{
					EBP7A4 = 2;
				}
				else if(EBP7B0 == 12)
				{
					EBP7A4 = 3;
				}
				else if(EBP7B0 == 16)
				{
					EBP7A4 = 4;
				}
			}

			int EBP7B4 = this->GetTokenNumber();
			int EBP7B8 = this->GetTokenNumber();
			
			if(EBP7B4 != 0 )
			{
				if( EBP7B8 == 0)
				{
					if((rand()%100) < 80)
					{
						EBP7B4 |= 4; 
					}
					else
					{
						EBP7B4 |= 8; 
					}
				}
				else if (EBP7B8 == 1) 
				{
					EBP7B4 |= 4; 
				}
				else
				{
					EBP7B4 |= 8; 
				}
			}
			
			int EBP7BC = this->GetTokenNumber();

			if(EBP7BC > 0)
			{
				EBP7A8 |= 0x20;
			}

			int EBP7C0 = this->GetTokenNumber();

			if(EBP7C0 > 0)
			{
				EBP7A8 |= 0x10;
			}

			int EBP7C4 = this->GetTokenNumber();

			if(EBP7C4 > 0)
			{
				EBP7A8 |= 0x08;
			}

			int EBP7C8 = this->GetTokenNumber();

			if(EBP7C8 > 0)
			{
				EBP7A8 |= 0x04;
			}

			int EBP7CC = this->GetTokenNumber();

			if(EBP7CC > 0)
			{
				EBP7A8 |= 0x02;
			}

			int EBP7D0 = this->GetTokenNumber();

			if(EBP7D0 > 0)
			{
				EBP7A8 |= 0x01;
			}

			if( ItemType >= 0 && ItemType < 512 &&
				ItemIndex >= 0 && ItemIndex < 512)
			{
				int iItemNumber = ItemGetNumberMake(ItemType,ItemIndex);//7d4
				
				if( iItemNumber == ITEMGET(0,19) || 
					iItemNumber == ITEMGET(4,18) || 
					iItemNumber == ITEMGET(5,10) || 
					iItemNumber == ITEMGET(2,13))
				{
					EBP7A8 = 63;	
				}

				if(iItemNumber == ITEMGET(13,4) || iItemNumber ==  ITEMGET(13,5))
				{
					PetItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, iItemNumber, (BYTE)EBP798, (BYTE)iDur, (BYTE)EBP79C, (BYTE)EBP7A0, (BYTE)EBP7A4, -1, (BYTE)EBP7A8, (BYTE)EBP7B4); 
				}
				else
				{
					ItemSerialCreateSend(aIndex, (BYTE)gObj[aIndex].MapNumber, (BYTE)gObj[aIndex].X, (BYTE)gObj[aIndex].Y, iItemNumber, (BYTE)EBP798, (BYTE)iDur, (BYTE)EBP79C, (BYTE)EBP7A0, (BYTE)EBP7A4, -1, (BYTE)EBP7A8, (BYTE)EBP7B4); 
				}
			}
		}
		break;
		case 200:
		{
			pId = this->GetTokenString();

			if ( pId != NULL )
			{
				if ( strlen(pId) >= 1 )
				{
					::GCGuildWarRequestResult(pId, aIndex, 0);
				}
			}
		}
		break;
		case 202:
		{
			if ( (lpObj->Authority & 2 ) == 2 )
			{
				LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
					lpObj->Name, "Set GuildWar");
	
				pId = this->GetTokenString();

				if ( pId != NULL )
				{
					char * Rival = this->GetTokenString();

					if ( Rival != NULL )
					{
						if ( strlen(pId) >= 1 )
						{
							if ( strlen(Rival) >= 1 )
							{
								::GCManagerGuildWarSet(pId, Rival, 1);
							}
						}
					}
				}
			}
			else
			{
				if ( gEnableBattleSoccer != FALSE )
				{
					pId = this->GetTokenString();

					if ( pId != NULL )
					{
						if ( strlen(pId) >= 1 )
						{
							::GCGuildWarRequestResult(pId, aIndex, 1);
						}
					}
				}
			}
		}
		break;
		case 201:
		{
			gObjBillRequest(&gObj[aIndex]);

			if(CheckAuthorityCondition(64,&gObj[aIndex]) == 0)
			{
				break; //lol
			}
		}
		break;
		case 203:
		{
			pId = this->GetTokenString();

			if ( pId != NULL )
			{
				BOOL bState;

				if ( strcmp(pId, "on" ) == 0 )
				{
					bState = TRUE;
				}
				else if ( strcmp(pId, "off") == 0 )
				{
					bState = FALSE;
				}

				if ( bState >= FALSE && bState <= TRUE )
				{
					::gObjSetTradeOption(aIndex, bState);
					::gObjSetDuelOption(aIndex, bState);
				}
			}
		}
		break;
		case 320:
		{
			LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµР»уЕВєё±в");
			KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµР»уЕВєё±в");

			for ( int n=0;n<MAX_VIEWPORT;n++)
			{
				if ( lpObj->VpPlayer[n].state != 0 )
				{
					if ( lpObj->VpPlayer[n].type == OBJ_MONSTER )
					{
						if ( lpObj->VpPlayer[n].number >= 0 )
						{
							LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

							if ( lpTarget->Class == 275 )
							{
								TNotice pNotice(1);
								pNotice.SendToUser(lpObj->m_Index, "ДпµР HP = %7.0f / %7.0f", lpTarget->Life, lpTarget->MaxLife);
								pNotice.SendToUser(lpObj->m_Index, "ДпµР HP ГКґзИёє№·® = %d Иёє№·® = %d Иёє№ЅГ°Ј = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);
							}
						}
					}
				}
			}

		}
		break;
		case 321:
		{
			if(CheckAuthorityCondition(98,&gObj[aIndex]) == 0)
			{
				break; //lol
			}

			LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµРHPјіБ¤");
			KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµРHPјіБ¤");

			int iLife = this->GetTokenNumber();

			for ( int n=0;n<MAX_VIEWPORT;n++)
			{
				if ( lpObj->VpPlayer[n].state != FALSE )
				{
					if ( lpObj->VpPlayer[n].type == OBJ_MONSTER )
					{
						if ( lpObj->VpPlayer[n].number >= 0 )
						{
							LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

							if ( lpTarget->Class == 275 )
							{
								if  ( iLife <= 5000 )
								{
									iLife = 5000 ;
								}

								if ( iLife > lpTarget->MaxLife )
								{
									iLife = (int)lpTarget->MaxLife;
								}

								lpTarget->Life = (float)iLife;
							
								TNotice pNotice(1);
								pNotice.SendToUser(lpObj->m_Index, "ДпµР HP = %7.0f / %7.0f",lpTarget->Life, lpTarget->MaxLife);
							}
						}
					}
				}
			}
		}
		break;
		case 322:
		{
			LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµРHPИёє№·®јіБ¤");
			KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµРHPИёє№·®јіБ¤");

			int RefillHP = this->GetTokenNumber();

			if ( RefillHP <= 0 || RefillHP > 5000000 )
			{
				return 0;
			}

			giKundunRefillHP = RefillHP;

			TNotice pNotice(0);
			pNotice.SendToUser(lpObj->m_Index, "ДпµР HP ГКґзИёє№·® = %d Иёє№·® = %d Иёє№ЅГ°Ј = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);
		}
		break;
		case 323:
		{
			LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµРHPГКґзИёє№·®јіБ¤");
			KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµРHPГКґзИёє№·®јіБ¤");

			int RefillHPSec = this->GetTokenNumber();

			if ( RefillHPSec <= 0 || RefillHPSec > 10000 )
			{
				return 0;
			}

			giKundunRefillHPSec = RefillHPSec;

			TNotice pNotice(0);
			pNotice.SendToUser(lpObj->m_Index, "ДпµР HP ГКґзИёє№·® = %d Иёє№·® = %d Иёє№ЅГ°Ј = %d",
				giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);
		}
		break;
		case 324:
		{
			LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµРHPИёє№ЅГ°ЈјіБ¤");
			KUNDUN_GM_LOG.Output("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "ДпµРHPИёє№ЅГ°ЈјіБ¤");

			int RefillHPTime = this->GetTokenNumber();

			if ( RefillHPTime < 0 || RefillHPTime > 60000 )
			{
				return 0;
			}

			giKundunRefillHPTime = RefillHPTime;

			TNotice pNotice(0);
			pNotice.SendToUser(lpObj->m_Index, "ДпµР HP ГКґзИёє№·® = %d Иёє№·® = %d Иёє№ЅГ°Ј = %d", giKundunRefillHPSec, giKundunRefillHP, giKundunRefillHPTime);

		}
		break;
//#if(GS_CASTLE==1)
        case 331:
			char *szNewOwnerGuild;
			szNewOwnerGuild = this->GetTokenString();
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 0, szNewOwnerGuild);
			break;
        case 332:
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 1, 0);
			break;
        case 333:
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 2, 0);
			break;
        case 334:
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 3, 0);
			break;
        case 335:
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 4, 0);
			break;
        case 336:
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 5, 0);
			break;
        case 337:
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 6, 0);
			break;
        case 338:
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 7, 0);
			break;
		case 340:
			char *szGuildName;
			szGuildName = this->GetTokenString();
			g_CastleSiege.OperateGmCommand(lpObj->m_Index, 8, szGuildName);
			break;
		case 345:
			g_Crywolf.OperateGmCommand(lpObj->m_Index,1);
			break;
		case 346:
			g_Crywolf.OperateGmCommand(lpObj->m_Index,2);
			break;
		case 347:
			g_Crywolf.OperateGmCommand(lpObj->m_Index,3);
			break;
		case 348:
			g_Crywolf.OperateGmCommand(lpObj->m_Index,0);
			break;
//#endif
//#if(GS_CASTLE==0)
		case 369:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 0);
			break;
		case 370:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 1);
			break;
		case 371:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 2);
			break;
		case 372:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 3);
			break;
		case 373:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 4);
			break;
		case 374:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 5);
			break;
		case 375:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 6);
			break;
		case 376:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 7);
			break;
		case 377:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 8);
			break;
		case 378:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 9);
			break;
		case 379:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 10);
			break;
		case 380:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 11);
			break;
		case 381:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 12);
			break;
		case 382:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 13);
			break;
		case 383:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 14);
			break;
		case 384:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 15);
			break;
		case 385:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 16);
			break;
		case 386:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 17);
			break;
		case 387:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 18);
			break;
		case 388:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 19);
			break;
		case 389:
			g_Kanturu.OperateGmCommand(lpObj->m_Index, 20);
			break;
//#endif
		case 218:
		{
			int iClass = lpObj->Class;

			lpObj->ChangeUP = 0;

			lpObj->Strength = DCInfo.DefClass[iClass].Strength;
			lpObj->Dexterity = DCInfo.DefClass[iClass].Dexterity;
			lpObj->Vitality = DCInfo.DefClass[iClass].Vitality;
			lpObj->Energy = DCInfo.DefClass[iClass].Energy;
			lpObj->Life = DCInfo.DefClass[iClass].Life;
			lpObj->MaxLife = DCInfo.DefClass[iClass].MaxLife;
			lpObj->Mana = DCInfo.DefClass[iClass].Mana;
			lpObj->MaxMana = DCInfo.DefClass[iClass].MaxMana;
			lpObj->Leadership = DCInfo.DefClass[iClass].Leadership;

			if(lpObj->Class == CLASS_DARKLORD || lpObj->Class == CLASS_MAGUMSA)
			{
				lpObj->LevelUpPoint = 7 * (lpObj->Level -1 );
			}
			else
			{
				lpObj->LevelUpPoint = 5 * (lpObj->Level -1 );
			}

			GCServerMsgStringSend("ДіёЇЕН Б¤єё°Ў ё®јВµЗѕъЅАґПґЩ. »х·О ї¬°б ЗПјјїд", lpObj->m_Index, 1);
			gObjCloseSet(lpObj->m_Index, 1);
		}
		break;
		case 312:
		{
			int iClass = lpObj->Class;
			int iLevel = this->GetTokenNumber(); //EBP-10E8

			if(iLevel < 1)
			{
				iLevel = 1;
			}

			lpObj->Level = iLevel;
			lpObj->Experience = gLevelExperience[-1+lpObj->Level];
			lpObj->iFruitPoint = 0;

			this->ManagementProc(lpObj,"/ЅєЕИё®јВ",aIndex); //lol
		}
		break;
		case 316:
		{
			int iTokenNumber = this->GetTokenNumber();
			int iPetItem_Mode = 0;

			if(iTokenNumber == 0)
			{
				iPetItem_Mode = CDarkSpirit::PetItem_Mode_Normal;
			}
			else if(iTokenNumber == 1)
			{
				iPetItem_Mode = CDarkSpirit::PetItem_Mode_Attack_Random;
			}
			else if(iTokenNumber == 2)
			{
				iPetItem_Mode = CDarkSpirit::PetItem_Mode_Attack_WithMaster;
			}
			else if(iTokenNumber == 3)
			{
				iPetItem_Mode = CDarkSpirit::PetItem_Mode_Attack_Target;
			}

			gDarkSpirit[lpObj->m_Index].SetMode((CDarkSpirit::ePetItem_Mode)iPetItem_Mode,-1);
		}
		break;
		case 317:
		{
			int iInventoryPos = this->GetTokenNumber();
			int iPetItemLevel = this->GetTokenNumber();

			lpObj->pInventory[iInventoryPos].m_PetItem_Level = iPetItemLevel;
			lpObj->pInventory[iInventoryPos].Convert(lpObj->pInventory[iInventoryPos].m_Type, 
				lpObj->pInventory[iInventoryPos].m_Option1, 
				lpObj->pInventory[iInventoryPos].m_Option2, 
				lpObj->pInventory[iInventoryPos].m_Option3, 
				lpObj->pInventory[iInventoryPos].m_NewOption, 
				lpObj->pInventory[iInventoryPos].m_SetOption, 
				lpObj->pInventory[iInventoryPos].m_ItemOptionEx, NULL, 0xFF, 0, 3);
		}
		break;
		case 392:
		g_IllusionTempleEvent.OperateGMCommand(1, lpObj->MapNumber);
		break;
		case 393:
		g_IllusionTempleEvent.OperateGMCommand(2, lpObj->MapNumber);
		break;
		case 394:
		g_IllusionTempleEvent.OperateGMCommand(3, lpObj->MapNumber);
		break;
		case 219:
		{
			BYTE QuestBitMask[8];

			QuestBitMask[0]=0xFC;
			QuestBitMask[1]=0xFC;
			QuestBitMask[2]=0xF3;
			QuestBitMask[3]=0xF3;
			QuestBitMask[4]=0xCF;
			QuestBitMask[5]=0xCF;
			QuestBitMask[6]=0x3F;
			QuestBitMask[7]=0x3F;

			int QuestIndex = this->GetTokenNumber();

			if(QuestIndex == 0)
			{
				memset(lpObj->m_Quest, 0xFF, sizeof(lpObj->m_Quest));
				lpObj->m_SendQuestInfo = 0;
				CGRequestQuestInfo(lpObj->m_Index);
			}
			else	//Reset Current State?
			{
				int State = 3;
				int index = (QuestIndex/4);
				int shift = (QuestIndex % 4)*2;
				lpObj->m_Quest[index] &= QuestBitMask[shift];
				lpObj->m_Quest[index] |= (State&3) << shift;

				lpObj->m_SendQuestInfo = 0;
				CGRequestQuestInfo(lpObj->m_Index);
			}

			lpObj->m_i3rdQuestIndex = -1;

			for(int i = 0; i < 5; i++)
			{
				lpObj->MonsterKillInfo[i].MonIndex = -1;
				lpObj->MonsterKillInfo[i].KillCount = -1;
			}
		}
		break;
		case 220:
		{
			int iMapNumber = this->GetTokenNumber();
			int iCoordX = this->GetTokenNumber();
			int iCoordY = this->GetTokenNumber();

			if( CHECK_LIMIT(iMapNumber, MAX_NUMBER_MAP) == FALSE )
			{
				break;
			}

			if( CHECK_LIMIT(iCoordX, 256) == FALSE )
			{
				break;
			}

			if( CHECK_LIMIT(iCoordX, 256) == FALSE )
			{
				break;
			}

			BYTE attr = MapC[iMapNumber].GetAttr(iCoordX,iCoordY);

			if( ((attr&(BYTE)4) == (BYTE)4) || ((attr&(BYTE)8) == (BYTE)8))
			{
				PMSG_NOTICE pNotice;
				TNotice::MakeNoticeMsgEx(&pNotice, 0, "ЗШґз БцїЄАё·О ЗцАз БВЗҐАМµї ЗТ јц ѕшЅАґПґЩ. (јУјєДЪµе:%d)", attr);
				TNotice::SendNoticeToUser(lpObj->m_Index,&pNotice);
				break;
			}
			
			gObjTeleport(lpObj->m_Index, iMapNumber, iCoordX, iCoordY);

			if(iMapNumber == MAP_INDEX_RAKLION_BOSS)
			{
				g_RaklionBattleUserMng.AddUserData(lpObj->m_Index);
			}
		}
		break;
		case 360:
		this->GetInfinityArrowMPConsumption(lpObj);
		break;
		case 361:
		this->ControlInfinityArrowMPConsumption0(lpObj, this->GetTokenNumber());
		break;
		case 362:
		this->ControlInfinityArrowMPConsumption1(lpObj, this->GetTokenNumber());
		break;
		case 363:
		this->ControlInfinityArrowMPConsumption2(lpObj, this->GetTokenNumber());
		break;
		case 443:
		this->ControlInfinityArrowMPConsumption3(lpObj, this->GetTokenNumber());
		break;
		case 364:
		this->SetInfinityArrowTime(lpObj, this->GetTokenNumber());
		break;
		case 365:
		{
			__int64 addexp = this->GetTokenNumber();
			gObjLevelUp(lpObj, addexp, 0, 0);
		}
		break;
		case 366:
		this->ControlFireScreamDoubleAttackDistance(lpObj, this->GetTokenNumber());
		break;
		case 367:
		{
			int unk0 = this->GetTokenNumber();
			int unk1 = this->GetTokenNumber();
			int OptionType = this->GetTokenNumber();
			int OptionLevel = this->GetTokenNumber();
			int iInventoryTargetPos = unk0+(unk1*8)+3;

			g_kJewelOfHarmonySystem.StrengthenItemByMacro(lpObj, iInventoryTargetPos, OptionType, OptionLevel);
		}
		break;
		case 368:
		{
			int unk0 = this->GetTokenNumber();
			int unk1 = this->GetTokenNumber();
			int Option = this->GetTokenNumber();
			int iInventoryTargetPos = unk0+(unk1*8)+3;
			g_kItemSystemFor380.SetOptionItemByMacro(lpObj, iInventoryTargetPos, Option);
		}
		break;
		case 402:
		{
			CItem pItem;
			char szItemName[50];
			memset(szItemName, NULL, sizeof(szItemName));
			strcpy(szItemName, this->GetTokenString());

			g_ChaosCard.CheckChaosCardInfo(szItemName, &pItem);

			if(pItem.IsItem() == 0)
			{
				break;
			}

			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)lpObj->X, (BYTE)lpObj->Y, pItem.m_Type, (BYTE)pItem.m_Level, (BYTE)pItem.m_Durability, (BYTE)pItem.m_Option1, (BYTE)pItem.m_Option2, (BYTE)pItem.m_Option3, lpObj->m_Index, (BYTE)pItem.m_NewOption, 0); 
		}
		break;
		case 403:
			{
				int unk0 = this->GetTokenNumber();
				int unk1 = this->GetTokenNumber();
				int iInventoryTargetPos = unk0+(unk1*8)+3;

				gObjInventoryDeleteItem(lpObj->m_Index, iInventoryTargetPos);
				GCItemListSend(lpObj->m_Index);
			}
			break;
		case 404:
			{
				//for( int i = INVETORY_WEAR_SIZE; i < MAIN_INVENTORY_SIZE; i++)
				for( int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)	
				{
					if(lpObj->pInventory[i].IsItem() == TRUE)
					{
						gObjInventoryDeleteItem(lpObj->m_Index, i);
					}
				}
				GCItemListSend(lpObj->m_Index);
			}
			break;
		case 390:
			{
				if ( (lpObj->Authority & 32 ) != 32 )
				{
					return FALSE;
				}

				gObjApplyBuffEffectDuration(lpObj, AT_INVISIBILITY, 0, 0, 0, 0, -10);
				gObjViewportListProtocolDestroy(lpObj);
			}
			break;
		case 391:
			{
				if ( (lpObj->Authority & 32 ) != 32 )
				{
					return FALSE;
				}
				gObjRemoveBuffEffect(lpObj, AT_INVISIBILITY);
				gObjViewportListProtocolCreate(lpObj);
			}
			break;
		case 411:
			g_Raklion.OperateGmCommand(lpObj->m_Index,2);
		break;
        case 419:
			g_Raklion.OperateGmCommand(lpObj->m_Index,10);
		break;
        case 420:
			g_Raklion.OperateGmCommand(lpObj->m_Index,11);
		break;
        case 421:
			g_Raklion.OperateGmCommand(lpObj->m_Index,12);
		break;
        case 422:
			g_Raklion.OperateGmCommand(lpObj->m_Index,13);
		break;
        case 423:
			g_Raklion.OperateGmCommand(lpObj->m_Index,14);
		break;
        case 424:
			g_Raklion.OperateGmCommand(lpObj->m_Index,15);
		break;
        case 425:
			g_Raklion.OperateGmCommand(lpObj->m_Index,16);
		break;
        case 426:
			g_Raklion.OperateGmCommand(lpObj->m_Index,17);
		break;
        case 427:
			g_Raklion.OperateGmCommand(lpObj->m_Index,18);
		break;
        case 428:
			g_Raklion.OperateGmCommand(lpObj->m_Index,19);
		break;
        case 429:
			g_Raklion.OperateGmCommand(lpObj->m_Index,20);
		break;
        case 430:
			g_Raklion.OperateGmCommand(lpObj->m_Index,21);
		break;
        case 431:
			g_Raklion.OperateGmCommand(lpObj->m_Index,22);
		break;
        case 432:
			g_Raklion.OperateGmCommand(lpObj->m_Index,23);
		break;       
		case 433:
			g_Raklion.OperateGmCommand(lpObj->m_Index,24);
		break;
        case 434:
			g_Raklion.OperateGmCommand(lpObj->m_Index,25);
		break;
        case 435:
			g_Raklion.OperateGmCommand(lpObj->m_Index,26);
		break;
        case 501:
			this->CmdAbility(lpObj,this->GetTokenString());
		break;
        case 502:
			this->CmdParty(lpObj,this->GetTokenString());
		break;
        case 503:
   		{
			char * szName = this->GetTokenString();
			int ct = this->GetTokenNumber();
			this->CmdSummonMonster(lpObj,szName,ct);
		}
		break;
        case 504:
			this->CmdClearMonster(lpObj,this->GetTokenNumber());
		break;
        case 505:
			this->CmdClearItem(lpObj,this->GetTokenNumber());
		break;
        case 506:
			this->CmdClearInven(lpObj);
		break;
        case 507:
			this->CmdSummonChar(lpObj,this->GetTokenString());
		break;
			//PCBang Related
		case 446:
		{
#if(PC_BANG_POINT_SYSTEM==1)
			int iAddPoint = this->GetTokenNumber();
			lpObj->m_PcBangPointSystem.m_dwPcBangPointTick = GetTickCount();
			lpObj->m_PcBangPointSystem.m_iPcBangAccumulatedPoint += iAddPoint;

			char szTemp[256];
			wsprintf(szTemp, lMsg.Get(3392), iAddPoint);
			GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);

			g_PCBangPointSystem.EGReqUpdatePcBangResetPointInfo(lpObj->m_Index);

			LogAddTD("[PCBangPointSystem][Add Point] [%s] %d/Total:%d Rule(%d)", 
					lpObj->AccountID, lpObj->m_PcBangPointSystem.m_sPcBangGainPoint, 
					lpObj->m_PcBangPointSystem.m_iPcBangAccumulatedPoint, lpObj->m_PcBangPointSystem.m_bPcBangCommonRule);
#endif
		}
		break;
		case 447:
		{
#if(PC_BANG_POINT_SYSTEM==1)
			int iAddPoint = 0;
			lpObj->m_PcBangPointSystem.m_dwPcBangPointTick = GetTickCount();
			lpObj->m_PcBangPointSystem.m_iPcBangAccumulatedPoint = iAddPoint;

			char szTemp[256];
			wsprintf(szTemp, lMsg.Get(3392), iAddPoint);
			GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);

			g_PCBangPointSystem.EGReqUpdatePcBangResetPointInfo(lpObj->m_Index);

			LogAddTD("[PCBangPointSystem][Add Point] [%s] %d/Total:%d Rule(%d)", 
					lpObj->AccountID, lpObj->m_PcBangPointSystem.m_sPcBangGainPoint, 
					lpObj->m_PcBangPointSystem.m_iPcBangAccumulatedPoint, lpObj->m_PcBangPointSystem.m_bPcBangCommonRule);
#endif
		}
		break;
		case 600:
		{
			//if(CheckAuthorityCondition(34,lpObj) == 1)//Season 4.5 addon
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_gmove))
				{
					return false;
				}
				// ----
				pId = this->GetTokenString();

				if ( pId == NULL )
				{
					return 0;
				}

				int iTokenNumber1 = this->GetTokenNumber();
				int iTokenNumber2 = this->GetTokenNumber();
				int iTokenNumber3 = this->GetTokenNumber();
				int iIndex = gObjGetIndex(pId);
				LPOBJ lpTargetObj;

				if ( iIndex >= 0 )
				{
					lpTargetObj = gObjFind(pId);

					if ( lpTargetObj == NULL )
					{
						return 0;
					}

					LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
						lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
						lpTargetObj->Name, "User SetPosition");

					gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2, iTokenNumber3);
				}
			}
		}
		break;
        case 601:
   		{
			//Empty Command
		}
		break;
#if(_NEW_PT_SYSTEM_==1)
	case 602:
		{
			if(!ExConfig.CommonServer.CommandSetLeader)return false;
			char * TargetName	= this->GetTokenString();
			if(TargetName == NULL) return false;
			int TargetIndex		= gObjGetIndex(TargetName);
			// ----
			if( !gParty.SetLeader(lpObj->m_Index, TargetIndex) )
			{
				return false;
			}
		}
		break;
#endif
#if(_BAN_SYSTEM_)
	case 604:	//BanChat
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->BanChat = time(NULL) + ( iTokenNumber1 * 3600 );
				MsgNormal(aIndex,"[BanChat]: %s %d Hour",lpTargetObj->Name,iTokenNumber1);
				MsgNormal(TargetIndex,"[BanChat]: %d Hour",iTokenNumber1);
			}
		}
		break;
		// ---
	case 605:	//BanPost
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->BanPost = time(NULL) + ( iTokenNumber1 * 3600 );
				MsgNormal(aIndex,"[BanPost]: %s %d Hour",lpTargetObj->Name,iTokenNumber1);
				MsgNormal(TargetIndex,"[BanPost]: %d Hour",iTokenNumber1);
			}
		}
		break;
		// ---
	case 606:	//BanChar
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_banchar))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->BanChar = time(NULL) + ( iTokenNumber1 * 3600 );
				MsgNormal(aIndex,"[BanChar]: %s %d Hour",lpTargetObj->Name,iTokenNumber1);
				MsgNormal(TargetIndex,"[BanChar]: %d Hour",iTokenNumber1);
#ifdef _RECONNECT_
				g_ConnectEx.SendClose(TargetIndex,0);
#else
				CloseClient(TargetIndex);
#endif
			}
		}
		break;
	case 607:	//Ban All Chat
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->BanChat = time(NULL) + ( iTokenNumber1 * 3600 );
				lpTargetObj->BanPost = time(NULL) + ( iTokenNumber1 * 3600 );
				MsgNormal(aIndex,"[BanAllChat]: %s %d Hour",lpTargetObj->Name,iTokenNumber1);
				MsgNormal(TargetIndex,"[BanAllChat]: %d Hour",iTokenNumber1);
			}
		}
		break;
		// ---

	case 608:	//UnBanChat
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->BanChat = 0;
				MsgNormal(aIndex,"[UnBanChat]: %s",lpTargetObj->Name);
				MsgNormal(TargetIndex,"[UnBanChat]");
			}
		}
		break;
		// ---
	case 609:	//UnBanPost
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->BanPost = 0;
				MsgNormal(aIndex,"[UnBanPost]: %s",lpTargetObj->Name);
				MsgNormal(TargetIndex,"[UnBanPost]");
			}
		}
		break;
		// ---
	case 610:	//UnBan All Chat
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_banchat))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->BanChat = 0;
				lpTargetObj->BanPost = 0;
				MsgNormal(aIndex,"[UnBanAllChat]: %s",lpTargetObj->Name);
				MsgNormal(TargetIndex,"[UnBanAllChat]");
			}
		}
		break;
		// ---
	case 611: //UnBan Char
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_banchar))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				if ( TargetName == NULL ) return 0;
				BAN_CHAR_GS pMsg;
				pMsg.h.set((LPBYTE)&pMsg, 0xE2, 0x00, sizeof(BAN_CHAR_GS));
				pMsg.Result = 1;
				pMsg.Type = 3;
				pMsg.aIndex = aIndex;
				memcpy(pMsg.Name,TargetName,11);
				cDBSMng.Send((char*)&pMsg, pMsg.h.size);
			}
		}
		break;
#endif
	case 612:
		{
			OffExp.OffExpStart(aIndex,0);
		}
		break;
	//Jewels Bank
	case 613:
		{
#if(CUSTOM_ACCOUNT_SECURITY)
			if(g_AccountSecurity.CheckInventory(lpObj->m_Index) == false)
			{
				return 0;
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				return 0;
			}
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.sendchaosbank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 614:
		{
#if(CUSTOM_ACCOUNT_SECURITY)
			if(g_AccountSecurity.CheckInventory(lpObj->m_Index) == false)
			{
				return 0;
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				return 0;
			}
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.sendblessbank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 615:
		{
#if(CUSTOM_ACCOUNT_SECURITY)
			if(g_AccountSecurity.CheckInventory(lpObj->m_Index) == false)
			{
				return 0;
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				return 0;
			}
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.sendsoulbank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 616:
		{
#if(CUSTOM_ACCOUNT_SECURITY)
			if(g_AccountSecurity.CheckInventory(lpObj->m_Index) == false)
			{
				return 0;
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				return 0;
			}
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.sendlifebank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 617:
		{
#if(CUSTOM_ACCOUNT_SECURITY)
			if(g_AccountSecurity.CheckInventory(lpObj->m_Index) == false)
			{
				return 0;
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				return 0;
			}
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.recvchaosbank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 618:
		{
#if(CUSTOM_ACCOUNT_SECURITY)
			if(g_AccountSecurity.CheckInventory(lpObj->m_Index) == false)
			{
				return 0;
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				return 0;
			}
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.recvblessbank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 619:
		{
#if(CUSTOM_ACCOUNT_SECURITY)
			if(g_AccountSecurity.CheckInventory(lpObj->m_Index) == false)
			{
				return 0;
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				return 0;
			}
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.recvsoulbank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 620:
		{
#if(CUSTOM_ACCOUNT_SECURITY)
			if(g_AccountSecurity.CheckInventory(lpObj->m_Index) == false)
			{
				return 0;
			}
#endif
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				return 0;
			}
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.recvlifebank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 621:
		{
			char * NextCommand	= this->GetTokenString();
			int iTokenNumber1   = this->GetTokenNumber();
			if ( NextCommand <= NULL) return 0;

			gCreditDonate.Chat(aIndex,NextCommand,iTokenNumber1);

		}
		break;
	case 622:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_sellcredit))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				if( iTokenNumber1 == NULL) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->ExCred += iTokenNumber1;
				MsgNormal(aIndex,"[Credits]: %s %d ",lpTargetObj->Name,iTokenNumber1);
				MsgNormal(TargetIndex,"[Credits]: +%d ",iTokenNumber1);
				ExUserDataSend(TargetIndex);
				return 1;
			}
		}
		break;
	case 623:
		{
			if(!ExConfig.ExCustom.AutoParty)
			{
				return 1;
			}

			int iTokenNumber1   = this->GetTokenNumber();
			if(iTokenNumber1 == 0)
			{
				lpObj->AutoPt = 0;
			}
			else if(iTokenNumber1 > 0 && iTokenNumber1 <= 400)
			{
				lpObj->AutoPt = iTokenNumber1;
				MessaageAllGlobal("[.::AutoParty::.][%s] %s %d %d",lpObj->Name,exMapName(lpObj->MapNumber),lpObj->X,lpObj->Y);
			}
		}
		break;
	case 624://Send Zen
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 >= 1000) return 0;

			unsigned int M = iTokenNumber1 * 1000000;

			if(M > lpObj->Money) return 0;

			lpObj->Money -= M;
			lpObj->Zen += iTokenNumber1;
			GCMoneySend(aIndex,lpObj->Money);
			ExUserDataSend(aIndex);
		}
		break;
	case 625://Recv Zen
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 >= 1000) return 0;
			int M = iTokenNumber1 * 1000000;
			unsigned long long totalzen = M + lpObj->Money;
			if(totalzen > MAX_ZEN) return 0;
			if(iTokenNumber1 > lpObj->Zen) return 0;

			lpObj->Money += M;
			lpObj->Zen -= iTokenNumber1;
			GCMoneySend(aIndex,lpObj->Money);
			ExUserDataSend(aIndex);
		}
		break;
	case 626:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			char * NextCommand	= this->GetTokenString();
			if(NextCommand == NULL) return 0;
			gCreditDonate.exClass(aIndex,NextCommand);
		}
		break;
	case 627:
		{
			lpObj->AutoPt = 0;
			MsgNormal(aIndex,"[AutoParty]: Recv Off ");
		}
		break;
	case 628:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				// ----
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_sellcredit))
				{
					return false;
				}
				// ----
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				if(iTokenNumber1 < 0) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				lpTargetObj->ExCred += iTokenNumber1;
				MsgNormal(aIndex,"[Credit]: %s %d",lpTargetObj->Name,iTokenNumber1);
				MsgNormal(TargetIndex,"[Credit]: %d",iTokenNumber1);
				ExUserDataSend(TargetIndex);
			}
		}
		break;
	case 629:
		{
				int WCoin = 0;
				if (lpObj->GameShop.GoblinPoint == 0)
				{
					return false;
				}
				else if (lpObj->GameShop.GoblinPoint > 0 && lpObj->GameShop.GoblinPoint < 50)
				{
					WCoin = 1;
				}
				else
				{
					WCoin = lpObj->GameShop.GoblinPoint / 50;
				}
				lpObj->GameShop.GoblinPoint = 0;
				lpObj->GameShop.WCoinC += WCoin;
				gGameShop.GDSaveUserInfo(aIndex);
				MsgNormal(aIndex, "[WCoin]: +%d", WCoin);
				return true;

		}
		break;
#ifdef PRIVATE_MODULE
#if _CONFLICT_
	case 630:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140) return 0;
			gJewelsBank.exchaos(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 631:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.exbless(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 632:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.exsoul(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 633:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.exlife(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
		case 637:
		{		
			if(g_ExLicense.CheckUser(eExUB::PrideMuLocal) || 
				g_ExLicense.CheckUser(eExUB::PrideMu) || 
				g_ExLicense.CheckUser(eExUB::drynea) || 
				g_ExLicense.CheckUser(eExUB::Local3) || 
				g_ExLicense.CheckUser(eExUB::feqan)	||
				g_ExLicense.CheckUser(eExUB::MU2Play) || 
				g_ExLicense.CheckUser(eExUB::bassreflexive) ||
				g_ExLicense.CheckUser(eExUB::Escalate) || 
				g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
				g_ExLicense.CheckUser(eExUB::eternalmu))
			{
					//NeedCredit// Price			1 - Zen; 2 - ExCred; 3 - WCoinC; 4 - WCoinP; 5 - Goblin
			int iTokenNumber1;
			if(g_ExLicense.CheckUser(eExUB::feqan) || 
				g_ExLicense.CheckUser(eExUB::MU2Play) || 
				g_ExLicense.CheckUser(eExUB::bassreflexive) || 
				g_ExLicense.CheckUser(eExUB::Escalate) || 
				g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
				g_ExLicense.CheckUser(eExUB::eternalmu))
			{
				iTokenNumber1   = this->GetTokenNumber();
				if ( iTokenNumber1 <= NULL || iTokenNumber1 > 31 ) return 0;
			}
			if(Premium.Price == 1)
			{		
					if(g_ExLicense.CheckUser(eExUB::feqan) || 
						g_ExLicense.CheckUser(eExUB::MU2Play) || 
						g_ExLicense.CheckUser(eExUB::bassreflexive) || 
						g_ExLicense.CheckUser(eExUB::Escalate) || 
						g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
						g_ExLicense.CheckUser(eExUB::eternalmu))
					{
						if((Premium.Value * iTokenNumber1) > lpObj->Zen )
						{
							MsgNormal(lpObj->m_Index,"[Need Zen]: %d",Premium.Value);
							return 0;
						}
						lpObj->Zen -= iTokenNumber1 * Premium.Value;
						lpObj->PremiumTime += ( iTokenNumber1 * 86400 );
					}
					else
					{
						if(Premium.Value > lpObj->Zen )
						{
							MsgNormal(lpObj->m_Index,"[Need Zen]: %d",Premium.Value);
							return 0;
						}
						lpObj->Zen -= Premium.Value;
						lpObj->PremiumTime += ( 31 * 86400 );
					}

					if(g_ExLicense.CheckUser(eExUB::drynea))
					{
					}
					else
					{
						if(g_ExLicense.CheckUser(eExUB::feqan) || 
							g_ExLicense.CheckUser(eExUB::MU2Play) || 
							g_ExLicense.CheckUser(eExUB::bassreflexive) || 
							g_ExLicense.CheckUser(eExUB::Escalate) || 
							g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
							g_ExLicense.CheckUser(eExUB::eternalmu))
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",iTokenNumber1);
						}
						else
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",31);
						}
					}
					GCMoneySend(aIndex,lpObj->Money);
					ExUserDataSend(aIndex);
					return TRUE;
			}
			else if (Premium.Price == 2)
			{
					if(g_ExLicense.CheckUser(eExUB::feqan) || 
						g_ExLicense.CheckUser(eExUB::MU2Play) || 
						g_ExLicense.CheckUser(eExUB::bassreflexive) || 
						g_ExLicense.CheckUser(eExUB::Escalate) || 
						g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
						g_ExLicense.CheckUser(eExUB::eternalmu))
					{
						if((Premium.Value * iTokenNumber1) > lpObj->ExCred )
						{
							MsgNormal(lpObj->m_Index,"[Need Credit]: %d",Premium.Value);
							return 0;
						}
						lpObj->ExCred -= iTokenNumber1 * Premium.Value;
						lpObj->PremiumTime += ( iTokenNumber1 * 86400 );
					}
					else
					{
						if(Premium.Value > lpObj->ExCred )
						{
							MsgNormal(lpObj->m_Index,"[Need Credit]: %d",Premium.Value);
							return 0;
						}
					
						lpObj->ExCred -= Premium.Value;
						lpObj->PremiumTime += ( 31 * 86400 );
					}
					
					if(g_ExLicense.CheckUser(eExUB::drynea))
					{
					}
					else
					{
						if(g_ExLicense.CheckUser(eExUB::feqan) || 
							g_ExLicense.CheckUser(eExUB::MU2Play) || 
							g_ExLicense.CheckUser(eExUB::bassreflexive) || 
							g_ExLicense.CheckUser(eExUB::Escalate) || 
							g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
							g_ExLicense.CheckUser(eExUB::eternalmu))
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",iTokenNumber1);
						}
						else
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",31);
						}
					}
					ExUserDataSend(aIndex);
					return TRUE;
			}
			else if (Premium.Price == 3)
			{
					if(g_ExLicense.CheckUser(eExUB::feqan) || 
						g_ExLicense.CheckUser(eExUB::MU2Play) || 
						g_ExLicense.CheckUser(eExUB::bassreflexive) || 
						g_ExLicense.CheckUser(eExUB::Escalate) || 
						g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
						g_ExLicense.CheckUser(eExUB::eternalmu))
					{
						if((Premium.Value * iTokenNumber1) > lpObj->GameShop.WCoinC )
						{
							MsgNormal(lpObj->m_Index,"[Need WCoinC]: %d",Premium.Value);
							return 0;
						}
						lpObj->GameShop.WCoinC -= iTokenNumber1 * Premium.Value;
						lpObj->PremiumTime += ( iTokenNumber1 * 86400 );
					}
					else
					{
						if(Premium.Value > lpObj->GameShop.WCoinC )
						{
							MsgNormal(lpObj->m_Index,"[Need WCoinC]: %d",Premium.Value);
							return 0;
						}
					
						lpObj->GameShop.WCoinC -= Premium.Value;
						lpObj->PremiumTime += ( 31 * 86400 );
					}

					if(g_ExLicense.CheckUser(eExUB::drynea))
					{
					}
					else
					{
						if(g_ExLicense.CheckUser(eExUB::feqan) || 
							g_ExLicense.CheckUser(eExUB::MU2Play) || 
							g_ExLicense.CheckUser(eExUB::bassreflexive) || 
							g_ExLicense.CheckUser(eExUB::Escalate) || 
							g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
							g_ExLicense.CheckUser(eExUB::eternalmu))
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",iTokenNumber1);
						}
						else
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",31);
						}
					}
#ifndef FIX_DS_CRASH
					gGameShop.GDSaveUserInfo(aIndex);
					GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
					ExUserDataSend(aIndex);
					return TRUE;
			}
			else if (Premium.Price == 4)
			{
				
					if(g_ExLicense.CheckUser(eExUB::feqan) || 
						g_ExLicense.CheckUser(eExUB::MU2Play) || 
						g_ExLicense.CheckUser(eExUB::bassreflexive) || 
						g_ExLicense.CheckUser(eExUB::Escalate) || 
						g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
						g_ExLicense.CheckUser(eExUB::eternalmu))
					{
						if((Premium.Value * iTokenNumber1) > lpObj->GameShop.WCoinP )
						{
							MsgNormal(lpObj->m_Index,"[Need WCoinP]: %d",Premium.Value);
							return 0;
						}
						lpObj->GameShop.WCoinP -= iTokenNumber1 * Premium.Value;
						lpObj->PremiumTime += ( iTokenNumber1  * 86400 );
					}
					else
					{
						if(Premium.Value > lpObj->GameShop.WCoinP )
						{
							MsgNormal(lpObj->m_Index,"[Need WCoinP]: %d",Premium.Value);
							return 0;
						}
					
					
						lpObj->GameShop.WCoinP -= Premium.Value;
						lpObj->PremiumTime += ( 31 * 86400 );
					}
					
					if(g_ExLicense.CheckUser(eExUB::drynea))
					{
					}
					else
					{
						if(g_ExLicense.CheckUser(eExUB::feqan) || 
							g_ExLicense.CheckUser(eExUB::MU2Play) || 
							g_ExLicense.CheckUser(eExUB::bassreflexive) || 
							g_ExLicense.CheckUser(eExUB::Escalate) || 
							g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
							g_ExLicense.CheckUser(eExUB::eternalmu))
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",iTokenNumber1);
						}
						else
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",31);
						}
					}
#ifndef FIX_DS_CRASH
					gGameShop.GDSaveUserInfo(aIndex);
					GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
					ExUserDataSend(aIndex);
					return TRUE;
			}
			else if (Premium.Price == 5)
			{
				
					
				if(g_ExLicense.CheckUser(eExUB::feqan) || 
					g_ExLicense.CheckUser(eExUB::MU2Play) || 
					g_ExLicense.CheckUser(eExUB::bassreflexive) || 
					g_ExLicense.CheckUser(eExUB::Escalate) || 
					g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
					g_ExLicense.CheckUser(eExUB::eternalmu))
				{
					if((Premium.Value * iTokenNumber1) > lpObj->GameShop.GoblinPoint )
					{
						MsgNormal(lpObj->m_Index,"[Need GoblinPoint]: %d",Premium.Value);
						return 0;
					}
					lpObj->GameShop.GoblinPoint -= iTokenNumber1 * Premium.Value;
					lpObj->PremiumTime += ( iTokenNumber1 * 86400 );
				}
				else
				{
					if(Premium.Value > lpObj->GameShop.GoblinPoint )
					{
						MsgNormal(lpObj->m_Index,"[Need GoblinPoint]: %d",Premium.Value);
						return 0;
					}
					
					lpObj->GameShop.GoblinPoint -= Premium.Value;
					lpObj->PremiumTime += ( 31 * 86400 );
				}

					
					if(g_ExLicense.CheckUser(eExUB::drynea))
					{
					}
					else
					{
						if(g_ExLicense.CheckUser(eExUB::feqan) || 
							g_ExLicense.CheckUser(eExUB::MU2Play) || 
							g_ExLicense.CheckUser(eExUB::bassreflexive) || 
							g_ExLicense.CheckUser(eExUB::Escalate) || 
							g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
							g_ExLicense.CheckUser(eExUB::eternalmu))
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",iTokenNumber1);
						}
						else
						{
							MessageChat(aIndex,"@[Premium Status] + %d Day",31);
						}
					}
#ifndef FIX_DS_CRASH
					gGameShop.GDSaveUserInfo(aIndex);
					GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
					ExUserDataSend(aIndex);
					return TRUE;
			}
			}
					
		}break;
#ifdef SEND_CREDIT_SILVER

		case 638:
		{		
			if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2))
			{
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				if(iTokenNumber1 < 0) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				if(aIndex == TargetIndex) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				if (lpObj->ExCred < iTokenNumber1)
				{
					MsgNormal(aIndex,"[Credit]: Error you don`t have %d credits",iTokenNumber1 - lpObj->ExCred);
					return 0;
				}
				lpObj->ExCred -= iTokenNumber1;
				lpTargetObj->ExCred += iTokenNumber1;
				MsgNormal(aIndex,"[Credit]: Succesed added %d Credits to %s", iTokenNumber1, lpTargetObj->Name);
				MsgNormal(TargetIndex,"[Credit]: You have sent %d credits from %s", iTokenNumber1, lpObj->Name);
				
				ExUserDataSend(aIndex);
				ExUserDataSend(TargetIndex);

			}
		}break;
	

#endif
#ifdef DISCONECT_FRIEND
		case 639:
		{		
			if( g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(ulasevich) || g_ExLicense.CheckUser(ulasevich2) || 
				g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2)
				 || g_ExLicense.CheckUser(eExUB::MU2Play) || g_ExLicense.CheckUser(eExUB::Escalate) || 
				 g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2) || g_ExLicense.CheckUser(eExUB::RevoMU) || g_ExLicense.CheckUser(eExUB::GloryMU) ||
				 g_ExLicense.CheckUser(eExUB::mu4you) || g_ExLicense.CheckUser(eExUB::eternalmu) || g_ExLicense.CheckUser(eExUB::NSGames))
			{
				char * TargetLogin	= this->GetTokenString();
				char * TargetPass	= this->GetTokenString();
				if ( TargetLogin == NULL ) return 0;
				if ( TargetPass == NULL ) return 0;
				
				int n;

				for (n=OBJ_STARTUSERINDEX;n<OBJMAX; n++)
				{
					if ( gObj[n].Connected >= PLAYER_PLAYING)
					{
						if ( gObj[n].AccountID[0] == TargetLogin[0] )
						{
							if ( strcmp(&gObj[n].AccountID[0], TargetLogin) == 0)
							{
								if ( strcmp(gObj[n].Pass, TargetPass) == 0)
								{
									#if(CUSTOM_ACCOUNT_SECURITY)
									if(g_AccountSecurity.CheckDisconnectFriend(n, aIndex) == true)
									{
										g_ConnectEx.SendClose(n, NORM_DC);
									}
									#else
									g_ConnectEx.SendClose(n, NORM_DC);
									#endif
									
									break;
								} 
							}
						}
					}
				}
			}
		}
		break;
#endif // DISCONECT_FRIEND

#endif
#endif

#if(SYSTEMOF_BROTHER==TRUE)
	//this->cCommand.Add("/brteleport", 640, 1);
	//this->cCommand.Add("/brstart", 641, 1);
	//this->cCommand.Add("/brexit", 642, 1);

	case 640:
		{
			char * TargetName	= this->GetTokenString();
			int iTokenNumber1   = this->GetTokenNumber();
			if ( TargetName == NULL ) return 0;
			if(iTokenNumber1 < 0) return 0;
			int TargetIndex		= gObjGetIndex(TargetName);
			if(TargetIndex == -1) return 0;
			if(aIndex == TargetIndex) return 0;
			//LPOBJ lpTargetObj   = &gObj[TargetIndex];
			gBrotherhood.Teleport(lpObj,TargetIndex);
		}
		break;
	case 641:
		{
			char * TargetName	= this->GetTokenString();
			if ( TargetName == NULL ) return 0;
			gBrotherhood.UserAddedBrother(aIndex, TargetName);
		}
		break;
	case 642:
		{
			gBrotherhood.UserExitBrother(aIndex);
		}
		break;
#endif
/*
	this->cCommand.Add("/sendwcoinc", 643, 1);
	this->cCommand.Add("/sendwcoinp", 644, 1);
	this->cCommand.Add("/sendgoblin", 645, 1);
*/
	case 643:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{

				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_sendwcoin))
				{
					return false;
				}

				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				if(iTokenNumber1 < 0) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				if ( iTokenNumber1 <= NULL || iTokenNumber1 > 65535 ) return 0;
				LPOBJ lpTarget = &gObj[TargetIndex];
				lpTarget->GameShop.WCoinC += iTokenNumber1;
				gGameShop.GDSaveUserInfo(TargetIndex);
				MsgNormal(aIndex, "[SEND]: Name: %s WcoinC: %d", TargetName, iTokenNumber1);
				MsgNormal(TargetIndex, "[RECV]: WcoinC: +%d", iTokenNumber1);
			}
		}
		break;
	case 644:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_sendwcoin))
				{
					return false;
				}

				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				if(iTokenNumber1 < 0) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				if ( iTokenNumber1 <= NULL || iTokenNumber1 > 65535 ) return 0;
				LPOBJ lpTarget = &gObj[TargetIndex];
				lpTarget->GameShop.WCoinP += iTokenNumber1;
				gGameShop.GDSaveUserInfo(TargetIndex);
				MsgNormal(aIndex, "[SEND]: Name: %s WcoinP: %d", TargetName, iTokenNumber1);
				MsgNormal(TargetIndex, "[RECV]: WcoinP: +%d", iTokenNumber1);
			}
		}
		break;
	case 645:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_sendwcoin))
				{
					return false;
				}

				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				if(iTokenNumber1 < 0) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				if ( iTokenNumber1 <= NULL || iTokenNumber1 > 65535 ) return 0;
				LPOBJ lpTarget = &gObj[TargetIndex];
				lpTarget->GameShop.GoblinPoint += iTokenNumber1;
				gGameShop.GDSaveUserInfo(TargetIndex);
				MsgNormal(aIndex, "[SEND]: Name: %s Goblin: %d", TargetName, iTokenNumber1);
				MsgNormal(TargetIndex, "[RECV]: Goblin: +%d", iTokenNumber1);
			}
		}
		break;
	case 646:
		{
			//	/brothers nick
				char * TargetName	= this->GetTokenString();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				gBrotherhood.NewAddBrother(aIndex,TargetIndex);
		}
		break;
	case 647:
		{
			BMQuest.CharacterInformation(aIndex);
		}
		break;
#if(CMD_DC_ALL)
	case 648:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				for (int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
				{
					if (gObj[n].Connected >= PLAYER_PLAYING)
					{
						if(gObj[n].OffExp)
						{
							GJPUserClose(gObj[n].AccountID);
							gObjDel(n);
							gObj[n].OffExp = 0;
						}		
						else if(gObj[n].m_OfflineMode)
						{
							GJPUserClose(gObj[n].AccountID);
							gObjDel(n);
							gObj[n].m_OfflineMode = 0;
						}
						else 
						{
							g_ConnectEx.SendClose(n, NORM_DC);
						}

					}
				}
			}
		}
		break;
#endif
#if(CUSTOM_MARRIAGE)
	case 649:
		{
			if(lpObj->bMarriage)
			{
				g_Marriage.GDDelete(aIndex);
			}
		}
		break;
#endif
	case 650:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.sendcreateonbank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 651:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.recvcreateonbank(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 652:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.excreateon(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 653:
		{
			lpObj->bAutoPt = false;
			return true;
		}
		break;
	case 654:
		{
			lpObj->bAutoPt = true;
			return true;
		}
		break;
	case 655:
		{
#if(DONATE_SHOP==TRUE)
			if(g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
				g_ExLicense.CheckUser(eExUB::absolute) || 
				g_ExLicense.CheckUser(eExUB::MU2Play) ||
				g_ExLicense.CheckUser(eExUB::Local) ||
				g_ExLicense.CheckUser(eExUB::Stone) ||
				g_ExLicense.CheckUser(eExUB::Sentinel) ||
				g_ExLicense.CheckUser(eExUB::Artem) ||
				g_ExLicense.CheckUser(eExUB::Artem2) ||
				THINNAKORN_MAC == 1 ||
				g_ExLicense.CheckUser(eExUB::EpicMU) ||
				g_ExLicense.CheckUser(eExUB::Escalate)||
				g_ExLicense.CheckUser(eExUB::RevoMU) ||
				g_ExLicense.CheckUser(eExUB::TGBA_LLC) ||
				g_ExLicense.CheckUser(eExUB::GloryMU) ||
				g_ExLicense.CheckUser(eExUB::ArcMu) ||
				g_ExLicense.CheckUser(eExUB::mu4you) ||
				g_ExLicense.CheckUser(eExUB::eternalmu) ||
				g_ExLicense.CheckUser(eExUB::NSGames))
			{
				if(g_ExUser.InSafeZone(aIndex) == true)
				{
					CG_NEW_CASH_SHOP pMsg;
					pMsg.Number = DONAT_SHOP_START;
					NewShopRecv(&pMsg, aIndex);
					return true;
				}
			}
#endif
		}
		break;
#if(EVENT_DUNGEON_SIEGE)
	case 656:
		{
#if(!DUNGEON_SIEGE_DEBUG)
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
#endif
			{
				if(g_DungeonSiege.CheckStatus(eEVENTDUNGEON_CLOSE))
				{
					//g_DungeonSiege.SetStatus(eEVENTDUNGEON_WAIT);
					g_DungeonSiege.ProcessStatusStart();
				}
			}
		}
		break;
#endif
	case 657:
		{

			MsgOutput(lpObj->m_Index, "[DEBUG] Test China Command");
			//MsgNormal(aIndex, "[DEBUG]");
			//	/*if(g_ExLicense.user.NpcBuffer)
			//	{
			//		g_ExGDManager.GD_ExBuffLoad(aIndex);
			//	}*/

			////g_BufferSystem.UserConnect(aIndex);

			//#if(EVENT_TEAM_VS_TEAM==TRUE)

			//#endif
		}
		break;
#if(CMD_ANTI_CHEAT_HDD)
	case 658:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				char * TargetName	= this->GetTokenString();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				MsgOutput(lpObj->m_Index, "Name: %s HDD: %d", TargetName, gObj[TargetIndex].hdd_id);
			}
		}
		break;
#endif
#if(COMMAND_DROP)
	case 659:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				if(!g_GMManager.CheckCommand(aIndex, egm_cmd_item))
				{
					return false;
				}

				int type = GetTokenNumber();
				int index = GetTokenNumber();
				int ItemLevel = GetTokenNumber();
				int ItemSkill = GetTokenNumber();
				int ItemLuck = GetTokenNumber();
				int ItemOpt = GetTokenNumber();
				int ItemExc = GetTokenNumber();
				int ItemAncient = GetTokenNumber();
				int dur = 0;
				dur = GetTokenNumber();

				if((type >= 0 && type <= 15))
				{
					int Item = ItemGetNumberMake( type, index);

					if(Item == -1)
					{
						GCServerMsgStringSend("[Make] no item", lpObj->m_Index, 1);
						return FALSE;	
					}

					if(Item == ITEMGET(13,4) || Item ==  ITEMGET(13,5))
					{
						PetItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item,ItemLevel,dur,ItemSkill,ItemLuck,ItemOpt,aIndex,ItemExc,ItemAncient); 
					}
					else
					{
						ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item,ItemLevel,dur,ItemSkill,ItemLuck,ItemOpt,aIndex,ItemExc,ItemAncient);
					}
				}
			}
		}
		break;
#endif
	case 660:
		{
			if(g_ExLicense.user.PremiumEx == true && g_GMManager.CheckCommand(aIndex, egm_cmd_sellpremium))
			{
				char* TargetName = this->GetTokenString();
				int iPremiumDay = GetTokenNumber();

				if(TargetName != NULL && iPremiumDay > 0)
				{
					int iTargetIndex = gObjGetIndex(TargetName);

					if(iTargetIndex != -1)
					{
						LPOBJ lpTarget = &gObj[iTargetIndex];

						lpTarget->PremiumTimeType = 1;
						lpTarget->PremiumTime += ( iPremiumDay * 86400 );

						g_PremiumSystemEx.InfoMessage(iTargetIndex);
						ExUserDataSend(iTargetIndex);
						g_PremiumSystemEx.UserBuff(iTargetIndex);

						MsgOutput(aIndex, "[%s] vip level: %d", lpObj->Name, lpTarget->PremiumTimeType);
					}

					return true;
				}
			}
		}
		break;

	case 661:
		{
			if(g_ExLicense.user.PremiumEx == true && g_GMManager.CheckCommand(aIndex, egm_cmd_sellpremium))
			{
				char* TargetName = this->GetTokenString();
				int iPremiumDay = GetTokenNumber();

				if(TargetName != NULL && iPremiumDay > 0)
				{
					int iTargetIndex = gObjGetIndex(TargetName);

					if(iTargetIndex != -1)
					{
						LPOBJ lpTarget = &gObj[iTargetIndex];

						lpTarget->PremiumTimeType = 2;
						lpTarget->PremiumTime += ( iPremiumDay * 86400 );

						g_PremiumSystemEx.InfoMessage(iTargetIndex);
						ExUserDataSend(iTargetIndex);
						g_PremiumSystemEx.UserBuff(iTargetIndex);

						MsgOutput(aIndex, "[%s] vip level: %d", lpObj->Name, lpTarget->PremiumTimeType);
					}

					return true;
				}
			}
		}
		break;

	case 662:
		{
			if(g_ExLicense.user.PremiumEx == true && g_GMManager.CheckCommand(aIndex, egm_cmd_sellpremium))
			{
				char* TargetName = this->GetTokenString();
				int iPremiumDay = GetTokenNumber();

				if(TargetName != NULL && iPremiumDay > 0)
				{
					int iTargetIndex = gObjGetIndex(TargetName);

					if(iTargetIndex != -1)
					{
						LPOBJ lpTarget = &gObj[iTargetIndex];

						lpTarget->PremiumTimeType = 3;
						lpTarget->PremiumTime += ( iPremiumDay * 86400 );

						g_PremiumSystemEx.InfoMessage(iTargetIndex);
						ExUserDataSend(iTargetIndex);
						g_PremiumSystemEx.UserBuff(iTargetIndex);

						MsgOutput(aIndex, "[%s] vip level: %d", lpObj->Name, lpTarget->PremiumTimeType);
					}

					return true;
				}
			}
		}
		break;
	case 663:
		{
			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) ||
				g_ExLicense.CheckUser(eExUB::MedoniAndrei))
			{
#if(CUSTOM_MULTIWAREHOUSE)
				this->CmdWare(lpObj, this->GetTokenNumber());
#endif
				return 1;
			}
		}
		break;
#if(DEV_BANSYSTEM)
	case 664:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				g_BanSystem.DSReqInsert(TargetName, lpTargetObj->hdd_id, ( iTokenNumber1 * 3600 ), 1);
				MsgNormal(aIndex,"[BanChatHdd]: %s %d Hour",lpTargetObj->Name,iTokenNumber1);
				MsgNormal(TargetIndex,"[BanChatHdd]: %d Hour",iTokenNumber1);
			}
		}
		break;
	case 665:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;		
				g_BanSystem.DSReqDelete(TargetName);
				MsgNormal(aIndex,"[UnBanChatHdd]: %s", TargetName);
				int TargetIndex = gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				MsgNormal(TargetIndex,"[UnBanChatHdd]: %d Hour",iTokenNumber1);
			}
		}
		break;
	case 666:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				char * TargetName	= this->GetTokenString();
				int iTokenNumber1   = this->GetTokenNumber();
				if ( TargetName == NULL ) return 0;
				int TargetIndex		= gObjGetIndex(TargetName);
				if(TargetIndex == -1) return 0;
				LPOBJ lpTargetObj   = &gObj[TargetIndex];
				g_BanSystem.DSReqInsert(TargetName, lpTargetObj->hdd_id, ( iTokenNumber1 * 3600 ), 0);
				MsgNormal(aIndex,"[BanCharHdd]: %s %d Hour",lpTargetObj->Name,iTokenNumber1);
				MsgNormal(TargetIndex,"[BanCharHdd]: %d Hour",iTokenNumber1);
			}
		}
		break;
	case 667:
		{
			if(lpObj->Authority == 8 || lpObj->Authority == 32)
			{
				char * TargetName	= this->GetTokenString();
				if ( TargetName == NULL ) return 0;
				g_BanSystem.DSReqDelete(TargetName);
				MsgNormal(aIndex, "[UnBanCharHdd]: %s", TargetName);
			}
		}
		break;
#endif
	case 668:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.exGuardian(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 669:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.exHarmony(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 670:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.exLowStone(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 671:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.exHighStone(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;
	case 672:
		{
			if ( (lpObj->m_IfState.use) > 0 ) return 0;
			int iTokenNumber1   = this->GetTokenNumber();
			if ( iTokenNumber1 <= NULL || iTokenNumber1 > 140 ) return 0;
			gJewelsBank.exGemStone(aIndex, iTokenNumber1);
			return TRUE;
		}
		break;

	case 690:
		{
			#if(EVENT_QUESTIONANSWER)
			g_QuestionAnswer.Search();
			#endif
		}
		break;
	}
	return 0;
}

void CGMMng::GetInfinityArrowMPConsumption(LPOBJ lpObj)
{
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·®[+0:%d] [+1:%d] [+2:%d]",
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus0(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus1(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus2());
}

void CGMMng::ControlInfinityArrowMPConsumption0(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus0(iValue);
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·® єЇ°ж(+0) : %d",iValue);

}	

void CGMMng::ControlInfinityArrowMPConsumption1(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus1(iValue);
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·® єЇ°ж(+1) : %d",iValue);

}

void CGMMng::ControlInfinityArrowMPConsumption2(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus2(iValue);
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·® єЇ°ж(+2) : %d",iValue);

}

void CGMMng::ControlInfinityArrowMPConsumption3(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus3(iValue);
	MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм MP јТёр·® єЇ°ж(+3) : %d",iValue);

}

void CGMMng::SetInfinityArrowTime(LPOBJ lpObj, int iValue)
{
	if ( lpObj->Class == CLASS_ELF && lpObj->Type == OBJ_USER && lpObj->ChangeUP == 1 )
	{
		MsgOutput(lpObj->m_Index, "АОЗЗґПЖј ѕЦ·Оїм ЅГ°Ј °­Б¦ јіБ¤ : %dГК", iValue);
	}
	else
	{
		MsgOutput(lpObj->m_Index, "220·№є§ АМ»у №ВБої¤ЗБёё »зїл°ЎґЙЗХґПґЩ.");
	}
}

void CGMMng::ControlFireScreamDoubleAttackDistance(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetFireScreamExplosionAttackDistance(iValue);
	MsgOutput(lpObj->m_Index, "ЖДАМѕоЅєЕ©ёІ ґхєнµҐ№МБц Жш№Я°Её® єЇ°ж:%d", iValue);
}

// #Season 4.5 NEW FUNCS START
//00577CF0 
void CGMMng::CmdAbility(LPOBJ lpObj,char *szName)
{
	LPOBJ lpTargetObj = 0;
	int tIndex = -1;

	char szText[256];

	memset(szText,0,sizeof(szText));

	if(szName == NULL)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}
	
	tIndex = gObjGetIndex(szName);

	if(tIndex <= 0 )
	{
		GCServerMsgStringSend("Result-User Not Found", lpObj->m_Index, 1);
		return;
	}
	
	lpTargetObj = &gObj[tIndex];
	
	wsprintf(szText, "Result-Ability(%s)", szName);

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);

	int loc68 = 0;

	memset(szText,0,sizeof(szText));

	if(lpTargetObj->Class >= 0 && lpTargetObj->Class <= 5)
	{
		char classname[6][20] = {
			"WIZARD",
			"KNIGHT",
			"ELF",
			"MAGUMSA",
			"DARKLORD",
			"SUMMONER"
		};
		
		wsprintf(szText, "Class:%s",classname[lpTargetObj->Class] );
        GCServerMsgStringSend(szText, lpObj->m_Index, 1);
	}

	memset(szText,0,sizeof(szText));
	 
	wsprintf(szText,"Strength[%d] Dexterity[%d] Vitality[%d] Energy[%d] Leadership[%d]",
	lpTargetObj->AddStrength+lpTargetObj->Strength,
	lpTargetObj->AddDexterity+lpTargetObj->Dexterity,
	lpTargetObj->AddVitality+lpTargetObj->Vitality,
	lpTargetObj->AddEnergy+lpTargetObj->Energy,
	lpTargetObj->AddLeadership+lpTargetObj->Leadership);

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdParty(LPOBJ lpObj,char *szName)
{
	LPOBJ lpTargetObj = 0;
	int tIndex = -1;

	char szText[256];

	memset(szText,0,sizeof(szText));

	if(szName == NULL)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}
	
	tIndex = gObjGetIndex(szName);

	if(tIndex <= 0 )
	{
		GCServerMsgStringSend("Result-User Not Found", lpObj->m_Index, 1);
		return;
	}

	if(gObj[tIndex].PartyNumber < 0)
	{
		GCServerMsgStringSend("Result-Party Not Found", lpObj->m_Index, 1);
		return;
	}

	PARTY_STRUCT * lpParty = &gParty.m_PartyS[gObj[tIndex].PartyNumber];//loc68

	if(lpParty == 0)
	{
		GCServerMsgStringSend("Result-Invalid Point", lpObj->m_Index, 1);
		return;
	}
	
	GCServerMsgStringSend("Result-Party", lpObj->m_Index, 1);

	int PartyCount = 0;
	int PartyNumber = -1;//loc70

	for(int i = 0; i < 5;i++)
	{
		PartyNumber = lpParty->Number[i];

		if(PartyNumber < 0)
		{
			continue;
		}

		LPOBJ lpPartyObj = &gObj[PartyNumber];

		if(lpPartyObj != NULL)
		{
			if(lpPartyObj->Connected >= PLAYER_PLAYING)
			{
				PartyCount++;
				
				strcat(szText, lpPartyObj->Name);

				if(i == 0)
				{
					strcat(szText, "(Leader)");
				}

				if( lpParty->Count > PartyCount)
				{
					strcat(szText, ", ");
				}
			}
		}
	}

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdSummonMonster(LPOBJ lpObj,char *szMonsterName,int MonsterCount)
{
	char szText[256];

	memset(szText,0,sizeof(szText));

	if(MonsterCount < 1)
	{
		MonsterCount = 1;
	}

	if(szMonsterName == NULL)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	if(MonsterCount > 20)
	{
		GCServerMsgStringSend("Result-Too Manay Count", lpObj->m_Index, 1);
		return;
	}

	BYTE MapAttr = MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y);

	if ( (MapAttr &1) == 1 )
	{
		GCServerMsgStringSend("Result-Is Safetyzone", lpObj->m_Index, 1);
		return;
	}
	
	int MonsterClass = atoi(szMonsterName);//loc67
	LPMONSTER_ATTRIBUTE lpMonsterAttr = NULL;//loc68

	if(MonsterClass != 0)
	{
		lpMonsterAttr = gMAttr.GetAttr(MonsterClass);
	}
	else
	{
		lpMonsterAttr = gMAttr.GetAttr(szMonsterName);
	}

	if(lpMonsterAttr == NULL)
	{
		GCServerMsgStringSend("Result-Monster Not Found", lpObj->m_Index, 1);
		return;
	}

	if(this->GetType(lpMonsterAttr->m_Index) != OBJ_MONSTER)
	{
		GCServerMsgStringSend("Result-Monster Not Found", lpObj->m_Index, 1);
		return;	
	}

	for(int i = 0; i < MonsterCount; i++)
	{
		BYTE X = lpObj->X;
		BYTE Y = lpObj->Y;

		int iMonsterIndex = gObjAddMonster(lpObj->MapNumber);

		if ( iMonsterIndex >= 0 )
		{
			gObj[iMonsterIndex].m_btSummonedbyGM = 1;//i think its m_btSummonedbyGM
			gObj[iMonsterIndex].m_PosNum = -1;
			gObj[iMonsterIndex].X = X;
			gObj[iMonsterIndex].Y = Y;
			gObj[iMonsterIndex].MapNumber = lpObj->MapNumber;
			gObj[iMonsterIndex].TX = gObj[iMonsterIndex].X;
			gObj[iMonsterIndex].TY = gObj[iMonsterIndex].Y ;
			gObj[iMonsterIndex].m_OldX = gObj[iMonsterIndex].X;
			gObj[iMonsterIndex].m_OldY = gObj[iMonsterIndex].Y;
			gObj[iMonsterIndex].StartX = gObj[iMonsterIndex].X;
			gObj[iMonsterIndex].StartY = gObj[iMonsterIndex].Y;
			gObj[iMonsterIndex].Level = lpMonsterAttr->m_Level;
			gObj[iMonsterIndex].m_Attribute = 60;
			gObj[iMonsterIndex].MaxRegenTime = 0;
			gObj[iMonsterIndex].Dir = rand() % 8;
			gObjSetMonster(iMonsterIndex,lpMonsterAttr->m_Index );
		}
	}

	wsprintf(szText, "Result-SummonMonster(%s:%d)", lpMonsterAttr->m_Name, MonsterCount);
	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdClearMonster(LPOBJ lpObj,int Dis)
{
	char szText[256];

	memset(szText,0,sizeof(szText));
	
	if(Dis <= 0)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	int MapNumber = lpObj->MapNumber;//loc66
	int DeletedMonCount = 0;

	for(int i = 0;i<OBJ_MAXMONSTER;i++)
	{
		LPOBJ lpMonObj = &gObj[i];//loc69

		if( lpMonObj->MapNumber == MapNumber && 
			gObj[i].Connected == PLAYER_PLAYING &&
			gObj[i].Type == OBJ_MONSTER &&
			lpMonObj->Live != 0 &&
			lpMonObj->m_State == 2 )
		{
			if(gObjCalDistance(lpObj, lpMonObj) <= Dis)
			{
				if(lpMonObj->m_btSummonedbyGM == 1)
				{
					gObjDel(lpMonObj->m_Index);
				}
				else
				{
					lpMonObj->Live = 0;
					lpMonObj->m_State = 4;
					lpMonObj->RegenTime = GetTickCount();
					lpMonObj->DieRegen = 1;
					lpMonObj->PathCount = 0;
					GCDiePlayerSend( lpMonObj, lpMonObj->m_Index, 0, lpObj->m_Index);
				}

				DeletedMonCount++;
			}
		}
	}
	
	wsprintf(szText, "Result-ClearMonster(%d)", DeletedMonCount);
	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdClearItem(LPOBJ lpObj,int Dis)
{
	char szText[256];

	memset(szText,0,sizeof(szText));

	if(Dis <= 0)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}
	
	int MapNumber = lpObj->MapNumber;//loc66
	MapClass * lpMap = &MapC[MapNumber];//loc67

	int ItemCount = lpMap->GetVisibleItemCount(lpObj,Dis);

	wsprintf(szText, "Result-ClearItem(%d)", ItemCount);
	GCServerMsgStringSend(szText, lpObj->m_Index, 1);

}

void CGMMng::CmdClearInven(LPOBJ lpObj)
{
	char szText[256];
	memset(szText,0,sizeof(szText));

	int ItemCount = 0;

	for(int i = INVETORY_WEAR_SIZE;i < MAIN_INVENTORY_SIZE ; i++)
	{
		if(lpObj->pInventory[i].IsItem() == 1)
		{
			gObjInventoryDeleteItem(lpObj->m_Index, i);
			ItemCount++;
		}
	}

	GCItemListSend(lpObj->m_Index);

	wsprintf(szText, "Result-ClearInven(%d)", ItemCount);

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
}

void CGMMng::CmdSummonChar(LPOBJ lpObj,char * szName)
{
	LPOBJ lpTargetObj = 0;
	int tIndex = -1;

	char szText[256];
	memset(szText,0,sizeof(szText));

	if(szName == NULL)
	{
		GCServerMsgStringSend("Result-Invalid Argument", lpObj->m_Index, 1);
		return;
	}

	tIndex = gObjGetIndex(szName);

	if(tIndex <= 0)
	{
		GCServerMsgStringSend("Result-User Not Found", lpObj->m_Index, 1);
		return;
	}
	
	if(gObj[tIndex].Connected != PLAYER_PLAYING)
	{
		GCServerMsgStringSend("Result-Disconnect User", lpObj->m_Index, 1);
		return;
	}

	int MapNum = lpObj->MapNumber;//loc68
	int X = lpObj->X + 1;//loc69
	int Y = lpObj->Y + 1;//loc70

	BYTE MapAttr = MapC[MapNum].GetAttr(X, Y);
	
	if((MapAttr&4) == 4 || (MapAttr&8) == 8)
	{
		GCServerMsgStringSend("Result-Invalid Area", lpObj->m_Index, 1);
		return;
	}
	
	wsprintf(szText, "Result-SummonCharacter(%s)", szName);

	GCServerMsgStringSend(szText, lpObj->m_Index, 1);
	
	gObjTeleport(tIndex, MapNum,X, Y);

}

int CGMMng::GetType(WORD wClass)
{
	WORD Type = 0xFF;

	for(int i = 0; i< OBJ_MAXMONSTER; i++)
	{
		LPOBJ lpMonsterObj = &gObj[i];

		if(lpMonsterObj == NULL)
		{
			continue;
		}
		
		if(lpMonsterObj->Class == wClass)
		{
			Type = lpMonsterObj->Type;
			break;
		}
	}

	return Type;
}
#if(CUSTOM_MULTIWAREHOUSE)
void CGMMng::CmdWare(LPOBJ lpObj, int number)
{
	TNotice pNotice(1);

	if (!gObjIsConnected(lpObj->m_Index))
	{
		return;
	}

	if(g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		if(number == 2)
		{
			if(lpObj->PremiumTimeType < 1)
			{
				GCServerMsgStringSend("You need minimum premium level 1", lpObj->m_Index, 1);
				return;
			}
		}
		else if(number == 3)
		{
			if(lpObj->PremiumTimeType < 2)
			{
				GCServerMsgStringSend("You need minimum premium level 1", lpObj->m_Index, 1);
				return;
			}
		}
		else if(number == 4)
		{
			if(lpObj->PremiumTimeType < 3)
			{
				GCServerMsgStringSend("You need minimum premium level 1", lpObj->m_Index, 1);
				return;
			}
		}
	}

	/*if (!lpObj->bTemporaryUser)
	{
		GCServerMsgStringSend("You can't make ware, if you try exit the game", lpObj->m_Index, 1);
		return;
	}*/

	/*if (lpObj->MapNumber != 2)
	{
		GCServerMsgStringSend("You can do ware only in Capital Devias town", lpObj->m_Index, 1);
		return;
	}*/

	/*if (lpObj->m_PK_Level > 3)
	{
		GCServerMsgStringSend("PK Clear before make ware", lpObj->m_Index, 1);
		return;
	}*/

	BYTE attr = MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y);

	if ((attr & 1) == 0) //non safezone
	{
		GCServerMsgStringSend("You can do ware only in Capital Devias town safe zone!", lpObj->m_Index, 1);
		return;
	}

	if ((GetTickCount() - lpObj->MySelfDefenseTime) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), lpObj->m_Index, 1);
		GCCloseMsgSend(lpObj->m_Index, -1); //Season 2.5 add-on
		return;
	}

	/*if (lpObj->PartyNumber >= 0)
	{
		GCServerMsgStringSend("You cant do ware in party", lpObj->m_Index, 1);
		return;
	}

	if (lpObj->MapNumber != 2 && (lpObj->X >= 164 && lpObj->X <= 246)
		&& (lpObj->Y >= 2 && lpObj->Y <= 83))
	{
		GCServerMsgStringSend("You can do ware only in Capital Devias town", lpObj->m_Index, 1);
		return;
	}*/

	//lpObj->m_IfState.type = -1;
//	lpObj->m_IfState.state = -1;
//	lpObj->m_IfState.use = 0;

	//GDSetWarehouseList(lpObj->m_Index);

	//CGWarehouseUseEnd(lpObj->m_Index);

	// -----> CHECK

	if (lpObj->CloseCount >= 0)
	{
		pNotice.SendToUser(lpObj->m_Index, "[0] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.state == 1)
	{
		pNotice.SendToUser(lpObj->m_Index, "[1] Close NPC or Warehouse befor change number");
		return;
	}

	

	if (lpObj->m_IfState.use > 0)
	{
		pNotice.SendToUser(lpObj->m_Index, "[2] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.use == 1)
	{
		pNotice.SendToUser(lpObj->m_Index, "[3] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_ReqWarehouseOpen != false)
	{
		pNotice.SendToUser(lpObj->m_Index, "[4] Close Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.use == 1 && lpObj->m_IfState.type == 6)
	{
		//CGWarehouseUseEnd(lpObj->m_Index);
		pNotice.SendToUser(lpObj->m_Index, "[5] Close NPC or Warehouse befor change number");
		return;
	}

	if (lpObj->m_IfState.use && lpObj->m_IfState.type == 6)
	{
		//lpObj->m_IfState.use = 0;
		//lpObj->m_IfState.state = 0;
		//lpObj->WarehouseSave = FALSE;
		pNotice.SendToUser(lpObj->m_Index, "[6] Close NPC or Warehouse befor change number");
		return;
	}

	if ( lpObj->m_IfState.type != 6 )
	{
		pNotice.SendToUser(lpObj->m_Index, "[7] Close NPC or Warehouse befor change number");
		return;
	}

	if ( lpObj->m_IfState.type == 6 && lpObj->m_IfState.state == 1 )
	{
		pNotice.SendToUser(lpObj->m_Index, "[8] Close NPC or Warehouse befor change number");
		return;
	}

	

	/*
	if ( lpObj->m_IfState.type == 6 )
	{
		lpObj->m_IfState.state = 1;
		lpObj->WarehouseSave = TRUE;
	}*/

	/*if (lpObj->m_IfState.use > 1)
	{
		pNotice.SendToUser(lpObj->m_Index, "[8] Close NPC or Warehouse befor change number");
		return;
	}*/

	int WarehouseNumber = 0;
	if (number < 0 || number > 4)
	{
		pNotice.SendToUser(lpObj->m_Index, "Ware number: %d | Min: 0| Max: 4", number, WarehouseNumber);
		return;
	}

	//CGWarehouseUseEnd(lpObj->m_Index);//

	lpObj->WarehouseNumber = number;
	if (lpObj->WarehouseNumber >= 4)
	{
		lpObj->WarehouseNumber = 4;
	}
	if (lpObj->WarehouseNumber <= 0)
	{
		lpObj->WarehouseNumber = 0;
	}
	pNotice.SendToUser(lpObj->m_Index, "Ware number: %d", number);
	//lpObj->Money -= 1000000 + (25000 * lpObj->Reset) + (450000 * lpObj->GrandReset) + (1000000 * lpObj->GR);
	//GCMoneySend(lpObj->m_Index, lpObj->Money);
	//int iChaosTaxMoney = 1000000 + (25000 * lpObj->Reset) + (450000 * lpObj->GrandReset) + (1000000 * lpObj->GR) * g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100;
	//if (iChaosTaxMoney < 0)
	//{
	//	iChaosTaxMoney = 0;
	//}
	//g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);

	//GDGetWarehouseList(lpObj->m_Index, lpObj->AccountID, lpObj->WarehouseNumber);//
}
#endif