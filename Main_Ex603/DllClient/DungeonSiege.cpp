#include "stdafx.h"
#include "DungeonSiege.h"
#include "Interface.h"
#include "Console.h"
#include "User.h"
#include "ExMenuV3.h"
#include "ExLicense.h"

#if(EVENT_DUNGEON_SIEGE)

CDungeonSiege g_DungeonSiege;

CDungeonSiege::CDungeonSiege()
{
	this->Init();
}

CDungeonSiege::~CDungeonSiege()
{
}
		 
void CDungeonSiege::Init()
{
	this->bRegistration = false;
	this->iMsgCode = 0;
	this->bCaptured = false;
	this->PlayerGuildNumber = 0;
	this->ireg_list_count = 0;
	this->iEventStatus = eEVENTDUNGEON_CLOSE;
	memset(this->szLordGuild, 0, sizeof(this->szLordGuild));
	memset(this->reg_list, 0, sizeof(this->reg_list));
	GetVolumeInformationA("c:\\", 0, 0, &this->dwHWID, 0, 0, 0, 0); 
	this->m_mysocre = 0;
	for(int i = 0; i < 10; i++)
	{
		this->m_guildscore[i] = 0;
	}
	this->m_finalscore1 = 0;
	this->m_finalscore2 = 0;
	this->m_finalguild1 = 0;
	this->m_finalguild2 = 0;
	memset(this->m_finalname1, 0, sizeof(this->m_finalname1));
	memset(this->m_finalname2, 0, sizeof(this->m_finalname2));
	memset(this->m_EventName, 0, sizeof(this->m_EventName));
	this->m_insiege = false;
}

void CDungeonSiege::Load()
{

}

void CDungeonSiege::BindImages()
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	gInterface.BindObject(ePT_DUNGEON_SIEGE_MAIN, 0x7A5A, 222, 407, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_DIV2, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_REG, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_NAME, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_NAME2, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD1, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD2, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD3, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD4, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD5, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD6, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD7, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD8, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD9, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILD10, ex_SMITHY_TEXT, 170, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_NAMEOWNER, 0x7BAC, 168, 18, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_DIVOWNER, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePT_DUNGEON_SIEGE_GUILDOWNER, ex_SMITHY_TEXT, 170, 21, -1, -1);
}

