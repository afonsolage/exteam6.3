#include "stdafx.h"
#include "Monster.h"
#include "TMemory.h"
#include "Console.h"
#include "Import.h"
#include "Defines.h"
#include "Object.h"
#include "ReadScript.h"
#include "ExFunction.h"
#include "Configs.h"
// ----------------------------------------------------------------------------------------------

Monster gMonster;
// ----------------------------------------------------------------------------------------------

void Monster::Load()
{
	ZeroMemory(this->lpNpcName, sizeof(this->lpNpcName));
	ZeroMemory(this->Data,sizeof(Data));
	// ----
	this->ReadList("Data\\Custom\\Configs\\Monster.ini");
	
	// ----
	//SetRange((LPVOID)0x005852EC, 0xa4, ASM::NOP);
	//SetOp((LPVOID)0x005852EC, (LPVOID)CraftMasterView, ASM::JMP);
	// ----
	SetOp((LPVOID)0x0061FE3F, (LPVOID)this->LoadMonsterBMD, ASM::CALL);
	SetOp((LPVOID)0x0061FEEA, (LPVOID)this->LoadMonsterTexture, ASM::CALL);
	//Limit kill
	SetByte((LPVOID)(0x00559B82 + 3),0xFF);
	SetByte((LPVOID)(0x00559B82 + 4),0xFF);
	// ----
	SetOp((LPVOID)0x004E199D, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00587049, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00590CCC, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x005BBEE6, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0064229D, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00642D51, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00643229, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0065EA86, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911903, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0091191D, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911937, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911951, (LPVOID)this->ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0091196B, (LPVOID)this->ShowMonster, ASM::CALL);
	// ----
	SetOp((LPVOID)0x0058101A, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058105B, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058109C, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005810DD, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058111E, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058115F, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005811A0, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005811E1, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00581222, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00581263, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005812A8, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005812ED, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058132E, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058136F, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005813B4, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005813F9, (LPVOID)this->SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00586859, (LPVOID)this->SetMainAttribute, ASM::CALL);
}
// ----------------------------------------------------------------------------------------------

void Monster::ReadList(char * File)
{
	int Token;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if (!SMDFile)
	{
		MessageBoxError("%s - file nor found", File);
		ExitProcess(0);
		return;
	}
	// ----
	this->Count = 0;
	// ----
	while(true)
	{
		Token = GetToken();
		// ----
		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}
		// ----
		if( this->Count >= MAX_MONSTER)
		{
			break;
		}
		// ----
		this->Data[this->Count].ID		= TokenNumber;
		// ----
		GetToken();
		this->Data[this->Count].Type	= TokenNumber;
		// ----
		GetToken();
		memcpy(this->Data[this->Count].Name, TokenString, sizeof(this->Data[this->Count].Name));
		// ----
		GetToken();
		memcpy(this->Data[this->Count].Dir, TokenString, sizeof(this->Data[this->Count].Dir));
		// ----
		GetToken();
		memcpy(this->Data[this->Count].Folder, TokenString, sizeof(this->Data[this->Count].Folder));
		// ----
		GetToken();
		memcpy(this->Data[this->Count].BMDFile, TokenString, sizeof(this->Data[this->Count].BMDFile));
		// ----
		GetToken();
		this->Data[this->Count].Size	= TokenNumber;
		// ----
		this->Count++;
	} 
	fclose(SMDFile);	
#ifdef _GRAND_SYSTEM_
	
	this->Data[this->Count].ID		= 586;
	this->Data[this->Count].Type	= 0;
	memcpy(this->Data[this->Count].Name, "Hero City", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "\\Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster166", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++;

	this->Data[this->Count].ID		= 587;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Aidos", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster176", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++; 

	this->Data[this->Count].ID		= 588;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "ZveroLom", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "monster178", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++;

	this->Data[this->Count].ID		= 589;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "StriKozel", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster215", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++;

	this->Data[this->Count].ID		= 590;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Brokin", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster213", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.5;
	this->Count++;

	this->Data[this->Count].ID		= 591;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Varol", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "monster169", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.5;
	this->Count++;

	this->Data[this->Count].ID		= 592;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Ishak", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster167", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.3;
	this->Count++;

	this->Data[this->Count].ID		= 593;
	this->Data[this->Count].Type	= 1;
	memcpy(this->Data[this->Count].Name, "Hero Boss", sizeof(this->Data[this->Count].Name));
	memcpy(this->Data[this->Count].Dir, "Data\\Monster\\", sizeof(this->Data[this->Count].Dir));
	memcpy(this->Data[this->Count].Folder, "Monster\\", sizeof(this->Data[this->Count].Folder));
	memcpy(this->Data[this->Count].BMDFile, "Monster171", sizeof(this->Data[this->Count].BMDFile));
	this->Data[this->Count].Size	= 1.5;
	this->Count++;
	
#endif
}
// ----------------------------------------------------------------------------------------------

