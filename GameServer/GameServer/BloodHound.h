#include "StdAfx.h"
#include "user.h"

#ifdef BloodHoundEvent

#define MAX_ITEMS_BH 100

#define BLOODHOND_DIR "..\\Data\\ExData\\Events\\BloodHoundEvent.ini"

/*
��� ������� �� ����� �� ������ ������� �������� ����� � ���-��� �������� �� 1��� �� 150-����� ������� � 150 �� 250 ������ � 250�� 350-� 350 �� 400
*/

class cBloodHound
{
private:
	int Enable;

	int NPC;
	int NPC_X;
	int NPC_Y;
	int NPC_Map;

	int EventTime;

	bool StartEvent;
	int TickEvent;

	bool UserCheck[OBJMAX];

	bool UserEvent[OBJMAX];
	int iUserType[OBJMAX];
	int iUserIndex[OBJMAX];
	int iUserLevel[OBJMAX];
	int iUserCount[OBJMAX];
	char iUserName[OBJMAX][50];

	struct 
	{
		int Hour;
		int Minute;
	}sTime[MAX_ITEMS_BH];
	int tCount;

	struct 
	{
		int Type;
		int Index;
		int Level;
		int Count;
		char Name[50];
	}sItem[MAX_ITEMS_BH];
	int sCount;

	struct 
	{
		int Type;
		int Index;
		int Level;
		int Skill;
		int Luck;
		int Opt;
		int Exl;
		int Anc;
	}iReward[MAX_ITEMS_BH];
	int rCount;

public:
	void ReedConfig();
	void UserStart(int aIndex);
	void NPCClick(int aIndex,int aNPC);
	void Times();
	void TakeJob(int aIndex);
	void RunJob(int aIndex);
};
extern cBloodHound BloodHound;

#endif