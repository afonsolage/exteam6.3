#include "StdAfx.h"
#include "EventTimer.h"
#include "Configs.h"
#include "GameMain.h"
#include "Functions.h"
#include "logproc.h"
#include "..\include\readscript.h"
#include "protocol.h"
#include "..\\common\\winutil.h"
#include "ExFunction.h"
#include "ExLicense.h"
#include "LoraBattle.h"
#include "DeviasBattle.h"
#include "TvTEvent.h"
#include "PandoraBoxEvent.h"
#include "SearchEvent.h"
#include "TeleportShop.h"
#include "HappyHour.h"
#include "DropEvent.h"
#include "CastleSiege.h"
#include "DungeonSiege.h"
#include "VIPSystem.h"

cEventTimer gEventTimer;

cEventTimer::cEventTimer()
{

}

cEventTimer::~cEventTimer()
{

}

void cEventTimer::LoadTimer()
{
	this->Enable = GetPrivateProfileInt("ExTeam","EventTimer",0,ExCustom_DIR);

	if(!this->Enable) return;

	FILE * file = fopen(gDirPath.GetNewPath(".\\Events\\BloodCastle.dat"),"r");
	if(file == NULL)
	{
		MessageBoxA(0,gDirPath.GetNewPath(".\\Events\\BloodCastle.dat"),"LOAD FILE ERROR",0);
		ExitProcess(0);
	}
	char Buff[256];
	int Flag = 0;
	this->CountBC = 0;
	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 4)
		{
			int n[2];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->BC[this->CountBC].Hour = n[0];
			this->BC[this->CountBC].Min = n[1];
			this->CountBC++;
		}
	}
	fclose(file);

	// ----

	FILE * file2 = fopen(gDirPath.GetNewPath(".\\Events\\DevilSquare.dat"),"r");
	if(file2 == NULL)
	{
		MessageBoxA(0,gDirPath.GetNewPath(".\\Events\\DevilSquare.dat"),"LOAD FILE ERROR",0);
		ExitProcess(0);
	}
	char Buff2[256];
	int Flag2 = 0;
	this->CountDS = 0;
	while(!feof(file2))
	{
		fgets(Buff2,256,file);
		if(Ex_IsBadFileLine(Buff2, Flag2))
			continue;
		if(Flag2 == 4)
		{
			int n[2];
			sscanf(Buff2, "%d %d", &n[0], &n[1]);
			this->DS[this->CountDS].Hour = n[0];
			this->DS[this->CountDS].Min = n[1];
			this->CountDS++;
		}
	}
	fclose(file2);

	// ----

	FILE * file3 = fopen(gDirPath.GetNewPath(".\\Events\\ChaosCastle.dat"),"r");
	if(file3 == NULL)
	{
		MessageBoxA(0,gDirPath.GetNewPath(".\\Events\\ChaosCastle.dat"),"LOAD FILE ERROR",0);
		ExitProcess(0);
	}
	char Buff3[256];
	int Flag3 = 0;
	this->CountCC = 0;
	while(!feof(file3))
	{
		fgets(Buff3,256,file3);
		if(Ex_IsBadFileLine(Buff3, Flag3))
			continue;
		if(Flag3 == 2)
		{
			int n[2];
			sscanf(Buff3, "%d %d", &n[0], &n[1]);
			this->CC[this->CountCC].Hour = n[0];
			this->CC[this->CountCC].Min = n[1];
			this->CountCC++;
		}
	}
	fclose(file3);

	// ----

	SMDFile = fopen(gDirPath.GetNewPath(".\\Events\\EventManagement.dat"), "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,gDirPath.GetNewPath(".\\Events\\EventManagement.dat"),"LOAD FILE ERROR",0);
		ExitProcess(0);
	}

	int Token;
	int type = -1;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		type = (int)TokenNumber;

		while ( true )
		{
			if ( type == 0 )
			{
				Token = GetToken();

				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				int EventType  = (int)TokenNumber;

				Token = GetToken();
				int EventHour = (int)TokenNumber;

				Token = GetToken();
				int EventMin = (int)TokenNumber;

				if(EventType == 2)
				{
					this->GD[this->CountGD].Hour = EventHour;
					this->GD[this->CountGD].Min = EventMin;
					this->CountGD++;
				}
				if(EventType == 3)
				{
					this->WW[this->CountWW].Hour = EventHour;
					this->WW[this->CountWW].Min = EventMin;
					this->CountWW++;
				}
				if(EventType == 0)
				{
					this->RD[this->CountRD].Hour = EventHour;
					this->RD[this->CountRD].Min = EventMin;
					this->CountRD++;
				}
			}
		}
	}

	fclose(SMDFile);

}

