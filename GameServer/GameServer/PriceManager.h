#include "StdAfx.h"
#ifdef _PRICE_MANAGER_

#define MAX_PRICE_ITEM 512
#define PRICEMANAGER_DIR "..\\Data\\ExData\\PriceManager.ini"

class cPriceManager
{
private:
	int Enable;
	int AllSellNull;

	struct 
	{
		int Type;
		int Index;
		int Level;
		int PriceType;	//0 - Zen, 1 - ExPoint, 2 - WCoin , 3 - Credit
		int Price;
	}SellPrice[MAX_PRICE_ITEM];
	int sCount;

	struct 
	{
		int Type;
		int Index;
		int Level;
		int PriceType;	//0 - Zen, 1 - ExPoint, 2 - WCoin , 3 - Credit
		int Price;
	}BuyPrice[MAX_PRICE_ITEM];
	int bCount;

public:
	void LoadConfig();
	void SellPriceItem(int aIndex,int iPos,int & money);
	bool BuyPriceItem(int aIndex, int iType, int &iStoreTaxMoney, int ItemLevel);
	void ReadList(char * File);
};
extern cPriceManager PriceManager;
#endif