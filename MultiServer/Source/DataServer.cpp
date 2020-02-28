#include "stdafx.h"
#include "zMultiServer.h"
#include "DataServer.h"
#include "Window.h"
#include "DataServerDB.h"
#include "winutil.h"

DS_INFO g_DSInfo;
#if(ENABLE_DATASERVER2)
DS_INFO g_DSInfo2;
#endif

void DataServerInit()
{
g_bIsServer[ST_DATASERVER] = TRUE;

	g_DSInfo.TCPPort = GetPrivateProfileInt(DS_INISECTION,"TCPPort",55960,INI_FILE);
	g_DSInfo.bCharCreate = GetPrivateProfileInt(DS_INISECTION,"CreateCharacter",1,INI_FILE);
	g_DSInfo.bResetCol = 1;//GetPrivateProfileInt(DS_INISECTION,"IsResetCol",0,INI_FILE);

	GetPrivateProfileString(DS_INISECTION,"DSN","MuOnline",g_DSInfo.dbDSN,sizeof(g_DSInfo.dbDSN),INI_FILE);
	sprintf(g_DSInfo.dbResetCol, "Resets");
	sprintf(g_DSInfo.dbGrandCol, "GrandReset");
	//GetPrivateProfileString(DS_INISECTION,"ResetCol","Resets",g_DSInfo.dbResetCol,sizeof(g_DSInfo.dbResetCol),INI_FILE);

	GetPrivateProfileString(DS_INISECTION, "CreditTable", "Character", g_DSInfo.CreditTable, sizeof(g_DSInfo.CreditTable),INI_FILE);
	GetPrivateProfileString(DS_INISECTION, "CreditColumnCredits", "Credits", g_DSInfo.CreditColumnCredits, sizeof(g_DSInfo.CreditTable),INI_FILE);
	GetPrivateProfileString(DS_INISECTION, "CreditColumnAccount", "AccountID", g_DSInfo.CreditColumnAccount, sizeof(g_DSInfo.CreditTable),INI_FILE);

	g_DataServerDB.S_TYPE = ST_DATASERVER;
	g_PartyMatchDB.S_TYPE = ST_DATASERVER;
	g_GuildMatchDB.S_TYPE = ST_DATASERVER;

	if( g_DataServerDB.Connect(3,g_DSInfo.dbDSN,SQLUser,SQLPass) == TRUE )
	{
		g_Window.LogAdd(Log::Info, "[ %s ] connection successful !",g_DSInfo.dbDSN);
	}

	if( g_PartyMatchDB.Connect(3,g_DSInfo.dbDSN,SQLUser,SQLPass) == TRUE )
	{
		g_Window.LogAdd(Log::Info, "[ %s ] Party Matching connection successful !",g_DSInfo.dbDSN);
	}

	if( g_GuildMatchDB.Connect(3,g_DSInfo.dbDSN,SQLUser,SQLPass) == TRUE )
	{
		g_Window.LogAdd(Log::Info, "[ %s ] Guild Matching connection successful !",g_DSInfo.dbDSN);
	}

	if(CreateGIocp(g_DSInfo.TCPPort,ST_DATASERVER) != TRUE)
	{
		g_Window.LogAdd(Log::Error, "Failed to start [ ST_DATASERVER ] on port [ %d ]",g_DSInfo.TCPPort);
	}
	else
	{
		g_Window.LogAdd(Log::Info, "[ DataServer ] created on port [ %d ]",g_DSInfo.TCPPort);
	}
}

#if(ENABLE_DATASERVER2)
void DataServer2Init()
{
	g_bIsServer[ST_DATASERVER2] = TRUE;

	g_DSInfo2.TCPPort = GetPrivateProfileInt(DS2_INISECTION,"TCPPort",55960,INI_FILE);
	g_DSInfo2.bCharCreate = GetPrivateProfileInt(DS2_INISECTION,"CreateCharacter",1,INI_FILE);
	//g_DSInfo2.bResetCol = 1;//GetPrivateProfileInt(DS_INISECTION,"IsResetCol",0,INI_FILE);

	GetPrivateProfileString(DS2_INISECTION,"DSN","MuOnline",g_DSInfo2.dbDSN,sizeof(g_DSInfo2.dbDSN),INI_FILE);
	sprintf(g_DSInfo2.dbResetCol, "Resets");
	//GetPrivateProfileString(DS_INISECTION,"ResetCol","Resets",g_DSInfo.dbResetCol,sizeof(g_DSInfo.dbResetCol),INI_FILE);

	GetPrivateProfileString(DS2_INISECTION, "CreditTable", "Character", g_DSInfo2.CreditTable, sizeof(g_DSInfo2.CreditTable),INI_FILE);
	GetPrivateProfileString(DS2_INISECTION, "CreditColumnCredits", "Credits", g_DSInfo2.CreditColumnCredits, sizeof(g_DSInfo2.CreditTable),INI_FILE);
	GetPrivateProfileString(DS2_INISECTION, "CreditColumnAccount", "AccountID", g_DSInfo2.CreditColumnAccount, sizeof(g_DSInfo2.CreditTable),INI_FILE);

	//g_DataServerDB.S_TYPE = ST_DATASERVER;

	if( g_DataServerDB.Connect(3,g_DSInfo2.dbDSN,SQLUser,SQLPass) == TRUE )
	{
		g_Window.LogAdd(Log::Info, "[ %s ] connection successful !",g_DSInfo2.dbDSN);
	}

	if(CreateGIocp(g_DSInfo2.TCPPort,ST_DATASERVER2) != TRUE)
	{
		g_Window.LogAdd(Log::Error, "Failed to start [ ST_DATASERVER2 ] on port [ %d ]",g_DSInfo2.TCPPort);
	}
	else
	{
		g_Window.LogAdd(Log::Info, "[ DataServer 2 ] created on port [ %d ]",g_DSInfo2.TCPPort);
	}
}
#endif

