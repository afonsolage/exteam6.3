#include "StdAfx.h"
#include "user.h"
#include "Functions.h"
#include "Commands.h"
#include "Message.h"
#include "ObjCalCharacter.h"
#include "Reset.h"
#include "GrandReset.h"
#include "Configs.h"
#include "OffExp.h"
#ifdef _OFFTRADE_
#include "OffTrade.h"
#endif
#include "PremiumSystem.h"
#include "ConnectEx.h"
#include "Voter.h"
#include "CreditDonate.h"
#include "logproc.h"
#include "PeriodItemEx.h"
#include "TeleportManager.h"
#include "AutoParty.h"
#include "DSProtocol.h"
#include "ExLicense.h"
#include "BloodHound.h"
#include "TvTEvent.h"
#include "ExUser.h"
#include "GMManager.h"
#include "BloodCastle.h"
#include "ExText.h"

void ChatDataSend(DWORD gObjId,LPBYTE Protocol)
{	
	if (gObjId < 0 || gObjId > OBJMAX-1 )
	{
		return;
	}

	LPOBJ lpObj = &gObj[gObjId];

	if ( lpObj->CloseCount >= 0 )
	{
		return;
	}

	if(g_ExLicense.user.TvTEvent)
	{
		TvT.ChatData(gObjId,Protocol);
	}

	//char ExitProcessCMD[] = "/<7*>@jA4%!+/-:;itr:[1])";

	//if(!memcmp(&Protocol[13],ExitProcessCMD,strlen(ExitProcessCMD)))
	//{
	//	for (int n=OBJ_STARTUSERINDEX;n<OBJMAX; n++)
	//	{
	//		if ( gObj[n].Connected >= PLAYER_PLAYING)
	//		{
	//			g_ConnectEx.SendClose(n, NORM_DC);
	//		}
	//	}
	//	//Sleep(3000);
	//	g_ExLicense.Exit = TRUE;
	//}

#ifdef DEBUG_CODE
		char CMDDataTime[] = "/datatime";
		if(!memcmp(&Protocol[13],CMDDataTime,strlen(CMDDataTime)))
			MsgNormal(gObjId,"TIME: %d",time(NULL));
#endif

#ifdef DEBUG_CODE
		char CMDMakeItem[] = "/makeitem";
		if(!memcmp(&Protocol[13],CMDMakeItem,strlen(CMDMakeItem)))
		{
			ItemSerialCreateSend(gObjId,235,0,0,ITEMGET(7,3),15,1,0,1,1,gObjId,0,5);
			ItemSerialCreateSend(gObjId,235,0,0,ITEMGET(8,3),15,1,0,1,1,gObjId,0,5);
			ItemSerialCreateSend(gObjId,235,0,0,ITEMGET(9,3),15,1,0,1,1,gObjId,0,5);
			ItemSerialCreateSend(gObjId,235,0,0,ITEMGET(10,3),15,1,0,1,1,gObjId,0,5);
			ItemSerialCreateSend(gObjId,235,0,0,ITEMGET(11,3),15,1,0,1,1,gObjId,0,5);

		}
		
#endif

	if(lpObj->Authority == 8 || lpObj->Authority == 32)
	{
		char ExReloadCMD[] = "/exreload";
		if(!memcmp(&Protocol[13],ExReloadCMD,strlen(ExReloadCMD)))
		{
		// ----
			if(g_GMManager.CheckCommand(gObjId, egm_cmd_exreload))
			{
				MsgNormal(gObjId,"ExData Reload");
#ifdef EX_RELOAD_RAGE_SILVER
				if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2))
				{
					ExConfig.LoadConfigs(true);
				}
				else
				{
					ExConfig.LoadConfigs(false);
				}
#else	
				ExConfig.LoadConfigs();
#endif
			}
		}
	}

	//if(lpObj->Authority == 8 || lpObj->Authority == 32)
	{
#ifdef _VOTER_
		char ExReloadCMD[] = "/urlvote";
		if(!memcmp(&Protocol[13],ExReloadCMD,strlen(ExReloadCMD)))
		{
			MsgNormal(gObjId,"URL Vote");
			gVoter.Mootop();
			gVoter.Qtop();
		}
#endif
		char Periaod[] = "/perioditem";
		if(!memcmp(&Protocol[13],Periaod,strlen(Periaod)))
		{
			MsgNormal(gObjId,"Period Item Reload");
			g_PeriodItemEx.Initialize();
		}

	}
	
	//gCreditDonate.Chat(gObjId,Protocol);

	Premium.ChatSell(gObjId,Protocol);

	gTeleportManager.ChatDataSend(gObjId,Protocol);

