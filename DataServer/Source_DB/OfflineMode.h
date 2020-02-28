#pragma once

#include "StdAfx.h"
#include ".\\DbSet\\DBConBase.h"
#include "..\include\ProDef.h"
#include <vector>

#define OFFLINE_MODE_RESTORE	1
#define OFFLINEMODE_DBMAX		8
#define OFFLINEMODE_DBPRICE		544
#define OFFLINEMODE_DBCREDIT	128

struct PMSG_DGANS_OFFMODE_START
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Password[11];
	char Name[11];
	DWORD TickCount;
};

struct PMSG_GDREQ_OFFMODE_CHAR
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	short Number;
};

struct PMSG_GDLOAD_OFFMODE_DATA
{
	PWMSG_HEAD h;
	short Number;
	BYTE AttackData[OFFLINEMODE_DBMAX];
	bool PShopOpen;
	char PShopText[36];
	BYTE PriceData[OFFLINEMODE_DBPRICE];
	BYTE CreditData[OFFLINEMODE_DBCREDIT];
};

struct PMSG_GDSAVE_OFFMODE_DATA
{
	PWMSG_HEAD h;
	char Name[11];
	bool Status;
	BYTE AttackData[OFFLINEMODE_DBMAX];
	bool PShopOpen;
	char PShopText[36];
	BYTE PriceData[OFFLINEMODE_DBPRICE];
	BYTE CreditData[OFFLINEMODE_DBCREDIT];
};

struct PMSG_GDREQ_OFFMODE_STATUS
{
	PBMSG_HEAD2 h;
	char Name[11];
	BYTE Status;
};

struct OFFMODEUSER_DATA
{
	int uIndex;
	char AccountID[11];
	char Password[11];
	char Name[11];
};

class COfflineMode
{
public:
			COfflineMode();
			~COfflineMode();

	bool	Connect();
	void	CreateTable();

	void	GDReqAllPlayer(int uIndex);
	void	GDReqOffCharacter(PMSG_GDREQ_OFFMODE_CHAR* lpMsg, int uIndex);

	void	CreateCharecter(char* Name);
	void	SelectData(int uIndex, int  Number, char* Name);
	void	UpdateData(PMSG_GDSAVE_OFFMODE_DATA* lpMsg, int uIndex);
	void	UpdateStatus(PMSG_GDREQ_OFFMODE_STATUS* lpMsg, int uIndex);
	void	Run();
	
	bool	m_bQueenQuery;
	CQuery	m_DBQuery;	

	CQuery	m_AccountDBQuery;
	CQuery	m_PasswordDBQuery;
	CQuery  m_MembStat;

	bool    m_RunActive;
	bool	m_ConnectedUser;
	DWORD   m_ConnectedTick;

	std::vector<OFFMODEUSER_DATA> m_users;
};

extern COfflineMode g_OfflineMode;