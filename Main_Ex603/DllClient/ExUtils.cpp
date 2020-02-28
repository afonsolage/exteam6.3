#include "stdafx.h"
#include "ExUtils.h"
#include "Import.h"
#include "ExText.h"

ExUtils g_ExUtils;

void ExUtils::Load()
{

}


//char* GetDate(DWORD Time, int Type)
//{
//
//	char BuffDate[256] = { 0 };
//
//	time_t t = Time;
//	tm* m = gmtime(&t);
//
//	if(m->tm_yday > 0)
//	{
//		if(Type == 0)
//		{
//			sprintf(BuffDate, "Day: %2d Hour: %2d Minutes: %2d Seconds: %2d",m->tm_yday,m->tm_hour,m->tm_min,m->tm_sec);
//		}
//		else if(Type == 1)
//		{
//			sprintf(BuffDate, "Day: %2d Hour: %2d Min: %2d",m->tm_yday,m->tm_hour,m->tm_min);
//		}
//		else
//		{
//			sprintf(BuffDate, "Day: %2d Hour: %2d",m->tm_yday,m->tm_hour);
//		}		
//		return BuffDate;
//	}
//	else if(m->tm_hour > 0)
//	{
//		if(Type == 0)
//		{
//			sprintf(BuffDate, "Hour: %2d Minutes: %2d Seconds: %2d",m->tm_hour,m->tm_min,m->tm_sec);
//		}
//
//		else if(Type == 1)
//		{
//			sprintf(BuffDate, "Hour: %2d Min: %2d",m->tm_hour,m->tm_min);
//		}
//		else
//		{
//			sprintf(BuffDate, "Hour: %2d",m->tm_hour);
//		}		
//		return BuffDate;
//	}
//	else if(m->tm_min > 0)
//	{
//		if(Type == 0)
//		{
//			sprintf(BuffDate, "Minutes: %2d Seconds: %2d",m->tm_min,m->tm_sec);
//		}
//		else
//		{
//			sprintf(BuffDate, "Min: %2d",m->tm_min,m->tm_sec);
//		}
//		
//		return BuffDate;
//	}
//	else if(m->tm_sec > 0)
//	{
//		if(Type == 0)
//		{
//			sprintf(BuffDate, "Seconds: %2d",m->tm_sec);
//		}
//		else
//		{
//			sprintf(BuffDate, "Sec: %2d",m->tm_sec);
//		}
//
//		return BuffDate;
//	}
//
//	return "0";
//}

char* GetDate(DWORD Time, int Type)
{

	char BuffDate[256] = { 0 };

	time_t t = Time;
	tm* m = gmtime(&t);

	if(m->tm_yday > 0)
	{
		if(Type == 0)
		{
			sprintf(BuffDate, g_ExText.GetText(166),m->tm_yday,m->tm_hour,m->tm_min,m->tm_sec);
		}
		else if(Type == 1)
		{
			sprintf(BuffDate, g_ExText.GetText(167),m->tm_yday,m->tm_hour,m->tm_min);
		}
		else
		{
			sprintf(BuffDate, g_ExText.GetText(168),m->tm_yday,m->tm_hour);
		}		
		return BuffDate;
	}
	else if(m->tm_hour > 0)
	{
		if(Type == 0)
		{
			sprintf(BuffDate, g_ExText.GetText(169),m->tm_hour,m->tm_min,m->tm_sec);
		}

		else if(Type == 1)
		{
			sprintf(BuffDate, g_ExText.GetText(170),m->tm_hour,m->tm_min);
		}
		else
		{
			sprintf(BuffDate, g_ExText.GetText(171),m->tm_hour);
		}		
		return BuffDate;
	}
	else if(m->tm_min > 0)
	{
		if(Type == 0)
		{
			sprintf(BuffDate, g_ExText.GetText(172),m->tm_min,m->tm_sec);
		}
		else
		{
			sprintf(BuffDate, g_ExText.GetText(173),m->tm_min,m->tm_sec);
		}
		
		return BuffDate;
	}
	else if(m->tm_sec > 0)
	{
		if(Type == 0)
		{
			sprintf(BuffDate, g_ExText.GetText(174),m->tm_sec);
		}
		else
		{
			sprintf(BuffDate, g_ExText.GetText(175),m->tm_sec);
		}

		return BuffDate;
	}

	return "0";
}

void MsgBox(char *szlog, ...)
{
	char szBuffer[512]="";
	va_list pArguments;
	va_start(pArguments, szlog);
	vsprintf(szBuffer, szlog, pArguments);
	va_end(pArguments);
	MessageBox(pGameWindow, szBuffer, "error", MB_OK|MB_APPLMODAL);
}
// ----------------------------------------------------------------------------------------------