void CDungeonSiege::Draw()
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	this->SetPKLevelTarget();
	this->DrawRanking();

	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinDungeonSiege))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color				= eWhite;
	float StartY			= 10.0;
	float StartX			= 205.0;
	float ContentX          = StartX;
	float ContentY			= StartY;
	float ButtonX			= StartX + 84;

	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_MAIN, StartX, StartY+2);
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ePT_DUNGEON_SIEGE_FRAME, StartX, StartY+67.0, 20);
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_FOOTER, StartX, StartY);

	ContentY += 10;
	gInterface.DrawFormat(eGold, ContentX, ContentY, 230, 3, this->m_EventName);

	ContentY += 18;
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_NAMEOWNER, ContentX+30, ContentY);
	gInterface.DrawFormat(eWhite, ContentX, ContentY+2, 230, 3, "Siege Owner");
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_GUILDOWNER, (ContentX+28), (ContentY+20));
	if(this->bCaptured)
	{
		gInterface.DrawFormat(eAncient, ContentX, (ContentY+25), 230, 3, this->szLordGuild);
	}
	else
	{
		gInterface.DrawFormat(eAncient, ContentX, (ContentY+25), 230, 3, "no castle owner");
	}
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_DIVOWNER, ContentX, (ContentY+35));

	ContentY += 48;
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_NAME, ContentX+30, ContentY);
	gInterface.DrawFormat(eWhite, ContentX, ContentY+2, 230, 3, "Registration guild on siege");
	
	ContentY += 16;
	switch(this->iMsgCode)
	{
		case 0: gInterface.DrawFormat(eExcellent, ContentX, ContentY+2, 230, 3, "You can register"); break;
		case 1: gInterface.DrawFormat(eRed, ContentX, ContentY+2, 230, 3, "You are not in a guild"); break;
		case 2: gInterface.DrawFormat(eRed, ContentX, ContentY+2, 230, 3, "You are not a Guild Master"); break;
		case 3: gInterface.DrawFormat(eRed, ContentX, ContentY+2, 230, 3, "You are the owners of the Dungeon castle"); break;
		case 4: gInterface.DrawFormat(eRed, ContentX, ContentY+2, 230, 3, "The max number of guild siege on 10"); break;
		case 5: gInterface.DrawFormat(eRed, ContentX, ContentY+2, 230, 3, "To register for the siege should be min 10 player in guild"); break;
		case 6: gInterface.DrawFormat(eRed, ContentX, ContentY+2, 230, 3, "Your guild is already registered"); break;
	}
	
	ContentY += 16;
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_REG, ButtonX, ContentY);
	gInterface.DrawFormat(eWhite, ContentX, ContentY+10, 230, 3, "Registration");
	gInterface.Data[ePT_DUNGEON_SIEGE_REG].Attribute = this->bRegistration;
	if(!this->bRegistration)
	{
		gInterface.DrawColoredGUIObj(ePT_DUNGEON_SIEGE_REG, gInterface.Data[ePT_DUNGEON_SIEGE_REG].X, gInterface.Data[ePT_DUNGEON_SIEGE_REG].Y, eGray150);
	}
	else
	{
		if(gInterface.IsWorkZoneObj(ePT_DUNGEON_SIEGE_REG))
		{
			Color = eGray100;
			if(gInterface.Data[ePT_DUNGEON_SIEGE_REG].OnClick)
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUIObj(ePT_DUNGEON_SIEGE_REG, gInterface.Data[ePT_DUNGEON_SIEGE_REG].X, gInterface.Data[ePT_DUNGEON_SIEGE_REG].Y, Color);
		}
	}

	ContentY += 25;
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_DIV, ContentX, ContentY);

	ContentY += 13;
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_NAME2, ContentX+30, ContentY);
	gInterface.DrawFormat(eWhite, ContentX, ContentY+2, 230, 3, "Guild registered for the siege");

	float GuildX = ContentX + 28;
	float GuildY = ContentY;
	for(int i = 0; i < this->ireg_list_count; i++)
	{
		int iObj = ePT_DUNGEON_SIEGE_GUILD1 + i;
		GuildY += 20;
		gInterface.DrawGUI(iObj, GuildX, GuildY);
		gInterface.DrawFormat(eYellow, (GuildX-28), (GuildY+5), 230, 3, this->reg_list[i].szGuildName);
	}

	ContentY += 215;
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_DIV2, ContentX, ContentY);

	ContentY += 16;
	gInterface.DrawGUI(ePT_DUNGEON_SIEGE_OK, ButtonX, ContentY);
	gInterface.DrawFormat(eWhite, ContentX, ContentY+10, 230, 3, "Ok");
	if(gInterface.IsWorkZoneObj(ePT_DUNGEON_SIEGE_OK))
	{
		Color = eGray100;
		if(gInterface.Data[ePT_DUNGEON_SIEGE_OK].OnClick)
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUIObj(ePT_DUNGEON_SIEGE_OK, gInterface.Data[ePT_DUNGEON_SIEGE_OK].X, gInterface.Data[ePT_DUNGEON_SIEGE_OK].Y, Color);
	}
}

void CDungeonSiege::Button(DWORD Event)
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinDungeonSiege))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, ePT_DUNGEON_SIEGE_REG, true))
	{
		PMSG_PROTOCOL_RESULT pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x44,  sizeof(pMsg));
		pMsg.Result = true;
		gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));
	}
	else if(gInterface.ButtonEx(Event, ePT_DUNGEON_SIEGE_OK, false))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinDungeonSiege);
	}
}

void CDungeonSiege::GCNpcInfo(PMSG_GC_DUNGEON_SIEGE_NPC* lpMsg)
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	char szOwName[9];
	memset(this->reg_list, 0, sizeof(this->reg_list));

	szOwName[8] = 0;
	this->bCaptured = lpMsg->Captured;
	memcpy(szOwName, lpMsg->szGuildOwner, 8);
	memcpy(this->szLordGuild, szOwName, 8);

	this->bRegistration = lpMsg->bResultReg;
	this->iMsgCode = lpMsg->iMsgCode;
	this->ireg_list_count = lpMsg->iCountGuild;

	for(int i = 0; i < this->ireg_list_count; i++)
	{
		char szGName[9];
		szGName[8] = 0;
		memcpy(szGName, lpMsg->szGuildName[i], 8);
		memcpy(this->reg_list[i].szGuildName, szGName, 8);	
	}

	gInterface.OpenWindowEx(ObjWindowsEx::exWinDungeonSiege);
}

void CDungeonSiege::CGHWID()
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	PMSG_CG_DUNBEON_SIEGE_HWID pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x45,  sizeof(pMsg));
	pMsg.dwHWID = this->dwHWID;
	gProtocol.DataSend((LPBYTE)&pMsg, sizeof(pMsg));
}

void CDungeonSiege::GCVieweSiege(LPBYTE aRecv)
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	memset(this->m_viewe, 0, sizeof(this->m_viewe));

	int datasize = 6;
	int excount = aRecv[datasize-1];

	for (int n = 0; n < excount; n++)
	{
		DUNGEON_VIEWE Vp;
		memcpy(&Vp,&aRecv[datasize],sizeof(Vp));

		this->m_viewe[n].aIndex = Vp.aIndex;
		this->m_viewe[n].GuildNumber = Vp.GuildNumber;

		datasize += sizeof(Vp);
	}
}

