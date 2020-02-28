#include "stdafx.h"
#include "AntiCheat.h"
#include "Splash.h"
#include "TMemory.h"
#include "Interface.h"
#include "Console.h"
//---------------------------------------------------------------------------
#if(ANTI_CHEAT_OLD==TRUE)

AntiCheat g_AntiCheat;
//---------------------------------------------------------------------------

void AntiCheat::Load()
{
	this->MsgBox = true;
#if(ONE_WINDOWS==TRUE)
	CreateMutexA(NULL, TRUE, "MuOnline");
	if( GetLastError() == ERROR_ALREADY_EXISTS )
	{
		ExitProcess(0);
	}
#endif
#if(LOG_ENABLE==TRUE)
	CreateDirectory("Log", 0);
#endif

#if(ANTI_CHEAT_DEBUG==TRUE)
	//gConsole.Output(cGREY, "Splash Start");
#endif
	this->Splash();
#if(ANTI_CHEAT_DEBUG==TRUE)
	//gConsole.Output(cGREY, "Dump Start");
#endif
	this->Dump();
	this->Main();

#if(ANTI_CHEAT_DEBUG==TRUE)
	//gConsole.Output(cGREY, "Loaded Start");
#endif

	SetRange((LPVOID)0x00788F9D, 5, ASM::NOP);
	SetOp((LPVOID)0x00788F9D,  (LPVOID)this->AntiElite, ASM::CALL);

	this->MsgBox = false;

	CloseHandle(CreateThread(NULL,0,LPTHREAD_START_ROUTINE(Timer),NULL,0,NULL));
	//CloseHandle(CreateThread(NULL,0,LPTHREAD_START_ROUTINE(Timer2),NULL,0,NULL));
}
//---------------------------------------------------------------------------

void AntiCheat::Main()
{
#if(ANTI_CHEAT_DEBUG==TRUE)
	if(this->MsgBox == true)
		//gConsole.Output(cGREY, "ClassWindow Start");
#endif
	this->ClassWindow();
#if(ANTI_CHEAT_DEBUG==TRUE)
	if(this->MsgBox == true)
		gConsole.Output(cGREY, "Inject Start");
#endif
	this->Inject();
#if(ANTI_CHEAT_DEBUG==TRUE)
	if(this->MsgBox == true)
		gConsole.Output(cGREY, "ProcessID Start");
#endif
	this->ProcessID();
#if(ANTI_CHEAT_DEBUG==TRUE)
	if(this->MsgBox == true)
		gConsole.Output(cGREY, "TitleWindow Start");
#endif
	this->TitleWindow();
}
//---------------------------------------------------------------------------

void AntiCheat::Timer(LPVOID lpParam)
{
	while(true)
	{
		g_AntiCheat.Main();
		Sleep(10000);
	}
}
//---------------------------------------------------------------------------

void AntiCheat::Timer2(LPVOID lpParam)
{
	while(true)
	{
		g_AntiCheat.Dump();
		Sleep(10000);
	}
}
//---------------------------------------------------------------------------

void AntiCheat::Write(LPSTR Text, ...)
{
	char TimeBuff[100] = { 0 };
	char TextBuff[3000] = { 0 };
	char LogBuff[5000] = { 0 };
	// ----
	va_list ArgPointer;
    va_start(ArgPointer, Text);
	vsprintf(TextBuff, Text, ArgPointer);
	va_end(ArgPointer);
	// ----
#if(LOG_ENABLE==TRUE)
	SYSTEMTIME Time;
	GetLocalTime(&Time);
	sprintf_s(TimeBuff, "[%02d:%02d:%02d] ", Time.wHour, Time.wMinute, Time.wSecond);
	sprintf_s(LogBuff, "%s %s\n", TimeBuff, TextBuff);
	char LogFile[MAX_PATH] = { 0 };
	sprintf_s(LogFile, ".\\InfoLog\\[%02d-%02d-%04d] Anti-Cheat System.log", Time.wDay, Time.wMonth, Time.wYear);
	FILE* Input = fopen(LogFile, "a");
	fprintf(Input, LogBuff);
	fclose(Input);
#endif
//#if(MESSAGE_ENABLE==TRUE)
	if(this->MsgBox == true)
	{
		MessageBoxA(NULL, TextBuff, AH_TITLE, ERROR);
		Sleep(3000);
	}
//#endif
}
//---------------------------------------------------------------------------

