//-> Decompiled by DarkSim | 18.02.2013 | 1.01.00 GS-N (All names are original)
// -------------------------------------------------------------------------------

#include "StdAfx.h"
#include "NewMasterLevelSystem.h"
#include "NewMasterLevelSkillTreeSystem.h"
#include "logproc.h"
#include "GameMain.h"
#include "..\common\winutil.h"
#include "DBSockMng.h"
#include "ObjCalCharacter.h"
#include "DSProtocol.h"
#include "GensSystem.h"
#include "..\include\ReadScript.h"
#include "Configs.h"
#include "ExLicense.h"
// -------------------------------------------------------------------------------

int g_bIsSpeedServer;		//-> extern from GameMain.cpp (0b0415c8)
int g_MLBattleZoneAddExp;	//-> extern from GameMain.cpp (0b0415dc)
// -------------------------------------------------------------------------------

CMasterLevelSystem g_MasterLevelSystem;
// -------------------------------------------------------------------------------

//00553160	-> 100%
CMasterLevelSystem::CMasterLevelSystem()
{
	// ----
}
// -------------------------------------------------------------------------------

//005531e0	-> 100%
CMasterLevelSystem::~CMasterLevelSystem()
{
	// ----
}
// -------------------------------------------------------------------------------

//00553210	-> 100%
void CMasterLevelSystem::ReadCommonServerInfo()	//OK
{
	this->m_UseMonsterList = GetPrivateProfileInt("Common", "UseMonsterList", true, gDirPath.GetNewPath("MasterSystem.cfg"));
	// ----
	if( this->m_UseMonsterList )
	{
		this->ReadMonsterList(gDirPath.GetNewPath("MasterSystemMonster.txt"));
	}
	// ----
	this->m_iMinMonsterKillLevel = GetPrivateProfileInt("Common", "MonsterMinLevel", 110, gDirPath.GetNewPath("MasterSystem.cfg"));
	char szTemp[10] = { 0 };
	GetPrivateProfileString("Common", "AddExperience", "1", szTemp, 5, gDirPath.GetNewPath("MasterSystem.cfg"));
	this->m_fAddExpRate = atof(szTemp);
	// ----
/*	if( g_bIsSpeedServer )	//-> New
	{
		char defaultExp[10] = "";
		_gcvt(3.0, 4, defaultExp);
		GetPrivateProfileString("GameServerInfo", "SpeedS_ML_AddExperience", defaultExp, szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
		this->m_fAddExpRate  = atof(szTemp);
	}*/

	this->m_CharacterLevel = GetPrivateProfileInt("Common", "CharacterLevel", 0, gDirPath.GetNewPath("MasterSystem.cfg"));
	this->m_CharacterReset = GetPrivateProfileInt("Common", "CharacterReset", 0, gDirPath.GetNewPath("MasterSystem.cfg"));
	this->m_CharacterGrand = GetPrivateProfileInt("Common", "CharacterGrand", 0, gDirPath.GetNewPath("MasterSystem.cfg"));

	// ----
	LogAddTD("MasterLevel Info Set MinMonsterKillLevel:%d, AddExpRate:%d", this->m_iMinMonsterKillLevel,this->m_fAddExpRate);
}
// -------------------------------------------------------------------------------

//Custom
void CMasterLevelSystem::ReadMonsterList(char * File)
{
	ZeroMemory(this->m_MonsterList, sizeof(this->m_MonsterList));
	int Token;
	int	LoadedCount = 0;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if( SMDFile == 0 )
	{
		MsgBox(lMsg.Get(MSGGET(0, 112)), File);
		return;
	}
	// ----
	while(true) 
	{
		Token = GetToken();
		// ----
		if( Token == END )
		{
			break;
		}
		else
		{
			this->m_MonsterList[LoadedCount] = TokenNumber;
			LoadedCount++;
		}
	}
	// ----
	LogAddTD("[MasterSystem] [%d] Monsters loaded from list", LoadedCount);
	fclose(SMDFile);
}
// -------------------------------------------------------------------------------

