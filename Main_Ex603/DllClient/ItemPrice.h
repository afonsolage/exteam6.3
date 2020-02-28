#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Object.h"
#ifdef _ITEM_PRICE_MANAGER_
// ----------------------------------------------------------------------------------------------

#define ITEMPRICE_DEBUG		0
#define MAX_ITEMPRICE_ITEM	512
// ----------------------------------------------------------------------------------------------

enum ePrice
{
	eZen,
	eCredit,
	eWCoin,
	eWCoinP,
	eGoblinPoint,
};
// ----------------------------------------------------------------------------------------------

struct ITEMPRICE_DATA
{
	WORD ItemType;
	WORD ItemIndex;
	BYTE ItemLevel;
	BYTE PriceType;
	__int64 Price;
};
// ----------------------------------------------------------------------------------------------

class ItemPrice
{
public:
	ItemPrice();
	~ItemPrice();
	// ----
	bool			Enable;
	bool			SellItemNullZen;
	// ----
	bool			ShowItem;
	int				ShowType;
	int				ShowItemLevel;
	__int64			ShowPrice;
	// ----
	void			Init();
	void			ReadList(char * File);
	void			Load();
	bool			CheckItemSell(short ItemCode, int ItemLevel, __int64 * Price);
	bool			CheckItemBuy(short ItemCode, int ItemLevel, __int64 * Price);
	// ----
	static __int64	GetPrice(ObjectItem * lpItem, int Mode);
	static void		ShowSellPrice(DWORD a1, const char *a2, char *Price);
	static void		ShowBuyPrice(DWORD a1, const char *a2, char *Price);
	static void		ShowItemLevelName(DWORD a1, const char *a2, char * Level);
	static int		PriceItemDiv(int a1, int a2);
	// ----
private:
	int				m_LoadedSellCount;
	int				m_LoadedBuyCount;
	// ----
	ITEMPRICE_DATA	m_SellData[MAX_ITEMPRICE_ITEM];
	ITEMPRICE_DATA	m_BuyData[MAX_ITEMPRICE_ITEM];
	// ----
}; extern ItemPrice gItemPrice;
// ----------------------------------------------------------------------------------------------
#endif