void cEventTimer::Client()
{
	if(!this->Enable) return;

	DWORD BCStart = 0;
	DWORD DSStart = 0;
	DWORD CCStart = 0;
	DWORD GDStart = 0;
	DWORD WWStart = 0;
	DWORD RDStart = 0;

	SYSTEMTIME t;
	GetLocalTime(&t);

	DWORD Tim = time(NULL);

	for(int i=0;i<this->CountBC;i++)
	{
/*
	ATLENSURE( nYear >= 1900 );
	ATLENSURE( nMonth >= 1 && nMonth <= 12 );
	ATLENSURE( nDay >= 1 && nDay <= 31 );
	ATLENSURE( nHour >= 0 && nHour <= 23 );
	ATLENSURE( nMin >= 0 && nMin <= 59 );
	ATLENSURE( nSec >= 0 && nSec <= 59 );
*/

		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime = this->BC[i].Hour * 3600 + this->BC[i].Min * 60 ;

		if(fTime > lTime )
		{
			BCStart = fTime - lTime;
			break;
		}
	}

	if(BCStart == 0)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime =  86400 + this->BC[0].Hour * 3600 + this->BC[0].Min * 60 ;

		if(fTime > lTime )
		{
			BCStart = fTime - lTime;
		}
	}

	// ----

	for(int i=0;i<this->CountDS;i++)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime = this->DS[i].Hour * 3600 + this->DS[i].Min * 60 ;

		if(fTime > lTime )
		{
			DSStart = fTime - lTime;
			break;
		}
	}

	if(DSStart == 0)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime =  86400 + this->DS[0].Hour * 3600 + this->DS[0].Min * 60 ;

		if(fTime > lTime )
		{
			DSStart = fTime - lTime;
		}
	}

	// ----

	for(int i=0;i<this->CountCC;i++)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime = this->CC[i].Hour * 3600 + this->CC[i].Min * 60 ;

		if(fTime > lTime )
		{
			CCStart = fTime - lTime;
			break;
		}
	}

	if(CCStart == 0)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime =  86400 + this->CC[0].Hour * 3600 + this->CC[0].Min * 60 ;

		if(fTime > lTime )
		{
			CCStart = fTime - lTime;
		}
	}

	// ----

	for(int i=0;i<this->CountGD;i++)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime = this->GD[i].Hour * 3600 + this->GD[i].Min * 60 ;

		if(fTime > lTime )
		{
			GDStart = fTime - lTime;
			break;
		}
	}

	if(GDStart == 0)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime =  86400 + this->GD[0].Hour * 3600 + this->GD[0].Min * 60 ;

		if(fTime > lTime )
		{
			GDStart = fTime - lTime;
		}
	}

	// ----

	for(int i=0;i<this->CountWW;i++)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime = this->WW[i].Hour * 3600 + this->WW[i].Min * 60 ;

		if(fTime > lTime )
		{
			WWStart = fTime - lTime;
			break;
		}
	}

	if(WWStart == 0)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime =  86400 + this->WW[0].Hour * 3600 + this->WW[0].Min * 60 ;

		if(fTime > lTime )
		{
			WWStart = fTime - lTime;
		}
	}

