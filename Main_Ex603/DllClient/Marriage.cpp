#include "stdafx.h"
#include "Marriage.h"
#include "Interface.h"
#include "Console.h"

#if(CUSTOM_MARRIAGE)

CMarriage g_Marriage;

CMarriage::CMarriage()
{
	this->Init();
}

CMarriage::~CMarriage()
{
}

void CMarriage::Init()
{
	this->Result = false;
	this->bUser1 = false;
	this->bUser2 = false;
	this->iCountHeart1 = 0;
	this->iCountHeart2 = 0;
	this->iNeedHeart1 = 0;
	this->iNeedHeart2 = 0;
	this->bDrawOK = true;
}

void CMarriage::Load()
{
	this->Init();

}

void CMarriage::LoadImages()
{
	pLoadImage("Custom\\Interface\\Marriage.tga", MaiObjID::ex_MARRIAGE, 0x2601, 0x2900, 1, 0);
}

void CMarriage::BindImages()
{
	gInterface.BindObject(eMARRIAGE_MAIN, 0x7A5A, 222, 240, -1, -1);
	gInterface.BindObject(eMARRIAGE_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eMARRIAGE_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eMARRIAGE_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eMARRIAGE_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eMARRIAGE_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eMARRIAGE_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eMARRIAGE_IMG, MaiObjID::ex_MARRIAGE, 200, 50, -1, -1);
}

void CMarriage::Draw()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMarriage))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color				= eGray100;
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentX			= StartX;
	float ContentY          = StartY;

	gInterface.DrawGUI(eMARRIAGE_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eMARRIAGE_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eMARRIAGE_FRAME, StartX, StartY + 67.0, 9);
	gInterface.DrawGUI(eMARRIAGE_FOOTER, StartX, StartY);
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Marriage");

	gInterface.DrawGUI(eMARRIAGE_IMG, StartX+13, 150);

	// ----

	gInterface.DrawFormat(eYellow, ContentX + 10, ContentY + 110, 100, 3, "Husband");
	gInterface.DrawFormat(eYellow, ContentX + 110, ContentY + 110, 100, 3, "Wife");

	if(this->bUser1)
	{
		gInterface.DrawFormat(eWhite, ContentX + 10, ContentY + 120, 100, 3, "%s", this->szName1);
		//gConsole.Output(cGREY, "%d | %s", this->bUser1, this->szName1);
	}
	else
	{
		gInterface.DrawFormat(eWhite, ContentX + 10, ContentY + 120, 100, 3, "- / -");
	}

	if(this->bUser2)
	{
		gInterface.DrawFormat(eWhite, ContentX + 110, ContentY + 120, 100, 3, "%s", this->szName2);
	}
	else
	{
		gInterface.DrawFormat(eWhite, ContentX + 110, ContentY + 120, 100, 3, "- / -");
	}

	gInterface.DrawFormat(eYellow, ContentX + 60, ContentY + 140, 100, 3, "Need:");
	//maket
	gInterface.DrawFormat(eYellow, ContentX + 10, ContentY + 150, 100, 3, "Heart:");
	gInterface.DrawFormat(eYellow, ContentX + 110, ContentY + 150, 100, 3, "Heart:");

	gInterface.DrawFormat(eWhite, ContentX + 10, ContentY + 160, 100, 3, "%d / %d", this->iCountHeart1, this->iNeedHeart1);
	gInterface.DrawFormat(eWhite, ContentX + 110, ContentY + 160, 100, 3, "%d / %d", this->iCountHeart2, this->iNeedHeart2);
	// ----
	if(this->bDrawOK)
	{
		gInterface.DrawGUI(eMARRIAGE_OK, StartX+30, StartY - 5);
		gInterface.DrawFormat(eWhite, StartX + 35, StartY+5, 50, 3, "Ok");

		if(!this->Result)
		{
			gInterface.Data[eMARRIAGE_OK].Attribute = false;
			gInterface.DrawColoredGUI(eMARRIAGE_OK, gInterface.Data[eMARRIAGE_OK].X, gInterface.Data[eMARRIAGE_OK].Y, eGray150);
		}
		else
		{
			gInterface.Data[eMARRIAGE_OK].Attribute = true;
			if( gInterface.IsWorkZone(eMARRIAGE_OK) )
			{
				Color = eGray100;
				if( gInterface.Data[eMARRIAGE_OK].OnClick )
				{
					Color = eGray150;
				}
				gInterface.DrawColoredGUI(eMARRIAGE_OK, gInterface.Data[eMARRIAGE_OK].X, gInterface.Data[eMARRIAGE_OK].Y, Color);
			}
		}
	}
	// ---- 
	gInterface.DrawGUI(eMARRIAGE_CLOSE, StartX + 70 + 62, StartY - 5 );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5, 50, 3, "Cancel");
	if(gInterface.IsWorkZone(eMARRIAGE_CLOSE))
	{
		Color = eGray100;
		if(gInterface.Data[eMARRIAGE_CLOSE].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eMARRIAGE_CLOSE, gInterface.Data[eMARRIAGE_CLOSE].X, gInterface.Data[eMARRIAGE_CLOSE].Y, Color);
	}
}

void CMarriage::Button(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMarriage))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, eMARRIAGE_CLOSE, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinMarriage);	//need packet for gs
		PMSG_CG_MARRIAGE_CLOSE pRequest = { 0 };
		pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x3E, sizeof(pRequest));
		pRequest.bResultClose = 1;
		gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
	}
	if(this->bDrawOK)
	{
		if(gInterface.ButtonEx(Event, eMARRIAGE_OK, true))
		{
			//need packet for gs
			PMSG_CG_MARRIAGE_CLOSE pRequest = { 0 };
			pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x3F, sizeof(pRequest));
			pRequest.bResultClose = 1;
			gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
			this->bDrawOK = false;
		}
	}
}

void CMarriage::GCInfoNames(PMSG_GC_MARRIAGE_NAMES* aRecv)
{
	this->bDrawOK = true;
	this->Result = aRecv->bResult;

	this->bUser1 = aRecv->bUser1;
	this->bUser2 = aRecv->bUser2;

	this->szName1[10] = 0;
	memcpy(this->szName1, aRecv->szName1, sizeof(this->szName1)-1);

	this->szName2[10] = 0;
	memcpy(this->szName2, aRecv->szName2, sizeof(this->szName2)-1);

	this->iCountHeart1 = aRecv->iCountHeart1;
	this->iCountHeart2 = aRecv->iCountHeart2;
	this->iNeedHeart1 = aRecv->iNeedHeart1;
	this->iNeedHeart2 = aRecv->iNeedHeart2;

	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinMarriage))
	{
		gInterface.OpenWindowEx(ObjWindowsEx::exWinMarriage);
	}
}


void CMarriage::GCWindowClose()
{
	gInterface.CloseWindowEx(ObjWindowsEx::exWinMarriage);
}
#endif