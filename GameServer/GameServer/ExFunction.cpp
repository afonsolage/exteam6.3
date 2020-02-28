#include "StdAfx.h"
#include "user.h"
#include "Configs.h"
#include "..\\common\\winutil.h"
#include "GameMain.h"
#include "SystemOfRage.h"
#include "ExLicense.h"
#include "WinQuestSystem.h"
#include "EventTimer.h"
#include "ExFunction.h"
#include "PersonalShopEx.h"
#include "ExText.h"

void exGCConfigSend(int aIndex)
{
	EX_GC_CONFIG_SEND rSend;
	LPOBJ lpObj =&gObj[aIndex];
	rSend.h.set((LPBYTE)&rSend, 0xFB, 15, sizeof(rSend));
	rSend.CharSwitch = (BYTE)ExConfig.ExCustom.SwitchChar;
	rSend.sGENS = (BYTE)gGENS;
	rSend.HelperLevel = ExConfig.ExCustom.HelperClickerLevel;
	rSend.AutoParty =  ExConfig.ExCustom.AutoParty;
	rSend.Top100 = ExConfig.ExCustom.Top100;
	rSend.EventTimer = gEventTimer.Enable;
	rSend.MoveTargetPosEffect = ExConfig.ExCustom.MoveTargetPosEffect;
	rSend.CastleSiegeSkill = ExConfig.Character.CastleSiegeSkillEnable;
	rSend.AntiCheat = ExConfig.ExCustom.ClientAntiCheat;
	rSend.GensColorEnable = ExConfig.Command.GensColorEnable;
	rSend.GensColorRed = ExConfig.Command.GensColorRed;
	rSend.GensColorGreen = ExConfig.Command.GensColorGreen;
	rSend.GensColorBlue = ExConfig.Command.GensColorBlue;
	rSend.MaxStats = ExConfig.Character.MaxStats;

	rSend.DLReflect = 0;
	rSend.MasterSkills = 1;
	rSend.DivFireScreamSpeed = 1;
	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		rSend.DLReflect = ExConfig.ExCustom.DLReflect;
		rSend.MasterSkills = ExConfig.ExCustom.MasterSkills;
		rSend.DivFireScreamSpeed = ExConfig.ExCustom.DivFireScreamSpeed;
	}

	if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
	{
		rSend.DivFireScreamSpeed = ExConfig.ExCustom.DivFireScreamSpeed;
	}

	rSend.MasterSkills = ExConfig.ExCustom.MasterSkills;

	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
}



bool exCheckSimbol(char* String, int StrLen)
{
	for(int i=0;i<StrLen;i++)
	{
		if(String[i] == NULL)
			continue;
		
		switch(String[i])
		{
			case 'a': continue ; break;
			case 'b': continue ; break;
			case 'c': continue ; break;
			case 'd': continue ; break;
			case 'e': continue ; break;
			case 'f': continue ; break;
			case 'g': continue ; break;
			case 'h': continue ; break;
			case 'i': continue ; break;
			case 'j': continue ; break;
			case 'k': continue ; break;
			case 'l': continue ; break;
			case 'm': continue ; break;
			case 'n': continue ; break;
			case 'o': continue ; break;
			case 'p': continue ; break;
			case 'q': continue ; break;
			case 'r': continue ; break;
			case 's': continue ; break;
			case 't': continue ; break;
			case 'u': continue ; break;
			case 'v': continue ; break;
			case 'w': continue ; break;
			case 'x': continue ; break;
			case 'y': continue ; break;
			case 'z': continue ; break;
			case 'A': continue ; break;
			case 'B': continue ; break;
			case 'C': continue ; break;
			case 'D': continue ; break;
			case 'E': continue ; break;
			case 'F': continue ; break;
			case 'G': continue ; break;
			case 'H': continue ; break;
			case 'I': continue ; break;
			case 'J': continue ; break;
			case 'K': continue ; break;
			case 'L': continue ; break;
			case 'M': continue ; break;
			case 'N': continue ; break;
			case 'O': continue ; break;
			case 'P': continue ; break;
			case 'Q': continue ; break;
			case 'R': continue ; break;
			case 'S': continue ; break;
			case 'T': continue ; break;
			case 'U': continue ; break;
			case 'V': continue ; break;
			case 'W': continue ; break;
			case 'X': continue ; break;
			case 'Y': continue ; break;
			case 'Z': continue ; break;
			case '0': continue ; break;
			case '1': continue ; break;
			case '2': continue ; break;
			case '3': continue ; break;
			case '4': continue ; break;
			case '5': continue ; break;
			case '6': continue ; break;
			case '7': continue ; break;
			case '8': continue ; break;
			case '9': continue ; break;
			default: return false;
		}
	}
	return true;
}

