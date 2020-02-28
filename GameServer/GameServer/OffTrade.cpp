#include "StdAfx.h"

#ifdef _OFFTRADE_

#include "OffTrade.h"
#include "user.h"
#include "giocp.h"
#include "Message.h"
#include "SProtocol.h"
#include "logproc.h"
#include "DSProtocol.h"
#include "ConnectEx.h"
#include "ExUser.h"
#include "ExLicense.h"
#include "ExFunction.h"
#include "PersonalShopEx.h"
#include "ExGDManager.h"
#include "ExText.h"

cOffTrade gOffTrade;

void cOffTrade::Load()
{
	//CheckFile(OFFTRADE_DIR);

	this->Enable = GetPrivateProfileInt("Common","Enable",1,OFFTRADE_DIR);

	this->OffTradeZen = GetPrivateProfileInt("Common","OffTradeZen",1,OFFTRADE_DIR);
	this->OffTradeCredits = GetPrivateProfileInt("Common","OffTradeCredits",1,OFFTRADE_DIR);
	this->OffTradeWcoinC = GetPrivateProfileInt("Common","OffTradeWcoinC",1,OFFTRADE_DIR);
	this->OffTradeWcoinP = GetPrivateProfileInt("Common","OffTradeWcoinP",1,OFFTRADE_DIR);
	this->OffTradeGoblin = GetPrivateProfileInt("Common","OffTradeGoblin",1,OFFTRADE_DIR);

	this->OffTradeChaos = GetPrivateProfileInt("Common","OffTradeChaos",1,OFFTRADE_DIR);
	this->OffTradeBless = GetPrivateProfileInt("Common","OffTradeBless",1,OFFTRADE_DIR);
	this->OffTradeSoul = GetPrivateProfileInt("Common","OffTradeSoul",1,OFFTRADE_DIR);
	this->OffTradeLife = GetPrivateProfileInt("Common","OffTradeLife",1,OFFTRADE_DIR);

	this->OnlineOffSell = GetPrivateProfileInt("Common","OnlineOffSell",0,OFFTRADE_DIR);

	this->WorkOnlyLorenMarket = GetPrivateProfileInt("Common","WorkOnlyLorenMarket",0,OFFTRADE_DIR);
	
}

