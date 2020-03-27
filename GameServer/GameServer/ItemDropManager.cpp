#include "stdafx.h"
#include "gObjMonster.h"
#include "..\include\ReadScript.h"
#include "..\common\WzMemScript.h"
#include "LogProc.H"
#include "DSProtocol.h"
#include "ItemDropManager.h"
#include "Functions.h"
#include "ExLicense.h"
#include "GameMain.h"
#include "..\\common\\SetItemOption.h"

CItemDropManager gItemDropManager;

void CItemDropManager::Init()
{
	ZeroMemory(&this->Drop,sizeof(this->Drop));

	this->MapBlockCount = 0;
	ZeroMemory(&this->MapBlockDrop,sizeof(this->MapBlockDrop));

	for(int i = 0; i > OBJMAX; i++)
	{
		this->iUser[i]	= false;
	}

	this->ReadAnc(gDirPath.GetNewPath("ExData\\AncentDrop.ini"));

	FILE *file = fopen(ITEM_DROP_DIR,"r");

	if (file == NULL)
	{
		MessageBoxA(0,ITEM_DROP_DIR,"CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	this->DropCount = 0;
	this->BlockCount = 0;

	this->m_MapDropRate.clear();
	this->m_MapAllowDrop.clear();

	char Buff[256];
	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff,256,file);

		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if (Flag == 1)
		{
			int n[19];
			sscanf(Buff,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7],&n[8],&n[9],&n[10],&n[11],&n[12],&n[13],&n[14],&n[15],&n[16],&n[17],&n[18]);
			this->Drop[this->DropCount].Type			= n[0];
			this->Drop[this->DropCount].Index			= n[1];
			this->Drop[this->DropCount].MinLevel		= n[2];
			this->Drop[this->DropCount].MaxLevel		= n[3];
			this->Drop[this->DropCount].Dur				= n[4];
			this->Drop[this->DropCount].OptionRate		= n[5];
			this->Drop[this->DropCount].MaxOption		= n[6];
			this->Drop[this->DropCount].LuckRate		= n[7];
			this->Drop[this->DropCount].LuckOption		= n[8];
			this->Drop[this->DropCount].SkillRate		= n[9];
			this->Drop[this->DropCount].SkillOption		= n[10];
			this->Drop[this->DropCount].ExlRate			= n[11];
			this->Drop[this->DropCount].ExlOption		= n[12];
			this->Drop[this->DropCount].AncRate			= n[13];
			this->Drop[this->DropCount].AncOption		= n[14];
			this->Drop[this->DropCount].MonsterMinLevel = n[15];
			this->Drop[this->DropCount].MonsterMaxLevel = n[16];
			this->Drop[this->DropCount].MonsterMap		= n[17];
			this->Drop[this->DropCount].ItemDropRate	= n[18];
			this->DropCount++;
		}

		if(Flag == 2)
		{
			int n[2];
			sscanf(Buff,"%d %d", &n[0],&n[1]);
			this->Block[this->BlockCount].Type	= n[0];
			this->Block[this->BlockCount].Index = n[1];
			this->BlockCount++;
		}

		//if(g_ExLicense.CheckUser(Local) || g_ExLicense.CheckUser(ulasevich) || g_ExLicense.CheckUser(ulasevich2))
		//{
		if(Flag == 3)
		{
			int n[3];
			sscanf(Buff,"%d %d %d", &n[0], &n[1], &n[2]);
			this->MapBlockDrop[this->MapBlockCount].Map	= n[0];
			this->MapBlockDrop[this->MapBlockCount].Type	= n[1];
			this->MapBlockDrop[this->MapBlockCount].Index	= n[2];
			this->MapBlockCount++;
		}
		//}

		if(Flag == 4)
		{
			int n[2];
			sscanf(Buff,"%d %d", &n[0], &n[1]);

			MAP_DROPRATE_DATA List;
			List.MapNum = n[0];
			List.Rate = n[1];

			this->m_MapDropRate.push_back(List);
		}

		if(Flag == 5)
		{
			int n[3];
			sscanf(Buff,"%d %d %d", &n[0], &n[1], &n[2]);

			MAP_ALLOW_DATA List;
			List.sType = n[0];
			List.sIndex = n[1];
			List.MapNum = n[2];

			this->m_MapAllowDrop.push_back(List);
		}
	}

	fclose(file);


	//-> Anc Read
}

