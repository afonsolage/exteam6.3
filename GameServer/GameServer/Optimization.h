#pragma once

#include "StdAfx.h"
#include "user.h"
#include "CriticalSectionEx.h"

#if(ENABLE_OPTIMIZATION)

class COptimization
{
public:
		COptimization();
		~COptimization();

	void Load();
	void Run();
	void AddedMemoryObject(int aIndex);
	int GetFirstEmptryIndex(int StartIndex, int MaxIndex);
	int AddObjectUser(SOCKET aSocket, char* ip);
	int AddObjectOffmoder();
	int AddObjectMonster();
	int AddObjectReCall();
	void DeleteObjectCount(int aIndex);
	void ViewePortCPU(short aIndex);

	int GetU();
	int GetM();
	int GetC();

private:
	CCriticalSectionEx m_crit;
	bool m_MemoryObject[OBJMAX];
	int m_UserIndex;
	int m_MonsterIndex;
	int m_ReCallIndex;
};

extern COptimization g_Optimization;

#endif