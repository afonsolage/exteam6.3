#include "stdAfx.h"

#define MAX_ALERT_SYSTEM_DATE 20
#define MAX_ALERT_SYSTEM_DAY 20
#define MAX_ALERT_SYSTEM_INTERVAL 20
#define ALERT_SYSTEM_DIR "..\\Data\\ExData\\AlertSystem.ini"

enum TypesAlert
{   DateAlert,
	EveryDayAlert,
	IntervalAlert,
	NoticeAlert,
};
class cAlertSystem
{
private:
	int Enable;
	int CountDateMessage;
	int CountEveryDayMessage;
	int CountIntervalMessage;
	int Interval[MAX_ALERT_SYSTEM_INTERVAL];
	struct
	{
		char Message[50];
		int Month;
		int Day;
		int Hour;
		int Minutes;
	}DateMessage[MAX_ALERT_SYSTEM_DATE];
	struct
	{
		char Message[50];
		int Hour;
		int Minutes;
	}EveryDayMessage[MAX_ALERT_SYSTEM_DAY];
	struct
	{
		char Message[50];
		int Interval;
	}IntervalMessage[MAX_ALERT_SYSTEM_INTERVAL];

	struct 
	{
		char Message[50];
		int Interval;
	} NoticeMessage[MAX_ALERT_SYSTEM_INTERVAL];
	int m_iNoticeCount;
	int m_iNotickeTick;
	//int m_iNextNoticeTime;
	int m_iNoticeID;

public:
	void Load();
	void PlayMessage(int id, int type);
	void TickTime();
	

};

extern cAlertSystem AlertSystem;