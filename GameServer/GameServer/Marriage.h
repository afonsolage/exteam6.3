#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"

#if(CUSTOM_MARRIAGE)
// Game Server <-> Client
struct PMSG_GC_MARRIAGE_NAMES
{
	PBMSG_HEAD2 h;
	bool bResult;
	bool bUser1;
	bool bUser2;
	char szName1[11];
	char szName2[11];
	int  iCountHeart1;
	int  iCountHeart2;
	int  iNeedHeart1;
	int  iNeedHeart2;
};

struct PMSG_CG_MARRIAGE_CLOSE
{
	PBMSG_HEAD2 h;
	bool bResultClose;
};

struct PMSG_GC_MARRIAGE_WIN_CLOSE
{
	PBMSG_HEAD2 h;
};
// Game Server <-> Data Server
struct PMSG_REQ_MARRIAGE_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bClass;
	char szName[11];
};

struct PMSG_ANS_MARRIAGE_LOAD
{
	PBMSG_HEAD2 h;
	int aIndex;
	char szMarriageName[11];
};
// ----
struct PMSG_REQ_MARRIAGE_INSERT
{
	PBMSG_HEAD2 h;
	int aIndex1;
	int aIndex2;
	char szName1[11];
	char szName2[11];
};

struct PMSG_ANS_MARRIAGE_INSERT
{
	PBMSG_HEAD2 h;
	int aIndex1;
	int aIndex2;
	bool bResult;
};
// ----
struct PMSG_REQ_MARRIAGE_DELETE
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bClass;
	char szName[11];
};

struct PMSG_ANS_MARRIAGE_DELETE
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool bResult;
};

class CMarriage
{
public:
		 CMarriage();
		 ~CMarriage();

	void Init();
	void Load();
	void Read(char* filename);

	bool NpcDialog(int aIndex, int aNpcIndex);
	void GCInfoNames();
	void IndexClose(int aIndex);
	void CGClickOK(int aIndex);
	void CGWindowClose();

	void GDLoad(int aIndex);
	void DGLoad(PMSG_ANS_MARRIAGE_LOAD* aRecv);

	void GDInsert();
	void DGInsert(PMSG_ANS_MARRIAGE_INSERT* aRecv);

	void GDDelete(int aIndex);
	void DGDelete(PMSG_ANS_MARRIAGE_DELETE* aRecv);

	void AddedCharacter(int aIndex);

	void BuffAdded(int aIndex);

	bool Enable;
	int  iNpcClass;
	int  iNpcMap;
	int  iNpcX;
	int  iNpcY;

	int  iNeedHeart1;
	int  iNeedHeart2;

	int  iRewardItemType;
	int  iRewardItemIndex;
	int  iRewardItemLevel;
	int  iRewardItemOpt;
	int  iRewardItemExel;
	int  iRewardDoubleDamage;
	int  iRewardIgnoreDefence;

	int  iKickPriceWcoin;

	int  iClassIndex1;
	int  iClassIndex2;

	bool bClickOK1;
	bool bClickOK2;
};

extern CMarriage g_Marriage;

#endif