#include "StdAfx.h"
#include "BMQuest.h"
#include "Message.h"
#include "USER.h"
#include "Functions.h"
#include "ExLicense.h"
#include "logproc.h"
#include "SystemOfRage.h"
#include "ObjCalCharacter.h"

cBMQuest BMQuest;

void cBMQuest::StartConfig()
{
	Enable = GetPrivateProfileInt("Common","Enable",0,_DIR_BMQUEST);
	NPC = GetPrivateProfileInt("Common","NPC",0,_DIR_BMQUEST);
	NPC_Map = GetPrivateProfileInt("Common","NPC_Map",0,_DIR_BMQUEST);
	NPC_X = GetPrivateProfileInt("Common","NPC_X",0,_DIR_BMQUEST);
	NPC_Y = GetPrivateProfileInt("Common","NPC_Y",0,_DIR_BMQUEST);
	Reset = GetPrivateProfileInt("Common","Reset",0,_DIR_BMQUEST);

	this->m_sRandOptNPC_Class = GetPrivateProfileInt("Common","RandOptNPC_Class",0,_DIR_BMQUEST);
	this->m_btRandOptNPC_Map = GetPrivateProfileInt("Common","RandOptNPC_Map",0,_DIR_BMQUEST);
	this->m_btRandOptNPC_X = GetPrivateProfileInt("Common","RandOptNPC_X",0,_DIR_BMQUEST);
	this->m_btRandOptNPC_Y = GetPrivateProfileInt("Common","RandOptNPC_Y",0,_DIR_BMQUEST);

	for (int i(0);i<_MAX_CLASS_BMQUEST;i++)
	{
		for(int j(0);j<_MAX_BMQUEST;j++)
		{
			Quest[i][j].Mob = 0;
			Quest[i][j].Coun = 0;
			Quest[i][j].proc = 0;
			Quest[i][j].rew = 0;
			Quest[i][j].gift = 0;
			Quest[i][j].msg[0] = NULL;
			Quest[i][j].msg2[0] = NULL;
		}
	}
}

