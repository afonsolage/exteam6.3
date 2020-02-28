#include "StdAfx.h"
#include "user.h"
#include "Message.h"
#include "Reset.h"
#include "Functions.h"
#include "LogProc.h"
#include "Configs.h"
#include "GrandReset.h"
#include "SystemOfRage.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "MoveCommand.h"
#include "ExLicense.h"
#if _CONFLICT_
#include "ExUser.h"
#endif
#include "ObjCalCharacter.h"
#include "ExFunction.h"
#include "BuffManager.h"
#include "Achievements.h"
#include "ExText.h"

cResetSystem gResetSystem;

void cResetSystem::Load()
{
#if(ADD_RESET_WINDOW)
	this->Reset_NPC_ID = 0;
	this->Reset_NPC_MAP = 0;
	this->Reset_NPC_X = 0;
	this->Reset_NPC_Y = 0;

	this->m_needitem.clear();
	this->m_reward.clear();
#endif

	this->EnableResetSystem = GetPrivateProfileInt("Reset","Enable",0,Reset_DIR);	
	this->Maxres = GetPrivateProfileInt("Reset","Max.res",100,Reset_DIR);
	this->ZenForm = GetPrivateProfileInt("Reset","ZenForm",0,Reset_DIR);
	this->NeedZen = GetPrivateProfileInt("Reset","Need.Zen",0,Reset_DIR);
	this->NeedLevel = GetPrivateProfileInt("Reset","Need.Level",0,Reset_DIR);
	this->AddForm = GetPrivateProfileInt("Reset","Add.Form",0,Reset_DIR);
	this->AddPointsDW = GetPrivateProfileInt("Reset","Add.PointsDW",0,Reset_DIR);
	this->AddPointsDK = GetPrivateProfileInt("Reset","Add.PointsDK",0,Reset_DIR);
	this->AddPointsELF = GetPrivateProfileInt("Reset","Add.PointsELF",0,Reset_DIR);
	this->AddPointsSUM = GetPrivateProfileInt("Reset","Add.PointsSUM",0,Reset_DIR);
	this->AddPointsMG = GetPrivateProfileInt("Reset","Add.PointsMG",0,Reset_DIR);
	this->AddPointsDL = GetPrivateProfileInt("Reset","Add.PointsDL",0,Reset_DIR);
	this->AddPointsRF = GetPrivateProfileInt("Reset","Add.PointsRF",0,Reset_DIR);
	this->NeedEmptyInv = GetPrivateProfileInt("Reset","Need.EmptyInv",1,Reset_DIR);

	this->m_iMapForReset = GetPrivateProfileInt("Reset","MapForReset",0,Reset_DIR);

	this->AddCredits = GetPrivateProfileInt("Reset","AddCredits",0,Reset_DIR);
	this->AddWcoinC = GetPrivateProfileInt("Reset","AddWcoinC",0,Reset_DIR);
	this->AddWcoinP = GetPrivateProfileInt("Reset","AddWcoinP",0,Reset_DIR);
	this->AddGoblinPoint = GetPrivateProfileInt("Reset","AddGoblinPoint",0,Reset_DIR);

	this->DinamicExp = GetPrivateProfileInt("Reset","DinamicExp",1,Reset_DIR);

	GetPrivateProfileString("Reset", "cmd","/reset",this->CommandReset,100,Reset_DIR);

#ifdef PRIVATE_MODULE
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea) || g_ExLicense.CheckUser(eExUB::Cherkashin))
		{
		this->NeedWCoinToReset = GetPrivateProfileInt("Reset","NeedWCoinToReset",0,Reset_DIR);
		
#if _CONFLICT_
		this->NeedCreditToReset = GetPrivateProfileInt("Reset","NeedCreditToReset",0,Reset_DIR);
#endif
		
		}
#endif
#if(ADD_RESET_WINDOW)
	this->Reset_NPC_ID = GetPrivateProfileInt("Reset", "Reset_NPC_ID", 0, Reset_DIR);
	this->Reset_NPC_MAP = GetPrivateProfileInt("Reset", "Reset_NPC_MAP", 0, Reset_DIR);
	this->Reset_NPC_X = GetPrivateProfileInt("Reset", "Reset_NPC_X", 0, Reset_DIR);
	this->Reset_NPC_Y = GetPrivateProfileInt("Reset", "Reset_NPC_Y", 0, Reset_DIR);
#endif

	for(int i(0);i<RESET_EXP_MAX_RES;i++)
	{
		this->Number[i].Res = 0;
		this->Number[i].Exp = 0;
		
#ifdef PRIVATE_MODULE
		this->ItemsRes[i].ItemCount = 0;
		this->ItemsRes[i].ItemIndex = 0;
		this->ItemsRes[i].ItemType = 0;
		this->ItemsRes[i].Res = 0;
		this->LevelRes[i].Res = 0;
		this->LevelRes[i].Level = 0;
#endif
	}
	FILE * file = fopen(Reset_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,Reset_DIR,"LOAD FILE ERROR",0);
		ExitProcess(0);
	}

	char Buff[256];
	int Flag = 0;
	this->rCount = 0;
	this->iCount = 0;
	this->lCount = 0;

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			int n[2];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Number[this->rCount].Res = n[0];
			this->Number[this->rCount].Exp = n[1];
			this->rCount++;
		}
