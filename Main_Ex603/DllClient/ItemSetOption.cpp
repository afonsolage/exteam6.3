#include "stdafx.h"
#include "ItemSetOption.h"
#include "TMemory.h"
#include "Import.h"
// ----------------------------------------------------------------------------------------------

#if(ENABLE_ITEMSETOPTION)
// ----------------------------------------------------------------------------------------------

CItemSetOption g_ItemSetOption;
// ----------------------------------------------------------------------------------------------

CItemSetOption::CItemSetOption()
{
}
// ----------------------------------------------------------------------------------------------

CItemSetOption::~CItemSetOption()
{
}
// ----------------------------------------------------------------------------------------------

void CItemSetOption::Load()
{
	memset(this->m_SetOptionData, 0, sizeof(this->m_SetOptionData));

	this->m_dwSetOptionAddress = (DWORD)&this->m_SetOptionData;
	
	//SetOp((LPVOID)oItemSetOptionBMDLoad, (LPVOID)this->BMDLoad, ASM::CALL);

	this->BMDLoad("Data\\Custom\\Local\\itemsetoption_new.bmd");

	this->m_dwJmpReturn1 = oItemSetOptionAsm1 + 13;
	SetRange((LPVOID)oItemSetOptionAsm1, 13, ASM::NOP);
	SetOp((LPVOID)oItemSetOptionAsm1, (LPVOID)this->AsmAncent1, ASM::JMP);

	this->m_dwJmpReturn2 = oItemSetOptionAsm2 + 10;
	SetRange((LPVOID)oItemSetOptionAsm2, 10, ASM::NOP);
	SetOp((LPVOID)oItemSetOptionAsm2, (LPVOID)this->AsmAncent2, ASM::JMP);

	this->m_dwJmpReturn3 = oItemSetOptionAsm3 + 10;
	SetRange((LPVOID)oItemSetOptionAsm3, 10, ASM::NOP);
	SetOp((LPVOID)oItemSetOptionAsm3, (LPVOID)this->AsmAncent3, ASM::JMP);

	this->m_dwJmpReturn4 = oItemSetOptionAsm4 + 10;
	SetRange((LPVOID)oItemSetOptionAsm4, 10, ASM::NOP);
	SetOp((LPVOID)oItemSetOptionAsm4, (LPVOID)this->AsmAncent4, ASM::JMP);

	this->m_dwJmpReturn5 = oItemSetOptionAsm5 + 10;
	SetRange((LPVOID)oItemSetOptionAsm5, 10, ASM::NOP);
	SetOp((LPVOID)oItemSetOptionAsm5, (LPVOID)this->AsmAncent5, ASM::JMP);

	this->m_dwJmpReturn6 = oItemSetOptionAsm6 + 13;
	SetRange((LPVOID)oItemSetOptionAsm6, 13, ASM::NOP);
	SetOp((LPVOID)oItemSetOptionAsm6, (LPVOID)this->AsmAncent6, ASM::JMP);

	this->m_dwJmpReturn7 = oItemSetOptionAsm7 + 10;
	SetRange((LPVOID)oItemSetOptionAsm7, 10, ASM::NOP);
	SetOp((LPVOID)oItemSetOptionAsm7, (LPVOID)this->AsmAncent7, ASM::JMP);

	this->m_dwJmpReturn8 = oItemSetOptionAsm8 + 10;
	SetRange((LPVOID)oItemSetOptionAsm8, 10, ASM::NOP);
	SetOp((LPVOID)oItemSetOptionAsm8, (LPVOID)this->AsmAncent8, ASM::JMP);
}
// ----------------------------------------------------------------------------------------------
bool CItemSetOption::BMDLoad(char* FileName)
{
	int File = pFileOpen(FileName, "rb");
	//int File = pFileOpen("Data\\ExData\\Local\\itemsetoption_new.bmd", "rb");

	if(File)
	{
		int iTemp = 0;
		int iSize = 0;
		int iLenCount = MAX_SETOPT_LINE;

		//pFileRead((int)&g_ItemSetOption.m_SetOptionData[iSize], MAX_BSETOPT_SIZE, 1, File);
		//pFileRead((int)&iTemp, 4, 1, File);
		//pFileClose(File);
		//pFileCRC((int)&g_ItemSetOption.m_SetOptionData[iSize], iLenCount << 6, 0xA2F1);

		pFileRead((int)&g_ItemSetOption.m_SetOptionData[iSize], MAX_BSETOPT_SIZE, 1, File);
		pFileRead((int)&iTemp, 4, 1, File);
		pFileClose(File);
		//int iCRCKey = pFileCRC((int)&g_ItemSetOption.m_SetOptionData[iSize], MAX_BSETOPT_SIZE, 0xA2F1);
		pFileCRC((int)&g_ItemSetOption.m_SetOptionData[iSize], iLenCount << 6, 0xA2F1);
		//if(iTemp == iCRCKey)
		{
			for(int i = 0; i < MAX_SETOPT_COUNT; i++)
			{
				pFileDec((int)&g_ItemSetOption.m_SetOptionData[iSize], iLenCount);
				iSize += iLenCount;
			}
		}
		//else
		//{
		//	char szText[64];
		//	sprintf(szText, "%s - File corrupted.", FileName);
		//	MessageBoxA(pGameWindow, szText, NULL, NULL);
		//	SendMessageA(pGameWindow, WM_DESTROY, NULL, NULL);
		//}
	}
	else
	{
		char szText[64];
		sprintf(szText, "%s - File not exist.", FileName);
		MessageBoxA(pGameWindow, szText, NULL, NULL);
		SendMessageA(pGameWindow, WM_DESTROY, NULL, NULL);
	}

	return true;
}
// ----------------------------------------------------------------------------------------------

