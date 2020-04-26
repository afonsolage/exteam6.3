#include "stdafx.h"
#include "TMemory.h"
#include "Other.h"
#include "VisualFix.h"
#include "Console.h"
#include "RageSystem.h"
#include "ConnectEx.h"
#include "User.h"
#include "HpBar.h"
#include "ChatExpanded.h"
#include "QuestSystem.h"
#include "SwitchChar.h"
#include "Configs.h"
#include "AutoParty.h"
#include "Protocol.h"
#include "Ranking.h"
#include "EventTimer.h"
#include "Monster.h"
#include "ItemSmokeEffect.h"
#include "MonsterQuest.h"
#include "NewPartyBuff.h"
#include "NewParty.h"
#include "PartySearch.h"
#include "PersonalShopEx.h"
#include "NewsBoard.h"
#include "AntiCheatPlus.h"
#include "BufferSystem.h"
#include "Smithy.h"
#include "ExLicense.h"
#include "OfflineMode.h"
#include "Marriage.h"
#include "InfoLog.h"
#include "AddPoints.h"
#include "CustomMenu.h"
#include "ResetSystem.h"
#include "DonateShop.h"
#include "DungeonSiege.h"
#include "ItemRank.h"
#include "DrawTime.h"
#include "TeamVsTeam.h"
#include "Sound.h"
#include "Achievements.h"
#include "ExTeleport.h"
#include "PremiumSystemEx.h"
#include "ExTeleportEvo.h"
#include "PKClear.h"
#include "AccountSecurity.h"
#include "ItemAsm.h"
#include "ReferralSystem.h"
#include "PostItem.h"
#include "BuffIcon.h"
#include "ExWinQuestSystem.h"
#include "PickUpItemInfo.h"
#include "Lottery.h"
#include "DataSend.h"
#include "ItemMarket.h"
#include "StatsAdvance.h"
#include "PetEx.h"
#include "MuHelper.h"
#include "MUHelperOffline.h"

Protocol	gProtocol;
// ----------------------------------------------------------------------------------------------

static unsigned char bBuxCode[3]={0xFC, 0xCF, 0xAB};	// Xox Key for some interesthing things :)

void BuxConvert(char* buf, int size)
{
	int n;

	for (n=0;n<size;n++)
	{
		buf[n]^=bBuxCode[n%3] ;		// Nice trick from WebZen
	}
}
// ----------------------------------------------------------------------------------------------

bool CheckerText(PMSG_CHATDATA * Recv)
{
	
	int len = strlen(Recv->chatmsg);

	if(len > 60)
	{
		return false;
	}

	return true;
}
// ----------------------------------------------------------------------------------------------

void Protocol::Load()
{
	this->byXorFilter[0] = 0x54;
	this->byXorFilter[1] = 0xAD;
	this->byXorFilter[2] = 0x65;
	this->byXorFilter[3] = 0x0F;
	this->byXorFilter[4] = 0x33;
	this->byXorFilter[5] = 0xFE;
	this->byXorFilter[6] = 0x31;
	this->byXorFilter[7] = 0xBB;
	this->byXorFilter[8] = 0x9A;
	this->byXorFilter[9] = 0x13;
	this->byXorFilter[10] = 0x56;
	this->byXorFilter[11] = 0xAC;
	this->byXorFilter[12] = 0x71;
	this->byXorFilter[13] = 0x83;
	this->byXorFilter[14] = 0x60;
	this->byXorFilter[15] = 0x2B;
	this->byXorFilter[16] = 0x13;
	this->byXorFilter[17] = 0x47;
	this->byXorFilter[18] = 0xBF;
	this->byXorFilter[19] = 0x28;
	this->byXorFilter[20] = 0xE9;
	this->byXorFilter[21] = 0x00;
	this->byXorFilter[22] = 0x7F;
	this->byXorFilter[23] = 0x10;
	this->byXorFilter[24] = 0x6F;
	this->byXorFilter[25] = 0x32;
	this->byXorFilter[26] = 0x65;
	this->byXorFilter[27] = 0xF6;
	this->byXorFilter[28] = 0x92;
	this->byXorFilter[29] = 0x1D;
	this->byXorFilter[30] = 0xD3;
	this->byXorFilter[31] = 0xEF;

	for( int i = 0; i < 32; i++ )
	{
		SetByte((PVOID)((oXORFilterStart + 4 * i) + 3), this->byXorFilter[i]);
	}

	SetOp((LPVOID)oDataRecv_Call, (LPVOID)this->DataRecv, ASM::CALL);
}

void Protocol::DataSend(LPBYTE Data, int Size, bool encrypt)
{
	if (encrypt)
	{
		int StartPos = 0;

		if( Data[0] == 0xC1 || Data[0] == 0xC3 )
		{
			StartPos = 3;
		}
		else if( Data[0] == 0xC2 || Data[0] == 0xC4 )
		{
			StartPos = 4;
		}

		for( int i = StartPos; i < Size; i++ )
		{
			Data[i] ^= Data[i - 1] ^ this->byXorFilter[i%32];
		}
	}
	send(pActiveSocket, (char*)Data, Size, 0);
}

void Protocol::DataRecv(DWORD Case, LPBYTE Data, int Len, int aIndex)
{
	DataRecvPre(Case, Data, Len, aIndex);
	pDataRecv(Case, Data, Len, aIndex);
	DataRecvPos(Case, Data, Len, aIndex);
}

void Protocol::DataRecvPre(DWORD Case, LPBYTE Data, int Len, int aIndex)
{
	BYTE ProtocolType = Data[0];
	
	gConsole.Output(cGREEN, "protoNum: 0x%X | HEAD: 0x%X 0x%X 0x%X 0x%X ",Case,Data[0],Data[1],Data[2],Data[3]);

#ifdef exDEBUG_CODE
	//gConsole.Output(cGREEN, "protoNum: 0x%X | HEAD: 0x%X 0x%X 0x%X 0x%X ",Case,Data[0],Data[1],Data[2],Data[3]);

	PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)Data;
	//if(lpDef->subcode==19)
	//gConsole.Output(cGREEN, "0x%X: %d subcode: %d", Case, lpDef->subcode);
