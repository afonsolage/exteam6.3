#pragma once

#include "StdAfx.h"
#include "BanSystem.h"
#include "DBSockMng.h"
#include "user.h"
#include "..\\include\\ReadScript_ex.h"
#include "GameMain.h"
#include "ExLicense.h"

#if(DEV_BANSYSTEM)

CBanSystem g_BanSystem;

CBanSystem::CBanSystem()
{
	this->m_HddData.clear();
}

CBanSystem::~CBanSystem()
{
}

void CBanSystem::Load()
{
	this->Enable = 0;

	this->m_HddData.clear();

	if(g_ExLicense.CheckUser(eExUB::Gredy) || 
	   g_ExLicense.CheckUser(eExUB::GredyLocal) || 
	   g_ExLicense.CheckUser(eExUB::Gredy2) || 
	   g_ExLicense.CheckUser(eExUB::Escalate))
	{
		this->Read(gDirPath.GetNewPath("ExData\\BanChatHdd.dat"));
	}
}

void CBanSystem::Read(char* filename)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 1, filename);
}

bool CBanSystem::Chat(int aIndex)
{
	if(!this->Enable)
	{
		return true;
	}	

	for(int i = 0; i < this->m_HddData.size(); i++)
	{
		BANHDD_DATA & ritem = this->m_HddData[i];

		if(ritem.Hdd == gObj[aIndex].hdd_id && ritem.Time > 0 && ritem.Type == 1)
		{
			return false;
		}
	}

	return true;
}

bool CBanSystem::Player(int aIndex)
{
	if(!this->Enable)
	{
		return true;
	}	

	for(int i = 0; i < this->m_HddData.size(); i++)
	{
		BANHDD_DATA & ritem = this->m_HddData[i];

		if(ritem.Hdd == gObj[aIndex].hdd_id && ritem.Time > 0 && ritem.Type == 0)
		{
			return false;
		}
	}

	return true;
}

void CBanSystem::DSReqSelect()
{
	if(!this->Enable)
	{
		return;
	}

	this->m_HddData.clear();

	PMSG_REQ_BANSYSTEM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x20, sizeof(pMsg));
	pMsg.Result = 1;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CBanSystem::DSAnsSelect(PMSG_SELECT_BANSYSTEM* lpMsg)
{
	BANHDD_DATA list;
	memcpy(list.Name, lpMsg->Name, sizeof(list.Name));
	list.Hdd = lpMsg->Hdd;
	list.Time = lpMsg->Time;
	list.Type = lpMsg->Type;
	this->m_HddData.push_back(list);
}

void CBanSystem::DSReqInsert(char* Name, DWORD Hdd, DWORD Time, DWORD Type)
{
	if(!this->Enable)
	{
		return;
	}

	BANHDD_DATA list;
	memcpy(&list.Name, Name, sizeof(list.Name));
	list.Hdd = Hdd;
	list.Time = Time;
	list.Type = Type;
	this->m_HddData.push_back(list);

	PMSG_INSERT_BANSYSTEM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x21, sizeof(pMsg));
	memcpy(&pMsg.Name, Name, sizeof(pMsg.Name));
	pMsg.Hdd = Hdd;
	pMsg.Time = Time;
	pMsg.Type = Type;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CBanSystem::DSReqDelete(char* Name)
{
	if(!this->Enable)
	{
		return;
	}

	PMSG_DELETE_BANSYSTEM pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x22, sizeof(pMsg));
	memcpy(&pMsg.Name, Name, sizeof(pMsg.Name));
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);

	for(int i = 0; i < this->m_HddData.size(); i++)
	{
		if(!strcmp(this->m_HddData[i].Name, Name))
		{
			this->m_HddData.erase(this->m_HddData.begin()+i);
			break;
		}
	}

}

void CBanSystem::Run()
{
	for(int i = 0; i < this->m_HddData.size(); i++)
	{
		BANHDD_DATA & ritem = this->m_HddData[i];

		if(ritem.Time > 0)
		{
			if(ritem.Hdd != NULL)
			{
				ritem.Time--;

				if(ritem.Time <= 0)
				{
					this->DSReqDelete(ritem.Name);
				}
			}
		}
	}
}

#endif