void DSProtocolCore(int aIndex, DWORD headcode, LPBYTE aRecv, int Len)
{
//	g_ServerInfoDisplayer.SetState(TRUE,gSObj[aIndex].SType);

	//g_Window.LogAdd(Log::Info, "[ DataServer ] headcode [ 0x%2X ]", headcode);

	switch( headcode )
	{
	case 0x00:
		DataServerLogin((LPSDHP_SERVERINFO)aRecv,aIndex);
		break;
	case 0x01:
		JGPGetCharList((LPSDHP_GETCHARLIST)aRecv,aIndex);
		break;
	case 0x04:
		JGCharacterCreateRequest((LPSDHP_CREATECHAR)aRecv,aIndex);
		break;
	case 0x05:
		JGCharDelRequest((LPSDHP_CHARDELETE)aRecv,aIndex);
		break;
	case 0x06:
		JGGetCharacterInfo((LPSDHP_DBCHARINFOREQUEST)aRecv,aIndex);
		break;
	case 0x07:
		GJSetCharacterInfo((LPSDHP_DBCHAR_INFOSAVE)aRecv,aIndex);
		break;
	case 0x08:
		DGGetWarehouseList((LPSDHP_GETWAREHOUSEDB)aRecv,aIndex);
		break;
	case 0x09:
		GDSetWarehouseList((LPSDHP_GETWAREHOUSEDB_SAVE)aRecv,aIndex);
		break;
	case 0x11:
		GDUserItemSave((LPSDHP_DBCHAR_ITEMSAVE)aRecv,aIndex);
		break;
	case 0x13:
		DGGetMonsterKillInfo((LPMSG_REQ_QUESTMONSTERKILLINFO)aRecv,aIndex);
		break;
	case 0x14:
		DGSaveMonsterKillInfo((LPMSG_SAVE_MONSTERKILLINFO)aRecv,aIndex);
		break;
	case 0x15:
		DGSaveQuestExInfo((PMSG_REQ_QUESTEXINFO_SAVE*)aRecv,aIndex);
		break;
	case 0x16:
		DGReqQuestExInfo((PMSG_REQ_QUESTEXINFO*)aRecv,aIndex);
		break;

	case 0x40:
		{
			PBMSG_HEAD2 * lpDef = (PBMSG_HEAD2 *)aRecv;

			switch( lpDef->subcode )
			{
			case 0x00:
				DGRequestServerInfo((PMSG_REQ_GENS_SERVERINFO*)aRecv,aIndex);
				break;
			case 0x01:
				DGRequestGensInfo((PMSG_REQ_GENS_INFO*)aRecv,aIndex);
				break;
			case 0x02:
				DGRequestJoinGens((PMSG_REQ_GENS_JOINREQUEST*)aRecv,aIndex);
				break;
			case 0x03:
				DGSaveGens((PMSG_GENS_INFOSAVE*)aRecv);
				break;
			case 0x04:
				DGRequestLeaveGens((PMSG_REQ_LEAVE_GENS*)aRecv,aIndex);
				break;
			}
		}
		break;

	case 0x30:
		JGGetMasterInfo((LPSDHP_DBMASTERINFOREQUEST)aRecv,aIndex);
		break;
	case 0x31:
		DGSaveMasterInfo((LPMSG_SAVE_MASTERINFO)aRecv,aIndex);
		break;
	case 0x52:
		ItemSerialCreateRecv((LPSDHP_ITEMCREATE)aRecv,aIndex);
		break;
	case 0x55:
		PetItemSerialCreateRecv((LPSDHP_ITEMCREATE)aRecv,aIndex);
		break;
	case 0x56:
		DGRecvPetItemInfo((LPSDHP_REQUEST_PETITEM_INFO)aRecv,aIndex);
		break;
	case 0x57:
		GDSavePetItemInfo((LPSDHP_SAVE_PETITEM_INFO)aRecv,aIndex);
		break;
	case 0x60:
		DGOptionDataRecv((LPSDHP_SKILLKEYDATA)aRecv,aIndex);
		break;
	case 0x61:
		DGMuBotOptionRecv((LPMUBOT_SETTINGS_REQ_SAVE)aRecv,aIndex);
		break;
	case 0x80:
		{
			PBMSG_HEAD2 * lpDef1 = (PBMSG_HEAD2 *)aRecv;
			switch(lpDef1->subcode)
			{
			case 0x01:
				DGAnsOwnerGuildMaster((LPCSP_REQ_OWNERGUILDMASTER)aRecv,aIndex);
				break;
			case 0x03:
				DGAnsCastleNpcBuy((LPCSP_REQ_NPCBUY)aRecv,aIndex);
				break;
			case 0x04:
				DGAnsCastleNpcRepair((LPCSP_REQ_NPCREPAIR)aRecv,aIndex);
				break;
			case 0x05:
				DGAnsCastleNpcUpgrade((LPCSP_REQ_NPCUPGRADE)aRecv,aIndex);
				break;
			case 0x06:
				DGAnsTaxInfo((LPCSP_REQ_TAXINFO)aRecv,aIndex);
				break;
			case 0x07:
				DGAnsTaxRateChange((LPCSP_REQ_TAXRATECHANGE)aRecv,aIndex);
				break;
			case 0x08:
				DGAnsCastleMoneyChange((LPCSP_REQ_MONEYCHANGE)aRecv,aIndex);
				break;
			case 0x09:
				DGAnsSiegeDateChange((LPCSP_REQ_SDEDCHANGE)aRecv,aIndex);
				break;
			case 0x0A:
				DGAnsGuildMarkRegInfo((LPCSP_REQ_GUILDREGINFO)aRecv,aIndex);
				break;
			case 0x0B:
				DGAnsSiegeEndedChange((LPCSP_REQ_SIEGEENDCHANGE)aRecv,aIndex);
				break;
			case 0x0C:
				DGAnsCastleOwnerChange((LPCSP_REQ_CASTLEOWNERCHANGE)aRecv,aIndex);
				break;
			case 0x0D:
				DGAnsRegAttackGuild((LPCSP_REQ_REGATTACKGUILD)aRecv,aIndex);
				break;
			case 0x0E:
				DGAnsRestartCastleState((LPCSP_REQ_CASTLESIEGEEND)aRecv,aIndex);
				break;
			case 0x0F:
				DGAnsMapSvrMsgMultiCast((LPCSP_REQ_MAPSVRMULTICAST)aRecv,aIndex);
				break;
			case 0x10:
				DGAnsRegGuildMark((LPCSP_REQ_GUILDREGMARK)aRecv,aIndex);
				break;
			case 0x11:
				DGAnsGuildMarkReset((LPCSP_REQ_GUILDRESETMARK)aRecv,aIndex);
				break;
			case 0x12:
				DGAnsGuildSetGiveUp((LPCSP_REQ_GUILDSETGIVEUP)aRecv,aIndex);
				break;
			case 0x16:
				DGAnsNpcRemove((LPCSP_REQ_NPCREMOVE)aRecv,aIndex);
				break;
			case 0x17:
				DGAnsCastleStateSync((LPCSP_REQ_CASTLESTATESYNC)aRecv,aIndex);
				break;
			case 0x18:
				DGAnsCastleTributeMoney((LPCSP_REQ_CASTLETRIBUTEMONEY)aRecv,aIndex);
				break;
			case 0x19:
				DGAnsResetCastleTaxInfo((LPCSP_REQ_RESETCASTLETAXINFO)aRecv,aIndex);
				break;
			case 0x1A:
				DGAnsResetSiegeGuildInfo((LPCSP_REQ_RESETSIEGEGUILDINFO)aRecv,aIndex);
				break;
			case 0x1B:
				DGAnsResetRegSiegeInfo((LPCSP_REQ_RESETREGSIEGEINFO)aRecv,aIndex);
				break;
			}
		}
		break;
	case 0x81:
		DGAnsCastleInitData((LPCSP_REQ_CSINITDATA)aRecv,aIndex);
		break;
	case 0x83:
		DGAnsAllGuildMarkRegInfo((LPCSP_REQ_ALLGUILDREGINFO)aRecv,aIndex);
		break;
	case 0x84:
		DGAnsFirstCreateNPC((LPCSP_REQ_NPCSAVEDATA)aRecv,aIndex);
		break;
	case 0x85:
		DGAnsCalcRegGuildList((LPCSP_REQ_CALCREGGUILDLIST)aRecv,aIndex);
		break;
	case 0x86:
		DGAnsCsGulidUnionInfo((LPCSP_REQ_CSGUILDUNIONINFO)aRecv,aIndex);
		break;
	case 0x87:
		DGAnsCsSaveTotalGuildInfo((LPCSP_REQ_CSSAVETOTALGUILDINFO)aRecv,aIndex);
		break;
	case 0x88:
		DGAnsCsLoadTotalGuildInfo((LPCSP_REQ_CSLOADTOTALGUILDINFO)aRecv,aIndex);
		break;
	case 0x89:
		DGAnsCastleNpcUpdate((LPCSP_REQ_NPCUPDATEDATA)aRecv,aIndex);
		break;
	case 0xB0:
		DGAnsCrywolfSync((LPCWP_REQ_CRYWOLFSYNC)aRecv,aIndex);
		break;
	case 0xB1:
		DGAnsCrywolfInfoLoad((LPCWP_REQ_CRYWOLFINFOLOAD)aRecv,aIndex);
		break;
	case 0xB2:
		DGAnsCrywolfInfoSave((LPCWP_REQ_CRYWOLFINFOSAVE)aRecv,aIndex);
		break;
	case 0xD0:
		{
			PBMSG_HEAD2 * lpMsg = (PBMSG_HEAD2 *)aRecv;

			switch ( lpMsg->subcode )
			{
			case 0x03:
				DGAnsPeriodItemInsert((LPMSG_REQ_PERIODITEM_INSERT)aRecv,aIndex);
				break;
			case 0x05:
				DGAnsPeriodItemList((LPMSG_REQ_PERIODITEM_LIST)aRecv,aIndex);
				break;
			case 0x07:
				DGAnsPeriodItemUpdate((LPMSG_REQ_PERIODITEM_UPDATE)aRecv,aIndex);
				break;
			case 0x09:
				DGAnsPeriodItemDelete((LPMSG_REQ_PERIODITEM_DELETE)aRecv,aIndex);
				break;
			}
		}
		break;
	case 0xA2:
		DGSummonerCreate((CSHOP_SET_SUMMONER_CREATE*)aRecv);
		break;
	case 0xA3:
		DGExpandRequest((LPCSHOP_SET_EXPANDINVENTORY)aRecv);
		break;
	case 0xA4:
		DGAnsErtelList((LPMSG_REQ_ERTELLIST)aRecv,aIndex);
		break;
	case 0xA5:
		DGSaveErtelList((LPMSG_SAVE_ERTELLIST)aRecv);
		break;
	case 0xA6:	//-> Custom
		{
			PBMSG_HEAD2* lpHead = (PBMSG_HEAD2*)aRecv;
			switch(lpHead->subcode)
			{
			case 0x00:
				{
					DGAchievUpdateMonsterData((AchievGDUpdateMonster*)aRecv, aIndex);
				}
				break;
			case 0x01:
				{
					DGAchievUpdateEventData((AchievGDUpdateEvent*)aRecv, aIndex);
				}
				break;
			case 0x02:
				{
					DGAchievUpdateMixData((AchievGDUpdateMix*)aRecv, aIndex);
				}
				break;
			}
		}
		break;
	case 0xEF:
		{
			PBMSG_HEAD2* lpHead = (PBMSG_HEAD2*)aRecv;
			// ----
			switch(lpHead->subcode)
			{
			case 0x00:
				DGPartyMatchRegister((LPMSG_PARTYMATCHING_REG_REQ)aRecv,aIndex);
				break;
			case 0x01:
				DGPartyMatchInfo((LPMSG_PARTYMATCHING_INFO_REQ)aRecv,aIndex);
				break;
			case 0x02:
				DGPartyMatchJoin((LPMSG_PARTYMATCHING_JOIN_REQ)aRecv,aIndex);
				break;
			case 0x03:
				DGPartyMatchWaitInfo((LPMSG_PARTYMATCHING_WAIT_REQ)aRecv,aIndex);
				break;
			case 0x04:
				DGPartyMatchReqList((PARTYMATCH_GDREQ_REQUESTLIST*)aRecv, aIndex);
				break;
			case 0x05:
				DGPartyMatchRequestAnswer((PARTYMATCH_GDREQ_REQUESTANSWER*)aRecv, aIndex);//
				break;
			case 0x06:
				DGPartyMatchCancel((LPMSG_PARTYMATCHING_CANCEL_REQ)aRecv,aIndex);
				break;
			case 0x07:
				GDPartyMatchUpdateStatus((PARTYMATCH_GDREQ_UPDATESTATUS*)aRecv);
				break;
			}
		}
		break;
	case 0xED:
		{
			PBMSG_HEAD2* lpHead = (PBMSG_HEAD2*)aRecv;
			// ----
			switch(lpHead->subcode)
			{
			case 0x00:
				g_GuildClass.GDReqOfferList(aIndex, (GUILDMATCH_GDREQ_OFFERLIST*)aRecv);
				break;
			case 0x01:
				g_GuildClass.GDReqOfferListByFilter(aIndex, (GUILDMATCH_GDREQ_OFFERLISTFILTER*)aRecv);
				break;
			case 0x02:
				g_GuildClass.GDReqOfferCreate(aIndex, (GUILDMATCH_GDREQ_OFFERCREATE*)aRecv);
				break;
			case 0x03:
				g_GuildClass.GDReqOfferDelete(aIndex, (GUILDMATCH_GDREQ_OFFERDELETE*)aRecv);
				break;
			case 0x04:
				g_GuildClass.GDReqJoinReqAdd(aIndex, (GUILDMATCH_GDREQ_JOINREQ*)aRecv);
				break;
			case 0x05:
				g_GuildClass.GDReqJoinReqDelete(aIndex, (GUILDMATCH_GDREQ_JOINREQSTATUS*)aRecv);
				break;
			case 0x06:
				g_GuildClass.GDReqJoinReqAnswer(aIndex, (GUILDMATCH_GDREQ_REQUESTANSWER*)aRecv);
				break;
			case 0x07:
				g_GuildClass.GDReqJoinReqList(aIndex, (GUILDMATCH_GDREQ_REQUESTLIST*)aRecv);
				break;
			case 0x08:
				g_GuildClass.GDReqJoinReqStatus(aIndex, (GUILDMATCH_GDREQ_JOINREQSTATUS*)aRecv);
				break;
			}
		}
		break;
	case 0xE6:
		GDReqLoadEventInvenItem(aIndex, (_tagSDHP_REQ_DBEVENT_INVEN_LOAD *)aRecv);
		break;
	case 0xE7:
		GDReqSaveEventInvenItem(aIndex, (_tagSDHP_REQ_DBEVENT_INVEN_SAVE *)aRecv);
		break;
	case 0xF1:
		GDReqLoadMuunInvenItem((SDHP_REQ_DBMUUN_INVEN_LOAD *)aRecv,aIndex);
        break;
	case 0xF2:
		GDReqSaveMuunInvenItem((_tagSDHP_REQ_DBMUUN_INVEN_SAVE *)aRecv,aIndex);
        break;
#if(DEV_ACHERON)
		case 0xF8:
			{
				PBMSG_HEAD2* lpMsg = (PBMSG_HEAD2*)aRecv;
				//PMSG_DEFAULT2 * lpMsg = reinterpret_cast<PMSG_DEFAULT2 *>(aRecv);
				
				switch ( lpMsg->subcode )
				{
					case 0x30:
						GDReqArcaBattleGuildJoin(aIndex, (_tagPMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS *)(aRecv));
						break;
					case 0x32:
						GDReqArcaBattleGuildMemberJoin(aIndex, (_tagPMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS *)(aRecv));
						break;
					case 0x34:
						GDReqArcaBattleEnter(aIndex, (_tagPMSG_REQ_ARCA_BATTLE_ENTER_DS *)(aRecv));
						break;
					case 0x38:
						GDReqArcaBattleWinGuildInfoInsert(aIndex, (_tagPMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS *)(aRecv));
						break;
					case 0x39:
						GDReqArcaBattleWinGuildInfo(aIndex, (_tagPMSG_REQ_AB_WIN_GUILD_INFO_DS *)(aRecv));
						break;
					case 0x3D:
						GDReqDeleteArcaBattleInfo(aIndex);
						break;
					case 0x3E:
						GDReqArcaBattleProcMultiCast(aIndex, (_tagPMSG_REQ_AB_PROC_INSERT_DS *)(aRecv));
						break;
					case 0x3F:
						GDReqArcaBattleProcState(aIndex, (_tagPMSG_REQ_AB_PROC_STATE_DS *)(aRecv));
						break;
					case 0x41:
						GDReqArcaBattleJoinMemberUnder(aIndex, (_tagPMSG_REQ_AB_JOIN_MEMBER_UNDER_DS *)(aRecv));
						break;
					case 0x43:
						GDReqArcaBattleJoinMemberUnderReq(aIndex, (_tagPMSG_REQ_AB_JOIN_CANCEL_DS *)(aRecv));
						break;
					case 0x45:
						GDReqArcaBattleRegisteredMemberCnt(aIndex, (_tagPMSG_REQ_AB_REG_MEMBER_CNT_DS *)(aRecv));
						break;
					case 0x47:
						GDReqRemoveAllGuildBuffMultiCast(aIndex, (_tagPMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS *)(aRecv));
						break;
					case 0x4D:
						GDReqArcaBattleMarkCnt(aIndex, (_tagPMSG_REQ_ARCA_BATTLE_MARK_CNT_DS *)aRecv);
						break;
					case 0x4F:
						GDReqArcaBattleMarkReg(aIndex, (_tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DS *)aRecv);
						break;
					case 0x51:
						GDReqArcaBattleMarkRank(aIndex, (_tagPMSG_REQ_ARCA_BATTLE_MARK_RANK_DS *)aRecv);
						break;
					case 0x53:
						GDReqArcaBattleMarkRegDel(aIndex, (_tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DEL_DS *)aRecv);
						break;
					case 0x54:
						GDReqArcaBattleIsTopRank(aIndex, (_tagPMSG_REQ_ARCA_BATTLE_IS_TOP_RANK *)aRecv);
						break;
					case 0x55:
						GDReqArcaBattleMarkRegAllDel(aIndex);
						break;
					case 0xF0:
						GDReqAcheronGuardianProcMultiCast(aIndex, (_tagPMSG_REQ_AE_PLAY_DS *)aRecv);
						break;
					case 0xFD:
						GDReqArcaBattleMarkRegSet(aIndex, (_tagPMSG_REQ_AB_MARK_REG_UPDATE_DS *)aRecv);
						break;
					case 0xFE:
						GDReqArcaBattleGuildRegInit(aIndex, (_tagPMSG_REQ_GUILD_REG_INIT *)aRecv);
						break;
					default:
						if (aRecv[4] == 0xFB)
						{
							GDReqArcaBattleAllGuildMarkCnt(aIndex);
						}
						break;
				}
			}
			break;
#endif
	case 0xFD:
		{
			PBMSG_HEAD2* lpHead = (PBMSG_HEAD2*)aRecv;
			// ----
			switch(lpHead->subcode)
			{
				case 0x04:
				DBRecvVaultInfo((LPMSG_VAULT_INFO)aRecv,aIndex);
				break;

			}
		}
		break;

	case 0xFE:
		{
			PBMSG_HEAD2* lpHead = (PBMSG_HEAD2*)aRecv;
			// ----
			switch(lpHead->subcode)
			{
			case 0:
				GD_HardcoreModeActivate((GD_HardcoreMode_Activate*)aRecv, aIndex);
				break;
			}
		}
		break;
	}
	

//	g_ServerInfoDisplayer.SetState(FALSE,gSObj[aIndex].SType);
}