void AntiCheat::ClassWindow()
{
#if(CLASS_WINDOW_ENABLE==TRUE)
	//ClasseWindow("ConsoleWindowClass"); // Prompt de comando 
	//ClasseWindow("ThunderRT6FormDC");   // autoclic Klic0r
	this->ClassWindowCheck("PROCEXPL");             // Process explorer
	this->ClassWindowCheck("TreeListWindowClass");  // Process explorer (Process windows)
	this->ClassWindowCheck("ProcessHacker");        // Process Hacker	
	this->ClassWindowCheck("PhTreeNew");            // Process Hakcer (Process windows)
	this->ClassWindowCheck("RegEdit_RegEdit");      // Regedit
	this->ClassWindowCheck("0x150114 (1376532)");   // Win 7 - System configuration
	this->ClassWindowCheck("SysListView32");        // Lista de processos do process explorer
	this->ClassWindowCheck("Tmb");
	this->ClassWindowCheck("TformSettings");
	this->ClassWindowCheck("Afx:400000:8:10011:0:20575");
	this->ClassWindowCheck("TWildProxyMain");
	this->ClassWindowCheck("TUserdefinedform");
	this->ClassWindowCheck("TformAddressChange");
	this->ClassWindowCheck("TMemoryBrowser");
	this->ClassWindowCheck("TFoundCodeDialog");

	this->ClassWindowCheck("OllyDbg");
	this->ClassWindowCheck("SandboxieControlWndClass");
	//this->Check("#32770");
#endif
}
//---------------------------------------------------------------------------

void AntiCheat::ClassWindowCheck(LPCSTR WindowClasse)
{
	
	WinClasse = FindWindowExA(NULL,NULL,WindowClasse,NULL);
	if( WinClasse > 0)
	{
		this->Write(CLASS_WINDOW_TEXT,WindowClasse);
		ExitProcess(0);
	}
}
//---------------------------------------------------------------------------

