#include "StdAfx.h"
#include "user.h"
#include "Configs.h"
#include "DSProtocol.h"
#include "Message.h"
#include "logproc.h"

#include <random>

// -----------------------------------------------------------------------------------------------------------------------------------------
unsigned char GetRandomExeOption(unsigned char MaxOption)
{
	unsigned char ExeOptions[6] = {1,2,4,8,16,32};
	// ----
	unsigned char Random = 0;
	unsigned char RandomEx = 0;
	unsigned char ReturnValue = 0;

	Random = rand()%(MaxOption+1);

	for (int i=0;i<Random;i++)
	{
		while ( true )
		{
			RandomEx = ExeOptions[rand()%6];

			if ( (ReturnValue&RandomEx) == 0 )
			{
				ReturnValue+=RandomEx;
				break;
			}
		}
	}
	return ReturnValue;
}
bool Ex_IsBadFileLine(char *FileLine, int &Flag)
{
	if(Flag == 0)
	{
		if(isdigit(FileLine[0]))
		{
			Flag = FileLine[0] - 48;
			return true;
		}
	}
	else if(Flag < 0 || Flag > 9)	//Old 9
	{
		Flag = 0;
	}

	if(!strncmp(FileLine, "end", 3))
	{
		Flag = 0;
		return true;
	}

	if(FileLine[0] == '/' || FileLine[0] == '\n')
		return true;


	for(UINT i = 0; i < strlen(FileLine); i++)
	{
		if(isalnum(FileLine[i]))
			return false;
	}
	return true;
}
int GetNumberByPercent(int Proc, int Min, int Max)
{
	int Random = rand()%100;

	if(Proc == 0 || Max == Min)
		return Min;
	
	if(Random <= Proc)
		return Max;

	if(Proc > 50)
		return GetNumberByPercent(Proc/2, Min, Max-1);
	else if(Proc < 30)
		return GetNumberByPercent(Proc*3/2, Min, Max-1);
	else
		return GetNumberByPercent(Proc, Min, Max-1);
}
int GenExcOpt(int amount)
{
	// User input errors
	if (amount > 6) amount = 6;
	if (amount < 1) return 0;

	int opt_db[6]  = {1, 2, 4, 8, 16, 32};
	int exc = 0;

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(opt_db, opt_db + 6, g);

	for(int n=0; n < amount; n++)
		exc += opt_db[n];

	return exc;
}

int ExGenExcOpt(int amount)
{
	// User input errors
	if (amount > 6) amount = 6;
	if (amount < 1) return 0;

	int opt_db[6]  = {1, 2, 4, 8, 16, 32};
	int exc = 0;

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(opt_db, opt_db + 6, g);

	for(int n=0; n < amount; n++)
		exc += opt_db[n];

	return exc;
}

