#include "StdAfx.h"
#include "DSProtocol.h"
#include "protocol.h"
#include "ExUser.h"
#include "logproc.h"
#include "..\\common\\winutil.h"
#include "..\include\prodef.h"
#include "Configs.h"
#include "ExLicense.h"
#include "GameMain.h"
#include "TUnion.h"
#include "ObjCalCharacter.h"
#include "CreditDonate.h"
#include "ItemRank.h"
#include "PremiumSystemEx.h"
#include "Ranking.h"
#include "WingsDamage.h"
#include "SystemOfRage.h"
#include "ExGDManager.h"
#include "AntiCheatPlus.h"
#include "Smithy.h"
#include "OfflineMode.h"
#include "MapQuest.h"
#include "UserConfig.h"
#include "EDSProtocol.h"
#include "CustomSystem.h"
#include "VIPSystem.h"

void ExUserDataSend(int aIndex)
{
	EXINFO_UPDATE rSend;
	LPOBJ lpObj =&gObj[aIndex];
	rSend.h.set((LPBYTE)&rSend, 0xFB, 14, sizeof(rSend));
	rSend.PremiumTime = g_VIPSystem.VipTimeLeft(lpObj->PremiumTime);
	rSend.Chaos = lpObj->ChaosBank;
	rSend.Bless = lpObj->BlessBank;
	rSend.Soul = lpObj->SoulBank;
	rSend.Life = lpObj->LifeBank;
	rSend.ExCred = lpObj->ExCred;
	rSend.Zen = lpObj->Zen;

	rSend.WCoinC = (int)lpObj->GameShop.WCoinC;
	rSend.WCoinP = (int)lpObj->GameShop.WCoinP;
	rSend.WCoinG = (int)lpObj->GameShop.GoblinPoint;

	rSend.CreateonBank = lpObj->CreateonBank;

	rSend.PremiumType = lpObj->PremiumTimeType;
	rSend.DonateCredit = lpObj->m_iDonateCredit;

	rSend.GuardianBank = lpObj->GuardianBank;
	rSend.HarmonyBank = lpObj->HarmonyBank;
	rSend.LowStoneBank = lpObj->LowStoneBank;
	rSend.HighStoneBank = lpObj->HighStoneBank;
	rSend.GemStoneBank = lpObj->GemStoneBank;

	rSend.PCPoint = lpObj->PCPoint;

	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
}

#ifdef NEW_HP_BAR

struct VieweCharEx
{
	short aIndex;		//2
	int Life;			//6
	int MaxLife;		//10
	int SD;				//14
	int MaxSD;			//18
	short Level;		//20
	short Reset;		//22
	short GrandReset;	//24
	short Defence;		//26
	short Class;		//28
	short AutoParty;	//30
#ifdef PREM_TYPE
	int PremType;
#endif
	BYTE TvTTeam;
#ifdef VIEW_MONSTER
	char Name[20];
#endif
};

struct CGExUserHpBar
{
	//PBMSG_HEAD2 h;
	//struct PWMSG_HEAD h;
	PWMSG_HEAD2 h;
	//int MaxCount;
#ifdef VIEW_MONSTER
	VieweCharEx Vp[75];	//MAX_VIEWPORT
#else
	VieweCharEx Vp[75];	//MAX_VIEWPORT
#endif
};

struct EX_USER_COUNT
{
	PWMSG_HEAD2 h;
	BYTE count;
};

struct CGExUserHpBar2
{
	//PBMSG_HEAD2 h;
	//struct PWMSG_HEAD h;
	PWMSG_HEAD2 h;
	//int MaxCount;
#ifdef VIEW_MONSTER
	VieweCharEx Vp[75];	//MAX_VIEWPORT
#else
	VieweCharEx Vp[75];	//MAX_VIEWPORT
#endif
};

void ExUserVieweport(int aIndex)
{
#ifdef HPBAR_UPDATE

	if(!ExConfig.ExCustom.EnableHPBar)
	{
		return;
	}

	BYTE SendBuff[5000];
	int datasize = 6;//6
	BYTE icount = 0;

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}


#if(OFFLINE_MODE == TRUE)
		if(lpObj->m_OfflineMode == true)
		{
			return;
		}
