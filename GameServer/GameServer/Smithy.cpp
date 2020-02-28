#include "StdAfx.h"
#include "Smithy.h"
#include "GameMain.h"
#include "..\\include\\ReadScript.h"
#include "logproc.h"
#include "DSProtocol.h"
#include "ExUser.h"
#include "ExLicense.h"
#include "Achievements.h"

#if(CUSTOM_SMITHY == TRUE)

CSmithy g_Smithy;

CSmithy::CSmithy()
{
	this->Init();
}

CSmithy::~CSmithy()
{
}

void CSmithy::Init()
{
	this->itemdata.clear();
	this->MaxLevel = 0;
	this->LevelPrice = 0;
	this->LuckPrice = 0;
	this->AddPrice = 0;
	this->Opt1Price = 0;
	this->Opt2Price = 0;
	this->Opt3Price = 0;
	this->Opt4Price = 0;
	this->Opt5Price = 0;
	this->Opt6Price = 0;
	this->MaxExlOpt = 6;
}

void CSmithy::Load()
{
	if(!g_ExLicense.user.Smithy)
	{
		return;
	}
	this->Init();
	this->Read(gDirPath.GetNewPath("ExData\\Smithy.ini"));
}

void CSmithy::Read(char* filename)
{
	SMDToken Token;
	SMDFile = fopen(filename, "r");

	if(!SMDFile)
	{
		MsgBox("[Smithy] %s file not found", filename);
		return;
	}

	while(true)
	{
		SMDToken Token = GetToken();

		if( Token == END )
		{
			break;
		}

		int Type = (int)TokenNumber;

		while(true)
		{
			if(Type == 0)
			{
				Token = GetToken();
				if(!strcmp("end", TokenString))
				{
					break;
				}
				this->MaxLevel = TokenNumber;
				Token = GetToken();
				this->LevelPrice = TokenNumber;
				Token = GetToken();
				this->LuckPrice = TokenNumber;
				Token = GetToken();
				this->AddPrice = TokenNumber;
				Token = GetToken();
				this->Opt1Price = TokenNumber;
				Token = GetToken();
				this->Opt2Price = TokenNumber;
				Token = GetToken();
				this->Opt3Price = TokenNumber;
				Token = GetToken();
				this->Opt4Price = TokenNumber;
				Token = GetToken();
				this->Opt5Price = TokenNumber;
				Token = GetToken();
				this->Opt6Price = TokenNumber;
				Token = GetToken();
				this->MaxExlOpt = TokenNumber;
			}
			if(Type == 1)
			{
				Token = GetToken();
				if(!strcmp("end", TokenString))
				{
					break;
				}
				SmithyDATA lpData;
				lpData.Type = TokenNumber;
				Token = GetToken();
				lpData.Index = TokenNumber;
				lpData.Class = Type-1;
				Token = GetToken();
				lpData.Price = TokenNumber;
				this->itemdata.push_back(lpData);
			}
			else if(Type == 2)
			{
				Token = GetToken();
				if(!strcmp("end", TokenString))
				{
					break;
				}
				SmithyDATA lpData;
				lpData.Type = TokenNumber;
				Token = GetToken();
				lpData.Index = TokenNumber;
				lpData.Class = Type-1;
				Token = GetToken();
				lpData.Price = TokenNumber;
				this->itemdata.push_back(lpData);
			}
			else if(Type == 3)
			{
				Token = GetToken();
				if(!strcmp("end", TokenString))
				{
					break;
				}
				SmithyDATA lpData;
				lpData.Type = TokenNumber;
				Token = GetToken();
				lpData.Index = TokenNumber;
				lpData.Class = Type-1;
				Token = GetToken();
				lpData.Price = TokenNumber;
				this->itemdata.push_back(lpData);
			}
			else if(Type == 4)
			{
				Token = GetToken();
				if(!strcmp("end", TokenString))
				{
					break;
				}
				SmithyDATA lpData;
				lpData.Type = TokenNumber;
				Token = GetToken();
				lpData.Index = TokenNumber;
				lpData.Class = Type-1;
				Token = GetToken();
				lpData.Price = TokenNumber;
				this->itemdata.push_back(lpData);
			}
			else if(Type == 5)
			{
				Token = GetToken();
				if(!strcmp("end", TokenString))
				{
					break;
				}
				SmithyDATA lpData;
				lpData.Type = TokenNumber;
				Token = GetToken();
				lpData.Index = TokenNumber;
				lpData.Class = Type-1;
				Token = GetToken();
				lpData.Price = TokenNumber;
				this->itemdata.push_back(lpData);
			}
			else if(Type == 6)
			{
				Token = GetToken();
				if(!strcmp("end", TokenString))
				{
					break;
				}
				SmithyDATA lpData;
				lpData.Type = TokenNumber;
				Token = GetToken();
				lpData.Index = TokenNumber;
				lpData.Class = Type-1;
				Token = GetToken();
				lpData.Price = TokenNumber;
				this->itemdata.push_back(lpData);
			}
			else if(Type == 7)
			{
				Token = GetToken();
				if(!strcmp("end", TokenString))
				{
					break;
				}
				SmithyDATA lpData;
				lpData.Type = TokenNumber;
				Token = GetToken();
				lpData.Index = TokenNumber;
				lpData.Class = Type-1;
				Token = GetToken();
				lpData.Price = TokenNumber;
				this->itemdata.push_back(lpData);
			}
		}
	}

	fclose(SMDFile);
	LogAdd("%s file load!", filename);
}

