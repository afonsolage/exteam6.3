#include "stdafx.h"
#include "PKClear.h"
#include "Import.h"
#include "Protocol.h"
#include "Interface.h" 
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PKCLEAR_NPC==TRUE)

PKClear g_PKClear;
// ----------------------------------------------------------------------------------------------

void PKClear::Init()
{
	this->Result = 0;
	this->PKLevel = 0;
	this->Zen = 0;
	this->JewelOfChaos = 0;
	this->JewelOfBless = 0;
	this->JewelOfChaos = 0;
}
// ----------------------------------------------------------------------------------------------

void PKClear::Load()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

void PKClear::BindImages()
{
	gInterface.BindObject(ePKCLEAR_MAIN, 0x7A5A, 222, 140, -1, -1);
	gInterface.BindObject(ePKCLEAR_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(ePKCLEAR_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(ePKCLEAR_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(ePKCLEAR_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePKCLEAR_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(ePKCLEAR_CLOSE, 0x7A5F, 62, 27, -1, -1);
}
// ----------------------------------------------------------------------------------------------

void PKClear::GC_Price(GC_PKCLEAR_PRICE* aRecv)
{
	this->Result = aRecv->Result;
	this->PKLevel = aRecv->PkLevel;
	this->Zen = aRecv->Zen;
	this->JewelOfChaos = aRecv->Chaos;
	this->JewelOfBless = aRecv->Bless;
	this->JewelOfSoul = aRecv->Soul;

	gInterface.OpenWindowEx(exWinPKClear);
}
// ----------------------------------------------------------------------------------------------

void PKClear::CG_Result()
{
	CG_PKCLEAR_RESULT pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0xAF, sizeof(pRequest));
	pRequest.Result = 1;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

void PKClear::Draw()
{
	if(!gInterface.CheckWindowEx(exWinPKClear))
	{
		return;
	}

	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

	float ContentY			= StartY;
	// ----
	gInterface.DrawGUI(ePKCLEAR_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(ePKCLEAR_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ePKCLEAR_FRAME, StartX, StartY + 67.0, 2);
	gInterface.DrawGUI(ePKCLEAR_FOOTER, StartX, StartY);
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "PK Clear");
	// ---- 
	if(this->PKLevel <= 3)
	{
		gInterface.DrawFormat(eWhite, StartX + 10, ContentY + 60, 210, 3, "You do not need PK Clear");
	}
	else
	{
		ContentY += 5;

		gInterface.DrawFormat(eWhite, StartX + 10, ContentY + 30, 210, 3, "You are advised to wash the PK status %d Kill !", (this->PKLevel - 3));
		ContentY += 10;

		if(this->Zen > 0)
		{
			char MoneyBuff[50];
			pGetMoneyFormat((double)this->Zen, MoneyBuff, 0);
			gInterface.DrawFormat(eYellow, StartX + 10, ContentY + 30, 210, 3, "%s Zen",MoneyBuff);
			ContentY += 10;
		}
		
		if(this->JewelOfChaos > 0)
		{
			gInterface.DrawFormat(eYellow, StartX + 10, ContentY + 30, 210, 3, "Jewel Of Chaos x %d", this->JewelOfChaos);
			ContentY += 10;
		}

		if(this->JewelOfBless > 0)
		{
			gInterface.DrawFormat(eYellow, StartX + 10, ContentY + 30, 210, 3, "Jewel Of Bless x %d", this->JewelOfBless);
			ContentY += 10;
		}

		if(this->JewelOfSoul > 0)
		{
			gInterface.DrawFormat(eYellow, StartX + 10, ContentY + 30, 210, 3, "Jewel Of Soul x %d", this->JewelOfSoul);
			ContentY += 10;
		}
	}
	// ---- 
	gInterface.DrawGUI(ePKCLEAR_OK, StartX+30, StartY - 5);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5, 50, 3, "Ok");

	if(!this->Result)
	{
		gInterface.Data[ePKCLEAR_OK].Attribute = false;
		gInterface.DrawColoredGUI(ePKCLEAR_OK, gInterface.Data[ePKCLEAR_OK].X, gInterface.Data[ePKCLEAR_OK].Y, eGray150);
	}
	else
	{
		gInterface.Data[ePKCLEAR_OK].Attribute = true;
		if( gInterface.IsWorkZone(ePKCLEAR_OK) )
		{
			DWORD Color = eGray100;
			// ----
			if( gInterface.Data[ePKCLEAR_OK].OnClick )
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(ePKCLEAR_OK, gInterface.Data[ePKCLEAR_OK].X, gInterface.Data[ePKCLEAR_OK].Y, Color);
		}
	}

	// ---- 
	gInterface.DrawGUI(ePKCLEAR_CLOSE, StartX + 70 + 62, StartY - 5 );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5, 50, 3, "Cancel");

	if( gInterface.IsWorkZone(ePKCLEAR_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePKCLEAR_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePKCLEAR_CLOSE, gInterface.Data[ePKCLEAR_CLOSE].X, gInterface.Data[ePKCLEAR_CLOSE].Y, Color);
	}
}
// ----------------------------------------------------------------------------------------------

void PKClear::EventButton(DWORD Event)
{
	if(!gInterface.CheckWindowEx(exWinPKClear))
	{
		return;
	}

	if( gInterface.ButtonEx(Event, ePKCLEAR_OK, true ) )
	{
		gInterface.CloseWindowEx(exWinPKClear);
		this->CG_Result();
		return;
	}

	if( gInterface.ButtonEx(Event, ePKCLEAR_CLOSE, false ) )
	{
		gInterface.CloseWindowEx(exWinPKClear);
		return;
	}
}
// ----------------------------------------------------------------------------------------------

#endif