#endif

	if(lpObj->OffExp != 0) return;
	if(lpObj->OffTrade != 0) return;



	//CGExUserHpBar exSend;
	//int SizeSend = 0;
	//memset(&exSend,-1,sizeof(exSend));
	//PHeadSetW((LPBYTE)&exSend, 0xFA, sizeof(exSend));	
	//PHeadSubSetW((LPBYTE)&exSend, 0xFA, 0x01, sizeof(exSend));
	//SizeSend += 4 + 4;
	//int count = 0;

	//exSend.MaxCount = 0;

	for(int n = 0; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected == PLAYER_PLAYING)
		{
			if(lpTempObj->m_State == 1 || lpTempObj->m_State == 2)
			{
				if(lpObj->MapNumber == lpTempObj->MapNumber)
				{
					if(gObjCheckViewport(aIndex,lpTempObj->X,lpTempObj->Y) == 1)
					{
						if(lpTempObj->Type != OBJ_MONSTER && lpTempObj->Type != OBJ_USER) continue;

						VieweCharEx Vp;

						Vp.aIndex = n;
						Vp.Life = (DWORD)gObj[n].Life;
						Vp.MaxLife = (DWORD)gObj[n].MaxLife + gObj[n].AddLife;
						Vp.SD = (DWORD)gObj[n].iShield;
						Vp.MaxSD = (DWORD)gObj[n].iMaxShield + gObj[n].iAddShield;
						Vp.Level = lpTempObj->Level;
						Vp.Reset = lpTempObj->Reset;
						Vp.GrandReset = lpTempObj->GReset;
						Vp.Defence = lpTempObj->m_Defense;		
						Vp.Class = lpTempObj->Class;	
						Vp.AutoParty = lpTempObj->AutoPt;	
#ifdef PREM_TYPE
						if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
						{
							Vp.PremType = lpTempObj->PremiumTimeType;
						}
#endif
#if(EVENT_TEAM_VS_TEAM)
						Vp.TvTTeam = lpTempObj->m_TvTTeam;
#endif
#ifdef VIEW_MONSTER
						if(lpTempObj->Type == OBJ_USER)
						{
							memcpy(Vp.Name, gObj[n].Name, sizeof(Vp.Name));
						}
						else
						{
							LPMONSTER_ATTRIBUTE lpMonsterAttr = gMAttr.GetAttr(lpTempObj->Class);
							memcpy(Vp.Name, lpMonsterAttr->m_Name, sizeof(Vp.Name));
						}				
#endif
						memcpy(&SendBuff[datasize],&Vp,sizeof(Vp));
						datasize += sizeof(Vp);

						icount++;
#ifdef VIEW_MONSTER
						if(icount == 75-1) break;
#else
						if(icount == 75-1) break;
#endif
					}
				}
			}
		}
	}

	//SendBuff[0]=0xC2;	// packet header
	//SendBuff[1]=SET_NUMBERH(datasize);
	//SendBuff[2]=SET_NUMBERL(datasize);
	//SendBuff[3]=0xFA;
	//SendBuff[4]=0x01;
	//SendBuff[5]=count;

	if(icount > 0)
	{
		//EX_USER_COUNT pCount;
		//PHeadSubSetW((LPBYTE)&pCount, 0xFA, 0x01, sizeof(datasize));
		//pCount.count = icount;
		//memcpy(SendBuff,&pCount,sizeof(pCount));

		SendBuff[0]=0xC2;	// packet header
		SendBuff[1]=SET_NUMBERH(datasize);
		SendBuff[2]=SET_NUMBERL(datasize);
		SendBuff[3]=0xFA;
		SendBuff[4]=0x01;
		SendBuff[5]=icount;

		//LogAddC(2,"datasize: %d",datasize);

		DataSend(aIndex,SendBuff,datasize);
	}

