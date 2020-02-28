#pragma once


class cEventTimer
{
public:
	cEventTimer();

	bool Active;
	bool Show;

	void Load();
	void Draw();

	DWORD StartY;
	DWORD Width;
	DWORD High;	
	DWORD StartX;

	DWORD BCStart;
	DWORD DSStart;
	DWORD CCStart;
	DWORD GDStart;
	DWORD WWStart;
	DWORD RDStart;

	DWORD TimeLora;
	DWORD TimeDevias;
	DWORD TimeTvT;
	DWORD TimePandora;
	DWORD TimeEvengelion;
	DWORD TimeShop;
	DWORD TimeHappy;
	DWORD TimeDropEvent;

	DWORD m_dwTimeCryWolf;
	DWORD m_dwTimeCastleSiege;
	DWORD m_dwTimeDungeonSiege;
	DWORD m_dwTimeRedDragon;
};
extern cEventTimer gEventTimer;