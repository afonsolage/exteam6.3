#include "StdAfx.h"
#include "user.h"
#include "OffExp.h"
#include "GameMain.h"
#include "Message.h"
#include "ObjUseSkill.h"
#include "MagicInf.h"
#include "SProtocol.h"
#include "ConnectEx.h"
#include "ExUser.h"
#include "ExLicense.h"
#include "ExFunction.h"
#include "ExText.h"

cOffExp OffExp;

void cOffExp::LoadConfig()
{
	//CheckFile(OFF_EXP_DIR);

	this->Enable = GetPrivateProfileInt("Common","Enable",1,OFF_EXP_DIR);
	this->KickFallen = GetPrivateProfileInt("Common","KickFallen",0,OFF_EXP_DIR);
	this->EnableTime = GetPrivateProfileInt("Common","EnableTime",0,OFF_EXP_DIR);
	this->TimeEnd = GetPrivateProfileInt("Common","Time",0,OFF_EXP_DIR);

	this->PriceZen = GetPrivateProfileInt("Common","PriceZen",0,OFF_EXP_DIR);
	this->PriceCredit = GetPrivateProfileInt("Common","PriceCredit",0,OFF_EXP_DIR);
	this->PriceWCoinC = GetPrivateProfileInt("Common","PriceWCoinC",0,OFF_EXP_DIR);
	this->PriceWCoinP = GetPrivateProfileInt("Common","PriceWCoinP",0,OFF_EXP_DIR);
	this->PriceGoblin = GetPrivateProfileInt("Common","PriceGoblin",0,OFF_EXP_DIR);

	this->TickPriceEnable = GetPrivateProfileInt("Common", "TickPriceEnable", 0, OFF_EXP_DIR);
	this->TickTimeMin = GetPrivateProfileInt("Common", "TickTimeMin", 0, OFF_EXP_DIR);
	this->TickPriceType = GetPrivateProfileInt("Common", "TickPriceType", 0, OFF_EXP_DIR);
	this->TickPrice = GetPrivateProfileInt("Common", "TickPrice", 0, OFF_EXP_DIR);
}

