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
	char* Change(char* Text);

	int m_Count;
	TEXTCHANGE_DATA m_change[1000];
};

extern CText g_Text;