char * exMapName(int MapNum)
{
	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::MU2Play))
	{
		if(MAP_INDEX_ELBELAND == MapNum)
		{
			return  "Arkania";
		}
	}

	switch(MapNum)
	{
	case MAP_INDEX_RORENCIA:			return g_ExText.GetText(164); //Lorencia";
	case MAP_INDEX_DUNGEON:				return g_ExText.GetText(165); //Dungeon";
	case MAP_INDEX_DEVIAS:				return g_ExText.GetText(166); //Devias";
	case MAP_INDEX_NORIA:				return g_ExText.GetText(167); //Noria";
	case MAP_INDEX_LOSTTOWER:			return g_ExText.GetText(168); //LostTower";
	//MAP_INDEX_RESERVED = 0x5,
	case MAP_INDEX_BATTLESOCCER:		return g_ExText.GetText(169); //Arena";
	case MAP_INDEX_ATHLANSE:			return g_ExText.GetText(170); //Atlans";
	case MAP_INDEX_TARKAN:				return g_ExText.GetText(171); //Tarkan";
	case MAP_INDEX_DEVILSQUARE:			return g_ExText.GetText(172); //DevilSquare";
	case MAP_INDEX_ICARUS:				return g_ExText.GetText(173); //Icarus";
	case MAP_INDEX_BLOODCASTLE1:		return g_ExText.GetText(174); //Blood Castle 1";
	case MAP_INDEX_BLOODCASTLE2:		return g_ExText.GetText(175); //Blood Castle 2";
	case MAP_INDEX_BLOODCASTLE3:		return g_ExText.GetText(176); //Blood Castle 3";
	case MAP_INDEX_BLOODCASTLE4:		return g_ExText.GetText(177); //Blood Castle 4";
	case MAP_INDEX_BLOODCASTLE5:		return g_ExText.GetText(178); //Blood Castle 5";
	case MAP_INDEX_BLOODCASTLE6:		return g_ExText.GetText(179); //Blood Castle 6";
	case MAP_INDEX_BLOODCASTLE7:		return g_ExText.GetText(180); //Blood Castle 7";
	case MAP_INDEX_CHAOSCASTLE1:		return g_ExText.GetText(181); //Chaos Castle 1";
	case MAP_INDEX_CHAOSCASTLE2:		return g_ExText.GetText(182); //Chaos Castle 2";
	case MAP_INDEX_CHAOSCASTLE3:		return g_ExText.GetText(183); //Chaos Castle 3";
	case MAP_INDEX_CHAOSCASTLE4:		return g_ExText.GetText(184); //Chaos Castle 4";
	case MAP_INDEX_CHAOSCASTLE5:		return g_ExText.GetText(185); //Chaos Castle 5";
	case MAP_INDEX_CHAOSCASTLE6:		return g_ExText.GetText(186); //Chaos Castle 6";
	case MAP_INDEX_KALIMA1:				return g_ExText.GetText(187); //Kalima 1";
	case MAP_INDEX_KALIMA2:				return g_ExText.GetText(188); //Kalima 2";
	case MAP_INDEX_KALIMA3:				return g_ExText.GetText(189); //Kalima 3";
	case MAP_INDEX_KALIMA4:				return g_ExText.GetText(190); //Kalima 4";
	case MAP_INDEX_KALIMA5:				return g_ExText.GetText(191); //Kalima 5";
	case MAP_INDEX_KALIMA6:				return g_ExText.GetText(192); //Kalima 6";
	case MAP_INDEX_CASTLESIEGE:			return g_ExText.GetText(193); //Castle";
	case MAP_INDEX_CASTLEHUNTZONE :		return g_ExText.GetText(194); //Land Of Trial";
	//case MAP_INDEX_DEVILSQUARE2:		return g_ExText.GetText(164); //Blood Castle 7";
	case MAP_INDEX_AIDA:				return g_ExText.GetText(195); //Aida";
	case MAP_INDEX_CRYWOLF_FIRSTZONE:	return g_ExText.GetText(196); //Cry Wolf";
	case MAP_INDEX_CRYWOLF_SECONDZONE:	return g_ExText.GetText(197); //Cry Wolf";
	case MAP_INDEX_KALIMA7:				return g_ExText.GetText(198); //Kalima 7";
	case MAP_INDEX_KANTURU1:			return g_ExText.GetText(199); //Kanturu";
	case MAP_INDEX_KANTURU2:			return g_ExText.GetText(200); //Kanturu Relic";
	case MAP_INDEX_KANTURU_BOSS:		return g_ExText.GetText(201); //Kanturu Boss";
	case MAP_INDEX_GM_SUMMONZONE:		return g_ExText.GetText(245); //Blood Castle 7";
	case MAP_INDEX_BALGASS_BARRACKS:	return g_ExText.GetText(202); //Balgas Baraks";
	case MAP_INDEX_BALGASS_REFUGEE:		return g_ExText.GetText(203); //Balgas Refuge";
	case MAP_INDEX_ILLUSIONTEMPLE1:		return g_ExText.GetText(204); //Illusion Temple 1";
	case MAP_INDEX_ILLUSIONTEMPLE2:		return g_ExText.GetText(205); //Illusion Temple 2";
	case MAP_INDEX_ILLUSIONTEMPLE3:		return g_ExText.GetText(206); //Illusion Temple 3";
	case MAP_INDEX_ILLUSIONTEMPLE4:		return g_ExText.GetText(207); //Illusion Temple 4";
	case MAP_INDEX_ILLUSIONTEMPLE5:		return g_ExText.GetText(208); //Illusion Temple 5";
	case MAP_INDEX_ILLUSIONTEMPLE6:		return g_ExText.GetText(209); //Illusion Temple 6";
	case MAP_INDEX_ELBELAND:			return g_ExText.GetText(210); //Elblend";
	case MAP_INDEX_BLOODCASTLE8:		return g_ExText.GetText(211); //Blood Castle 8";
	case MAP_INDEX_CHAOSCASTLE7:		return g_ExText.GetText(212); //Chaos Castle 7";
	case MAP_INDEX_DEVILSQUARE7:		return g_ExText.GetText(213); //Devil Squere 7";
	case MAP_INDEX_SWAMPOFCALMNESS:		return g_ExText.GetText(214); //Swamp Of Calmness";
	case MAP_INDEX_RAKLION:				return g_ExText.GetText(215); //Raklion";
	case MAP_INDEX_RAKLION_BOSS:		return g_ExText.GetText(216); //Raklion Boss";
	case MAP_INDEX_SANTATOWN:			return g_ExText.GetText(217); //Santa Town";
	case MAP_INDEX_VULCAN:				return g_ExText.GetText(218); //Vulcan";
	case MAP_INDEX_VULCANROOM:			return g_ExText.GetText(219); //Vulcan Room";
	case MAP_INDEX_DOUBLE_GOER1:		return g_ExText.GetText(220); //Double Goer 1";
	case MAP_INDEX_DOUBLE_GOER2:		return g_ExText.GetText(221); //Double Goer 2";
	case MAP_INDEX_DOUBLE_GOER3:		return g_ExText.GetText(222); //Double Goer 3";
	case MAP_INDEX_DOUBLE_GOER4:		return g_ExText.GetText(223); //Double Goer 4";
	case MAP_INDEX_IMPERIAL1:			return g_ExText.GetText(224); //Imperial 1";
	case MAP_INDEX_IMPERIAL2:			return g_ExText.GetText(225); //Imperial 2";
	case MAP_INDEX_IMPERIAL3:			return g_ExText.GetText(226); //Imperial 3";
	case MAP_INDEX_IMPERIAL4:			return g_ExText.GetText(227); //Imperial 4";
	case 79: return g_ExText.GetText(228); //Loren Market";
	case 80: return g_ExText.GetText(229); //Karutan";
	case 81: return g_ExText.GetText(230); //Karutan 2";
	}

	return  "Unknown";
}

