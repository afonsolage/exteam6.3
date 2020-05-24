#pragma once

#include "StdAfx.h"
#include "CQuery.h"
#include "Server.h"

using namespace std;

#if(ENABLE_EXDATASERVER)
#define EXDS_INISECTION		"ExDataServer"
#endif
#define MAX_MEMBER_GUILD	80

struct EXDS_INFO
{
	WORD TCPPort;
	char dbDSN[64];
	char mydbDSN[64];
};

extern EXDS_INFO g_ExDSInfo;
extern CQuery g_ExDataServerDB;

struct SDHP_USERCLOSE
{
	PBMSG_HEAD h;	//	
	char CharName[10];	//	3
	char GuildName[8];	//	D
	unsigned char Type;	//	15
};

struct SDHP_GUILDCREATE
{
	PBMSG_HEAD h;
	char GuildName[9];	// 3
	char Master[11];	// C
	BYTE Mark[32];	// 17
	BYTE NumberH;	// 37
	BYTE NumberL;	// 38
	BYTE btGuildType;	// 39
};

struct SDHP_GUILDCREATE_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	unsigned char Flag;	//	4
	unsigned long GuildNumber;	//	8
	unsigned char NumberH;	//	C
	unsigned char NumberL;	//	D
	char Master[11];	//	E
	char GuildName[9];	//	19
	unsigned char Mark[32];	//	22
	unsigned char btGuildType;	//	42
};

struct SDHP_GUILDMEMBER_INFO
{
	PBMSG_HEAD h;	//	
	char GuildName[9];	//	3
	char MemberID[11];	//	C
	unsigned char btGuildStatus;	//	17
	unsigned char btGuildType;	//	18
	short pServer;	//	1A
};

struct SDHP_GUILDALL_COUNT
{
	PWMSG_HEAD h;
	int Number;	// 4
	char GuildName[9];	// 8
	char Master[11];	// 11
	unsigned char Mark[32];	// 1C
	int score;	// 3C
	BYTE btGuildType;	// 40
	int iGuildUnion;	// 44
	int iGuildRival;	// 48
	char szGuildRivalName[9];	// 4C
	unsigned char Count;	// 55
};

struct SDHP_GUILDALL
{
	char MemberID[11];	// 0
	BYTE btGuildStatus;	// B
	short pServer;	// C
};

struct EXSDHP_UNION_RELATIONSHIP_LIST
{
	PWMSG_HEAD h;	//	
	unsigned char btFlag;	//	4
	unsigned char btRelationShipType;	//	5
	unsigned char btRelationShipMemberCount;	//	6
	char szUnionMasterGuildName[9];	//	7
	int iUnionMasterGuildNumber;	//	10
	int iRelationShipMember[100];	//	14
};

struct SDHP_GUILDDESTROY
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char GuildName[8];	// 5
	char Master[10];	// D
};

struct SDHP_GUILDDESTROY_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	unsigned char Flag;	//	4
	unsigned char NumberH;	//	5
	unsigned char NumberL;	//	6
	char GuildName[9];	//	7
	char Master[11];	//	10
};

struct EXSDHP_NOTIFICATION_RELATIONSHIP
{
	PWMSG_HEAD h;	//	
	unsigned char btFlag;	//	4
	unsigned char btUpdateFlag;	//	5
	unsigned char btGuildListCount;	//	6
	int iGuildList[100];	//	8
};

struct SDHP_GUILDMEMBERADD
{
	PBMSG_HEAD h;
	char GuildName[9];	// 3
	char MemberID[11];	// C
	BYTE NumberH;	// 17
	BYTE NumberL;	// 18
};

struct SDHP_GUILDMEMBERADD_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	unsigned char Flag;	//	4
	unsigned char NumberH;	//	5
	unsigned char NumberL;	//	6
	char GuildName[9];	//	7
	char MemberID[11];	//	10
	short pServer;	//	1C
};

struct SDHP_GUILDMEMBERDEL
{
	PBMSG_HEAD h;	// C1:33
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char GuildName[8];	// 5
	char MemberID[10];	// D
};

struct SDHP_GUILDMEMBERDEL_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	unsigned char Flag;	//	4
	unsigned char NumberH;	//	5
	unsigned char NumberL;	//	6
	char GuildName[9];	//	7
	char MemberID[11];	//	10
};

struct SDHP_GUILDMEMBER_INFO_REQUEST
{
	PBMSG_HEAD h;	// C1:35
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char MemberID[10];	// 5
};

struct SDHP_GUILDSCOREUPDATE
{
	PBMSG_HEAD h;	//	
	char GuildName[9];	//	3
	int Score;	//	C
};

