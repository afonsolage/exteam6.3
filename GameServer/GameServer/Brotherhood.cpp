#include "StdAfx.h"
#include "user.h"
#include "Brotherhood.h"
#include "PartyClass.h"
#include "GameMain.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "gObjMonster.h"
#include "MoveCommand.h"
#include "Raklion.h"
#include "RaklionBattleUserMng.h"
#include "Message.h"
#include "BuffManager.h"
#include "ExLicense.h"
#include "ExUser.h"
#include "DSProtocol.h"
#include "DBSockMng.h"
#include "TeleportManager.h"

#if(SYSTEMOF_BROTHER==TRUE)

Brotherhood gBrotherhood;

void Brotherhood::Load()
{
	if(g_ExLicense.user.Brotherhood == false)
	{
		this->Enable = 0;
		return;
	}

	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,Brotherhood_DIR);
	this->PlusExp = GetPrivateProfileInt("ExTeam","PlusExp",0,Brotherhood_DIR);
	this->PlusZen = GetPrivateProfileInt("ExTeam","PlusZen",0,Brotherhood_DIR);

	this->PlusDamage = GetPrivateProfileInt("ExTeam","PlusDamage",0,Brotherhood_DIR);
	this->PlusDefence = GetPrivateProfileInt("ExTeam","PlusDefence",0,Brotherhood_DIR);
	this->PlusIgnore = GetPrivateProfileInt("ExTeam","PlusIgnore",0,Brotherhood_DIR);
	this->PlusDoubleDamage = GetPrivateProfileInt("ExTeam","PlusDoubleDamage",0,Brotherhood_DIR);

	this->BuyType = GetPrivateProfileInt("ExTeam","BuyType",0,Brotherhood_DIR);
	this->BuyCost = GetPrivateProfileInt("ExTeam","BuyCost",0,Brotherhood_DIR);

	this->TeleportActive = GetPrivateProfileInt("ExTeam","TeleportActive",1,Brotherhood_DIR);
	this->ExitActive = GetPrivateProfileInt("ExTeam","ExitActive",0,Brotherhood_DIR);

	#if(BROTHER_PAYTELEPORT)
	this->m_TeleportWCoin = GetPrivateProfileInt("ExTeam","TeleportWCoin",0,Brotherhood_DIR);
	#endif

	FILE *file = fopen(Brotherhood_DIR,"r");

	if (file == NULL)
	{
		MessageBoxA(0,Brotherhood_DIR,"CRITICAL ERROR",0);
		this->Enable = 0;
		return;
	}

	this->DropCount = 0;

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

	}
	fclose(file);
}

