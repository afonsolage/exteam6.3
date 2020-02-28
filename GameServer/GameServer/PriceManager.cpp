#include "StdAfx.h"
#include "user.h"
#include "PriceManager.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "Message.h"
#include "ExUser.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "ExText.h"
#include "ExLicense.h"

cPriceManager PriceManager;

void cPriceManager::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,PRICEMANAGER_DIR);
	this->AllSellNull = GetPrivateProfileInt("Common","AllSellNull",0,PRICEMANAGER_DIR);

	this->sCount = 0;
	this->bCount = 0;

	for(int i(0);i<MAX_PRICE_ITEM;i++)
	{
		this->SellPrice[i].Type = 0;
		this->SellPrice[i].Index = 0;
		this->SellPrice[i].Level = 0;
		this->SellPrice[i].Price = 0;
	}

	for (int i(0); i<MAX_PRICE_ITEM; i++)
	{
		this->BuyPrice[i].Type = 0;
		this->BuyPrice[i].Index = 0;
		this->BuyPrice[i].Level = 0;
		this->BuyPrice[i].Price = 0;
	}

	this->ReadList(PRICEMANAGER_DIR);

	return;

	FILE * file = fopen(PRICEMANAGER_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,PRICEMANAGER_DIR,"LOAD ERROR",0);
		this->Enable = false;
	}
	if(!this->Enable)return;

	char Buff[256];
	int Flag = 0;
	this->sCount = 0;
	this->bCount = 0;

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			if(this->sCount == MAX_PRICE_ITEM) break;

			int n[5];
			sscanf(Buff, "%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
			this->SellPrice[this->sCount].Type = n[0];
			this->SellPrice[this->sCount].Index = n[1];
			this->SellPrice[this->sCount].Level = n[2];
			this->SellPrice[this->sCount].PriceType = n[3];
			this->SellPrice[this->sCount].Price = n[4];
			this->sCount++;
		}

		if(Flag == 2)
		{
			if(this->bCount == MAX_PRICE_ITEM) break;

			int n[5];
			sscanf(Buff, "%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
			this->BuyPrice[this->bCount].Type = n[0];
			this->BuyPrice[this->bCount].Index = n[1];
			this->BuyPrice[this->bCount].Level = n[2];
			this->BuyPrice[this->bCount].PriceType = n[3];
			this->BuyPrice[this->bCount].Price = n[4];
			this->bCount++;
		}
	}
	fclose(file);
/*
this->Init();
int Token;
// ----
SMDFile = fopen(File, "r");
// ----
if ( !SMDFile )
{
MessageBox(NULL, "file not found", "[ItemPrice]", ERROR);
return;
}
// ----
int Category = -1;
// ----
while (true)
{
Token = GetToken();
// ----
if( Token == END )
{
break;
}
// ----
if( Token != NUMBER )
{
continue;
}
// ----
Category = TokenNumber;
// ----
while(true)
{
if( Category == 0)
{
Token = GetToken();
// ----
if( strcmp("end", TokenString) == NULL )
{
break;
}
// ----
this->Enable = TokenNumber;
// ----
Token = GetToken();
this->SellItemNull = TokenNumber;
}
else if( Category == 1 )	//-> Sell List
{
Token = GetToken();
// ----
if( strcmp("end", TokenString) == NULL )
{
break;
}
// ----
if( this->m_LoadedSellCount >= MAX_ITEMPRICE_ITEM )
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
else if( Category == 2)	//-> Buy List
{
Token = GetToken();
// ----
if( strcmp("end", TokenString) == NULL )
{
break;
}
// ----
if( this->m_LoadedBuyCount >= MAX_ITEMPRICE_ITEM )
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
this->m_BuyData[this->m_LoadedBuyCount].Price = TokenNumber;
// ----
this->m_LoadedBuyCount++;
}
}
}
// ----
this->m_IsLoaded = true;
fclose(SMDFile);
*/
}