//00553380	-> 100%
void CMasterLevelSystem::SetExperienceTable()	//OK
{
	this->MLExpTlb[0] = 0;
	__int64 nTotalLevel				= 0;
	__int64 nTotalLevel_Over		= 0;
	__int64 i64Exp					= 0;
	// ----
	for( int iLevel = 1; iLevel < MAX_MASTER_LEVEL + 1; iLevel++ )
	{
		nTotalLevel			= iLevel + MAX_CHAR_LEVEL;
		i64Exp				= (nTotalLevel + 9) * nTotalLevel * nTotalLevel * 10;
		nTotalLevel_Over	= nTotalLevel - 255;
		i64Exp				+= (nTotalLevel_Over + 9) * nTotalLevel_Over * nTotalLevel_Over * 1000;
		i64Exp				= (i64Exp - 3892250000) / 2;
		// ----
		this->MLExpTlb[iLevel] = i64Exp;
	}
	// ----
	LogAddTD("Master level system exp table setting is complete");
}
// -------------------------------------------------------------------------------

//00553540	-> 100%
void CMasterLevelSystem::gObjNextMLExpCal(LPOBJ lpObj)	//OK
{
	int nNextML						= lpObj->MLevel + 1;
	lpObj->MLNextExp	= this->MLExpTlb[nNextML];
}
// -------------------------------------------------------------------------------

//005535a0	-> 100%
int	CMasterLevelSystem::MasterLevelUp(LPOBJ lpObj, __int64 & iAddExp, bool bEventMapReward, int iMonsterType)	//OK
{
	if( !this->CheckIsMasterLevelCharacter(lpObj) )
	{
		return false;
	}
	// ----

	int iTotalMasterLevel = MAX_MASTER_LEVEL;

	if(g_ExLicense.CheckUser(eExUB::NSGames))
	{
		iTotalMasterLevel = 1;
	}

	if( lpObj->MLevel >= iTotalMasterLevel )
	{
		GCServerMsgStringSend(lMsg.Get(1136), lpObj->m_Index, 1);
		return false;
	}
	// ----
	if( bEventMapReward )	//-> New
	{
		iAddExp = iAddExp;	//???
	}
	else
	{
		if(gGENS)
		{
				if( gGensSystem.IsMapBattleZone(lpObj->MapNumber) )	//-> Original g_GensSystem maybe
				{
					iAddExp = iAddExp * (this->m_fAddExpRate + g_MLBattleZoneAddExp);
				}
				else
				{
					iAddExp = iAddExp * this->m_fAddExpRate;
				}
		}
		else
		{
				iAddExp = iAddExp * this->m_fAddExpRate;
		}
	}
	// ----
	if( lpObj->m_MPSkillOpt.MpsPlusExp > 0 )
	{
		iAddExp += iAddExp * lpObj->m_MPSkillOpt.MpsPlusExp / 100;
	}
	// ----
	if( iAddExp > 0 )
	{
		gObjSetExpPetItem(lpObj->m_Index, iAddExp);
		// ----
		LogAddTD("ML Experience : Map[%d]-(%d,%d) [%s][%s](%d) %I64d %I64d MonsterIndex : %d",	//-> Updated
          lpObj->MapNumber, lpObj->X, lpObj->Y, lpObj->AccountID,lpObj->Name,
          lpObj->MLevel, lpObj->MLExp, iAddExp, iMonsterType);
		// ----
		if( iAddExp + lpObj->MLExp >= lpObj->MLNextExp )
		{
			iAddExp = 0;
			// -----
			lpObj->MLExp	= lpObj->MLNextExp;
			lpObj->MLevel++;
#ifdef LVL_UP_POINTS
			if(lpObj->Class == CLASS_WIZARD)
			{
				lpObj->MLPoint += ExConfig.AddMasterLvlPoint.DwLevelPoints;
			}
			else if(lpObj->Class == CLASS_KNIGHT)
			{
				lpObj->MLPoint += ExConfig.AddMasterLvlPoint.DkLevelPoints;
			}
			else if(lpObj->Class == CLASS_ELF)
			{
				lpObj->MLPoint += ExConfig.AddMasterLvlPoint.ElfLevelPoints;
			}
			else if ( lpObj->Class == CLASS_MAGUMSA )
			{
				lpObj->MLPoint += ExConfig.AddMasterLvlPoint.MgLevelPoints;
			}
			else if ( lpObj->Class == CLASS_DARKLORD )
			{
				lpObj->MLPoint += ExConfig.AddMasterLvlPoint.DlLevelPoints;
			}
			else if(lpObj->Class == CLASS_SUMMONER)
			{
				lpObj->MLPoint += ExConfig.AddMasterLvlPoint.SumLevelPoints;
			}
#ifdef MONK
			else if ( lpObj->Class == CLASS_MONK )
			{
				lpObj->MLPoint += ExConfig.AddMasterLvlPoint.RfLevelPoints;
			}
#endif
#else
			lpObj->MLPoint++;	//-> In future can use it for change ml point per level)
#endif
			// -----
			gObjCalCharacter(lpObj->m_Index);
			// -----
			lpObj->MaxLife				+= DCInfo.DefClass[ lpObj->Class ].LevelLife;
			lpObj->MaxMana				+= DCInfo.DefClass[ lpObj->Class ].LevelMana;
			lpObj->Life					= lpObj->AddLife + lpObj->MaxLife;
			lpObj->Mana					= lpObj->AddMana + lpObj->MaxMana;
			// -----
			gObjCalcShieldPoint(lpObj);
			lpObj->iShield				= lpObj->iAddShield + lpObj->iMaxShield;
			// -----
			this->gObjNextMLExpCal(lpObj);
			// ----
			gObjCalcMaxLifePower(lpObj->m_Index);
			gObjSetBP(lpObj->m_Index);
			//GJSetCharacterInfo(lpObj, lpObj->m_Index, 0, 0);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			this->GCMasterLevelUpInfo(lpObj);
			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0, lpObj->iShield);
			GCManaSend(lpObj->m_Index, lpObj->Mana, 0xFF, 0, lpObj->BP);	//-> Original name ->_BP
		}
		else
		{
			lpObj->MLExp += iAddExp;
		}
		// ----
		GCSendExp_INT64(lpObj->m_Index, 65535, iAddExp, 0, 0);		
	}
	// ----
	return true;
}
// -------------------------------------------------------------------------------

