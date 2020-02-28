#include "Stdafx.h"
#include "Text.h"
#include "..\\include\\ReadScript.h"
#include "ExFunction.h"
#include "logproc.h"
#include "GameMain.h"

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
}

void CText::Load()
{
	this->Init();
	this->Read(gDirPath.GetNewPath("ExData\\TextChange.dat"));
}

void CText::Read(char* filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
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

		n++;
	} 

	this->m_Count = n;

	fclose(SMDFile);	
}


char* CText::Change(char* Text)
{
	for(int i = 0; i < this->m_Count; i++)
	{
		if(!strcmp(this->m_change[i].Text, Text))
		{
			return this->m_change[i].Text2;
		}
	}

	return Text;
}