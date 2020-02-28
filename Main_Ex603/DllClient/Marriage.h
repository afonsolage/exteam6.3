#pragma once

#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_MARRIAGE)

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

struct PMSG_CG_MARRIAGE_OK
{
	PBMSG_HEAD2 h;
	bool bClickOK;
};

class CMarriage
{
public:
		 CMarriage();
		 ~CMarriage();

	void Init();
	void Load();
	void LoadImages();
	void BindImages();
	void Draw();
	void Button(DWORD Event);

	void GCInfoNames(PMSG_GC_MARRIAGE_NAMES* aRecv);
	void GCWindowClose();

	bool Result;
	bool bUser1;
	bool bUser2;
	char szName1[11];
	char szName2[11];
	int  iCountHeart1;
	int  iCountHeart2;
	int  iNeedHeart1;
	int  iNeedHeart2;
	bool bDrawOK;
};
extern CMarriage g_Marriage;

#endif