void cOffTrade::CreateOffTrade(int aIndex, int type)
{
	if(!this->Enable)return;

	LPOBJ lpObj = &gObj[aIndex];

	if(type == OFFZEN_DC)	//Check OffTrade Zen Enable
	{
		if(!this->OffTradeZen) return;
	}
	else if (type == OFFCR_DC)
	{
		if(!this->OffTradeCredits) return;
	}
	else if (type == OFFWC_DC)
	{
		if(!this->OffTradeWcoinC) return;
	}
	else if (type == OFFWP_DC)
	{
		if(!this->OffTradeWcoinP) return;
	}
	else if (type == OFFWG_DC)
	{
		if(!this->OffTradeGoblin) return;
	}
	else if (type == OFFCHAOS_DC)
	{
		if(!this->OffTradeChaos) return;
	}
	else if (type == OFFBLESS_DC)
	{
		if(!this->OffTradeBless) return;
	}
	else if (type == OFFSOUL_DC)
	{
		if(!this->OffTradeSoul) return;
	}
	else if (type == OFFLIFE_DC)
	{
		if(!this->OffTradeLife) return;
	}
	else
	{
		return;
	}

	if(this->WorkOnlyLorenMarket && lpObj->MapNumber != 79)
	{
		MsgNormal(aIndex,g_ExText.GetText(45));
		return;
	}

	if(lpObj->MapNumber == MAP_INDEX_CASTLESIEGE)
	{
		MsgNormal(aIndex,g_ExText.GetText(46));
		return;
	}


	if(lpObj->m_bPShopOpen == false)
	{
		MsgNormal(aIndex,g_ExText.GetText(47));
		return;
	}

	if(lpObj->MapNumber==0 || lpObj->MapNumber==2 || lpObj->MapNumber==3 || lpObj->MapNumber==51 || lpObj->MapNumber==79)
	{
//#if(CUSTOM_PERSONAL_SHOP==TRUE)
		if(g_PersonalShopEx.Enable)
		{
			char szBuff[256] = { 0 };

			if(lpObj->MapNumber==0)
			{
				sprintf_s(szBuff,g_ExText.GetText(48),lpObj->Name,lpObj->X,lpObj->Y);
			}
			else if(lpObj->MapNumber==2)
			{
				sprintf_s(szBuff,g_ExText.GetText(49),lpObj->Name,lpObj->X,lpObj->Y);
			}
			else if(lpObj->MapNumber==3)
			{
				sprintf_s(szBuff,g_ExText.GetText(50),lpObj->Name,lpObj->X,lpObj->Y);
			}
			else if(lpObj->MapNumber==51)
			{
				sprintf_s(szBuff,g_ExText.GetText(51),lpObj->Name,lpObj->X,lpObj->Y);
			}
			else if(lpObj->MapNumber==79)
			{
				sprintf_s(szBuff,g_ExText.GetText(52),lpObj->Name,lpObj->X,lpObj->Y);
			}
			else
			{
				GCServerMsgStringSend(g_ExText.GetText(53), aIndex, 1);
				return;
			}

			AllSendServerMsg(szBuff);
		}
		else
		{
//#else


			if(type == OFFZEN_DC)
			{
				strcpy(lpObj->m_szPShopText,g_ExText.GetText(54));
			}
			else if(type == OFFCR_DC)
			{
				strcpy(lpObj->m_szPShopText,g_ExText.GetText(55));
			}
			else if(type == OFFWC_DC)
			{
				if (g_ExLicense.CheckUser(eExUB::snaker))
				{
					strcpy(lpObj->m_szPShopText,".::元宝商店::.");
				}
				else
				{
					strcpy(lpObj->m_szPShopText,g_ExText.GetText(56));
				}
			}
			else if(type == OFFWP_DC)
			{
				if (g_ExLicense.CheckUser(eExUB::snaker))
				{
					strcpy(lpObj->m_szPShopText,".::积分商店::.");
				}
				else
				{
					strcpy(lpObj->m_szPShopText,g_ExText.GetText(57));
				}
			}
			else if(type == OFFWG_DC)
			{
				strcpy(lpObj->m_szPShopText,g_ExText.GetText(58));
			}
			else if(type == OFFCHAOS_DC)
			{
				strcpy(lpObj->m_szPShopText,g_ExText.GetText(59));
			}
			else if(type == OFFBLESS_DC)
			{
				strcpy(lpObj->m_szPShopText,g_ExText.GetText(60));
			}
			else if(type == OFFSOUL_DC)
			{
				strcpy(lpObj->m_szPShopText,g_ExText.GetText(61));
			}
			else if(type == OFFLIFE_DC)
			{
	#ifdef PRIVATE_MODULE
				if(g_ExLicense.CheckUser(eExUB::Vadim))
				{
					strcpy(lpObj->m_szPShopText,".::JOW SHOP::.");
				}
				else
				{
					strcpy(lpObj->m_szPShopText,g_ExText.GetText(62));
				}
	#else
				strcpy(lpObj->m_szPShopText,LIFE_SHOP);
	#endif
			}

			if(lpObj->MapNumber==0)
				MessaageAllGlobal(g_ExText.GetText(63),lpObj->m_szPShopText,lpObj->Name,lpObj->X,lpObj->Y);
			else if(lpObj->MapNumber==2)
				MessaageAllGlobal(g_ExText.GetText(64),lpObj->m_szPShopText,lpObj->Name,lpObj->X,lpObj->Y);
			else if(lpObj->MapNumber==3)
				MessaageAllGlobal(g_ExText.GetText(65),lpObj->m_szPShopText,lpObj->Name,lpObj->X,lpObj->Y);
			else if(lpObj->MapNumber==51)
				MessaageAllGlobal(g_ExText.GetText(66),lpObj->m_szPShopText,lpObj->Name,lpObj->X,lpObj->Y);
			else if(lpObj->MapNumber==79)
				MessaageAllGlobal(g_ExText.GetText(67),lpObj->m_szPShopText,lpObj->Name,lpObj->X,lpObj->Y);
			//gObjCloseSet(aIndex, 2);
		}
//#endif 
#ifdef _RECONNECT_

	if(type == OFFZEN_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFZEN_DC);
	}
	else if(type == OFFCR_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFCR_DC);
	}
	else if(type == OFFWC_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFWC_DC);
	}
	else if(type == OFFWP_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFWP_DC);
	}
	else if(type == OFFWG_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFWG_DC);
	}
	else if(type == OFFCHAOS_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFCHAOS_DC);
	}
	else if(type == OFFBLESS_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFBLESS_DC);
	}
	else if(type == OFFSOUL_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFSOUL_DC);
	}
	else if(type == OFFLIFE_DC)
	{
		g_ConnectEx.SendClose(aIndex,OFFLIFE_DC);
	}
		g_ConnectEx.SendClose(aIndex,type);