void DataServerLogin(LPSDHP_SERVERINFO lpMsg,int aIndex)
{
	SDHP_RESULT pResult;

	pResult.h.size = sizeof( pResult );
	pResult.h.c = PMHC_BYTE;
	pResult.h.headcode = 0x00;

	pResult.Result = 0x01;
	pResult.ItemCount = GetItemCount(lpMsg->ServerCode / 20);

	gSObj[aIndex].ServerCode = lpMsg->ServerCode;

	if( gSObjSetInfo(aIndex, lpMsg->Port, lpMsg->Type, lpMsg->ServerName) == FALSE )
	{
		pResult.Result = 0x00;
		g_Window.ServerLogAdd(ST_DATASERVER,"Client Authentication Fail");
	}

	DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
}

void JGPGetCharList(LPSDHP_GETCHARLIST lpMsg,int aIndex)
{
	char cBUFFER[10000]={0};

	LPSDHP_CHARLISTCOUNT pCount = (LPSDHP_CHARLISTCOUNT)(cBUFFER);
	LPSDHP_CHARLIST pCL = (LPSDHP_CHARLIST)(cBUFFER + sizeof(SDHP_CHARLISTCOUNT));

	char szAccountID[MAX_IDSTRING+1];
	memcpy(szAccountID,lpMsg->Id,MAX_IDSTRING);
	szAccountID[MAX_IDSTRING] = 0;

	PMSG_ANS_SUMMONER_CREATE pMsg;
	PHeadSetB((LPBYTE)&pMsg,0x72,sizeof(pMsg));

	memcpy(pMsg.szAccount,szAccountID,MAX_IDSTRING);
	pMsg.Number = lpMsg->Number;
	pMsg.Result = GetSummonerCreate(&pMsg,szAccountID);

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));

	pCount->Number = lpMsg->Number;
	lstrcpy(pCount->AccountId,szAccountID);

	pCount->Count = GetCharList(szAccountID,pCount,pCL);

	PHeadSetW((LPBYTE)pCount, 0x01, sizeof(SDHP_CHARLISTCOUNT) + sizeof(SDHP_CHARLIST) * pCount->Count);

	DataSend(aIndex,(LPBYTE)&cBUFFER,sizeof(SDHP_CHARLISTCOUNT) + sizeof(SDHP_CHARLIST) * pCount->Count);
}



void JGCharacterCreateRequest(LPSDHP_CREATECHAR lpMsg,int aIndex)
{
	char szAccountID[MAX_IDSTRING+1];
	char szName[MAX_IDSTRING+1];

	memcpy(szAccountID, lpMsg->AccountId, MAX_IDSTRING);
	memcpy(szName, lpMsg->Name, MAX_IDSTRING);

	szAccountID[MAX_IDSTRING] = 0;
	szName[MAX_IDSTRING] = 0;

	SDHP_CREATECHARRESULT pResult;

	pResult.ClassSkin = lpMsg->ClassSkin;
	pResult.Number = lpMsg->Number;

	memcpy(pResult.AccountId,szAccountID,MAX_IDSTRING);
	memcpy(pResult.Name,szName,MAX_IDSTRING);

	memset(pResult.Equipment,0x00,sizeof(pResult.Equipment));

	if ( SQLSyntexCheck(szName) == FALSE )
	{
		pResult.Result = 0;
	}
	else
	{
		pResult.Result = CreateCharacter(szAccountID,szName,&pResult);
	}

	pResult.h.c = PMHC_BYTE;
	pResult.h.size = sizeof( pResult );
	pResult.h.headcode = 0x04;

	DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
}

void JGCharDelRequest(LPSDHP_CHARDELETE lpMsg,int aIndex)
{
	SDHP_CHARDELETERESULT pResult;

	char szAccountID[MAX_IDSTRING+1] = {0};
	char szName[MAX_IDSTRING+1] = {0};
	char szGuild[MAX_IDSTRING] = {0};

	pResult.h.c = PMHC_BYTE;
	pResult.h.size = sizeof( pResult );
	pResult.h.headcode = 0x05;

	memcpy(szAccountID,lpMsg->AccountID,MAX_IDSTRING);
	memcpy(szName,lpMsg->Name,MAX_IDSTRING);
	memcpy(szGuild,lpMsg->GuildName,sizeof(lpMsg->GuildName));

	memcpy(pResult.AccountID,szAccountID,MAX_IDSTRING);

	pResult.Number = lpMsg->Number;

	if(strlen(szAccountID) < 4 || strlen(szName) < 4)
		pResult.Result = 0;
	else
		pResult.Result = DeleteCharacter(szAccountID,szName,szGuild,lpMsg->Guild);

	DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
}

void JGGetCharacterInfo(LPSDHP_DBCHARINFOREQUEST lpMsg,int aIndex)
{
	SDHP_DBCHAR_INFORESULT pResult;

	PHeadSetW((LPBYTE)&pResult, 0x06, sizeof(pResult));

	char szAccountID[MAX_IDSTRING+1]={0};
	char szName[MAX_IDSTRING+1]={0};
	BuxConvert(lpMsg->Name, 10);

	memcpy(szAccountID, lpMsg->AccountID, MAX_IDSTRING);
	memcpy(szName, lpMsg->Name, MAX_IDSTRING);

	memcpy(pResult.AccountID, szAccountID, MAX_IDSTRING);
	memcpy(pResult.Name, szName, MAX_IDSTRING);

	pResult.Number = lpMsg->Number;

	pResult.result = GetCharacterInfo(szAccountID,szName,&pResult);

	if( pResult.result )
	{
		PartyMatchUpdateServerInfo(gSObj[aIndex].ServerCode, szName);
		
		UpdateGameIDC(szAccountID, szName);
	}

	DataSend(aIndex,(LPBYTE)&pResult,sizeof(pResult));

	if(pResult.result == TRUE)
	{
		SDHP_SKILLKEYDATA_SEND pSkillData = {0};

		pSkillData.h.c = PMHC_BYTE;
		pSkillData.h.size = sizeof( pSkillData );
		pSkillData.h.headcode = 0x60;

		memcpy(pSkillData.Name, szName, MAX_IDSTRING);
		pSkillData.aIndex = lpMsg->Number;

		if(GetOptionData(szName,&pSkillData) == TRUE)
		{
			DataSend(aIndex,(LPBYTE)&pSkillData,pSkillData.h.size);

			MUBOT_SETTINGS_SEND pMuBot = {0};
			pMuBot.h.c = PMHC_WORD;
			pMuBot.h.sizeH = SET_NUMBERH(sizeof(pMuBot));
			pMuBot.h.sizeL = SET_NUMBERL(sizeof(pMuBot));
			pMuBot.h.headcode = 0x61;

			strcpy(pMuBot.szName,szName);
			pMuBot.aIndex = lpMsg->Number;
			GetMuBotData(szName,&pMuBot);
			DataSend(aIndex,(LPBYTE)&pMuBot,sizeof(pMuBot));
		}
	}
}

void GJSetCharacterInfo(LPSDHP_DBCHAR_INFOSAVE lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1] = {0};
	memcpy(szName,lpMsg->Name,MAX_IDSTRING);

	if(strlen(szName) < 4)
		return;

	SetCharacterInfo(szName,lpMsg);
}

void DGGetWarehouseList(LPSDHP_GETWAREHOUSEDB lpMsg,int aIndex)
{
	char szAccountID[MAX_IDSTRING+1] = {0};
	memcpy(szAccountID,lpMsg->AccountID,MAX_IDSTRING);

	SDHP_GETWAREHOUSEDB_SAVE pResult;

	PHeadSetW((LPBYTE)&pResult, 0x08, sizeof(pResult));
	memcpy(pResult.AccountID, szAccountID, MAX_IDSTRING);
	pResult.aIndex = lpMsg->aIndex;

	if( GetWarehouseData(szAccountID,&pResult) == FALSE )
	{
		CreateWarehouseData(szAccountID);

		SDHP_GETWAREHOUSEDB_RESULT pMsg;

		PHeadSetB((LPBYTE)&pMsg, 0x10, sizeof(pMsg));
		pMsg.aIndex = lpMsg->aIndex;
		memcpy(pMsg.AccountID, szAccountID, 10);

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	DataSend(aIndex,(LPBYTE)&pResult,sizeof( pResult ));
}

void GDSetWarehouseList(LPSDHP_GETWAREHOUSEDB_SAVE lpMsg,int aIndex)
{
	char szAccountID[MAX_IDSTRING+1] = {0};
	memcpy(szAccountID,lpMsg->AccountID,MAX_IDSTRING);

	SetWarehouseData(szAccountID,lpMsg);
}

void GDUserItemSave(LPSDHP_DBCHAR_ITEMSAVE lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1] = {0};
	memcpy(szName,lpMsg->Name,MAX_IDSTRING);

	SetInventoryData(szName,lpMsg);
}

void ItemSerialCreateRecv(LPSDHP_ITEMCREATE lpMsg,int aIndex)
{
	SDHP_ITEMCREATERECV pResult;

	pResult.h.c = PMHC_BYTE;
	pResult.h.size = sizeof( pResult );
	pResult.h.headcode = 0x52;

	pResult.aIndex = lpMsg->aIndex;
	pResult.Dur = lpMsg->Dur;
	pResult.Level = lpMsg->Level;
	pResult.lootindex = lpMsg->lootindex;

	pResult.m_Number = GetNewSerial();
	pResult.MapNumber = lpMsg->MapNumber;
	pResult.NewOption = lpMsg->NewOption;
	pResult.Op1 = lpMsg->Op1;
	pResult.Op2 = lpMsg->Op2;
	pResult.Op3 = lpMsg->Op3;
	pResult.SetOption = lpMsg->SetOption;
	pResult.Type = lpMsg->Type;
	pResult.x = lpMsg->x;
	pResult.y = lpMsg->y;

#if (EX700==1)
	pResult.SocketBonus = lpMsg->SocketBonus;
	memcpy(pResult.SocketOptions,lpMsg->SocketOptions,5);
#endif

	DataSend(aIndex, (LPBYTE)&pResult,sizeof( pResult ) );
}

void PetItemSerialCreateRecv(LPSDHP_ITEMCREATE lpMsg,int aIndex)
{
	SDHP_ITEMCREATERECV pResult;

	pResult.h.c = PMHC_BYTE;
	pResult.h.size = sizeof( pResult );
	pResult.h.headcode = 0x52;

	pResult.aIndex = lpMsg->aIndex;
	pResult.Dur = lpMsg->Dur;
	pResult.Level = lpMsg->Level;
	pResult.lootindex = lpMsg->lootindex;

	pResult.m_Number = GetNewPet();
	pResult.MapNumber = lpMsg->MapNumber;
	pResult.NewOption = lpMsg->NewOption;
	pResult.Op1 = lpMsg->Op1;
	pResult.Op2 = lpMsg->Op2;
	pResult.Op3 = lpMsg->Op3;
	pResult.SetOption = lpMsg->SetOption;
	pResult.Type = lpMsg->Type;
	pResult.x = lpMsg->x;
	pResult.y = lpMsg->y;

#if (EX700==1)
	pResult.SocketBonus = lpMsg->SocketBonus;
	memcpy(pResult.SocketOptions,lpMsg->SocketOptions,5);
#endif

	DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
}

