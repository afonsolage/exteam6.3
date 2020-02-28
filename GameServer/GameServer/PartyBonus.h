#include "stdAfx.h"
#pragma once
#include "user.h"

#define MAX_CLASS_BONUS 20
#define PartyBonus_DIR "..\\Data\\ExData\\PartyBonus.ini"

struct sClassBonus
{
	int dw;
	int dk;
	int elf;
	int mg;
	int dl;
	int sum;
	int rf;
	int Bonus;
};
class PartyBonus
{
public:
	void Init();
	void Load();
	int ExpNearbyCount(LPOBJ lpObj, LPOBJ lpTargetObj, int viewplayer);
	int ExpClassBonus(LPOBJ lpObj, LPOBJ lpTargetObj, int viewplayer);
	bool isEnable(int viewplayer);
//private:
	int Enable;
	sClassBonus ClassBonus[MAX_CLASS_BONUS];
	int Count;
	int nearbycount1;
	int nearbycount2;
	int nearbycount3;
	int nearbycount4;
	int nearbycount5;
};

extern PartyBonus gPartyBonus;