CTime StrToCTime(const char* str)
{
	int year, month, day, hh, mm, ss;
	sscanf(str, "%d.%d.%d %d:%d:%d", &day, &month, &year, &hh, &mm, &ss);
	return CTime(year, month, day, hh, mm, ss);
}

bool CheckFile(char* File)
{
	bool Result = true;
	FILE *file = fopen(File,"r");
	if (file == NULL)
	{
		Result = false;
		MessageBoxA(0,File,"LOAD FILE ERROR",0);
	}
	else
	{
		fclose(file);
	}
	
	return Result;
}

/*
	MAP_INDEX_RORENCIA = 0x0,
	MAP_INDEX_DUNGEON = 0x1,
	MAP_INDEX_DEVIAS = 0x2,
	MAP_INDEX_NORIA = 0x3,
	MAP_INDEX_LOSTTOWER = 0x4,
	MAP_INDEX_RESERVED = 0x5,
	MAP_INDEX_BATTLESOCCER = 0x6,
	MAP_INDEX_ATHLANSE = 0x7,
	MAP_INDEX_TARKAN = 0x8,
	MAP_INDEX_DEVILSQUARE = 0x9,
	MAP_INDEX_ICARUS = 0xa,
	MAP_INDEX_BLOODCASTLE1 = 0xb,
	MAP_INDEX_BLOODCASTLE2 = 0xc,
	MAP_INDEX_BLOODCASTLE3 = 0xd,
	MAP_INDEX_BLOODCASTLE4 = 0xe,
	MAP_INDEX_BLOODCASTLE5 = 0xf,
	MAP_INDEX_BLOODCASTLE6 = 0x10,
	MAP_INDEX_BLOODCASTLE7 = 0x11,
	MAP_INDEX_CHAOSCASTLE1 = 0x12,
	MAP_INDEX_CHAOSCASTLE2 = 0x13,
	MAP_INDEX_CHAOSCASTLE3 = 0x14,
	MAP_INDEX_CHAOSCASTLE4 = 0x15,
	MAP_INDEX_CHAOSCASTLE5 = 0x16,
	MAP_INDEX_CHAOSCASTLE6 = 0x17,
	MAP_INDEX_KALIMA1 = 0x18,
	MAP_INDEX_KALIMA2 = 0x19,
	MAP_INDEX_KALIMA3 = 0x1a,
	MAP_INDEX_KALIMA4 = 0x1b,
	MAP_INDEX_KALIMA5 = 0x1c,
	MAP_INDEX_KALIMA6 = 0x1d,
	MAP_INDEX_CASTLESIEGE = 0x1e,
	MAP_INDEX_CASTLEHUNTZONE = 0x1f,
	MAP_INDEX_DEVILSQUARE2 = 0x20,
	MAP_INDEX_AIDA = 0x21,
	MAP_INDEX_CRYWOLF_FIRSTZONE = 0x22,
	MAP_INDEX_CRYWOLF_SECONDZONE = 0x23,
	MAP_INDEX_KALIMA7 = 0x24,
	MAP_INDEX_KANTURU1 = 0x25,
	MAP_INDEX_KANTURU2 = 0x26,
	MAP_INDEX_KANTURU_BOSS = 0x27,
	MAP_INDEX_GM_SUMMONZONE = 0x28,
	MAP_INDEX_BALGASS_BARRACKS = 0x29,
	MAP_INDEX_BALGASS_REFUGEE = 0x2A,
	MAP_INDEX_ILLUSIONTEMPLE1 = 0x2D,
	MAP_INDEX_ILLUSIONTEMPLE2 = 0x2E,
	MAP_INDEX_ILLUSIONTEMPLE3 = 0x2F,
	MAP_INDEX_ILLUSIONTEMPLE4 = 0x30,
	MAP_INDEX_ILLUSIONTEMPLE5 = 0x31,
	MAP_INDEX_ILLUSIONTEMPLE6 = 0x32,
	MAP_INDEX_ELBELAND = 0x33,
	MAP_INDEX_BLOODCASTLE8 = 0x34,
	MAP_INDEX_CHAOSCASTLE7 = 0x35,
	MAP_INDEX_DEVILSQUARE7 = 0x36,
	MAP_INDEX_SWAMPOFCALMNESS = 0x38,
	MAP_INDEX_RAKLION = 0x39,
	MAP_INDEX_RAKLION_BOSS = 0x3A,
	MAP_INDEX_SANTATOWN = 0x3E,
	MAP_INDEX_VULCAN			= 0x3f,
	MAP_INDEX_VULCANROOM		= 0x40,
	MAP_INDEX_DOUBLE_GOER1 = 65,	//Season 5 DoppelGanger
	MAP_INDEX_DOUBLE_GOER2 = 66,	//Season 5 DoppelGanger
	MAP_INDEX_DOUBLE_GOER3 = 67,	//Season 5 DoppelGanger
	MAP_INDEX_DOUBLE_GOER4 = 68,	//Season 5 DoppelGanger
	MAP_INDEX_IMPERIAL1 = 69,		//Season 5 ImperialFort
	MAP_INDEX_IMPERIAL2 = 70,
	MAP_INDEX_IMPERIAL3 = 71,
	MAP_INDEX_IMPERIAL4 = 72
*/

bool CheckOptionItem(int Item1, int Item2, int iType)
{
	if(iType)
	{
		if(Item1 == Item2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(Item1 && Item2)
		{
			return true;
		}
		else if(!Item1 && !Item2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void CheckAndFixMinNumber(int &Number, int MinNumber)
{
	if(Number < MinNumber)
	{
		Number = MinNumber;
	}
}

void CheckAndFixNumber(int &Number, int MinNumber, int MaxNumber)
{
	if(Number < MinNumber)
	{
		Number = MinNumber;
	}
	if(Number > MaxNumber)
	{
		Number = MaxNumber;
	}
}