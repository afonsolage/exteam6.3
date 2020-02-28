#include "StdAfx.h"
#include "user.h"
#define OFF_EXP_DIR "..\\Data\\ExData\\OffExp.ini"


#define DEBUG_OFFEXP	1
class cOffExp
{
public:
	int Enable;
	int KickFallen;
	int EnableTime;
	int TimeEnd;

	int PriceZen;
	int PriceCredit;
	int PriceWCoinC;
	int PriceWCoinP;
	int PriceGoblin;

	int TickPriceEnable;
	int TickTimeMin;
	int TickPriceType;
	int TickPrice;

	void LoadConfig();

	void OffExpStart(int aIndex, int Time);

	void MainFunction(int aIndex);

	void DarkKnightOff(LPOBJ lpObj);
	void DarkWizardOff(LPOBJ lpObj);
	void FairyElfOff(LPOBJ lpObj);
	void MagicGladiatorOff(LPOBJ lpObj);
	void DarkLordOff(LPOBJ lpObj);
	void SummonerOff(LPOBJ lpObj);
	void RageFighterOff(LPOBJ lpObj);

	void UseMana(int aIndex);
	void UseLife(int aIndex);

	int SearchTarget(LPOBJ lpObj);

	bool CheckTerrain(LPOBJ lpObj);
};
extern cOffExp OffExp;
// ----------------------------------------------------------------------------------------------