//00553a90	-> 100%
int CMasterLevelSystem::CheckIsMasterLevelCharacter(LPOBJ lpObj)	//
{
	if( lpObj == NULL )
	{
		return false;
	}
	// ----
	if( !lpObj->MLInfoLoad )
	{
		return false;
	}
	// ----
	if( lpObj->Level >= MAX_CHAR_LEVEL && lpObj->ChangeUP3rd == 1 )
	{
		return true;
	}



	// ----
	return false;
}
// -------------------------------------------------------------------------------

//00553b00	-> 100%
int CMasterLevelSystem::CheckMinMonsterLevel(LPOBJ lpObj, LPOBJ lpTargetObj)	//OK
{

	//if(this->CheckIsMasterLevelCharacter(lpObj) != FALSE)
	//{
	//	if(lpTargetObj->Level < this->m_iMinMonsterKillLevel)
	//	{
	//		return 0;
	//	}
	//}
	//return 1;

	if(this->CheckIsMasterLevelCharacter(lpObj) != FALSE)
	{
		if(this->m_CharacterLevel > lpObj->Level)
		{
			return false;
		}

		if(this->m_CharacterReset > lpObj->Reset)
		{
			return false;
		}

		if(this->m_CharacterGrand > lpObj->GReset)
		{
			return false;
		}

		if(this->m_UseMonsterList)
		{
			for(int i = 0; i < MASTER_MAX_LIST; i++)
			{
				if(this->m_MonsterList[i] == lpTargetObj->Class)
				{
					return true;
				}
			}

			return false;
		}
		else
		{
			if(lpTargetObj->Level < this->m_iMinMonsterKillLevel)
			{
				return false;
			}
		}

	}

	return true;
}
// -------------------------------------------------------------------------------

//00553b60	-> 100%
__int64 CMasterLevelSystem::GetLevelExperienceTable(int iMasterLevel)	//OK
{
	return MLExpTlb[iMasterLevel];
}
// -------------------------------------------------------------------------------

//00553b90	-> 100%
int CMasterLevelSystem::CheckMasterLevelCharacterPkLevel(LPOBJ lpObj)	//OK
{
	if( !this->CheckIsMasterLevelCharacter(lpObj) )
	{
		return -1;
	}
	// ----
	int iRetValue = 0;
	// ----
	if( lpObj->m_PK_Level <= 3 )
	{
		iRetValue = 7;
	}
	else if( lpObj->m_PK_Level == 4 )
	{
		iRetValue = 20;
	}
	else if( lpObj->m_PK_Level == 5 )
	{
		iRetValue = 30;
	}
	else if( lpObj->m_PK_Level >= 6 )
	{
		iRetValue = 40;
	}
	// ----
	return iRetValue;
}
// -------------------------------------------------------------------------------