bool Brotherhood::ActiveBrother(LPOBJ lpObj)
{
	if(!this->Enable) return false;

#ifdef BR_DEBUG
	return true;
#endif

	int	partynum = lpObj->PartyNumber;

	if(!strcmp(lpObj->Brotherhood,"One"))
	{
		return false;
	}

	if(g_ExLicense.CheckUser(Local) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2))
	{
		int Countbr = 0;
		for (int n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
		{
			if ( gObj[n].Connected == PLAYER_PLAYING )
			{
				LPOBJ LpBrother = &gObj[n];
				if(!strncmp(lpObj->Brotherhood,LpBrother->Brotherhood,10))
				{
					Countbr++;
				}
			}
		}

		if(Countbr >= 5)
		{
			return true;
		}

		return false;
	}
	else
	{

		if(partynum == -1) return false;

		int number = 0;

		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
#if _NEW_PARTY_SYSTEM_ == TRUE
			if( n >= g_MaxPartyMember)
			{
				break;
			}
#endif
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				LPOBJ LpBrother = &gObj[number];

				/*if(g_ExLicense.CheckUser(Local) || g_ExLicense.CheckUser(ulasevich) || g_ExLicense.CheckUser(ulasevich2))
				{
					if(!strncmp(lpObj->Brotherhood,LpBrother->Brotherhood,10))
					{
						return true;
					}
				}
				else*/
				{
					if(strncmp(lpObj->Brotherhood,LpBrother->Brotherhood,10))
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void Brotherhood::UserExp(LPOBJ lpObj, __int64 & Exp)
{
	if(!this->Enable) return;

	if(!this->ActiveBrother(lpObj)) return;

	Exp += ( Exp * this->PlusExp ) / 100;
}

void Brotherhood::UserBonusZen(LPOBJ lpObj, float & money)
{
	if(!this->Enable) return;

	if(!this->ActiveBrother(lpObj)) return;

	money += ( money * this->PlusZen ) / 100;
}

bool Brotherhood::ProccessItemDrop(LPOBJ lpMobObj, LPOBJ lpTargetObj)
{
	if(!this->Enable) return false; 

	if(!this->ActiveBrother(lpTargetObj)) return false;

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
							iLuck = 1;
						}
					}

					if(this->Drop[i].ExlOption)
					{
						if( rand() % 100 < this->Drop[i].ExlRate )
						{
							iExlOpt = GenExcOpt(this->Drop[i].ExlOption);
						}
					}

					if(this->Drop[i].AncOption == 5 || this->Drop[i].AncOption == 10)
					{
						if( rand() % 100 < this->Drop[i].AncRate )
						{
							iAncOpt = this->Drop[i].AncOption;
						}
					}

					ItemSerialCreateSend(lpMobObj->m_Index,lpMobObj->MapNumber,lpMobObj->X,lpMobObj->Y,ITEMGET(this->Drop[i].Type,this->Drop[i].Index),iLevel,this->Drop[i].Dur,iSkill,iLuck,iOption,gObjMonsterTopHitDamageUser(lpMobObj),iExlOpt,iAncOpt);
					return true;
				}
			}
		}
	}
	return false;
}

void Brotherhood::CharacterAdded(LPOBJ lpObj)
{
	if(!this->Enable) return; 
	if(!this->ActiveBrother(lpObj)) return;
	//Damage
	lpObj->m_AttackDamageMaxLeft += ((lpObj->m_AttackDamageMaxLeft * this->PlusDamage) / 100);
	lpObj->m_AttackDamageMinLeft += ((lpObj->m_AttackDamageMinLeft * this->PlusDamage) / 100);
	lpObj->m_AttackDamageMaxRight += ((lpObj->m_AttackDamageMaxRight * this->PlusDamage) / 100);
	lpObj->m_AttackDamageMinRight += ((lpObj->m_AttackDamageMinRight * this->PlusDamage) / 100);
	//Ignore
	lpObj->SetOpIgnoreDefense += this->PlusIgnore;
	//Double Damage
	lpObj->SetOpDoubleDamage += this->PlusDoubleDamage;
	lpObj->m_MagicDamageMin += ((gObj->m_MagicDamageMin * this->PlusDamage) / 100);
	lpObj->m_MagicDamageMax += ((gObj->m_MagicDamageMax * this->PlusDamage) / 100);
	//Defense
	lpObj->m_Defense += ((lpObj->m_Defense * this->PlusDefence) / 100);
	lpObj->m_MagicDefense += ((lpObj->m_MagicDefense * this->PlusDefence) / 100);
}

