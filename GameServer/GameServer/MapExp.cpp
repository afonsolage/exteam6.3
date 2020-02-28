#include "StdAfx.h"

#include "user.h"
#include "MapExp.h"
#include "Functions.h"

cMapExp gMapExp;

void cMapExp::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,MAP_EXP_DIR);
	for(int i(0);i<MAX_NUMBER_MAP;i++)
	{
		this->Number[i].Map = 0;
		this->Number[i].Exp = 0;
	}
	FILE * file = fopen(MAP_EXP_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,MAP_EXP_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
	}
	if(!this->Enable)return;

	char Buff[256];
	int Flag = 0;
	this->rCount = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[2];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Number[this->rCount].Map = n[0];
			this->Number[this->rCount].Exp = n[1];
			this->rCount++;
		}
	}
	fclose(file);
}

void cMapExp::Main(LPOBJ lpObj, __int64 & Experience)
{
	if(!this->Enable) return;
	int aIndex = lpObj->m_Index;
	__int64 NewExp = Experience;
	for(int i=0;i<this->rCount;i++)
	{
		if(this->Number[i].Map == lpObj->MapNumber)
		{
			NewExp = (( NewExp * this->Number[i].Exp ) / 100 );
			break;
		}
	}
	Experience = NewExp;
}