#else
		CloseClient(aIndex);
		lpObj->OffTrade = type;
#endif
	}
	else
	{
		MsgNormal(aIndex,g_ExText.GetText(68));
	}
}

void cOffTrade::ConnectUser(char* Acc)
{
	if(!this->Enable)return;

	for(int i = OBJ_MAXMONSTER; i<OBJMAX;i++)
	{
		LPOBJ lpObj = &gObj[i];
		if(lpObj->Connected == 3)
		{
			if(!strcmp(Acc,lpObj->AccountID))
			{
				if(lpObj->OffTrade != 0)
				{
					g_ExGDManager.GD_OfflineAfk(i, 0, 0);
					GJPUserClose(lpObj->AccountID);
					gObjDel(i);
					lpObj->OffTrade = 0;
				}
				return;
			}
		}
	}
}

bool cOffTrade::CheckOnlineUser(int aIndex)
{
	if(!this->Enable) return false;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->OffTrade != 0)
	{
		lpObj->CheckTick = GetTickCount();
		return true;
	}

	return false;
}

bool cOffTrade::CheckMoney(int aSourceIndex, int aIndex, int ItemPos)
{
	if(!this->Enable) return false;

	LPOBJ SourceObj = &gObj[aSourceIndex];
	LPOBJ lpObj = &gObj[aIndex];

	int Value = lpObj->Inventory1[ItemPos].m_iPShopValue;


	if(lpObj->OffTrade == OFFCR_DC)
	{
		if ( SourceObj->ExCred < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of ExCred",
				gObj[aSourceIndex].AccountID, 
				gObj[aSourceIndex].Name, 
				lpObj->AccountID, 
				lpObj->Name);
			//::CGPShopAnsBuyItem(aSourceIndex, lpObj->m_Index, 0, 7);
			MsgNormal(aSourceIndex,g_ExText.GetText(69),Value);
			return false;
		}
	}
	else if(lpObj->OffTrade == OFFWC_DC)
	{
		if ( SourceObj->GameShop.WCoinC < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of WCoinC",
				gObj[aSourceIndex].AccountID, 
				gObj[aSourceIndex].Name, 
				lpObj->AccountID, 
				lpObj->Name);
			MsgNormal(aSourceIndex,g_ExText.GetText(70),Value);
			return false;
		}
	}
	else if(lpObj->OffTrade == OFFWP_DC)
	{
		if ( SourceObj->GameShop.WCoinP < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of WCoinP",
				gObj[aSourceIndex].AccountID, 
				gObj[aSourceIndex].Name, 
				lpObj->AccountID, 
				lpObj->Name);
			MsgNormal(aSourceIndex,g_ExText.GetText(71),Value);
			return false;
		}
	}
	else if(lpObj->OffTrade == OFFWG_DC)
	{
		if ( SourceObj->GameShop.GoblinPoint < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of WCoinG",
				gObj[aSourceIndex].AccountID, 
				gObj[aSourceIndex].Name, 
				lpObj->AccountID, 
				lpObj->Name);
			MsgNormal(aSourceIndex,g_ExText.GetText(72),Value);
			return false;
		}
	}
	else if(lpObj->OffTrade == OFFCHAOS_DC)
	{
		if ( SourceObj->ChaosBank < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of Chaos Bank",
				gObj[aSourceIndex].AccountID, 
				gObj[aSourceIndex].Name, 
				lpObj->AccountID, 
				lpObj->Name);
			MsgNormal(aSourceIndex,g_ExText.GetText(73),Value);
			return false;
		}
	}
	else if(lpObj->OffTrade == OFFBLESS_DC)
	{
		if ( SourceObj->BlessBank < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of Bless Bank",
				gObj[aSourceIndex].AccountID, gObj[aSourceIndex].Name, lpObj->AccountID, lpObj->Name);
			MsgNormal(aSourceIndex,g_ExText.GetText(74),Value);
			return false;
		}
	}
	else if(lpObj->OffTrade == OFFSOUL_DC)
	{
		if ( SourceObj->SoulBank < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of Soul Bank",
				gObj[aSourceIndex].AccountID, gObj[aSourceIndex].Name, lpObj->AccountID, lpObj->Name);
			MsgNormal(aSourceIndex,g_ExText.GetText(75),Value);
			return false;
		}
	}
	else if(lpObj->OffTrade == OFFLIFE_DC)
	{
		if ( SourceObj->LifeBank < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of Life Bank",
				gObj[aSourceIndex].AccountID, gObj[aSourceIndex].Name, lpObj->AccountID, lpObj->Name);
			MsgNormal(aSourceIndex,g_ExText.GetText(76),Value);
			return false;
		}
	}
	else
	{
		if ( SourceObj->Money < Value )
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Lack of Zen",
				SourceObj->AccountID, 
				SourceObj->Name, 	
				lpObj->AccountID, 
				lpObj->Name);

			::CGPShopAnsBuyItem(aSourceIndex, lpObj->m_Index, 0, 7);
			return false;
		}
