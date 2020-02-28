#pragma once
// -------------------------------------------------------------------------------

#include "stdafx.h"
//#include "ProtocolDefine.h"
#include "Protocol.h"
#include "Object.h"
// -------------------------------------------------------------------------------

#if(DONATE_SHOP==TRUE)
// -------------------------------------------------------------------------------

//#define BONUS_SHOP			18
//#define SANTA_SHOP			19
#define DONAT_SHOP_START	20
#define DONAT_SHOP_END		45
#define MAX_SHOP			46

#define MAX_ITEM_IN_SHOP	120
#define MAX_ITEMPRICE_ITEM	512

#define MAXPRICEITEM		200
// -------------------------------------------------------------------------------

enum ePriceEx
{
	ePriceZen = 1,
	ePriceBonus,
	ePriceCredit,
};
// -------------------------------------------------------------------------------

struct GC_ShopPay
{
	BYTE ItemType;
	BYTE ItemIndex;
	BYTE ItemLevel;
	BYTE ItemExl;
	BYTE ItemAnc;
	BYTE PayType;
	DWORD PayPrice;
};
// -------------------------------------------------------------------------------

struct CG_NEW_CASH_SHOP
{
	PBMSG_HEAD2 h;
	WORD Number;
};
// -------------------------------------------------------------------------------

struct GC_SHOP_CLICK
{
	PBMSG_HEAD2 h;
	WORD Shop_Num;
};
// -------------------------------------------------------------------------------

struct ShopPay_DATA
{
	BYTE ItemType;
	BYTE ItemIndex;
	BYTE ItemLevel;
	BYTE ItemExl;
	BYTE ItemAnc;
	BYTE PayType;
	DWORD PayPrice;
};
// ----------------------------------------------------------------------------------------------

struct GCDataPrice
{
	BYTE iType;
	BYTE iIndex;
	BYTE iLevel;
	DWORD iPrice;
};
// ----------------------------------------------------------------------------------------------

struct PriceDATA
{
	int iType;
	int iIndex;
	int iLevel;
	int iPrice;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_DONATE_CHECKBUY
{
	PBMSG_HEAD2 h;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_DONATE_ITEMBUY
{
	PBMSG_HEAD2 h;
	BYTE Result;
};
// ----------------------------------------------------------------------------------------------

class DonateShop
{
public:
	void			Load();
	void			LoadItemPrice();
	void			GC_Recv_shop(LPBYTE aRecv);
	void			GC_RecvShopNum(GC_SHOP_CLICK* aRecv);
	bool			CheckItemBuy(short ItemCode, int ItemLevel, int Exl, int Anc, __int64 * Price);
	bool			CheckItemSell(short ItemCode, int ItemLevel, __int64 * Price);
	bool			CheckExellent(int Exl1, int Exl2);
	void			CG_CashSend();
	void			GCStandartShopRecv(LPBYTE aRecv);
	// ----
	static __int64	GetPrice(ObjectItem * lpItem, int Mode);
	static void		ShowBuyPrice(DWORD a1, const char *a2, char *Price);
	static void		ShowSellPrice(DWORD a1, const char *a2, char *Price);
	void			ShopButtonDraw();
	void			ButtonClick(DWORD Event);
	// ----
	bool			DrawDonateCheckBuy();
	void			GCCheckBuyDonateItem(PMSG_DONATE_CHECKBUY* lpMsg);

	// ----
	bool			ShowItem;
	int				ShowType;
	int				ShowItemLevel;
	int				ShowitemAnc;
	__int64			ShowPrice;
	// ----
	int				OpenShop;
	int				ShopNumber;
	int				m_LoadedBuyCount;
	// ----
	ShopPay_DATA	ShopEx[MAX_ITEM_IN_SHOP];

	PriceDATA		databuy[MAXPRICEITEM];
	PriceDATA		datasell[MAXPRICEITEM];

	int				buyCount;
	int				sellCount;
};
extern DonateShop g_DonateShop;
// -------------------------------------------------------------------------------
#endif