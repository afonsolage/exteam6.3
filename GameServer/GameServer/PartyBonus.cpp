#include "stdafx.h"
#include "PartyBonus.h"
#include "user.h"
#include "Functions.h"
#include "PartyClass.h"
#include "GameMain.h"

PartyBonus gPartyBonus;

void PartyBonus::Init()
{
	this->Enable = 0;
	for (int i = 0; i < MAX_CLASS_BONUS; i++)
	{
		ClassBonus[i].dw = 0;
		ClassBonus[i].dk = 0;
		ClassBonus[i].elf = 0;
		ClassBonus[i].mg = 0;
		ClassBonus[i].dl = 0;
		ClassBonus[i].sum = 0;
		ClassBonus[i].rf = 0;
		ClassBonus[i].Bonus = 0;
	}
	this->nearbycount2  = 0;
	this->nearbycount3  = 0;
	this->nearbycount4  = 0;
	this->nearbycount5  = 0;
	this->Count = 0;

}

void PartyBonus::Load()
{
	this->Init();


	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,PartyBonus_DIR);
	
	this->nearbycount1	= GetPrivateProfileInt("ExTeam","nearbycount1",100,PartyBonus_DIR);
	this->nearbycount2	= GetPrivateProfileInt("ExTeam","nearbycount2",100,PartyBonus_DIR);
	this->nearbycount3  = GetPrivateProfileInt("ExTeam","nearbycount3",100,PartyBonus_DIR);
	this->nearbycount4  = GetPrivateProfileInt("ExTeam","nearbycount4",100,PartyBonus_DIR);
	this->nearbycount5	= GetPrivateProfileInt("ExTeam","nearbycount5",100,PartyBonus_DIR);

	FILE * file = fopen(PartyBonus_DIR,"r");
	char Buff[256];
	int Flag = 0;

	if(file == NULL)
	{
		MessageBoxA(0,PartyBonus_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
	}

	if(!this->Enable) return;

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			int n[8];
			sscanf(Buff, "%d %d %d %d %d %d %d %d" , &n[0], &n[1], &n[2], &n[3] , &n[4], &n[5], &n[6], &n[7]);
			ClassBonus[this->Count].dw	=	n[0];
			ClassBonus[this->Count].dk	=	n[1];
			ClassBonus[this->Count].elf	=	n[2];
			ClassBonus[this->Count].mg	=	n[3];
			ClassBonus[this->Count].dl	=	n[4];
			ClassBonus[this->Count].sum	=	n[5];
			ClassBonus[this->Count].rf	=	n[6];
			ClassBonus[this->Count].Bonus	=	n[7];
			this->Count++;
			if (this->Count >= MAX_CLASS_BONUS) return;
		}
	}
	fclose(file);

}

int PartyBonus::ExpNearbyCount(LPOBJ lpObj, LPOBJ lpTargetObj, int viewplayer)
{
	if(!this->Enable) return gAddExperience;
	
	LPOBJ lpPartyObj;
	int dis[MAX_USER_IN_PARTY];

	
	int partynum = lpObj->PartyNumber;
	
	int number = 0;
	int ViewCount = 0;

	for(int n = 0; n < MAX_USER_IN_PARTY; n++)
	{
		number = gParty.m_PartyS[partynum].Number[n];
		if(number >= 0)
		{

			lpPartyObj = &gObj[number];
			
			if(lpTargetObj->MapNumber == lpPartyObj->MapNumber)
			{
				dis[n] = gObjCalDistance(lpTargetObj,&gObj[number]);

				if(dis[n] < 10)
				{
					ViewCount++;
				}
			}
		}
	}


	if (ViewCount == 2)	
	{
		return int(nearbycount2);
	}
	else if (ViewCount == 3)
	{
		return int(nearbycount3);
	}
	else if (ViewCount == 4)
	{
		return int(nearbycount4);
	}
	else if (ViewCount >= 5)
	{
		return int(nearbycount5);
	}
	return this->nearbycount1;
}

int PartyBonus::ExpClassBonus(LPOBJ lpObj, LPOBJ lpTargetObj, int viewplayer)
{
	if(!this->Enable) return false;

	LPOBJ lpPartyObj;
	int dis[MAX_USER_IN_PARTY];
	
	int dwCount = 0;
	int dkCount = 0;
	int elfCount = 0;
	int mgCount = 0;
	int dlCount = 0;
	int sumCount = 0;
	int rfCount = 0;
	int number = 0;

	int partynum = lpObj->PartyNumber;
	
	for(int n = 0; n < MAX_USER_IN_PARTY; n++)
	{
		number = gParty.m_PartyS[partynum].Number[n];
		if(number >= 0)
		{
			lpPartyObj = &gObj[number];
			
			if(lpTargetObj->MapNumber == lpPartyObj->MapNumber)
			{
				dis[n] = gObjCalDistance(lpTargetObj,&gObj[number]);

				if(dis[n] < 10)
				{
					if (lpPartyObj->Class == CLASS_WIZARD)
					{
						dwCount++;
					}	
					else if (lpPartyObj->Class == CLASS_KNIGHT)
					{
						dkCount++;
					}
					else if (lpPartyObj->Class == CLASS_ELF)
					{
						elfCount++;
					}
					else if(lpPartyObj->Class == CLASS_MAGUMSA)
					{
						mgCount++;
					}
					else if(lpPartyObj->Class == CLASS_DARKLORD)
					{
						dlCount++;
					}
					else if (lpPartyObj->Class == CLASS_SUMMONER)
					{
						sumCount++;
					}
					else if (lpPartyObj->Class == CLASS_MONK)
					{
						rfCount++;
					}
				}
			}
		}
	}
	for (int i = 0; i < this->Count; i++)
	{
		if (ClassBonus[i].dw == dwCount)
			if (ClassBonus[i].dk == dkCount)
				if (ClassBonus[i].elf == elfCount)
					if (ClassBonus[i].mg == mgCount)
						if (ClassBonus[i].dl == dlCount)
							if (ClassBonus[i].sum == sumCount)
								if (ClassBonus[i].rf == rfCount)
								{
									return int(ClassBonus[i].Bonus);
								}
	}
	return 100;
			
}

bool PartyBonus::isEnable(int viewplayer)
{
	if(!this->Enable) return false;
	else return true;
}