#ifdef PRIVATE_MODULE
		if(g_ExLicense.CheckUser(eExUB::Vadim) || g_ExLicense.CheckUser(eExUB::drynea) || g_ExLicense.CheckUser(eExUB::Local3) || 
			g_ExLicense.CheckUser(eExUB::Cherkashin) || g_ExLicense.CheckUser(eExUB::EpicMU) || 
			g_ExLicense.CheckUser(Gredy) || g_ExLicense.CheckUser(Gredy2) || g_ExLicense.CheckUser(GredyLocal))
		{
			if(Flag == 2)
			{
				int n[4];
				sscanf(Buff, "%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);
				this->ItemsRes[this->iCount].Res = n[0];
				this->ItemsRes[this->iCount].ItemType = n[1];
				this->ItemsRes[this->iCount].ItemIndex = n[2];
				this->ItemsRes[this->iCount].ItemCount = n[3];
				this->iCount++;
			}
		}
		if(g_ExLicense.CheckUser(eExUB::Local) || 
			g_ExLicense.CheckUser(eExUB::ulasevich) || 
			g_ExLicense.CheckUser(eExUB::Cherkashin) || 
			g_ExLicense.CheckUser(eExUB::Local3) || 
			g_ExLicense.CheckUser(eExUB::MU2Play) || g_ExLicense.CheckUser(eExUB::Sentinel) || g_ExLicense.CheckUser(eExUB::EpicMU) || g_ExLicense.CheckUser(eExUB::AlterMU) ||
			g_ExLicense.CheckUser(eExUB::EpicMU) || g_ExLicense.CheckUser(eExUB::Escalate) || g_ExLicense.CheckUser(eExUB::eternalmu) ||
			g_ExLicense.CheckUser(eExUB::Gredy) ||
			g_ExLicense.CheckUser(eExUB::Gredy2) || 
			g_ExLicense.CheckUser(eExUB::GredyLocal) ||
			g_ExLicense.CheckUser(eExUB::mu4you) ||
			g_ExLicense.CheckUser(eExUB::NSGames))
		{
			if(Flag == 3)
			{
				int n[2];
				sscanf(Buff, "%d %d", &n[0], &n[1]);
				this->LevelRes[this->lCount].Res = n[0];
				this->LevelRes[this->lCount].Level = n[1];
				this->lCount++;
			}
		}
		if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2) || g_ExLicense.CheckUser(eExUB::MU2Play)
			 || g_ExLicense.CheckUser(eExUB::Sentinel) || g_ExLicense.CheckUser(eExUB::EpicMU) ||
				g_ExLicense.CheckUser(eExUB::Gredy) ||
				g_ExLicense.CheckUser(eExUB::Gredy2) || 
				g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Escalate) || g_ExLicense.CheckUser(eExUB::eternalmu) ||
				g_ExLicense.CheckUser(eExUB::Artem) || g_ExLicense.CheckUser(eExUB::Artem2) ||
				g_ExLicense.CheckUser(eExUB::RevoMU) || g_ExLicense.CheckUser(eExUB::GloryMU) ||
				g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
				g_ExLicense.CheckUser(eExUB::mu4you) || g_ExLicense.CheckUser(eExUB::NSGames))
		{
			if(Flag == 4)
			{
				RESET_NEEDITEM_DATA list;
				sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d", &list.ResetNum,&list.Type,&list.Index,&list.Level,&list.Skill,&list.Luck,&list.Opt,&list.Exl,&list.Anc,&list.Count);
				this->m_needitem.push_back(list);
			}
			else if(Flag == 5)
			{
				RESET_REWARD_DATA list;
				sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d %d %d",&list.ResetNum,&list.WcoinC,&list.EnableItem,&list.Type,&list.Index,&list.Level,&list.Skill,&list.Luck,&list.Opt,&list.Exl,&list.Anc,&list.Credit);
				this->m_reward.push_back(list);
			}
		}
#endif
	}
	fclose(file);
}

void cResetSystem::ExResetSystemFunciton(int aIndex)
{
	if(!this->EnableResetSystem)return;

	LPOBJ lpObj = &gObj[aIndex];

	int ZenMoney = 0;

	if ( (GetTickCount() - lpObj->MySelfDefenseTime ) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), lpObj->m_Index, 1);
		GCCloseMsgSend(aIndex,-1); //Season 2.5 add-on
		return;
	}

	if(lpObj->SkillRecallParty_Time != 0)
	{
		return;
	}

	if(lpObj->MapNumber != this->m_iMapForReset)
	{
		MsgNormal(aIndex, g_ExText.GetText(3), exMapName(this->m_iMapForReset));
		return;
	}

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		GCServerMsgStringSend(g_ExText.GetText(4),lpObj->m_Index,1);
		return;
	}

	//Проверка на максимальное количество ресетов
	if(lpObj->Reset >= this->Maxres)
	{
		MsgNormal(aIndex,g_ExText.GetText(5),this->Maxres);
		return;
	}
	
	//Проверка на уровень
	if(g_ExLicense.user.Rage)
	{
		if((this->NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0) > lpObj->Level))
		{
			MsgNormal(aIndex,g_ExText.GetText(6),this->NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0));
			return;
		}
	}
	else
	{
#ifdef PRIVATE_MODULE
		if(g_ExLicense.CheckUser(eExUB::Cherkashin) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::AlterMU) || g_ExLicense.CheckUser(eExUB::EpicMU))
		{
			bool SearchRes = false;
			for(int i=0;i<lCount;i++)
			{
				if(this->LevelRes[i].Res == (lpObj->Reset + 1))
				{
					if(this->LevelRes[i].Level > lpObj->Level)
					{
						MsgNormal(aIndex,g_ExText.GetText(6),this->LevelRes[i].Level);
						return;
					} 
					SearchRes = true; 
				}
			} 
			if (!SearchRes)
			{
				if(this->NeedLevel > lpObj->Level)
				{
					MsgNormal(aIndex,g_ExText.GetText(6),this->NeedLevel);
					return;
				} 
			}
			
		 
		}
		else
		{
			if(this->NeedLevel > lpObj->Level)
			{
				MsgNormal(aIndex,g_ExText.GetText(6),this->NeedLevel);
				return;
			} 
		}

