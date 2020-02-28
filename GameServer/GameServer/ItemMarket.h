#pragma once

#define DEV_PLAYERSHOP	0

#if(DEV_PLAYERSHOP)

#define MARKET_ITEM_BUFFER		16
#define MARKET_ITEM_MAX			16

struct MARKET_DATA
{
	char Name[10];
	BYTE Item[MARKET_ITEM_BUFFER];
	int Price;
};

struct MARKET_INFO
{
	char Name[10];
	short ItemType;
	float ItemDurability;
	BYTE ItemData[MAX_ITEM_INFO];
	int Price;
};

// GAME SERVER - DATA SERVER

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

// ----

struct SDHP_SELL_MARKET_ITEM
{
	PBMSG_HEAD2 h;
	int Result;
	int aIndex;
	MARKET_DATA Data;
};

struct SDHP_SELL_MARKET_RESULT
{
	PBMSG_HEAD2 h;
	int Result;
	int aIndex;
	MARKET_DATA Data;
};

// ----

struct SDHP_BUY_MARKET_ITEM
{
	PBMSG_HEAD2 h;
	int Result;
	int aIndex;
};

struct SDHP_BUY_MARKET_RESULT
{
	PBMSG_HEAD2 h;
	int Result;
	int aIndex;
};

// GAME SERVER - GAME CLIENT 

struct PMSG_SEND_MARKET_ITEM
{
	PBMSG_HEAD2 h;
	int Result;
	MARKET_INFO Info[MARKET_ITEM_MAX];
};

class CItemMarket
{
public:
		 CItemMarket();
		 ~CItemMarket();

	void Init();
	void Load();

	void Protocol(BYTE protoNum, BYTE *aRecv);

	void ReqItemList(int aIndex, int NumPage);
	void RecvItemList(SDHP_ANS_MARKET_ITEM* lpMsg);

	void SellItem(int aIndex);
	void SellResult(SDHP_SELL_MARKET_RESULT* lpMsg);

	void BuyItem(int aIndex);
	void BuyResult(SDHP_BUY_MARKET_RESULT* lpMsg);
};

extern CItemMarket g_ItemMarket;

#endif
