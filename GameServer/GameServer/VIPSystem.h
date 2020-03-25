#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"

#define ONE_VIP_DAY 86400
#define VIP_DAY_COUNT 30

struct GC_VIP_SEND
{
	PBMSG_HEAD2 h;
	WORD	WCoin;
	WORD	Price;
};

struct CG_VIP_BUY
{
	PBMSG_HEAD2 h;
};

struct CG_VIP_SEND_OPEND_WIN
{
	PBMSG_HEAD2 h;
	BYTE Result;
};

class CVIPSystem
{
public:
	CVIPSystem(void);
	virtual ~CVIPSystem(void);

public:
	void Init();
	void Load();

	void CG_RecvBuy(int aIndex, CG_VIP_BUY* Recv);
	void GC_Send(int aIndex, CG_VIP_SEND_OPEND_WIN* Recv);

	void InfoMessage(int aIndex);
	void UserConnect(int aIndex);

	void SecondProc(int aIndex);
private:

	bool m_Enabled;
	int m_Price;
};

extern CVIPSystem g_VIPSystem;