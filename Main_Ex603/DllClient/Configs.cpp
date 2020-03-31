#include "stdafx.h"
#include "Configs.h"
#include "NewHpBar.h"
#include "Console.h"
#include "Graphics.h"
#include "ExFunction.h"
#include "EncDec.h"
#include "TMemory.h"

cConfig gConfig;

#define MAX_XoR	8
BYTE XoRT[MAX_XoR] = {  0xD4, 0x7B, 0x2B, 0x2B, 0x58, 0x48, 0xD4, 0xD9 };

bool gGENS;
bool gGRANDRESET;
bool gRAGESYSTEM;
bool gWINQUEST;
bool gMONSTER_QUEST_SYSTEM;
bool gPARTY_SYSTEM;
DWORD gHelperLevel = 80;
int iMonsterHPBar;
int iUserHpBar;
int iPartyHpBar;
int interCustom;
bool bAntiHack;
bool gFogEffect;
int g_MaxCharacter = 7;
BYTE g_MaxPartyMember;
bool gAutoLogin = false;

char gWindowTitle[50];
bool gMultiLang = false;
bool gFontEnable = false;
int gFontSize[5];
char gFontName[5][20];
bool gGlowEffect;
bool gCheckCloseWindow;
bool gMiniMap;
DWORD g_dwDivFireScreamSpeed = 1;
bool gAutoMouseKey;
bool gMuHelperInventory;
bool gDamageTable;
bool gAdvanceStats;
	 
void cConfig::Configs()
{
	memset(gFontName, 0, sizeof(gFontName));

	gGENS = GetPrivateProfileInt("ExTeam","Gens",0,DIR_CONFIGS);
	gGRANDRESET = FALSE;//GetPrivateProfileInt("ExTeam","GrandReset",0,DIR_CONFIGS);
	gFogEffect = GetPrivateProfileInt("ExTeam","FogEffect",0,DIR_CONFIGS);
	GetPrivateProfileString("ExTeam", "WindowTitle", "MU", gWindowTitle, 50, DIR_CONFIGS);
	gMultiLang = GetPrivateProfileInt("ExTeam","MultiLang",0,DIR_CONFIGS);
	gFontEnable = GetPrivateProfileInt("ExTeam","FontEnable",0,DIR_CONFIGS);
	GetPrivateProfileString("ExTeam", "FontName1", "Gulim", gFontName[0], 20, DIR_CONFIGS);
	GetPrivateProfileString("ExTeam", "FontName2", "0", gFontName[1], 20, DIR_CONFIGS);
	GetPrivateProfileString("ExTeam", "FontName3", "0", gFontName[2], 20, DIR_CONFIGS);
	GetPrivateProfileString("ExTeam", "FontName4", "0", gFontName[3], 20, DIR_CONFIGS);
	
	gFontSize[0] = GetPrivateProfileInt("ExTeam","FontSize1",13,DIR_CONFIGS);
	gFontSize[1] = GetPrivateProfileInt("ExTeam","FontSize2",13,DIR_CONFIGS);
	gFontSize[2] = GetPrivateProfileInt("ExTeam","FontSize3",13,DIR_CONFIGS);
	gFontSize[3] = GetPrivateProfileInt("ExTeam","FontSize4",13,DIR_CONFIGS);
	gFontSize[4] = GetPrivateProfileInt("ExTeam","FontSize5",13,DIR_CONFIGS);

	gGlowEffect = GetPrivateProfileInt("ExTeam","GlowEffect",0,DIR_CONFIGS);
	gCheckCloseWindow = GetPrivateProfileInt("ExTeam","CheckCloseWindow",0,DIR_CONFIGS);
	gMiniMap = GetPrivateProfileInt("ExTeam","MiniMap",1,DIR_CONFIGS);
	gAutoMouseKey = GetPrivateProfileInt("ExTeam","AutoMouseKey",1,DIR_CONFIGS);
	gMuHelperInventory = GetPrivateProfileInt("ExTeam","MuHelperInventory",1,DIR_CONFIGS);
	
	gDamageTable = GetPrivateProfileInt("ExTeam","DamageTable",1,DIR_CONFIGS);
	gAdvanceStats = GetPrivateProfileInt("ExTeam","AdvanceStats",1,DIR_CONFIGS);

#if(CUSTOM_MUHELPER_INV)
	if(gMuHelperInventory)
	{
		SetRange((LPVOID)0x0095DE51, 2, ASM::NOP);	//MUHelper Inventory 1
		SetByte((LPVOID)(0x0095CE90), 0xEB);		//MUHelper Inventory 2
	}
#endif


	gRAGESYSTEM = 0;
	gWINQUEST = 0;
	gMONSTER_QUEST_SYSTEM = false;
	gPARTY_SYSTEM = false;
	this->LauncherActive = 0;
	g_MaxPartyMember = 5;

#if(ENABLE_ENCODER)
	g_EncDec.GetBuffer(CONNECT_IP_DIR);
	g_EncDec.PackBuffer();
#if DEBUG
	char tmp[256] = {0};
	sscanf(g_EncDec.m_PackBuff, "%s %d %s %s %s", &this->MyIp, &this->LauncherActive, &this->LauncherParameters, &this->Serial, &tmp);
	gConsole.Output(cGREEN, "IP: %s, Launcher: %s, LauncherParam: %s, Serial: %s, Version: %s", this->MyIp, this->LauncherActive ? "TRUE" : "FALSE", this->LauncherParameters, this->Serial, tmp);

	int ver = atoi(tmp);
	sprintf(this->Version, "%d", (ver - 10000) + 22345);
#else
	sscanf(g_EncDec.m_PackBuff, "%s %d %s", &this->MyIp, &this->LauncherActive, &this->LauncherParameters);
	gConsole.Output(cGREEN, "IP: %s, Launcher: %s, LauncherParam: %s, Serial: %s, Version: %s", this->MyIp, this->LauncherActive ? "TRUE" : "FALSE", this->LauncherParameters);
#endif
	g_EncDec.ClearBuffer();
#else
	this->ReedConnect();
#endif
}