#endif

	//if(Case == 0xFB)
	//{
	//	if(lpDef->subcode == 18)
	//	{
	//		gMonsterQuest.RecvKill((GCMonsterQuestKill *) Data);
	//	}
	//	if(lpDef->subcode == 19)
	//	{
	//		gMonsterQuest.RecvMission((GCMonsterQuestDialog *)Data);
	//	}
	//	if(lpDef->subcode == 20)
	//	{
	//		gMonsterQuest.RecvWindowsOpen((GCQuestWindowsOpen *)Data);
	//	}
	//}
	// ----
#if(exRECONNECT)
	if( Data[2] == 0xF4 && Data[3] == 3)
	{
		PMSG_ANS_SERVER_INFO * lpDef = (PMSG_ANS_SERVER_INFO *)Data;
		sprintf(gConnectEx.m_GSIP, "%s", lpDef->Ip);
		gConnectEx.m_GSPort = lpDef->Port;
		pDataRecv(Case, Data, Len, aIndex);
		return;
	}
#endif

	if(gWINQUEST) 
	{
		gQuestSystem.Protocol(Case, Data, Len, aIndex);
	}

	gAutoParty.Protocol(Case, Data, Len, aIndex);
	gRanking.RecvGS(Case, Data, Len, aIndex);

	if(ProtocolType == 0xC1)
	{
		switch(BYTE(Case))
		{
		#if(ENABLE_PETEX)
		//case 0x25:
		//	g_PetEx.RefreshViewPortItem((DWORD)Data);
		//	break;
		#endif
		case 0xBF:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)Data;
				switch(lpDef->subcode)
				{
				case 0x51:
					gMuHelper.GCData(Data);
					break;
				}
				break;
			}
			break;
#if(CUSTOM_POSTITEM)
		case 0x78:
			gPostItem.RecvPostItem ( ( PMSG_POSTITEM* ) Data );
			//g_ConsoleEx.Output(cGREEN, "gPostItem.RecvPostItem");
			break;
#endif
#if(FIX_GUILD_CRASH==TRUE)
		case 0x0D:
			{
				if(!CheckerText((PMSG_CHATDATA*)Data) /*&& pPlayerState == GameProcess*/)
				{
					return;
				}
			}
			break;
#endif
		case 0x00:
			{
				gChatExpanded.GCChatData((PMSG_CHATDATA * )Data);
#if(CUSTOM_EX_CHAT==TRUE)
				if(pPlayerState == GameProcess)
				{
					g_InfoLog.GCChatProc((PMSG_CHATDATA*)Data);
				}
			}