void Brotherhood::Teleport(LPOBJ lpObj, int TargetIndex)
{
	if(!this->Enable) return; 

	if(!this->ActiveBrother(lpObj)) return;

	LPOBJ lpTarget = &gObj[TargetIndex];

	if(strcmp(lpObj->Brotherhood,lpTarget->Brotherhood))
	{
		return;
	}

	if(!gTeleportManager.CheckTeleoprtMap(lpObj->m_Index, TargetIndex))
	{
		return;
	}
	if (this->TeleportActive == 0)
	{
		return;
	}
	if(gMoveCommand.CheckMainToMove(lpObj) == 0)
	{
		GCServerMsgStringSend("[Brotherhood]: No Move Map",lpObj->m_Index,1);
		return;
	}

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		GCServerMsgStringSend("[Brotherhood]: No Move Interface",lpObj->m_Index,1);
		return;
	}

	if( lpObj->MapNumber == MAP_INDEX_RAKLION_BOSS &&
		lpObj->Connected == PLAYER_PLAYING &&
		(g_Raklion.GetRaklionState() == RAKLION_STATE_CLOSE_DOOR ||
		g_Raklion.GetRaklionState() == RAKLION_STATE_ALL_USER_DIE ||
		g_Raklion.GetRaklionState() == RAKLION_STATE_NOTIFY_4 ||
		g_Raklion.GetRaklionState() == RAKLION_STATE_END) ) 
	{
		GCServerMsgStringSend("[Brotherhood]: No Move Map",lpObj->m_Index,1);
		return;
	}

	LPOBJ lpBrother = &gObj[TargetIndex];

	GCMagicAttackNumberSend(lpObj,AT_SKILL_RECALL_PARTY,lpObj->m_Index,skillSuccess);

#if(GS_CASTLE==1 || CS_SERVER)
	if(g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		if(lpBrother->m_btCsJoinSide != lpObj->m_btCsJoinSide)
		{
			return;
		}
	}
#endif

	int movelevel = gMoveCommand.GetMoveLevel(lpObj->MapNumber,lpObj->X,lpObj->Y,lpBrother->Class);
	int bCheckMainToMove = gMoveCommand.CheckMainToMove(lpBrother);
	int bCheckEquipmentToMove = gMoveCommand.CheckEquipmentToMove(lpBrother,lpObj->MapNumber);
	int bCheckInterfaceToMove = gMoveCommand.CheckInterfaceToMove(lpBrother);

	if(lpBrother->Level >= movelevel
		&& movelevel != -1
		&& bCheckMainToMove != false
		&& bCheckEquipmentToMove != false
		&& bCheckInterfaceToMove != false)
	{

		#if(BROTHER_PAYTELEPORT)
		if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::ulasevich2))
		{
			if(lpObj->GameShop.WCoinC < this->m_TeleportWCoin)
			{
				GCServerMsgStringSend("[Brotherhood]: No Teleport Wcoin",lpBrother->m_Index,1);
				return;
			}
		}
		#endif

		gObjTeleport(lpBrother->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y);
			
		//Season4 add-on
		if(lpObj->MapNumber == MAP_INDEX_RAKLION_BOSS)
		{
			g_RaklionBattleUserMng.AddUserData(lpBrother->m_Index);
		}

		GCServerMsgStringSend("[Brotherhood]: Teleport Move",lpBrother->m_Index,1);
	}
	else
	{
		GCServerMsgStringSend("[Brotherhood]: No Teleport Move",lpBrother->m_Index,1);
	}

}


void Brotherhood::UserConnect(int aIndex)
{
	if(!this->Enable)
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

	if(!strcmp(lpUser->Brotherhood,"One"))
	{
		return;
	}

	MsgNormal(aIndex,"[Brotherhood]: %s",lpUser->Brotherhood);

}