void cOffExp::OffExpStart(int aIndex, int Time)
{
	if(!this->Enable) return;
	
	LPOBJ lpObj = &gObj[aIndex];


	if(lpObj->MapNumber == MAP_INDEX_CASTLESIEGE)
	{
		MsgNormal(aIndex,"[OfflineExp] Disable in Castle siege map");
		return;
	}

	if (CheckTerrain(lpObj))
	{
		if(g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::drynea) || g_ExLicense.CheckUser(eExUB::Local2) || g_ExLicense.CheckUser(eExUB::Local))
		{
			if(this->PriceZen && (!lpObj->PremiumTime))
			{
				if(this->PriceZen > lpObj->Money)
				{
					MsgNormal(aIndex,"[OffExp] Need %d Zen",this->PriceZen);
					return;
				}
				lpObj->Money -= this->PriceZen;
				GCMoneySend(aIndex,lpObj->Money);
			}
			else if(this->PriceCredit && (!lpObj->PremiumTime))
			{
				if(this->PriceCredit > lpObj->ExCred)
				{
					MsgNormal(aIndex,"[OffExp] Need %d Credit",this->PriceCredit);
					return;
				}
				lpObj->ExCred -= this->PriceCredit;//Conflict
				ExUserDataSend(aIndex);
			}
			else if(this->PriceWCoinC && (!lpObj->PremiumTime))
			{
				if(this->PriceWCoinC > lpObj->GameShop.WCoinC)
				{
					MsgNormal(aIndex,"[OffExp] Need %d WCoinC",this->PriceWCoinC);
					return;
				}
				lpObj->GameShop.WCoinC -= this->PriceWCoinC;
				gGameShop.GDSaveUserInfo(aIndex);
			}
			else if(this->PriceWCoinP && (!lpObj->PremiumTime))
			{
				if(this->PriceWCoinP > lpObj->GameShop.WCoinP)
				{
					MsgNormal(aIndex,"[OffExp] Need %d WCoinP",this->PriceWCoinP);
					return;
				}
				lpObj->GameShop.WCoinP -= this->PriceWCoinP;
				gGameShop.GDSaveUserInfo(aIndex);
			}
			else if(this->PriceGoblin && (!lpObj->PremiumTime))
			{
				if(this->PriceGoblin > lpObj->GameShop.GoblinPoint)
				{
					MsgNormal(aIndex,"[OffExp] Need %d Goblin",this->PriceGoblin);
					return;
				}
				lpObj->GameShop.GoblinPoint -= this->PriceGoblin;
				gGameShop.GDSaveUserInfo(aIndex);
			}
		}
		else
		{
			if(this->PriceZen)
			{
				if(this->PriceZen > lpObj->Money)
				{
					MsgNormal(aIndex, g_ExText.GetText(239),this->PriceZen);
					return;
				}
				lpObj->Money -= this->PriceZen;
				GCMoneySend(aIndex,lpObj->Money);
			}
			else if(this->PriceCredit)
			{
				if(this->PriceCredit > lpObj->ExCred)
				{
					MsgNormal(aIndex,g_ExText.GetText(240),this->PriceCredit);
					return;
				}
				lpObj->ExCred -= this->PriceCredit;//Conflict
				ExUserDataSend(aIndex);
			}
			else if(this->PriceWCoinC)
			{
				if(this->PriceWCoinC > lpObj->GameShop.WCoinC)
				{
					MsgNormal(aIndex,g_ExText.GetText(241),this->PriceWCoinC);
					return;
				}
				lpObj->GameShop.WCoinC -= this->PriceWCoinC;
				gGameShop.GDSaveUserInfo(aIndex);
			}
			else if(this->PriceWCoinP)
			{
				if(this->PriceWCoinP > lpObj->GameShop.WCoinP)
				{
					MsgNormal(aIndex,g_ExText.GetText(242),this->PriceWCoinP);
					return;
				}
				lpObj->GameShop.WCoinP -= this->PriceWCoinP;
				gGameShop.GDSaveUserInfo(aIndex);
			}
			else if(this->PriceGoblin)
			{
				if(this->PriceGoblin > lpObj->GameShop.GoblinPoint)
				{
					MsgNormal(aIndex,g_ExText.GetText(243),this->PriceGoblin);
					return;
				}
				lpObj->GameShop.GoblinPoint -= this->PriceGoblin;
				gGameShop.GDSaveUserInfo(aIndex);
			}
		}
		//******
#ifdef _RECONNECT_
		g_ConnectEx.SendClose(aIndex,OFFAFK_DC);
#else
		CloseClient(aIndex);
		lpObj->OffExp = 1;
#endif
		if(this->EnableTime) lpObj->OffExpTick = 0;
	}
	else
	{
		MsgNormal(aIndex,g_ExText.GetText(244));
	}
}

