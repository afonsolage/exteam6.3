#include "stdafx.h"
#include "Ranking.h"
#include "Import.h"
#include "Interface.h"
#include "ExFunction.h"
#include "Controller.h"
#include "ExLicense.h"
#include "ExText.h"

cRanking gRanking;

cRanking::cRanking()
{
	this->Active = false;
	this->Show = false;

	this->StartX = 20;
	this->StartY = 20;

	this->Page = 1;

	ZeroMemory(&RankingChar,sizeof(RankingChar));
	
}

cRanking::~cRanking()
{

}

void cRanking::ImageLoad()
{
	gInterface.LoadImages("Custom\\Interface\\top.tga", 100037, 0x2601, 0x2900, 1);

}

void cRanking::RecvGS(DWORD Case, LPBYTE Data, int Len, int aIndex)
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
				case 0x06:
					{
						DGCharTop * Recv = (DGCharTop*)Data;

						ZeroMemory(&RankingChar,sizeof(RankingChar));

						for(int i=0;i<MAXTOP;i++)
						{
							strncpy(this->RankingChar[i].Name,Recv->tp[i].Name,10);

							this->RankingChar[i].Class = Recv->tp[i].Class;
							this->RankingChar[i].level = Recv->tp[i].level;
							this->RankingChar[i].Reset = Recv->tp[i].Reset;
							this->RankingChar[i].Grand = Recv->tp[i].Grand;
							this->RankingChar[i].Str = Recv->tp[i].Str;
							this->RankingChar[i].Agi = Recv->tp[i].Agi;
							this->RankingChar[i].Vit = Recv->tp[i].Vit;
							this->RankingChar[i].Ene = Recv->tp[i].Ene;
							this->RankingChar[i].Cmd = Recv->tp[i].Cmd;
							this->RankingChar[i].Premium = Recv->tp[i].Premium;

							strncpy(this->RankingChar[i].Guild,Recv->tp[i].Guild,8);
						}
					}
					break;
				}
			}
		}
	}
}

void cRanking::Draw()
{
	if( !this->Active ) return;

	if(!this->Show) return;

	pSetCursorFocus = true;

	pDrawGUI(100037, StartX, StartY , 640, 480);

	int TitleX = StartX + 10 + 20;
	int TitleY = StartY + 50;

	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(48));

	TitleX += 20;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(49));

	TitleX += 80;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(50));

	TitleX += 70;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(51));

	TitleX += 30;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(52));

	TitleX += 30;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(53));

	TitleX += 30;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(54));

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(55));

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(56));

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(57));

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(58));

	TitleX += 45;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, g_ExText.GetText(59));

	pDrawGUI(0x7B67, StartX + 10 + 20, TitleY+10 , 150, 2);
	pDrawGUI(0x7B67, StartX + 10 + 20+150, TitleY+10 , 150, 2);
	pDrawGUI(0x7B67, StartX + 10 + 20+150+150, TitleY+10 , 150, 2);
	pDrawGUI(0x7B67, StartX + 10 + 20+150+150+90, TitleY+10 , 150, 2);
	
	int InfoY = StartY + 50+15;

	int c = 0;

	for(int i = 0; i < 25; i++)
	{
		int InfoX = StartX + 10 + 20;
		int up = i + ( ( this->Page - 1 ) * 25 );

		if(this->RankingChar[up].Name[0] == NULL) continue;

		DWORD Color;

		if(c == 0 )
		{
			Color = eWhite;
		}
		else
		{
			Color = eShinyGreen;
		}

		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d", up+1);

		InfoX += 20;
		char NameID[10+1];
		NameID[10] = 0;
		memcpy(NameID, this->RankingChar[up].Name, sizeof(this->RankingChar[up].Name));
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, NameID);

		InfoX += 80;
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, CharacterCode(this->RankingChar[up].Class));

		bool bLicenesePremium = false;

		if( g_ExLicense.CheckUser(eExUB::Local)			||
			g_ExLicense.CheckUser(eExUB::SILVER1)		||
		    g_ExLicense.CheckUser(eExUB::SILVER2)		||
	        g_ExLicense.CheckUser(eExUB::SILVER_Local))
		{
			bLicenesePremium = true;
		}

		InfoX += 70;
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].level);

		InfoX += 30;
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].Reset);

		InfoX += 30;
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].Grand);

		if(g_ExLicense.CheckUser(eExUB::masonX))
		{
			InfoX += 30;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d", 
				this->RankingChar[up].Str + this->RankingChar[up].Agi + this->RankingChar[up].Vit + this->RankingChar[up].Ene + this->RankingChar[up].Cmd);
		}
		else if(bLicenesePremium == true && this->RankingChar[up].Premium > 0)
		{
			InfoX += 30;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "- / -");
		}
		else
		{
			InfoX += 30;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].Str);

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].Agi);

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].Vit);

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].Ene);

			InfoX += 45;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].Cmd);
		}

		InfoX += 45;

		char GuildID[8+1];
		GuildID[8] = 0;
		memcpy(GuildID, this->RankingChar[up].Guild, sizeof(this->RankingChar[up].Guild));

		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, GuildID);

		pDrawGUI(0x7B67, StartX + 10 + 20, InfoY+8 , 150, 2);
		pDrawGUI(0x7B67, StartX + 10 + 20+150, InfoY+8 , 150, 2);
		pDrawGUI(0x7B67, StartX + 10 + 20+150+150, InfoY+8 , 150, 2);
		pDrawGUI(0x7B67, StartX + 10 + 20+150+150+90, InfoY+8 , 150, 2);

		InfoY+=12;
		c++;
		if(c==2)c=0;
	}

	//00000000000000000

	DWORD Delay = (GetTickCount() - this->ClickTime);

	int ButX = 180;
	int ButY = 98;

	pDrawGUI(0x7BAA, StartX+60+ButX, StartY+275+ButY , 20, 20);

	if(CursorZoneButton(StartX+60+ButX, StartY+275+ButY, StartX+60+20+ButX, StartY+275+20+ButY))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
			if(this->Page != 1) this->Page--;
		}
		pDrawColorButton(0x7BAA, StartX+60+ButX, StartY+275+ButY, 20, 20, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	gInterface.DrawFormat(eGold, StartX+100+ButX, StartY+277+ButY, 100, 1, g_ExText.GetText(34), this->Page,4);


	pDrawGUI(0x7BAB, StartX+150+ButX, StartY+275+ButY , 20, 20);

	if(CursorZoneButton(StartX+150+ButX, StartY+275+ButY, StartX+150+20+ButX, StartY+275+20+ButY))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
			if(this->Page != 4) this->Page++;
		}
		pDrawColorButton(0x7BAB, StartX+150+ButX, StartY+275+ButY, 20, 20, 0, 0, pMakeColor(255, 204, 20, 130));
	}
}