#include "stdafx.h"
#include "ItemPrice.h"
#include "ReadScript.h"
#include "Object.h"
#include "Defines.h"
#include "Import.h"
#include "Item.h"
#include "TMemory.h"
#include "Console.h"
#include "ExFunction.h"
#include "DonateShop.h"
#include "ExLicense.h"
#include "ExText.h"

#ifdef _ITEM_PRICE_MANAGER_

// ----------------------------------------------------------------------------------------------
ItemPrice	gItemPrice;

// ----------------------------------------------------------------------------------------------

Naked(PriceGetItemLevel)
{
	_asm
	{
		MOV EAX,DWORD PTR DS:[EDX+2]
		SAR EAX,3
		AND EAX,0x0000000F
		MOV gItemPrice.ShowItemLevel, EAX
		Mov EDI, 0x007E3D6D
		JMP EDI		
	}
}
// ----------------------------------------------------------------------------------------------

ItemPrice::ItemPrice()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

ItemPrice::~ItemPrice()
{
	// ----
}
// ----------------------------------------------------------------------------------------------

void ItemPrice::Init()
{
	this->ShowItem = false;
	this->ShowItemLevel = 0;
	this->ShowPrice = 0;
	this->ShowType = 0;
	this->m_LoadedBuyCount = 0;
	this->m_LoadedSellCount = 0;
	this->Enable = false;
	this->SellItemNullZen = 0;
	// ----
	for (int i = 0; i < MAX_ITEMPRICE_ITEM; i++)
	{
		this->m_BuyData[i].ItemType = -1;
		this->m_BuyData[i].ItemIndex = -1;
		this->m_BuyData[i].ItemLevel = -1;
		this->m_BuyData[i].PriceType = -1;
		this->m_BuyData[i].Price = -1;
	}
	// ----
	for (int i = 0; i < MAX_ITEMPRICE_ITEM; i++)
	{
		this->m_SellData[i].ItemType = -1;
		this->m_SellData[i].ItemIndex = -1;
		this->m_SellData[i].ItemLevel = -1;
		this->m_SellData[i].PriceType = -1;
		this->m_SellData[i].Price = -1;
	}
}
// ----------------------------------------------------------------------------------------------

void ItemPrice::Load()
{
	this->ReadList("Data\\Custom\\Configs\\PriceManager.ini");
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
	SetOp((LPVOID)0x007E4383, this->ShowBuyPrice, ASM::CALL);
	SetOp((LPVOID)0x007E43DF, this->ShowSellPrice, ASM::CALL);
	SetOp((LPVOID)0x007E4873, this->ShowItemLevelName, ASM::CALL);
	// ----
	SetRange((LPVOID)0x007E3D64, 9, ASM::NOP);	
	SetOp((LPVOID)0x007E3D64, PriceGetItemLevel, ASM::JMP);
	// ----
	SetRange((LPVOID)0x007E429B, 6, ASM::NOP);	//Fix All Item Price
	SetRange((LPVOID)0x007E42BD, 2, ASM::NOP);	//Fix All Item Price2
	SetRange((LPVOID)0x007E42D4, 6, ASM::NOP);	//Fix All Item Price3	
	SetRange((LPVOID)0x007E42E3, 6, ASM::NOP);	//Fix All Item Price4
	// ----
	//SetByte((LPVOID)(0x007E42ED), 0xE9);		//Fix all Item Price5
	//SetByte((LPVOID)(0x007E42ED+1), 0x9B);		//Fix all Item Price5
	//SetByte((LPVOID)(0x007E42ED+2), 0x00);		//Fix all Item Price5
	//SetByte((LPVOID)(0x007E42ED+3), 0x00);		//Fix all Item Price5
	//SetByte((LPVOID)(0x007E42ED+4), 0x00);		//Fix all Item Price5
	//SetByte((LPVOID)(0x007E42ED+5), 0x90);		//Fix all Item Price5
	// ---- 007E43E7
	//005C15CF
	//005C15E9
	//005C15F3
	/*
	005C1680
	=>007E4350

	*/

	g_DonateShop.LoadItemPrice();
}
// ----------------------------------------------------------------------------------------------

