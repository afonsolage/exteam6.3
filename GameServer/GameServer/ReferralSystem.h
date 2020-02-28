#pragma once

#include "StdAfx.h"
#include "..\\include\\prodef.h"

#if(CUSTOM_REFERAL_SYSTEM)

#define REFERRAL_MAXDATA	10

// GS - DS
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
	char ReferalName[11];
};

struct PMSG_GDANS_REFERRAL_MASTER_UPDATE
{
	PBMSG_HEAD2 h;
	int aIndex;
	int Number;
	bool Result;
};

struct PMSG_GD_REFERRAL_USER_UPDATE
{
	PBMSG_HEAD2 h;
	int aIndex;
	char ReferalName[11];
};

// GS - CL
struct PMSG_REQ_REFERRAL_MASTER_INFO
{
	PBMSG_HEAD2 h;
	DWORD PageNumber;
};

struct PMSG_REQ_REFERRAL_USER_INFO
{
	PBMSG_HEAD2 h;
};

struct REFERRAL_MASTER_DATA
{
	char RefferalName[11];
	int RefferalMaster;
	int UserOnline;
	int UserLevel;
	int UserReset;
	int UserGrand;
	int UserNeedLevel;
	int UserNeedReset;
	int UserNeedGrand;
	int MasterRewardCredit;
	int MasterRewardWCoinC;
	int MasterRewardWCoinP;
	int MasterRewardWcoinG;
	int MasterRewardBonus;
	int MasterRewardPremiumType;
	int MasterRewardPremiumTime;
};

struct PMSG_ANS_REFERRAL_MASTER_INFO
{
	PWMSG_HEAD2 h;
	int RefferalMaxStage;
	int ReferralCount;
	int ReferralTotal;
	REFERRAL_MASTER_DATA Data[REFERRAL_MAXDATA];
};

struct PMSG_CGREQ_REFERRAL_MASTER_REWARD
{
	PBMSG_HEAD2 h;
	int ReferralNumber;
	char ReferalName[11];
};

struct PMSG_CGANS_REFERRAL_MASTER_REWARD
{
	PBMSG_HEAD2 h;
	int ReferralNumber;
	int UserNeedLevel;
	int UserNeedReset;
	int UserNeedGrand;
	int MasterRewardCredit;
	int MasterRewardWCoinC;
	int MasterRewardWCoinP;
	int MasterRewardWcoinG;
	int MasterRewardBonus;
	int MasterRewardPremiumType;
	int MasterRewardPremiumTime;
};

// ----

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

struct REFERRAL_USER_DATA
{
	int RefferalUser;
	int ReferralNeedLevel;
	int ReferralNeedReset;
	int ReferralNeedGrand;
	int ReferralRewardCredit;
	int ReferralRewardWCoinC;
	int ReferralRewardWCoinP;
	int ReferralRewardWcoinG;
	int ReferralRewardBonus;
	int ReferralRewardPremiumType;
	int ReferralRewardPremiumTime;
};

struct PMSG_ANS_REFERRAL_USER_INFO
{
	PBMSG_HEAD2 h;
	int RefferalMaxStage;
	REFERRAL_USER_DATA User;
};

struct PMSG_CGREQ_REFERRAL_USER_REWARD
{
	PBMSG_HEAD2 h;
};

struct PMSG_GDANS_REFERRAL_USER_UPDATE
{
	PBMSG_HEAD2 h;
	int aIndex;
	bool Result;
};

struct PMSG_GCANS_REFERRAL_USER_REWARD
{
	PBMSG_HEAD2 h;
	int UserNeedLevel;
	int UserNeedReset;
	int UserNeedGrand;
	int UserRewardCredit;
	int UserRewardWCoinC;
	int UserRewardWCoinP;
	int UserRewardWcoinG;
	int UserRewardBonus;
	int UserRewardPremiumType;
	int UserRewardPremiumTime;
};

struct REFERRAL_DATA
{
	int UserNeedLevel;
	int UserNeedReset;
	int UserNeedGrand;
	int MasterRewardCredit;
	int MasterRewardWCoinC;
	int MasterRewardWCoinP;
	int MasterRewardWCoinG;
	int MasterRewardBonus;
	int MasterRewardPremiumType;
	int MasterRewardPremiumTime;
	int UserRewardCredit;
	int UserRewardWCoinC;
	int UserRewardWCoinP;
	int UserRewardWCoinG;
	int UserRewardBonus;
	int UserRewardPremiumType;
	int UserRewardPremiumTime;
};

class CReferralSystem
{
public:
		 CReferralSystem();
		 ~CReferralSystem();

	void Load();
	void Read(char* FileName);

	void CGReqMasterInfo(PMSG_REQ_REFERRAL_MASTER_INFO* lpMsg, int aIndex);
	void GDReqMasterInfo(int aIndex, int Page);
	void DGAnsMasterInfo(PMSG_DGANS_REFERRAL_MASTER_INFO* lpMsg);
	void CGMasterResult(PMSG_CGREQ_REFERRAL_MASTER_REWARD* lpMsg, int aIndex);
	void GDReqMasterUpdate(int aIndex, char* Name, int Num);
	void DGAnsMasterUpdate(PMSG_GDANS_REFERRAL_MASTER_UPDATE* lpMsg);
	
	void CGReqUserInfo(PMSG_REQ_REFERRAL_USER_INFO* lpMsg, int aIndex);
	void GDReqUserInfo(int aIndex);
	void DGAnsUserInfo(PMSG_DGANS_REFERRAL_USER_INFO* lpMsg);
	void CGUserResult(PMSG_CGREQ_REFERRAL_USER_REWARD* lpMsg, int aIndex);
	void GDReqUserUpdate(int aIndex);
	void DGAnsUserUpdate(PMSG_GDANS_REFERRAL_USER_UPDATE* lpMsg);

	bool m_bActive;

	std::vector<REFERRAL_DATA> m_Data;
};

extern CReferralSystem g_ReferralSystem;

#endif