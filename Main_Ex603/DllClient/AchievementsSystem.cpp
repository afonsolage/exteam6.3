#include "AchievementsSystem.h"

#include "Controller.h"
#include "Interface.h"
#include "ExFunction.h"

cAchievementsSystem gAchievementsSystem;

cAchievementsSystem::cAchievementsSystem()
{
	this->Active = true;
	this->Show = false;

	this->StartX = 320;
	this->StartY = 30;
	this->Page	 = 1;
	
}


void cAchievementsSystem::ImageLoad()
{
	gInterface.LoadImages("Custom\\Interface\\achievement.tga", 100039, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\as_arrow_top.tga", 100040, 0x2601, 0x2900, 1);
}

void cAchievementsSystem::Draw()
{
	if( !this->Active ) return;

	if(!this->Show) return;

	//pSetCursorFocus = true;
	
	pDrawGUI(100039, StartX, StartY , 246, 367);
	gInterface.DrawFormatEx(eGold, StartX + 100, StartY + 30, 100, 1, "Genry Quest" );	


	//pDrawColorButton(0x7BAB, StartX+150, StartY+275, 20, 20, 0, 0, pMakeColor(106, 38, 31, 60));
	int PosY = StartY + 70;
	int Count = 12;
	float ScrollProcent = 0;
	for (int i = 0; i < Count; i++)
	{
		if (Count > 6)
		{

		}
		else
		{
		
			pDrawColorButton(0x0D43354, StartX+5, PosY, 220, 40, 0, 0, pMakeColor(20, 20, 20, 120));
			float High	= 10.5;
			float Whith = 7.5;
			float standartWhith = Whith / 96;
			float standartHight = High / 96;
			int v6 = (50 - 1) % 80;
			float CritX = (double)(v6 % 10) * Whith / 96;
			float CritY = (double)(v6 / 10) * High / 96;
			pDrawGUFULL(31725, StartX+8, PosY+5, 23, 30, CritX, CritY, standartWhith, standartHight, 1, 1, 0.0);


			PosY = PosY + 45;
		}
	}
	pDrawGUI(100040,  320+ 238 -8, StartY + 70 , 10, 10);
	if (Count <= 6)
	{
		pDrawColorButton(0x0D43354, 320+ 238 -8, StartY + 80, 10, 250, 0, 0, pMakeColor(120, 20, 20, 120));
	}
	else
	{
		//skolko 6 ot  % Count
		pDrawColorButton(0x0D43354, 320+ 238 -8, StartY + 80, 10, 250, 0, 0, pMakeColor(120, 20, 20, 120));
	}	
	pDrawGUI(100040,  320+ 238 -8, 367 - 20 , 10, 10);
	

	/*int TitleX = StartX + 10 + 20;
	int TitleY = StartY + 50;

	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "(N)");

	TitleX += 20;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Name");

	TitleX += 80;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Class");

	TitleX += 70;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Level");

	TitleX += 30;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Reset");

	TitleX += 30;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Grand");

	TitleX += 30;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Strength");

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Agility");

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Vitality");

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Energy");

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Command");

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Guild");

	pDrawGUI(0x7B67, StartX + 10 + 20, TitleY+10 , 150, 2);
	pDrawGUI(0x7B67, StartX + 10 + 20+150, TitleY+10 , 150, 2);
	pDrawGUI(0x7B67, StartX + 10 + 20+150+150, TitleY+10 , 150, 2);
	pDrawGUI(0x7B67, StartX + 10 + 20+150+150+90, TitleY+10 , 150, 2);
	
	int InfoY = StartY + 50+15;

	int c = 0;

	DWORD Delay = (GetTickCount() - this->ClickTime);

	int ButX = 180;
	int ButY = 98;

	pDrawGUI(0x7BAA, StartX+60+ButX, StartY+275+ButY , 20, 20);

	if(CursorZoneButton(StartX+60+ButX, StartY+275+ButY, StartX+60+20+ButX, StartY+275+20+ButY))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
		}
		pDrawColorButton(0x7BAA, StartX+60+ButX, StartY+275+ButY, 20, 20, 0, 0, pMakeColor(255, 204, 20, 130));
	}



	pDrawGUI(0x7BAB, StartX+150+ButX, StartY+275+ButY , 20, 20);

	if(CursorZoneButton(StartX+150+ButX, StartY+275+ButY, StartX+150+20+ButX, StartY+275+20+ButY))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
		}
		pDrawColorButton(0x7BAB, StartX+150+ButX, StartY+275+ButY, 20, 20, 0, 0, pMakeColor(255, 204, 20, 130));
	}*/
}