void CDungeonSiege::SetPKLevelTarget()
{
	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		return;
	}

	if(gObjUser.m_MapNumber != MAP_INDEX_DUNGEON)
	{
		return;
	}

	if(this->PlayerGuildNumber < 1)
	{
		return;
	}

	for(int i = 0; i < 400; i++)
	{
		lpViewObj lpObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		if( !lpObj || !lpObj->m_Model.Unknown4 )
		{
			continue;
		}

		if(lpObj->m_Model.ObjectType != emPlayer)
		{
			continue;
		}

		if(lpObj->aIndex == pGameIndex)
		{
			lpObj->PKLevel = 1;
			continue;
		}

		for(int n = 0; n < 75; n++)
		{
			DUNGEON_VIEWE* lpViewe = &this->m_viewe[n];

			if(lpViewe->aIndex == lpObj->aIndex)
			{
				if(this->PlayerGuildNumber == lpViewe->GuildNumber)
				{
					lpObj->PKLevel = 1;
				}
				else
				{
					lpObj->PKLevel = 7;
				}
				break;
			}
		}
	}
}

void CDungeonSiege::GCGuildNumber(PMSG_GC_GUILD_INDEX* lpMsg)
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	this->PlayerGuildNumber = lpMsg->GuildNumber;
}

void CDungeonSiege::DrawRanking()
{
	if(this->CheckStatus(eEVENTDUNGEON_CLOSE))
	{
		return;
	}

	bool DrawTable = true;

	if(    gInterface.CheckWindow(Party)
		|| gInterface.CheckWindow(Guild)
		|| gInterface.CheckWindow(Trade)
		|| gInterface.CheckWindow(Warehouse)
		|| gInterface.CheckWindow(ChaosBox)
		|| gInterface.CheckWindow(CommandWindow)
		|| gInterface.CheckWindow(PetInfo)
		|| gInterface.CheckWindow(Shop)
		|| gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(Store)
		|| gInterface.CheckWindow(OtherStore)
		|| gInterface.CheckWindow(Character)
		|| gInterface.CheckWindow(FastMenu)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(NPC_Titus)
		|| gInterface.CheckWindow(CashShop)
		|| gInterface.CheckWindow(FullMap)
		|| gInterface.CheckWindow(NPC_Dialog)
		|| gInterface.CheckWindow(GensInfo)
		|| gInterface.CheckWindow(NPC_Julia)
		|| gInterface.CheckWindow(ExpandInventory)
		|| gInterface.CheckWindow(ExpandWarehouse) 
		|| gInterface.CheckWindow(Helper) 
		|| gInterface.CheckWindow(Quest) 
		|| gInterface.CheckWindow(QuestDevin) 
		|| gInterface.CheckWindow(DevilSquery) 
		|| gInterface.CheckWindow(GuardNPC) 
		|| gInterface.CheckWindow(VorotaCS) 
		|| gInterface.CheckWindow(Rena) 
		|| gInterface.CheckWindow(LuckyCoins)
		|| gInterface.CheckWindow(Titus)
		|| gInterface.CheckWindow(BloodCastle) )
	{
		DrawTable = false;
	}

	if( gInterface.CheckWindowEx(exWinRanking)		  ||
		gInterface.CheckWindowEx(exWinPersonalPrice) )
	{
		DrawTable = false;
	}

	if(g_ExMenuV3.m_Enable && g_ExMenuV3.m_Version == EXMENU_NUMBER::eVERSION_ET)
	{
		if(gInterface.CheckWindowEx(exWinMenuV3))
		{
			DrawTable = false;
		}
	}

	if(!DrawTable)
	{
		return;
	}

	if(this->CheckStatus(eEVENTDUNGEON_WAIT) || this->CheckStatus(eEVENTDUNGEON_START_STAGE1))
	{
		//float RightMiniInfoY = 430;
		int mCount = 0;
		bool DrInfo = false;

		if(this->m_insiege)
		{
			mCount += 10;
		}

		for(int i = 0; i < this->ireg_list_count; i++)
		{
			mCount += 10;
			DrInfo = true;
		}

		if(!DrInfo)
		{
			return;
		}

		float Wind = 100;
		float Hig = 10 + mCount;
		//float StartiY = RightMiniInfoY - 10;
		float StartiY = gInterface.RightMiniInfoY - 10;
		
		float iX = 535;
		float iY = StartiY - Hig;	

		gInterface.RightMiniInfoY -= Hig;
		

		pDrawColorButton(0x7880, iX, iY, Wind, Hig, NULL, NULL, Color4f(0, 0, 0, 100));
		gInterface.DrawFormat(eOrange, iX, iY, 100, 3, "[%s]", this->m_EventName);
		
		if(this->m_insiege)
		{
			iY += 10;
			gInterface.DrawFormat(eYellow, iX+10, iY, 200, 1, "My Score: %d", this->m_mysocre);
		}

		for(int i = 0; i < this->ireg_list_count; i++)
		{
			iY+=10;
			gInterface.DrawFormat(eWhite, iX+10, iY, 200, 1, "%s: %d", this->reg_list[i].szGuildName, this->m_guildscore[i]);	
		}
	}
	else if(this->CheckStatus(eEVENTDUNGEON_WAIT_STAGE2) || this->CheckStatus(eEVENTDUNGEON_START_STAGE2))
	{
		//float RightMiniInfoY = 430;
		int mCount = 0;

		mCount += 10;
		mCount += 10;
		mCount += 10;
		mCount += 10;

		float Wind = 100;
		float Hig = 10 + mCount;
		//float StartiY = RightMiniInfoY - 10;
		float StartiY = gInterface.RightMiniInfoY - 15;
		gInterface.RightMiniInfoY -= Hig;

		float iX = 535;
		float iY = StartiY - Hig;	

		pDrawColorButton(0x7880, iX, iY, Wind, Hig, NULL, NULL, Color4f(0, 0, 0, 100));
		gInterface.DrawFormat(eOrange, iX, iY, 100, 3, "[%s]", this->m_EventName);
		
		iY += 10;
		gInterface.DrawFormat(eYellow, iX+10, iY, 200, 1, "- %s", this->reg_list[this->m_finalguild1].szGuildName);
		iY += 10;
		gInterface.DrawFormat(eWhite, iX+10, iY, 200, 1, "%s: %d", this->m_finalname1 , this->m_finalscore1);

		iY += 10;
		gInterface.DrawFormat(eYellow, iX+10, iY, 200, 1, "- %s", this->reg_list[this->m_finalguild2].szGuildName);
		iY += 10;
		gInterface.DrawFormat(eWhite, iX+10, iY, 200, 1, "%s: %d", this->m_finalname2 , this->m_finalscore2);
	}
}

