#include "stdafx.h"
#include "SocketItem.h"
#include "ReadScript.h"
#include "TMemory.h"
#include "Defines.h"
#include "Item.h"
#include "Configs.h"
#include "ExLicense.h"

cSocketItem gSocketItem;

void cSocketItem::Load()
{
	SMDFile = fopen(SOCKET_DIR, "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,SOCKET_DIR,"CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	int Token;
	int type = -1;

	this->ItemCount = 0;

	while ( true )
	{
		Token = GetToken();

		if ( strcmp("end", TokenString ) == 0)
		{
			break;
		}

		this->sItem[this->ItemCount].Type = TokenNumber;

		Token = GetToken();
		this->sItem[this->ItemCount].Index = TokenNumber;

		this->ItemCount++;
	}

	fclose(SMDFile);

	SetOp((LPVOID)0x00967FC1, gSocketItem.CheckItem, ASM::CALL);
	SetOp((LPVOID)0x00967FE7, gSocketItem.CheckItem, ASM::CALL);
}

int cSocketItem::CheckItem(signed int ItemCode)
{
	for(int i = 0; i < gSocketItem.ItemCount; i++ )
	{
		if( ItemCode == ITEMGET(gSocketItem.sItem[i].Type, gSocketItem.sItem[i].Index) )
		{
			return 1;
		}
		else if( gSocketItem.sItem[i].Type == -1 )
		{
			for( int Category = 7; Category < 12; Category++ )
			{
								
				if( ItemCode == ITEMGET(Category, gSocketItem.sItem[i].Index) )
				{
					return 1;
				}
			}
		}
	}
#ifdef _GRAND_SYSTEM_

	if(g_ExLicense.CheckUser(eExUB::Local) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || 
		g_ExLicense.CheckUser(eExUB::GredyLocal) || 
		g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		return 0;
	}

	switch(ItemCode)
	{
		case ITEMGET(0,41):
		case ITEMGET(0,42):
		case ITEMGET(0,43):
		case ITEMGET(2,20):
		case ITEMGET(4,30):
		case ITEMGET(5,41):
		case ITEMGET(5,42):
		case ITEMGET(6,30):
		case ITEMGET(6,31):
		case ITEMGET(6,32):
		case ITEMGET(6,33):
			return 1;
	}

	if( ItemCode >= ITEMGET(7,84) && ItemCode <= ITEMGET(7,90) ||
		ItemCode >= ITEMGET(8,84) && ItemCode <= ITEMGET(8,90) ||
		ItemCode >= ITEMGET(9,84) && ItemCode <= ITEMGET(9,90) ||
		ItemCode >= ITEMGET(10,84) && ItemCode <= ITEMGET(10,90) ||
		ItemCode >= ITEMGET(11,84) && ItemCode <= ITEMGET(11,90))
	{
		return 1;
	}

#endif
	return 0;
}