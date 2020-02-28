#include "stdafx.h"
#include "SwitchChar.h"
#include "TMemory.h"
#include "User.h"
#include "Configs.h"
/*
6 - No RF
5 - No Rf, No Sum
*/

void LoadSwitchChar(BYTE Id)
{
	gObjUser.SUM = 1;
	gObjUser.RF = 1;

	if(Id == 1)
	{
		g_MaxCharacter = 6;
		SetByte((PVOID) (0x004030D1 + 3), 6);
		gObjUser.SUM = 1;
		gObjUser.RF = 0;
	}
	else if(Id == 2)
	{
		g_MaxCharacter = 5;
		SetByte((PVOID) (0x004030D1 + 3), 5);
		gObjUser.SUM = 0;
		gObjUser.RF = 0;
	}
	else
	{
		g_MaxCharacter = 7;
	}
	

	//SetByte((PVOID) (0x00403126 + 6), 7);

	
}