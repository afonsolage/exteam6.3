#pragma once

#define DIR_CONFIGS		"Data/Custom/Configs/Common.ini"
#define GAMEINFO_DIR	"Data/Custom/Configs/Util/Game.ex"
#define CONNECT_IP_DIR	"Data/Custom/Configs/Util/Connect.ex"
#define ITEM_LOAD_DIR	"Data/Custom/Configs/LoadItems.ini"
#define CONNECT_IP_DIR2	".\\Data\\Custom\\Configs\\Util\\Connect.ex"
#define GAMEBUFFER		"%d %d %d %d"

#define MAX_ITEM_LOAD	1000

extern bool gGENS;
extern bool gGRANDRESET;
extern bool gJEWELSBANK;
extern bool gRAGESYSTEM;
extern bool gWINQUEST;
extern bool gMONSTER_QUEST_SYSTEM;
extern bool gPARTY_SYSTEM;
extern DWORD gHelperLevel;
extern int iMonsterHPBar;
extern int iUserHpBar;
extern int iPartyHpBar;
extern int interCustom;
extern bool bAntiHack;
extern bool gAutoLogin;
extern bool gFogEffect;
extern int g_MaxCharacter;
extern BYTE g_MaxPartyMember;

extern char gWindowTitle[50];
extern bool gMultiLang;
extern bool gFontEnable;
extern char gFontName[5][20];
extern int gFontSize[5];

extern bool gGlowEffect;
extern bool gCheckCloseWindow;
extern DWORD g_dwDivFireScreamSpeed;
extern bool gMiniMap;
extern bool gAutoMouseKey;
extern bool gMuHelperInventory;

extern bool gDamageTable;
extern bool gAdvanceStats;

struct LoadItem_DATA
{
	int Type;
	int Index;
	char BMD[50];
	char Dir1[50];
	char Dir2[50];
};

struct GlowItem_DATA
{
	int Type;
	int Index;
	float Red;
	float Green;
	float Blue;
};

class cConfig
{
public:
	void Configs();
	void Encode(char* buffer, int size);
	void SaveGame();
	void LoadGame();
	void ReedConnect();
	void ItemLoad();
	void Test();

	char MyIp[16];
	int  LauncherActive;
	char LauncherParameters[20];

	int CountItem;
	int CountGlow;
	LoadItem_DATA Item[MAX_ITEM_LOAD];
	GlowItem_DATA iGlow[MAX_ITEM_LOAD];


};

extern cConfig gConfig;