struct SDHP_GUILDNOTICE
{
	PBMSG_HEAD h;	//	
	char GuildName[9];	//	3
	char szGuildNotice[60];	//	C
};

struct EXSDHP_SERVERGROUP_GUILD_CHATTING_RECV
{
	PBMSG_HEAD h;	//	
	int iGuildNum;	//	4
	char szCharacterName[10];	//	8
	char szChattingMsg[60];	//	12
};

struct EXSDHP_SERVERGROUP_UNION_CHATTING_RECV
{
	PBMSG_HEAD h;	//	
	int iUnionNum;	//	4
	char szCharacterName[10];	//	8
	char szChattingMsg[60];	//	12
};

struct EXSDHP_GUILD_ASSIGN_STATUS_REQ
{
	PBMSG_HEAD h;
	WORD wUserIndex;	// 4
	BYTE btType;	// 6
	BYTE btGuildStatus;	// 7
	char szGuildName[9];	// 8
	char szTargetName[11];	// 11
};

struct EXSDHP_GUILD_ASSIGN_STATUS_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char btFlag;	//	3
	unsigned short wUserIndex;	//	4
	unsigned char btType;	//	6
	unsigned char btResult;	//	7
	unsigned char btGuildStatus;	//	8
	char szGuildName[9];	//	9
	char szTargetName[11];	//	12
};

struct EXSDHP_GUILD_ASSIGN_TYPE_REQ
{
	PBMSG_HEAD h;
	WORD wUserIndex;	// 4
	BYTE btGuildType;	// 6;
	char szGuildName[9];	// 7
};

struct EXSDHP_GUILD_ASSIGN_TYPE_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char btFlag;	//	3
	unsigned short wUserIndex;	//	4
	unsigned char btGuildType;	//	6
	unsigned char btResult;	//	7
	char szGuildName[9];	//	8
};

struct EXSDHP_RELATIONSHIP_JOIN_REQ 
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x2|*/ unsigned short wRequestUserIndex;
  /*<thisrel this+0x6>*/ /*|0x2|*/ unsigned short wTargetUserIndex;
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char btRelationShipType;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int iRequestGuildNum;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int iTargetGuildNum;
};

struct EXSDHP_RELATIONSHIP_JOIN_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char btFlag;	//	3
	unsigned short wRequestUserIndex;	//	4
	unsigned short wTargetUserIndex;	//	6
	unsigned char btResult;	//	8
	unsigned char btRelationShipType;	//	9
	int iRequestGuildNum;	//	C
	int iTargetGuildNum;	//	10
	char szRequestGuildName[9];	//	14
	char szTargetGuildName[9];	//	1D
};

struct EXSDHP_RELATIONSHIP_BREAKOFF_REQ 
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x2|*/ unsigned short wRequestUserIndex;
  /*<thisrel this+0x6>*/ /*|0x2|*/ unsigned short wTargetUserIndex;
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char btRelationShipType;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int iRequestGuildNum;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int iTargetGuildNum;
};

struct EXSDHP_RELATIONSHIP_BREAKOFF_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char btFlag;	//	3
	unsigned short wRequestUserIndex;	//	4
	unsigned short wTargetUserIndex;	//	6
	unsigned char btResult;	//	8
	unsigned char btRelationShipType;	//	9
	int iRequestGuildNum;	//	C
	int iTargetGuildNum;	//	10
};

struct EXSDHP_UNION_LIST_REQ 
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x2|*/ unsigned short wRequestUserIndex;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int iUnionMasterGuildNumber;
};

struct EXSDHP_UNION_LIST 
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char btMemberNum;
  /*<thisrel this+0x1>*/ /*|0x20|*/ unsigned char Mark[32];
  /*<thisrel this+0x21>*/ /*|0x8|*/ char szGuildName[8];
};

struct EXSDHP_UNION_LIST_COUNT 
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ PWMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btCount;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char btResult;
  /*<thisrel this+0x6>*/ /*|0x2|*/ unsigned short wRequestUserIndex;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int iTimeStamp;
  /*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char btRivalMemberNum;
  /*<thisrel this+0xd>*/ /*|0x1|*/ unsigned char btUnionMemberNum;
};

struct EXSDHP_KICKOUT_UNIONMEMBER_REQ 
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x2|*/ unsigned short wRequestUserIndex;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char btRelationShipType;
  /*<thisrel this+0x7>*/ /*|0x8|*/ char szUnionMasterGuildName[8];
  /*<thisrel this+0xf>*/ /*|0x8|*/ char szUnionMemberGuildName[8];
};

