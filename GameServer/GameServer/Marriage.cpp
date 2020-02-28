#include "StdAfx.h"
#include "Marriage.h"
#include "user.h"
#include "GameMain.h"
#include "Functions.h"
#include "DBSockMng.h"
#include "Message.h"
#include "DSProtocol.h"
#include "ExLicense.h"
#include "ExUser.h"
#include "BuffManager.h"

#if(CUSTOM_MARRIAGE)

CMarriage g_Marriage;

CMarriage::CMarriage()
{
	this->Init();
}

CMarriage::~CMarriage()
{
}

void CMarriage::Init()
{
	this->Enable = false;
	this->iNpcClass = 0;
	this->iNpcMap = 0;
	this->iNpcX = 0;
	this->iNpcY = 0;
	this->iNeedHeart1 = 0;
	this->iNeedHeart2 = 0;
	this->iRewardItemType = 0;
	this->iRewardItemIndex = 0;
	this->iRewardItemLevel = 0;
	this->iRewardItemOpt = 0;
	this->iRewardItemExel = 0;
	this->iRewardDoubleDamage = 0;
	this->iRewardIgnoreDefence = 0;
	this->iKickPriceWcoin = 0;
	this->iClassIndex1 = -1;
	this->iClassIndex2 = -1;
	this->bClickOK1 = false;
	this->bClickOK2 = false;
}

void CMarriage::Load()
{
	this->Init();

	if(!g_ExLicense.user.Marriage)
	{
		return;
	}

	this->Read(gDirPath.GetNewPath("ExData\\Marriage.ini"));
}

void CMarriage::Read(char* filename)
{
	this->Enable = GetPrivateProfileInt("Common", "Enable", 0, filename);
	this->iNpcClass = GetPrivateProfileInt("Common", "NpcClass", 0, filename);
	this->iNpcMap = GetPrivateProfileInt("Common", "NpcMap", 0, filename);
	this->iNpcX = GetPrivateProfileInt("Common", "NpcX", 0, filename);
	this->iNpcY = GetPrivateProfileInt("Common", "NpcY", 0, filename);
	this->iNeedHeart1 = GetPrivateProfileInt("Common", "NeedHeart1", 0, filename);
	this->iNeedHeart2 = GetPrivateProfileInt("Common", "NeedHeart2", 0, filename);
	this->iRewardItemType = GetPrivateProfileInt("Common", "RewardItemType", 0, filename);
	this->iRewardItemIndex = GetPrivateProfileInt("Common", "RewardItemIndex", 0, filename);
	this->iRewardItemLevel = GetPrivateProfileInt("Common", "RewardItemLevel", 0, filename);
	this->iRewardItemOpt = GetPrivateProfileInt("Common", "RewardItemOpt", 0, filename);
	this->iRewardItemExel = GetPrivateProfileInt("Common", "RewardItemExel", 0, filename);
	this->iRewardDoubleDamage = GetPrivateProfileInt("Common", "RewardDoubleDamage", 0, filename);
	this->iRewardIgnoreDefence = GetPrivateProfileInt("Common", "RewardIgnoreDefence", 0, filename);
	this->iKickPriceWcoin = GetPrivateProfileInt("Common", "KickPriceWcoin", 0, filename);
}

bool CMarriage::NpcDialog(int aIndex, int aNpcIndex)
{
	if(!this->Enable)
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if( lpNpc->Class == this->iNpcClass && 
		lpNpc->MapNumber == this->iNpcMap && 
		lpNpc->X == this->iNpcX && 
		lpNpc->Y == this->iNpcY )
	{

		if(lpUser->bMarriage)
		{
			MsgOutput(aIndex, "[Marriage] Married");
			return true;
		}

		if(lpUser->Class == CLASS_KNIGHT || lpUser->Class == CLASS_WIZARD || lpUser->Class == CLASS_MAGUMSA || lpUser->Class == CLASS_DARKLORD || lpUser->Class == CLASS_MONK)
		{
			if(this->iClassIndex1 != -1)
			{
				MsgOutput(aIndex, "[Marriage] class1 busy");
				return true;
			}
			this->iClassIndex1 = aIndex;
		}
		else
		{
			if(this->iClassIndex2 != -1)
			{
				MsgOutput(aIndex, "[Marriage] class2 busy");
				return true;
			}
			this->iClassIndex2 = aIndex;
		}

		this->GCInfoNames();

		return true;
	}

	return false;
}

