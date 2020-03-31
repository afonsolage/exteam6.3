#include "stdafx.h"
#include "Controller.h"
#include "TrayMode.h"
#include "Console.h"
#include "MiniMap.h"
#include "ChatWnd.h"
#include "Protocol.h"
#include "VisualFix.h"
#include "Interface.h"
#include "Item.h"
#include "MakePreviewCharSet.h"
#include "ItemAsm.h"
#include "Camera.h"
#include "RageSystem.h"
#include "User.h"
#include "AntiHack.h"
#include "ConnectEx.h"
#include "SpeedFix.h"
#include "TMemory.h"
#include "Configs.h"
#include "Other.h"
#include "NewHpBar.h"
#include "ChatExpanded.h"
#include "Graphics.h"
#include "QuestSystem.h"
#include "ItemPrice.h"
#include "SocketItem.h"
#include "Monster.h"
#include "DeBug.h"
#include "ItemSmokeEffect.h"
#include "Map.h"
#ifdef _GRAND_SYSTEM_
#include "Bow.h"
#endif
#include "NewPartyBuff.h"
#include "NewParty.h"
#include "Fog.h"
#include "AntiCheat.h"
#include "PartySearch.h"
#include "SecurityScript.h"
#include "PersonalShopEx.h"
#include "AntiCheatPlus.h"
#include "BufferSystem.h"
#include "Smithy.h"
#include "ExLicense.h"
#include "InfoLog.h"
#include "AddPoints.h"
#include "CustomMenu.h"
#include "DonateShop.h"
#include "ItemRank.h"
#include "FileMemory.h"
#include "ServerInfo.h"
#include "WingEffect.h"
#include "EncDec.h"
#include "MapManager.h"
#include "ExText.h"
#include "PremiumSystemEx.h"
#include "PKClear.h"
#include "ItemSetOption.h"
#include "ReferralSystem.h"
#include "ExWinQuestSystem.h"
#include "PickUpItemInfo.h"
#include "Skill.h"
#include "ItemPacket.h"
#include "Effect.h"
#include "CreateEffect.h"
#include "DynamicEffect.h"
#include "Fps.h"
#include "ItemMarket.h"
#include "PetEx.h"
#include "LoadMap.h"
// -------------------------------------------------------------------------------

#ifdef _ANTI_HACK_
DWORD WINAPI Timer(LPVOID lpParam)
{
	Sleep(5000);
	while(true)
	{
		if(bAntiHack)
		{
#ifdef exDEBUG_CODE
			//gConsole.Output(cGREEN,"SystemProcessesScan");
#endif
			SystemProcessesScan();
		}
		
		Sleep(5000);
	}
	return 1;
}
#endif
  // -------------------------------------------------------------------------------

DWORD WINAPI ExTimer(LPVOID lpParam)
{
	Sleep(1000);

	while(true)
	{
		if(gObjUser.Premium > 0)
		{
			gObjUser.Premium--;
		}

		#if(CUSTOM_EMULATOR_KEY)

		gController.ThreadhMouseAutoKey();

		#endif

		Sleep(1000);
	}
	return 1;
}
  // -------------------------------------------------------------------------------

void (*ProcLibrary)(void);


bool GetFalse(int a1)
{
	return true;
}

void LoadDll()
{
	HMODULE hLibrary = LoadLibrary("Effect.dll");

	if(hLibrary)
	{
		ProcLibrary = (void (*)(void))GetProcAddress(hLibrary, "ikennylee");

		if(ProcLibrary)
		{
			ProcLibrary();
		}
		else
		{
			MessageBox(0, "GetProc Error Effect.dll", "GetProc Error", ERROR);
		}
	}
	else
	{
		MessageBox(0, "Load Error Effect.dll", "Load Error", ERROR);
	}
}