struct EXSDHP_KICKOUT_UNIONMEMBER_RESULT
{
	PBMSG_HEAD2 h;	//	
	unsigned char btFlag;	//	4
	unsigned short wRequestUserIndex;	//	5
	unsigned char btRelationShipType;	//	8
	unsigned char btResult;	//	9
	char szUnionMasterGuildName[9];	//	A
	char szUnionMemberGuildName[9];	//	13
};

void ExDataServerInit();
void EDSProtocolCore(int aIndex, DWORD headcode, LPBYTE aRecv, int Len);
void ExDataServerLogin(int aIndex, SDHP_SERVERINFO* lpMsg);
void GDCharCloseRecv(int aIndex, SDHP_USERCLOSE* aRecv);
void GDGuildCreateSend(int aIndex,  SDHP_GUILDCREATE * aRecv);
void GDGuildDestroyRecv(int aIndex,  SDHP_GUILDDESTROY * aRecv);
void GDGuildMemberAdd(int aIndex,  SDHP_GUILDMEMBERADD * aRecv);
void GDGuildMemberDel(int aIndex,  SDHP_GUILDMEMBERDEL * aRecv);
void DGGuildMemberInfoRequest(int aIndex,  SDHP_GUILDMEMBER_INFO_REQUEST * aRecv);
void DGGuildScoreUpdate(int aIndex,  SDHP_GUILDSCOREUPDATE * aRecv);
void GDGuildNoticeSave(int aIndex,  SDHP_GUILDNOTICE * aRecv);
void GDGuildServerGroupChattingSend(int aIndex,  EXSDHP_SERVERGROUP_GUILD_CHATTING_RECV * aRecv);
void GDUnionServerGroupChattingSend(int aIndex, EXSDHP_SERVERGROUP_UNION_CHATTING_RECV * aRecv);
void GDGuildReqAssignStatus(int aIndex,  EXSDHP_GUILD_ASSIGN_STATUS_REQ * aRecv);
void GDGuildReqAssignType(int aIndex,  EXSDHP_GUILD_ASSIGN_TYPE_REQ * aRecv);
void DGRelationShipAnsJoin(int aIndex,  EXSDHP_RELATIONSHIP_JOIN_REQ * aRecv);
void DGRelationShipAnsBreakOff(int aIndex,  EXSDHP_RELATIONSHIP_BREAKOFF_REQ * aRecv);
void DGUnionListRecv(int aIndex,  EXSDHP_UNION_LIST_REQ * aRecv);
void DGRelationShipAnsKickOutUnionMember(int aIndex,  EXSDHP_KICKOUT_UNIONMEMBER_REQ *aRecv);

void FCHRoomCreateReq(int aIndex, char *szName, char *szFriendName, short Number, short ServerId, short FriendNumber, short FriendServerId);
void FriendChatRoomCreateReq(int aIndex, FHP_FRIEND_CHATROOM_CREATE_REQ* lpMsg);
void FriendChatRoomCreateAns(int aIndex, FCHP_CHATROOM_CREATE_RESULT* lpMsg);
void FriendChatRoomInvitationReq(int aIndex, FHP_FRIEND_INVITATION_REQ * lpMsg);
void FCHChatRoomInvitationReq(int aIndex, short RoomNumber, char *szName, short Number, short ServerId, BYTE Type);

int GetChatServer();

//--------------------------
// ---- ExDataServerDB -----
//--------------------------

struct strCmp
{
	bool operator()( const std::string s1, const std::string s2 ) const 
	{
		return strcmp( s1.data(), s2.data() ) < 0;
	}
};

typedef struct _GUILD_MEMBER
{
	char m_szMemberName[11];
	BYTE m_btStatus;
	BYTE m_btConnected;
	_GUILD_MEMBER()
	{
		ZeroMemory(m_szMemberName, sizeof(m_szMemberName));
		m_btStatus = 0;
		m_btConnected = -1;
	}
}GUILD_MEMBER, *LPGUILD_MEMBER;
typedef map<string, GUILD_MEMBER, strCmp> MAP_GUILD_MEMBER;

typedef struct tagGUILD_INFO_STRUCT
{
	int m_iNumber;
	char m_szGuildName[9];
	char m_szGuildMaster[11];
	BYTE m_btGuildType;
/*
	char m_szGuildMember[MAX_MEMBER_GUILD][10];
	BYTE m_btGuildStatus[MAX_MEMBER_GUILD];
	BYTE m_btConnected[MAX_MEMBER_GUILD];
*/
	MAP_GUILD_MEMBER m_mapGuildMember;
	int m_iRivalGuild;
	int m_iUnionGuild;
	BYTE m_Mark[32];
	int m_Score;
	char m_Notice[128];

	BOOL m_bGSHasData;
	tagGUILD_INFO_STRUCT()
	{
		m_iNumber = -1;
		memset(m_szGuildName, 0, sizeof(m_szGuildName));
		memset(m_szGuildMaster, 0, sizeof(m_szGuildMaster));
		m_btGuildType = -1;
		memset(m_Mark, 0, sizeof(m_Mark));
		memset(m_Notice,0,sizeof(m_Notice));
		m_iRivalGuild = 0;
		m_iUnionGuild = 0;
		m_Score = 0;
		m_mapGuildMember.clear();
		m_bGSHasData = FALSE;
	}

}GUILD_INFO_STRUCT, *LPGUILD_INFO_STRUCT;
typedef std::map<std::string, tagGUILD_INFO_STRUCT,strCmp> MAP_GUILD_INFO_STRUCT;