#if(EVENT_TIMER_EX)

	DWORD TimeLora = 0;
	DWORD TimeDevias = 0;
	DWORD TimeTvT = 0;
	DWORD TimePandora = 0;
	DWORD TimeEvengelion = 0;
	DWORD TimeShop = 0;
	DWORD TimeHappy = 0;
	DWORD TimeDropEvent = 0;
	DWORD TimeCryWolf = 0;
	DWORD TimeCastleSiege = 0;
	DWORD TimeDungeonSiege = 0;

	if(g_ExLicense.CheckUser(eExUB::Local) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2) || 
		g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2) )
	{
		// --
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		// --> Lorencia Battle
		int iCount = LoraBattle.Count;
		for(int i = 0; i < iCount; i++)
		{
			int fTime = LoraBattle.Time[i].Hour * 3600 + LoraBattle.Time[i].Min * 60;
			if(fTime > lTime )
			{
				TimeLora = fTime - lTime;
				break;
			}
		}
		if(TimeLora == 0)
		{
			int fTime =  86400 + LoraBattle.Time[0].Hour * 3600 + LoraBattle.Time[0].Min;
			if(fTime > lTime)
			{
				TimeLora = fTime - lTime;
			}
		}	
		// --> Devias Battle
		iCount = g_DeviasBattle.Count;
		for(int i = 0; i < iCount; i++)
		{
			int fTime = g_DeviasBattle.Time[i].Hour * 3600 + g_DeviasBattle.Time[i].Min * 60;
			if(fTime > lTime )
			{
				TimeDevias = fTime - lTime;
				break;
			}
		}
		if(TimeDevias == 0)
		{
			int fTime = 86400 + g_DeviasBattle.Time[0].Hour * 3600 + g_DeviasBattle.Time[0].Min;
			if(fTime > lTime)
			{
				TimeDevias = fTime - lTime;
			}
		}	
		// --> TvT
		iCount = TvT.Count;
		for(int i = 0; i < iCount; i++)
		{
			int fTime = TvT.T[i].H * 3600 + g_DeviasBattle.Time[i].Min * 60;
			if(fTime > lTime )
			{
				TimeTvT = fTime - lTime;
				break;
			}
		}
		if(TimeTvT == 0)
		{
			int fTime = 86400 + TvT.T[0].H * 3600 + g_DeviasBattle.Time[0].Min;
			if(fTime > lTime)
			{
				TimeTvT = fTime - lTime;
			}
		}	
		// --> Pandora
		iCount = gPandoraBoxEvent.CountTimes;
		for(int i = 0; i < iCount; i++)
		{
			int fTime = gPandoraBoxEvent.Times[i].Hour * 3600 + gPandoraBoxEvent.Times[i].Min * 60;
			if(fTime > lTime )
			{
				TimePandora = fTime - lTime;
				break;
			}
		}
		if(TimePandora == 0)
		{
			int fTime = 86400 + gPandoraBoxEvent.Times[0].Hour * 3600 + gPandoraBoxEvent.Times[0].Min;
			if(fTime > lTime)
			{
				TimePandora = fTime - lTime;
			}
		}	
		// --> Evangelion
		/*iCount = gPandoraBoxEvent.CountTimes;
		for(int i = 0; i < iCount; i++)
		{
			int fTime = gPandoraBoxEvent.Times[i].Hour * 3600 + gPandoraBoxEvent.Times[i].Min * 60;
			if(fTime > lTime )
			{
				TimePandora = fTime - lTime;
				break;
			}
		}
		if(TimePandora == 0)
		{
			int fTime = 86400 + gPandoraBoxEvent.Times[0].Hour * 3600 + gPandoraBoxEvent.Times[0].Min;
			if(fTime > lTime)
			{
				TimePandora = fTime - lTime;
			}
		}	*/
		// --> SearchEvent
		iCount = SearchEvent.Count;
		for(int i = 0; i < iCount; i++)
		{
			int fTime = SearchEvent.TickTime[i].Hour * 3600 + SearchEvent.TickTime[i].Min * 60;
			if(fTime > lTime )
			{
				TimeEvengelion = fTime - lTime;
				break;
			}
		}
		if(TimeEvengelion == 0)
		{
			int fTime = 86400 + SearchEvent.TickTime[0].Hour * 3600 + SearchEvent.TickTime[0].Min;
			if(fTime > lTime)
			{
				TimeEvengelion = fTime - lTime;
			}
		}	
		// --> Shop Event
		iCount = g_TeleportShop.TimeLoaded;
		for(int i = 0; i < iCount; i++)
		{
			int fTime = g_TeleportShop.DataTime[i].Hour * 3600 + g_TeleportShop.DataTime[i].Min * 60;
			if(fTime > lTime )
			{
				TimeShop = fTime - lTime;
				break;
			}
		}
		if(TimeShop == 0)
		{
			int fTime = 86400 + g_TeleportShop.DataTime[0].Hour * 3600 + g_TeleportShop.DataTime[0].Min;
			if(fTime > lTime)
			{
				TimeShop = fTime - lTime;
			}
		}	
		// --> Happy hour
		iCount = HappyHour.Count;
		for(int i = 0; i < iCount; i++)
		{
			int fTime = HappyHour.HappyStruct[i].Hour * 3600 + HappyHour.HappyStruct[i].Min * 60;
			if(fTime > lTime )
			{
				TimeHappy = fTime - lTime;
				break;
			}
		}
		if(TimeHappy == 0)
		{
			int fTime = 86400 + HappyHour.HappyStruct[0].Hour * 3600 + HappyHour.HappyStruct[0].Min;
			if(fTime > lTime)
			{
				TimeHappy = fTime - lTime;
			}
		}
		// --> Drop
		iCount = DropEvent.Count[2];
		for(int i = 0; i < iCount; i++)
		{
			int fTime = DropEvent.Time[i].Hour * 3600 + DropEvent.Time[i].Min * 60;
			if(fTime > lTime )
			{
				TimeDropEvent = fTime - lTime;
				break;
			}
		}
		if(TimeDropEvent == 0)
		{
			int fTime = 86400 + DropEvent.Time[0].Hour * 3600 + DropEvent.Time[0].Min;
			if(fTime > lTime)
			{
				TimeDropEvent = fTime - lTime;
			}
		}

#if(GS_CASTLE==1 || CS_SERVER)
		// --> CryWolf
		if(TimeCryWolf == 0)
		{
			int fTime = 86400 + g_Crywolf.m_StartTimeInfo[0].m_iHour * 3600 + g_Crywolf.m_StartTimeInfo[0].m_iMinute;

			if(g_Crywolf.m_StartTimeInfo[0].m_iDayOfWeek > 0)
			{
				lTime = t.wDayOfWeek * 86400 + t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
				fTime += 86400 * g_Crywolf.m_StartTimeInfo[0].m_iDayOfWeek;
			}

			if(fTime > lTime)
			{
				TimeCryWolf = fTime - lTime;
			}
		}
		// --> CastleSiege
		if(TimeCastleSiege == 0)
		{
			SYSTEMTIME tm;
			g_CastleSiege.GetStateDate(CASTLESIEGE_STATE_STARTSIEGE, &tm);

			lTime = t.wDayOfWeek * 86400 + t.wHour * 3600 + t.wMinute * 60 + t.wSecond;

			int fTime = 86400 * tm.wDay + tm.wHour * 3600 + tm.wMinute;

			if(fTime > lTime)
			{
				TimeCastleSiege = fTime - lTime;
			}
		}
#endif
#if(EVENT_DUNGEON_SIEGE)
		// --> DungeonSiege
		if(TimeDungeonSiege == 0)
		{
			int fTime = 86400 + g_DungeonSiege.iEventStartHour * 3600 + g_DungeonSiege.iEventeStartMinut;

			if(g_DungeonSiege.iEventStartDay > 0)
			{
				lTime = t.wDayOfWeek * 86400 + t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
				fTime += 86400 * g_DungeonSiege.iEventStartDay;
			}

			if(fTime > lTime)
			{
				TimeDungeonSiege = fTime - lTime;
			}
		}
#endif
	}

	// ----

	for(int i=0;i<this->CountRD;i++)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime = this->RD[i].Hour * 3600 + this->RD[i].Min * 60 ;

		if(fTime > lTime )
		{
			RDStart = fTime - lTime;
			break;
		}
	}

	if(RDStart == 0)
	{
		int lTime = t.wHour * 3600 + t.wMinute * 60 + t.wSecond;
		int fTime =  86400 + this->RD[0].Hour * 3600 + this->RD[0].Min * 60 ;

		if(fTime > lTime )
		{
			RDStart = fTime - lTime;
		}
	}

	// ----

