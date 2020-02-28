#include "stdafx.h"
#include "Lottery.h"
#include "Interface.h"
#include "DeBug.h"
#include "Console.h"

#if(CUSTOM_LOTTERY)

CLottery g_Lottery;

CLottery::CLottery()
{
	this->Init();
}

CLottery::~CLottery()
{
}

void CLottery::Init()
{
	this->m_RandomNumber = -1;
	this->m_SelectNumber = 4;
}

void CLottery::Load()
{
	this->Init();
}

void CLottery::LoadIMG()
{
	pLoadImage("ExData\\Interface\\Lottery\\Converted\\vq1.tga", ex_LOTTERY_SPIN, 0x2601, 0x2900, 1, 0);
	pLoadImage("ExData\\Interface\\Lottery\\close.tga", ex_LOTTERY_CLOSE, 0x2601, 0x2900, 1, 0);
}

void CLottery::BindIMG()
{
	gInterface.BindObject(eLOTTERY_SPIN, ex_LOTTERY_SPIN, 640, 440, -1, -1);
	gInterface.BindObject(eLOTTERY_CLOSE, ex_LOTTERY_CLOSE, 14, 16, -1, -1);

	// ----
	return;
	gInterface.BindObject(eLOTTERY_MAIN, 0x7A5A, 222, 366, -1, -1);
	gInterface.BindObject(eLOTTERY_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eLOTTERY_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eLOTTERY_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eLOTTERY_PLAY, 0x7A5E, 108, 29, -1, -1);
	gInterface.BindObject(eLOTTERY_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eLOTTERY_MONEYBG, 0x7A89, 170, 26, -1, -1);
	gInterface.BindObject(eLOTTERY_INFOBG1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eLOTTERY_LINE1, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eLOTTERY_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eLOTTERY_POINT, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eLOTTERY_PAGEUP, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eLOTTERY_PAGEDN, 0x7C0D, 15, 15, -1, -1);
	gInterface.BindObject(eLOTTERY_DIV, 0x7A62, 223, 21, -1, -1);
}

void CLottery::DrawMain()
{
	//return;
	//glColor3f(1.0, 1.0, 1.0);
	//pGLSwitch();
	pSetBlend(true);
	pGLSwitchBlend();

	gInterface.DrawGUI(eLOTTERY_SPIN, 0, 0);
	
	pSetBlend(false);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	return;


	/*
	this->DrawMain2();

	return;
	*/

	//if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinLottery))
	//{
	//	return;
	//}

	//pSetCursorFocus = true;

	float MainWidth = 230.0;
	float StartY = 0;
	float StartX = 0;//(MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentX = StartX;
	float ContentY = StartY;

	//gInterface.DrawWindow(eLOTTERY_MAIN, eLOTTERY_TITLE, eLOTTERY_FRAME, eLOTTERY_FOOTER, 11, StartX, StartY, "Lottery");

	gInterface.DrawGUI(eLOTTERY_SPIN, StartX, StartY);
	//pDrawColorButton(eLOTTERY_SPIN, StartX, StartY, 640, 440, 0, 0, pMakeColor(0, 0, 0, 0));
	//gInterface.DrawGUI(eLOTTERY_CLOSE, StartX, StartY);

	//gInterface.DrawColoredGUI(eLOTTERY_SPIN, gInterface.Data[eLOTTERY_SPIN].X, gInterface.Data[eLOTTERY_SPIN].Y, Color4f(50, 50, 50, 100));

	pSetBlend(false);
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
}