void cConfig::Encode(char* buffer, int size)
{
	int a = 0;
	for ( int i = 0 ; i < size ; i++ )
	{
		if( a == MAX_XoR )
		{
			a = 0;
		}
		buffer[i] = buffer[i] ^ XoRT[a];
		a++;
	}
}

void cConfig::SaveGame()
{
	FILE * file = fopen(GAMEINFO_DIR,"w");
	char InfoDate[512];
	sprintf(InfoDate, GAMEBUFFER,iMonsterHPBar, iUserHpBar, iPartyHpBar, g_bGlowGraphic, interCustom);
	fputs(InfoDate, file);
	fclose(file);
}

void cConfig::LoadGame()
{
	this->Configs();

	iMonsterHPBar = 2;
	iUserHpBar = 1;
	iPartyHpBar = 1;
	g_bGlowGraphic = 1;
	interCustom = 0;

	FILE * file = fopen(GAMEINFO_DIR,"r");

	if (file == NULL)
	{
		this->SaveGame();
		return;
	}

	char Buff[512];

	while (!feof(file))
	{
		fgets(Buff,512,file);
		sscanf(Buff, GAMEBUFFER, &iMonsterHPBar, &iUserHpBar, &iPartyHpBar, &g_bGlowGraphic, &interCustom);
	}

	fclose(file);

	this->ItemLoad();
}

void cConfig::ReedConnect()
{
	char Doc[512];
	FILE * file = fopen(CONNECT_IP_DIR,"r");
	if (file == NULL)
	{
		return;
	}
	char Buff[512];
	while (!feof(file))
	{
		fgets(Buff,512,file);
		sscanf(Buff, "%s %d %s", &this->MyIp,&this->LauncherActive,&this->LauncherParameters);
	}
	fclose(file);
}

void cConfig::ItemLoad()
{
	ZeroMemory(this->Item,sizeof(Item));
	ZeroMemory(this->iGlow,sizeof(iGlow));

	FILE * file = fopen(ITEM_LOAD_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,ITEM_LOAD_DIR,"LOAD ERROR",0);
		return;
	}

	char Buff[256];
	int Flag = 0;

	this->CountItem = 0;
	this->CountGlow = 0;