#if(_CONFLICT_)
		
		if (Value > (MAX_ZEN - lpObj->Money))
		{
			LogAddTD("[PShop] [%s][%s] PShop Item Buy Request Failed : [%s][%s] Max Zen In Inventory",
			SourceObj->AccountID, 
			SourceObj->Name, 	
			lpObj->AccountID, 
			lpObj->Name);
			MsgNormal(aSourceIndex,g_ExText.GetText(77), lpObj->Name);
			MsgNormal(aIndex,g_ExText.GetText(78));
			return false;
		}
#endif
	}
	return true;
}

void cOffTrade::ValueUpdate(int aSourceIndex, int aIndex, int Value)
{
	if(!this->Enable) return;

	LPOBJ SourceObj = &gObj[aSourceIndex];
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->OffTrade == OFFCR_DC)
	{
		SourceObj->ExCred -= Value;
		lpObj->ExCred += Value;
	}
	else if(lpObj->OffTrade == OFFWC_DC)
	{
		SourceObj->GameShop.WCoinC -= Value;
		lpObj->GameShop.WCoinC += Value;
		gGameShop.GDSaveUserInfo(aIndex);
		gGameShop.GDSaveUserInfo(aSourceIndex);
	}
	else if(lpObj->OffTrade == OFFWP_DC)
	{
		SourceObj->GameShop.WCoinP -= Value;
		lpObj->GameShop.WCoinP += Value;
		gGameShop.GDSaveUserInfo(aIndex);
		gGameShop.GDSaveUserInfo(aSourceIndex);
	}
	else if(lpObj->OffTrade == OFFWG_DC)
	{
		SourceObj->GameShop.GoblinPoint -= Value;
		lpObj->GameShop.GoblinPoint += Value;
		gGameShop.GDSaveUserInfo(aIndex);
		gGameShop.GDSaveUserInfo(aSourceIndex);
	}
	else if(lpObj->OffTrade == OFFCHAOS_DC)
	{
		SourceObj->ChaosBank -= Value;
		lpObj->ChaosBank += Value;
		ExUserDataSend(aSourceIndex);
	}
	else if(lpObj->OffTrade == OFFBLESS_DC)
	{
		SourceObj->BlessBank -= Value;
		lpObj->BlessBank += Value;
		ExUserDataSend(aSourceIndex);
	}
	else if(lpObj->OffTrade == OFFSOUL_DC)
	{
		SourceObj->SoulBank -= Value;
		lpObj->SoulBank += Value;
		ExUserDataSend(aSourceIndex);
	}
	else if(lpObj->OffTrade == OFFLIFE_DC)
	{
		SourceObj->LifeBank -= Value;
		lpObj->LifeBank += Value;
		ExUserDataSend(aSourceIndex);
	}
	else
	{
		gObj[aSourceIndex].Money -= Value;
		lpObj->Money += Value;
		::GCMoneySend(aSourceIndex, SourceObj->Money);
		::GCMoneySend(lpObj->m_Index, lpObj->Money);
	}
}

void cOffTrade::UserOnlineOffSell(LPOBJ lpObj)
{
	if(!this->Enable || this->OnlineOffSell) return;

	g_ExGDManager.GD_OfflineAfk(lpObj->m_Index, 0, 0);

	GJPUserClose(lpObj->AccountID);
	gObjDel(lpObj->m_Index);
	lpObj->OffTrade = 0;
}

#endif