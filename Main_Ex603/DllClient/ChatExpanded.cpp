#include "StdAfx.h"
#include "ChatExpanded.h"
#include "Other.h"
#include "TMemory.h"
#include "Defines.h"
#include <atlstr.h>
#include "TrayMode.h"
#include "Console.h"
#include "NewHpBar.h"
#include "ExFunction.h"
#include "Import.h"
#include "ExLicense.h"

// ----------------------------------------------------------------------------------------------

ChatExpanded	gChatExpanded;
// ----------------------------------------------------------------------------------------------

Naked(FixSysMsg1)
{
	__asm
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg1_FALSE
		_true:
		pop eax
		jmp FixSysMsg1_TRUE
	}
}
// ----------------------------------------------------------------------------------------------

Naked(FixSysMsg2)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg2_FALSE
		_true:
		pop eax
		jmp FixSysMsg2_TRUE
	}
}
// ----------------------------------------------------------------------------------------------

Naked(FixSysMsg3)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg3_FALSE
		_true:
		pop eax
		jmp FixSysMsg3_TRUE
	}
}
// ----------------------------------------------------------------------------------------------

//#define DEBUG_NEW_COLOR

#if(ENABLE_CHATCOLOR)

static DWORD dw00788DD9 = 0x00788DD9;
static DWORD dw0041FE10 = 0x0041FE10;
static DWORD dw004200B0 = 0x004200B0;
static DWORD dw00420040 = 0x00420040;
static DWORD dw00420120 = 0x00420120;

void __declspec(naked) StandartChat()
{

	__asm 
	{
		//BG COLOR
		PUSH 0x80								//ALFA
		PUSH 0x00								//BLUE
		PUSH 0x00								//GREEN
		PUSH 0x00								//RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw004200B0
		//TEXT COLOR
		PUSH 0xFF								//ALFA
		PUSH 0xEF                               //BLUE
		PUSH 0xCD                               //GREEN
		PUSH 0xDC                               //RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420040
		// --
		MOV EDX,DWORD PTR DS:[gChatExpanded.m_hFont]
		PUSH EDX
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420120
		JMP dw00788DD9
	}
}

void __declspec(naked) GuildChat()
{
	__asm 
	{
		//BG COLOR
		PUSH 0x80								//ALFA
		PUSH 0x00								//BLUE
		PUSH 0x00								//GREEN
		PUSH 0x00								//RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw004200B0
		//TEXT COLOR
		PUSH 0xFF								//ALFA
		PUSH 0x00                               //BLUE
		PUSH 0xFF                               //GREEN
		PUSH 0x00                               //RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420040
		// --
		MOV EDX,DWORD PTR DS:[gChatExpanded.m_hFont]
		PUSH EDX
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420120
		JMP dw00788DD9
	}
}

void __declspec(naked) PartyChat()
{
	__asm 
	{
		//BG COLOR
		PUSH 0x80								//ALFA
		PUSH 0x00								//BLUE
		PUSH 0x00								//GREEN
		PUSH 0x00								//RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw004200B0
		//TEXT COLOR
		PUSH 0xFF								//ALFA
		PUSH 0xFF                               //BLUE
		PUSH 0x96                               //GREEN
		PUSH 0x00                               //RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420040
		// --
		MOV EDX,DWORD PTR DS:[gChatExpanded.m_hFont]
		PUSH EDX
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420120
		JMP dw00788DD9
	}
}

void __declspec(naked) AllianceChat()
{
	__asm 
	{
		//BG COLOR
		PUSH 0x80								//ALFA
		PUSH 0x00								//BLUE
		PUSH 0x00								//GREEN
		PUSH 0x00								//RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw004200B0
		//TEXT COLOR
		PUSH 0xFF								//ALFA
		PUSH 0x00                               //BLUE
		PUSH 0xC8                               //GREEN
		PUSH 0xC8                               //RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420040
		// --
		MOV EDX,DWORD PTR DS:[gChatExpanded.m_hFont]
		PUSH EDX
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420120
		JMP dw00788DD9
	}
}

