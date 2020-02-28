#pragma once

#define DEV_BANSYSTEM			1

#if(DEV_BANSYSTEM)

#include <vector>

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

	bool Connect();
	void CreateTable();
	void SelectTable(PMSG_REQ_BANSYSTEM* lpMsg, int pIndex);
	void Insert(PMSG_INSERT_BANSYSTEM* lpMsg);
	void Delete(PMSG_DELETE_BANSYSTEM* lpMsg);

	CQuery m_DBQuery;

	std::vector<BANHDD_DATA> m_HddData;
};

extern CBanSystem g_BanSystem;

#endif

