#include "StdAfx.h"
#include "DonateManager.h"
#include "GameMain.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "ExLicense.h"

#if(CUSTOM_DONATEMANAGER)

CDonateManager g_DonateManager;

CDonateManager::CDonateManager()
{
	this->m_PetData.clear();
	this->m_ExpData.clear();
}

CDonateManager::~CDonateManager()
{
}

void CDonateManager::Load()
{
	if( g_ExLicense.CheckUser(eExUB::MU2Play) || 
		g_ExLicense.CheckUser(eExUB::Escalate) ||
		g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		this->m_PetData.clear();
		this->m_ExpData.clear();
		this->Read(gDirPath.GetNewPath("ExData\\DonateManager.dat"));
	}
}

void CDonateManager::Read(char* filename)
{
	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MsgBox("[Donate Manager] %s file not found", filename);
		return;
	}

	int iType = -1;

	while(true)
	{
		Token = GetToken();

		if( Token == END )
		{
			break;
		}

		iType = TokenNumber;

		while(true)
		{
			if(iType == 0)
			{
				Token = GetToken();

				if(strcmp("end", TokenString) == 0)
				{
					break;
				}

				IMPERIALPET_DATA list;

				list.Name[10] = 0;
				memcpy(list.Name, TokenString, 10);

				Token = GetToken();
				int iType = (short)TokenNumber;

				Token = GetToken();
				int iIndex = (short)TokenNumber;

				list.Pet = ITEMGET(iType, iIndex);

				this->m_PetData.push_back(list);
			}
			else if(iType == 1)
			{
				Token = GetToken();

				if(strcmp("end", TokenString) == 0)
				{
					break;
				}

				EXPCHAR_DATA list;

				list.Name[10] = 0;
				memcpy(list.Name, TokenString, 10);

				Token = GetToken();
				list.PlusExpPercent = (short)TokenNumber;

				this->m_ExpData.push_back(list);
			}
		}	
	}

	fclose(SMDFile);
	LogAdd("%s file load!", filename);
}

bool CDonateManager::CheckItem(int aIndex)
{
	if(g_ExLicense.CheckUser(eExUB::MU2Play) || g_ExLicense.CheckUser(eExUB::Escalate) || g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		if(!OBJMAX_RANGE(aIndex))
		{
			return true;
		}

		LPOBJ lpUser = &gObj[aIndex];

		for(int i = 0; i < this->m_PetData.size(); i++)
		{
			if(lpUser->Name[0] == this->m_PetData[i].Name[0])
			{
				if(!strcmp(lpUser->Name, this->m_PetData[i].Name))
				{
					if(this->m_PetData[i].Pet == lpUser->pInventory[8].m_Type)
					{
						return true;
					}
				}	
			}
		}
	}

	return false;
}

void CDonateManager::CheckExp(int aIndex, long long &exp)
{
	if(g_ExLicense.CheckUser(eExUB::MU2Play)|| g_ExLicense.CheckUser(eExUB::Escalate) || g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		if(!OBJMAX_RANGE(aIndex))
		{
			return;
		}

		LPOBJ lpUser = &gObj[aIndex];

		for(int i = 0; i < this->m_ExpData.size(); i++)
		{
			if(lpUser->Name[0] == this->m_ExpData[i].Name[0])
			{
				if(!strcmp(lpUser->Name, this->m_ExpData[i].Name))
				{
					exp += (exp * this->m_ExpData[i].PlusExpPercent) / 100;
					return;
				}	
			}
		}
	}
}

#endif