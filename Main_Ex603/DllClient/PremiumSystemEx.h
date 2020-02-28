#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

enum ePremium
{
	eVip1 =1,
	eVip2,
	eVip3,
};
// ----------------------------------------------------------------------------------------------

struct CG_PREMIUM_BUY
{
	PBMSG_HEAD2 h;
	BYTE PremiumType;
	WORD PremiumDay;
	BYTE PriceType;
};
// ----------------------------------------------------------------------------------------------

struct GC_PREMIUM_SEND
{
	PBMSG_HEAD2 h;
	DWORD Buy1CreditDay;
	DWORD Buy2CreditDay;
	DWORD Buy3CreditDay;
	WORD UserCredit;
	DWORD OfflineModePickUpPremiumRang;
	DWORD Buy1WCoinDay;
	DWORD Buy2WCoinDay;
	DWORD Buy3WCoinDay;
};
// ----------------------------------------------------------------------------------------------

struct CG_SEND_OPEND_WIN
{
	PBMSG_HEAD2 h;
	BYTE Result;
};
// ----------------------------------------------------------------------------------------------

struct GC_PREMIUM_CONFIG
{
	PBMSG_HEAD2 h;
	DWORD OfflineModeAttackFreePremiumRang;
	DWORD OfflineModePickUpPremiumRang;
};
// ----------------------------------------------------------------------------------------------

class PremiumSystemEx
{
public:
	void Init();
	void Load();
	void BindImages();

	void DrawWindow();
	void Button(DWORD Event);
	void GC_RecvInfo(GC_PREMIUM_SEND* Recv);
	void CG_SendOpenWindows();

	char* GetName(int Number);
	void GC_Config(GC_PREMIUM_CONFIG* lpMsg);

	BYTE PremiumSwitch;
	WORD PremiumDay;

	BYTE PriceSwitch;

	DWORD NeedCredit;
	DWORD NeedWCoin;

	int Buy1CreditDay;
	int Buy2CreditDay;
	int Buy3CreditDay;
	int Buy1WCoinDay;
	int Buy2WCoinDay;
	int Buy3WCoinDay;

	int m_iOfflineModeAttackFreePremiumRang;
	int m_iOfflineModePickUpPremiumRang;
};
extern PremiumSystemEx g_PremiumSystemEx;
// ----------------------------------------------------------------------------------------------