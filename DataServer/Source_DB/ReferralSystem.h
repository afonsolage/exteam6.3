#pragma once

#include "StdAfx.h"

#define CUSTOM_REFERAL_SYSTEM	1

#if(CUSTOM_REFERAL_SYSTEM)

#define REFERRAL_MAXDATA	10

struct PMSG_GDREQ_REFERRAL_INFO
{
	PBMSG_HEAD2 h;
	int aIndex;
	char Name[11];
	DWORD PageNumber;
};

struct REFERRAL_MASTER
{
	char RefferalName[11];
	int RefferalMaster;
	int RefferalUserLevel;
	int RefferalUserReset;
	int RefferalUserGrand;
};

struct PMSG_DGANS_REFERRAL_MASTER_INFO
{
	PWMSG_HEAD2 h;
	bool Result;
	int aIndex;
	int Count;
	int TotalCount;
	REFERRAL_MASTER Player[REFERRAL_MAXDATA];
};

struct PMSG_GD_REFERRAL_MASTER_UPDATE
{
	PBMSG_HEAD2 h;
	int aIndex;
	int Number;
	char Name[11];
	char RefferalName[11];
};

struct PMSG_GDANS_REFERRAL_MASTER_UPDATE
{
	PBMSG_HEAD2 h;
	int aIndex;
	int Number;
	bool Result;
};

struct PMSG_GDREQ_REFERRAL_USER_INFO
{
	PBMSG_HEAD2 h;
	int aIndex;
	char Name[11];
};

struct PMSG_DGANS_REFERRAL_USER_INFO
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool Result;
	int RefferalUser;
};

struct PMSG_GD_REFERRAL_USER_UPDATE
{
	PBMSG_HEAD2 h;
	int aIndex;
	char RefferalName[11];
};

struct PMSG_GDANS_REFERRAL_USER_UPDATE
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool Result;
};

class CReferralSystem
{
public:
		 CReferralSystem();
		 ~CReferralSystem();
	void Load();
	void Read(char* filename);
	bool Connect();
	void CreateColumn();
	void GDReqMasterInfo(PMSG_GDREQ_REFERRAL_INFO* lpMsg, int uIndex);
	void GDReqMasterUpdate(PMSG_GD_REFERRAL_MASTER_UPDATE* lpMsg, int uIndex);

	void GDReqUserInfo(PMSG_GDREQ_REFERRAL_USER_INFO* lpMsg, int uIndex);
	void GDReqUserUpdate(PMSG_GD_REFERRAL_USER_UPDATE* lpMsg, int uIndex);

	void UpdateState(char* Account);

	char szTableName[64];
	char szColumnName[64];

	CQuery m_DBQuery;
	CQuery m_MEMBQuery;
};
extern CReferralSystem g_ReferralSystem;

#endif