void cBMQuest::StartUP()
{
	if(!g_ExLicense.user.BMQuest)
	{
		Enable = false;
		return;
	}

	StartConfig();

	if(!Enable)
	{
		return;
	}

	this->m_RandOpt.clear();

	FILE *file;
	file = fopen(_DIR_BMQUEST,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"Data\\ExData\\BMQuest.ini Load Error","CRITICAL ERROR",0);
		return;
	}
	char Buff[256];
	int Flag = 0;
	Count[1] = 0;
	Count[2] = 0;
	Count[3] = 0;
	Count[4] = 0;
	Count[5] = 0;
	Count[6] = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[1][Count[1]].Mob  = n[0];
			Quest[1][Count[1]].Coun = n[1];
			Quest[1][Count[1]].proc = n[2];
			Quest[1][Count[1]].rew  = n[3];
			Quest[1][Count[1]].gift = n[4];
			sprintf(Quest[1][Count[1]].msg,"%s",mes);
			sprintf(Quest[1][Count[1]].msg2,"%s",mes2);
			Count[1]++;
		}
		if(Flag == 2)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[2][Count[2]].Mob  = n[0];
			Quest[2][Count[2]].Coun = n[1];
			Quest[2][Count[2]].proc = n[2];
			Quest[2][Count[2]].rew  = n[3];
			Quest[2][Count[2]].gift = n[4];
			sprintf(Quest[2][Count[2]].msg,"%s",mes);
			sprintf(Quest[2][Count[2]].msg2,"%s",mes2);
			Count[2]++;
		}
		if(Flag == 3)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[3][Count[3]].Mob  = n[0];
			Quest[3][Count[3]].Coun = n[1];
			Quest[3][Count[3]].proc = n[2];
			Quest[3][Count[3]].rew  = n[3];
			Quest[3][Count[3]].gift = n[4];
			sprintf(Quest[3][Count[3]].msg,"%s",mes);
			sprintf(Quest[3][Count[3]].msg2,"%s",mes2);
			Count[3]++;
		}
		if(Flag == 4)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[4][Count[4]].Mob  = n[0];
			Quest[4][Count[4]].Coun = n[1];
			Quest[4][Count[4]].proc = n[2];
			Quest[4][Count[4]].rew  = n[3];
			Quest[4][Count[4]].gift = n[4];
			sprintf(Quest[4][Count[4]].msg,"%s",mes);
			sprintf(Quest[4][Count[4]].msg2,"%s",mes2);
			Count[4]++;
		}
		if(Flag == 5)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[5][Count[5]].Mob  = n[0];
			Quest[5][Count[5]].Coun = n[1];
			Quest[5][Count[5]].proc = n[2];
			Quest[5][Count[5]].rew  = n[3];
			Quest[5][Count[5]].gift = n[4];
			sprintf(Quest[5][Count[5]].msg,"%s",mes);
			sprintf(Quest[5][Count[5]].msg2,"%s",mes2);
			Count[5]++;
		}
		if(Flag == 6)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[6][Count[6]].Mob  = n[0];
			Quest[6][Count[6]].Coun = n[1];
			Quest[6][Count[6]].proc = n[2];
			Quest[6][Count[6]].rew  = n[3];
			Quest[6][Count[6]].gift = n[4];
			sprintf(Quest[6][Count[6]].msg,"%s",mes);
			sprintf(Quest[6][Count[6]].msg2,"%s",mes2);
			Count[6]++;
		}
		if(Flag == 7)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[7][Count[7]].Mob  = n[0];
			Quest[7][Count[7]].Coun = n[1];
			Quest[7][Count[7]].proc = n[2];
			Quest[7][Count[7]].rew  = n[3];
			Quest[7][Count[7]].gift = n[4];
			sprintf(Quest[7][Count[7]].msg,"%s",mes);
			sprintf(Quest[7][Count[7]].msg2,"%s",mes2);
			Count[7]++;
		}
		if(Flag == 8)
		{
			BMQuestRandOpt_DATA list;

			sscanf(Buff,"%d %d %d %d %d %d %d %d",
				&list.NeedLevel,
				&list.NeedRageLevel,
				&list.AddDamageReflect,
				&list.AddDamage,
				&list.AddDefense,
				&list.AddCriticalDamage,
				&list.AddExcelentDamage,
				&list.AddLife);

			this->m_RandOpt.push_back(list);
		}
	}
	fclose(file);
}

void cBMQuest::AddedCharacter(int aIndex)
{
	if(!Enable)
		return;	

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	lpUser->DamageReflect += lpUser->BMDamageReflect;
	lpUser->m_AttackDamageMaxLeft += lpUser->BMDamage;
	lpUser->m_AttackDamageMinLeft += lpUser->BMDamage;
	lpUser->m_AttackDamageMaxRight += lpUser->BMDamage;
	lpUser->m_AttackDamageMinRight += lpUser->BMDamage;
	lpUser->m_MagicDamageMin += lpUser->BMDamage;
	lpUser->m_MagicDamageMax += lpUser->BMDamage;
	lpUser->m_Defense += lpUser->BMDefense;
	lpUser->m_MagicDefense += lpUser->BMDefense;
	lpUser->m_CriticalDamage += lpUser->BMCriticalDamage;
	lpUser->m_ExcelentDamage += lpUser->BMExcelentDamage;
}

