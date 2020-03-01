#include "StdAfx.h"
#include "OfflineMode.h"
#include "user.h"
#include "ExUser.h"
#include "ObjUseSkill.h"
#include "GameMain.h"
#include "ConnectEx.h"
#include "MagicDamage.h"
#include "logproc.h"
#include "PremiumSystemEx.h"
#include "ExLicense.h"
#include "Message.h"
#include "ExGDManager.h"
#include "NewMasterLevelSystem.h"
#include "..\\common\\winutil.h"
#include "SProtocol.h"
#include "MapServerManager.h"
#include "QuestUtil.h"
#include "SpotReturn.h"
#include "ConMember.h"
#include "PersonalShopEx.h"
#include "BuffManager.h"
#include "DBSockMng.h"
#include "Optimization.h"
#include "ExText.h"
#include "Functions.h"

#if(OFFLINE_MODE==TRUE)
// ----------------------------------------------------------------------------------------------

OfflineMode g_OfflineMode;
// ----------------------------------------------------------------------------------------------

OfflineMode::OfflineMode()
{
	this->StartBonusPay = 0;
	this->HourCredit = 0;
	this->m_bLoadedDB = false;
}
// ----------------------------------------------------------------------------------------------

OfflineMode::~OfflineMode()
{
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Load()
{
	this->Read(gDirPath.GetNewPath("ExData\\OfflineMode.ini"));
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Read(char* filename)
{
	//this->StartBonusPay = GetPrivateProfileInt("ExTeam", "StartBonusPay", 0, filename);
	//this->HourZenPay = GetPrivateProfileInt("ExTeam", "HourZenPay", 0, filename);
	this->PriceZen = GetPrivateProfileInt("ExTeam", "PriceZen", 0, filename);
	this->PriceWcoin = GetPrivateProfileInt("ExTeam", "PriceWcoin", 0, filename);
	this->HourCredit = GetPrivateProfileInt("ExTeam", "HourCredit", 0, filename);
	this->bOnlyLorenMarket = GetPrivateProfileInt("ExTeam", "OnlyLorenMarket", 0, filename);
	this->m_StandartPlayerTime = GetPrivateProfileInt("ExTeam", "StandartPlayerTime", 12, filename);
	this->m_OtherPlayerMaxTime = GetPrivateProfileInt("ExTeam", "OtherPlayerMaxTime", 24, filename);
	this->m_PremiumPlayerMaxTime = GetPrivateProfileInt("ExTeam", "PremiumPlayerMaxTime", 72, filename);

	this->m_BlockMap.clear();

	if( g_ExLicense.CheckUser(eExUB::Local)		 || 
		g_ExLicense.CheckUser(eExUB::SILVER1)	 || 
		g_ExLicense.CheckUser(eExUB::SILVER2) )
	{

		FILE * file = fopen(filename,"r");

		if(file == NULL)
		{
			MessageBoxA(0,filename,"LOAD FILE ERROR",0);
		}

		char Buff[256];
		int Flag = 0;

		while(!feof(file))
		{
			fgets(Buff,256,file);
			if(Ex_IsBadFileLine(Buff, Flag))
				continue;

			if( g_ExLicense.CheckUser(eExUB::Local)		 || 
				g_ExLicense.CheckUser(eExUB::SILVER1)	 || 
				g_ExLicense.CheckUser(eExUB::SILVER2) )
			{
				if(Flag == 1)
				{
					int n;
					sscanf(Buff, "%d", &n);
					OFFMODE_BLOCK_MAP List;			
					List.MapNumber = n;
					this->m_BlockMap.push_back(List);
				}
			}
		}

		fclose(file);
	}
}

void OfflineMode::Start(CG_OFFMODE_RESULT* aRecv, int UserIndex)
{
	if(!g_ExLicense.user.OfflineMode)
	{
		g_ExLicense.user.OfflineMode = true;
	}

	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}
	
	LPOBJ lpUser = &gObj[UserIndex];

	if(lpUser->MapNumber == MAP_INDEX_CASTLESIEGE)
	{
		MsgNormal(UserIndex,g_ExText.GetText(42));
		return;
	}

	if(!this->CheckBlockMap(lpUser->MapNumber))
	{
		MsgNormal(UserIndex,"[OfflineMode] work only special maps");
		return;
	}

	if(/*g_ExUser.InSafeZone(UserIndex) && */lpUser->m_bPShopOpen == true)
	{
		char szBuff[256] = { 0 };
		if(this->bOnlyLorenMarket && lpUser->MapNumber != 79)
		{
			MsgNormal(UserIndex,g_ExText.GetText(43));
			return;
		}
		else
		{
			sprintf_s(szBuff,g_ExText.GetText(44),lpUser->Name);
			AllSendServerMsg(szBuff);
		}
	}

	lpUser->m_OfflineSkill = aRecv->Result;
	lpUser->m_OfflineAutoBuff = aRecv->BuffResult;
#if(ADD_OFFMODE_PICKUP==TRUE)
	lpUser->m_OfflinePickZen = aRecv->bPickZen;
	lpUser->m_OfflinePickJewel = aRecv->bPickJewel;
	lpUser->m_OfflinePickExel = aRecv->bPickExel;
	lpUser->m_OfflinePickAnc = aRecv->bPickAnc;
#endif

	#if(ADD_OFFMODE_TIMER)
	lpUser->m_OfflineTimerMax = aRecv->TimerMax;
	#endif
	
	/*
	if(lpUser->PremiumType <= 0 || lpUser->PremiumTime <= 0)
	{
		if(!g_ExUser.InSafeZone(UserIndex))
		{
			if(this->StartBonusPay > lpUser->Bonus)
			{
				lpUser->m_OfflineMode = false;
				return;
			}
			lpUser->Bonus -= this->StartBonusPay;
		}
	}
	*/
#if(_RECONNECT_==TRUE)
	g_ConnectEx.SendClose(UserIndex, TRUE);
#else
	CloseClient(UserIndex);
	lpObj->m_OfflineMode = true;
#endif
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Attack(int UserIndex)
{
	if(!g_ExLicense.user.OfflineMode)
	{
		return;
	}

	if ( OBJMAX_RANGE(UserIndex) == FALSE )
	{
		return;
	}

	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	if(lpUser->m_OfflineMode == false) 
	{
		return;
	}

	if(g_ExUser.InSafeZone(UserIndex) == true)
	{
		return;
	}

	if(!lpUser->m_OfflineSkill && !lpUser->m_OfflineAutoBuff)
	{
		return;
	}

	/*
	if(lpUser->PremiumType <= 0 || lpUser->PremiumTime <= 0)
	{
		lpUser->m_OfflineAttackTime++;
		if(lpUser->m_OfflineAttackTime >= (3600*2))
		{
			if(this->HourZenPay > lpUser->Money)
			{
				lpUser->m_OfflineMode = false;
				return;
			}
			lpUser->Money -= this->HourZenPay;
			lpUser->m_OfflineAttackTime = 0;
		}
	}
	*/

	bool AttackFree = false;

	if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
	{
		if(lpUser->PremiumTimeType == g_PremiumSystemEx.m_iOfflineModeAttackFreePremiumRang && lpUser->PremiumTime > 0)
		{
			AttackFree = true;
		}		
	}

	if(AttackFree == false)
	{
		if(this->PriceZen > lpUser->Money || this->PriceWcoin > lpUser->GameShop.WCoinC)
		{
			return;
		}

		if(lpUser->m_OfflineAttackTime == 0)
		{
			if(this->PriceZen > 0)
			{
				if(this->PriceZen > lpUser->Money)
				{
					lpUser->m_OfflineMode = false;
					return;
				}
				lpUser->Money -= this->PriceZen;
			}

			if(this->PriceWcoin > 0)
			{
				if(this->PriceWcoin > lpUser->GameShop.WCoinC)
				{
					lpUser->m_OfflineMode = false;
					return;
				}
				lpUser->GameShop.WCoinC -= this->PriceWcoin;
				gGameShop.GDSaveUserInfo(UserIndex);
			}

			if(this->HourCredit > 0)
			{
				if(this->HourCredit > lpUser->ExCred)
				{
					lpUser->m_OfflineMode = false;
					return;
				}
				lpUser->ExCred -= this->HourCredit;
			}
		}
	}

	lpUser->m_OfflineAttackTime++;
	if(lpUser->m_OfflineAttackTime >= (3600*2))
	{
		#if(ADD_OFFMODE_TIMER)
		if(g_ExLicense.CheckUser(eExUB::eternalmu))
		{
			lpUser->m_OfflineTimerUser++;
			if(lpUser->m_OfflineTimerUser >= lpUser->m_OfflineTimerMax)
			{
			
				lpUser->m_OfflineMode = false;
			}
		}
		#endif
		lpUser->m_OfflineAttackTime = 0;
	}

	switch(lpUser->Class)
	{
		case 0:	this->DarkWizard(UserIndex);		break;
		case 1:	this->DarkKnight(UserIndex);		break;
		case 2:	this->FairyElf(UserIndex);			break;
		case 3:	this->MagicGladiator(UserIndex);	break;
		case 4:	this->DarkLord(UserIndex);			break;
		case 5:	this->Summoner(UserIndex);			break;
		case 6: this->Fighter(UserIndex);			break;
	}

#if(ADD_OFFMODE_PICKUP==TRUE)

	bool PremiumResult = true;

	//if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2) || g_ExLicense.CheckUser(eExUB::MedoniAndrei))
	//{
	//	if(lpUser->PremiumTimeType == g_PremiumSystemEx.m_iOfflineModePickUpPremiumRang && lpUser->PremiumTime > 0)
	//	{
	//		PremiumResult = true;
	//	}		
	//}
	//else
	//{
	//	if(lpUser->PremiumTime > 0)
	//	{
	//		PremiumResult = true;
	//	}
	//}

	//if(lpUser->PremiumTime > 0 /*&& lpUser->PremiumTime > 0*/)
	if(PremiumResult)
	{
		this->PickUP(UserIndex);
	}
#endif
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::DarkWizard(int UserIndex)
{
	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	CMagicInf *lpMagic;

	//Buff Mana shield
	if(lpUser->m_OfflineAutoBuff == true && lpUser->m_OfflineBuffTime == 0)
	{
		int partynum = -1;
		int partycount;
		int number;

		LPOBJ lpPartyObj;

		partynum = lpUser->PartyNumber;

		if(partynum != -1)
		{
			partycount = gParty.m_PartyS[partynum].Count;

			for(int j = 0; j < MAX_USER_IN_PARTY; j++)
			{
				number = gParty.m_PartyS[partynum].Number[j];

				if ( OBJMAX_RANGE(number) == TRUE )
				{
					lpPartyObj = &gObj[number];

					if(lpUser->MapNumber == lpPartyObj->MapNumber)
					{
						if(gObjCalDistance(lpUser, lpPartyObj) < 6)
						{
							//MS
							lpMagic = gObjGetMagicSearch( lpUser, 16);
							if(lpMagic != NULL) 
							{		
								gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							else
							{	
								lpMagic = gObjGetMagicSearch(lpUser, 403);
								if(lpMagic != NULL) 
								{		
									gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			//MS
			lpMagic = gObjGetMagicSearch(lpUser, 16);
			if(lpMagic != NULL) 
			{		
				gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
			else
			{	
				lpMagic = gObjGetMagicSearch(lpUser, 403);
				if(lpMagic != NULL) 
				{		
					gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
				}
			}
		}

		// Wizard Buff Damage
		lpMagic = gObjGetMagicSearch(lpUser, 233);
		if(lpMagic != NULL) 
		{		
			gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
		}
		else
		{
			lpMagic = gObjGetMagicSearch(lpUser, 380);
			if(lpMagic != NULL) 
			{		
				gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
		}
	}

	lpUser->m_OfflineBuffTime++;
	if(lpUser->m_OfflineBuffTime >= OFFMAXTIME_FOR_BUFF)
	{
		lpUser->m_OfflineBuffTime = 0;
	}

	lpMagic = gObjGetMagicSearch(lpUser, lpUser->m_OfflineSkill);

	if(!lpMagic)
	{
		return;
	}

	int tObjNum;
	int MaxDis = 0;

	if(lpUser->m_OfflineSkill == 9)
	{
		MaxDis = 6;
	}
	else
	{
		MaxDis = 3;
	}

	// Evil Spirit or Inferno
	if(lpUser->m_OfflineSkill == 9		|| 
		lpUser->m_OfflineSkill == 385	|| 
		lpUser->m_OfflineSkill == 14	||
		lpUser->m_OfflineSkill == 381)
	{
		gObjUseSkill.UseSkill(UserIndex, lpMagic, lpUser->X, lpUser->Y, 0, 0, -1);

		for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
		{
			tObjNum = lpUser->VpPlayer2[n].number;

			if(lpUser->VpPlayer2[n].state == 0)
			{
				continue;
			}
			if (OBJMAX_RANGE(tObjNum) == FALSE)
			{
				continue;
			}
			if ( gObj[tObjNum].Type != OBJ_MONSTER )
			{
				continue;
			}
			if(g_ExUser.InSafeZone(tObjNum) == true)
			{
				continue;
			}
			if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
			{
				gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
			}
		}
	}
	// Ice Shtorm
	else if(lpUser->m_OfflineSkill == 39)
	{
		int TargetIndex = this->SearchTarget(UserIndex, MaxDis);

		if(TargetIndex == -1) 
		{
			return;
		}
		if ( TargetIndex < 0 || TargetIndex > OBJMAX-1)
		{
			return;
		}
		if ( gObj[TargetIndex].Connected < PLAYER_PLAYING )
		{
			return;
		}

		LPOBJ lpMonster = &gObj[TargetIndex];

		gObjUseSkill.UseSkill(UserIndex, lpMagic, lpMonster->X, lpMonster->Y, 0, 0, TargetIndex);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::DarkKnight(int UserIndex)
{
	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	CMagicInf *lpMagic;

	// HP Buff
	if(lpUser->m_OfflineAutoBuff == true && lpUser->m_OfflineBuffTime == 0)
	{
		lpMagic = gObjGetMagicSearch( lpUser, 48);
		if(lpMagic != NULL) 
		{		
			gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
		}
		else
		{
			lpMagic = gObjGetMagicSearch(lpUser, 356);
			if(lpMagic != NULL) 
			{		
				gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}			
		}
	}

	lpUser->m_OfflineBuffTime++;
	if(lpUser->m_OfflineBuffTime >= OFFMAXTIME_FOR_BUFF)
	{
		lpUser->m_OfflineBuffTime = 0;
	}

	lpMagic = gObjGetMagicSearch(lpUser, lpUser->m_OfflineSkill);

	if(!lpMagic)
	{
		return;
	}

	int tObjNum;
	int MaxDis = 0;

	if(lpUser->m_OfflineSkill == 41 || lpUser->m_OfflineSkill == 330 || lpUser->m_OfflineSkill == 332 || lpUser->m_OfflineSkill == 481)
	{
		MaxDis = 2;
	}
	else if(lpUser->m_OfflineSkill == 42 || lpUser->m_OfflineSkill == 331 || lpUser->m_OfflineSkill == 333)
	{
		MaxDis = 3;
	}
	else if(lpUser->m_OfflineSkill == 232 || lpUser->m_OfflineSkill == 337 || lpUser->m_OfflineSkill == 340 || lpUser->m_OfflineSkill == 343)
	{
		MaxDis = 5;
	}

	// Twisting Slash
	if( lpUser->m_OfflineSkill == 41  || 
		lpUser->m_OfflineSkill == 330 ||
		lpUser->m_OfflineSkill == 332 ||
		lpUser->m_OfflineSkill == 481 )	//42 - урезать скорость в 2-3 раза
	{
		if(this->OffTimer(UserIndex, 3) == true)	//3
		{
			gObjUseSkill.UseSkill(UserIndex, lpMagic,lpUser->X, lpUser->Y,0,0,-1);

			for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
			{
				tObjNum = lpUser->VpPlayer2[n].number;

				if(lpUser->VpPlayer2[n].state == 0)
				{
					continue;
				}
				if (OBJMAX_RANGE(tObjNum) == FALSE)
				{
					continue;
				}
				if ( gObj[tObjNum].Type != OBJ_MONSTER )
				{
					continue;
				}
				if(g_ExUser.InSafeZone(tObjNum) == true)
				{
					continue;
				}
				if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
				{
					gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
				}
			}
		}
	}
	// Rageful Blow
	else if( lpUser->m_OfflineSkill == 42  ||
		lpUser->m_OfflineSkill == 331 ||
		lpUser->m_OfflineSkill == 333 )	//42 - урезать скорость в 2-3 раза
	{
		if(this->OffTimer(UserIndex, 4) == true)
		{
			gObjUseSkill.UseSkill(UserIndex, lpMagic,lpUser->X, lpUser->Y,0,0,-1);

			for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
			{
				tObjNum = lpUser->VpPlayer2[n].number;

				if(lpUser->VpPlayer2[n].state == 0)
				{
					continue;
				}
				if (OBJMAX_RANGE(tObjNum) == FALSE)
				{
					continue;
				}
				if ( gObj[tObjNum].Type != OBJ_MONSTER )
				{
					continue;
				}
				if(g_ExUser.InSafeZone(tObjNum) == true)
				{
					continue;
				}
				if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
				{
					gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
				}
			}
		}
	}
	// BK top skill
	else if(lpUser->m_OfflineSkill == 232 ||
			lpUser->m_OfflineSkill == 337 ||
			lpUser->m_OfflineSkill == 340 ||
			lpUser->m_OfflineSkill == 343 &&
			this->OffTimer(UserIndex, 4) == true)	//232 - урезать скорость в 3-4 раза
	{
		int TargetIndex = this->SearchTarget(UserIndex, MaxDis);

		if(TargetIndex == -1) 
		{
			return;
		}
		if (TargetIndex < 0 || TargetIndex > OBJMAX-1)
		{
			return;
		}
		if (gObj[TargetIndex].Connected < PLAYER_PLAYING)
		{
			return;
		}

		LPOBJ lpMonster = &gObj[TargetIndex];

		gObjUseSkill.UseSkill(UserIndex, lpMagic, lpMonster->X, lpMonster->Y, 0, 0, TargetIndex);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::FairyElf(int UserIndex)
{
	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	CMagicInf *lpMagic;

	//Buff
	if(lpUser->m_OfflineAutoBuff == true && lpUser->m_OfflineBuffTime == 0)
	{
		int partynum = -1;
		int partycount;
		int number = -1;

		LPOBJ lpPartyObj;

		partynum = lpUser->PartyNumber;

		if(partynum != -1)
		{
			partycount = gParty.m_PartyS[partynum].Count;

			for(int j = 0; j < MAX_USER_IN_PARTY; j++)
			{
				number = gParty.m_PartyS[partynum].Number[j];

				if ( OBJMAX_RANGE(number) == TRUE )
				{
					lpPartyObj = &gObj[number];

					if(lpUser->MapNumber == lpPartyObj->MapNumber)
					{
						if(gObjCalDistance(lpUser, lpPartyObj) < 6)
						{
							//Defence Baf
							lpMagic = gObjGetMagicSearch(lpUser, 27);
							if(lpMagic != NULL) 
							{		
								gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							else
							{
								lpMagic = gObjGetMagicSearch(lpUser, 417);
								if(lpMagic != NULL) 
								{		
									gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
								}
							}
							//Damage Baf
							lpMagic = gObjGetMagicSearch(lpUser, 28);
							if(lpMagic != NULL) 
							{		
								gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							else
							{
								lpMagic = gObjGetMagicSearch(lpUser, 420);
								if(lpMagic != NULL) 
								{		
									gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
								}
							}
							//Heal Baf
							lpMagic = gObjGetMagicSearch(lpUser, 26);
							if(lpMagic != NULL) 
							{		
								gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							else
							{
								lpMagic = gObjGetMagicSearch(lpUser, 413);
								if(lpMagic != NULL) 
								{		
									gObjUseSkill.UseSkill(lpUser->m_Index, lpPartyObj->m_Index, lpMagic);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			//Defence Baf
			lpMagic = gObjGetMagicSearch(lpUser, 27);
			if(lpMagic != NULL) 
			{		
				gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
			else
			{
				lpMagic = gObjGetMagicSearch(lpUser, 417);
				if(lpMagic != NULL) 
				{		
					gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
				}
			}
			//Damage Baf
			lpMagic = gObjGetMagicSearch(lpUser, 28);
			if(lpMagic != NULL) 
			{		
				gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
			else
			{
				lpMagic = gObjGetMagicSearch(lpUser, 420);
				if(lpMagic != NULL) 
				{		
					gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
				}
			}
			//Heal Baf
			lpMagic = gObjGetMagicSearch(lpUser, 26);
			if(lpMagic != NULL) 
			{		
				gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
			else
			{
				lpMagic = gObjGetMagicSearch(lpUser, 413);
				if(lpMagic != NULL) 
				{		
					gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
				}
			}
		}
	}

	lpUser->m_OfflineBuffTime++;
	if(lpUser->m_OfflineBuffTime >= OFFMAXTIME_FOR_BUFF)
	{
		lpUser->m_OfflineBuffTime = 0;
	}

	lpMagic = gObjGetMagicSearch(lpUser, lpUser->m_OfflineSkill);

	if(!lpMagic)
	{
		return;
	}

	int tObjNum;
	int MaxDis = 0;
	int AttackCount = 0;
	int MaxCount = 7;
	int TargetIndex = -1;

	if(lpUser->m_OfflineSkill == 24 || lpUser->m_OfflineSkill == 414 || lpUser->m_OfflineSkill == 418)
	{
		MaxDis = 6;
	}
	else if(lpUser->m_OfflineSkill == 235)
	{
		MaxDis = 6;
	}
	else if(lpUser->m_OfflineSkill == 51 || lpUser->m_OfflineSkill == 424)
	{
		MaxDis = 8;
	}

	// Multi Shot
	if( lpUser->m_OfflineSkill == 235)
	{
		for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
		{
			tObjNum = lpUser->VpPlayer2[n].number;

			if(lpUser->VpPlayer2[n].state == 0)
			{
				continue;
			}
			if (OBJMAX_RANGE(tObjNum) == FALSE)
			{
				continue;
			}
			if ( gObj[tObjNum].Type != OBJ_MONSTER )
			{
				continue;
			}
			if(g_ExUser.InSafeZone(tObjNum) == true)
			{
				continue;
			}
			if(AttackCount >= MaxCount)
			{
				continue;
			}

			if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
			{
				TargetIndex = tObjNum;
				gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
				AttackCount++;
			}
		}
		gObjUseSkill.UseSkill(UserIndex, lpMagic,lpUser->X, lpUser->Y,0,0,-1);
	}
	// Triple Shot
	else if(lpUser->m_OfflineSkill == 24	|| 
			lpUser->m_OfflineSkill == 51	||
			lpUser->m_OfflineSkill == 414	|| 
			lpUser->m_OfflineSkill == 418	||
			lpUser->m_OfflineSkill == 424)
	{
		TargetIndex = this->SearchTarget(UserIndex, MaxDis);

		if(TargetIndex == -1) 
		{
			return;
		}
		if(TargetIndex < 0 || TargetIndex > OBJMAX-1)
		{
			return;
		}
		if(gObj[TargetIndex].Connected < PLAYER_PLAYING)
		{
			return;
		}

		LPOBJ lpMonster = &gObj[TargetIndex];

		gObjUseSkill.UseSkill(lpUser->m_Index,TargetIndex,lpMagic);
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::MagicGladiator(int UserIndex)
{
	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	CMagicInf *lpMagic;

	// Ignore Buff
	/*if(lpUser->m_OfflineAutoBuff == true && lpUser->m_OfflineBuffTime == 0)
	{
		lpMagic = gObjGetMagicSearch(lpUser, 266);
		if(lpMagic != NULL) 
		{		
			gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
		}
	}*/

	lpUser->m_OfflineBuffTime++;
	if(lpUser->m_OfflineBuffTime >= OFFMAXTIME_FOR_BUFF)
	{
		lpUser->m_OfflineBuffTime = 0;
	}

	lpMagic = gObjGetMagicSearch(lpUser, lpUser->m_OfflineSkill);

	if(!lpMagic)
	{
		return;
	}

	int tObjNum;
	int MaxDis = 0;

	if(lpUser->m_OfflineSkill == 9 || lpUser->m_OfflineSkill == 237 || lpUser->m_OfflineSkill == 487)
	{
		MaxDis = 6;
	}
	else if(lpUser->m_OfflineSkill == 41 || lpUser->m_OfflineSkill == 330 || lpUser->m_OfflineSkill == 332 || lpUser->m_OfflineSkill == 481)
	{
		MaxDis = 2;
	}
	else if(lpUser->m_OfflineSkill == 56 || lpUser->m_OfflineSkill == 482)
	{
		MaxDis = 5;
	}

	// Evil Spirit or Inferno
	if(lpUser->m_OfflineSkill == 9 || lpUser->m_OfflineSkill == 41 || lpUser->m_OfflineSkill == 56 || lpUser->m_OfflineSkill == 237 || lpUser->m_OfflineSkill == 487)
	{
		gObjUseSkill.UseSkill(UserIndex, lpMagic, lpUser->X, lpUser->Y, 0, 0, -1);

		for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
		{
			tObjNum = lpUser->VpPlayer2[n].number;

			if(lpUser->VpPlayer2[n].state == 0)
			{
				continue;
			}
			if (OBJMAX_RANGE(tObjNum) == FALSE)
			{
				continue;
			}
			if ( gObj[tObjNum].Type != OBJ_MONSTER )
			{
				continue;
			}
			if(g_ExUser.InSafeZone(tObjNum) == true)
			{
				continue;
			}
			if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
			{
				gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
			}
		}
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::DarkLord(int UserIndex)
{
	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	CMagicInf * lpMagic;
	int MaxDis = 0;

	if(lpUser->m_OfflineSkill == 61 || lpUser->m_OfflineSkill == 78)
	{
		MaxDis = 6;
	}
	else if(lpUser->m_OfflineSkill == 238)
	{
		MaxDis = 4;
	}

	// Critical Buff
	if(lpUser->m_OfflineAutoBuff == true && lpUser->m_OfflineBuffTime == 0)
	{
		lpMagic = gObjGetMagicSearch(lpUser, 64);
		if(lpMagic != NULL) 
		{		
			gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
		}
		else
		{
			lpMagic = gObjGetMagicSearch(lpUser, 511);
			if(lpMagic != NULL) 
			{		
				gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
		}
	}

	lpUser->m_OfflineBuffTime++;
	if(lpUser->m_OfflineBuffTime >= OFFMAXTIME_FOR_BUFF)
	{
		lpUser->m_OfflineBuffTime = 0;
	}

	lpMagic = gObjGetMagicSearch(lpUser, lpUser->m_OfflineSkill);

	if(!lpMagic)
	{
		return;
	}

	if( lpUser->m_OfflineSkill == 61 || 
		lpUser->m_OfflineSkill == 508 || 
		lpUser->m_OfflineSkill == 514 || 
		lpUser->m_OfflineSkill == 238)
	{
		int TargetIndex = this->SearchTarget(UserIndex, 6);

		if(TargetIndex == -1) 
		{
			return;
		}
		if ( TargetIndex < 0 || TargetIndex > OBJMAX-1)
		{
			return;
		}
		if ( gObj[TargetIndex].Connected < PLAYER_PLAYING )
		{
			return;
		}

		gObjUseSkill.UseSkill(lpUser->m_Index, TargetIndex, lpMagic);
	}
	else if(lpUser->m_OfflineSkill == 78 || lpUser->m_OfflineSkill == 518)
	{
		gObjUseSkill.UseSkill(UserIndex, lpMagic, lpUser->X, lpUser->Y, 0, 0, -1);

		for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
		{
			int tObjNum = lpUser->VpPlayer2[n].number;

			if(lpUser->VpPlayer2[n].state == 0)
			{
				continue;
			}
			if (OBJMAX_RANGE(tObjNum) == FALSE)
			{
				continue;
			}
			if ( gObj[tObjNum].Type != OBJ_MONSTER )
			{
				continue;
			}
			if(g_ExUser.InSafeZone(tObjNum) == true)
			{
				continue;
			}
			if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
			{
				gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
			}
		}
	}

}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Summoner(int UserIndex)
{
	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	CMagicInf * lpMagic;

	int MaxDis = 6;

	// Bersaker Buff
	if(lpUser->m_OfflineAutoBuff == true && lpUser->m_OfflineBuffTime == 0)
	{
		lpMagic = gObjGetMagicSearch(lpUser, 218);
		if(lpMagic != NULL) 
		{		
			gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
		}
		else
		{
			lpMagic = gObjGetMagicSearch(lpUser, 469);
			if(lpMagic != NULL) 
			{		
				gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
			}
		}
	}

	lpUser->m_OfflineBuffTime++;
	if(lpUser->m_OfflineBuffTime >= OFFMAXTIME_FOR_BUFF)
	{
		lpUser->m_OfflineBuffTime = 0;
	}

	lpMagic = gObjGetMagicSearch(lpUser, lpUser->m_OfflineSkill);

	if(!lpMagic)
	{
		return;
	}

	if(lpUser->m_OfflineSkill == 230 || lpUser->m_OfflineSkill == 456)
	{
		gObjUseSkill.UseSkill(lpUser->m_Index, lpMagic, lpUser->X, lpUser->Y,0,0,-1);

		for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
		{
			int tObjNum = lpUser->VpPlayer2[n].number;

			if(lpUser->VpPlayer2[n].state == 0)
			{
				continue;
			}
			if (OBJMAX_RANGE(tObjNum) == FALSE)
			{
				continue;
			}
			if ( gObj[tObjNum].Type != OBJ_MONSTER )
			{
				continue;
			}
			if(g_ExUser.InSafeZone(tObjNum) == true)
			{
				continue;
			}
			if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
			{
				gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
			}
		}
	}
	else if(lpUser->m_OfflineSkill == 215 || lpUser->m_OfflineSkill == 455)
	{
		int TargetIndex = this->SearchTarget(UserIndex, 6);

		if(TargetIndex == -1) 
		{
			return;
		}
		if ( TargetIndex < 0 || TargetIndex > OBJMAX-1)
		{
			return;
		}
		if ( gObj[TargetIndex].Connected < PLAYER_PLAYING )
		{
			return;
		}

		LPOBJ lpMonster = &gObj[TargetIndex];

		gObjUseSkill.UseSkill(UserIndex, lpMagic, lpMonster->X, lpMonster->Y, 0, 0, TargetIndex);
	}
	else if(lpUser->m_OfflineSkill == 225)	//225 должна быть задержка
	{
		if(this->OffTimer(UserIndex, 6) == true)
		{
			int TargetIndex = this->SearchTarget(UserIndex, 6);

			if(TargetIndex == -1) 
			{
				return;
			}
			if ( TargetIndex < 0 || TargetIndex > OBJMAX-1)
			{
				return;
			}
			if ( gObj[TargetIndex].Connected < PLAYER_PLAYING )
			{
				return;
			}

			LPOBJ lpMonster = &gObj[TargetIndex];

			gObjUseSkill.UseSkill(UserIndex, lpMagic, lpMonster->X, lpMonster->Y, 0, 0, TargetIndex);
		}
	}
}
// ----------------------------------------------------------------------------------------------

void OfflineMode::Fighter(int UserIndex)
{
	if(!gObjIsConnectedEx(UserIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	CMagicInf * lpMagic;

	int MaxDis = 6;

	if(lpUser->m_OfflineAutoBuff == true && lpUser->m_OfflineBuffTime == 0)
	{
		lpMagic = gObjGetMagicSearch(lpUser, 266);//fix
		if(lpMagic != NULL) 
		{		
			gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
		}

		lpMagic = gObjGetMagicSearch(lpUser, 267);//fix
		if(lpMagic != NULL) 
		{		
			gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
		}

		lpMagic = gObjGetMagicSearch(lpUser, 268);//fix
		if(lpMagic != NULL) 
		{		
			gObjUseSkill.UseSkill(lpUser->m_Index, lpUser->m_Index, lpMagic);
		}
	}

	lpUser->m_OfflineBuffTime++;
	if(lpUser->m_OfflineBuffTime >= OFFMAXTIME_FOR_BUFF)
	{
		lpUser->m_OfflineBuffTime = 0;
	}

	lpMagic = gObjGetMagicSearch(lpUser, lpUser->m_OfflineSkill);

	if(!lpMagic)
	{
		return;
	}

	if(lpUser->m_OfflineSkill == 264 || lpUser->m_OfflineSkill == 560)
	{
		if(this->OffTimer(UserIndex, 4) == true)
		{
			gObjUseSkill.UseSkill(lpUser->m_Index, lpMagic, lpUser->X, lpUser->Y,0,0,-1);

			for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
			{
				int tObjNum = lpUser->VpPlayer2[n].number;

				if(lpUser->VpPlayer2[n].state == 0)
				{
					continue;
				}
				if (OBJMAX_RANGE(tObjNum) == FALSE)
				{
					continue;
				}
				if ( gObj[tObjNum].Type != OBJ_MONSTER )
				{
					continue;
				}
				if(g_ExUser.InSafeZone(tObjNum) == true)
				{
					continue;
				}
				if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
				{
					gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
				}
			}
		}
	}
	else if(lpUser->m_OfflineSkill == 263 || lpUser->m_OfflineSkill == 559)
	{
		gObjUseSkill.UseSkill(lpUser->m_Index, lpMagic, lpUser->X, lpUser->Y,0,0,-1);

		for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
		{
			int tObjNum = lpUser->VpPlayer2[n].number;

			if(lpUser->VpPlayer2[n].state == 0)
			{
				continue;
			}
			if (OBJMAX_RANGE(tObjNum) == FALSE)
			{
				continue;
			}
			if ( gObj[tObjNum].Type != OBJ_MONSTER )
			{
				continue;
			}
			if(g_ExUser.InSafeZone(tObjNum) == true)
			{
				continue;
			}
			if(MaxDis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
			{
				gObjAttack(lpUser, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0, 0);
			}
		}
	}
}
// ----------------------------------------------------------------------------------------------

int OfflineMode::SearchTarget(int UserIndex, int maxdis)
{
	if(!gObjIsConnectedEx(UserIndex))
	{
		return -1;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	int searchtarget = -1;
	int TargetIndex[MAX_VIEWPORT_MONSTER];
	int TargetCount = 0;
	int IndexNumber;

	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		int tObjNum = lpUser->VpPlayer2[n].number;

		if(lpUser->VpPlayer2[n].state == 0)
		{
			continue;
		}
		if (OBJMAX_RANGE(tObjNum) == FALSE)
		{
			continue;
		}
		if ( gObj[tObjNum].Type != OBJ_MONSTER )
		{
			continue;
		}
		if(g_ExUser.InSafeZone(tObjNum) == true)
		{
			continue;
		}
		if(maxdis >= gObjCalDistance(lpUser, &gObj[tObjNum]))
		{
			TargetIndex[TargetCount] = tObjNum;
			TargetCount++;
		}
	}

	if(TargetCount <= 0)
	{
		return -1;
	}
	
	IndexNumber = rand()%TargetCount;

	searchtarget = TargetIndex[IndexNumber];

	return searchtarget;
}
// ----------------------------------------------------------------------------------------------

bool OfflineMode::OffTimer(int UserIndex, int DivTime)
{
	if ( OBJMAX_RANGE(UserIndex) == FALSE )
	{
		return false;
	}

	if(!gObjIsConnectedEx(UserIndex))
	{
		return false;
	}
	
	LPOBJ lpUser = &gObj[UserIndex];

	for(int i = 0; i < OFFMAXTIME_FOR_BUFF; i++)
	{
		int res = DivTime * i;
		if(res == lpUser->m_OfflineBuffTime)
		{
			return true;
		}
	}

	return false;
}
// ----------------------------------------------------------------------------------------------

#if(ADD_OFFMODE_PICKUP==TRUE)
void OfflineMode::PickUP(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}
	int distance = 3;
	CMapItem * lpMapItem;
	LPOBJ lpUser = &gObj[aIndex];
	int map_num = gObj[aIndex].MapNumber;

	if(gObj[aIndex].DieRegen != 0)
	{
		return;
	}

	if (MAX_MAP_RANGE(map_num) == FALSE)
	{
		LogAdd("error-L3 : %s %d", __FILE__, __LINE__);
		return;
	}

	for(int item_num = 0; item_num < MAX_MAPITEM; item_num++)
	{
		lpMapItem = &MapC[map_num].m_cItem[item_num];

		if(lpMapItem->IsItem() == TRUE && lpMapItem->Give == false && lpMapItem->live == true)
		{
			int tx = lpUser->X - lpMapItem->px;
			int ty = lpUser->Y - lpMapItem->py;
					
			int dis = sqrt((float) (tx*tx+ty*ty));	//разобратся как работает

			if(dis > distance)
			{
				continue;
			}

			//all items
			if(lpMapItem->m_QuestItem != false )
			{
				if(!g_QuestInfo.CountQuestItemInInventory(aIndex, lpMapItem->m_Type, lpMapItem->m_Level))
				{
					continue;
				}
			}

			bool PickItem = false;

			//zen item
			if(lpMapItem->m_Type == ITEMGET(14,15))
			{
				if(lpUser->m_OfflinePickZen == true)
				{
					if(MapC[map_num].ItemGive(aIndex, item_num, false) == TRUE)
					{
						if(!gObjCheckMaxZen(aIndex, lpMapItem->m_BuyMoney))
						{
							if(lpUser->Money < MAX_ZEN)
							{
								lpUser->Money = MAX_ZEN;
								continue;
							}
						}
						else
						{
							lpUser->Money += lpMapItem->m_BuyMoney;
						}
					}
					continue;
				}
			}
			//Exellent
			if(lpMapItem->m_NewOption > 0)
			{
				if(lpUser->m_OfflinePickExel == true)
				{
					PickItem = true;
				}
			}
			//Ancent
			if(lpMapItem->m_SetOption > 0)
			{
				if(lpUser->m_OfflinePickAnc == true)
				{
					PickItem = true;
				}
			}
			//Jewels
			if(lpMapItem->m_Type == ITEMGET(12, 15) ||
			   lpMapItem->m_Type == ITEMGET(14, 13) ||
			   lpMapItem->m_Type == ITEMGET(14, 14) ||
			   lpMapItem->m_Type == ITEMGET(14, 16) ||
			   lpMapItem->m_Type == ITEMGET(14, 22) ||
			   lpMapItem->m_Type == ITEMGET(14, 31) ||
			   lpMapItem->m_Type == ITEMGET(14, 42))
			{
				if(lpUser->m_OfflinePickJewel == true)
				{
					PickItem =  true;
				}
			}
			//PickUP
			if(PickItem == false)
			{
				continue;
			}

			BYTE result = ::gObjInventoryInsertItemTemp(&gObj[aIndex], lpMapItem);
			if (result != 0xFF)
			{
				if(MapC[map_num].ItemGive(aIndex, item_num, false) == TRUE)
				{
					BYTE pos = ::gObjInventoryInsertItem(aIndex, lpMapItem);
					if(pos != 0xFF)
					{
						::GCSendGetItemInfoForParty(aIndex, lpMapItem);
					}
				}
			}
		}			
	}
}
#endif
// ----------------------------------------------------------------------------------------------

void OfflineMode::GCConfig(int aIndex)
{
	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	/*if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}*/

	GC_OFFMODE_CONFIG pSend;
	pSend.h.set((LPBYTE)&pSend, 0xFB, 0x30, sizeof(pSend));
	pSend.PriceZen = this->PriceZen;
	pSend.PriceWcoin = this->PriceWcoin;
	pSend.iHourCredit = this->HourCredit;

	#if(ADD_OFFMODE_TIMER)
	pSend.StandartPlayerTime = this->m_StandartPlayerTime;
	pSend.OtherPlayerMaxTime = this->m_OtherPlayerMaxTime;
	pSend.PremiumPlayerMaxTime = this->m_PremiumPlayerMaxTime;
	#endif

	DataSend(lpUser->m_Index, (LPBYTE)&pSend, pSend.h.size);
}
// ----------------------------------------------------------------------------------------------

#if(OFFLINE_MODE_RESTORE)
short OfflineMode::AddIndexPlayer()
{
	#if(ENABLE_OPTIMIZATION)
	return g_Optimization.AddObjectOffmoder();
	#endif

	if(gDisconnect == 1)
	{
		return -1;
	}

	if(gObjTotalUser >= gServerMaxUser)
	{
		return -1;
	}

	int totalcount = 0;
	int count = gObjCount;
	
	while(true)
	{
		if(gObj[count].Connected == PLAYER_EMPTY)
		{
			return count;
			break;
		}

		count++;

		if(count >= OBJMAX)
		{
			count = OBJ_STARTUSERINDEX;
		}

		totalcount++;

		if(totalcount >= OBJMAXUSER)
		{
			break;
		}
	}

	return -1;
}

void OfflineMode::GDReqAllPlayer()
{
	if(g_WaitOpen == true)
	{
		return;
	}

	if(this->m_bLoadedDB == true)
	{
		return;
	}

	this->m_bLoadedDB = true;

	PBMSG_HEAD2 pMsg;
	pMsg.set((LPBYTE)&pMsg, 0xEB, 0x11, sizeof(pMsg));
	cDBSMng.Send((char*)&pMsg, pMsg.size);
}

void OfflineMode::DGAnsAccauntPassword(PMSG_DGANS_OFFMODE_START* Data)
{
	short aIndex = this->AddIndexPlayer();

	if(aIndex == -1)
	{
		return;
	}

	//if(!gObjIsAccontConnect(aIndex, gObj[aIndex].AccountID))
	//{
	//	return;
	//}

	if(gObj[aIndex].Connected == PLAYER_PLAYING)
	{
		return;
	}

	if(gObjAdd(INVALID_SOCKET, "127.0.0.1", aIndex) == -1)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	char id[11] = { 0 };
	memcpy(id, Data->AccountID, sizeof(Data->AccountID));
	memcpy(gObj[aIndex].AccountID, id, sizeof(Data->AccountID));
	memcpy(gObj[aIndex].Name, Data->Name, sizeof(Data->Name));

	//#if(CUSTOM_PASSWORD==TRUE)
	char psw[21] = { 0 };
	memcpy(psw, Data->Password, sizeof(Data->Password));
	memcpy(gObj[aIndex].Pass, psw, sizeof(psw));
	gObj[aIndex].Pass[10] = 0;
	//#endif

	for(int i = OBJ_MAXMONSTER; i < OBJMAX; i++)
	{
		LPOBJ sObj = &gObj[i];

		if(sObj->Connected != PLAYER_PLAYING)
		{
			continue;
		}
		
		if(id[0] == sObj->AccountID[0] && psw[0] == sObj->Pass[0])
		{
			if(!strncmp(id, sObj->AccountID, 10) && !strncmp(psw, sObj->Pass, 10))
			{
				if(sObj->m_OfflineMode == false)
				{
					#if(OFFLINE_MODE_RESTORE)
					g_OfflineMode.GDReqUpdateStatus(i);
					#endif
				}
				gObjDel(aIndex);
				return;
			}
		}
	}

	LPOBJ lpObj = &gObj[aIndex];

	BuxConvert(Data->AccountID, MAX_ACCOUNT_LEN);
	BuxConvert(Data->Password, MAX_ACCOUNT_LEN);

	GJPUserClose(id);

	if(gObj[aIndex].Connected != PLAYER_CONNECTED)
	{
		LogAdd(lMsg.Get(MSGGET(1, 218)), aIndex, id);
		CloseClient(aIndex);
		return;
	}

	if(gObj[aIndex].LoginMsgSnd != FALSE)
	{
		if(gObj[aIndex].LoginMsgSnd == TRUE)
		{
			LogAdd(lMsg.Get(MSGGET(1, 219)), aIndex, id, gObj[aIndex].Ip_addr );
		}
		else
		{
			LogAdd("error : %d %s %d", gObj[aIndex].LoginMsgSnd, __FILE__, __LINE__);
		}
		return;
	}

	if(lpObj->Connected >= PLAYER_LOGGED)
	{
		return;
	}

	SDHP_IDPASS spMsg;

	PHeadSetB((LPBYTE)&spMsg, 0x01, sizeof(spMsg));
	spMsg.Number = aIndex;
	memcpy(spMsg.Id, Data->AccountID, sizeof(spMsg.Id));
	memcpy(spMsg.Pass, Data->Password, sizeof(spMsg.Pass));
	strcpy(spMsg.IpAddress, gObj[aIndex].Ip_addr);
	gObj[aIndex].CheckTick = Data->TickCount;
	gObj[aIndex].CheckTick2 = GetTickCount();
	gObj[aIndex].ConnectCheckTime = GetTickCount();
	gObj[aIndex].CheckSpeedHack = true;
	gObj[aIndex].LoginMsgSnd = 1;
	gObj[aIndex].LoginMsgCount = 1;
	gObj[aIndex].m_cAccountItemBlock = 0;
	gObj[aIndex].m_ReOfflineMode = true;
	gObj[aIndex].ukn_30 = 0;

	wsJServerCli.DataSend((char*)&spMsg, spMsg.h.size);
	LogAddTD("join send : (%d)%s", aIndex, gObj[aIndex].AccountID);
	
	lpObj->m_bMapSvrMoveReq = false;
	lpObj->m_sPrevMapSvrCode = -1; 
	lpObj->m_sDestMapNumber = -1;
	lpObj->m_btDestX = 0;
	lpObj->m_btDestY = 0;
}

void OfflineMode::GDReqOffCharacter(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->m_ReOfflineMode = false;

	PMSG_GDREQ_OFFMODE_CHAR pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x12, sizeof(pMsg));
	memcpy(pMsg.AccountID, lpUser->AccountID, sizeof(pMsg.AccountID));
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name));
	pMsg.Number = aIndex;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void OfflineMode::DGAnsOffCharacter(SDHP_DBCHAR_INFORESULT* lpMsg)
{
	short aIndex = lpMsg->Number;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	char szAccountID[11] = { 0 };
	char szName[11] = { 0 };

	memcpy(szAccountID, lpMsg->AccountID, sizeof(lpMsg->AccountID));
	memcpy(szName, lpMsg->Name, MAX_ACCOUNT_LEN);

	if(gObjIsAccontConnect(aIndex, szAccountID) == FALSE)
	{
		LogAddC(2, lMsg.Get(MSGGET(1, 170)), szAccountID);
		CloseClient(aIndex);
		return;
	}

	if(lpMsg->result == false)
	{
		LogAddC(2, lMsg.Get(MSGGET(1, 171)), szName, gObj[aIndex].AccountID);
		CloseClient(aIndex);
		return;
	}

	if((lpMsg->CtlCode&1) != 0)
	{
		LogAddC(2, "error-L1 : Load Block Character infomation", szName, gObj[aIndex].AccountID);
		CloseClient(aIndex);
		return;
	}

	for(int i = OBJ_STARTUSERINDEX; i < OBJMAX; i++)
	{
		if(gObj[i].Connected == PLAYER_PLAYING)
		{
			if(gObj[i].Type == OBJ_USER)
			{
				if(!strncmp(szName, gObj[i].Name, MAX_ACCOUNT_LEN) || !strncmp(szAccountID, gObj[i].AccountID, MAX_ACCOUNT_LEN))
				{
					LogAddTD("[Anti-HACK][JGGetCharacterInfo] Attempted Character-Copy by double logging [%s][%s]",	szName, gObj[aIndex].AccountID);
					CloseClient(aIndex);
					return;
				}
			}
		}
	}

	gObj[aIndex].Connected = PLAYER_LOGGED;	//!!!

	if(gObjSetCharacter((LPBYTE)lpMsg, aIndex) == FALSE)
	{
		LogAddC(2, lMsg.Get(MSGGET(1, 172)), szName);
		CloseClient(aIndex);
		return;
	}

	gObj[aIndex].CheckSumTime = 0;//!!!

	gObj[aIndex].iShield = gObj[aIndex].iMaxShield + gObj[aIndex].iAddShield;

	LPOBJ lpObj = &gObj[aIndex];

	if(gObj[aIndex].m_Index != aIndex)
	{
		LogAddC(2, lMsg.Get(MSGGET(1, 173)), __FILE__, __LINE__);
		CloseClient(aIndex);
		return;
	}

	if(lpObj->Money < 0)
	{
		LogAddC(2, "[ ZEN MODIFY ] [%s][%s] %d -> 0", szName, gObj[aIndex].AccountID, lpObj->Money);
		lpObj->Money = 0;
	}
	
	if(lpObj->m_bMapSvrMoveReq == false)	//???
	{
		if(MapNumberCheck(lpObj->MapNumber) == FALSE)
		{
			LogAdd("error-L3 : %s %d", __FILE__, __LINE__);
			CloseClient(aIndex);
			return;
		}

		short wGameServerCode = g_MapServerManager.CheckMoveMapSvr(lpObj->m_Index, lpObj->MapNumber, lpObj->m_sPrevMapSvrCode);

		if(wGameServerCode != gGameServerCode)
		{
			if(wGameServerCode == -1)
			{
				LogAddC(2,"[MapServerMng] Map Server Move Fail : CheckMoveMapSvr() == -1 [%s][%s] (%d)", lpObj->AccountID, lpObj->Name, lpObj->m_Index);
				CloseClient(aIndex);
				return;
			}

			GJReqMapSvrMove(lpObj->m_Index, wGameServerCode, lpObj->MapNumber, lpObj->X, lpObj->Y);
			LogAddTD("[MapServerMng] Request to Move Map Server : (%d) - [%s][%s] (%d)", wGameServerCode, lpObj->AccountID, lpObj->Name, lpObj->m_Index);
			return;
		}
	}
	
	lpObj->m_bMapSvrMoveReq = false;

	__int64 Experience = lpObj->Experience;

	if(g_MasterLevelSystem.CheckIsMasterLevelCharacter(lpObj) != FALSE)
	{
		Experience = lpObj->MLExp;
	}

	__int64 NextExperience = lpObj->NextExp;

	if(g_MasterLevelSystem.CheckIsMasterLevelCharacter(lpObj) != FALSE)
	{
		NextExperience = lpObj->MLExp;
	}

	g_QuestInfo.QuestInfoSave(lpObj);
	g_ExGDManager.DB_Load(aIndex);
	g_MasterLevelSystem.GDReqMasterLevelInfo(lpObj);
	g_QuestUtil.Quest3rdRequestInfo(lpObj);
	DGGuildMemberInfoRequest(aIndex);

	#if(FIX_LAND_OWNDER==TRUE)
	lpObj->GuildLoadTick = 1;
	#endif

	FriendListRequest(aIndex);
	gObjUseSkill.SkillChangeUse(lpObj->m_Index);

	#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
	g_PremiumSystemEx.UserConnect(aIndex);
	#endif

	#if(CUSTOM_SAVE_PT==TRUE)
	gParty.RestoreParty(aIndex);
	#endif

	#if(CUSTOM_RETURNSPOT==TRUE)
	g_SpotReturn.GDStatusUpdate(aIndex, eStatusNormal);
	#endif

	lpObj->m_OfflineMode = true;
	lpObj->m_OfflineSkill = 0;
}

void OfflineMode::DGPSelectData(PMSG_GDLOAD_OFFMODE_DATA* lpMsg)
{
	short aIndex = lpMsg->Number;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->m_OfflineSkill = MAKE_NUMBERW(lpMsg->AttackData[0], lpMsg->AttackData[1]);
	lpUser->m_OfflineAutoBuff = lpMsg->AttackData[2];
	lpUser->m_OfflinePickZen = lpMsg->AttackData[3];
	lpUser->m_OfflinePickJewel = lpMsg->AttackData[4];
	lpUser->m_OfflinePickExel = lpMsg->AttackData[5];
	lpUser->m_OfflinePickAnc = lpMsg->AttackData[6];
	//lpUser->m_OfflinePickForBonus = lpMsg->AttackData[7];

	if(lpMsg->PShopOpen)
	{
		int iSize = 0;
		int iCredSize = 0;

		for(int i = MAIN_INVENTORY_SIZE; i < INVENTORY_SIZE; i++)
		{
			if(!lpMsg->PriceData[iSize])
			{
				iSize += 17;
				iCredSize += 4;
				continue;
			}

			iSize++;

			CItem * sitem = &gObj[aIndex].Inventory1[i];
		
			sitem->m_iPShopValue = MAKE_NUMBERDW(MAKE_NUMBERW(lpMsg->PriceData[iSize], lpMsg->PriceData[iSize+1]), MAKE_NUMBERW(lpMsg->PriceData[iSize+2], lpMsg->PriceData[iSize+3]));
			iSize += 4;

			sitem->m_iPShopBonus = MAKE_NUMBERDW(MAKE_NUMBERW(lpMsg->PriceData[iSize], lpMsg->PriceData[iSize+1]), MAKE_NUMBERW(lpMsg->PriceData[iSize+2], lpMsg->PriceData[iSize+3]));
			iSize += 4;

			sitem->m_PShopBlessValue = MAKE_NUMBERW(lpMsg->PriceData[iSize], lpMsg->PriceData[iSize+1]);
			iSize += 2;

			sitem->m_PShopSoulValue = MAKE_NUMBERW(lpMsg->PriceData[iSize], lpMsg->PriceData[iSize+1]);
			iSize += 2;

			sitem->m_PShopChaosValue = MAKE_NUMBERW(lpMsg->PriceData[iSize], lpMsg->PriceData[iSize+1]);
			iSize += 2;

			sitem->m_PShopLifeValue = MAKE_NUMBERW(lpMsg->PriceData[iSize], lpMsg->PriceData[iSize+1]);
			iSize += 2;

			sitem->m_iPShopCredit = MAKE_NUMBERDW(MAKE_NUMBERW(lpMsg->CreditData[iCredSize], lpMsg->CreditData[iCredSize+1]), MAKE_NUMBERW(lpMsg->CreditData[iCredSize+2], lpMsg->CreditData[iCredSize+3]));
			iCredSize += 4;
		}

		memcpy(lpUser->m_szPShopText, lpMsg->PShopText, sizeof(lpMsg->PShopText));
		lpUser->m_bPShopOpen = true;

		PMSG_ANS_PSHOP_TEXT_CHANGED pMsg;
		PHeadSubSetB((LPBYTE)&pMsg, 0x3F, 0x10, sizeof(pMsg));
		pMsg.NumberH = SET_NUMBERH(aIndex);
		pMsg.NumberL = SET_NUMBERL(aIndex);
		memcpy(pMsg.btPShopText, lpMsg->PShopText, sizeof(pMsg.btPShopText));
		memcpy(pMsg.btName, gObj[aIndex].Name, sizeof(pMsg.btName));
		MsgSendV2(&gObj[aIndex], (LPBYTE)&pMsg, pMsg.h.size);
	}
}

void OfflineMode::GDUpdateData(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_GDSAVE_OFFMODE_DATA pMsg = { 0 };
	pMsg.h.set((LPBYTE)&pMsg, 0xED, sizeof(pMsg));
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name));
	pMsg.Status = lpUser->m_OfflineMode;
	memcpy(pMsg.PShopText, lpUser->m_szPShopText, sizeof(pMsg.PShopText));

	if(lpUser->m_OfflineMode && lpUser->m_bPShopOpen)
	{
		pMsg.PShopOpen = true;
	}
	else
	{
		pMsg.PShopOpen = false;
	}

	BYTE btBuff[OFFLINEMODE_DBMAX] = { 0 };

	btBuff[0] = SET_NUMBERH(lpUser->m_OfflineSkill);
	btBuff[1] = SET_NUMBERL(lpUser->m_OfflineSkill);	
	btBuff[2] = lpUser->m_OfflineAutoBuff;				
	btBuff[3] = lpUser->m_OfflinePickZen;				
	btBuff[4] = lpUser->m_OfflinePickJewel;				
	btBuff[5] = lpUser->m_OfflinePickExel;				
	btBuff[6] = lpUser->m_OfflinePickAnc;				
	btBuff[7] = 0;			

	memcpy(pMsg.AttackData, btBuff, OFFLINEMODE_DBMAX);

	int iSize = 0;
	BYTE btPacket[OFFLINEMODE_DBPRICE] = { 0 };

	int iCredSize = 0;
	BYTE btCredit[OFFLINEMODE_DBCREDIT] = { 0 };

	for(int i = MAIN_INVENTORY_SIZE; i < INVENTORY_SIZE; i++)
	{
		CItem* sitem = &gObj[aIndex].Inventory1[i];

		btPacket[iSize] = sitem->IsItem();									iSize++;

		btPacket[iSize] = SET_NUMBERH(SET_NUMBERHW(sitem->m_iPShopValue));	iSize++;
		btPacket[iSize] = SET_NUMBERL(SET_NUMBERHW(sitem->m_iPShopValue));	iSize++;
		btPacket[iSize] = SET_NUMBERH(SET_NUMBERLW(sitem->m_iPShopValue));	iSize++;
		btPacket[iSize] = SET_NUMBERL(SET_NUMBERLW(sitem->m_iPShopValue));	iSize++;

		btPacket[iSize] = SET_NUMBERH(SET_NUMBERHW(sitem->m_iPShopBonus));	iSize++;
		btPacket[iSize] = SET_NUMBERL(SET_NUMBERHW(sitem->m_iPShopBonus));	iSize++;
		btPacket[iSize] = SET_NUMBERH(SET_NUMBERLW(sitem->m_iPShopBonus));	iSize++;
		btPacket[iSize] = SET_NUMBERL(SET_NUMBERLW(sitem->m_iPShopBonus));	iSize++;

		btPacket[iSize] = SET_NUMBERH(sitem->m_PShopBlessValue);			iSize++;
		btPacket[iSize] = SET_NUMBERL(sitem->m_PShopBlessValue);			iSize++;
			
		btPacket[iSize] = SET_NUMBERH(sitem->m_PShopSoulValue);				iSize++;
		btPacket[iSize] = SET_NUMBERL(sitem->m_PShopSoulValue);				iSize++;

		btPacket[iSize] = SET_NUMBERH(sitem->m_PShopChaosValue);			iSize++;
		btPacket[iSize] = SET_NUMBERL(sitem->m_PShopChaosValue);			iSize++;

		btPacket[iSize] = SET_NUMBERH(sitem->m_PShopLifeValue);				iSize++;
		btPacket[iSize] = SET_NUMBERL(sitem->m_PShopLifeValue);				iSize++;

		btCredit[iCredSize] = SET_NUMBERH(SET_NUMBERHW(sitem->m_iPShopCredit));	iCredSize++;
		btCredit[iCredSize] = SET_NUMBERL(SET_NUMBERHW(sitem->m_iPShopCredit));	iCredSize++;
		btCredit[iCredSize] = SET_NUMBERH(SET_NUMBERLW(sitem->m_iPShopCredit));	iCredSize++;
		btCredit[iCredSize] = SET_NUMBERL(SET_NUMBERLW(sitem->m_iPShopCredit));	iCredSize++;
	}

	memcpy(pMsg.PriceData, btPacket, OFFLINEMODE_DBPRICE);

	memcpy(pMsg.CreditData, btCredit, OFFLINEMODE_DBCREDIT);

	cDBSMng.Send((char*)&pMsg, sizeof(pMsg));
}

void OfflineMode::GDReqUpdateStatus(int aIndex)
{
	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_GDREQ_OFFMODE_STATUS pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x13, sizeof(pMsg));
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name));
	pMsg.Status = lpUser->m_OfflineMode;
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);	

//	lpUser->m_OfflineMode = Status;

	//this->GDUpdateData(aIndex);	//need add other packet status 
}
#endif

bool OfflineMode::CheckBlockMap(int Map)
{
	if( g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::SILVER2))
	{
		for(int i = 0; i < this->m_BlockMap.size(); i++)
		{
			if(this->m_BlockMap[i].MapNumber == Map)
			{
				return false;
			}
		}
	}

	return true;
}


#endif