#endif
			break;
		case 0x02:
			{
				gChatExpanded.GCChatDataPrivate((PMSG_CHATDATA_WHISPER *)Data);
#if(CUSTOM_EX_CHAT==TRUE)
				g_InfoLog.GCChatWhisperRecv((CHAT_WHISPER_EX*)Data);
#endif
			}
			break;
		case 0xF1:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2*)Data;
				switch (lpDef->subcode)
				{
				case 0x00:
				{
					gVisualFix.RecvIndex((PMSG_JOINRESULT*)Data);
#if _NEW_PARTY_SYSTEM_ == TRUE
					//if(gPARTY_SYSTEM)
					{
						g_Party.PartyMemberCount = 0;
						ZeroMemory(g_Party.PartyData, sizeof(g_Party.PartyData));
					}
#endif
#ifdef AUTO_LOGIN
					gProtocol.AutoLogin();
#endif
#if(ANTI_CHEAT_PLUS==TRUE)
					g_AntiCheatPlus.CG_HddSend();
#endif
#if(EVENT_DUNGEON_SIEGE)
					g_DungeonSiege.CGHWID();
#endif
#if(CUSTOM_ACCOUNT_SECURITY)
					g_AccountSecurity.CGSendAccountConnect();
#endif
				}
				break;
				//				case 0x01:
				//					{
				//#if(!DEBUG_ACCOUNT_SECURITY)
				//						PMSG_RESULT * lpJoin = (PMSG_RESULT*)Data;
				//
				//						if(lpJoin->result == 1)
				//						{
				//							#if(CUSTOM_ACCOUNT_SECURITY)
				//							g_AccountSecurity.CGSendAccountConnect();
				//							#endif
				//						}
				//#endif
				//					}
				//					break;
				case 0x02:
				{
					PMSG_RESULT* lpMsg = (PMSG_RESULT*)Data;

					g_MUHelperOffline.GCMsgClose(lpMsg);
				}
				break;
				}
			}
			break;
		case 0xF3:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2*)Data;
				switch(lpDef->subcode)
				{
#ifdef AUTO_LOGIN
				case 0x00:
					//gProtocol.AutoCharacter();
					break;
#endif
				case 0x03:
					{
#ifdef exRECONNECT
						gConnectEx.RestoreGame();
#endif
						gVisualFix.RecvUpPoint((PMSG_CHARMAPJOINRESULT*)Data);
						HpBar.WorkHpBar(false);
						g_OfflineMode.ClearSettings();

#if(USER_BUFF_ICON_EX==TRUE)
						g_BuffIcon.DeleteAllBuff();
#endif
						gDataSend.SendConfig();
						gMuHelper.RestoreState();

					}
					break;
				case 0x04:
					{
						gVisualFix.RecvRespawn();
						HpBar.WorkHpBar(false);
					}
					break;
				case 0x05:
					gVisualFix.RecvUpLevel((PMSG_LEVELUP*)Data);
					break;
				case 0x06:
					gVisualFix.RecvDownPoint((PMSG_LVPOINTADDRESULT*)Data);
					break;
				}
			}
			break;
		case PROTOCOL_ATTACK:
			{
				gVisualFix.RecvDamage((PMSG_ATTACKRESULT*) Data);
				if (Data[1] > 10) HpBar.Recv((PMSG_ATTACKRESULT*)Data);

				//if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
				//{
				//	if(gInterface.CheckWindow(ObjWindow::Inventory))
				//	{
				//		gInterface.CloseWindow(ObjWindow::Inventory);
				//	}
				//}
			}
			break;
		case 0x17:
			{
				gVisualFix.RecvKilledObject((PMSG_DIEPLAYER*)Data);
				WORD tIndex = (Data[3] << 8) + Data[4];
				if (tIndex == HpBar.RetIndex() || (tIndex == pGameIndex))
				{
					HpBar.WorkHpBar(false);
				}
#ifdef NEW_HP_BAR
				for(int n = 0; n < MAX_VIEWPORT;n++)
				{
					if(tIndex == gObjUser.ExViewe[n].aIndex)
					{
						gObjUser.ExViewe[n].aIndex = -1;
						break;
					}
				}
#endif
				if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
				{
					if(tIndex == pGameIndex && gInterface.CheckWindow(ObjWindow::Inventory))
					{
						gInterface.CloseWindow(ObjWindow::Inventory);
					}
				}
			}
			break;
		case 0x26:
			gVisualFix.RecvHPSD((PMSG_REFILL*)Data);
			break;
		case 0x27:
			gVisualFix.RecvMPAG((PMSG_MANASEND*)Data);
			break;
		case 0x16:
			gVisualFix.RecvExp((PMSG_KILLPLAYER*)Data);
			break;
		case 0x9C:
			gVisualFix.RecvMasterExp((PMSG_KILLPLAYER_EXT*)Data);
			break;
		case 0x14: //Destroy viewport chars
			{
				for (unsigned int i=0; i<Data[3]; ++i)
				{
					WORD tIndex = (Data[4 + (i*2)] << 8) + Data[5 + (i*2)];
					if (tIndex == pGameIndex)
					{
						HpBar.WorkHpBar(false);
						break;
					}
				}
			}
			break;
		case 0x1C: //Teleport
			{
				HpBar.WorkHpBar(false);
				#if(EVENT_TEAM_VS_TEAM)
				if(pMapNumber == TEAMVSTEAM_MAP)
				{
					g_Sound.Stop(eSOUND_TEAM_VS_TEAM);
				}
				#endif
			}
			break;
		case 0xFB:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)Data;
				if(lpDef->subcode==19)
				gConsole.Output(cGREEN, "subcode: %d", lpDef->subcode);

				switch ( lpDef->subcode )
				{
				case 0x00:
					gRageSystem.RecvConfig((sConfigStruct *) Data);
					break;
				case 0x01:
					gRageSystem.RageRecv((ClickSend*)Data);
					break;
				case 0x02:
					gRageSystem.RecvStart((sRageUserSend*) Data);
					break;
				case 0x03:
					gRageSystem.RecvExp((RageExpSend *) Data);
					break;
				case 0x05:
					gObjUser.ResetSystemGC_CharUpdate((GC_RESET_CHAR_UPDATE*) Data);
					break;
#if(DONATE_SHOP==TRUE)
				case 0x06:
					{
						g_DonateShop.GC_RecvShopNum((GC_SHOP_CLICK*)Data);
					};
					break;
#endif
#ifdef exRECONNECT
				case 0xC:
					{
						gConnectEx.m_ConnectState = ConnectExType::OnForceDisconnect;
						gConnectEx.Disconnect();
					}
					break;
#endif
				case 0x08:
					gObjUser.UpdateCharInfo((CHAR_UPDATEINFO*)Data);
					break;
#if(CUSTOM_PREMIUM_SYSTEM==TRUE)
				case 0x09:
					{
						g_PremiumSystemEx.GC_RecvInfo((GC_PREMIUM_SEND*)Data);	
					};
					break;
				case 0x16:
					{
						g_PremiumSystemEx.GC_RecvVIPInfo((GC_VIP_SEND*)Data);
					};
					break;
#endif
				case 14:
					gProtocol.JewelsBankRecv((EXINFO_UPDATE*)Data);
					break;
				case 15:
					gProtocol.RecvConfig((EX_GC_CONFIG_SEND*)Data);
					break;
				case 16:
					gProtocol.RecvTimer((GCTEventTime*)Data);
					break;
				case 17:
					g_ExLicense.GCLicenseUser((PMSG_LICENSE_DATA*) Data);
					break;
				case 18:
					gMonsterQuest.RecvKill((GCMonsterQuestKill *) Data);
					break;
				case 19:
					gMonsterQuest.RecvMission((GCMonsterQuestDialog *)Data);
					break;
				case 20:
					gMonsterQuest.RecvWindowsOpen((GCQuestWindowsOpen *)Data);
					break;
				case 21:
					gProtocol.GC_ShopClose((GC_SHOP_CLOSE *)Data);
					break;
#if(CUSTOM_NPC_BUFFER==TRUE)
				case 0x20:
					g_BufferSystem.RecvData((GC_BuffNpcOpen*)Data);
					break;
#endif
#if(CUSTOM_PARTY_SEARCH==TRUE)
				case 0x1B:
					g_PartySearch.GC_InfoRecv((CG_AutoPartyInfo*)Data);
					break;
#endif
#if(CUSTOM_SMITHY == TRUE)
				case 0x1C:
					g_Smithy.GCSettingsRecv((GC_SmithySettings*)Data);
					break;
				case 0x1D:
					g_Smithy.GCItemSend((GC_SmithyDATA*)Data);
					break;
				case 0x1E:
					g_Smithy.GCItemInit((GC_SmithyInit*)Data);
					break;
#endif
#if(OFFLINE_MODE)
				case 0x30:
					g_OfflineMode.GCConfig((GC_OFFMODE_CONFIG*)Data);
					break;
#endif
#if(CUSTOM_MARRIAGE)
				case 0x31:
					g_Marriage.GCInfoNames((PMSG_GC_MARRIAGE_NAMES*)Data);
					break;
				case 0x32:
					g_Marriage.GCWindowClose();
					break;
#endif
#if(CUSTOM_ADD_POINTS==TRUE)
				case 0x27:
					g_AddPoints.GCResetPointRecv((GC_RESET_POINT_CFG*)Data);
					break;
#endif
#if(ANTI_CHEAT_PLUS==TRUE)
				case 0xFF:
					g_AntiCheatPlus.GC_Recv(Data);
					break;
#if(ANTI_CHEAT_PLUS_CRC)
				case 0xFE:
					g_AntiCheatPlus.GC_CRCRecv((PMSG_CRCBase*)Data);
					break;
				case 0xFD:
				case 0xFC:
				case 0xFB:
					g_AntiCheatPlus.CGAnsSendFile((PMSG_FILESEND*)Data);
					break;
#endif
#endif
				case 0x40:
					g_CustomMenu.GCChangeClassConfig((PMSG_GC_CHANGECLASS_CONFIG*)Data);
					break;
#if(CUSTOM_RESETSYSTEM)
				case 0x43:
					g_ResetSystem.GCDialogInfo((GC_RESET_DATA*)Data);
					break;
#endif
#if(EVENT_DUNGEON_SIEGE)
				case 0x44:
					g_DungeonSiege.GCNpcInfo((PMSG_GC_DUNGEON_SIEGE_NPC*)Data);
					break;
#endif
#if(CUSTOM_ITEM_RANK==TRUE)
				case 0x51:
					{
						g_ItemRank.GCRankInit((PMSG_INITRANK*)Data);
					}
					break;
				case 0x52:
					{
						g_ItemRank.GCRankData((PMSG_DATARANK*)Data);
					}
					break;
				case 0x53:
					{
						g_ItemRank.GCRankList((PMSG_LISTRANK*)Data);
					}
					break;
#endif
#if(EVENT_DUNGEON_SIEGE)
				case 0x54:
					g_DungeonSiege.GCGuildNumber((PMSG_GC_GUILD_INDEX*)Data);
					break;
				case 0x55:
					g_DungeonSiege.GCSiegeScore((PMSG_DUNGEON_SIEGE_SCORE*)Data);
					break;
				case 0x56:
					g_DungeonSiege.GCPlayerConnect((PMSG_DUNGEON_SIEGE_PLAYER_CONNECT*)Data);
					break;
				case 0x57:
					g_DungeonSiege.GCEventState((PMSG_DUNGEON_SIEGE_STATE*)Data);
					break;
#endif
				case 0x58:
					//license enable
					break;
				case 0x59:
					//license disable
					break;
				case 0x70:
					GCServerTime((PMSG_SERVER_TIME*)Data);
					break;
				case 0x71:
					gProtocol.GCMapQuestMiniInfo((PMSG_DUNGEON_SYSTEM*)Data);
					break;
				case 0x72:
					//gProtocol.PartyMiniMapInfo((PMSG_PARTY_MINIMAP*)Data);
					break;
#if(EVENT_TEAM_VS_TEAM)
				case 0x80:
					g_TeamVsTeam.GCEventStatus((PMSG_TVTGC_STATUS*)Data);
					break;
				case 0x81:
					g_TeamVsTeam.GCOpenWindow((PMSG_TVTGC_WINOPEN*)Data);
					break;
				case 0x82:
					g_TeamVsTeam.GCEventScore((PMSG_TVTGC_SCORE*)Data);
					break;
				case 0x83:
					g_TeamVsTeam.GCTeam((PMSG_TVTGC_TEAM*)Data);
					break;
				case 0x84:
					g_TeamVsTeam.GCUserKillCount((PMSG_TVTGC_KILL*) Data);
					break;
				case 0x85:
					g_TeamVsTeam.GCEventiTimer((PMSG_TVTGC_TIME*) Data);
					break;
#endif
#if(SYSTEM_ACHIEVEMENTS)
				case 0x90:
					g_Achievements.GCConfigData((PMSG_GC_ACH_SETTINGS_DATA*)Data);
					break;
				case 0x91:
					g_Achievements.GCPlayerData((PMSG_GC_ACH_PLAYER_DATA*)Data);
					break;
				case 0x92:
					g_Achievements.GCCalculatorPower((PMSG_GC_ACH_POWER*)Data);
					break;
#endif
				case 0x95:
					gRageSystem.GCRageReset((PMSG_REQ_RESETRAGE*)Data);
					break;
				case 0x96:
					g_DonateShop.GCCheckBuyDonateItem((PMSG_DONATE_CHECKBUY*)Data);
					break;
				case 0xA1:
					//g_ResetSystem.GCGrandDialogInfo((PMSG_GRAND_DIALOG*)Data);
					break;
#if(CUSTOM_PKCLEAR_NPC==TRUE)
				case 0xAC:
					g_PKClear.GC_Price((GC_PKCLEAR_PRICE*)Data);
					break;
#endif
#if(CUSTOM_ACCOUNT_SECURITY)
				case 0xB0:
					g_AccountSecurity.GCRecvAccountInfo((PMSG_REQ_ACC_INFO*)Data);
					break;
				case 0xB1:
					g_AccountSecurity.GCRecvSettingPC((PMSG_ANS_ACC_SETTING_PC*)Data);
					break;
				case 0xB4:
					g_AccountSecurity.GCRecvConnectLogin((PMSG_REQ_ACC_LOGIN*)Data);
					break;
#endif

				case 0xAD:
					g_PremiumSystemEx.GC_Config((GC_PREMIUM_CONFIG*)Data);
					break;
#if(CUSTOM_REFERAL_SYSTEM)
				case 0xAE:
					g_ReferralSystem.GCAnsMasterResult((PMSG_CGANS_REFERRAL_MASTER_REWARD*)Data);
					break;
#endif
#if(CUSTOM_REFERAL_SYSTEM)
				case 0xAF:
					g_ReferralSystem.GCAnsUserInfo((PMSG_ANS_REFERRAL_USER_INFO*)Data);
					break;
				case 0xB3:
					g_ReferralSystem.GCAnsUserResult((PMSG_GCANS_REFERRAL_USER_REWARD*)Data);
					break;
#endif
				case 0xC0:
					g_ExLicense.GC_UserConfigRecv((PMSG_USERCONFIG*)Data);
					break;
#if(CUSTOM_EX_QUEST_SYSTEM==TRUE)
				case 0xC3:
					{
						g_ExWinQuestSystem.GC_MiniInfoRecvEx((GC_ExWinMiniInfoEx*)Data);
					}
					break;
				case 0xC4:
					{
						g_ExWinQuestSystem.GC_Start((GC_ExWinStart*)Data);
					}
					break;
#endif
#if(CUSTOM_PICKUP_ITEM_INFO)
				case 0xBF:
					g_PickUpItemInfo.InfoRecv((PMSG_ANS_PICKUP_INFO*)Data);
					break;
#endif
				case 0xC1:
					gObjUser.WarehouseReq((CHANGEWAREHOUSE*)Data);
					break;
#if(CUSTOM_LOTTERY)
				case 0xD0:
					g_Lottery.GCLotteryData((PMSG_LOTTERY_DATA*)Data);
					break;
				case 0xD2:
					g_Lottery.GCLotteryResult((PMSG_LOTTERY_RESULT*)Data);
					break;
#endif
				#if(CUSTOM_MINIMAP_PARTY)
				case 0xD5:
					gObjUser.PartyMiniMapInfo((PMSG_PARTY_MINIMAP*)Data);
					break;
				#endif

				#if(DEV_STATS_ADVANCE)
				case 0xDA:
					g_StatsAdvance.Recv((PMSG_STATS_ADVANCE*)Data);
					break;
					#endif
				#if(DEV_PLAYERINFO)
				case 0xDB:
					gProtocol.RecvInfoPlayer((PMSG_ANS_INFOPLAYER*)Data);
					break;
				#endif
				#if(DEV_DAMAGE_TABLE)
				case 0xDC:
					gProtocol.RecvDamageTable((PMSG_DAMAGE_TABLE*)Data);
					break;
				#endif
				}
			}
			break;
		case 0x3F:
			{
				PBMSG_HEAD2 * lpDef = (PBMSG_HEAD2 *)Data;
				switch(lpDef->subcode)
				{
#if(CUSTOM_PERONAL_EX==TRUE)
				case 0x01:
					g_PersonalShopEx.GC_ResultPrice((PMSG_ANS_PSHOP_SETITEMPRICE*) Data);
					break;
#endif
				}
			}
			break;
		case 0x2E:
			g_NewPartyBuff.RecvBuff((PMSG_BUFFLIST_SEND_PARTY*)Data);
			break;
		case 0x22:
			{
				PMSG_ITEMGETRESULT * lpData = (PMSG_ITEMGETRESULT *)Data;
				if(lpData->result == 0xFE)
				{
					WORD MoneyH = MAKE_NUMBERW(lpData->Data[0],lpData->Data[1]);
					WORD MoneyL = MAKE_NUMBERW(lpData->Data[2],lpData->Data[3]);
					gObjUser.Money = MAKE_NUMBERDW(MoneyH, MoneyL);
				}
			}
			break;
