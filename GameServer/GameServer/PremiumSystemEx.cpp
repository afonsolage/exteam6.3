#include "StdAfx.h"
#include "PremiumSystemEx.h"
#include "GameMain.h"
#include "logproc.h"
//#include "BuffEffectSlot.h"
#include "ExUser.h"
#include "ObjCalCharacter.h"
//#include "BuffManagerEx.h"
#include "Message.h"
#include "DSProtocol.h"
#include "ExLicense.h"
#include "BuffManager.h"
#include "ExText.h"

#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
// -------------------------------------------------------------------------------

PremiumSystemEx g_PremiumSystemEx;
// -------------------------------------------------------------------------------

PremiumSystemEx::PremiumSystemEx()
{
	this->Init();
}
// -------------------------------------------------------------------------------

PremiumSystemEx::~PremiumSystemEx()
{
	// ----
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::Init()
{
	this->ActiveSystem = false;

	this->Plus1ExpProcent = 0;
	this->Plus1DropZenProcent = 0;
	this->Plus1DamageProcent = 0;
	this->Plus1DefenceProcent = 0;
	this->Plus1WizardDamageProcent = 0;
	this->Buy1CreditDay = 0;

	this->Plus2ExpProcent = 0;
	this->Plus2DropZenProcent = 0;
	this->Plus2DamageProcent = 0;
	this->Plus2DefenceProcent = 0;
	this->Plus2WizardDamageProcent = 0;
	this->Buy2CreditDay = 0;

	this->Plus3ExpProcent = 0;
	this->Plus3DropZenProcent = 0;
	this->Plus3DamageProcent = 0;
	this->Plus3DefenceProcent = 0;
	this->Plus3WizardDamageProcent = 0;
	this->Buy3CreditDay = 0;

	this->Buy1WCoinDay = 0;
	this->Buy2WCoinDay = 0;
	this->Buy3WCoinDay = 0;
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::Load()
{
	this->Init();

	if(g_ExLicense.user.PremiumEx == false)
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ExData\\PremiumSystemEx.ini"));

	this->CheckValue();
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::Read(char* File)
{
	this->ActiveSystem = GetPrivateProfileInt("Common", "ActiveSystem", 0, File);

	this->Plus1ExpProcent = GetPrivateProfileInt("Common", "Plus1ExpProcent", 0, File);
	this->Plus1DropZenProcent = GetPrivateProfileInt("Common", "Plus1DropZenProcent", 0, File);
	this->Plus1DamageProcent = GetPrivateProfileInt("Common", "Plus1DamageProcent", 0, File);
	this->Plus1DefenceProcent = GetPrivateProfileInt("Common", "Plus1DamageProcent", 0, File);
	this->Plus1WizardDamageProcent = GetPrivateProfileInt("Common", "Plus1WizardDamageProcent", 0, File);
	this->Buy1CreditDay = GetPrivateProfileInt("Common", "Buy1CreditDay", 0, File);

	this->Plus2ExpProcent = GetPrivateProfileInt("Common", "Plus2ExpProcent", 0, File);
	this->Plus2DropZenProcent = GetPrivateProfileInt("Common", "Plus2DropZenProcent", 0, File);
	this->Plus2DamageProcent = GetPrivateProfileInt("Common", "Plus2DamageProcent", 0, File);
	this->Plus2DefenceProcent = GetPrivateProfileInt("Common", "Plus2DefenceProcent", 0, File);
	this->Plus2WizardDamageProcent = GetPrivateProfileInt("Common", "Plus2WizardDamageProcent", 0, File);
	this->Buy2CreditDay = GetPrivateProfileInt("Common", "Buy2CreditDay", 0, File);

	this->Plus3ExpProcent = GetPrivateProfileInt("Common", "Plus3ExpProcent", 0, File);
	this->Plus3DropZenProcent = GetPrivateProfileInt("Common", "Plus3DropZenProcent", 0, File);
	this->Plus3DamageProcent = GetPrivateProfileInt("Common", "Plus3DamageProcent", 0, File);
	this->Plus3DefenceProcent = GetPrivateProfileInt("Common", "Plus3DefenceProcent", 0, File);
	this->Plus3WizardDamageProcent = GetPrivateProfileInt("Common", "Plus3WizardDamageProcent", 0, File);
	this->Buy3CreditDay = GetPrivateProfileInt("Common", "Buy3CreditDay", 0, File);

	this->m_iOfflineModeAttackFreePremiumRang = GetPrivateProfileInt("Common", "OfflineModeAttackFreePremiumRang", 0, File);
	this->m_iOfflineModePickUpPremiumRang = GetPrivateProfileInt("Common", "OfflineModePickUpPremiumRang", 0, File);

	this->Buy1WCoinDay = GetPrivateProfileInt("Common", "Buy1WCoinDay", 0, File);
	this->Buy2WCoinDay = GetPrivateProfileInt("Common", "Buy2WCoinDay", 0, File);
	this->Buy3WCoinDay = GetPrivateProfileInt("Common", "Buy3WCoinDay", 0, File);
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::CheckValue()
{
	if(this->Plus1ExpProcent < 0)
	{
		this->Plus1ExpProcent = 0;
	}
	if(this->Plus1DropZenProcent < 0)
	{
		this->Plus1DropZenProcent = 0;
	}
	if(this->Plus1DamageProcent < 0)
	{
		this->Plus1DamageProcent = 0;
	}
	if(this->Plus1DefenceProcent < 0)
	{
		this->Plus1DefenceProcent = 0;
	}
	if(this->Plus1WizardDamageProcent < 0)
	{
		this->Plus1WizardDamageProcent = 0;
	}
	// ----
	if(this->Plus2ExpProcent < 0)
	{
		this->Plus2ExpProcent = 0;
	}
	if(this->Plus2DropZenProcent < 0)
	{
		this->Plus2DropZenProcent = 0;
	}
	if(this->Plus2DamageProcent < 0)
	{
		this->Plus2DamageProcent = 0;
	}
	if(this->Plus2DefenceProcent < 0)
	{
		this->Plus2DefenceProcent = 0;
	}
	if(this->Plus2WizardDamageProcent < 0)
	{
		this->Plus2WizardDamageProcent = 0;
	}
	// ----
	if(this->Plus3ExpProcent < 0)
	{
		this->Plus3ExpProcent = 0;
	}
	if(this->Plus3DropZenProcent < 0)
	{
		this->Plus3DropZenProcent = 0;
	}
	if(this->Plus3DamageProcent < 0)
	{
		this->Plus3DamageProcent = 0;
	}
	if(this->Plus3DefenceProcent < 0)
	{
		this->Plus3DefenceProcent = 0;
	}
	if(this->Plus3WizardDamageProcent < 0)
	{
		this->Plus3WizardDamageProcent = 0;
	}

	if(this->Buy1CreditDay < 0)
	{
		this->Buy1CreditDay = 0;
	}
	if(this->Buy2CreditDay < 0)
	{
		this->Buy2CreditDay = 0;
	}
	if(this->Buy3CreditDay < 0)
	{
		this->Buy3CreditDay = 0;
	}

	if(this->Buy1WCoinDay < 0)
	{
		this->Buy1WCoinDay = 0;
	}
	if(this->Buy2WCoinDay < 0)
	{
		this->Buy2WCoinDay = 0;
	}
	if(this->Buy3WCoinDay < 0)
	{
		this->Buy3WCoinDay = 0;
	}
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::UserCalculatorPlus(int aIndex)
{
	if(!this->ActiveSystem)
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

	if(lpUser->PremiumTimeType <= 0 || lpUser->PremiumTimeType <= 0)
	{
		return;
	}

	if(lpUser->PremiumTimeType == eVip1)
	{
		lpUser->m_AttackDamageMinRight	+= ( lpUser->m_AttackDamageMinRight * this->Plus1DamageProcent ) / 100;
		lpUser->m_AttackDamageMaxRight	+= ( lpUser->m_AttackDamageMaxRight * this->Plus1DamageProcent ) / 100;
		lpUser->m_AttackDamageMinLeft	+= ( lpUser->m_AttackDamageMinLeft * this->Plus1DamageProcent ) / 100;
		lpUser->m_AttackDamageMaxLeft	+= ( lpUser->m_AttackDamageMaxLeft * this->Plus1DamageProcent ) / 100;
		lpUser->m_Defense				+= ( lpUser->m_Defense * this->Plus1DefenceProcent ) / 100;
		lpUser->m_MagicDefense			+= ( lpUser->m_MagicDefense * this->Plus1DefenceProcent ) / 100;
		lpUser->m_MagicDamageMin		+= ( lpUser->m_MagicDamageMin * this->Plus1WizardDamageProcent ) / 100;
		lpUser->m_MagicDamageMax		+= ( lpUser->m_MagicDamageMax * this->Plus1WizardDamageProcent ) / 100;
	}
	else if(lpUser->PremiumTimeType == eVip2)
	{
		lpUser->m_AttackDamageMinRight	+= ( lpUser->m_AttackDamageMinRight * this->Plus2DamageProcent ) / 100;
		lpUser->m_AttackDamageMaxRight	+= ( lpUser->m_AttackDamageMaxRight * this->Plus2DamageProcent ) / 100;
		lpUser->m_AttackDamageMinLeft	+= ( lpUser->m_AttackDamageMinLeft * this->Plus2DamageProcent ) / 100;
		lpUser->m_AttackDamageMaxLeft	+= ( lpUser->m_AttackDamageMaxLeft * this->Plus2DamageProcent ) / 100;
		lpUser->m_Defense				+= ( lpUser->m_Defense * this->Plus2DefenceProcent ) / 100;
		lpUser->m_MagicDefense			+= ( lpUser->m_MagicDefense * this->Plus2DefenceProcent ) / 100;
		lpUser->m_MagicDamageMin		+= ( lpUser->m_MagicDamageMin * this->Plus2WizardDamageProcent ) / 100;
		lpUser->m_MagicDamageMax		+= ( lpUser->m_MagicDamageMax * this->Plus2WizardDamageProcent ) / 100;
	}
	else if(lpUser->PremiumTimeType == eVip3)
	{
		lpUser->m_AttackDamageMinRight	+= ( lpUser->m_AttackDamageMinRight * this->Plus3DamageProcent ) / 100;
		lpUser->m_AttackDamageMaxRight	+= ( lpUser->m_AttackDamageMaxRight * this->Plus3DamageProcent ) / 100;
		lpUser->m_AttackDamageMinLeft	+= ( lpUser->m_AttackDamageMinLeft * this->Plus3DamageProcent ) / 100;
		lpUser->m_AttackDamageMaxLeft	+= ( lpUser->m_AttackDamageMaxLeft * this->Plus3DamageProcent ) / 100;
		lpUser->m_Defense				+= ( lpUser->m_Defense * this->Plus3DefenceProcent ) / 100;
		lpUser->m_MagicDefense			+= ( lpUser->m_MagicDefense * this->Plus3DefenceProcent ) / 100;
		lpUser->m_MagicDamageMin		+= ( lpUser->m_MagicDamageMin * this->Plus3WizardDamageProcent ) / 100;
		lpUser->m_MagicDamageMax		+= ( lpUser->m_MagicDamageMax * this->Plus3WizardDamageProcent ) / 100;
	}
}
// -------------------------------------------------------------------------------

int PremiumSystemEx::UserExpPlus(int aIndex)
{
	if(!this->ActiveSystem)
	{
		return 0;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return 0;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return 0;
	}

	if(lpUser->PremiumTimeType <= 0 || lpUser->PremiumTimeType <= 0)
	{
		return 0;
	}
	
	int Result = 0;

	if(lpUser->PremiumTimeType == eVip1)
	{
		Result = this->Plus1ExpProcent;
	}
	else if(lpUser->PremiumTimeType == eVip2)
	{
		Result = this->Plus2ExpProcent;
	}
	else if(lpUser->PremiumTimeType == eVip3)
	{
		Result = this->Plus3ExpProcent;
	}

	return Result;
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::UserZenPlus(int aIndex, float& Money)
{
	if(!this->ActiveSystem)
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

	if(lpUser->PremiumTimeType <= 0 || lpUser->PremiumTimeType <= 0)
	{
		return;
	}

	int ZenPlus = 0;

	if(lpUser->PremiumTimeType == eVip1)
	{
		ZenPlus = this->Plus1DropZenProcent;
	}
	else if(lpUser->PremiumTimeType == eVip2)
	{
		ZenPlus = this->Plus2DropZenProcent;
	}
	else if(lpUser->PremiumTimeType == eVip3)
	{
		ZenPlus = this->Plus3DropZenProcent;
	}

	Money += ( Money * ZenPlus ) / 100.0f;
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::UserConnect(int aIndex)
{
	if(!this->ActiveSystem)
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

	if(lpUser->PremiumTimeType <= 0 || lpUser->PremiumTime <= 0)
	{
		return;
	}

	/*if(lpUser->PremiumTimeType == eVip1)
	{
		g_BuffManagerEx.AddExBuffData(aIndex, AT_VIP_SILVER, lpUser->PremiumTime);
	}
	else if(lpUser->PremiumTimeType == eVip2)
	{
		g_BuffManagerEx.AddExBuffData(aIndex, AT_VIP_GOLD, lpUser->PremiumTime);
	}
	else if(lpUser->PremiumTimeType == eVip3)
	{
		g_BuffManagerEx.AddExBuffData(aIndex, AT_VIP_PLATINUM, lpUser->PremiumTime);
	}*/

	this->InfoMessage(aIndex);
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::PremiumTime(int aIndex)
{
	if(!this->ActiveSystem)
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

	if(lpUser->PremiumTimeType <= 0 || lpUser->PremiumTime <= 0)
	{
		return;
	}

	lpUser->PremiumTime--;

	if(lpUser->PremiumTime <= 0)
	{
		lpUser->PremiumTimeType = 0;
		lpUser->PremiumTime = 0;
		ExUserDataSend(aIndex);

		MessageChat(aIndex, g_ExText.GetText(252));
	}

}
// -------------------------------------------------------------------------------

void PremiumSystemEx::CG_RecvBuy(int aIndex, CG_PREMIUM_BUY* Recv)
{
	if(!this->ActiveSystem)
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

	int NeedCredit = 0;
	int iPremiumType = Recv->PremiumType;
	int iPremiumDay = Recv->PremiumDay;

	int NeedWCoin = 0;
	int iPriceType = 0;

	if(iPremiumType < 1 || iPremiumType > 3)
	{
		return;
	}

	if(iPremiumDay <= 0 || iPremiumDay > 100)
	{
		return;
	}

	if(iPremiumType == eVip1)
	{
		NeedCredit = this->Buy1CreditDay * Recv->PremiumDay;
	}
	else if(iPremiumType == eVip2)
	{
		NeedCredit = this->Buy2CreditDay * Recv->PremiumDay;
	}	
	else
	{
		NeedCredit = this->Buy3CreditDay * Recv->PremiumDay;
	}

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		iPriceType = Recv->PriceType;

		if(iPremiumType == eVip1)
		{
			NeedWCoin = this->Buy1WCoinDay * Recv->PremiumDay;
		}
		else if(iPremiumType == eVip2)
		{
			NeedWCoin = this->Buy2WCoinDay * Recv->PremiumDay;
		}	
		else
		{
			NeedWCoin = this->Buy3WCoinDay * Recv->PremiumDay;
		}
	}

	if(iPriceType == 0)
	{
		if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
		{
			if(NeedCredit >  lpUser->GameShop.WCoinC)
			{
				return;
			}
		}
		else
		{
			if(NeedCredit > lpUser->ExCred)
			{
				return;
			}

			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
			{
				if(NeedWCoin > lpUser->GameShop.WCoinC)
				{
					return;
				}
			}
		}
	}
	else if(iPriceType == 1)
	{
		if(NeedWCoin > lpUser->GameShop.WCoinC)
		{
			return;
		}
	}

	if(iPremiumType != lpUser->PremiumTimeType)
	{
		/*if(lpUser->PremiumTimeType == eVip1)
		{
			g_BuffManagerEx.DeleteExBuffData(aIndex, AT_VIP_SILVER);
		}
		else if(lpUser->PremiumTimeType == eVip2)
		{
			g_BuffManagerEx.DeleteExBuffData(aIndex, AT_VIP_GOLD);
		}
		else if(lpUser->PremiumTimeType == eVip3)
		{
			g_BuffManagerEx.DeleteExBuffData(aIndex, AT_VIP_PLATINUM);
		}*/

		lpUser->PremiumTimeType = 0;
		lpUser->PremiumTime = 0;
	}

	if(iPriceType == 0)
	{
		if(g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2))
		{
			lpUser->GameShop.WCoinC -= NeedCredit;
			gGameShop.GDSaveUserInfo(aIndex);
		}
		else
		{
			lpUser->ExCred -= NeedCredit;

			if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
			{
				lpUser->GameShop.WCoinC -= NeedWCoin;
				gGameShop.GDSaveUserInfo(aIndex);
			}
		}
	}
	else if(iPriceType == 1)
	{
		lpUser->GameShop.WCoinC -= NeedWCoin;
		gGameShop.GDSaveUserInfo(aIndex);
	}

	lpUser->PremiumTimeType = Recv->PremiumType;
	lpUser->PremiumTime += Recv->PremiumDay * 86400;

	/*if(lpUser->PremiumType == eVip1)
	{
		g_BuffManagerEx.AddExBuffData(aIndex, AT_VIP_SILVER, lpUser->PremiumTime);
	}
	else if(lpUser->PremiumType == eVip2)
	{
		g_BuffManagerEx.AddExBuffData(aIndex, AT_VIP_GOLD, lpUser->PremiumTime);
	}
	else if(lpUser->PremiumType == eVip3)
	{
		g_BuffManagerEx.AddExBuffData(aIndex, AT_VIP_PLATINUM, lpUser->PremiumTime);
	}*/

	this->InfoMessage(aIndex);

	ExUserDataSend(aIndex);

	this->UserBuff(aIndex);
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::GC_Send(int aIndex, CG_SEND_OPEND_WIN* Recv)
{
	if(!this->ActiveSystem)
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

	if(Recv->Result != 1)
	{
		return;
	}

	ExUserDataSend(aIndex);

	GC_PREMIUM_SEND pSend;
	pSend.h.set((LPBYTE)&pSend, 0xFB, 0x09, sizeof(pSend));
	pSend.Buy1CreditDay = this->Buy1CreditDay;
	pSend.Buy2CreditDay = this->Buy2CreditDay;
	pSend.Buy3CreditDay = this->Buy3CreditDay;
	pSend.UserCredit = (WORD)lpUser->ExCred;
	pSend.OfflineModePickUpPremiumRang = this->m_iOfflineModePickUpPremiumRang;
	pSend.Buy1WCoinDay = this->Buy1WCoinDay;
	pSend.Buy2WCoinDay = this->Buy2WCoinDay;
	pSend.Buy3WCoinDay = this->Buy3WCoinDay;
	DataSend(aIndex, (LPBYTE)&pSend, pSend.h.size);
}
// -------------------------------------------------------------------------------

void PremiumSystemEx::InfoMessage(int aIndex)
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

	if(lpUser->PremiumTimeType <= 0 || lpUser->PremiumTime <= 0)
	{
		return;
	}

	if(lpUser->PremiumTimeType == eVip1)
	{
		MessageChat(aIndex, g_ExText.GetText(246), Plus1ExpProcent);
		MessageChat(aIndex, g_ExText.GetText(247), Plus1DropZenProcent);
		MessageChat(aIndex, g_ExText.GetText(248), Plus1DamageProcent);
		MessageChat(aIndex, g_ExText.GetText(249), Plus1WizardDamageProcent);
		MessageChat(aIndex, g_ExText.GetText(250), Plus1DefenceProcent);
	}
	else if(lpUser->PremiumTimeType == eVip2)
	{
		MessageChat(aIndex, g_ExText.GetText(246), Plus2ExpProcent);
		MessageChat(aIndex, g_ExText.GetText(247), Plus2DropZenProcent);
		MessageChat(aIndex, g_ExText.GetText(248), Plus2DamageProcent);
		MessageChat(aIndex, g_ExText.GetText(249), Plus2WizardDamageProcent);
		MessageChat(aIndex, g_ExText.GetText(250), Plus2DefenceProcent);
	}
	else if(lpUser->PremiumTimeType == eVip3)
	{
		MessageChat(aIndex, g_ExText.GetText(246), Plus3ExpProcent);
		MessageChat(aIndex, g_ExText.GetText(247), Plus3DropZenProcent);
		MessageChat(aIndex, g_ExText.GetText(248), Plus3DamageProcent);
		MessageChat(aIndex, g_ExText.GetText(249), Plus3WizardDamageProcent);
		MessageChat(aIndex, g_ExText.GetText(250), Plus3DefenceProcent);
	}

	MessageChat(aIndex,g_ExText.GetText(251),(lpUser->PremiumTime/60));

	this->UserBuff(aIndex);
}

void PremiumSystemEx::GC_Config(int aIndex)
{
	if(!this->ActiveSystem)
	{
		return;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	GC_PREMIUM_CONFIG pSend;
	pSend.h.set((LPBYTE)&pSend, 0xFB, 0xAD, sizeof(pSend));
	pSend.OfflineModeAttackFreePremiumRang = this->m_iOfflineModeAttackFreePremiumRang;
	pSend.OfflineModePickUpPremiumRang = this->m_iOfflineModePickUpPremiumRang;
	DataSend(aIndex, (LPBYTE)&pSend, pSend.h.size);
}

/*
	AT_VIP_SILVER = 171,
	AT_VIP_GOLD = 172,
	AT_VIP_PLATINUM = 173,
*/

void PremiumSystemEx::UserBuff(int aIndex)
{
	if(!this->ActiveSystem)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->PremiumTimeType == eVip1)
	{
		gObjApplyBuffEffectDuration(lpUser, AT_VIP_SILVER, 0, 0, 0, 0, lpUser->PremiumTime);
	}
	else if(lpUser->PremiumTimeType == eVip2)
	{
		gObjApplyBuffEffectDuration(lpUser, AT_VIP_GOLD, 0, 0, 0, 0, lpUser->PremiumTime);
	}
	else if(lpUser->PremiumTimeType == eVip3)
	{
		gObjApplyBuffEffectDuration(lpUser, AT_VIP_PLATINUM, 0, 0, 0, 0, lpUser->PremiumTime);
	}
}

#endif