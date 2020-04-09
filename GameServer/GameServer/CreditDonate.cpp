#include "StdAfx.h"
#include "CreditDonate.h"
#include "Functions.h"
#include "CreditDonate.h"
#include "user.h"
#include "DSProtocol.h"
#include "logproc.h"
#include "..\\include\\ReadScript.h"
#include "..\\common\zzzitem.h"
#include "ExUser.h"
#include "..\common\SetItemOption.h"
#include "NewMasterLevelSkillTreeSystem.h"
#include "NewMasterLevelSystem.h"
#include "ExLicense.h"
#include "ExFunction.h"
#include "ExText.h"
#include "Reset.h"
#include "GrandReset.h"

cCreditDonate gCreditDonate;

int cCreditDonate::SetItemCount(int Type)
{
	if( ItemAttribute[Type].RequireClass[0] == 0 && 
		ItemAttribute[Type].RequireClass[1] == 0 &&   
		ItemAttribute[Type].RequireClass[2] == 0 && 
		ItemAttribute[Type].RequireClass[4] == 0 &&
		ItemAttribute[Type].RequireClass[5] == 0 )
	{
		if( ItemAttribute[Type].RequireClass[3] > 0 || ItemAttribute[Type].RequireClass[6] > 0 )
		{
			return 4;
		}
	}

	return 5;
}

int NumberFor100(int a)
{
	int b = 0;
	for(int i = 100; i < 10000; i+=100)
	{
		b++;
		if(a == i)
		{
			return b;
		}
	}
	return -1;
}

bool NormalItem(int Type, int Index)
{
	if(ITEMGET(Type, Index) < ITEMGET(11,255) ) return true;
	else return false;
}

void cCreditDonate::Load()
{
	this->Enable = GetPrivateProfileInt("ExTeam","Enable",0,CR_DONATE_DIR);
	this->SellProcent = GetPrivateProfileInt("ExTeam","SellProcent",0,CR_DONATE_DIR);

	this->BuyWcoinC = GetPrivateProfileInt("ExTeam","BuyWcoinC",0,CR_DONATE_DIR);
	this->BuyWcoinP = GetPrivateProfileInt("ExTeam","BuyWcoinP",0,CR_DONATE_DIR);
	this->BuyGoblin = GetPrivateProfileInt("ExTeam","BuyGoblin",0,CR_DONATE_DIR);
	this->BuyPremium = GetPrivateProfileInt("ExTeam","BuyPremium",0,CR_DONATE_DIR);

	this->ChangeClass = GetPrivateProfileInt("ExTeam","ChangeClass",0,CR_DONATE_DIR);
	this->ChangeCredit = GetPrivateProfileInt("ExTeam","ChangeCredit",0,CR_DONATE_DIR);
	this->ChangeWCoin = GetPrivateProfileInt("ExTeam","ChangeWCoin",0,CR_DONATE_DIR);

#ifdef PRIVATE_MODULE
	if(g_ExLicense.CheckUser(eExUB::Vadim))
	{
		this->premium_price_1 = GetPrivateProfileInt("ExTeam","premium_price_1",0,CR_DONATE_DIR);
		this->premium_price_7 = GetPrivateProfileInt("ExTeam","premium_price_7",0,CR_DONATE_DIR);
		this->premium_price_30 = GetPrivateProfileInt("ExTeam","premium_price_30",0,CR_DONATE_DIR);
	}
#endif

	// -> Evo
	this->m_MinResetChange = GetPrivateProfileInt("ExTeam","MinResetChange",0,CR_DONATE_DIR);
	this->m_MinGrandChange = GetPrivateProfileInt("ExTeam","MinGrandChange",0,CR_DONATE_DIR);
	this->m_ActiveDivResetChange = GetPrivateProfileInt("ExTeam","ActiveDivResetChange",0,CR_DONATE_DIR);
	this->m_MinusDivResetChange = GetPrivateProfileInt("ExTeam","MinusDivResetChange",0,CR_DONATE_DIR);
	this->m_ActiveDivGrandChange = GetPrivateProfileInt("ExTeam","ActiveDivGrandChange",0,CR_DONATE_DIR);
	this->m_MinusDivGrandChange = GetPrivateProfileInt("ExTeam","MinusDivGrandChange",0,CR_DONATE_DIR);
	this->m_StartDayChange = GetPrivateProfileInt("ExTeam","StartDayChange",-1,CR_DONATE_DIR);
	this->m_EndDayChange = GetPrivateProfileInt("ExTeam","EndDayChange",0,CR_DONATE_DIR);

	for(int i=0;i<MAX_DONATE_ITEM;i++)
	{
		this->Donate[i].cmd[0]	= 0;
		this->Donate[i].Type	= 0;
		this->Donate[i].Index	= 0;
		this->Donate[i].Level	= 0;
		this->Donate[i].Skill	= 0;
		this->Donate[i].Luck	= 0;
		this->Donate[i].Opt		= 0;
		this->Donate[i].Exl		= 0;
		this->Donate[i].Anc		= 0;
		this->Donate[i].CrPrice	= 0;
	}

	//CheckFile(CR_DONATE_DIR);

	FILE *file = fopen(CR_DONATE_DIR,"r");

	if(file == NULL)
	{
		this->Enable = 0;
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
			int n[9];
			char mes[100];

			sscanf(Buff,"\"%[^\"]\" %d %d %d %d %d %d %d %d %d",&mes,&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7],&n[8]);

			sprintf(this->Donate[this->Count].cmd,"%s",mes);

			if(n[0] == -1) continue;

			this->Donate[this->Count].Type		= n[0];
			this->Donate[this->Count].Index		= n[1];
			this->Donate[this->Count].Level		= n[2];
			this->Donate[this->Count].Skill		= n[3];
			this->Donate[this->Count].Luck		= n[4];
			this->Donate[this->Count].Opt		= n[5];
			this->Donate[this->Count].Exl		= n[6];
			this->Donate[this->Count].Anc		= n[7];

			this->Donate[this->Count].CrPrice	= n[8];

			if(this->Donate[this->Count].Skill) this->Donate[this->Count].Skill = 1;
			if(this->Donate[this->Count].Luck) this->Donate[this->Count].Luck = 1;

			this->Count++;

			if (this->Count>=MAX_DONATE_ITEM)
			{
				break;
			}
		}
	}
	fclose(file);
}