void cBMQuest::CharacterInformation(int aIndex)
{
	if(!Enable)
		return;

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}
	
	MessageChat(aIndex,"@[BMInfo] +%d Reflect",lpUser->BMDamageReflect);
	MessageChat(aIndex,"@[BMInfo] +%d Damage",lpUser->BMDamage);
	MessageChat(aIndex,"@[BMInfo] +%d Defense",lpUser->BMDefense);
	MessageChat(aIndex,"@[BMInfo] +%d CritDamage",lpUser->BMCriticalDamage);
	MessageChat(aIndex,"@[BMInfo] +%d ExcDamage",lpUser->BMExcelentDamage);
	MessageChat(aIndex,"@[BMInfo] +%d Life",lpUser->BMLife);
}

bool cBMQuest::NPCClick(int aIndex,int aNPC)
{
	if(!this->Enable)
	{
 		return false;
	}

	if ( OBJMAX_RANGE(aIndex) == FALSE || OBJMAX_RANGE(aNPC) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return false;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNPC];

	if(		lpNpc->Class		== this->NPC 
		&&	lpNpc->MapNumber	== this->NPC_Map
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{
		NPCdialogue(aIndex,aNPC);
		return true;
	}

	return false;
}

void cBMQuest::NPCdialogue(int aIndex,int aNPC)
{
	if ( OBJMAX_RANGE(aIndex) == FALSE || OBJMAX_RANGE(aNPC) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNPC];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(lpUser->Reset < Reset)
	{
		char Buffs[100];
		sprintf(Buffs,"Mission is available with %d reset",Reset);
		ChatTargetSend(lpNpc,Buffs,aIndex);
		return;
	}

	int QClass = lpUser->Class+1;
	//Проверяем не закончен ли квест
	if(lpUser->BMQuest_num < Count[QClass])
	{
		//Проверяем начат ли уже квест
		if(lpUser->BMQuest_start == 0)
		{
			ChatTargetSend(lpNpc,"Good luck!",aIndex);
			lpUser->BMQuest_start = 1;
			//exQueryUpdate("UPDATE Character SET BMQuest_start = 1 WHERE Name='%s'", NULL->Name);
			MessageChat(aIndex,"@[BMQuest] Mission: %d",lpUser->BMQuest_num+1);
			MessageChat(aIndex,"@[BMQuest] %s",Quest[QClass][lpUser->BMQuest_num].msg);
			MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
				Quest[QClass][lpUser->BMQuest_num].msg2,
				lpUser->BMQuest_kill,
				Quest[QClass][lpUser->BMQuest_num].Coun);
		}
		//Если квест уже взят
		else if(lpUser->BMQuest_start == 1)
		{
			//Если квест выполнен
			if(lpUser->BMQuest_kill >= Quest[QClass][lpUser->BMQuest_num].Coun)
			{
				Presents(aIndex,
					Quest[QClass][lpUser->BMQuest_num].rew,
					Quest[QClass][lpUser->BMQuest_num].gift); //Функция вознаграждения

				lpUser->BMQuest_start = 0;
				lpUser->BMQuest_num++;
				lpUser->BMQuest_kill = 0;
				ChatTargetSend(lpNpc,"You completed the mission!",aIndex);
				//exQueryUpdate("UPDATE Character SET BMQuest_start = 0 WHERE Name='%s'", NULL->Name);
				//exQueryUpdate("UPDATE Character SET BMQuest_num = BMQuest_num + 1 WHERE Name='%s'", NULL->Name);
				//MySQL.Execute("UPDATE Character SET BMQuest_kill = 0 WHERE Name='%s'",NULL->Name);
				if(lpUser->BMQuest_num == Count[QClass])
				{
					MessageChat(aIndex,"@[BMQuest] Finish");
				}
			}
			//Если квест не выполнен
			else
			{
				ChatTargetSend(lpNpc,"Your Mission is not finished!",aIndex);
				MessageChat(aIndex,"@[BMQuest] Mission: %d",lpUser->BMQuest_num+1);
				MessageChat(aIndex,"@[BMQuest] %s",Quest[QClass][lpUser->BMQuest_num].msg);
				MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
					Quest[QClass][lpUser->BMQuest_num].msg2,
					lpUser->BMQuest_kill,
					Quest[QClass][lpUser->BMQuest_num].Coun);
			}
		}
	}
	else
	{
		ChatTargetSend(lpNpc,"You have completed all the Mission!",aIndex);
		MessageChat(aIndex,"@[BMQuest] Finish");
	}
}

