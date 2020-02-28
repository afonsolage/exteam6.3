#pragma once

#include "stdafx.h"

struct TEXTCHANGE_DATA
{
	char Text[64];
	char Text2[64];
};

class CText 
{
public:
		 CText();
		~CText();

	void Init();
	void Load();
	void Read(char* filename);
	void ReadString(char* filename);

	LPCSTR Change(LPCSTR Text);

	TEXTCHANGE_DATA m_change[1000];
	int m_Count;

	char m_String[1000][64];
};

extern CText g_Text;