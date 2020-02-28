#ifndef GENSSYSTEM_H
#define GENSSYSTEM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
g_MLBattleZoneAddExp - no work опыт на батл картах
При разработке 6 сезон дописать дописать генс систему в скиллы монка
*/

// -------------------------------------------------------------------------

enum INFLUENCE_TYPE
{
	LEAVED_INFLUENCE  = -1, 
	NONE_INFLUENCE    =  0,
	VANERT_INFLUENCE  =  1, 
	DUPRIAN_INFLUENCE =  2,
};
// -------------------------------------------------------------------------

enum USER_BATTLE_ZONE 
{	
	BATTLE_ZONE_BLOCK   = 0,
	BATTLE_ZONE_UNBLOCK = 1
};
// -------------------------------------------------------------------------

struct PMSG_REQ_REG_GENS_MEMBER
{
	PBMSG_HEAD2 h; //0
	BYTE bResult;  //4
}; 
// -------------------------------------------------------------------------

struct PMSG_REQ_SEGEDE_GENS_MEMBER
{
	PBMSG_HEAD h; //0
	BYTE bResult; //3
};
// -------------------------------------------------------------------------

struct PMSG_GENS_REWARD_CODE
{
	PBMSG_HEAD2 h; //0
	BYTE bReward;  //4
};
// -------------------------------------------------------------------------
struct PMSG_REQ_GENS_INFO
{

};
// -------------------------------------------------------------------------

struct PMSG_ANS_GENS_INFO_EXDB
{
	PBMSG_HEAD2 h;
	BYTE bInfluence;
	WORD wIndexH;
	WORD wIndexL;
	int iContributePoint;
	int iGensClass;
	int iGensRanking;
};
// -------------------------------------------------------------------------

struct PMSG_ANS_REG_GENS_MEBMER 
{
	PBMSG_HEAD2 h;   //0
	BYTE bResult;    //4  
	BYTE iInfluence; //5
};
// -------------------------------------------------------------------------

struct PMSG_ANS_SECEDE_GENS_MEMBER_EXDB 
{
	PBMSG_HEAD2 h; //0
	BYTE bResult;  //4
	BYTE bIndexH;  //5
	BYTE bIndexL;  //6
};
// -------------------------------------------------------------------------

struct PMSG_ANS_ABUSING_INFO //9A (154) 
{
	PBMSG_HEAD h; //2
	BYTE bResult; //3
 char Name[0x0A]; //13
	char szCharNames[100]; //113
	int iKillUserCount; //114
	BYTE bIndexH; //154
	BYTE bIndexL; //155
	int KillCount[10]; //166
	//i150
	//i154
	//b154
	//b155
};
// -------------------------------------------------------------------------

struct PMSG_ANS_GENS_REWARD_EXDB
{
	PBMSG_HEAD h;
	BYTE b3;
	BYTE bResult; //4
	BYTE b5;
	BYTE b6;
	BYTE b7;
	int iGensClass; //8
	BYTE bIndexH; //12
	BYTE bIndexL; //13
};
// -------------------------------------------------------------------------

struct PMSG_ANS_GENS_MEMBER_COUNT_EXDB //0xA (10)
{
	PBMSG_HEAD2 h;
	int iVanertMemberCount;
	int iDuprianMemberCount;
};
// -------------------------------------------------------------------------

struct PMSG_ANS_GENS_REWARD_DAY_CHECK_EXDB
{
	PBMSG_HEAD h;
	BYTE bResult;
	BYTE bIndexH;
	BYTE bIndexL;
	int iRewardDay;
};
// -------------------------------------------------------------------------

struct PMSG_REQ_REG_GENS_MEMBER_EXDB //0x20 (32)
{
	PBMSG_HEAD2 h; 
	BYTE bResult;
	char Name[0x0A];
	BYTE bMessage;
	BYTE bInfluence;
	WORD wNumberH;
	WORD wNumberL;
	BYTE bIndexH;
	BYTE bIndexL;
};
// -------------------------------------------------------------------------

