#pragma once

#include "stdafx.h"
#include "Defines.h"

#ifdef exDEBUG_CODE

			//switch(gController.wKeyBord)
			//{
			//	case VK_LEFT:	flAsmItemX += 0.01;	break;	
			//	case VK_RIGHT:	flAsmItemX -= 0.01;	break;	
			//	case VK_UP:		flAsmItemY += 0.01;	break;
			//	case VK_DOWN:	flAsmItemY -= 0.01;	break;
			//}
			//
			//dPetInvX = flAsmItemX;		//InvX
			//dPetInvY = flAsmItemY;		//InvY

			//if(gController.wKeyBord)
			//{
			//	gConsole.Output(cGREY, "X:%f Y:%f SIZE:%f", dPetInvX, dPetInvY, pPetData->InvSize);
			//}

			//gController.wKeyBord = NULL;

#define sub_83BE10				((int(__thiscall*)(int This)) 0x83BE10)
#define sub_861950				((int(__thiscall*)(int This)) 0x861950)


#define sub_7E19C0 ((int(__thiscall*)(LPVOID This, LPVOID lp)) 0x7E19C0)	//__thiscall
#define sub_7E1AC0 ((int(__thiscall*)(LPVOID This, unsigned __int8 a2, unsigned __int8 a3, char a4, char a5, char a6, char a7, char a8, char a9, int a10)) 0x7E1AC0)

class CHookClass
{
public:
	void Load();
	static int __thiscall Hook(LPVOID This, LPVOID lp);//_TC
	static int __thiscall HookEx(LPVOID This, LPVOID lp);//_TC
	//__fastcall
	//__thiscall
};

extern CHookClass g_HookClass;

void DeBugLoad();

void DeBug_DrawItemPos();


/*
	0x7E19C0 - Client Packet Item Convert
	0x7E1AC0 - Client Bite Convert

*/

#endif