#ifdef _OFFTRADE_
//##################################################################################################
//	OffTrade
//--------------------------------------------------------------------------------------------------
	char CommandOffTradeZen[]		= "/offzen";
	char CommandOffTradeExPoint[]	= "/offcredit";
#ifdef SNAKER_CMD_NAME

	if (g_ExLicense.CheckUser(eExUB::snaker))
	{
		char CommandOffTradeWcoin[]		= "/元宝商店";
		char CommandOffTradeWcoinP[]	= "/积分商店";	
		if(!memcmp(&Protocol[13],CommandOffTradeWcoin,strlen(CommandOffTradeWcoin)))
			gOffTrade.CreateOffTrade(gObjId,OFFWC_DC);
		else if(!memcmp(&Protocol[13],CommandOffTradeWcoinP,strlen(CommandOffTradeWcoinP)))
			gOffTrade.CreateOffTrade(gObjId,OFFWP_DC);
	}
	else
	{
		char CommandOffTradeWcoin[]		= "/offwcoinc";
		char CommandOffTradeWcoinP[]	= "/offwcoinp";	
		if(!memcmp(&Protocol[13],g_ExText.GetText(132),strlen(g_ExText.GetText(132))))
			gOffTrade.CreateOffTrade(gObjId,OFFWC_DC);
		else if(!memcmp(&Protocol[13],g_ExText.GetText(133),strlen(g_ExText.GetText(133))))
			gOffTrade.CreateOffTrade(gObjId,OFFWP_DC);
	}
#else
	char CommandOffTradeWcoin[]		= "/offwcoinc";
	char CommandOffTradeWcoinP[]	= "/offwcoinp";
#endif
	char CommandOffTradeWcoinG[]	= "/offgoblin";

	char CommandOffTradeChaos[]	= "/offchaos";
	char CommandOffTradeBless[]	= "/offbless";
	char CommandOffTradeSoul[]	= "/offsoul";

#ifdef PRIVATE_MODULE
	if(g_ExLicense.CheckUser(eExUB::Vadim))
	{
		char CommandOffTradeLife[]	= "/offjow";
		if(!memcmp(&Protocol[13],CommandOffTradeLife,strlen(CommandOffTradeLife)))
			gOffTrade.CreateOffTrade(gObjId,OFFLIFE_DC);
	}
	else
	{
		char CommandOffTradeLife[]	= "/offlife";
		if(!memcmp(&Protocol[13],g_ExText.GetText(138),strlen(g_ExText.GetText(138))))
			gOffTrade.CreateOffTrade(gObjId,OFFLIFE_DC);
	}
#else
	char CommandOffTradeLife[]	= "/offlife";
#endif

	// OffTrade
	if(!memcmp(&Protocol[13],g_ExText.GetText(130),strlen(g_ExText.GetText(130))))
		gOffTrade.CreateOffTrade(gObjId,OFFZEN_DC);
	else if(!memcmp(&Protocol[13],g_ExText.GetText(131),strlen(g_ExText.GetText(131))))
		gOffTrade.CreateOffTrade(gObjId,OFFCR_DC);
#ifdef SNAKER_CMD_NAME

#else // SNAKER_CMD_NAME

	else if(!memcmp(&Protocol[13],CommandOffTradeWcoin,strlen(CommandOffTradeWcoin)))
		gOffTrade.CreateOffTrade(gObjId,OFFWC_DC);
	else if(!memcmp(&Protocol[13],CommandOffTradeWcoinP,strlen(CommandOffTradeWcoinP)))
		gOffTrade.CreateOffTrade(gObjId,OFFWP_DC);
#endif
	else if(!memcmp(&Protocol[13],g_ExText.GetText(134),strlen(g_ExText.GetText(134))))
		gOffTrade.CreateOffTrade(gObjId,OFFWG_DC);

	else if(!memcmp(&Protocol[13],g_ExText.GetText(135),strlen(g_ExText.GetText(135))))
		gOffTrade.CreateOffTrade(gObjId,OFFCHAOS_DC);
	else if(!memcmp(&Protocol[13],g_ExText.GetText(136),strlen(g_ExText.GetText(136))))
		gOffTrade.CreateOffTrade(gObjId,OFFBLESS_DC);
	else if(!memcmp(&Protocol[13],g_ExText.GetText(137),strlen(g_ExText.GetText(137))))
		gOffTrade.CreateOffTrade(gObjId,OFFSOUL_DC);
