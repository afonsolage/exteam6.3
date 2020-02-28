#pragma once

#include "EngineDebugerDefine.h"

#if(ENGINE_DEBUGER)

class CEngineDebuger
{
public:
	  CEngineDebuger();
	  ~CEngineDebuger();

	void Init();
	void Load();
	void Read(char* filename);
	void LoadIMG();

	void ConsoleInit();
	HANDLE ConsoleHandle(BOOL gImput);
	void ConsolePrint(DWORD Color, char* Format, ...);

	void KeyBoard(DWORD wParam);
	void KeyMouse(DWORD wParam);

	void GameDraw();

	int m_Enable;

	int m_LoadCount;
	INTERFACE_DATA m_Draw[MAX_INTERFACE_DATA];
};

extern CEngineDebuger g_EngineDebuger;

#endif