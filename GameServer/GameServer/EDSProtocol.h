#ifndef EDSPROTOCOL_H
#define EDSPROTOCOL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\prodef.h"
#include "protocol.h"
#include "..\..\Common\Packets.h"

struct SDHP_USERCLOSE
{
	PBMSG_HEAD h;	//	
	char CharName[10];	//	3
	char GuildName[8];	//	D
	BYTE Type;	//	15
};




struct SDHP_GUILDCREATE_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE Result;	//	3
	BYTE Flag;	//	4
	DWORD GuildNumber;	//	8
	BYTE NumberH;	//	C
	BYTE NumberL;	//	D
	char Master[11];	//	E
	char GuildName[9];	//	19
	BYTE Mark[32];	//	22
	BYTE btGuildType;	//	42
};



struct SDHP_GUILDDESTROY_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE Result;	//	3
	BYTE Flag;	//	4
	BYTE NumberH;	//	5
	BYTE NumberL;	//	6
	char GuildName[9];	//	7
	char Master[11];	//	10
};




struct SDHP_GUILDMEMBERADD_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE Result;	//	3
	BYTE Flag;	//	4
	BYTE NumberH;	//	5
	BYTE NumberL;	//	6
	char GuildName[9];	//	7
	char MemberID[11];	//	10
	short pServer;	//	1C
};




struct SDHP_GUILDMEMBERDEL_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE Result;	//	3
	BYTE Flag;	//	4
	BYTE NumberH;	//	5
	BYTE NumberL;	//	6
	char GuildName[9];	//	7
	char MemberID[11];	//	10
};




struct SDHP_GUILDUPDATE
{
	PBMSG_HEAD h;	//	
	char GuildName[9];	//	3
	char Master[11];	//	C
	BYTE Mark[32];	//	17
	int Score;	//	28
	BYTE Count;	//	3C
};




struct SDHP_GUILDMEMBER_INFO
{
	PBMSG_HEAD h;	//	
	char GuildName[9];	//	3
	char MemberID[11];	//	C
	BYTE btGuildStatus;	//	17
	BYTE btGuildType;	//	18
	short pServer;	//	1A
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
	char szGuildNotice[MAX_CHAT_LEN];	//	C	..60
};




struct SDHP_GUILDCREATED
{
	PBMSG_HEAD h;	//	
	WORD Number;	//	4
	char GuildName[9];	//	6
	char Master[11];	//	F
	BYTE Mark[32];	//	1A
	int score;	//	3C
};




struct SDHP_GUILDLISTSTATE
{
	PBMSG_HEAD h;	//	
	BYTE State;	//	3
	int Count;	//	4
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




struct EXSDHP_GUILD_ASSIGN_STATUS_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE btFlag;	//	3
	WORD wUserIndex;	//	4
	BYTE btType;	//	6
	BYTE btResult;	//	7
	BYTE btGuildStatus;	//	8
	char szGuildName[9];	//	9
	char szTargetName[11];	//	12
};




struct EXSDHP_GUILD_ASSIGN_TYPE_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE btFlag;	//	3
	WORD wUserIndex;	//	4
	BYTE btGuildType;	//	6
	BYTE btResult;	//	7
	char szGuildName[9];	//	8
};




struct EXSDHP_RELATIONSHIP_JOIN_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE btFlag;	//	3
	WORD wRequestUserIndex;	//	4
	WORD wTargetUserIndex;	//	6
	BYTE btResult;	//	8
	BYTE btRelationShipType;	//	9
	int iRequestGuildNum;	//	C
	int iTargetGuildNum;	//	10
	char szRequestGuildName[9];	//	14
	char szTargetGuildName[9];	//	1D
};




struct EXSDHP_RELATIONSHIP_BREAKOFF_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE btFlag;	//	3
	WORD wRequestUserIndex;	//	4
	WORD wTargetUserIndex;	//	6
	BYTE btResult;	//	8
	BYTE btRelationShipType;	//	9
	int iRequestGuildNum;	//	C
	int iTargetGuildNum;	//	10
};