void Monster::ReadName(char* File)
{
	int Token;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if( SMDFile == 0 )
	{
		//MsgBox(lMsg.Get(MSGGET(0, 112)), File);
		return;
	}

	this->iLoadedName = 0;

	while(true) 
	{
		Token = GetToken();

		if( Token == END || !strcmp(TokenString, "end") )
		{
			return;
		}

		this->name_data[this->iLoadedName].ObjectID = TokenNumber;

		Token = GetToken();
		int nomer = TokenNumber;

		Token = GetToken();
		memcpy(this->name_data[this->iLoadedName].Name, TokenString, 25);

		//gConsole.Output(cGREY, "%d %s",this->iLoadedName, this->name_data[this->iLoadedName].Name);

		this->iLoadedName++;
	}

	fclose(SMDFile);	
	// ----
};

void Monster::LoadMonsterBMD(signed int ModelID, char* a2, char* a3, signed int a4)
{
	int MonsterID = ModelID - MONSTER_MODEL;
	// ----
	for(int i=0;i<gMonster.Count;i++)
	{
		if(MonsterID == gMonster.Data[i].ID)
		{
			pLoadMonsterBMD(ModelID, gMonster.Data[i].Dir, gMonster.Data[i].BMDFile, -1);
			return;
		}
	}
	// ----
	pLoadMonsterBMD(ModelID, a2, a3, a4);
}
// ----------------------------------------------------------------------------------------------

void Monster::LoadMonsterTexture(signed int ModelID, char* a2, int a3, int a4)
{
	int MonsterID = ModelID - MONSTER_MODEL;
	// ----
	for(int i=0;i<gMonster.Count;i++)
	{
		if(MonsterID == gMonster.Data[i].ID)
		{
			pLoadMonsterTexture(ModelID, gMonster.Data[i].Folder, a3, a4);
			return;
		}
	}
	// ----
	pLoadMonsterTexture(ModelID, a2, a3, a4);
}
// ----------------------------------------------------------------------------------------------

void Monster::ShowMonster(int MonsterID, int a2, int a3, int a4)
{
	//__try
	//{
		for(int i=0;i<gMonster.Count;i++)
		{
			if(MonsterID == gMonster.Data[i].ID)
			{
				pLoadMonsterID(MonsterID);
				// ----
				DWORD ObjectStruct  = pVieweObject(a4, MonsterID + MONSTER_MODEL, a2, a3, 0.0);
				// -----
				lpViewObj Object	= &*(ObjectPreview*)ObjectStruct;
				// ----
				memcpy(Object->Name, gMonster.Data[i].Name, sizeof(gMonster.Data[i].Name));
				// ----
				if(gMonster.Data[i].Type == 0)
				{
					*(BYTE*)(ObjectStruct + 800) = emNPC;
				}
				else
				{
					*(BYTE*)(ObjectStruct + 800) = emMonster;
				}
				// ----
				*(float *)(ObjectStruct + 872) = gMonster.Data[i].Size;			
				// ----
				Object->ID = MonsterID;
				*(BYTE*)(ObjectStruct + 798) = 0;
				Object->Unknown128 = *(DWORD*)0x879343C;
				return;
			}	
		}
		// ----
		pShowMonster(MonsterID, a2, a3, a4);
	//}__except(EXCEPTION_EXECUTE_HANDLER)
	//{
	//}

		
}
// ----------------------------------------------------------------------------------------------

