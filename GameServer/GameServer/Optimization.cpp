#include "StdAfx.h"
#include "Optimization.h"
#include "user.h"
#include "logproc.h"
#include "GameMain.h"
#include "GameServer.h"
#include "AcceptIp.h"

#if(ENABLE_OPTIMIZATION)

COptimization g_Optimization;

COptimization::COptimization()
{
	for(int i = 0; i < OBJMAX; i++)
	{
		this->m_MemoryObject[i] = false;
	}

	this->m_UserIndex = OBJ_STARTUSERINDEX;
	this->m_MonsterIndex = 0;
	this->m_ReCallIndex = OBJ_MAXMONSTER;
}

COptimization::~COptimization()
{
}

void COptimization::Load()
{

}

void COptimization::Run()
{
	//return;

	//system("cls");
	//g_Console.Output(eCNS::CGREY, "User: %d | Monsters: %d | ReCalls: %d", this->m_UserIndex, this->m_MonsterIndex, this->m_ReCallIndex);
	
}

void COptimization::AddedMemoryObject(int aIndex)
{
	if(this->m_MemoryObject[aIndex])
	{
		return;
	}

	this->m_crit.lock();

	gObj[aIndex].m_lpMagicBack = new CMagicInf[MAGIC_SIZE];
	gObj[aIndex].Magic = new CMagicInf[MAGIC_SIZE];

	if(aIndex >= OBJ_STARTUSERINDEX)
	{
		gObj[aIndex].Inventory1 = new CItem[INVENTORY_SIZE];
		gObj[aIndex].Inventory2 = new CItem[INVENTORY_SIZE];
		gObj[aIndex].InventoryMap1 = new BYTE[INVENTORY_MAP_SIZE];
		gObj[aIndex].InventoryMap2 = new BYTE[INVENTORY_MAP_SIZE];

		gObj[aIndex].Trade = new CItem[TRADE_BOX_SIZE];
		gObj[aIndex].TradeMap = new BYTE[TRADE_BOX_MAP_SIZE];
		gObj[aIndex].pWarehouse = new CItem[WAREHOUSE_SIZE];
		gObj[aIndex].pWarehouseMap = new BYTE[WAREHOUSE_SIZE];

		gObj[aIndex].PerSocketContext = new _PER_SOCKET_CONTEXT;
	}

	this->m_crit.unlock();

	this->m_MemoryObject[aIndex] = true;
}

int COptimization::GetFirstEmptryIndex(int StartIndex, int MaxIndex)
{
	for(short aIndex = StartIndex; aIndex < MaxIndex; aIndex++)
	{
		if(gObj[aIndex].Connected == PLAYER_EMPTY)
		{
			return aIndex;
		}
	}

	return -1;
}

int COptimization::AddObjectUser(SOCKET aSocket, char* ip)
{
	if(gDisconnect == 1)
	{
		return -1;
	}

	if(gObjTotalUser >= gServerMaxUser)
	{
		if (acceptIP.IsIp(ip) == 0 )
		{
			GCJoinSocketResult(4, aSocket);
			return -1;
		}
	}

	int aIndex = this->GetFirstEmptryIndex(OBJ_STARTUSERINDEX, OBJMAX);

	if(this->m_UserIndex <= aIndex)
	{
		this->m_UserIndex = aIndex + 1;
	}

	return aIndex;
}

int COptimization::AddObjectOffmoder()
{
	if(gDisconnect == 1)
	{
		return -1;
	}

	if(gObjTotalUser >= gServerMaxUser)
	{
		return -1;
	}

	int aIndex = this->GetFirstEmptryIndex(OBJ_STARTUSERINDEX, OBJMAX);

	this->AddedMemoryObject(aIndex);

	if(this->m_UserIndex <= aIndex)
	{
		this->m_UserIndex = aIndex + 1;
	}

	return aIndex;
}

int COptimization::AddObjectMonster()
{
	int aIndex = this->GetFirstEmptryIndex(0, OBJ_MAXMONSTER);

	if(aIndex == -1)
	{
		return -1;
	}

	this->AddedMemoryObject(aIndex);

	gObjCharZeroSet(aIndex);
	gObj[aIndex].m_Index = aIndex;
	gObj[aIndex].Connected = PLAYER_CONNECTED;

	if(this->m_MonsterIndex <= aIndex)
	{
		this->m_MonsterIndex = aIndex + 1;
	}

	return aIndex;
}

