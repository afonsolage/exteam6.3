// 화면이나 파일에 쓰는 로그 처리를 담당한다.
// Date : 2000/07 - 
// Code : 송길섭
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <TIME.H>
#include "LogProc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static char m_szLogFileName[256];
static FILE *	logfp=NULL;

#if(NEW_WIN)
#define MAXLOGTEXT		20
#define MAXLOGTEXTC		108
#else
#define MAXLOGTEXT		30
#define MAXLOGTEXTC		80
#endif

char  LogText[MAXLOGTEXT][MAXLOGTEXTC];
short LogTextLength[MAXLOGTEXT];
BYTE  LogTextViewType[MAXLOGTEXT];

//WriteLog

int gLogOutType		= GetPrivateProfileInt("Connect", "WriteLog", 1, ".\\Connect.ini");
int gLogDateChange	= 0;

void LogAddFuncVoid(char *szlog, ...);
void LogAddHeadHexFuncVoid(int type, char *data, int len);
void LogTextPaintProcVoid(HWND hWnd);
BOOL LogDateChange();
void LogDataSet();

void LogAddTimeDateFunc(char *szlog, ...);
void LogAddTimeDateVoid(char *szlog, ...);

void LogAddFunc(char *szlog, ...);
void LogAddFuncColor(BYTE Color, char *szlog, ...);
void LogAddHeadHexFunc(int type, char *data, int len);

void (*LogAdd)(char *szlog, ...);
void (*LogAddC)(BYTE Color, char *szlog, ...);
void (*LogAddTD)(char *szlog, ...);
//void (*LogAddHeadHex)(char *head,char *data, int);

void (*LogTextPaint)(HWND hWnd);
void LogTextPaintProc(HWND hWnd);

CRITICAL_SECTION LogCritical;	// Critical Section For LOG

void LogInit(int logprint)
{
	__try
	{
		int n;
		InitializeCriticalSection(&LogCritical);

		if( logprint )
		{
			LogAdd = LogAddFunc;
			LogAddC = LogAddFuncColor;
			LogAddTD = LogAddTimeDateFunc;
			//LogAddHeadHex = LogAddHeadHexFunc;
			LogTextPaint = LogTextPaintProc;
			for( n=0; n<MAXLOGTEXT; n++)
			{
				memset(LogText[n], 0, MAXLOGTEXTC);
				LogTextLength[n] = 0;
				LogTextViewType[n] = 0;
			}

			if( gLogOutType == 0 ) return; // 파일까지 출력할땐 
		
			LogDataSet();
		}
		else
		{
			LogAdd = LogAddFuncVoid;
			//LogAddHeadHex = LogAddHeadHexFuncVoid;
			LogTextPaint = LogTextPaintProcVoid;
			LogAddTD = LogAddTimeDateVoid;
	
		}
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}	
}

int LogMYear, LogMonth, LogMDay;

void LogDataSet()
{
	__try
	{
		char		szTemp[50];
		struct tm * today;
		time_t		ltime;
	
		time( &ltime );
		today = localtime( &ltime );
	
		today->tm_year += 1900;

		LogMYear = today->tm_year;
		LogMonth = today->tm_mon+1;
		LogMDay  = today->tm_mday;

		wsprintf(szTemp, "log\\%02d%02d%02d.log",LogMYear, LogMonth,LogMDay);

		if( logfp!=NULL ) 
		{
			fclose(logfp);
			logfp = NULL;
		}
		logfp = fopen(szTemp, "a+t");
		if( logfp == NULL )
		{
			LogAdd("error-L1 : Log write error.");
		}
		strcpy(m_szLogFileName, szTemp);
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}
}

BOOL LogDateChange()
{
	bool EntCrit = false;

	__try
	{
		char szTemp[20];
		struct tm *today;
		time_t ltime;
	
		time( &ltime );
		today = localtime( &ltime );
	
		today->tm_year += 1900;
		today->tm_mon  += 1;

		if( (today->tm_year <= LogMYear) && 
			(today->tm_mon  <= LogMonth) &&
			(today->tm_mday <= LogMDay) )
		{
			return FALSE;
		}
		LogMYear = today->tm_year;
		LogMonth = today->tm_mon;
		LogMDay  = today->tm_mday;

		wsprintf(szTemp, "log\\%02d%02d%02d.log",LogMYear, LogMonth,LogMDay);

		EnterCriticalSection(&LogCritical);
		EntCrit = true;
		if( logfp!=NULL ) 
		{
			fclose(logfp);
			logfp = NULL;
		}
		logfp = fopen(szTemp, "a+t");
		if( logfp == NULL )
		{
			MsgBox("error-L1 : Log write error.");
		}
		strcpy(m_szLogFileName, szTemp);

		LeaveCriticalSection(&LogCritical);
		EntCrit = false;
		return TRUE;

	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
		if(EntCrit == true)
		{
			LeaveCriticalSection(&LogCritical);
		}
		return FALSE;
	}
}

