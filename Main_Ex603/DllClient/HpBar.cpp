#include "stdafx.h"
#include "HpBar.h"
#include "User.h"
#include "Console.h"

cHpBar HpBar;

void cHpBar::Load()
{
	gInterface.LoadImages("Custom\\Interface\\HPBar.tga", 0x787F, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\HPLine.jpg", 0x7880, 0x2601, 0x2900, 1);
}

void cHpBar::Draw()
{
	if (this->MaxHP == 0 || this->isDraw == false) return;
	int pHP = (this->HP * 100) / this->MaxHP;
	if (pHP > 0)
	{
		//pDrawGUI(NEWUI_BAR_SWITCH01, (MAX_WIN_WIDTH / 2) - 80, 0, 160, 18);
		//pDrawColorButton(NEWUI_BAR_SWITCH02, (MAX_WIN_WIDTH / 2) - 75, 5, (150 * pHP) / 100, 8, 0, 0, (int)Color4f(255, 0, 0, 130));

		pDrawGUI(0x787F, (MAX_WIN_WIDTH / 2) - 105, 0, 210, 20);
		pDrawColorButton(0x7880, (MAX_WIN_WIDTH / 2) - 85, 6, (175 * pHP) / 100, 6, 0, 0, (int)Color4f(255, 0, 0, 130));


		char wiad[256];
		sprintf_s(wiad, "%d / %d", this->HP, this->MaxHP);
		int len = strlen(wiad);
		int Width = (MAX_WIN_WIDTH / 2)-len*2;
		gInterface.DrawFormatEx(eWhite, /*(MAX_WIN_WIDTH / 2 - len)*/ Width, 4 , 100, 1, "%d / %d",this->HP, this->MaxHP);
		//gInterface.DrawFormatEx(eWhite, /*(MAX_WIN_WIDTH / 2 - len)*/ Width, 4 , 100, 1, "%d / %d",this->HP, this->MaxHP);
		//MU_SetTextColorEx(255, 255, 255, 255);
		//MU_OutText(Width,4,(LPCTSTR)wiad);
	}
}

//void cHpBar::SetupMob(int Life, int MaxLife, short index)
//{
//	if (Life > MaxLife || 0 > Life)
//	{
//		this->isDraw = false; //something is wrong ^.^
//	}
//	this->HP = Life;
//	this->MaxHP = MaxLife;
//	this->aIndex = index;
//	this->isDraw = TRUE;
//}

void cHpBar::Recv(PMSG_ATTACKRESULT * Recv)
{
	this->aIndex = MAKE_NUMBERW(Recv->NumberH,Recv->NumberL);
	if(aIndex == pGameIndex)
	{
		return;
	}

	if (Recv->Life > Recv->MaxLife || 0 > Recv->Life)
	{
		this->isDraw = false; //something is wrong ^.^
	}
	this->HP = Recv->Life;
	this->MaxHP = Recv->MaxLife;
	this->aIndex = MAKE_NUMBERW(Recv->NumberH,Recv->NumberL);

#ifdef NEW_HP_BAR
	for(int n = 0; n < MAX_VIEWPORT;n++)
	{
		if(this->aIndex == gObjUser.ExViewe[n].aIndex)
		{
#ifdef exDEBUG_CODE
			//gConsole.Output(cGREEN,"SD: %d MaxSD: %d",Recv->SD,Recv->MaxSD);
#endif
			
			gObjUser.ExViewe[n].aIndex = this->aIndex;
			gObjUser.ExViewe[n].Life = this->HP;
			gObjUser.ExViewe[n].MaxLife = this->MaxHP;
			gObjUser.ExViewe[n].SD = Recv->SD;
			gObjUser.ExViewe[n].MaxSD = Recv->MaxSD;
			break;
		}
	}
#endif

	this->isDraw = TRUE;
}

void cHpBar::WorkHpBar(bool work)
{
	this->isDraw = work;
}

short cHpBar::RetIndex()
{
	return this->aIndex;
}