void CDungeonSiege::GCSiegeScore(PMSG_DUNGEON_SIEGE_SCORE* lpMsg)
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	this->m_mysocre = lpMsg->MyScore;
	int iGuildCount = lpMsg->GuildCount;
	this->ireg_list_count = iGuildCount;
	for(int i = 0; i < iGuildCount; i++)
	{
		this->m_guildscore[i] = lpMsg->GuildScore[i];
	}
	this->m_finalguild1 = lpMsg->FinalGuildID1;
	this->m_finalguild2 = lpMsg->FinalGuildID2;
	this->m_finalscore1 = lpMsg->FinalScore1;
	this->m_finalscore2 = lpMsg->FinalScore2;

	this->m_finalname1[10] = 0;
	this->m_finalname2[10] = 0;
	memcpy(this->m_finalname1, lpMsg->Name1, 10);
	memcpy(this->m_finalname2, lpMsg->Name2, 10);

	this->m_insiege = lpMsg->InSiege;
}

void CDungeonSiege::GCPlayerConnect(PMSG_DUNGEON_SIEGE_PLAYER_CONNECT* lpMsg)
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	char szOwName[9];
	memset(this->reg_list, 0, sizeof(this->reg_list));

	szOwName[8] = 0;
	this->bCaptured = lpMsg->Captured;
	memcpy(szOwName, lpMsg->szGuildOwner, 8);
	memcpy(this->szLordGuild, szOwName, 8);

	this->ireg_list_count = lpMsg->iCountGuild;

	for(int i = 0; i < this->ireg_list_count; i++)
	{
		char szGName[9];
		szGName[8] = 0;
		memcpy(szGName, lpMsg->szGuildName[i], 8);
		memcpy(this->reg_list[i].szGuildName, szGName, 8);	
	}
	memset(this->m_EventName, 0, sizeof(this->m_EventName));
	memcpy(this->m_EventName, lpMsg->EventName, sizeof(this->m_EventName));
}

void CDungeonSiege::GCEventState(PMSG_DUNGEON_SIEGE_STATE* lpMsg)
{
	if (g_ExLicense.user.DungeonSiege == false) return;

	this->iEventStatus = lpMsg->EventState;
}

bool CDungeonSiege::CheckStatus(int Status)
{
	if (g_ExLicense.user.DungeonSiege == false) return false;

	if(this->iEventStatus == Status)
	{
		return true;
	}

	return false;
}

#endif