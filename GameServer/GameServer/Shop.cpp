//GameServer 1.00.77 JPN - Completed
//GameServer 1.00.90 JPN - Completed
#include "stdafx.h"
#include "GameServer.h"
#include "WzAG.h"
#include "Shop.h"
#include "LogProc.h"
#include "..\include\readscript.h"
#include "GameMain.h"
#include "..\common\WzMemScript.h"
#include "..\\include\\prodef.h"
#include "..\\common\\winutil.h"
#include "CastleSiegeSync.h"
#include "ExLicense.h"
#include "ExUser.h"
#include "Achievements.h"
#include "ExText.h"

CShop ShopC[MAX_SHOP];

CShop::CShop()
{
	return;
}


CShop::~CShop()
{
	return;
}

void CShop::Init()
{
	this->SendItemDataLen = 0;
	this->ItemCount = 0;
	memset(this->ShopInventoryMap, 0, sizeof(this->ShopInventoryMap));
#if(DONATE_SHOP==TRUE)
	ZeroMemory(&ShopEx,sizeof(ShopEx));
#endif
}

BOOL CShop::InsertItem(int type, int index, int level, int dur, int op1, int op2 ,int op3, int Excellent, int Ancient)
{
	int itemp;
	int width;
	int height;
	int x;
	int y;
	int blank;

	blank = -1;
	itemp = type * MAX_SUBTYPE_ITEMS + index;
	
	if ( itemp < 0 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 53)), __FILE__, __LINE__, type, index);
		return false;
	}
	
	ItemGetSize(itemp, width, height);

	if ( width < 0 || height < 0 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 54)), __FILE__, __LINE__);
		return FALSE;
	}

	for ( y=0;y<15;y++)
	{
		for ( x=0;x<8;x++)
		{
			if ( this->ShopInventoryMap[x + y*8] == 0 )
			{
				blank = this->InentoryMapCheck(x, y, width, height);

				if ( blank >= 0 )
				{
					goto skiploop;
				}
			}
		}
	}

	if ( blank < 0 )
	{
		MsgBox("error-L2 : %s %d", __FILE__, __LINE__);
		return FALSE;
	}

skiploop:

	this->m_item[blank].m_Level = level;

	if ( dur == 0 )
	{
		dur = ItemGetDurability(ITEMGET(type, index), level, 0, 0);
	}

	this->m_item[blank].m_Durability = (float)dur;
	this->m_item[blank].Convert(itemp, op1, op2, op3, Excellent, Ancient, 0, NULL, 0xFF, 0, CURRENT_DB_VERSION);
	this->m_item[blank].Value();

	if(g_SocketOption.CheckItemType(itemp) == 1)//Season 4.5 addon
	{
		g_SocketOption.ClearSlotOption(&this->m_item[blank],g_iShopBuySocketItemSlotCount);
	}

	this->SendItemData[this->SendItemDataLen] = blank;
	this->SendItemDataLen++;
	ItemByteConvert((LPBYTE)&this->SendItemData[this->SendItemDataLen], this->m_item[blank]);
	this->SendItemDataLen += MAX_ITEM_INFO;
	this->ItemCount++;

	return TRUE;
}

#if(DONATE_SHOP==TRUE)
BOOL CShop::InsertItemSocket(int type, int index, int level, int dur, int op1, int op2 ,int op3, int Excellent, int Ancient, BYTE Sock1, BYTE Sock2, BYTE Sock3, BYTE Sock4, BYTE Sock5, BYTE iPayType, DWORD iPayPrice)
{
	int itemp;
	int width;
	int height;
	int x;
	int y;
	int blank;

	blank = -1;
	itemp = type * MAX_SUBTYPE_ITEMS + index;
	
	if ( itemp < 0 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 53)), __FILE__, __LINE__, type, index);
		return false;
	}
	
	ItemGetSize(itemp, width, height);

	if ( width < 0 || height < 0 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 54)), __FILE__, __LINE__);
		return FALSE;
	}

	for ( y=0;y<15;y++)
	{
		for ( x=0;x<8;x++)
		{
			if ( this->ShopInventoryMap[x + y*8] == 0 )
			{
				blank = this->InentoryMapCheck(x, y, width, height);

				if ( blank >= 0 )
				{
					goto skiploop;
				}
			}
		}
	}

	if ( blank < 0 )
	{
		MsgBox("error-L2 : %s %d", __FILE__, __LINE__);
		return FALSE;
	}