void startup_app(LPCTSTR lpApplicationName)
{
   // additional information
   STARTUPINFO si;     
   PROCESS_INFORMATION pi;

   // set the size of the structures
   ZeroMemory( &si, sizeof(si) );
   si.cb = sizeof(si);
   ZeroMemory( &pi, sizeof(pi) );

  // start the program up
  CreateProcess( lpApplicationName,   // the path
    NULL,        // Command line
    NULL,           // Process handle not inheritable
    NULL,           // Thread handle not inheritable
    FALSE,          // Set handle inheritance to FALSE
    0,              // No creation flags
    NULL,           // Use parent's environment block
    NULL,           // Use parent's starting directory 
    &si,            // Pointer to STARTUPINFO structure
    &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}

bool ExInited = false;

extern "C" __declspec(dllexport)void ExInit()
{
	if (ExInited)
		return;

	ExInited = true;

	DWORD OldProtect;
	// ----
	if(VirtualProtect(LPVOID(0x401000),0xD21FFF,PAGE_EXECUTE_READWRITE,&OldProtect))
	{

		//Minimap hover
		SetByte((LPVOID)(0x0082BAB5-0x150+1),0); // Включение отображения всех нпц на миникарте
		SetRange((LPVOID)(0x0082BAB7-0x150),0x2,ASM::NOP);
		SetRange((LPVOID)(0x0082B7FA-0x150),0xA0,ASM::NOP);

#if(ENABLE_DEBUG)
		DeBugLoad();
#endif
#if(ENABLE_ENCODER)
		g_EncDec.Load();
#endif

#ifdef PROTECT
	if( VMProtectIsDebuggerPresent(TRUE) != 0 )
	{
		MessageBox(0, "Protect system found debugger, process will be closed", "ExCheatGuard", ERROR);
		ExitProcess(0);
	}
#endif
#if(ENABLE_EXPROTECTOR1)
	if(!LoadLibrary("wz_up.dll"))
	{
		MessageBox(0, "Protect", "Protect Client Error", ERROR);
		ExitProcess(0);
	}

	//HMODULE hLibrary = LoadLibrary("Effect.dll");

#endif
#if(ENABLE_EXPROTECTOR2)
	if(!LoadLibrary("Protect.dll"))
	{
		MessageBox(0, "Protect", "Protect Client Error", ERROR);
		ExitProcess(0);
	}

	//HMODULE hLibrary = LoadLibrary("Effect.dll");

#endif
	//gConfig.Configs();

#ifdef _LAUNCHER_
	if(gConfig.LauncherActive == 1)
	{
		char **	Command	= 0;
		CommandLineToArg(GetCommandLine(), &Command);

		DWORD dwAttrib = GetFileAttributes("Launcher.tmp");

		if (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) 
		{
			DeleteFileA("Launcher.exe");
			rename("Launcher.tmp", "Launcher.exe");
			startup_app("Launcher.exe");
			ExitProcess(0);
		}
		
		if( strcmp(gConfig.LauncherParameters, Command[1]) )
		{
			gConsole.Output(cMAGENTA, "%s != %s (%s)", gConfig.LauncherParameters, Command[1], GetCommandLine());
			startup_app("Launcher.exe");
			ExitProcess(0);
		}
	}
#endif

#if(ANTI_CHEAT_PLUS==TRUE)
	g_AntiCheatPlus.Load();
#endif

#if(ANTI_CHEAT==TRUE) 
#endif
#if(DLL_EX_ANTI_CHEAT==TRUE)
#endif
	// ----
	LoadLibrary("ttlci.dll");
#if(THINNAKORN_MAC)
	LoadLibrary("vcorp.dll");
	LoadLibrary("EliteBlock.dll");
#endif
	// ----
	gController.Load();

	gStart.Load();

	gTrayMode.Load();
	gProtocol.Load();



	gInterface.Load();
	gCamera.Load();
#if(exCHATWND)
	ChatWndHooks();
#endif
	initEffectSkil();
	gVisualFix.InitVisualFix();


	gItem.Load();

	InitItemAsm();
#if(exPRIVIEWESET)
	gMakePreviewCharSet.Load();
#endif
//#ifdef exRAGESYSTEM
	gRageSystem.Load();
//#endif
	gObjUser.Load();
#if(exRECONNECT)
	gConnectEx.Load();
#endif
#if(_SPEED_FIX_==TRUE)
	InitAttackSpeed();
#endif
//#if(v103K)
	g_MiniMap.Load();
//#endif
#ifdef NEW_HP_BAR
	gViewePortInfo.InitNewHpBar();
#endif
	gChatExpanded.Load();
#if(NEW_GLOW_EFFECT)
	if(gGlowEffect)
	{
		gGraphics.Load();
	}
#endif
#ifdef _ITEM_PRICE_MANAGER_
	gItemPrice.Load();
#endif
	gSocketItem.Load();
#ifdef _NEW_MONSTER_
	//gMonster.Load();
#endif
#ifdef exDEBUG_CODE
	//DeBug_Init();
#endif
#if NEW_PARTY_BUFF == TRUE
	g_NewPartyBuff.Load();
#endif
//#if _NEW_PARTY_SYSTEM_ == TRUE
	{
		g_Party.Load();
	}
//#endif
#if(CUSTOM_PARTY_SEARCH==TRUE)
		g_PartySearch.Load();
#endif
//#if(CUSTOM_PERONAL_EX==TRUE)
		g_PersonalShopEx.Init();
//#endif
#if(CUSTOM_NPC_BUFFER==TRUE)
		g_BufferSystem.Load();
#endif
#if(CUSTOM_SMITHY == TRUE)
		g_Smithy.Load();
#endif
#if(CUSTOM_EX_CHAT==TRUE)
		g_InfoLog.Load();
#endif
#if(CUSTOM_MENU)
		g_CustomMenu.Load();
#endif
#if(CUSTOM_ITEM_RANK==TRUE)
		g_ItemRank.Load();
#endif
#ifdef _ANTI_HACK_
	CloseHandle(CreateThread(NULL,0,Timer,NULL,0,NULL));
#endif
	CloseHandle(CreateThread(NULL,0,ExTimer,NULL,0,NULL));

#if(ENABLE_FILEMEMORY)
	FileMemoryLoad();
#endif

#if(CUSTOM_NEW_MAP)
	//g_Map.Load();
#endif
//#if(BASSREFLEXIVE)
	g_ServerInfo.Load();
//#endif
#if(CUSTOM_WINGSEFFECT)
	g_WingEffect.Load();
#endif
#if(ENABLE_CHANGE)
	g_Text.Load();
#endif
#if(CUSTOM_MAP_MANAGER)
	g_MapManager.Load();
#endif
#if(CUSTOM_EXTEXT)
	g_ExText.Load();
#endif
#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
	g_PremiumSystemEx.Load();
#endif
#if(CUSTOM_PKCLEAR_NPC==TRUE)
	g_PKClear.Load();
#endif
#if(CUSTOM_REFERAL_SYSTEM)
	g_ReferralSystem.Load();
#endif

	gMonster.ReadName(".\\Data\\Local\\Eng\\Npcname(eng).txt");

#if(CUSTOM_EX_QUEST_SYSTEM==TRUE)
	g_ExWinQuestSystem.Load();
#endif	
#if(CUSTOM_PICKUP_ITEM_INFO)
	g_PickUpItemInfo.Load();
#endif
#if(DEV_SKILL)
	g_Skill.Load();
#endif
#if(DEV_PACKET_ITEM)
	g_ItemPacket.Load();
#endif

#if(DEBUG_FPS)
	g_Fps.Load();
#endif
gLoadMap.Load();
#if(ENABLE_TEST)
	//-> Fix BC Master Disable
	//SetByte((LPVOID)(0x008742AC+3), 0x07);
	//SetByte((LPVOID)(0x00874C04+6), 0x07);
	//SetRange((LPVOID)(0x00874EBF), 5, ASM::NOP);
#endif

#if(ENABLE_TEST)
			//SetRange((LPVOID)0x0080F6AE, 5, ASM::NOP);	//user bar
			//SetByte((LPVOID)(0x004D9746+3), 0xE0);		//gl draw 480px

			//SetByte((LPVOID)(0x0080F683), 0xE9);	//disable userbar
			//SetByte((LPVOID)(0x0080F683+1), 0x97);
			//SetByte((LPVOID)(0x0080F683+2), 0x00);
			//SetByte((LPVOID)(0x0080F683+3), 0x00);
			//SetByte((LPVOID)(0x0080F683+4), 0x00);

	

			//004D9746
	//0080F6AE
	//420220 - bitmap load
	//6363D0 - gl vieweport
			//004D9746 - 1b0
#endif
#if(DEV_EFFECT)
	gEffect.Load();
#endif
#if(DEV_EFFECT2)
	gCreateEffect.Load();
#endif
		//#if(ENABLE_ITEMSETOPTION)
		//g_ItemSetOption.Load();
		//#endif
		//007E1B7F
		//SHL EDX,9 <<
		//SAR ECX,7 >>
		//007E1B75
		//C1 E1 04

		//007E1B75 nop
		//SetRange((LPVOID)0x007E1B75, 3, ASM::NOP);
		//SetRange((LPVOID)0x007E519C, 6, ASM::NOP);	//ItemAddOption in Wings

	
		//SetRange((LPVOID)0x007E5188, 20, ASM::NOP);	// ItemAddOption in Wings

		//007E5195 -> CALL CHECK WINGS

		//SetOp((LPVOID)0x007E3FC0, GetFalse, ASM::CALL);
		//SetOp((LPVOID)0x007E4766, GetFalse, ASM::CALL);
		//SetOp((LPVOID)0x007E5195, GetFalse, ASM::CALL);

	
	

		//skill
		//006D81CC
		// 006D80F0 - nop 2 

		#if(ENABLE_CHECK)
		//Credit Shop
		//SetRange((LPVOID)0x007D3C1C, 5, ASM::NOP);	
		//SetOp((LPVOID)0x007D3C1C, _007D3C16, ASM::JMP);
		//SetRange((LPVOID)0x00811D6F, 5, ASM::NOP);	
		//SetOp((LPVOID)0x00811D6F, _00811D69, ASM::JMP);
		//SetOp((LPVOID)0x007D3C1C, (LPVOID)0x00811F40, ASM::JMP);	// disable key X
		 SetOp((LPVOID)0x007D3C16, (LPVOID)0x007D3DF5, ASM::JMP);	// disable key X
		 
		//SetRange((LPVOID)0x00784B77, 5, ASM::NOP);
		#endif
		#if(DEV_PLAYERSHOP)
		g_ItemMarket.Load();
		#endif
		#if(ENABLE_PETEX)
		g_PetEx.Load();
		#endif

	}
	else
	{
		
	}
}

#if(ENABLE_RAM_MIN)
void RamOptimization(LPVOID lpThreadParameter) 
{ 
	HANDLE hCurrentProcess = NULL;

	while(TRUE) 
	{ 
		Sleep(5000);

		hCurrentProcess = GetCurrentProcess();

		SetProcessWorkingSetSize(hCurrentProcess, 0xFFFFFFFF, 0xFFFFFFFF); 

		SetThreadPriority(hCurrentProcess, THREAD_BASE_PRIORITY_MAX); 
	} 
}
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
#if(ENABLE_RAM_MIN)
			CreateThread (0, 0, (LPTHREAD_START_ROUTINE)RamOptimization, 0, 0 , 0);
#endif

#if(EX_LICENSE==TRUE)
			g_ExLicense.Load();
#endif
			gController.Instance = hModule;
#if(exCONSOLE)
			gConsole.InitCore();
#endif
			gConfig.LoadGame();
//#if(NEW_QUEST_SYSTEM)
			gQuestSystem.LoadGame();
//#endif
			if (gFogEffect)
			{
				g_Fog.Load();
			}

			ExInit();

#if(SECURITY_SCRIPT==TRUE)


//	if(!strcmp(a1,"Data\\World1\\EncTerrain1.map"))
	{
	//	Packed = true;
	}

	//if(Packed==true)
	{
		//g_SecurityScript.ReadScript("Data\\World1\\EncTerrain1.obj");
		//g_SecurityScript.WriteScript("Data\\World1\\EncTerrain1.obj");
	}

	//Result = sub_5D6E50(a1);

	//if(Packed==true)
	{
		//g_SecurityScript.WriteScript(a1);
	}

			//g_SecurityScript.Test();
#endif
		}
		break;
	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
		
	case DLL_PROCESS_DETACH:
		{
			gConfig.SaveGame();
//#if(NEW_QUEST_SYSTEM)
			gQuestSystem.SaveGame();
//#endif
			if (gFogEffect)
			{
				g_Fog.End();
			}
#if(SECURITY_SCRIPT==TRUE)

	{
		//g_SecurityScript.WriteScript("Data\\World1\\EncTerrain1.obj");
	}

#endif
	//ExitProcess(0);
		}
		break;
	case WM_CLOSE:
		//ExitProcess(0);
		break;
	}
	return true;
}
  // -------------------------------------------------------------------------------

