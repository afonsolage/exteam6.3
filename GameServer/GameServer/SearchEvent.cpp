#include "StdAfx.h"
#include "user.h"
#include "SearchEvent.h"
#include "DSProtocol.h"
#include "Message.h"
#include "Functions.h"
#include "ExLicense.h"
#ifdef _MESSAGE_CONFIG_
#include "Configs.h"
#endif
#include "ExFunction.h"
#include "logproc.h"
#include "TimerEx.h"
#include "ExText.h"

cSearchEvent SearchEvent;

cSearchEvent::cSearchEvent()
{
	this->Start = false;
}

cSearchEvent::~cSearchEvent()
{

}

void cSearchEvent::LoadingEvent()
{

	this->Enable = GetPrivateProfileInt("Common","Enable",1,SEARCH_EVENT_DIR);
	this->NPC = GetPrivateProfileInt("Common","NPC",258,SEARCH_EVENT_DIR);
	this->PresWcoin = GetPrivateProfileInt("Common","PresWcoin",10,SEARCH_EVENT_DIR);
	this->Map = GetPrivateProfileInt("Common","Map",0,SEARCH_EVENT_DIR);
	this->Time = GetPrivateProfileInt("Common","Time",60,SEARCH_EVENT_DIR) * 60;
	this->ItemCount = GetPrivateProfileInt("Common","ItemCount",5,SEARCH_EVENT_DIR);

	this->BonusCredits = GetPrivateProfileInt("Common","BonusCredits",10,SEARCH_EVENT_DIR);
	this->BonusWcoinC = GetPrivateProfileInt("Common","BonusWcoinC",10,SEARCH_EVENT_DIR);
	this->BonusWcoinP = GetPrivateProfileInt("Common","BonusWcoinP",10,SEARCH_EVENT_DIR);
	this->BonusGoblinPoints = GetPrivateProfileInt("Common","BonusGoblinPoints",10,SEARCH_EVENT_DIR);

	for(int i=0;i<10;i++)
	{
		this->TickTime[i].Hour = 0;
		this->TickTime[i].Min = 0;
	}

	for(int i(0);i < 255; i++)
	{
		this->Item[i].Index = 0;
		this->Item[i].Type  = 0;
		this->Item[i].Level = 0;
		this->Item[i].Skill = 0;
		this->Item[i].Luck  = 0;
		this->Item[i].Opt   = 0;
		this->Item[i].Exl	= 0;
		this->Item[i].Anc   = 0;
	}

	for(int i=0;i<3;i++)
	{
		for(int l=0;l<100;l++)
		{
			this->Cord[i][l].X = 0;
			this->Cord[i][l].Y = 0;
		}
	}

	FILE *file = fopen(SEARCH_EVENT_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,SEARCH_EVENT_DIR,"LOAD ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;

	this->Count = 0;
	this->Count2 = 0;

	this->CountCord[1] = 0;
	this->CountCord[2] = 0;
	this->CountCord[3] = 0;

	while(!feof(file)) 
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if(Flag == 1)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->TickTime[this->Count].Hour  = n[0];
			this->TickTime[this->Count].Min   = n[1];
			this->Count++;
		}
		if(Flag == 2)
		{
			int n[10];
			sscanf(Buff, "%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);

			this->Item[this->Count2].Type  = n[0];
			this->Item[this->Count2].Index = n[1];
			this->Item[this->Count2].Level = n[2];
			this->Item[this->Count2].Skill = n[3];
			this->Item[this->Count2].Luck  = n[4];
			this->Item[this->Count2].Opt   = n[5];
			this->Item[this->Count2].Exl   = n[6];
			this->Item[this->Count2].Anc   = n[7];
			this->Count2++;
		}
		//----------------------------------------
		//Lorencia
		if(Flag == 3)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Cord[1][this->CountCord[1]].X  = n[0];
			this->Cord[1][this->CountCord[1]].Y   = n[1];
			this->CountCord[1]++;
		}
		//Noria
		if(Flag == 4)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Cord[2][this->CountCord[2]].X  = n[0];
			this->Cord[2][this->CountCord[2]].Y   = n[1];
			this->CountCord[2]++;
		}
		//Devias
		if(Flag == 5)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Cord[3][this->CountCord[3]].X  = n[0];
			this->Cord[3][this->CountCord[3]].Y   = n[1];
			this->CountCord[3]++;
		}
	}
	fclose(file);
}

void cSearchEvent::SearchIndexNPC()
{
}

