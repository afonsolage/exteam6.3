#include "stdafx.h"
#include "PetObject.h"
#include "user.h"
#include "logproc.h"

void CPetObject::Summon(LPOBJ lpObj, int petClass)
{
	auto index = gObjAddMonster(lpObj->MapNumber);

	if (index < 0)
	{
		LOG_ERROR("Failed to summon pet for player %s", lpObj->AccountID);
		return;
	}

	BYTE x = lpObj->X;
	BYTE y = lpObj->Y;
	
	if (!gObjGetRandomItemDropLocation(lpObj->MapNumber, x, y, 2, 2, 10))
	{
		x = lpObj->X;
		y = lpObj->Y;
	}
	
	LPOBJ lpPet = &gObj[index];

	lpPet->X = x;
	lpPet->Y = y;
	lpPet->m_PosNum = -1;
	lpPet->MapNumber = lpObj->MapNumber;
	lpPet->TX = x;
	lpPet->TY = y;
	lpPet->m_OldX = x;
	lpPet->m_OldY = y;
	lpPet->StartX = x;
	lpPet->StartY = y;
	lpPet->Level = lpObj->Level;
	lpPet->Reset = lpObj->Reset;
	lpPet->m_Attribute = 60;
	lpPet->MaxRegenTime = 0;
	lpPet->Dir = rand() % 8;
	lpPet->m_RecallMon = lpObj->m_Index;
	gObjSetMonster(index, petClass);
}