void __declspec(naked) GensChat()
{
	__asm 
	{
		//BG COLOR
		PUSH 0x80								//ALFA
		PUSH 0x00								//BLUE
		PUSH 0x00								//GREEN
		PUSH 0x00								//RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw004200B0
		//TEXT COLOR
		PUSH 0xFF								//ALFA
		PUSH 0xFF                               //BLUE
		PUSH 0xFF                               //GREEN
		PUSH 0x00                               //RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420040
		// --
		MOV EDX,DWORD PTR DS:[gChatExpanded.m_hFont]
		PUSH EDX
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420120
		JMP dw00788DD9
	}
}

void __declspec(naked) PrivateChat()
{
	__asm 
	{
		//BG COLOR
		PUSH 0x80								//ALFA
		PUSH 0x00								//BLUE
		PUSH 0x00								//GREEN
		PUSH 0x00								//RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw004200B0
		//TEXT COLOR
		PUSH 0xFF								//ALFA
		PUSH 0x96                               //BLUE
		PUSH 0x00                               //GREEN
		PUSH 0xFF                               //RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420040
		// --
		MOV EDX,DWORD PTR DS:[gChatExpanded.m_hFont]
		PUSH EDX
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420120
		JMP dw00788DD9
	}
}

void __declspec(naked) PrivateChatEVO()
{
	__asm 
	{
		//BG COLOR
		PUSH 0x80								//ALFA
		PUSH 0x00								//BLUE
		PUSH 0x00								//GREEN
		PUSH 0x00								//RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw004200B0
		//TEXT COLOR
		PUSH 0xFF								//ALFA
		PUSH 0xFF                               //BLUE
		PUSH 0xFF                               //GREEN
		PUSH 0x00                               //RED
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420040
		// --
		MOV EDX,DWORD PTR DS:[gChatExpanded.m_hFont]
		PUSH EDX
		CALL dw0041FE10
		MOV ECX,EAX
		CALL dw00420120
		JMP dw00788DD9
	}
}
#endif


DWORD NEW_COLOR[100] = { 0 };

#ifdef DEBUG_NEW_COLOR
DWORD Return_00788DD9 = 0x00788DDF;
DWORD MyColor = 0;
DWORD _0078BF00 = 0x0078BF00;
Naked(_00788DD9)
{
	_asm
	{

		MOV ECX,DWORD PTR SS:[EBP-0x2C]
		CALL _0078BF00
		//CMP EAX,9
		MOV MyColor, EAX

	}

#ifdef exDEBUG_CODE
	//gConsole.Output(cGREEN,"COLOR: %d",MyColor);
	if(MyColor == 10)
	{



	
	}
#endif

	_asm
	{
		MOVZX EAX,BYTE PTR SS:[EBP-0x2D]
		TEST EAX,EAX
		JMP Return_00788DD9;
	}


}

//#define CheckBattleCursor        ((bool(__cdecl*)()) 0x59A8B0)

#define  sub_78BE90	((BYTE(__thiscall*)(LPVOID this1, int a2, int a3, signed int a4))	0x78BE90)// char __thiscall 

BYTE _sub_78BE90(LPVOID this1, int a2, int a3, signed int a4)
{
#ifdef exDEBUG_CODE
	//gConsole.Output(cGREEN,"COLOR: %d %d %d",a2, a3, a4);
#endif

	//if(a3)
	//a3 = 8;

	return sub_78BE90(this1, a2, a3, a4);
}


void InitTestColor()
{
	SetOp((LPVOID)0x00788DD9, _00788DD9, ASM::JMP);

	
	SetOp((LPVOID)0x00789C03, (LPVOID)_sub_78BE90, ASM::CALL);

	//меняем ограничение на цветовые тайпы
#ifdef DEBUG_NEW_COLOR	
	SetByte((LPVOID)(0x0078BE97+3), 20);
#endif
}

#endif

void ChatExpanded::Load()
{
#ifdef DEBUG_NEW_COLOR
	//InitTestColor();
#endif

	this->IsActive = true;
	SetOp((LPVOID)oShowChatMessage_Call, (LPVOID)this->ShowChatMessage, ASM::CALL);
	SetOp((LPVOID)oWhisperChat_Call, (LPVOID)this->WhisperChatRecv, ASM::CALL);
	SetOp((LPVOID)FixSysMsg1_Hook, FixSysMsg1, ASM::JMP);
	SetOp((LPVOID)FixSysMsg2_Hook, FixSysMsg2, ASM::JMP);
	SetOp((LPVOID)FixSysMsg3_Hook, FixSysMsg3, ASM::JMP);

}
// ----------------------------------------------------------------------------------------------