void cSearchEvent::NPCClick(int aIndex, int aNPC)
{
	if(!this->Enable)
		return;
	if(this->Start == false)
		return;
	LPOBJ lpObj = &gObj[aIndex];

	LPOBJ NpcObj = &gObj[aNPC];

	if(NpcObj->Class == this->NPC && this->IndexNPC == NpcObj->m_Index)
	{

		if(this->Stage == 1)
		{
			if(lpObj->MapNumber != 0)
				return;
		}
		else if(this->Stage == 2)
		{
			if(lpObj->MapNumber != 3)
				return;
		}
		else if(this->Stage == 3)
		{
			if(lpObj->MapNumber != 2)
				return;
		}

		this->Present(aIndex);

		if(this->Stage == 1)
		{

			MessaageAllGlobal(g_ExText.GetText(92), lpObj->Name);

			if(CountCord[2] == 0)
			{
				this->EventEnd();
				this->Stage = 0;
				return;
			}

			//To Noria
			int Num = rand()%CountCord[2];
			int X = Cord[2][Num].X;
			int Y = Cord[2][Num].Y;

			NpcObj->MapNumber = 3;	//noria
			NpcObj->X = X;
			NpcObj->Y = Y;

			MessaageAllGlobal(g_ExText.GetText(93));

			this->Stage++;
		}
		else if(this->Stage == 2)
		{

			MessaageAllGlobal(g_ExText.GetText(94),lpObj->Name);

			if(CountCord[3] == 0)
			{
				this->EventEnd();
				this->Stage = 0;
				return;
			}

			//To Devias
			int Num = rand()%CountCord[3];

			NpcObj->MapNumber = 2;	//Devias
			int X = Cord[3][Num].X;
			int Y = Cord[3][Num].Y;

			NpcObj->X = X;
			NpcObj->Y = Y;
#ifdef PRIVATE_MODULE
			/*if(g_ExLicense.CheckUser(Encode))
			{
				MessaageAllGlobal("[Evangelion] In Elysea!");
			}
			else if(g_ExLicense.CheckUser(eExUB::MU2Play))
			{
				MessaageAllGlobal("[Evangelion] In Arkania!");
			}
			else*/
			{
				MessaageAllGlobal(g_ExText.GetText(95));
			}
#else
			MessaageAllGlobal("[Evangelion] In Devias!");
#endif
			this->Stage++;
		}
		else if(this->Stage == 3)
		{
#ifdef PRIVATE_MODULE
			/*if(g_ExLicense.CheckUser(Encode))
			{
				MessaageAllGlobal("[Evangelion] Elysea Win %s!",lpObj->Name);
			}
			else if(g_ExLicense.CheckUser(Encode))
			{
				MessaageAllGlobal("[Evangelion] Arkania Win %s!",lpObj->Name);
			}
			else*/
			{
				MessaageAllGlobal(g_ExText.GetText(96), lpObj->Name);
			}
#else
			MessaageAllGlobal("[Evangelion] Devias Win %s!",lpObj->Name);
#endif
			//To End
			this->EventEnd();
			this->Stage = 0;
		}
	}
}

void cSearchEvent::EventStart()
{
	srand(time(NULL));

	if(CountCord[1] == 0)
	{
		this->EventEnd();
		this->Stage = 0;
		return;
	}

	int Num = rand()%CountCord[1];
	int X = Cord[1][Num].X;
	int Y = Cord[1][Num].Y;

	int result = gObjAddMonster(this->Map);

	if(result >= 0 && result < OBJ_MAXMONSTER)
	{
		gObj[result].m_PosNum = (WORD)-1;
		gObj[result].MapNumber = this->Map;
		gObj[result].X = X;
		gObj[result].Y = Y;
		gObj[result].TX = X;
		gObj[result].TY = Y;
		gObj[result].m_OldX = X;
		gObj[result].m_OldY = Y;
		gObj[result].StartX = X;
		gObj[result].StartY = Y;
		gObj[result].MaxRegenTime = 0;
		gObj[result].Dir = rand()%8;
		gObj[result].RegenTime = GetTickCount();

		gObj[result].m_ActState.Emotion       = 1;
		gObj[result].m_ActState.EmotionCount  = 15;

		gObjSetMonster(result,this->NPC);

		this->IndexNPC = result;
	}

	MessaageAllGlobal(g_ExText.GetText(97));
	this->Start = true;
	this->Stage = 1;
}