bool Brotherhood::CheckSimbol(char* String)
{
	if(String[0] == ' ')
		return false;

	for(int i(0);i<10;i++)
	{
		if(String[i] == NULL)
			continue;

		switch(String[i])
		{
		case 'a': continue ; break;
		case 'b': continue ; break;
		case 'c': continue ; break;
		case 'd': continue ; break;
		case 'e': continue ; break;
		case 'f': continue ; break;
		case 'g': continue ; break;
		case 'h': continue ; break;
		case 'i': continue ; break;
		case 'j': continue ; break;
		case 'k': continue ; break;
		case 'l': continue ; break;
		case 'm': continue ; break;
		case 'n': continue ; break;
		case 'o': continue ; break;
		case 'p': continue ; break;
		case 'q': continue ; break;
		case 'r': continue ; break;
		case 's': continue ; break;
		case 't': continue ; break;
		case 'u': continue ; break;
		case 'v': continue ; break;
		case 'w': continue ; break;
		case 'x': continue ; break;
		case 'y': continue ; break;
		case 'z': continue ; break;
		case 'A': continue ; break;
		case 'B': continue ; break;
		case 'C': continue ; break;
		case 'D': continue ; break;
		case 'E': continue ; break;
		case 'F': continue ; break;
		case 'G': continue ; break;
		case 'H': continue ; break;
		case 'I': continue ; break;
		case 'J': continue ; break;
		case 'K': continue ; break;
		case 'L': continue ; break;
		case 'M': continue ; break;
		case 'N': continue ; break;
		case 'O': continue ; break;
		case 'P': continue ; break;
		case 'Q': continue ; break;
		case 'R': continue ; break;
		case 'S': continue ; break;
		case 'T': continue ; break;
		case 'U': continue ; break;
		case 'V': continue ; break;
		case 'W': continue ; break;
		case 'X': continue ; break;
		case 'Y': continue ; break;
		case 'Z': continue ; break;
		case '0': continue ; break;
		case '1': continue ; break;
		case '2': continue ; break;
		case '3': continue ; break;
		case '4': continue ; break;
		case '5': continue ; break;
		case '6': continue ; break;
		case '7': continue ; break;
		case '8': continue ; break;
		case '9': continue ; break;
		case ' ': continue ; break;
		default: return false;
		}
	}
	return true;
}

void Brotherhood::UserAddedBrother(int aIndex, char* BrName)
{
	if(!this->Enable)
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

#ifndef BR_DEBUG

	//Проверка на состояние в партии
	if(lpUser->PartyNumber == -1)
	{
		MsgNormal(aIndex,"[Brotherhood] No Party");
		return;
	}



	if (strlen(BrName) > 10) 
	{
		MsgNormal(aIndex,"[Brotherhood] Max Len 10");
		return;
	}
#endif
	char szBrName[11] = { 0 };
	strncpy(szBrName,BrName,10);

	//Проверка на разрешенные символы
	if(this->CheckSimbol(szBrName) == false)
	{
		MsgNormal(aIndex,"[Brotherhood] Word Error");
		return;
	}

	if(strcmp(lpUser->Brotherhood,"One"))
	{
		return;
	}

	int number = 0;
	int BrCount = 0;
	int	partynum = lpUser->PartyNumber;

#ifndef BR_DEBUG

	if( !gParty.Isleader(gObj[aIndex].PartyNumber, aIndex, gObj[aIndex].DBNumber) )
	{
		MsgNormal(aIndex,"[Brotherhood] No Party Leader");
		return;
	}
	
	int PartyUserCount = gParty.GetPartyCount(partynum);

	if(PartyUserCount > 5)
	{
		MsgNormal(aIndex,"[Brotherhood] Need Max User 5");
		return;
	}

	for(int n = 0; n < MAX_USER_IN_PARTY; n++)
	{
#if _NEW_PARTY_SYSTEM_ == TRUE
		if( n >= g_MaxPartyMember)
		{
			break;
		}
#endif
		number = gParty.m_PartyS[partynum].Number[n];

		if(number >= 0 && lpUser->Connected == PLAYER_PLAYING)
		{
			LPOBJ LpBrother = &gObj[number];
			if(!strncmp(lpUser->Brotherhood,LpBrother->Brotherhood,10))
			{
				BrCount++;
			}
		}
		else
		{
			continue;
		}
	}

#if _NEW_PARTY_SYSTEM_ == TRUE
	if(5 > BrCount)
	{
		MsgNormal(aIndex,"[Brotherhood]: Brother Party %d/5",BrCount);
		return;
	}
#else
	if(MAX_USER_IN_PARTY > BrCount)
	{
		MsgNormal(aIndex,"[Brotherhood]: Brother Party %d/5",BrCount);
		return;
	}
#endif

	if(this->BuyType == 1)	//Zen
	{
		if(lpUser->Money < this->BuyCost)
		{
			MsgNormal(aIndex,"[Brotherhood]: Need %d Zen",this->BuyCost);
			return;
		}
		lpUser->Money -= this->BuyCost;
		GCMoneySend(aIndex,lpUser->Money);
	}
	else if(this->BuyType == 2)	//WcoinC
	{
		if(lpUser->GameShop.WCoinC < this->BuyCost)
		{
			MsgNormal(aIndex,"[Brotherhood]: Need %d WCoinC",this->BuyCost);
			return;
		}
		lpUser->GameShop.WCoinC -= this->BuyCost;
		gGameShop.GDSaveUserInfo(aIndex);
		ExUserDataSend(aIndex);
	}
	else if(this->BuyType == 3)	//WcoinP
	{
		if(lpUser->GameShop.WCoinP < this->BuyCost)
		{
			MsgNormal(aIndex,"[Brotherhood]: Need %d WCoinP",this->BuyCost);
			return;
		}
		lpUser->GameShop.WCoinP -= this->BuyCost;
		gGameShop.GDSaveUserInfo(aIndex);
		ExUserDataSend(aIndex);
	}
	else if(this->BuyType == 4)	//Goblin
	{
		if(lpUser->GameShop.GoblinPoint < this->BuyCost)
		{
			MsgNormal(aIndex,"[Brotherhood]: Need %d Goblin",this->BuyCost);
			return;
		}
		lpUser->GameShop.GoblinPoint -= this->BuyCost;
		gGameShop.GDSaveUserInfo(aIndex);
		ExUserDataSend(aIndex);
	}
	else if(this->BuyType == 5)	//Credits
	{
		if(lpUser->ExCred < this->BuyCost)
		{
			MsgNormal(aIndex,"[Brotherhood]: Need %d Credit",this->BuyCost);
			return;
		}
		lpUser->ExCred -= this->BuyCost;
		ExUserDataSend(aIndex);
	}

#if _NEW_PARTY_SYSTEM_ == TRUE
	for(int i=0; i< g_MaxPartyMember; i++)
#else
	for(int i=0; i < MAX_USER_IN_PARTY; i++)
#endif
	{
		number = gParty.m_PartyS[partynum].Number[i];

		if(number >= 0)
		{
			LPOBJ LpBrother = &gObj[number];
			strncpy(LpBrother->Brotherhood,szBrName,10);
			ExFireCracker(number, LpBrother->X, LpBrother->Y);
			MessageChat(number,"~[Brotherhood]: Create: %s",szBrName);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(LpBrother, number, 0);
#endif
		}
	}
	// Done
#else
			strncpy(gObj[aIndex].Brotherhood,szBrName,10);
			//ExFireCracker(aIndex, LpBrother->X, LpBrother->Y);
			MessageChat(aIndex,"~[Brotherhood]: Create: %s",szBrName);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(&gObj[aIndex], aIndex, 0);
#endif
#endif
}