void CItemDropManager::ReadAnc(char* filename)
{
	if( //!g_ExLicense.CheckUser(eExUB::Local) && 
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei)&&
		!g_ExLicense.CheckUser(eExUB::EpicMU) &&
		!g_ExLicense.CheckUser(eExUB::masonX))
	{
		return;
	}

	for(int i = 0; i < 100; i++)
	{
		this->m_AncData[i].sMap = 0; 
		this->m_AncData[i].sMinLvlMob = 0;
		this->m_AncData[i].sMaxLvlMob = 0;
		this->m_AncData[i].iRate = 0;
		this->m_AncData[i].ItemCount = 0;
		for(int j = 0; j < 256; j++)
		{
			this->m_AncData[i].m_item[j].sType = 0;
			this->m_AncData[i].m_item[j].sIndex = 0;
			this->m_AncData[i].m_item[j].sOpt = 0;
		}
	}

	this->iAncCount = 0;

	SMDToken Token;

	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MsgBox("[Ancent Drop] %s file not found", filename);
		return;
	}

	while(true)
	{
		Token = GetToken();

		if( Token == END )
		{
			break;
		}

		int a = this->iAncCount;
		int n = 0;

		this->m_AncData[a].sMap = (int)TokenNumber;
		Token = GetToken();

		this->m_AncData[a].sMinLvlMob = (int)TokenNumber;
		Token = GetToken();

		this->m_AncData[a].sMaxLvlMob = (int)TokenNumber;
		Token = GetToken();

		this->m_AncData[a].iRate = (int)TokenNumber;

		while(true)
		{
			Token = GetToken();

			if(!strcmp("end", TokenString))
			{
				break;
			}

			this->m_AncData[a].m_item[n].sType = (int)TokenNumber;

			Token = GetToken();
			this->m_AncData[a].m_item[n].sIndex = (int)TokenNumber;

			//if(g_ExLicense.CheckUser(eExUB::masonX))
			{
				Token = GetToken();
				this->m_AncData[a].m_item[n].sOpt = (int)TokenNumber;
			}

			n++;
		}

		this->m_AncData[this->iAncCount].ItemCount = n;
		this->iAncCount++;
	}

	fclose(SMDFile);
	LogAdd("%s file load!", filename);
}