int COptimization::AddObjectReCall()
{
	int aIndex = this->GetFirstEmptryIndex(OBJ_MAXMONSTER, OBJ_STARTUSERINDEX);

	if(aIndex == -1)
	{
		return -1;
	}

	this->AddedMemoryObject(aIndex);

	gObjCharZeroSet(aIndex);
	gObj[aIndex].m_Index = aIndex;
	gObj[aIndex].Connected = PLAYER_CONNECTED;

	if(this->m_ReCallIndex <= aIndex)
	{
		this->m_ReCallIndex = aIndex + 1;
	}

	return aIndex;
}

void COptimization::ViewePortCPU(short aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(lpObj->RegenOk > 0)
	{
		return;
	}

	int mapnum = lpObj->MapNumber;
	gItemLoop2 = 0;

	if(lpObj->Type == OBJ_USER)
	{
		MapClass * lpMap = &MapC[mapnum];

		for(int n = 0; n < MAX_MAPITEM; n++)
		{
			if(lpMap->m_cItem[n].live)
			{
				gItemLoop2++;

				if(lpMap->m_cItem[n].m_State == 1 || lpMap->m_cItem[n].m_State == 2)
				{
					if(gObjCheckViewport(aIndex,lpMap->m_cItem[n].px,lpMap->m_cItem[n].py) == 1)
					{
						ViewportAdd(aIndex,n,5);
					}
				}
			}
		}
	}

	if(aIndex == 0)
	{
		gItemLoopMax = gItemLoop2;
		gItemLoop = gItemLoop2;
		gCurPaintPlayer = aIndex;
	}

	LPOBJ lpTempObj;

	if(lpObj->Type == OBJ_USER)
	{
		for(int n = 0; n < OBJMAX; n++)
		{
			lpTempObj = &gObj[n];

			if(lpTempObj->Connected == PLAYER_PLAYING && aIndex != n)
			{
				if(lpTempObj->m_State == 1 || lpTempObj->m_State == 2)
				{
					if(mapnum == lpTempObj->MapNumber)
					{
						if(gObjCheckViewport(aIndex,lpTempObj->X,lpTempObj->Y) == 1)
						{
							ViewportAdd(aIndex,n,lpTempObj->Type);
							ViewportAdd2(n,aIndex,gObj[aIndex].Type);
						}
					}
				}
			}
		}
	}
	else if(lpObj->Type == OBJ_MONSTER
#if(GS_CASTLE==1)
		|| lpObj->Type == OBJ_NPC && lpObj->MapNumber == MAP_INDEX_CASTLESIEGE
#endif
		)
	{
		for(int n = OBJ_MAXMONSTER; n < this->m_ReCallIndex; n++)
		{
			if(gObj[n].Connected == PLAYER_PLAYING && aIndex != n)
			{
				if(gObj[n].m_State == 1 || gObj[n].m_State == 2)
				{
					if(mapnum == gObj[n].MapNumber)
					{
						if(gObjCheckViewport(aIndex,gObj[n].X,gObj[n].Y) == 1)
						{
							ViewportAdd(aIndex,n,gObj[n].Type);
							ViewportAdd2(n,aIndex,gObj[aIndex].Type);
						}
					}
				}
			}
		}

		for(int n = OBJ_STARTUSERINDEX; n < this->m_UserIndex; n++)
		{
			if(gObj[n].Connected == PLAYER_PLAYING && aIndex != n)
			{
				if(gObj[n].m_State == 1 || gObj[n].m_State == 2)
				{
					if(mapnum == gObj[n].MapNumber)
					{
						if(gObjCheckViewport(aIndex,gObj[n].X,gObj[n].Y) == 1)
						{
							ViewportAdd(aIndex,n,gObj[n].Type);
							ViewportAdd2(n,aIndex,gObj[aIndex].Type);
						}
					}
				}
			}
		}
	}
}

int COptimization::GetU()
{
	return this->m_UserIndex;
}

int COptimization::GetM()
{
	return this->m_MonsterIndex;
}

int COptimization::GetC()
{
	return this->m_ReCallIndex;
}

#endif