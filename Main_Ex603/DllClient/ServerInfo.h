#pragma once

#include "stdafx.h"

#define sub_953620		((LPVOID(__thiscall*)(LPVOID This)) 0x953620)
#define sub_9527D0		((int(__thiscall*)(char* This)) 0x9527D0)
#define sub_402320		((int(__stdcall*)(int a1)) 0x402320)
#define sub_9526C0		((int(__thiscall*)(DWORD* This, char* a2)) 0x9526C0)
#define sub_9CF52A		((int(*)(int a1, const char *a2, ...)) 0x9CF52A)

struct SERVERINFO_DATA
{
	char ServerName[20];
	int SubServerNum;
	char ServerText[256];
};

class CServerInfo
{
public:
		 CServerInfo();
		 ~CServerInfo();

	void Load();
	void Read(char* filename);

	static int ServerDrawText(int a1, signed int a2, signed int a3);
	static void ServerDrawTextHook(int a1, char *a2, char* ServerName, int SubServerNum, char* TextConnect);

	std::vector<SERVERINFO_DATA> m_data;
};
extern CServerInfo g_ServerInfo;