bool CItemDropManager::ProccessItemDrop(LPOBJ lpMobObj, LPOBJ lpTargetObj)
{

	switch(lpMobObj->Class)
	{
	case 78:	//-> Golden Goblin
	case 53:	//-> Golden Titan
	case 79:	//-> Golden Dragon
	case 80:	//-> Golden Lizard
	case 82:	//-> Golden Tantalos
	case 502:	//-> Golden Rabbit
	case 493:	//-> Golden Dark Knight
	case 494:	//-> Golden Devil
	case 495:	//-> ???
	case 496:	//-> Golden Crust
	case 497:	//-> Golden Satiros
	case 498:	//-> Golden Twintail
	case 499:	//-> Golden Iron Knight
	case 500:	//-> Golden Neipin
	case 501:	//-> Golden Great Dragon
		{
			return false;
		}
		break;
	}

	//this->DropAncent(lpTargetObj->m_Index, lpMobObj->m_Index);

	for (int i=0; i < this->DropCount; i++)
	{
		if ( lpMobObj->MapNumber == this->Drop[i].MonsterMap || this->Drop[i].MonsterMap == -1 )
		{
			if ( lpMobObj->Level >= this->Drop[i].MonsterMinLevel && lpMobObj->Level <= this->Drop[i].MonsterMaxLevel )
			{
				if ( (rand()%10000) < this->Drop[i].ItemDropRate )
				{
					int iLevel	= 0;
					int iOption	= 0;
					int iLuck	= 0;
					int iSkill	= 0;
					int iExlOpt	= 0;
					int iAncOpt	= 0;
					
					if( this->Drop[i].MaxLevel == this->Drop[i].MinLevel )
					{
						iLevel = this->Drop[i].MinLevel;
					}
					else
					{
						iLevel = this->Drop[i].MinLevel + (rand() % (this->Drop[i].MaxLevel - this->Drop[i].MinLevel + 1));
					}	

					if( this->Drop[i].MaxOption != 0 )
					{
						if( rand() % 100 < this->Drop[i].OptionRate )
						{
							iOption = rand() % this->Drop[i].MaxOption + 1;
						}
					}

					if( this->Drop[i].LuckOption == 1 )
					{
						if( rand() % 100 < this->Drop[i].LuckRate )
						{
							iLuck = 1;
						}
					}

					if( this->Drop[i].SkillOption == 1 )
					{
						if( rand() % 100 < this->Drop[i].SkillRate )
						{
							iSkill = 1;
						}
					}

					if(this->Drop[i].ExlOption)
					{
						if( rand() % 100 < this->Drop[i].ExlRate )
						{
							if(g_ExLicense.CheckUser(eExUB::masonX))
							{
								int iRandExl = rand() % this->Drop[i].ExlOption + 1;

								iExlOpt = GenExcOpt(iRandExl);
							}
							else
							{
								iExlOpt = GenExcOpt(this->Drop[i].ExlOption);
							}
						}
					}

					if(this->Drop[i].AncOption == 5 || this->Drop[i].AncOption == 10)
					{
						if( rand() % 100 < this->Drop[i].AncRate )
						{
							iAncOpt = this->Drop[i].AncOption;
						}
					}

					this->iUser[lpMobObj->m_Index] = true;

					ItemSerialCreateSend(lpMobObj->m_Index,lpMobObj->MapNumber,lpMobObj->X,lpMobObj->Y,ITEMGET(this->Drop[i].Type,this->Drop[i].Index),iLevel,this->Drop[i].Dur,iSkill,iLuck,iOption,gObjMonsterTopHitDamageUser(lpMobObj),iExlOpt,iAncOpt);	

					return true;
				}
			}
		}
	}

	return false;
}

bool CItemDropManager::BlockItemDrop(int aIndex, int ItemID, int MapNumber)
{
	if( //!g_ExLicense.CheckUser(eExUB::Local)	&& 
		!g_ExLicense.CheckUser(eExUB::Gredy)	&&
		!g_ExLicense.CheckUser(eExUB::Gredy2)	&& 
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!g_ExLicense.CheckUser(eExUB::EpicMU) &&
		!g_ExLicense.CheckUser(eExUB::masonX) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		return true;
	}

	if( MapNumber >= 0 && MapNumber <= MAX_NUMBER_MAP )
	{
		//Check if this item is on MapAllowDrop
		bool found = false;
		for(int i = 0; i < this->m_MapAllowDrop.size(); i++)
		{
			if (ItemID == ITEMGET(this->m_MapAllowDrop[i].sType,this->m_MapAllowDrop[i].sIndex))
			{
				//The item is listed on MapAllowDrop
				found = true;

				if (this->m_MapAllowDrop[i].MapNum == MapNumber)
					return true;
			}
		}

		//If item is listed on MapAllowDrop and our current MapNumber doesn't match any on allowed, we block the drop
		if (found)
			return false;

		for(int i = 0; i< this->MapBlockCount; i++)
		{
			if(this->MapBlockDrop[i].Map == MapNumber && ItemID == ITEMGET(this->MapBlockDrop[i].Type,this->MapBlockDrop[i].Index))
			{
				return false;
			}
		}

		if(this->iUser[aIndex] == true)
		{
			this->iUser[aIndex] = false;
			for(int i = 0; i< this->DropCount; i++)
			{
				if(ItemID == ITEMGET(this->Drop[i].Type,this->Drop[i].Index) )
				{
					return true;
				}
			}
		}

		for(int i = 0; i< this->BlockCount; i++)
		{
			if(ItemID == ITEMGET(this->Block[i].Type,this->Block[i].Index))
			{
				LogAddTD("[DropBlock] Item %d has been blocked", ItemID);
				return false;
			}
		}
	}

	//for(int i = 0; i < this->m_MapDropRate.size(); i++)
	//{
	//	if(this->m_MapDropRate[i].MapNum == MapNumber)
	//	{
	//		if(this->m_MapDropRate[i].Rate < rand()%100)
	//		{
	//			return false;
	//		}
	//	}
	//}

	return true;
}

