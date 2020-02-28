#pragma once

#include "StdAfx.h"
#include "user.h"

#define _MAX_BMQUEST		1000
#define _DIR_BMQUEST		"..\\Data\\ExData\\BMQuest.ini"
#define _MAX_CLASS_BMQUEST	8

struct BMQuestRandOpt_DATA
{
	int NeedLevel;
	int NeedRageLevel;
	int AddDamageReflect;
	int AddDamage;
	int AddDefense;
	int AddCriticalDamage;
	int AddExcelentDamage;
	int AddLife;
};

class cBMQuest
{
public:
	void StartConfig();
	void StartUP();
	void AddedCharacter(int aIndex);
	void CharacterInformation(int aIndex);
	bool NPCClick(int aIndex,int aNPC);
	void NPCdialogue(int aIndex,int aNPC);
	void MonsterKill(int aIndex, int aMob);
	void Presents(int aIndex, int Present, int Gifts);

	struct
	{
		int Mob;
		int Coun;
		int proc;
		int rew;
		int gift;
		char msg[100];
		char msg2[100];
	}Quest[_MAX_CLASS_BMQUEST][_MAX_BMQUEST];

	int Enable;
	int NPC;
	int NPC_Map;
	int	NPC_X;
	int	NPC_Y;
	int Reset;
	int Count[_MAX_CLASS_BMQUEST];

	bool RandOptNpcDialog(int aIndex, int aNpcIndex);
	short m_sRandOptNPC_Class;
	BYTE m_btRandOptNPC_Map;
	BYTE m_btRandOptNPC_X;
	BYTE m_btRandOptNPC_Y;

	void CheckLevels(int aIndex);
	std::vector<BMQuestRandOpt_DATA> m_RandOpt;
};
extern cBMQuest BMQuest;