struct PMSG_ANS_REG_GENS_MEMBER_EXDB
{
	PBMSG_HEAD2 h;   //0 
	BYTE bResult;    //4
	BYTE bInfluence; //5
	BYTE bIndexH;    //6
	BYTE bIndexL;    //7
};
// -------------------------------------------------------------------------

struct PMSG_REQ_SECEDE_GENS_MEMBER_EXDB //0x16 (22)
{
	PBMSG_HEAD2 h;
	char Name[10];
	BYTE bResult;
	WORD wNumberH;
	WORD wNumberL;
	BYTE bIndexH;
	BYTE bIndexL;
};
// -------------------------------------------------------------------------

struct PMSG_REQ_ABUSING_INFO //0x10 (16)
{
	PBMSG_HEAD2 h;
	char Name[0x0A];
	BYTE bResult;
	BYTE bIndexH;
	BYTE bIndexL;
};
// -------------------------------------------------------------------------

struct PMSG_REQ_SAVE_CONTRIBUTE_POINT_EXDB //0x1A (24)
{
	PBMSG_HEAD2 h;
	//PBMSG_HEAD h;
	//char Name[0x0D];
	int Index;
	char Name[10];
	BYTE Influence;
	int iContributePoint;
	int iGensClass;
};
// -------------------------------------------------------------------------

struct PMSG_REQ_SAVE_ABUSING_KILLUSER_EXDB //0xB0 (176)
{
	PBMSG_HEAD h; //
	char AccountID[0x0D];
	BYTE bResult;
	char Name[0x0A];
	char KillName[100]; 
	int KillCount[10]; 
	//i150
	//i154
	//b154
	//b155
};
// -------------------------------------------------------------------------

struct GENS_RANKING
{
	PBMSG_HEAD h;
	BYTE bRanking;
};
// -------------------------------------------------------------------------

struct PMSG_GENS_MEMBER_VIEWPORT_INFO // 0x10
{
	BYTE btInfluence;     // +0x0(0x1)
	BYTE NumberH;         // +0x1(0x1)
	BYTE NumberL;         // +0x2(0x1)
	int iGensRanking;     // +0x4(0x4)
	int iGensClass;       // +0x8(0x4)
	int iContributePoint; // +0xc(0x4)
	// ----
}; extern PMSG_GENS_MEMBER_VIEWPORT_INFO pGensMsg;
// -------------------------------------------------------------------------

struct PMSG_SEND_GENS_MEMBER_VIEWPORT // 0x6
{
	struct PWMSG_HEAD2 h; // +0x0(0x5)
	BYTE Count;           // +0x5(0x1)
	// ----
}; extern PMSG_SEND_GENS_MEMBER_VIEWPORT pGensCount;
// -------------------------------------------------------------------------

struct PMSG_SEND_GENS_INFO //0x16 (20)
{
	PBMSG_HEAD2 h; 
	BYTE bInfluence;
	int iGensRanking;
	int iGensClass;
	int iContributePoint;
	int iNextContributePoint;
};
// -------------------------------------------------------------------------

struct PMSG_REQ_GENS_REWARD_CHECK_EXDB //0x18 (24)
{
	PBMSG_HEAD h;
	char Name[0x0D];
	BYTE bResult;
	WORD wIndexH;
	WORD wIndexL;
	int iInfluence;
};
// -------------------------------------------------------------------------

struct PMSG_REQ_GENS_REWARD_COMPLETE_EXDB //0x14 (20)
{
	PBMSG_HEAD h;
	BYTE bResult;
	char Name[0x0B];
	WORD wIndexH;
	WORD wIndexL;
};
// -------------------------------------------------------------------------

struct PMSG_SEND_GENS_REWARD //0x8 (8)
{
	PBMSG_HEAD h;
	BYTE bResult;
	BYTE bItemType; 
};
// -------------------------------------------------------------------------

struct PMSG_REQ_GENS_MEMBER_COUNT //0x14 (20)
{
	PBMSG_HEAD h;
	BYTE bResult;
	char Name[0x0D];
	WORD wIndexH;
	WORD wIndexL;
};
// -------------------------------------------------------------------------

