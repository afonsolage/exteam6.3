#pragma once

#define ONLINEBONUS_DIR "..\\Data\\ExData\\OnlineBonus.ini"

class OnlineBonus
{
private:
	int Enable;

	int WCoinCActive;
	int WCoinCTime;
	int WCoinCBonus;

	int WCoinPActive;
	int WCoinPTime;
	int WCoinPBonus;

	int GoblinActive;
	int GoblinTime;
	int GoblinBonus;
	int GoblinBonusVIP;
	float GoblinBonusPVPMult;

	int ExCredActive;
	int ExCredTime;
	int ExCredBonus;

public:
	void Load();
	void TickTime(int aIndex);
};
extern OnlineBonus gOnlineBonus;