void cOffExp::MainFunction(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(!lpObj->OffExp) return;

	// ----

	if(!this->CheckTerrain(lpObj))
	{
		if(this->KickFallen)
		{
			GJPUserClose(lpObj->AccountID);
			gObjDel(lpObj->m_Index);
			lpObj->OffExp = 0;
		}
		return;
	}

	// ----

	if(this->EnableTime)
	{
		lpObj->OffExpTick++;
		if(lpObj->OffExpTick >= this->TimeEnd)
		{
			GJPUserClose(lpObj->AccountID);
			gObjDel(lpObj->m_Index);
			lpObj->OffExp = 0;
			return;
		}
	}

	// ----

#ifdef PRIVATE_MODULE)
#ifdef DRYNEA_13_11
	if(g_ExLicense.CheckUser(eExUB::Vadim) || g_ExLicense.CheckUser(eExUB::drynea))
#else
	if(g_ExLicense.CheckUser(eExUB::Vadim))
#endif
	{
		if(lpObj->PremiumTime > 0)
		{
			lpObj->OffExpTickPRice = 0;
		}
		else
		{
			lpObj->OffExpTickPRice++;
		}
	}
	else
	{
		lpObj->OffExpTickPRice++;
	}
#else
	lpObj->OffExpTickPRice++;
#endif

	if (this->TickPriceEnable)
	{
		if (lpObj->OffExpTickPRice > (this->TickTimeMin * 60))
		{
			lpObj->OffExpTickPRice = 0;
			if (this->TickPriceType == 0)
			{
				if (this->TickPrice > lpObj->Money)
				{
					GJPUserClose(lpObj->AccountID);
					gObjDel(lpObj->m_Index);
					lpObj->OffExp = 0;
					return;
				}
				lpObj->Money -= this->TickPrice;
			}
			else if (this->TickPriceType == 1)
			{
				if (this->TickPrice > lpObj->ExCred)
				{
					GJPUserClose(lpObj->AccountID);
					gObjDel(lpObj->m_Index);
					lpObj->OffExp = 0;
					return;
				}
				lpObj->ExCred -= this->TickPrice;
			}
			else if (this->TickPriceType == 2)
			{
				if (this->TickPrice > lpObj->GameShop.WCoinC)
				{
					GJPUserClose(lpObj->AccountID);
					gObjDel(lpObj->m_Index);
					lpObj->OffExp = 0;
					return;
				}
				lpObj->GameShop.WCoinC -= this->TickPrice;
				gGameShop.GDSaveUserInfo(aIndex);
			}
			else if (this->TickPriceType == 3)
			{
				if (this->TickPrice > lpObj->GameShop.WCoinP)
				{
					GJPUserClose(lpObj->AccountID);
					gObjDel(lpObj->m_Index);
					lpObj->OffExp = 0;
					return;
				}
				lpObj->GameShop.WCoinP -= this->TickPrice;
				gGameShop.GDSaveUserInfo(aIndex);
			}
			else if (this->TickPriceType == 4)
			{
				if (this->TickPrice > lpObj->GameShop.GoblinPoint)
				{
					GJPUserClose(lpObj->AccountID);
					gObjDel(lpObj->m_Index);
					lpObj->OffExp = 0;
					return;
				}
				lpObj->GameShop.GoblinPoint -= this->TickPrice;
				gGameShop.GDSaveUserInfo(aIndex);
			}
		}
	}


	switch(lpObj->Class)
	{
		case 0:	this->DarkWizardOff(lpObj);		break;
		case 1:	this->DarkKnightOff(lpObj);		break;
		case 2:	this->FairyElfOff(lpObj);		break;
		case 3:	this->MagicGladiatorOff(lpObj);	break;
		case 4:	this->DarkLordOff(lpObj);		break;
		case 5:	this->SummonerOff(lpObj);		break;
		case 6: this->RageFighterOff(lpObj);	break;
	}
}
//=====================================
//	Dark Wizard Offline Experience
//=====================================
void cOffExp::DarkWizardOff(LPOBJ lpObj)
{
	int SearchSkill = 0;
	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 9) != NULL) SearchSkill = 9;
	else if(gObjGetMagicSearch( lpObj, 445) != NULL) SearchSkill = 445;
	else if(gObjGetMagicSearch( lpObj, 446) != NULL) SearchSkill = 446;
	else if(gObjGetMagicSearch( lpObj, 447) != NULL) SearchSkill = 447;
	else if(gObjGetMagicSearch( lpObj, 448) != NULL) SearchSkill = 448;
	else if(gObjGetMagicSearch( lpObj, 449) != NULL) SearchSkill = 449;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(6 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Dark Knight Offline Experience
//=====================================
void cOffExp::DarkKnightOff(LPOBJ lpObj)
{
	int SearchSkill = 0;
	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 41) != NULL) SearchSkill = 41;
	else if(gObjGetMagicSearch( lpObj, 455) != NULL) SearchSkill = 455;
	else if(gObjGetMagicSearch( lpObj, 456) != NULL) SearchSkill = 456;
	else if(gObjGetMagicSearch( lpObj, 457) != NULL) SearchSkill = 457;
	else if(gObjGetMagicSearch( lpObj, 458) != NULL) SearchSkill = 458;
	else if(gObjGetMagicSearch( lpObj, 459) != NULL) SearchSkill = 459;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(2 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Fairy Elf Offline Experience
//=====================================
void cOffExp::FairyElfOff(LPOBJ lpObj)
{
	int SearchSkill = 0;
	int dis;
	int tObjNum;
	BYTE attr;

	CMagicInf * lpMagic;

	//Buff
	SYSTEMTIME time;
	GetLocalTime(&time);
	if( time.wSecond == 0  || 
	    time.wSecond == 10 ||
	    time.wSecond == 20 ||
	    time.wSecond == 30 ||
	    time.wSecond == 40 ||
	    time.wSecond == 50 )
	{
		int partynum = -1;
		int partycount;
		int number;

		LPOBJ lpPartyObj;

		partynum = lpObj->PartyNumber;

		if(partynum != -1)
		{
			partycount = gParty.m_PartyS[partynum].Count;

			for(int j = 0; j < MAX_USER_IN_PARTY; j++)
			{
				number = gParty.m_PartyS[partynum].Number[j];

				if(number >= 0)
				{
					lpPartyObj = &gObj[number];

					if(lpObj->MapNumber == lpPartyObj->MapNumber)
					{
						dis = gObjCalDistance(lpObj,&gObj[number]);

						if(dis < 6)
						{
							////Defence Baf
							//lpMagic = gObjGetMagicSearch( lpObj, 27);
							//if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							////Damage Baf
							//lpMagic = gObjGetMagicSearch( lpObj, 28);
							//if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							////Heal Baf
							//lpMagic = gObjGetMagicSearch( lpObj, 26);
							//if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							//Defence Baf
							if(gObjGetMagicSearch( lpObj, 27) != NULL) SearchSkill = 27;
							else if(gObjGetMagicSearch( lpObj, 480) != NULL) SearchSkill = 480;
							else if(gObjGetMagicSearch( lpObj, 481) != NULL) SearchSkill = 481;
							else if(gObjGetMagicSearch( lpObj, 482) != NULL) SearchSkill = 482;
							else if(gObjGetMagicSearch( lpObj, 483) != NULL) SearchSkill = 483;
							else if(gObjGetMagicSearch( lpObj, 484) != NULL) SearchSkill = 484;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							//Damage Baf
							if(gObjGetMagicSearch( lpObj, 28) != NULL) SearchSkill = 28;
							else if(gObjGetMagicSearch( lpObj, 485) != NULL) SearchSkill = 485;
							else if(gObjGetMagicSearch( lpObj, 486) != NULL) SearchSkill = 486;
							else if(gObjGetMagicSearch( lpObj, 487) != NULL) SearchSkill = 487;
							else if(gObjGetMagicSearch( lpObj, 488) != NULL) SearchSkill = 488;
							else if(gObjGetMagicSearch( lpObj, 489) != NULL) SearchSkill = 489;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							//Heal Baf
							if(gObjGetMagicSearch( lpObj, 26) != NULL) SearchSkill = 26;
							else if(gObjGetMagicSearch( lpObj, 475) != NULL) SearchSkill = 475;
							else if(gObjGetMagicSearch( lpObj, 476) != NULL) SearchSkill = 476;
							else if(gObjGetMagicSearch( lpObj, 477) != NULL) SearchSkill = 477;
							else if(gObjGetMagicSearch( lpObj, 478) != NULL) SearchSkill = 478;
							else if(gObjGetMagicSearch( lpObj, 479) != NULL) SearchSkill = 479;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							}
						}
					}
				}
			}
		}
		else
		{
			//Defence Baf
			if(gObjGetMagicSearch( lpObj, 27) != NULL) SearchSkill = 27;
			else if(gObjGetMagicSearch( lpObj, 480) != NULL) SearchSkill = 480;
			else if(gObjGetMagicSearch( lpObj, 481) != NULL) SearchSkill = 481;
			else if(gObjGetMagicSearch( lpObj, 482) != NULL) SearchSkill = 482;
			else if(gObjGetMagicSearch( lpObj, 483) != NULL) SearchSkill = 483;
			else if(gObjGetMagicSearch( lpObj, 484) != NULL) SearchSkill = 484;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
			//Damage Baf
			if(gObjGetMagicSearch( lpObj, 28) != NULL) SearchSkill = 28;
			else if(gObjGetMagicSearch( lpObj, 485) != NULL) SearchSkill = 485;
			else if(gObjGetMagicSearch( lpObj, 486) != NULL) SearchSkill = 486;
			else if(gObjGetMagicSearch( lpObj, 487) != NULL) SearchSkill = 487;
			else if(gObjGetMagicSearch( lpObj, 488) != NULL) SearchSkill = 488;
			else if(gObjGetMagicSearch( lpObj, 489) != NULL) SearchSkill = 489;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
			//Heal Baf
			if(gObjGetMagicSearch( lpObj, 26) != NULL) SearchSkill = 26;
			else if(gObjGetMagicSearch( lpObj, 475) != NULL) SearchSkill = 475;
			else if(gObjGetMagicSearch( lpObj, 476) != NULL) SearchSkill = 476;
			else if(gObjGetMagicSearch( lpObj, 477) != NULL) SearchSkill = 477;
			else if(gObjGetMagicSearch( lpObj, 478) != NULL) SearchSkill = 478;
			else if(gObjGetMagicSearch( lpObj, 479) != NULL) SearchSkill = 479;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
		}
	}

	CItem * Right = &lpObj->pInventory[0];
	CItem * Left  = &lpObj->pInventory[1];

	if(Right->m_Type >= ITEMGET(4,0) && Right->m_Type <= ITEMGET(4,255) || Left->m_Type >= ITEMGET(4,0) && Left->m_Type <= ITEMGET(4,255))
	{
		lpMagic = gObjGetMagicSearch( lpObj, 235);	//Multi-Shot 235
		if(lpMagic==NULL) return;

		int NumDir[6] = {0, 50, 100, 150, 200, 250 };
		int StartDir = NumDir[rand()%6];
		gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,StartDir,0,-1);

		for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
		{
			tObjNum = lpObj->VpPlayer2[n].number;
			if(lpObj->VpPlayer2[n].state == 0) continue;
			if ( tObjNum >= 0 )
			{
				if ( gObj[tObjNum].Type == OBJ_MONSTER )
				{
					attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
					if ( (attr&1) != 1 )
					{
						dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
						if(5 >= dis)
						{
							gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0,0);
						}
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Magic Gladiator Offline Experience
//=====================================
void cOffExp::MagicGladiatorOff(LPOBJ lpObj)
{
	int skill;
	int NormDis;
	CMagicInf * lpMagic;
	int SearchSkill = 0;

	if(lpObj->pInventory[0].m_Type >= ITEMGET(5,0) && lpObj->pInventory[0].m_Type < ITEMGET(6,0))
	{
		if(gObjGetMagicSearch( lpObj, 9) != NULL) SearchSkill = 9;
		else if(gObjGetMagicSearch( lpObj, 530) != NULL) SearchSkill = 530;
		else if(gObjGetMagicSearch( lpObj, 531) != NULL) SearchSkill = 531;
		else if(gObjGetMagicSearch( lpObj, 532) != NULL) SearchSkill = 532;
		else if(gObjGetMagicSearch( lpObj, 533) != NULL) SearchSkill = 533;
		else if(gObjGetMagicSearch( lpObj, 534) != NULL) SearchSkill = 534;
		else return;
		skill = SearchSkill;
		NormDis = 6;
	}
	else
	{
		if(gObjGetMagicSearch( lpObj, 41) != NULL) SearchSkill = 41;
		else if(gObjGetMagicSearch( lpObj, 495) != NULL) SearchSkill = 495;
		else if(gObjGetMagicSearch( lpObj, 496) != NULL) SearchSkill = 496;
		else if(gObjGetMagicSearch( lpObj, 497) != NULL) SearchSkill = 497;
		else if(gObjGetMagicSearch( lpObj, 498) != NULL) SearchSkill = 498;
		else if(gObjGetMagicSearch( lpObj, 499) != NULL) SearchSkill = 499;
		else return;
		skill = SearchSkill;
		NormDis = 2;
	}

	lpMagic = gObjGetMagicSearch( lpObj, skill);	//Twisting Slash 41
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(NormDis >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Dark Lord Offline Experience
//=====================================
void cOffExp::DarkLordOff(LPOBJ lpObj)	//Work
{
	int Target = this->SearchTarget(lpObj);

	if(Target == -1) return;

	int SearchSkill = 0;
	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 61) != NULL) SearchSkill = 61;
	else if(gObjGetMagicSearch( lpObj, 520) != NULL) SearchSkill = 520;
	else if(gObjGetMagicSearch( lpObj, 521) != NULL) SearchSkill = 521;
	else if(gObjGetMagicSearch( lpObj, 522) != NULL) SearchSkill = 522;
	else if(gObjGetMagicSearch( lpObj, 523) != NULL) SearchSkill = 523;
	else if(gObjGetMagicSearch( lpObj, 524) != NULL) SearchSkill = 524;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index,Target, lpMagic); //

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Summoner Offline Experience
//=====================================
void cOffExp::SummonerOff(LPOBJ lpObj)
{
	CMagicInf * lpMagic;
	lpMagic = gObjGetMagicSearch( lpObj, 230);	//Lightning Shock
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(6 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}

//=====================================
//	Ragi Fighter Offline Experience
//=====================================
void cOffExp::RageFighterOff(LPOBJ lpObj)
{
	CMagicInf * lpMagic;
#ifdef TEST_OFFAFF_DARK_SIDE
	if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		lpMagic = gObjGetMagicSearch( lpObj, 263);
	}
	else
	{
		lpMagic = gObjGetMagicSearch( lpObj, 264);
	}
#else
	lpMagic = gObjGetMagicSearch( lpObj, 264);
#endif
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(6 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE, 0 , 0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}

int cOffExp::SearchTarget(LPOBJ lpObj)
{
	int dis;
	int searchtarget = -1;
	int tObjNum;
	BYTE attr;
	int TargetIndex[MAX_VIEWPORT_MONSTER];
	int TargetCount = 0;
	int IndexNumber;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(6 >= dis)
					{
						TargetIndex[TargetCount] = tObjNum;
						TargetCount++;
					}
				}
			}
		}
	}

	if(TargetCount == 0)	return -1;
	
	IndexNumber = rand()%TargetCount;

	searchtarget = TargetIndex[IndexNumber];

	return searchtarget;
}

void cOffExp::UseMana(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Mana > 100) return;
		
	int pos;

	pos = gObjGetManaItemPos(aIndex);

	if(pos == -1) return;

	if( lpObj->pInventory[pos].m_Type == ITEMGET(14,4) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,5) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,6)  )
	{
		int tMana = (lpObj->pInventory[pos].m_Value*10) - (gObj[aIndex].Level);

		if ( tMana < 0 )
		{
			tMana=0;
		}

		switch ( lpObj->pInventory[pos].m_Type )
		{
		case ITEMGET(14,4):
			tMana += ((int)(gObj[aIndex].MaxMana + gObj[aIndex].AddMana))*20/100; 
			break;
		case ITEMGET(14,5):
			tMana += ((int)(gObj[aIndex].MaxMana + gObj[aIndex].AddMana))*30/100; 
			break;
		case ITEMGET(14,6):
			tMana += ((int)(gObj[aIndex].MaxMana + gObj[aIndex].AddMana))*40/100; 
			break;
		}

		gObj[aIndex].Mana += tMana;

		if ( gObj[aIndex].Mana > (gObj[aIndex].MaxMana+gObj[aIndex].AddMana-1.0f) )
		{
			gObj[aIndex].Mana = gObj[aIndex].MaxMana+gObj[aIndex].AddMana;
		}

		GCManaSend(aIndex, (int)gObj[aIndex].Mana, 0xFF, 0, (int)gObj[aIndex].BP);

		if ( !gObjSearchItemMinus(&gObj[aIndex], pos, 1) )
		{
			gObjInventoryItemSet(aIndex, pos, -1);
			gObj[aIndex].pInventory[pos].Clear();
			GCInventoryItemDeleteSend(aIndex, pos, 1);
		}
	}
}