bool AntiCheat::DumpCheck(HANDLE hProcess) 
{
	for( int i = 0; i < MAX_PROCESS_DUMP; i++ )
	{
		char aTmpBuffer[MAX_DUMP_SIZE];
		SIZE_T aBytesRead = 0;
		ReadProcessMemory(hProcess, (LPCVOID)g_ProcessesDumps[i].m_aOffset, (LPVOID)aTmpBuffer, sizeof(aTmpBuffer), &aBytesRead);

		if(memcmp(aTmpBuffer, g_ProcessesDumps[i].m_aMemDump, MAX_DUMP_SIZE) == 0)
		{
			this->Write(DAMP_LOG_TEXT, g_ProcessesDumps[i].Name);
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------

void AntiCheat::Dump() 
{
#if(DUMP_SCAN_ENABLE==TRUE)
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if(Process32First(hProcessSnap, &pe32))
		{
			do
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if(hProcess != NULL)
				{
					if(this->DumpCheck(hProcess))
					{
						ExitProcess(0);
					}
				}
			}
			while(Process32Next(hProcessSnap, &pe32));
		}
	}
	CloseHandle(hProcessSnap);
#endif
}
//---------------------------------------------------------------------------

void AntiCheat::Inject()
{
#if(INJECT_ENABLE==TRUE)
     // [NAME.extension] Are NON case-sensitive.
	this->InjectCheck("speedhack.dll");
	this->InjectCheck("speed-hack.dll");
	this->InjectCheck("speed-hack.dll");
	this->InjectCheck("speed_hack.dll");
	this->InjectCheck("hack_speed.dll");
	this->InjectCheck("hack-speed.dll");
	this->InjectCheck("hackspeed.dll");
	this->InjectCheck("hack.dll");
	this->InjectCheck("wpepro.dll");
	this->InjectCheck("Cr4ck3r.dll");
	this->InjectCheck("wpeprospy.dll");
    this->InjectCheck("engine.dll");
	this->InjectCheck("CheatEngine.dll");
	this->InjectCheck("c.e.dll");
	this->InjectCheck("cheat.dll");
    this->InjectCheck("smoll.dll");
#endif
}
//---------------------------------------------------------------------------

void AntiCheat::InjectCheck(LPCSTR InjectHandle)
{
	if(GetModuleHandle(InjectHandle))
	{
		this->Write(INJECT_TEXT,InjectHandle);
		ExitProcess(0);
	}
}
//---------------------------------------------------------------------------

void AntiCheat::ProcessID()
{
#if(PROCESS_ID_ENABLE==TRUE)
	this->ProcessIDCheck("ollydbg.exe*32");
	this->ProcessIDCheck("ollydbg.exe");
	this->ProcessIDCheck("bvkhex.exe");
    this->ProcessIDCheck("cheatengine-x86_64.exe");
	this->ProcessIDCheck("HxD.exe");
	this->ProcessIDCheck("procexp2.exe");
	this->ProcessIDCheck("Hide Toolz3.3.3.exe");
	this->ProcessIDCheck("SbieSvc.exe");    // < sandbox 
	this->ProcessIDCheck("SbieSvc*32.exe"); // < sandbox 
	this->ProcessIDCheck("SbieSvc*32.exe"); // < sandbox 
	this->ProcessIDCheck("SbieCtrl.exe");   // < sandbox 
	this->ProcessIDCheck("Start.exe");      // < sandbox 

	this->ProcessIDCheck("GustyMU-Win32.exe");
	this->ProcessIDCheck("SbieCtrl.exe");
#endif
}
//---------------------------------------------------------------------------

void AntiCheat::ProcessIDCheck(LPCSTR ProcName)
{
	PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;

	pe32.dwSize = sizeof( PROCESSENTRY32 );
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

    if( Process32First( hSnapshot, &pe32 ))
	{
        do
		{
            if( strcmp( pe32.szExeFile, ProcName ) == 0 )
            {
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);  // Close detected process
				TerminateProcess(hProcess,NULL);                                               // Close detected process

				this->Write(PROCESS_ID_TEXT, ProcName);
				ExitProcess(0);	
            }
        }
		while( Process32Next( hSnapshot, &pe32 ) );
    }
    if( hSnapshot != INVALID_HANDLE_VALUE )
	{
        CloseHandle( hSnapshot );   
	}
}
//---------------------------------------------------------------------------

