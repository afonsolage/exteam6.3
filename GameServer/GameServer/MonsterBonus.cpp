#include "StdAfx.h"
#include "MonsterBonus.h"
#include "Functions.h"
#include "ExUser.h"
#include "Message.h"
#include "ExLicense.h"
#include "PremiumSystem.h"
#include "ExText.h"

cMonsterBonus gMonsterBonus;

cMonsterBonus::cMonsterBonus()
{
	this->Enable = false;
	this->Count = 0;
	ZeroMemory(&this->MobData,sizeof(this->MobData));
}

cMonsterBonus::~cMonsterBonus()
{

}

void cMonsterBonus::Load()
{
	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,MOB_BONUS_DIR);

	FILE * file = fopen(MOB_BONUS_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,MOB_BONUS_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
		return;
	}

	char Buff[256];
	int Flag = 0;
	this->Count = 0;

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
			{
				int n[4];
				sscanf(Buff, "%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);
				this->MobData[this->Count].MobID = n[0];
				this->MobData[this->Count].BonusType = n[1];
				this->MobData[this->Count].BonusCount = n[2];
				this->MobData[this->Count].MapNumber = n[3];
				this->Count++;
			}
			else
			{
				int n[3];
				sscanf(Buff, "%d %d %d", &n[0], &n[1], &n[2]);
				this->MobData[this->Count].MobID = n[0];
				this->MobData[this->Count].BonusType = n[1];
				this->MobData[this->Count].BonusCount = n[2];
				this->Count++;
			}

			if(this->Count >= MAX_MOB_BONUS) break;
		}
	}
	fclose(file);
}

void cMonsterBonus::Main(LPOBJ lpMobObj, LPOBJ lpTargetObj)
{
	if(!this->Enable) return;
	for(int i = 0; i < this->Count; i++)
	{
		if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			if(lpMobObj->MapNumber != this->MobData[i].MapNumber)
			{
				continue;
			}
		}

		if(lpMobObj->Class == this->MobData[i].MobID)
		{
			if(this->MobData[i].BonusType == 1)	//Credits
			{
				lpTargetObj->ExCred += this->MobData[i].BonusCount;
				ExUserDataSend(lpTargetObj->m_Index);	//Может быть реконект если быстро убиваешь монстров нужно пересматривать
				MsgNormal(lpTargetObj->m_Index,g_ExText.GetText(109),this->MobData[i].BonusCount);
				return;
			}
			else if(this->MobData[i].BonusType == 2)	//WcoinC
			{
				lpTargetObj->GameShop.WCoinC += this->MobData[i].BonusCount;
				gGameShop.GDSaveUserInfo(lpTargetObj->m_Index);
				MsgNormal(lpTargetObj->m_Index,g_ExText.GetText(110),this->MobData[i].BonusCount);
				return;
			}
			else if(this->MobData[i].BonusType == 3)	//Wcoin
			{
				lpTargetObj->GameShop.WCoinP += this->MobData[i].BonusCount;
				gGameShop.GDSaveUserInfo(lpTargetObj->m_Index);
				MsgNormal(lpTargetObj->m_Index,g_ExText.GetText(111),this->MobData[i].BonusCount);
				return;
			}
			else if(this->MobData[i].BonusType == 4)	//Wcoin
			{
				lpTargetObj->GameShop.GoblinPoint += this->MobData[i].BonusCount;
				gGameShop.GDSaveUserInfo(lpTargetObj->m_Index);
				MsgNormal(lpTargetObj->m_Index,g_ExText.GetText(112),this->MobData[i].BonusCount);
				return;
			}
#if(CUSTOM_MONSTER_PREMIUM)
			if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
			{
				 if(this->MobData[i].BonusType == 5)
				 {
					lpTargetObj->PremiumTime += (this->MobData[i].BonusCount * 3600);
					lpTargetObj->PremiumTimeType = PREM_BRONZE;
					MessageChat(lpTargetObj->m_Index, "@[Premium Status] +%d Hour, Type:Bronze", this->MobData[i].BonusCount);
					ExUserDataSend(lpTargetObj->m_Index);
				 }
				 else if(this->MobData[i].BonusType == 6)
				 {
					lpTargetObj->PremiumTime += (this->MobData[i].BonusCount * 3600);
					lpTargetObj->PremiumTimeType = PREM_SILVER;
					MessageChat(lpTargetObj->m_Index, "@[Premium Status] +%d Hour, Type:Silver", this->MobData[i].BonusCount);
					ExUserDataSend(lpTargetObj->m_Index);
				 }
				 else if(this->MobData[i].BonusType == 7)
				 {
					lpTargetObj->PremiumTime += (this->MobData[i].BonusCount * 3600);
					lpTargetObj->PremiumTimeType = PREM_GOLD;
					MessageChat(lpTargetObj->m_Index, "@[Premium Status] +%d Hour, Type:Gold", this->MobData[i].BonusCount);
					ExUserDataSend(lpTargetObj->m_Index);
				 }
			}
#endif
			return;
		}
	}
}