void cCreditDonate::Chat(int aIndex , char* Message, int Count)
{
	if(!this->Enable) return;

	LPOBJ lpObj = &gObj[aIndex];
	if(Count)
	{
		if(!strcmp(Message,"wcoinc") && this->BuyWcoinC)
		{
			int b = NumberFor100(Count);
			if(b == -1)
			{
				MsgOutput(aIndex,g_ExText.GetText(113));
				return;
			}
			if(b > lpObj->ExCred )
			{
				MsgOutput(aIndex,g_ExText.GetText(114),b);
				return;
			}
			lpObj->ExCred -= b;
			lpObj->GameShop.WCoinC += Count;

			gGameShop.GDSaveUserInfo(aIndex);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ExUserDataSend(aIndex);
		}
		else if(!strcmp(Message,"wcoinp") && this->BuyWcoinP)
		{
			int b = NumberFor100(Count);
			if(b == -1)
			{
				MsgOutput(aIndex,g_ExText.GetText(115));
				return;
			}
			if(b > lpObj->ExCred )
			{
				MsgOutput(aIndex,g_ExText.GetText(116),b);
				return;
			}
			lpObj->ExCred -= b;
			lpObj->GameShop.WCoinP += Count;

			gGameShop.GDSaveUserInfo(aIndex);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ExUserDataSend(aIndex);
		}
		else if(!strcmp(Message,"goblin") && this->BuyGoblin)
		{
			int b = NumberFor100(Count);
			if(b == -1)
			{
				MsgOutput(aIndex,g_ExText.GetText(117));
				return;
			}
			if(b > lpObj->ExCred )
			{
				MsgOutput(aIndex,g_ExText.GetText(118),b);
				return;
			}
			lpObj->ExCred -= b;
			lpObj->GameShop.GoblinPoint += Count;

			gGameShop.GDSaveUserInfo(aIndex);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ExUserDataSend(aIndex);
		}
		else if(!strcmp(Message,"premium") && this->BuyPremium)
		{
#ifdef PRIVATE_MODULE
			if(g_ExLicense.CheckUser(eExUB::Vadim))
			{
				if(Count == 1)
				{
					if(this->premium_price_1 > lpObj->ExCred)
					{
						MsgOutput(aIndex,g_ExText.GetText(119),this->premium_price_1);
						return;
					}
					lpObj->ExCred -= this->premium_price_1;
					lpObj->PremiumTime += ( 1 * 86400 );
#ifndef FIX_DS_CRASH
					GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
					ExUserDataSend(aIndex);
				}
				else if(Count == 2)
				{
					if(this->premium_price_7 > lpObj->ExCred)
					{
						MsgOutput(aIndex,g_ExText.GetText(119),this->premium_price_7);
						return;
					}
					lpObj->ExCred -= this->premium_price_7;
					lpObj->PremiumTime += ( 7 * 86400 );
#ifndef FIX_DS_CRASH
					GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
					ExUserDataSend(aIndex);
				}
				else if(Count == 3)
				{
					if(this->premium_price_30 > lpObj->ExCred)
					{
						MsgOutput(aIndex,g_ExText.GetText(119),this->premium_price_30);
						return;
					}
					lpObj->ExCred -= this->premium_price_30;
					lpObj->PremiumTime += ( 30 * 86400 );
#ifndef FIX_DS_CRASH
					GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
					ExUserDataSend(aIndex);
				}
			}
			else
			{
				if(Count > lpObj->ExCred)
				{
					MsgOutput(aIndex,g_ExText.GetText(119),Count);
					return;
				}
				lpObj->ExCred -= Count;
				lpObj->PremiumTime += ( Count * 86400 );
#ifndef FIX_DS_CRASH
				GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
				ExUserDataSend(aIndex);
			}
#else
			if(Count > lpObj->ExCred)
			{
				MsgOutput(aIndex,"[Credit Donate]:Buy Premium Need %d",Count);
				return;
			}
			lpObj->ExCred -= Count;
			lpObj->PremiumTime += ( Count * 86400 );
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ExUserDataSend(aIndex);
#endif
		}
	}
	else
	{
		for(int i=0;i<this->Count;i++)
		{
			if(this->Donate[i].cmd[0] == Message[0])
			{
				if(!strcmp(Message,this->Donate[i].cmd))
				{
					//if ( CheckInventoryEmptySpace(lpObj,4,8) == false )

					int iHeight = ItemAttribute[ITEMGET(this->Donate[i].Type,this->Donate[i].Index)].Height;
					int iWidth = ItemAttribute[ITEMGET(this->Donate[i].Type,this->Donate[i].Index)].Width;
					
					if ( CheckInventoryEmptySpace(lpObj,iHeight,iWidth) == false )
					{
						MsgOutput(aIndex,g_ExText.GetText(120),iHeight,iWidth);
						//GCServerMsgStringSend("[Credit Donate]: Need to make space in the inventory (4x8)",aIndex,1);
						return;
					}

					if(this->Donate[i].CrPrice > lpObj->ExCred)
					{
						MsgOutput(aIndex,g_ExText.GetText(121),this->Donate[i].CrPrice);
						return;
					}

					lpObj->ExCred -= this->Donate[i].CrPrice;

					//if(this->Donate[i].Type == -1)
					//{
					//	ItemSerialCreateSend(aIndex,235,1,1,ITEMGET(7,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
					//	ItemSerialCreateSend(aIndex,235,1,1,ITEMGET(8,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
					//	ItemSerialCreateSend(aIndex,235,1,1,ITEMGET(9,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
					//	ItemSerialCreateSend(aIndex,235,1,1,ITEMGET(10,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
					//	ItemSerialCreateSend(aIndex,235,1,1,ITEMGET(11,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
					//}
					//else
					//{
						ItemSerialCreateSend(aIndex,235,lpObj->X,lpObj->Y,ITEMGET(this->Donate[i].Type,this->Donate[i].Index),this->Donate[i].Level,0,this->Donate[i].Skill,this->Donate[i].Luck,this->Donate[i].Opt,aIndex,this->Donate[i].Exl,this->Donate[i].Anc);
					//}

					MsgOutput(aIndex,g_ExText.GetText(122),this->Donate[i].cmd,this->Donate[i].CrPrice);

					ExUserDataSend(aIndex);
			
					return;
				}
			}
		}		
	}
}