#else

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(lpObj->OffExp != 0) return;
	if(lpObj->OffTrade != 0) return;

	CGExUserHpBar exSend;
	//int SizeSend = 0;
	memset(&exSend,-1,sizeof(exSend));
	//PHeadSetW((LPBYTE)&exSend, 0xFA, sizeof(exSend));	
	PHeadSubSetW((LPBYTE)&exSend, 0xFA, 0x01, sizeof(exSend));
	//SizeSend += 4 + 4;
	int count = 0;

	//exSend.MaxCount = 0;

	for(int n = 0; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected == PLAYER_PLAYING)
		{
			if(lpTempObj->m_State == 1 || lpTempObj->m_State == 2)
			{
				if(lpObj->MapNumber == lpTempObj->MapNumber)
				{
					if(gObjCheckViewport(aIndex,lpTempObj->X,lpTempObj->Y) == 1)
					{
						if(lpTempObj->Type != OBJ_MONSTER && lpTempObj->Type != OBJ_USER) continue;

						exSend.Vp[count].aIndex = n;
						exSend.Vp[count].Life = (DWORD)gObj[n].Life;
						exSend.Vp[count].MaxLife = (DWORD)gObj[n].MaxLife + gObj[n].AddLife;
						exSend.Vp[count].SD = (DWORD)gObj[n].iShield;
						exSend.Vp[count].MaxSD = (DWORD)gObj[n].iMaxShield + gObj[n].iAddShield;
						exSend.Vp[count].Level = lpTempObj->Level;
						exSend.Vp[count].Reset = lpTempObj->Reset;
						exSend.Vp[count].GrandReset = lpTempObj->GReset;
						exSend.Vp[count].Defence = lpTempObj->m_Defense;		
						exSend.Vp[count].Class = lpTempObj->Class;	
						exSend.Vp[count].AutoParty = lpTempObj->AutoPt;	


#ifdef VIEW_MONSTER
							strcpy(exSend.Vp[count].Name,gObj[n].Name);
							//lpMonsterAttr = gMAttr.GetAttr(MonsterClass);
#endif
						count++;

						//exSend.MaxCount++;

						//SizeSend += 30;
#ifdef VIEW_MONSTER
						if(count == 75-1) break;
#else
						if(count == 75-1) break;
#endif
					}
				}
			}
		}
	}

	//LogAddC(2,"OldSizeSend: %d | NewSizeSend: %d",sizeof(exSend),SizeSend);

	//PHeadSubSetW((LPBYTE)&exSend, 0xFA, 0x01, SizeSend);
	DataSend(aIndex,(LPBYTE)&exSend,sizeof(exSend));
	//DataSend(aIndex,(LPBYTE)&exSend,SizeSend);
#endif
}

/*
							memcpy(&sendBuf[lOfs],&pViewportDestroy,sizeof(pViewportDestroy));
							lOfs += sizeof(pViewportDestroy);
							count += 1;

		if(count > 0)
		{
			pCount.h.c = 0xC1;
			pCount.h.headcode = 0x14;
			pCount.h.size = lOfs;
			pCount.count = count;

			memcpy(sendBuf,&pCount,sizeof(pCount));
			DataSend(aIndex,sendBuf,lOfs);
		}
*/

#endif

void ResetSystemGC_CharUpdate(LPOBJ lpUser)
{
	GC_RESET_CHAR_UPDATE pSend;

	pSend.h.set((LPBYTE)&pSend, 0xFB, 0x05, sizeof(pSend));

	pSend.Level = lpUser->Level;
	pSend.Exp = lpUser->Experience;
	pSend.MaxExp = lpUser->NextExp;
	pSend.Str = lpUser->Strength;
	pSend.Agi = lpUser->Dexterity;
	pSend.Vit = lpUser->Vitality;
	pSend.Ene = lpUser->Energy;
	pSend.Cmd = lpUser->Leadership;
	pSend.UpPoint = lpUser->LevelUpPoint;
	pSend.Reset = lpUser->Reset;
	pSend.Grand = lpUser->GReset;

	DataSend(lpUser->m_Index, (LPBYTE)&pSend, pSend.h.size);
}

bool ExUserInSafeZone(int aIndex)
{
	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	int map = lpUser->MapNumber;

	if(MAX_MAP_RANGE(map) == FALSE)
	{
		return false;
	}

	BYTE attr = MapC[map].GetAttr(lpUser->X, lpUser->Y);

	if ( (attr&1) == 1 )
	{
		return true;
	}

	return false;
}
// -------------------------------------------------------------------------------

ÑExUser g_ExUser;
// -------------------------------------------------------------------------------

ÑExUser::ÑExUser()
{
	
}
// -------------------------------------------------------------------------------

ÑExUser::~ÑExUser()
{
}
// -------------------------------------------------------------------------------

void ÑExUser::Load()
{
	this->m_bActiveAutoHP = false;

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		if(g_UserConfig.m_EvoMU.HPAutoClicker)
		{
			this->m_bActiveAutoHP = true;
		}
	}
	
	#if(DEV_PLAYERINFO)
	this->EnableInfoPlayer = true;
	#endif

	#if(DEV_DAMAGE_TABLE)
	this->EnableTable = false;

	if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::NSGames) || g_ExLicense.CheckUser(eExUB::eternalmu))
	{
		this->EnableTable = true;
	}
	#endif

}
// -------------------------------------------------------------------------------

bool ÑExUser::InSafeZone(int aIndex)
{
	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	int map = lpUser->MapNumber;

	if(MAX_MAP_RANGE(map) == FALSE)
	{
		return false;
	}

	BYTE attr = MapC[map].GetAttr(lpUser->X, lpUser->Y);

	if ( (attr&1) == 1 )
	{
		return true;
	}

	return false;
}
// -------------------------------------------------------------------------------

