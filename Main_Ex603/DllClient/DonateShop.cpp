#include "stdafx.h"
#include "DonateShop.h"
#include "Console.h"
#include "TMemory.h"
#include "Object.h"
#include "Protocol.h"
#include "Interface.h"
#include "User.h"
#include "Item.h"
#include "ItemPrice.h"
#include "ExLicense.h"
// -------------------------------------------------------------------------------
#if(DONATE_SHOP==TRUE)

DonateShop g_DonateShop;
// -------------------------------------------------------------------------------

static DWORD DonateShopBuffer;

Naked(PriceGetItemLevel2)
{
	_asm
	{
		MOV EAX,DWORD PTR DS:[EDX+2]
		SAR EAX,3
		AND EAX,0x0000000F
		MOV g_DonateShop.ShowItemLevel, EAX
		/*
		Mov EDI, 0x007E3D6D
		JMP EDI		
		*/
		Mov DonateShopBuffer, 0x007E3D6D
		JMP DonateShopBuffer		
	}
}
// ----------------------------------------------------------------------------------------------

static DWORD _004EC436 = 0x004EC436;
static DWORD bt;

Naked(PriceGetItemAncent)
{
	__asm
	{
		//MOV g_DonateShop.ShowitemAnc, BYTE PTR DS:[ECX+0x18]
		//MOV EDX, DWORD PTR DS:[ECX+0x18]
		MOV g_DonateShop.ShowitemAnc, EDX
		AND EDX,0x80000003
		JMP _004EC436
	}
}

void DonateShop::Load()
{
	this->ShowItem = false;
	this->ShowType = -1;
	this->ShowPrice = 0;
	// ----
	this->m_LoadedBuyCount = 0;
	this->OpenShop = -1;
	this->ShopNumber = DONAT_SHOP_START;
	// ----
	SetOp((LPVOID)0x5087E6, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x58B78F, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x58B7A6, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x58B7FC, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x5C1A7F, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x5C2117, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x5C4268, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x7AF806, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x7E42F9, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x7E4347, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x7E439C, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x846B99, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x846C13, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x8475C3, this->GetPrice, ASM::CALL);
	SetOp((LPVOID)0x9683D0, this->GetPrice, ASM::CALL);
	// ----
	SetRange((LPVOID)0x007E3D64, 9, ASM::NOP);	
	SetOp((LPVOID)0x007E3D64, PriceGetItemLevel2, ASM::JMP);
	// ----
	SetRange((LPVOID)0x007E4383, 5, ASM::NOP);	
	SetOp((LPVOID)0x007E4383, this->ShowBuyPrice, ASM::CALL);

	SetRange((LPVOID)0x007E43DF, 5, ASM::NOP);	
	SetOp((LPVOID)0x007E43DF, this->ShowSellPrice, ASM::CALL);
	// ----
	SetRange((LPVOID)0x007E429B, 6, ASM::NOP);	//Fix All Item Price
	SetRange((LPVOID)0x007E42BD, 2, ASM::NOP);	//Fix All Item Price2
	SetRange((LPVOID)0x007E42D4, 6, ASM::NOP);	//Fix All Item Price3	
	SetRange((LPVOID)0x007E42E3, 6, ASM::NOP);	//Fix All Item Price4
	// ----

	// need bind images function
	gInterface.BindObject(eDONATE_LEFT, 0x7BAA, 17, 17, -1, -1);
	gInterface.BindObject(eDONATE_RIGHT, 0x7BAB, 17, 17, -1, -1);

	gInterface.BindObject(eDONATE_INFOBG1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eDONATE_INFOBG2, 0x7AA3, 170, 21, -1, -1);

	gInterface.BindObject(eDONATE_CHECKWIN_MAIN, 0x7A5A, 222, 110, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_CLOSE, 0x7A5F, 62, 27, -1, -1);
}
// -------------------------------------------------------------------------------

