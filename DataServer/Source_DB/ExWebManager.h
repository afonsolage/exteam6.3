#pragma once

#include "StdAfx.h"
#include ".\\DbSet\\DBConBase.h"

struct GAMESHOP_WEB_UPDATE
{
	PBMSG_HEAD2	h;
	char	AccountID[MAX_IDSTRING+1];
	DWORD	WCoinC;
	DWORD	WCoinP;
	DWORD	GoblinPoint;
};

struct CREDIT_WEB_UPDATE
{
	PBMSG_HEAD2	h;
	char	AccountID[MAX_IDSTRING+1];
	DWORD	Credit;
};

// -----

struct CREDIT_WEB_REQ
{
	PBMSG_HEAD2	h;
	char AccountID[MAX_IDSTRING+1];
};

struct CREDIT_WEB_ANS
{
	PBMSG_HEAD2	h;
	DWORD Count;
};




class CExWebManager
{
public:
	CExWebManager();
	~CExWebManager();
	bool Connect();
	void Protocol(BYTE protoNum, BYTE *aRecv, int uIndex);
	void GameShopUpdate(GAMESHOP_WEB_UPDATE* lpMsg, int uIndex);
	void CreditsUpdate(CREDIT_WEB_UPDATE* lpMsg, int uIndex);
	void ReqCredit(CREDIT_WEB_REQ* lpMsg);

	CQuery	m_DBQuery;
	CQuery  m_MEMBQuery;
};


extern CExWebManager g_ExWebManager;