skiploop:

	this->m_item[blank].m_Level = level;

	if ( dur == 0 )
	{
		dur = ItemGetDurability(ITEMGET(type, index), level, 0, 0);
	}

	this->m_item[blank].m_Durability = dur;
	this->m_item[blank].Convert(itemp, op1, op2, op3, Excellent, Ancient, 0, NULL, 0xFF, 0, CURRENT_DB_VERSION);
	this->m_item[blank].Value();

	this->ShopEx[this->ItemCount].ItemType = type;
	this->ShopEx[this->ItemCount].ItemIndex = index;
	this->ShopEx[this->ItemCount].ItemLevel = level;
	this->ShopEx[this->ItemCount].ItemExl = Excellent;
	this->ShopEx[this->ItemCount].ItemAnc = Ancient;
	this->ShopEx[this->ItemCount].PayType = iPayType;
	this->ShopEx[this->ItemCount].PayPrice = iPayPrice;

	if(g_SocketOption.CheckItemType(itemp) == 1)
	{
		this->m_item[blank].m_SocketOption[0] = Sock1;
		this->m_item[blank].m_SocketOption[1] = Sock2;
		this->m_item[blank].m_SocketOption[2] = Sock3;
		this->m_item[blank].m_SocketOption[3] = Sock4;
		this->m_item[blank].m_SocketOption[4] = Sock5;

		this->m_item[blank].m_SocketOptionIndex = 0xFF;
	}

	this->SendItemData[this->SendItemDataLen] = blank;
	this->SendItemDataLen++;
	ItemByteConvert((LPBYTE)&this->SendItemData[this->SendItemDataLen], this->m_item[blank]);
	this->SendItemDataLen += MAX_ITEM_INFO;
	this->ItemCount++;

	return TRUE;
}

BOOL CShop::InsertItemEx(int type, int index, int level, int dur, int op1, int op2 ,int op3, int Excellent, int Ancient, BYTE iPayType, DWORD iPayPrice)
{
	int itemp;
	int width;
	int height;
	int x;
	int y;
	int blank;

	blank = -1;
	itemp = type * MAX_SUBTYPE_ITEMS + index;
	
	if ( itemp < 0 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 53)), __FILE__, __LINE__, type, index);
		return false;
	}
	
	ItemGetSize(itemp, width, height);

	if ( width < 0 || height < 0 )
	{
		MsgBox(lMsg.Get(MSGGET(2, 54)), __FILE__, __LINE__);
		return FALSE;
	}

	for ( y=0;y<15;y++)
	{
		for ( x=0;x<8;x++)
		{
			if ( this->ShopInventoryMap[x + y*8] == 0 )
			{
				blank = this->InentoryMapCheck(x, y, width, height);

				if ( blank >= 0 )
				{
					goto skiploop;
				}
			}
		}
	}

	if ( blank < 0 )
	{
		MsgBox("error-L2 : %s %d", __FILE__, __LINE__);
		return FALSE;
	}

skiploop:

	this->m_item[blank].m_Level = level;

	if ( dur == 0 )
	{
		dur = ItemGetDurability(ITEMGET(type, index), level, 0, 0);
	}

	this->m_item[blank].m_Durability = dur;
//#if(SHOP_EXL_ANC==TRUE)
	this->m_item[blank].Convert(itemp, op1, op2, op3, Excellent, Ancient, 0, NULL, 0xFF, 0, CURRENT_DB_VERSION);