void DonateShop::LoadItemPrice()
{
	this->ShowItem = false;
	this->ShowType = -1;
	this->ShowPrice = 0;
	// ----
	this->m_LoadedBuyCount = 0;
	this->OpenShop = -1;
	this->ShopNumber = DONAT_SHOP_START;
	// ----
	// need bind images function
	gInterface.BindObject(eDONATE_LEFT, 0x7BAA, 17, 17, -1, -1);
	gInterface.BindObject(eDONATE_RIGHT, 0x7BAB, 17, 17, -1, -1);

	gInterface.BindObject(eDONATE_INFOBG1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eDONATE_INFOBG2, 0x7AA3, 170, 21, -1, -1);

	//-> Item Opt Text Fix
	//SetRange((LPVOID)0x004EC911, 35, ASM::NOP);
	//SetRange((LPVOID)0x004EC622, 35, ASM::NOP);
	//SetRange((LPVOID)0x007E5886, 44, ASM::NOP);

	//ancent true
	//004EC461 ancent check
	//004EC45C <--
	SetRange((LPVOID)0x004EC430, 6, ASM::NOP);	
	SetOp((LPVOID)0x004EC430, PriceGetItemAncent, ASM::JMP);

	gInterface.BindObject(eDONATE_CHECKWIN_MAIN, 0x7A5A, 222, 110, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eDONATE_CHECKWIN_CLOSE, 0x7A5F, 62, 27, -1, -1);
}
// -------------------------------------------------------------------------------

void DonateShop::GC_Recv_shop(LPBYTE aRecv)
{
	ZeroMemory(&ShopEx,sizeof(ShopEx));
	int datasize = 6;
	int excount = aRecv[datasize-1];

	this->m_LoadedBuyCount = excount;

	for (int n = 0; n < excount; n++)
	{
		GC_ShopPay Vp;
		memcpy(&Vp,&aRecv[datasize],sizeof(Vp));

		ShopEx[n].ItemType = Vp.ItemType;
		ShopEx[n].ItemIndex = Vp.ItemIndex;
		ShopEx[n].ItemLevel = Vp.ItemLevel;
		ShopEx[n].ItemExl = Vp.ItemExl;
		ShopEx[n].ItemAnc = Vp.ItemAnc;
		ShopEx[n].PayType = Vp.PayType;
		ShopEx[n].PayPrice = Vp.PayPrice;

		datasize += sizeof(Vp);
	}

	gConsole.Output(cGREEN, "GC_Recv_shop");
}
// -------------------------------------------------------------------------------

void DonateShop::GC_RecvShopNum(GC_SHOP_CLICK* aRecv)
{
	this->OpenShop = aRecv->Shop_Num;

	//if(this->OpenShop)

	/*if(this->OpenShop >= DONAT_SHOP_START && this->OpenShop < DONAT_SHOP_END)
	{
		this->Load();
	}
	else
	{
		gItemPrice.Load();
	}*/

	gConsole.Output(cGREEN, "GC_RecvShopNum");
}
// -------------------------------------------------------------------------------