#if(USER_BUFF_ICON_EX==TRUE)
		case 0x2D:
			{
				g_BuffIcon.Recv((PMSG_SEND_BUFF_ICON*)Data);
			}
			break;
#endif
		case 0xEC:
			{
				PWMSG_HEAD2 * lpDef = (PWMSG_HEAD2 *)Data;

				switch(lpDef->subcode)
				{
				case 0x00:
					#if(DEV_PLAYERSHOP)
					g_ItemMarket.RecvItemList((PMSG_SEND_MARKET_ITEM*)Data);
					#endif
					break;
				};
			}
			break;
		case LC_HEADER:
			{
				PBMSG_HEAD2 * lpDef = (PBMSG_HEAD2 *)Data;

				switch(lpDef->subcode)
				{
				case LC_MUHELPER_OFF_ACTION:
					{
						g_MUHelperOffline.GCAction((MUHELPEROFF_ACTION*) lpDef);
					}
					break;
				};
			}
		}
	}
	else if( ProtocolType == 0xC2 )
	{
		switch(BYTE(Case))
		{
		case 0x3F:
			{
				PWMSG_HEAD2 * lpDef = (PWMSG_HEAD2 *)Data;
				switch(lpDef->subcode)
				{
#if(CUSTOM_PERONAL_EX==TRUE)
				case 0x05:
					g_PersonalShopEx.GC_PSRecv((PMSG_ANS_BUYLIST_FROM_PSHOP*) Data);
					break;
#endif
				}
			}
			break;
		case 0xFA:
			{
				PWMSG_HEAD2 * lpDef = (PWMSG_HEAD2 *)Data;
				switch(lpDef->subcode)
				{
				case 0x01:
#ifdef HPBAR_UPDATE
					gProtocol.NewExVieweport(Data);
#else
					gProtocol.NewExVieweport((CGExUserHpBar*)Data);
#endif
					break;
#if(DONATE_SHOP==TRUE)
				case 0x07:
					{
						g_DonateShop.GC_Recv_shop(Data);
					}
					break;
#endif
#if(CUSTOM_PARTY_SEARCH==TRUE)
				case 0x08:
					g_PartySearch.GC_Recv(Data);
					break;
#endif		
#if(CUSTOM_PERONAL_EX==TRUE)
				case 0x09:
					g_PersonalShopEx.GC_Recv(Data);
					break;
				case 0x0A:
					g_PersonalShopEx.GC_RecvUpdatePSInvValue(Data);
					break;
				case 0x0B:
					g_PersonalShopEx.GC_RecvUpdatePSInvTargetValue(Data);
					break;
#endif
				case 0x0C:
					g_DungeonSiege.GCVieweSiege(Data);
					break;
#if(EVENT_TEAM_VS_TEAM)
				case 0x10:
					g_TeamVsTeam.GCViewePortTvT(Data);
					break;
				case 0x11:
					g_TeamVsTeam.GCEventStatistic((PMSG_TVT_STATISTIC*)Data);
					break;
#endif
#if(CUSTOM_EX_TELEPORT==TRUE)
				case 0x0F:
					g_ExTeleport.GCWindows((PMSG_GC_TELEPORTWIN*)Data);
					break;
#endif
#if(CUSTOM_EX_TELEPORT_EVO==TRUE)
				case 0x12:
					g_ExTeleportEvo.GCWindows((PMSG_GC_TELEPORTWINEVO*)Data);
					break;
#endif
				case 0xBF:
					{
						PMSG_WINGS_INFO * lpMsg = (PMSG_WINGS_INFO*)Data;

						memset(gProtocol.m_Wing, 0, sizeof(gProtocol.m_Wing));

						for(int i = 0; i < MAX_WINGS_ITEM; i++)
						{
							gProtocol.m_Wing[i].ItemType = lpMsg->Wing[i].ItemType;
							gProtocol.m_Wing[i].Damage = lpMsg->Wing[i].Damage;
							gProtocol.m_Wing[i].Absord = lpMsg->Wing[i].Absord;

							g_bWingsActive = true;
						}

						g_bWingsActive = true;

						//SetByte((LPVOID)0x007E4C3D, 0xEB);
						//SetRange((LPVOID)0x007E4C31, 38, ASM::NOP);
					}
					break;

#if(CUSTOM_REFERAL_SYSTEM)
				case 0xAE:
					g_ReferralSystem.GCAnsMasterInfo((PMSG_ANS_REFERRAL_MASTER_INFO*)Data);
					break;
#endif
#if(CUSTOM_EX_QUEST_SYSTEM==TRUE)
				case 0xCC:
					{
						g_ExWinQuestSystem.GC_RecvMain((GC_MainPacket*)Data);
					}
					break;
				case 0xCD:
					{
						g_ExWinQuestSystem.GC_MiniInfoRecv((GC_ExWinMiniInfo*)Data);
					}
					break;
#endif

				}
			}
			break;
#if(CUSTOM_NEWS==TRUE)
		case 0xFD:
			g_NewsBoard.OpenMain((NEWS_ANS_TITLES*)Data);
			break;
		case 0xFE:
			g_NewsBoard.OpenItem((NEWS_ANS_NEWS*)Data);
			break;
#endif
		case 0x65:
			gProtocol.GCGuildInfo(Data);
			break;
		//case 0xEC:
		//	{
		//		PWMSG_HEAD2 * lpDef = (PWMSG_HEAD2 *)Data;
		//		switch(lpDef->subcode)
		//		{
		//			case 0x00:
		//			#if(DEV_PLAYERSHOP)

		//			#endif
		//			break;
		//		};
		//	}
		//	break;

		}
	}
}

