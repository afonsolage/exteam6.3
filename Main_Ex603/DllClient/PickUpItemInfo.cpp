#include "stdafx.h"
#include "PickUpItemInfo.h"
#include "Object.h"
#include "Console.h"
#include "Interface.h"
#include "Import.h"
#include "PersonalShopEx.h"
#include "TMemory.h"
#include "ExLicense.h"

#if(CUSTOM_PICKUP_ITEM_INFO)

CPickUpItemInfo g_PickUpItemInfo;

CPickUpItemInfo::CPickUpItemInfo()
{
}

CPickUpItemInfo::~CPickUpItemInfo()
{
}

void CPickUpItemInfo::Init()
{
	this->m_dwItemRecv = false;
	memset(&this->m_Data, 0, sizeof(this->m_Data));
}

void CPickUpItemInfo::Load()
{
	this->Init();	
}

void CPickUpItemInfo::InfoSend()
{
	if(!g_ExLicense.user.PickUpItemInfo)
	{
		return;
	}

	if(pItemPosNum != -1 && GetKeyState(VK_SHIFT) & 0x8000)
	{
		PMSG_REQ_PICKUP_INFO pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xBF, sizeof(pMsg));
		pMsg.ItemNum = pItemPosNum;
		gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
	}
	else
	{
		this->m_dwItemRecv = false;
	}
}

void CPickUpItemInfo::InfoRecv(PMSG_ANS_PICKUP_INFO* lpMsg)
{
	if(!g_ExLicense.user.PickUpItemInfo)
	{
		return;
	}

	memset(&this->m_Data, 0, sizeof(this->m_Data));

	if(lpMsg->result == 0)
	{
		this->m_dwItemRecv = false;
		return;
	}

	DWORD dwAddress = (DWORD)&this->m_Data;

	*(WORD *)dwAddress = lpMsg->Type;
	int a5 = lpMsg->Durability;
	*(BYTE *)(dwAddress + 22) = a5;
	int a6 = lpMsg->Data[3];
	*(BYTE *)(dwAddress + 23) = a6;
	int a7 = lpMsg->Data[4];
	*(BYTE *)(dwAddress + 24) = a7;
	int a8 = lpMsg->Data[5];
	*(BYTE *)(dwAddress + 97) = (a8 & 2) >> 1 > 0;
	*(BYTE *)(dwAddress + 98) = (a8 & 4) >> 2 > 0;
	*(BYTE *)(dwAddress + 73) = 16 * (a8 & 8) >> 7 > 0;
	int a9 = lpMsg->Data[6];
	*(WORD *)(dwAddress + 69) = (a9 & 0xF0) >> 4;
	*(WORD *)(dwAddress + 71) = a9 & 0xF;

	DWORD a10 = (DWORD)&lpMsg->Data[7];

	if ( a10 )
	{
		*(BYTE *)(dwAddress + 79) = 5;

		for (int i = 0; i < 5; ++i )
			*(BYTE *)(i + dwAddress + 74) = *(BYTE *)(i + a10);

		for (int j = 0; j < 5; ++j )
		{
			if ( *(BYTE *)(j + a10) == 255 )
			{
				*(BYTE *)(dwAddress + 79) = j;
				break;
			}

			if ( *(BYTE *)(j + a10) == 254 )
			{
				*(BYTE *)(j + dwAddress + 80) = -1;
			}
			else
			{
				*(BYTE *)(j + dwAddress + 80) = *(BYTE *)(j + a10) % 50;
				*(BYTE *)(j + dwAddress + 85) = *(BYTE *)(j + a10) / 50 + 1;
			}
		}

		if ( this->CheckItemInfo(*(WORD *)dwAddress) )
		{
			*(BYTE *)(dwAddress + 90) = a9;
			*(WORD *)(dwAddress + 69) = 0;
			*(WORD *)(dwAddress + 71) = 0;
		}
		else
		{
			*(BYTE *)(dwAddress + 90) = -1;
		}
	}
	else
	{
		*(BYTE *)(dwAddress + 79) = 0;
	}

	*(BYTE *)(dwAddress + 96) = 0;
    *(DWORD *)(dwAddress + 103) = 1;

	pSetItemOption(&this->m_Data, lpMsg->Data[1], lpMsg->Data[3], lpMsg->Data[4]);

	this->m_dwItemRecv = true;
}

void CPickUpItemInfo::Draw()
{
	if(!g_ExLicense.user.PickUpItemInfo)
	{
		return;
	}

	if(pItemPosNum != -1)
	{
		if(this->m_dwItemRecv == true)
		{
			gInterface.DrawItemToolTipText((void*)&this->m_Data, pCursorX + 80, pCursorY - 80 );
		}
	}
}

int CPickUpItemInfo::CheckItemInfo(signed int a1)
{
	if ( a1 > 3092 )
	{
		if ( a1 > 4661 )
		{
			if ( a1 > 5685 || a1 < 5676 && (a1 < 5164 || a1 > 5173) )
				return 0;
		}
		else if ( a1 < 4652 && (a1 > 4149 || a1 < 4140 && (a1 < 3628 || a1 > 3637)) )
		{
			return 0;
		}

		return 1;
	}

	if ( a1 >= 3089 )
		return 1;

	if ( a1 > 2071 )
	{
		if ( a1 != 2580 && (a1 <= 2589 || a1 > 2592) )
			return 0;
		return 1;
	}

	if ( a1 == 2071 || a1 <= 1041 && (a1 >= 1040 || a1 >= 26 && a1 <= 28) )
		return 1;

	return 0;
}

#endif