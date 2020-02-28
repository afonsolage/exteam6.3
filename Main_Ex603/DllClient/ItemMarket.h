#pragma once

#define DEV_PLAYERSHOP	0

#if(DEV_PLAYERSHOP)



#define MARKET_ITEM_VERSION		0

#define MARKET_ITEM_BUFFER		16
#define MARKET_ITEM_MAX			16

struct MARKET_INFO
{
	char Name[10];
	short ItemType;
	float ItemDurability;
	BYTE ItemData[MAX_ITEM_INFO];
	int Price;
};

// GAME SERVER - CLIENT 

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
	void LoadIMG();
	void Bind();
	void DrawMain();
	void DrawShop();
	void DrawItem(int Width, int Height, int X, int Y, int Type, int Index, int Level);
	void DrawPrice();
	void DrawToolTip(BYTE* Buffer, float X, float Y);

	void Button(DWORD Event);
	void Scroll(MOUSEHOOKSTRUCTEX * Mouse, WPARAM wParam);

	void RecvItemList(PMSG_SEND_MARKET_ITEM* lpMsg);
	void AddItemList(short Type, float Durability, LPBYTE Data, ObjectItem Item);
	int CheckItemInfo(signed int a1);

	int m_Page;
	int m_ScrollY;

	ObjectItem m_Data[MARKET_ITEM_MAX];
};

extern CItemMarket g_ItemMarket;

#endif