void CSmithy::GCInitItem(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	GC_SmithyInit pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x1E,  sizeof(pMsg));
	pMsg.result = true;
	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void CSmithy::GCIemSend(int aIndex)
{
	if(!g_ExLicense.user.Smithy)
	{
		return;
	}

	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	this->GCSettingsSend(aIndex);
	this->GCInitItem(aIndex);
	for(int i = 0; i < itemdata.size(); i++)
	{
		GC_SmithyDATA pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x1D,  sizeof(pMsg));
		pMsg.Class = itemdata[i].Class;
		pMsg.Type = itemdata[i].Type;
		pMsg.Index = itemdata[i].Index;
		pMsg.Price = itemdata[i].Price;
		DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
	}
}

void CSmithy::GCSettingsSend(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	GC_SmithySettings pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x1C,  sizeof(pMsg));
	pMsg.MaxLevel = this->MaxLevel;
	pMsg.LevelPrice = this->LevelPrice;
	pMsg.LuckPrice = this->LuckPrice;
	pMsg.AddPrice = this->AddPrice;
	pMsg.Opt1Price = this->Opt1Price;
	pMsg.Opt2Price = this->Opt2Price;
	pMsg.Opt3Price = this->Opt3Price;
	pMsg.Opt4Price = this->Opt4Price;
	pMsg.Opt5Price = this->Opt5Price;
	pMsg.Opt6Price = this->Opt6Price;
	pMsg.MaxExlOpt = this->MaxExlOpt;
	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void CSmithy::CGCreateItem(CG_SmithyCreateItem* aRecv, int aIndex)
{
	if(!g_ExLicense.user.Smithy)
	{
		return;
	}
	
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	int iTotalExlOpt = aRecv->ItemOpt1 + aRecv->ItemOpt2 + aRecv->ItemOpt3 + aRecv->ItemOpt4 + aRecv->ItemOpt5 + aRecv->ItemOpt6;

	if(iTotalExlOpt > this->MaxExlOpt)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	unsigned short id = aRecv->Item;

	if(id > itemdata.size())
	{
		return;
	}

	SmithyDATA smItem =  this->itemdata[id];

	short iType = ITEMGET(smItem.Type,smItem.Index);

	int result = smItem.Price;
	result += aRecv->ItemLevel * this->LevelPrice;
	result += aRecv->ItemAdd * this->AddPrice;
	BYTE NewOption = 0;

	if(aRecv->ItemLuck)
	{
		result += this->LuckPrice;
	}
	if(aRecv->ItemOpt1)
	{
		result += this->Opt1Price;
		 NewOption |= 0x20;
	}
	if(aRecv->ItemOpt2)
	{
		result += this->Opt2Price;
		NewOption |= 0x10;
	}
	if(aRecv->ItemOpt3)
	{
		result += this->Opt3Price;
		NewOption |= 0x08;
	}
	if(aRecv->ItemOpt4)
	{
		result += this->Opt4Price;
		NewOption |= 0x04;
	}
	if(aRecv->ItemOpt5)
	{
		result += this->Opt5Price;
		NewOption |= 0x02;
	}
	if(aRecv->ItemOpt6)
	{
		result += this->Opt6Price;
		NewOption |= 0x01;
	}

	int iHeight = ItemAttribute[iType].Height;
	int iWidth = ItemAttribute[iType].Width;
					
	if(CheckInventoryEmptySpace(lpUser,iHeight,iWidth) == false)
	{
		MsgOutput(aIndex, "[Smithy]: Need space in the inventory (%dx%d)", iHeight, iWidth);
		return;
	}

	if(g_ExLicense.CheckUser(eExUB::Local)		  || 
		g_ExLicense.CheckUser(eExUB::SILVER1)	  || 
		g_ExLicense.CheckUser(eExUB::SILVER2)	  ||	
		g_ExLicense.CheckUser(eExUB::SILVER_Local) )
	{
		if(result > lpUser->ExCred)
		{
			MsgOutput(aIndex, "[Smithy]: Price: %d", result);
			return;
		}
		lpUser->ExCred -= result;
	}
	else
	{
		if(result > lpUser->GameShop.WCoinC)
		{
			MsgOutput(aIndex, "[Smithy]: Price: %d", result);
			return;
		}
		lpUser->GameShop.WCoinC -= result;
		gGameShop.GDSaveUserInfo(lpUser->m_Index);
	}

#if(SYSTEM_ACHIEVEMENTS)
	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		g_Achievements.BuyDonateShopItem(aIndex, result);
	}
#endif

	ExUserDataSend(aIndex);
	ItemSerialCreateSend(aIndex, 235, lpUser->X, lpUser->Y, iType, aRecv->ItemLevel, 0, 1, aRecv->ItemLuck, aRecv->ItemAdd, aIndex, NewOption, 0);
	MsgOutput(aIndex, "[Smithy]: Create Item", result);
}


#endif
