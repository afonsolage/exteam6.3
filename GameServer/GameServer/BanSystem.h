#pragma once

#if(DEV_BANSYSTEM)

#include "..\include\prodef.h"

struct PMSG_REQ_BANSYSTEM
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

struct PMSG_SELECT_BANSYSTEM
{
	PBMSG_HEAD2 h;
	char Name[11];
	DWORD Hdd;
	DWORD Time;
	DWORD Type;
};

struct PMSG_INSERT_BANSYSTEM
{
	PBMSG_HEAD2 h;
	char Name[11];
	DWORD Hdd;
	DWORD Time;
	DWORD Type;
};

struct PMSG_DELETE_BANSYSTEM
{
	PBMSG_HEAD2 h;
	char Name[11];
	DWORD Type;
};

struct BANHDD_DATA
{
	char Name[11];
	DWORD Hdd;
	DWORD Time;	
	DWORD Type;
};

class CBanSystem
{
public:
		CBanSystem();
		~CBanSystem();

	void Load();
	void Read(char* filename);
	bool Chat(int aIndex);
	bool Player(int aIndex);

	void DSReqSelect();
	void DSAnsSelect(PMSG_SELECT_BANSYSTEM* lpMsg);
	void DSReqInsert(char* Name, DWORD Hdd, DWORD Time, DWORD Type);
	void DSReqDelete(char* Name);
	
	void Run();

	bool Enable;

	std::vector<BANHDD_DATA> m_HddData;


};

extern CBanSystem g_BanSystem;

#endif