void DonateShop::ShowBuyPrice(DWORD a1, const char *a2, char *Price)
{
	if (!g_DonateShop.ShowItem)
	{
		pShowPrice(a1, "Buy Price: %s Zen", Price);
		gConsole.Output(cGREEN, "Buy Price: %s Zen", Price);
		return;
	}
	// ----
	int v14 = g_DonateShop.ShowPrice;
	int v12 = v14 % 1000;
	int v13 = v14 % 1000000 / 1000;
	int v11 = v14 % 1000000000 / 1000000;
	// ----
	switch (g_DonateShop.ShowType)
	{
	case ePriceEx::ePriceZen:
	{
		if (v14 < 1000000000)
		{
			if (v14 < 1000000)
			{
				if (v14 < 1000)
					pShowPrice(a1, "Buy Price: %d Zen", v12);
				else
					pShowPrice(a1, "Buy Price: %d,%03d Zen", v13, v12);
			}
			else
			{
				pShowPrice(a1, "Buy Price: %d,%03d,%03d Zen", v11, v13, v12);
			}
		}
		else
		{
			pShowPrice(a1, "Buy Price: %d,%03d,%03d,%03d Zen",1, v11, v13, v12);
		}
	}
	break;
	// --
	case ePriceEx::ePriceBonus:
	{
		if (v14 < 1000000000)
		{
			if (v14 < 1000000)
			{
				if (v14 < 1000)
					pShowPrice(a1, "Buy Price: %d WCoin", v12);
				else
					pShowPrice(a1, "Buy Price: %d,%03d WCoin", v13, v12);
			}
			else
			{
				pShowPrice(a1, "Buy Price: %d,%03d,%03d WCoin", v11, v13, v12);
			}
		}
		else
		{
			pShowPrice(a1, "Buy Price: %d,%03d,%03d,%03d WCoin", v11, v13, v12);
		}
	}
	break;
	// --
	case ePriceEx::ePriceCredit:
	{
		if(g_ExLicense.CheckUser(eExUB::NSGames))
		{
			if (v14 < 1000000000)
			{
				if (v14 < 1000000)
				{
					if (v14 < 1000)
						pShowPrice(a1, "Buy Price: %d NSPoint", v12);
					else
						pShowPrice(a1, "Buy Price: %d,%03d NSPoint", v13, v12);
				}
				else
				{
					pShowPrice(a1, "Buy Price: %d,%03d,%03d NSPoint", v11, v13, v12);
				}
			}
			else
			{
				pShowPrice(a1, "Buy Price: %d,%03d,%03d,%03d NSPoint", v11, v13, v12);
			}
		}
		else
		{
			if (v14 < 1000000000)
			{
				if (v14 < 1000000)
				{
					if (v14 < 1000)
						pShowPrice(a1, "Buy Price: %d Credits", v12);
					else
						pShowPrice(a1, "Buy Price: %d,%03d Credits", v13, v12);
				}
				else
				{
					pShowPrice(a1, "Buy Price: %d,%03d,%03d Credits", v11, v13, v12);
				}
			}
			else
			{
				pShowPrice(a1, "Buy Price: %d,%03d,%03d,%03d Credits", v11, v13, v12);
			}
		}
	}
	break;
	// --
	default:
	{
		pShowPrice(a1, "Buy Price: %s Zen", Price);
	}
		break;
	}
}
// ----------------------------------------------------------------------------------------------

void DonateShop::ShowSellPrice(DWORD a1, const char *a2, char *Price)
{
	if (!g_DonateShop.ShowItem)
	{
		pShowPrice(a1, "Sell Price: %s Zen", Price);
		return;
	}
	// ----
	pShowPrice(a1, "Sell Price: %s Zen", Price);
	gConsole.Output(cGREEN, "ShowSellPrice: %d", Price);

}
// ----------------------------------------------------------------------------------------------

__int64 DonateShop::GetPrice(ObjectItem * lpItem, int Mode)
{
	__int64 Money = -1;
	__int64 StartMoney = pSetItemPrice(lpItem, Mode);
	__int64 NewOptionAddMoney = 0;
	int Divisor = 3;
	// ----
	if (Mode)	//-> Sell
	{
		if (g_DonateShop.CheckItemSell(lpItem->ItemID, g_DonateShop.ShowItemLevel, &Money))
		{
			return Money;
		}
	}
	else	//-> Buy
	{
		//gConsole.Output(cGREEN, "ANC: %d", (int)lpItem->AncientOption /*g_DonateShop.ShowitemAnc*/);
		if (g_DonateShop.CheckItemBuy(lpItem->ItemID, gItemPrice.ShowItemLevel, lpItem->Unknown19, g_DonateShop.ShowitemAnc, &Money))
		{
			return Money;
		}
	}
	// ----
	/*
	if (lpItem->ItemID >= ITEM(0, 0) && lpItem->ItemID <= ITEM(12, 6)
		|| lpItem->ItemID >= ITEM(12, 36) && lpItem->ItemID <= ITEM(12, 43)
		|| lpItem->ItemID >= ITEM(12, 49) && lpItem->ItemID <= ITEM(12, 50)
		|| lpItem->ItemID == ITEM(13, 30))
	{
		for (int i = 0; i < lpItem->SpecialCount; i++)
		{
			switch (lpItem->SpecialType[i])
			{
			case eItemOption::Damage:
			case eItemOption::WizardryDamage:
			case eItemOption::CurseSpell:
			case eItemOption::Defense:
			case eItemOption::HPRecovery:
			{
				switch (lpItem->SpecialValue[i])
				{
				case 20:
					NewOptionAddMoney += (StartMoney * 84.0 / 10.0);
					break;
				case 24:
					NewOptionAddMoney += (StartMoney * 112.0 / 10.0);
					break;
				case 28:
					NewOptionAddMoney += (StartMoney * 140.0 / 10.0);
					break;
				}
			}
				break;
			}
		}
	}
	// ----
	if (NewOptionAddMoney > 0)
	{
		if (StartMoney + NewOptionAddMoney > 2000000000)
		{
			Money = 2000000000;
		}
		else
		{
			Money = StartMoney + NewOptionAddMoney;
		}
	}
	// ----
	if (Money != -1)
	{
		if (Mode == 1)
		{
			Money /= 3;
		}
		// ----
		return Money;
	}
	// ----
	*/
	return pSetItemPrice(lpItem, Mode);
}
// ----------------------------------------------------------------------------------------------