#else
		if(this->NeedLevel > lpObj->Level)
		{
			MsgNormal(aIndex,g_ExText.GetText(6),this->NeedLevel);
			return;
		}
#endif
		
	}

	//Проверка на зен
	switch(this->ZenForm)
	{
		case 1: ZenMoney = this->NeedZen * ( lpObj->Reset + 1 ); break;
		case 2: ZenMoney = this->NeedZen; break;
	}

#ifdef PRIVATE_MODULE
	int WCoinMoney = 0;
	int CreditMoney = 0;
	if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea) || g_ExLicense.CheckUser(eExUB::Cherkashin))
		{
		WCoinMoney  = this->NeedWCoinToReset * ( lpObj->Reset + 1 );
		
#if _CONFLICT_
		CreditMoney  = this->NeedCreditToReset * ( lpObj->Reset + 1 );
#endif
		if( lpObj->GameShop.WCoinC < WCoinMoney)
		{
				MsgNormal(aIndex,g_ExText.GetText(7),WCoinMoney);
				return;	
		}
		
#if _CONFLICT_
	

		if( lpObj->ExCred < CreditMoney)
		{
			MsgNormal(aIndex, g_ExText.GetText(8),CreditMoney);
				return;	
		}
#endif
	}
#endif
	
	if(this->ZenForm != 0)
	{
		if(lpObj->Money < ZenMoney)
		{
			MsgNormal(aIndex, g_ExText.GetText(9), ZenMoney);
			return;
		}
	}
	//Проверка на пустой инвентарь
	if(this->NeedEmptyInv)
	{
		if(lpObj->pInventory[0].m_Type != -1 || lpObj->pInventory[1].m_Type != -1 || lpObj->pInventory[2].m_Type != -1 ||
		   lpObj->pInventory[3].m_Type != -1 || lpObj->pInventory[4].m_Type != -1 || lpObj->pInventory[5].m_Type != -1 ||
		   lpObj->pInventory[6].m_Type != -1 || lpObj->pInventory[7].m_Type != -1 || lpObj->pInventory[8].m_Type != -1 ||
		   lpObj->pInventory[9].m_Type != -1 || lpObj->pInventory[10].m_Type != -1|| lpObj->pInventory[11].m_Type != -1)
		{
			MsgNormal(aIndex, g_ExText.GetText(10));
			return;
		}
	}

#ifdef PRIVATE_MODULE
	if(g_ExLicense.CheckUser(eExUB::Vadim) || g_ExLicense.CheckUser(eExUB::drynea) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::Cherkashin))
	{
		for(int i=0;i<iCount;i++)
		{
			if(this->ItemsRes[i].Res == (lpObj->Reset + 1))
			{
				if(gObjGetItemCountInInventory(aIndex,ITEMGET(this->ItemsRes[i].ItemType,this->ItemsRes[i].ItemIndex),0) < this->ItemsRes[i].ItemCount)
				{
					MsgNormal(aIndex, g_ExText.GetText(11),this->ItemsRes[i].ItemCount);
					return;
				}
				gObjDeleteItemsCount(aIndex,ITEMGET(this->ItemsRes[i].ItemType,this->ItemsRes[i].ItemIndex),0,this->ItemsRes[i].ItemCount);
				break;
			}
		}
	}
#endif

	/////////////////////
	//Выполнение ресета//
	/////////////////////
	lpObj->Money -= ZenMoney;
#ifdef PRIVATE_MODULE
if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2) || g_ExLicense.CheckUser(eExUB::drynea)|| g_ExLicense.CheckUser(eExUB::Cherkashin))
			{
		lpObj->GameShop.WCoinC -= WCoinMoney;
		gGameShop.GDSaveUserInfo(lpObj->m_Index);
#if _CONFLICT_
		lpObj->ExCred -= CreditMoney;
		ExUserDataSend(lpObj->m_Index);
#endif
	}
