#include "StdAfx.h"

#ifdef _OFFTRADE_

#include "user.h"

#define OFFTRADE_DIR	"..\\Data\\ExData\\OffTrade.ini"

#define ZEN_SHOP		".::ZEN SHOP::."
#define CREDIT_SHOP		".::CREDIT SHOP::."
#define WCOIN_SHOPC		".::WCOIN SHOP::."
#define WCOIN_SHOPP		".::WCOIN(P) SHOP::."
#define WCOIN_SHOPG		".::GOBLIN SHOP::."
#define CHAOS_SHOP		".::CHAOS SHOP::."
#define BLESS_SHOP		".::BLESS SHOP::."
#define SOUL_SHOP		".::SOUL SHOP::."
#define LIFE_SHOP		".::LIFE SHOP::."

//#define OFFTRADE_ZEN	1
//#define OFFTRADE_CR		2
//#define OFFTRADE_WC		3
//#define OFFTRADE_WP		4
//#define OFFTRADE_WG		5

class cOffTrade
{
public:
	void Load();
	void CreateOffTrade(int aIndex,int type);
	void ConnectUser(char* Acc);
	bool CheckOnlineUser(int aIndex);
	bool CheckMoney(int aSourceIndex, int aIndex, int ItemPos);
	void ValueUpdate(int aSourceIndex, int aIndex, int Value);

	void UserOnlineOffSell(LPOBJ lpObj);

private:
	bool Enable;
	bool OffTradeZen;
	bool OffTradeCredits;
	bool OffTradeWcoinC;
	bool OffTradeWcoinP;
	bool OffTradeGoblin;

	bool OffTradeChaos;
	bool OffTradeBless;
	bool OffTradeSoul;
	bool OffTradeLife;

	bool OnlineOffSell;

	bool WorkOnlyLorenMarket;

};
extern cOffTrade gOffTrade;

#endif