//#else
//	this->m_item[blank].Convert(itemp, op1, op2, op3, 0, 0, 0, NULL, 0xFF, CURRENT_DB_VERSION);
//#endif
	this->m_item[blank].Value();

	this->ShopEx[this->ItemCount].ItemType = type;
	this->ShopEx[this->ItemCount].ItemIndex = index;
	this->ShopEx[this->ItemCount].ItemLevel = level;
	this->ShopEx[this->ItemCount].ItemExl = Excellent;
	this->ShopEx[this->ItemCount].ItemAnc = Ancient;
	this->ShopEx[this->ItemCount].PayType = iPayType;
	this->ShopEx[this->ItemCount].PayPrice = iPayPrice;

	if(g_SocketOption.CheckItemType(itemp) == 1)//Season 4.5 addon
	{
		g_SocketOption.ClearSlotOption(&this->m_item[blank],g_iShopBuySocketItemSlotCount);
	}

	this->SendItemData[this->SendItemDataLen] = blank;
	this->SendItemDataLen++;
	ItemByteConvert((LPBYTE)&this->SendItemData[this->SendItemDataLen], this->m_item[blank]);
	this->SendItemDataLen += MAX_ITEM_INFO;
	this->ItemCount++;

	return TRUE;
}
#endif

int CShop::InentoryMapCheck(int sx, int sy, int width, int height)
{
	int x;
	int y;
	int blank = 0;

	if ( (sx+width) > 8 )
		return -1;

	if ( (sy+height) > 15 )
		return -1;

	for(y=0;y<height;y++)
	{
		for(x=0;x<width;x++)
		{
			if ( this->ShopInventoryMap[( sy + y) * 8 + (sx + x)] )
			{
				blank++;
				break;
			}
		}
	}

	if ( blank == 0 )
	{
		for(y=0;y<height;y++)
		{
			for(x=0;x<width;x++)
			{
				this->ShopInventoryMap[( sy + y) * 8 + (sx + x)] = 1;
			}
		}

		return (sx + sy*8);
	}

	return -1;
}

BOOL CShop::LoadShopItem(char* filename )
{
	int Token;
	int type;
	int index;
	int level;
	int dur;
	int op1;
	int op2;
	int op3;
	int Excellent;
	int Ancient;

	this->Init();

	SMDFile = fopen(filename, "r");

	if ( SMDFile == NULL )
	{
		MsgBox("Shop data load error %s", filename);
		return FALSE;
	}

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			type = (int)TokenNumber;

			Token = GetToken();
			index = (int)TokenNumber;

			Token = GetToken();
			level = (int)TokenNumber;

			Token = GetToken();
			dur = (int)TokenNumber;

			Token = GetToken();
			op1 = (int)TokenNumber;

			Token = GetToken();
			op2 = (int)TokenNumber;

			Token = GetToken();
			op3 = (int)TokenNumber;

			Token = GetToken();
			Excellent = TokenNumber;

			Token = GetToken();
			Ancient = TokenNumber;

			if(Ancient != 5 && Ancient != 10)
			{
				Ancient = 0;
			}

			if (this->InsertItem(type, index, level, dur, op1, op2, op3, Excellent, Ancient) == FALSE )
			{
				MsgBox("error-L3 : %s %s %d", filename, __FILE__, __LINE__);
			}
		}
	}

	fclose(SMDFile);
	return true;
}


