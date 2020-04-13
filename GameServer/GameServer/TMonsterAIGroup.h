#pragma once

#include "TMonsterAIGroupMember.h"

#define MAX_MONSTER_AI_GROUP		(100)	//(50)	//Season 5 ImperialFort
#define MAX_MONSTER_AI_GROUP_MEMBER	(200)	//(100)	//Season 5 ImperialFort

class TMonsterAIGroup  
{

public:

	TMonsterAIGroup();
	virtual ~TMonsterAIGroup();

	static void Init(int iGroupNumber);
	static void InitAll();
	static BOOL LoadData(char* lpszFileName);
	static BOOL DelAllGroupInfo();
	static BOOL DelGroupInstance(int iGroupNumber);
	static void ChangeAIOrder(int iGroupNumber, int iAIOrder);
	static TMonsterAIGroupMember* FindGroupMember(int iGroupNumber, int iGuid);
	static TMonsterAIGroupMember* FindGroupMemberToSommon(int iObjIndex, int iGroupNumber, int iGuid);
	static TMonsterAIGroupMember* FindGroupMemberToHeal(int iObjIndex, int iGroupNumber, int iGuid, int iDistance);
	static int FindGroupLeader(int iGroupNumber);
	static int FindGroupMemberObjectIndex(int iGroupNumber, int iGuid);
	static BOOL s_bDataLoad;
	static TMonsterAIGroupMember s_MonsterAIGroupMemberArray[MAX_MONSTER_AI_GROUP][MAX_MONSTER_AI_GROUP_MEMBER];
	static int s_iMonsterAIGroupMemberCount[MAX_MONSTER_AI_GROUP];

private:


};