#ifndef SPROTOCOL_H
#define SPROTOCOL_H
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "protocol.h"
#include "EDSProtocol.h"

// EventControl
//-----------------------------
#define DRAGON_EVENT		0
#define XMAS_EVENT			1
#define FIRECRACKER_EVENT	2
#define HEARTOFLOVE_EVENT	3
#define MEDAL_EVENT			4

// OptionControl
//-----------------------------
#define OPTION_RELOAD		0
#define MONSTER_RELOAD		1
#define SHOP_RELOAD			2
#define ALLOPTION_RELOAD	3
#define EVENTINFO_RELOAD	4
#define ETCINFO_RELOAD		5
#define OPTION_CONTROL		6

/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet User Close by Id
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x05
 */
struct SDHP_USERCLOSE_ID
{
	PBMSG_HEAD h;
	char szId[10];
	char szName[10];
	WORD Level;
	BYTE DbClass;
};

/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Id Pass Result
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x01
 */
struct SDHP_IDPASSRESULT
{
	PBMSG_HEAD h;
	BYTE result;	// 3
	short Number;	// 4
	char Id[10];	//	6
	int UserNumber;
	int DBNumber;
	char JoominNumber[13];
	int ukn_30;//NEW
	BYTE PcBangRoom;//NEW
};

typedef struct
{
	PBMSG_HEAD	h;
	char szId[MAX_IDSTRING];
} SDHP_USEROFFLINE_CLOSE, *LPSDHP_USEROFFLINE_CLOSE;


/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x02
 */
struct SDHP_JOINFAIL
{
	PBMSG_HEAD h;
	short Number;
	char Id[11];
	int UserNumber;
	int DBNumber;

};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x04
 */