bool DonateShop::CheckItemBuy(short ItemCode, int ItemLevel, int Exl, int Anc, __int64 * Price)
{
	this->ShowItem = false;
	this->ShowType = -1;
	this->ShowPrice = 0;

	if(g_DonateShop.OpenShop >= 0 && g_DonateShop.OpenShop < DONAT_SHOP_START)
	{
		for (int i = 0; i < this->buyCount; i++)
		{
			if (ItemCode != ITEM(this->databuy[i].iType, this->databuy[i].iIndex))
			{
				continue;
			}
			// ----
			if (ItemLevel != this->databuy[i].iLevel)
			{
				continue;
			}
			// ----
			if (this->databuy[i].iPrice < 0)
			{
				continue;
			}
			// ----
			this->ShowItem = true;
			this->ShowType = 1;
			this->ShowPrice = this->databuy[i].iPrice;
			*Price = this->databuy[i].iPrice;
			// ----
			return true;
		}
		// ----
		return false;
	}
	// ----
	for (int i = 0; i < this->m_LoadedBuyCount; i++)
	{
		if (ItemCode != ITEM(this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex))
		{
			continue;
		}
		// ----
		if (ItemLevel != this->ShopEx[i].ItemLevel)
		{
			continue;
		}
		// ----
		if(!this->CheckExellent(Exl, this->ShopEx[i].ItemExl))
		{
			continue;
		}
		// ----
		if (this->ShopEx[i].ItemAnc != Anc)
		{
			continue;
		}
		// ----
		if (this->ShopEx[i].PayType < 0 || this->ShopEx[i].PayType > 3)
		{
			continue;
		}
		// ----
		this->ShowItem = true;
		this->ShowType = this->ShopEx[i].PayType;
		this->ShowPrice = this->ShopEx[i].PayPrice;
		*Price = this->ShopEx[i].PayPrice;
		// ----
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool DonateShop::CheckItemSell(short ItemCode, int ItemLevel, __int64 * Price)
{
	// ----
	this->ShowItem = false;
	this->ShowType = -1;
	this->ShowPrice = 0;
	// ----
	if(g_DonateShop.OpenShop >= 0 && g_DonateShop.OpenShop < DONAT_SHOP_START)
	{
		for (int i = 0; i < this->sellCount; i++)
		{
			if (ItemCode != ITEM(this->datasell[i].iType, this->datasell[i].iIndex))
			{
				continue;
			}
			// ----
			if (ItemLevel != this->datasell[i].iLevel)
			{
				continue;
			}
			// ----
			if (this->datasell[i].iPrice < 0)
			{
				continue;
			}
			// ----
			this->ShowItem = true;
			this->ShowType = 1;
			this->ShowPrice = this->datasell[i].iPrice;
			*Price = this->datasell[i].iPrice;
			// ----
			return true;
		}
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool DonateShop::CheckExellent(int Exl1, int Exl2)
{
	if(!Exl1 && !Exl2)
	{
		return true;
	}
	else if(Exl1 && Exl2)
	{
		return true;
	}

	return false;

}
// ----------------------------------------------------------------------------------------------

void DonateShop::CG_CashSend()
{
	CG_NEW_CASH_SHOP pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x08, sizeof(pRequest));
	pRequest.Number = this->ShopNumber;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

void DonateShop::ShopButtonDraw()
{
	this->DrawDonateCheckBuy();

	return;

	if(!gInterface.CheckWindow(Shop))
	{
		this->ShopNumber = DONAT_SHOP_START;
		return;
	}

	if( this->OpenShop < DONAT_SHOP_START && DONAT_SHOP_END > this->OpenShop/* && this->OpenShop != BONUS_SHOP && this->OpenShop != SANTA_SHOP*/)
	{
		return;
	}

	//float StartX = 271;
	//float StartY = 355;

	float StartX = 0;
	float StartY = 390;

	if(!gInterface.CheckWindow(ExpandInventory) && !gInterface.CheckWindow(ChatWindow))
	{
		gInterface.DrawGUI(eDONATE_INFOBG1, StartX , StartY);
		gInterface.DrawFormat(eGold, StartX + 35, StartY + 5, 70, 1, "WCoin:");
		gInterface.DrawFormat(eWhite, StartX + 115, StartY + 5, 70, 1, "%d", gObjUser.WCoinC); // if full reset

		StartY += 20;

		if(g_ExLicense.CheckUser(eExUB::NSGames))
		{
			gInterface.DrawGUI(eDONATE_INFOBG2, StartX , StartY);
			gInterface.DrawFormat(eGold, StartX + 35, StartY + 5, 70, 1, "NSPoint:");
			gInterface.DrawFormat(eWhite, StartX + 115, StartY + 5, 70, 1, "%d",(int)gObjUser.m_PCPoint); // if full reset
		}
		else
		{
			gInterface.DrawGUI(eDONATE_INFOBG2, StartX , StartY);
			gInterface.DrawFormat(eGold, StartX + 35, StartY + 5, 70, 1, "Credits:");
			gInterface.DrawFormat(eWhite, StartX + 115, StartY + 5, 70, 1, "%d",(int)gObjUser.ExCred); // if full reset
		}
	}

	//if(this->OpenShop == BONUS_SHOP || this->OpenShop == SANTA_SHOP)
	//{
	//	return;
	//}

	//StartX += 50;
	//StartY += 25;

	StartX = 270 + 43;
	StartY = 355 + 50;

	if(gInterface.CheckWindow(ExpandInventory))
	{
		StartX -= 190;
	}

	gInterface.DrawFormat(eGold, StartX-10, StartY+5, 100, 3, "Page: %d / %d", ((this->ShopNumber+1)-DONAT_SHOP_START), (DONAT_SHOP_END+1)-DONAT_SHOP_START);

	gInterface.DrawGUI(eDONATE_LEFT, StartX, StartY);

	int plusWinX = 50;

	if(pGameResolutionMode < 5)
	{
		plusWinX = 60;
	}

	gInterface.DrawGUI(eDONATE_RIGHT, StartX + plusWinX, StartY);

	if(gInterface.IsWorkZone(eDONATE_LEFT))
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eDONATE_LEFT].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eDONATE_LEFT, StartX, StartY, Color);
	}
	else if(gInterface.IsWorkZone(eDONATE_RIGHT))
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eDONATE_RIGHT].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eDONATE_RIGHT, StartX + plusWinX, StartY, Color);
	}
}
// ----------------------------------------------------------------------------------------------

