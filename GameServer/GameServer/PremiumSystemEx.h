#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\\include\\prodef.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PREMIUM_SYSTEM==TRUE)

/*
Бронза сильвер голд
*/

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
	PremiumSystemEx();
	~PremiumSystemEx();

	void Init();
	void Load();
	void Read(char* File);

	void CheckValue();

	void UserCalculatorPlus(int aIndex);
	int UserExpPlus(int aIndex);
	void UserZenPlus(int aIndex, float& Money);

	void UserConnect(int aIndex);
	void PremiumTime(int aIndex);

	void CG_RecvBuy(int aIndex, CG_PREMIUM_BUY* Recv);
	void GC_Send(int aIndex, CG_SEND_OPEND_WIN* Recv);
	void GC_Config(int aIndex);

	void InfoMessage(int aIndex);
	void UserBuff(int aIndex);

	bool ActiveSystem;

	int Plus1ExpProcent;
	int Plus1DropZenProcent;
	int Plus1DamageProcent;
	int Plus1DefenceProcent;
	int Plus1WizardDamageProcent;
	
	int Buy1CreditDay;

	int Plus2ExpProcent;
	int Plus2DropZenProcent;
	int Plus2DamageProcent;
	int Plus2DefenceProcent;
	int Plus2WizardDamageProcent;

	int Buy2CreditDay;

	int Plus3ExpProcent;
	int Plus3DropZenProcent;
	int Plus3DamageProcent;
	int Plus3DefenceProcent;
	int Plus3WizardDamageProcent;

	int Buy3CreditDay;

	int m_iOfflineModeAttackFreePremiumRang;
	int m_iOfflineModePickUpPremiumRang;

	int Buy1WCoinDay;
	int Buy2WCoinDay;
	int Buy3WCoinDay;

	int m_PremiumServerEnable;
};
extern PremiumSystemEx g_PremiumSystemEx;
// ----------------------------------------------------------------------------------------------
#endif