#include "stdafx.h"
#include "Interface.h"
#include "QuestSystem.h"
#include "Controller.h"
#include "User.h"
#include "Console.h"
#include "NewHpBar.h"
#include "ExFunction.h"

cQuestSystem gQuestSystem;

cQuestSystem::cQuestSystem()
{
	ZeroMemory(&this->Quest,sizeof(this->Quest));

	this->QMainTableHigh = 394;
	this->QMainTableWidth = 416;
	this->DrawStartX = 640/2 - QMainTableWidth/2;
	this->DrawStartY = 20;
	this->MenuOpen = 0;
	this->DrawQuestTable = false;

	this->InfoColor = 255;
	this->InfoStartY = 23;	
	this->InfoWidth	 = 80;
	this->InfoHigh	 = 75;	
	this->InfoStartX = 90;	
	this->DrawInfoTable = true;

	this->InfoColor2 = 255;
	this->InfoStartY2 = 23;
	this->InfoWidth2	 = 80;
	this->InfoHigh2	 = 120;	
	this->InfoStartX2 = 173;
	this->DrawInfoTable2 = true;

	this->MoveAct = false;
	this->MoveAct2 = false;
}

cQuestSystem::~cQuestSystem()
{
}

//---------------------------------------------------------------------------------

void cQuestSystem::LoadTGA()
{
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\NewTable.tga", 100000, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B1On.tga", 100001, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B2On.tga", 100002, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B3On.tga", 100003, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B4On.tga", 100004, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B5On.tga", 100005, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B6On.tga", 100006, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B7On.tga", 100007, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B8On.tga", 100008, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B9On.tga", 100009, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B10On.tga", 100010, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B1Off.tga", 100011, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B2Off.tga", 100012, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B3Off.tga", 100013, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B4Off.tga", 100014, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B5Off.tga", 100015, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B6Off.tga", 100016, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B7Off.tga", 100017, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B8Off.tga", 100018, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B9Off.tga", 100019, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\B10Off.tga", 100020, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\AcceptOn.tga", 100021, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\AcceptOff.tga", 100022, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\RewardOn.tga", 100023, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\RewardOff.tga", 100024, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\Color.tga", 100025, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\Left.tga", 100026, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\Right.tga", 100027, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Border\\wing1.tga", 100028, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Border\\wing2.tga", 100029, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Border\\reward.tga", 100030, 0x2601, 0x2900, 1);	//Reward
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Border\\price.tga", 100031, 0x2601, 0x2900, 1);		//Price
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Border\\drop.tga", 100032, 0x2601, 0x2900, 1);		//Drop
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Border\\kill.tga", 100033, 0x2601, 0x2900, 1);		//kill
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Border\\info.tga", 100034, 0x2601, 0x2900, 1);		//Info Border
	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Border\\need.tga", 100035, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\QuestSystem\\Buttons\\Close.tga", 100036, 0x2601, 0x2900, 1);
}

//---------------------------------------------------------------------------------

void cQuestSystem::Init()
{

}

//---------------------------------------------------------------------------------

void cQuestSystem::MouseRun()
{
	return;
	if( gController.wMouse == WM_LBUTTONDOWN && 
		pCursorX >=  InfoStartX && pCursorX <=  InfoStartX+InfoWidth && 
		pCursorY >=  InfoStartY && pCursorY <=  InfoStartY+20 )
	{
		pSetCursorFocus = true;
	}
	if( gController.wMouse == WM_LBUTTONUP && MoveAct == true )
	{
		pSetCursorFocus = false;
	}
	if(gController.wMouse == WM_MOUSEMOVE && MoveAct == true && this->DrawInfoTable)
	{
		if( pCursorY > 0 && pCursorY + InfoHigh < 420 && pCursorX >= InfoWidth/2 && pCursorX < 640-InfoWidth/2 )
		{
			pSetCursorFocus = true;
		}
	}

	// ----

	if( gController.wMouse == WM_LBUTTONDOWN && 
		pCursorX >=  InfoStartX2 && pCursorX <=  InfoStartX2+InfoWidth2 && 
		pCursorY >=  InfoStartY2 && pCursorY <=  InfoStartY2+20 )
	{
		pSetCursorFocus = true;
	}
	if( gController.wMouse == WM_LBUTTONUP && MoveAct2 == true )
	{
		pSetCursorFocus = false;
	}
	if(gController.wMouse == WM_MOUSEMOVE && MoveAct2 == true && this->DrawInfoTable2)
	{
		if( pCursorY > 0 && pCursorY + InfoHigh2 < 420 && pCursorX >= InfoWidth2/2 && pCursorX < 640-InfoWidth2/2 )
		{
			pSetCursorFocus = true;
		}
	}
}

//---------------------------------------------------------------------------------