void ChatExpanded::SetInstance(LPVOID Instance)
{
	this->Instance			= Instance;
	this->PosYBuff			= this->GetPosY();
	this->HeightBuff		= this->GetHeight();
	this->MessageCountBuff	= this->GetMessageCount();
	this->MessageTypeBuff	= this->GetMessageType();
	this->ScrollPosBuff		= this->GetScrollPos();
}
// ----------------------------------------------------------------------------------------------

void ChatExpanded::Restore()
{
	this->SetPosY(this->PosYBuff);
	this->SetHeight(this->HeightBuff);
	this->SetMessageCount(this->MessageCountBuff);
	this->SetMessageType(this->MessageTypeBuff);
	this->SetScrollPos(this->ScrollPosBuff);
}
// ----------------------------------------------------------------------------------------------

void ChatExpanded::Switch()
{
	if( !gChatExpanded.IsActive )
	{
		SetOp((LPVOID)FixSysMsg1_Hook, FixSysMsg1, ASM::JMP);
		SetOp((LPVOID)FixSysMsg2_Hook, FixSysMsg2, ASM::JMP);
		SetOp((LPVOID)FixSysMsg3_Hook, FixSysMsg3, ASM::JMP);
		gChatExpanded.IsActive = true;
	}
	else
	{
		SetOp((LPVOID)FixSysMsg1_Hook, (LPVOID)oNewCall, ASM::CALL);
		SetOp((LPVOID)FixSysMsg2_Hook, (LPVOID)oNewCall, ASM::CALL);
		SetOp((LPVOID)FixSysMsg3_Hook, (LPVOID)oNewCall, ASM::CALL);
		gChatExpanded.IsActive = false;
	}
}
// ----------------------------------------------------------------------------------------------

bool ChatExpanded::ShowChatMessage(LPVOID This, LPVOID EDX)
{
//#ifdef exDEBUG_CODE
	//gConsole.Output(cGREEN,"COLOR: %d",MyColor);
//#endif
	if( !gChatExpanded.IsActive )
	{
		return pShowChatMessage(This);
	}
	// ----
	gChatExpanded.SetInstance(This);
	gChatExpanded.SetPosY(198);	//172	178
	gChatExpanded.SetHeight(100);	//100
	gChatExpanded.SetMessageCount(4);	//4
	pSetChatMessageType(This, 3);
	pShowChatMessage(This);
	gChatExpanded.Restore();
	return pShowChatMessage(This);
}
// ----------------------------------------------------------------------------------------------

void ChatExpanded::WhisperChatRecv(CHAT_WHISPER_EX * pRequest)
{
#ifdef exDEBUG_CODE
	//gConsole.Output(cRED,"POST: %d",pRequest->Type);
#endif
	if( pRequest->Type )
	{
		SetByte((LPVOID)(0x006401AF+1), pRequest->Type);
	}
	else
	{
		SetByte((LPVOID)(0x006401AF+1), 2);
	}
	// ----
	//pRequest->Type = 0;
	pWhisperChatRecv(pRequest);
	// ----
	/*if( pChatIsClosed(pChatThis(pWindowThis())) )
	{
		return;
	}
	// ----
	char * Name = new char[11];
	memcpy(Name, pRequest->Name, 10);
	char * Message = new char[91];
	memcpy(Message, pRequest->Message, 90);
	// ----
	pChatCheckLevel(10, pRequest->Name);
	// ----
	if( pChatWhisperActive(pChatWhisperThis(pWindowThis())) )
	{
		pChatReserveLine(38, 0, 0);
	}
	// ----
	pChatOutput(pChatBoxThis(pWindowThis()), Name, Message, 2, 0);
	delete [] Message;
	delete [] Name;*/
}
// ----------------------------------------------------------------------------------------------