#ifdef _GRAND_SYSTEM_
	
		this->iGlow[this->CountGlow].Type	= -1;
		this->iGlow[this->CountGlow].Index	= 90;
		this->iGlow[this->CountGlow].Red	= 0.30;
		this->iGlow[this->CountGlow].Green	= 0.30;
		this->iGlow[this->CountGlow].Blue	= 0.80;
		this->CountGlow++;
		//cl.r = 0.00f; cl.g = 0.20f; cl.b = 0.10f;
		this->iGlow[this->CountGlow].Type	= -1;
		this->iGlow[this->CountGlow].Index	= 84;
		this->iGlow[this->CountGlow].Red	= 0.00;
		this->iGlow[this->CountGlow].Green	= 0.20;
		this->iGlow[this->CountGlow].Blue	= 0.10;
		this->CountGlow++;
		//cl.r = 0.60f; cl.g = 0.30f; cl.b = 1.00f;
		this->iGlow[this->CountGlow].Type	= -1;
		this->iGlow[this->CountGlow].Index	= 85;
		this->iGlow[this->CountGlow].Red	= 0.90;
		this->iGlow[this->CountGlow].Green	= 0.10;
		this->iGlow[this->CountGlow].Blue	= 0.10;
		//this->iGlow[this->CountGlow].Red	= 0.60;
		//this->iGlow[this->CountGlow].Green	= 0.30;
		//this->iGlow[this->CountGlow].Blue	= 1.00;
		this->CountGlow++;
		//cl.r = 0.10f; cl.g = 0.60f; cl.b = 0.50f
		this->iGlow[this->CountGlow].Type	= -1;
		this->iGlow[this->CountGlow].Index	= 86;
		this->iGlow[this->CountGlow].Red	= 0.10;
		this->iGlow[this->CountGlow].Green	= 0.60;
		this->iGlow[this->CountGlow].Blue	= 0.50;
		//
		this->CountGlow++;
		//cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f
		this->iGlow[this->CountGlow].Type	= -1;
		this->iGlow[this->CountGlow].Index	= 87;
		this->iGlow[this->CountGlow].Red	= 0.40;
		this->iGlow[this->CountGlow].Green	= 0.40;
		this->iGlow[this->CountGlow].Blue	= 0.40;
		this->CountGlow++;
		//cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f;
		this->iGlow[this->CountGlow].Type	= -1;
		this->iGlow[this->CountGlow].Index	= 88;
		this->iGlow[this->CountGlow].Red	= 0.40;
		this->iGlow[this->CountGlow].Green	= 0.40;
		this->iGlow[this->CountGlow].Blue	= 0.40;
		this->CountGlow++;
		//cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f;
		this->iGlow[this->CountGlow].Type	= -1;
		this->iGlow[this->CountGlow].Index	= 89;
		this->iGlow[this->CountGlow].Red	= 0.40;
		this->iGlow[this->CountGlow].Green	= 0.40;
		this->iGlow[this->CountGlow].Blue	= 0.40;
		this->CountGlow++;
		//cl.r = 0.10f; cl.g = 0.30f; cl.b = 0.50f; Apocalypse staff
		this->iGlow[this->CountGlow].Type	= 5;
		this->iGlow[this->CountGlow].Index	= 41;
		this->iGlow[this->CountGlow].Red	= 0.90;
		this->iGlow[this->CountGlow].Green	= 0.10;
		this->iGlow[this->CountGlow].Blue	= 0.10;
	/*	this->iGlow[this->CountGlow].Red	= 0.10;
		this->iGlow[this->CountGlow].Green	= 0.30;
		this->iGlow[this->CountGlow].Blue	= 0.50;*/
		this->CountGlow++;

		//cl.r = 0.70; cl.g = 0.70f; cl.b = 0.70f Divine Shield
		this->iGlow[this->CountGlow].Type	= 6;
		this->iGlow[this->CountGlow].Index	= 33;
		this->iGlow[this->CountGlow].Red	= 0.90;
		this->iGlow[this->CountGlow].Green	= 0.10;
		this->iGlow[this->CountGlow].Blue	= 0.10;
		/*this->iGlow[this->CountGlow].Red	= 0.70;
		this->iGlow[this->CountGlow].Green	= 0.70;
		this->iGlow[this->CountGlow].Blue	= 0.70;*/
		this->CountGlow++;
		//cl.r = 0.30f; cl.g = 1.00f; cl.b = 1.00f Naga
		this->iGlow[this->CountGlow].Type	= 5;
		this->iGlow[this->CountGlow].Index	= 41;
		this->iGlow[this->CountGlow].Red	= 0.30;
		this->iGlow[this->CountGlow].Green	= 1.00;
		this->iGlow[this->CountGlow].Blue	= 1.00;
		this->CountGlow++;
		//cl.r = 0.30f; cl.g = 1.00f; cl.b = 1.00f Lazy wing shield
		this->iGlow[this->CountGlow].Type	= 6;
		this->iGlow[this->CountGlow].Index	= 32;
		this->iGlow[this->CountGlow].Red	= 0.30;
		this->iGlow[this->CountGlow].Green	= 1.00;
		this->iGlow[this->CountGlow].Blue	= 1.00;
		this->CountGlow++;
		//cl.r = 0.30f; cl.g = 0.30f; cl.b = 0.00f; Bow
		this->iGlow[this->CountGlow].Type	= 4;
		this->iGlow[this->CountGlow].Index	= 30;
		this->iGlow[this->CountGlow].Red	= 0.30;
		this->iGlow[this->CountGlow].Green	= 0.30;
		this->iGlow[this->CountGlow].Blue	= 0.00;
		this->CountGlow++;
		//cl.r = 0.30f; cl.g = 0.20f; cl.b = 0.00f Shtorm Sword
		this->iGlow[this->CountGlow].Type	= 5;
		this->iGlow[this->CountGlow].Index	= 42;
		this->iGlow[this->CountGlow].Red	= 0.30;
		this->iGlow[this->CountGlow].Green	= 0.20;
		this->iGlow[this->CountGlow].Blue	= 0.00;
		this->CountGlow++;
		//case ITEM(6,31)Hell Knight Shield cl.r = 0.80f; cl.g = 0.30f; cl.b = 0.10f; OldGlow = false; break;
		this->iGlow[this->CountGlow].Type	= 6;
		this->iGlow[this->CountGlow].Index	= 31;
		this->iGlow[this->CountGlow].Red	= 0.80;
		this->iGlow[this->CountGlow].Green	= 0.30;
		this->iGlow[this->CountGlow].Blue	= 0.10;
		this->CountGlow++;
		//case ITEM(2,20):Sep Scepter cl.r = 0.90f; cl.g = 0.50f; cl.b = 0.20f; OldGlow = false; break;
		this->iGlow[this->CountGlow].Type	= 2;
		this->iGlow[this->CountGlow].Index	= 20;
		this->iGlow[this->CountGlow].Red	= 0.90;
		this->iGlow[this->CountGlow].Green	= 0.50;
		this->iGlow[this->CountGlow].Blue	= 0.20;
		this->CountGlow++;
		//case ITEM(6,30):Embisyeon Shield cl.r = 0.90f; cl.g = 0.50f; cl.b = 0.20f; OldGlow = false; break;
		this->iGlow[this->CountGlow].Type	= 6;
		this->iGlow[this->CountGlow].Index	= 30;
		this->iGlow[this->CountGlow].Red	= 0.90;
		this->iGlow[this->CountGlow].Green	= 0.50;
		this->iGlow[this->CountGlow].Blue	= 0.20;
		this->CountGlow++;
		//case ITEM(5,41):Spirit Stick cl.r = 0.10f; cl.g = 0.30f; cl.b = 0.50f; OldGlow = false; break;
		this->iGlow[this->CountGlow].Type	= 5;
		this->iGlow[this->CountGlow].Index	= 42;
		this->iGlow[this->CountGlow].Red	= 0.10;
		this->iGlow[this->CountGlow].Green	= 0.30;
		this->iGlow[this->CountGlow].Blue	= 0.50;
		this->CountGlow++;
