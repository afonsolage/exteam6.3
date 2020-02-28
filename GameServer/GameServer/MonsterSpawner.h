#include "StdAfx.h"
#include "user.h"
#define MAX_MONSTER_SPAWNER 100
#define MONSTER_SPAWNER_DIR "..\\Data\\ExData\\MonsterSpawner.ini"

struct sMonsterSpawn
{
	int ID;
	int MapNumber;
	int X;
	int Y;
	int WeekDay;
	int TimeHour;
	int TimeMin;
	char Message[100];
	bool Status;
	int Index;
};

class cMonsterSpawner
{
	
private:
	sMonsterSpawn MonsterSpawn[MAX_MONSTER_SPAWNER];
	int Enable;
	char Message[50];
	int CountMobs;
public:
	void Load();
	bool StartMonster(int );
	void KillMob(LPOBJ );
	void TickTime();

};
extern cMonsterSpawner gMonsterSpawner;

