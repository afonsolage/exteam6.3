#include "StdAfx.h"
#include "DevilSquareRewardItem.h"

//#include "CreditDonate.h"
#include "Functions.h"
//#include "CreditDonate.h"
//#include "user.h"
#include "DSProtocol.h"
//#include "logproc.h"
//#include "..\\include\\ReadScript.h"
//#include "..\\common\zzzitem.h"
//#include "ExUser.h"

//#include "ExLicense.h"
#include "ExFunction.h"

cDevilSquareRewardItem gDevilSquareRewardItem;


void cDevilSquareRewardItem::Load()
{

	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,DS_REWARD_ITEM_DIR);
	this->m_iRewardItemCount = GetPrivateProfileInt("ExTeam","RewardItemCount",0,DS_REWARD_ITEM_DIR);
	for (int j = 1; j < 8; j++)
	{
		for(int i=0;i<MAX_DS_REWARD_ITEM;i++)
		{
			this->Reward[i][j].Type	= 0;
			this->Reward[i][j].Index	= 0;
			this->Reward[i][j].Level	= 0;
			this->Reward[i][j].Skill	= 0;
			this->Reward[i][j].Luck	= 0;
			this->Reward[i][j].Opt		= 0;
			this->Reward[i][j].Exl		= 0;
			this->Reward[i][j].Anc		= 0;
		}
	}

	//CheckFile(DS_REWARD_ITEM_DIR);

	FILE *file = fopen(DS_REWARD_ITEM_DIR,"r");

	if(file == NULL)
	{
		this->Enable = 0;
		return;
	}

	char Buff[256];
	int Flag = 0;
	for (int j = 1; j < 8; j++)
	{
		this->Count[j] = 0;
	}
	
	while(!feof(file))
	{
		fgets(Buff,256,file);	
		if(Ex_IsBadFileLine(Buff, Flag))	
			continue;
		for (int j = 1; j < 8; j++)
		{
			if(Flag == j)
			{
				int n[8];

				sscanf(Buff," %d %d %d %d %d %d %d %d %d",&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7]);

				this->Reward[this->Count[j]][j].Type		= n[0];
				this->Reward[this->Count[j]][j].Index		= n[1];
				this->Reward[this->Count[j]][j].Level		= n[2];
				this->Reward[this->Count[j]][j].Skill		= n[3];
				this->Reward[this->Count[j]][j].Luck		= n[4];
				this->Reward[this->Count[j]][j].Opt		= n[5];
				this->Reward[this->Count[j]][j].Exl		= n[6];
				this->Reward[this->Count[j]][j].Anc		= n[7];

				this->Count[j]++;

				if (this->Count[j]>=MAX_DS_REWARD_ITEM)
				{
					break;
				}
			}
		
		}
	}
	fclose(file);
}

void cDevilSquareRewardItem::Main(int aIndex)
{
	
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	
	for (int j = 1; j < 8; j++)
	{
		if (lpObj->m_bDevilSquareIndex == j)
		{
			//srand(time(NULL));
			if (this->Count[j] == 0)
			{
				return;
			}

			if(THINNAKORN_MAC)
			{
				for(int i = 0; i < this->m_iRewardItemCount; i++)
				{
					int itemId = rand()%this->Count[j];
					ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(this->Reward[itemId][j].Type,this->Reward[itemId][j].Index),this->Reward[itemId][j].Level,0,this->Reward[itemId][j].Skill,this->Reward[itemId][j].Luck,this->Reward[itemId][j].Opt,aIndex,this->Reward[itemId][j].Exl,this->Reward[itemId][j].Anc);
				}
			}
			else
			{
				int itemId = rand()%this->Count[j];
				ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEMGET(this->Reward[itemId][j].Type,this->Reward[itemId][j].Index),this->Reward[itemId][j].Level,0,this->Reward[itemId][j].Skill,this->Reward[itemId][j].Luck,this->Reward[itemId][j].Opt,aIndex,this->Reward[itemId][j].Exl,this->Reward[itemId][j].Anc);
			}
			return;	
		}
	}
}
