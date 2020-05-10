#include "stdafx.h"
#include "SkillDelay.h"
#include "MagicDamage.h"

CSkillDelay::CSkillDelay()
{
	this->Init();
}


CSkillDelay::~CSkillDelay()
{
	return;
}


void CSkillDelay::Init()
{
	memset(this->LastSkillUseTime, 0, sizeof(this->LastSkillUseTime) );
}


int CSkillDelay::Check(WORD skill)
{
	int skilldelaytime = MagicDamageC.GetDelayTime(skill);

	if (skilldelaytime == 0)
	{
		return TRUE;
	}

	DWORD dwtime = GetTickCount();

	if (skilldelaytime + this->LastSkillUseTime[skill] >= dwtime)
	{
		return FALSE;
	}

	else
	{
		this->LastSkillUseTime[skill] = dwtime;
		return TRUE;
	}
}

int CSkillDelay::CanUse(WORD skill)
{
	int skilldelaytime = MagicDamageC.GetDelayTime(skill);

	if (skilldelaytime == 0)
	{
		return TRUE;
	}

	DWORD dwtime = GetTickCount();

	return dwtime >= skilldelaytime + this->LastSkillUseTime[skill];
}