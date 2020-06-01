#include "stdafx.h"
#include "Interface.h"
#include "Defines.h"
#include "TMemory.h"
#include "RageSystem.h"
#include "User.h"
#include "ConnectEx.h"
#include "DrawTime.h"
#include "HpBar.h"
#include "JewelsBank.h"
#include "NewHpBar.h"
#include "Graphics.h"
#include "QuestSystem.h"
#include "Console.h"
//#include "ExMenu.h"
#include "Configs.h"
#include "AutoParty.h"
#include "Ranking.h"
#include "Ranking.h"
#include "EventTimer.h"
#include "MonsterQuest.h"
#include "Controller.h"
#include "NewPartyBuff.h"
#include "NewParty.h"
#include "PartySearch.h"
#include "PersonalShopEx.h"
#ifdef ACHIEVEMENTS_SYSTEM
#include "AchievementsSystem.h"
#endif // ACHIEVEMENTS_SYSTEM
#include "NewsBoard.h"
#include "BufferSystem.h"
#include "Smithy.h"
#include "OfflineMode.h"
#include "Marriage.h"
#include "AddPoints.h"
#include "CustomMenu.h"
#include "ResetSystem.h"
#include "DonateShop.h"
#include "DungeonSiege.h"
#include "ExLicense.h"
#include "TeamVsTeam.h"
#include "MiniMenu.h"
#include "Achievements.h"
#include "ExTeleport.h"
#include "PremiumSystemEx.h"
#include "ExTeleportEvo.h"
#include "PKClear.h"
#include "AccountSecurity.h"
#include "ReferralSystem.h"
#include "PostItem.h"
#include "ExWinQuestSystem.h"
#include "Item.h"
#include "PickUpItemInfo.h"
#include "DeBug.h"
#include "Lottery.h"
#include "UserShop.h"
#include "Fps.h"
#include "ExMenuV3.h"
#include "ItemMarket.h"
#include "StatsAdvance.h"
#include "Settings.h"

#include "Inter3.h"
#include "InterEx.h"
#include "CustomInterfaceMenu.h"
#include "TrayMode.h"
#include "MUHelperOffline.h"

#define pCursorDraw            ((int(__cdecl*)()) 0x5BB0B0)
#define sub_637C60				((int(__cdecl*)(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)) 0x637C60)
#define sub_42CFE0            ((int(*)(int a1)) 0x42CFE0)

void  pNewDrawGUI(int a1, float a2, float a3, float a4, float a5)
{
	DWORD* v5; // ST3C_4@1
	float v6; // ST40_4@1
	float v7; // ST48_4@1
	float v8; // ST44_4@1
	float v9; // ST38_4@1
	float v10; // ST34_4@1
	float v11; // ST30_4@1

	//*v5 = sub_42CFE0(a1);
	//v6 = 0.5 / *(float *)(v5 + 260);
	//v7 = 0.5 / *(float *)(v5 + 264);
	//v8 = (a4 - 0.5) / *(float *)(v5 + 260);
	//v9 = (a5 - 0.5) / *(float *)(v5 + 264);
	v10 = v9 - v7;
	v11 = v8 - v6;
	//sub_637C60(a1, a2, a3, a4, a5, v6, v7, v11, v10, 1, 1, 0.0);

	sub_637C60(a1, a2, a4, a4, a5, 0.0, 0.0,/* */1.0, 1.0, 1, 1, 0.0);
}


