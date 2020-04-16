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
#include "CustomSystem.h"
#include "VIPSystem.h"

cResetSystem gResetSystem;

void cResetSystem::Load()
{
#if(ADD_RESET_WINDOW)
	this->Reset_NPC_ID = 0;
	this->Reset_NPC_MAP = 0;
	this->Reset_NPC_X = 0;
	this->Reset_NPC_Y = 0;
#endif

	this->EnableResetSystem = GetPrivateProfileInt("Reset","Enable",0,Reset_DIR);	
	this->Maxres = GetPrivateProfileInt("Reset","Max.res",100,Reset_DIR);
	this->NeedLevel = GetPrivateProfileInt("Reset","Need.Level",0,Reset_DIR);
	//this->NeedLevelVip = GetPrivateProfileInt("Reset","Need.Level.Vip",0,Reset_DIR);
	
	this->AddCredits = GetPrivateProfileInt("Reset","AddCredits",0,Reset_DIR);
	this->AddWcoinC = GetPrivateProfileInt("Reset","AddWcoinC",0,Reset_DIR);
	this->AddWcoinP = GetPrivateProfileInt("Reset","AddWcoinP",0,Reset_DIR);
	this->AddGoblinPoint = GetPrivateProfileInt("Reset","AddGoblinPoint",0,Reset_DIR);

	GetPrivateProfileString("Reset", "cmd","/reset",this->CommandReset,100,Reset_DIR);

#if(ADD_RESET_WINDOW)
	this->Reset_NPC_ID = GetPrivateProfileInt("Reset", "Reset_NPC_ID", 0, Reset_DIR);
	this->Reset_NPC_MAP = GetPrivateProfileInt("Reset", "Reset_NPC_MAP", 0, Reset_DIR);
	this->Reset_NPC_X = GetPrivateProfileInt("Reset", "Reset_NPC_X", 0, Reset_DIR);
	this->Reset_NPC_Y = GetPrivateProfileInt("Reset", "Reset_NPC_Y", 0, Reset_DIR);
#endif

	for(int i(0);i<RESET_EXP_MAX_RES;i++)
	{
		this->PointRes[i].Res = 0;
		this->ExpRes[i].Exp = 0;
		this->ZenRes[i].Zen = 0;
	}

	FILE * file = fopen(Reset_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,Reset_DIR,"LOAD FILE ERROR",0);
		ExitProcess(0);
	}

	char Buff[256];
	int Flag = 0;
	this->expCount = 0;
	this->pointCount = 0;
	this->zenCount = 0;

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			int reset;
			float rate;

			sscanf(Buff, "%d %f", &reset, &rate);
			this->ExpRes[this->expCount].Res = reset;
			this->ExpRes[this->expCount].Exp = rate;
			this->expCount++;
		}
		else if (Flag == 2)
		{
			int reset;
			int zen;

			sscanf(Buff, "%d %d", &reset, &zen);
			this->ZenRes[this->zenCount].Res = reset;
			this->ZenRes[this->zenCount].Zen = zen;
			this->zenCount++;
		}
		else if (Flag == 3)
		{
			int reset;
			int point;

			sscanf(Buff, "%d %d", &reset, &point);
			this->PointRes[this->pointCount].Res = reset;
			this->PointRes[this->pointCount].Point = point;
			this->pointCount++;
		}
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

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		GCServerMsgStringSend(g_ExText.GetText(4),lpObj->m_Index,1);
		return;
	}

	if(lpObj->Reset >= this->Maxres)
	{
		MsgNormal(aIndex,g_ExText.GetText(5),this->Maxres);
		return;
	}
	
	if(g_CustomSystem.IsRage())
	{
		if((this->NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0) > lpObj->Level))
		{
			MsgNormal(aIndex,g_ExText.GetText(6),this->NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0));
			return;
		}
	}
	else
	{
		int needLevel = GetNeedLevel(lpObj->m_Index);

		if(needLevel > lpObj->Level)
		{
			MsgNormal(aIndex,g_ExText.GetText(6),needLevel);
			return;
		} 
	}

	int needZen = GetNeedZen(lpObj->m_Index);
	if (needZen == 0)
	{
		LogAdd("[ResetSystem] Failed to find NeedZen for reset %d.", lpObj->Reset);
		return;
	}

	if(lpObj->Money < needZen)
	{
		MsgNormal(aIndex, g_ExText.GetText(9), ZenMoney);
		return;
	}

	int addPoints = GetAddPoints(lpObj->m_Index);
	if (addPoints == 0)
	{
		LogAdd("[ResetSystem] Failed to find AddPoints for reset %d.", lpObj->Reset);
		return;
	}

	/////////////////////
	//Reseting		   //
	/////////////////////
	lpObj->Money -= ZenMoney;
	lpObj->Level = 1;
	lpObj->Experience = 0;
	lpObj->NextExp = 100;
	lpObj->Strength = 25;
	lpObj->Dexterity = 25;
	lpObj->Vitality = 25;
	lpObj->Energy = 25;
	
	if(lpObj->Class == 4) lpObj->Leadership = 25;

	lpObj->LevelUpPoint = ( lpObj->Reset + 1 ) * addPoints;
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

	LogAddTD("[ResetSystem] Accaunt: %s , Name: %s , Reset: %d",lpObj->AccountID, lpObj->Name,lpObj->Reset);