int m_cline=0;

void LogTextAdd(BYTE type, char *msg, int len)
{
	__try
	{
		if( len > MAXLOGTEXTC-1 ) len = MAXLOGTEXTC-1;

		m_cline++;
		if( m_cline > MAXLOGTEXT-1) m_cline = 0;

		LogText[m_cline][0]			= '\0';
	
		memcpy(LogText[m_cline], msg, len);

		LogText[m_cline][len]		= LogText[m_cline][len+1] = '\0';
		LogTextLength[m_cline  ]	= len;
		LogTextViewType[m_cline]	= type;
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}
}

void LogAddFuncVoid(char *szlog, ...)
{
	return;
}

void LogAddTimeDateVoid(char *szlog, ...)
{
	return;
}

void LogAddFunc(char *szlog, ...)
{	
#ifdef DEBUG_LOG
	return;
#endif

	bool EntCrit = false;

	__try
	{
		char szBuffer[1024]=""; //wz doubled buffer :)
		va_list		pArguments;

		va_start(pArguments, szlog);
		vsprintf(szBuffer, szlog, pArguments);
		va_end(pArguments);
		LogTextAdd(0, szBuffer, strlen(szBuffer));

		if( gLogOutType == 0 ) 
		{
			return;
		}
		else
		{
			if( logfp == NULL ) 
			{
				return;
			}
			EnterCriticalSection(&LogCritical);
			EntCrit = true;
			fprintf(logfp, "%s\n",szBuffer);
			LeaveCriticalSection(&LogCritical);
			EntCrit = false;
		}
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
		if(EntCrit == true)
		{
			LeaveCriticalSection(&LogCritical);
		}
	}
}

void LogAddFuncColor(BYTE Color, char *szlog, ...)
{	
#ifdef DEBUG_LOG
	return;
#endif
	bool EntCrit = false;
	__try
	{
		char		szBuffer[1024]="";
		va_list		pArguments;

		va_start(pArguments, szlog);
		vsprintf(szBuffer, szlog, pArguments);
		va_end(pArguments);
		LogTextAdd(Color, szBuffer, strlen(szBuffer));

		if( gLogOutType == 0 ) return;
		if( logfp == NULL ) 
		{
			return;
		}
		EnterCriticalSection(&LogCritical);
		EntCrit = true;
		fprintf(logfp, "%s\n",szBuffer);
		LeaveCriticalSection(&LogCritical);
		EntCrit = false;
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}
}

void LogAddTimeDateFunc(char *szlog, ...)
{	
#ifdef DEBUG_LOG
	return;
#endif
	bool EntCrit = false;
	__try
	{
#if(NEW_WIN)
		char		szBuffer[1024]="";
		va_list		pArguments;
		char		tmpbuf[512];
		va_start(pArguments, szlog);
		vsprintf(szBuffer, szlog, pArguments);
		va_end(pArguments);

		struct tm * today;
		time_t		ltime;
		time( &ltime );
		today = localtime( &ltime );
		if( today->tm_hour >= 12 )
		{
			today->tm_hour -= 12;
		}
		if( today->tm_hour == 0 )
		{
			today->tm_hour = 12;
		}
		wsprintf(tmpbuf, "%.8s ",asctime( today ) + 11 );

		strcat(tmpbuf, szBuffer);
		LogTextAdd(0, szBuffer, strlen(szBuffer));

		if(gLogOutType == 0)
		{
			return;
		}
		if(logfp == NULL) 
		{
			return;	
		}
		EnterCriticalSection(&LogCritical);
		EntCrit = true;
		fprintf(logfp, "%s\n",tmpbuf);
		LeaveCriticalSection(&LogCritical);
		EntCrit = false;
#else
		char		szBuffer[1024]="";
		va_list		pArguments;
		struct tm * today;
		time_t		ltime;
		char		tmpbuf[512], ampm[] = "a";
		time( &ltime );
		today = localtime( &ltime );
		if( today->tm_hour >= 12 )
		{
			strcpy( ampm, "p" );
			today->tm_hour -= 12;
		}
		if( today->tm_hour == 0 )
		{
			today->tm_hour = 12;
		}
		wsprintf(tmpbuf, "%.8s%s ",asctime( today ) + 11, ampm );
		va_start(pArguments, szlog);
		vsprintf(szBuffer, szlog, pArguments);
		va_end(pArguments);
		strcat(tmpbuf, szBuffer);
		LogTextAdd(0, tmpbuf, strlen(tmpbuf));
		if( gLogOutType == 0 ) return;
		if( logfp == NULL ) 
		{
			//LogAdd("error-L2 : 파일을 생성할수 없습니다. %s %d",__FILE__, __LINE__);
			return;	
		}
		fprintf(logfp, "%s\n",tmpbuf);
#endif
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
		if(EntCrit == true)
		{
			LeaveCriticalSection(&LogCritical);
		}
	}
}