void Protocol::DataRecvPos(DWORD Case, LPBYTE Data, int Len, int aIndex)
{
	BYTE ProtocolType = Data[0];
	if(ProtocolType == 0xC1)
	{
		switch(BYTE(Case))
		{
			case 0xF3:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2*)Data;
				switch(lpDef->subcode)
				{
				case 0x03:
					{
						g_MUHelperOffline.RestoreState();
					}
					break;
				}
			}
			case PROTOCOL_MOVE:
			{
				PMSG_RECVMOVE* lpMsg = (PMSG_RECVMOVE*)Data;

				g_MUHelperOffline.GCMoveProc(lpMsg);
			}
			break;
		}
	}
}

void Protocol::JewelsBankRecv(EXINFO_UPDATE * aRecv)
{
	gConsole.Output(0, "Premium Time: %d", aRecv->PremiumTime);

	gObjUser.Premium = aRecv->PremiumTime;
	gObjUser.ChaosBank = aRecv->Chaos;
	gObjUser.BlessBank = aRecv->Bless;
	gObjUser.SoulBank = aRecv->Soul;
	gObjUser.LifeBank = aRecv->Life;

	gObjUser.ExCred = aRecv->ExCred;
	gObjUser.Zen = aRecv->Zen;

	gObjUser.WCoinC = aRecv->WCoinC;
	gObjUser.WCoinP = aRecv->WCoinP;
	gObjUser.WCoinG = aRecv->WCoinG;

	gObjUser.CreateonBank = 0;

	gObjUser.GuardianBank = 0;
	gObjUser.HarmonyBank = 0;
	gObjUser.LowStoneBank = 0;
	gObjUser.HighStoneBank = 0;
	gObjUser.GemStoneBank = 0;

#if(ADD_JEWELBANK_CREATEON)
	/*if(g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2) || 
		g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))*/
	{
		gObjUser.CreateonBank = aRecv->CreateonBank;
	}
#endif

	gObjUser.GuardianBank = aRecv->GuardianBank;
	gObjUser.HarmonyBank = aRecv->HarmonyBank;
	gObjUser.LowStoneBank = aRecv->LowStoneBank;
	gObjUser.HighStoneBank = aRecv->HighStoneBank;
	gObjUser.GemStoneBank = aRecv->GemStoneBank;

	gObjUser.PremiumType = aRecv->PremiumType;

	gObjUser.m_iDonateCredit = aRecv->DonateCredit;

	gObjUser.m_PCPoint = aRecv->PCPoint;
}

