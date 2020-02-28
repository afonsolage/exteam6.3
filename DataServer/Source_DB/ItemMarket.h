#pragma once

#define DEV_PLAYERSHOP			1

#if(DEV_PLAYERSHOP)

#define MARKET_ITEM_BUFFER		16
#define MARKET_ITEM_MAX			16

struct MARKET_DATA
{
	char Name[10];
	BYTE Item[MARKET_ITEM_BUFFER];
	int Price;
};

struct SDHP_REQ_MARKET_ITEM
{
	PBMSG_HEAD2 h;
	int Result;
	int aIndex;
	int Page;
};

struct SDHP_ANS_MARKET_ITEM
{
	PWMSG_HEAD2 h;
	int Result;
	int aIndex;
	MARKET_DATA Data[MARKET_ITEM_MAX];
};

struct SDHP_BUY_MARKET_ITEM
{
	PBMSG_HEAD2 h;
	int Result;
	int aIndex;
};

struct SDHP_SELL_MARKET_ITEM
{
	PBMSG_HEAD2 h;
	int Result;
	int aIndex;
	MARKET_DATA Data;
};

class CItemMarket
{
public:
		 CItemMarket();
		 ~CItemMarket();

	void Init();
	void Load();

	bool Connect();
	void CreateTable();
	void Protocol(BYTE protoNum, BYTE *aRecv, int uIndex);

	void ReqItemList(SDHP_REQ_MARKET_ITEM* lpMsg, int uIndex);

	void SellItem(SDHP_SELL_MARKET_ITEM* lpMsg, int uIndex);
	void BuyItem(SDHP_BUY_MARKET_ITEM* lpMsg, int uIndex);

	//MARKET_DATA GetItemData(int id);
	
	CQuery m_DBQuery;
	CQuery m_DBItem;
};

extern CItemMarket g_ItemMarket;

#endif
