#include "stdafx.h"
#include "TMemory.h"
#include "MiniMap.h"
#include "Import.h"

CMiniMap g_MiniMap;

bool CMiniMap::MiniMapTabKey(int a1)
{
	return false;
}

bool CMiniMap::MiniMapCheck(int a1)
{
	if(g_MiniMap.Show && pMapNumber == 30)
	{
		return true;
	}

	return false;
}

void CMiniMap::Load()
{
	
	this->Show = true;
	SetOp((LPVOID)0x007D3B57, (LPVOID)g_MiniMap.MiniMapTabKey, ASM::CALL);
	SetOp((LPVOID)0x00886B87, (LPVOID)g_MiniMap.MiniMapCheck, ASM::CALL);
	SetRange((LPVOID)0x008874B4, 5, ASM::NOP);
	
}