void Brotherhood::UserExitBrother(int aIndex)
{
	if(!this->Enable)
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

	if(strcmp(lpUser->Brotherhood,"One"))
	{
		strcpy(lpUser->Brotherhood,"One");
#ifndef FIX_DS_CRASH
		GJSetCharacterInfo(lpUser, aIndex, 0);
#endif
		MessageChat(aIndex,"~[Brotherhood]: Exit");
		return;
	}
}


void Brotherhood::TickTime(int aIndex)
{

	if(!this->Enable)
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

	if(ActiveBrother(lpUser))
	{
		if(gObjSearchActiveEffect(lpUser, AT_BT_BROTHERHOOD_BUFF) == FALSE )
		{
			gObjApplyBuffEffectDuration(lpUser,AT_BT_BROTHERHOOD_BUFF,0,0,0,0,600);
		}
	}
	else
	{
		if(gObjSearchActiveEffect(lpUser, AT_BT_BROTHERHOOD_BUFF) == TRUE )
		{
			gObjRemoveBuffEffect(lpUser,AT_BT_BROTHERHOOD_BUFF);
		}
	}
}

bool Brotherhood::NewAddBrother(int aIndex, int TargetIndex)
{

	if(!this->Enable)
	{
		return false;
	}

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
#ifndef BR_DEBUG
	//Проверка на состояние в партии
	if(lpUser->PartyNumber == -1)
	{
		MsgNormal(aIndex,"[Brotherhood] No Party");
		return false;
	}

	if(!strcmp(lpUser->Brotherhood,"One"))
	{
		MsgNormal(aIndex,"[Brotherhood] create brother /brstart");
		return false;
	}

	int number = 0;
	int BrCount = 0;
	int	partynum = lpUser->PartyNumber;

	if( !gParty.Isleader(gObj[aIndex].PartyNumber, aIndex, gObj[aIndex].DBNumber) )
	{
		MsgNormal(aIndex,"[Brotherhood] No Party Leader");
		return false;
	}

	int PartyUserCount = gParty.GetPartyCount(partynum);

	if(PartyUserCount > 5)
	{
		MsgNormal(aIndex,"[Brotherhood] Need Max User 5");
		return false;
	}

#endif

	GD_CheckBrother Send;

	Send.h.c = 0xC1;
	Send.h.headcode = 0xE2;
	Send.h.subcode = 0x04;
	Send.h.size = sizeof(GD_CheckBrother);
	Send.aIndex = aIndex;
	Send.aTargetIndex = TargetIndex;
	//Send
	Send.BrName[MAX_ACCOUNT_LEN] = 0;
	memcpy(Send.BrName, lpUser->Brotherhood, sizeof(Send.BrName)-1);

	cDBSMng.Send((char*)&Send, sizeof(GD_CheckBrother));

}