struct EXSDHP_NOTIFICATION_RELATIONSHIP
{
	PWMSG_HEAD h;	//	
	BYTE btFlag;	//	4
	BYTE btUpdateFlag;	//	5
	BYTE btGuildListCount;	//	6
	int iGuildList[100];	//	8
};




struct EXSDHP_UNION_RELATIONSHIP_LIST
{
	PWMSG_HEAD h;	//	
	BYTE btFlag;	//	4
	BYTE btRelationShipType;	//	5
	BYTE btRelationShipMemberCount;	//	6
	char szUnionMasterGuildName[9];	//	7
	int iUnionMasterGuildNumber;	//	10
	int iRelationShipMember[100];	//	14
};

struct EXSDHP_KICKOUT_UNIONMEMBER_RESULT
{
	PBMSG_HEAD2 h;	//	
	BYTE btFlag;	//	4
	WORD wRequestUserIndex;	//	5
	BYTE btRelationShipType;	//	8
	BYTE btResult;	//	9
	char szUnionMasterGuildName[9];	//	A
	char szUnionMemberGuildName[9];	//	13
};

struct PMSG_FRIEND_STATE_C
{
	PBMSG_HEAD h;	//	
	BYTE ChatVeto;	//	3
};

struct PMSG_FRIEND_LIST_COUNT
{
	PWMSG_HEAD h;
	BYTE MemoCount;	// 4
	BYTE MailTotal;	// 5
	BYTE Count;	// 6
};

struct PMSG_FRIEND_ADD_SIN_REQ
{
	PBMSG_HEAD h;
	char Name[10];	// 3
};

struct PMSG_FRIEND_STATE
{
	PBMSG_HEAD h;	// C1:C4
	char Name[10];	// 3
	BYTE State;	// D
};

struct PMSG_FRIEND_ADD_REQ
{
	PBMSG_HEAD h;
	char Name[10];	// 3
};

struct PMSG_FRIEND_ADD_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	char Name[10];	// 4
	BYTE State;	// E
};

struct PMSG_FRIEND_ADD_SIN_RESULT
{
	PBMSG_HEAD h;	//	
	BYTE Result;	//	3
	char Name[10];	//	4
};

struct PMSG_FRIEND_DEL_REQ
{
	PBMSG_HEAD h;	//	
	char Name[10];	//	3
};

struct PMSG_FRIEND_DEL_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	char Name[10];	// 4
};

struct PMSG_FRIEND_ROOMCREATE_REQ
{
	PBMSG_HEAD h;	//	
	char Name[10];	//	3
};

struct PMSG_FRIEND_ROOMCREATE_RESULT
{
	PBMSG_HEAD h;
	BYTE ServerIp[15];	// 3
	WORD RoomNumber;	// 12
	DWORD Ticket;	// 14
	BYTE Type;	// 18
	char Name[10];	// 19
	BYTE Result;	// 23
};

struct PMSG_FRIEND_MEMO
{
	PWMSG_HEAD h;	//	
	DWORD WindowGuid;	//	4
	char Name[10];	//	8
	char Subject[32];	//	12
	char tmp[28];// -> 6.3?
	BYTE Dir;	//	32
	BYTE Action;	//	33
	short MemoSize;	//	34
	char Memo[1000];	//	36
};

struct PMSG_JG_MEMO_SEND
{
	PWMSG_HEAD h;
	char Name[10];	// 4
	char TargetName[10];	// E
	char Subject[32];	// 18
	short MemoSize;	// 38
	char Memo[1000];	// 3A
};

struct PMSG_FRIEND_MEMO_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	DWORD WindowGuid;	// 4
};

struct PMSG_FRIEND_MEMO_LIST
{
	PBMSG_HEAD h;
	WORD Number;	// 4
	char Name[10];	// 6
	char Date[30];	// 10
	//char Subject[32];	// 2E	//6.3
	char Subject[60];
	BYTE read;	// 4E
};