void cBMQuest::MonsterKill(int aIndex, int mIndex)
{
	if(!Enable)
		return;
	
	if ( OBJMAX_RANGE(aIndex) == FALSE || OBJMAX_RANGE(mIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[mIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	int QClass = lpUser->Class+1;

	if(lpUser->BMQuest_start == 1 && lpMonster->Class == Quest[QClass][lpUser->BMQuest_num].Mob)
	{
		int iRate = rand()%100+1;

		if(Quest[QClass][lpUser->BMQuest_num].proc >= iRate)
		{			
			if(lpUser->BMQuest_kill < Quest[QClass][lpUser->BMQuest_num].Coun)
			{
				lpUser->BMQuest_kill++;
				//MySQL.Execute("UPDATE Character SET BMQuest_kill = BMQuest_kill + 1 WHERE Name='%s'",NULL->Name);
				MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
					Quest[QClass][lpUser->BMQuest_num].msg2,
					lpUser->BMQuest_kill,
					Quest[QClass][lpUser->BMQuest_num].Coun);
			
				if(lpUser->BMQuest_kill == Quest[QClass][lpUser->BMQuest_num].Coun)
				{
					MessageChat(aIndex,"@[BMQuest] Mission accomplished!");
				}
			}
		}
	}
}

void cBMQuest::Presents(int aIndex, int Present, int Gifts)
{
	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}
	
	/*
		1 - BMDamageReflect;
		2 - BMDamage;
		3 - BMDefense;
		4 - BMCriticalDamage;
		5 - BMExcelentDamage;
		6 - BMLife;
	*/
	if(Present == 1)		//BMDamageReflect
	{
		lpUser->BMDamageReflect += Gifts;
		//exQueryUpdate("UPDATE Character SET BMDamageReflect = BMDamageReflect + %d WHERE Name='%s'", Gifts, NULL->Name);
		MessageChat(aIndex,"@[BMQuest] DamageReflect: +%d",Gifts);
	}
	else if(Present == 2)	//BMDamage
	{
		lpUser->BMDamage += Gifts;
		//exQueryUpdate("UPDATE Character SET BMDamage = BMDamage + %d WHERE Name='%s'", Gifts, NULL->Name);
		MessageChat(aIndex,"@[BMQuest] Damage: +%d",Gifts);
	}
	else if(Present == 3)	//BMDefense
	{
		lpUser->BMDefense += Gifts;
		//exQueryUpdate("UPDATE Character SET BMDefense = BMDefense + %d WHERE Name='%s'", Gifts, NULL->Name);
		MessageChat(aIndex,"@[BMQuest] Defense: +%d",Gifts);
	}
	else if(Present == 4)	//BMCriticalDamage
	{
		lpUser->BMCriticalDamage += Gifts;
		//exQueryUpdate("UPDATE Character SET BMCriticalDamage = BMCriticalDamage + %d WHERE Name='%s'", Gifts, NULL->Name);
		MessageChat(aIndex,"@[BMQuest] CriticalDamage: +%d",Gifts);
	}
	else if(Present == 5)	//BMExcelentDamage
	{
		lpUser->BMExcelentDamage += Gifts;
		//exQueryUpdate("UPDATE Character SET BMExcelentDamage = BMExcelentDamage + %d WHERE Name='%s'", Gifts, NULL->Name);
		MessageChat(aIndex,"@[BMQuest] ExcelentDamage: +%d",Gifts);
	}
	else if(Present == 6)	//BMLife
	{
		lpUser->BMLife += Gifts;
		//exQueryUpdate("UPDATE Character SET BMLife = BMLife + %d WHERE Name='%s'", Gifts, NULL->Name);
		MessageChat(aIndex,"@[BMQuest] Life: +%d",Gifts);
	}
	//LevelUpEffect (aIndex,1);
	ExFireCracker(aIndex, lpUser->X, lpUser->Y);
}

bool cBMQuest::RandOptNpcDialog(int aIndex, int aNpcIndex)
{
	if(!THINNAKORN_MAC)
	{
		return false;
	}

	if(!this->Enable)
	{
		return false;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aNpcIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(lpNpc->Class == this->m_sRandOptNPC_Class && lpNpc->MapNumber == this->m_btRandOptNPC_Map && lpNpc->X == this->m_btRandOptNPC_X && lpNpc->Y == this->m_btRandOptNPC_Y)
	{
		if(lpUser->Level >= 400 || gSystemOfRage.rUser[aIndex].rLevel == 300)
		{

		}

		//MessageChat(aIndex,"@[BMInfo] +%d Reflect",lpUser->BMDamageReflect);
		//MessageChat(aIndex,"@[BMInfo] +%d Damage",lpUser->BMDamage);
		//MessageChat(aIndex,"@[BMInfo] +%d Defense",lpUser->BMDefense);
		////MessageChat(aIndex,"@[BMInfo] +%d CritDamage",lpUser->BMCriticalDamage);
		//MessageChat(aIndex,"@[BMInfo] +%d ExcDamage",lpUser->BMExcelentDamage);
		//MessageChat(aIndex,"@[BMInfo] +%d Life",lpUser->BMLife);

		//MsgOutput(aIndex, "[BMQuest] Random option", iTotalRagePoint);

		return true;
	}

	return false;
}

void cBMQuest::CheckLevels(int aIndex)
{
	if(!THINNAKORN_MAC)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	for(int i = 0; i < this->m_RandOpt.size(); i++)
	{	
		if(lpUser->Level == this->m_RandOpt[i].NeedLevel && gSystemOfRage.rUser[aIndex].rLevel == this->m_RandOpt[i].NeedRageLevel)
		{
			int iRand = rand()%6;

			switch(iRand)
			{
			case 0:
				{
					lpUser->BMDamageReflect += this->m_RandOpt[i].AddDamageReflect;
					MessageChat(aIndex, "@[BMQuest] Random option Reflect: +%d", this->m_RandOpt[i].AddDamageReflect);
				}
				break;
			case 1:
				{
					lpUser->BMDamage += this->m_RandOpt[i].AddDamage;
					MessageChat(aIndex, "@[BMQuest] Random option Damage: +%d", this->m_RandOpt[i].AddDamage);
				}
				break;
			case 2:
				{
					lpUser->BMDefense += this->m_RandOpt[i].AddDefense;
					MessageChat(aIndex, "@[BMQuest] Random option Defence: +%d", this->m_RandOpt[i].AddDefense);
				}
				break;
			case 3:
				{
					lpUser->BMCriticalDamage += this->m_RandOpt[i].AddCriticalDamage;
					MessageChat(aIndex, "@[BMQuest] Random option Critical Damage: +%d", this->m_RandOpt[i].AddCriticalDamage);
				}
				break;
			case 4:
				{
					lpUser->BMExcelentDamage += this->m_RandOpt[i].AddExcelentDamage;
					MessageChat(aIndex, "@[BMQuest] Random option Exellent Damage: +%d", this->m_RandOpt[i].AddExcelentDamage);
				}
				break;
			case 5:
				{
					lpUser->BMLife += this->m_RandOpt[i].AddLife;
					MessageChat(aIndex, "@[BMQuest] Random option Life: +%d", this->m_RandOpt[i].AddLife);
				}
				break;
			}

			gObjCalCharacter(aIndex);
			ExFireCracker(aIndex, lpUser->X, lpUser->Y);
			return;
		}
	}
}
