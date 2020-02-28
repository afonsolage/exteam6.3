#pragma once
#include "stdafx.h"
#include "Protocol.h"

#define AS_WINDOWS_WIDTH 100
#define AS_WINDOWS_HEIGHT 300



class cAchievementsSystem
{
public:
	cAchievementsSystem();

	bool Active;
	bool Show;

	int StartX;
	int StartY;


	DWORD ClickTime;

	void ImageLoad();

	void Draw();
	int Page;

private:

	
};
extern cAchievementsSystem gAchievementsSystem;