//00553c50	-> 100%
int CMasterLevelSystem::CheckMasterLevelCharacterMoneyLevel(LPOBJ lpObj)	//OK
{
	if( !this->CheckIsMasterLevelCharacter(lpObj) )
	{
		return -1;
	}
	// ----
	return MASTER_ZEN_DEC;
}
// -------------------------------------------------------------------------------

//00553c90	-> 100%
void CMasterLevelSystem::GDReqMasterLevelInfo(LPOBJ lpObj)	//OK
{
	if( lpObj->MLInfoLoad )
	{
		return;
	}
	// ----
	MLP_REQ_MASTERLEVEL_INFO pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0x30, sizeof(MLP_REQ_MASTERLEVEL_INFO));
	// ----
	pMsg.iUserIndex = lpObj->m_Index;
    memcpy(pMsg.szCharName, lpObj->Name, MAX_IDSTRING);
    pMsg.szCharName[MAX_IDSTRING] = 0;
	// ----
    cDBSMng.Send((char*)&pMsg, pMsg.h.size);
	// ----
    LogAddTD("[%s][%s] Request master level info to DB", lpObj->AccountID, lpObj->Name);
}
// -------------------------------------------------------------------------------

//00553d40	-> 100%
void CMasterLevelSystem::DGRequestMasterLevelInfoLoad(BYTE * aRecv)	//OK
{
	if( !aRecv )
	{
		return;
	}
	// ----
	MLP_ANS_MASTERLEVEL_INFO * lpRecvMsg = (MLP_ANS_MASTERLEVEL_INFO*)aRecv;
	// ----
	if( !gObjIsConnectedGP(lpRecvMsg->iUserIndex) )
	{
		return;
	}
	// ----
	int iIndex	= lpRecvMsg->iUserIndex;
	LPOBJ lpObj	= &gObj[lpRecvMsg->iUserIndex];
	// ---
	if( lpObj->MLInfoLoad )
	{
		return;
	}
	// ----
	if( !lpRecvMsg->btResult )
	{
		LogAddTD("[%s][%s] MasterLevel Info Load Fail", lpObj->AccountID, lpObj->Name);	//-> New
		return;
	}
	// ----
	if( lpRecvMsg->btResult == 1 )
	{
		/*if( lpObj->MLPoint + lpRecvMsg->nMLPoint != lpRecvMsg->nMLevel )	//-> New (be good use MASTER_MAX_POINT for check)
		{
			LogAddTD("[%s][%s] MasterLevel Info Mismatch!! - Point(%d), Use Point(%d), Level(%d)",
				lpObj->AccountID, lpObj->Name,
				lpRecvMsg->nMLPoint, lpObj->MLInfoLoad, lpRecvMsg->nMLevel);
		}*/
		// ----
		lpObj->MLInfoLoad = 1;
		// ----
		if( lpRecvMsg->nMLevel == 0 && lpRecvMsg->i64NextMLExp == 0 )
		{
			lpObj->MLevel			= lpRecvMsg->nMLevel;
			lpObj->MLExp		= lpRecvMsg->i64MLExp;
			lpObj->MLNextExp	= MLExpTlb[1];
			lpObj->MLPoint		= lpRecvMsg->nMLPoint;
			// ----
			LogAddTD("[%s][%s] MasterLevel Info First Set [MLevel:%d][MLExp:%I64d][MLNextExp:%I64d][MLPoint:%d]",
				lpObj->AccountID, lpObj->Name, lpObj->MLevel, 
				lpObj->MLExp, lpObj->MLNextExp, lpObj->MLPoint);
			// ----
			this->GDRequestMasterLevelInfoSave(lpObj);
		}
		else
		{
			lpObj->MLevel			= lpRecvMsg->nMLevel;
			lpObj->MLExp		= lpRecvMsg->i64MLExp;
			lpObj->MLNextExp	= lpRecvMsg->i64NextMLExp;
			lpObj->MLPoint		= lpRecvMsg->nMLPoint;
			// ----
			LogAddTD("[%s][%s] Recv MasterLevel Info [MLevel:%d][MLExp:%I64d][MLNextExp:%I64d][MLPoint:%d]", 
				lpObj->AccountID, lpObj->Name, lpObj->MLevel, 
				lpObj->MLExp, lpObj->MLNextExp, lpObj->MLPoint);
			// ----
			this->GDRequestMasterLevelInfoSave(lpObj);
		}
		// ----
		lpObj->MaxLife = DCInfo.DefClass[lpObj->Class].Life + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelLife  + ((lpObj->Vitality - DCInfo.DefClass[lpObj->Class].Vitality ) * DCInfo.DefClass[lpObj->Class].VitalityToLife);
		// ----
		if( lpObj->Life > lpObj->MaxLife + lpObj->AddLife )
		{
			lpObj->Life = lpObj->MaxLife;
		}
		// ----
		lpObj->MaxMana = DCInfo.DefClass[lpObj->Class].Mana + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelMana  + ((lpObj->Energy - DCInfo.DefClass[lpObj->Class].Energy ) * DCInfo.DefClass[lpObj->Class].EnergyToMana);
		// ----
		if( lpObj->Mana > lpObj->MaxMana + lpObj->AddMana )
		{
			lpObj->Mana = lpObj->MaxMana;
		}
		// ----
		gObjCalcMaxLifePower(lpObj->m_Index);
		gObjSetBP(lpObj->m_Index);
		gObjCalcShieldPoint(lpObj);
		// ----
		lpObj->iShield = lpObj->iMaxShield + lpObj->iAddShield;
		// ----
		LogAddTD("[%s][%s] Reset Max Value For MasterLevel [MaxLife:%d][MaxMana:%d][MaxSD:%d]", lpObj->AccountID, lpObj->Name, lpObj->MaxLife, lpObj->MaxMana, lpObj->iShield);
		// ----
		this->GCSendMasterLevelWindowStatus(lpObj);
		// ----
		//	GCSendMasterLevelWindowStatus
		//GCReFillSend(lpObj->m_Index, lpObj->Life, -1, 0, lpObj->iShield);
		//GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
	}
	// ----
	gObjCalCharacter(lpObj->m_Index);
	// -----
	gObjCalcMLSkillItemOption(lpObj);
	g_MasterSkillSystem.CGReqGetMasterLevelSkillTree(lpObj->m_Index);

	
}
// -------------------------------------------------------------------------------