void CMarriage::GCInfoNames()
{
	if(!this->Enable)
	{
		return;
	}

	PMSG_GC_MARRIAGE_NAMES pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x31, sizeof(pMsg));

	pMsg.bResult = true;
	pMsg.bUser1 = false;
	pMsg.bUser2 = false;

	memset(pMsg.szName1, 0, sizeof(pMsg.szName1));
	memset(pMsg.szName2, 0, sizeof(pMsg.szName2));

	pMsg.iCountHeart1 = 0;
	pMsg.iCountHeart2 = 0;

	pMsg.iNeedHeart1 = this->iNeedHeart1;
	pMsg.iNeedHeart2 = this->iNeedHeart2;

	if(OBJMAX_RANGE(this->iClassIndex1))
	{
		pMsg.bUser1 = true;
		pMsg.szName1[10] = 0;
		memcpy(pMsg.szName1, gObj[this->iClassIndex1].Name, sizeof(pMsg.szName1)-1);

		pMsg.iCountHeart1 = gObjGetItemCountInInventory(this->iClassIndex1, ITEMGET(14,12), 1);

		if(pMsg.iNeedHeart1 > pMsg.iCountHeart1)
		{
			pMsg.bResult = false;
		}
	}
	else
	{
		pMsg.bResult = false;
	}

	if(OBJMAX_RANGE(this->iClassIndex2))
	{
		pMsg.bUser2 = true;
		pMsg.szName2[10] = 0;
		memcpy(pMsg.szName2, gObj[this->iClassIndex2].Name, sizeof(pMsg.szName2)-1);

		pMsg.iCountHeart2 = gObjGetItemCountInInventory(this->iClassIndex2, ITEMGET(14,12), 1);

		if(pMsg.iNeedHeart2 > pMsg.iCountHeart2)
		{
			pMsg.bResult = false;
		}
	}	
	else
	{
		pMsg.bResult = false;
	}

	if(this->iClassIndex1 != -1)
	{
		DataSend(this->iClassIndex1, (LPBYTE)&pMsg, sizeof(pMsg));
	}

	if(this->iClassIndex2 != -1)
	{
		DataSend(this->iClassIndex2, (LPBYTE)&pMsg, sizeof(pMsg));
	}	
}

void CMarriage::IndexClose(int aIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if(aIndex == this->iClassIndex1)
	{
		this->iClassIndex1 = -1;
		this->bClickOK1 = false;
	}

	if(aIndex == this->iClassIndex2)
	{
		this->iClassIndex2 = -1;
		this->bClickOK2 = false;
	}

	this->GCInfoNames();
}

void CMarriage::CGClickOK(int aIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	if (gObj[aIndex].Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(aIndex == this->iClassIndex1)
	{
		this->bClickOK1 = true;
	}

	if(aIndex == this->iClassIndex2)
	{
		this->bClickOK2 = true;
	}

	if(OBJMAX_RANGE(this->iClassIndex1) && OBJMAX_RANGE(this->iClassIndex2))
	{
		if(this->bClickOK1 == true && this->bClickOK2 == true)
		{
			this->GDInsert();
			this->CGWindowClose();
		}
	}
}

void CMarriage::CGWindowClose()
{
	PMSG_GC_MARRIAGE_WIN_CLOSE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x32, sizeof(pMsg));
	DataSend(this->iClassIndex1, (LPBYTE)&pMsg, sizeof(pMsg));
	DataSend(this->iClassIndex2, (LPBYTE)&pMsg, sizeof(pMsg));

	this->iClassIndex1 = -1;
	this->bClickOK1 = false;
	this->iClassIndex2 = -1;
	this->bClickOK2 = false;
}