#endif

	lpObj->Level = 1;
	lpObj->Experience = 0;
	lpObj->NextExp = 100;
	if(this->AddForm == 2)
	{
		lpObj->Strength = 25;
		lpObj->Dexterity = 25;
		lpObj->Vitality = 25;
		lpObj->Energy = 25;
		if(g_ExLicense.CheckUser(eExUB::DavitRazmadze) || g_ExLicense.CheckUser(eExUB::DavitRazmadze2) || g_ExLicense.CheckUser(eExUB::DavitRazmadze3))
		{
		}
		else
		{
			if(lpObj->Class == 4)
				lpObj->Leadership = 25;
		}
	}
	//Поинта за ресет
	if(this->AddForm == 1 || this->AddForm == 2)
	{
		switch (lpObj->Class)
		{
			case 0: lpObj->LevelUpPoint = ( lpObj->Reset + 1 ) * this->AddPointsDW ;  break;
			case 1: lpObj->LevelUpPoint = ( lpObj->Reset + 1 ) * this->AddPointsDK ;  break;
			case 2: lpObj->LevelUpPoint = ( lpObj->Reset + 1 ) * this->AddPointsELF ; break;
			case 3: lpObj->LevelUpPoint = ( lpObj->Reset + 1 ) * this->AddPointsMG ;  break;
			case 4: lpObj->LevelUpPoint = ( lpObj->Reset + 1 ) * this->AddPointsDL ;  break;
			case 5: lpObj->LevelUpPoint = ( lpObj->Reset + 1 ) * this->AddPointsSUM ; break;
			case 6: lpObj->LevelUpPoint = ( lpObj->Reset + 1 ) * this->AddPointsRF ; break;
		}
	}
	//Поинта от гранд ресета
	if(gGrandReset.EnableGrandResetSystem)
	{
		if(lpObj->GReset > 0)
		{
			if(gGrandReset.AddForm == 1 || gGrandReset.AddForm == 2)
			{
				switch (lpObj->Class)
				{
					case 0: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsDW ;  break;
					case 1: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsDK ;  break;
					case 2: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsELF ; break;
					case 3: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsMG ;  break;
					case 4: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsDL ;  break;
					case 5: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsSUM ; break;
					case 6: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsRF ; break;
				}
			}
			if(gGrandReset.AddForm == 3)
			{
				switch (lpObj->Class)
				{
					case 0: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsDW  * ( lpObj->Reset+1 ); break;
					case 1: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsDK  * ( lpObj->Reset+1 ); break;
					case 2: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsELF * ( lpObj->Reset+1 ); break;
					case 3: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsMG  * ( lpObj->Reset+1 ); break;
					case 4: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsDL  * ( lpObj->Reset+1 ); break;
					case 5: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsSUM * ( lpObj->Reset+1 ); break;
					case 6: lpObj->LevelUpPoint += lpObj->GReset * gGrandReset.AddPointsRF * ( lpObj->Reset+1 ); break;
				}
			}
		}
	}

	lpObj->LevelUpPoint += lpObj->ExFreePoints;
	
	lpObj->Reset += 1;

	if(this->AddCredits > 0)
	{
		if(g_ExLicense.CheckUser(eExUB::NSGames))
		{
			lpObj->PCPoint += this->AddCredits;	
		}
		else
		{
			lpObj->ExCred += this->AddCredits;		
		}
	}
	if(this->AddWcoinC > 0)
	{
		lpObj->GameShop.WCoinC += this->AddWcoinC;
	}
	if(this->AddWcoinP > 0)
	{
		lpObj->GameShop.WCoinP += this->AddWcoinP;
	}
	if(this->AddGoblinPoint > 0)
	{
		lpObj->GameShop.GoblinPoint += this->AddGoblinPoint;
	}

	if(this->AddWcoinC > 0 || this->AddWcoinP > 0 || this->AddGoblinPoint > 0)
	{
		gGameShop.GDSaveUserInfo(aIndex);
	}	

	ExFireCracker(aIndex, lpObj->X, lpObj->Y);

	lpObj->Life = DCInfo.DefClass[lpObj->Class].Life + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelLife  + ((lpObj->Vitality - DCInfo.DefClass[lpObj->Class].Vitality ) * DCInfo.DefClass[lpObj->Class].VitalityToLife);
	lpObj->Mana = DCInfo.DefClass[lpObj->Class].Mana + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelMana  + ((lpObj->Energy - DCInfo.DefClass[lpObj->Class].Energy ) * DCInfo.DefClass[lpObj->Class].EnergyToMana);

	lpObj->MaxLife = DCInfo.DefClass[lpObj->Class].Life + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelLife  + ((lpObj->Vitality - DCInfo.DefClass[lpObj->Class].Vitality ) * DCInfo.DefClass[lpObj->Class].VitalityToLife);
	lpObj->MaxMana = DCInfo.DefClass[lpObj->Class].Mana + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelMana  + ((lpObj->Energy - DCInfo.DefClass[lpObj->Class].Energy ) * DCInfo.DefClass[lpObj->Class].EnergyToMana);

	lpObj->VitalityToLife = DCInfo.DefClass[lpObj->Class].VitalityToLife;
	lpObj->EnergyToMana = DCInfo.DefClass[lpObj->Class].EnergyToMana;

	::gObjSetBP(aIndex);
	lpObj->BP = lpObj->MaxBP / 2;
	::gObjCalcMaxLifePower(aIndex);

	GCReFillSend(aIndex, (int)lpObj->MaxLife + lpObj->AddLife, 0xFE, 0, lpObj->iMaxShield + lpObj->iAddShield);
	//gObjSetBP(aIndex);
	GCManaSend(aIndex,(int)lpObj->MaxMana + lpObj->AddMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
	gObjCalCharacter(aIndex);

	//gObjCloseSet(aIndex, 1);
	ResetSystemGC_CharUpdate(lpObj);

	GCMoneySend(aIndex, lpObj->Money);

#if(CUSTOM_NOOBBUFF)
	if(ExConfig.CommonServer.bNoobBuffEnable)
	{
		if(ExConfig.CommonServer.iNoobBuffMaxReset > lpObj->Reset)
		{
			if(gObjSearchActiveEffect(lpObj,AT_NOOB_BUFF) == TRUE)
			{
				gObjRemoveBuffEffect(lpObj,AT_NOOB_BUFF);
			}
		}
	}
#endif

	LogAddTD("[ResetSystem] Accaunt: %s , Name: %s , Reset: %d",lpObj->AccountID, lpObj->Name,lpObj->Reset);

#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.ResetUp(aIndex);
#endif
}

