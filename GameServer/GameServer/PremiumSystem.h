#include "StdAfx.h"
#include "user.h"

#define PREM_BRONZE 1
#define PREM_SILVER 2
#define PREM_GOLD	3

#define PREMIUM_DIR "..\\Data\\ExData\\PremiumSystem.ini"
#define MAX_RES_PREM 1000
class PremiumSystem
{
private:
	int Enable;

	int PlusExp;
	int PlusZen;

#ifdef PREM_TYPE
	int BronzePlusExp;
	int BronzePlusZen;
	int SilverPlusExp;
	int SilverPlusZen;
	int GoldPlusExp;
	int GoldPlusZen;
#endif
	struct 
	{
		int Res;
		int Exp;
		int Zen;
	} NumberResPrem[MAX_RES_PREM];
	int CountRes;


public:
	int Value;
	int Price;

	void Loader();
	void TickTime(int aIndex);
	void Exp(LPOBJ lpObj, __int64 & Experience);
	void Zen(LPOBJ lpObj, float & money);
	void ChatSell(int aIndex, LPBYTE Protocol);
	void ConnectInfo(int aIndex);
	bool CheckPremium(int aIndex);
	bool CheckPremiumServer(int aIndex);

	bool m_PremiumServerEnable;

};
extern PremiumSystem Premium;