int __cdecl sub_5BB0B0()
{
	//gConsole.Output(cGREEN,__FUNCTION__);

	if (pSetCursorFocus == true &&
		gController.wMouse == WM_LBUTTONDOWN &&
		gInterface.Data[eMQUEST_MAIN].OnShow)
	{
		float v0 = pCursorY - 2.0;
		float v1 = pCursorX - 2.0;
		int result = sub_637C60(30013, v1, v0, 24.0, 24.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		return result;
	}


	return pCursorDraw();
}

//-----
//#define DEBUG_X_Y_DRAW			2
#ifdef DEBUG_X_Y_DRAW
#define sub_637C60				((void(__cdecl*)(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)) 0x637C60)
//void __cdecl sub_637C60 ((void(__cdecl*)int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12))0x637C60)

void Crack_sub_637C60(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	if (a1 == 0x787E)
	{
		a10 = 0;
		a11 = 0;
	}
	sub_637C60(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}

#endif

static DWORD InterfaceBuffer;

Interface gInterface;

Naked(MainKeyEsc)
{
	if (gInterface.CloseWindowsExAll())
	{
		_asm
		{
			MOV InterfaceBuffer, 0x007D3440
			JMP InterfaceBuffer
		}
	}

	_asm
	{
		MOV InterfaceBuffer, 0x008248E0
		CALL InterfaceBuffer

		MOV InterfaceBuffer, 0x007D3363
		JMP InterfaceBuffer
	}
}

int cHeight = 14;

static HFONT FontRet1()
{
	if (!strcmp(gFontName[0], "0"))
	{
		return CreateFont(gFontSize[0], 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, NULL);
	}

	return CreateFont(gFontSize[0], 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, gFontName[0]);	//Gulim
}

static HFONT FontRet2()
{
	if (!strcmp(gFontName[1], "0"))
	{
		return CreateFont(gFontSize[1], 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, NULL);
	}

	return CreateFont(gFontSize[1], 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, gFontName[1]);
}

static HFONT FontRet3()
{
	if (!strcmp(gFontName[2], "0"))
	{
		return CreateFont(gFontSize[2], 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, NULL);
	}

	return CreateFont(gFontSize[2], 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, gFontName[2]);
}

static HFONT FontRet4()
{
	if (!strcmp(gFontName[3], "0"))
	{
		return CreateFont(gFontSize[3], 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, NULL);
	}

	return CreateFont(gFontSize[3], 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, gFontName[3]);	//text.bmd?
}

static HFONT FontRet5()
{
	if (!strcmp(gFontName[4], "0"))
	{
		return CreateFont(gFontSize[4], 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, NULL);
	}

	return CreateFont(gFontSize[4], 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, gFontName[4]);
}

Interface::Interface()
{
	ZeroMemory(this->Data, sizeof(this->Data));
	ZeroMemory(this->WindowEx, sizeof(this->WindowEx));
}

void __declspec(naked) Interface::NewLogoDraw()
{
	static DWORD _004DB060 = 0x004DB060;
	static float standartWhith = 1.87;
	static float standartHight = 1.87;

	glColor3f(1, 1, 1);

	if (pGameResolutionMode == 2)
	{
		pDrawGUFULL(0x9C40, 0, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 213, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 425, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 0, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 213, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 425, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}
	else if (pGameResolutionMode == 7)
	{

		pDrawGUFULL(0x9C40, 0, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 213, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 424, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 0, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 213, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 424, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}
	else if (pGameResolutionMode == 8)
	{
		pDrawGUFULL(0x9C40, 1 + 0, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 1 + 211, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 1 + 423, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 1 + 0, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 1 + 211, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 1 + 423, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}
	else if (pGameResolutionMode == 4)
	{
		pDrawGUFULL(0x9C40, 1 + 0, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 1 + 213, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 1 + 425, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 1 + 0, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 1 + 213, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 1 + 425, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}
	else if (pGameResolutionMode == 9)
	{
		pDrawGUFULL(0x9C40, 1 + 0, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 1 + 210, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 1 + 423, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 1 + 0, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 1 + 210, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 1 + 423, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}
	else if (pGameResolutionMode == 10)
	{
		pDrawGUFULL(0x9C40, 0, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 213, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 425, -1, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 0, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 213, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 425, 239, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}
	else if (pGameResolutionMode == 11)
	{
		pDrawGUFULL(0x9C40, 0, -2, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 213, -2, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 425, -2, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 0, 237, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 213, 237, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 425, 237, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}
	else if (pGameResolutionMode == 1)
	{
		pDrawGUFULL(0x9C40, 0, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 213, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 425, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 0, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 213, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 425, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}
	else
	{
		pDrawGUFULL(0x9C40, 0, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C41, 213, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C42, 425, 0, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

		pDrawGUFULL(0x9C43, 0, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C44, 213, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
		pDrawGUFULL(0x9C45, 425, 240, 640, 480, 0, 0, standartWhith, standartHight, 1, 1, 0.0);
	}

	//pDrawGUFULL(ex_MU_Logo, 50, 50, 622, 90, 0, 0, standartWhith, standartHight, 1, 1, 0.0);

	//pDrawGUI(ex_MU_Logo, 10, 30, 622, 90);

#if(NEW_INTEFACE==TRUE)
	//g_Interface.DrawFormat(eYellow, 580, 480, 100, 1, "ExTeam Project");
#endif

	//gInterface.DrawFormat(eGold, 100, 100, 210, 3, "WWWWWWWWWWWWWWWWWWWWWW");

	_asm
	{
		FLD DWORD PTR DS : [0x0E8CB18]
		MOV InterfaceBuffer, 0x004D7B18
		JMP InterfaceBuffer
	}
}

void Interface::BindObject(short ID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[ID].EventTick = 0;
	this->Data[ID].OnClick = false;
	this->Data[ID].OnShow = false;
	this->Data[ID].ModelID = ModelID;
	this->Data[ID].Width = Width;
	this->Data[ID].Height = Height;
	this->Data[ID].X = X;
	this->Data[ID].Y = Y;
	this->Data[ID].MaxX = X + Width;
	this->Data[ID].MaxY = Y + Height;
	this->Data[ID].Attribute = 0;
}

void Interface::LoadImages(char * Folder, int Code, int Arg3, int Arg4, int Arg5)
{
	pLoadImage(Folder, Code, Arg3, Arg4, Arg5, 0);
}

void Interface::LoadTga()
{
	gJewelsBank.JewelsBankImageLoad();
	TimeImageLoad();
#if(OLD_HP_BAR==1)
	HpBar.Load();
#endif
	//#if(exRAGESYSTEM)
	gRageSystem.LoadImages();
	//#endif
#ifdef NEW_HP_BAR
	gViewePortInfo.NewHpBarLoad();
#endif
#if(NEW_GLOW_EFFECT)
	if (gGlowEffect)
	{
		gGraphics.InitGraphics();
	}
#endif

	gQuestSystem.LoadTGA();

	//gExMenu.Load();
	gRanking.ImageLoad();
#ifdef ACHIEVEMENTS_SYSTEM
	gAchievementsSystem.ImageLoad();
#endif // ACHIEVEMENTS_SYSTEM
	gCustomMenuInterface.ImageLoad();
	gEventTimer.Load();

#if(CUSTOM_PARTY_SEARCH==TRUE)
	g_PartySearch.LoadImages();
#endif

#if(CUSTOM_PERONAL_EX==TRUE)
	g_PersonalShopEx.LoadImages();
#endif

#if(CUSTOM_NEWS==TRUE)
	pLoadImage("Custom\\Interface\\NewsBoard_Title.tga", ex_NEWS_TITLE, 0x2601, 0x2900, 1, 0);
#endif
#if(CUSTOM_SMITHY == TRUE)
	g_Smithy.LoadImg();
#endif

#if(CUSTOM_MARRIAGE)
	g_Marriage.LoadImages();
#endif
#if(CUSTOM_ADD_POINTS)
	g_AddPoints.ImageLoad();
#endif
#if(_NEW_PARTY_SYSTEM_==1 && ADD_PARTY_LEADER==1)
	g_Party.LoadIMG();
#endif
#if(INTERFACE_LOGIN_IMG || THINNAKORN_MAC || BASSREFLEXIVE || EPICMU)
	pLoadImage("ExData\\Interface\\Logo\\logo_01.jpg", 0x9C40, 0x2601, 0x2900, 1, 0);
	pLoadImage("ExData\\Interface\\Logo\\logo_02.jpg", 0x9C41, 0x2601, 0x2900, 1, 0);
	pLoadImage("ExData\\Interface\\Logo\\logo_03.jpg", 0x9C42, 0x2601, 0x2900, 1, 0);
	pLoadImage("ExData\\Interface\\Logo\\logo_04.jpg", 0x9C43, 0x2601, 0x2900, 1, 0);
	pLoadImage("ExData\\Interface\\Logo\\logo_05.jpg", 0x9C44, 0x2601, 0x2900, 1, 0);
	pLoadImage("ExData\\Interface\\Logo\\logo_06.jpg", 0x9C45, 0x2601, 0x2900, 1, 0);
#endif

	pLoadImage("Custom\\Interface\\TimeBar.tga", ex_LORA_BATTLE_SCORE, 0x2601, 0x2900, 1, 0);
#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.LoadImages();
#endif
#if(CUSTOM_EX_TELEPORT==TRUE)
	g_ExTeleport.LoadImages();
#endif
#if(CUSTOM_EX_TELEPORT_EVO==TRUE)
	//g_ExTeleportEvo.LoadImages();
#endif
#if(CUSTOM_PLAYERTITLE)
	pLoadImage("ExData\\Interface\\Title\\a.tga", ex_PLAYERTITLE_A, 0x2601, 0x2900, 1, 0);
#endif

#if(CUSTOM_REFERAL_SYSTEM)
	g_ReferralSystem.LoadFileImage();
#endif

#if(CUSTOM_AUTOHP)
	pLoadImage("Custom\\Interface\\ramka0.tga", ex_AUTOHP_OFF, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\ramka1.tga", ex_AUTOHP_ON, 0x2601, 0x2900, 1, 0);
#endif

	// Мини карта
	pLoadImage("Custom\\Maps\\PlayerPoint.jpg", ex_PLAYER_POINT, 0x2600, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\null.tga", ex_NULL_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Lorencia.tga", ex_LORENCIA_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Dungeon.tga", ex_DUNGEON_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Devias.tga", ex_DEVIAS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Noria.tga", ex_NORIA_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Losttower.tga", ex_LOSTTOWER_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Atlans.tga", ex_ATLANS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Tarkan.tga", ex_Tarkan_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Elbeland.tga", ex_Elbeland_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Icarus.tga", ex_ICARUS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\LandOfTrials.tga", ex_LANDOFTRIALS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Aida.tga", ex_AIDA_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Crywolf.tga", ex_CRYWOLF_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Kantru.tga", ex_KANTRU_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Kantru3.tga", ex_KANTRU3_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Barracks.tga", ex_BARRACKS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Calmness.tga", ex_CALMNESS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Raklion.tga", ex_RAKLION_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Vulcanus.tga", ex_VULCANUS_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Kalrutan.tga", ex_KALRUTAN_MAP, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Maps\\Kalrutan2.tga", ex_KALRUTAN2_MAP, 0x2601, 0x2900, 1, 0);
#if(CUSTOM_EX_QUEST_SYSTEM==TRUE)
	g_ExWinQuestSystem.ImageLoad();
#endif

#if(CUSTOM_LOTTERY)
	g_Lottery.LoadIMG();
#endif

#if(DEV_PLAYERSHOP)
	g_ItemMarket.LoadIMG();
#endif

	//pLoadImage("ExData\\Interface\\arrow.tga", ex_WAREHOUSE, 0x2601, 0x2900, 1, 0 );
	//pLoadImage("ExData\\Interface\\arrow1.tga", ex_WAREHOUSE1, 0x2601, 0x2900, 1, 0 );

#if(DEV_INTERFASE_SEASON3)
	if (interCustom == 1 || interCustom == 2 || interCustom == 3)
	{
		if (interCustom == 1)
		{
			pLoadImage("Custom\\Interface\\S3\\2Menu01.jpg", 31292, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		}
		if (interCustom == 2 || interCustom == 3)
		{
			pLoadImage("Custom\\Interface\\S3\\2Menu01_new.jpg", 31292, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		}
		//pLoadImage("[PG]Data\\Interface\\s3\\2Menu01_new.jpg", 31292, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		pLoadImage("Custom\\Interface\\S3\\2Menu02.jpg", 31293, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		pLoadImage("Custom\\Interface\\S3\\2Menu03_new.jpg", 31294, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		pLoadImage("Custom\\Interface\\S3\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0); //replace
		pLoadImage("Custom\\Interface\\S3\\2Menu_Red.jpg", 0x7A42, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		pLoadImage("Custom\\Interface\\S3\\2Menu_Green.jpg", 0x7A41, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		pLoadImage("Custom\\Interface\\S3\\2Menu_Blue.jpg", 0x7A40, GL_LINEAR, GL_CLAMP, 1, 0);//replace
		pLoadImage("Custom\\Interface\\S3\\2Menu04.tga", iDragonLeft, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\S3\\2Menu05.tga", iDragonRight, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\S3\\2Menu_Inventory.jpg", iNewInventory, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\S3\\2Menu_Character.jpg", iNewCharacter, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\S3\\2Menu_Party.jpg", iNewParty, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\S3\\2win_push.jpg", iNewWinpush, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\S3\\2menu01_new2.jpg", iNewFastMenu, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\S3\\2SkillBox.jpg", iNewSkillBox, GL_LINEAR, GL_CLAMP, 1, 0);
	}
#endif

#if(DEV_EXMENU_V3)
	g_ExMenuV3.LoadIMG();
#endif

#if(DEV_INTERFACE_EX700)
	//Interface Ex700
	pLoadImage("Interface\\GFx\\none.tga", 31292, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\none.tga", 0x7A48, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Main_IE.tga", 31293, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\none.tga", 31294, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\none.tga", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_skillbox.tga", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Main_I3.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Main_I2.tga", 31297, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Main_I1.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Main_I5.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Main_I4.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_skill.tga", 31308, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_skill2.tga", 31309, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_skill3.tga", 31311, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_command.tga", 31310, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_non_skill.tga", 31314, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_non_skill2.tga", 31315, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_non_skill3.tga", 31317, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\newui_non_command.tga", 31316, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Shop1.tga", 0x901, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Shop2.tga", 0x902, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Character1.tga", 0x903, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Character2.tga", 0x904, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Inventory1.tga", 0x905, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Inventory2.tga", 0x906, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Quest1.tga", 0x907, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Quest2.tga", 0x908, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Community1.tga", 0x909, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\Community2.tga", 0x910, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\System1.tga", 0x911, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Interface\\GFx\\Botones\\System2.tga", 0x912, GL_LINEAR, GL_CLAMP, 1, 0);
#endif	

#if(USERPANEL)
	pLoadImage("Custom\\Interface\\UsersPanel_BG.tga", ex_USERSPANELBG, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\UsersPanel.tga", ex_USERSPANEL_BUTTON, 0x2601, 0x2900, 1, 0);
#endif

	pLoadSomeForm();
}

#if(ENABLE_TEST)
void DrawUserBar()
{
	float fldefY = 432;
	float flWidth = 20;
	float flHigh = 16;
	float flTestX = 560;
	float flTestY = fldefY;

	pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	pDrawGUI(100059, flTestX + 1, flTestY + 1, flWidth, flHigh);

	flTestY += flHigh + 1;
	pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	pDrawGUI(100060, flTestX + 1, flTestY + 1, flWidth, flHigh);

	flTestX += flWidth;
	flTestY = fldefY;
	pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	pDrawGUI(100061, flTestX + 1, flTestY + 1, flWidth, flHigh);

	flTestY += flHigh + 1;
	pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	pDrawGUI(100062, flTestX + 1, flTestY + 1, flWidth, flHigh);

	// =====

	flTestX += flWidth;
	flTestY = fldefY;
	pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	pDrawGUI(100063, flTestX + 1, flTestY + 1, flWidth, flHigh);

	flTestY += flHigh + 1;
	pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	pDrawGUI(100064, flTestX + 1, flTestY + 1, flWidth, flHigh);

	flTestX += flWidth;
	flTestY = fldefY;
	pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	pDrawGUI(100065, flTestX + 1, flTestY + 1, flWidth, flHigh);

	flTestY += flHigh + 1;
	pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	pDrawGUI(100066, flTestX + 1, flTestY + 1, flWidth, flHigh);
}
#endif

#if(DEV_GUILDBANK)

struct PMSG_GUILD_BANK
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

void Interface::DrawGuildBank(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
	pDrawText(This, PosX, PosY, (char*)Text, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);

	if (!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!g_ExLicense.CheckUser(eExUB::Local) &&
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) &&
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::ProtectDebug))
	{
		return;
	}

	int iPosX = PosX;
	int iPosY = PosY;

	iPosX += 25;
	iPosY += 345;
	gInterface.DrawGUI(eGUILD_BANK_BT1, iPosX, iPosY);

	iPosX += 5;
	iPosY += 10;
	gInterface.DrawFormat(eYellow, iPosX, iPosY, 100, 3, "Guild Bank");
}

void Interface::EventGuildBank(DWORD Event)
{
	if (!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!g_ExLicense.CheckUser(eExUB::Local) &&
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) &&
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::ProtectDebug))
	{
		return;
	}

	if (!this->CheckWindow(ObjWindow::Guild))
	{
		return;
	}

	if (gInterface.ButtonEx(Event, eGUILD_BANK_BT1, false))
	{
		this->CloseWindow(ObjWindow::Guild);

		PMSG_GUILD_BANK pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xD8, sizeof(pMsg));
		pMsg.Result = 1;
		gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
	}
}

#endif

void Interface::DrawWarehouseHook(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
	pDrawText(This, PosX, PosY, (char*)Text, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);

	if (!g_ExLicense.CheckUser(eExUB::MedoniAndrei) && !g_ExLicense.CheckUser(eExUB::Local) && !g_ExLicense.CheckUser(eExUB::ProtectDebug) &&
		!g_ExLicense.CheckUser(eExUB::Gredy) && !g_ExLicense.CheckUser(eExUB::GredyLocal) && !g_ExLicense.CheckUser(eExUB::Gredy2) &&
		!g_ExLicense.CheckUser(eExUB::Artem) && !g_ExLicense.CheckUser(eExUB::Artem2) && !g_ExLicense.CheckUser(eExUB::NSGames))
	{
		return;
	}

	PosX += 45;
	PosY += 335;

	gInterface.DrawGUI(eWAREHOUSE, PosX, PosY);
	gInterface.DrawGUI(eWAREHOUSE1, PosX + 45, PosY);
	gInterface.DrawFormat(eWhite, PosX + 25, PosY + 4, 10, 1, "%d/5", gObjUser.WarehouseNumber + 1);
	// ----
	if (gInterface.IsWorkZone(eWAREHOUSE))
	{
		if (gInterface.Data[eWAREHOUSE].OnClick)
		{
			gInterface.DrawColoredGUI(eWAREHOUSE, PosX, PosY, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		gInterface.DrawColoredGUI(eWAREHOUSE, PosX, PosY, pMakeColor(255, 204, 20, 200));
	}
	else if (gInterface.IsWorkZone(eWAREHOUSE1))
	{
		if (gInterface.Data[eWAREHOUSE1].OnClick)
		{
			gInterface.DrawColoredGUI(eWAREHOUSE1, PosX + 45, PosY, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		gInterface.DrawColoredGUI(eWAREHOUSE1, PosX + 45, PosY, pMakeColor(255, 204, 20, 200));
	}
}

void Interface::Load()
{
	this->m_GameDraw = false;
#if(DEV_GUILDBANK)
	gInterface.BindObject(eGUILD_BANK_BT1, 0x7A5E, 108, 29, -1, -1);
	SetOp((LPVOID)0x007CB9F9, this->DrawGuildBank, ASM::CALL);
#endif

#if(DEV_STORAGE)
	SetOp((LPVOID)0x00857A45, this->DrawWarehouseHook, ASM::CALL);
	//SetRange((LPVOID)0x00857B1C, 5, ASM::NOP);
#endif


#if(ENABLE_TEST)
	SetOp((LPVOID)0x0080F70D, DrawUserBar, ASM::CALL);
#endif

	for (int i = 0; i < MAX_WINDOW_EX; i++)
	{
		this->WindowEx[i] = false;
	}

#if(CUSTOM_AUTOCTRL)
	this->m_bAutoCtrl = false;
#endif
	this->m_ActiveAutoHP = false;
	this->m_AutoHP = false;
	this->m_AutoHPTick = GetTickCount();

	TimeLoad();
	gJewelsBank.JewelsBankLoad();
	gQuestSystem.Init();

	//if(gMONSTER_QUEST_SYSTEM)
	{
		gMonsterQuest.InterfaceLoad();
	}



	//SetOp((LPVOID)oDrawLogoDraw_Call, this->LogoDraw, ASM::CALL);
	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);
	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadTga, ASM::CALL);

#ifdef DEBUG_X_Y_DRAW
	SetOp((LPVOID)0x00790ABD, Crack_sub_637C60, ASM::CALL);
#endif

	//SetOp((LPVOID)0x004D5EE6, sub_5BB0B0, ASM::CALL);
	//SetOp((LPVOID)0x004D9CDB, sub_5BB0B0, ASM::CALL);

	SetOp((LPVOID)0x004D5EE6, this->CursorDraw, ASM::CALL);
	SetOp((LPVOID)0x004D9CDB, this->CursorDraw, ASM::CALL);

#if(CUSTOM_PARTY_SEARCH==TRUE)
	g_PartySearch.BindImages();
#endif	
	//sub_5BB0B0()
#if(CUSTOM_PERONAL_EX==TRUE)
	g_PersonalShopEx.BindImages();
#endif

#if(CUSTOM_NEWS==TRUE)
	gInterface.BindObject(eNEWS_MAIN, 0x7A5A, 222, 303, -1, -1);
	gInterface.BindObject(eNEWS_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eNEWS_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eNEWS_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eNEWS_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eNEWS_INFOBG, ex_NEWS_TITLE, 170, 21, -1, -1);
	gInterface.BindObject(eNEWS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eNEWS_BACK, 0x7A5E, 108, 29, -1, -1);
#endif
#if(CUSTOM_NPC_BUFFER==TRUE)
	g_BufferSystem.BindImages();
#endif

#if(CUSTOM_SMITHY == TRUE)
	g_Smithy.BindImg();
#endif

#if(OFFLINE_MODE==TRUE)
	g_OfflineMode.BindImages();
#endif
#if(CUSTOM_MARRIAGE)
	g_Marriage.BindImages();
#endif
#if(CUSTOM_ADD_POINTS)
	g_AddPoints.BindImage();
#endif
#if(CUSTOM_MENU)
	g_CustomMenu.BindImages();
#endif
#if(CUSTOM_RESETSYSTEM)
	g_ResetSystem.BindImages();
#endif
#if(EVENT_DUNGEON_SIEGE)
	g_DungeonSiege.BindImages();
#endif
#if(INTERFACE_LOGIN_IMG || THINNAKORN_MAC || BASSREFLEXIVE || EPICMU)
	SetByte((LPVOID)(0x004D7A63), 0xEB);
	SetOp((LPVOID)0x004D7B12, (LPVOID)this->NewLogoDraw, ASM::JMP);
#endif
#if(EVENT_TEAM_VS_TEAM)
	g_TeamVsTeam.BindImage();
#endif
#if(CUSTOM_MINIMENU==TRUE)
	g_MiniMenu.BindImage();
#endif
#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.BindImages();
#endif
#if(CUSTOM_EX_TELEPORT==TRUE)
	g_ExTeleport.BindImages();
#endif
#if(CUSTOM_EX_TELEPORT_EVO==TRUE)
	g_ExTeleportEvo.BindImages();
#endif
#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
	g_PremiumSystemEx.BindImages();
#endif
#if(CUSTOM_PKCLEAR_NPC==TRUE)
	g_PKClear.BindImages();
#endif
#if(CUSTOM_ACCOUNT_SECURITY)
	g_AccountSecurity.BindImage();
#endif
#if(CUSTOM_REFERAL_SYSTEM)
	g_ReferralSystem.BindImages();
#endif
#if(CUSTOM_EX_QUEST_SYSTEM==TRUE)
	g_ExWinQuestSystem.BindImages();
#endif
	//Minimap
	this->BindObject(ePLAYER_POINT_1, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_2, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_3, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_4, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_5, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_6, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_7, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_8, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_9, ex_PLAYER_POINT, 3, 3, -1, -1);
	this->BindObject(ePLAYER_POINT_10, ex_PLAYER_POINT, 3, 3, -1, -1);

	this->BindObject(eNULL_MAP, ex_NULL_MAP, 128, 128, -1, -1);
	this->BindObject(eLORENCIA_MAP, ex_LORENCIA_MAP, 128, 128, -1, -1);
	this->BindObject(eDUNGEON_MAP, ex_DUNGEON_MAP, 128, 128, -1, -1);
	this->BindObject(eDEVIAS_MAP, ex_DEVIAS_MAP, 128, 128, -1, -1);
	this->BindObject(eNORIA_MAP, ex_NORIA_MAP, 128, 128, -1, -1);
	this->BindObject(eLOSTTOWER_MAP, ex_LOSTTOWER_MAP, 128, 128, -1, -1);
	this->BindObject(eATLANS_MAP, ex_ATLANS_MAP, 128, 128, -1, -1);
	this->BindObject(eTarkan_MAP, ex_Tarkan_MAP, 128, 128, -1, -1);
	this->BindObject(eElbeland_MAP, ex_Elbeland_MAP, 128, 128, -1, -1);
	this->BindObject(eICARUS_MAP, ex_ICARUS_MAP, 128, 128, -1, -1);
	this->BindObject(eLANDOFTRIALS_MAP, ex_LANDOFTRIALS_MAP, 128, 128, -1, -1);
	this->BindObject(eAIDA_MAP, ex_AIDA_MAP, 128, 128, -1, -1);
	this->BindObject(eCRYWOLF_MAP, ex_CRYWOLF_MAP, 128, 128, -1, -1);
	this->BindObject(eKANTRU_MAP, ex_KANTRU_MAP, 128, 128, -1, -1);
	this->BindObject(eKANTRU3_MAP, ex_KANTRU3_MAP, 128, 128, -1, -1);
	this->BindObject(eBARRACKS_MAP, ex_BARRACKS_MAP, 128, 128, -1, -1);
	this->BindObject(eCALMNESS_MAP, ex_CALMNESS_MAP, 128, 128, -1, -1);
	this->BindObject(eRAKLION_MAP, ex_RAKLION_MAP, 128, 128, -1, -1);
	this->BindObject(eVULCANUS_MAP, ex_VULCANUS_MAP, 128, 128, -1, -1);
	this->BindObject(eKALRUTAN_MAP, ex_KALRUTAN_MAP, 128, 128, -1, -1);
	this->BindObject(eKALRUTAN2_MAP, ex_KALRUTAN2_MAP, 128, 128, -1, -1);

	this->BindObject(eNEWS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eNEWS_BACK, 0x7A5E, 108, 29, -1, -1);

	this->BindObject(eAUTO_HP_ON, ex_AUTOHP_ON, 75, 17, -1, -1);
	this->BindObject(eAUTO_HP_OFF, ex_AUTOHP_OFF, 75, 17, -1, -1);

	//this->BindObject(eWAREHOUSE, ex_WAREHOUSE, 25, 11, -1, -1);	//325.5, 348);
	//this->BindObject(eWAREHOUSE1, ex_WAREHOUSE1, 25, 11, -1, -1);	//370.5, 348);

	this->BindObject(eWAREHOUSE, 0x7BAA, 17, 17, -1, -1);	//325.5, 348);
	this->BindObject(eWAREHOUSE1, 0x7BAB, 17, 17, -1, -1);	//370.5, 348);
	//this->BindObject(eOFFTRADE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eOFFTRADE_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eOFFTRADE_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eOFFTRADE_CHECK1, 0x7B69, 15, 15, -1, -1);

	SetRange((LPVOID)0x007D335E, 5, ASM::NOP);
	SetOp((LPVOID)0x007D335E, (LPVOID)MainKeyEsc, ASM::JMP);
#if(EPICMU)
	SetRange((LPVOID)0x004D7C98, 5, ASM::NOP);
	SetRange((LPVOID)0x004D7C0D, 5, ASM::NOP);
#endif

	SetOp((LPVOID)oAllowGUI_Call1, this->AllowGUI, ASM::CALL);
	SetOp((LPVOID)oAllowGUI_Call2, this->AllowGUI, ASM::CALL);

	//#if(LANG_CHINA)
	if (gMultiLang)
	{
		SetByte((LPVOID)0x004215A7, 0xEB);	//[0-9A-Za-z] Name
		SetByte((LPVOID)(0x00507AEA + 1), 0x72); //can not use symbol
		SetByte((LPVOID)(0x00958BCC + 3), 0xA8);	//1 Codepage utf
		SetByte((LPVOID)(0x00958BCC + 4), 0x03);	//2	Codepage utf

		SetByte((LPVOID)0x00507AFD, 0xEB);	//[0-9A-Za-z] Guild
	}
	//#endif

	if (gFontEnable)
	{
		DWORD OffSetCall = 0x004060D0;	//1
		SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
		SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet1, ASM::CALL);

		OffSetCall = 0x004D2882;	//2
		SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
		SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet2, ASM::CALL);

		OffSetCall = 0x004D28EB;	//3
		SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
		SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet3, ASM::CALL);

		OffSetCall = 0x004D2957;	//4
		SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
		SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet4, ASM::CALL);

		OffSetCall = 0x004D29C1;	//5
		SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
		SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet5, ASM::CALL);
	}

#if(CUSTOM_LOTTERY)
	g_Lottery.BindIMG();
#endif

#if(DEV_INTERFASE_SEASON3)
	if (interCustom == 1 || interCustom == 2 || interCustom == 3)
	{
		this->BindObject(eSkillBox, iNewSkillBox, 32, 38, 305, 443);
		this->BindObject(eDragonLeft, iDragonLeft, 108, 45, 0, 388);
		this->BindObject(eDragonRight, iDragonRight, 108, 45, 532, 388);
		this->BindObject(eParty, iNewParty, 25, 25, 348, 449);
		this->BindObject(eCharacter, iNewCharacter, 25, 25, 379, 449);
		this->BindObject(eInventory, iNewInventory, 25, 25, 409, 449);
		//	this->BindObject(eCashShop, iNewCashShop, 25, 25, 439, 449);
		this->BindObject(eFriend, iNewWinpush, 54, 20, 581, 432);
		this->BindObject(eGuild, iNewGuild, 54, 20, 581, 449);
		this->BindObject(eFastMenu, iNewFastMenu, 55, 21, 5, 432);
	}
#endif

#if(DEV_EXMENU_V3)
	g_ExMenuV3.Bind();
#endif	

#if(DEV_PLAYERSHOP)
	g_ItemMarket.Bind();
#endif

#if(DEV_STATS_ADVANCE)
	g_StatsAdvance.Bind();
#endif

#if(DEV_PLAYERINFO)
	this->m_EnableDrawTargetInfo = false;
#endif

#if(DEV_DAMAGE_TABLE)
	this->m_EnableDamageTable = false;
#endif

#if(DEV_INTERFACE_EX700)
	this->BindObject(eMainEx700, 31293, 960, 160, 50, 388);
	this->BindObject(eShop1, 0x901, 17, 17, 76.5, 452);
	this->BindObject(eShop2, 0x902, 17, 17, 76.5, 452);
	this->BindObject(eCharacter1, 0x903, 17, 17, 98.5, 452);
	this->BindObject(eCharacter2, 0x904, 17, 17, 98.5, 452);
	this->BindObject(eInventory1, 0x905, 17, 17, 120.5, 452);
	this->BindObject(eInventory2, 0x906, 17, 17, 120.5, 452);
	this->BindObject(eQuest1, 0x907, 17, 17, 503.5, 452);
	this->BindObject(eQuest2, 0x908, 17, 17, 503.5, 452);
	this->BindObject(eCommunity1, 0x909, 17, 17, 525.5, 452);
	this->BindObject(eCommunity2, 0x910, 17, 17, 525.5, 452);
	this->BindObject(eSystem1, 0x911, 17, 17, 547.5, 452);
	this->BindObject(eSystem2, 0x912, 17, 17, 547.5, 452);

	InitInterEx();
#endif

#if(USERPANEL)
	//this->BindObject(eUSERSPANELBG, ex_USERSPANELBG, 37, 18, 173, 0);
	//this->BindObject(eUSERSPANEL_BUTTON, ex_USERSPANEL_BUTTON, 16, 12, 175.5, 1);
	this->BindObject(eUSERSPANELBG, ex_USERSPANELBG, 37, 18, 173, 0);
	this->BindObject(eUSERSPANEL_BUTTON, ex_USERSPANEL_BUTTON, 40, 12, 175.5, 1);
#endif
}

void Interface::LogoDraw()
{
	//gInterface.DrawFormat(eGold, 100, 100, 210, 3, "WWWWWWWWWWWWWWWWWWWWWW");
	pDrawLogoDraw();


}

bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}

void Interface::DrawGUI(short ObjectID)
{
	pDrawGUI(this->Data[ObjectID].ModelID, this->Data[ObjectID].X, this->Data[ObjectID].Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);

	this->m_iDrawObjectID = ObjectID;
}

void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	//if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}

	//if(ObjectID >= eLORENCIA_MAP && eKALRUTAN2_MAP >= ObjectID)
	//{
	//	float flX = GAME_X_IN_FULL_X(PosX);
	//	float flY = GAME_Y_IN_FULL_Y(PosY);
	//	static float standartWhith = 0.5;
	//	static float standartHight = 0.5;
	//	pDrawGUFULL(this->Data[ObjectID].ModelID, flX, flY, this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, standartWhith, standartHight, 0, 0, 0.0);
	//	return;
	//}


	// ----
	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);

	this->m_iDrawObjectID = ObjectID;
}

void Interface::DrawColoredGUI(short ObjectID, DWORD Color)
{
	pDrawColorButton(this->Data[ObjectID].ModelID, this->Data[ObjectID].X, this->Data[ObjectID].Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawColoredGUIObj(short ObjectID, float X, float Y, DWORD Color)
{
	//if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X = X;
		this->Data[ObjectID].Y = Y;
		this->Data[ObjectID].MaxX = X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = Y + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawColorGUI(int MainID, int X, int Y, int Width, int Height, DWORD Color)
{
	pDrawColorButton(MainID, X, Y, Width, Height, 0, 0, Color);
}

int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
#if(ENABLE_CHANGE)
	Text = g_Text.Change(Text);
#endif

	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	int LineCount = 0;
	// ----
	char * Line = strtok(Buff, "\n");
	// ----
	while (Line != NULL)
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
	// ----
	return PosY;
}

void Interface::DrawFormatEx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
#if(ENABLE_CHANGE)
	Text = g_Text.Change(Text);
#endif
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	pDrawColorText(Buff, PosX, PosY, Width, 0, Color, 0, Align);
}

int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
#if(ENABLE_CHANGE)
	Text = g_Text.Change(Text);
#endif
	char Buff[2048];
	int BuffLen = sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	return pDrawToolTip(X, Y, Buff);
}
// ----------------------------------------------------------------------------------------------

int Interface::DrawToolTipEx(int X, int Y, LPCSTR Text, ...)
{
#if(ENABLE_CHANGE)
	Text = g_Text.Change(Text);
#endif
	char Buff[2048];
	int BuffLen = sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	int LineCount = 0;
	// ----
	char * Line = strtok(Buff, "\n");
	// ----
	while (Line != NULL)
	{
		pDrawToolTip(X, Y, Line);
		Y += 10;
		Line = strtok(NULL, "\n");
	}
	// ----
	return Y;
}

bool Interface::IsWorkZone(float X, float Y, float MaxX, float MaxY)
{
	if ((pCursorX < X || pCursorX > MaxX)
		|| (pCursorY < Y || pCursorY > MaxY))
	{
		return false;
	}
	// ----
	return true;
}

bool Interface::IsWorkZoneObj(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;
	// ----
	//if( ObjectID == eSAMPLEBUTTON 
	//	|| ObjectID == eCAMERA_MAIN 
	//	|| ObjectID == eCAMERA_BUTTON1
	//	|| ObjectID == eCAMERA_BUTTON2 )
	//{
	//	PosX = this->GetResizeX(ObjectID);
	//	MaxX = PosX + this->Data[ObjectID].Width;
	//}

	if ((gObjUser.m_CursorX < PosX || gObjUser.m_CursorX > MaxX)
		|| (gObjUser.m_CursorY < this->Data[ObjectID].Y || gObjUser.m_CursorY > this->Data[ObjectID].MaxY))
	{
		return false;
	}

	// ----
	//if( (pCursorX < PosX || pCursorX > MaxX) 
	//	|| (pCursorY < this->Data[ObjectID].Y || pCursorY > this->Data[ObjectID].MaxY) )
	//{
	//	//gConsole.Output(cGREEN,__FUNCTION__);
	//	return false;
	//}
	// ----
	return true;
}

float Interface::DrawRepeatGUI(short MonsterID, float X, float Y, int Count)
{
	float StartY = Y;
	// ----
	for (int i = 0; i < Count; i++)
	{
		pDrawGUI(this->Data[MonsterID].ModelID, X, StartY,
			this->Data[MonsterID].Width, this->Data[MonsterID].Height);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

bool Interface::RightWindows()
{
	//FriendList		= 1,
	//MoveList		= 2,
	//Party			= 3,
	//Guild			= 6,
	//Trade			= 7,
	//Warehouse		= 8,
	//ChaosBox		= 9,
	//CommandWindow	= 10,
	//PetInfo			= 11,
	//Shop			= 12,
	//Inventory		= 13,
	//Store			= 14,
	//OtherStore		= 15,
	//Character		= 16,
	//ChatWindow		= 33,
	//FastMenu		= 34,
	//Options			= 35,
	//Help			= 36,
	//FastDial		= 39,
	//SkillTree		= 57,
	//NPC_Titus		= 63,
	//CashShop		= 65,
	//FullMap			= 72,
	//NPC_Dialog		= 73,
	//GensInfo		= 74,
	//NPC_Julia		= 75,
	//ExpandInventory	= 77,
	//ExpandWarehouse	= 78,

	if ( //this->CheckWindow(ObjWindow::Party) || 
		//this->CheckWindow(ObjWindow::Guild) ||
		this->CheckWindow(ObjWindow::FullMap) ||
		//this->CheckWindow(ObjWindow::Trade) ||
		//this->CheckWindow(ObjWindow::Warehouse) ||
		this->CheckWindow(ObjWindow::CommandWindow) ||
		this->CheckWindow(ObjWindow::Shop) ||
		this->CheckWindow(ObjWindow::Inventory) ||
		//this->CheckWindow(ObjWindow::Store) ||
		//this->CheckWindow(ObjWindow::OtherStore) ||
		//this->CheckWindow(ObjWindow::Character) ||
		this->CheckWindow(ObjWindow::SkillTree) ||
		//	this->CheckWindow(ObjWindow::NPC_Titus) ||
		this->CheckWindow(ObjWindow::CashShop) ||
		//	this->CheckWindow(ObjWindow::NPC_Dialog) ||
		//	this->CheckWindow(ObjWindow::GensInfo) ||
		//	this->CheckWindow(ObjWindow::NPC_Julia) ||
			//this->CheckWindow(ObjWindow::ExpandInventory) ||
		this->CheckWindow(ObjWindow::ExpandWarehouse) ||
		this->CheckWindow(ObjWindow::SkillTree) ||
		this->CheckWindow(ObjWindow::FastMenu) /* ||*/
	//this->CheckWindow(ObjWindow::Helper) 
	//this->CheckWindow(64)
		)
	{
		return false;
	}
	return true;
}

int Interface::OpenWindow(int WindowID)
{
	return pOpenWindow(pWindowThis(), WindowID);
}

int Interface::CloseWindow(int WindowID)
{
	return pCloseWindow(pWindowThis(), WindowID);
}

// ----------------------------------------------------------------------------------------------

void Interface::Work()
{
	gTrayMode.Work();

	gInterface.RightMiniInfoY = 430;

	if (gInterface.CheckWindow(ExpandWarehouse))
	{
		pSetCursorFocus = true;
		//gConsole.Output(cGREEN, "true");
	}
	else
	{
		pSetCursorFocus = false;
		//gConsole.Output(cGREEN, "false");
	}

	//system("cls");
	for (int i = 0; i < pPartyMemberCount; ++i)
	{
		//	*(DWORD*)(0x81CB504 + 8 * i) = g_NewPartyList[i].ViewportID;
		//	*(BYTE*)(0x81CB500 + 32 * i) = g_NewPartyList[i].LifePercent;
			//*(BYTE*)(0x81CB500 + 32 * i) = g_NewPartyList[i].LifePercent;
			//byte_81CB500[32 * alpha]

			//gConsole.Output(cGREEN, "0x81CB504: %d | ViewportID: %d",*(DWORD*)(0x81CB504 + 8 * i), g_NewPartyList[i].ViewportID);
	}
	//pDrawGUI(31558, 50, 50, 50, 50);


	//gConsole.Output(cGREEN, "NameID: %d",SearchVieweID("DangeR"));


	for (int i = 0; i < MAX_USER_IN_PARTY; i++)
	{
		//gConsole.Output(cGREEN, "[%s] LifePercent: %d  ViewportID: %d Unknown: %d",g_NewPartyList[i].Name, g_NewPartyList[i].LifePercent, g_NewPartyList[i].ViewportID, g_NewPartyList[i].gap01);






		//PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * i);

		//int v34 = (int)((char *)(0x081CB4E8 + 32 * i));

		//gConsole.Output(cGREEN, "[%s] LifePercent: %d  ViewportID: %d Unknown: %d",PartyMember.Name, PartyMember.ViewportID, PartyMember.gap01);
	}
	//if( pSetCursorFocus == true && 
	//	gController.wMouse == WM_LBUTTONDOWN &&
	//	gInterface.Data[eMQUEST_MAIN].OnShow )
	//{
	//	pDrawGUI(0x753D, pCursorX, pCursorY,50, 50);
	//}

	for (int i = 0; i < 5; i++)
	{


		float X = 100;
		float Y = 50 + 23.0 * i;

		//pDrawGUI(31557, X, Y, 77.0, 23.0);

		//formula

		float wh = 77.0;
		float hg = 23.0;

		//float _WH = 1024 * wh / 800.0;// = 16	//98,56

		//float _WH =	800.0 * wh / 1024;// 1024 * wh / 800.0;
		//float _HG =	600.0 * hg / 1024;

		float _WH = wh;//( 640 * wh ) / pWinWidth;// 1024 * wh / 800.0;
		float _HG = hg; //( 480 * hg ) / pWinHeight;

		//float _WH =	( 800 * wh ) / pWinWidth;// 1024 * wh / 800.0;
		//float _HG = ( 600 * hg ) / pWinHeight;


		//pNewDrawGUI(31557, X, Y, _WH, _HG);
	}
#if _NEW_PARTY_SYSTEM_ == TRUE
	g_Party.PartyVieweID();
#endif	

#if NEW_PARTY_BUFF == TRUE
	g_NewPartyBuff.DrawBuff();
#endif

	g_MUHelperOffline.Tick();

	//gExMenu.Draw();
#if(USERPANEL)
	//gInterface.DrawUsersPanel();
#endif

#if(CUSTOM_REFERAL_SYSTEM)
	g_ReferralSystem.DrawMain();
#endif

	gObjUser.Refresh();
#if OLD_HP_BAR == 1
	HpBar.Draw();
#endif


#if(exRECONNECT)
	gConnectEx.Run();
#endif



	DrawTime();

	gInterface.DrawMiniMap();


	if (gWINQUEST) gQuestSystem.Draw();



	gJewelsBank.JewelsBankDraw();


#ifdef AUTO_PARTY
	gAutoParty.Work();
#endif

	gEventTimer.Draw();

	if (gRAGESYSTEM)
	{
		gRageSystem.rDrawInterface();
	}

	gRanking.Draw();

#ifdef ACHIEVEMENTS_SYSTEM
	gAchievementsSystem.Draw();
#endif // ACHIEVEMENTS_SYSTEM
	gCustomMenuInterface.Draw();
	if (gMONSTER_QUEST_SYSTEM)
	{
		gMonsterQuest.DrawMainTable();
	}

#if(CUSTOM_PARTY_SEARCH==TRUE)
	g_PartySearch.DrawMaster();
	g_PartySearch.DrawUser();
#endif

#if(CUSTOM_PERONAL_EX==TRUE)
	g_PersonalShopEx.Draw();
	g_PersonalShopEx.DrawPrice();
#endif
#if(CUSTOM_NEWS==TRUE)
	g_NewsBoard.DrawNewsWindow();
#endif
#if(CUSTOM_NPC_BUFFER==TRUE)
	g_BufferSystem.Draw();
#endif
#if(CUSTOM_SMITHY == TRUE)
	g_Smithy.Draw();
#endif
#if(OFFLINE_MODE==TRUE)
	g_OfflineMode.Draw();
#endif
#if(CUSTOM_MARRIAGE)
	g_Marriage.Draw();
#endif
#if(CUSTOM_ADD_POINTS==TRUE)
	g_AddPoints.Draw();
	g_AddPoints.CharInfoDraw();
#endif
#if(CUSTOM_MENU)
	g_CustomMenu.DrawMain();
#endif

#if(CUSTOM_RESETSYSTEM)
	g_ResetSystem.DrawReset();
	//g_ResetSystem.DrawGrand();
#endif

#if(DONATE_SHOP==TRUE)
	g_DonateShop.ShopButtonDraw();
#endif
#if(EVENT_DUNGEON_SIEGE)
	g_DungeonSiege.Draw();
#endif
#if(EVENT_TEAM_VS_TEAM)
	g_TeamVsTeam.DrawMain();
#endif

	gInterface.DrawRightMiniInfoMapQuest();
#if(CUSTOM_MINIMENU==TRUE)
	g_MiniMenu.Draw();
#endif
#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.Draw();
#endif
#if(CUSTOM_EX_TELEPORT==TRUE)
	g_ExTeleport.Draw();
#endif
#if(CUSTOM_EX_TELEPORT_EVO==TRUE)
	g_ExTeleportEvo.Draw();
#endif
#if(CUSTOM_AUTOCTRL)
	gInterface.DrawAutoCtrl();
#endif
#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
	g_PremiumSystemEx.DrawWindow();
#endif
#if(CUSTOM_PKCLEAR_NPC==TRUE)
	g_PKClear.Draw();
#endif
#if(CUSTOM_ACCOUNT_SECURITY)
	g_AccountSecurity.DrawMain();
#endif
#if(CUSTOM_REFERAL_SYSTEM)
	//g_ReferralSystem.DrawMain();
#endif
	gInterface.DrawAutoHPClick();
#if(CUSTOM_EX_QUEST_SYSTEM==TRUE)
	g_ExWinQuestSystem.Draw();
	g_ExWinQuestSystem.DrawMiniInfo();
#endif	


#if(CUSTOM_PICKUP_ITEM_INFO)
	g_PickUpItemInfo.InfoSend();
#endif

	//gInterface.DrawWarehouseUI();
	gInterface.DrawOffTrade();

#if(ENABLE_DEBUG)

	DeBug_DrawItemPos();

#endif

#if(CUSTOM_EMULATOR_KEY)

	gInterface.DrawAutoClickMouse();

#endif

#if(CUSTOM_LOTTERY)
	g_Lottery.DrawMain();
#endif

#if(DEV_USERSHOP)
	g_UserShop.Draw();;
#endif

	gInterface.DrawItemMarket();

#if(DEV_INTERFASE_SEASON3)
	if (interCustom == 1 || interCustom == 2 || interCustom == 3)
	{
		gInterface.DrawMenuButton();
		gInterface.DrawS2Interface();
	}
#endif

#if(DEBUG_FPS)
	g_Fps.Draw();
#endif

#if(DEV_EXMENU_V3)
	g_ExMenuV3.DrawMain();
#endif
#if(DEV_STATS_ADVANCE)
	g_StatsAdvance.DrawInfo();
#endif

#if(DEV_DAMAGE_TABLE)
	gInterface.DrawDamageTable();
#endif
#if(DEV_INTERFACE_EX700)
	//gInterface.DrawInterfaceEx700();
	gInterface.DrawMenuButton();
	gInterface.DrawInterfaceCustom();
#endif



	pDrawInterface();

#if(ENABLE_TEST)
	float flWidth = 20;
	float flHigh = 16;
	float flTestX = 600;
	float flTestY = 450;

	//pDrawGUI(100050, flTestX, flTestY, flWidth, flHigh);
	//pDrawGUI(100059, flTestX+1, flTestY+1, flWidth, flHigh);
#endif


}

bool Interface::AllowGUI()
{
	if (gInterface.CheckWindowEx(exWinDonateCheck))
	{
		return false;
	}
	// ----
	return pAllowGUI();
}

void Interface::OpenWindowEx(int WindowID)
{
	if (WindowID < 0 || WindowID > MAX_WINDOW_EX)
	{
		return;
	}
	//pSetCursorFocus = true;
#if(CUSTOM_PERONAL_EX==TRUE)
	if (WindowID == exWinPersonalPrice)
	{
		*(BYTE*)0xE8C5AC = 0;
	}
#endif
#if(CUSTOM_ACCOUNT_SECURITY)
	if (WindowID == exWinAccPC || WindowID == exWinAccNumber)
	{
		*(BYTE*)0xE8C5AC = 0;
	}
#endif
	if (WindowID == exWinMiniMenu)
	{
		sub_814FE0((char*)sub_861090(sub_860FC0()), 0, 1);
	}

	if (WindowID == ObjWindowsEx::exWinMiniMenu)
	{
		if (this->CheckWindowEx(ObjWindowsEx::exWinAchievements))
		{
			this->CloseWindowEx(ObjWindowsEx::exWinAchievements);
		}

		if (this->CheckWindowEx(ObjWindowsEx::exWinAchievementsPower))
		{
			this->CloseWindowEx(ObjWindowsEx::exWinAchievementsPower);
		}
	}

	this->WindowEx[WindowID] = 1;
}
// ----------------------------------------------------------------------------------------------

void Interface::CloseWindowEx(int WindowID)
{
	if (WindowID < 0 || WindowID > MAX_WINDOW_EX)
	{
		return;
	}

	if (WindowID == exWinMiniMenu)
	{
		sub_814FE0((char*)sub_861090(sub_860FC0()), 0, 0);
	}

	this->WindowEx[WindowID] = 0;
	//pSetCursorFocus = false;
#if(CUSTOM_PERONAL_EX==TRUE)
	if (WindowID == exWinPersonalPrice)
	{
		*(BYTE*)0xE8C5AC = 1;
	}
#endif
#if(CUSTOM_ACCOUNT_SECURITY)
	if (WindowID == exWinAccPC || WindowID == exWinAccNumber)
	{
		*(BYTE*)0xE8C5AC = 1;
	}
#endif
}
// ----------------------------------------------------------------------------------------------

bool Interface::CheckWindowEx(int WindowID)
{
	if (WindowID < 0 || WindowID > MAX_WINDOW_EX)
	{
		return 0;
	}
	return this->WindowEx[WindowID];
}
// ----------------------------------------------------------------------------------------------

bool Interface::CloseWindowsExAll()
{
	bool bResult = false;

	for (int i = 0; i < MAX_WINDOW_EX; i++)
	{
		if (this->CheckWindowEx(i))
		{
			if (i == exWinDonateCheck)
			{
				PMSG_DONATE_ITEMBUY pMsg;
				pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x96, sizeof(pMsg));
				pMsg.Result = 0;
				gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
			}

			this->CloseWindowEx(i);
			bResult = true;
		}
	}

	if (gJewelsBank.Active)
	{
		gJewelsBank.Active = false;
		bResult = true;
	}
	else if (gAutoParty.Show)
	{
		gAutoParty.Show = false;
		bResult = true;
	}
	else if (gEventTimer.Show)
	{
		gEventTimer.Show = false;
		bResult = true;
	}
	else if (gEventTimer.Show)
	{
		gEventTimer.Show = false;
		bResult = true;
	}
	else if (gInterface.Data[eRageTable].OnShow)
	{
		gInterface.Data[eRageTable].OnShow = false;
		bResult = true;
	}
	/*	else if(gRanking.Show)
		{
			gRanking.Show = false;
			bResult = true;
		}	*/

	gInterface.Data[eRESETSYSTEM_MAIN].OnShow = false;
	gInterface.Data[eGRANDSYSTEM_MAIN].OnShow = false;

	return bResult;
}
// ----------------------------------------------------------------------------------------------

bool Interface::IsWorkZone(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;
	// ----
	if ((gObjUser.m_CursorX < PosX || gObjUser.m_CursorX > MaxX)
		|| (gObjUser.m_CursorY < this->Data[ObjectID].Y || gObjUser.m_CursorY > this->Data[ObjectID].MaxY))
	{
		return false;
	}
	// ----
	return true;
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = X;
		this->Data[ObjectID].Y = Y;
		this->Data[ObjectID].MaxX = X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = Y + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawCheckLine(bool Switch, int Point, int Check, int Line, float X, float Y, int Color, char* Text)
{
	gInterface.DrawGUI(Point, X + 35, Y);	//233
	gInterface.DrawFormat(Color, X + 60, Y + 2, 120, 1, Text);
	if (Switch == true)
	{
		gInterface.DrawGUIY(Check, X + 175, Y - 2, 0);
	}
	else
	{
		gInterface.DrawGUIY(Check, X + 175, Y - 2, 1);
	}
	if (Line)
	{
		gInterface.DrawGUI(Line, X + 35, Y + 12);
	}
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawCheckLineEx(bool Switch, int Point, int Check, int Line, float X, float Y, int Color, char* Text)
{
	gInterface.DrawGUI(Point, X + 20, Y);	//233
	gInterface.DrawFormat(Color, X + 40, Y + 2, 150, 1, Text);
	if (Switch == true)
	{
		gInterface.DrawGUIY(Check, X + 190, Y - 2, 0);
	}
	else
	{
		gInterface.DrawGUIY(Check, X + 190, Y - 2, 1);
	}
	if (Line)
	{
		gInterface.DrawGUI(Line, X + 35, Y + 12);
	}
}
// ----------------------------------------------------------------------------------------------

void Interface::PartUPandDN(int Point, int PageUp, int PageDn, int Line, float X, float Y, int Color, int Number, char* Text)
{
	// --
	gInterface.DrawGUI(Point, X + 35, Y);	//293
	gInterface.DrawFormat(Color, X + 60, Y + 2, 70, 1, Text);

	if (gInterface.Data[PageDn].OnClick)
	{
		gInterface.DrawGUIY(PageDn, X + 130, Y - 2, 1);
	}
	else
	{
		gInterface.DrawGUIY(PageDn, X + 130, Y - 2, 0);
	}

	pDrawColorButton(0x7880, X + 150, Y, 20, 13, 0, 0, Color4f(0, 0, 0, 255));

	gInterface.DrawFormat(eWhite, X + 125, Y + 2, 70, 3, "%d", Number);

	if (gInterface.Data[PageUp].OnClick)
	{
		gInterface.DrawGUIY(PageUp, X + 175, Y - 2, 1);
	}
	else
	{
		gInterface.DrawGUIY(PageUp, X + 175, Y - 2, 0);
	}

	gInterface.DrawGUI(Line, X + 35, Y + 12);
	// --
}
// ----------------------------------------------------------------------------------------------

void Interface::PartUPandDNEx(int Point, int PageUp, int PageDn, int Line, float X, float Y, int Color, int Number, char* Text)
{
	// --
	gInterface.DrawGUI(Point, X + 20, Y);	//293
	gInterface.DrawFormat(Color, X + 40, Y + 2, 150, 1, Text);

	int iPlusX = 15;

	if (gInterface.Data[PageDn].OnClick)
	{
		gInterface.DrawGUIY(PageDn, X + 130 + iPlusX, Y - 2, 1);
	}
	else
	{
		gInterface.DrawGUIY(PageDn, X + 130 + iPlusX, Y - 2, 0);
	}

	pDrawColorButton(0x7880, X + 150 + iPlusX, Y, 20, 13, 0, 0, Color4f(0, 0, 0, 255));

	gInterface.DrawFormat(eWhite, X + 125 + iPlusX, Y + 2, 70, 3, "%d", Number);

	if (gInterface.Data[PageUp].OnClick)
	{
		gInterface.DrawGUIY(PageUp, X + 175 + iPlusX, Y - 2, 1);
	}
	else
	{
		gInterface.DrawGUIY(PageUp, X + 175 + iPlusX, Y - 2, 0);
	}

	gInterface.DrawGUI(Line, X + 35, Y + 12);
	// --
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawGUIY(short ObjectID, float PosX, float PosY, int Type)
{
	//if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----

	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY, this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0.0, (Type * this->Data[ObjectID].Height));
	/*
	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);*/
}

bool Interface::Button(DWORD Event, int WinID, int ButtonID, bool Type)
{
	if (!this->CheckWindowEx(WinID) || !this->IsWorkZone(ButtonID))
	{
		return false;
	}

	if (Type == true)
	{
		if (!this->Data[ButtonID].Attribute)
		{
			return false;
		}
	}

	// ----
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);
	// ----

	if (Event == WM_LBUTTONDOWN && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
		//return false;
	}

	if (Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[ButtonID].OnClick = false;
	// ----
	this->Data[ButtonID].EventTick = GetTickCount();
	//gConsole.Output(cGREEN,"%d",ButtonID);
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool Interface::ButtonEx(DWORD Event, int ButtonID, bool Type)
{
	if (!this->IsWorkZone(ButtonID))
	{
		return false;
	}

	if (Type == true)
	{
		if (!this->Data[ButtonID].Attribute)
		{
			return false;
		}
	}

	// ----
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);
	// ----

	if (Event == WM_LBUTTONDOWN && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
		//return false;
	}

	if (Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[ButtonID].OnClick = false;
	// ----
	this->Data[ButtonID].EventTick = GetTickCount();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

int __cdecl Interface::CursorDraw()
{

	bool ExWinResult = false;
	/*
	if(gInterface.CheckWindowEx(exWinRanking))
	{
		ExWinResult = true;
	}
	// ----
	if(gInterface.CheckWindowEx(exWinReset))
	{
		ExWinResult = true;
	}
	// ----
	if(gInterface.CheckWindowEx(exWinGrandReset))
	{
		ExWinResult = true;
	}
	// ----
	if(gInterface.CheckWindowEx(exWinSettings))
	{
		ExWinResult = true;
	}
	// ----
	if(gInterface.CheckWindowEx(exWinPremium))
	{
		ExWinResult = true;
	}
	// ----
	if(gInterface.CheckWindowEx(exWinMiniMenu))
	{
		ExWinResult = true;
	}*/
	if (gInterface.Data[eMQUEST_MAIN].OnShow)
	{
		ExWinResult = true;
	}

	//if(gExMenu.iStatus)
	//{
	//	ExWinResult = true;	
	//}
	// ----
	if (gInterface.CheckWindowEx(exWinPTSearchMaster))
	{
		ExWinResult = true;
	}
	// ----
	if (gInterface.CheckWindowEx(exWinPTSearchUser))
	{
		ExWinResult = true;
	}
	// ----
	if (gJewelsBank.Active)
	{
		ExWinResult = true;
	}
	// ----
	if (pSetCursorFocus == true && gController.wMouse == WM_LBUTTONDOWN && ExWinResult == true)
	{
		float v0 = pCursorY - 2.0;
		float v1 = pCursorX - 2.0;
		int result = pDrawGUFULL(30013, v1, v0, 24.0, 24.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		return result;
	}

	return pCursorDraw();
}
// ----------------------------------------------------------------------------------------------

void Interface::KeyBoxEvent(DWORD Event, char* kText, int MaxText)
{
	int Len = strlen(kText);

	if (kText[0] == '0')
	{
		kText[0] = 0;
	}

	switch (Event)
	{
	case VK_0:
	case VK_NUMPAD0:
	{
		if (Len < MaxText)
		{
			strcat(kText, "0");
		}
	}
	break;
	case VK_1:
	case VK_NUMPAD1:
	{
		if (Len < MaxText)
			strcat(kText, "1");
	}
	break;
	case VK_2:
	case VK_NUMPAD2:
	{
		if (Len < MaxText)
			strcat(kText, "2");
	}
	break;
	case VK_3:
	case VK_NUMPAD3:
	{
		if (Len < MaxText)
			strcat(kText, "3");
	}
	break;
	case VK_4:
	case VK_NUMPAD4:
	{
		if (Len < MaxText)
			strcat(kText, "4");
	}
	break;
	case VK_5:
	case VK_NUMPAD5:
	{
		if (Len < MaxText)
			strcat(kText, "5");
	}
	break;
	case VK_6:
	case VK_NUMPAD6:
	{
		if (Len < MaxText)
			strcat(kText, "6");
	}
	break;
	case VK_7:
	case VK_NUMPAD7:
	{
		strcat(kText, "7");
	}
	break;
	case VK_8:
	case VK_NUMPAD8:
	{
		if (Len < MaxText)
			strcat(kText, "8");
	}
	break;
	case VK_9:
	case VK_NUMPAD9:
	{
		if (Len < MaxText)
			strcat(kText, "9");
	}
	break;
	case VK_BACK:
	{
		if (Len > 0)
			kText[Len - 1] = 0;
	}
	break;
	}

	if (kText[0] == 0)
	{
		strcpy(kText, "0");
	}

	//int GetNum = atoi(this->KeyText);
	//gConsole.Output(cGREY, "atoi: %d", GetNum);
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawButtonMini(int id, int X, int Y, int res, char* Text)
{
	int StartX = X;
	int StartY = Y;

	gInterface.DrawGUI(id, StartX, StartY);
	gInterface.DrawFormat(eWhite, StartX + 5, StartY + 10, 50, 3, Text);

	if (!res)
	{
		gInterface.Data[id].Attribute = false;
		gInterface.DrawColoredGUI(id, gInterface.Data[id].X, gInterface.Data[id].Y, eGray150);
	}
	else
	{
		gInterface.Data[id].Attribute = true;
		if (gInterface.IsWorkZone(id))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[id].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(id, gInterface.Data[id].X, gInterface.Data[id].Y, Color);
		}
	}
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawPrice(int X, int Y, int iZen, int iChaos, int iBless, int iSoul, int iLife, int iBonus, int iCredit)
{
	int total = 0;

	if (iZen > 0)
	{
		total++;
	}
	if (iChaos > 0)
	{
		total++;
	}
	if (iBless > 0)
	{
		total++;
	}
	if (iSoul > 0)
	{
		total++;
	}
	if (iLife > 0)
	{
		total++;
	}
	if (iBonus > 0)
	{
		total++;
	}
	if (iCredit > 0)
	{
		total++;
	}

	int StartX = X;
	int StartY = Y;

	if (total == 1)
	{
		StartY += 15;
	}
	else if (total == 2)
	{
		StartY += 10;
	}
	else if (total == 3)
	{
		StartY += 5;
	}

	int ContentY = StartY;

	if (iZen > 0)
	{
		if (g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
		{
			gInterface.DrawFormat(eYellow, StartX, ContentY, 100, 3, "%d Credit", iZen);
			ContentY += 10;
		}
		else
		{
			char MoneyBuff[50];
			pGetMoneyFormat((double)iZen, MoneyBuff, 0);
			gInterface.DrawFormat(eYellow, StartX, ContentY, 100, 3, "%s Zen", MoneyBuff);
			ContentY += 10;
		}
	}

	if (iChaos > 0)
	{
		gInterface.DrawFormat(eYellow, StartX, ContentY, 100, 3, "Jewel Of Chaos x %d", iChaos);
		ContentY += 10;
	}
	if (iBless > 0)
	{
		gInterface.DrawFormat(eYellow, StartX, ContentY, 100, 3, "Jewel Of Bless x %d", iBless);
		ContentY += 10;
	}
	if (iSoul > 0)
	{
		gInterface.DrawFormat(eYellow, StartX, ContentY, 100, 3, "Jewel Of Soul x %d", iSoul);
		ContentY += 10;
	}
	if (iLife > 0)
	{
		gInterface.DrawFormat(eYellow, StartX, ContentY, 100, 3, "Jewel Of Soul x %d", iLife);
		ContentY += 10;
	}
	if (iBonus > 0)
	{
		gInterface.DrawFormat(eYellow, StartX, ContentY, 100, 3, "%d WCoin", iBonus);
		ContentY += 10;
	}
	if (iCredit > 0)
	{
		gInterface.DrawFormat(eYellow, StartX, ContentY, 100, 3, "%d Credit", iCredit);
		ContentY += 10;
	}
}
// ----------------------------------------------------------------------------------------------

int Interface::DrawFormat_Ex(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	int LineCount = 0;
	// ----
	char * Line = strtok(Buff, "/");
	// ----
	while (Line != NULL)
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "/");
	}
	// ----
	return PosY;
}
// ----------------------------------------------------------------------------------------------

bool Interface::ButtonCord(DWORD Event, float bX, float bY, float bW, float bH, bool& bClick, DWORD& EventTick)
{
	if (!this->IsWorkZone(bX, bY, bX + bW, bY + bH))
	{
		//gConsole.Output(cYELLOW, "return IsWorkZone");
		return false;
	}
	// ----
	DWORD Delay = (GetTickCount() - EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN && bClick == false)
	{
		bClick = true;
		//gConsole.Output(cYELLOW, "return false ButtonCord");
		//return false;
	}
	// ----
	if (Event == WM_LBUTTONUP && bClick == true)
	{
		//gConsole.Output(cYELLOW, "return ButtonCord");
		bClick = false;
		return true;
	}
	// ----
	if (Delay < 500)
	{
		//gConsole.Output(cYELLOW, "return 500 ButtonCord");
		return false;
	}
	// ----
	bClick = false;
	// ----
	EventTick = GetTickCount();
	// ----
	//gConsole.Output(cYELLOW, "return end ButtonCord");
	return false;
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawBorder(float X, float Y, float Whith, float High, float bor, DWORD eColor)
{
	pDrawColorButton(0x7880, X, Y, Whith, bor, 0, 0, eColor);
	pDrawColorButton(0x7880, X, Y, bor, High, 0, 0, eColor);

	pDrawColorButton(0x7880, X, Y + High, Whith + bor, bor, 0, 0, eColor);	//Должна быть нижняя линия
	pDrawColorButton(0x7880, X + Whith, Y, bor, High, 0, 0, eColor);	//Боковая линия
}
// ----------------------------------------------------------------------------------------------


void Interface::DrawButtonBig(int ObjID, bool bActive, float fX, float fY, char* Text)
{
	gInterface.DrawGUI(ObjID, fX, fY);
	gInterface.DrawFormat(eWhite, fX + 4, fY + 10, 100, 3, Text);
	if (bActive)
	{
		gInterface.Data[ObjID].Attribute = true;
		if (gInterface.IsWorkZone(ObjID))
		{
			DWORD Color = eGray100;
			if (gInterface.Data[ObjID].OnClick)
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(ObjID, gInterface.Data[ObjID].X, gInterface.Data[ObjID].Y, Color);
		}
	}
	else
	{
		gInterface.Data[ObjID].Attribute = false;
		gInterface.DrawColoredGUI(ObjID, gInterface.Data[ObjID].X, gInterface.Data[ObjID].Y, eGray150);
	}
}

void Interface::DrawRightMiniInfoMapQuest()
{
	if (!gObjUser.m_MapQuestShow)
	{
		return;
	}

	if (gInterface.CheckWindow(Party)
		|| gInterface.CheckWindow(Guild)
		|| gInterface.CheckWindow(Trade)
		|| gInterface.CheckWindow(Warehouse)
		|| gInterface.CheckWindow(ChaosBox)
		|| gInterface.CheckWindow(CommandWindow)
		|| gInterface.CheckWindow(PetInfo)
		|| gInterface.CheckWindow(Shop)
		|| gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(Store)
		|| gInterface.CheckWindow(OtherStore)
		|| gInterface.CheckWindow(Character)
		|| gInterface.CheckWindow(FastMenu)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(NPC_Titus)
		|| gInterface.CheckWindow(CashShop)
		|| gInterface.CheckWindow(FullMap)
		|| gInterface.CheckWindow(NPC_Dialog)
		|| gInterface.CheckWindow(GensInfo)
		|| gInterface.CheckWindow(NPC_Julia)
		|| gInterface.CheckWindow(ExpandInventory)
		|| gInterface.CheckWindow(ExpandWarehouse)
		|| gInterface.CheckWindow(Helper)
		|| gInterface.CheckWindow(Quest)
		|| gInterface.CheckWindow(QuestDevin)
		|| gInterface.CheckWindow(DevilSquery)
		|| gInterface.CheckWindow(GuardNPC)
		|| gInterface.CheckWindow(VorotaCS)
		|| gInterface.CheckWindow(Rena)
		|| gInterface.CheckWindow(LuckyCoins)
		|| gInterface.CheckWindow(Titus)
		|| gInterface.CheckWindow(BloodCastle))
	{
		return;
	}

	if (gInterface.CheckWindowEx(exWinRanking) ||
		gInterface.CheckWindowEx(exWinPersonalPrice))
	{
		return;
	}

	if (g_ExMenuV3.m_Enable && g_ExMenuV3.m_Version == EXMENU_NUMBER::eVERSION_ET)
	{
		if (gInterface.CheckWindowEx(exWinMenuV3))
		{
			return;
		}
	}

	int qCount = 15;
	int mCount = 10;
	bool DrInfo = true;

	if (DrInfo == false)
	{
		return;
	}

	float iX = 535;
	float iY = 320;
	float Wind = 100;
	float Hig = qCount + mCount;

	float StartiY = 425;
	// ----
	StartiY = gInterface.RightMiniInfoY - 5;
	gInterface.RightMiniInfoY -= Hig;
	// ----
	iY = StartiY - Hig;

	pDrawColorButton(0x7880, iX, iY, Wind, Hig, NULL, NULL, Color4f(0, 0, 0, 100));

	iY += 3;

	gInterface.DrawFormat(eOrange, iX + 5, iY, 200, 1, "Map Quest");

	iY += 10;
	gInterface.DrawFormat(eWhite, iX + 10, iY, 200, 1, "- Monster Count: %d / %d", gObjUser.m_MapQuestCount, gObjUser.m_MapQuestMaxCount);
}

void Interface::DrawGUIText(short ObjectID, float PosX, float PosY, char* Text)
{
	//if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----

	DWORD Color = eWhite;

	if (gInterface.IsWorkZone(ObjectID))
	{
		Color = eYellow;
	}

	gInterface.DrawFormat(Color, PosX, PosY, this->Data[ObjectID].Width, 3, Text);

}

void Interface::CashShopOpen()
{
	//*(int*)(0x1EE153E8 + 56) = 1;
	sub_811A60(&*(char*)0x1EE153E8);
	//*(int*)(0x1EE153E8 + 56) = 0;
	return;



	pPShopThis2(pPShopThis1());

	if (pCashShopCheck())
	{
		LPVOID v39 = pCashShopThis();
		LPVOID v40;
		if (pCashShopCheck2(v39) != 1 || (v40 = pCashShopThis(), pCashShopCheck3(v40)))
		{
			LPVOID v41 = pCashShopThis();
			if ((unsigned __int8)sub_93FB90(v41) == 1)
			{
				LPVOID v42 = pCashShopThis();
				if ((unsigned __int8)sub_93F7E0(v42) == 1)
				{
					LPVOID v43 = pCashShopThis();
					LPVOID v44 = sub_940EB0(v43);
					LPVOID v45 = pCashShopThis();
					LPVOID v46 = sub_940E80(v45);
					LPVOID v47 = sub_860FC0();
					//sub_8617B0((int)v47);
					//sub_944E60(v46, v44);
				}
			}
			LPVOID v48 = sub_860FC0();
			//if ( sub_85EAD0(v48, 65) )
			//{
			//	sub_404B40(&v75);
			//	v79 = 9;
			//	sub_404B90(-63, -46);
			//	sub_4050D0(2);
			//	sub_4050D0(1);
			//	//((void (__thiscall *)(char *, _DWORD, _DWORD))loc_404D70)(&v75, 0, 0);
			//	v79 = -1;
			//	sub_404B60(&v75);
			//	sub_860FC0();
			//	sub_85F850(65);
			//}
			//else
			//{
			//	LPVOID v49 = pCashShopThis();
			//	if ( !(unsigned __int8)sub_940540(v49) )
			//	{
			//		sub_404B40(&v76);
			//		v79 = 8;
			//		sub_404B90(-63, -46);
			//		sub_4050D0(2);
			//		sub_4050D0(0);
			//		//((void (__thiscall *)(char *, _DWORD, _DWORD))loc_404D70)(&v76, 0, 0);
			//		v79 = -1;
			//		sub_404B60(&v76);
			//		pCashShopThis();
			//		sub_940520(1);
					//LPVOID v50 = sub_860FC0();
					//sub_861090(v50);
					//sub_814FE0(0, 1);
			//	}
			//}
		}
	}
}

#if(CUSTOM_AUTOCTRL)
void Interface::DrawAutoCtrl()
{
	if (!this->m_bAutoCtrl)
	{
		return;
	}

	this->DrawFormat(eExcellent, 200, 4, 100, 1, "Auto Ctrl: ON");
}
#endif

void Interface::DrawWindow(int ObjMain, int ObjTitle, int ObjFrame, int ObjFooter, int Repeat, float X, float Y, char* Text)
{
	float StartY = Y;
	float StartX = X;

	gInterface.DrawGUI(ObjMain, StartX, StartY + 2);
	gInterface.DrawGUI(ObjTitle, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ObjFrame, StartX, StartY + 67.0, Repeat);
	gInterface.DrawGUI(ObjFooter, StartX, StartY);

	gInterface.DrawFormat(eGold, StartX + 10, Y + 10, 210, 3, Text);
}

void Interface::DrawPage(int ObjL, int ObjR, int Page, int MaxPage, float X, float Y)
{
	DWORD Color = eGray100;
	float ContentX = X;
	float ContentY = Y;

	gInterface.DrawGUI(ObjL, ContentX + 75, ContentY + 325);
	gInterface.DrawGUI(ObjR, ContentX + 135, ContentY + 325);

	if (gInterface.IsWorkZone(ObjL))
	{
		Color = eGray100;
		if (gInterface.Data[ObjL].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eREFERRAL_L, gInterface.Data[eREFERRAL_L].X, gInterface.Data[eREFERRAL_L].Y, Color);
	}

	if (gInterface.IsWorkZone(ObjR))
	{
		Color = eGray100;
		if (gInterface.Data[ObjR].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(ObjR, gInterface.Data[eREFERRAL_R].X, gInterface.Data[eREFERRAL_R].Y, Color);
	}

	gInterface.DrawFormat(eGold, ContentX + 64, ContentY + 329, 100, 3, "Page: %d / %d", Page + 1, MaxPage);
}



void testfunc()
{
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
}

void Interface::DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse)
{
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();

	sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);

	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;
	sub_6358A0_Addr(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C);

	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();

	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();

	pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, Excl, Anc, OnMouse);

	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();

	glColor3f(1, 1, 1);
	pSetBlend(false);
}

#if(CUSTOM_POSTITEM)

void Interface::LoadItemPost()
{
#if(CUSTOM_POSTITEM)
	this->item_post_ = nullptr;
	SetOp((LPVOID)oDrawInterface2_Call, this->Work2, ASM::CALL);
#endif
}

void Interface::Work2() {
	if (gInterface.item_post_) {
		DrawItemToolTipText(gInterface.item_post_, pCursorX + 80, pCursorY - 80);

		if (gInterface.last_tickcount_view_ + 100 < GetTickCount()) {
			gInterface.item_post_ = nullptr;
		}
	}

#if(CUSTOM_PICKUP_ITEM_INFO)
	//gItem.DrawPickUpItemInfp();
#endif

#if(CUSTOM_PICKUP_ITEM_INFO)
	g_PickUpItemInfo.Draw();
#endif
#if(CUSTOM_WIN_SETTINGS==TRUE)
	g_Settings.Draw();
#endif
	pDrawInterface2();
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawChat(int mode, char* character, char* message) {
	PBMSG_CHATPOSTITEM chat;
	memset(&chat.character_[0], 0, 10);
	memset(&chat.message_[0], 0, 89);
	memcpy(&chat.character_[0], &character[0], 10);
	memcpy(&chat.message_[0], &message[0], strlen(message));
	pHandlePacketChatData(&chat);

	if (mode >= 1 && mode <= 9 && ChatBoxMuObjectChatDataPtrArrayLength) {
		int index = ChatBoxMuObjectChatDataPtrArrayLength - 1;
		ChatBoxMuObjectChatDataPtrArray[index]->chat_type_ = mode;
	}
}
// ----------------------------------------------------------------------------------------------
/*
00424749
004D8890
004D933D
004D96F4
004D98E3
004D9CBB
005977E8
005B4BC4









*/
void Interface::DrawItemToolTipText(void * item, int x, int y) {
	static DWORD mem = 0;
	_asm {
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH item;
		PUSH y;
		PUSH x;
		MOV mem, 0x00860FC0;
		CALL mem;
		MOV ECX, EAX;
		MOV mem, 0x00861950;
		CALL mem;
		MOV ECX, EAX;
		MOV mem, 0x007E3CE0;
		CALL mem;
	}
}


long MessageTick;
char MessageText[80];

void Interface::MapMessageRender()
{
	if (MessageTick + 1700 > GetTickCount())	// 1.7 seconds for those who read slowly
	{
		SetByte((LPVOID)0x007D2CB9, 0x90);	// NOP
		SetByte((LPVOID)(0x007D2CB9 + 1), 0x90);	// NOP
		SetByte((LPVOID)(0x007D2CB9 + 2), 0x68);	// PUSH
		SetDword((LPVOID)(0x007D2CB9 + 3), (DWORD)&MessageText);	// Text
	}
	else
	{
		SetByte((LPVOID)0x007D2CB9, 0x8D);	// LEA
		SetByte((LPVOID)(0x007D2CB9 + 1), 0x95);	// EDX
		SetDword((LPVOID)(0x007D2CB9 + 2), 0xFFFFFF00);	// Local.64
		SetByte((LPVOID)0x007D2CBF, 0x52);	// PUSH EDX
	}
}

void CheckProcent(char* message)
{
	unsigned int MessageLength = strlen(message);
	for (unsigned int nLetter = 0; nLetter <= MessageLength; nLetter++)
	{
		if (message[nLetter] == '%')
		{
			message[nLetter] = ' ';
		}
	}
}

void Interface::SetMapMessage(const char* Format, ...)
{
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(MessageText, Format, pArguments);
	CheckProcent(MessageText); // "%" Bug Fix
	va_end(pArguments);

	MessageTick = GetTickCount();
}

void Interface::DrawBarForm(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(1);
	glColor4f(red, green, blue, alpha);
	pDrawBarForm(PosX, PosY, Width, Height, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
}


#endif


void Interface::DrawMiniMap()
{
	if (gMiniMap)
	{
		if (this->MiniMapCheck() || this->CombinedChecks())
		{
			return;
		}

		if (g_ExMenuV3.m_Enable && g_ExMenuV3.m_Version == EXMENU_NUMBER::eVERSION_ET)
		{
			if (gInterface.CheckWindowEx(exWinMenuV3))
			{
				return;
			}
		}

		float MainWidth = 138.0;
		float MainHeight = 265.0;
		float StartY = 264.0 + 7.0;
		gInterface.RightMiniInfoY -= 128;

		float StartX = 512.0;

		switch (gObjUser.m_MapNumber)
		{
		case 0:    //Lorencia
		{
			this->DrawGUI(eLORENCIA_MAP, StartX, StartY + 30);
			//this->DrawColorGUI(eLORENCIA_MAP, StartX, StartY + 30, 128, 128,  Color4f(0, 0, 0, 255));
		}
		break;
		// --
		case 1:    //Dungeon
		{
			this->DrawGUI(eDUNGEON_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 2:    //Devias
		{
			this->DrawGUI(eDEVIAS_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 3:    //Noria
		{
			this->DrawGUI(eNORIA_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 4:    //LostTower
		{
			this->DrawGUI(eLOSTTOWER_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 5:    //Exile (disabled)
		{
			return;
		}
		break;
		// --
		// --
		case 7:    //Atlans
		{
			this->DrawGUI(eATLANS_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 8:    //Tarkan
		{
			this->DrawGUI(eTarkan_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 10:    //Icarus
		{
			this->DrawGUI(eICARUS_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 31:    //Land of Trials
		{
			this->DrawGUI(eLANDOFTRIALS_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 33:    //Aida
		{
			this->DrawGUI(eAIDA_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 34:    //Crywolf Fortress
		{
			this->DrawGUI(eCRYWOLF_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 37:    //Kantru
		{
			this->DrawGUI(eKANTRU_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 38:    //Kantru 3
		{
			this->DrawGUI(eKANTRU3_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 41:    //Barracks
		{
			this->DrawGUI(eBARRACKS_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 51:    //Elbeland
		{
			this->DrawGUI(eElbeland_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 56:    //Swamp of Calmness
		{
			this->DrawGUI(eCALMNESS_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 57:    //Raklion
		{
			this->DrawGUI(eRAKLION_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 63:    //Vulcanus
		{
			this->DrawGUI(eVULCANUS_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 80:    //Kalrutan
		{
			this->DrawGUI(eKALRUTAN_MAP, StartX, StartY + 30);
		}
		break;
		// --
		case 81:    //Kalrutan 2
		{
			this->DrawGUI(eKALRUTAN2_MAP, StartX, StartY + 30);
		}
		break;

		// --
		default: //Default
		{
			return;
			// this->DrawGUI(eNULL_MAP, StartX, StartY + 30);
		}
		}
		// ----

		//if(this->m_iDrawObjectID >= eLORENCIA_MAP && eKALRUTAN2_MAP >= this->m_iDrawObjectID)
		{
			//gInterface.DrawColoredGUI(this->m_iDrawObjectID, StartX, StartY + 30, Color4f(255, 255, 255, 50));
			//gInterface.DrawColoredGUI(this->m_iDrawObjectID, StartX, StartY + 30, eGray100);
		}

		lpViewObj lpViewPlayer = &*(ObjectPreview*)oUserPreviewStruct;

#if(CUSTOM_MINIMAP_PARTY)
		if (g_Party.PartyMemberCount > 0)
		{
			for (int i = 0; i < gObjUser.m_PartyMapCount; i++)
			{
				if (pMapNumber != gObjUser.m_PartyMapData[i].Map)
				{
					continue;
				}

				BYTE btPlayerX = gObjUser.m_PartyMapData[i].X;
				BYTE btPlayerY = gObjUser.m_PartyMapData[i].Y;

				this->DrawGUI(ePLAYER_POINT_1 + i, (float)(StartX - 1 + btPlayerX / 2), (float)(294 - 1 + (255 - btPlayerY) / 2));

				if (this->IsWorkZone(ePLAYER_POINT_1 + i))
				{
					this->DrawFormat(eWhite, (float)(StartX - 5 + btPlayerX / 2), (float)(294 - 8 + (255 - btPlayerY) / 2), 25, 1, gObjUser.m_PartyMapData[i].Name);
				}
			}
		}
		else
#endif
		{
			this->DrawGUI(ePLAYER_POINT_1, (float)(StartX - 1 + lpViewPlayer->MapPosX / 2), (float)(294 - 1 + (255 - lpViewPlayer->MapPosY) / 2));

			if (this->IsWorkZone(ePLAYER_POINT_1))
			{
				this->DrawFormat(eWhite, (float)(StartX - 5 + lpViewPlayer->MapPosX / 2), (float)(294 - 8 + (255 - lpViewPlayer->MapPosY) / 2), 25, 1, lpViewPlayer->Name);
			}
		}
		//pSetBlend(false);
		//pGLSwitchBlend();

	//pGLSwitch();
	// glColor3f(1.0, 1.0, 1.0);
	}
}

bool Interface::MiniMapCheck()
{
	if (this->CheckWindow(Inventory) ||
		this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(Character) ||
		this->CheckWindow(CommandWindow) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(GensInfo) ||
		this->CheckWindow(Guild) ||
		this->CheckWindow(NPC_Dialog) ||
		this->CheckWindow(NPC_Julia) ||
		this->CheckWindow(NPC_Titus) ||
		this->CheckWindow(OtherStore) ||
		this->CheckWindow(Party) ||
		this->CheckWindow(PetInfo) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Store) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(FriendList) ||
		this->CheckWindow(FastMenu) ||
		this->CheckWindow(Helper) ||
		this->CheckWindow(Quest) ||
		this->CheckWindow(Warehouse))
		return true;
	return false;
}

bool Interface::CombinedChecks()
{
	if ((this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store)) ||
		(this->CheckWindow(Inventory)
			&& this->CheckWindow(Warehouse)
			&& this->CheckWindow(ExpandWarehouse)) ||
			(this->CheckWindow(Inventory)
				&& this->CheckWindow(Character)
				&& this->CheckWindow(Store)))
		return true;
	return false;
}

void Interface::DrawAutoHPClick()
{
	if (!this->m_ActiveAutoHP)
	{
		return;
	}

	if (pPlayerState != GameProcess)
	{
		return;
	}

	if (this->CheckWindow(FullMap) ||
		this->CheckWindow(CashShop))
	{
		return;
	}

	//if(gExMenu.iStatus)
	//{
	//	return;
	//}

	int ContentX = 190;	//195
	int ContentY = 0;

	if (this->m_AutoHP == true)
	{
		this->DrawGUI(eAUTO_HP_ON, ContentX, ContentY);
	}
	else
	{
		this->DrawGUI(eAUTO_HP_OFF, ContentX, ContentY);
	}

	gInterface.DrawFormat(eWhite, ContentX - 20, ContentY + 5, 100, 3, "Auto HP");

	if (this->IsWorkZone(eAUTO_HP_ON) || this->IsWorkZone(eAUTO_HP_OFF))
	{
		pSetCursorFocus = true;

		if (gController.wMouse == WM_LBUTTONDOWN && (GetTickCount() - this->m_AutoHPTick) > 1000)
		{
			this->m_AutoHP = !this->m_AutoHP;
			this->m_AutoHPTick = GetTickCount();
			gProtocol.CG_AutoHP(this->m_AutoHP);
		}
	}
}

void Interface::EventAutoHPClick(DWORD Event)
{
	if (!this->m_ActiveAutoHP)
	{
		return;
	}

	if (pPlayerState != GameProcess)
	{
		return;
	}

	if (this->CheckWindow(FullMap) ||
		this->CheckWindow(CashShop))
	{
		return;
	}

	//if(gExMenu.iStatus)
	//{
	//	return;
	//}

	if (gInterface.ButtonEx(Event, eAUTO_HP_ON, false) &&
		gInterface.ButtonEx(Event, eAUTO_HP_OFF, false))
	{

	}
}


bool Interface::IsWorkFullZone(float X, float Y, float MaxX, float MaxY)
{
	if ((gObjUser.CursorX_Ex < X || gObjUser.CursorX_Ex > MaxX)
		|| (gObjUser.CursorY_Ex < Y || gObjUser.CursorY_Ex > MaxY))
	{
		return false;
	}
	// ----
	return true;
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawGUIEx(short ObjectID, float PosX, float PosY, bool dr)
{
	//if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}

	if (!dr)
	{
		return;
	}
	// ----
#if(DEBUG_X_Y_DRAW==TRUE)
	//float a2 = GAME_X_IN_FULL_X(PosX);
	//float a3 = GAME_Y_IN_FULL_Y(PosY);

	/*
		float CritX = (double)(v6 % 10) * Whith / 256;
		float CritY = (double)(v6 / 10) * High / 256;

		float standartWhith = Whith / 256;
		float standartHight = High / 256;

		pDrawGUFULL(Model, X, Y, Whith, High, CritX, CritY, standartWhith, standartHight, NULL, NULL, 0.0);
		*/
		//pDrawGUFULL(this->Data[ObjectID].ModelID, a2, a3, this->Data[ObjectID].Width, this->Data[ObjectID].Height, 1.0, 1.0, 1.0, 1.0, 0, 0, 0.0);

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
#else
	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
#endif
}

float Interface::GetResizeX(short ObjectID)
{
	if (pWinWidth == 800)
	{
		return this->Data[ObjectID].X + 16.0;
	}
	else if (pWinWidth != 1024)
	{
		return this->Data[ObjectID].X - 16.0;
	}
	// ----
	return this->Data[ObjectID].X;
}

void Interface::DrawWarehouseUI()
{
	if (!g_ExLicense.CheckUser(eExUB::MedoniAndrei) && !g_ExLicense.CheckUser(eExUB::Local) && !g_ExLicense.CheckUser(eExUB::ProtectDebug) &&
		!g_ExLicense.CheckUser(eExUB::Gredy) && !g_ExLicense.CheckUser(eExUB::GredyLocal) && !g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		return;
	}

	if (!this->CheckWindow(Warehouse))
	{
		//gObjUser.WarehouseNumber = 0;
		return;
	}

	float PosX = 294;
	float PosY = 345;

	if (pWinWidth == 800)
	{
		PosX = PosX + 16.0;
	}
	else if (pWinWidth != 1024)
	{
		PosX = PosX - 16.0;
	}

	if (this->CheckWindow(ExpandInventory))
	{
		PosX = PosX - 190;
	}

	this->DrawGUI(eWAREHOUSE, PosX, PosY);
	this->DrawGUI(eWAREHOUSE1, PosX + 45, PosY);
	this->DrawFormat(eWhite, PosX + 25, PosY + 4, 10, 1, "%d/5", gObjUser.WarehouseNumber + 1);
	// ----
	if (IsWorkZone(eWAREHOUSE))
	{
		if (this->Data[eWAREHOUSE].OnClick)
		{
			this->DrawColoredGUI(eWAREHOUSE, PosX, PosY, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		this->DrawColoredGUI(eWAREHOUSE, PosX, PosY, pMakeColor(255, 204, 20, 200));
	}
	else if (IsWorkZone(eWAREHOUSE1))
	{
		if (this->Data[eWAREHOUSE1].OnClick)
		{
			this->DrawColoredGUI(eWAREHOUSE1, PosX + 45, PosY, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		this->DrawColoredGUI(eWAREHOUSE1, PosX + 45, PosY, pMakeColor(255, 204, 20, 200));
	}
}

// ----------------------------------------------------------------------------------------------

void Interface::EventWarehouseUI(DWORD Event)
{
	if (!g_ExLicense.CheckUser(eExUB::MedoniAndrei) && !g_ExLicense.CheckUser(eExUB::Local) && !g_ExLicense.CheckUser(eExUB::ProtectDebug) &&
		!g_ExLicense.CheckUser(eExUB::Gredy) && !g_ExLicense.CheckUser(eExUB::GredyLocal) && !g_ExLicense.CheckUser(eExUB::Gredy2) &&
		!g_ExLicense.CheckUser(eExUB::mu4you) && !g_ExLicense.CheckUser(eExUB::Artem) && !g_ExLicense.CheckUser(eExUB::Artem2) &&
		!g_ExLicense.CheckUser(eExUB::NSGames))
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();
	// ----
	if (!this->CheckWindow(Warehouse))
	{
		return;
	}
	// ----
	if (IsWorkZone(eWAREHOUSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eWAREHOUSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eWAREHOUSE].OnClick = true;
			return;
		}
		// ----
		this->Data[eWAREHOUSE].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eWAREHOUSE].EventTick = GetTickCount();
		// ----
		if (gObjUser.WarehouseNumber - 1 < 0)
		{
			return;
		}

		CHANGEWAREHOUSE pRequest;
		pRequest.Number = gObjUser.WarehouseNumber - 1;
		pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0xC1, sizeof(pRequest));
		gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
	}
	else if (IsWorkZone(eWAREHOUSE1))
	{
		DWORD Delay = (CurrentTick - this->Data[eWAREHOUSE1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eWAREHOUSE1].OnClick = true;
			return;
		}
		// ----
		this->Data[eWAREHOUSE1].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eWAREHOUSE1].EventTick = GetTickCount();
		// ----
		if (gObjUser.WarehouseNumber + 1 > 4)
		{
			return;
		}
		CHANGEWAREHOUSE pRequest;
		pRequest.Number = gObjUser.WarehouseNumber + 1;
		pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0xC1, sizeof(pRequest));
		gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
	}
}

void Interface::DrawOffTrade()
{
	if (!g_ExLicense.CheckUser(eExUB::MedoniAndrei) && !g_ExLicense.CheckUser(eExUB::Local))
	{
		return;
	}

	if (!this->CheckWindow(Store))
	{
		return;
	}

	float PosX = 258 - 20;
	float PosY = 360;

	if (pWinWidth == 800)
	{
		PosX = PosX + 16.0;
	}
	else if (pWinWidth != 1024)
	{
		PosX = PosX - 16.0;
	}

	if (this->CheckWindow(ExpandInventory))
	{
		PosX = PosX - 190;
	}

	gInterface.DrawGUI(eOFFTRADE_POINT1, PosX + 20, PosY);	//233
	gInterface.DrawFormat(eWhite, PosX + 40, PosY + 2, 150, 1, "Active OffTrade");
	if (this->m_OffTradeSwitch == true)
	{
		gInterface.DrawGUIY(eOFFTRADE_CHECK1, PosX + 100, PosY - 2, 0);
	}
	else
	{
		gInterface.DrawGUIY(eOFFTRADE_CHECK1, PosX + 100, PosY - 2, 1);
	}
}

void Interface::EventOffTrade(DWORD Event)
{
	if (!g_ExLicense.CheckUser(eExUB::MedoniAndrei) && !g_ExLicense.CheckUser(eExUB::Local))
	{
		return;
	}

	if (!this->CheckWindow(Store))
	{
		return;
	}

	if (gInterface.ButtonEx(Event, eOFFTRADE_CHECK1, false))
	{
		this->m_OffTradeSwitch = !this->m_OffTradeSwitch;

		PMSG_OFFTRADE pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xC2, sizeof(pMsg));
		pMsg.Active = this->m_OffTradeSwitch;
		gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
	}
}

#if(CUSTOM_EMULATOR_KEY)

void Interface::DrawAutoClickMouse()
{
	if (gInterface.CheckWindow(ObjWindow::CashShop) ||
		gInterface.CheckWindow(ObjWindow::FullMap) ||
		gInterface.CheckWindow(ObjWindow::SkillTree) ||
		gInterface.CheckWindow(ObjWindow::MoveList))
	{
		return;
	}

	if (!gController.m_AutoMouseLeft && !gController.m_AutoMouseRight)
	{
		return;
	}

	char szTextAuto[64] = { 0 };
	float flX = 35.0;
	float flY = 22.0;

	gInterface.DrawFormat(eGold, flX, flY, 50, 1, "Auto Mouse:");

	flX += 45.0;

	if (gController.m_AutoMouseLeft)
	{
		strcat(szTextAuto, "(Left)");
	}

	if (gController.m_AutoMouseRight)
	{
		strcat(szTextAuto, "(Right)");
	}

	gInterface.DrawFormat(eWhite, flX, flY, 50, 1, szTextAuto);
}

#endif

#if(DEV_INTERFASE_SEASON3)
bool Interface::EventInterfaceS3_Main(DWORD Event)
{
	if (interCustom == 1 || interCustom == 2 || interCustom == 3)
	{
		this->EventMenuButton(Event);

		return true;
	}
}

void Interface::DrawS2Interface()
{
	if (interCustom == 1 || interCustom == 2 || interCustom == 3)
	{
		gInterface.DrawGUI(eSkillBox, 305, 443);

		/*		if (this->CheckWindow(ObjWindow::ChatWindow) || this->CheckWindow(ObjWindow::CashShop)
					|| this->CheckWindow(ObjWindow::FullMap) || this->CheckWindow(ObjWindow::SkillTree)
					|| this->CheckWindow(ObjWindow::MoveList))
					{
					return;
					}
					gInterface.DrawGUI(eDragonLeft, 0, 388);*/
	}

}

void Interface::DrawMenuButton()
{
	if (interCustom == 1 || interCustom == 2 || interCustom == 3)
	{
		if (IsWorkZone(eParty))
		{
			this->DrawToolTip(345, 420, "Party (P)");
		}
		if (this->CheckWindow(Party))
		{
			gInterface.DrawGUI(eParty, 348, 449);
		}
		if (IsWorkZone(eCharacter))
		{
			this->DrawToolTip(375, 420, "Character (C)");
		}
		if (this->CheckWindow(Character))
		{
			gInterface.DrawGUI(eCharacter, 378.5f, 449);
		}
		if (IsWorkZone(eInventory))
		{
			this->DrawToolTip(405, 420, "Inventory (V)");
		}
		if (this->CheckWindow(Inventory))
		{
			gInterface.DrawGUI(eInventory, 409, 449);
		}
		if (IsWorkZone(eFriend))
		{
			this->DrawToolTip(440, 420, "Friends (F)");
		}
		if (this->CheckWindow(FriendList))
		{
			gInterface.DrawGUI(eFriend, 581, 432);
		}
		if (IsWorkZone(eFastMenu))
		{
			this->DrawToolTip(115, 420, "Menu (U)");
		}
		if (this->CheckWindow(FastMenu))
		{
			gInterface.DrawGUI(eFastMenu, 5, 432);
		}
		/*if (IsWorkZone(eCashShop))
		{
		this->DrawToolTip(439, 420, "CashShop (X)");
		}
		if (this->CheckWindow(CashShop))
		{
		gInterface.DrawGUI(eCashShop, 439, 449);
		}*/
		if (IsWorkZone(eGuild))
		{
			this->DrawToolTip(440, 420, "Guild (G)");
		}
		if (this->CheckWindow(Guild))
		{
			gInterface.DrawGUI(eGuild, 581, 449);
		}

		/*		if (this->CheckWindow(ObjWindow::CashShop)
					|| this->CheckWindow(ObjWindow::FullMap)
					|| this->CheckWindow(ObjWindow::SkillTree)
					|| this->CheckWindow(ObjWindow::Inventory)
					|| this->CheckWindow(ObjWindow::Guild)
					|| this->CheckWindow(ObjWindow::Party)
					|| this->CheckWindow(ObjWindow::Character)
					|| this->CheckWindow(ObjWindow::FastMenu)
					|| this->CheckWindow(ObjWindow::FriendList)
					|| this->CheckWindow(ObjWindow::GensInfo)
					|| this->CheckWindow(ObjWindow::Quest)
					|| this->CheckWindow(ObjWindow::CommandWindow)
					|| gObjUser.m_MapNumber == 34 || gObjUser.m_MapNumber == 30)
					{
					return;
					}
					gInterface.DrawGUI(eDragonRight, 532, 388);
					*/
	}
}

bool Interface::EventMenuButton(DWORD Event)
{
	if (interCustom == 1 || interCustom == 2 || interCustom == 3)
	{
		DWORD CurrentTick = GetTickCount();
		if (this->CheckWindow(ChaosBox))
		{
			return true;
		}

		if (IsWorkZone(eParty))
		{
			DWORD Delay = (CurrentTick - this->Data[eParty].EventTick);
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eParty].OnClick = true;
				return true;
			}
			this->Data[eParty].OnClick = false;
			if (Delay < 500)
			{
				return true;
			}
			this->Data[eParty].EventTick = GetTickCount();
			if (this->CheckWindow(Party))
			{
				this->CloseWindow(Party);
			}
			else {
				this->OpenWindow(Party);
			}
		}
		else if (IsWorkZone(eCharacter))
		{
			DWORD Delay = (CurrentTick - this->Data[eCharacter].EventTick);
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eCharacter].OnClick = true;
				return true;
			}
			this->Data[eCharacter].OnClick = false;
			if (Delay < 500)
			{
				return true;
			}
			this->Data[eCharacter].EventTick = GetTickCount();
			if (this->CheckWindow(Character))
			{
				this->CloseWindow(Character);
			}
			else
			{
				this->OpenWindow(Character);
			}
		}
		else if (IsWorkZone(eInventory))
		{
			DWORD Delay = (CurrentTick - this->Data[eInventory].EventTick);
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eInventory].OnClick = true;
				return true;
			}
			this->Data[eInventory].OnClick = false;
			if (Delay < 500)
			{
				return true;
			}
			this->Data[eInventory].EventTick = GetTickCount();
			if (this->CheckWindow(Inventory))
			{
				this->CloseWindow(Inventory);
			}
			else
			{
				this->OpenWindow(Inventory);
			}
		}
		else if (IsWorkZone(eFriend))
		{
			DWORD Delay = (CurrentTick - this->Data[eFriend].EventTick);
			if (Event == WM_LBUTTONDOWN) {
				this->Data[eFriend].OnClick = true;
				return true;
			}
			this->Data[eFriend].OnClick = false;
			if (Delay < 500) {
				return true;
			}
			this->Data[eFriend].EventTick = GetTickCount();
			if (this->CheckWindow(FriendList)) {
				this->CloseWindow(FriendList);
			}
			else {
				this->OpenWindow(FriendList);
			}
		}
		else if (IsWorkZone(eFastMenu))
		{
			DWORD Delay = (CurrentTick - this->Data[eFastMenu].EventTick);
			if (Event == WM_LBUTTONDOWN) {
				this->Data[eFastMenu].OnClick = true;
				return true;
			}
			this->Data[eFastMenu].OnClick = false;
			if (Delay < 500) {
				return true;
			}
			this->Data[eFastMenu].EventTick = GetTickCount();
			if (this->CheckWindow(FastMenu)) {
				this->CloseWindow(FastMenu);
			}
			else {
				this->OpenWindow(FastMenu);
			}
		}
		/*else if (IsWorkZone(eCashShop))
		{
		DWORD Delay = (CurrentTick - this->Data[eCashShop].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
		this->Data[eCashShop].OnClick = true;
		return true;
		}
		this->Data[eCashShop].OnClick = false;
		if (Delay < 500)
		{
		return true;
		}
		this->Data[eCashShop].EventTick = GetTickCount();
		if (this->CheckWindow(CashShop))
		{
		this->CloseWindow(CashShop);
		}
		else
		{
		this->OpenWindow(CashShop);
		}
		}*/
		else if (IsWorkZone(eGuild))
		{
			DWORD Delay = (CurrentTick - this->Data[eGuild].EventTick);
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eGuild].OnClick = true;
				return true;
			}
			this->Data[eGuild].OnClick = false;
			if (Delay < 500)
			{
				return true;
			}
			this->Data[eGuild].EventTick = GetTickCount();
			if (this->CheckWindow(Guild))
			{
				this->CloseWindow(Guild);
			}
			else {
				this->OpenWindow(Guild);
			}
		}
	}
}

#endif

void Interface::DrawMiniBar(float X, float Y, int Count)
{
	pDrawGUI(0x7B72, X, Y, 20.0, 20.0); X += 20;

	for (int i = 0; i < Count; i++)
	{
		pDrawGUI(0x7B73, X, Y, 20.0, 20.0); X += 20;
	}

	pDrawGUI(0x7B74, X, Y, 20.0, 20.0);
}

void Interface::DrawSizeGUI(short ObjectID, float Width, float High, float PosX, float PosY, float SizeW, float SizeH)
{
	float flHigh = High;//100;//this->Data[ObjectID].Height;
	float flWidth = Width;//125;//this->Data[ObjectID].Width;
	float flCritX = 0.0;
	float flCritY = 0.0;
	//float flCritX = flWidth / 96;//(double)(v6 % 10) * Whith / 96;
	//float flCritY = flHigh / 96;//(double)(v6 / 10) * High / 96;
	float flSizeW = SizeW;
	float flSizeH = SizeH;

	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + flWidth;//this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + flHigh;

	pDrawGUFULL(this->Data[ObjectID].ModelID, PosX, PosY, flWidth, flHigh, flCritX, flCritY, flSizeW, flSizeH, 1, 1, 0.0);
}


#if(DEV_PLAYERINFO)

void Interface::DrawTargetInfo()
{
	if (!gObjUser.m_TargetInfo)
	{
		//*return;
	}

	if (pViewAttackTargetID == -1)
	{
		//return;
	}

	lpViewObj lpViewTarget = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewAttackTargetID);

	if (!lpViewTarget || !lpViewTarget->m_Model.Unknown4) return;

	VAngle Angle;
	Angle.X = lpViewTarget->m_Model.VecPosX;
	Angle.Y = lpViewTarget->m_Model.VecPosY;
	Angle.Z = lpViewTarget->m_Model.VecPosZ + lpViewTarget->m_Model.Unknown216.Z + 100.0;

	int PosX = 0;
	int PosY = 0;

	pGetPosFromAngle(&Angle, &PosX, &PosY);

	//PosX -= 50;
	//PosY -= 20;

	//this->DrawBarForm(PosX, PosY, 100, 50, 0, 0, 0, 255);
	pDrawColorButton(0x7880, PosX, PosY, 100, 50, NULL, NULL, Color4f(0, 0, 0, 100));

	this->DrawFormat(eWhite, PosX, PosY + 5, 100, 3, "Target Player Info");

	this->DrawFormat(eWhite, PosX, PosY + 10, 100, 1, "Strength:");
	this->DrawFormat(eWhite, PosX, PosY + 20, 100, 1, "Agility:");
	this->DrawFormat(eWhite, PosX, PosY + 30, 100, 1, "Vitality:");
	this->DrawFormat(eWhite, PosX, PosY + 40, 100, 1, "Energy:");
	this->DrawFormat(eWhite, PosX, PosY + 50, 100, 1, "Command:");

	this->DrawFormat(eWhite, PosX + 50, PosY + 10, 100, 1, "Reset:");
	this->DrawFormat(eWhite, PosX + 50, PosY + 20, 100, 1, "GReset:");
	this->DrawFormat(eWhite, PosX + 50, PosY + 30, 100, 1, "PKLevel:");
	this->DrawFormat(eWhite, PosX + 50, PosY + 40, 100, 1, "Vip:");
	this->DrawFormat(eWhite, PosX + 50, PosY + 50, 100, 1, "Unk:");

}

#endif

#if(DEV_DAMAGE_TABLE)

void Interface::DrawDamageTable()
{
	if (!gDamageTable)
	{
		return;
	}

	if (!gObjUser.m_SecondInfo)
	{
		return;
	}

	if (this->MiniMapCheck() || this->CombinedChecks())
	{
		return;
	}

	//if(g_ExMenuV3.m_Enable && g_ExMenuV3.m_Version == EXMENU_NUMBER::eVERSION_ET)
	//{
	//	if(gInterface.CheckWindowEx(exWinMenuV3))
	//	{
	//		return;
	//	}
	//}

	float Wind = 100;
	float Hig = 10 + 60;

	gInterface.RightMiniInfoY -= Hig;

	float PosX = 535;
	float PosY = gInterface.RightMiniInfoY - 5;

	//this->DrawBarForm(PosX, PosY, 100, 50, 0, 0, 0, 255);
	pDrawColorButton(0x7880, PosX, PosY, Wind, Hig, NULL, NULL, Color4f(0, 0, 0, 100));

	this->DrawFormat(eOrange, PosX, PosY, 100, 3, "Hunting Status p/ Sec");
	gInterface.BindObject(eOFFMODE_PAGEUP, 0x7AA4, 15, 15, -1, -1);


	this->DrawFormat(eWhite, PosX + 20, PosY + 10, 100, 1, "Zen:");
	this->DrawFormat(eWhite, PosX + 20, PosY + 20, 100, 1, "Exp:");
	this->DrawFormat(eWhite, PosX + 20, PosY + 30, 100, 1, "Damage:");
	this->DrawFormat(eWhite, PosX + 20, PosY + 40, 100, 1, "Defence:");
	this->DrawFormat(eWhite, PosX + 20, PosY + 50, 100, 1, "Reflect:");
	this->DrawFormat(eWhite, PosX + 20, PosY + 60, 100, 1, "DamageMax:");

	this->DrawFormat(eYellow, PosX + 70, PosY + 10, 100, 1, "%d", (gObjUser.m_SecondZen / gObjUser.m_SecondCount));
	this->DrawFormat(eYellow, PosX + 70, PosY + 20, 100, 1, "%d", (gObjUser.m_SecondExp / gObjUser.m_SecondCount));
	this->DrawFormat(eYellow, PosX + 70, PosY + 30, 100, 1, "%d", (gObjUser.m_SecondDamage / gObjUser.m_SecondCount));
	this->DrawFormat(eYellow, PosX + 70, PosY + 40, 100, 1, "%d", (gObjUser.m_SecondDefence / gObjUser.m_SecondCount));
	this->DrawFormat(eYellow, PosX + 70, PosY + 50, 100, 1, "%d", (gObjUser.m_SecondReflect / gObjUser.m_SecondCount));
	this->DrawFormat(eYellow, PosX + 70, PosY + 60, 100, 1, "%d", (gObjUser.m_SecondDamageMax));


	//float iX = 535;
	//float iY = 320;
	//float Wind = 100;
	//float Hig = qCount + mCount;

	//float StartiY = 425;
	//// ----
	//StartiY = gInterface.RightMiniInfoY - 5;
	//gInterface.RightMiniInfoY -= Hig;
	//// ----
	//iY = StartiY - Hig;

	//pDrawColorButton(0x7880, iX, iY, Wind, Hig, NULL, NULL, Color4f(0, 0, 0, 100));
}

void Interface::ResetDamageTable()
{
	gObjUser.m_SecondZen = 0;
	gObjUser.m_SecondExp = 0;
	gObjUser.m_SecondDamage = 0;
	gObjUser.m_SecondDefence = 0;
	gObjUser.m_SecondReflect = 0;
	gObjUser.m_SecondCount = 1;
	gObjUser.m_SecondDamageMax = 0;
}

#endif

#if(DEV_INTERFACE_EX700)

void Interface::DrawInterfaceEx700()
{
	//pDrawGUFULL(31409, 0.0, 406.0, 935.0, 110.0, 0.0, 0.0, 1.3, 1.3, 1, 1, 0);
  //double v0; // st6
  //double v1; // st6
  //GLfloat v2; // ST48_4
  //GLfloat v3; // ST34_4
  //float v4; // ST48_4
  //float v5; // ST2C_4
  //float v6; // ST48_4
  //float v7; // ST24_4
  //float v8; // ST48_4
  //char v9; // al
  //char v10; // al
  //char v11; // al
  //char v12; // al
  //char v13; // al
  //int v14; // eax
  //int v15; // ecx
  //int v16; // edx
  //double v17; // st7
  //int v18; // esi
  //signed int v19; // ebx
  //int v20; // eax
  //int v21; // edi
  //float v22; // ST48_4
  //float v23; // [esp+10h] [ebp-40h]
  //float v24; // [esp+18h] [ebp-38h]
  //float v25; // [esp+1Ch] [ebp-34h]
  //float v26; // [esp+1Ch] [ebp-34h]
  //float v27; // [esp+1Ch] [ebp-34h]
  //float v28; // [esp+1Ch] [ebp-34h]
  //float v29; // [esp+1Ch] [ebp-34h]
  //float v30; // [esp+1Ch] [ebp-34h]
  //float v31; // [esp+20h] [ebp-30h]
  //float v32; // [esp+20h] [ebp-30h]
  //float v33; // [esp+20h] [ebp-30h]
  //float v34; // [esp+20h] [ebp-30h]
  //float v35; // [esp+20h] [ebp-30h]
  //float v36; // [esp+20h] [ebp-30h]
  //float v37; // [esp+20h] [ebp-30h]
  //float red; // [esp+24h] [ebp-2Ch]
  //float reda; // [esp+24h] [ebp-2Ch]
  //float redb; // [esp+24h] [ebp-2Ch]
  //float redc; // [esp+24h] [ebp-2Ch]
  //float redd; // [esp+24h] [ebp-2Ch]
  //float rede; // [esp+24h] [ebp-2Ch]
  //float green; // [esp+28h] [ebp-28h]
  //float greena; // [esp+28h] [ebp-28h]
  //float greenb; // [esp+28h] [ebp-28h]
  //float greenc; // [esp+28h] [ebp-28h]
  //float greend; // [esp+28h] [ebp-28h]
  //float greene; // [esp+28h] [ebp-28h]
  //float greenf; // [esp+28h] [ebp-28h]
  //float blue; // [esp+2Ch] [ebp-24h]
  //float v52; // [esp+3Ch] [ebp-14h]
  //float v53; // [esp+40h] [ebp-10h]
  //int v54; // [esp+40h] [ebp-10h]
  //float v55; // [esp+44h] [ebp-Ch]
  //float v56; // [esp+48h] [ebp-8h]
  //float v57; // [esp+4Ch] [ebp-4h]
  //float v58; // [esp+4Ch] [ebp-4h]
  //float v59; // [esp+4Ch] [ebp-4h]

  //if ( *(_DWORD *)dword_102082F8 && dword_102082FC )
  //{
  //  v57 = 0.0;
  //  v52 = 0.0;
  //  if ( dword_10208334 > 0 )
  //    v57 = (double)(unsigned int)(dword_10208334 - *(_DWORD *)ArgList) / (double)(unsigned int)dword_10208334;
  //  if ( dword_1020833C > 0 )
  //    v52 = (double)(unsigned int)(dword_1020833C - *(_DWORD *)dword_10208338) / (double)(unsigned int)dword_1020833C;
  //  pDrawGUFULL(31410, 475.0, 409.0, 65.0, 65.0, 0.0, 0.0, 0.68000001, 0.75, 1, 1, 0);
  //  pDrawGUFULL(31410, 110.0, 409.0, 65.0, 65.0, 0.0, 0.0, 0.68000001, 0.75, 1, 1, 0);
  //  v0 = v57 * 65.0;
  //  v53 = v0 + 409.0;
  //  v55 = 65.0 - v0;
  //  v58 = (1.0 - v57) * 65.0 / 90.0;
  //  v56 = v0 / 90.0;
  //  green = 0.72222221;
  //  v31 = 0.0;
  //  v24 = 65.0;
  //  v23 = 110.0;
  //  if ( (unsigned __int8)MEMORY[0x5EF7BB](MEMORY[0x79B9D48] + 1096, 55) == 1 )
  //    MEMORY[0x5E0C03](
  //      31418,
  //      LODWORD(v23),
  //      LODWORD(v53),
  //      LODWORD(v24),
  //      LODWORD(v55),
  //      LODWORD(v31),
  //      LODWORD(v56),
  //      LODWORD(green),
  //      LODWORD(v58),
  //      1,
  //      1,
  //      0);
  //  else
  //    MEMORY[0x5E0C03](
  //      31412,
  //      LODWORD(v23),
  //      LODWORD(v53),
  //      LODWORD(v24),
  //      LODWORD(v55),
  //      LODWORD(v31),
  //      LODWORD(v56),
  //      LODWORD(green),
  //      LODWORD(v58),
  //      1,
  //      1,
  //      0);
  //  sub_1000F440(432, 3, -1, 115, 45, "%d ", *(_DWORD *)ArgList);
  //  if ( (unsigned __int8)MEMORY[0x6E26A7](110, 409, 65, 65) == 1 )
  //    sub_10010400(110, 400, "Life: %d/%d", *(_DWORD *)ArgList, dword_10208334);
  //  v1 = v52 * 65.0;
  //  v2 = (1.0 - v52) * 65.0 / 90.0;
  //  v3 = v2;
  //  v4 = v1 / 90.0;
  //  v5 = v4;
  //  v6 = 65.0 - v1;
  //  v7 = v6;
  //  v8 = v1 + 409.0;
  //  MEMORY[0x5E0C03](31411, 475.0, LODWORD(v8), 65.0, LODWORD(v7), 0.0, LODWORD(v5), 0.72222221, LODWORD(v3), 1, 1, 0);
  //  sub_1000F440(432, 3, -1, 490, 45, "%d ", *(_DWORD *)dword_10208338);
  //  if ( (unsigned __int8)MEMORY[0x6E26A7](475, 409, 65, 65) == 1 )
  //    sub_10010400(475, 400, "Mana: %d/%d", *(_DWORD *)dword_10208338, dword_1020833C);
  //  pDrawGUFULL(31409, 0.0, 406.0, 935.0, 110.0, 0.0, 0.0, 1.3, 1.3, 1, 1, 0);
  //  greena = 0.94999999;
  //  red = 0.85000002;
  //  v32 = 0.0;
  //  v25 = 0.0;
  //  if ( (unsigned __int8)MEMORY[0x6E26A7](44, 449, 23, 24) == 1 )
  //  {
  //    MEMORY[0x5E0C03](
  //      31420,
  //      44.0,
  //      449.0,
  //      25.0,
  //      26.0,
  //      LODWORD(v25),
  //      LODWORD(v32),
  //      LODWORD(red),
  //      LODWORD(greena),
  //      1,
  //      1,
  //      0);
  //    sub_10010400(48, 439, "Shop");
  //  }
  //  else
  //  {
  //    MEMORY[0x5E0C03](
  //      31420,
  //      44.0,
  //      449.0,
  //      23.0,
  //      24.0,
  //      LODWORD(v25),
  //      LODWORD(v32),
  //      LODWORD(red),
  //      LODWORD(greena),
  //      1,
  //      1,
  //      0);
  //  }
  //  v9 = MEMORY[0x6E26A7](69, 449, 23, 24);
  //  greenb = 0.94999999;
  //  reda = 0.85000002;
  //  v33 = 0.0;
  //  v26 = 0.0;
  //  if ( v9 == 1 )
  //  {
  //    MEMORY[0x5E0C03](
  //      31423,
  //      69.0,
  //      449.0,
  //      25.0,
  //      26.0,
  //      LODWORD(v26),
  //      LODWORD(v33),
  //      LODWORD(reda),
  //      LODWORD(greenb),
  //      1,
  //      1,
  //      0);
  //    sub_10010400(71, 439, "Stats");
  //  }
  //  else
  //  {
  //    MEMORY[0x5E0C03](
  //      31423,
  //      69.0,
  //      449.0,
  //      23.0,
  //      24.0,
  //      LODWORD(v26),
  //      LODWORD(v33),
  //      LODWORD(reda),
  //      LODWORD(greenb),
  //      1,
  //      1,
  //      0);
  //  }
  //  v10 = MEMORY[0x6E26A7](93, 449, 23, 24);
  //  greenc = 0.94999999;
  //  redb = 0.85000002;
  //  v34 = 0.0;
  //  v27 = 0.0;
  //  if ( v10 == 1 )
  //  {
  //    pDrawGUFULL(
  //      31425,
  //      93.0,
  //      450.0,
  //      25.0,
  //      26.0,
  //      LODWORD(v27),
  //      LODWORD(v34),
  //      LODWORD(redb),
  //      LODWORD(greenc),
  //      1,
  //      1,
  //      0);
  //    sub_10010400(92, 439, "Inventory");
  //  }
  //  else
  //  {
  //    pDrawGUFULL(
  //      31425,
  //      93.0,
  //      450.0,
  //      23.0,
  //      24.0,
  //      LODWORD(v27),
  //      LODWORD(v34),
  //      LODWORD(redb),
  //      LODWORD(greenc),
  //      1,
  //      1,
  //      0);
  //  }
  //  v11 = pDrawGUFULL(541, 449, 23, 24);
  //  greend = 0.94999999;
  //  redc = 0.85000002;
  //  v35 = 0.0;
  //  v28 = 0.0;
  //  if ( v11 == 1 )
  //  {
  //    MEMORY[0x5E0C03](
  //      31426,
  //      541.0,
  //      449.0,
  //      25.0,
  //      26.0,
  //      LODWORD(v28),
  //      LODWORD(v35),
  //      LODWORD(redc),
  //      LODWORD(greend),
  //      1,
  //      1,
  //      0);
  //    sub_10010400(541, 439, "Quests");
  //  }
  //  else
  //  {
  //    pDrawGUFULL(
  //      31426,
  //      541.0,
  //      449.0,
  //      23.0,
  //      24.0,
  //      LODWORD(v28),
  //      LODWORD(v35),
  //      LODWORD(redc),
  //      LODWORD(greend),
  //      1,
  //      1,
  //      0);
  //  }
  //  v12 = MEMORY[0x6E26A7](566, 449, 23, 24);
  //  greene = 0.94999999;
  //  redd = 0.85000002;
  //  v36 = 0.0;
  //  v29 = 0.0;
  //  if ( v12 == 1 )
  //  {
  //    pDrawGUFULL(
  //      31427,
  //      566.0,
  //      449.0,
  //      25.0,
  //      26.0,
  //      LODWORD(v29),
  //      LODWORD(v36),
  //      LODWORD(redd),
  //      LODWORD(greene),
  //      1,
  //      1,
  //      0);
  //    sub_10010400(568, 439, "Friend");
  //  }
  //  else
  //  {
  //    MEMORY[0x5E0C03](
  //      31427,
  //      566.0,
  //      449.0,
  //      23.0,
  //      24.0,
  //      LODWORD(v29),
  //      LODWORD(v36),
  //      LODWORD(redd),
  //      LODWORD(greene),
  //      1,
  //      1,
  //      0);
  //  }
  //  v13 = MEMORY[0x6E26A7](591, 449, 23, 24);
  //  greenf = 0.94999999;
  //  rede = 0.85000002;
  //  v37 = 0.0;
  //  v30 = 0.0;
  //  if ( v13 == 1 )
  //  {
  //    MEMORY[0x5E0C03](
  //      31428,
  //      591.0,
  //      449.0,
  //      25.0,
  //      26.0,
  //      LODWORD(v30),
  //      LODWORD(v37),
  //      LODWORD(rede),
  //      LODWORD(greenf),
  //      1,
  //      1,
  //      0);
  //    sub_10010400(594, 439, "Menu");
  //  }
  //  else
  //  {
  //    MEMORY[0x5E0C03](
  //      31428,
  //      591.0,
  //      449.0,
  //      23.0,
  //      24.0,
  //      LODWORD(v30),
  //      LODWORD(v37),
  //      LODWORD(rede),
  //      LODWORD(greenf),
  //      1,
  //      1,
  //      0);
  //  }
  //  v14 = MEMORY[0x750101]();
  //  v15 = MEMORY[0x750192](v14);
  //  v54 = v15;
  //  if ( *(_BYTE *)(*(_DWORD *)dword_102082F8 + 118) )
  //  {
  //    v16 = dword_102082FC;
  //    v59 = 319.0;
  //    v17 = 0.80000001;
  //    v18 = *(_BYTE *)(v15 + 20) != 0 ? 5 : 0;
  //    v19 = 0;
  //    do
  //    {
  //      v20 = v19 + v18 + 1;
  //      v59 = v59 + 23.0;
  //      if ( v20 == 10 )
  //        v20 = 0;
  //      v21 = *(_DWORD *)(v15 + 4 * v20 + 24);
  //      if ( v21 != -1 && ((unsigned int)(v21 - 120) > 3 || *(_DWORD *)(v16 + 592)) )
  //      {
  //        blue = v17;
  //        if ( *(unsigned __int8 *)(v16 + 50) == v21 )
  //        {
  //          glColor3f(1.0, 0.89999998, blue);
  //          v22 = v59 - 2.0;
  //          MEMORY[0x5E0C03](31308, LODWORD(v22), 442.0, 21.0, 28.0, 0.0, 0.0, 1.0, 0.58999997, 1, 1, 0);
  //        }
  //        else
  //        {
  //          glColor3f(0.60000002, 0.69999999, blue);
  //        }
  //        sub_100045A0(v21, v59, 444.0, 17.0, 24.0);
  //        v17 = 0.80000001;
  //        v16 = dword_102082FC;
  //        v15 = v54;
  //      }
  //      ++v19;
  //    }
  //    while ( v19 < 5 );
  //    sub_100045A0(*(unsigned __int8 *)(v16 + 50), 316.0, 443.0, 17.0, 24.0);
  //  }
  //}
}
// 102082FC: using guessed type int dword_102082FC;
// 10208334: using guessed type int dword_10208334;
// 1020833C: using guessed type int dword_1020833C;

//----- (10003FA0) --------------------------------------------------------
//int sub_10003FA0()
//{
//  float v0; // ST28_4
//  float v1; // ST28_4
//  int result; // eax
//  float v3; // [esp+20h] [ebp-4h]
//
//  v3 = 0.0;
//  if ( dword_1020834C > 0 )
//  {
//    v3 = (double)(unsigned int)(dword_1020834C - *(_DWORD *)dword_10208348) / (double)(unsigned int)dword_1020834C;
//    if ( v3 < 0.0 )
//      v3 = 1.0;
//  }
//  glColor4f(0.7098, 0.48234999, 0.0, 1.0);
//  v0 = v3 * 66.0;
//  v1 = v0 + 185.0;
//  MEMORY[0x5E093C](LODWORD(v1));
//  MEMORY[0x5DF41B]();
//  glColor4f(1.0, 1.0, 1.0, 1.0);
//  sub_1000F440(428, 3, -1, (signed int)(185.0 + 0.0), 45, "%d", *(_DWORD *)dword_10208348);
//  result = MEMORY[0x6E26A7](185, 428, 66, 7);
//  if ( (_BYTE)result == 1 )
//    result = sub_10010400(185, 408, "SD: %d/%d", *(_DWORD *)dword_10208348, dword_1020834C);
//  return result;
//}
//// 10003FA0: could not find valid save-restore pair for ebx
//// 10003FA0: could not find valid save-restore pair for esi
//// 1020834C: using guessed type int dword_1020834C;
//
////----- (10004100) --------------------------------------------------------
//int sub_10004100()
//{
//  int result; // eax
//
//  glColor4f(0.57255, 0.2, 0.67058998, 1.0);
//  MEMORY[0x5E093C](407.0);
//  MEMORY[0x5DF41B]();
//  glColor4f(1.0, 1.0, 1.0, 1.0);
//  sub_1000F440(428, 3, -1, 432, 45, "%d", *(_DWORD *)dword_10208340);
//  result = MEMORY[0x6E26A7](407, 428, 66, 7);
//  if ( (_BYTE)result == 1 )
//    result = sub_10010400(407, 408, "AG: %d/%d", *(_DWORD *)dword_10208340, dword_10208344);
//  return result;
//}
//// 10004100: could not find valid save-restore pair for ebx
//// 10004100: could not find valid save-restore pair for esi
//// 10208344: using guessed type int dword_10208344;
//
////----- (10004250) --------------------------------------------------------
//int sub_10004250()
//{
//  int result; // eax
//  int v1; // edi
//  int v2; // esi
//  double v3; // st7
//  double v4; // st6
//  double v5; // st7
//  GLfloat alpha; // ST20_4
//  float v7; // ST30_4
//  int v8; // ecx
//  double v9; // st7
//  double v10; // st6
//  double v11; // st7
//  GLfloat v12; // ST20_4
//  float v13; // ST30_4
//  float v14; // [esp+24h] [ebp-Ch]
//
//  result = *(_DWORD *)dword_102082F8;
//  if ( *(_DWORD *)dword_102082F8 && dword_102082FC )
//  {
//    v14 = 0.0;
//    if ( (unsigned __int8)MEMORY[0x4FD3FA](*(unsigned __int8 *)(*(_DWORD *)dword_102082F8 + 11))
//      && *(_WORD *)(*(_DWORD *)dword_102082F8 + 14) >= 400
//      && MEMORY[0x7FE8D1C] >= 0
//      && (MEMORY[0x7FE8D1C] > 0 || *(_DWORD *)&MEMORY[0x7FE8D18]) )
//    {
//      v1 = dword_1020B5CC[2 * MEMORY[0x7FE8D10]];
//      v2 = dword_1020B5C8[2 * MEMORY[0x7FE8D10]];
//      v3 = (double)(MEMORY[0x7FE8D20] - __PAIR__(v1, v2));
//      if ( v3 <= 0.0 )
//      {
//        v5 = 1.0;
//      }
//      else
//      {
//        v4 = (v3 - (double)(*(_QWORD *)&MEMORY[0x7FE8D18] - __PAIR__(v1, v2))) / v3;
//        v5 = 1.0;
//        v14 = v4;
//        if ( v14 < 0.0 )
//          v14 = 1.0;
//      }
//      alpha = v5;
//      glColor4f(0.2, 0.80000001, 0.2, alpha);
//      v7 = 540.0 - v14 * 540.0;
//      MEMORY[0x5E093C](65.0, 473.0, LODWORD(v7), 3.0, 0.0, 0);
//      MEMORY[0x5DF41B]();
//      glColor4f(1.0, 1.0, 1.0, 1.0);
//      sub_1000F440(469, 3, -1, 612, 15, "%d", MEMORY[0x7FE8D10]);
//      result = MEMORY[0x6E26A7](65, 473, 540, 3);
//      if ( (_BYTE)result == 1 )
//        result = sub_10010400(
//                   165,
//                   458,
//                   "Experience: %I64u/%I64u",
//                   *(_DWORD *)&MEMORY[0x7FE8D18],
//                   MEMORY[0x7FE8D1C],
//                   MEMORY[0x7FE8D20],
//                   MEMORY[0x7FE8D24]);
//    }
//    else
//    {
//      v8 = (int)*(&dword_1020AF7C + *(signed __int16 *)(*(_DWORD *)dword_102082F8 + 14));
//      v9 = (double)(unsigned int)(*(_DWORD *)(*(_DWORD *)dword_102082F8 + 20) - v8);
//      if ( v9 <= 0.0 )
//      {
//        v11 = 1.0;
//      }
//      else
//      {
//        v10 = (v9 - (double)(unsigned int)(*(_DWORD *)(*(_DWORD *)dword_102082F8 + 16) - v8)) / v9;
//        v11 = 1.0;
//        v14 = v10;
//        if ( v14 < 0.0 )
//          v14 = 1.0;
//      }
//      v12 = v11;
//      glColor4f(0.98039216, 4.0392156, 0.0, v12);
//      v13 = 540.0 - v14 * 540.0;
//      MEMORY[0x5E093C](65.0, 473.0, LODWORD(v13), 3.0, 0.0, 0);
//      MEMORY[0x5DF41B]();
//      glColor4f(1.0, 1.0, 1.0, 1.0);
//      sub_1000F440(469, 3, -1, 612, 15, "%d", *(signed __int16 *)(*(_DWORD *)dword_102082F8 + 14));
//      result = MEMORY[0x6E26A7](65, 473, 540, 3);
//      if ( (_BYTE)result == 1 )
//        result = sub_10010400(
//                   165,
//                   458,
//                   "Experience: %d/%d",
//                   *(_DWORD *)(*(_DWORD *)dword_102082F8 + 16),
//                   *(_DWORD *)(*(_DWORD *)dword_102082F8 + 20));
//    }
//  }
//  return result;
//}


#endif

void Interface::DrawItemMarket()
{
#if(DEV_PLAYERSHOP)
	g_ItemMarket.DrawMain();
#endif
}

///////////////////Interface Ex700///////////////////
#if(DEV_INTERFACE_EX700)

void Interface::DrawInterfaceCustom()
{
	//gInterface.DrawIMG(eMainEx700, 36, 413, 1.5, 2.0);
	gInterface.DrawIMG(eMainEx700, 36, 440, 1.5, 2.0);
	gInterface.DrawGUI(eShop1, 76.5, 452);
	gInterface.DrawGUI(eCharacter1, 98.5, 452);
	gInterface.DrawGUI(eInventory1, 120.5, 452);
	gInterface.DrawGUI(eQuest1, 503.5, 452);
	gInterface.DrawGUI(eCommunity1, 525.5, 452);
	gInterface.DrawGUI(eSystem1, 547.5, 452);
}

void Interface::DrawMenuButton()
{
	if (IsWorkZone(eShop2))
	{
		this->DrawToolTip(74, 441, "In-Game Shop");
	}
	if (this->CheckWindow(CashShop))
	{
		gInterface.DrawButton(eShop2, 76.5, 452, 0.0, 0.0);
	}
	if (IsWorkZone(eCharacter2))
	{
		this->DrawToolTip(96.5, 441, "Character");
	}
	if (this->CheckWindow(Character))
	{
		gInterface.DrawButton(eCharacter2, 98.5, 452, 0.0, 0.0);
	}
	if (IsWorkZone(eInventory2))
	{
		this->DrawToolTip(103, 441, "Inventory");
	}
	if (this->CheckWindow(Inventory))
	{
		gInterface.DrawButton(eInventory2, 120.5, 452, 0.0, 0.0);
	}
	if (IsWorkZone(eQuest2))
	{
		this->DrawToolTip(501, 441, "Quest");
	}
	if (this->CheckWindow(Quest))
	{
		gInterface.DrawButton(eQuest2, 503.5, 452, 0.0, 0.0);
	}
	if (IsWorkZone(eCommunity2))
	{
		this->DrawToolTip(523, 441, "Community");
	}
	if (this->CheckWindow(FriendList))
	{
		gInterface.DrawButton(eCommunity2, 525.5, 452, 0.0, 0.0);
	}
	if (IsWorkZone(eSystem2))
	{
		this->DrawToolTip(545, 441, "System");
	}
	if (this->CheckWindow(FastMenu))
	{
		gInterface.DrawButton(eSystem2, 547.5, 452, 0.0, 0.0);
	}

}

void Interface::EventMenuButton(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if (this->CheckWindow(ChaosBox))
	{
		return;
	}

	if (IsWorkZone(eShop1))
	{
		DWORD Delay = (CurrentTick - this->Data[eShop1].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eShop1].OnClick = true;
			return;
		}
		this->Data[eShop1].OnClick = false;
		if (Delay < 1000) {
			return;
		}
		this->Data[eShop1].EventTick = GetTickCount();
		if (this->CheckWindow(CashShop)) {
			this->CloseWindow(CashShop);
		}
		else {
			this->OpenWindow(CashShop);
		}
	}
	else if (IsWorkZone(eCharacter1))
		if (IsWorkZone(eCharacter1))
		{
			DWORD Delay = (CurrentTick - this->Data[eCharacter1].EventTick);
			if (Event == WM_LBUTTONDOWN) {
				this->Data[eCharacter1].OnClick = true;
				return;
			}
			this->Data[eCharacter1].OnClick = false;
			if (Delay < 500) {
				return;
			}
			this->Data[eCharacter1].EventTick = GetTickCount();
			if (this->CheckWindow(Character)) {
				this->CloseWindow(Character);
			}
			else {
				this->OpenWindow(Character);
			}
		}

		else if (IsWorkZone(eInventory1))
		{
			DWORD Delay = (CurrentTick - this->Data[eInventory1].EventTick);
			if (Event == WM_LBUTTONDOWN) {
				this->Data[eInventory1].OnClick = true;
				return;
			}
			this->Data[eInventory1].OnClick = false;
			if (Delay < 500) {
				return;
			}
			this->Data[eInventory1].EventTick = GetTickCount();
			if (this->CheckWindow(Inventory)) {
				this->CloseWindow(Inventory);
			}
			else {
				this->OpenWindow(Inventory);
			}
		}

		else if (IsWorkZone(eQuest1))
		{
			DWORD Delay = (CurrentTick - this->Data[eQuest1].EventTick);
			if (Event == WM_LBUTTONDOWN) {
				this->Data[eQuest1].OnClick = true;
				return;
			}
			this->Data[eQuest1].OnClick = false;
			if (Delay < 500) {
				return;
			}
			this->Data[eQuest2].EventTick = GetTickCount();
			if (this->CheckWindow(Quest)) {
				this->CloseWindow(Quest);
			}
			else {
				this->OpenWindow(Quest);
			}
		}

		else if (IsWorkZone(eCommunity1))
		{
			DWORD Delay = (CurrentTick - this->Data[eCommunity1].EventTick);
			if (Event == WM_LBUTTONDOWN) {
				this->Data[eCommunity1].OnClick = true;
				return;
			}
			this->Data[eCommunity1].OnClick = false;
			if (Delay < 500) {
				return;
			}
			this->Data[eCommunity1].EventTick = GetTickCount();
			if (this->CheckWindow(FriendList)) {
				this->CloseWindow(FriendList);
			}
			else {
				this->OpenWindow(FriendList);
			}
		}

		else if (IsWorkZone(eSystem1))
		{
			DWORD Delay = (CurrentTick - this->Data[eSystem1].EventTick);
			if (Event == WM_LBUTTONDOWN) {
				this->Data[eSystem1].OnClick = true;
				return;
			}
			this->Data[eSystem1].OnClick = false;
			if (Delay < 500) {
				return;
			}
			this->Data[eSystem1].EventTick = GetTickCount();
			if (this->CheckWindow(FastMenu)) {
				this->CloseWindow(FastMenu);
			}
			else {
				this->OpenWindow(FastMenu);
			}
}
}

#endif

void Interface::DrawButton(short ObjectID, float PosX, float PosY, float Width, float Height)
{
	pDrawGUI(this->Data[ObjectID].ModelID, this->Data[ObjectID].X, this->Data[ObjectID].Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	pDrawGUFULL(this->Data[ObjectID].ModelID, this->Data[ObjectID].X, this->Data[ObjectID].Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, ScaleX, ScaleY, 1, 1, 0.0);
}
#if(USERPANEL)
void Interface::DrawUsersPanel()
{
	float PosX = this->GetResizeX(eUSERSPANELBG);
	// ----
	if (this->CheckWindow(CashShop)
		|| this->CheckWindow(SkillTree)
		|| this->CheckWindow(FullMap)
		|| this->CheckWindow(MoveList)
		|| (this->CheckWindow(Inventory)
			&& this->CheckWindow(ExpandInventory)
			&& this->CheckWindow(Store))
		|| (this->CheckWindow(Inventory)
			&& this->CheckWindow(Warehouse)
			&& this->CheckWindow(ExpandWarehouse)))
	{
		return;
}

	// ----
#ifdef __POS_CUR__
	this->DrawFormat(eAncient, gObjUser.m_CursorX + 25, gObjUser.m_CursorY - 10, 100, 1, "X[%d] Y[%d]", gObjUser.m_CursorX, gObjUser.m_CursorY);
#endif

	this->DrawGUI(eUSERSPANELBG, PosX, 0);
	this->DrawGUI(eUSERSPANEL_BUTTON, PosX + 2, 1);
	// ----
	/*if (gCamera.CameraOn)
	{
		this->DrawColoredGUI(eUSERSPANEL_BUTTON, PosX + 2, 1, eGray100);
	}*/

	// ----
	if (IsWorkZone(eUSERSPANEL_BUTTON))
	{
		this->DrawToolTip(PosX + 2 - 5, 25, "Open Users Panel");
		// ----
		if (this->Data[eUSERSPANEL_BUTTON].OnClick)
		{
			this->DrawColoredGUI(eUSERSPANEL_BUTTON, PosX + 2, 1, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		this->DrawColoredGUI(eUSERSPANEL_BUTTON, PosX + 2, 1, pMakeColor(255, 204, 20, 200));
	}

	this->m_GameDraw = true;
}

void Interface::EventUsersPanel(DWORD Event)
{
	if (pPlayerState != GameProcess)
	{
		this->m_GameDraw = false;
		return;
	}

	if (!this->m_GameDraw)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();
	// ----
	if (this->CheckWindow(CashShop)
		|| this->CheckWindow(SkillTree)
		|| this->CheckWindow(FullMap)
		|| this->CheckWindow(MoveList)
		|| (this->CheckWindow(Inventory)
			&& this->CheckWindow(ExpandInventory)
			&& this->CheckWindow(Store))
		|| (this->CheckWindow(Inventory)
			&& this->CheckWindow(Warehouse)
			&& this->CheckWindow(ExpandWarehouse)))
	{
		return;
	}

	if (gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievements))
	{
		return;
	}

	if (gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievementsPower))
	{
		return;
	}

	if (gInterface.CheckWindowEx(ObjWindowsEx::exWinSmithy))
	{
		return;
	}

	if (gInterface.CheckWindowEx(ObjWindowsEx::exWinQuest))
	{
		return;
	}

	if (gInterface.CheckWindowEx(ObjWindowsEx::exWinDungeonSiege))
	{
		return;
	}

	if (gInterface.Data[eRageTable].OnShow == true)
	{
		return;
	}

	int ButtonID = eUSERSPANEL_BUTTON;

	if (IsWorkZone(eUSERSPANEL_BUTTON))
	{
		// ----
		DWORD Delay = (CurrentTick - this->Data[ButtonID].EventTick);
		// ----
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eUSERSPANEL_BUTTON].OnClick = true;
			return;
		}

		this->Data[ButtonID].OnClick = false;

		if (Delay < 1000)
		{
			return;
		}
		// ----
		// ----
		this->Data[ButtonID].EventTick = GetTickCount();

		//SwitchUsersPanel();

		if (gInterface.CheckWindowEx(ObjWindowsEx::exWinMenuV3))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinMenuV3);
		}
		else
		{
			gInterface.OpenWindowEx(ObjWindowsEx::exWinMenuV3);
		}

		// ----
		//return;
	}
}
#endif