#ifdef HPBAR_UPDATE
void Protocol::NewExVieweport(LPBYTE aRecv)
{
	ZeroMemory(&gObjUser.ExViewe,sizeof(gObjUser.ExViewe));
	int datasize = 6;
	int excount = aRecv[datasize-1];

	for (int n = 0; n < excount; n++)
	{
		VieweCharEx Vp;
		memcpy(&Vp,&aRecv[datasize],sizeof(Vp));
		gObjUser.ExViewe[n].aIndex = Vp.aIndex;
		gObjUser.ExViewe[n].Life = Vp.Life;
		gObjUser.ExViewe[n].MaxLife = Vp.MaxLife;
		gObjUser.ExViewe[n].SD = Vp.SD;
		gObjUser.ExViewe[n].MaxSD = Vp.MaxSD;
		gObjUser.ExViewe[n].Level = Vp.Level;
		gObjUser.ExViewe[n].Reset = Vp.Reset;
		gObjUser.ExViewe[n].GrandReset = Vp.GrandReset;
		gObjUser.ExViewe[n].Defence = Vp.Defence;
		gObjUser.ExViewe[n].Class = Vp.Class;
		gObjUser.ExViewe[n].AutoParty = Vp.AutoParty;
#ifdef PREM_TYPE
		if(g_ExLicense.CheckUser(eExUB::ulasevich)  || 
		   g_ExLicense.CheckUser(eExUB::ulasevich2)	||	   
		   g_ExLicense.CheckUser(eExUB::Local3))
		{
			gObjUser.ExViewe[n].PremType = Vp.PremiumType;
		}
#endif
		gObjUser.ExViewe[n].TvTTeam = Vp.TvTTeam;
#ifdef VIEW_MONSTER
		memcpy(gObjUser.ExViewe[n].Name,Vp.Name,sizeof(gObjUser.ExViewe[n].Name));
#endif
		datasize += sizeof(Vp);
	}
}
#else
void Protocol::NewExVieweport(CGExUserHpBar * aRecv)
{
	ZeroMemory(&gObjUser.ExViewe,sizeof(gObjUser.ExViewe));
	for (int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(aRecv->Vp[n].aIndex == -1)continue;
		gObjUser.ExViewe[n].aIndex = aRecv->Vp[n].aIndex;
		gObjUser.ExViewe[n].Life = aRecv->Vp[n].Life;
		gObjUser.ExViewe[n].MaxLife = aRecv->Vp[n].MaxLife;
		gObjUser.ExViewe[n].SD = aRecv->Vp[n].SD;
		gObjUser.ExViewe[n].MaxSD = aRecv->Vp[n].MaxSD;
		gObjUser.ExViewe[n].Level = aRecv->Vp[n].Level;
		gObjUser.ExViewe[n].Reset = aRecv->Vp[n].Reset;
		gObjUser.ExViewe[n].GrandReset = aRecv->Vp[n].GrandReset;
		gObjUser.ExViewe[n].Defence = aRecv->Vp[n].Defence;
		gObjUser.ExViewe[n].Class = aRecv->Vp[n].Class;
		gObjUser.ExViewe[n].AutoParty = aRecv->Vp[n].AutoParty;
#ifdef VIEW_MONSTER
		memcpy(gObjUser.ExViewe[n].Name,Vp.Name,sizeof(gObjUser.ExViewe[n].Name));
#endif
	}
}

