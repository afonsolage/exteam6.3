#pragma once

#include "StdAfx.h"

struct MOB_MSG_DATA 
{
	int iClass;
	char szMsg[100];
};

class CMonsterMsg
{
public:
		 CMonsterMsg();
		 ~CMonsterMsg();

	void Init();
	void Load();
	void Read(char* filename);
	void RegenMessage(int aIndex);
	void DieMessage(int aIndex, int aTargetIndex);

	std::vector<MOB_MSG_DATA> m_Data;
};
extern CMonsterMsg g_MonsterMsg;