#pragma once

#include "StdAfx.h"
#include "protocol.h"

#define MAX_exTIME	100
// ----------------------------------------------------------------------------------------------

#define EVENT_TIMER_EX	1
// ----------------------------------------------------------------------------------------------

struct BC_Time
{
	int Hour;
	int Min;
};

struct DS_Time
{
	int Hour;
	int Min;
};

struct CC_Time
{
	int Hour;
	int Min;
};

struct GD_Time
{
	int Hour;
	int Min;
};

struct WW_Time
{
	int Hour;
	int Min;
};
// ----------------------------------------------------------------------------------------------

struct GCTEventTime
{
	PBMSG_HEAD2 h;
	DWORD TimeBC;
	DWORD TimeDS;
	DWORD TimeCC;
	DWORD TimeGD;
	DWORD TimeWW;
	// --
	DWORD TimeLora;
	DWORD TimeDevias;
	DWORD TimeTvT;
	DWORD TimePandora;
	DWORD TimeEvengelion;
	DWORD TimeShop;
	DWORD TimeHappy;
	DWORD TimeDropEvent;
	// --
	DWORD TimeCryWolf;
	DWORD TimeCastleSiege;
	DWORD TimeDungeonSiege;
	DWORD TimeRedDragon;
};
// ----------------------------------------------------------------------------------------------

class cEventTimer
{
public:
	cEventTimer();
	~cEventTimer();

	int Enable;

	void LoadTimer();

	void Client();
	void NewEvent();


private:
	BC_Time BC[MAX_exTIME];
	int CountBC;
	DS_Time DS[MAX_exTIME];
	int CountDS;
	CC_Time CC[MAX_exTIME];
	int CountCC;
	GD_Time GD[MAX_exTIME];
	int CountGD;
	WW_Time WW[MAX_exTIME];
	int CountWW;
	GD_Time RD[MAX_exTIME];
	int CountRD;
};
extern cEventTimer gEventTimer;