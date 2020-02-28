#include "stdafx.h"
#include "gObjMonster.h"
#include "..\include\ReadScript.h"
#include "..\common\WzMemScript.h"
#include "LogProc.H"
#include "DSProtocol.h"
#include "BossRewardItem.h"
#include "Functions.h"

#ifdef BOSS_REWARD_ITEM

cBossRewardItem gBossRewardItem;

void cBossRewardItem::Init()
{
	ZeroMemory(&this->Drop,sizeof(this->Drop));

	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,BOSS_REWARD_DIR);
	

	FILE *file = fopen(BOSS_REWARD_DIR,"r");
	if (file == NULL)
	{
		this->Enable = 0;
		MessageBoxA(0,BOSS_REWARD_DIR,"LOAD ERROR",0);
		return;
	}

	this->DropCount = 0;
	this->BlockCount = 0;

	char Buff[256];
	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff,256,file);

		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if (Flag == 1)
		{
			int n[17];
			sscanf(Buff,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7],&n[8],&n[9],&n[10],&n[11],&n[12],&n[13],&n[14],&n[15],&n[16]);
			this->Drop[this->DropCount].MonsterID		= n[0];
			this->Drop[this->DropCount].Type			= n[1];
			this->Drop[this->DropCount].Index			= n[2];
			this->Drop[this->DropCount].MinLevel		= n[3];
			this->Drop[this->DropCount].MaxLevel		= n[4];
			this->Drop[this->DropCount].Dur				= n[5];
			this->Drop[this->DropCount].OptionRate		= n[6];
			this->Drop[this->DropCount].MaxOption		= n[7];
			this->Drop[this->DropCount].LuckRate		= n[8];
			this->Drop[this->DropCount].LuckOption		= n[9];
			this->Drop[this->DropCount].SkillRate		= n[10];
			this->Drop[this->DropCount].SkillOption		= n[11];
			this->Drop[this->DropCount].ExlRate			= n[12];
			this->Drop[this->DropCount].ExlOption		= n[13];
			this->Drop[this->DropCount].AncRate			= n[14];
			this->Drop[this->DropCount].AncOption		= n[15];
			this->Drop[this->DropCount].ItemDropRate	= n[16];
			this->DropCount++;
		}
	}
	fclose(file);
}

bool cBossRewardItem::ProccessItemDrop(LPOBJ lpMobObj)
{
	if (!this->Enable)	
	{
		return false;
	}
	int ArrayDropItem[100];
	int CountItem = 0;
	for (int i=0; i < this->DropCount; i++)
	{
		if(CountItem >= 100)
		{
			break;
		}
		if( lpMobObj->Class == this->Drop[i].MonsterID )
		{
			ArrayDropItem[CountItem] = i;
			CountItem++;
		}
	}
	
	if (CountItem == 0)
	{
		return false;
	}
	//srand(time(NULL));
	int ItemIndex = ArrayDropItem[rand()%CountItem];
	//srand(time(NULL));
	if ( (rand()%10000) < this->Drop[ItemIndex].ItemDropRate )
	{
		int iLevel	= 0;
		int iOption	= 0;
		int iLuck	= 0;
		int iSkill	= 0;
		int iExlOpt	= 0;
		int iAncOpt	= 0;

		if( this->Drop[ItemIndex].MaxLevel == this->Drop[ItemIndex].MinLevel )
		{
			iLevel = this->Drop[ItemIndex].MinLevel;
		}
		else
		{
			iLevel = this->Drop[ItemIndex].MinLevel + (rand() % (this->Drop[ItemIndex].MaxLevel - this->Drop[ItemIndex].MinLevel + 1));
		}	

		if( this->Drop[ItemIndex].MaxOption != 0 )
		{
			if( rand() % 100 < this->Drop[ItemIndex].OptionRate )
			{
				iOption = rand() % this->Drop[ItemIndex].MaxOption + 1;
			}
		}

		if( this->Drop[ItemIndex].LuckOption == 1 )
		{
			if( rand() % 100 < this->Drop[ItemIndex].LuckRate )
			{
				iLuck = 1;
			}
		}

		if( this->Drop[ItemIndex].SkillOption == 1 )
		{
			if( rand() % 100 < this->Drop[ItemIndex].SkillRate )
			{
				iLuck = 1;
			}
		}

		if(this->Drop[ItemIndex].ExlOption)
		{
			if( rand() % 100 < this->Drop[ItemIndex].ExlRate )
			{
				iExlOpt = GenExcOpt(this->Drop[ItemIndex].ExlOption);
			}
		}

		if(this->Drop[ItemIndex].AncOption == 5 || this->Drop[ItemIndex].AncOption == 10)
		{
			if( rand() % 100 < this->Drop[ItemIndex].AncRate )
			{
				iAncOpt = this->Drop[ItemIndex].AncOption;
			}
		}

		ItemSerialCreateSend(lpMobObj->m_Index,lpMobObj->MapNumber,lpMobObj->X,lpMobObj->Y,ITEMGET(this->Drop[ItemIndex].Type,this->Drop[ItemIndex].Index),iLevel,this->Drop[ItemIndex].Dur,iSkill,iLuck,iOption,gObjMonsterTopHitDamageUser(lpMobObj),iExlOpt,iAncOpt);
		return true;
	}

	return false;
}

#endif // BOSS_REWARD_ITEM
