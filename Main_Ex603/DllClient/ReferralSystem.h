#pragma once

#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_REFERAL_SYSTEM)

#define REFERRAL_MAXDATA	10

struct PMSG_REQ_REFERRAL_MASTER_INFO
{
	PBMSG_HEAD2 h;
	DWORD PageNumber;
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

struct PMSG_REQ_REFERRAL_USER_INFO
{
	PBMSG_HEAD2 h;
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
	char ReferalName[11];
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
	char Name[11];
	int RefferalMaster;
	int UserOnline;
	int UserLevel;
	int UserReset;
	int UserGrand;
	int ReferralNeedLevel;
	int ReferralNeedReset;
	int ReferralNeedGrand;
	int MasterRewardCredit;
	int MasterRewardWCoinC;
	int MasterRewardWCoinP;
	int MasterRewardWCoinG;
	int MasterRewardBonus;
	int MasterRewardPremiumType;
	int MasterRewardPremiumTime;
};

struct REFERRAL_USER
{
	int RefferalActive;
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

class CReferralSystem
{
public:
		 CReferralSystem();
		 ~CReferralSystem();

	void Load();
	void BindImages();
	void LoadFileImage();
	void DrawMain();
	void DrawIco();
	void DrawMenu();
	void Draw();
	void Draw2();

	void ButtonIco(DWORD Event);
	void Button(DWORD Event);

	void CGReqMasterInfo();
	void GCAnsMasterInfo(PMSG_ANS_REFERRAL_MASTER_INFO* lpMsg);
	void CGReqMasterResult(int Number);
	void GCAnsMasterResult(PMSG_CGANS_REFERRAL_MASTER_REWARD* lpMsg);
	
	void CGReqUserInfo();
	void GCAnsUserInfo(PMSG_ANS_REFERRAL_USER_INFO* lpMsg);
	void CGReqUserResult();
	void GCAnsUserResult(PMSG_GCANS_REFERRAL_USER_REWARD* lpMsg);

	int m_iDraw;
	int m_iPage;
	int m_iOpen;
	int m_iMaxStage;
	int m_iReferralCount;
	int m_iReferralTotal;
	bool m_bCheckClick;
	DWORD m_dwTickCountClick;
	REFERRAL_DATA m_Data[REFERRAL_MAXDATA];
	REFERRAL_USER m_User;
};

extern CReferralSystem g_ReferralSystem;

#endif