struct PMSG_SET_GENS_REWARD_DAY_EXDB
{
	PBMSG_HEAD h;
	BYTE bRewardDay;
};
// -------------------------------------------------------------------------

struct PMSG_REQ_GENS_REWARD_DAY
{
	PBMSG_HEAD h;
	WORD bRewardDay;
	BYTE bIndexH, bIndexL;
};
// -------------------------------------------------------------------------

struct PMSG_GENS_REWARD_REQ
{
	PBMSG_HEAD2 h;
	// ----
	char		Name[11];
	int			aIndex;
};
// -----------------------------------------------------------------

struct PMSG_GENS_REWARD_ANS 
{
	PBMSG_HEAD2 h;
	// ----
	BYTE		Result;
	int			aIndex;
};
// -----------------------------------------------------------------

struct PMSG_GENS_REWARD_SET
{
	PBMSG_HEAD2 h;
	// ----
	char		Name[11];
};
// -----------------------------------------------------------------

#define MAX_BATTLE_ZONE		11
#define MAX_REWARD_TABLE	8

struct RewardTable
{
	BYTE	Rank;
	int		ItemID;
	int		ItemIndex;
	BYTE	ItemLevel;
	BYTE	ItemCount;
};

enum eGensClass
{
	Private = 0,
};

const int MAX_VIEWPORT_INFO = 0x7FC + 1;



extern BOOL g_GensSystemIsEnabled;
extern int g_GensAbusingResetTime;
extern int g_GensInitialContributePoint;
extern int g_BattleZoneAddExp;
extern int g_GensMasterLevelBattleZoneAddExp;
extern int g_PkPenaltyAddNeedZenMapMove;



//--------------------------------------------------

void CGReqRegGensMember(PMSG_REQ_REG_GENS_MEMBER *lpMsg, int iIndex);
void CGReqSecedeGensMember(PMSG_REQ_SEGEDE_GENS_MEMBER *lpMsg, int iIndex);
void CGReqGensReward(PMSG_GENS_REWARD_CODE *lpMsg, int iIndex);
void CGReqGensMemberInfo(PMSG_REQ_GENS_INFO *lpMsg, int iIndex);

//--------------------------------------------------



//--------------------------------------------------

void DGAnsGensInfo(PMSG_ANS_GENS_INFO_EXDB *lpMsg);
void DGAnsRegGensMember(PMSG_ANS_REG_GENS_MEMBER_EXDB *lpMsg);
void DGAnsSecedeGensMember(PMSG_ANS_SECEDE_GENS_MEMBER_EXDB *lpMsg);
void DGAnsAbusingInfo(PMSG_ANS_ABUSING_INFO *lpMsg);
void DGAnsGensReward(PMSG_ANS_GENS_REWARD_EXDB *lpMsg);
void DGAnsGensMemberCount(PMSG_ANS_GENS_MEMBER_COUNT_EXDB *lpMsg);
void DGAnsGensRewardDayCheck(PMSG_ANS_GENS_REWARD_DAY_CHECK_EXDB *lpMsg);
//--------------------------------------------------



//--------------------------------------------------

class GensSystem
{
public:
	GensSystem(void);
	virtual ~GensSystem(void);

