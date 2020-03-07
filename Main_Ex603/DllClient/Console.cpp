#include "stdafx.h"
#include "Console.h"
// -----------------------------------------------------------------------
cConsole gConsole;
// -----------------------------------------------------------------------
void cConsole::InitCore()
{
#ifdef exCONSOLE
	AllocConsole();
	SetConsoleTitleA("Multi Season");
	setlocale(LC_ALL, "");
	this->Output(cMAGENTA,"###################################################################");
	this->Output(cYELLOW,"\t\t\tDev. Multi Season");
	this->Output(cYELLOW,"\t\t\tDeveloper: DangeR | AfonsoLage");
	this->Output(cMAGENTA,"###################################################################");
#endif
}
// -----------------------------------------------------------------------
void cConsole::Output(int Color , const char* Format, ...)
{
#ifdef exCONSOLE
	SYSTEMTIME Time;
	GetLocalTime(&Time);
	// ----
	char Message[1024];
	char MessageOutPut[2048];
	DWORD dwBytes;
	// ----
	HANDLE Handle		 = GetStdHandle(STD_OUTPUT_HANDLE);
	char CorrectDate[11] = {0};
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(Message , Format , pArguments);
	va_end(pArguments);
	// ----
	sprintf_s(CorrectDate , "[%02d:%02d:%02d]" , Time.wHour , Time.wMinute , Time.wSecond);
	// ----
	sprintf_s(MessageOutPut , "%s %s\n" , CorrectDate , Message);
	// ----
	switch(Color)
	{
	case cRED:		SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_INTENSITY);	break;
	case cGREEN:	SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);	break;
	case cBLUE:		SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);	break;
	case cCYAN:		SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);break;
	case cYELLOW:	SetConsoleTextAttribute(this->Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);	break;
	case cMAGENTA:	SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);	break;
	case cGREY:		SetConsoleTextAttribute(this->Handle(FALSE),FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);	break;
	}
	// ----
	WriteFile(Handle , MessageOutPut , strlen(MessageOutPut) , &dwBytes , NULL);
#endif
}
// -----------------------------------------------------------------------
HANDLE cConsole::Handle(BOOL gImput)
{
	if(gImput == TRUE)
	{
		return GetStdHandle(STD_INPUT_HANDLE);
	}
	// ----
	else
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
}
// -----------------------------------------------------------------------
//extern cConsole Console;
// -----------------------------------------------------------------------