void cPriceManager::SellPriceItem(int aIndex,int iPos,int & money)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	for(int i=0;i<this->sCount;i++)
	{
		if ( lpObj->pInventory[iPos].m_Type == ITEMGET(this->SellPrice[i].Type,this->SellPrice[i].Index) &&
			 lpObj->pInventory[iPos].m_Level == this->SellPrice[i].Level )
		{
			if(this->SellPrice[i].PriceType == 0)	//Zen
			{
				money = this->SellPrice[i].Price;
				return;
			}
			else if(this->SellPrice[i].PriceType == 1)	//Credits
			{
				lpObj->ExCred += this->SellPrice[i].Price;
				money = 0;
				ExUserDataSend(aIndex);
				return;
			}
			else if(this->SellPrice[i].PriceType == 2)	//WcoinC
			{
				lpObj->GameShop.WCoinC += this->SellPrice[i].Price;
				gGameShop.GDSaveUserInfo(aIndex);
				money = 0;
				return;
			}
			else if(this->SellPrice[i].PriceType == 3)	//Wcoin
			{
				lpObj->GameShop.WCoinP += this->SellPrice[i].Price;
				gGameShop.GDSaveUserInfo(aIndex);
				money = 0;
				return;
			}
			else if(this->SellPrice[i].PriceType == 4)	//Wcoin
			{
				lpObj->GameShop.GoblinPoint += this->SellPrice[i].Price;
				gGameShop.GDSaveUserInfo(aIndex);
				money = 0;
				return;
			}
		}
	}

	if(this->AllSellNull)
	{
		money = 0;
	}
}

bool cPriceManager::BuyPriceItem(int aIndex, int iType, int &iStoreTaxMoney, int ItemLevel)
{
	if(!this->Enable) return true;
	LPOBJ lpObj = &gObj[aIndex];
	for(int i=0;i<this->bCount;i++)
	{
		if ( iType == ITEMGET(this->BuyPrice[i].Type,this->BuyPrice[i].Index) && this->BuyPrice[i].Level == ItemLevel)
		{
			if(this->BuyPrice[i].PriceType == 0)	//Zen
			{
				iStoreTaxMoney = this->BuyPrice[i].Price;
				if(iStoreTaxMoney > lpObj->Money)
				{
					MsgNormal(aIndex,g_ExText.GetText(79),iStoreTaxMoney);
					return false;
				}
			}
			else if(this->BuyPrice[i].PriceType == 1)	//Credits
			{
				//if(g_ExLicense.CheckUser(eExUB::NSGames))
				//{
				//	if(this->BuyPrice[i].Price > lpObj->PCPoint)
				//	{
				//		MsgNormal(aIndex,"Need %d NSPoint", this->BuyPrice[i].Price);
				//		return false;
				//	}
				//	MsgNormal(aIndex, "Price: %d NSPoint",this->BuyPrice[i].Price);
				//	lpObj->ExCred -= this->BuyPrice[i].Price;
				//	ExUserDataSend(lpObj->m_Index);
				//	iStoreTaxMoney = 0;
				//}
				//else
				//{
					if(this->BuyPrice[i].Price > lpObj->ExCred)
					{
						MsgNormal(aIndex,g_ExText.GetText(80),this->BuyPrice[i].Price);
						return false;
					}
					MsgNormal(aIndex,g_ExText.GetText(81),this->BuyPrice[i].Price);
					lpObj->ExCred -= this->BuyPrice[i].Price;
					ExUserDataSend(lpObj->m_Index);
					iStoreTaxMoney = 0;
				//}
				return true;
			}
			else if(this->BuyPrice[i].PriceType == 2)	//WcoinC
			{
				if(this->BuyPrice[i].Price > lpObj->GameShop.WCoinC)
				{
					MsgNormal(aIndex,g_ExText.GetText(82),this->BuyPrice[i].Price);
					return false;
				}
				MsgNormal(aIndex,g_ExText.GetText(83),this->BuyPrice[i].Price);
				lpObj->GameShop.WCoinC -= this->BuyPrice[i].Price;
				gGameShop.GDSaveUserInfo(aIndex);
				iStoreTaxMoney = 0;
				return true;
			}
			else if(this->BuyPrice[i].PriceType == 3)	//Wcoin
			{
				if(this->BuyPrice[i].Price > lpObj->GameShop.WCoinP)
				{
					MsgNormal(aIndex,g_ExText.GetText(84),this->BuyPrice[i].Price);
					return false;
				}
				MsgNormal(aIndex,g_ExText.GetText(85),this->BuyPrice[i].Price);
				lpObj->GameShop.WCoinP -= this->BuyPrice[i].Price;
				gGameShop.GDSaveUserInfo(aIndex);
				iStoreTaxMoney = 0;
				return true;
			}
			else if(this->BuyPrice[i].PriceType == 4)	//Wcoin
			{
				if(this->BuyPrice[i].Price > lpObj->GameShop.GoblinPoint)
				{
					MsgNormal(aIndex,g_ExText.GetText(86),this->BuyPrice[i].Price);
					return false;
				}
				MsgNormal(aIndex,g_ExText.GetText(87),this->BuyPrice[i].Price);
				lpObj->GameShop.GoblinPoint -= this->BuyPrice[i].Price;
				gGameShop.GDSaveUserInfo(aIndex);
				iStoreTaxMoney = 0;
				return true;
			}
		}
	}

	return true;
}