void cOffExp::UseLife(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Life > 100) return;
		
	int pos;

	pos = gObjGetLifeItemPos(aIndex);

	if(pos == -1) return;

	if( lpObj->pInventory[pos].m_Type == ITEMGET(14,0) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,1) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,2) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,3)  )
	{
		int tLife = (lpObj->pInventory[pos].m_Value*10) - (gObj[aIndex].Level);

		if ( tLife < 0 )
		{
			tLife=0;
		}

		switch ( lpObj->pInventory[pos].m_Type )
		{
			case ITEMGET(14,0):
			tLife += ((int)(gObj[aIndex].MaxLife + gObj[aIndex].AddLife))*20/100; 
			break;		
			case ITEMGET(14,1):
			tLife += ((int)(gObj[aIndex].MaxLife + gObj[aIndex].AddLife))*20/100; 
			break;
		case ITEMGET(14,2):
			tLife += ((int)(gObj[aIndex].MaxLife + gObj[aIndex].AddLife))*30/100; 
			break;
		case ITEMGET(14,3):
			tLife += ((int)(gObj[aIndex].MaxLife + gObj[aIndex].AddLife))*40/100; 
			break;
		}

		gObj[aIndex].Life += tLife;

		if ( gObj[aIndex].Life > (gObj[aIndex].MaxLife+gObj[aIndex].AddLife-1.0f) )
		{
			gObj[aIndex].Life = gObj[aIndex].MaxLife+gObj[aIndex].AddLife;
		}

		GCReFillSend(aIndex, (int)gObj[aIndex].Life, 0xFF, 0, (int)gObj[aIndex].BP);

		if ( !gObjSearchItemMinus(&gObj[aIndex], pos, 1) )
		{
			gObjInventoryItemSet(aIndex, pos, -1);
			gObj[aIndex].pInventory[pos].Clear();
			GCInventoryItemDeleteSend(aIndex, pos, 1);
		}
	}
}

bool cOffExp::CheckTerrain(LPOBJ lpObj)
{	
	BYTE attr = MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y);
	if ( (attr&1) != 1 )
	{
		return true;
	}
	else
	{
		return false;
	}
}