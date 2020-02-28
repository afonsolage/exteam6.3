#include "StdAfx.h"
#ifdef _GRAND_SYSTEM_
#include "Bow.h"
#include "Console.h"
#include "ToolKit.h"
#include "Import.h"

DWORD FUNCTIONC = 0x006D8F20;
//CALL 006D8F20
DWORD RETURN = 0x00749FDE;
//00749FDE  |.  8B55 EC       MOV EDX,DWORD PTR SS:[EBP-14]

DWORD BOW = 0;
DWORD SKILL = 0;

__declspec(naked) void SkillEffect()
{
	_asm
	{
		MOV ECX,DWORD PTR SS:[EBP-0x4]
		MOV DWORD PTR SS:[EBP-0x14],ECX
		MOV BOW,ECX
		/*CPU Disasm
		Address   Hex dump          Command                                  Comments
		00749FD8  |> \8B4D FC       MOV ECX,DWORD PTR SS:[EBP-4]
		00749FDB  |.  894D EC       MOV DWORD PTR SS:[EBP-14],ECX
		00749FDE  |.  8B55 EC       MOV EDX,DWORD PTR SS:[EBP-14]
		*/
		/*MOV EDX,DWORD PTR SS:[EBP-0x8]
		MOV DWORD PTR SS:[EBP-0x14],EDX
		MOV BOW,EDX*/
	}

	if(BOW >= ITEM2(4,30) && BOW <= ITEM2(4,255))
	{
		_asm
		{
			PUSH -1
			PUSH ECX
			FLDZ
			FSTP DWORD PTR SS:[ESP]
			PUSH 0
			MOVZX ECX,WORD PTR SS:[EBP+0x18]
			PUSH ECX
			MOVZX EDX,WORD PTR SS:[EBP+0x14]
			PUSH EDX
			MOV EAX,DWORD PTR SS:[EBP+0x0C]
			MOVZX ECX,WORD PTR DS:[EAX+0x2C]
			PUSH ECX
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			PUSH EDX
			MOV EAX,DWORD PTR SS:[EBP-0x8]
			PUSH EAX
			MOV ECX,DWORD PTR SS:[EBP+0x0C]
			ADD ECX,0x9C
			PUSH ECX
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			ADD EDX,0x108
			PUSH EDX
			MOV EAX,DWORD PTR SS:[EBP+0x0C]
			ADD EAX,0x0FC 
			PUSH EAX
			PUSH 0x144
			CALL FUNCTIONC

		//			CPU Disasm
		//Address   Hex dump          Command                                  Comments
		//00749F8A  />  6A FF         PUSH -1
		//00749F8C  |.  51            PUSH ECX
		//00749F8D  |.  D9EE          FLDZ
		//00749F8F  |.  D91C24        FSTP DWORD PTR SS:[ESP]
		//00749F92  |.  6A 00         PUSH 0
		//00749F94  |.  0FB74D 18     MOVZX ECX,WORD PTR SS:[EBP+18]
		//00749F98  |.  51            PUSH ECX
		//00749F99  |.  0FB755 14     MOVZX EDX,WORD PTR SS:[EBP+14]
		//00749F9D  |.  52            PUSH EDX
		//00749F9E  |.  8B45 0C       MOV EAX,DWORD PTR SS:[EBP+0C]
		//00749FA1  |.  0FB748 2C     MOVZX ECX,WORD PTR DS:[EAX+2C]
		//00749FA5  |.  51            PUSH ECX
		//00749FA6  |.  8B55 0C       MOV EDX,DWORD PTR SS:[EBP+0C]
		//00749FA9  |.  52            PUSH EDX
		//00749FAA  |.  8B45 F8       MOV EAX,DWORD PTR SS:[EBP-8]
		//00749FAD  |.  50            PUSH EAX
		//00749FAE  |.  8B4D 0C       MOV ECX,DWORD PTR SS:[EBP+0C]
		//00749FB1  |.  81C1 9C000000 ADD ECX,9C
		//00749FB7  |.  51            PUSH ECX
		//00749FB8  |.  8B55 0C       MOV EDX,DWORD PTR SS:[EBP+0C]
		//00749FBB  |.  81C2 08010000 ADD EDX,108
		//00749FC1  |.  52            PUSH EDX
		//00749FC2  |.  8B45 0C       MOV EAX,DWORD PTR SS:[EBP+0C]
		//00749FC5  |.  05 FC000000   ADD EAX,0FC
		//00749FCA  |.  50            PUSH EAX
		//00749FCB  |.  68 44010000   PUSH 144
		//00749FD0  |.  E8 4BEFF8FF   CALL 006D8F20

		//	PUSH -1                                  ; /Arg12 = -1
		//	PUSH 0                                   ; |Arg11 = 0
		//	PUSH 0                                   ; |Arg10 = 0
		//	MOV DX,WORD PTR SS:[EBP+0x18]            ; |
		//	PUSH EDX                                 ; |Arg9
		//	MOV AX,WORD PTR SS:[EBP+0x14]            ; |
		//	PUSH EAX                                 ; |Arg8
		//	MOV ECX,DWORD PTR SS:[EBP+0x0C]          ; |
		//	MOV DX,WORD PTR DS:[ECX+0x2C]            ; |
		//	PUSH EDX                                 ; |Arg7
 		//	MOV EAX,DWORD PTR SS:[EBP+0x0C]          ; |
		//	PUSH EAX                                 ; |Arg6
		//	MOV ECX,DWORD PTR SS:[EBP-0x0C]          ; |
		//	PUSH ECX                                 ; |Arg5
		//	MOV EDX,DWORD PTR SS:[EBP+0x0C]          ; |
		//	ADD EDX,0x9C                             ; |
		//	PUSH EDX                                 ; |Arg4
		//	MOV EAX,DWORD PTR SS:[EBP+0x0C]          ; |
		//	ADD EAX,0x108                            ; |
		//	PUSH EAX                                 ; |Arg3
		//	MOV ECX,DWORD PTR SS:[EBP+0x0C]          ; |
		//	ADD ECX,0x0FC                            ; |
		//	PUSH ECX                                 ; |Arg2
		//	PUSH 296//0x144                          ; |Arg1 = 144
		//	CALL FUNCTIONC                           ; \Main.00650FF0
		//
		}
	}

	_asm{JMP RETURN}
}