void ItemPrice::ReadList(char * File)
{
	this->Init();
	int Token;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if (!SMDFile)
	{
		MessageBoxError("%s - file nor found", File);
		ExitProcess(0);
		return;
	}
	// ----
	int Category = -1;
	// ----
	while (true)
	{
		Token = GetToken();
		// ----
		if (Token == END)
		{
			break;
		}
		// ----
		if (Token != NUMBER)
		{
			continue;
		}
		// ----
		Category = TokenNumber;
		// ----
		while (true)
		{
			if (Category == 0)
			{
				Token = GetToken();
				// ----
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}
				// ----
				this->Enable = TokenNumber;
				// ----
				Token = GetToken();
				this->SellItemNullZen = TokenNumber;
			}
			else if (Category == 1)	//-> Sell List	//-> Need Check Dev
			{
				Token = GetToken();
				// ----
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}
				// ----
				if (this->m_LoadedSellCount >= MAX_ITEMPRICE_ITEM)
				{
					break;
				}
				// ----
				this->m_SellData[this->m_LoadedSellCount].ItemType = TokenNumber;
				// ----
				Token = GetToken();
				this->m_SellData[this->m_LoadedSellCount].ItemIndex = TokenNumber;
				// ----
				Token = GetToken();
				this->m_SellData[this->m_LoadedSellCount].ItemLevel = TokenNumber;
				// ----
				Token = GetToken();
				this->m_SellData[this->m_LoadedSellCount].PriceType = TokenNumber;
				// ----
				Token = GetToken();
				this->m_SellData[this->m_LoadedSellCount].Price = TokenNumber;
				// ----
				this->m_LoadedSellCount++;
			}
			else if (Category == 2)	//-> Buy List	//-> Need Check	Dev
			{
				Token = GetToken();
				// ----
				if (strcmp("end", TokenString) == NULL)
				{
					break;
				}
				// ----
				if (this->m_LoadedBuyCount >= MAX_ITEMPRICE_ITEM)
				{
					break;
				}
				// ----
				this->m_BuyData[this->m_LoadedBuyCount].ItemType = TokenNumber;
				// ----
				Token = GetToken();
				this->m_BuyData[this->m_LoadedBuyCount].ItemIndex = TokenNumber;
				// ----
				Token = GetToken();
				this->m_BuyData[this->m_LoadedBuyCount].ItemLevel = TokenNumber;
				// ----
				Token = GetToken();
				this->m_BuyData[this->m_LoadedBuyCount].PriceType = TokenNumber;
				// ----
				Token = GetToken();
				this->m_BuyData[this->m_LoadedBuyCount].Price = dwTokenNumber;
				// ----
				this->m_LoadedBuyCount++;
			}
		}
	}
	// ----
	fclose(SMDFile);
}
// ----------------------------------------------------------------------------------------------