void AntiCheat::TitleWindow()
{
#if(TITLE_WINDOW_ENABLE== TRUE)
	this->TitleWindowCheck("!xSpeed 6.0");
	this->TitleWindowCheck("Process Explorer");
	this->TitleWindowCheck("!xSpeed 6.0");
	this->TitleWindowCheck("!xSpeed.net 2");
	this->TitleWindowCheck("!xSpeed.net 3");
	this->TitleWindowCheck("!xSpeed.net 6");
	this->TitleWindowCheck("!xSpeed.net");
	this->TitleWindowCheck("!xSpeedPro");
	this->TitleWindowCheck("!xpeed.net 1.41");
	this->TitleWindowCheck("99QJ MU Bot");
	this->TitleWindowCheck("AE Bot v1.0 beta");
	this->TitleWindowCheck("AIO Bots");
	this->TitleWindowCheck("Add address");
	this->TitleWindowCheck("ArtMoney PRO v7.27");
	this->TitleWindowCheck("ArtMoney SE v7.31");
	this->TitleWindowCheck("ArtMoney SE v7.32");
	this->TitleWindowCheck("Auto Combo");
	this->TitleWindowCheck("Auto-Repairer");
	this->TitleWindowCheck("AutoBuff D-C");
	this->TitleWindowCheck("AutoBuff");
	this->TitleWindowCheck("AutoCombo D-C By WANTED");
	this->TitleWindowCheck("AutoCombo");
	this->TitleWindowCheck("Auto_Buff v5 Hack Rat");
	this->TitleWindowCheck("Autoprision");
	this->TitleWindowCheck("Bot MG-DK-ELF");
	this->TitleWindowCheck("CapoteCheatfreadcompany");
	this->TitleWindowCheck("Capotecheat");
	this->TitleWindowCheck("Capotecheat(deltacholl)");
	this->TitleWindowCheck("Catastrophe v0.1");
	this->TitleWindowCheck("Catastrophe v1.2");
	this->TitleWindowCheck("Catastrophe");
	this->TitleWindowCheck("Chaos Bot 2.1.0");
	this->TitleWindowCheck("CharBlaster");
	this->TitleWindowCheck("CharEditor (www.darkhacker.com.ar)");
	this->TitleWindowCheck("Cheat Engine 5.0");
	this->TitleWindowCheck("Cheat Engine 5.1");
	this->TitleWindowCheck("Cheat Engine 5.1.1");
	this->TitleWindowCheck("Cheat Engine 5.2");
	this->TitleWindowCheck("Cheat Engine 5.3");
	this->TitleWindowCheck("Cheat Engine 5.4");
	this->TitleWindowCheck("Cheat Engine 5.5");
	this->TitleWindowCheck("Cheat Engine 5.6");
	this->TitleWindowCheck("Cheat Engine 5.6.1");
	this->TitleWindowCheck("Cheat Engine 6.0");
	this->TitleWindowCheck("Cheat Engine 6.1");
	this->TitleWindowCheck("Cheat Engine 6.4");
	this->TitleWindowCheck("Cheat Engine");
	this->TitleWindowCheck("Cheat Happens v3.95b1/b2");
	this->TitleWindowCheck("Cheat Happens v3.95b3");
	this->TitleWindowCheck("Cheat Happens v3.96b2");
	this->TitleWindowCheck("Cheat Happens v3.9b1");
	this->TitleWindowCheck("Cheat Happens");
	this->TitleWindowCheck("Cheat Master");
	this->TitleWindowCheck("Cheat4Fun v0.9 Beta");
	this->TitleWindowCheck("Cheat4Fun");
	this->TitleWindowCheck("CheatHappens");
	this->TitleWindowCheck("Codehitcz");
	this->TitleWindowCheck("Created processes");
	this->TitleWindowCheck("D-C Bypass");
	this->TitleWindowCheck("D-C DupeHack 1.0");
	this->TitleWindowCheck("D-C Master Inject v1.0 by WANTED");
	this->TitleWindowCheck("DC Mu 1.04x _F3R_ Hack");
	this->TitleWindowCheck("DC-BYPASS By DjCheats  Public Vercion");
	this->TitleWindowCheck("DK(AE)MultiStrikeByDude");
	this->TitleWindowCheck("DarkCheats Mu Ar");
	this->TitleWindowCheck("DarkLord Bot v1.1");
	this->TitleWindowCheck("DarkyStats (www.darkhacker.com.ar)");
	this->TitleWindowCheck("Dizzys Auto Buff");
	this->TitleWindowCheck("Dupe-Full");
	this->TitleWindowCheck("Easy As MuPie");
	this->TitleWindowCheck("Esperando Mu Online");
	this->TitleWindowCheck("FunnyZhyper v5");
	this->TitleWindowCheck("FunnyZhyper");
	this->TitleWindowCheck("Game Speed Adjuster");
	this->TitleWindowCheck("Game Speed Changer");
	this->TitleWindowCheck("GodMode");
	this->TitleWindowCheck("Godlike");
	this->TitleWindowCheck("HahaMu 1.16");
	this->TitleWindowCheck("Hasty MU 0.3");
	this->TitleWindowCheck("Hasty MU");
	this->TitleWindowCheck("HastyMU");
	this->TitleWindowCheck("HastyMu 1.1.0 NEW");
	this->TitleWindowCheck("HastyMu v0.1");
	this->TitleWindowCheck("HastyMu v0.2");
	this->TitleWindowCheck("HastyMu v0.3");
	this->TitleWindowCheck("HastyMu");
	this->TitleWindowCheck("HiDeToolz");
	this->TitleWindowCheck("HideToolz");
	this->TitleWindowCheck("Hit Count");
	this->TitleWindowCheck("Hit Hack");
	this->TitleWindowCheck("Injector");
	this->TitleWindowCheck("Janopn Mini Multi Cheat v0.1");
	this->TitleWindowCheck("Jewel Drop Beta");
	this->TitleWindowCheck("JoyToKey");
	this->TitleWindowCheck("Kill");
	this->TitleWindowCheck("Lipsum v1 and v2");
	this->TitleWindowCheck("Lipsum_v2");
	this->TitleWindowCheck("List");
	this->TitleWindowCheck("Load File");
	this->TitleWindowCheck("Load");
	this->TitleWindowCheck("MJB Perfect DL Bot");
	this->TitleWindowCheck("MLEngine");
	this->TitleWindowCheck("MU Lite Trainer");
	this->TitleWindowCheck("MU Utilidades");
	this->TitleWindowCheck("MU-SS4 Speed Hack 1.2");
	this->TitleWindowCheck("MUSH");
	this->TitleWindowCheck("Minimize");	//?
	this->TitleWindowCheck("ModzMu");
	this->TitleWindowCheck("MoonLight");
	this->TitleWindowCheck("Mu Cheater 16");
	this->TitleWindowCheck("Mu Philiphinas Cheat II");
	this->TitleWindowCheck("Mu Pie Beta");
	this->TitleWindowCheck("Mu Pirata MMHack v0.2 by janopn");
	this->TitleWindowCheck("Mu proxy");
	this->TitleWindowCheck("MuBot");
	this->TitleWindowCheck("MuCheat");
	this->TitleWindowCheck("MuHackRm");
	this->TitleWindowCheck("MuOnline Speed Hack");
	this->TitleWindowCheck("MuPie HG v2");
	this->TitleWindowCheck("MuPie HG v3");
	this->TitleWindowCheck("MuPie v2 Beta");
	this->TitleWindowCheck("MuPieHGV2");
	this->TitleWindowCheck("MuPieHGV3");
	this->TitleWindowCheck("MuPieX");
	this->TitleWindowCheck("MuPie_v2Beta");
	this->TitleWindowCheck("MuProxy");
	this->TitleWindowCheck("Mugster Bot");
	this->TitleWindowCheck("Mupie Minimizer");
	this->TitleWindowCheck("Mush");
	this->TitleWindowCheck("NoNameMini");
	this->TitleWindowCheck("Nsauditor 1.9.1");
	this->TitleWindowCheck("Olly Debugger");
	this->TitleWindowCheck("Overclock Menu");
	this->TitleWindowCheck("Perfect AutoPotion");
	this->TitleWindowCheck("Permit");
	this->TitleWindowCheck("PeruCheats");
	this->TitleWindowCheck("Process Explorer 11.33");
	this->TitleWindowCheck("Process Explorer");
	this->TitleWindowCheck("ProxCheatsX 2.0 - Acacias");
	this->TitleWindowCheck("RPE");
	this->TitleWindowCheck("Razor Code Only");
	this->TitleWindowCheck("Razor Code");
	this->TitleWindowCheck("Snd Bot 1.5");
	this->TitleWindowCheck("Speed Gear 5");
	this->TitleWindowCheck("Speed Gear 6");
	this->TitleWindowCheck("Speed Gear v5.00");
	this->TitleWindowCheck("Speed Gear");
	this->TitleWindowCheck("Speed Hack 99.62t");
	this->TitleWindowCheck("Speed Hack Simplifier 1.0-1.2");
	this->TitleWindowCheck("Speed Hack Simplifier");
	this->TitleWindowCheck("Speed Hack");
	this->TitleWindowCheck("Speed Hacker");
	this->TitleWindowCheck("SpeedGear");
	this->TitleWindowCheck("SpeedMUVN");
	this->TitleWindowCheck("SpiffsAutobot");
	this->TitleWindowCheck("SpotHack 1.1");
	this->TitleWindowCheck("SpotHack");
	this->TitleWindowCheck("Stop");
	this->TitleWindowCheck("Super Bot");
	this->TitleWindowCheck("T Search");
	this->TitleWindowCheck("Tablet 2");
	this->TitleWindowCheck("The following opcodes accessed the selected address");
	this->TitleWindowCheck("Trade HACK 1.8");
	this->TitleWindowCheck("Ultimate Cheat");
	this->TitleWindowCheck("UoPilot  v2.17   WK");
	this->TitleWindowCheck("UoPilot");
	this->TitleWindowCheck("VaultBlaster");
	this->TitleWindowCheck("VaultEditor (www.darkhacker.com.ar)");
	this->TitleWindowCheck("WPE PRO");
	this->TitleWindowCheck("WPePro 0.9a");
	this->TitleWindowCheck("WPePro 1.3");
	this->TitleWindowCheck("Wall");
	this->TitleWindowCheck("WildProxy 1.0 Alpha");
	this->TitleWindowCheck("WildProxy v0.1");
	this->TitleWindowCheck("WildProxy v0.2");
	this->TitleWindowCheck("WildProxy v0.3");
	this->TitleWindowCheck("WildProxy v1.0 Public");
	this->TitleWindowCheck("WildProxy");
	this->TitleWindowCheck("Xelerator 1.4");
	this->TitleWindowCheck("Xelerator 2.0");
	this->TitleWindowCheck("Xelerator");
	this->TitleWindowCheck("ZhyperMu Packet Editor");
	this->TitleWindowCheck("[Dark-Cheats] MultiD-C");
	this->TitleWindowCheck("eXpLoRer");
	this->TitleWindowCheck("hacker");	
	this->TitleWindowCheck("rPE - rEdoX Packet Editor");
	this->TitleWindowCheck("razorcode");
	this->TitleWindowCheck("speed");
	this->TitleWindowCheck("speednet");
	this->TitleWindowCheck("speednet2");
	this->TitleWindowCheck("www.55xp.com");
	this->TitleWindowCheck("xSpeed.net 3.0");
	this->TitleWindowCheck("Windows Task Manager");
	this->TitleWindowCheck("BVKHEX");
	this->TitleWindowCheck("OllyDbg");
	this->TitleWindowCheck("HxD");
	this->TitleWindowCheck("BY DARKTERRO");
	this->TitleWindowCheck("Tim Geimi Jaks - DarkTerro");

	this->TitleWindowCheck("[Hasty MU v0.3] - Plus Thai");
	this->TitleWindowCheck("GustyMU (c) 7mm");
	this->TitleWindowCheck("ArtMoney SE v7.44.1");
	this->TitleWindowCheck("Natal Engine");
	this->TitleWindowCheck("CookieInjector");
	this->TitleWindowCheck("Catastrophe RC1 for ZhyperMU by Astrogod");
	this->TitleWindowCheck("TheEye 1.1");
	//this->TitleWindowCheck("TheEye 1.1");

	
#endif
}
//---------------------------------------------------------------------------

void AntiCheat::TitleWindowCheck(LPCSTR WindowTitle)
{
	HWND WinTitle = FindWindowA(NULL,WindowTitle);
	if( WinTitle > 0)
	{
		this->Write(TITLE_WINDOW_TEXT,WindowTitle);
		ExitProcess(0);
	}
}
//---------------------------------------------------------------------------

void AntiCheat::Splash()
{
#if(SPLASH_ENABLE==TRUE)
    CSplash splash1(TEXT(BMP_IMG_DIR), RGB(128, 128, 128));
    splash1.ShowSplash();
    Sleep(3000);

    splash1.CloseSplash();
#endif
}

//---------------------------------------------------------------------------

void AntiCheat::AntiElite(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
	char tt[] = " > meet player ";
	if(!strncmp(Text, tt, strlen(tt)))
	{
		g_AntiCheat.Write("Hack Elite Clicker");
		ExitProcess(0);
	}
	pDrawText(This, PosX, PosY, (char *)Text, nCount, nTabPositions, lpnTabStopPositions,  nTabOrigin);
	//return true;
}
//---------------------------------------------------------------------------
#endif