bool ÑExUser::CheckAlliancePlayer(int aIndex, int aTarget)
{
	if (!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTarget))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTarget];

	if(lpUser->Connected < PLAYER_PLAYING || lpTarget->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	_GUILD_INFO_STRUCT * lpGuildUser = lpUser->lpGuild;
	_GUILD_INFO_STRUCT * lpGuildTarget = lpTarget->lpGuild;

	if(!lpGuildUser || !lpGuildTarget)
	{
		return false;
	}

	if(!strcmp(lpGuildUser->Name, lpGuildTarget->Name))
	{
		return true;
	}

	TUnionInfo * pUnionUser = UnionManager.SearchUnion(lpGuildUser->iGuildUnion);
	TUnionInfo * pUnionTarget = UnionManager.SearchUnion(lpGuildTarget->iGuildUnion);

	if(!pUnionUser || !pUnionTarget)
	{
		return false;
	}

	if(!strcmp(pUnionUser->m_szMasterGuild, pUnionTarget->m_szMasterGuild))
	{
		return true;
	}

	return false;
}

void ÑExUser::GCDataClient(int aIndex)
{
	if (!OBJMAX_RANGE(aIndex))
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

#if(CUSTOM_ITEM_RANK==TRUE)
	g_ItemRank.GCRankInit(aIndex);
	g_ItemRank.GCRankData(aIndex);
	g_ItemRank.GCRankList(aIndex);
#endif
#if(OFFLINE_MODE == TRUE)
	//g_OfflineMode.GCConfigSend(aIndex);
#endif
#if(CUSTOM_ADD_POINTS==TRUE)
	g_ExUser.ResetPointSend(aIndex);
#endif
	gCreditDonate.GCChangeClassConfig(aIndex);
	g_PremiumSystemEx.GC_Config(aIndex);
}

#if(CUSTOM_ADD_POINTS==TRUE)
void ÑExUser::CGAddPoints(int aIndex, PMSG_ADD_POINTS* aRecv)
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

	if(lpUser->Type != OBJ_USER)
	{
		return;
	}

	if(lpUser->Strength + aRecv->Strength > ExConfig.Character.MaxStats)
	{
		return;
	}
	if(lpUser->Dexterity + aRecv->Dexterity > ExConfig.Character.MaxStats)
	{
		return;
	}
	if(lpUser->Vitality + aRecv->Vitality > ExConfig.Character.MaxStats)
	{
		return;
	}
	if(lpUser->Energy + aRecv->Energy > ExConfig.Character.MaxStats)
	{
		return;
	}
	if(lpUser->Leadership + aRecv->Leadership > ExConfig.Character.MaxStats)
	{
		return;
	}

	int TotalCheck = aRecv->Strength + aRecv->Dexterity + aRecv->Vitality + aRecv->Energy + aRecv->Leadership;

	if(TotalCheck > lpUser->LevelUpPoint)
	{
		MsgOutput(aIndex, "[AddPoints] Total Point Error");
		return;
	}

	lpUser->Strength		+= aRecv->Strength;
	lpUser->Dexterity		+= aRecv->Dexterity;
	lpUser->Vitality		+= aRecv->Vitality;
	lpUser->Energy			+= aRecv->Energy;
	lpUser->Leadership		+= aRecv->Leadership;
	lpUser->LevelUpPoint	-= TotalCheck;

	lpUser->Life = DCInfo.DefClass[lpUser->Class].Life + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelLife  + ((lpUser->Vitality - DCInfo.DefClass[lpUser->Class].Vitality ) * DCInfo.DefClass[lpUser->Class].VitalityToLife);
	lpUser->Mana = DCInfo.DefClass[lpUser->Class].Mana + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelMana  + ((lpUser->Energy - DCInfo.DefClass[lpUser->Class].Energy ) * DCInfo.DefClass[lpUser->Class].EnergyToMana);

	lpUser->MaxLife = DCInfo.DefClass[lpUser->Class].Life + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelLife  + ((lpUser->Vitality - DCInfo.DefClass[lpUser->Class].Vitality ) * DCInfo.DefClass[lpUser->Class].VitalityToLife);
	lpUser->MaxMana = DCInfo.DefClass[lpUser->Class].Mana + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelMana  + ((lpUser->Energy - DCInfo.DefClass[lpUser->Class].Energy ) * DCInfo.DefClass[lpUser->Class].EnergyToMana);


	gObjCalCharacter(aIndex);

	UpdateCharInfo(aIndex);
}
#endif

