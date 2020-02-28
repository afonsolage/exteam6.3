#include "StdAfx.h"
#include "user.h"
#include "QuestSystem.h"
#include "..\include\ReadScript.h"
#include "Message.h"
#include "Functions.h"
#include "DSProtocol.h"

NewS5Quest S5Quest;

void NewS5Quest::ReadConfig()
{
	SMDFile = fopen(ELFQUEST_DIR, "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,"[ElfQuest] Info file Load Fail [..\\Data\\Quest\\ElfQuest.ini]","CRITICAL ERROR",0);
		ExitProcess(1);
	}

	int Token;
	int type = -1;
	this->eCount = 1;

	while ( true )
	{
	    Token = GetToken();

        if( Token == 2)
		{
            break;
		}

		type = (int)TokenNumber;

		while ( true )
		{
			//if ( type < 0 || type > 4 )
			//{
			//	break;
			//}
		    Token = GetToken();

			if ( strcmp("end", TokenString ) == 0)
			{
				break;
			}

			this->ElfQuest[this->eCount].Mob = (int)TokenNumber;

			Token = GetToken();
			this->ElfQuest[this->eCount].CountMob = (int)TokenNumber;

			Token = GetToken();
			this->ElfQuest[this->eCount].Proc = (int)TokenNumber;

			Token = GetToken();
			strcpy(this->ElfQuest[this->eCount].MSG,TokenString);

			Token = GetToken();
			strcpy(this->ElfQuest[this->eCount].MS2,TokenString);

			Token = GetToken();
			this->ElfQuest[this->eCount].iType = (int)TokenNumber;

			Token = GetToken();
			this->ElfQuest[this->eCount].iIndex = (int)TokenNumber;

			Token = GetToken();
			this->ElfQuest[this->eCount].iLevel = (int)TokenNumber;

			this->eCount++;
		}
    }
	fclose(SMDFile);
	// ---
	SMDFile = fopen(GENSQUEST_DIR, "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,"[GensQuest] Info file Load Fail [..\\Data\\Quest\\GensQuest.ini]","CRITICAL ERROR",0);
		ExitProcess(1);
	}

	Token = 0;
	int Tokentype = -1;
	this->gCount = 1;

	while ( true )
	{
	    Token = GetToken();

        if( Token == 2)
		{
            break;
		}

		Tokentype = (int)TokenNumber;

		while ( true )
		{
			//if ( type < 0 || type > 4 )
			//{
			//	break;
			//}
		    Token = GetToken();

			if ( strcmp("end", TokenString ) == 0)
			{
				break;
			}

			this->GensQuest[this->gCount].Mob = (int)TokenNumber;

			Token = GetToken();
			this->GensQuest[this->gCount].CountMob = (int)TokenNumber;

			Token = GetToken();
			this->GensQuest[this->gCount].Proc = (int)TokenNumber;

			Token = GetToken();
			strcpy(this->GensQuest[this->gCount].MSG,TokenString);

			Token = GetToken();
			strcpy(this->GensQuest[this->gCount].MS2,TokenString);

			Token = GetToken();
			this->GensQuest[this->gCount].Contribution = (int)TokenNumber;

			this->gCount++;
		}
    }
	fclose(SMDFile);
}
void NewS5Quest::NPCQuest(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	BYTE Packet[200] = {0};
	Packet[0] = 0xC1;
	Packet[1] = 0x08;
	Packet[2] = 0xF6;
	Packet[3] = 0x0A;
	Packet[4] = 0x01;
	Packet[5] = 0x01;
	Packet[6] = 0x00;
	Packet[7] = 0x00;

	if(lpObj->NPC == 257)
	{
		this->ElfMainQuest(lpObj);
	}
	else if(lpObj->NPC == 543 || lpObj->NPC == 544)
	{
		this->GensMainQuest(lpObj);
	}
	DataSend(aIndex,Packet,Packet[1]);
}

void NewS5Quest::ElfMainQuest(LPOBJ lpObj)
{
	//if(lpObj->ElfQuestNum == 0) lpObj->ElfQuestNum++;

	//int Num = lpObj->ElfQuestNum;

	//if(Num >= this->eCount)
	//{
	//	MessageChat(lpObj->m_Index,"@[ElfQuest]: Finish!");
	//	return;
	//}
	//if(lpObj->ElfMonsterCount == this->ElfQuest[Num].CountMob)
	//{
	//	this->ElfReward(lpObj,Num);
	//	lpObj->ElfQuestNum++;
	//	lpObj->ElfMonsterCount = 0;
	//}
	//else
	//{
	//	MessageChat(lpObj->m_Index,"@[ElfQuest]: Mission #%d",Num);	//Fix
	//	MessageChat(lpObj->m_Index,"@[ElfQuest]: %s",this->ElfQuest[Num].MSG);
	//	MessageChat(lpObj->m_Index,"@[ElfQuest]: %s [%d/%d]",this->ElfQuest[Num].MS2,lpObj->ElfMonsterCount,this->ElfQuest[Num].CountMob);
	//}
}