void Brotherhood::DG_RecvBrotherCount(DG_CheckBrother* Recv)
{
	if(!this->Enable)
	{
		return;
	}

	int aIndex = Recv->aIndex;
	int aTragetIndex = Recv->aTargetIndex;
	int Count = Recv->Count;

	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	if ( OBJMAX_RANGE(aTragetIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTragetIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(lpTarget->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(Count <= 0)
	{
		MsgNormal(aIndex,"[Brotherhood] No Brother");
		return;
	}

	if(Count >= 5)
	{
		MsgNormal(aIndex,"[Brotherhood] 5/5");
		return;
	}

#ifndef BR_DEBUG

	int number = 0;
	int BrCount = 0;
	int	partynum = lpUser->PartyNumber;

	for(int n = 0; n < MAX_USER_IN_PARTY; n++)
	{
#if _NEW_PARTY_SYSTEM_ == TRUE
		if( n >= g_MaxPartyMember)
		{
			break;
		}
#endif
		number = gParty.m_PartyS[partynum].Number[n];

		if(number >= 0 && lpUser->Connected == PLAYER_PLAYING)
		{
			LPOBJ LpBrother = &gObj[number];
			if(!strncmp(lpUser->Brotherhood,LpBrother->Brotherhood,10))
			{
				BrCount++;
			}
		}
		else
		{
			continue;
		}
	}


	if(BrCount != Count)
	{
		MsgNormal(aIndex,"[Brotherhood] Need Full %d / %d for add new",BrCount,Count);
		return;
	}

#if _NEW_PARTY_SYSTEM_ == TRUE
	for(int i=0; i< g_MaxPartyMember; i++)
#else
	for(int i=0; i < MAX_USER_IN_PARTY; i++)
#endif
	{
		number = gParty.m_PartyS[partynum].Number[i];

		if(number >= 0)
		{
			LPOBJ LpBrother = &gObj[number];
			strncpy(LpBrother->Brotherhood,lpUser->Brotherhood,10);
			ExFireCracker(number, LpBrother->X, LpBrother->Y);
			MessageChat(number,"~[Brotherhood]: New: %s",lpUser->Brotherhood);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(LpBrother, number, 0);
#endif
		}
	}

#else
			strncpy(lpUser->Brotherhood,lpUser->Brotherhood,10);
			ExFireCracker(aIndex, lpUser->X, lpUser->Y);
			MessageChat(aIndex,"~[Brotherhood]: New: %s",lpUser->Brotherhood);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpUser, aIndex, 0);
#endif

#endif

}
#endif