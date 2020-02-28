#include "StdAfx.h"
#include "MonsterMsg.h"
#include "GameMain.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "Message.h"
#include "ExLicense.h"
#include "ExFunction.h"

CMonsterMsg g_MonsterMsg;

CMonsterMsg::CMonsterMsg()
{
	this->Init();
}

CMonsterMsg::~CMonsterMsg()
{
}

void CMonsterMsg::Init()
{
	this->m_Data.clear();
}

void CMonsterMsg::Load()
{
	if(!g_ExLicense.CheckUser(eExUB::Local)			&&
	   !g_ExLicense.CheckUser(eExUB::Gredy)			&& 
	   !g_ExLicense.CheckUser(eExUB::Gredy2)		&&
	   !g_ExLicense.CheckUser(eExUB::GredyLocal)	&&
	   !g_ExLicense.CheckUser(eExUB::SILVER1)		&&
	   !g_ExLicense.CheckUser(eExUB::SILVER2)		&&
	   !g_ExLicense.CheckUser(eExUB::MU2Play)		&&
	   !g_ExLicense.CheckUser(eExUB::SILVER_Local)  &&
	   !g_ExLicense.CheckUser(eExUB::Artem)			&&
	   !g_ExLicense.CheckUser(eExUB::Artem2)		&&
	   !g_ExLicense.CheckUser(eExUB::Escalate)		&&
	   !g_ExLicense.CheckUser(eExUB::ArcMu)			&&
	   !g_ExLicense.CheckUser(eExUB::MedoniAndrei)  &&
	   !g_ExLicense.CheckUser(eExUB::mu4you)		&&
	   !g_ExLicense.CheckUser(eExUB::eternalmu)		&&
	   !g_ExLicense.CheckUser(eExUB::NSGames))
	{
		return;
	}

	this->Init();
	this->Read(gDirPath.GetNewPath("ExData\\MonsterMsg.dat"));
}

void CMonsterMsg::Read(char* filename)
{
	SMDFile = fopen(filename, "r");

	if( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 198)), filename);
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END )
		{
			break;
		}

		MOB_MSG_DATA List;

		List.iClass			= TokenNumber;

		GetToken();
		strncpy(List.szMsg, TokenString, 100);

		this->m_Data.push_back(List);
	}

	fclose(SMDFile);
}

void CMonsterMsg::RegenMessage(int aIndex)
{
	if(!g_ExLicense.CheckUser(eExUB::Local)			&&
	   !g_ExLicense.CheckUser(eExUB::Gredy)			&& 
	   !g_ExLicense.CheckUser(eExUB::Gredy2)		&&
	   !g_ExLicense.CheckUser(eExUB::GredyLocal)	&&
	   !g_ExLicense.CheckUser(eExUB::SILVER1)		&&
	   !g_ExLicense.CheckUser(eExUB::SILVER2)		&&
	   !g_ExLicense.CheckUser(eExUB::MU2Play)		&&
	   !g_ExLicense.CheckUser(eExUB::SILVER_Local)  &&
	   !g_ExLicense.CheckUser(eExUB::Artem)			&& 
	   !g_ExLicense.CheckUser(eExUB::Artem2)		&&
	   !g_ExLicense.CheckUser(eExUB::Escalate)		&&
	   !g_ExLicense.CheckUser(eExUB::ArcMu)			&&
	   !g_ExLicense.CheckUser(eExUB::MedoniAndrei)	&&
	   !g_ExLicense.CheckUser(eExUB::mu4you)		&&
	   !g_ExLicense.CheckUser(eExUB::eternalmu)		&&
	   !g_ExLicense.CheckUser(eExUB::NSGames))
	{
		return;
	}

	if(!OBJMON_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpMonster = &gObj[aIndex];

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		MOB_MSG_DATA & Mob = this->m_Data[i];
		if(Mob.iClass == lpMonster->Class)
		{
			AllSendServerMsg(Mob.szMsg);
			return;
		}
	}
}

void CMonsterMsg::DieMessage(int aIndex, int aTargetIndex)
{
	if(!g_ExLicense.CheckUser(eExUB::Local)			&&
	   !g_ExLicense.CheckUser(eExUB::Gredy)			&& 
	   !g_ExLicense.CheckUser(eExUB::Gredy2)		&&
	   !g_ExLicense.CheckUser(eExUB::GredyLocal)	&&
	   !g_ExLicense.CheckUser(eExUB::SILVER1)		&&
	   !g_ExLicense.CheckUser(eExUB::SILVER2)		&&
	   !g_ExLicense.CheckUser(eExUB::MU2Play)		&&
	   !g_ExLicense.CheckUser(eExUB::SILVER_Local)  &&
	   !g_ExLicense.CheckUser(eExUB::Artem)			&&
	   !g_ExLicense.CheckUser(eExUB::Artem2)		&&
	   !g_ExLicense.CheckUser(eExUB::Escalate)		&&
	   !g_ExLicense.CheckUser(eExUB::ArcMu)			&&
	   !g_ExLicense.CheckUser(eExUB::MedoniAndrei)	&&
	   !g_ExLicense.CheckUser(eExUB::mu4you)		&&
	   !g_ExLicense.CheckUser(eExUB::eternalmu)		&&
	   !g_ExLicense.CheckUser(eExUB::NSGames))
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[aTargetIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	int iMapNumber = lpMonster->MapNumber;

	if(!MAX_MAP_RANGE(iMapNumber)) 
	{
		return;
	}

	for(int i = 0; i < this->m_Data.size(); i++)
	{
		MOB_MSG_DATA & Mob = this->m_Data[i];
		if(Mob.iClass == lpMonster->Class)
		{
			LPMONSTER_ATTRIBUTE lpMonsterAttr = gMAttr.GetAttr(lpMonster->Class);
			char szMsg[128];
			sprintf(szMsg,"%s defeated by %s in %s", lpMonsterAttr->m_Name, lpUser->Name, exMapName(iMapNumber));
			AllSendServerMsg(szMsg);
			return;
		}
	}
}