void DonateShop::ButtonClick(DWORD Event)
{
	if(gInterface.CheckWindowEx(exWinDonateCheck))
	{
		if(gInterface.ButtonEx(Event, eDONATE_CHECKWIN_OK, false))
		{
			PMSG_DONATE_ITEMBUY pMsg;
			pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x96, sizeof(pMsg));	
			pMsg.Result = 1;
			gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);

			gInterface.CloseWindowEx(exWinDonateCheck);
		}
		if(gInterface.ButtonEx(Event, eDONATE_CHECKWIN_CLOSE, false))
		{		
			PMSG_DONATE_ITEMBUY pMsg;
			pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x96, sizeof(pMsg));	
			pMsg.Result = 0;
			gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
			gInterface.CloseWindowEx(exWinDonateCheck);
		}
		return;
	}

	if(!gInterface.CheckWindow(Shop))
	{
		return;
	}

	if( this->OpenShop < DONAT_SHOP_START && DONAT_SHOP_END > this->OpenShop )
	{
		return;
	}

	if( gInterface.ButtonEx(Event, eDONATE_LEFT, false ) )
	{
		if(this->ShopNumber != DONAT_SHOP_START)
		{
			this->ShopNumber--;
			this->CG_CashSend();
		}
		return;
	}
	else if( gInterface.ButtonEx(Event, eDONATE_RIGHT, false ) )
	{
		if(this->ShopNumber != DONAT_SHOP_END)
		{
			this->ShopNumber++;
			this->CG_CashSend();
		}	
		return;
	}
}
// ----------------------------------------------------------------------------------------------