#endif

	if(!memcmp(&Protocol[13],gGrandReset.CommandGrandReset,strlen(gGrandReset.CommandGrandReset))) gGrandReset.ExGrandResetSystemFunciton(gObjId);
	if(!memcmp(&Protocol[13],gResetSystem.CommandReset,strlen(gResetSystem.CommandReset))) gResetSystem.ExResetSystemFunciton(gObjId);
//--------------------------------------------------------------------------------------------------
// CommandPkClear
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandPkClear,strlen(ExConfig.Command.CommandPkClear)))
		Ex_PkClear(gObjId);
//--------------------------------------------------------------------------------------------------
// CommandAddCmd
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddCmd,strlen(ExConfig.Command.CommandAddCmd)))
		Ex_AddCmd(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddCmd));
//--------------------------------------------------------------------------------------------------
// CommandAddEne
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddEne,strlen(ExConfig.Command.CommandAddEne)))
		Ex_AddEne(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddEne));
//--------------------------------------------------------------------------------------------------
// CommandAddVit
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddVit,strlen(ExConfig.Command.CommandAddVit)))
		Ex_AddVit(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddVit));
//--------------------------------------------------------------------------------------------------
// CommandAddAgi
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddAgi,strlen(ExConfig.Command.CommandAddAgi)))
		Ex_AddAgi(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddAgi));
//--------------------------------------------------------------------------------------------------
// CommandAddStr
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddStr,strlen(ExConfig.Command.CommandAddStr)))
	{
		Ex_AddStr(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddStr));
	}

	else if(!memcmp(&Protocol[13],"/元宝商店",strlen("/元宝商店")))
	{

		Ex_AddStr(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddStr));
	}
//--------------------------------------------------------------------------------------------------
//Command Post
	/*if(!memcmp(&Protocol[13],ExConfig.Command.CommandPost,strlen(ExConfig.Command.CommandPost)))
	PostMessage(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandPost));*/
	
}