void __declspec(naked) CItemSetOption::AsmAncent1()
{
	_asm
	{
		MOV ECX,g_ItemSetOption.m_dwSetOptionAddress
		LEA EDX,[EAX+ECX]
		JMP g_ItemSetOption.m_dwJmpReturn1
	}
}
// ----------------------------------------------------------------------------------------------

void __declspec(naked) CItemSetOption::AsmAncent2()
{
	_asm
	{
		MOV ECX,g_ItemSetOption.m_dwSetOptionAddress

		LEA EDX,[EAX+ECX]
		JMP g_ItemSetOption.m_dwJmpReturn2
	}
}
// ----------------------------------------------------------------------------------------------

void __declspec(naked) CItemSetOption::AsmAncent3()
{
	_asm
	{
		MOV EDX,g_ItemSetOption.m_dwSetOptionAddress
		LEA EAX,[ECX+EDX]
		JMP g_ItemSetOption.m_dwJmpReturn3
	}
}
// ----------------------------------------------------------------------------------------------

void __declspec(naked) CItemSetOption::AsmAncent4()
{
	_asm
	{
		MOV EAX,g_ItemSetOption.m_dwSetOptionAddress
		LEA ECX,[EDX+EAX]
		JMP g_ItemSetOption.m_dwJmpReturn4
	}
}
// ----------------------------------------------------------------------------------------------

void __declspec(naked) CItemSetOption::AsmAncent5()
{
	_asm
	{
		MOV EAX,g_ItemSetOption.m_dwSetOptionAddress
		LEA ECX,[EDX+EAX]
		JMP g_ItemSetOption.m_dwJmpReturn5
	}
}
// ----------------------------------------------------------------------------------------------

void __declspec(naked) CItemSetOption::AsmAncent6()
{
	_asm
	{
		MOV EDX,g_ItemSetOption.m_dwSetOptionAddress
		LEA EAX,[ECX+EDX]
		JMP g_ItemSetOption.m_dwJmpReturn6
	}
}
// ----------------------------------------------------------------------------------------------

void __declspec(naked) CItemSetOption::AsmAncent7()
{
	_asm
	{
		MOV EAX,g_ItemSetOption.m_dwSetOptionAddress
		LEA ECX,[EDX+EAX]
		JMP g_ItemSetOption.m_dwJmpReturn7
	}
}
// ----------------------------------------------------------------------------------------------

void __declspec(naked) CItemSetOption::AsmAncent8()
{
	_asm
	{
		MOV ECX,g_ItemSetOption.m_dwSetOptionAddress
		LEA EDX,[EAX+ECX]
		JMP g_ItemSetOption.m_dwJmpReturn8
	}
}
// ----------------------------------------------------------------------------------------------
#endif