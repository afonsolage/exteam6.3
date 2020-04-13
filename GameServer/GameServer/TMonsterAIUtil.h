#pragma once

#include "user.h"

class TMonsterAIUtil  
{

public:

	TMonsterAIUtil();
	virtual ~TMonsterAIUtil();

	BOOL FindPathToMoveMonster(LPOBJ lpObj, int iTargetX, int iTargetY, int iMaxPathCount, BOOL bPreventOverMoving);
	BOOL SendMonsterMoveMsg(LPOBJ lpObj);
	BOOL CheckMovingCondition(LPOBJ lpObj);
	void SendMonsterV2Msg(LPOBJ lpObj, LPBYTE lpMsg, int size);
	BOOL CheckMoveRange(LPOBJ lpObj, int iTargetX, int iTargetY);
	BOOL GetXYToPatrol(LPOBJ lpObj);
	BOOL GetXYToEascape(LPOBJ lpObj);
	BOOL GetXYToChase(LPOBJ lpObj);
	BOOL FindMonViewportObj(int iObjIndex, int iTargetObjIndex);
	BOOL FindMonViewportObj2(int iObjIndex, int iTargetObjIndex);
	void __cdecl SendChattingMsg(int iObjIndex, char* lpszMsg, ...);

};