#if(SYSTEM_ACHIEVEMENTS)
	g_Achievements.ResetUp(aIndex);
#endif
}

int cResetSystem::Main(LPOBJ lpObj)
{
	// This function was disabled due to new exp system based on reset.

	/*if(!this->EnableResetSystem)
	{*/
	return gAddExperience;
	/*}
	else
	{
		int rate = GetExpRate(lpObj->m_Index);
		if (rate == 0)
		{
			LogAdd("[ResetSystem] Failed to find ExpRate for reset %d.", lpObj->Reset);
			return gAddExperience;
		}
		else
		{
			return rate;
		}
	}*/
}

#if(ADD_RESET_WINDOW)

bool cResetSystem::NpcDialog(int aIndex, int aNpcIndex)
{
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

float cResetSystem::GetExpRate(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	for(int i = 0; i < expCount; i++)
	{
		if (ExpRes[i].Res == lpUser->Reset)
		{
			return ExpRes[i].Exp;
		}
	}

	return 0;
}

int cResetSystem::GetNeedZen(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	for(int i = 0; i < zenCount; i++)
	{
		if (ZenRes[i].Res == lpUser->Reset)
		{
			return ZenRes[i].Zen;
		}
	}

	return 0;
}

int cResetSystem::GetAddPoints(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	for(int i = 0; i < pointCount; i++)
	{
		if (PointRes[i].Res == lpUser->Reset +1)
		{
			return PointRes[i].Point;
		}
	}

	return 0;
}

void cResetSystem::Exp(LPOBJ lpUser, __int64 & Experience)
{
	float rate = GetExpRate(lpUser->m_Index);

	if (rate == 0)
	{
		LogAdd("[ResetSystem] Failed to find ExpRate for reset %d.", lpUser->Reset);
		return ;
	}

	Experience = (__int64)(Experience * rate);
}

int cResetSystem::GetNeedLevel(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	return /*(g_VIPSystem.VipTimeLeft(lpUser->PremiumTime) > 0) ? this->NeedLevelVip : */this->NeedLevel;
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
	if(lpUser->Reset >= this->Maxres)
	{
		pMsg.Result = false;
	}
	
	int needLevel = GetNeedLevel(lpUser->m_Index);
	pMsg.NeedLevel = needLevel;

	if(needLevel > lpUser->Level)
	{
		pMsg.Result = false;
	} 

	pMsg.NeedMoney = GetNeedZen(lpUser->m_Index);

	if (pMsg.NeedMoney > lpUser->Money)
	{
		pMsg.Result = false;
	}

	int LevelUpPoint = GetAddPoints(lpUser->m_Index);

	LevelUpPoint += lpUser->ExFreePoints;
	pMsg.RewardPoint = LevelUpPoint;

	pMsg.AddCredits = this->AddCredits;
	pMsg.AddWcoinC = this->AddWcoinC;
	pMsg.AddWcoinP = this->AddWcoinP;
	pMsg.AddWcoinG = this->AddGoblinPoint;
	
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
	int iNeedLevel = GetNeedLevel(lpUser->m_Index);
	if(iNeedLevel > lpUser->Level)
	{
		MsgNormal(aIndex,"[Reset]: You need above %d Level to Reset",this->NeedLevel);
		return;
	} 

	int ZenMoney = GetNeedZen(lpUser->m_Index);

	if (lpUser->Money < ZenMoney)
	{
		MsgNormal(aIndex, "[Reset]: You need at least %d Zen to Reset", ZenMoney);
		return;
	}

	int LevelUpPoint = GetAddPoints(lpUser->m_Index);

	LevelUpPoint += lpUser->ExFreePoints;

	lpUser->Money -= ZenMoney;
	lpUser->Level = 1;
	lpUser->Experience = 0;
	lpUser->NextExp = 100;

	lpUser->Strength = 25;
	lpUser->Dexterity = 25;
	lpUser->Vitality = 25;
	lpUser->Energy = 25;

	if(lpUser->Class == 4)
	{
		lpUser->Leadership = 25;
	}

	lpUser->LevelUpPoint = LevelUpPoint;
	
	lpUser->Reset++;

	if(this->AddCredits>0)
	{
		lpUser->ExCred += AddCredits;
	}
	if(this->AddWcoinC > 0)
	{
		lpUser->GameShop.WCoinC += this->AddWcoinC;
	}
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

void cResetSystem::CGResetMenu(int aIndex)
{
	this->GCDialogInfo(aIndex);
}

#endif