//005543f0	-> 100%
void CMasterLevelSystem::GDRequestMasterLevelInfoSave(LPOBJ lpObj)	//OK
{
	if( !lpObj->MLInfoLoad )
	{
		return;
	}
	// ----
	MLP_REQ_MASTERLEVEL_INFOSAVE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0x31, sizeof(MLP_REQ_MASTERLEVEL_INFOSAVE));
	// ----
	memcpy(pMsg.szCharName, lpObj->Name, MAX_IDSTRING);
	pMsg.szCharName[MAX_IDSTRING] = 0;
	pMsg.nMLevel		= lpObj->MLevel;
	pMsg.i64MLExp		= lpObj->MLExp;
	pMsg.i64NextMLExp	= lpObj->MLNextExp;
	pMsg.nMLPoint		= LOWORD(lpObj->MLPoint);
	// ----
	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
	// ----
	LogAddTD("[%s][%s] MasterLevel Info Save [MLevel:%d][MLExp:%I64d][MLNextExp:%I64d][MLPoint:%d]",
		lpObj->AccountID, lpObj->Name, lpObj->MLevel, 
		LODWORD(lpObj->MLExp), HIDWORD(lpObj->MLExp), 
		LODWORD(lpObj->MLNextExp), HIDWORD(lpObj->MLNextExp),
		lpObj->MLPoint);
}
// -------------------------------------------------------------------------------