#endif

bool GetMasterDisable(BYTE Class)
{
	return false;
}

void Protocol::RecvConfig(EX_GC_CONFIG_SEND * Data)
{
	LoadSwitchChar(Data->CharSwitch);

	if(Data->sGENS)
	{
		SetOp((LPVOID)oIsBattleServer_Call1, (LPVOID)gObjUser.IsBattleServer, ASM::CALL);
		SetOp((LPVOID)oIsBattleServer_Call2, (LPVOID)gObjUser.IsBattleServer, ASM::CALL);
	}

	gHelperLevel = Data->HelperLevel;
	gAutoParty.Active = Data->AutoParty;
	gRanking.Active = Data->Top100;
	gEventTimer.Active = Data->EventTimer;

	if(!Data->MoveTargetPosEffect)
	{
		SetRange((LPVOID)0x006E899D, 5, ASM::NOP);
		SetRange((LPVOID)0x007126FA, 5, ASM::NOP);
		SetRange((LPVOID)0x005B768F, 5, ASM::NOP);
		SetRange((LPVOID)0x005B770C, 5, ASM::NOP);
	}

	if(Data->CastleSiegeSkill)
	{
		SetByte((PVOID)(0x005B89C7), (BYTE)0xEB);
		SetByte((PVOID)(0x005B89C7+1), (BYTE)0x4C);		
	}

	if(Data->AntiCheat)
	{
		bAntiHack = Data->AntiCheat;
	}

	if(Data->GensColorEnable)
	{
		SetByte((LPVOID)(0x00788DB8+1), Data->GensColorBlue);	//Blue
		SetByte((LPVOID)(0x00788DBD+1), Data->GensColorGreen);	//Green
		SetByte((LPVOID)(0x00788DC2+1), Data->GensColorRed);	//Red
	}
	
	g_AddPoints.m_MaxStats = Data->MaxStats;

	if(Data->DLReflect)
	{
		SetRange((LPVOID)0x005528DE, 23, ASM::NOP);
	}

	if(!Data->MasterSkills)
	{
		SetRange((LPVOID)0x00784B77, 5, ASM::NOP);
		SetOp((LPVOID)0x00784F79, (LPVOID)GetMasterDisable, ASM::CALL);//  CALL 005878E0		//Master Button Disable
		SetOp((LPVOID)0x007D3916, (LPVOID)GetMasterDisable, ASM::CALL);//  CALL 005878E0		//Master A Key Disable
	}

	g_dwDivFireScreamSpeed = Data->DivFireScreamSpeed;
}

void Protocol::RecvTimer(GCTEventTime * Recv)
{
	gEventTimer.BCStart = Recv->TimeBC;
	gEventTimer.DSStart = Recv->TimeDS;
	gEventTimer.CCStart = Recv->TimeCC;
	gEventTimer.GDStart = Recv->TimeGD;
	gEventTimer.WWStart = Recv->TimeWW;
	//Recv->
	gEventTimer.TimeLora = Recv->TimeLora;
	gEventTimer.TimeDevias = Recv->TimeDevias;
	gEventTimer.TimeTvT = Recv->TimeTvT;
	gEventTimer.TimePandora = Recv->TimePandora;
	gEventTimer.TimeEvengelion = Recv->TimeEvengelion;
	gEventTimer.TimeShop = Recv->TimeShop;
	gEventTimer.TimeHappy = Recv->TimeHappy;
	gEventTimer.TimeDropEvent = Recv->TimeDropEvent;

	gEventTimer.m_dwTimeCryWolf = Recv->TimeCryWolf;
	gEventTimer.m_dwTimeCastleSiege = Recv->TimeCastleSiege;
	gEventTimer.m_dwTimeDungeonSiege = Recv->TimeDungeonSiege;
	gEventTimer.m_dwTimeRedDragon = Recv->TimeRedDragon;
}

bool oneLogin = true;