bool cCreditDonate::Sell(int aIndex, int Pos, int &iAddZen)
{
	if(!this->Enable) return false;

	LPOBJ lpObj = &gObj[aIndex];

	//if(lpObj->pInventory[Pos].m_Number != 1 && lpObj->pInventory[Pos].m_Number != 2)
	//{
	//	return;
	//}

	for(int i=0;i<this->Count;i++)
	{
		bool bItems = NormalItem(this->Donate[i].Type,this->Donate[i].Index);

		if(
			lpObj->pInventory[Pos].m_Type == ITEMGET(this->Donate[i].Type,this->Donate[i].Index) && 
			lpObj->pInventory[Pos].m_Level == this->Donate[i].Level &&
			lpObj->pInventory[Pos].m_Option2 == this->Donate[i].Luck &&
			lpObj->pInventory[Pos].m_Option3 >= this->Donate[i].Opt &&
			CheckOptions(bItems, lpObj->pInventory[Pos].m_NewOption, this->Donate[i].Exl) &&
			lpObj->pInventory[Pos].m_SetOption == this->Donate[i].Anc
			)
		{
			float NewPrice = this->Donate[i].CrPrice;
			float CrSell = NewPrice - ( ( NewPrice * this->SellProcent ) / 100 );
			//if(lpObj->pInventory[Pos].m_SetOption)
			//{
			//	CrSell += 10;
			//}
			lpObj->ExCred += CrSell;
			MsgOutput(aIndex,g_ExText.GetText(123),CrSell);
#ifndef FIX_DS_CRASH
			GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
#endif
			ExUserDataSend(aIndex);
			iAddZen = 0;
			return true;
		}
		//else if( lpObj->pInventory[Pos].m_Number == 1 &&
		//	this->Donate[i].Type == -1 && lpObj->pInventory[Pos].m_Type % 512 == this->Donate[i].Index && 
		//	lpObj->pInventory[Pos].m_Level == this->Donate[i].Level &&
		//	CheckOptions(lpObj->pInventory[Pos].m_NewOption, this->Donate[i].Exl))
		//{
		//	float NewPrice = this->Donate[i].CrPrice / SetItemCount(lpObj->pInventory[Pos].m_Type);
		//	float CrSell = NewPrice - ( ( NewPrice * this->SellProcent ) / 100 );
		//	if(lpObj->pInventory[Pos].m_SetOption)
		//	{
		//		CrSell += 10;
		//	}
		//	lpObj->ExCred += CrSell;
		//	MsgOutput(aIndex,"[Credit Donate]: Sell %.2f Credits",CrSell);

		//	GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
		//	ExUserDataSend(aIndex);
		//	iAddZen = 0;
		//	return;
		//}
	}
}

