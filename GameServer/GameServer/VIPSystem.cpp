#include "stdafx.h"
#include "VIPSystem.h"
#include "Message.h"
#include "DSProtocol.h"
#include "logproc.h"
#include "ExUser.h"
#include "GameMain.h"
#include "ExText.h"

CVIPSystem g_VIPSystem;

CVIPSystem::CVIPSystem(void)
{
}


CVIPSystem::~CVIPSystem(void)
{
}

void CVIPSystem::Init()
{
	m_Price = 0;
	m_Enabled = 0;
}

void CVIPSystem::Load()
{
	m_Enabled = (bool) GetPrivateProfileInt("VIP", "Enabled", 0, gDirPath.GetNewPath("Custom\\VIPSystem.ini"));
	m_Price = GetPrivateProfileInt("VIP", "Price", 0, gDirPath.GetNewPath("Custom\\VIPSystem.ini"));
}

void CVIPSystem::CG_RecvBuy(int aIndex, CG_VIP_BUY* Recv)
{
	if(!this->m_Enabled)
	{
		return;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	int NeedWCoin = this->m_Price;

	if (lpUser->GameShop.WCoinC < NeedWCoin)
		return;

	lpUser->GameShop.WCoinC -= NeedWCoin;
	gGameShop.GDSaveUserInfo(aIndex);

	int timeLeft = this->VipTimeLeft(lpUser->PremiumTime);

	lpUser->PremiumTime = (int) (GetEpoch() + timeLeft + ONE_VIP_DAY * VIP_DAY_COUNT);

	this->InfoMessage(aIndex);

	GC_Send(aIndex, NULL);
}

void CVIPSystem::GC_Send(int aIndex, CG_VIP_SEND_OPEND_WIN* Recv)
{
	if(!this->m_Enabled)
	{
		return;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(Recv != NULL && Recv->Result != 1)
	{
		return;
	}

	ExUserDataSend(aIndex);

	GC_VIP_SEND pSend;
	pSend.h.set((LPBYTE)&pSend, 0xFB, 0x16, sizeof(pSend));
	pSend.Price = m_Price;
	pSend.WCoin = lpUser->GameShop.WCoinC;
	DataSend(aIndex, (LPBYTE)&pSend, pSend.h.size);
}

void CVIPSystem::InfoMessage(int aIndex)
{
	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	int vipTime = VipTimeLeft(lpUser->PremiumTime);

	if (vipTime > 0)
	{
		vipTime = ((vipTime - 1) / ONE_VIP_DAY) + 1;
	}

	MessageChat(aIndex, "[VIP] Tempo restante: %d dia(s)", vipTime);
}

void CVIPSystem::UserConnect(int aIndex)
{
	InfoMessage(aIndex);
}

int CVIPSystem::VipTimeLeft(int premiumTime)
{
	DWORD premium = (DWORD) premiumTime;
	DWORD now = GetEpoch();
	if (premium < now)
		return 0;
	else return premium - now;
}

void CVIPSystem::SecondProc(int aIndex)
{
	if(!this->m_Enabled)
	{
		return;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(lpUser->PremiumTime == 0)
	{
		return;
	}
	else if (VipTimeLeft(lpUser->PremiumTime) == 0)
	{
		InfoMessage(aIndex);
		lpUser->PremiumTime = 0;
	}
}