#if(DONATE_SHOP==TRUE)
BOOL CShop::LoadShopItemEx(char* filename )
{
	int Token;
	int type;
	int index;
	int level;
	int dur;
	int op1;
	int op2;
	int op3;
	int Excellent;
	int Ancient;
	int iPayType;
	int iPayPrice;

	BYTE Sock1;
	BYTE Sock2;
	BYTE Sock3;
	BYTE Sock4;
	BYTE Sock5;

	this->Init();

	SMDFile = fopen(filename, "r");

	if ( SMDFile == NULL )
	{
		MsgBox("Shop data load error %s", filename);
		return FALSE;
	}

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			type = TokenNumber;

			Token = GetToken();
			index = TokenNumber;

			Token = GetToken();
			level = TokenNumber;

			Token = GetToken();
			dur = TokenNumber;

			Token = GetToken();
			op1 = TokenNumber;

			Token = GetToken();
			op2 = TokenNumber;

			Token = GetToken();
			op3 = TokenNumber;

			Token = GetToken();
			Excellent = TokenNumber;

			if(Excellent < 0 || Excellent > 63)
			{
				Excellent = 0;
			}

			Token = GetToken();
			Ancient = TokenNumber;

			if(Ancient != 5 && Ancient != 10)
			{
				Ancient = 0;
			}

			// ----

			Token = GetToken();
			Sock1 = TokenNumber;

			Token = GetToken();
			Sock2 = TokenNumber;

			Token = GetToken();
			Sock3 = TokenNumber;

			Token = GetToken();
			Sock4 = TokenNumber;

			Token = GetToken();
			Sock5 = TokenNumber;

			// ----

			Token = GetToken();
			iPayType = TokenNumber;

			if(iPayType < 0 || iPayType > 3)
			{
				iPayType = 0;
			}

			Token = GetToken();
			iPayPrice = TokenNumber;

			if(iPayPrice < 0)
			{
				iPayPrice = 0;
			}

			//if (this->InsertItemEx(type, index, level, dur, op1, op2, op3, Excellent, Ancient, iPayType, iPayPrice) == FALSE )
			if (this->InsertItemSocket(type, index, level, dur, op1, op2, op3, Excellent, Ancient, Sock1, Sock2, Sock3, Sock4, Sock5, iPayType, iPayPrice) == FALSE )
			{
				MsgBox("error-L3 : %s %s %d", filename, __FILE__, __LINE__);
			}
		}
	}

	fclose(SMDFile);
	return true;
}
#endif

BOOL CShop::LoadShopItem(int ShopNumber)
{
	gWzAG.RequestData(ShopNumber);
	int DataBufferSize = gWzAG.GetDataBufferSize();
	char* DataBuffer = gWzAG.GetDataBuffer();

	CWzMemScript WzMemScript;
	int Token;
	int type;
	int index;
	int level;
	int dur;
	int op1;
	int op2;
	int op3;
	int Excellent;
	int Ancient;

	WzMemScript.SetBuffer(DataBuffer, DataBufferSize);

	this->Init();

	
	while ( true )
	{
		Token = WzMemScript.GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			type = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			index = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			level = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			dur = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			op1 = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			op2 = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();
			op3 = WzMemScript.GetNumber();

			Token = GetToken();
			Excellent = TokenNumber;

			Token = GetToken();
			Ancient = TokenNumber;

			if(Ancient != 5 && Ancient != 10)
			{
				Ancient = 0;
			}

			if (this->InsertItem(type, index, level, dur, op1, op2, op3, Excellent, Ancient) == FALSE )
			{
				MsgBox("error-L3 : Shop %d", ShopNumber);
			}
		}
	}

	return TRUE;
}

