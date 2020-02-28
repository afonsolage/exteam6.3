#include "StdAfx.h"
#define HH_DIR			"..\\Data\\ExData\\Events\\HappyHour.ini"
#define MAX_HH_STRUCT	128

class cHappyHour
{
public:
	int Enable;
	int PlusExp;
	int PlusDrop;
	bool StartHappyHour;

	struct  
	{
		int Hour;
		int Min;

		int EndHour;
		int EndMin;
	}HappyStruct[MAX_HH_STRUCT];

	int Count;
public:
	void LoadConfig();
	void LoadFile();
	void Timetick();

	void UserBonusExp(__int64 & Experience);
	void UserBonusZen(float & money);
	
};extern cHappyHour HappyHour;