void CItemDropManager::DropAncent(int aIndex, int iMobIndex)
{
	if( //!g_ExLicense.CheckUser(eExUB::Local)	&& 
		!g_ExLicense.CheckUser(eExUB::Gredy)	&&
		!g_ExLicense.CheckUser(eExUB::Gredy2)	&& 
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!g_ExLicense.CheckUser(eExUB::EpicMU) &&
		!g_ExLicense.CheckUser(eExUB::masonX) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(iMobIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpMonster = &gObj[iMobIndex];
	
	for(int i = 0; i < this->iAncCount; i++)
	{
		ANCENT_GROUP_DATA* lpDrop = &this->m_AncData[i];

		if(lpDrop->sMap == lpMonster->MapNumber || lpDrop->sMap == -1)
		{
			if(lpMonster->Level >= lpDrop->sMinLvlMob && lpMonster->Level <= lpDrop->sMaxLvlMob)
			{
				if(lpDrop->iRate > (rand()%10000))
				{
					int icount = lpDrop->ItemCount;

					if(icount <= 0)
					{
						continue;
					}

					int iRand = rand()%icount;

					int itemnum = ITEMGET(lpDrop->m_item[iRand].sType, lpDrop->m_item[iRand].sIndex); 

					if(!gSetItemOption.IsSetItem(itemnum))
					{
						continue;
					}

					int SetOption = gSetItemOption.GenSetOption(itemnum);

					//if(g_ExLicense.CheckUser(eExUB::masonX))
					{
						if(lpDrop->m_item[iRand].sOpt == 5 || lpDrop->m_item[iRand].sOpt == 10)
						{
							SetOption = lpDrop->m_item[iRand].sOpt;
						}
					}

					int option1rand = 6;
					int option2rand = 4;
					int option3rand = rand()%100;
					int optionc = rand()%3;
					int Option1 = 0;
					int Option2 = 0;
					int Option3 = 0;

					if(rand()%100 < option2rand)
					{
						Option2 = 1;
					}

					switch(optionc)
					{
					case 0: 
						if(option3rand < 4)
						{
							Option3 = 3;
						}
						break;
					case 1:
						if(option3rand < 8)
						{
							Option3 = 2;
						}
						break;
					case 2: 
						if(option3rand < 12)
						{
							Option3 = 1;
						}
						break;
					default: break;
					}

					Option1 = 1;

					ItemSerialCreateSend(aIndex,lpMonster->MapNumber,(BYTE)lpMonster->X,(BYTE)lpMonster->Y,itemnum,0,0,(BYTE)Option1,(BYTE)Option2,(BYTE)Option3,aIndex,0,(BYTE)SetOption);
					return;
				}
			}
		}
	}
	
}

int CItemDropManager::GetMapDropRate(int Map)
{
	for(int i = 0; i < this->m_MapDropRate.size(); i++)
	{
		if(this->m_MapDropRate[i].MapNum == Map)
		{
			return this->m_MapDropRate[i].Rate;
		}
	}

	return gItemDropPer;
}