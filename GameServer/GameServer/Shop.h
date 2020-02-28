#ifndef ___SHOP_H
#define ___SHOP_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\common\zzzitem.h"
#if(DONATE_SHOP==TRUE)
#define DONAT_SHOP_START	20
#define DONAT_SHOP_END		45
#define MAX_SHOP 46
#else
#define MAX_SHOP 21 //15 confirmed season 2.5 (18 max shop)
#endif
#define MAX_ITEM_IN_SHOP 120

#if(DONATE_SHOP==TRUE)
enum ePrice
{
	ePriceZen = 1,
	ePriceBonus,
	ePriceCredit,
};

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
#endif

class CShop
{

public:

	CShop();
	virtual ~CShop();

	void Init();
	BOOL LoadShopItem(int Shopnumber);
	BOOL LoadShopItem(char* filename);
	int InsertItem(int type, int index, int level, int dur, int op1,  int op2, int op3, int Excellent, int Ancient);
	int InentoryMapCheck(int sx, int sy, int width,  int height);
#if(DONATE_SHOP==TRUE)
	BOOL InsertItemSocket(int type, int index, int level, int dur, int op1, int op2 ,int op3, int Excellent, int Ancient, BYTE Sock1, BYTE Sock2, BYTE Sock3, BYTE Sock4, BYTE Sock5, BYTE iPayType, DWORD iPayPrice);

	BOOL InsertItemEx(int type, int index, int level, int dur, int op1, int op2 ,int op3, int Excellent, int Ancient, BYTE iPayType, DWORD iPayPrice);
	BOOL LoadShopItemEx(char* filename );
	void GC_ShopInfo(int aIndex);
	bool CheckBuyItemEx(int aIndex, int ItemPos, int &iStoreTaxMoney);
	bool BuyItemEx(int aIndex, int ItemPos);
#endif

public:

	BYTE ShopInventoryMap[MAX_ITEM_IN_SHOP];	// 4
	int ItemCount;	// 7C
	CItem m_item[MAX_ITEM_IN_SHOP];	// 80
	BYTE SendItemData[MAX_ITEM_IN_SHOP*(MAX_ITEM_INFO+1)];	// 5300
	int SendItemDataLen;	// 56C0
#if(DONATE_SHOP==TRUE)
	ShopPay_DATA ShopEx[MAX_ITEM_IN_SHOP];
#endif
};
#if(DONATE_SHOP==TRUE)
struct CG_NEW_CASH_SHOP
{
	PBMSG_HEAD2 h;
	WORD Number;
};
void NewShopRecv(CG_NEW_CASH_SHOP* Recv, int aIndex);
#endif
BOOL ShopDataLoad();
extern CShop ShopC[MAX_SHOP];

#endif