#endif

	// ----

	for (int n=OBJ_STARTUSERINDEX;n<OBJMAX; n++)
	{
		LPOBJ lpObj = &gObj[n];
		if ( lpObj->Connected >= PLAYER_PLAYING && lpObj->OffExp == 0 && lpObj->OffTrade == 0)
		{
			GCTEventTime tSend;
			ZeroMemory(&tSend,sizeof(tSend));
			tSend.h.set((LPBYTE)&tSend, 0xFB, 16, sizeof(tSend));
			tSend.TimeBC = BCStart;
			tSend.TimeDS = DSStart;
			tSend.TimeCC = CCStart;
			tSend.TimeGD = GDStart;
			tSend.TimeWW = WWStart;
#if(EVENT_TIMER_EX)
			tSend.TimeLora = TimeLora;
			tSend.TimeDevias = TimeDevias;
			tSend.TimeTvT = TimeTvT;
			tSend.TimePandora = TimePandora;
			tSend.TimeEvengelion = TimeEvengelion;
			tSend.TimeShop = TimeShop;
			tSend.TimeHappy = TimeHappy;
			tSend.TimeDropEvent = TimeDropEvent;

			tSend.TimeCryWolf = TimeCryWolf;
			tSend.TimeCastleSiege = TimeCastleSiege;
			tSend.TimeDungeonSiege = TimeDungeonSiege;
			tSend.TimeRedDragon = RDStart;
#endif
			DataSend(n,(LPBYTE)&tSend,sizeof(tSend));
		}
	}
}

void NewEvent();