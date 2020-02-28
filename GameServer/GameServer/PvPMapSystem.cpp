#include "StdAfx.h"
#include "user.h"
#include "Functions.h"
#include "MapClass.h"
#include "PvPMapSystem.h"

cPvPMapSystem PvPMapSystem;

void cPvPMapSystem::LoadConfig()
{
	this->EnablePvPMap = GetPrivateProfileInt("Common","EnablePvPMap",0,PVPMAPSYSTEM_DIR);
	this->EnableLoraRing = GetPrivateProfileInt("Common","EnableLoraRing",0,PVPMAPSYSTEM_DIR);

	//lpObj->X >= 137 && lpObj->X <= 144 && lpObj->Y >= 124 && lpObj->Y <= 131
	this->m_LoraRingX1 = GetPrivateProfileInt("Common","LoraRingX1",137,PVPMAPSYSTEM_DIR);
	this->m_LoraRingY1 = GetPrivateProfileInt("Common","LoraRingY1",124,PVPMAPSYSTEM_DIR);
	this->m_LoraRingX2 = GetPrivateProfileInt("Common","LoraRingX2",144,PVPMAPSYSTEM_DIR);
	this->m_LoraRingY2 = GetPrivateProfileInt("Common","LoraRingY2",131,PVPMAPSYSTEM_DIR);

	for(int i(0);i<MAX_NUMBER_MAP;i++)
	{
		this->PvP[i].Map = 0;
		this->PvP[i].Status = 0;
	}

	FILE * file = fopen(PVPMAPSYSTEM_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,PVPMAPSYSTEM_DIR,"LOAD FILE ERROR",0);
		this->EnablePvPMap = false;
	}
	if(!this->EnablePvPMap)return;

	char Buff[256];
	int Flag = 0;
	this->pCount = 0;

#ifdef _CONFLICT_
#ifdef _FIX_PK_IN_DUEL_
	this->PvP[this->pCount].Map		= 64;
	this->PvP[this->pCount].Status	= 1;
#if UPDATE_PVP == 1
	this->PvP[this->pCount].X1		= 0;
	this->PvP[this->pCount].Y1		= 0;
	this->PvP[this->pCount].X2		= 255;
	this->PvP[this->pCount].Y2		= 255;
#endif
	this->pCount++;
#endif
#endif
	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[6];
#if UPDATE_PVP == 1
			sscanf(Buff, "%d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
			this->PvP[this->pCount].Map		= n[0];
			this->PvP[this->pCount].Status	= n[1];
			this->PvP[this->pCount].X1		= n[2];
			this->PvP[this->pCount].Y1		= n[3];
			this->PvP[this->pCount].X2		= n[4];
			this->PvP[this->pCount].Y2		= n[5];
#else
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->PvP[this->pCount].Map = n[0];
			this->PvP[this->pCount].Status = n[1];
#endif
			this->pCount++;
		}
	}
	fclose(file);
}
//0 - Нормально, 1 - можно убивать и не фонишся, 2 - нельзя атаковать цель
bool cPvPMapSystem::CheckAttackMap(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(!this->EnablePvPMap) return true;
	if(lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER)
	{
		for(int i=0;i<this->pCount;i++)
		{
			if(this->PvP[i].Map == lpObj->MapNumber && this->PvP[i].Status == 2)
			{
				if(		(lpObj->X >= this->PvP[i].X1 && lpObj->X <= this->PvP[i].X2)
					&&	(lpObj->Y >= this->PvP[i].Y1 && lpObj->Y <= this->PvP[i].Y2) )
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool cPvPMapSystem::CheckPkMap(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(!this->EnablePvPMap) return true;
	if(lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER)
	{
		if(this->EnableLoraRing)
		{
			if(lpObj->MapNumber==0 && lpObj->X >= this->m_LoraRingX1 && lpObj->X <= this->m_LoraRingX2 && lpObj->Y >= this->m_LoraRingY1 && lpObj->Y <= this->m_LoraRingY2) return false;
		}
		for(int i=0;i<this->pCount;i++)
		{
			if(this->PvP[i].Map == lpObj->MapNumber && this->PvP[i].Status == 1)
			{
				if(		(lpObj->X >= this->PvP[i].X1 && lpObj->X <= this->PvP[i].X2)
					&&	(lpObj->Y >= this->PvP[i].Y1 && lpObj->Y <= this->PvP[i].Y2) )
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool cPvPMapSystem::CheckPvPMap(LPOBJ lpObj)
{
	if(!this->EnablePvPMap) return true;

	if(lpObj->Type == OBJ_USER)
	{
		for(int i=0;i<this->pCount;i++)
		{
			if(this->PvP[i].Map == lpObj->MapNumber && this->PvP[i].Status == 2)
			{
				if(	(lpObj->X >= this->PvP[i].X1 && lpObj->X <= this->PvP[i].X2) &&	
					(lpObj->Y >= this->PvP[i].Y1 && lpObj->Y <= this->PvP[i].Y2) )
				{
					return false;
				}
			}
		}
	}

	return true;
}