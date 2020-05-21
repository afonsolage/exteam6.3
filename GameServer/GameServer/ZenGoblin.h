#pragma once

#include "PetObject.h"

#define ZEN_GOBLIN_CLASS 629

class CZenGoblin : CPetObject
{
public:
	void Summon(LPOBJ lpObj);

private:

};

extern CZenGoblin g_ZenGoblin;