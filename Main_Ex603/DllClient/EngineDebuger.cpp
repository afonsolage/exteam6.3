#include "stdafx.h"
#include "ReadScript.h"
#include "Import.h"
#include "EngineDebuger.h"

#if(ENGINE_DEBUGER)

CEngineDebuger g_EngineDebuger;

CEngineDebuger::CEngineDebuger()
{
	this->Init();
}

CEngineDebuger::~CEngineDebuger()
{
}

void CEngineDebuger::Init()
{
	this->m_Enable = false;
}

void CEngineDebuger::Load()
{
	this->ConsoleInit();

	this->Read(".\\Interface.dat");
}

void CEngineDebuger::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(SMDFile == NULL)
	{
		MessageBox(pGameWindow, filename, "LOAD FILE ERROR", NULL);
		return;
	}

	SMDToken Token;

	int iType = -1;

	while(true)
	{
		Token = GetToken();

        if(Token == END)
		{
            break;
		}

		iType = (int)TokenNumber;

		if(iType < 0 || iType > 1)
		{
			break;
		}

		while(true)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				this->m_Enable = (int)TokenNumber;
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(!strcmp("end", TokenString))
				{
					break;
				}

				INTERFACE_DATA * pList = &this->m_Draw[this->m_LoadCount];

				pList->TypeDraw = TokenNumber;

				Token = GetToken();
				pList->Index = TokenNumber;

				Token = GetToken();
				pList->PosX = TokenNumber;

				Token = GetToken();
				pList->PosY = TokenNumber;

				Token = GetToken();
				pList-> Width = TokenNumber;

				Token = GetToken();
				pList->Height = TokenNumber;

				Token = GetToken();
				memcpy(pList->Path, TokenString, sizeof(pList->Path));

				this->m_LoadCount++;
			}
		}
	}

	fclose(SMDFile);
}
	
void CEngineDebuger::LoadIMG()
{
	for(int i = 0; i < this->m_LoadCount; i++)
	{
		INTERFACE_DATA * pList = &this->m_Draw[i];
	}
}

void CEngineDebuger::ConsoleInit()
{
	AllocConsole();
	SetConsoleTitleA("ENGINE CONSTRUCTOR");
	setlocale(LC_ALL, "Russian");
	this->ConsolePrint(eCONSOLE_GREEN, "###################################################################");
	this->ConsolePrint(eCONSOLE_YELLOW, "\t\t\tENGINE CONTROLLER\t\t\t");
	this->ConsolePrint(eCONSOLE_YELLOW, "\t\t\tENGINE DEBUGER\t\t\t");
	this->ConsolePrint(eCONSOLE_YELLOW, "\t\t\tENGINE INFORMATION");
	this->ConsolePrint(eCONSOLE_GREEN, "###################################################################");
}

HANDLE CEngineDebuger::ConsoleHandle(BOOL gImput)
{
	if(gImput == TRUE)
	{
		return GetStdHandle(STD_INPUT_HANDLE);
	}

	else
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
}

void CEngineDebuger::ConsolePrint(DWORD Color, char* Format, ...)
{
	SYSTEMTIME Time;
	GetLocalTime(&Time);

	char Message[1024];
	char MessageOutPut[2048];
	DWORD dwBytes;

	HANDLE Handle		 = GetStdHandle(STD_OUTPUT_HANDLE);
	char CorrectDate[11] = {0};

	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf_s(Message , Format , pArguments);
	va_end(pArguments);

	sprintf_s(CorrectDate , "[%02d:%02d:%02d]" , Time.wHour , Time.wMinute , Time.wSecond);

	sprintf_s(MessageOutPut , "%s %s\n" , CorrectDate , Message);
	
	switch(Color)
	{
	case eCONSOLE_RED:		SetConsoleTextAttribute(this->ConsoleHandle(FALSE), FOREGROUND_RED | FOREGROUND_INTENSITY);	break;
	case eCONSOLE_GREEN:	SetConsoleTextAttribute(this->ConsoleHandle(FALSE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);	break;
	case eCONSOLE_BLUE:		SetConsoleTextAttribute(this->ConsoleHandle(FALSE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);	break;
	case eCONSOLE_CYAN:		SetConsoleTextAttribute(this->ConsoleHandle(FALSE), FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);break;
	case eCONSOLE_YELLOW:	SetConsoleTextAttribute(this->ConsoleHandle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);	break;
	case eCONSOLE_MAGENTA:	SetConsoleTextAttribute(this->ConsoleHandle(FALSE),FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);	break;
	case eCONSOLE_GREY:		SetConsoleTextAttribute(this->ConsoleHandle(FALSE),FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);	break;
	}

	WriteFile(Handle , MessageOutPut , strlen(MessageOutPut) , &dwBytes , NULL);
}

void CEngineDebuger::KeyBoard(DWORD wParam)
{

}

void CEngineDebuger::KeyMouse(DWORD wParam)
{

}

void CEngineDebuger::GameDraw()
{

}

#endif