void DGRecvPetItemInfo(LPSDHP_REQUEST_PETITEM_INFO lpMsg,int aIndex)
{
	char szAccountID[MAX_IDSTRING+1]={0};
	memcpy(szAccountID, lpMsg->AccountID, MAX_IDSTRING);
	int lOfs1 = sizeof(SDHP_REQUEST_PETITEM_INFO);
	int lOfs2 = sizeof(SDHP_RECV_PETITEM_INFO);
	char cBUFFER[1000]={0};
	SDHP_RECV_PETITEM_INFO * pRecvPetInfoCount = (SDHP_RECV_PETITEM_INFO *)(cBUFFER);
	Request_PetItem_Info * pRequestPetInfo;
	Recv_PetItem_Info * pRecvPetInfo;

	for(int i = 0; i < lpMsg->nCount; i++)
	{
		pRequestPetInfo = (Request_PetItem_Info *)((LPBYTE)lpMsg + lOfs1);
		pRecvPetInfo = (Recv_PetItem_Info *)((LPBYTE)cBUFFER + lOfs2);

		pRecvPetInfo->nPos = pRequestPetInfo->nPos;
		pRecvPetInfo->nSerial = pRequestPetInfo->nSerial;

		GetPetInfo(pRecvPetInfo);

		pRecvPetInfoCount->nCount++;

		lOfs1+=sizeof(Request_PetItem_Info);
		lOfs2+=sizeof(Recv_PetItem_Info);
	}

	PHeadSetW((LPBYTE)pRecvPetInfoCount, 0x56, sizeof(SDHP_RECV_PETITEM_INFO) + pRecvPetInfoCount->nCount * sizeof(Recv_PetItem_Info));
	pRecvPetInfoCount->InvenType = lpMsg->InvenType;
	pRecvPetInfoCount->Number = lpMsg->Number;
	memcpy(pRecvPetInfoCount->AccountID, szAccountID, 10);

	DataSend(aIndex, (LPBYTE)cBUFFER, sizeof(SDHP_RECV_PETITEM_INFO) + pRecvPetInfoCount->nCount * sizeof(Recv_PetItem_Info));

}

void GDSavePetItemInfo(LPSDHP_SAVE_PETITEM_INFO lpMsg,int aIndex)
{
	int lOfs = sizeof(SDHP_SAVE_PETITEM_INFO);

	Save_PetItem_Info * pSavePetInfo = (Save_PetItem_Info *)((LPBYTE)lpMsg + lOfs);

	for(int i=0;i<lpMsg->nCount;i++)
	{
		SetPetInfo(&pSavePetInfo[i]);
	}
}

void DGOptionDataRecv(LPSDHP_SKILLKEYDATA lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1] = {0};
	memcpy(szName,lpMsg->Name,MAX_IDSTRING);

	SetOptionData(szName,lpMsg);
}

void DGAnsOwnerGuildMaster(LPCSP_REQ_OWNERGUILDMASTER lpMsg,int aIndex)
{
	CSP_ANS_OWNERGUILDMASTER pResult;

	pResult.h.c = PMHC_BYTE;
	pResult.h.size = sizeof( pResult );
	pResult.h.headcode = 0x80;
	pResult.h.subcode = 0x01;

	pResult.wMapSvrNum = lpMsg->wMapSvrNum;
	pResult.iIndex = lpMsg->iIndex;

	GetCastleOwner(lpMsg->wMapSvrNum,&pResult);

	DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
}