#if(CUSTOM_ADD_POINTS==TRUE)
void ÑExUser::CGResetPoints(int aIndex, PMSG_ADD_POINTSRESET* aRecv)
{
#if(ADD_ADD_RESETPOINT==0)
	return;
#endif

	if( !g_ExLicense.CheckUser(eExUB::Local) && 
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::MU2Play) &&
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::SILVER1) &&
		!g_ExLicense.CheckUser(eExUB::SILVER2) &&
		!g_ExLicense.CheckUser(eExUB::EpicMU) &&
		!THINNAKORN_MAC &&
		!g_ExLicense.CheckUser(eExUB::Escalate)&&
		!g_ExLicense.CheckUser(eExUB::eternalmu)&&
		!g_ExLicense.CheckUser(eExUB::Artem) &&
		!g_ExLicense.CheckUser(eExUB::Artem2) &&
		!g_ExLicense.CheckUser(eExUB::RevoMU)&&
		!g_ExLicense.CheckUser(eExUB::masonX)&&
		!g_ExLicense.CheckUser(eExUB::ArcMu) &&
		!g_ExLicense.CheckUser(eExUB::GloryMU) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!g_ExLicense.CheckUser(eExUB::mu4you) &&
		!g_ExLicense.CheckUser(eExUB::NSGames))
	{
		return;
	}

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

	if(lpUser->Type != OBJ_USER)
	{
		return;
	}

	if(!aRecv->Result)
	{
		if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
		{
			/*if(lpUser->PremiumTime > 0)
			{
			}
			else
			{
				return;
			}*/
		}
		else
		{
			if(this->ResetStatsPriceWCoin > lpUser->GameShop.WCoinC)
			{
				return;
			}
			lpUser->GameShop.WCoinC -= this->ResetStatsPriceWCoin;	
			gGameShop.GDSaveUserInfo(aIndex);
		}
	}
	else
	{
		if(this->ResetStatsPriceCredit > lpUser->ExCred)
		{
			return;
		}
		lpUser->ExCred -= this->ResetStatsPriceCredit;
	}

	ExUserDataSend(aIndex);

	int TotalPoint = lpUser->Strength + lpUser->Dexterity + lpUser->Vitality + lpUser->Energy + lpUser->Leadership + lpUser->LevelUpPoint;

	TotalPoint -= DCInfo.DefClass[lpUser->Class].Strength;
	TotalPoint -= DCInfo.DefClass[lpUser->Class].Dexterity;
	TotalPoint -= DCInfo.DefClass[lpUser->Class].Energy;
	TotalPoint -= DCInfo.DefClass[lpUser->Class].Vitality;
	TotalPoint -= DCInfo.DefClass[lpUser->Class].Leadership;

	lpUser->Strength = DCInfo.DefClass[lpUser->Class].Strength;
	lpUser->Dexterity = DCInfo.DefClass[lpUser->Class].Dexterity;
	lpUser->Energy = DCInfo.DefClass[lpUser->Class].Energy;
	lpUser->Vitality = DCInfo.DefClass[lpUser->Class].Vitality;
	lpUser->Leadership = DCInfo.DefClass[lpUser->Class].Leadership;

	lpUser->LevelUpPoint = TotalPoint;

	lpUser->Life = DCInfo.DefClass[lpUser->Class].Life + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelLife  + ((lpUser->Vitality - DCInfo.DefClass[lpUser->Class].Vitality ) * DCInfo.DefClass[lpUser->Class].VitalityToLife);
	lpUser->Mana = DCInfo.DefClass[lpUser->Class].Mana + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelMana  + ((lpUser->Energy - DCInfo.DefClass[lpUser->Class].Energy ) * DCInfo.DefClass[lpUser->Class].EnergyToMana);

	lpUser->MaxLife = DCInfo.DefClass[lpUser->Class].Life + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelLife  + ((lpUser->Vitality - DCInfo.DefClass[lpUser->Class].Vitality ) * DCInfo.DefClass[lpUser->Class].VitalityToLife);
	lpUser->MaxMana = DCInfo.DefClass[lpUser->Class].Mana + (lpUser->Level + lpUser->MLevel - 1) * DCInfo.DefClass[lpUser->Class].LevelMana  + ((lpUser->Energy - DCInfo.DefClass[lpUser->Class].Energy ) * DCInfo.DefClass[lpUser->Class].EnergyToMana);

	lpUser->VitalityToLife = DCInfo.DefClass[lpUser->Class].VitalityToLife;
	lpUser->EnergyToMana = DCInfo.DefClass[lpUser->Class].EnergyToMana;


	::gObjSetBP(aIndex);
	::gObjCalcMaxLifePower(aIndex);
	GCReFillSend(aIndex, (int)lpUser->MaxLife + lpUser->AddLife, 0xFE, 0, lpUser->iMaxShield + lpUser->iAddShield);
	GCReFillSend(aIndex, (int)lpUser->Life, 0xFF, 0, lpUser->iShield);
	GCManaSend(aIndex,(int)lpUser->MaxMana + lpUser->AddMana, 0xFE, 0, lpUser->MaxBP + lpUser->AddBP);
	GCManaSend(aIndex, (int)lpUser->Mana, 0xFF, 0, lpUser->BP);
	UpdateCharInfo(aIndex);
	gObjCalCharacter(aIndex);
}