void LogAddHeadHexFuncVoid(int type, char *data, int len)
{
	return;
}

void LogAddHeadHexFunc(int type, char *data, int len)
{
	bool EntCrit = false;
	__try
	{
		LogTextAdd(type, data, len);

		if( gLogOutType == 0 ) return;
		if( logfp == NULL ) 
		{
			return;
		}	
		if( logfp == NULL ) 
		{
			return;	
		}

		EnterCriticalSection(&LogCritical);
		EntCrit = true;

		switch(type)
		{
		case 2  : fprintf(logfp, "Send:[%d] : (", len);	break;
		case 3  : fprintf(logfp, "FDWrite:[%d] : (", len);	break;
		case 4  : fprintf(logfp, "Recv:[%d] : (", len);	break;
		default : fprintf(logfp, "%d[%d] : (", type, len);	break;
		}
	
		for( int n=0; n<len; n++)
		{
			fprintf(logfp, "0x%02x ",(BYTE)data[n]);
		}
		fprintf(logfp, ")\n");
		LeaveCriticalSection(&LogCritical);
		EntCrit = false;
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
		if(EntCrit == true)
		{
			LeaveCriticalSection(&LogCritical);
		}
	}
}

void LogTextClear()
{
	__try
	{
		int n;
		for( n=0; n<MAXLOGTEXT; n++)
		{
			memset(LogText[n], 0, MAXLOGTEXTC);
			LogTextLength[n] = 0;
			LogTextViewType[n] = 0;
		}	
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}
}

void LogTextPaintProcVoid(HWND hWnd)
{
	return;
}

void LogTextPaintProc(HWND hWnd)
{
	__try
	{
		HDC	hdc;
		hdc = GetDC(hWnd);
		int total = MAXLOGTEXT;
		int n = m_cline;
#if(NEW_WIN)
		int iOldBkMode = SetBkMode(hdc, TRANSPARENT);
		while( total-- )
		{
			switch( LogTextViewType[n] )
			{
			case 2:
				SetTextColor(hdc, RGB(180, 30, 30));
				break;
			case 3:
				SetTextColor(hdc, RGB(0, 100, 0));
				break;
			case 4:
				SetTextColor(hdc, RGB(130, 170, 190));
				break;
			case 5:
				SetTextColor(hdc, RGB(155, 0, 0));
				break;
			case 6:
				SetTextColor(hdc, RGB(0, 0, 100));
				break;
			case 7:
				SetTextColor(hdc, RGB(210, 30, 150));
				break;
			default:
				SetTextColor(hdc, RGB(32, 240, 190));
				break;
			}
			if( strlen(LogText[n]) > 1 )
			{
				TextOutA(hdc, 10, 90+(total*15), LogText[n], strlen(LogText[n]));
			}
			n--;
			if( n < 0 )
			{
				n = MAXLOGTEXT-1;
			}
		}
		SetBkMode(hdc, iOldBkMode);
#else
		while( total-- )
		{
			switch( LogTextViewType[n] )
			{
			case 2  : SetTextColor(hdc, RGB(255,0,0)); break;
			case 3  : SetTextColor(hdc, RGB(0,100,0)); break;
			case 4  : SetTextColor(hdc, RGB(0,0,255)); break;
			case 5  : SetTextColor(hdc, RGB(155,0,0)); break;
			case 6  : SetTextColor(hdc, RGB(0,0,100)); break;
			default : SetTextColor(hdc, RGB(0,0,0)); break;
			}
			if( strlen(LogText[n]) > 1 )
			{
				TextOutA(hdc, 0, 68+(total*15), LogText[n], strlen(LogText[n]));
			}
			n--;
			if( n < 0 )
			{
				n = MAXLOGTEXT-1;
			}
		}
#endif
		ReleaseDC(hWnd, hdc);
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}
}

char * LogGetFileName()
{
#ifdef _DEBUG
	return m_szLogFileName;
#endif
	return NULL;
}

void LogClose()
{
	__try
	{
		if( logfp != NULL )
		{
			fclose(logfp);
		}
		DeleteCriticalSection(&LogCritical);
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}
}

void MsgBox(char *szlog, ...)
{	
	__try
	{
		char szBuffer[512]="";
		va_list		pArguments;

		va_start(pArguments, szlog);
		vsprintf(szBuffer, szlog, pArguments);
		va_end(pArguments);
	
		MessageBox(NULL, szBuffer, "error", MB_OK);
	}__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}
}

