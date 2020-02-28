#ifndef BATTLESOCCERMANAGER_H
#define BATTLESOCCERMANAGER_H


#if _MSC_VER > 1000
#pragma once
#endif

#define MAX_BATTLESOCCER_TIME 600000

#include "User.h"

class CBattleSoccerManager
{

public:

	CBattleSoccerManager();
	virtual ~CBattleSoccerManager();
};


#define BATTLE_SOCCER_GROUND_RANGE(value) ( ((value)< 0)?FALSE:((value) >= MAX_BATTLESOCCER_GROUND)?FALSE:TRUE  )
	
void InitBattleSoccer();
void ClearBattleSoccer();
BOOL gCheckBlankBattleGround();
int gCheckBattleGroundTimer();
void gBattleGroundEnable(int n, BOOL enable);
void gSetBattleTeamMaster(int ground, int team, char * szname, _GUILD_INFO_STRUCT * lpGuild);
void gBattleGetTeamPosition(int ground, int team, short & X, short & Y);
char * GetBattleTeamName(int ground, int team);
void SetBattleTeamScore(int ground, int team, int score);
int  GetBattleTeamScore(int ground, int team);
void BattleSoccerGoalStart(int ground);
void BattleSoccerGoalEnd(int ground);
int  GetBattleSoccerGoalMove(int ground);
BOOL gBattleSoccerScoreUpdate(int ground, int team);
int  gCheckGoal(int x, int y, int & ground);
int  gCheckBattleGround(LPOBJ lpObj);


#endif