void cCreditDonate::exClass(int aIndex, char* Message)
{
	if(!this->ChangeClass)
	{
		return;
	}
	LPOBJ lpObj = &gObj[aIndex];

	BYTE NewClass;

	if(!strcmp(Message,"wizard") && lpObj->Class != CLASS_WIZARD)
	{
		NewClass = 0;
	}
	else if(!strcmp(Message,"knight") && lpObj->Class != CLASS_KNIGHT)
	{
		NewClass = 16;
	}
	else if(!strcmp(Message,"elf") && lpObj->Class != CLASS_ELF)
	{
		NewClass = 32;
	}
	else if(!strcmp(Message,"magic") && lpObj->Class != CLASS_MAGUMSA)
	{
		NewClass = 48;
	}
	else if(!strcmp(Message,"lord") && lpObj->Class != CLASS_DARKLORD)
	{
		NewClass = 64;
	}		
	else if(!strcmp(Message,"summoner") && lpObj->Class != CLASS_SUMMONER)
	{
		NewClass = 80;
	}
	else if(!strcmp(Message,"monk") && lpObj->Class != CLASS_MONK)
	{
		NewClass = 96;
	}
	else
	{
		return;
	}

	for ( int i=0;i<INVETORY_WEAR_SIZE;i++)
	{
		if ( lpObj->pInventory[i].IsItem() )
		{
			MsgOutput(aIndex,g_ExText.GetText(124));
			return;
		}
	}

	if(this->ChangeCredit > lpObj->ExCred)
	{
		MsgOutput(aIndex,g_ExText.GetText(125),this->ChangeCredit);
		return;
	}

	lpObj->ExCred -= this->ChangeCredit;

	lpObj->DbClass = NewClass;

	for (int i=0;i<MAX_MAGIC ; i++)
	{
		lpObj->Magic[i].Clear(); //Changed
	}

	g_MasterSkillSystem.ClearPassiveSkill(lpObj);
	memset(lpObj->m_Quest, 0xFF, sizeof(lpObj->m_Quest));
	gObjCloseSet(aIndex, 1);


}

