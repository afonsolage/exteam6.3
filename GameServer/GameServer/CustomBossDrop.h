#pragma once

#include "CustomDrop.h"
#include "..\common\zzzitem.h"
#include "user.h"

class CCustomBossDrop : public CCustomDrop
{
public:
	CCustomBossDrop(void);
	virtual ~CCustomBossDrop(void);
	void DropBossItem(LPOBJ lpBoss, LPOBJ lpKiller);
};