//00554540	-> 100%
void CMasterLevelSystem::GCSendMasterLevelWindowStatus(LPOBJ lpObj)	//OK
{
	if( !lpObj->MLInfoLoad )
	{
		this->GDReqMasterLevelInfo(lpObj);
		return;
	}
	// ----
	PMSG_MASTERLEVEL_INFO pMsg;
	PHeadSubSetB(&pMsg.h.c, 0xF3, 0x50, sizeof(PMSG_MASTERLEVEL_INFO));
	// ----
	pMsg.nMLevel		= lpObj->MLevel;// lpObj->MLevel;
	// ----
	pMsg.btMLExp1		= SET_NUMBERH(SET_NUMBERHW(HIDWORD(lpObj->MLExp)));
	pMsg.btMLExp2		= SET_NUMBERL(SET_NUMBERHW(HIDWORD(lpObj->MLExp)));
	pMsg.btMLExp3		= SET_NUMBERH(SET_NUMBERLW(HIDWORD(lpObj->MLExp)));
	pMsg.btMLExp4		= SET_NUMBERL(SET_NUMBERLW(HIDWORD(lpObj->MLExp)));
	pMsg.btMLExp5		= SET_NUMBERH(SET_NUMBERHW(LODWORD(lpObj->MLExp)));
	pMsg.btMLExp6		= SET_NUMBERL(SET_NUMBERHW(LODWORD(lpObj->MLExp)));
	pMsg.btMLExp7		= SET_NUMBERH(SET_NUMBERLW(LODWORD(lpObj->MLExp)));
	pMsg.btMLExp8		= SET_NUMBERL(SET_NUMBERLW(LODWORD(lpObj->MLExp)));
	// ----
	pMsg.btMLNextExp1	= SET_NUMBERH(SET_NUMBERHW(HIDWORD(lpObj->MLNextExp)));
	pMsg.btMLNextExp2	= SET_NUMBERL(SET_NUMBERHW(HIDWORD(lpObj->MLNextExp)));
	pMsg.btMLNextExp3	= SET_NUMBERH(SET_NUMBERLW(HIDWORD(lpObj->MLNextExp)));
	pMsg.btMLNextExp4	= SET_NUMBERL(SET_NUMBERLW(HIDWORD(lpObj->MLNextExp)));
	pMsg.btMLNextExp5	= SET_NUMBERH(SET_NUMBERHW(LODWORD(lpObj->MLNextExp)));
	pMsg.btMLNextExp6	= SET_NUMBERL(SET_NUMBERHW(LODWORD(lpObj->MLNextExp)));
	pMsg.btMLNextExp7	= SET_NUMBERH(SET_NUMBERLW(LODWORD(lpObj->MLNextExp)));
	pMsg.btMLNextExp8	= SET_NUMBERL(SET_NUMBERLW(LODWORD(lpObj->MLNextExp)));
	// ----
	pMsg.nMLPoint		= LOWORD(lpObj->MLPoint);
	pMsg.wMaxLife		= (double)lpObj->AddLife + lpObj->MaxLife;
	pMsg.wMaxMana		= (double)lpObj->AddMana + lpObj->MaxMana;
	pMsg.wMaxShield		= LOWORD(lpObj->iAddShield) + LOWORD(lpObj->iMaxShield);
	pMsg.wMaxBP			= LOWORD(lpObj->AddBP) + LOWORD(lpObj->MaxBP);
	// ----
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
}
// -------------------------------------------------------------------------------

//00554960	-> 100%
void CMasterLevelSystem::GCMasterLevelUpInfo(LPOBJ lpObj)	//OK
{
	PMSG_MASTERLEVEL_UP pMsg;
	PHeadSubSetB(&pMsg.h.c, 0xF3, 0x51, 0x20);
	// ----
	pMsg.nMLevel		= lpObj->MLevel;
	pMsg.nAddMLPoint	= 1;
	pMsg.nMLPoint		= lpObj->MLPoint;
	pMsg.nMaxMLPoint	= MASTER_MAX_POINT;
	pMsg.wMaxLife		= (double)lpObj->AddLife + lpObj->MaxLife;
	pMsg.wMaxMana		= (double)lpObj->AddMana + lpObj->MaxMana;
	pMsg.wMaxShield		= LOWORD(lpObj->iAddShield) + LOWORD(lpObj->iMaxShield);
	pMsg.wMaxBP			= LOWORD(lpObj->AddBP) + LOWORD(lpObj->MaxBP);
	// ----
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	GCSendEffectInfo(lpObj->m_Index, 16);
	// ----
	LogAddTD("[%s][%s] Master Level Up :%d, MLPoint:%d/%d", lpObj->AccountID, lpObj->Name, lpObj->MLevel, lpObj->MLPoint, MASTER_MAX_POINT);
}
// -------------------------------------------------------------------------------