int cResetSystem::Main(LPOBJ lpObj)
{
	if(!this->EnableResetSystem || !this->DinamicExp)
	{
		return gAddExperience;
	}

	for(int i=0;i<this->rCount;i++)
	{
		if(this->Number[i].Res == lpObj->Reset)
		{
			return this->Number[i].Exp;
		}
	}

	return gAddExperience;
}
#if(ADD_RESET_WINDOW)
bool cResetSystem::NpcDialog(int aIndex, int aNpcIndex)
{
	if( !g_ExLicense.CheckUser(eExUB::Local) && 
		!g_ExLicense.CheckUser(eExUB::ulasevich) && 
		!g_ExLicense.CheckUser(eExUB::ulasevich2)&& 
		!g_ExLicense.CheckUser(eExUB::MU2Play)  && 
		!g_ExLicense.CheckUser(eExUB::Sentinel) &&
		!g_ExLicense.CheckUser(eExUB::EpicMU) && 
		!g_ExLicense.CheckUser(eExUB::Escalate) &&
		!g_ExLicense.CheckUser(eExUB::Artem) && 
		!g_ExLicense.CheckUser(eExUB::Artem2) &&
		!g_ExLicense.CheckUser(eExUB::RevoMU) &&
		!g_ExLicense.CheckUser(eExUB::GloryMU) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei)&&
		!g_ExLicense.CheckUser(eExUB::mu4you) &&
		!g_ExLicense.CheckUser(eExUB::eternalmu) &&
		!g_ExLicense.CheckUser(eExUB::NSGames))
	{
		return false;
	}

	if(!OBJMAX_RANGE(aIndex) && !OBJMAX_RANGE(aNpcIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if(lpNpc->Class		== this->Reset_NPC_ID  &&
	   lpNpc->MapNumber	== this->Reset_NPC_MAP &&
	   lpNpc->X			== this->Reset_NPC_X   &&
	   lpNpc->Y			== this->Reset_NPC_Y )
	{
		this->GCDialogInfo(aIndex);
		return true;
	}

	return false;
}

void cResetSystem::GCDialogInfo(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	GC_RESET_DATA pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x43, sizeof(pMsg));

	pMsg.Result = true;

	if((GetTickCount() - lpUser->MySelfDefenseTime ) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), aIndex, 1);
		GCCloseMsgSend(aIndex,-1);
		return;
	}

	if(lpUser->MapNumber != this->m_iMapForReset)
	{
		MsgNormal(aIndex, g_ExText.GetText(3), exMapName(this->m_iMapForReset));
		return;
	}

	if(lpUser->SkillRecallParty_Time != 0)
	{
		MsgNormal(aIndex,"[Reset]: Skill Recall Party Time");
		return;
	}
	
	if(gMoveCommand.CheckInterfaceToMove(lpUser) == 0)
	{
		GCServerMsgStringSend("[Reset]: Interface Disable",lpUser->m_Index,1);
		return;
	}

	pMsg.Reset = lpUser->Reset;
	pMsg.MaxReset = this->Maxres;
	if(lpUser->Reset >= this->Maxres)
	{
		pMsg.Result = false;
	}
	
	//Проверка на уровень
	pMsg.NeedLevel = this->NeedLevel;

	bool SearchRes = false;
	for(int i=0; i<this->lCount; i++)
	{
		if(this->LevelRes[i].Res == (lpUser->Reset + 1))
		{
			if(g_ExLicense.user.Rage)
			{
				pMsg.NeedLevel = this->LevelRes[i].Level - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0);
				if(pMsg.NeedLevel > lpUser->Level)
				{
					pMsg.Result = false;
				} 
				SearchRes = true; 
				break;
			}
			else
			{
				pMsg.NeedLevel = this->LevelRes[i].Level;
				if(this->LevelRes[i].Level > lpUser->Level)
				{
					pMsg.Result = false;
				} 
				SearchRes = true; 
				break;
			}
		}
	} 
	if (!SearchRes)
	{
		if(g_ExLicense.user.Rage)
		{
			if((this->NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0) > lpUser->Level))
			{
				pMsg.Result = false;
			}
		}
		else
		{
			if(this->NeedLevel > lpUser->Level)
			{
				pMsg.Result = false;
			} 
		}
	}

	//Проверка на зен
	int ZenMoney = 0;

	switch(this->ZenForm)
	{
		case 1: ZenMoney = this->NeedZen * ( lpUser->Reset + 1 ); break;
		case 2: ZenMoney = this->NeedZen; break;
	}

	if(this->ZenForm != 0)
	{
		if(lpUser->Money < ZenMoney)
		{
			pMsg.Result = false;
		}
	}

	pMsg.NeedMoney = ZenMoney;

	//Проверка на пустой инвентарь
	if(this->NeedEmptyInv)
	{
		if(lpUser->pInventory[0].m_Type != -1 || lpUser->pInventory[1].m_Type != -1 || lpUser->pInventory[2].m_Type != -1 ||
		   lpUser->pInventory[3].m_Type != -1 || lpUser->pInventory[4].m_Type != -1 || lpUser->pInventory[5].m_Type != -1 ||
		   lpUser->pInventory[6].m_Type != -1 || lpUser->pInventory[7].m_Type != -1 || lpUser->pInventory[8].m_Type != -1 ||
		   lpUser->pInventory[9].m_Type != -1 || lpUser->pInventory[10].m_Type != -1|| lpUser->pInventory[11].m_Type != -1)
		{
			MsgNormal(aIndex,"[Reset]: You need Empty Inventory to Reset");
			return;
		}
	}

	//Поинта за ресет
	int LevelUpPoint = 0;

	if(this->AddForm == 1 || this->AddForm == 2)
	{
		switch (lpUser->Class)
		{
			case 0: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsDW ;  break;
			case 1: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsDK ;  break;
			case 2: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsELF ; break;
			case 3: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsMG ;  break;
			case 4: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsDL ;  break;
			case 5: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsSUM ; break;
			case 6: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsRF ; break;
		}
	}

	//Поинта от гранд ресета
	if(gGrandReset.EnableGrandResetSystem)
	{
		if(lpUser->GReset > 0)
		{
			if(gGrandReset.AddForm == 1 || gGrandReset.AddForm == 2)
			{
				switch (lpUser->Class)
				{
					case 0: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDW ;  break;
					case 1: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDK ;  break;
					case 2: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsELF ; break;
					case 3: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsMG ;  break;
					case 4: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDL ;  break;
					case 5: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsSUM ; break;
					case 6: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsRF ; break;
				}
			}
			if(gGrandReset.AddForm == 3)
			{
				switch (lpUser->Class)
				{
					case 0: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDW  * ( lpUser->Reset+1 ); break;
					case 1: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDK  * ( lpUser->Reset+1 ); break;
					case 2: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsELF * ( lpUser->Reset+1 ); break;
					case 3: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsMG  * ( lpUser->Reset+1 ); break;
					case 4: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDL  * ( lpUser->Reset+1 ); break;
					case 5: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsSUM * ( lpUser->Reset+1 ); break;
					case 6: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsRF  * ( lpUser->Reset+1 ); break;
				}
			}
		}
	}

	LevelUpPoint += lpUser->ExFreePoints;
	pMsg.RewardPoint = LevelUpPoint;

	pMsg.AddCredits = this->AddCredits;
	pMsg.AddWcoinC = this->AddWcoinC;
	pMsg.AddWcoinP = this->AddWcoinP;
	pMsg.AddWcoinG = this->AddGoblinPoint;

	// Need Item
	pMsg.AddEnableItem = false;
	pMsg.AddItem = -1;
	pMsg.AddItemLevel = 0;
	pMsg.AddItemSkill = 0;
	pMsg.AddItemLuck = 0;
	pMsg.AddItemOpt = 0;
	pMsg.AddItemExl = 0;
	pMsg.AddItemAnc = 0;
	pMsg.AddItemCount = 0;

	for(int i = 0; i < this->m_needitem.size(); i++)
	{
		RESET_NEEDITEM_DATA & nitem = this->m_needitem[i];
		if(nitem.ResetNum == (lpUser->Reset + 1))
		{
			pMsg.AddEnableItem = true;
			pMsg.AddItem = ITEMGET(nitem.Type, nitem.Index);
			pMsg.AddItemLevel = nitem.Level;
			pMsg.AddItemSkill = nitem.Skill;
			pMsg.AddItemLuck = nitem.Luck;
			pMsg.AddItemOpt = nitem.Opt;
			pMsg.AddItemExl = nitem.Exl;
			pMsg.AddItemAnc = nitem.Anc;
			pMsg.AddItemCount = nitem.Count;

			if(!SearchItem(aIndex, nitem.Type, nitem.Index, nitem.Level, nitem.Skill, nitem.Luck, nitem.Opt, nitem.Exl, nitem.Anc, nitem.Count, false))
			{
				pMsg.Result = false;
			}

			break;
		}
	}

	//reward Item
	pMsg.RewardEnableItem = false;
	pMsg.RewardItem = 0;
	pMsg.RewardLevel = 0;
	pMsg.RewardSkill = 0;
	pMsg.RewardLuck = 0;
	pMsg.RewardOpt = 0;
	pMsg.RewardExl = 0;
	pMsg.RewardAnc = 0;

	for(int i = 0; i < this->m_reward.size(); i++)
	{
		RESET_REWARD_DATA & ritem = this->m_reward[i];
		if(ritem.ResetNum == (lpUser->Reset + 1))
		{
			pMsg.AddWcoinC = ritem.WcoinC;
			pMsg.RewardEnableItem = ritem.EnableItem;
			pMsg.RewardItem = ITEMGET(ritem.Type, ritem.Index);
			pMsg.RewardLevel = ritem.Level;
			pMsg.RewardSkill = ritem.Skill;
			pMsg.RewardLuck = ritem.Luck;
			pMsg.RewardOpt = ritem.Opt;
			pMsg.RewardExl = ritem.Exl;
			pMsg.RewardAnc = ritem.Anc;
			pMsg.AddCredits = ritem.Credit;
			break;
		}
	}

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void cResetSystem::CGResulInfo(int aIndex)
{
	if(!this->EnableResetSystem)return;

	LPOBJ lpUser = &gObj[aIndex];

	if((GetTickCount() - lpUser->MySelfDefenseTime ) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), aIndex, 1);
		GCCloseMsgSend(aIndex,-1);
		return;
	}

	if(lpUser->MapNumber != this->m_iMapForReset)
	{
		MsgNormal(aIndex, g_ExText.GetText(3), exMapName(this->m_iMapForReset));
		return;
	}

	if(lpUser->SkillRecallParty_Time != 0)
	{
		MsgNormal(aIndex,"[Reset]: Skill Recall Party Time");
		return;
	}
	
	if(gMoveCommand.CheckInterfaceToMove(lpUser) == 0)
	{
		GCServerMsgStringSend("[Reset]: Interface Disable",lpUser->m_Index,1);
		return;
	}

	if(lpUser->Reset >= this->Maxres)
	{
		MsgNormal(aIndex,"[Reset]: Max Reset %d",this->Maxres);
		return;
	}
	
	//Проверка на уровень
	int iNeedLevel = this->NeedLevel;

	bool SearchRes = false;
	for(int i=0; i<this->lCount; i++)
	{
		if(g_ExLicense.user.Rage)
		{
			if(this->LevelRes[i].Res == (lpUser->Reset + 1))
			{
				if(this->LevelRes[i].Level - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0) > lpUser->Level)
				{
					MsgNormal(aIndex,"[Reset]: You need above %d Level to Reset",this->LevelRes[i].Level);
					return;
				} 
				SearchRes = true; 
				break;
			}
		}
		else
		{
			if(this->LevelRes[i].Res == (lpUser->Reset + 1))
			{
				if(this->LevelRes[i].Level > lpUser->Level)
				{
					MsgNormal(aIndex,"[Reset]: You need above %d Level to Reset",this->LevelRes[i].Level);
					return;
				} 
				SearchRes = true; 
				break;
			}
		}
	} 
	if(!SearchRes)
	{
		if(g_ExLicense.user.Rage)
		{
			if((this->NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0) > lpUser->Level))
			{
				MsgNormal(aIndex, "[Reset]: You need above %d Level to Reset", (this->NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0)));
				return;
			}
		}
		else
		{
			if(this->NeedLevel > lpUser->Level)
			{
				MsgNormal(aIndex,"[Reset]: You need above %d Level to Reset",this->NeedLevel);
				return;
			} 
		}
	}

	//Проверка на зен
	int ZenMoney = 0;

	switch(this->ZenForm)
	{
		case 1: ZenMoney = this->NeedZen * ( lpUser->Reset + 1 ); break;
		case 2: ZenMoney = this->NeedZen; break;
	}

	if(this->ZenForm != 0)
	{
		if(lpUser->Money < ZenMoney)
		{
			MsgNormal(aIndex,"[Reset]: You need above %d Zen to Reset",ZenMoney);
			return;
		}
	}

	//Проверка на пустой инвентарь
	if(this->NeedEmptyInv)
	{
		if(lpUser->pInventory[0].m_Type != -1 || lpUser->pInventory[1].m_Type != -1 || lpUser->pInventory[2].m_Type != -1 ||
		   lpUser->pInventory[3].m_Type != -1 || lpUser->pInventory[4].m_Type != -1 || lpUser->pInventory[5].m_Type != -1 ||
		   lpUser->pInventory[6].m_Type != -1 || lpUser->pInventory[7].m_Type != -1 || lpUser->pInventory[8].m_Type != -1 ||
		   lpUser->pInventory[9].m_Type != -1 || lpUser->pInventory[10].m_Type != -1|| lpUser->pInventory[11].m_Type != -1)
		{
			MsgNormal(aIndex,"[Reset]: You need Empty Inventory to Reset");
			return;
		}
	}

	//Поинта за ресет
	int LevelUpPoint = 0;

	if(this->AddForm == 1 || this->AddForm == 2)
	{
		switch (lpUser->Class)
		{
			case 0: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsDW ;  break;
			case 1: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsDK ;  break;
			case 2: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsELF ; break;
			case 3: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsMG ;  break;
			case 4: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsDL ;  break;
			case 5: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsSUM ; break;
			case 6: LevelUpPoint = ( lpUser->Reset + 1 ) * this->AddPointsRF ; break;
		}
	}

	//Поинта от гранд ресета
	if(gGrandReset.EnableGrandResetSystem)
	{
		if(lpUser->GReset > 0)
		{
			if(gGrandReset.AddForm == 1 || gGrandReset.AddForm == 2)
			{
				switch (lpUser->Class)
				{
					case 0: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDW ;  break;
					case 1: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDK ;  break;
					case 2: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsELF ; break;
					case 3: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsMG ;  break;
					case 4: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDL ;  break;
					case 5: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsSUM ; break;
					case 6: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsRF ; break;
				}
			}
			if(gGrandReset.AddForm == 3)
			{
				switch (lpUser->Class)
				{
					case 0: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDW  * ( lpUser->Reset+1 ); break;
					case 1: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDK  * ( lpUser->Reset+1 ); break;
					case 2: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsELF * ( lpUser->Reset+1 ); break;
					case 3: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsMG  * ( lpUser->Reset+1 ); break;
					case 4: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDL  * ( lpUser->Reset+1 ); break;
					case 5: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsSUM * ( lpUser->Reset+1 ); break;
					case 6: LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsRF  * ( lpUser->Reset+1 ); break;
				}
			}
		}
	}

	LevelUpPoint += lpUser->ExFreePoints;

	/*
	pMsg.AddCredits = this->AddCredits;
	pMsg.AddWcoinC = this->AddWcoinC;
	pMsg.AddWcoinP = this->AddWcoinP;
	pMsg.AddWcoinG = this->AddGoblinPoint;
	*/

	// Need Item
	for(int i = 0; i < this->m_needitem.size(); i++)
	{
		RESET_NEEDITEM_DATA & nitem = this->m_needitem[i];
		if(nitem.ResetNum == (lpUser->Reset + 1))
		{
			if(!SearchItem(aIndex, nitem.Type, nitem.Index, nitem.Level, nitem.Skill, nitem.Luck, nitem.Opt, nitem.Exl, nitem.Anc, nitem.Count, true))
			{
				MsgNormal(aIndex,"[Reset]: Need Reset Items");
				return;
			}
			break;
		}
	}

	//reward Item
	for(int i = 0; i < this->m_reward.size(); i++)
	{
		RESET_REWARD_DATA & ritem = this->m_reward[i];
		if(ritem.ResetNum == (lpUser->Reset + 1))
		{
			if(ritem.WcoinC > 0)
			{
				lpUser->GameShop.WCoinC += ritem.WcoinC;
				gGameShop.GDSaveUserInfo(lpUser->m_Index);
			}
			if(ritem.EnableItem)
			{
				ItemSerialCreateSend(aIndex,lpUser->MapNumber,lpUser->X,lpUser->Y,ITEMGET(ritem.Type, ritem.Index),ritem.Level,0,ritem.Skill,ritem.Luck,ritem.Opt,aIndex,ritem.Exl,ritem.Anc);
			}
			if(ritem.Credit > 0)
			{
				lpUser->ExCred += ritem.Credit;
			}
			break;
		}
	}

	/////////////////////
	//Выполнение ресета//
	/////////////////////
	lpUser->Money -= ZenMoney;
	lpUser->Level = 1;
	lpUser->Experience = 0;
	lpUser->NextExp = 100;
	if(this->AddForm == 2)
	{
		lpUser->Strength = 25;
		lpUser->Dexterity = 25;
		lpUser->Vitality = 25;
		lpUser->Energy = 25;

		if(lpUser->Class == 4)
		{
			lpUser->Leadership = 25;
		}
	}
	lpUser->LevelUpPoint = LevelUpPoint;
	
	lpUser->Reset++;

	if(this->AddCredits>0)
	{
		lpUser->ExCred += AddCredits;
	}

	/*if(this->AddWcoinC > 0)
	{
		lpUser->GameShop.WCoinC += this->AddWcoinC;
	}*/
	if(this->AddWcoinP > 0)
	{
		lpUser->GameShop.WCoinP += this->AddWcoinP;
	}
	if(this->AddGoblinPoint > 0)
	{
		lpUser->GameShop.GoblinPoint += this->AddGoblinPoint;
	}

	if(this->AddWcoinC > 0 || this->AddWcoinP > 0 || this->AddGoblinPoint > 0)
	{
		gGameShop.GDSaveUserInfo(aIndex);
	}	

	ExFireCracker(aIndex, lpUser->X, lpUser->Y);

	lpUser->Life = DCInfo.DefClass[lpUser->Class].Life + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelLife  + ((lpUser->Vitality - DCInfo.DefClass[lpUser->Class].Vitality ) * DCInfo.DefClass[lpUser->Class].VitalityToLife);
	lpUser->Mana = DCInfo.DefClass[lpUser->Class].Mana + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelMana  + ((lpUser->Energy - DCInfo.DefClass[lpUser->Class].Energy ) * DCInfo.DefClass[lpUser->Class].EnergyToMana);

	lpUser->MaxLife = DCInfo.DefClass[lpUser->Class].Life + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelLife  + ((lpUser->Vitality - DCInfo.DefClass[lpUser->Class].Vitality ) * DCInfo.DefClass[lpUser->Class].VitalityToLife);
	lpUser->MaxMana = DCInfo.DefClass[lpUser->Class].Mana + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelMana  + ((lpUser->Energy - DCInfo.DefClass[lpUser->Class].Energy ) * DCInfo.DefClass[lpUser->Class].EnergyToMana);

	lpUser->VitalityToLife = DCInfo.DefClass[lpUser->Class].VitalityToLife;
	lpUser->EnergyToMana = DCInfo.DefClass[lpUser->Class].EnergyToMana;

	::gObjSetBP(aIndex);
	lpUser->BP = lpUser->MaxBP / 2;
	::gObjCalcMaxLifePower(aIndex);

	GCReFillSend(aIndex, (int)lpUser->MaxLife + lpUser->AddLife, 0xFE, 0, lpUser->iMaxShield + lpUser->iAddShield);
	//gObjSetBP(aIndex);
	GCManaSend(aIndex,(int)lpUser->MaxMana + lpUser->AddMana, 0xFE, 0, lpUser->MaxBP + lpUser->AddBP);
	gObjCalCharacter(aIndex);

	//gObjCloseSet(aIndex, 1);
	ResetSystemGC_CharUpdate(lpUser);

	GCMoneySend(aIndex, lpUser->Money);
	LogAddTD("[ResetSystem] Accaunt: %s , Name: %s , Reset: %d",lpUser->AccountID, lpUser->Name,lpUser->Reset);