void DonateShop::GCStandartShopRecv(LPBYTE aRecv)
{
	ZeroMemory(&this->databuy,sizeof(this->databuy));
	ZeroMemory(&this->datasell,sizeof(this->datasell));

	int datasize = 7;
	this->buyCount = aRecv[datasize-2];
	this->sellCount = aRecv[datasize-1];

	for (int i = 0; i < this->buyCount; i++)
	{
		GCDataPrice pMsg;
		memcpy(&pMsg,&aRecv[datasize],sizeof(pMsg));
		this->databuy[i].iType = pMsg.iType;
		this->databuy[i].iIndex = pMsg.iIndex;
		this->databuy[i].iLevel = pMsg.iLevel;
		this->databuy[i].iPrice =pMsg.iPrice;
		datasize += sizeof(pMsg);
	}

	for (int i = 0; i < this->sellCount; i++)
	{
		GCDataPrice pMsg;
		memcpy(&pMsg,&aRecv[datasize],sizeof(pMsg));
		this->datasell[i].iType = pMsg.iType;
		this->datasell[i].iIndex = pMsg.iIndex;
		this->datasell[i].iLevel = pMsg.iLevel;
		this->datasell[i].iPrice =pMsg.iPrice;
		datasize += sizeof(pMsg);
	}

	gConsole.Output(cGREEN, "GC_Recv_shop: %d", sellCount);
}
// ----------------------------------------------------------------------------------------------

bool DonateShop::DrawDonateCheckBuy()
{
	if(!gInterface.CheckWindowEx(exWinDonateCheck))
	{
		return false;
	}

	pSetCursorFocus = true;

	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 130;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	gInterface.DrawGUI(eDONATE_CHECKWIN_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eDONATE_CHECKWIN_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eDONATE_CHECKWIN_FRAME, StartX, StartY + 67.0, 0);
	gInterface.DrawGUI(eDONATE_CHECKWIN_FOOTER, StartX, StartY);
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Check Buy");
	// ---- 
	gInterface.DrawFormat(eWhite, StartX + 10, 110 + 50 - 20, 210, 3, "Check Buy Item?");
	gInterface.DrawGUI(eDONATE_CHECKWIN_OK, StartX+30, StartY /*- 5*/);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5 + 5, 50, 3, "Yes");

	if( gInterface.IsWorkZone(eDONATE_CHECKWIN_OK) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eDONATE_CHECKWIN_OK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eDONATE_CHECKWIN_OK, gInterface.Data[eDONATE_CHECKWIN_OK].X, gInterface.Data[eDONATE_CHECKWIN_OK].Y, Color);
	}
	// ---- 
	gInterface.DrawGUI(eDONATE_CHECKWIN_CLOSE, StartX + 70 + 62, StartY /*- 5*/ );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5 + 5, 50, 3, "No");

	if( gInterface.IsWorkZone(eDONATE_CHECKWIN_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eDONATE_CHECKWIN_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eDONATE_CHECKWIN_CLOSE, gInterface.Data[eDONATE_CHECKWIN_CLOSE].X, gInterface.Data[eDONATE_CHECKWIN_CLOSE].Y, Color);
	}

	return true;
}

void DonateShop::GCCheckBuyDonateItem(PMSG_DONATE_CHECKBUY* lpMsg)
{
	gInterface.OpenWindowEx(exWinDonateCheck);
}

#endif