/*
if(Flag == 1)
{
if(this->sCount == MAX_PRICE_ITEM) break;

int n[5];
sscanf(Buff, "%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
this->SellPrice[this->sCount].Type = n[0];
this->SellPrice[this->sCount].Index = n[1];
this->SellPrice[this->sCount].Level = n[2];
this->SellPrice[this->sCount].PriceType = n[3];
this->SellPrice[this->sCount].Price = n[4];
this->sCount++;
}

if(Flag == 2)
{
if(this->bCount == MAX_PRICE_ITEM) break;

int n[5];
sscanf(Buff, "%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
this->BuyPrice[this->bCount].Type = n[0];
this->BuyPrice[this->bCount].Index = n[1];
this->BuyPrice[this->bCount].Level = n[2];
this->BuyPrice[this->bCount].PriceType = n[3];
this->BuyPrice[this->bCount].Price = n[4];
this->bCount++;
}
*/

void cPriceManager::ReadList(char * File)
{
	//this->Init();
	int Token;
	// ----
	SMDFile = fopen(File, "r");
	// ----
	if (!SMDFile)
	{
		MsgBox("%s - file nor found", File);
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
				this->AllSellNull = TokenNumber;
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
				if (this->sCount >= MAX_PRICE_ITEM)
				{
					break;
				}
				// ----
				this->SellPrice[this->sCount].Type = TokenNumber;
				// ----
				Token = GetToken();
				this->SellPrice[this->sCount].Index = TokenNumber;
				// ----
				Token = GetToken();
				this->SellPrice[this->sCount].Level = TokenNumber;
				// ----
				Token = GetToken();
				this->SellPrice[this->sCount].PriceType = TokenNumber;
				// ----
				Token = GetToken();
				this->SellPrice[this->sCount].Price = TokenNumber;
				// ----
				this->sCount++;
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
				if (this->bCount >= MAX_PRICE_ITEM)
				{
					break;
				}
				// ----
				this->BuyPrice[this->bCount].Type = TokenNumber;
				// ----
				Token = GetToken();
				this->BuyPrice[this->bCount].Index = TokenNumber;
				// ----
				Token = GetToken();
				this->BuyPrice[this->bCount].Level = TokenNumber;
				// ----
				Token = GetToken();
				this->BuyPrice[this->bCount].PriceType = TokenNumber;
				// ----
				Token = GetToken();
				this->BuyPrice[this->bCount].Price = TokenNumber;
				// ----
				this->bCount++;
			}
		}
	}
	// ----
	fclose(SMDFile);
}


/*
		int MinusCred = 0;
		if(ShopC[tShop].m_item[lpMsg->Pos].m_Type == ITEMGET(14,215))
		{
			MinusCred++;
		}
		else if(ShopC[tShop].m_item[lpMsg->Pos].m_Type == ITEMGET(14,216))
		{
			MinusCred += 5;
		}
		else if(ShopC[tShop].m_item[lpMsg->Pos].m_Type == ITEMGET(14,217))
		{
			MinusCred += 10;
		}
		else if(ShopC[tShop].m_item[lpMsg->Pos].m_Type == ITEMGET(14,218))
		{
			MinusCred += 20;
		}
		else if(ShopC[tShop].m_item[lpMsg->Pos].m_Type == ITEMGET(14,219))
		{
			MinusCred += 50;
		}
		else if(ShopC[tShop].m_item[lpMsg->Pos].m_Type == ITEMGET(14,220))
		{
			MinusCred += 100;
		}
		if(MinusCred>0)
		{
			if(MinusCred > lpObj->ExCred)
			{
				MsgNormal(aIndex,"[Buy Credit] Need %d",MinusCred);
				DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
				return;
			}
			iStoreTaxMoney = 0;
			lpObj->ExCred -= MinusCred;
			ExPCPointSystem.InitPCPointForPlayer(lpObj, lpObj->PCPoint, lpObj->ExCred );
		}
*/