#endif
	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if(Flag == 1)
		{
			char mes[3][50];
			int n[2];
			sscanf(Buff, "%d %d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"", &n[0], &n[1], &mes[0], &mes[1], &mes[2]);
			this->Item[this->CountItem].Type			= n[0];
			this->Item[this->CountItem].Index			= n[1];
			sprintf(this->Item[this->CountItem].BMD,"%s",mes[0]);
			sprintf(this->Item[this->CountItem].Dir1,"%s",mes[1]);
			sprintf(this->Item[this->CountItem].Dir2,"%s",mes[2]);
			this->CountItem++;
		}

		if(Flag == 2)
		{
			int n[2];
			float c[3];
			sscanf(Buff, "%d %d %f %f %f", &n[0], &n[1], &c[0], &c[1], &c[2]);
			this->iGlow[this->CountGlow].Type	= n[0];
			this->iGlow[this->CountGlow].Index	= n[1];
			this->iGlow[this->CountGlow].Red	= c[0];
			this->iGlow[this->CountGlow].Green	= c[1];
			this->iGlow[this->CountGlow].Blue	= c[2];
			this->CountGlow++;
		}
	}
		
	fclose(file);
}

void cConfig::Test()
{
	int Test1, Test2;

	g_EncDec.GetBuffer(DIR_CONFIGS);

	char* pWinTitle = (char*)&g_EncDec.m_PackBuff;

	gConsole.Output(cGREEN, "0x%2X", (DWORD)pWinTitle);
	//Sleep(1000);

	Test1 = GetPrivateProfileIntA("ExTeam", "Gens", 50,  &*(char*)pWinTitle);
	Test2 = GetPrivateProfileIntA("ExTeam", "FontSize1", 50,  pWinTitle);

	gConsole.Output(cGREEN, "%d %d", Test1, Test2);
	//Sleep(1000);

	g_EncDec.ClearBuffer();
}