struct PMSG_FRIEND_READ_MEMO_REQ
{
	PBMSG_HEAD h;	//	
	WORD MemoIndex;	//	4
};

struct PMSG_FRIEND_READ_MEMO
{
	PWMSG_HEAD h;
	WORD MemoIndex;	// 4
	short MemoSize;	// 6
	BYTE Photo[18];	// 8
	BYTE Dir;	// 1A
	BYTE Action;	//1B
	char Memo[1000];	// 1C
};

struct PMSG_FRIEND_MEMO_DEL_REQ
{
	PBMSG_HEAD h;	//	
	WORD MemoIndex;	//	4
};

struct PMSG_FRIEND_MEMO_DEL_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	WORD MemoIndex;	// 4
};

struct PMSG_ROOM_INVITATION
{
	PBMSG_HEAD h;	//	
	char Name[10];	//	3
	WORD RoomNumber;	//	E
	DWORD WindowGuid;	//	10
};

struct PMSG_ROOM_INVITATION_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	DWORD WindowGuid;	// 4
};

void ExDataServerProtocolCore(BYTE protoNum, LPBYTE aRecv, int aLen);
void ExDataServerLogin();
void GDCharClose(int type, LPSTR GuildName, LPSTR Name);
void ExDataServerLoginResult( SDHP_RESULT* lpMsg);
void GDCharCloseRecv( SDHP_USERCLOSE* lpMsg);
void GDGuildCreateSend(int aIndex, LPSTR Name, LPSTR Master, LPBYTE Mark, int iGuildType);
void GDGuildCreateRecv( SDHP_GUILDCREATE_RESULT* lpMsg);
void GDGuildDestroySend(int aIndex, LPSTR Name, LPSTR Master);
void GDGuildDestroyRecv( SDHP_GUILDDESTROY_RESULT* lpMsg);
void GDGuildMemberAdd(int aIndex, LPSTR Name, LPSTR MemberId);
void GDGuildMemberAddResult( SDHP_GUILDMEMBERADD_RESULT* lpMsg);
void GDGuildMemberDel(int aIndex, LPSTR Name, LPSTR MemberId);
void GDGuildMemberDelResult( SDHP_GUILDMEMBERDEL_RESULT* lpMsg);
void GDGuildUpdate(LPSTR Name, LPSTR Master, LPBYTE Mark,  int score, BYTE count);
void DGGuildUpdateRecv( SDHP_GUILDUPDATE* lpMsg);
void DGGuildMemberInfoRequest(int aIndex);
void DGGuildMemberInfo( SDHP_GUILDMEMBER_INFO* lpMsg);
void DGGuildMasterListRecv(LPBYTE lpData);
void DGGuildScoreUpdate(LPSTR guildname, int score);
void GDGuildScoreUpdateRecv( SDHP_GUILDSCOREUPDATE* lpMsg);
void GDGuildNoticeSave(LPSTR guild_name, LPSTR guild_notice);
void DGGuildNoticeRecv( SDHP_GUILDNOTICE* lpMsg);
void DGGuildListRequest();
void DGGuildList( SDHP_GUILDCREATED* lpMsg);
int __stdcall GuildListDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
void DGGuildListState( SDHP_GUILDLISTSTATE* lpMsg);
void GDGuildServerGroupChattingSend(int iGuildNum,  PMSG_CHATDATA* lpChatData);
void DGGuildServerGroupChattingRecv( EXSDHP_SERVERGROUP_GUILD_CHATTING_RECV* lpMsg);
void GDUnionServerGroupChattingSend(int iUnionNum,  PMSG_CHATDATA* lpChatData);
void DGUnionServerGroupChattingRecv( EXSDHP_SERVERGROUP_UNION_CHATTING_RECV* lpMsg);
void GDGuildReqAssignStatus(int aIndex, int iAssignType, LPSTR szTagetName, int iGuildStatus);
void DGGuildAnsAssignStatus( EXSDHP_GUILD_ASSIGN_STATUS_RESULT* lpMsg);
void GDGuildReqAssignType(int aIndex, int iGuildType);
void DGGuildAnsAssignType( EXSDHP_GUILD_ASSIGN_TYPE_RESULT* lpMsg);
void GDRelationShipReqJoin(int aIndex, int iTargetUserIndex, int iRelationShipType);
void DGRelationShipAnsJoin( EXSDHP_RELATIONSHIP_JOIN_RESULT* lpMsg);
void GDUnionBreakOff(int aIndex, int iUnionNumber);
void DGUnionBreakOff( EXSDHP_RELATIONSHIP_BREAKOFF_RESULT* lpMsg);
void GDRelationShipReqBreakOff(int aIndex, int iTargetUserIndex, int iRelationShipType);
void DGRelationShipAnsBreakOff( EXSDHP_RELATIONSHIP_BREAKOFF_RESULT* lpMsg);
void DGRelationShipNotificationRecv( EXSDHP_NOTIFICATION_RELATIONSHIP* lpMsg);
void DGRelationShipListRecv( EXSDHP_UNION_RELATIONSHIP_LIST* lpMsg);
void GDUnionListSend(int iUserIndex, int iUnionMasterGuildNumber);
void DGUnionListRecv(LPBYTE aRecv);
void GDRelationShipReqKickOutUnionMember(int aIndex, LPSTR szTargetGuildName);
void DGRelationShipAnsKickOutUnionMember( EXSDHP_KICKOUT_UNIONMEMBER_RESULT* lpMsg);
void FriendListRequest(int aIndex);
void FriendListResult(LPBYTE lpMsg);
void WaitFriendListResult( FHP_WAITFRIENDLIST_COUNT* lpMsg);
void FriendStateClientRecv( PMSG_FRIEND_STATE_C* lpMsg, int aIndex);
void FriendStateRecv( FHP_FRIEND_STATE* lpMsg);
void FriendAddRequest( PMSG_FRIEND_ADD_REQ * lpMsg, int aIndex);
void FriendAddResult( FHP_FRIEND_ADD_RESULT* lpMsg);
void WaitFriendAddRequest( PMSG_FRIEND_ADD_SIN_RESULT* lpMsg, int aIndex);
void WaitFriendAddResult( FHP_WAITFRIEND_ADD_RESULT* lpMsg);
void FriendDelRequest( PMSG_FRIEND_DEL_REQ* lpMsg, int aIndex);
void FriendDelResult( FHP_FRIEND_DEL_RESULT* lpMsg);
void FriendChatRoomCreateReq( PMSG_FRIEND_ROOMCREATE_REQ* lpMsg, int aIndex);
void FriendChatRoomCreateResult( FHP_FRIEND_CHATROOM_CREATE_RESULT* lpMsg);
void FriendMemoSend( PMSG_FRIEND_MEMO* lpMsg, int aIndex);
void FriendMemoSendEx(int toIndex, int fromIndex, std::string subject, std::string body, BYTE dir, BYTE action, std::string senderName);
void MngFriendMemoSend( PMSG_JG_MEMO_SEND* lpMsg);
BOOL WithdrawUserMoney(LPSTR Type, struct OBJECTSTRUCT* lpObj, int Withdraw_Money);
void FriendMemoSendResult( FHP_FRIEND_MEMO_SEND_RESULT* lpMsg);
void FriendMemoListReq(int aIndex);
void FriendMemoList( FHP_FRIEND_MEMO_LIST* lpMsg);
void FriendMemoReadReq( PMSG_FRIEND_READ_MEMO_REQ* lpMsg, int aIndex);
void FriendMemoRead( FHP_FRIEND_MEMO_RECV* lpMsg);
void FriendMemoDelReq( PMSG_FRIEND_MEMO_DEL_REQ* lpMsg, int aIndex);
void FriendMemoDelResult( FHP_FRIEND_MEMO_DEL_RESULT* lpMsg);
void FriendRoomInvitationReq( PMSG_ROOM_INVITATION* lpMsg, int aIndex);
void FriendRoomInvitationRecv( FHP_FRIEND_INVITATION_RET* lpMsg);


#endif