void NewS5Quest::ElfMonsterKillProc(LPOBJ lpObj, LPOBJ lpTargetObj)	//lpTargetObj - тот кто убил
{
	//int Num = lpTargetObj->ElfQuestNum;;
	//if(Num==0) return;
	//if(lpObj->Class == this->ElfQuest[Num].Mob)
	//{
	//	if(this->ElfQuest[Num].CountMob == lpTargetObj->ElfMonsterCount)
	//	{
	//		return;
	//	}
	//	srand(time(NULL));
	//	if(this->ElfQuest[Num].Proc > rand()%100)
	//	{
	//		lpTargetObj->ElfMonsterCount++;
	//		MessageChat(lpTargetObj->m_Index,"@[ElfQuest]: %s [%d/%d]",this->ElfQuest[Num].MS2,lpTargetObj->ElfMonsterCount,this->ElfQuest[Num].CountMob);

	//		if(this->ElfQuest[Num].CountMob == lpTargetObj->ElfMonsterCount)
	//		{
	//			MessageChat(lpTargetObj->m_Index,"@[ElfQuest]: Mission accomplished!");
	//		}
	//	}
	//}
}

void NewS5Quest::ElfReward(LPOBJ lpObj, int Rew)
{
	int Type = ITEMGET(this->ElfQuest[Rew].iType,this->ElfQuest[Rew].iIndex);
	ItemSerialCreateSend(lpObj->m_Index,(BYTE)lpObj->MapNumber,(BYTE)lpObj->X,(BYTE)lpObj->Y,Type,this->ElfQuest[Rew].iLevel,0,0,0,0,lpObj->m_Index,0,0);
	ExFireCracker(lpObj->m_Index, lpObj->X, lpObj->Y);
}

// --- --- --- --- --- --- --- --- --- --- --- --- ---

void NewS5Quest::GensMainQuest(LPOBJ lpObj)
{
	//if(lpObj->GensQuestNum == 0) lpObj->GensQuestNum++;

	//int Num = lpObj->GensQuestNum;

	//if(Num >= this->eCount)
	//{
	//	MessageChat(lpObj->m_Index,"~[GensQuest]: Finish!");
	//	return;
	//}
	//if(lpObj->GensMonsterCount == this->GensQuest[Num].CountMob)
	//{
	//	this->GensReward(lpObj,Num);
	//	lpObj->GensQuestNum++;
	//	lpObj->GensMonsterCount = 0;
	//}
	//else
	//{
	//	MessageChat(lpObj->m_Index,"~[GensQuest]: Mission #%d",Num);	//Fix
	//	MessageChat(lpObj->m_Index,"~[GensQuest]: %s",this->GensQuest[Num].MSG);
	//	MessageChat(lpObj->m_Index,"~[GensQuest]: %s [%d/%d]",this->GensQuest[Num].MS2,lpObj->GensMonsterCount,this->GensQuest[Num].CountMob);
	//}
}

void NewS5Quest::GensMonsterKillProc(LPOBJ lpObj, LPOBJ lpTargetObj)	//lpTargetObj - тот кто убил
{
	//int Num = lpTargetObj->GensQuestNum;;
	//if(Num==0) return;
	//if(lpObj->Class == this->GensQuest[Num].Mob)
	//{
	//	if(this->GensQuest[Num].CountMob == lpTargetObj->GensMonsterCount)
	//	{
	//		return;
	//	}
	//	srand(time(NULL));
	//	if(this->GensQuest[Num].Proc > rand()%100)
	//	{
	//		lpTargetObj->GensMonsterCount++;
	//		MessageChat(lpTargetObj->m_Index,"~[GensQuest]: %s [%d/%d]",this->GensQuest[Num].MS2,lpTargetObj->GensMonsterCount,this->GensQuest[Num].CountMob);

	//		if(this->ElfQuest[Num].CountMob == lpTargetObj->GensMonsterCount)
	//		{
	//			MessageChat(lpTargetObj->m_Index,"~[GensQuest]: Mission accomplished!");
	//		}
	//	}
	//}
}

void NewS5Quest::GensReward(LPOBJ lpObj, int Rew)
{
	//MessageChat(lpObj->m_Index,"~[GensQuest]: +%d Contribution!",this->GensQuest[Rew].Contribution);
	//lpObj->GensExp += this->GensQuest[Rew].Contribution;
}

void NewS5Quest::MainKillMonster(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	//this->ElfMonsterKillProc(lpObj,lpTargetObj);
	//this->GensMonsterKillProc(lpObj,lpTargetObj);
}

void NewS5Quest::Info(int aIndex)
{
	//LPOBJ lpObj = &gObj[aIndex];
	//int eNum = lpObj->ElfQuestNum;
	//int gNum = lpObj->GensQuestNum;
	//if(eNum != 0)
	//{
	//	MessageChat(lpObj->m_Index,"@[ElfQuest]: %s [%d/%d]",this->ElfQuest[eNum].MS2,lpObj->ElfMonsterCount,this->ElfQuest[eNum].CountMob);
	//}
	//if(gNum != 0)
	//{
	//	MessageChat(lpObj->m_Index,"~[GensQuest]: %s [%d/%d]",this->GensQuest[gNum].MS2,lpObj->GensMonsterCount,this->GensQuest[gNum].CountMob);
	//}
}