#include "stdafx.h"
#include "ZenGoblin.h"

CZenGoblin g_ZenGoblin;

void CZenGoblin::Summon(LPOBJ lpObj)
{
	CPetObject::Summon(lpObj, ZEN_GOBLIN_CLASS);


}
