#include "StdAfx.h"
#include "Manager.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "GameMain.h"
#include "ExLicense.h"

#if(CUSTOM_MANAGER)

CManager g_Manager;

CManager::CManager()
{
	this->m_DarkRevenAttackBlock.clear();
}

CManager::~CManager()
{
}

void CManager::Load()
{
	if(g_ExLicense.CheckUser(eExUB::Local) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || 
		g_ExLicense.CheckUser(eExUB::Gredy2) || 
		g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		this->m_DarkRevenAttackBlock.clear();

		this->Read(gDirPath.GetNewPath("ExData\\Manager.dat"));
	}
}

void CManager::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if(SMDFile == NULL)
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), filename);
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

		if(iType != 0)
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

				DARKREVAN_ATTACK_BLOCK List;

				List.Map = (int)TokenNumber;

				this->m_DarkRevenAttackBlock.push_back(List);
			}
		}
	}

	fclose(SMDFile);

	LogAdd("%s file load!", filename);
}

#endif