void ÑExUser::ResetPointsLoad()
{
	this->ResetStatsPriceWCoin = GetPrivateProfileInt("ExTeam", "ResetStatsPriceWCoin", 0, gDirPath.GetNewPath("ExData\\ResetStats.ini"));;
	this->ResetStatsPriceCredit = GetPrivateProfileInt("ExTeam", "ResetStatsPriceCredit", 0, gDirPath.GetNewPath("ExData\\ResetStats.ini"));;
}

void ÑExUser::ResetPointSend(int aIndex)
{
#if(ADD_ADD_RESETPOINT==0)
	return;
#endif

	if( !g_ExLicense.CheckUser(eExUB::Local) && 
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::MU2Play) &&
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::SILVER1) &&
		!g_ExLicense.CheckUser(eExUB::SILVER2) &&
		!g_ExLicense.CheckUser(eExUB::EpicMU) &&
		!THINNAKORN_MAC &&
		!g_ExLicense.CheckUser(eExUB::Escalate)&&
		!g_ExLicense.CheckUser(eExUB::eternalmu)&&
		!g_ExLicense.CheckUser(eExUB::Artem)&&
		!g_ExLicense.CheckUser(eExUB::Artem2)&&
		!g_ExLicense.CheckUser(eExUB::RevoMU)&&
		!g_ExLicense.CheckUser(eExUB::masonX)&&
		!g_ExLicense.CheckUser(eExUB::ArcMu) &&
		!g_ExLicense.CheckUser(eExUB::GloryMU) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!g_ExLicense.CheckUser(eExUB::mu4you) &&
		!g_ExLicense.CheckUser(eExUB::NSGames) )
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	GC_RESET_POINT_CFG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x27, sizeof(pMsg));
	pMsg.iResetStatsPriceBonus = this->ResetStatsPriceWCoin;
	pMsg.iResetStatsPriceCredit = this->ResetStatsPriceCredit;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);	
}
#endif

#if(CUSTOM_SERVER_TIME)
void ÑExUser::GCServerTime()
{
	if(!g_ExLicense.CheckUser(eExUB::Local) && 
	   !g_ExLicense.CheckUser(eExUB::Gredy) &&
	   !g_ExLicense.CheckUser(eExUB::Gredy2) && 
	   !g_ExLicense.CheckUser(eExUB::GredyLocal) &&
	   !g_ExLicense.CheckUser(eExUB::Artem) &&
	   !g_ExLicense.CheckUser(eExUB::Stone) &&
	   !g_ExLicense.CheckUser(eExUB::Artem2)&&
	   !g_ExLicense.CheckUser(eExUB::RevoMU))
	{
		return;
	}

	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		PMSG_SERVER_TIME pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x70, sizeof(pMsg));
		pMsg.Hour = sysTime.wHour;
		pMsg.Minute = sysTime.wMinute;
		pMsg.Second = sysTime.wSecond;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);	
	}
}
#endif

void ÑExUser::TickCountClientDataSend()
{
	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(lpUser->m_iLoadConfigNumber <= 0 || lpUser->m_iLoadConfigNumber  > 10)
		{
			continue;
		}

		DWORD dwDelay = (GetTickCount() - lpUser->m_iLoadConfigTickCount);

		if(dwDelay < 1000)
		{
			continue;
		}

		switch(lpUser->m_iLoadConfigNumber)
		{
		case 1:
			g_ExGDManager.DB_Load(aIndex);
			break;
		case 2:
			#if(SYSTEM_ACHIEVEMENTS)
			g_Achievements.GCSettingsData(aIndex);
			#endif
			break;
		case 3:
			this->GCDataClient(aIndex);
		case 4:
			gWingsDamage.PlayerCalculator(aIndex);
			break;
		case 5:
			gRanking.SendUser(aIndex);
			break;
		case 6:
			{
				#if(ANTI_CHEAT_PLUS==TRUE)
				g_AntiCheatPlus.GC_Cheat(aIndex);
				g_AntiCheatPlus.CheckMultiWindow(aIndex);
				g_AntiCheatPlus.CheckMaxWindow(aIndex);
				#endif
			}
			break;
		case 7:
			#if(CUSTOM_SMITHY == TRUE)
			g_Smithy.GCIemSend(aIndex);
			#endif
			break;
		case 8:
			{
				if(g_CustomSystem.IsRage())
				{
					gSystemOfRage.RageConnect(aIndex);
				}
			}
			break;
		case 9:
			{
				#if(OFFLINE_MODE==TRUE)
				if(g_ExLicense.user.OfflineMode)
				{
					g_OfflineMode.GCConfig(aIndex);
				}
				#endif
			}
			break;
		case 10:
			#if(CUSTOM_MAPQUEST)
			g_MapQuest.TeleportMap(aIndex, lpUser->MapNumber);
			#endif
			break;
		}

		lpUser->m_iLoadConfigNumber++;
		lpUser->m_iLoadConfigTickCount = GetTickCount();
	}
}

