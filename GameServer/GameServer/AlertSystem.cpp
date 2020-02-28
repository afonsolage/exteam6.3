#include "StdAfx.h"
#include "AlertSystem.h"
#include "Functions.h"
#include "Message.h"
#include "TimerEx.h"

cAlertSystem AlertSystem;

void cAlertSystem::Load()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,ALERT_SYSTEM_DIR);
	

	FILE * file = fopen(ALERT_SYSTEM_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,ALERT_SYSTEM_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
	}

	char Buff[256];
	int Flag = 0;
	this->CountDateMessage = 0;
	this->CountEveryDayMessage = 0;
	this->CountIntervalMessage = 0;

	this->m_iNoticeID = 0;
	this->m_iNoticeCount = 0;
	this->m_iNotickeTick = 0;

	for (int i = 0; i < MAX_ALERT_SYSTEM_INTERVAL; i++){this->Interval[i] = 0;}

	for (int i = 0; i < MAX_ALERT_SYSTEM_DATE; i++)
	{
		this->DateMessage[i].Day = 0;
		this->DateMessage[i].Hour = 0;
		ZeroMemory(this->DateMessage[i].Message, strlen(this->DateMessage[i].Message));
		this->DateMessage[i].Minutes = 0;
		this->DateMessage[i].Month = 0;		
	}
	for (int i = 0; i < MAX_ALERT_SYSTEM_DAY; i++)
	{
		this->EveryDayMessage[i].Hour = 0;
		this->EveryDayMessage[i].Minutes = 0;
		ZeroMemory(this->EveryDayMessage[i].Message, strlen(this->EveryDayMessage[i].Message));
	}
	for (int i = 0; i < MAX_ALERT_SYSTEM_INTERVAL; i++)
	{
		this->IntervalMessage[i].Interval = 0;
		ZeroMemory(this->IntervalMessage[i].Message, strlen(this->IntervalMessage[i].Message));
	}
	for (int i = 0; i < MAX_ALERT_SYSTEM_INTERVAL; i++)
	{
		this->NoticeMessage[i].Interval = 0;
		ZeroMemory(this->NoticeMessage[i].Message, strlen(this->NoticeMessage[i].Message));
	}

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			if(this->CountDateMessage == MAX_ALERT_SYSTEM_DATE) break;
			int n[4];
			char str[100];
			sscanf(Buff, "%d %d %d %d \"%[^\"]\"", &n[0], &n[1], &n[2], &n[3], &str);
			this->DateMessage[this->CountDateMessage].Month = n[0];
			this->DateMessage[this->CountDateMessage].Day = n[1];
			this->DateMessage[this->CountDateMessage].Hour = n[2];
			this->DateMessage[this->CountDateMessage].Minutes = n[3];
			strcpy(DateMessage[this->CountDateMessage].Message,str);
			this->CountDateMessage++;
		}
		if(Flag == 2)
		{
			if(this->CountDateMessage == MAX_ALERT_SYSTEM_DAY) break;
			int n[2];
			char str[100];
			sscanf(Buff, "%d %d \"%[^\"]\"", &n[0], &n[1], &str);
			this->EveryDayMessage[this->CountEveryDayMessage].Hour = n[0];
			this->EveryDayMessage[this->CountEveryDayMessage].Minutes = n[1];
			strcpy(EveryDayMessage[this->CountEveryDayMessage].Message,str);
			this->CountEveryDayMessage++;
		}
		if(Flag == 3)
		{
			if(this->CountDateMessage == MAX_ALERT_SYSTEM_INTERVAL) break;
			int n;
			char str[100];
			sscanf(Buff, "%d \"%[^\"]\"", &n, &str);
			this->IntervalMessage[this->CountIntervalMessage].Interval = n * 60;
			strcpy(IntervalMessage[this->CountIntervalMessage].Message,str);
			this->CountIntervalMessage++;
		}

		//this->m_iNextNoticeTime = 0;

		if(Flag == 4)
		{
			if(this->m_iNoticeCount == MAX_ALERT_SYSTEM_INTERVAL) break;
			int n;
			char str[100];
			sscanf(Buff, "%d \"%[^\"]\"", &n, &str);
			this->NoticeMessage[this->m_iNoticeCount].Interval = n * 60;
			strcpy(NoticeMessage[this->m_iNoticeCount].Message,str);
			this->m_iNoticeCount++;
		}

	}
	fclose(file);
}
void cAlertSystem::PlayMessage(int id, int type)
{
	switch (type)
	{
	case DateAlert:
		MessaageAllGlobal(this->DateMessage[id].Message);
		break;
	case EveryDayAlert:
		MessaageAllGlobal(this->EveryDayMessage[id].Message);
		break;
	case IntervalAlert:
		MessaageAllGlobal(this->IntervalMessage[id].Message);
		break;
	case NoticeAlert:
		MessaageAllGlobal(this->NoticeMessage[id].Message);
		break;
	}
}
void cAlertSystem::TickTime()
{
	if (!this->Enable) return;
	SYSTEMTIME t;
	GetLocalTime(&t);
	int i;
	for (i = 0; i < this->CountDateMessage; i++)
	{
		if(t.wDay == this->DateMessage[i].Day && t.wMonth == this->DateMessage[i].Month && t.wHour == this->DateMessage[i].Hour && t.wMinute == this->DateMessage[i].Minutes && 		
#if(NEWTIMEREX)
			g_TimerEx.GetSecond() == 00)
#else		
			t.wSecond == 00)
#endif
		{
				this->PlayMessage(i,DateAlert);
		}
	}
	for (i = 0; i < this->CountEveryDayMessage; i++)
	{
		if( t.wHour == this->EveryDayMessage[i].Hour && t.wMinute == this->EveryDayMessage[i].Minutes &&
#if(NEWTIMEREX)
			g_TimerEx.GetSecond() == 00)
#else		
			t.wSecond == 00)
#endif
		{
				this->PlayMessage(i,EveryDayAlert);
		}
	}
	for (i = 0; i < this->CountIntervalMessage; i++)
	{
		if(this->IntervalMessage[i].Interval <= this->Interval[i])
		{
				this->PlayMessage(i,IntervalAlert);
				this->Interval[i] = 0;
		}
		else
		{
			this->Interval[i]++;
		}
	}

	if(this->m_iNoticeCount > 0)
	{
		this->m_iNotickeTick++;
		if(this->m_iNotickeTick > this->NoticeMessage[this->m_iNoticeID].Interval)
		{
			this->PlayMessage(this->m_iNoticeID, NoticeAlert);

			this->m_iNoticeID++;
			if(this->m_iNoticeID >= this->m_iNoticeCount)
			{
				this->m_iNoticeID = 0;
			}

			this->m_iNotickeTick = 0;
		}
	}
}