#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.ResetUp(aIndex);
#endif
}

bool cResetSystem::SearchItem(int aIndex, int Type, int Index, int Level, bool Skill, bool Luck, bool Opt, bool Exl, bool Anc, int count, bool del)
{
	LPOBJ lpUser = &gObj[aIndex];
	int iCount = 0;
	short iType = ITEMGET(Type, Index);

	for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
	{
		if( lpUser->pInventory[i].m_Type == iType && 
			lpUser->pInventory[i].m_Level >= Level &&
			CheckOptionItem(lpUser->pInventory[i].m_Option1, Skill, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_Option2, Luck, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_Option3, Opt, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_NewOption, Exl, FALSE) &&
			CheckOptionItem(lpUser->pInventory[i].m_SetOption, Anc, FALSE) )
		{
			iCount++;
		}
	}

	if(iCount >= count)
	{
		if(del)
		{
			int iDelCount = 0;
			for(int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE; i++)
			{
				if( lpUser->pInventory[i].m_Type == iType && 
					lpUser->pInventory[i].m_Level >= Level &&
					CheckOptionItem(lpUser->pInventory[i].m_Option1, Skill, FALSE) &&
					CheckOptionItem(lpUser->pInventory[i].m_Option2, Luck, FALSE) &&
					CheckOptionItem(lpUser->pInventory[i].m_Option3, Opt, FALSE) &&
					CheckOptionItem(lpUser->pInventory[i].m_NewOption, Exl, FALSE) &&
					CheckOptionItem(lpUser->pInventory[i].m_SetOption, Anc, FALSE) )
				{
					gObjInventoryDeleteItem(aIndex, i);
					GCInventoryItemDeleteSend(aIndex, i, 1);
					iDelCount++;
					if(iDelCount == count)
					{
						return true;
					}
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void cResetSystem::CGResetMenu(int aIndex)
{
	if( !g_ExLicense.CheckUser(eExUB::Local) && 
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	{
		return;
	}

	this->GCDialogInfo(aIndex);
}

#endif