BOOL ShopDataLoad() //Season 3.0 identical Season 2.5 identical gs-cs 56
{
	ShopC[0].LoadShopItem("..\\data\\Shops\\00_HanzoBlacksmith.txt");
	ShopC[1].LoadShopItem("..\\data\\Shops\\01_LumenBarmaid.txt");
	ShopC[2].LoadShopItem("..\\data\\Shops\\02_PasiMage.txt");
	ShopC[3].LoadShopItem("..\\data\\Shops\\03_HaroldWandering.txt");
	ShopC[4].LoadShopItem("..\\data\\Shops\\04_Wandering.txt");
	ShopC[5].LoadShopItem("..\\data\\Shops\\05_PotionGirl.txt");
	ShopC[6].LoadShopItem("..\\data\\Shops\\06_LiamBarmaid.txt");
	ShopC[7].LoadShopItem("..\\data\\Shops\\07_Wizard.txt");
	ShopC[8].LoadShopItem("..\\data\\Shops\\08_ZiennaWeapon.txt");
	ShopC[9].LoadShopItem("..\\data\\Shops\\09_EoCraftsman.txt");
	ShopC[10].LoadShopItem("..\\data\\Shops\\10_ElfLala.txt");
	ShopC[11].LoadShopItem("..\\data\\Shops\\11_Alex.txt");
	ShopC[12].LoadShopItem("..\\data\\Shops\\12_ThompsonKennel.txt");

	//season 2.5 add-on
	ShopC[13].LoadShopItem("..\\data\\Shops\\13_FireworksGirl.txt"); //WzAG 0x1E
	//ShopC[14].LoadShopItem("..\\data\\Shops\\14_PCPoint.txt"); //WzAG 0x1F

	//season 3.0 add-on
	ShopC[15].LoadShopItem("..\\data\\Shops\\15_Silvia.txt"); //WzAG 0x20
	ShopC[16].LoadShopItem("..\\data\\Shops\\16_Leah.txt"); //WzAG 0x21
	ShopC[17].LoadShopItem("..\\data\\Shops\\17_Marseille.txt"); //WzAG 0x22

	//season 4.5 add-on
	///

	//Season 5 Shop
	ShopC[18].LoadShopItem("..\\data\\Shops\\19_Bolo.txt"); //WzAG 0x22
	ShopC[19].LoadShopItem("..\\data\\Shops\\01_LumenBarmaid.txt"); //WzAG 0x22

#if(DONATE_SHOP==TRUE)
	if(g_ExLicense.CheckUser(eExUB::MedoniAndrei) || 
		g_ExLicense.CheckUser(eExUB::absolute) || 
		g_ExLicense.CheckUser(eExUB::MU2Play) || 
		g_ExLicense.CheckUser(eExUB::Local) ||
		g_ExLicense.CheckUser(eExUB::Stone) || g_ExLicense.CheckUser(eExUB::Sentinel) || g_ExLicense.CheckUser(eExUB::Artem) ||
		THINNAKORN_MAC == 1 ||
		g_ExLicense.CheckUser(eExUB::EpicMU) ||
		g_ExLicense.CheckUser(eExUB::Escalate) ||
		g_ExLicense.CheckUser(eExUB::Artem2) ||
		g_ExLicense.CheckUser(eExUB::RevoMU) ||
		g_ExLicense.CheckUser(eExUB::TGBA_LLC) ||
		g_ExLicense.CheckUser(eExUB::GloryMU) ||
		g_ExLicense.CheckUser(eExUB::ArcMu) ||
		g_ExLicense.CheckUser(eExUB::mu4you) ||
		g_ExLicense.CheckUser(eExUB::eternalmu) ||
		g_ExLicense.CheckUser(eExUB::NSGames)
		)
	{
		ShopC[20].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\00_DonateShop.txt"));
		ShopC[21].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\01_DonateShop.txt"));
		ShopC[22].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\02_DonateShop.txt"));
		ShopC[23].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\03_DonateShop.txt"));
		ShopC[24].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\04_DonateShop.txt"));
		ShopC[25].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\05_DonateShop.txt"));
		ShopC[26].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\06_DonateShop.txt"));
		ShopC[27].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\07_DonateShop.txt"));
		ShopC[28].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\08_DonateShop.txt"));
		ShopC[29].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\09_DonateShop.txt"));
		ShopC[30].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\10_DonateShop.txt"));
		ShopC[31].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\11_DonateShop.txt"));
		ShopC[32].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\12_DonateShop.txt"));
		ShopC[33].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\13_DonateShop.txt"));
		ShopC[34].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\14_DonateShop.txt"));
		ShopC[35].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\15_DonateShop.txt"));
		ShopC[36].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\16_DonateShop.txt"));
		ShopC[37].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\17_DonateShop.txt"));
		ShopC[38].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\18_DonateShop.txt"));
		ShopC[39].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\19_DonateShop.txt"));
		ShopC[40].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\20_DonateShop.txt"));
		ShopC[41].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\21_DonateShop.txt"));
		ShopC[42].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\22_DonateShop.txt"));
		ShopC[43].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\23_DonateShop.txt"));
		ShopC[44].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\24_DonateShop.txt"));
		ShopC[45].LoadShopItemEx(gDirPath.GetNewPath("ExData\\Donate\\25_DonateShop.txt"));
	}
#endif

	LogAdd(lMsg.Get(MSGGET(1, 209)));
	return TRUE;
}