void cSearchEvent::StartNPC()
{
	if(!this->Enable)
		return;

	if(this->Start == true)
	{
		this->Tick++;
		if(this->Tick >= this->Time)
		{
			this->EventEnd();
			return;
		}
	}

	SYSTEMTIME t;
	GetLocalTime(&t);

	//LogAddC(2, "[DEBUG] ms: %d sec: %d :: tick: %d", t.wMilliseconds, t.wSecond, g_TimerEx.GetSecond());

#if(NEWTIMEREX)
	if(g_TimerEx.GetSecond() == 00)
#else
	if(t.wSecond == 00)
#endif
	{
		for(int i = 0; i < this->Count; i++)
		{
			
#ifdef _MESSAGE_CONFIG_
			if(TickTime[i].Min > 5)
			{
				for(int j=1; j <= 5; j++)
				{
			
					if(TickTime[i].Hour == t.wHour && (TickTime[i].Min-j) == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, j);
				}
			}
			else if(TickTime[i].Min == 4)
			{
					if(TickTime[i].Hour-1 == t.wHour && 59 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 5);
					if(TickTime[i].Hour == t.wHour && 0 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 4);
					if(TickTime[i].Hour == t.wHour && 1 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 3);
					if(TickTime[i].Hour == t.wHour && 2 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 2);
					if(TickTime[i].Hour == t.wHour && 3 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 1);

			}
			else if(TickTime[i].Min == 3)
			{
					if(TickTime[i].Hour-1 == t.wHour && 58 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 5);
					if(TickTime[i].Hour-1 == t.wHour && 59 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 4);
					if(TickTime[i].Hour == t.wHour && 0 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 3);
					if(TickTime[i].Hour == t.wHour && 1 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 2);
					if(TickTime[i].Hour == t.wHour && 2 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 1);
			}
			else if(TickTime[i].Min == 2)
			{
					if(TickTime[i].Hour-1 == t.wHour && 57 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 5);
					if(TickTime[i].Hour-1 == t.wHour && 58 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 4);
					if(TickTime[i].Hour-1 == t.wHour && 59 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 3);
					if(TickTime[i].Hour == t.wHour && 0 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 2);
					if(TickTime[i].Hour == t.wHour && 1 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 1);
			}
			else if(TickTime[i].Min == 1)
			{
					if(TickTime[i].Hour-1 == t.wHour && 56 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 5);
					if(TickTime[i].Hour-1 == t.wHour && 57 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 4);
					if(TickTime[i].Hour-1 == t.wHour && 58 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 3);
					if(TickTime[i].Hour-1 == t.wHour && 59 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 2);
					if(TickTime[i].Hour == t.wHour && 0 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 1);
			}
			else if(TickTime[i].Min == 0)
			{
					if(TickTime[i].Hour-1 == t.wHour && 55 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 5);
					if(TickTime[i].Hour-1 == t.wHour && 56 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 4);
					if(TickTime[i].Hour-1 == t.wHour && 57 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 3);
					if(TickTime[i].Hour-1 == t.wHour && 58 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 2);
					if(TickTime[i].Hour-1 == t.wHour && 59 == t.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.SearchEvent, 1);
			
			}
#endif

			if(this->TickTime[i].Hour == t.wHour && this->TickTime[i].Min == t.wMinute)
			{
				this->EventStart();
				return;
			}
		}
	}
}

void cSearchEvent::Present(int aIndex)
{
	//OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);	
	LPOBJ lpObj = &gObj[aIndex];
	if(this->ItemCount > 0)
	{
		for(int i=0;i<this->ItemCount;i++)
		{
			int Ran = rand()%Count2;

			int NewExl = 0;
			int NewAnc = 0;

			int DropItem = ITEMGET(this->Item[Ran].Type,this->Item[Ran].Index);

			if(Item[Ran].Exl > 0)
				NewExl = GenExcOpt(Item[Ran].Exl);

			if(Item[Ran].Anc == 5 || Item[Ran].Anc == 10)
				NewAnc = Item[Ran].Anc;

			ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,DropItem,this->Item[Ran].Level,0,
				this->Item[Ran].Skill,this->Item[Ran].Luck,this->Item[Ran].Opt,aIndex,NewExl,NewAnc);
		}
	}

	if(this->BonusCredits > 0)
	{
		lpObj->ExCred += this->BonusCredits;
	}

	if(this->BonusWcoinC > 0)
	{
		lpObj->GameShop.WCoinC += this->BonusWcoinC;
	}
	if(this->BonusWcoinP > 0)
	{
		lpObj->GameShop.WCoinP += this->BonusWcoinP;
	}
	if(this->BonusGoblinPoints > 0)
	{
		lpObj->GameShop.GoblinPoint += this->BonusGoblinPoints;
	}

	if(this->BonusWcoinC > 0 || this->BonusWcoinP > 0 || this->BonusGoblinPoints > 0)
	{
		gGameShop.GDSaveUserInfo(lpObj->m_Index);
	}
}

void cSearchEvent::EventEnd()
{
	this->Start = false;
	this->Tick = 0;
	//OBJECTSTRUCT *gObjNPC = (OBJECTSTRUCT*) OBJECT_POINTER (this->IndexNPC);
	//gObjNPC->MapNumber = DEF_MAP;
	//gObjNPC->X = DEF_X;
	//gObjNPC->Y = DEF_Y;

	gObjDel(this->IndexNPC);
	this->IndexNPC = -1;

	MessaageAllGlobal(g_ExText.GetText(98));
}