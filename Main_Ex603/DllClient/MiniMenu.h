#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_MINIMENU==TRUE)

#define ENABLE_DONATE_BUTTON	TRUE
// ----------------------------------------------------------------------------------------------

struct GC_MMOTOPURL
{
	PBMSG_HEAD2 h;
	BYTE Result;
	char mmotopurl[64];
};
// ----------------------------------------------------------------------------------------------

struct PMSG_GC_QTOPURL
{
	PBMSG_HEAD2 h;
	BYTE Result;
	char szUrl[64];
};
// ----------------------------------------------------------------------------------------------

class MiniMenu
{
public:
		 MiniMenu();
		 ~MiniMenu();

	void Init();
	void Load();
	void BindImage();
	// --
	void Draw();
	void DrawV1();
	void DrawV2();
	float DrawButton(char* Name, int ButtonID, float X, float Y);

	void Botton(DWORD Event);
	// --
	void GC_RecvMMOTOP(GC_MMOTOPURL* pData);
	void GC_RecvQTOP(PMSG_GC_QTOPURL* pData);
	// --
	int GetCountButton();
	// --
	char UrlMootop[64];
	char szUrlQtop[64];
	// --
};
// ----------------------------------------------------------------------------------------------
extern MiniMenu g_MiniMenu;
// ----------------------------------------------------------------------------------------------
#endif