#include "StdAfx.h"
#include "TeleportShop.h"
#include "user.h"
#include "ExFunction.h"
#include "Functions.h"
#include "Message.h"
#include "ExLicense.h"
#include "logproc.h"
#include "TimerEx.h"

#if(TELEPORT_SHOP==TRUE)

TeleportShop g_TeleportShop;
// -------------------------------------------------------------------------------

void TeleportShop::Init()
{
	this->Enable = 0;
	this->EventTime = 0;
	this->Tick = 0;
	this->Start = false;
	this->TimeLoaded = 0;
	if(this->IndexNPC >= 0)
	{
		gObjDel(this->IndexNPC);
	}
	this->IndexNPC = -1;

	ZeroMemory(&this->DataTime, sizeof(DataTime));
}
// -------------------------------------------------------------------------------

void TeleportShop::Load()
{
	this->Init();

	//if( g_ExLicense.CheckUser(feqan) == false)
	//{
	//	return;
	//}

	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,TELEPORT_SHOP_DIR);
	this->EventTime = GetPrivateProfileInt("ExTeam","EventTime",0,TELEPORT_SHOP_DIR) * 60;
	this->Teleport_NPC = GetPrivateProfileInt("ExTeam","Teleport_NPC",379,TELEPORT_SHOP_DIR);
	this->Teleport_Map = GetPrivateProfileInt("ExTeam","Teleport_Map",0,TELEPORT_SHOP_DIR);
	this->Teleport_X = GetPrivateProfileInt("ExTeam","Teleport_X",0,TELEPORT_SHOP_DIR);
	this->Teleport_Y = GetPrivateProfileInt("ExTeam","Teleport_Y",0,TELEPORT_SHOP_DIR);

	GetPrivateProfileString("ExTeam", "MessageStart","MessageStart",this->MessageStart,100,TELEPORT_SHOP_DIR);
	GetPrivateProfileString("ExTeam", "MessageEnd","MessageEnd",this->MessageEnd,100,TELEPORT_SHOP_DIR);

	FILE *file = fopen(TELEPORT_SHOP_DIR,"r");

	/*char szBuf[256] = { 0 };
	sprintf(szBuf, "FILE SIZE: %d", file->_charbuf);
	MessageBoxA(0,szBuf,"LOAD FILE !!!",0);*/

	if(file == NULL)
	{
		MessageBoxA(0,TELEPORT_SHOP_DIR,"LOAD FILE ERROR",0);
		return;
	}

	char Buff[256];
	int Flag = 0;

	this->TimeLoaded = 0;

	while(!feof(file)) 
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if(Flag == 1)
		{
			if(TimeLoaded >= 10)
			{
				break;
			}
			int n[2];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->DataTime[this->TimeLoaded].Hour  = n[0];
			this->DataTime[this->TimeLoaded].Min   = n[1];
			this->TimeLoaded++;
		}
	}
	fclose(file);
}
// -------------------------------------------------------------------------------

void TeleportShop::TickTime()
{
	if(!this->Enable)
		return;

	if(this->Start == true)
	{
		this->Tick++;
		if(this->Tick >= this->EventTime)
		{
			this->EventEnd();
		}
		return;
	}

	SYSTEMTIME t;
	GetLocalTime(&t);
#if(NEWTIMEREX)
	if(g_TimerEx.GetSecond() == 00)
#else
	if(t.wSecond == 00)
#endif
	{
		for(int i = 0; i < this->TimeLoaded; i++)
		{
			if(this->DataTime[i].Hour == t.wHour && this->DataTime[i].Min == t.wMinute)
			{
				this->EventStart();
				return;
			}
		}
	}
}
// -------------------------------------------------------------------------------

void TeleportShop::EventStart()
{
	srand(time(NULL));

	int X = this->Teleport_X;
	int Y = this->Teleport_Y;

	int result = gObjAddMonster(this->Teleport_Map);

	if(result >= 0 && result < OBJ_MAXMONSTER)
	{
		gObj[result].m_PosNum = (WORD)-1;
		gObj[result].MapNumber = this->Teleport_Map;
		gObj[result].X = X;
		gObj[result].Y = Y;
		gObj[result].TX = X;
		gObj[result].TY = Y;
		gObj[result].m_OldX = X;
		gObj[result].m_OldY = Y;
		gObj[result].StartX = X;
		gObj[result].StartY = Y;
		gObj[result].MaxRegenTime = 0;
		gObj[result].Dir = 3;//rand()%8;
		gObj[result].RegenTime = GetTickCount();

		gObj[result].m_ActState.Emotion       = 1;
		gObj[result].m_ActState.EmotionCount  = 15;

		gObjSetMonster(result,this->Teleport_NPC);

		this->IndexNPC = result;
	}

	MessaageAllGlobal(this->MessageStart);
	this->Start = true;
}
// -------------------------------------------------------------------------------

void TeleportShop::EventEnd()
{
	this->Start = false;
	this->Tick = 0;
	if(this->IndexNPC >= 0)
	{
		gObjDel(this->IndexNPC);
	}
	this->IndexNPC = -1;
	MessaageAllGlobal(this->MessageEnd);
	this->GC_CloseWindowShop();
}
// -------------------------------------------------------------------------------

void TeleportShop::GC_CloseWindowShop()
{
	for(int n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
	{
		LPOBJ lpSearch = &gObj[n];
		if(lpSearch->Connected < PLAYER_PLAYING) 
		{
			continue;
		}
		if(lpSearch->NPC == this->Teleport_NPC)
		{
			// -> GC Close Wingosw packet 21
			GC_SHOP_CLOSE rSend;
			ZeroMemory(&rSend,sizeof(rSend));
			rSend.h.set((LPBYTE)&rSend, 0xFB, 21, sizeof(rSend));
			rSend.Close = 1;
			DataSend(n,(LPBYTE)&rSend,sizeof(rSend));
		}
	}
}
// -------------------------------------------------------------------------------
#endif