void Monster::SetMainAttribute(int ObjectPointer, int MonsterID)
{
	lpViewObj Object	= &*(ObjectPreview*)ObjectPointer;
	int MapClass		= pMapNumber - 9;	//ebp-4
	// ----
	if( MapClass > 0 && MapClass <= 8 && MonsterID >= 84 && MonsterID <= 143 )
	{
		Object->Unknown130				= 0;
		*(float*)(ObjectPointer + 872)	+= (double)(MapClass / 3) * 0.05;
	}
	// ----
	if( !Object )
	{
		return;
	}
	// ----

	for( int i = 0; i < MAX_MONSTER; i++ )
	{
		gMonster.lpNpcName[i] = *(NpcNameList*)(oNpcName + sizeof(NpcNameList) * i);
		// ----
		if( MonsterID == gMonster.lpNpcName[i].ObjectID )
		{
			memcpy(Object->Name, gMonster.lpNpcName[i].Name, sizeof(gMonster.lpNpcName[i].Name)-1);
			break;
		}
		else if( MonsterID == 579 )
		{
			memcpy(Object->Name, "David", sizeof("David"));
		}
		else if( MonsterID == 0 )
		{
			memcpy(Object->Name, "Bull Fighter", sizeof("Bull Fighter"));
		}
		else if ( MonsterID == 561 )
		{
			memcpy(Object->Name, "Medusa (Boss)", sizeof("Medusa (Boss)"));
		}
	}
	// ----
	Object->ID = MonsterID;
	*(BYTE*)(ObjectPointer + 798) = 0;
	Object->Unknown128 = *(DWORD*)0x879343C;
	// ----
	if( MonsterID == 200 )	//-> Soccerball
	{
		*(BYTE*)(ObjectPointer + 800) = emMonster;
	}
	else
	{
		if( MonsterID < 260 )
		{
			if( MonsterID <= 200 )
			{
				if( MonsterID < 150 )
				{
					if( MonsterID <= 110 )
					{
						if( MonsterID < 100 )
						{
							*(BYTE*)(ObjectPointer + 800)	= emMonster;
						}
						else
						{
							*(BYTE*)(ObjectPointer + 800)	= emNone;
						}
					}
					else
					{
						*(BYTE*)(ObjectPointer + 800) = emMonster;
					}
				}
				else
				{
					*(BYTE*)(ObjectPointer + 800)	= emMonster;
				}
			}
			else
			{
				*(BYTE*)(ObjectPointer + 800) = emNPC;
			}
		}
		else
		{
			*(BYTE*)(ObjectPointer + 800) = emMonster;
		}
	}
	// ----
	switch(MonsterID)
	{
		//-> 칸투르 npc
	case 367:	//-> Gateway Machine
	case 368:	//-> Elpis
		//-> 조화의 보석 관련 npc
	case 369:	//-> Osbourne
	case 370:	//-> Jerridon
		//-> 화이트엔젤 이벤트 아이템 지급 NPC 추가
	case 371:	//-> Leo the Helper
		//-> 카오스카드 담당
	case 375:	//-> Chaos Card Master
		//-> 공성전 신규 물약 NPC
	case 376:	//-> Pamela the Supplier
	case 377:	//-> Angela the Supplier
		//-> 설날 복주머니 이름
	case 379:	//-> Natasha the Firecracker Merchant
		//-> 신규 이벤트맵
	case 380:	//-> Stone Statue
	case 381:	//-> MU Allies General
	case 382:	//-> Illusion Sorcerer Elder
	case 383:	//-> Alliance Sacred Item Storage
	case 384:	//-> Illusion Castle Sacred Item Storage
	case 385:	//-> Mirage
		//-> 3차 체인지업
	case 406:	//-> Apostle Devin
	case 407:	//-> Werewolf Quarel
	case 408:	//-> Gatekeeper
		//-> 추석(2007)이벤트
	case 414:	//-> Helper Ellen
		//-> 엘베란드  NPC
	case 415:	//-> Silvia
	case 416:	//-> Rhea
	case 417:	//-> Marce
		//-> 벚꽃이벤트 npc 추가	
	case 450:	//-> Cherry Blossom Spirit
		//-> 소켓 시스템 NPC
	case 452:	//-> Seed Master
	case 453:	//-> Seed Researcher
		//-> 체험서버용 NPC 추가	
	case 464:	//-> Re-Initialization Helper
		//-> 크리스마스이벤트 NPC 추가(국내 적용 추가)
	case 465:	//-> Santa Claus
	case 467:	//-> Snowman
	case 468:	//-> Dasher
	case 469:	//-> Kermit
	case 470:	//-> Little Santa
	case 471:	//-> Cupid
	case 472:	//-> Prancer
	case 473:	//-> Donner
	case 474:	//-> Vixen
	case 475:	//-> Blitzen
		//-> 상용화 7주년 이벤트 NPC 추가
	case 478:	//-> Delgado
		//-> PK필드 몬스터 NPC 추가
	case 479:	//-> Doorkeeper Titus
		//-> 겜블 NPC 추가
	case 492:	//-> Moss
		//-> 일반 몬스터 NPC
	case 522:	//-> Jerint the Assistant
		//-> 도플갱어 몬스터 NPC
	case 540:	//-> Lugard
	case 541:	//-> Interim Reward Chest
	case 542:	//-> Final Reward Chest
		//-> 겐스 NPC
	case 543:	//-> Gens Duprian Steward
	case 544:	//-> Gens Vanert Steward
		//-> 로랜시장 NPC 추가
	case 545:	//-> Christine the General Goods Merchant
	case 546:	//-> Jeweler Raul
	case 547:	//-> Market Union Member Julia
		//-> 스켈레톤변신반지용 변신스켈레톤 추가
	case 566:	//-> Mercenary Guild Manager Tercia
	case 567:	//-> Priestess Veina
	case 568:	//-> Wandering Merchant Zyro
		//-> 칼루탄 NPC 추가 2010-06-30 홍승욱
	case 577:	//-> Leina the General Goods Merchant
	case 578:	//-> Weapons Merchant Bolo
		//-> 럭키아이템 NPC 추가 2010-09-01 이기수	
	case 579:	//-> David
		{
			*(BYTE*)(ObjectPointer + 800) = emNPC;
		}
		break;
	}
	// ----
	if( MonsterID >= 480 && MonsterID <= 491 )	//-> PK필드 몬스터
	{
		*(BYTE*)(ObjectPointer + 800) = emMonster;
	}
	// ----
	if( MonsterID == 451 )	//-> Cherry Blossom Tree
	{
		*(BYTE*)(ObjectPointer + 800) = emNone;
	}
	// ----
	//*(float *)(ObjectPointer + 872) = 0.5;
	//Object->m_Model.Scale = 0.5;
}
// ----------------------------------------------------------------------------------------------

char* Monster::GetMonsterName(int MOBID)
{
	for( int i = 0; i < MAX_MONSTER; i++ )
	{
		if(MOBID == gMonster.name_data[i].ObjectID)
		{
			return this->name_data[i].Name;
		}
	}
	return NULL;
}