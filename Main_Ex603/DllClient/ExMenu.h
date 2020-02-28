#pragma once
#include "stdafx.h"

class ExMenu
{
public:
	ExMenu();

	float DrawX;
	float DrawY;

	void Load();
	void MoveX();
	void Draw();

	int countX;
	int statX;
	bool bPlusX;
	int iStatus;
	int mWidth;
	int mHigh;
	int bWidth;
	int bHigh;	
	int StartX;
	int StartY;
	int MenuWidth;
	int MoveStartX;
	DWORD ClickTime;
};
extern ExMenu gExMenu;