#if(DONATE_SHOP==TRUE)
struct GC_ShopPay
{
	BYTE ItemType;
	BYTE ItemIndex;
	BYTE ItemLevel;
	BYTE ItemExl;
	BYTE ItemAnc;
	BYTE PayType;
	DWORD PayPrice;
};

void CShop::GC_ShopInfo(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	int icount = 0;
	int datasize = 6;
	BYTE SendBuff[5000];

	for(int i=0; i < this->ItemCount; i++)
	{
		if(!this->ShopEx[i].PayType) 
		{
			continue;
		}

		GC_ShopPay p;

		p.ItemType = this->ShopEx[i].ItemType;
		p.ItemIndex = this->ShopEx[i].ItemIndex;
		p.ItemLevel = this->ShopEx[i].ItemLevel;
		p.ItemExl = this->ShopEx[i].ItemExl;
		p.ItemAnc = this->ShopEx[i].ItemAnc;
		p.PayType = this->ShopEx[i].PayType;
		p.PayPrice = this->ShopEx[i].PayPrice;

		memcpy(&SendBuff[datasize],&p,sizeof(p));
		datasize += sizeof(p);

		icount++;

		if(icount >= MAX_ITEM_IN_SHOP-1)
		{
			break;		
		}
	}

	if(icount > 0)
	{
		SendBuff[0]=0xC2;	// packet header
		SendBuff[1]=SET_NUMBERH(datasize);
		SendBuff[2]=SET_NUMBERL(datasize);
		SendBuff[3]=0xFA;
		SendBuff[4]=0x07;
		SendBuff[5]=this->ItemCount;
		DataSend(aIndex,SendBuff,datasize);
	}
}

bool CheckExellent(int Exl1, int Exl2)
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

bool CShop::CheckBuyItemEx(int aIndex, int ItemPos, int &iStoreTaxMoney)
{
	char szBuff[256] = { 0 };

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	for(int i=0; i<this->ItemCount; i++)
	{
		if ( this->m_item[ItemPos].m_Type != ITEMGET(this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex))
		{
			continue;
		}
		// ----
		if (this->m_item[ItemPos].m_Level != this->ShopEx[i].ItemLevel)
		{
			continue;
		}
		// ----
		if(!CheckExellent(this->m_item[ItemPos].m_NewOption, this->ShopEx[i].ItemExl))
		{
			continue;
		}
		// ----
		if (this->ShopEx[i].ItemAnc != this->m_item[ItemPos].m_SetOption)
		{
			continue;
		}
		// ----
		if (this->ShopEx[i].PayType <= 0 || this->ShopEx[i].PayType > 3)
		{
			continue;
		}
		// ----

		if(this->ShopEx[i].PayType == ePriceZen)
		{
			iStoreTaxMoney = this->ShopEx[i].PayPrice;
			if(iStoreTaxMoney > lpUser->Money)
			{
				sprintf_s(szBuff,g_ExText.GetText(231),iStoreTaxMoney);
				GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
				return false;
			}
			return true;
		}
		else if(this->ShopEx[i].PayType == ePriceBonus)
		{
			if(this->ShopEx[i].PayPrice > lpUser->GameShop.WCoinC)
			{
				sprintf_s(szBuff,g_ExText.GetText(232),this->ShopEx[i].PayPrice);
				GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
				return false;
			}
			//lpUser->Bonus -= this->ShopEx[i].PayPrice;
			//GJSetCharacterInfo(lpUser, lpUser->m_Index, 0);
			iStoreTaxMoney = 0;
			return true;
		}
		else if(this->ShopEx[i].PayType == ePriceCredit)
		{
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				if(this->ShopEx[i].PayPrice > lpUser->PCPoint)
				{
					sprintf_s(szBuff, "[Buy] Need %d NSPoint", this->ShopEx[i].PayPrice);
					GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
					return false;
				}
				//lpUser->Credits -= this->ShopEx[i].PayPrice;
				//GJSetCharacterInfo(lpUser, lpUser->m_Index, 0);
				iStoreTaxMoney = 0;
				return true;
			}
			else
			{
				if(this->ShopEx[i].PayPrice > lpUser->ExCred)
				{
					sprintf_s(szBuff,g_ExText.GetText(233),this->ShopEx[i].PayPrice);
					GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
					return false;
				}
				//lpUser->Credits -= this->ShopEx[i].PayPrice;
				//GJSetCharacterInfo(lpUser, lpUser->m_Index, 0);
				iStoreTaxMoney = 0;
				return true;
			}
		}
	}

	return true;
}

