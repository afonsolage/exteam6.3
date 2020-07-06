#include "stdafx.h"
#include "CustomBossDrop.h"
#include "gObjMonster.h"

CCustomBossDrop::CCustomBossDrop(void)
{
}


CCustomBossDrop::~CCustomBossDrop(void)
{
}

void CCustomBossDrop::DropBossItem(LPOBJ lpBoss, LPOBJ lpKiller)
{
	auto maxHitUser = gObjMonsterTopHitDamageUser(lpBoss);

	if (maxHitUser != -1 && gObjIsConnected(maxHitUser))
	{
		lpKiller = &gObj[maxHitUser];
	}

	this->DropItem(lpKiller);

	char tmp[256] = { 0 };
	sprintf(tmp, "%s Killed %s", lpKiller->Name, this->m_sName);
	AllSendServerMsg(tmp);
}
