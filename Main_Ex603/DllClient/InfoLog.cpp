#include "stdafx.h"
#include "InfoLog.h"
#include "Interface.h"
#include "Console.h"
#include "ExLicense.h"

#if(CUSTOM_EX_CHAT==TRUE)

CInfoLog g_InfoLog;

CInfoLog::CInfoLog()
{
	this->Init();
}

CInfoLog::~CInfoLog()
{
}

void CInfoLog::Init()
{
	CreateDirectory(".\\InfoLog", NULL);
	CreateDirectory(".\\InfoLog\\Chat", NULL);
	CreateDirectory(".\\InfoLog\\Killers", NULL);
}

void CInfoLog::Load()
{
	this->Init();
}

void CInfoLog::GCChatProc(PMSG_CHATDATA* lpChat)
{
	if( !g_ExLicense.CheckUser(eExUB::Local)  &&  
		!g_ExLicense.CheckUser(eExUB::Gredy)  &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::GredyLocal)&&
		!g_ExLicense.CheckUser(eExUB::Artem) &&
		!g_ExLicense.CheckUser(eExUB::Artem2))
	{
		return;
	}

	strcpy(szMsg, lpChat->chatmsg);
	
	DWORD dwNum = MultiByteToWideChar( CP_UTF8, 0, lpChat->chatmsg, -1, NULL, 0 );

	if(dwNum)
	{
		MultiByteToWideChar( CP_UTF8, 0, szMsg, -1, pwText, dwNum );
		dwNum = WideCharToMultiByte( CP_ACP, 0, pwText, -1, NULL, 0, NULL, NULL );
		WideCharToMultiByte( CP_ACP, 0, pwText, -1, psText, dwNum, NULL, NULL );
	}

	if(lpChat->chatmsg[0] == '~' || lpChat->chatmsg[0] == ']')
	{
		this->Output("Chat", "Message", "[PARTY] [%s] %s", lpChat->chatid, &psText[1]);
	}
	else if(lpChat->chatmsg[0] == '@' && lpChat->chatmsg[1] == '@')
	{
		this->Output("Chat", "Message", "[ALLIANCE] [%s] %s", lpChat->chatid, &psText[2]);
	}
	else if(lpChat->chatmsg[0] == '@')
	{
		this->Output("Chat", "Message", "[GUILD] [%s] %s", lpChat->chatid, &psText[1]);
	}
	else if(lpChat->chatmsg[0] == '$')
	{
		this->Output("Chat", "Message", "[POST] [%s] %s", lpChat->chatid, &psText[7]);
	}
	else if(lpChat->chatmsg[0] == '/')
	{

	}
	else
	{
		this->Output("Chat", "Message", "[STREET] [%s] %s", lpChat->chatid, psText);
	}
}

void CInfoLog::GCChatWhisperRecv(CHAT_WHISPER_EX* lpMsg)
{
	if( !g_ExLicense.CheckUser(eExUB::Local)  &&  
		!g_ExLicense.CheckUser(eExUB::Gredy)  &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::GredyLocal)&&
		!g_ExLicense.CheckUser(eExUB::Artem) &&
		!g_ExLicense.CheckUser(eExUB::Artem2))
	{
		return;
	}

	strcpy(szMsg, lpMsg->Message);
	
	DWORD dwNum = MultiByteToWideChar( CP_UTF8, 0, szMsg, -1, NULL, 0 );

	if( dwNum )
	{
		MultiByteToWideChar( CP_UTF8, 0, szMsg, -1, pwText, dwNum );
		dwNum = WideCharToMultiByte( CP_ACP, 0, pwText, -1, NULL, 0, NULL, NULL );
		WideCharToMultiByte( CP_ACP, 0, pwText, -1, psText, dwNum, NULL, NULL );
	}

	if(lpMsg->Type == 2)
	{
		this->Output("Chat", "Message", "[PRIVATE] [%s] %s", lpMsg->Name, psText);
	}
	else
	{
		this->Output("Chat", "Message", "[POST] [%s] %s", lpMsg->Name, &psText[7]);
	}
}
// ----------------------------------------------------------------------------------------------

void CInfoLog::Output(LPSTR folder, LPSTR filename, LPSTR szMsg, ...)
{
	__try
	{
		va_list argptr;
		int iChrWritten;
		char szLogFileName[260];
		char cBUFFER[512];

		SYSTEMTIME strSystime;

		va_start(argptr, szMsg);
		vsprintf(cBUFFER , szMsg, argptr);
		va_end(argptr);

		GetLocalTime(&strSystime);

		wsprintf(szLogFileName, "InfoLog\\%s\\[%02d.%02d.%04d] %s.txt",
			folder, strSystime.wDay, strSystime.wMonth, strSystime.wYear,
			filename);

		FILE* file = fopen(szLogFileName, "a+");

		if(!file)
		{
			return;
		}
		
		fprintf(file, "[%02d:%02d:%02d] %s\n", strSystime.wHour, strSystime.wMinute, strSystime.wSecond, cBUFFER);
		fclose(file);	
	}
	__except(EXCEPTION_ACCESS_VIOLATION == GetExceptionCode())
	{
	}
}

#endif