struct SDHP_COMMAND_BLOCK
{
	PBMSG_HEAD h;
	short Number;
	char Id[11];
	int UserNumber;
	int DBNumber;
	BYTE BlockCode;
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Bill Search Result
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x06
 */
struct SDHP_BILLSEARCH_RESULT
{
	PBMSG_HEAD h;
	char Id[10];
	short Number;
	BYTE cCertifyType;
	BYTE PayCode;
	char EndsDays[12];
	int EndTime;
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Bill Kill User
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x07, 0x09
 */
struct SDHP_BILLKILLUSER
{
	struct PBMSG_HEAD h;
	char Id[10];
	short Number;
};


typedef struct
{
	PBMSG_HEAD	h;
	char szId[MAX_IDSTRING];
} SDHP_FORCE_USERCLOSE, *LPSDHP_FORCE_USERCLOSE;




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x08
 */
struct SDHP_OTHERJOINMSG
{
	struct PBMSG_HEAD h;
	char AccountID[10];
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x20
 */
struct SDHP_EXITMSG
{
	PBMSG_HEAD h;
	BYTE ExitCode[3];
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x30
 */
struct SDHP_EVENTSTART
{
	PBMSG_HEAD h;
	BYTE Event;
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x40
 */
struct SDHP_EVENTCONTROL
{
	PBMSG_HEAD h;
	BYTE Event;
	BYTE Stat;
};


/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x41
 */
struct SDHP_OPTIONCONTROL
{
	PBMSG_HEAD h;
	BYTE Option;
};





/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x30
 */
struct SDHP_LOVEHEARTEVENT
{
	PBMSG_HEAD h;
	char Account[10];
	char Name[10];
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x61
 */
struct SDHP_LOVEHEARTEVENT_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;
	char Name[10];
	int Number;
};






/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x31
 */
struct SDHP_LOVEHEARTCREATE
{
	PBMSG_HEAD h;
	BYTE x;
	BYTE y;
	BYTE MapNumber;
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x62
 */
struct SDHP_NOTICE
{
	PBMSG_HEAD h;
	char Notice[61];
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x63
 */
struct SDHP_USER_NOTICE
{
	PBMSG_HEAD h;
	char szId[10];
	char Notice[61];
};




/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Join Fail
 *	Direction : GameServer -> JoinServer
 *  Code : 0xC1
 *	HeadCode : 0x7A
 */
struct PMSG_REQ_MAPSVRMOVE
{
	PBMSG_HEAD h;
	int iIndex;
	char szAccountID[11];
	char szCharName[11];
	WORD wCurMapSvrCode;
	WORD wDstMapSvrCode;
	WORD wMapNumber;
	BYTE btX;
	BYTE btY;
	BYTE btPcbangRoom;
};



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Other Join Message
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x7A
 */
struct PMSG_ANS_MAPSVRMOVE
{
	PBMSG_HEAD h;
	int iIndex;
	char szAccountID[11];
	char szCharName[11];
	WORD wCurMapSvrCode;
	WORD wDstMapSvrCode;
	WORD wMapNumber;
	BYTE btX;
	BYTE btY;
	int iResult;
	int iJoinAuthCode1;
	int iJoinAuthCode2;
	int iJoinAuthCode3;
	int iJoinAuthCode4;
};


typedef struct
{
	PBMSG_HEAD	h;
	char szId[MAX_IDSTRING];
	bool Offline;
} SDHP_USEROFFLINE_CHANGE, *LPSDHP_USEROFFLINE_CHANGE;



/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet Map Server Auth Answer
 *	Direction : JoinServer -> GameServer
 *  Code : 0xC1
 *	HeadCode : 0x7A ?????????????????????????????? #error
 */
struct PMSG_ANS_MAPSVRAUTH
{
	PBMSG_HEAD h;
	int iIndex;
	char szAccountID[11];
	char szCharName[11];
	WORD wPrevMapSvrCode;
	WORD wMapNumber;
	BYTE btX;
	BYTE btY;
	int iResult;
	int iUserNumber;
	int iDBNumber;
	char cJoominNumber[13];
	BYTE btBlockCode;
	int ukn_30;//NEW
	BYTE PcBangRoom;//NEW
};

struct BroadCastMessageInfo
{
	PWMSG_HEAD	h;
	BYTE		Type;
	BYTE		SenderChannel;
	char		Sender[10];
	char		Text[90];
};

struct BroadCastPCIDConnectedInfo
{
	PWMSG_HEAD	h;
	BYTE		SenderChannel;
	DWORD		PCID;
	int			index;
};

struct BroadCastPCIDDisconnectedInfo
{
	PWMSG_HEAD	h;
	BYTE		SenderChannel;
	DWORD		PCID;
	int			index;
};

struct BroadCastGSDisconnectedInfo
{
	PWMSG_HEAD	h;
	BYTE		SenderChannel;
};

struct BroadCastGSConnectedInfo
{
	PWMSG_HEAD	h;
	BYTE		SenderChannel;
};

struct GSPCInfo
{
	DWORD		PCID;
	int			index;
};

typedef struct 
{
	PWMSG_HEAD	h;
	BYTE		SenderChannel;
	BYTE		DestChannel;
	DWORD		Count;
} PMSG_GSPCInfo, *LPMSG_GSPCInfo;

typedef struct
{
	PWMSG_HEAD	h;
	BYTE		SenderChannel;
	DWORD		Count;
} PMSG_GSSyncPCInfo, *LPMSG_GSSyncPCInfo;

void SProtocolCore(BYTE protoNum, LPBYTE aRecv, int aLen);
void GJServerLogin();
void JGServerLoginResult( SDHP_RESULT * lpMsg);
void GJPUserClose(LPCSTR szAccountID);
void GJPUserClose(LPOBJ lpObj);
void JGPAccountRequest(SDHP_IDPASSRESULT * lpMsg);
void JGPDisconnectOfflineuser(LPSDHP_USEROFFLINE_CLOSE lpMsg);

void GJPAccountFail(short number, char* Id, int DBNumber, int UserNumber);
void GJPAccountBlock(short number, char * Id, int DBNumber, int UserNumber, int BlockCode);
void GJPBillCeckRecv(SDHP_BILLSEARCH_RESULT * lpMsg);
void GJPUserKillRecv(SDHP_BILLKILLUSER * lpMsg);
void JGOtherJoin(SDHP_OTHERJOINMSG * lpMsg);
void GJPUserDisconnectRecv( SDHP_BILLKILLUSER * lpMsg);
void GJPUserDisconnectRecv( SDHP_BILLKILLUSER * lpMsg);
void GJPForceUserDisconnect(LPSDHP_FORCE_USERCLOSE lpMsg);
void JGPExitCodeRecv( SDHP_EXITMSG * lpMsg );
void JGPEventStart( SDHP_EVENTSTART * lpMsg );
void JGPEventControl( SDHP_EVENTCONTROL * lpMsg );
void JGPOptionControl( SDHP_OPTIONCONTROL * lpMsg );
void LoveHeartEventSend(int aIndex, LPSTR AcountId, LPSTR Name);
void LoveHeartEventRecv( SDHP_LOVEHEARTEVENT_RESULT * lpMsg );
void LoveHeartCreateSend();
void AllNoticeRecv( SDHP_NOTICE * lpMsg);
void UserNoticeRecv( SDHP_USER_NOTICE * lpMsg);
void GJReqMapSvrMove(int iIndex, WORD wDesMapSvrCode, WORD wMapNumber, BYTE btX, BYTE btY);
void JGAnsMapSvrMove(PMSG_ANS_MAPSVRMOVE * lpMsg);
void GJReqMapSvrAuth(int iIndex, LPSTR lpszAccountID, LPSTR lpszCharName, int iJA1, int iJA2, int iJA3, int iJA4);
void JGAnsMapSvrAuth(PMSG_ANS_MAPSVRAUTH * lpMsg);
void GJNotifyMaxUserCount();
void JGPSendMail(PMSG_JG_MEMO_SEND * lpMsg);
void GJUpdateMatchDBUserCharacters(LPOBJ lpObj);
void JGPCInfo(PMSG_GSPCInfo* lpMsg);
void JGSyncPC(PMSG_GSSyncPCInfo* lpMsg);

void GJPCConnected(DWORD PCID, int index);
void GJPCDisconnected(DWORD PCID, int index);

void BroadCastMessage(BroadCastMessageInfo* lpData);
void BroadCastPCIDConnected(BroadCastPCIDConnectedInfo* lpData);
void BroadCastPCIDDisconnected(BroadCastPCIDDisconnectedInfo* lpData);
void BroadCastGSDisconnected(BroadCastGSDisconnectedInfo* lpData);
void BroadCastGSConnected(BroadCastGSConnectedInfo* lpData);

#endif