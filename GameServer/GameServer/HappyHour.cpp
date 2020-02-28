#include "StdAfx.h"
#include "USER.h"
#include "HappyHour.h"
#include "Functions.h"
#include "Message.h"
#ifdef _MESSAGE_CONFIG_
#include "Configs.h"
#endif
#include "TimerEx.h"
#include "ExText.h"

cHappyHour HappyHour;

void cHappyHour::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",1,HH_DIR);
	this->PlusExp = GetPrivateProfileInt("Common","PlusExp",10,HH_DIR);
	this->PlusDrop = GetPrivateProfileInt("Common","PlusDrop",10,HH_DIR);

	this->LoadFile();

	this->StartHappyHour = false;
}

void cHappyHour::LoadFile()
{
	FILE * file = fopen(HH_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,HH_DIR,"LOAD FILE ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;
	this->Count = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			this->HappyStruct[this->Count].Hour		= 0;
			this->HappyStruct[this->Count].Min		= 0;
			this->HappyStruct[this->Count].EndHour	= 0;
			this->HappyStruct[this->Count].EndMin	= 0;

			int n[4];
			sscanf(Buff, "%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);
			this->HappyStruct[this->Count].Hour		= n[0];
			this->HappyStruct[this->Count].Min		= n[1];
			this->HappyStruct[this->Count].EndHour	= n[2];
			this->HappyStruct[this->Count].EndMin	= n[3];
			this->Count++;
		}
	}
	fclose(file);
}

void cHappyHour::Timetick()
{
	SYSTEMTIME time;
	GetLocalTime(&time);

#if(NEWTIMEREX)
	if(g_TimerEx.GetSecond() == 00)
#else
	if(time.wSecond == 00)
#endif
	{
		for(int i = 0; i < this->Count; i++)
		{
#ifdef _MESSAGE_CONFIG_
			if(HappyStruct[i].Min > 5)
			{
				for(int j=1; j <= 5; j++)
				{
			
					if(HappyStruct[i].Hour == time.wHour && (HappyStruct[i].Min-j) == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, j);
				}
			}
			else if(HappyStruct[i].Min == 4)
			{
					if(HappyStruct[i].Hour-1 == time.wHour && 59 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 5);
					if(HappyStruct[i].Hour == time.wHour && 0 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 4);
					if(HappyStruct[i].Hour == time.wHour && 1 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 3);
					if(HappyStruct[i].Hour == time.wHour && 2 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 2);
					if(HappyStruct[i].Hour == time.wHour && 3 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 1);

			}
			else if(HappyStruct[i].Min == 3)
			{
					if(HappyStruct[i].Hour-1 == time.wHour && 58 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 5);
					if(HappyStruct[i].Hour-1 == time.wHour && 59 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 4);
					if(HappyStruct[i].Hour == time.wHour && 0 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 3);
					if(HappyStruct[i].Hour == time.wHour && 1 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 2);
					if(HappyStruct[i].Hour == time.wHour && 2 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 1);
			}
			else if(HappyStruct[i].Min == 2)
			{
					if(HappyStruct[i].Hour-1 == time.wHour && 57 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 5);
					if(HappyStruct[i].Hour-1 == time.wHour && 58 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 4);
					if(HappyStruct[i].Hour-1 == time.wHour && 59 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 3);
					if(HappyStruct[i].Hour == time.wHour && 0 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 2);
					if(HappyStruct[i].Hour == time.wHour && 1 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 1);
			}
			else if(HappyStruct[i].Min == 1)
			{
					if(HappyStruct[i].Hour-1 == time.wHour && 56 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 5);
					if(HappyStruct[i].Hour-1 == time.wHour && 57 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 4);
					if(HappyStruct[i].Hour-1 == time.wHour && 58 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 3);
					if(HappyStruct[i].Hour-1 == time.wHour && 59 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 2);
					if(HappyStruct[i].Hour == time.wHour && 0 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 1);
			}
			else if(HappyStruct[i].Min == 0)
			{
					if(HappyStruct[i].Hour-1 == time.wHour && 55 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 5);
					if(HappyStruct[i].Hour-1 == time.wHour && 56 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 4);
					if(HappyStruct[i].Hour-1 == time.wHour && 57 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 3);
					if(HappyStruct[i].Hour-1 == time.wHour && 58 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 2);
					if(HappyStruct[i].Hour-1 == time.wHour && 59 == time.wMinute)
						MessaageAllGlobal(ExConfig.MessageConfig.HappyHour, 1);
			
			}
#endif
			if(HappyStruct[i].Hour == time.wHour && HappyStruct[i].Min == time.wMinute)
			{
				this->StartHappyHour = true;
				MessaageAllGlobal(g_ExText.GetText(99));
				MessaageAllGlobal(g_ExText.GetText(100),PlusExp,PlusDrop);
				break;
			}
			if(HappyStruct[i].EndHour == time.wHour && HappyStruct[i].EndMin == time.wMinute)
			{
				MessaageAllGlobal(g_ExText.GetText(101));
				this->StartHappyHour = false;
				break;
			}
		}
	}
}

void cHappyHour::UserBonusExp(__int64 & Experience)
{
	if(!this->Enable || !this->StartHappyHour) return;

	Experience += ( Experience * this->PlusExp ) / 100;
}

void cHappyHour::UserBonusZen(float & money)
{
	if(!this->Enable || !this->StartHappyHour) return;

	money += ( money * this->PlusDrop ) / 100;
}