void CLottery::DrawMain2()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinLottery))
	{
		return;
	}

	pSetCursorFocus = true;

	float StartY = 50;

	float StartX = (MAX_WIN_WIDTH / 2) - (230.0 / 2);

	gInterface.DrawWindow(eLOTTERY_MAIN, eLOTTERY_TITLE, eLOTTERY_FRAME, eLOTTERY_FOOTER, 17, StartX, StartY, "Lottery");

	gInterface.DrawGUI(eLOTTERY_CLOSE, StartX + 195, StartY);

	if(gInterface.IsWorkZone(eLOTTERY_CLOSE))
	{
		DWORD Color = eGray100;
		if(gInterface.Data[eLOTTERY_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eLOTTERY_CLOSE, gInterface.Data[eLOTTERY_CLOSE].X, gInterface.Data[eLOTTERY_CLOSE].Y, Color);
	}

	//StartY += 35;
	//gInterface.DrawFormat(eWhite, StartX + 65, StartY, 100, 3, "Lotery Spin Luck");

	StartY += 35;
	gInterface.DrawGUI(eLOTTERY_INFOBG1, StartX + 30, StartY);

	StartY += 5;
	gInterface.DrawFormat(eWhite, StartX + 40, StartY, 100, 1, "Random number:", this->m_RandomNumber + 1);

	if(this->m_RandomNumber > 0 && this->m_RandomNumber < MAX_LOTERRY_NUM) 
	{
		gInterface.DrawFormat(eAncient, StartX + 100, StartY, 100, 3, "<< %d >>", this->m_RandomNumber + 1);
	}
	else
	{
		gInterface.DrawFormat(eGold, StartX + 100, StartY, 100, 3, "<< NUM >>");
	}

	StartY += 20;
	gInterface.DrawGUI(eLOTTERY_INFOBG1, StartX + 30, StartY);

	StartY += 5;
	gInterface.DrawFormat(eWhite, StartX + 40, StartY, 100, 1, "Price:", this->m_RandomNumber + 1);
	gInterface.DrawFormat(eGold, StartX + 100, StartY, 100, 3, "%d WCoin", 500);

	StartY += 10;
	gInterface.DrawGUI(eLOTTERY_DIV, StartX, StartY);

	int iTempNum = 0;
	float flTempX = 0;
	float flTempY = 0;

	StartY += 5;
	for(int i = 0; i < MAX_LOTERRY_NUM; i++)
	{
		DWORD Color = eExcellent;

		StartY += 15;

		gInterface.DrawGUI(eLOTTERY_POINT1, StartX + 30, StartY);

		if(this->m_RandomNumber == i)
		{
			Color = eRed;
		}

		gInterface.DrawFormat(Color, StartX + 55, StartY, 100, 1, this->GetRewardText(i));

		gInterface.DrawGUI(eLOTTERY_LINE1, StartX + 55, StartY + 10);

		if(/*gInterface.IsWorkZone(StartX, StartY, StartX + 150, StartY + 10) && */i == eLOTTERY_ITEM)
		{
			//this->DrawItem(this->m_Data[i].Type, this->m_Data[i].Index, this->m_Data[i].Level);
			//iTempNum = i;
			//flTempX = StartX;
			//flTempY = StartY;


		}
	}

	if(flTempX > 0 && flTempY > 0)
	{
		//this->DrawItem(this->m_Data[iTempNum].Type, this->m_Data[iTempNum].Index, this->m_Data[iTempNum].Level);
	}

	StartY += 10;
	gInterface.DrawGUI(eLOTTERY_DIV, StartX, StartY);

	StartY += 20;
	gInterface.DrawGUI(eLOTTERY_MONEYBG, StartX + 30, StartY);

	StartY += 10;
	gInterface.DrawFormat(eYellow, StartX + 80, StartY - 1, 100, 1, "Prize - %d WCoin", 500000);

	StartY += 10; 
	gInterface.DrawGUI(eLOTTERY_DIV, StartX, StartY);

	StartY += 20; 
	gInterface.PartUPandDN(eLOTTERY_POINT, eLOTTERY_PAGEUP, eLOTTERY_PAGEDN, NULL, StartX, StartY, eWhite, this->m_SelectNumber+1, "Lottery Number");

	StartY += 10; 
	gInterface.DrawGUI(eLOTTERY_DIV, StartX, StartY);

	StartY += 15;
	gInterface.DrawButtonBig(eLOTTERY_PLAY, true, StartX + 60, StartY, "Play");
}

void CLottery::Button(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinLottery))
	{
		return;
	}

	if(gInterface.Button(Event, ObjWindowsEx::exWinLottery, eLOTTERY_PLAY, 0))
	{
		this->CGLotteryPlay();
	}
	else if(gInterface.Button(Event, ObjWindowsEx::exWinLottery, eLOTTERY_CLOSE, 0))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinLottery);
		this->ClearDraw();
	}
	else if(gInterface.Button(Event, ObjWindowsEx::exWinLottery, eLOTTERY_PAGEUP, 0))
	{
		if(this->m_SelectNumber < MAX_LOTERRY_NUM - 1)
		{
			this->m_SelectNumber++;
		}
	}
	else if(gInterface.Button(Event, ObjWindowsEx::exWinLottery, eLOTTERY_PAGEDN, 0))
	{
		if(this->m_SelectNumber > 0)
		{
			this->m_SelectNumber--;
		}
	}
}