typedef struct tagUNION_DATA
{
	std::vector<int>	m_vecUnionMember;
}UNION_DATA, *LPUNION_DATA;
typedef std::map<int, tagUNION_DATA> MAP_UNION_DATA;

BOOL InitGuild(char * Query);

LPGUILD_MEMBER GetGuildMember(char *szGuild, char *szName);
BOOL GuildExists(char *szGuild);
int CreateDBGuild(char* szGuild, char* szMaster, LPBYTE pMark);
int GetDBGuildNumber(char *szGuild);
BOOL AddGuild(char *szGuild, char *szMaster, int iNumber, char *lpNotice, int iScore, LPBYTE pMark, int iType);
BOOL CreateRelationShipData(int iGuild);
LPUNION_DATA GetUnionData(int iGuild);
BOOL UpdateGuildMemberStatus(char *szGuild, char *szName, BYTE btStatus);
BOOL UpdateGuildType(char *szGuild, BYTE btType);
void SendGuildMemberInfo(int aIndex,  char *szName);
BOOL GetGuildMemberInfo(char *szName, OUT char *szGuild, OUT int& riLevel, OUT int& riStatus);
void DGGuildMasterListSend(char *szGuild);
LPGUILD_INFO_STRUCT GetGuild(char *szGuild);
LPGUILD_INFO_STRUCT GetGuild(int iNumber);
void DGRelationShipListSend(int aIndex,  int iGuild, int relation_type, BOOL snd_all);
BOOL IsCSGuild(char *szGuild);
int UnionBreak(LPGUILD_INFO_STRUCT lpMasterGuild, LPGUILD_INFO_STRUCT lpKickGuild);
BOOL KickUnion(LPGUILD_INFO_STRUCT lpMasterGuild, LPGUILD_INFO_STRUCT lpKickGuild);
BOOL UpdateDBUnion(int iGuild, int iUnion);
void DGRelationShipNotificationSend(int iGuild, int iUpdateFlag);
void SendListToAllRivals(LPGUILD_INFO_STRUCT lpGuild);
int RivalBreak(LPGUILD_INFO_STRUCT lpMasterGuild, LPGUILD_INFO_STRUCT lpKickGuild);
BOOL UpdateDBRival(int iGuild, int iRival);
BOOL MasterDBExists(char *szMaster);
BOOL DelAllDBGuildMember(char *szGuild);
BOOL DelDBGuild(char *szGuild);
BOOL DelGuild(char *szGuild);
BOOL DBGuildMemberExists(char *szName);
BOOL AddDBGuildMember(char *szGuild, char *szName);
BOOL AddGuildMember(char *szGuild, char *szName, BYTE btStatus = 0, BYTE btConnected = -1);
BOOL GuildMemberExists(char *szGuild, char *szName);
BOOL DelDBGuildMember(char *szName);
BOOL DelGuildMember(char *szGuild, char *szName);
BOOL UpdateScore(char *szGuild, int iScore);
BOOL SaveNotice(char *szGuild, char *szNotice);
int RelationShipOperation(int iReqGuild, int iTargGuild, int relation_type, int operation);
int RelationShipJoin(LPGUILD_INFO_STRUCT lpReqGuild, LPGUILD_INFO_STRUCT lpTargGuild, int type);
int RelationShipBreak(LPGUILD_INFO_STRUCT lpMasterGuild, LPGUILD_INFO_STRUCT lpKickGuild, int type);
int UnionJoin(LPGUILD_INFO_STRUCT lpReqGuild, LPGUILD_INFO_STRUCT lpTargGuild);
BOOL AddUnion(LPGUILD_INFO_STRUCT lpReqGuild, LPGUILD_INFO_STRUCT lpTargGuild);
BOOL AddUnion(int iReqGuild, int iTargGuild);
int RivalJoin(LPGUILD_INFO_STRUCT lpReqGuild, LPGUILD_INFO_STRUCT lpTargGuild);

//--------------------------
// ---- FriendSererDB -----
//--------------------------