void ÑExUser::AutoHPClick()
{
	if(!this->m_bActiveAutoHP)
	{
		return;
	}

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(lpUser->m_bAutoHP)
		{
			if((GetTickCount() - gObj[aIndex].m_PotionTick) < ExConfig.CommonServer.PotionDelay)
			{
				continue;
			}

			int count = 0;
	
			for(int n = 0; n < MAIN_INVENTORY_SIZE; n++)
			{
				if(lpUser->pInventory[n].IsItem() == TRUE)
				{
					if( lpUser->pInventory[n].m_Type == ITEMGET(14,0) || 
						lpUser->pInventory[n].m_Type == ITEMGET(14,1) || 
						lpUser->pInventory[n].m_Type == ITEMGET(14,2) || 
						lpUser->pInventory[n].m_Type == ITEMGET(14,3) )
					{
						int iHP = 0;

						switch(lpUser->pInventory[n].m_Type)
						{
						case ITEMGET(14,0):
							iHP += ((int)(lpUser->MaxLife + lpUser->AddLife)) * 10 / 100; 
							break;
						case ITEMGET(14,1):
							iHP += ((int)(lpUser->MaxLife + lpUser->AddLife)) * 20 / 100; 
							break;
						case ITEMGET(14,2):
							iHP += ((int)(lpUser->MaxLife + lpUser->AddLife)) * 30 / 100; 
							break;
						case ITEMGET(14,3):
							iHP += ((int)(lpUser->MaxLife + lpUser->AddLife)) * 40 / 100; 
							break;
						}			

						lpUser->Life += iHP;

						if(lpUser->Life > (lpUser->MaxLife + lpUser->AddLife - 1.0f))
						{
							lpUser->Life = lpUser->MaxLife + lpUser->AddLife;
						}

						GCReFillSend(aIndex, (int)gObj[aIndex].Life, 0xFF, 0, (int)gObj[aIndex].iShield);

						if((int)lpUser->pInventory[n].m_Durability > 1)
						{
							lpUser->pInventory[n].m_Durability--;
							GCItemDurSend(lpUser->m_Index, (BYTE)n, (BYTE)lpUser->pInventory[n].m_Durability, 1);
						}
						else
						{
							gObjInventoryItemSet(aIndex, n, -1);
							gObj[aIndex].pInventory[n].Clear();
							GCInventoryItemDeleteSend(aIndex, n, 1);
						}

						lpUser->m_PotionTick = GetTickCount();

						break;
					}
				}
			}
		}
	}
}

void ÑExUser::CG_RecvAutoHPClicker(PMSG_PROTOCOL_RESULT* lpMsg, int aIndex)
{
	if(!this->m_bActiveAutoHP)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(!lpMsg)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->m_bAutoHP = (bool)lpMsg->Result;
}

void ÑExUser::PlayerKillInfoMail(int aIndex, int aTargetIndex)
{
	if( !g_ExLicense.CheckUser(eExUB::MedoniAndrei) && 
		!g_ExLicense.CheckUser(eExUB::Local) &&
	    !g_ExLicense.CheckUser(eExUB::Gredy) &&
	    !g_ExLicense.CheckUser(eExUB::Gredy2) && 
	    !g_ExLicense.CheckUser(eExUB::GredyLocal)&&
	    !g_ExLicense.CheckUser(eExUB::Artem) &&
	    !g_ExLicense.CheckUser(eExUB::Artem2) )
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		if(!lpUser->m_OfflineMode)
		{
			return;
		}
	}

	char szKillerName[32];
	sprintf(szKillerName, "Killer Name: %s", lpTarget->Name);

	PMSG_FRIEND_MEMO pMsg;
	memset(&pMsg, 0, sizeof(pMsg));
	pMsg.WindowGuid = 0;
	pMsg.Action = 0;
	pMsg.Dir = lpTarget->Dir;
	memcpy(pMsg.Name, lpUser->Name, sizeof(pMsg.Name));
	memcpy(pMsg.Subject, szKillerName, sizeof(pMsg.Subject));
	//memset(pMsg.Memo, 0, sizeof(pMsg.Memo));
	//pMsg.MemoSize = 0;
	memcpy(pMsg.Memo, szKillerName, sizeof(pMsg.Memo));
	pMsg.MemoSize = strlen(szKillerName);
	FriendMemoSendEx(&pMsg, aIndex);
}

