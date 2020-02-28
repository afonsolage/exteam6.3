#include "Stdafx.h"
#include "Text.h"
#include "ReadScript.h"
#include "ExFunction.h"
#include "Console.h"

CText g_Text;

CText::CText()
{
	this->Init();
}

CText::~CText()
{
}

void CText::Init()
{
	this->m_Count = 0;
	memset(this->m_change, 0, sizeof(this->m_change));
	memset(this->m_String, 0, sizeof(this->m_String));
}

void CText::Load()
{
	this->Init();
	this->Read(".\\Data\\Custom\\Configs\\TextChange.dat");
	this->Read(".\\Data\\Custom\\Configs\\Text.dat");
}

void CText::Read(char* filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		//MessageBoxError("%s - file nor found", filename);
		//ExitProcess(0);
		return;
	}

	int n = 0;

	while(true)
	{
		Token = GetToken();

		if(Token == END || !strcmp("end", TokenString))
		{
			break;
		}

		memcpy(this->m_change[n].Text, TokenString, sizeof(this->m_change[n].Text));

		Token = GetToken();
		memcpy(this->m_change[n].Text2, TokenString, sizeof(this->m_change[n].Text2));

		//gConsole.Output(cGREEN, "%s %s", this->m_change[n].Text, this->m_change[n].Text2);

		n++;
	} 

	this->m_Count = n;

	fclose(SMDFile);	
}

void CText::ReadString(char* filename)
{
	//this->m_String[]
}

LPCSTR CText::Change(LPCSTR Text)
{
	for(int i = 0; i < this->m_Count; i++)
	{
		//gConsole.Output(cGREEN, "%s %s", this->m_change[i].Text, Text);

		if(!strcmp(this->m_change[i].Text, Text))
		{
			return this->m_change[i].Text2;
		}
	}

	return Text;
}