void Protocol::AutoLogin()
{
#if ENABLE_AUTOLOGIN ==	FALSE
	if(oneLogin == true)
	{
		return;
	}

	int Enable = GetPrivateProfileIntA("ExTeam","Enable",0,".\\AutoLogin.ini");

	if(!Enable) 
	{
		return;
	}



	oneLogin = true;
#endif

	//static bool AutoLoginStart = true;

#if ENABLE_AUTOLOGIN ==	TRUE

	char acc[11];
	char pas[11];

	ZeroMemory(&acc,sizeof(acc));
	ZeroMemory(&pas,sizeof(pas));

	strcpy(acc,LOGIN);
	strcpy(pas,PASSWORD);

#else
	char acc[11];
	char pas[11];

	ZeroMemory(&acc,sizeof(acc));
	ZeroMemory(&pas,sizeof(pas));

	GetPrivateProfileStringA("ExTeam", "Account", NULL, acc, sizeof(acc), ".\\AutoLogin.ini");
	GetPrivateProfileStringA("ExTeam", "Password", NULL, pas, sizeof(pas), ".\\AutoLogin.ini");
#endif

	PMSG_IDPASS pSend;
	ZeroMemory(&pSend,sizeof(pSend));
	pSend.h.set((LPBYTE)&pSend, 0xF1, sizeof(pSend));
	pSend.subcode = 0x01;

	BuxConvert(acc,sizeof(acc));
	BuxConvert(pas,sizeof(pas));

	memcpy(pSend.Id,acc,sizeof(pSend.Id)); 
	memcpy(pSend.Pass,pas,sizeof(pSend.Pass)); 

	pSend.TickCount = 0;

	char Seiral[17];
	char Version[6];

#if(IN_DLL==1)
		char VersionEx[6];
		memcpy(Seiral,SERIAL,sizeof(Seiral);
		memcpy(VersionEx,VERSION,sizeof(VersionEx));
		for (int i = 0; i < 5; ++i )
		{
			Version[i] =  ( VersionEx[i] - (i + 1) );	
		}
#else
		for (int i = 0; i < 16; ++i )
		{
			Seiral[i] =  *(BYTE*)(0x0E61F70 + i);	
		}
		for (int i = 0; i < 5; ++i )
		{
			Version[i] =  ( *(BYTE*)(0x0E61F68 + i) - (i + 1) );	
		}
#endif

	memcpy(pSend.CliSerial,Seiral,sizeof(pSend.CliSerial));
	memcpy(pSend.CliVersion,Version,sizeof(pSend.CliVersion));

	gProtocol.DataSend((LPBYTE)&pSend, pSend.h.size);
}

void Protocol::AutoCharacter()
{
	PMSG_CHARMAPJOIN pSend;
	ZeroMemory(&pSend,sizeof(pSend));
	pSend.h.set((LPBYTE)&pSend, 0xF3, sizeof(pSend));
	pSend.subcode = 0x03;
	memset(pSend.Name, 0, 10);
	char _name[] = "DangeR";
	//BuxConvert(_name, sizeof(_name));

	strncpy(pSend.Name,_name,10);

	

	gProtocol.DataSend((LPBYTE)&pSend, pSend.h.size);

	//pPlayerState = GameProcess;
}

void Protocol::GC_ShopClose(GC_SHOP_CLOSE *Recv)
{
	if(Recv->Close)
	{
		if(gInterface.CheckWindow(Shop))
		{
			gInterface.CloseWindow(Shop);
		}
	}
}

void Protocol::GCGuildInfo(LPBYTE aRecv)
{
	/*int datasize = 5;

	PMSG_SIMPLE_GUILDVIEWPORT pGuild;
	memcpy(&pGuild,&aRecv[datasize],sizeof(pGuild));

	short aIndex = MAKE_NUMBERW(pGuild.NumberH, pGuild.NumberL);
	gConsole.Output(cYELLOW, "%d %d %d", aIndex, pGameIndex, pGuild.GuildNumber);
	if(aIndex == pGameIndex)
	{
		gObjUser.GuildNamber = pGuild.GuildNumber;
		
	}*/
}

void Protocol::GCMapQuestMiniInfo(PMSG_DUNGEON_SYSTEM* aRecv)
{
	gObjUser.m_MapQuestShow = aRecv->Show;
	gObjUser.m_MapQuestCount = aRecv->Count;
	gObjUser.m_MapQuestMaxCount = aRecv->MaxCount;
}

void Protocol::CG_AutoHP(bool State)
{
	PMSG_PROTOCOL_RESULT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xBA, sizeof(pMsg));
	pMsg.Result = State;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

#if(DEV_PLAYERINFO)

void Protocol::SendInfoPlayer()
{
	if(pViewAttackTargetID == -1)
	{
		gObjUser.m_TargetInfo = false;
		return;
	}	

	lpViewObj lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewAttackTargetID);

	if(lpViewTarget->m_Model.ObjectType != emPlayer)
	{
		return;
	}

	PMSG_REQ_INFOPLAYER pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xDB, sizeof(pMsg));
	pMsg.aIndex = lpViewTarget->aIndex;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);	
}

void Protocol::RecvInfoPlayer(PMSG_ANS_INFOPLAYER* lpMsg)
{
	gObjUser.m_TargetData.aIndex = lpMsg->Data.aIndex;
	gObjUser.m_TargetData.Strength = lpMsg->Data.Strength;
	gObjUser.m_TargetData.Agility = lpMsg->Data.Agility;
	gObjUser.m_TargetData.Vitality = lpMsg->Data.Vitality;
	gObjUser.m_TargetData.Energy = lpMsg->Data.Energy;
	gObjUser.m_TargetData.Command = lpMsg->Data.Command;
	gObjUser.m_TargetData.Reset = lpMsg->Data.Reset;
	gObjUser.m_TargetData.GReset = lpMsg->Data.GReset;
	gObjUser.m_TargetData.PKLevel = lpMsg->Data.PKLevel;
	gObjUser.m_TargetData.Vip = lpMsg->Data.Vip;

	gObjUser.m_TargetInfo = true;
}

#endif

// ----------------------------------------------------------------------------------------------

#if(DEV_DAMAGE_TABLE)

void Protocol::RecvDamageTable(PMSG_DAMAGE_TABLE* lpMsg)
{
	if(!gAdvanceStats)
	{
		return;
	}

	unsigned long long dmg = gObjUser.m_SecondDamage;
	dmg += lpMsg->SecondDamage;

	if (dmg >= INT_MAX)
	{
		gObjUser.m_SecondZen = 0;
		gObjUser.m_SecondExp = 0;
		gObjUser.m_SecondDamage = 0;
		gObjUser.m_SecondDefence = 0;
		gObjUser.m_SecondReflect = 0;
		gObjUser.m_SecondCount = 0;
	}

	gObjUser.m_SecondZen += lpMsg->SecondZen;
	gObjUser.m_SecondExp += lpMsg->SecondExp;
	gObjUser.m_SecondDamage += lpMsg->SecondDamage;
	gObjUser.m_SecondDefence += lpMsg->SecondDefence;
	gObjUser.m_SecondReflect += lpMsg->SecondReflect;
	gObjUser.m_SecondCount += 1;

	int avg = gObjUser.m_SecondDamage / gObjUser.m_SecondCount;

	if(avg > gObjUser.m_SecondDamageMax)
	{
		gObjUser.m_SecondDamageMax = avg;
	}

	gObjUser.m_SecondInfo = true;
}

#endif