void DGAnsCastleNpcBuy(LPCSP_REQ_NPCBUY lpMsg,int aIndex)
{
	CSP_ANS_NPCBUY pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x03;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iBuyCost = lpMsg->iBuyCost;
	pMsg.iNpcIndex = lpMsg->iNpcIndex;
	pMsg.iNpcNumber = lpMsg->iNpcNumber;

	pMsg.iResult = CastleNpcBuy(lpMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCastleNpcRepair(LPCSP_REQ_NPCREPAIR lpMsg,int aIndex)
{
	CSP_ANS_NPCREPAIR pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x04;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iNpcIndex = lpMsg->iNpcIndex;
	pMsg.iNpcNumber = lpMsg->iNpcNumber;
	pMsg.iRepairCost = lpMsg->iRepairCost;

	pMsg.iResult = CastleNpcRepair(lpMsg,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCastleNpcUpgrade(LPCSP_REQ_NPCUPGRADE lpMsg,int aIndex)
{
	CSP_ANS_NPCUPGRADE pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x05;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.iNpcIndex = lpMsg->iNpcIndex;
	pMsg.iNpcNumber = lpMsg->iNpcNumber;
	pMsg.iNpcUpIndex = lpMsg->iNpcUpIndex;
	pMsg.iNpcUpType = lpMsg->iNpcUpType;
	pMsg.iNpcUpValue = lpMsg->iNpcUpValue;

	pMsg.iResult = CastleNpcUpgrade(lpMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsTaxInfo(LPCSP_REQ_TAXINFO lpMsg,int aIndex)
{
	CSP_ANS_TAXINFO pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x06;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.iResult = GetTaxInfo(lpMsg->wMapSvrNum,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsTaxRateChange(LPCSP_REQ_TAXRATECHANGE lpMsg,int aIndex)
{
	CSP_ANS_TAXRATECHANGE pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x07;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.iResult = SetTaxInfo(lpMsg,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsSiegeDateChange(LPCSP_REQ_SDEDCHANGE lpMsg,int aIndex)
{
	CSP_ANS_SDEDCHANGE pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x09;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.wStartYear = lpMsg->wStartYear;
	pMsg.btStartMonth = lpMsg->btStartMonth;
	pMsg.btStartDay = lpMsg->btStartDay;
	pMsg.wEndYear = lpMsg->wEndYear;
	pMsg.btEndMonth = lpMsg->btEndMonth;
	pMsg.btEndDay = lpMsg->btEndDay;

	pMsg.iResult = SiegeDateChange(lpMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsGuildMarkRegInfo(LPCSP_REQ_GUILDREGINFO lpMsg,int aIndex)
{
	CSP_ANS_GUILDREGINFO pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x0A;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	char szGuildName[9] = {0};
	memcpy(szGuildName,lpMsg->szGuildName,8);
	memcpy(pMsg.szGuildName,lpMsg->szGuildName,8);

	pMsg.iResult = GuildMarkRegInfo(lpMsg->wMapSvrNum,szGuildName,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsSiegeEndedChange(LPCSP_REQ_SIEGEENDCHANGE lpMsg,int aIndex)
{
	CSP_ANS_SIEGEENDCHANGE pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x0B;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.bIsSiegeEnded = lpMsg->bIsSiegeEnded;
	pMsg.iResult = SiegeEndedChange(lpMsg->wMapSvrNum,lpMsg->bIsSiegeEnded);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCastleOwnerChange(LPCSP_REQ_CASTLEOWNERCHANGE lpMsg,int aIndex)
{
	CSP_ANS_CASTLEOWNERCHANGE pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x0C;

	pMsg.bIsCastleOccupied = lpMsg->bIsCastleOccupied;

	char szOwnerGuildName[9] = {0};
	memcpy(szOwnerGuildName,lpMsg->szOwnerGuildName,0x08);
	memcpy(pMsg.szOwnerGuildName,lpMsg->szOwnerGuildName,0x08);

	pMsg.iResult = CastleOwnerChange(lpMsg->wMapSvrNum,lpMsg->bIsCastleOccupied,szOwnerGuildName);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsRegAttackGuild(LPCSP_REQ_REGATTACKGUILD lpMsg,int aIndex)
{
	CSP_ANS_REGATTACKGUILD pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x0D;
	pMsg.iResult = 0;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	char szEnemyGuildName[9] = {0};
	memcpy(szEnemyGuildName,lpMsg->szEnemyGuildName,0x08);
	memcpy(pMsg.szEnemyGuildName,lpMsg->szEnemyGuildName,0x08);

	pMsg.iResult = RegAttackGuild(lpMsg->wMapSvrNum,szEnemyGuildName);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsRestartCastleState(LPCSP_REQ_CASTLESIEGEEND lpMsg,int aIndex)
{
	CSP_ANS_CASTLESIEGEEND pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x0E;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.iResult = RestartCastleState(lpMsg->wMapSvrNum);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsMapSvrMsgMultiCast(LPCSP_REQ_MAPSVRMULTICAST lpMsg,int aIndex)
{
	CSP_ANS_MAPSVRMULTICAST pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x0F;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	memcpy(pMsg.szMsgText,lpMsg->szMsgText,sizeof(lpMsg->szMsgText));

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if( gSObj[i].Connected < 2 || 
			gSObj[i].SType != ST_DATASERVER ||
			gSObj[i].ServerCode == (WORD)-1 || 
			(gSObj[i].ServerCode / 20) != lpMsg->wMapSvrNum )
			continue;

		DataSend(i,(LPBYTE)&pMsg,pMsg.h.size);

		g_Window.ServerLogAdd(ST_DATASERVER,"[ MULTICAST ] TO SERVER[%d] MESSAGE:[%s]",
			gSObj[i].ServerCode,pMsg.szMsgText);
	}
}

void DGAnsRegGuildMark(LPCSP_REQ_GUILDREGMARK lpMsg,int aIndex)
{
	CSP_ANS_GUILDREGMARK pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x10;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iItemPos = lpMsg->iItemPos;

	char szGuildName[9] = {0};

	memcpy(szGuildName,lpMsg->szGuildName,0x08);
	memcpy(pMsg.szGuildName,lpMsg->szGuildName,0x08);

	pMsg.iResult = RegGuildMark(lpMsg->wMapSvrNum,szGuildName,&pMsg.iRegMarkCount);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsGuildMarkReset(LPCSP_REQ_GUILDRESETMARK lpMsg,int aIndex)
{
	CSP_ANS_GUILDRESETMARK pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x11;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	char szGuildName[9] = {0};
	memcpy(szGuildName,lpMsg->szGuildName,0x08);
	memcpy(pMsg.szGuildName,lpMsg->szGuildName,0x08);

	pMsg.iResult = GuildMarkReset(lpMsg->wMapSvrNum,szGuildName,&pMsg.iRegMarkCount);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsGuildSetGiveUp(LPCSP_REQ_GUILDSETGIVEUP lpMsg,int aIndex)
{
	CSP_ANS_GUILDSETGIVEUP pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x12;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.bIsGiveUp = lpMsg->bIsGiveUp;

	char szGuildName[9] = {0};

	memcpy(szGuildName,lpMsg->szGuildName,0x08);
	memcpy(pMsg.szGuildName,lpMsg->szGuildName,0x08);

	pMsg.iResult = GuildSetGiveUp(lpMsg,szGuildName,&pMsg.iRegMarkCount);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsNpcRemove(LPCSP_REQ_NPCREMOVE lpMsg, int aIndex)
{
	CSP_ANS_NPCREMOVE pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x16;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iNpcIndex = lpMsg->iNpcIndex;
	pMsg.iNpcNumber = lpMsg->iNpcNumber;

	pMsg.iResult = NpcRemove(lpMsg->wMapSvrNum,lpMsg->iNpcNumber,lpMsg->iNpcIndex);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCastleStateSync(LPCSP_REQ_CASTLESTATESYNC lpMsg, int aIndex)
{
	CSP_ANS_CASTLESTATESYNC pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x17;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iCastleState = lpMsg->iCastleState;
	pMsg.iTaxHuntZone = lpMsg->iTaxHuntZone;
	pMsg.iTaxRateChaos = lpMsg->iTaxRateChaos;
	pMsg.iTaxRateStore = lpMsg->iTaxRateStore;

	memcpy(pMsg.szOwnerGuildName,lpMsg->szOwnerGuildName,0x08);


	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if( gSObj[i].Connected < 2 || 
			gSObj[i].SType != ST_DATASERVER ||
			gSObj[i].ServerCode == (WORD)-1 || 
			(gSObj[i].ServerCode / 20) != lpMsg->wMapSvrNum)
			continue;

		DataSend(i,(LPBYTE)&pMsg,pMsg.h.size);
	}
}

void DGAnsCastleTributeMoney(LPCSP_REQ_CASTLETRIBUTEMONEY lpMsg,int aIndex)
{
	CSP_ANS_MONEYCHANGE pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x18;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iResult = FALSE;

	if(lpMsg->iCastleTributeMoney > 0)
	{
		pMsg.iResult = CastleTributeMoney(lpMsg->wMapSvrNum,lpMsg->iCastleTributeMoney,&pMsg.i64CastleMoney);
	}

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsResetCastleTaxInfo(LPCSP_REQ_RESETCASTLETAXINFO lpMsg,int aIndex)
{
	CSP_ANS_RESETCASTLETAXINFO pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x19;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iResult = ResetCastleTaxInfo(lpMsg->wMapSvrNum);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsResetSiegeGuildInfo(LPCSP_REQ_RESETSIEGEGUILDINFO lpMsg,int aIndex)
{
	CSP_ANS_RESETSIEGEGUILDINFO pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x1A;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.iResult = ResetSiegeGuildInfo(lpMsg->wMapSvrNum);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsResetRegSiegeInfo(LPCSP_REQ_RESETREGSIEGEINFO lpMsg,int aIndex)
{
	CSP_ANS_RESETREGSIEGEINFO pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x1B;
	pMsg.iResult = 0;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.iResult = ResetRegSiegeInfo(lpMsg->wMapSvrNum);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCastleInitData(LPCSP_REQ_CSINITDATA lpMsg,int aIndex)
{
	BYTE SendData[sizeof(CSP_ANS_CSINITDATA) + (sizeof(CSP_CSINITDATA) * MAX_CS_NPC)] = {0};

	LPCSP_ANS_CSINITDATA pMsg = (LPCSP_ANS_CSINITDATA)SendData;
	LPCSP_CSINITDATA pMsgBody = (LPCSP_CSINITDATA)&SendData[sizeof(CSP_ANS_CSINITDATA)];

	pMsg->h.c = 0xC2;
	pMsg->h.headcode = 0x81;
	pMsg->wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg->iCount = 0;
	pMsg->iResult = 0;

	if(GetCastleTotalInfo(lpMsg->wMapSvrNum,lpMsg->iCastleEventCycle,pMsg) == TRUE)
	{
		pMsg->iResult = TRUE;
		pMsg->iCount = GetCastleNpcInfo(lpMsg->wMapSvrNum,pMsgBody);
	}

	int size = sizeof(CSP_ANS_CSINITDATA) + (sizeof(CSP_CSINITDATA)*pMsg->iCount);
	pMsg->h.sizeH = SET_NUMBERH(size);
	pMsg->h.sizeL = SET_NUMBERL(size);

	DataSend(aIndex,(LPBYTE)SendData,size);
}

void DGAnsAllGuildMarkRegInfo(LPCSP_REQ_ALLGUILDREGINFO lpMsg,int aIndex)
{
	BYTE SendData[sizeof(CSP_ANS_ALLGUILDREGINFO) + sizeof(CSP_GUILDREGINFO) * MAX_CS_GUILDLIST] = {0};

	LPCSP_ANS_ALLGUILDREGINFO pMsg = (LPCSP_ANS_ALLGUILDREGINFO)SendData;
	LPCSP_GUILDREGINFO pMsgBody = (LPCSP_GUILDREGINFO)&SendData[sizeof(CSP_ANS_ALLGUILDREGINFO)];

	pMsg->h.c = PMHC_WORD;
	pMsg->h.headcode = 0x83;
	pMsg->iResult = TRUE;

	pMsg->iIndex = lpMsg->iIndex;
	pMsg->wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg->iCount = GetAllGuildMarkRegInfo(lpMsg->wMapSvrNum,pMsgBody);

	int size = sizeof(CSP_ANS_ALLGUILDREGINFO) + sizeof(CSP_GUILDREGINFO) * pMsg->iCount;

	pMsg->h.sizeH = SET_NUMBERH(size);
	pMsg->h.sizeL = SET_NUMBERL(size);

	DataSend(aIndex,(LPBYTE)SendData,size);
}

void DGAnsFirstCreateNPC(LPCSP_REQ_NPCSAVEDATA lpMsg,int aIndex)
{
	CSP_ANS_NPCSAVEDATA pMsg;

	LPCSP_NPCSAVEDATA pMsgBody = (LPCSP_NPCSAVEDATA)((PBYTE)lpMsg + sizeof(CSP_REQ_NPCSAVEDATA));

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x84;

	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iResult = FirstCreateNPC(lpMsg->wMapSvrNum,lpMsg->iCount,pMsgBody);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCalcRegGuildList(LPCSP_REQ_CALCREGGUILDLIST lpMsg,int aIndex)
{
	BYTE SendData[sizeof(CSP_ANS_CALCREGGUILDLIST) + sizeof(CSP_CALCREGGUILDLIST) * MAX_CS_GUILDLIST] = {0};
	
	LPCSP_ANS_CALCREGGUILDLIST pMsg = (LPCSP_ANS_CALCREGGUILDLIST)SendData;
	LPCSP_CALCREGGUILDLIST pMsgBody = (LPCSP_CALCREGGUILDLIST)&SendData[sizeof(CSP_ANS_CALCREGGUILDLIST)];

	pMsg->h.c = PMHC_WORD;
	pMsg->h.headcode = 0x85;
	pMsg->wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg->iResult = TRUE;
	pMsg->iCount = GetCalcRegGuildList(lpMsg->wMapSvrNum,pMsgBody);

	if(pMsg->iCount < 0)
	{
		pMsg->iCount = 0;
		pMsg->iResult = FALSE;
	}

	int size = sizeof(CSP_ANS_CALCREGGUILDLIST) + sizeof(CSP_CALCREGGUILDLIST) * pMsg->iCount;

	pMsg->h.sizeH = SET_NUMBERH(size);
	pMsg->h.sizeL = SET_NUMBERL(size);

	DataSend(aIndex,(PBYTE)SendData,size);
}

void DGAnsCsGulidUnionInfo(LPCSP_REQ_CSGUILDUNIONINFO lpMsg,int aIndex)
{
	BYTE SendData[sizeof(CSP_ANS_CSGUILDUNIONINFO) + sizeof(CSP_CSGUILDUNIONINFO) * MAX_CS_GUILDLIST * 3] = {0};

	LPCSP_CSGUILDUNIONINFO lpMsgBody = (LPCSP_CSGUILDUNIONINFO)((PBYTE)lpMsg + sizeof(CSP_REQ_CSGUILDUNIONINFO));

	LPCSP_ANS_CSGUILDUNIONINFO pMsg = (LPCSP_ANS_CSGUILDUNIONINFO)SendData;
	LPCSP_CSGUILDUNIONINFO pMsgBody = (LPCSP_CSGUILDUNIONINFO)&SendData[sizeof(CSP_ANS_CSGUILDUNIONINFO)];

	pMsg->h.c = 0xC2;
	pMsg->h.headcode = 0x86;
	pMsg->iResult = TRUE;
	pMsg->wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg->iCount = GetCsGuildUnionInfo(lpMsg->iCount,lpMsgBody,pMsgBody);

	int size = sizeof(CSP_ANS_CSGUILDUNIONINFO) + sizeof(CSP_CSGUILDUNIONINFO) * pMsg->iCount;

	pMsg->h.sizeH = SET_NUMBERH(size);
	pMsg->h.sizeL = SET_NUMBERL(size);

	DataSend(aIndex,(PBYTE)SendData,size);
}

void DGAnsCsSaveTotalGuildInfo(LPCSP_REQ_CSSAVETOTALGUILDINFO lpMsg,int aIndex)
{
	CSP_ANS_CSSAVETOTALGUILDINFO pMsg;
	LPCSP_CSSAVETOTALGUILDINFO lpMsgBody = (LPCSP_CSSAVETOTALGUILDINFO)((PBYTE)lpMsg+sizeof(CSP_REQ_CSSAVETOTALGUILDINFO));

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x87;

	pMsg.iResult = TRUE;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.iResult = SetSiegeGuildInfo(lpMsg->wMapSvrNum,lpMsg->iCount,lpMsgBody);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCsLoadTotalGuildInfo(LPCSP_REQ_CSLOADTOTALGUILDINFO lpMsg,int aIndex)
{
	BYTE SendData[sizeof(CSP_ANS_CSLOADTOTALGUILDINFO) + sizeof(CSP_CSLOADTOTALGUILDINFO) * MAX_CS_GUILDLIST] = {0};

	CSP_ANS_CSLOADTOTALGUILDINFO * pMsg = (CSP_ANS_CSLOADTOTALGUILDINFO*)SendData;
	CSP_CSLOADTOTALGUILDINFO * pMsgBody = (CSP_CSLOADTOTALGUILDINFO*)&SendData[sizeof(CSP_ANS_CSLOADTOTALGUILDINFO)];

	pMsg->h.c = 0xC2;
	pMsg->h.headcode = 0x88;
	pMsg->wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg->iResult = TRUE;

	pMsg->iCount = CsLoadTotalGuildInfo(lpMsg->wMapSvrNum,pMsgBody);

	if(pMsg->iCount < 0)
	{
		pMsg->iCount = 0;
		pMsg->iResult = FALSE;
	}

	int size = sizeof(CSP_ANS_CSLOADTOTALGUILDINFO) + sizeof(CSP_CSLOADTOTALGUILDINFO) * pMsg->iCount;

	pMsg->h.sizeH = SET_NUMBERH(size);
	pMsg->h.sizeL = SET_NUMBERL(size);

	DataSend(aIndex,(PBYTE)SendData,size);
}

void DGAnsCastleNpcUpdate(LPCSP_REQ_NPCUPDATEDATA lpMsg,int aIndex)
{
	CSP_ANS_NPCUPDATEDATA pMsg;

	LPCSP_NPCUPDATEDATA lpMsgBody = (LPCSP_NPCUPDATEDATA)((PBYTE)lpMsg + sizeof(CSP_REQ_NPCUPDATEDATA));

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0x89;
	pMsg.iResult = FALSE;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsg.iResult = CastleNpcUpdate(lpMsg->wMapSvrNum,lpMsg->iCount,lpMsgBody);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCrywolfSync(LPCWP_REQ_CRYWOLFSYNC lpMsg,int aIndex)
{
	CWP_ANS_CRYWOLFSYNC pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0xB0;
	pMsg.btResult = TRUE;

	pMsg.iCrywolfState = lpMsg->iCrywolfState;
	pMsg.iOccupationState = lpMsg->iOccupationState;

	for(int i = 0; i < MAX_SERVEROBJECT; i++)
	{
		if( gSObj[i].Connected < 2 || 
			gSObj[i].SType != ST_DATASERVER ||
			gSObj[i].ServerCode == (WORD)-1 || 
			(gSObj[i].ServerCode / 20) != lpMsg->wMapSvrNum)
			continue;

		DataSend(i,(LPBYTE)&pMsg,pMsg.h.size);
	}
}

void DGAnsCrywolfInfoLoad(LPCWP_REQ_CRYWOLFINFOLOAD lpMsg,int aIndex)
{
	CWP_ANS_CRYWOLFINFOLOAD pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0xB1;

	pMsg.btResult = CrywolfInfoLoad(lpMsg->wMapSvrNum,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsCrywolfInfoSave(LPCWP_REQ_CRYWOLFINFOSAVE lpMsg,int aIndex)
{
	CWP_ANS_CRYWOLFINFOSAVE pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.size = sizeof( pMsg );
	pMsg.h.headcode = 0xB2;
	
	pMsg.btResult = CrywolfInfoSave(lpMsg->wMapSvrNum,lpMsg->iOccupationState,lpMsg->iCrywolfState);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
}

void DGAnsPeriodItemInsert(LPMSG_REQ_PERIODITEM_INSERT lpMsg,int aIndex)
{
	PMSG_ANS_PERIODITEM_INSERT pMsg;

	pMsg.head.c = PMHC_BYTE;
	pMsg.head.size = sizeof( pMsg );
	pMsg.head.headcode = 0xD0;
	pMsg.head.subcode = 0x04;

	pMsg.iUserIndex = lpMsg->iUserIndex;
	pMsg.iItemPeriodDate = lpMsg->iItemPeriodDate;
	pMsg.btItemEffectType1 = lpMsg->btItemEffectType1;
	pMsg.btItemEffectType2 = lpMsg->btItemEffectType2;
	pMsg.iItemCode = lpMsg->iItemCode;

	pMsg.btResult = InsertPeriodItem(lpMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.head.size);
}

void DGAnsPeriodItemList(LPMSG_REQ_PERIODITEM_LIST lpMsg, int aIndex)
{
	char szName[MAX_IDSTRING+1] = {0};
	memcpy(szName,lpMsg->chCharacterName,MAX_IDSTRING);

	PMSG_ANS_PERIODITEM_LIST pMsg;

	pMsg.head.c = PMHC_WORD;
	pMsg.head.headcode = 0xD0;
	pMsg.head.subcode = 0x06;
	pMsg.head.sizeH = SET_NUMBERH(sizeof( pMsg ));
	pMsg.head.sizeL = SET_NUMBERL(sizeof( pMsg ));

	pMsg.btResult = FALSE;

	pMsg.iUserGuid = lpMsg->iUserGuid;
	pMsg.iUserIndex = lpMsg->iUserIndex;

	pMsg.btCount = GetPeriodItemList(lpMsg->iUserGuid,szName,&pMsg.Items[0]);

	if(pMsg.btCount <= 0)
	{
		pMsg.btResult = -1;
	}

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGAnsPeriodItemUpdate(LPMSG_REQ_PERIODITEM_UPDATE lpMsg,int aIndex)
{
	PMSG_ANS_PERIODITEM_UPDATE pMsg;

	pMsg.head.c = PMHC_BYTE;
	pMsg.head.headcode = 0xD0;
	pMsg.head.subcode = 0x08;
	pMsg.head.size = sizeof( pMsg );

	pMsg.iUserIndex = lpMsg->iUserIndex;
	pMsg.iItemCode = lpMsg->iItemCode;

	pMsg.btResult = UpdatePeriodItem(lpMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.head.size);
}

void DGAnsPeriodItemDelete(LPMSG_REQ_PERIODITEM_DELETE lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING] = {0};
	memcpy(szName,lpMsg->chCharacterName,MAX_IDSTRING);

	PMSG_ANS_PERIODITEM_DELETE pMsg;

	pMsg.head.c = PMHC_BYTE;
	pMsg.head.headcode = 0xD0;
	pMsg.head.subcode = 0x0A;
	pMsg.head.size = sizeof( pMsg );

	pMsg.iUserGuid = lpMsg->iUserGuid;
	pMsg.iUserIndex = lpMsg->iUserIndex;
	pMsg.btResult = DeletePeriodItem(lpMsg->iUserGuid,szName);

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.head.size);
}


void DGAnsCastleMoneyChange(LPCSP_REQ_MONEYCHANGE lpMsg,int aIndex)
{
	CSP_ANS_MONEYCHANGE pMsg;
	
	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.headcode = 0x80;
	pMsg.h.subcode = 0x08;
	pMsg.iResult = 0;

	pMsg.iIndex = lpMsg->iIndex;
	pMsg.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsg.iMoneyChanged = lpMsg->iMoneyChanged;

	pMsg.iResult = CastleTributeMoney(lpMsg->wMapSvrNum,lpMsg->iMoneyChanged,&pMsg.i64CastleMoney);

	DataSend(aIndex,(PBYTE)&pMsg,sizeof(pMsg));
}

void JGGetMasterInfo(LPSDHP_DBMASTERINFOREQUEST lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = 0;

	PMSG_ANS_MASTERINFO pMsg;
	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.headcode = 0x30;

	pMsg.Index = lpMsg->Index;
	memcpy(pMsg.szName,szName,MAX_IDSTRING);
	pMsg.szName[10] = 0;

	pMsg.result = GetMasterInfo(&pMsg,szName);

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGGetMonsterKillInfo(LPMSG_REQ_QUESTMONSTERKILLINFO lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = 0;

	PMSG_ANS_MONSTERKILLINFO pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.headcode = 0x14;

	pMsg.Index = lpMsg->Index;

	memcpy(pMsg.szName,szName,MAX_IDSTRING);
	pMsg.szName[10] = 0;

	if( GetMonsterKillInfo(&pMsg,szName) != TRUE )
	{
		pMsg.QuestIndex = -1;
		memset(pMsg.KillInfo,-1,sizeof(pMsg.KillInfo));
	}

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGSaveMonsterKillInfo(LPMSG_SAVE_MONSTERKILLINFO lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = 0;

	SaveMonsterKillInfo(lpMsg,szName);
}

void DGSaveMasterInfo(LPMSG_SAVE_MASTERINFO lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = 0;

	SaveMasterInfo(lpMsg,szName);
}

void DGSummonerCreate(CSHOP_SET_SUMMONER_CREATE* lpMsg)
{
	char szId[MAX_IDSTRING+1];
	memcpy(szId,lpMsg->szId,MAX_IDSTRING);
	szId[10] = 0;

	SaveSummonerCreate(szId);
}

void DGSaveQuestExInfo(PMSG_REQ_QUESTEXINFO_SAVE* lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = 0;

	UpdateQuestInfoEx(lpMsg,szName);
}

void DGReqQuestExInfo(PMSG_REQ_QUESTEXINFO* lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = 0;

	PMSG_ANS_QUESTEXINFO pMsg = {0};
	pMsg.h.c = 0xC2;
	pMsg.h.headcode = 0x16;

	pMsg.h.sizeL = SET_NUMBERL(sizeof(pMsg));
	pMsg.h.sizeH = SET_NUMBERH(sizeof(pMsg));

	strcpy(pMsg.szName,szName);
	pMsg.aIndex = lpMsg->aIndex;

	ReadQuestInfoEx(szName,&pMsg);


	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGRequestJoinGens(PMSG_REQ_GENS_JOINREQUEST* lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	char szGuildMaster[MAX_IDSTRING+1];

	memcpy(szName,lpMsg->szRequestID,MAX_IDSTRING);
	memcpy(szGuildMaster,lpMsg->szGuildMasterID,MAX_IDSTRING);

	szName[10] = '\0';
	szGuildMaster[10] = '\0';

	PMSG_ANS_GENS_JOINREQUEST pMsg = {0};
	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.headcode = 0x40;
	pMsg.h.subcode = 0x02;

	pMsg.aIndex = lpMsg->aIndex;

	JoinGens(szName,szGuildMaster,lpMsg->btGensType,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGRequestGensInfo(PMSG_REQ_GENS_INFO* lpMsg,int aIndex)
{
char szName[MAX_IDSTRING+1];

	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = '\0';

	PMSG_ANS_GENS_INFO pMsg = {0};
	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.headcode = 0x40;
	pMsg.h.subcode = 0x01;

	pMsg.aIndex = lpMsg->aIndex;

	GetGensInfo(szName,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGSaveGens(PMSG_GENS_INFOSAVE* lpMsg)
{
char szName[MAX_IDSTRING+1];

	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = '\0';

	UpdateGens(szName,lpMsg->iContribution,lpMsg->iReward);
}

void DGRequestLeaveGens(PMSG_REQ_LEAVE_GENS* lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];

	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = '\0';

	PMSG_ANS_LEAVE_GENS pMsg;
	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.headcode = 0x40;
	pMsg.h.subcode = 0x04;

	pMsg.aIndex = lpMsg->aIndex;

	LeaveGens(szName,lpMsg->btGens,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGRequestServerInfo(PMSG_REQ_GENS_SERVERINFO* lpMsg,int aIndex)
{
	PMSG_ANS_GENS_SERVERINFO pMsg;
	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.headcode = 0x40;
	pMsg.h.subcode = 0x00;

	GensServerInfo(lpMsg->btMapSvrCode,lpMsg->btUpdateDays,lpMsg->btPrizeDays,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGExpandRequest(LPCSHOP_SET_EXPANDINVENTORY lpMsg)
{
	char szName[MAX_IDSTRING+1];
	char szAccountID[MAX_IDSTRING+1];

	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[10] = '\0';

	memcpy(szAccountID,lpMsg->szAccountID,MAX_IDSTRING);
	szAccountID[10] = '\0';

	if( lpMsg->btType == 1 )
	{
		ExpandWarehouse(szAccountID,lpMsg->btCount);
	}
	else if( lpMsg->btType == 2 )
	{
		ExpandInventory(szAccountID,szName,lpMsg->btCount);
	}
	else
	{
		g_Window.ServerLogAdd(ST_DATASERVER,"[ExpandRequest] Invalid request type: %d",lpMsg->btType);
	}
}

void DGMuBotOptionRecv(LPMUBOT_SETTINGS_REQ_SAVE lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[MAX_IDSTRING] = '\0';

	MuBotSaveOption(szName,lpMsg);
}

void DGAnsErtelList(LPMSG_REQ_ERTELLIST lpMsg,int aIndex)
{
	char szName[MAX_IDSTRING+1];
	char szAccount[MAX_IDSTRING+1];

	memcpy(szAccount,lpMsg->szAccount,MAX_IDSTRING);
	szAccount[MAX_IDSTRING] = '\0';

	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[MAX_IDSTRING] = '\0';

	PMSG_ANS_ERTELLIST pMsg;
	pMsg.h.c = 0xC2;
	pMsg.h.sizeH = SET_NUMBERH(sizeof(pMsg));
	pMsg.h.sizeL = SET_NUMBERL(sizeof(pMsg));
	pMsg.h.headcode = 0xA4;

	pMsg.aIndex = lpMsg->aIndex;
	memcpy(pMsg.szName,szName,10);

	GetErtelList(szAccount,szName,&pMsg);

	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void DGSaveErtelList(LPMSG_SAVE_ERTELLIST lpMsg)
{
	char szName[MAX_IDSTRING+1];
	char szAccount[MAX_IDSTRING+1];

	memcpy(szAccount,lpMsg->szAccount,MAX_IDSTRING);
	szAccount[MAX_IDSTRING] = '\0';

	memcpy(szName,lpMsg->szName,MAX_IDSTRING);
	szName[MAX_IDSTRING] = '\0';

	SaveErtelList(szAccount,szName,lpMsg);
}

void DGAchievUpdateMonsterData(AchievGDUpdateMonster* lpData, int aIndex)
{
	char UserName[MAX_IDSTRING+1];
	memcpy(UserName, lpData->Name, MAX_IDSTRING);
	UserName[MAX_IDSTRING] = '\0';
	AchievUpdateMonsterData(0, lpData->MonsterID, UserName);
	AchievUpdateMonsterData(1, lpData->MonsterID, UserName);
}

void DGAchievUpdateEventData(AchievGDUpdateEvent* lpData, int aIndex)
{
	char UserName[MAX_IDSTRING+1];
	memcpy(UserName, lpData->Name, MAX_IDSTRING);
	UserName[MAX_IDSTRING] = '\0';
	AchievUpdateEventData(0, UserName, lpData);
	AchievUpdateEventData(1, UserName, lpData);
}

void DGAchievUpdateMixData(AchievGDUpdateMix* lpData, int aIndex)
{
	char UserName[MAX_IDSTRING+1];
	memcpy(UserName, lpData->Name, MAX_IDSTRING);
	UserName[MAX_IDSTRING] = '\0';
	AchievUpdateMixData(0, UserName, lpData->Success);
	AchievUpdateMixData(1, UserName, lpData->Success);
}

void DBRecvVaultInfo(LPMSG_VAULT_INFO lpMsg,int aIndex)
{
	char sql[256] = { 0 };

	char UserName[MAX_IDSTRING+1];
	memcpy(UserName, lpMsg->chAccountID, MAX_IDSTRING);
	UserName[MAX_IDSTRING] = '\0';

	wsprintfA(sql, "EXEC WarehouseChange '%d', '%s'", lpMsg->VaultID, UserName);

	if( g_DataServerDB.Exec(sql) == FALSE )
	{
		g_DataServerDB.Clear();
		return;
	}

	g_DataServerDB.Clear();
	g_Window.LogAdd(Log::Info, "Set Warehouse Number (%d) : [%s]",lpMsg->VaultID, lpMsg->chAccountID);

	PMSG_VAULT_RESULT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.size = sizeof(pMsg);
	pMsg.h.headcode = 0xFD;
	pMsg.h.subcode = 0x04;

	pMsg.aIndex = lpMsg->aIndex;
	pMsg.Result = FALSE;

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);

}

void GD_HardcoreModeActivate(GD_HardcoreMode_Activate* lpData, int aIndex)
{
	g_Window.LogAdd(Log::Debug, "Hardcore status: %d", lpData->Status);
	g_CustomHardcoreMode = lpData->Status;
	g_CustomHardcoreDefaultLife = lpData->LifeCount;
}


//void GDReqLoadMuunInvenItem(SDHP_REQ_DBMUUN_INVEN_LOAD* lpMsg,int aIndex)// OK
//{
//	char szQuery[256];
//
//	SDHP_MUUN_INVENTORY_SEND pMsg;
//
//	//pMsg.h.(0x27,0x00,sizeof(pMsg));
//	pMsg.h.c = 0xF1;
//	pMsg.h.headcode = 0x00;
//	pMsg.h.size = sizeof(pMsg);
//	pMsg.index = lpMsg->aIndex;
//
//	memcpy(pMsg.AccountID,lpMsg->AccountID,sizeof(pMsg.AccountID));
//
//	memcpy(pMsg.Name,lpMsg->Name,sizeof(pMsg.Name));
//
//	sprintf(szQuery,"SELECT Items FROM MuunInventory WHERE Name='%s'",lpMsg->Name);
//
//	if( g_DataServerDB.ReadBlob(szQuery,pMsg.dbInventory) <= 0)
//	{
//	    g_DataServerDB.Clear();
//		
//		memset(pMsg.dbInventory,0xFF,sizeof(pMsg.dbInventory));
//	}
//}
//
//void GDReqSaveMuunInvenItem(_tagSDHP_REQ_DBMUUN_INVEN_SAVE* lpMsg, int aIndex) // OK
//{
//	char szQuery[256];
//	sprintf(szQuery,"SELECT Name FROM MuunInventory WHERE Name = '%s'",lpMsg->Name);
//
//	if(g_DataServerDB.Exec(szQuery) == FALSE || g_DataServerDB.Fetch() == SQL_NO_DATA)
//	{
//		g_DataServerDB.Clear();
//		sprintf(szQuery,"INSERT INTO MuunInventory  (Name,Items) VALUES ('%s',?)",lpMsg->Name);
//
//		g_DataServerDB.Exec(szQuery);
//		g_DataServerDB.Clear();
//		return;
//	}
//	else
//	{
//		g_DataServerDB.Clear();
//		sprintf(szQuery,"UPDATE MuunInventory SET Items=? WHERE Name='%s'",lpMsg->Name);
//	    g_DataServerDB.WriteBlob(szQuery,lpMsg->dbInventory,sizeof(lpMsg->dbInventory));
//		g_DataServerDB.Exec(szQuery);
//	}
//
//	g_DataServerDB.Clear();
//}



void GDReqLoadMuunInvenItem(SDHP_REQ_DBMUUN_INVEN_LOAD* lpMsg, int aIndex)
{
	char szQuery[256];

	_tagSDHP_ANS_DBMUUN_INVEN_LOAD pMsg;
	PHeadSetW((LPBYTE)&pMsg, 0xF1, sizeof(pMsg));
	pMsg.aIndex = lpMsg->aIndex;

	sprintf(szQuery,"SELECT * FROM MuunInventory WHERE Name='%s'",lpMsg->Name);

	if(g_DataServerDB.Exec(szQuery) == FALSE || g_DataServerDB.Fetch() == SQL_NO_DATA)
	{
		g_DataServerDB.Clear();
		sprintf(szQuery,"INSERT INTO MuunInventory (Name) VALUES ('%s')",lpMsg->Name);
		g_DataServerDB.Exec(szQuery);
		g_DataServerDB.Clear();
		memset(pMsg.dbItems, 0xFF, sizeof(pMsg.dbItems));
		sprintf(szQuery, "UPDATE MuunInventory SET Items=? WHERE Name='%s'", lpMsg->Name);
		g_DataServerDB.WriteBlob(szQuery, pMsg.dbItems, sizeof(pMsg.dbItems));
	}
	else
	{
		g_DataServerDB.Clear();
		sprintf(szQuery, "SELECT Items FROM MuunInventory WHERE Name = '%s'", lpMsg->Name);
		g_DataServerDB.ReadBlob(szQuery,pMsg.dbItems);
	    g_DataServerDB.Clear();
	}
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void GDReqSaveMuunInvenItem(_tagSDHP_REQ_DBMUUN_INVEN_SAVE * aRecv, int aIndex)
{
	// 11 simbol
	char szQuery[256];
	wsprintf(szQuery, "UPDATE MuunInventory SET Items=? WHERE Name='%s'", aRecv->Name);
	g_DataServerDB.WriteBlob(szQuery, aRecv->dbInventory, sizeof(aRecv->dbInventory));
}

void GDReqLoadEventInvenItem(int aIndex, _tagSDHP_REQ_DBEVENT_INVEN_LOAD * aRecv)
{
	_tagSDHP_ANS_DBEVENT_INVEN_LOAD pMsg;
	PHeadSetW((LPBYTE)&pMsg, 0xE6, sizeof(pMsg));
	pMsg.aIndex = aRecv->aIndex;

	char szQuery[512];
	sprintf(szQuery,"SELECT * FROM EventInventory WHERE Name='%s'",aRecv->Name);

	if(g_DataServerDB.Exec(szQuery) == FALSE || g_DataServerDB.Fetch() == SQL_NO_DATA)
	{
		g_DataServerDB.Clear();
		sprintf(szQuery,"INSERT INTO EventInventory (Name) VALUES ('%s')", aRecv->Name);
		g_DataServerDB.Exec(szQuery);
		g_DataServerDB.Clear();
		memset(pMsg.dbItems, 0xFF, sizeof(pMsg.dbItems));
		sprintf(szQuery, "UPDATE EventInventory SET Items=? WHERE Name = '%s'", aRecv->Name);
		g_DataServerDB.WriteBlob(szQuery, pMsg.dbItems, sizeof(pMsg.dbItems));
	}
	else
	{
		g_DataServerDB.Clear();
		sprintf(szQuery, "SELECT Items FROM EventInventory WHERE Name = '%s'", aRecv->Name);
		g_DataServerDB.ReadBlob(szQuery, pMsg.dbItems);
	}

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void GDReqSaveEventInvenItem(int aIndex, _tagSDHP_REQ_DBEVENT_INVEN_SAVE * aRecv)
{
	char szQuery[512];
	wsprintf(szQuery, "UPDATE EventInventory SET Items=? WHERE Name = '%s'", aRecv->Name);
	g_DataServerDB.WriteBlob(szQuery, aRecv->dbInventory, sizeof(aRecv->dbInventory));
}

#if(DEV_ACHERON)

void GDReqArcaBattleGuildJoin(int aIndex, _tagPMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS * aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x31, sizeof(pMsg));

	sprintf(szQuery, "EXEC IGC_ArcaBattleGuildInsert '%s', '%s', %d", aRecv->szGuildName, aRecv->szGuildMaster, aRecv->dwGuild);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();

	pMsg.btResult = g_DataServerDB.GetInt(0);
	pMsg.wNumber = aRecv->wNumber;

	g_DataServerDB.Clear();
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void GDReqArcaBattleGuildMemberJoin(int aIndex, _tagPMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x33, sizeof(pMsg));

	sprintf(szQuery, "EXEC IGC_ArcaBattleGuildMemberInsert '%s', '%s', %d", aRecv->szGuildName, aRecv->szCharName, aRecv->dwGuild);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();

	pMsg.btResult = g_DataServerDB.GetInt(0);
	pMsg.wNumber = aRecv->wNumber;

	g_DataServerDB.Clear();
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void GDReqArcaBattleEnter(int aIndex, _tagPMSG_REQ_ARCA_BATTLE_ENTER_DS *aRecv)
{
	char szQuery[256];
	_tagPMSG_ANS_ARCA_BATTLE_ENTER_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x35, sizeof(pMsg));

	sprintf(szQuery,"EXEC IGC_ArcaBattleMemberSelect '%s'", aRecv->szCharName);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();

	pMsg.btResult = g_DataServerDB.GetInt(0);
	pMsg.wNumber = aRecv->wNumber;
	pMsg.btEnterSeq = aRecv->btEnterSeq;

	g_DataServerDB.Clear();
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void GDReqArcaBattleWinGuildInfoInsert(int aIndex, _tagPMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x3A, sizeof(pMsg));

	for (int i = 0; i < aRecv->btGuildCnt; i++)
	{
		sprintf(szQuery,"EXEC IGC_ArcaBattleWinGuildInsert '%s', %d, %d, %d, %I64d", 
			aRecv->m_stABWinGuildInfoDS[i].szGuildName, aRecv->m_stABWinGuildInfoDS[i].dwGuild, 
			aRecv->m_stABWinGuildInfoDS[i].wOccupyObelisk, aRecv->m_stABWinGuildInfoDS[i].wObeliskGroup, 0);

		g_DataServerDB.Exec(szQuery);
		g_DataServerDB.Fetch();
		g_DataServerDB.Clear();
	}
	
	for (int i = 0; i < aRecv->btGuildCnt; i++)
	{
		pMsg.m_stABWinGuildInfoDS[i].dwGuild = aRecv->m_stABWinGuildInfoDS[i].dwGuild;
		pMsg.m_stABWinGuildInfoDS[i].wObeliskGroup = aRecv->m_stABWinGuildInfoDS[i].wObeliskGroup;
		pMsg.m_stABWinGuildInfoDS[i].wOccupyObelisk = aRecv->m_stABWinGuildInfoDS[i].wOccupyObelisk;
		memcpy(pMsg.m_stABWinGuildInfoDS[i].szGuildName, aRecv->m_stABWinGuildInfoDS[i].szGuildName, MAX_GUILD_LEN+1);
	}

	pMsg.btGuildCnt = aRecv->btGuildCnt;

	for(int i=0;i<MAX_SERVEROBJECT;i++)
	{
		if(gSObj[i].ServerCode != -1 
			&& gSObj[i].SType == gSObj[aIndex].SType
			&& (gSObj[i].ServerCode / 20) == aRecv->wMapSvrNum)
		{
			DataSend(i,(PBYTE)&pMsg,sizeof(pMsg));
		}
	}
}

void GDReqArcaBattleWinGuildInfo(int aIndex, _tagPMSG_REQ_AB_WIN_GUILD_INFO_DS *aRecv)
{
	_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x3A, sizeof(pMsg));
	pMsg.btGuildCnt = 0;

	g_DataServerDB.Exec("EXEC IGC_ArcaBattleWinGuildSelect");

	while ( g_DataServerDB.Fetch() == SQL_SUCCESS )
	{
		g_DataServerDB.GetStr("G_Name", pMsg.m_stABWinGuildInfoDS[pMsg.btGuildCnt].szGuildName);
		pMsg.m_stABWinGuildInfoDS[pMsg.btGuildCnt].dwGuild = g_DataServerDB.GetInt("G_Number");
		pMsg.m_stABWinGuildInfoDS[pMsg.btGuildCnt].wOccupyObelisk = g_DataServerDB.GetInt("OuccupyObelisk");
		pMsg.m_stABWinGuildInfoDS[pMsg.btGuildCnt].wObeliskGroup = g_DataServerDB.GetInt("ObeliskGroup");
		pMsg.btGuildCnt++;

		if(pMsg.btGuildCnt >= 5)
		{
			break;
		}
	}

	g_DataServerDB.Clear();
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void GDReqDeleteArcaBattleInfo(int aIndex)
{
	g_DataServerDB.Exec("EXEC IGC_ArcaBattleInfoDelete");
	g_DataServerDB.Fetch();
	g_DataServerDB.Clear();
}

void GDReqArcaBattleProcMultiCast(int aIndex, _tagPMSG_REQ_AB_PROC_INSERT_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_AB_PROC_STATE_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x40, sizeof(pMsg));

	sprintf(szQuery, "EXEC IGC_ArcaBattleProcInsert %d", aRecv->btProcState);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();
	g_DataServerDB.Clear();

	pMsg.btProcState = aRecv->btProcState;

	for(int i=0;i<MAX_SERVEROBJECT;i++)
	{
		if(gSObj[i].ServerCode != -1 
			&& gSObj[i].SType == gSObj[aIndex].SType
			&& (gSObj[i].ServerCode / 20) == aRecv->wMapSvrNum)
		{
			DataSend(i,(PBYTE)&pMsg,sizeof(pMsg));
		}
	}
}

void GDReqArcaBattleProcState(int aIndex, _tagPMSG_REQ_AB_PROC_STATE_DS *aRecv)
{
	_tagPMSG_ANS_AB_PROC_STATE_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x40, sizeof(pMsg));

	g_DataServerDB.Exec("EXEC IGC_ArcaBattleProcSelect");
	g_DataServerDB.Fetch();

	pMsg.btProcState = g_DataServerDB.GetInt(0);
	g_DataServerDB.Clear();

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void GDReqArcaBattleJoinMemberUnder(int aIndex, _tagPMSG_REQ_AB_JOIN_MEMBER_UNDER_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_AB_JOIN_MEMBER_UNDER_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x42, sizeof(pMsg));
	pMsg.btGuildCnt = 0;

	g_DataServerDB.Exec("EXEC IGC_ArcaBattleGuildNamesSelect");
	int iGuildNamesCnt = 0;

	while (g_DataServerDB.Fetch() == SQL_SUCCESS)
	{
		g_DataServerDB.GetStr("G_Name", pMsg.GuildMemberCnt[iGuildNamesCnt].szGuildNames);
		iGuildNamesCnt++;

		if(iGuildNamesCnt >= 6)
		{
			break;
		}
	}

	g_DataServerDB.Clear();

	for(int i = 0; i < iGuildNamesCnt; i++)
	{
		sprintf(szQuery, "EXEC IGC_ArcaBattleMemberUnderSelect '%s'", pMsg.GuildMemberCnt[i].szGuildNames);
		g_DataServerDB.Exec(szQuery);
		g_DataServerDB.Fetch();
		
		pMsg.GuildMemberCnt[i].btGuildMemberCnt = g_DataServerDB.GetInt(0);
		g_DataServerDB.Clear();
	}

	pMsg.btGuildCnt = iGuildNamesCnt;

	for(int i=0;i<MAX_SERVEROBJECT;i++)
	{
		if(gSObj[i].ServerCode != -1 
			&& gSObj[i].SType == gSObj[aIndex].SType
			&& (gSObj[i].ServerCode / 20) == aRecv->wMapSvrNum)
		{
			DataSend(i,(PBYTE)&pMsg,sizeof(pMsg));
		}
	}
}

void GDReqArcaBattleJoinMemberUnderReq(int aIndex, _tagPMSG_REQ_AB_JOIN_CANCEL_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_AB_JOIN_CANCEL_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x44, sizeof(pMsg));
	pMsg.btGuildCnt = 0;

	g_DataServerDB.Exec("EXEC IGC_ArcaBattleGuildNamesSelect");
	int iGuildNamesCnt = 0;
	char szGuildNames[6][MAX_GUILD_LEN+1];

	while (g_DataServerDB.Fetch() == SQL_SUCCESS)
	{
		g_DataServerDB.GetStr("G_Name", szGuildNames[iGuildNamesCnt]);
		iGuildNamesCnt++;

		if(iGuildNamesCnt >= 6)
		{
			break;
		}
	}

	g_DataServerDB.Clear();

	for(int i = 0; i < iGuildNamesCnt; i++)
	{
		sprintf(szQuery, "EXEC IGC_ArcaBattleMinGuildSelect '%s', %d", szGuildNames[i], aRecv->btMinGuildMemNum);
		g_DataServerDB.Exec(szQuery);
		g_DataServerDB.Fetch();

		int iResult = g_DataServerDB.GetInt(0);

		if (iResult < 0)
		{
			memcpy(pMsg.CancelGuildNames[pMsg.btGuildCnt].szGuildNames, szGuildNames[i], MAX_GUILD_LEN+1);
			pMsg.btGuildCnt++;
		}

		g_DataServerDB.Clear();
	}

	for(int i = 0; i < pMsg.btGuildCnt; i++)
	{
		sprintf(szQuery, "EXEC IGC_ArcaBattleMinGuildDelete '%s'", pMsg.CancelGuildNames[i].szGuildNames);
		g_DataServerDB.Exec(szQuery);
		g_DataServerDB.Fetch();
		g_DataServerDB.Clear();
	}

	for(int i=0;i<MAX_SERVEROBJECT;i++)
	{
		if(gSObj[i].ServerCode != -1 
			&& gSObj[i].SType == gSObj[aIndex].SType
			&& (gSObj[i].ServerCode / 20) == aRecv->wMapSvrNum)
		{
			DataSend(i,(PBYTE)&pMsg,sizeof(pMsg));
		}
	}
}

void GDReqArcaBattleRegisteredMemberCnt(int aIndex, _tagPMSG_REQ_AB_REG_MEMBER_CNT_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_AB_REG_MEMBER_CNT_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x46, sizeof(pMsg));

	sprintf(szQuery, "EXEC IGC_ArcaBattleGuildMemberSelect %d", aRecv->iGuildNumber);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();

	pMsg.btRegMemCnt = g_DataServerDB.GetInt(0);
	pMsg.wNumber = aRecv->iIndex;

	g_DataServerDB.Clear();
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void GDReqRemoveAllGuildBuffMultiCast(int aIndex, _tagPMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS *aRecv)
{
	_tagPMSG_ANS_REMOVE_ALL_GUILD_BUFF_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x48, sizeof(pMsg));

	for(int i=0;i<MAX_SERVEROBJECT;i++)
	{
		if(gSObj[i].ServerCode != -1 
			&& gSObj[i].SType == gSObj[aIndex].SType
			&& (gSObj[i].ServerCode / 20) == aRecv->wMapSvrNum)
		{
			DataSend(i,(PBYTE)&pMsg,sizeof(pMsg));
		}
	}
}

void GDReqArcaBattleMarkCnt(int aIndex, _tagPMSG_REQ_ARCA_BATTLE_MARK_CNT_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_ARCA_BATTLE_MARK_CNT_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x4E, sizeof(pMsg));

	sprintf(szQuery, "EXEC IGC_ArcaBattleMarkCntSelect %d", aRecv->dwGuildNum);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();

	int iResult = g_DataServerDB.GetInt(0);

	if (iResult < 0)
	{
		pMsg.dwMarkCnt = 0;
		pMsg.btResult = 1;
	}

	else
	{
		pMsg.dwMarkCnt = iResult;
		pMsg.btResult = 0;
	}

	pMsg.wNumber = aRecv->wNumber;
	g_DataServerDB.Clear();

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void GDReqArcaBattleMarkReg(int aIndex, _tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_ARCA_BATTLE_MARK_REG_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x50, sizeof(pMsg));

	sprintf(szQuery, "EXEC IGC_ArcaBattleMarkInsert '%s', %d, '%s', %I64d", aRecv->szGuildName, aRecv->dwGuildNum, aRecv->szGuildMaster, (INT64)aRecv->dwMarkCnt);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();

	int iResult = g_DataServerDB.GetInt(0);
	g_DataServerDB.Clear();

	if (iResult == 0)
	{
		g_Window.LogAdd(Log::Info, "[ArcaBattle] Error GDReqArcaBattleMarkReg() GuildName[%s] GuildNum[%d] GuildMaster[%s] MarkCnt[%d]",
			aRecv->szGuildName, aRecv->dwGuildNum, aRecv->szGuildMaster, aRecv->dwMarkCnt);

		pMsg.wNumber = aRecv->wNumber;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		return;
	}
}

void GDReqArcaBattleMarkRank(int aIndex, _tagPMSG_REQ_ARCA_BATTLE_MARK_RANK_DS *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x52, sizeof(pMsg));

	g_DataServerDB.Exec("EXEC IGC_ArcaBattleTopRankSelect");
	pMsg.btGuildCnt = 0;

	while (g_DataServerDB.Fetch() == SQL_SUCCESS)
	{
		pMsg.ArcaBattleMarkTopRank[pMsg.btGuildCnt].btRank = pMsg.btGuildCnt + 1;
		g_DataServerDB.GetStr("G_Name", pMsg.ArcaBattleMarkTopRank[pMsg.btGuildCnt].szGuildNames);
		pMsg.ArcaBattleMarkTopRank[pMsg.btGuildCnt].dwMarkCnt = g_DataServerDB.GetInt("MarkCnt");
		pMsg.btGuildCnt++;

		if (pMsg.btGuildCnt >= 6)
		{
			break;
		}
	}

	g_DataServerDB.Clear();
	sprintf(szQuery, "EXEC IGC_ArcaBattleMarkRankSelect %d", aRecv->dwGuildNum);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();

	int iResult = g_DataServerDB.GetInt(0);

	if (iResult == 0 || pMsg.btGuildCnt == 0)
	{
		pMsg.btRank = 0;
		pMsg.dwMarkCnt = 0;
		pMsg.btGuildCnt = 0;
		pMsg.wNumber = aRecv->wNumber;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}

	else
	{
		pMsg.btRank = iResult;
		pMsg.dwMarkCnt = g_DataServerDB.GetInt(1);
		pMsg.wNumber = aRecv->wNumber;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}

	g_DataServerDB.Clear();
}

void GDReqArcaBattleMarkRegDel(int aIndex, _tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DEL_DS *aRecv)
{
	char szQuery[256];
	sprintf(szQuery, "EXEC IGC_ArcaBattleMarkRegDel %d", aRecv->dwGuildNum);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();
	g_DataServerDB.Clear();
}

void GDReqArcaBattleIsTopRank(int aIndex, _tagPMSG_REQ_ARCA_BATTLE_IS_TOP_RANK *aRecv)
{
	char szQuery[256];

	_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0x2B, sizeof(pMsg));

	sprintf(szQuery, "EXEC IGC_ArcaBattleMarkRankSelect %d", aRecv->dwGuildNum);
	g_DataServerDB.Exec(szQuery);
	g_DataServerDB.Fetch();
	int iRank = g_DataServerDB.GetInt(0);

	if (iRank <= 0 || iRank > 6)
	{
		pMsg.btResult = 6;
	}

	else
	{
		pMsg.btResult = 0;
	}

	g_DataServerDB.Clear();
	pMsg.wNumber = aRecv->wNumber;

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}

void GDReqArcaBattleMarkRegAllDel(int aIndex)
{
	g_DataServerDB.Exec("EXEC IGC_ArcaBattleGuildMarkInfoAllDel");
	g_DataServerDB.Fetch();
	g_DataServerDB.Clear();
}

void GDReqArcaBattleAllGuildMarkCnt(int aIndex)
{
	_tagPMSG_ANS_ALL_GUILD_MARK_CNT_DS pMsg;

	PHeadSubSetW((LPBYTE)&pMsg, 0xF8, 0xFC, sizeof(pMsg));

	g_DataServerDB.Exec("EXEC IGC_ArcaBattleAllMarkCntSelect");
	pMsg.wGuildCnt = 0;

	while (g_DataServerDB.Fetch() == SQL_SUCCESS)
	{
		g_DataServerDB.GetStr("G_Name", pMsg.ABAllGuildMark[pMsg.wGuildCnt].szGuildName);
		pMsg.ABAllGuildMark[pMsg.wGuildCnt].dwMarkCnt = g_DataServerDB.GetInt("MarkCnt");
		pMsg.wGuildCnt++;

		if(pMsg.wGuildCnt >= 250)
		{
			break;
		}
	}

	g_DataServerDB.Clear();
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void GDReqArcaBattleMarkRegSet(int aIndex, _tagPMSG_REQ_AB_MARK_REG_UPDATE_DS *aRecv)
{
	char szQuery[256];
	sprintf(szQuery, "UPDATE IGC_ARCA_BATTLE_GUILDMARK_REG SET MarkCnt = %d WHERE G_Number = %d", aRecv->dwMarkCnt, aRecv->dwGuildNum);
	g_DataServerDB.Exec(szQuery);
}

void GDReqArcaBattleGuildRegInit(int aIndex, _tagPMSG_REQ_GUILD_REG_INIT *aRecv)
{
	g_DataServerDB.Exec("DELETE IGC_ARCA_BATTLE_MEMBER_JOIN_INFO");
	g_DataServerDB.Exec("DELETE IGC_ARCA_BATTLE_GUILD_JOIN_INFO");
	g_DataServerDB.Exec("DELETE IGC_ARCA_BATTLE_GUILDMARK_REG");
}

void GDReqArcaBattleAllJoinUser(int aIndex, _tagPMSG_REQ_AB_ALL_JOIN_USER_DS *aRecv)
{
	_tagPMSG_ANS_AB_ALL_JOIN_USER_DS pMsg;

	PHeadSetW((LPBYTE)&pMsg, 0xE5, sizeof(pMsg));

	g_DataServerDB.Exec("EXEC IGC_ArcaBattleAllJoinUserSelect");
	pMsg.btUserCnt = 0;

	while (g_DataServerDB.Fetch() == SQL_SUCCESS)
	{
		g_DataServerDB.GetStr("G_Name", pMsg.stABJoinUserInfo[pMsg.btUserCnt].szGuildName);
		pMsg.stABJoinUserInfo[pMsg.btUserCnt].dwGuild = g_DataServerDB.GetInt("Number");
		g_DataServerDB.GetStr("CharName", pMsg.stABJoinUserInfo[pMsg.btUserCnt].szUserName);
		pMsg.btUserCnt++;

		if(pMsg.btUserCnt >= 250)
		{
			break;
		}
	}

	g_DataServerDB.Clear();
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void GDReqAcheronGuardianProcMultiCast(int aIndex, _tagPMSG_REQ_AE_PLAY_DS * aRecv)
{
	_tagPMSG_ANS_AE_PLAY_DS pMsg;
	PHeadSubSetB((LPBYTE)&pMsg, 0xF8, 0xF1, sizeof(pMsg));

	pMsg.btPlay = aRecv->btPlay;

	for(int i=0;i<MAX_SERVEROBJECT;i++)
	{
		if(gSObj[i].ServerCode != -1 
			&& gSObj[i].SType == gSObj[aIndex].SType
			&& (gSObj[i].ServerCode / 20) == aRecv->wMapSvrNum)
		{
			DataSend(i,(PBYTE)&pMsg,sizeof(pMsg));
		}
	}
}

#endif