char* CLottery::GetRewardText(int Number)
{
	static char szResult[128] = { 0 };

	switch(this->m_Data[Number].Type)
	{
	case eLOTTERY_FUND_MAIN:
		sprintf(szResult, "%d - FOUND = %d", Number+1, this->m_Data[Number].Value); 
		break;
	case eLOTTERY_ZEN:
		sprintf(szResult, "%d - ZEN = %d", Number+1, this->m_Data[Number].Value); 
		break;
	case eLOTTERY_WCOINC:
		sprintf(szResult, "%d - WCOIN(C) = %d", Number+1, this->m_Data[Number].Value); 
		break;
	case eLOTTERY_WCOINP:
		sprintf(szResult, "%d - WCOIN(P) = %d", Number+1, this->m_Data[Number].Value); 
		break;
	case eLOTTERY_GOBLIN:
		sprintf(szResult, "%d - GOBLIN POINT = %d", Number+1, this->m_Data[Number].Value); 
		break;
	case eLOTTERY_CREDIT:
		sprintf(szResult, "%d - CREDIT = %d", Number+1, this->m_Data[Number].Value); 
		break;
	case eLOTTERY_ITEM:
		sprintf(szResult, "%d - ITEM = %d", Number+1, this->m_Data[Number].Value); 
		break;
	case eLOTTERY_FOND_PERCENT:
		sprintf(szResult, "%d - FOND PERCENT = %d", Number+1, this->m_Data[Number].Value); 
		break;
	}
	
	return szResult;
}

void CLottery::DrawItem(int Type, int Index, int Level)
{
	float MainWidth	 = 230.0;
	float ContentX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentY = 100.0;

	//ContentX += MainWidth;
	//gInterface.DrawWindow(eSMITHY_ITEM_MAIN, eSMITHY_ITEM_TITLE, eSMITHY_ITEM_FRAME, eSMITHY_ITEM_FOOTER, 0, ContentX, ContentY, "Item");

	ContentX += MainWidth;
	gInterface.DrawGUI(eSMITHY_ITEM_BG, ContentX, ContentY);

	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(ITEM(Type, Index));

	const int WidthValue = 12;	//24
	const int HeightValue = 13;	//26
	float barWidth = WidthValue * ItemInfo->ItemWidth;
	float barHeight = HeightValue * ItemInfo->ItemHeight;

	float flDrawItemX;// = ContentX - (WidthValue * (float)(ItemInfo->ItemWidth / 2.0f) + 10) + 80;
	float flDrawItemY;// = ContentY + 20;

	flDrawItemX = ContentX + ( 152 / 2 ) - ( WidthValue * ItemInfo->ItemWidth / 2 );
	flDrawItemY = ContentY + ( 124 / 2 ) - ( HeightValue * ItemInfo->ItemHeight / 2 );

	gInterface.DrawItem(
		flDrawItemX,
		flDrawItemY,
		barWidth,
		barHeight,
		ITEMGET(Type,Index),
		SET_ITEMOPT_LEVEL(Level),
		1,0,0);

}

void CLottery::ClearDraw()
{
	this->Init();
}

void CLottery::CGLotteryOpen(int aIndex)
{

	//this->GCLotteryData(aIndex);


}

void CLottery::GCLotteryData(PMSG_LOTTERY_DATA* lpMsg)
{
	memcpy(&this->m_Data, &lpMsg->Data, sizeof(this->m_Data));

	gInterface.OpenWindowEx(ObjWindowsEx::exWinLottery);
}

void CLottery::CGLotteryPlay()
{
	PMSG_LOTTERY_PLAY pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xD1, sizeof(pMsg));
	pMsg.Result = this->m_SelectNumber;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CLottery::GCLotteryResult(PMSG_LOTTERY_RESULT* lpMsg)
{
	this->m_RandomNumber = lpMsg->Result;
}


#endif