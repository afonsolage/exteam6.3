#pragma once
//---------------------------------------------------------------------------

#include "stdafx.h"

#define ANTI_CHEAT_OLD			0
#if(ANTI_CHEAT_OLD==TRUE)
//---------------------------------------------------------------------------
// -> Active define
#define ANTI_CHEAT				TRUE	//Dedumakarke nado vklu4it
#define ANTI_CHEAT_DEBUG		FALSE
//---------------------------------------------------------------------------

#define AH_TITLE				"Anti-Cheat"
#define BMP_IMG_DIR				".\\Data/AntiCheat.bmp"
//---------------------------------------------------------------------------

// -> System
#define LOG_ENABLE				TRUE
#define MESSAGE_ENABLE			FALSE	//NoWork
#define SPLASH_ENABLE			TRUE
//---------------------------------------------------------------------------

// -> Dump Scan
#define DUMP_SCAN_ENABLE		TRUE
#define DAMP_LOG_TEXT			"Hack: %s"
//---------------------------------------------------------------------------
// -> Title Window
#define TITLE_WINDOW_ENABLE		TRUE
#define TITLE_WINDOW_TEXT		"Hack: %s"
//---------------------------------------------------------------------------
// -> Class Window
#define CLASS_WINDOW_ENABLE		TRUE
#define CLASS_WINDOW_TEXT		"Hack: %s"
//---------------------------------------------------------------------------
// -> Inject
#define INJECT_ENABLE			TRUE
#define INJECT_TEXT				"Inject: %s"
//---------------------------------------------------------------------------
// -> ProcessID
#define PROCESS_ID_ENABLE		TRUE
#define PROCESS_ID_TEXT			"ProcessID: %s"
//---------------------------------------------------------------------------
#define ONE_WINDOWS				FALSE

#define MAX_DUMP_OFFSETS	3
#define MAX_DUMP_SIZE		32
#define MAX_PROCESS_DUMP	706
//---------------------------------------------------------------------------

struct ANITHACK_PROCDUMP
{
	unsigned int m_aOffset;
	unsigned char m_aMemDump[MAX_DUMP_SIZE];
	char Name[100];
};
extern ANITHACK_PROCDUMP g_ProcessesDumps[MAX_PROCESS_DUMP];
//---------------------------------------------------------------------------

class AntiCheat
{
public:
	void Load();
	void Main();
	void Write(LPSTR Text, ...);
	static void Timer(LPVOID lpParam);
	static void Timer2(LPVOID lpParam);
	// --
	void ClassWindow();
	void ClassWindowCheck(LPCSTR WindowClasse);
	// --
	bool DumpCheck(HANDLE hProcess);
	void Dump();
	// --
	void Inject();
	void InjectCheck(LPCSTR InjectHandle);
	// --
	void ProcessID();
	void ProcessIDCheck(LPCSTR ProcName);
	// --
	void TitleWindow();
	void TitleWindowCheck(LPCSTR WindowTitle);
	// -- 
	void Splash();

	static void __thiscall  AntiElite(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);


	bool MsgBox;
};
extern AntiCheat g_AntiCheat;
//---------------------------------------------------------------------------


#endif