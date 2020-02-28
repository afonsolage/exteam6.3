#include "StdAfx.h"
#include "Defines.h"
#include "ChatWnd.h"
#include "TMemory.h"
#include "Other.h"

#if(exCHATWND)

DWORD dwMsgType;
DWORD dwYpos;
DWORD dwHeight;
DWORD dwMsgCnt;
DWORD dwScrollPos;

int SystChatSepar = 190;

Naked(ShowSysMsgs)
{
	__asm 
	{
		call GetDisplayMsgType
		mov dwMsgType, eax
		MOV ECX, DWORD PTR SS:[EBP-4]
		MOV EAX, DWORD PTR DS:[ECX+0xB4]
		MOV dwYpos, EAX
		MOV EAX, DWORD PTR DS:[ECX+0xC4]
		MOV dwHeight, EAX
		// ----
		MOV EDX, [SystChatSepar]
		MOV DWORD PTR DS:[ECX+0xB4], EDX
		MOV DWORD PTR DS:[ECX+0xC4], 0x64
		MOV EAX, DWORD PTR DS:[ECX+0xC8]
		MOV dwMsgCnt, EAX
		MOV DWORD PTR DS:[ECX+0xC8], 4		//string Log
		MOV EAX, DWORD PTR DS:[ECX+0xD4]
		MOV dwScrollPos, EAX
		PUSH 3
		MOV ECX, DWORD PTR SS:[EBP-4]
		CALL SetDisplayMsgType
		MOV ECX, DWORD PTR SS:[EBP-4]
		CALL ShowChatMsgs
		MOV ECX, DWORD PTR SS:[EBP-4]
		PUSH dwMsgType
		CALL SetDisplayMsgType
		MOV ECX, DWORD PTR SS:[EBP-4]
		MOV EAX, dwYpos
		MOV DWORD PTR DS:[ECX+0xB4], EAX
		MOV EAX, dwHeight
		MOV DWORD PTR DS:[ECX+0xC4], EAX
		MOV EAX, dwMsgCnt
		MOV DWORD PTR DS:[ECX+0xC8], EAX
		MOV EAX, dwScrollPos
		MOV DWORD PTR DS:[ECX+0xD4], EAX
		MOV ECX, DWORD PTR SS:[EBP-4]
		CALL ShowChatMsgs
		retn
	}
}

Naked(FixSysMsg1)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCallChat
		jmp FixSysMsg1_FALSE
		_true:
		pop eax
		jmp FixSysMsg1_TRUE
	}
}

Naked(FixSysMsg2)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCallChat
		jmp FixSysMsg2_FALSE
		_true:
		pop eax
		jmp FixSysMsg2_TRUE
	}
}

Naked(FixSysMsg3)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCallChat
		jmp FixSysMsg3_FALSE
		_true:
		pop eax
		jmp FixSysMsg3_TRUE
	}
}

void ChatWndHooks()
{
	SetOp((PVOID)ShowChatMsgsCall_Hook , ShowSysMsgs, ASM::CALL);
	SetOp((PVOID)FixSysMsg1_Hook, FixSysMsg1, ASM::JMP);
	SetOp((PVOID)FixSysMsg2_Hook, FixSysMsg2, ASM::JMP);
	SetOp((PVOID)FixSysMsg3_Hook, FixSysMsg3, ASM::JMP);
}  

#endif