void cCreditDonate::GCChangeClassConfig(int aIndex)
{
	if( !g_ExLicense.CheckUser(eExUB::Local) && 
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::EpicMU) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!THINNAKORN_MAC)
	{
		return;
	}

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_GC_CHANGECLASS_CONFIG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x40, sizeof(pMsg));
	pMsg.iChangeClassWcoinPrice = this->ChangeWCoin;
	pMsg.iChangeClassCreditPrice = this->ChangeCredit;
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void cCreditDonate::CGChangeClass(PMSG_CG_CHANGECLASS* aRecv, int aIndex)
{
	if( !g_ExLicense.CheckUser(eExUB::Local) && 
		!g_ExLicense.CheckUser(eExUB::Gredy) &&
		!g_ExLicense.CheckUser(eExUB::Gredy2) && 
		!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
		!g_ExLicense.CheckUser(eExUB::EpicMU) &&
		!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
		!THINNAKORN_MAC)
	{
		return;
	}

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}
	/*
	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))	
	{
		SYSTEMTIME systime;
		GetLocalTime(&systime);

		if(this->m_StartDayChange >= systime.wDayOfWeek && systime.wDayOfWeek <= this->m_EndDayChange )
		{
			if(this->m_MinResetChange > lpUser->Reset)
			{
				MsgOutput(aIndex, "[Change Class]: Min Reset %d", this->m_MinResetChange);
				return;
			}

			if(this->m_MinGrandChange > lpUser->GReset)
			{
				MsgOutput(aIndex, "[Change Class]: Min Grand %d", this->m_MinResetChange);
				return;
			}
		}
		else
		{
			MsgOutput(aIndex, "[Change Class]: Day Of Week %d - %d", this->m_StartDayChange, this->m_EndDayChange);
			return;
		}
	}
	*/
	BYTE NewClass = aRecv->iNewClass;
	BYTE btPriceType = aRecv->PriceType;

	if(NewClass == CLASS_WIZARD && lpUser->Class != CLASS_WIZARD)
	{
		NewClass = 0;
	}
	else if(NewClass == CLASS_KNIGHT && lpUser->Class != CLASS_KNIGHT)
	{
		NewClass = 16;
	}
	else if(NewClass == CLASS_ELF && lpUser->Class != CLASS_ELF)
	{
		NewClass = 32;
	}
	else if(NewClass == CLASS_MAGUMSA && lpUser->Class != CLASS_MAGUMSA)
	{
		NewClass = 48;
	}
	else if(NewClass == CLASS_DARKLORD && lpUser->Class != CLASS_DARKLORD)
	{
		NewClass = 64;
	}		
	else if(NewClass == CLASS_SUMMONER && lpUser->Class != CLASS_SUMMONER)
	{
		NewClass = 80;
	}
	else if(NewClass == CLASS_MONK && lpUser->Class != CLASS_MONK)
	{
		NewClass = 96;
	}
	else
	{
		MsgOutput(aIndex,"[Change Class]: class busy");
		return;
	}

	for ( int i=0;i<INVETORY_WEAR_SIZE;i++)
	{
		if ( lpUser->pInventory[i].IsItem() )
		{
			MsgOutput(aIndex,"[Change Class]: You need Empty Inventory");
			return;
		}
	}

	if(btPriceType == 0)
	{
		if(this->ChangeCredit > lpUser->ExCred)
		{
			MsgOutput(aIndex,"[Change Class]: Need %d Credit",this->ChangeCredit);
			return;
		}
		lpUser->ExCred -= this->ChangeCredit;
	}
	else if(btPriceType == 1)
	{
		if(this->ChangeWCoin > lpUser->GameShop.WCoinC)
		{
			MsgOutput(aIndex,"[Change Class]: Need %d WCoin",this->ChangeWCoin);
			return;
		}
		lpUser->GameShop.WCoinC -= this->ChangeWCoin;
	}

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))	
	{
		if(this->m_ActiveDivResetChange)
		{
			lpUser->Reset = lpUser->Reset / this->m_MinusDivResetChange;
		}

		if(this->m_MinusDivGrandChange)
		{
			lpUser->GReset = lpUser->GReset / this->m_MinusDivGrandChange;
		}
	}

	lpUser->DbClass = NewClass;

	for (int i=0;i<MAX_MAGIC ; i++)
	{
		lpUser->Magic[i].Clear();
	}

	g_MasterSkillSystem.ClearPassiveSkill(lpUser);

	if(g_ExLicense.CheckUser(eExUB::Local) ||	
	   g_ExLicense.CheckUser(eExUB::Gredy) ||
	   g_ExLicense.CheckUser(eExUB::Gredy2) || 
	   g_ExLicense.CheckUser(eExUB::GredyLocal))
	{

#if(EVO_CREDITDONATE)

		if(aRecv->iNewClass == CLASS_WIZARD ||
			aRecv->iNewClass == CLASS_KNIGHT || 
			aRecv->iNewClass == CLASS_ELF ||
			aRecv->iNewClass == CLASS_SUMMONER )
		{
			if(lpUser->ChangeUP)
			{
				lpUser->DbClass += 1;
			}
		}

		if(lpUser->ChangeUP3rd)
		{
			lpUser->DbClass += 2;
		}

		/*
		if(aRecv->iNewClass == CLASS_KNIGHT)
		{
			g_QuestInfo.SetQuestState(lpUser, 2, 1);
			g_QuestInfo.SetQuestState(lpUser, 3, 1);
		}
		*/

		lpUser->Strength = 25;
		lpUser->Dexterity = 25;
		lpUser->Vitality = 25;
		lpUser->Energy = 25;

		if(lpUser->Class == 4)
		{
			lpUser->Leadership = 25;
		}

		lpUser->ChangeUP = 0;
		lpUser->ChangeUP3rd = 0;
		lpUser->LevelUpPoint = 0;

		//Поинта за ресет
		int addPoint = gResetSystem.GetAddPoints(lpUser->m_Index);
		lpUser->LevelUpPoint += ( lpUser->Reset + 1 ) * addPoint;

		//Поинта от гранд ресета
		if(gGrandReset.EnableGrandResetSystem)
		{
			if(lpUser->GReset > 0)
			{
				if(gGrandReset.AddForm == 1 || gGrandReset.AddForm == 2)
				{
					switch (aRecv->iNewClass)
					{
						case 0: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDW ;  break;
						case 1: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDK ;  break;
						case 2: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsELF ; break;
						case 3: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsMG ;  break;
						case 4: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDL ;  break;
						case 5: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsSUM ; break;
						case 6: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsRF ; break;
					}
				}
				else if(gGrandReset.AddForm == 3)
				{
					switch (aRecv->iNewClass)
					{
						case 0: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDW  * ( lpUser->Reset+1 ); break;
						case 1: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDK  * ( lpUser->Reset+1 ); break;
						case 2: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsELF * ( lpUser->Reset+1 ); break;
						case 3: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsMG  * ( lpUser->Reset+1 ); break;
						case 4: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsDL  * ( lpUser->Reset+1 ); break;
						case 5: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsSUM * ( lpUser->Reset+1 ); break;
						case 6: lpUser->LevelUpPoint += lpUser->GReset * gGrandReset.AddPointsRF * ( lpUser->Reset+1 ); break;
					}
				}
			}
		}

		lpUser->LevelUpPoint += lpUser->ExFreePoints;



#endif

	}
	else
	{
		memset(lpUser->m_Quest, 0xFF, sizeof(lpUser->m_Quest));
	}

	// ---------------
	
	gObjCloseSet(aIndex, 2);
}

int cCreditDonate::GetClassID(int aIndex, int NewClass)
{
	LPOBJ lpUser = &gObj[aIndex];

	if(NewClass == CLASS_WIZARD && lpUser->Class != CLASS_WIZARD)
	{
		NewClass = 16;
	}
	else if(NewClass == CLASS_KNIGHT && lpUser->Class != CLASS_KNIGHT)
	{
		NewClass = 16;
	}
	else if(NewClass == CLASS_ELF && lpUser->Class != CLASS_ELF)
	{
		NewClass = 32;
	}
	else if(NewClass == CLASS_MAGUMSA && lpUser->Class != CLASS_MAGUMSA)
	{
		NewClass = 48;
	}
	else if(NewClass == CLASS_DARKLORD && lpUser->Class != CLASS_DARKLORD)
	{
		NewClass = 64;
	}		
	else if(NewClass == CLASS_SUMMONER && lpUser->Class != CLASS_SUMMONER)
	{
		NewClass = 80;
	}
	else if(NewClass == CLASS_MONK && lpUser->Class != CLASS_MONK)
	{
		NewClass = 96;
	}
	else
	{
		MsgOutput(aIndex,"[Change Class]: class busy");
		return -1;
	}
}