//Возвращяет количество заданых вещей
int gObjGetItemCountInInventory(int aIndex, int ItemID,int ItemLevel)
{
	if(aIndex >= OBJMAX)
		return 0;

	LPOBJ lpObj = &gObj[aIndex];

	int Count = 0;
	for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
	{
		if (lpObj->pInventory[i].m_Type == ItemID && lpObj->pInventory[i].m_Level == ItemLevel)
			Count++;
	}
	return Count;
}
//Удаляет заданное количество вещей 
int gObjDeleteItemsCount(int aIndex, short Type, short Level, int dCount)
{
	if(aIndex >= OBJMAX)
		return 0;

	LPOBJ lpObj = &gObj[aIndex];

	int count = 0;
	for(int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
	{
		if(lpObj->pInventory[i].m_Type == Type && lpObj->pInventory[i].m_Level == Level)
		{
			gObjInventoryDeleteItem(aIndex, i);
			GCInventoryItemDeleteSend(aIndex, i, 1);
			count++;

			if(dCount == count)
				break;
		}
	}
	return count;
}
//==================================================================================================
// FireCracker
//==================================================================================================
void ExFireCracker(int aIndex, BYTE X, BYTE Y)
{
	LPOBJ lpObj = &gObj[aIndex];
	BYTE Packet[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y};
	DataSend(aIndex,Packet,Packet[1]);
	BYTE Packet2[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X+1, Y};
	DataSend(aIndex,Packet2,Packet2[1]);
	BYTE Packet3[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y+1};
	DataSend(aIndex,Packet3,Packet3[1]);
	BYTE Packet4[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y-1};
	DataSend(aIndex,Packet4,Packet4[1]);
	BYTE Packet5[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X-1, Y};
	DataSend(aIndex,Packet5,Packet5[1]);
}

//#ifdef _WCOIN_ONLINE_
//void TimeTickWCoin(int aIndex)
//{
//	if(!ExConfig.CommonServer.WCoinTime || !ExConfig.CommonServer.WCoinReward) return;
//	LPOBJ lpObj = &gObj[aIndex];
//#ifdef _OFFTRADE_
//	if(lpObj->OffTrade != 0) return;
//#endif
//#ifdef _OFFEXP_
//	if(lpObj->OffExp == 1)	return;
//#endif
//	lpObj->WCoinTick++;
//	if(lpObj->WCoinTick >= ExConfig.CommonServer.WCoinTime)
//	{
//		LPOBJ lpObj = &gObj[aIndex];
//		lpObj->WCoinTick = 0;
//		GDRequestWcoinInfoLoad (lpObj,ExConfig.CommonServer.WCoinReward,1);
//		MsgNormal(aIndex,"[Wcoin Online]: +%d",ExConfig.CommonServer.WCoinReward);
//	}
//}
//#endif
//#ifdef _CREDIT_ONLINE_
//void TimeTickCredit(int aIndex)
//{
//	if(!ExConfig.CommonServer.CreditTime || !ExConfig.CommonServer.CreditReward) return;
//	LPOBJ lpObj = &gObj[aIndex];
//#ifdef _OFFTRADE_
//	if(lpObj->OffTrade != 0) return;
//#endif
//#ifdef _OFFEXP_
//	if(lpObj->OffExp == 1)	return;
//#endif
//	lpObj->CreditTick++;
//	if(lpObj->CreditTick >= ExConfig.CommonServer.CreditTime)
//	{
//		LPOBJ lpObj = &gObj[aIndex];
//		lpObj->CreditTick = 0;
//		lpObj->ExCred += ExConfig.CommonServer.CreditReward;
//		ExPCPointSystem.InitPCPointForPlayer(lpObj,lpObj->PCPoint, lpObj->ExCred);
//		MsgNormal(aIndex,"[Credits Online]: +%d",ExConfig.CommonServer.CreditReward);
//	}
//}
//#endif

BYTE GetExcOptionCount(BYTE ExcellentOption)
{
	int ExcellentCount = 0;
	// ----
	for( int i = 0; i < 6; i++ )
	{
		if( (ExcellentOption >> i) & 1 )
		{
			ExcellentCount++;
		}
	}
	// ----
	return ExcellentCount;
}

int EmptyPointInventory(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int Empty = 0;
	// ----

	for( int i = INVETORY_WEAR_SIZE; i < 76; i++ )
    {
        if( !lpObj->pInventory[i].IsItem() )
		{
			Empty++;
		}
	}

	if(lpObj->ExpandedInventory == 0)
	{
		return Empty;
	}

	for( int i = 76; i < 108; i++ )
    {
        if( !lpObj->pInventory[i].IsItem() )
		{
			Empty++;
		}
	}	

	if(lpObj->ExpandedInventory == 1)
	{
		return Empty;
	}

	for( int i = 108; i < 140; i++ )
    {
        if( !lpObj->pInventory[i].IsItem() )
		{
			Empty++;
		}
	}	

	return Empty;
}

int ExCheckInventoryEmptySpace(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int iEmptyCount = 0;
	for ( int x=0;x<64;x++)
	{
		if ( lpObj->pInventoryMap[x] == 0xFF )
		{
			iEmptyCount++;
		}
	}

	if(lpObj->ExpandedInventory == 0)
	{
		return iEmptyCount;
	}

	for ( int x=64;x<96;x++)
	{
		if ( lpObj->pInventoryMap[x] == 0xFF )
		{
			iEmptyCount++;
		}
	}

	if(lpObj->ExpandedInventory == 1)
	{
		return iEmptyCount;
	}

	for ( int x=96;x<128;x++)
	{
		if ( lpObj->pInventoryMap[x] == 0xFF )
		{
			iEmptyCount++;
		}
	}

	return iEmptyCount;

	//LPOBJ lpObj = &gObj[aIndex];
	//int h=0;
	//int w=0;
	//int iItemWidth = 1, iItemHeight = 1;
	//BYTE blank = 0;

	//int Point = 0;
	//
	//for(h=0;h<8;h++)
	//{
	//	for(w=0;w<8;w++)
	//	{
	//		if(*(BYTE*)(lpObj->pInventoryMap+(h)*8+(w)) == 255)
	//		{
	//			blank = gObjOnlyInventoryRectCheck(lpObj->m_Index, w, h, 1, 1);

	//			//if ( blank == 0xFE )
	//			//{
	//			//	continue;
	//			//	//result = FALSE;
	//			//	//break;
	//			//}

	//			//if ( blank == 0xFF )
	//			//{
	//			//	Point++;
	//			//	//return TRUE;
	//			//}

	//			if ( blank == 0xFF )
	//			{
	//				Point++;
	//			}
	//				
	//		}
	//	}
	//}
	//
	//if(lpObj->ExpandedInventory == 0)
	//{
	//	return Point;
	//}
	//
	//for(h=0;h<4;h++)
	//{
	//	for(w=0;w<8;w++)
	//	{
	//		if(*(BYTE*)((lpObj->pInventoryMap+64)+(h)*8+(w)) == 255)
	//		{
	//			blank = gObjOnlyInventoryRectCheck(lpObj->m_Index, w, h, 1, 1);

	//			//if ( blank == 0xFE )
	//			//{
	//			//	continue;
	//			//	//result = FALSE;
	//			//	//break;
	//			//}

	//			//if ( blank == 0xFF )
	//			//{
	//			//	Point++;
	//			//	//return TRUE;
	//			//}
	//			
	//			if ( blank == 0xFF )
	//			{
	//				Point++;
	//			}
	//		}
	//	}
	//}
	//
	//if(lpObj->ExpandedInventory == 1)
	//{
	//	return Point;
	//}
	//
	//for(h=0;h<4;h++)
	//{
	//	for(w=0;w<8;w++)
	//	{
	//		if(*(BYTE*)((lpObj->pInventoryMap+96)+(h)*8+(w)) == 255)
	//		{
	//			blank = gObjOnlyInventoryRectCheck(lpObj->m_Index, w, h, 1, 1);

	//			LogAdd("0x%X",blank);

	//			//if ( blank == 0xFE )
	//			//{
	//			//	continue;
	//			//	//result = FALSE;
	//			//	//break;
	//			//}

	//			//if ( blank == 0xFF )
	//			//{
	//			//	Point++;
	//			//	//return TRUE;
	//			//}
	//			if ( blank == 0xFF )
	//			{
	//				Point++;
	//			}
	//		}
	//	}
	//}

	//LogAdd("Point: %d",Point);

	//return Point;
}

bool ExIsBadFileLineV2(char *FileLine, int &Flag)
{
	if(Flag == 0)
	{
		if(isdigit(FileLine[0]))
		{
			Flag = FileLine[0] - 48;
			return true;
		}
	}
	else if(Flag < 0 || Flag > 999)	//Old 9
	{
		Flag = -1;
	}

	if(!strncmp(FileLine, "end", 3))
	{
		Flag = -1;
		return true;
	}

	if(FileLine[0] == '/' || FileLine[0] == '\n')
		return true;

	for(UINT i = 0; i < strlen(FileLine); i++)
	{
		if(isalnum(FileLine[i]))
			return false;
	}
	return true;
}

bool CheckOptions(bool bItem, int Item1, int Item2)
{
	if(bItem)
	{
		if(Item1 == Item2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(Item2 && Item2)
		{
			return true;
		}
		else if(!Item2 && !Item2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool CheckInCharacterItem(int aIndex, int ItemType)
{
	LPOBJ lpObj = &gObj[aIndex];

	for (int i=0;i<INVETORY_WEAR_SIZE;i++)
	{
		if(!lpObj->pInventory[i].IsItem())
		{
			continue;
		}

		if(lpObj->pInventory[i].m_Durability <= 0.0f)
		{
			continue;
		}

		if(lpObj->pInventory[i].m_Type != ItemType)
		{
			continue;
		}

		return true;
		
	}
	return false;
}

bool CheckInventoryItem(int aIndex, int ItemType)
{
	LPOBJ lpObj = &gObj[aIndex];

	for ( int i=INVETORY_WEAR_SIZE;i<INVENTORY_SIZE;i++)
	{
		
			if(lpObj->pInventory[i].m_Type == ItemType)
			{
				return true;
			}
	}
	return false;
}


void Max90Procent(int & Value)
{
	if(Value > 90)
	{
		Value = 90;
	}
}


int GetInventoryEmptyPoint(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int iEmptyCount = 0;

	for ( int x=0;x<64;x++)
	{
		if ( lpObj->pInventoryMap[x] == 0xFF )
		{
			iEmptyCount++;
		}
	}

	if(lpObj->ExpandedInventory == 0)
	{
		return iEmptyCount;
	}

	for ( int x=64;x<96;x++)
	{
		if ( lpObj->pInventoryMap[x] == 0xFF )
		{
			iEmptyCount++;
		}
	}

	if(lpObj->ExpandedInventory == 1)
	{
		return iEmptyCount;
	}

	for ( int x=96;x<128;x++)
	{
		if ( lpObj->pInventoryMap[x] == 0xFF )
		{
			iEmptyCount++;
		}
	}

	return iEmptyCount;
}