	int GDReqAbusingInfo(LPOBJ lpObj); 
	int ReqExDBGensInfo(LPOBJ lpObj);
	void ReqRegGensMember(LPOBJ lpObj, unsigned char btInfluence);
	int AnsRegGensMember(int iObjIndex, unsigned char btResult);
	bool IsInfluenceNPC(LPOBJ lpObj);
	int ReqSecedeGensMember(LPOBJ lpObj);
	int SendGensInfo(LPOBJ lpObj);
	int AnsSecedeGensMember(int iObjIndex, BYTE btResult);
	int SendPkPenaltyMapMove(LPOBJ lpObj);
	int GDReqSaveContributePoint(LPOBJ lpObj);
	int DBSaveAbusingKillUserName(LPOBJ lpObj);
	void BattleZoneChatMsgSend(LPOBJ obj, LPBYTE Msg, int size);
	signed int IsMoveMapBattleZone(int iMapIndex);
	void GensViewportListProtocol(LPOBJ lpObj);
	signed int IsMapBattleZone(int iMapIndex);
	void SetGensInfluence(LPOBJ lpObj, int iInfluence);
	signed int IsPkEnable(LPOBJ lpObj, LPOBJ lpTargetObj);
	signed int GetGensInfluence(LPOBJ lpObj);
	char *GetGensInfluenceName(LPOBJ lpObj);
	bool IsRegGensInfluence(LPOBJ lpObj);
	int SetUserBattleZoneEnable(LPOBJ lpObj, int bBattleZoneEnable);
	int IsUserBattleZoneEnable(LPOBJ lpObj);
	int SetContributePoint(LPOBJ lpObj, int iContributePoint);
	int AddContributePoint(LPOBJ lpObj, int iContributePoint);
	int SubContributePoint(LPOBJ lpObj, int iContributePoint);
	int GetContributePoint(LPOBJ lpObj);
	signed int PkPenaltyAddNeedZenMapMove(LPOBJ lpObj);
	void PkPenaltyDropInvenItem(LPOBJ lpObj);
	void PkPenaltyDropZen(LPOBJ lpObj);
	int SendPKPenaltyDebuff(LPOBJ lpObj);
	void CalcContributePoint(LPOBJ lpObj, LPOBJ lpTargetObj);
	signed int ChkKillUserName(LPOBJ lpObj, char *szCharName);
	signed int AbusingPenalty(LPOBJ lpObj, int iKillUserIndex);
	int InsertKillUserName(LPOBJ lpObj, char *szCharName);
	void MoveInBattleZonePartySplit(LPOBJ lpObj);
	void AbusingInfoReset(LPOBJ lpObj);
	void CalGensClass(LPOBJ lpObj);
	int SetGensRanking(LPOBJ lpObj, int iGensRanking);
	int SetGensClass(LPOBJ lpObj, int iGensClass);
	int GetGensClass(LPOBJ lpObj);
	int GetNextContributePoint(LPOBJ lpObj);
	int SetGensMemberCount(int iInfluence, int iMemberCount);
	signed int GetGensMemberCount(int iInfluence);
	int ReqExDBGensRewardCheck(LPOBJ lpObj, int iInfluence);
	int ReqExDBGensRewardComplete(LPOBJ lpObj);
	int SendGensReward(LPOBJ lpObj, unsigned char btResult);
	signed int SendGensRewardItem(LPOBJ lpObj, int iGensClass);
	bool GensRewardInventoryCheck(LPOBJ lpObj, int iItemCount);
	int ReqExDBGensMemberCount(LPOBJ lpObj);
	int ReqExDBSetGensRewardDay(void);
	int ReqExDBSetGensRanking(void);
	int LoadData(char *lpszFileName);
	int ReqGensRewardDay(LPOBJ lpObj);
	// ----
	void GDRewardReq(LPOBJ lpObj);
	void DGRewardAns(PMSG_GENS_REWARD_ANS * aRecv);
	void GDRankingUpdate();
	// ----
	BYTE		BattleZoneList[MAX_BATTLE_ZONE];
	BYTE		BattleMapList[MAX_BATTLE_ZONE];
	RewardTable RewardTableList[MAX_REWARD_TABLE+1];
	// ----
	bool	GuildCreateReqGens;
	bool	CheckGuildEnter;
	bool	CheckPartyEnter;
	bool	CheckAllianceEnter;
	bool	AllowPK;
	// ----
	int		ChatPrice;
	// ----
	BOOL b_PkPenaltyDropZen;
	BOOL b_PkPenaltyDropInvenItem;

	int iVanertMemberCount;
	int iDuprianMemberCount;

	int iIndex;

protected:
};
extern GensSystem gGensSystem;

//--------------------------------------------------

#endif