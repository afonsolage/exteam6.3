#include "StdAfx.h"
#include "BlockMoveItem.h"
#include "Functions.h"
#include "user.h"
#include "logproc.h"

cBlockMoveItem gBlockMoveIteml;

void cBlockMoveItem::Load()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,BLOCK_MOVE_ITEM_DIR);
	this->MaxLevel = GetPrivateProfileInt("Common","MaxLevel",0,BLOCK_MOVE_ITEM_DIR);
	this->MaxExlOpt = GetPrivateProfileInt("Common","MaxExlOpt",0,BLOCK_MOVE_ITEM_DIR);
	for(int i(0);i<BMI_MAX_ITEM;i++)
	{
		this->bmi[i].Type = 0;
		this->bmi[i].Index = 0;
	}
	FILE * file = fopen(BLOCK_MOVE_ITEM_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,BLOCK_MOVE_ITEM_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
	}
	if(!this->Enable)return;

	char Buff[256];
	int Flag = 0;
	this->Count = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[2];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->bmi[this->Count].Type = n[0];
			this->bmi[this->Count].Index = n[1];
			this->Count++;
		}
	}
	fclose(file);
}

bool cBlockMoveItem::ItemMoveBlockExlOpt(int exlopt_num)
{
//#ifdef DEBUG_CODE
	//LogAddC(2,"EXL MOVE %d",exlopt_num);
//#endif
	if(this->MaxExlOpt == 0) return true;
	int ExlOptCount = 0;
	switch (exlopt_num)
	{
		case 0: ExlOptCount = 0; break; case 1: ExlOptCount = 1; break; case 2: ExlOptCount = 1; break; case 3: ExlOptCount = 2; break; case 4: ExlOptCount = 1; break;
		case 5: ExlOptCount = 2; break; case 6: ExlOptCount = 2; break; case 7: ExlOptCount = 3; break; case 8: ExlOptCount = 1; break; case 9: ExlOptCount = 2; break;
		case 10:ExlOptCount = 2; break; case 11:ExlOptCount = 3; break; case 12:ExlOptCount = 2; break; case 13:ExlOptCount = 3; break; case 14:ExlOptCount = 3; break;
		case 15:ExlOptCount = 4; break; case 16:ExlOptCount = 1; break; case 17:ExlOptCount = 2; break; case 18:ExlOptCount = 2; break; case 19:ExlOptCount = 3; break;
		case 20:ExlOptCount = 2; break; case 21:ExlOptCount = 3; break; case 22:ExlOptCount = 3; break; case 23:ExlOptCount = 4; break; case 24:ExlOptCount = 2; break;
		case 25:ExlOptCount = 3; break; case 26:ExlOptCount = 3; break; case 27:ExlOptCount = 4; break; case 28:ExlOptCount = 3; break; case 29:ExlOptCount = 4; break;
		case 30:ExlOptCount = 4; break; case 31:ExlOptCount = 5; break; case 32:ExlOptCount = 1; break; case 33:ExlOptCount = 2; break; case 34:ExlOptCount = 2; break;
		case 35:ExlOptCount = 3; break; case 36:ExlOptCount = 2; break; case 37:ExlOptCount = 3; break; case 38:ExlOptCount = 3; break; case 39:ExlOptCount = 4; break;
		case 40:ExlOptCount = 2; break; case 41:ExlOptCount = 3; break; case 42:ExlOptCount = 3; break; case 43:ExlOptCount = 4; break; case 44:ExlOptCount = 3; break;
		case 45:ExlOptCount = 4; break; case 46:ExlOptCount = 4; break; case 47:ExlOptCount = 5; break; case 48:ExlOptCount = 2; break; case 49:ExlOptCount = 3; break;
		case 50:ExlOptCount = 3; break; case 51:ExlOptCount = 4; break; case 52:ExlOptCount = 3; break; case 53:ExlOptCount = 4; break; case 54:ExlOptCount = 4; break;
		case 55:ExlOptCount = 5; break; case 56:ExlOptCount = 3; break; case 57:ExlOptCount = 4; break; case 58:ExlOptCount = 4; break; case 59:ExlOptCount = 5; break;
		case 60:ExlOptCount = 4; break; case 61:ExlOptCount = 5; break; case 62:ExlOptCount = 5; break; case 63:ExlOptCount = 6; break; 
	}
	//LogAddC(2,"EXL MOVE %d",ExlOptCount);
	if(ExlOptCount > this->MaxExlOpt) return false;
	else return true;
}

bool cBlockMoveItem::Move(int aIndex, int Pos)
{
	if(!this->Enable)return true;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->pInventory[Pos].m_Level > this->MaxLevel)
	{
		return false;
	}

	if(this->ItemMoveBlockExlOpt(lpObj->pInventory[Pos].m_NewOption) == false)
	{
		return false;
	}

	for(int i=0;i<this->Count;i++)
	{
		if(lpObj->pInventory[Pos].m_Type == ITEMGET(this->bmi[i].Type,this->bmi[i].Index))
		{
			return false;
		}
	}

	return true;
}

bool cBlockMoveItem::Sell(int aIndex, int Pos)
{
	if(!this->Enable)return true;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->pInventory[Pos].m_Number == 1 || lpObj->pInventory[Pos].m_Number == 2 ) return true;

	if(lpObj->pInventory[Pos].m_Level > this->MaxLevel)
	{
		return false;
	}

	if(this->ItemMoveBlockExlOpt(lpObj->pInventory[Pos].m_NewOption) == false)
	{
		return false;
	}

	for(int i=0;i<this->Count;i++)
	{
		if(lpObj->pInventory[Pos].m_Type == ITEMGET(this->bmi[i].Type,this->bmi[i].Index))
		{
			return false;
		}
	}

	return true;
}