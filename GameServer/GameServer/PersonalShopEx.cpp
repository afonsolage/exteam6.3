#include "StdAfx.h"
#include "PersonalShopEx.h"
#include "user.h"
#include "GameMain.h"
#include "ExLicense.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PERSONAL_SHOP==TRUE)

PersonalShopEx g_PersonalShopEx;
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Init()
{
	this->Enable = FALSE;
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Load()
{
	this->Init();

	if(!g_ExLicense.user.PerosnalStoreEx)
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ExData\\PersonalShopEx.ini"));
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Read(char* File)
{
	this->Enable = GetPrivateProfileInt("Common", "Enable", 0, File);

	this->NPC_CLASS = GetPrivateProfileInt("Common", "NPC_CLASS", 0, File);
	this->NPC_MAP = GetPrivateProfileInt("Common", "NPC_MAP", 0, File);
	this->NPC_X = GetPrivateProfileInt("Common", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("Common", "NPC_Y", 0, File);

	this->BonusPrice = GetPrivateProfileInt("Common", "BonusPrice", 0, File);

	this->CreditPrice = 0;

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal) || 
	   g_ExLicense.CheckUser(eExUB::ProtectDebug) || g_ExLicense.CheckUser(eExUB::mu4you) || g_ExLicense.CheckUser(eExUB::NSGames))
	{
		this->CreditPrice = GetPrivateProfileInt("Common", "CreditPrice", 1, File);
	}
	
}
// ----------------------------------------------------------------------------------------------

bool PersonalShopEx::NPC_Dialog(int aIndex, int aIndexNPC)
{
	if(!this->Enable)
	{
 		return false;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aIndexNPC];

	if(		lpNpc->Class		== this->NPC_CLASS 
		&&	lpNpc->MapNumber	== this->NPC_MAP
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{
		CG_PersonalPage aCG;
		aCG.Page = 0;
		this->Search(aIndex,&aCG);
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Search(int aIndex, CG_PersonalPage* aRecv)
{
	if(!this->Enable)
	{
		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int Page = aRecv->Page;

	if(Page < 0 )
	{
		Page = 0;
	}

	if(lpUser->OffExp != 0 || lpUser->OffTrade !=0)
	{
		return;
	}

	BYTE SendBuff[5000];
	int datasize = 8;
	short icount = 0;
	BYTE SendCount = 0;

	int StartCount = Page * 10;
	int EndCount =  StartCount + 10;

	for(int n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
	{
		LPOBJ lpSearch = &gObj[n];
		if(lpSearch->Connected < PLAYER_PLAYING || !lpSearch->m_bPShopOpen || n == aIndex) 
		{
			continue;
		}

		if( StartCount <= icount && EndCount > icount)
		{
			if(SendCount < 10)
			{
				GC_PersonalShopInfo psi;
				psi.aIndex = n;
				strncpy(psi.Name, lpSearch->Name, 10);
				strncpy(psi.PersonalText, lpSearch->m_szPShopText, 36);
				psi.Value = 0;

				memcpy(&SendBuff[datasize],&psi,sizeof(psi));
				datasize += sizeof(psi);

				SendCount++;
			}
		}

		icount++;
	}

	SendBuff[0]=0xC2;	// packet header
	SendBuff[1]=SET_NUMBERH(datasize);
	SendBuff[2]=SET_NUMBERL(datasize);
	SendBuff[3]=0xFA;
	SendBuff[4]=0x09;
	SendBuff[5]=SET_NUMBERH(icount);
	SendBuff[6]=SET_NUMBERL(icount);
	SendBuff[7]=SendCount;
	DataSend(aIndex,SendBuff,datasize);
}

void PersonalShopEx::UpdatePSInventoryUser(int aIndex)
{
	//if(!this->Enable)
	//{
	//	return;
	//}

	if(!this->Enable)
	{
 		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int datasize = 6;
	BYTE icount = 0;
	BYTE SendBuff[5000];

	for ( int n=MAIN_INVENTORY_SIZE;n<INVENTORY_SIZE;n++)
	{
		if ( lpUser->Inventory1[n].IsItem() == TRUE )
		{
			GC_PSInventoryValue pMsg;

			pMsg.ItemPos = n;
			//ItemByteConvert(pMsgIL.ItemInfo, lpObjTarget->Inventory1[n]);
			//pMsgIL.PShopItemValue = lpObjTarget->Inventory1[n].m_iPShopValue;
			pMsg.Zen = lpUser->Inventory1[n].m_iPShopValue;
			pMsg.Bonus = lpUser->Inventory1[n].m_iPShopBonus;
			pMsg.Bless = lpUser->Inventory1[n].m_PShopBlessValue;
			pMsg.Soul = lpUser->Inventory1[n].m_PShopSoulValue;
			pMsg.Chaos = lpUser->Inventory1[n].m_PShopChaosValue;
			pMsg.Life = lpUser->Inventory1[n].m_PShopLifeValue;
			#if(DEV_PERSONAL_CREDIT)
			pMsg.Credit = lpUser->Inventory1[n].m_iPShopCredit;
			#endif
			memcpy(&SendBuff[datasize], &pMsg, sizeof(pMsg));
			
			datasize += sizeof(pMsg);

			icount++;
		}
	}

	SendBuff[0]=0xC2;	// packet header
	SendBuff[1]=SET_NUMBERH(datasize);
	SendBuff[2]=SET_NUMBERL(datasize);
	SendBuff[3]=0xFA;
	SendBuff[4]=0x0A;
	SendBuff[5]=icount;
	DataSend(aIndex,SendBuff,datasize);
}

void PersonalShopEx::UpdatePSInventoryTarget(int aIndex, int aTargetIndex)
{
	if(!this->Enable)
	{
 		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[aTargetIndex];

	int datasize = 8;
	BYTE icount = 0;
	BYTE SendBuff[5000];

	for ( int n=MAIN_INVENTORY_SIZE;n<INVENTORY_SIZE;n++)
	{
		if ( lpTarget->Inventory1[n].IsItem() == TRUE )
		{
			GC_PSInventoryValue pMsg;

			pMsg.ItemPos = n;
			//ItemByteConvert(pMsgIL.ItemInfo, lpObjTarget->Inventory1[n]);
			//pMsgIL.PShopItemValue = lpObjTarget->Inventory1[n].m_iPShopValue;
			pMsg.Zen = lpTarget->Inventory1[n].m_iPShopValue;
			pMsg.Bonus = lpTarget->Inventory1[n].m_iPShopBonus;
			pMsg.Bless = lpTarget->Inventory1[n].m_PShopBlessValue;
			pMsg.Soul = lpTarget->Inventory1[n].m_PShopSoulValue;
			pMsg.Chaos = lpTarget->Inventory1[n].m_PShopChaosValue;
			pMsg.Life = lpTarget->Inventory1[n].m_PShopLifeValue;
			#if(DEV_PERSONAL_CREDIT)
			pMsg.Credit = lpTarget->Inventory1[n].m_iPShopCredit;
			#endif

			memcpy(&SendBuff[datasize], &pMsg, sizeof(pMsg));
			
			datasize += sizeof(pMsg);

			icount++;
		}
	}

	SendBuff[0]=0xC2;	// packet header
	SendBuff[1]=SET_NUMBERH(datasize);
	SendBuff[2]=SET_NUMBERL(datasize);
	SendBuff[3]=0xFA;
	SendBuff[4]=0x0B;
	SendBuff[5]=SET_NUMBERH(aTargetIndex);
	SendBuff[6]=SET_NUMBERL(aTargetIndex);
	SendBuff[7]=icount;
	DataSend(aIndex,SendBuff,datasize);
}

int PersonalShopEx::GetMoney(int aIndex, int Pos)
{

	if(!gObjIsConnectedEx(aIndex))
	{
		return 0;
	}

	LPOBJ lpUser = &gObj[aIndex];

	int Zen = lpUser->Inventory1[Pos].m_iPShopValue;
	int Bonus = lpUser->Inventory1[Pos].m_iPShopBonus;
	int Bless = lpUser->Inventory1[Pos].m_PShopBlessValue;
	int Soul = lpUser->Inventory1[Pos].m_PShopSoulValue;
	int Chaos = lpUser->Inventory1[Pos].m_PShopChaosValue;
	int Life = lpUser->Inventory1[Pos].m_PShopLifeValue;
	#if(DEV_PERSONAL_CREDIT)
	int Credit = lpUser->Inventory1[Pos].m_iPShopCredit;
	#endif

	bool Result = 0;

	if( Zen > 0 )
	{
		Result = 1;
	}
	if( Bless > 0)
	{
		Result = 1;
	}
	if( Soul > 0)
	{
		Result = 1;
	}
	if( Chaos > 0)
	{
		Result = 1;
	}
	if( Life > 0)
	{
		Result = 1;
	}
	#if(DEV_PERSONAL_CREDIT)
	if(this->CreditPrice)
	{
		if( Credit > 0)
		{
			Result = 1;
		}
	}
	else
	{
		if( Credit > 0)
		{
			Result = 0;
		}
	}
	#endif

	if(!this->BonusPrice)
	{
		if(Bonus > 0)
		{
			Result = 0;
		}
	}
	else
	{
		if(Bonus > 0)
		{
			Result = 1;
		}
	}

	return Result;
}

bool PersonalShopEx::CheckPrice(int Zen, int Bonus, int Bless, int Soul, int Chaos, int Life, int Credit)
{
	bool Result = 0;

	if( Zen > 0 )
	{
		Result = 1;
	}
	if( Bless > 0)
	{
		Result = 1;
	}
	if( Soul > 0)
	{
		Result = 1;
	}
	if( Chaos > 0)
	{
		Result = 1;
	}
	if( Life > 0)
	{
		Result = 1;
	}
	#if(DEV_PERSONAL_CREDIT)
	if(this->CreditPrice)
	{
		if( Credit > 0)
		{
			Result = 1;
		}
	}
	else
	{
		if( Credit > 0)
		{
			Result = 0;
		}
	}
	#endif

	if(!this->BonusPrice)
	{
		if(Bonus > 0)
		{
			Result = 0;
		}
	}
	else
	{
		if(Bonus > 0)
		{
			Result = 1;
		}
	}

	return Result;
}

bool PersonalShopEx::PShop_CheckInventoryPrice(short aIndex)
{
	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	bool Result = false;

	for(int i = MAIN_INVENTORY_SIZE; i < INVENTORY_SIZE; i++)
	{
		if(lpObj->Inventory1[i].IsItem() == 1)
		{
			Result = false;

			if(lpObj->Inventory1[i].m_iPShopValue > 0 )
			{
				Result = true;
			}
			if(lpObj->Inventory1[i].m_PShopBlessValue > 0)
			{
				Result = true;
			}
			if(lpObj->Inventory1[i].m_PShopSoulValue > 0)
			{
				Result = true;
			}
			if(lpObj->Inventory1[i].m_PShopChaosValue > 0)
			{
				Result = true;
			}
			if(lpObj->Inventory1[i].m_PShopLifeValue > 0)
			{
				Result = true;
			}
			#if(DEV_PERSONAL_CREDIT)
			if(g_PersonalShopEx.CreditPrice)
			{
				if(lpObj->Inventory1[i].m_iPShopCredit > 0)
				{
					Result = true;
				}
			}
			else
			{
				if(lpObj->Inventory1[i].m_iPShopCredit > 0)
				{
					Result = false;
				}
			}
			#endif

			if(!this->BonusPrice)
			{
				if(lpObj->Inventory1[i].m_iPShopBonus > 0)
				{
					Result = false;
				}
			}
			else
			{
				if(lpObj->Inventory1[i].m_iPShopBonus > 0)
				{
					Result = true;
				}
			}

			if(Result == false)
			{
				break;
			}
		}
	}
	return Result;
}

#endif