void ChatExpanded::GCChatData(PMSG_CHATDATA * Recv)
{
	if( gTrayMode.InTray )
	{
		char Name[100];
		char Message[100];
		char Pristavka[100];
		char ChatBuffer[100];

		memcpy(Name,Recv->chatid,10);
		strcpy(Message,Recv->chatmsg);

		if(Message[0] == '~' && Message[1] == '[')
		{
			sprintf(Pristavka, "[POST] %s",Name);
			strcpy(ChatBuffer,&Message[8]);
		}
		else if(Message[0] == '~')
		{
			sprintf(Pristavka, "[PARTY] %s",Name);
			strcpy(ChatBuffer,&Message[1]);
		}
		else if(Message[0] == '@' && Message[1] == '@')
		{
			sprintf(Pristavka, "[ALLIANCE] %s",Name);
			strcpy(ChatBuffer,&Message[2]);
		}
		else if(Message[0] == '@')
		{
			sprintf(Pristavka, "[GUILD] %s",Name);
			strcpy(ChatBuffer,&Message[1]);
		}
		else
		{
			strcpy(Pristavka,Name);
			strcpy(ChatBuffer,Message);
		}

		if(CheckSimbolEng(ChatBuffer[0]) == false) return;

		//gConsole.Output(cGREEN,"%s",ChatBuffer);
		gTrayMode.ShowMessage(NIIF_INFO, 10000, Pristavka, ChatBuffer);
	}
}

void ChatExpanded::GCChatDataPrivate(PMSG_CHATDATA_WHISPER * Recv)
{
	if( gTrayMode.InTray )
	{
		char Name[100];
		char Message[100];
		char Pristavka[100];

		memcpy(Name,Recv->id,10);
		strcpy(Message,Recv->chatmsg);

		sprintf(Pristavka, "[PRIVATE] %s",Name);

		if(CheckSimbolEng(Message[0]) == false) return;

		gTrayMode.ShowMessage(NIIF_INFO, 10000, Pristavka, Message);
	}
}

void ChatExpanded::LoadChatEx()
{
#if(ENABLE_CHATCOLOR)

	int cHeight = 14;

	this->m_hFont = CreateFont(cHeight, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE, NULL);

	SetOp((LPVOID)0x00788BE5, StandartChat, ASM::JMP);
	SetOp((LPVOID)0x00788C74, GuildChat, ASM::JMP);
	SetOp((LPVOID)0x00788C2E, PartyChat, ASM::JMP);
	SetOp((LPVOID)0x00788D00, AllianceChat, ASM::JMP);
	SetOp((LPVOID)0x00788D9C, GensChat, ASM::JMP);

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		SetOp((LPVOID)0x00788B16, PrivateChatEVO, ASM::JMP);
	}
	else
	{
		SetOp((LPVOID)0x00788B16, PrivateChat, ASM::JMP);
	}

	BYTE btLineY = 12;
	BYTE btLineMax = 20;

	if(pGameResolutionMode > 2)
	{
		btLineY = 10;	//10
		btLineMax = 26;	//24
	}
	
	//SetFloat((LPVOID)0x0D24EC0, 10.00);
	
	//show text
	SetByte((LPVOID)(0x00788A1E+2), btLineY);
	SetByte((LPVOID)(0x00788E1C+2), btLineY);

	//cursor text
	SetByte((LPVOID)(0x0078A8E2+2), btLineY);
	SetByte((LPVOID)(0x0078A90E+2), btLineY);
	SetByte((LPVOID)(0x0078A91F+1), btLineMax);//
	
	//chat up
	SetByte((LPVOID)(0x0078A9E6+1), btLineY);//
	SetByte((LPVOID)(0x0078A9E4+1), 0x14);//
	SetByte((LPVOID)(0x0078AE1B+2), btLineMax);//
	SetByte((LPVOID)(0x0078AD58+1), btLineMax);
	SetByte((LPVOID)(0x0078AE8B+1), btLineMax);
	
	//in function
	SetByte((LPVOID)(0x0078A47F+2), btLineY);
	SetByte((LPVOID)(0x0078B45C+2), btLineY);

	//Max text viewe
	SetByte((LPVOID)(0x0078A41A+6), btLineMax);
	//SetByte((LPVOID)(0x0078A426+6), 4);//

#endif
}