bool CShop::BuyItemEx(int aIndex, int ItemPos)
{
	char szBuff[256] = { 0 };

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	for(int i=0; i<this->ItemCount; i++)
	{
		if ( this->m_item[ItemPos].m_Type != ITEMGET(this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex))
		{
			continue;
		}
		// ----
		if (this->m_item[ItemPos].m_Level != this->ShopEx[i].ItemLevel)
		{
			continue;
		}
		// ----
		if(!CheckExellent(this->m_item[ItemPos].m_NewOption, this->ShopEx[i].ItemExl))
		{
			continue;
		}
		// ----
		if (this->ShopEx[i].ItemAnc != this->m_item[ItemPos].m_SetOption)
		{
			continue;
		}
		// ----
		if (this->ShopEx[i].PayType <= 0 || this->ShopEx[i].PayType > 3)
		{
			continue;
		}
		// ----

		if(this->ShopEx[i].PayType == ePriceZen)
		{
			if(this->ShopEx[i].PayPrice > lpUser->Money)
			{
				sprintf_s(szBuff,g_ExText.GetText(234),this->ShopEx[i].PayPrice);
				GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
				return false;
			}
			lpUser->Money -= this->ShopEx[i].PayPrice;
			GCMoneySend(aIndex, lpUser->Money);
			return true;
		}
		else if(this->ShopEx[i].PayType == ePriceBonus)
		{
			if(this->ShopEx[i].PayPrice > lpUser->GameShop.WCoinC)
			{
				sprintf_s(szBuff,g_ExText.GetText(235),this->ShopEx[i].PayPrice);
				GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
				return false;
			}
			lpUser->GameShop.WCoinC -= this->ShopEx[i].PayPrice;
			sprintf_s(szBuff,g_ExText.GetText(236),(int)lpUser->GameShop.WCoinC);
			GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
			gGameShop.GDSaveUserInfo(aIndex);
			ExUserDataSend(aIndex);
#if(CREDIT_DONATE_LOG==TRUE)
			int iType = ITEMGET(this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex);

			g_BonusShopLog.Output("[%s] [%s] Buy: Item(Name:%s,Type:%d,Index:%d,Level:%d,Luck:%d,Add:%d,Exl:%d,Anc:%d)",
				lpUser->AccountID, lpUser->Name, 
				ItemAttribute[iType].Name, this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex, 
				this->ShopEx[i].ItemLevel, this->m_item->m_Option2, this->m_item->m_Option3, this->m_item->m_NewOption, this->m_item->m_SetOption);
#endif
			return true;
		}
		else if(this->ShopEx[i].PayType == ePriceCredit)
		{
			if(g_ExLicense.CheckUser(eExUB::NSGames))
			{
				if(this->ShopEx[i].PayPrice > lpUser->PCPoint)
				{
					sprintf_s(szBuff, "[Buy] Need %d NSPoint", this->ShopEx[i].PayPrice);
					GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
					return false;
				}
				lpUser->PCPoint -= this->ShopEx[i].PayPrice;

				#if(SYSTEM_ACHIEVEMENTS)
				g_Achievements.BuyDonateShopItem(aIndex, this->ShopEx[i].PayPrice);
				#endif

				//GJSetCharacterInfo(lpUser, lpUser->m_Index, 0, FALSE, FALSE, FALSE, FALSE);

				sprintf_s(szBuff,"[Buy] %d NSPoint",(int)lpUser->ExCred);
				GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
				ExUserDataSend(aIndex);
				#if(CREDIT_DONATE_LOG==TRUE)
				int iType = ITEMGET(this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex);

				g_CreditShopLog.Output("[%s] [%s] Buy: Item(Name:%s,Type:%d,Index:%d,Level:%d,Luck:%d,Add:%d,Exl:%d,Anc:%d) Price: %d",
					lpUser->AccountID, lpUser->Name, 
					ItemAttribute[iType].Name, this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex, 
					this->ShopEx[i].ItemLevel, this->m_item->m_Option2, this->m_item->m_Option3, this->m_item->m_NewOption, this->m_item->m_SetOption,
					this->ShopEx[i].PayPrice);
				#endif
				return true;
			}
			else
			{
				if(this->ShopEx[i].PayPrice > lpUser->ExCred)
				{
					sprintf_s(szBuff,g_ExText.GetText(237),this->ShopEx[i].PayPrice);
					GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
					return false;
				}
				lpUser->ExCred -= this->ShopEx[i].PayPrice;

				#if(SYSTEM_ACHIEVEMENTS)
				g_Achievements.BuyDonateShopItem(aIndex, this->ShopEx[i].PayPrice);
				#endif

				//GJSetCharacterInfo(lpUser, lpUser->m_Index, 0, FALSE, FALSE, FALSE, FALSE);

				sprintf_s(szBuff,g_ExText.GetText(238),(int)lpUser->ExCred);
				GCServerMsgStringSend(szBuff, lpUser->m_Index, 1);
				ExUserDataSend(aIndex);
				#if(CREDIT_DONATE_LOG==TRUE)
				int iType = ITEMGET(this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex);

				g_CreditShopLog.Output("[%s] [%s] Buy: Item(Name:%s,Type:%d,Index:%d,Level:%d,Luck:%d,Add:%d,Exl:%d,Anc:%d) Price: %d",
					lpUser->AccountID, lpUser->Name, 
					ItemAttribute[iType].Name, this->ShopEx[i].ItemType, this->ShopEx[i].ItemIndex, 
					this->ShopEx[i].ItemLevel, this->m_item->m_Option2, this->m_item->m_Option3, this->m_item->m_NewOption, this->m_item->m_SetOption,
					this->ShopEx[i].PayPrice);
				#endif
				return true;
			}
		}
	}

	return false;
}