DWORD IBOW = 0;
//005CA6DF  |.  D945 B4          FLD DWORD PTR SS:[EBP-4C]

DWORD SHOWBOW = 0x005CA6DF;

                                
//005CA727  |. /75 29            JNE SHORT 005CA752

DWORD DEFBOW  = 0x005CA752;

_declspec(naked)void FixShowInventoryBow()
{
	_asm
	{
//		CPU Disasm
//Address   Hex dump             Command                                          Comments
//005CA720  |> \817D 08 A70C0000 CMP DWORD PTR SS:[EBP+8],0CA7
		/*MOV EAX,DWORD PTR SS:[EBP+8]
		MOV PMAP,EAX*/
		MOV EAX,DWORD PTR SS:[EBP+0x8]
		MOV IBOW, EAX
	}

	if(IBOW == 0x0CA7)
	{
		_asm{JMP SHOWBOW}
	}
	else if(IBOW >= ITEM2(4,30) && IBOW <= ITEM2(4,255))
	{
		_asm{JMP SHOWBOW}
	}
	//else if(IBOW >= ITEM2(13,160) && IBOW <= ITEM2(13,255))
	//{
	//	_asm{JMP SHOWBOW}
	//}
	else
	{
		_asm{JMP DEFBOW}
	}
} 



void initEffectSkil()
{

	//SetNop(0x00749FD8,6);
	WriteJmp(0x00749FD8,(DWORD)&SkillEffect);


	WriteJmp(0x005CA720,(DWORD)&FixShowInventoryBow);

}
#endif