void ÑExUser::PartyMiniMapInfo()
{
#if(CUSTOM_MINIMAP_PARTY)

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected < PLAYER_PLAYING)
		{
			continue;
		}

		if(!lpUser->m_MiniMap)
		{
			continue;
		}

		int iPartyNumber = lpUser->PartyNumber;

		if(iPartyNumber >= 0)
		{
			PMSG_PARTY_MINIMAP pMsg;
			pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xD5, sizeof(pMsg));
			pMsg.Count = gParty.GetCount(iPartyNumber);

			int n = 0;

			for(int i = 0; i < MAX_USER_IN_PARTY; i++ )
			{
				int iPartyUser = gParty.m_PartyS[iPartyNumber].Number[i];

				if(gObjIsConnected(iPartyUser))
				{
					LPOBJ lpPartyUser = &gObj[iPartyUser];

					if(lpUser->MapNumber == lpPartyUser->MapNumber)
					{
						memcpy(pMsg.Data[n].Name, lpPartyUser->Name, sizeof(pMsg.Data[i].Name));
						pMsg.Data[n].Map = lpPartyUser->MapNumber;
						pMsg.Data[n].X = lpPartyUser->X;
						pMsg.Data[n].Y = lpPartyUser->Y;

						n++;
					}
				}
			}

			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);	
		}
		
	}
#endif
}

#if(ADD_CTRL_KEY)
void ÑExUser::CGCtrlKey(int aIndex, PMSG_CONTROLLER_CTRL* aRecv)
{
	if(!g_ExLicense.CheckUser(eExUB::Local) &&
	   !g_ExLicense.CheckUser(eExUB::ArcMu))
	{
		return;
	}

	if (!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	lpUser->CtrlKey = aRecv->CtrlKey;
	//LogAddC(2, "Ctrl: %d", lpUser->CtrlKey);
}
#endif

void ÑExUser::RecvConfig(CG_MINIMAP_PARTY* lpMsg, int aIndex)
{
	if (!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	lpUser->m_MiniMap = lpMsg->MiniMap;
}


#if(DEV_PLAYERINFO)
void ÑExUser::RecvInfoPlayer(PMSG_REQ_INFOPLAYER* lpMsg, int aIndex)
{
	if(!this->EnableInfoPlayer)
	{
		return;
	}

	int aTargetIndex = lpMsg->aIndex;

	if(!OBJMAX_RANGE(aIndex) || !OBJMAX_RANGE(aTargetIndex))
	{
		return;
	}

	LPOBJ lpTarget = &gObj[aTargetIndex];

	if(lpTarget->Connected < PLAYER_PLAYING)
	{
		return;
	}

	PMSG_ANS_INFOPLAYER pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xDB, sizeof(pMsg));///////////////////
	pMsg.Data.aIndex = aTargetIndex;
	pMsg.Data.Strength = lpTarget->Strength;
	pMsg.Data.Agility = lpTarget->Dexterity;
	pMsg.Data.Vitality = lpTarget->Vitality;
	pMsg.Data.Energy = lpTarget->Energy;
	pMsg.Data.Command = lpTarget->Leadership;
	pMsg.Data.Reset = lpTarget->Reset;
	pMsg.Data.GReset = lpTarget->GReset;
	pMsg.Data.PKLevel = lpTarget->m_PK_Level;
	pMsg.Data.Vip = lpTarget->PremiumTimeType;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);	
}
#endif

#if(DEV_DAMAGE_TABLE)
void ÑExUser::ResetDamageTable()
{
	if(!this->EnableTable)
	{
		return;
	}

	for(int aIndex = OBJ_STARTUSERINDEX; aIndex < OBJMAX; aIndex++)
	{
		LPOBJ lpUser = &gObj[aIndex];

		if(lpUser->Connected != PLAYER_PLAYING)
		{
			continue;
		}

		lpUser->m_SecondDamage = 0;
		lpUser->m_SecondDefence = 0;
		lpUser->m_SecondReflect = 0;

		this->GCDamageTable(aIndex);
	}
}

void ÑExUser::GCDamageTable(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];

	PMSG_DAMAGE_TABLE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xDC, sizeof(pMsg));//////////////////////
	pMsg.SecondDamage = lpUser->m_SecondDamage;
	pMsg.SecondDefence = lpUser->m_SecondDefence;
	pMsg.SecondReflect = lpUser->m_SecondReflect;
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

#endif