void NewShopRecv(CG_NEW_CASH_SHOP* Recv, int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(g_ExUser.InSafeZone(aIndex) == false)
	{
		return;
	}

	int ShopNum = Recv->Number;

	if ( ShopNum < MAX_SHOP && ShopNum >= 0 )
	{
		if ( ShopC[ShopNum].ItemCount < TRUE )
		{
			return;
		}
	}
	else
	{
		return;
	}

	lpUser->TargetShopNumber = ShopNum;
	lpUser->m_IfState.use = 1;
	lpUser->m_IfState.type = 3;
	lpUser->m_ShopTime = 0;

	PMSG_TALKRESULT pResult;
	pResult.h.c = 0xC3;
	pResult.h.headcode = 0x30;
	pResult.h.size = sizeof(pResult);
	pResult.result = 0;
	DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);

	BYTE SendByte[1024];
	int lOfs = 0;

	PMSG_SHOPITEMCOUNT pShopItemCount;

	lOfs += sizeof(pShopItemCount );

	int size = lOfs + ShopC[ShopNum].SendItemDataLen;
	PHeadSetW((LPBYTE)&pShopItemCount, 0x31, size);
	pShopItemCount.Type = 0;
	pShopItemCount.count = ShopC[ShopNum].ItemCount;
	memcpy(SendByte, &pShopItemCount, sizeof(pShopItemCount));
	memcpy(&SendByte[lOfs], ShopC[ShopNum].SendItemData, ShopC[ShopNum].SendItemDataLen);

	DataSend(aIndex, SendByte, size);
	GCAnsCsMapSvrTaxInfo(lpUser->m_Index,2,  ::g_CastleSiegeSync.GetTaxRateStore(lpUser->m_Index));
	
	GC_SHOP_CLICK pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x06, sizeof(GC_SHOP_CLICK));	//need next
	// ----
	pRequest.Shop_Num = ShopNum;
	// ----
	DataSend(aIndex, (LPBYTE)&pRequest, sizeof(pRequest));
	                                       
	ShopC[ShopNum].GC_ShopInfo(aIndex);
}
#endif