bool ItemPrice::CheckItemSell(short ItemCode, int ItemLevel, __int64 * Price)
{
	if (!this->Enable)
	{
		return false;
	}
	// ----
	this->ShowItem = false;
	this->ShowType = -1;
	this->ShowPrice = 0;
	// ----
	for (int i = 0; i < this->m_LoadedSellCount; i++)
	{
		if (ItemCode != ITEM(this->m_SellData[i].ItemType, this->m_SellData[i].ItemIndex))
		{
			continue;
		}
		// ----
		if (ItemLevel != this->m_SellData[i].ItemLevel)
		{
			continue;
		}
		// ----
		if (this->m_SellData[i].Price == -1)
		{
			continue;
		}
		// ----
		if (this->m_SellData[i].PriceType < 0 || this->m_SellData[i].PriceType > 4)
		{
			continue;
		}
		// ----
		this->ShowItem = true;
		this->ShowType = this->m_SellData[i].PriceType;
		this->ShowPrice = this->m_SellData[i].Price;
		*Price = this->m_SellData[i].Price;
		// ----
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool ItemPrice::CheckItemBuy(short ItemCode, int ItemLevel, __int64 * Price)
{
	if (!this->Enable)
	{
		return false;
	}
	// ----
	this->ShowItem = false;
	this->ShowType = -1;
	this->ShowPrice = 0;
	// ----
	for (int i = 0; i < this->m_LoadedBuyCount; i++)
	{
		if (ItemCode != ITEM(this->m_BuyData[i].ItemType, this->m_BuyData[i].ItemIndex))
		{
			continue;
		}
		// ----
		if (ItemLevel != this->m_BuyData[i].ItemLevel)
		{
			continue;
		}
		// ----
		if (this->m_BuyData[i].Price == -1)
		{
			continue;
		}
		// ----
		if (this->m_BuyData[i].PriceType < 0 || this->m_BuyData[i].PriceType > 4)
		{
			continue;
		}
		// ----
		this->ShowItem = true;
		this->ShowType = this->m_BuyData[i].PriceType;
		this->ShowPrice = this->m_BuyData[i].Price;
		*Price = this->m_BuyData[i].Price;
		// ----
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

__int64 ItemPrice::GetPrice(ObjectItem * lpItem, int Mode)
{
	__int64 Money = -1;
	__int64 StartMoney = pSetItemPrice(lpItem, Mode);
	__int64 NewOptionAddMoney = 0;
	int Divisor = 3;
	// ----
	if (Mode)	//-> Sell
	{
		if (gItemPrice.CheckItemSell(lpItem->ItemID, gItemPrice.ShowItemLevel, &Money))
		{
			return Money;
		}
	}
	else	//-> Buy
	{
#if(DONATE_SHOP)
		if(g_DonateShop.OpenShop >= DONAT_SHOP_START && g_DonateShop.OpenShop <= DONAT_SHOP_END)
		{
			return g_DonateShop.GetPrice(lpItem, Mode);
		}
#endif
		if (gItemPrice.CheckItemBuy(lpItem->ItemID, gItemPrice.ShowItemLevel, &Money))
		{
			return Money;
		}
	}
	// ----
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
	return pSetItemPrice(lpItem, Mode);
}
// ----------------------------------------------------------------------------------------------

void ItemPrice::ShowSellPrice(DWORD a1, const char *a2, char *Price)
{
	if (!gItemPrice.Enable || !gItemPrice.ShowItem)
	{
		pShowPrice(a1, g_ExText.GetText(88), Price);
		return;
	}
	// ----
	switch (gItemPrice.ShowType)	//-> Need Recode
	{
		case ePrice::eZen:
		{
			 pShowPrice(a1, g_ExText.GetText(88), Price);
		}
		break;
		// --
		case ePrice::eCredit:
		{
			pShowPrice(a1, g_ExText.GetText(89), Price);
		}
		break;
		// --
		case ePrice::eWCoin:
		{
			pShowPrice(a1, g_ExText.GetText(90), Price);
		}
		break;
		// --
		case ePrice::eWCoinP:
		{
			pShowPrice(a1, g_ExText.GetText(91), Price);
		}
		break;
		// --
		case ePrice::eGoblinPoint:
		{
			pShowPrice(a1, g_ExText.GetText(92), Price);
		}
		break;
		// --
		default:
		{
			if (gItemPrice.SellItemNullZen)
			{
				pShowPrice(a1, g_ExText.GetText(88), 0);
			}
			else
			{
				pShowPrice(a1, g_ExText.GetText(88), Price);
			}
		}
		break;
	}
}
// ----------------------------------------------------------------------------------------------

void ItemPrice::ShowBuyPrice(DWORD a1, const char *a2, char *Price)
{
#if(DONATE_SHOP)
	if(g_DonateShop.OpenShop >= DONAT_SHOP_START && g_DonateShop.OpenShop <= DONAT_SHOP_END)
	{
		g_DonateShop.ShowBuyPrice(a1, a2, Price);
		return;
	}
#endif
	if (!gItemPrice.Enable || !gItemPrice.ShowItem)
	{
		pShowPrice(a1, g_ExText.GetText(93), Price);

		return;
	}
	// ----
	int v14 = gItemPrice.ShowPrice;
	int v12 = v14 % 1000;
	int v13 = v14 % 1000000 / 1000;
	int v11 = v14 % 1000000000 / 1000000;
	// ----
	switch (gItemPrice.ShowType)
	{
	case ePrice::eZen:
	{
		if (v14 < 1000000000)
		{
			if (v14 < 1000000)
			{
				if (v14 < 1000)
				{
					pShowPrice(a1, g_ExText.GetText(94), v12);
				}
				else
				{
					pShowPrice(a1, g_ExText.GetText(95), v13, v12);
				}
			}
			else
			{
				pShowPrice(a1, g_ExText.GetText(96), v11, v13, v12);
			}
		}
		else
		{
			if(gItemPrice.ShowPrice >= 2000000000)
			{
				pShowPrice(a1, g_ExText.GetText(97), 2, v11, v13, v12);
			}
			else
			{
				pShowPrice(a1, g_ExText.GetText(97), 1, v11, v13, v12);
			}		 
		}
	}
		break;
		// --
	case ePrice::eCredit:
	{
		if (v14 < 1000000000)
		{
			if (v14 < 1000000)
			{
				if (v14 < 1000)
				{
					pShowPrice(a1, g_ExText.GetText(98), v12);
				}
				else
				{
					pShowPrice(a1, g_ExText.GetText(99), v13, v12);
				}
			}
			else
			{
				pShowPrice(a1, g_ExText.GetText(100), v11, v13, v12);
			}
		}
		else
		{
			pShowPrice(a1, g_ExText.GetText(101), v11, v13, v12);
		}
	}
		break;
		// --
	case ePrice::eWCoin:
	{
		if (v14 < 1000000000)
		{
			if (v14 < 1000000)
			{
				if (v14 < 1000)
				{
					pShowPrice(a1, g_ExText.GetText(102), v12);
				}
				else
				{
					pShowPrice(a1, g_ExText.GetText(103), v13, v12);
				}
			}
			else
			{
				pShowPrice(a1, g_ExText.GetText(104), v11, v13, v12);
			}
		}
		else
		{
			pShowPrice(a1, g_ExText.GetText(105), v11, v13, v12);
		}
	}
	break;
		// --
	case ePrice::eWCoinP:
	{
		if (v14 < 1000000000)
		{
			if (v14 < 1000000)
			{
				if (v14 < 1000)
				{
					pShowPrice(a1, g_ExText.GetText(106), v12);
				}
				else
				{
					pShowPrice(a1, g_ExText.GetText(107), v13, v12);
				}
			}
			else
			{
				pShowPrice(a1, g_ExText.GetText(108), v11, v13, v12);
			}
		}
		else
		{
			pShowPrice(a1, g_ExText.GetText(109), v11, v13, v12);
		}
	}
	break;
		// --
	case ePrice::eGoblinPoint:
	{
		if (v14 < 1000000000)
		{
			if (v14 < 1000000)
			{
				if (v14 < 1000)
				{
					pShowPrice(a1, g_ExText.GetText(110), v12);
				}
				else
				{
					pShowPrice(a1, g_ExText.GetText(111), v13, v12);
				}
			}
			else
			{
				pShowPrice(a1, g_ExText.GetText(112), v11, v13, v12);
			}
		}
		else
		{
			pShowPrice(a1, g_ExText.GetText(113), v11, v13, v12);
		}
	}
	break;
		// --
	default:
		{
			pShowPrice(a1, g_ExText.GetText(93), Price);
		}
		break;
	}
}
// ----------------------------------------------------------------------------------------------


void ItemPrice::ShowItemLevelName(DWORD a1, const char *a2, char * Level)
{
	pShowPrice(a1, a2, Level);
}
// ----------------------------------------------------------------------------------------------

#endif