void CMarriage::GDLoad(int aIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	PMSG_REQ_MARRIAGE_LOAD pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x00, sizeof(pMsg));

	pMsg.aIndex = aIndex;

	if(lpUser->Class == CLASS_KNIGHT || lpUser->Class == CLASS_WIZARD || lpUser->Class == CLASS_MAGUMSA || lpUser->Class == CLASS_DARKLORD || lpUser->Class == CLASS_MONK)
	{
		pMsg.bClass = 0;
	}
	else
	{
		pMsg.bClass = 1;
	}

	pMsg.szName[10] = 0;
	memcpy(pMsg.szName, lpUser->Name, sizeof(pMsg.szName)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CMarriage::DGLoad(PMSG_ANS_MARRIAGE_LOAD* aRecv)
{
	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->bMarriage = true;

	lpUser->MarriageName[10] = 0;
	memcpy(lpUser->MarriageName, aRecv->szMarriageName, sizeof(lpUser->MarriageName)-1);

	bool bMarriageOnline = false;

	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ sObj = &gObj[n];

		if(sObj->Connected < PLAYER_PLAYING || n == aIndex) 
		{
			continue;
		}

		if(sObj->Name[0] == lpUser->MarriageName[0])
		{
			if(strcmp(sObj->Name, lpUser->MarriageName) == 0)
			{
				bMarriageOnline = true;
				MessageChat(n, "~[MARRIAGE] Player: %s Connected!", lpUser->Name);
				break;
			}
		}				
	}

	if(bMarriageOnline)
	{
		MessageChat(aIndex, "~[MARRIAGE] Player: %s Online", lpUser->MarriageName);
	}
	else
	{
		MessageChat(aIndex, "~[MARRIAGE] Player: %s Offline", lpUser->MarriageName);
	}
}

void CMarriage::GDInsert()
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(this->iClassIndex1) || !OBJMAX_RANGE(this->iClassIndex2))
	{
		return;
	}

	LPOBJ lpUser1 = &gObj[this->iClassIndex1];
	LPOBJ lpUser2 = &gObj[this->iClassIndex2];

	PMSG_REQ_MARRIAGE_INSERT pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x01, sizeof(pMsg));
	pMsg.aIndex1 = this->iClassIndex1;
	pMsg.aIndex2 = this->iClassIndex2;

	pMsg.szName1[10] = 0;
	memcpy(pMsg.szName1, lpUser1->Name, sizeof(pMsg.szName1)-1);

	pMsg.szName2[10] = 0;
	memcpy(pMsg.szName2, lpUser2->Name, sizeof(pMsg.szName2)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CMarriage::DGInsert(PMSG_ANS_MARRIAGE_INSERT* aRecv)
{
	if(!aRecv->bResult)
	{
		return;
	}

	int aIndex1 = aRecv->aIndex1;
	int aIndex2 = aRecv->aIndex2;

	if(!OBJMAX_RANGE(aIndex1) || !OBJMAX_RANGE(aIndex2))
	{
		return;
	}

	LPOBJ lpUser1 = &gObj[aIndex1];
	LPOBJ lpUser2 = &gObj[aIndex2];

	if(lpUser1->Connected < PLAYER_PLAYING || lpUser2->Connected < PLAYER_PLAYING)
	{
		return;
	}

	gObjDeleteItemsCount(aIndex1, ITEMGET(14,12), 1, this->iNeedHeart1);
	gObjDeleteItemsCount(aIndex2, ITEMGET(14,12), 1, this->iNeedHeart2);

	MessaageAllGlobal("Congratulations, %s and %s are now married", lpUser1->Name, lpUser2->Name);
	
	ExFireCracker(aIndex1, lpUser1->X, lpUser1->Y);
	ExFireCracker(aIndex1, lpUser2->X, lpUser2->Y);
	ExFireCracker(aIndex2, lpUser1->X, lpUser1->Y);
	ExFireCracker(aIndex2, lpUser2->X, lpUser2->Y);

	lpUser1->bMarriage = true;
	lpUser2->bMarriage = true;

	int iItemType = ITEMGET(this->iRewardItemType, this->iRewardItemIndex);
	int iItemLevel = this->iRewardItemLevel;
	int iItemOpt = this->iRewardItemOpt;
	int iItemExl = GenExcOpt(this->iRewardItemExel);

	ItemSerialCreateSend(aIndex1,235,lpUser1->X,lpUser2->Y,iItemType,iItemLevel,0,0,0,iItemOpt,aIndex1,iItemExl,0);
	ItemSerialCreateSend(aIndex2,235,lpUser1->X,lpUser2->Y,iItemType,iItemLevel,0,0,0,iItemOpt,aIndex1,iItemExl,0);
}

void CMarriage::GDDelete(int aIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if(this->iKickPriceWcoin > lpUser->GameShop.WCoinC)
	{
		MessageChat(aIndex, "~[MARRIAGE] Kick Price: %d WCoin", this->iKickPriceWcoin);
		return;
	}

	lpUser->GameShop.WCoinC -= this->iKickPriceWcoin;
	gGameShop.GDSaveUserInfo(aIndex);
	ExUserDataSend(aIndex);

	PMSG_REQ_MARRIAGE_DELETE pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xEB, 0x02, sizeof(pMsg));

	pMsg.aIndex = aIndex;

	if(lpUser->Class == CLASS_KNIGHT || lpUser->Class == CLASS_WIZARD || lpUser->Class == CLASS_MAGUMSA || lpUser->Class == CLASS_DARKLORD || lpUser->Class == CLASS_MONK)
	{
		pMsg.bClass = 0;
	}
	else
	{
		pMsg.bClass = 1;
	}

	pMsg.szName[10] = 0;
	memcpy(pMsg.szName, lpUser->Name, sizeof(pMsg.szName)-1);

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);
}