void cQuestSystem::DrawMainTable()
{
	if(!this->DrawQuestTable) return;
	pSetCursorFocus = true;

	//-----------------------------------------------------------------------------------
	//	Draw Quest Icons
	//-----------------------------------------------------------------------------------

	//Close Button
	if(CursorZoneButton(DrawStartX+QMainTableWidth-20, DrawStartY,DrawStartX+QMainTableWidth, DrawStartY+20) && gController.wMouse == WM_LBUTTONDOWN)
	{
		DrawQuestTable = false;
		pSetCursorFocus = false;
		return;
	}

	pDrawGUI(100000, DrawStartX, DrawStartY, QMainTableWidth, QMainTableHigh);

	// ----

	int DrawButtonY = DrawStartY+63;
	int DrawButtonX = DrawStartX+21;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 0;
		}
		pDrawGUI(100001, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 0)
	{
		pDrawGUI(100001, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100011, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 1;
		}
		pDrawGUI(100002, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 1)
	{
		pDrawGUI(100002, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100012, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 2;
		}
		pDrawGUI(100003, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 2)
	{
		pDrawGUI(100003, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100013, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 3;
		}
		pDrawGUI(100004, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 3)
	{
		pDrawGUI(100004, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100014, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 4;
		}
		pDrawGUI(100005, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 4)
	{
		pDrawGUI(100005, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100015, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 5;
		}
		pDrawGUI(100006, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 5)
	{
		pDrawGUI(100006, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100016, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 6;
		}
		pDrawGUI(100007, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 6)
	{
		pDrawGUI(100007, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100017, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 7;
		}
		pDrawGUI(100008, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 7)
	{
		pDrawGUI(100008, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100018, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 8;
		}
		pDrawGUI(100009, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 8)
	{
		pDrawGUI(100009, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100019, DrawButtonX, DrawButtonY, 142, 25);
	}

	// ----

	DrawButtonY += 28;

	if(CursorZoneButton(DrawButtonX, DrawButtonY, DrawButtonX + 142, DrawButtonY + 25))
	{
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			MenuOpen = 9;
		}
		pDrawGUI(100010, DrawButtonX, DrawButtonY, 142, 25);
	}
	else if(MenuOpen == 9)
	{
		pDrawGUI(100010, DrawButtonX, DrawButtonY, 142, 25);
	}
	else
	{
		pDrawGUI(100020, DrawButtonX, DrawButtonY, 142, 25);
	}

	//---------------------------------------------------------------------------------
	//	Data Send Client -> Server
	//---------------------------------------------------------------------------------

	if(this->Quest[MenuOpen].Finish)
	{
		pDrawGUI(100022, DrawButtonX + 240, DrawButtonY + 37, 142, 25);
	}
	else
	{
		if(this->Quest[MenuOpen].accept && !this->Quest[MenuOpen].start)
		{
			if(CursorZoneButton(DrawButtonX + 240, DrawButtonY + 37, DrawButtonX + 240 + 142, DrawButtonY + 37 + 25) && gController.wMouse == WM_LBUTTONDOWN)
			{
				//Packet Prinyal Quest
				CGSendQuestResult rSend;
				rSend.h.set((LPBYTE)&rSend, 0xFB, 15, sizeof(rSend));
				rSend.Result = 1;	// 1 - Accept
				rSend.Num = MenuOpen;
				gProtocol.DataSend((LPBYTE)&rSend, rSend.h.size);
			}
			pDrawGUI(100021, DrawButtonX + 240, DrawButtonY + 37, 142, 25);
		}
		else if(this->Quest[MenuOpen].reward && this->Quest[MenuOpen].start)
		{
			if(CursorZoneButton(DrawButtonX + 240, DrawButtonY + 37, DrawButtonX + 240 + 142, DrawButtonY + 37 + 25) && gController.wMouse == WM_LBUTTONDOWN)
			{
				//Packet Reward Quest
				CGSendQuestResult rSend;
				rSend.h.set((LPBYTE)&rSend, 0xFB, 15, sizeof(rSend));
				rSend.Result = 2;	//2 - Reward
				rSend.Num = MenuOpen;
				gProtocol.DataSend((LPBYTE)&rSend, rSend.h.size);

			}
			pDrawGUI(100023, DrawButtonX + 240, DrawButtonY + 37, 142, 25);
		}
		else if(!this->Quest[MenuOpen].reward && this->Quest[MenuOpen].start)
		{
			pDrawGUI(100024, DrawButtonX + 240, DrawButtonY + 37, 142, 25);
		}
		else
		{
			pDrawGUI(100022, DrawButtonX + 240, DrawButtonY + 37, 142, 25);
		}
	}

	//-----------------------------------------------------------------------------------
	//	Quest Information List
	//-----------------------------------------------------------------------------------

	int TextY = ( DrawStartY + 70 );

	// ----

	if(this->Quest[MenuOpen].Finish)
	{
		gInterface.DrawFormat(eAncient, 300-10 , TextY-5 , 208, 4, "FINISH");
		return;
	}
	
	// ----

	pDrawGUI(100028, DrawButtonX + 166, DrawStartY+62, 142, 25);	//Wings Draw
	pDrawGUI(100029, DrawButtonX + 320, DrawStartY+62, 142, 25);	//Wings Draw

	gInterface.DrawFormat(eGold, 300 , TextY-10+5 , 208 , 3, this->Quest[MenuOpen].Name);	//"Kill All Monsters"

	gInterface.DrawFormat(eWhite, 300, TextY+7 , 208, 3, "Quest: %d / %d", this->Quest[MenuOpen].n+1,this->Quest[MenuOpen].e);

	TextY += 25;

	// ----

	pDrawGUI(100034, DrawButtonX + 170, DrawStartY+90, 200, 100);	//Info Table Border

	// ----

	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);

	strcpy(Buff,this->Quest[MenuOpen].Info);

	char * Line = strtok(Buff, "|");

	while( Line != NULL )
	{
		pDrawColorText(Line, 300, TextY, 208, 0, eYellow, 0, 3);
		TextY += 10;
		Line = strtok(NULL, "|");
	}

	int DMainY = 0;

	// ----

	int MTextY = DrawStartY + 70 + 75 - 5;

	gInterface.DrawFormat(eExcellent, 250 , MTextY , 208, 3, "Mission:");
	
	int BorderY = DrawStartY+150+5-5;

	for(int k=0;k<5;k++)
	{
		if(!this->Quest[MenuOpen].MissionType[k]) continue;

		char Buffer[128];
		ZeroMemory(Buffer, sizeof(Buffer));

		//0 - off; 1 - kill; 2 - drop; 3 - item;

		if(this->Quest[MenuOpen].MissionType[k] == 1)	//Kill Mission
		{
			pDrawGUI(100033, DrawButtonX + 170+1, BorderY, 100, 15);
		}
		else if(this->Quest[MenuOpen].MissionType[k] == 2)	//drop
		{
			pDrawGUI(100032, DrawButtonX + 170+1, BorderY, 100, 15);
		}
		else if(this->Quest[MenuOpen].MissionType[k] == 3)	//item
		{
			pDrawGUI(100032, DrawButtonX + 170+1, BorderY, 100, 15);
			
			if(this->Quest[MenuOpen].MissionLvL[k])
			{
				sprintf(Buffer, "%s+%d", this->Quest[MenuOpen].MissionName[k],this->Quest[MenuOpen].MissionLvL[k]);
			}
			else
			{
				sprintf(Buffer, "%s", this->Quest[MenuOpen].MissionName[k]);
			}

			if(this->Quest[MenuOpen].MissionLuck[k])
			{
				strcat(Buffer, "+L");
			}
			if(this->Quest[MenuOpen].MissionExl[k])
			{
				strcat(Buffer, "+E");
			}
			if(this->Quest[MenuOpen].MissionAnc[k])
			{
				strcat(Buffer, "+A");
			}
		}		

		BorderY += 18;

		if(this->Quest[MenuOpen].MissionCheck[k])
		{
			if(this->Quest[MenuOpen].MissionType[k] == 3)
			{
				gInterface.DrawFormat(eWhite, DrawButtonX+90+2 , BorderY - 15 , 208, 3, Buffer);
				gInterface.DrawFormat(eAncient, DrawButtonX+90+55 , BorderY - 15 , 208, 3, "1");
			}
			else
			{
				gInterface.DrawFormat(eWhite, DrawButtonX+90+2 , BorderY - 15 , 208, 3, this->Quest[MenuOpen].MissionName[k]);
				gInterface.DrawFormat(eAncient, DrawButtonX+90+55 , BorderY - 15 , 208, 3, "%d / %d", this->Quest[MenuOpen].Count[k],this->Quest[MenuOpen].MissionLvL[k]);
			}
		}
		else
		{
			if(this->Quest[MenuOpen].MissionType[k] == 3)
			{
				gInterface.DrawFormat(eWhite, DrawButtonX+90+2 , BorderY - 15 , 208, 3, Buffer);
				gInterface.DrawFormat(eRed, DrawButtonX+90+55 , BorderY - 15 , 208, 3, "1");
			}
			else
			{
				gInterface.DrawFormat(eWhite, DrawButtonX+90+2 , BorderY - 15 , 208, 3, this->Quest[MenuOpen].MissionName[k]);
				gInterface.DrawFormat(eRed, DrawButtonX+90+55 , BorderY - 15 , 208, 3, "%d / %d", this->Quest[MenuOpen].Count[k],this->Quest[MenuOpen].MissionLvL[k]);
			}
		}
	}
	
	// ----
	
	gInterface.DrawFormat(eExcellent, 350 , MTextY , 208, 3, "Reward:");

	int RewardY = DrawStartY+150+5-5;

	for(int k = 0; k < 5; k++)
	{
		if(!this->Quest[MenuOpen].RewardType[k]) continue;

		char Buffer[128];
		ZeroMemory(Buffer, sizeof(Buffer));

		//0-off;1-zen;2-ExFreePoints;3-WcoinC;4-WcoinP;5-Goblin;6-Cred;7-Damage;8-Defence;9-Life;10-SD;11-CritDmg;12-ExlDmg;13-Double;14-Ignore;15-Ref;16-Exp;17-Drop;18-Item

		pDrawGUI(100030, DrawButtonX + 170+102, RewardY, 100, 15);

		if(this->Quest[MenuOpen].RewardType[k] == 1)	//zen
		{
			sprintf(Buffer, "Zen Money", this->Quest[MenuOpen].RewardMain[k]);
		}
			
		if(this->Quest[MenuOpen].RewardType[k] == 2)	//ExFreePoints
		{
			sprintf(Buffer, "ExFree Points", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 3)	//WcoinC
		{
			sprintf(Buffer, "WCoin", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 4)	//WcoinP
		{
			sprintf(Buffer, "WCoinP", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 5)	//5-Goblin
		{
			sprintf(Buffer, "Goblin Points", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 6)	//6-Cred
		{
			sprintf(Buffer, "Credits", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 7)	//7-Damage
		{
			sprintf(Buffer, "Damage", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 8)	//8-Defence
		{
			sprintf(Buffer, "Defence", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 9)	//9-Life;
		{
			sprintf(Buffer, "Life", this->Quest[MenuOpen].RewardMain[k]);
		}
			
		if(this->Quest[MenuOpen].RewardType[k] == 10)	//10-SD;
		{
			sprintf(Buffer, "SD", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 11)	//11-CritDmg
		{
			sprintf(Buffer, "Critical Damage", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 12)	//12-ExlDmg
		{
			sprintf(Buffer, "Exellent Damage", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 13)	//13-Double
		{
			sprintf(Buffer, "Double Damage", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 14)	//14-Ignore
		{
			sprintf(Buffer, "Ignore Defence", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 15)	//15-Ref
		{
			sprintf(Buffer, "Reflect Damage", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 16)	//16-Exp
		{
			sprintf(Buffer, "Experience", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 17)	//17-Drop;
		{
			sprintf(Buffer, "Drop", this->Quest[MenuOpen].RewardMain[k]);
		}

		if(this->Quest[MenuOpen].RewardType[k] == 17)	//18-Item
		{
			if(this->Quest[MenuOpen].RewardLvL[k])
			{
				sprintf(Buffer, "%s+%d", (char*)(oItemName * this->Quest[MenuOpen].RewardMain[k]),this->Quest[MenuOpen].RewardLvL[k]);
			}
			else
			{
				sprintf(Buffer, "%s", (char*)(oItemName * this->Quest[MenuOpen].RewardMain[k]));
			}

			if(this->Quest[MenuOpen].RewardLuck[k])
			{
				strcat(Buffer, "+L");
			}
			if(this->Quest[MenuOpen].RewardExl[k])
			{
				strcat(Buffer, "+E");
			}
			if(this->Quest[MenuOpen].RewardAnc[k])
			{
				strcat(Buffer, "+A");
			}
		}

		gInterface.DrawFormat(eWhite, DrawButtonX+90+55+48 , RewardY+3 , 208, 3, Buffer);

		if(this->Quest[MenuOpen].RewardType[k] == 17)
		{
			gInterface.DrawFormat(eAncient, DrawButtonX+90+55+50+51 , RewardY+3 , 208, 3, "1");
		}
		else
		{
			gInterface.DrawFormat(eAncient, DrawButtonX+90+55+50+51 , RewardY+3 , 208, 3, "%d",this->Quest[MenuOpen].RewardMain[k]);
		}
		
		RewardY += 18;
	}

	if(BorderY > RewardY)
	{
		DMainY = BorderY;
	}
	else
	{
		DMainY = RewardY;
	}

	// ----

	MTextY = DMainY-3;

	int PriceY = DMainY+7;

	if(!this->Quest[MenuOpen].start)
	{
		for(int b = 0; b < 5; b++)
		{
			if(this->Quest[MenuOpen].PriceType[b])
			{
				gInterface.DrawFormat(eExcellent, 250 , MTextY , 208, 3, "Price:");
				break;
			}
		}

		for(int k = 0; k < 5; k++)
		{
			if(!this->Quest[MenuOpen].PriceType[k]) continue;

			char Buffer[128];
			ZeroMemory(Buffer, sizeof(Buffer));

			pDrawGUI(100031, DrawButtonX + 170+1, PriceY, 100, 15);

			//0 - off; 1 - zen; 2 - WcoinC; 3 - WcoinP; 4 - Goblin; 5 - Cred; 6 - Item

			if(this->Quest[MenuOpen].PriceType[k] == 1)	//zen
			{
				sprintf(Buffer, "Zen Money", this->Quest[MenuOpen].PriceMain[k], this->Quest[MenuOpen].PriceDone[k]);
			}
			if(this->Quest[MenuOpen].PriceType[k] == 2)	//WcoinC
			{
				sprintf(Buffer, "WCoin", this->Quest[MenuOpen].PriceMain[k], this->Quest[MenuOpen].PriceDone[k]);
			}
			if(this->Quest[MenuOpen].PriceType[k] == 3)	//WcoinP
			{
				sprintf(Buffer, "WCoinP", this->Quest[MenuOpen].PriceMain[k], this->Quest[MenuOpen].PriceDone[k]);
			}
			if(this->Quest[MenuOpen].PriceType[k] == 4)	//Goblin
			{
				sprintf(Buffer, "Goblin Points", this->Quest[MenuOpen].PriceMain[k], this->Quest[MenuOpen].PriceDone[k]);
			}
			if(this->Quest[MenuOpen].PriceType[k] == 5)	//Cred
			{
				sprintf(Buffer, "Credits", this->Quest[MenuOpen].PriceMain[k], this->Quest[MenuOpen].PriceDone[k]);
			}
			if(this->Quest[MenuOpen].PriceType[k] == 6)	//Item
			{
				if(this->Quest[MenuOpen].PriceLvL[k])
				{
					sprintf(Buffer, "%s+%d", (char*)(oItemName * this->Quest[MenuOpen].PriceMain[k]),this->Quest[MenuOpen].PriceLvL[k]);
				}
				else
				{
					sprintf(Buffer, "%s", (char*)(oItemName * this->Quest[MenuOpen].PriceMain[k]));
				}
			}

			gInterface.DrawFormat(eWhite, DrawButtonX+90+2 , PriceY+3 , 208, 3, Buffer);

			if(this->Quest[MenuOpen].PriceCheck[k])
			{
				gInterface.DrawFormat(eAncient, DrawButtonX+90+55 , PriceY+3 , 208, 3, "%d",this->Quest[MenuOpen].PriceMain[k], this->Quest[MenuOpen].PriceDone[k]);
			}
			else
			{
				gInterface.DrawFormat(eRed, DrawButtonX+90+55 , PriceY+3 , 208, 3, "%d",this->Quest[MenuOpen].PriceMain[k], this->Quest[MenuOpen].PriceDone[k]);
			}
			
			PriceY += 18;
		}

		// ----

		if(this->Quest[MenuOpen].NeedLevel || this->Quest[MenuOpen].NeedReset || this->Quest[MenuOpen].NeedGrand)
		{
			gInterface.DrawFormat(eExcellent, 350 , MTextY , 208, 3, "Need:");
		}

		int NeedY = DMainY+7;
		
		if(this->Quest[MenuOpen].NeedLevel)
		{
			pDrawGUI(100035, DrawButtonX + 170+102, NeedY, 100, 15);
			gInterface.DrawFormat(eWhite, DrawButtonX+90+55+48 , NeedY+3 , 208, 3, "Level", this->Quest[MenuOpen].NeedLevel, this->Quest[MenuOpen].LevelDone);

			if(this->Quest[MenuOpen].NeedLevel > this->Quest[MenuOpen].LevelDone)
			{
				gInterface.DrawFormat(eRed, DrawButtonX+90+55+50+51 , NeedY+3 , 208, 3, "%d", this->Quest[MenuOpen].NeedLevel);
			}
			else
			{
				gInterface.DrawFormat(eAncient, DrawButtonX+90+55+50+51 , NeedY+3 , 208, 3, "%d", this->Quest[MenuOpen].NeedLevel);
			}

			NeedY+= 18;
		}
		
		if(this->Quest[MenuOpen].NeedReset)
		{
			pDrawGUI(100035, DrawButtonX + 170+102, NeedY, 100, 15);
			gInterface.DrawFormat(eWhite, DrawButtonX+90+55+48 , NeedY+3 , 208, 3, "Reset", this->Quest[MenuOpen].NeedReset, this->Quest[MenuOpen].ResetDone);

			if(this->Quest[MenuOpen].NeedReset > this->Quest[MenuOpen].ResetDone)
			{
				gInterface.DrawFormat(eRed, DrawButtonX+90+55+50+51 , NeedY+3 , 208, 3, "%d", this->Quest[MenuOpen].NeedReset);
			}
			else
			{
				gInterface.DrawFormat(eAncient, DrawButtonX+90+55+50+51 , NeedY+3 , 208, 3, "%d", this->Quest[MenuOpen].ResetDone);
			}

			NeedY+= 18;
		}
		
		if(this->Quest[MenuOpen].NeedGrand)
		{
			pDrawGUI(100035, DrawButtonX + 170+102, NeedY, 100, 15);
			gInterface.DrawFormat(eWhite, DrawButtonX+90+55+48 , NeedY +3, 208, 3, "Grand Reset");

			if(this->Quest[MenuOpen].NeedGrand > this->Quest[MenuOpen].GrandDone)
			{
				gInterface.DrawFormat(eRed, DrawButtonX+90+55+50+51 , NeedY+3 , 208, 3, "%d", this->Quest[MenuOpen].NeedGrand);
			}
			else
			{
				gInterface.DrawFormat(eAncient, DrawButtonX+90+55+50+51 , NeedY+3 , 208, 3, "%d", this->Quest[MenuOpen].NeedGrand);
			}
			
			NeedY+= 18;
		}
	}

	return;
}

// -------------------------------------------------------------------------------------------

void cQuestSystem::DrawInfo()
{
	if(!this->DrawInfoTable) return;
	//if(this->DrawQuestTable) return;

	//if(!gInterface.RightWindows()) return;

	if( gInterface.CheckWindow(CashShop)
		||	gInterface.CheckWindow(SkillTree)
		||	gInterface.CheckWindow(FullMap) 
		||	gInterface.CheckWindow(MoveList) 
		||  (gInterface.CheckWindow(Inventory) 
		&& gInterface.CheckWindow(ExpandInventory) 
		&& gInterface.CheckWindow(Store)) 
		||  (gInterface.CheckWindow(Inventory) 
		&& gInterface.CheckWindow(Warehouse) 
		&& gInterface.CheckWindow(ExpandWarehouse)) )
	{
		return;
	}

	pDrawColorButton(0x7880, InfoStartX , InfoStartY, InfoWidth, 11, 0, 0, (int)Color4f(0, 0, 0, 255));
	pDrawColorButton(0x7880, InfoStartX , InfoStartY, 2, InfoHigh, 0, 0, (int)Color4f(0, 0, 0, 255));

	pDrawColorButton(0x7880, InfoStartX , InfoStartY+InfoHigh, InfoWidth+2, 2, 0, 0, (int)Color4f(0, 0, 0, 255));	//Должна быть нижняя линия
	pDrawColorButton(0x7880, InfoStartX+InfoWidth , InfoStartY, 2, InfoHigh, 0, 0, (int)Color4f(0, 0, 0, 255));	//Боковая линия

	pDrawColorButton(0x7880, InfoStartX , InfoStartY, InfoWidth, InfoHigh, 0, 0, (int)Color4f(0, 0, 0, this->InfoColor));
	gInterface.DrawFormat(eYellow, InfoStartX+2, InfoStartY+2, InfoWidth, 3, "Quest: %d",this->MenuOpen+1);

	float TextY = InfoStartY+2+10;

	DWORD Delay = (GetTickCount() - this->InfoClickTime);

	// ----//NewCode

	pDrawGUI(100036,InfoStartX+InfoWidth-10 , InfoStartY, 10, 10);

	if(CursorZoneButton(InfoStartX+InfoWidth-10, InfoStartY, InfoStartX+InfoWidth-10+11, InfoStartY+11) && gController.wMouse == WM_LBUTTONDOWN && Delay > 500)
	{
		this->DrawInfoTable = false;
		
		this->InfoClickTime = GetTickCount();
	}

	// ----	

	pDrawGUI(100025,InfoStartX , InfoStartY, 10, 10);

	if(CursorZoneButton(InfoStartX, InfoStartY, InfoStartX+11, InfoStartY+11) && gController.wMouse == WM_LBUTTONDOWN && Delay > 500)
	{
		if(this->InfoColor == 255)
		{
			this->InfoColor = 0;
		}
		else if(this->InfoColor+50 > 255)
		{
			this->InfoColor = 255;
		}
		else
		{
			this->InfoColor += 50;
		}
		this->InfoClickTime = GetTickCount();
	}

	// ----

	pDrawGUI(100026,InfoStartX+12 , InfoStartY, 10, 10);

	if(CursorZoneButton(InfoStartX+12, InfoStartY, InfoStartX+12+11, InfoStartY+11) && gController.wMouse == WM_LBUTTONDOWN && Delay > 500)
	{
		if(this->MenuOpen != 0)
		{
			this->MenuOpen--;
		}
		
		this->InfoClickTime = GetTickCount();
	}

	// ----

	pDrawGUI(100027,InfoStartX+InfoWidth-22 , InfoStartY, 10, 10);

	if(CursorZoneButton(InfoStartX+InfoWidth-22, InfoStartY, InfoStartX+InfoWidth-22+11, InfoStartY+11) && gController.wMouse == WM_LBUTTONDOWN && Delay > 500)
	{
		if(this->MenuOpen != 9)
		{
			this->MenuOpen++;
		}
		
		this->InfoClickTime = GetTickCount();
	}

	// ----

	if(this->Quest[MenuOpen].Finish)
	{
		gInterface.DrawFormat(eAncient, InfoStartX , InfoStartY+2+10 , InfoWidth, 3, "FINISH");
		return;
	}

	if(!this->Quest[MenuOpen].start) 
	{
		gInterface.DrawFormat(eAncient, InfoStartX , InfoStartY+2+10 , InfoWidth, 3, "NO MISSION");
		return;
	}

	TextY = gInterface.DrawFormat(eExcellent, InfoStartX, TextY, InfoWidth, 3, this->Quest[this->MenuOpen].Name);

	for(int k=0;k<5;k++)
	{
		char Buffer[128];
		ZeroMemory(Buffer, sizeof(Buffer));

		//0 - off; 1 - kill; 2 - drop; 3 - item;

		if(this->Quest[MenuOpen].MissionType[k] == 1)	//Kill Mission
		{
			sprintf(Buffer, "%s: %d / %d", this->Quest[MenuOpen].MissionName[k],this->Quest[MenuOpen].Count[k],this->Quest[MenuOpen].MissionLvL[k]);
		}
		else if(this->Quest[MenuOpen].MissionType[k] == 2)	//drop
		{
			sprintf(Buffer, "%s: %d / %d", this->Quest[MenuOpen].MissionName[k],this->Quest[MenuOpen].Count[k],this->Quest[MenuOpen].MissionLvL[k]);
		}
		else if(this->Quest[MenuOpen].MissionType[k] == 3)	//item
		{
			if(this->Quest[MenuOpen].MissionLvL[k])
			{
				sprintf(Buffer, "%s +%d", this->Quest[MenuOpen].MissionName[k],this->Quest[MenuOpen].MissionLvL[k]);
			}
			else
			{
				sprintf(Buffer, "%s", this->Quest[MenuOpen].MissionName[k]);
			}

			if(this->Quest[MenuOpen].MissionLuck[k])
			{
				strcat(Buffer, " +Luck");
			}
			if(this->Quest[MenuOpen].MissionExl[k])
			{
				strcat(Buffer, " +Exellent");
			}
			if(this->Quest[MenuOpen].MissionAnc[k])
			{
				strcat(Buffer, " +Ancent");
			}
		}		
		if(this->Quest[MenuOpen].MissionCheck[k])
		{
			TextY = gInterface.DrawFormat(eAncient, InfoStartX , TextY , InfoWidth, 3, Buffer);
		}
		else
		{
			TextY = gInterface.DrawFormat(eRed, InfoStartX , TextY , InfoWidth, 3, Buffer);
		}
	}

	return;
}

void cQuestSystem::DrawInfoAchievements()
{
	if(!this->DrawInfoTable2) return;
	if(this->DrawQuestTable) return;

	//if(!gInterface.RightWindows()) return;

	if( gInterface.CheckWindow(CashShop)
		||	gInterface.CheckWindow(SkillTree)
		||	gInterface.CheckWindow(FullMap) 
		//||	gInterface.CheckWindow(MoveList) 
		||  (gInterface.CheckWindow(Inventory) 
		&& gInterface.CheckWindow(ExpandInventory) 
		&& gInterface.CheckWindow(Store)) 
		||  (gInterface.CheckWindow(Inventory) 
		&& gInterface.CheckWindow(Warehouse) 
		&& gInterface.CheckWindow(ExpandWarehouse)) )
	{
		return;
	}

	pDrawColorButton(0x7880, InfoStartX2 , InfoStartY2, InfoWidth2, 11, 0, 0, (int)Color4f(0, 0, 0, 255));
	pDrawColorButton(0x7880, InfoStartX2 , InfoStartY2, 2, InfoHigh2, 0, 0, (int)Color4f(0, 0, 0, 255));

	pDrawColorButton(0x7880, InfoStartX2 , InfoStartY2+InfoHigh2, InfoWidth2+2, 2, 0, 0, (int)Color4f(0, 0, 0, 255));	//Должна быть нижняя линия
	pDrawColorButton(0x7880, InfoStartX2+InfoWidth2 , InfoStartY2, 2, InfoHigh2, 0, 0, (int)Color4f(0, 0, 0, 255));	//Боковая линия

	pDrawColorButton(0x7880, InfoStartX2 , InfoStartY2, InfoWidth2, InfoHigh2, 0, 0, (int)Color4f(0, 0, 0, this->InfoColor2));	//100
	gInterface.DrawFormat(eYellow, InfoStartX2, InfoStartY2+2, InfoWidth2, 3, "Achievements");

	float TextY = InfoStartY2+2+10;

	pDrawGUI(100025,InfoStartX2+InfoWidth2-22 , InfoStartY2, 10, 10);	//Settings

	DWORD Delay = (GetTickCount() - this->InfoClickTime2);

	if(CursorZoneButton(InfoStartX2+InfoWidth2-22, InfoStartY2, InfoStartX2+InfoWidth2-22+11, InfoStartY2+11) && gController.wMouse == WM_LBUTTONDOWN && Delay > 500)
	{
		if(this->InfoColor2 == 255)
		{
			this->InfoColor2 = 0;
		}
		else if(this->InfoColor2+50 > 255)
		{
			this->InfoColor2 = 255;
		}
		else
		{
			this->InfoColor2 += 50;
		}
		this->InfoClickTime2 = GetTickCount();
	}

	// ----

	pDrawGUI(100036,InfoStartX2+InfoWidth2-10 , InfoStartY2, 10, 10);

	if(CursorZoneButton(InfoStartX2+InfoWidth2-10, InfoStartY2, InfoStartX2+InfoWidth2-10+11, InfoStartY2+11) && gController.wMouse == WM_LBUTTONDOWN && Delay > 500)
	{
		this->DrawInfoTable2 = false;
		
		this->InfoClickTime2 = GetTickCount();
	}

	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Damage: +%d",this->Damage);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Defence: +%d",this->Defence);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Critical Damage: +%d%%",this->Crit);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Exellent Damage: +%d%%",this->Exel);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Double Damage: +%d%%",this->Double);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Ignore Defence: +%d%%",this->Ignore);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Reflect Damage: +%d%%",this->Ref);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Experience: +%d%%",this->Exp);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Drop: +%d%%",this->Drop);	
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "Life: +%d",this->Life);
	TextY = gInterface.DrawFormat(eExcellent, InfoStartX2 , TextY , InfoWidth2, 3, "SD: +%d",this->SD);
	
	return;
}

// -------------------------------------------------------------------------------------------

void cQuestSystem::Draw()
{
	this->DrawMainTable();
	this->DrawInfo();
	this->DrawInfoAchievements();
}

// -------------------------------------------------------------------------------------------

void cQuestSystem::Protocol(DWORD Case, LPBYTE Data, int Len, int aIndex)
{
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
				case 0x02:
					{
						CGWinQuestSystemTable * Recv = (CGWinQuestSystemTable*)Data;
						for(int i=0; i < MAX_WIN_QUEST; i++)
						{
							strncpy(this->Quest[i].Name,Recv->exQuest[i].Name,50);
							strncpy(this->Quest[i].Info,Recv->exQuest[i].Info,256);

							this->Quest[i].n = Recv->exQuest[i].n;
							this->Quest[i].e = Recv->exQuest[i].e;

							this->Quest[i].Finish = Recv->exQuest[i].Finish;

							this->Quest[i].start = Recv->exQuest[i].start;

							this->Quest[i].accept = Recv->exQuest[i].accept;
							this->Quest[i].reward = Recv->exQuest[i].reward;

							// ----

							for(int k = 0; k < 5; k++)
							{
								this->Quest[i].MissionType[k] = Recv->exQuest[i].MissionType[k];
								this->Quest[i].MissionMain[k] = Recv->exQuest[i].MissionMain[k];
								this->Quest[i].MissionLvL[k] = Recv->exQuest[i].MissionLvL[k];
								this->Quest[i].MissionLuck[k] = Recv->exQuest[i].MissionLuck[k];
								this->Quest[i].MissionExl[k] = Recv->exQuest[i].MissionExl[k];
								this->Quest[i].MissionAnc[k] = Recv->exQuest[i].MissionAnc[k];

								this->Quest[i].MissionCheck[k] = Recv->exQuest[i].MissionCheck[k];

								strncpy(this->Quest[i].MissionName[k],Recv->exQuest[i].MissionName[k],20);

								this->Quest[i].Count[k] = Recv->exQuest[i].Count[k];
							}

							// ----

							for(int k = 0; k < 5; k++)
							{
								this->Quest[i].RewardType[k] = Recv->exQuest[i].RewardType[k];
								this->Quest[i].RewardMain[k] = Recv->exQuest[i].RewardMain[k];
								this->Quest[i].RewardLvL[k] = Recv->exQuest[i].RewardLvL[k];
								this->Quest[i].RewardLuck[k] = Recv->exQuest[i].RewardLuck[k];
								this->Quest[i].RewardExl[k] = Recv->exQuest[i].RewardExl[k];
								this->Quest[i].RewardAnc[k] = Recv->exQuest[i].RewardAnc[k];
							}

							// ----
		
							for(int k = 0; k < 5; k++)
							{
								this->Quest[i].PriceType[k] = Recv->exQuest[i].PriceType[k];
								this->Quest[i].PriceMain[k] = Recv->exQuest[i].PriceMain[k];
								this->Quest[i].PriceLvL[k] = Recv->exQuest[i].PriceLvL[k];

								this->Quest[i].PriceDone[k] = Recv->exQuest[i].PriceDone[k];

								this->Quest[i].PriceCheck[k] = Recv->exQuest[i].PriceCheck[k];
							}

							// ----

							this->Quest[i].NeedLevel = Recv->exQuest[i].NeedLevel;
							this->Quest[i].NeedReset = Recv->exQuest[i].NeedReset;
							this->Quest[i].NeedGrand = Recv->exQuest[i].NeedGrand;

							this->Quest[i].LevelDone = Recv->exQuest[i].LevelDone;
							this->Quest[i].ResetDone = Recv->exQuest[i].ResetDone;
							this->Quest[i].GrandDone = Recv->exQuest[i].GrandDone;
						}

						this->Damage = Recv->Damage;
						this->Defence = Recv->Defence;
						this->Life = Recv->Life;
						this->SD = Recv->SD;
						this->Crit = Recv->Crit;
						this->Exel = Recv->Exel;
						this->Double = Recv->Double;
						this->Ignore = Recv->Ignore;
						this->Ref = Recv->Ref;
						this->Exp = Recv->Exp;
						this->Drop = Recv->Drop;	

						if(Recv->OpenWind)
						{
							this->DrawQuestTable = true;
						}
					}
					break;
				case 0x03:
					{
						CGWinQuestProcess * Recv = (CGWinQuestProcess*)Data;
						for(int i=0; i < MAX_WIN_QUEST; i++)
						{
							for(int k=0;k<5;k++)
							{
								this->Quest[i].Count[k] = Recv->Count[i][k];
								this->Quest[i].MissionCheck[k] = Recv->Check[i][k];
							}
						}						
					}
					break;
				case 0x04:	//Windows Close Packet
					{
						CGWinClose * Recv = (CGWinClose*)Data;
						if(Recv->Result == 1)
						{
							this->DrawQuestTable = false;
						}
					}
					break;
				}
				
			}
			break;
		}
	}

}

void cQuestSystem::RestartQuest()
{
	ZeroMemory(&this->Quest,sizeof(this->Quest));
}

void cQuestSystem::Encode(char* buffer, int size)
{
	BYTE QuestXoR[MAX_QXoR] = {  0xD4, 0x7B, 0x5E, 0x2B, 0x58, 0x48, 0xD4, 0xD9 };

	int a = 0;
	for ( int i = 0 ; i < size ; i++ )
	{
		if( a == MAX_QXoR )
		{
			a = 0;
		}
		buffer[i] = buffer[i] ^ QuestXoR[a];
		a++;
	}
}

void cQuestSystem::SaveGame()
{
	FILE * file = fopen(QUESTINFO_DIR,"w");

	char InfoDate[512];

	sprintf(InfoDate, QUESTBUFFER,this->DrawInfoTable,this->DrawInfoTable2);

	this->Encode(InfoDate,strlen(InfoDate));
	fputs(InfoDate, file);

	fclose(file);
}

void cQuestSystem::LoadGame()
{
	this->DrawInfoTable = true;
	this->DrawInfoTable2 = true;

	FILE * file = fopen(QUESTINFO_DIR,"r");

	if (file == NULL)
	{
		this->SaveGame();
		return;
	}

	char Buff[512];

	while (!feof(file))
	{
		fgets(Buff,512,file);

		this->Encode(Buff,strlen(Buff));

		sscanf(Buff, QUESTBUFFER, &this->DrawInfoTable,&this->DrawInfoTable2);
	}
	fclose(file);
}

void cQuestSystem::Keyboard(WPARAM Click)
{
	if(gInterface.CheckWindow(ObjWindow::ChatWindow)) return;

	if(Click == 0x48)	//H
	{
		if(!this->DrawInfoTable) this->DrawInfoTable = true;
		else this->DrawInfoTable = false;
	}
	else if(Click == 0x4A)	//J
	{
		if(!this->DrawInfoTable2) this->DrawInfoTable2 = true;
		else this->DrawInfoTable2 = false;
	}
}

void cQuestSystem::Switcher(BYTE type)
{
	if(type == 0)
	{
		this->DrawInfoTable = !this->DrawInfoTable;
	}
	else if(type == 1)	//J
	{
		this->DrawInfoTable2 = !this->DrawInfoTable2;
	}
}

bool cQuestSystem::GetActive(BYTE type)
{
	if(type == 0)
	{
		return this->DrawInfoTable;
	}
	else if(type == 1)	//J
	{
		return this->DrawInfoTable2;
	}
}