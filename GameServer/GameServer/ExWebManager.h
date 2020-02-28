#pragma once

#include "..\\include\\prodef.h"

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

class CExWebManager
{
public:
	void Protocol(BYTE protoNum, BYTE *aRecv);
	void GameShopUpdate(GAMESHOP_WEB_UPDATE* lpMsg);
	void CreditsUpdate(CREDIT_WEB_UPDATE* lpMsg);
};

extern CExWebManager g_ExWebManager;