void CMarriage::DGDelete(PMSG_ANS_MARRIAGE_DELETE* aRecv)
{
	if(!aRecv->bResult)
	{
		return;
	}

	int aIndex = aRecv->aIndex;

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->bMarriage = false;

	MessageChat(aIndex, "~[MARRIAGE] Kick Players");

	for(int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
	{
		LPOBJ sObj = &gObj[n];

		if(sObj->Connected < PLAYER_PLAYING || n == aIndex) 
		{
			continue;
		}

		if(sObj->Name[0] == lpUser->MarriageName[0])
		{
			if(strcmp(sObj->Name, lpUser->MarriageName) == 0)
			{
				sObj->bMarriage = false;
				MessageChat(n, "~[MARRIAGE] Kick Players!", lpUser->Name);
				break;
			}
		}				
	}
}

void CMarriage::AddedCharacter(int aIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(!lpUser->bMarriage)
	{
		return;
	}

	lpUser->SetOpIgnoreDefense += this->iRewardIgnoreDefence;
	lpUser->SetOpDoubleDamage += this->iRewardDoubleDamage;

	if(lpUser->SetOpIgnoreDefense > 90)
	{
		lpUser->SetOpIgnoreDefense = 90;
	}

	if(lpUser->SetOpDoubleDamage > 90)
	{
		lpUser->SetOpDoubleDamage = 90;
	}
}

void CMarriage::BuffAdded(int aIndex)
{
	if(!this->Enable)
	{
		return;
	}

	if(!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::GredyLocal) || g_ExLicense.CheckUser(eExUB::Gredy2))
	{
		if(!lpUser->bMarriage)
		{
			if(gObjSearchActiveEffect(lpUser,AT_MARRI_BUFF2) == TRUE)
			{
				gObjRemoveBuffEffect(lpUser,AT_MARRI_BUFF2);
			}
			return;
		}

		if(gObjSearchActiveEffect(lpUser,AT_MARRI_BUFF2) == FALSE)
		{
			gObjApplyBuffEffectDuration(lpUser,AT_MARRI_BUFF2,0,0,0,0,600);
		}
	}
	else
	{
		if(!lpUser->bMarriage)
		{
			if(gObjSearchActiveEffect(lpUser,AT_MARRI_BUFF) == TRUE)
			{
				gObjRemoveBuffEffect(lpUser,AT_MARRI_BUFF);
			}
			return;
		}

		if(gObjSearchActiveEffect(lpUser,AT_MARRI_BUFF) == FALSE)
		{
			gObjApplyBuffEffectDuration(lpUser,AT_MARRI_BUFF,0,0,0,0,600);
		}
	}
}

#endif