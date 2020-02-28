#include "stdafx.h"
#include "AutoParty.h"
#include "Interface.h"
#include "Protocol.h"
#include "ExFunction.h"
#include "Controller.h"
#include "NewParty.h"
#include "Configs.h"
#include "ExText.h"

#ifdef AUTO_PARTY

cAutoParty gAutoParty;

cAutoParty::cAutoParty()
{
	this->Active = true;
	this->Show = false;
	this->ClickTime = 0;
	this->Page = 1;
}

cAutoParty::~cAutoParty()
{

}

void cAutoParty::Work()
{
	if( !this->Active ) return;


	if( !this->Show )
	{
		return;
	}

	DWORD Delay = (GetTickCount() - this->ClickTime);

	pSetCursorFocus = true;

	// ----
	float MainWidth		= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----

	pDrawGUI(0x7A5A, StartX, StartY + 2, 222, 303);

	pDrawGUI(0x7A63, StartX, StartY, 230, 67);

	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, g_ExText.GetText(23));

	int BordY = StartY;

	for( int i = 0; i < 13; i++ )
	{
		pDrawGUI(0x7A58, StartX, BordY + 67.0,
			230, 15);
		// ----
		BordY += 15;
	}

	pDrawGUI(0x7A59, StartX, StartY + 230+30, 230, 50);


	pDrawGUI(0x7EC5, StartX + MainWidth - 36, 67 + 29 + 2, 36, 29);	//Close

	if(CursorZoneButton(StartX + MainWidth - 36, 67 + 29 + 2, StartX + MainWidth - 36+36, 67 + 29 + 2+29))
	{
		gInterface.DrawToolTip(StartX + MainWidth - 36-10, 67 + 29 + 2+20, g_ExText.GetText(24));
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
			this->Show = false;
		}
		pDrawColorButton(0x7EC5, StartX + MainWidth - 36, 67 + 29 + 2, 36, 29, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	pDrawGUI(0x7A59, StartX, StartY + 230+30, 230, 50);

	pDrawGUI(0x7A62, StartX, StartY+80, 230, 20);

	pDrawGUI(0x7A62, StartX, StartY+250, 230, 20);

	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, g_ExText.GetText(23));


	int TitleText = gInterface.DrawFormat(eWhite, StartX + 10, 150, 210, 3, g_ExText.GetText(25));
	TitleText += gInterface.DrawFormat(eWhite, StartX + 10, TitleText, 210, 3, g_ExText.GetText(26));
	

	//-> List Draw

	int ListDrawY = StartY+10;

	gInterface.DrawFormat(eGold, StartX+12, ListDrawY + 100, 100, 1, g_ExText.GetText(27));

	gInterface.DrawFormat(eGold, StartX+20+2, ListDrawY + 100, 100, 1, g_ExText.GetText(28));

	gInterface.DrawFormat(eGold, StartX+95, ListDrawY + 100, 100, 1, g_ExText.GetText(29));

	gInterface.DrawFormat(eGold, StartX+115, ListDrawY + 100, 100, 1, g_ExText.GetText(30));

	gInterface.DrawFormat(eGold, StartX+170, ListDrawY + 100, 100, 1, g_ExText.GetText(31));

	gInterface.DrawFormat(eGold, StartX+185, ListDrawY + 100, 100, 1, g_ExText.GetText(32));

	gInterface.DrawFormat(eGold, StartX+200, ListDrawY + 100, 100, 1, g_ExText.GetText(33));

	pDrawGUI(0x7B67, StartX+10, ListDrawY+100+10 , 150, 2);
	pDrawGUI(0x7B67, StartX+65, ListDrawY+100+10 , 150, 2);

	 ListDrawY += 13;

	// =============

	for(int a = 0; a<10; a++)
	{
		int up = a + ( ( this->Page - 1 ) * 10 );

		if(this->Party[up].Name[0] == NULL) break;

		gInterface.DrawFormat(eWhite, StartX+12, ListDrawY + 100+1, 100, 1, "%d",up+1);

		gInterface.DrawFormat(eWhite, StartX+20+2, ListDrawY + 100+1, 100, 1, "%s",this->Party[up].Name);

		gInterface.DrawFormat(eWhite, StartX+95, ListDrawY + 100+1, 100, 1, "%d",this->Party[up].Level);

		gInterface.DrawFormat(eWhite, StartX+115, ListDrawY + 100+1, 100, 1, "%s",pGetMapName(this->Party[up].Map));

		gInterface.DrawFormat(eWhite, StartX+170, ListDrawY + 100+1, 100, 1, "%d",this->Party[up].X);

		gInterface.DrawFormat(eWhite, StartX+185, ListDrawY + 100+1, 100, 1, "%d",this->Party[up].Y);
#if _NEW_PARTY_SYSTEM_ == TRUE
			gInterface.DrawFormat(eWhite, StartX+200+3, ListDrawY + 100+1, 100, 1, "%d",this->Party[up].Total);
#else
		gInterface.DrawFormat(eWhite, StartX+200, ListDrawY + 100+1, 100, 1, "%d / 5",this->Party[up].Total);
#endif
		
		pDrawGUI(0x7B67, StartX+10, ListDrawY+100+10 , 150, 2);
		pDrawGUI(0x7B67, StartX+65, ListDrawY+100+10 , 150, 2);

		ListDrawY += 12;
	}

	//00000000000000000

	pDrawGUI(0x7BAA, StartX+60, StartY+275 , 20, 20);

	if(CursorZoneButton(StartX+60, StartY+275, StartX+60+20, StartY+275+20))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
			if(this->Page != 1) this->Page--;
		}
		pDrawColorButton(0x7BAA, StartX+60, StartY+275, 20, 20, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	gInterface.DrawFormat(eGold, StartX+100, StartY+277, 100, 1, g_ExText.GetText(34), this->Page,10);


	pDrawGUI(0x7BAB, StartX+150, StartY+275 , 20, 20);

	if(CursorZoneButton(StartX+150, StartY+275, StartX+150+20, StartY+275+20))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
			if(this->Page != 10) this->Page++;
		}
		pDrawColorButton(0x7BAB, StartX+150, StartY+275, 20, 20, 0, 0, pMakeColor(255, 204, 20, 130));
	}
}

void cAutoParty::Protocol(DWORD Case, LPBYTE Data, int Len, int aIndex)
{
	if( !this->Active ) return;

	BYTE ProtocolType = Data[0];

	if( ProtocolType == 0xC2 )
	{
		PWMSG_HEAD2 * lpDef = (PWMSG_HEAD2 *)Data;

		switch(BYTE(Case))
		{
		case 0xFA:
			{
				PWMSG_HEAD2 * lpDef = (PWMSG_HEAD2 *)Data;
				switch(lpDef->subcode)
				{
				case 0x05:
					{
						GCPartyList * Recv = (GCPartyList*)Data;

						for(int i=0;i<100;i++)
						{
							strncpy(this->Party[i].Name,Recv->Name[i],10);
							this->Party[i].Level = Recv->Level[i];
							this->Party[i].Map = Recv->Map[i];
							this->Party[i].X = Recv->X[i];
							this->Party[i].Y = Recv->Y[i];
							this->Party[i].Total = Recv->Total[i];
							if(this->Party[i].Total == 0) this->Party[i].Total = 1;
						}

						this->Show = !this->Show;
					}
					break;
				}
			}
		}
	}
}

#endif