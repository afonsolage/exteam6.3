#pragma once

#include "StdAfx.h"

#if(CUSTOM_DONATEMANAGER)

struct IMPERIALPET_DATA
{
	char Name[11];
	short Pet;
};

struct EXPCHAR_DATA
{
	char Name[11];
	short PlusExpPercent;
};

class CDonateManager
{
public:
		 CDonateManager();
		 ~CDonateManager();

	void Load();
	void Read(char* filename);
	bool CheckItem(int aIndex);
	void CheckExp(int aIndex, long long &exp);

	std::vector<IMPERIALPET_DATA>	m_PetData;
	std::vector<EXPCHAR_DATA>		m_ExpData;
};
extern CDonateManager g_DonateManager;

#endif