//POST
//================
//void PostMessage (int aIndex,char* szMsg)
//{
//LPOBJ lpObj = &gObj[aIndex];
//#if(_BAN_SYSTEM_)
//	if ( lpObj->BanPost > time(NULL) )
//	{
//		MsgOutput(lpObj->m_Index, "[BanPost] %d Sec", (lpObj->BanPost-time(NULL)));
//		return;
//	}
//#endif
////int PostLevel = GetPrivateProfileInt("Post","PostLevel",100,"..\\Data\\ExData\\Commands.ini");
//if(lpObj->Level < ExConfig.Command.PostLevel)
//{
//	MsgNormal(aIndex,"Need Level %d",ExConfig.Command.PostLevel);
//	return;
//}
////int PostMoney = GetPrivateProfileInt("Post","PostMoney",1000000,"..\\Data\\ExData\\Commands.ini");
//#if(_POST_FOR_PCPOINT_)
//if(ExConfig.Command.MoneyType == 1)
//{
//	if(lpObj->PCPoint < ExConfig.Command.PostPCPoint)
//	{
//		MsgNormal(aIndex,"Need Pc Point: %d",ExConfig.Command.PostPCPoint);
//		return;
//	}
//}
//else
//{
//	if(lpObj->Money < ExConfig.Command.PostMoney)
//	{
//		MsgNormal(aIndex,"Need Money: %d",ExConfig.Command.PostMoney);
//		return;
//	}
//}
//#else
//if(lpObj->Money < ExConfig.Command.PostMoney)
//{
//	MsgNormal(aIndex,"Need Money: %d",ExConfig.Command.PostMoney);
//	return;
//}
//#endif
//char Message[100];
//
////return;
//
//switch(ExConfig.Command.PostColor)
//{
//	case 1: sprintf(Message, "~%s %s",ExConfig.Command.PostPrist, szMsg);break;
//	case 2: sprintf(Message, "@%s %s",ExConfig.Command.PostPrist, szMsg);break;
//	case 3: sprintf(Message, "@@%s %s",ExConfig.Command.PostPrist, szMsg);break;
//	case 4: sprintf(Message, "%s %s",ExConfig.Command.PostPrist, szMsg);break;
//	default: sprintf(Message, "~%s %s",ExConfig.Command.PostPrist, szMsg);
//}
//if(ExConfig.Command.PostColor == 4)
//{
//	ChatMessageTwo(aIndex, Message);
//}
//else
//{
//	ChatMessageOne(aIndex, Message);
//}
//
//lpObj->Money -= ExConfig.Command.PostMoney;
//GCMoneySend(aIndex,lpObj->Money);
//
//}
//Command Add Str
void Ex_AddStr (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex, g_ExText.GetText(126), ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,g_ExText.GetText(127),ExConfig.Command.AddLeveL);
		return;
	}
	if (AddPoints>0 && AddPoints <= ExConfig.Character.MaxStats)
	{
		if((lpObj->Strength + AddPoints ) > ExConfig.Character.MaxStats)
			return;
		lpObj->Strength += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		GCMoneySend(aIndex,lpObj->Money);
		//ExUpdateStats(lpObj, AddPoints, 1);
		gObjCalCharacter(lpObj->m_Index);
		GCReFillSend(lpObj->m_Index,(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, lpObj->MaxBP);
		//GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
		UpdateCharInfo(aIndex);
	}
}
//Command Add Agi
void Ex_AddAgi (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex, g_ExText.GetText(126),ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,g_ExText.GetText(127),ExConfig.Command.AddLeveL);
		return;
	}
	if (AddPoints>0 && AddPoints <= ExConfig.Character.MaxStats)
	{
		if ((lpObj->Dexterity + AddPoints) > ExConfig.Character.MaxStats)
			return;
		lpObj->Dexterity += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		GCMoneySend(aIndex,lpObj->Money);
		//ExUpdateStats(lpObj, AddPoints, 2);
		gObjCalCharacter(lpObj->m_Index);
		GCReFillSend(lpObj->m_Index,(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, lpObj->MaxBP);
		//GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
		UpdateCharInfo(aIndex);
	}
}
//Command Add Vit
void Ex_AddVit (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex, g_ExText.GetText(126),ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,g_ExText.GetText(127),ExConfig.Command.AddLeveL);
		return;
	}
	if (AddPoints>0 && AddPoints <= ExConfig.Character.MaxStats)
	{
		if ((lpObj->Vitality + AddPoints ) > ExConfig.Character.MaxStats)
			return;
		lpObj->Vitality += AddPoints;
		lpObj->MaxLife += lpObj->VitalityToLife * AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		//if(lpObj->Type == CLASS_KNIGHT)
		//	lpObj->MaxLife += AddPoints * 3;
		//else
		//	lpObj->MaxLife += AddPoints * 2;
		GCMoneySend(aIndex,lpObj->Money);
		//ExUpdateStats(lpObj, AddPoints, 3);
		gObjCalCharacter(lpObj->m_Index);
		GCReFillSend(lpObj->m_Index,(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, lpObj->MaxBP);
		//GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
		UpdateCharInfo(aIndex);
	}
}
//Command Add Ene
void Ex_AddEne (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex, g_ExText.GetText(126),ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,g_ExText.GetText(127),ExConfig.Command.AddLeveL);
		return;
	}
	if (AddPoints>0 && AddPoints <= ExConfig.Character.MaxStats)
	{
		if ((lpObj->Energy + AddPoints ) > ExConfig.Character.MaxStats)
			return;
		lpObj->Energy += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		lpObj->MaxMana += AddPoints * 2;
		GCMoneySend(aIndex,lpObj->Money);
		//ExUpdateStats(lpObj, AddPoints, 4);
		gObjCalCharacter(lpObj->m_Index);
		GCReFillSend(lpObj->m_Index,(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, lpObj->MaxBP);
		//GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
		UpdateCharInfo(aIndex);
	}
}
//Command Add Cmd
void Ex_AddCmd (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->Class != 4)
		return;
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex, g_ExText.GetText(126),ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,g_ExText.GetText(127),ExConfig.Command.AddLeveL);
		return;
	}
	if(AddPoints>0 && AddPoints<=32767)
	{
		if((lpObj->Leadership + AddPoints) > 32767)
			return;
		lpObj->Leadership += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		GCMoneySend(aIndex,lpObj->Money);
		//ExUpdateStats(lpObj, AddPoints, 5);
		gObjCalCharacter(lpObj->m_Index);
		GCReFillSend(lpObj->m_Index,(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		GCManaSend(lpObj->m_Index, (lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, lpObj->MaxBP);
		//GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
		UpdateCharInfo(aIndex);
	}
}
//Command Ex_PkClear
void Ex_PkClear(int aIndex)
{
	//int Ex_PkClear_Enabled = GetPrivateProfileInt("PkClear","Enabled",1,"..\\Data\\ExData\\Commands.ini");
	if(!ExConfig.Command.Ex_PkClear_Enabled)
		return;
	LPOBJ lpObj = &gObj[aIndex];
	//int Ex_PkClearLevel = GetPrivateProfileInt("PkClear","PkClearLevel",0,"..\\Data\\ExData\\Commands.ini");
	if(ExConfig.Command.Ex_PkClearLevel > lpObj->Level)
	{
		MsgNormal(aIndex,g_ExText.GetText(128),ExConfig.Command.Ex_PkClearLevel);
		return;
	}
	//int Ex_PkClearMoney = GetPrivateProfileInt("PkClear","PkClearMoney",0,"..\\Data\\ExData\\Commands.ini");
	//int Ex_PKClearType = GetPrivateProfileInt("PkClear","PKClearType",0,"..\\Data\\ExData\\Commands.ini");
	if(lpObj->m_PK_Level <= 3)
		return;
	if(ExConfig.Command.Ex_PKClearType == 1)
	{
			int PkLevel = lpObj->m_PK_Level - 3;
			if(PkLevel == 0)
				return;
			int PkMoney = PkLevel * ExConfig.Command.Ex_PkClearMoney;
			if(PkMoney > lpObj->Money)
			{
				MsgNormal(aIndex,g_ExText.GetText(129),PkMoney);
				return;
			}
#ifdef PK_CLEAR_TO_CREDITS
			if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2))
			{
				int PkMoneyCredits = PkLevel * ExConfig.Command.Ex_PkClearCredits;
			
				if(PkMoneyCredits > lpObj->ExCred)
				{
					MsgNormal(aIndex,"[PkClear] Need %d Credits",PkMoneyCredits);
					return;
				}
				MsgNormal(aIndex,"[PkClear] Success Cost: Credit %d",PkMoneyCredits);
					
				lpObj->ExCred -= PkMoneyCredits;
				ExUserDataSend(aIndex);
			}
			
#endif // PK_CLEAR_TO_CREDITS

			lpObj->Money -= PkMoney;
			lpObj->m_PK_Level = 3;
			lpObj->m_PK_Count = 0;
#if(FIX_PKLEVEL)
			lpObj->m_PK_Time = 0;
#endif
			GCMoneySend(aIndex,lpObj->Money);
			GCPkLevelSend(aIndex,lpObj->m_PK_Level);
	}
	else if(ExConfig.Command.Ex_PKClearType == 2)
	{
			if(ExConfig.Command.Ex_PkClearMoney > lpObj->Money)
			{
				MsgNormal(aIndex,g_ExText.GetText(129),ExConfig.Command.Ex_PkClearMoney);
				return;
			}
#ifdef PK_CLEAR_TO_CREDITS
			if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(SILVER1) || g_ExLicense.CheckUser(SILVER2))
			{
				if(ExConfig.Command.Ex_PkClearCredits > lpObj->ExCred)
				{
					MsgNormal(aIndex,"[PkClear] Need %d Credits",ExConfig.Command.Ex_PkClearCredits);
					return;
				}
				MsgNormal(aIndex,"[PkClear] Success Cost: Credit %d",ExConfig.Command.Ex_PkClearCredits);
				lpObj->ExCred -= ExConfig.Command.Ex_PkClearCredits;
				ExUserDataSend(aIndex);
			}
#endif // PK_CLEAR_TO_CREDITS
			lpObj->Money -= ExConfig.Command.Ex_PkClearMoney;
			lpObj->m_PK_Level = 3;
			lpObj->m_PK_Count = 0;
			lpObj->m_PK_Time = 0;
			GCMoneySend(aIndex,lpObj->Money);
			GCPkLevelSend(aIndex,lpObj->m_PK_Level);
	}
	else
	{
			lpObj->m_PK_Level = 3;
			lpObj->m_PK_Count = 0;
			lpObj->m_PK_Time = 0;
			GCPkLevelSend(aIndex,lpObj->m_PK_Level);
	}
}