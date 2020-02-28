#pragma once

#if(DEV_MONSTERTIME)

#define MAX_MONSTERTIME	100

struct MONSTERTIME_INFO
{
	int Class;
	int MapNumber;
	int MapX;
	int MapY;
	int Day;
	int Hour;
	int Minute;
};

struct MONSTERTIME_DATA
{
	int Class;
	int Index;
	int Pos;
};

class CMonsterTime
{
public:
		CMonsterTime();
		~CMonsterTime();

	void Init();
	void Load();
	void Read(char* filename);
	void Run();
	void LoadMonsterPos();
	int GetMonsterPos(WORD Type, BYTE Map, BYTE X, BYTE Y);
	void AddMonster(int Num, int Map);
	void DieMonster(int aIndex, int aMonsterIndex);
	void ReloadMonster();

	int m_Enable;
	int m_LoadPos;
	int m_LoadCount;

	int m_Loaded;

	MONSTERTIME_INFO m_Info[MAX_MONSTERTIME];
	MONSTERTIME_DATA m_Data[MAX_MONSTERTIME];
};

extern CMonsterTime g_MonsterTime;

#endif