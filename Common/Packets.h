#pragma once

struct FHP_FRIENDLIST_REQ
{

	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0x10>*/ /*|0x1|*/ unsigned char pServer;

};
// <size 0x12>

struct FHP_FRIENDLIST
{

	/*<thisrel this+0x0>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0xa>*/ /*|0x1|*/ unsigned char Server;
};
// <size 0xb>

struct FHP_FRIENDLIST_COUNT
{

	/*<thisrel this+0x0>*/ /*|0x4|*/ struct PWMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0x10>*/ /*|0x1|*/ unsigned char Count;
	/*<thisrel this+0x11>*/ /*|0x1|*/ unsigned char MailCount;
	/*<thisrel this+0x12>*/ /*|0x1|*/ unsigned char Server;
};
// <size 0x12>


struct FHP_WAITFRIENDLIST_COUNT
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	char Name[10];	//	6
	char FriendName[10];	//	10
};

struct FHP_FRIEND_STATE_C
{

	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0x10>*/ /*|0x1|*/ unsigned char State;
};
// <size 0x12>



struct FHP_FRIEND_STATE
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	char Name[10];	//	6
	char FriendName[10];	//	10
	unsigned char State;	//	1A
};


struct FHP_FRIEND_ADD_REQ
{
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0x10>*/ /*|0xa|*/ char FriendName[10];
};
// <size 0x1a>


struct FHP_FRIEND_ADD_RESULT
{
	PBMSG_HEAD h;
	short Number;	// 4
	unsigned char Result;	// 6
	char Name[10];	// 7
	char FriendName[10];	// 11
	unsigned char Server;	// 1B
};

struct FHP_WAITFRIEND_ADD_REQ
{

	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char Result;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0x10>*/ /*|0xa|*/ char FriendName[10];
};
// <size 0x1a>


struct FHP_WAITFRIEND_ADD_RESULT
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	unsigned char Result;	//	6
	char Name[10];	//	7
	char FriendName[10];	//	11
	unsigned char pServer;	//	1B
};



struct FHP_FRIEND_DEL_RESULT
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	unsigned char Result;	//	6
	char Name[10];	//	7
	char FriendName[10];	//	11
};


struct FHP_FRIEND_MEMO_SEND
{
	/*<thisrel this+0x0>*/ /*|0x4|*/ struct PWMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long WindowGuid;
	/*<thisrel this+0xc>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0x16>*/ /*|0xa|*/ char ToName[10];
	/*<thisrel this+0x20>*/ /*|0x20|*/ char Subject[60];
	/*<thisrel this+0x40>*/ /*|0x1|*/ unsigned char Dir;
	/*<thisrel this+0x41>*/ /*|0x1|*/ unsigned char Action;
	/*<thisrel this+0x42>*/ /*|0x2|*/ short MemoSize;
	/*<thisrel this+0x44>*/ /*|0x12|*/ unsigned char Photo[18];
	/*<thisrel this+0x56>*/ /*|0x3e8|*/ char Memo[1000];
};
// <size 0x440>

struct FHP_FRIEND_MEMO_SEND_OLD
{
	struct PWMSG_HEAD h;
	short Number;
	unsigned long WindowGuid;
	char Name[10];
	char ToName[10];
	char Subject[32];
	unsigned char Dir;
	unsigned char Action;
	short MemoSize;
	unsigned char Photo[13];
	char Memo[1000];
};

struct FHP_FRIEND_MEMO_SEND_RESULT
{
	PBMSG_HEAD h;	//	
	short Number;	//	4
	char Name[10];	//	6
	unsigned char Result;	//	10
	unsigned long WindowGuid;	//	14
};


struct FHP_FRIEND_MEMO_LIST_REQ
{

	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ unsigned short Number;
	/*<thisrel this+0x6>*/ /*|0xa|*/ char Name[10];

};
// <size 0x10>


struct FHP_FRIEND_MEMO_LIST
{
	PWMSG_HEAD h;	//	
	unsigned short Number;	//	4
	unsigned short MemoIndex;	//	6
	char SendName[10];	//	8
	char RecvName[10];	//	12
	char Date[30];	//	1C
	char Subject[60];	//	3A
	unsigned char read;	//	5A
};

struct FHP_FRIEND_MEMO_RECV_REQ
{

	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0x2|*/ unsigned short MemoIndex;
	/*<thisrel this+0x8>*/ /*|0xa|*/ char Name[10];

};
// <size 0x12>


struct FHP_FRIEND_MEMO_RECV
{
	PWMSG_HEAD h;	//	
	short Number;	//	4
	char Name[10];	//	6
	unsigned short MemoIndex;	//	10
	short MemoSize;	//	12
	unsigned char Photo[18];	//	14
	unsigned char Dir;	//	26
	unsigned char Action;	//	27
	char Memo[1000];	//	28
};

struct FHP_FRIEND_MEMO_RECV_OLD
{
	PWMSG_HEAD h;
	short Number;
	char Name[10];
	unsigned short MemoIndex;
	short MemoSize;
	unsigned char Photo[13];
	unsigned char Dir;
	unsigned char Action;
	char Memo[1000];
};

struct FHP_FRIEND_MEMO_DEL_REQ
{

	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0x2|*/ unsigned short MemoIndex;
	/*<thisrel this+0x8>*/ /*|0xa|*/ char Name[10];

};
// <size 0x12>

struct FHP_FRIEND_MEMO_DEL_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	unsigned short MemoIndex;	//	4
	short Number;	//	6
	char Name[10];	//	8
};

struct MEMO_HEADER
{
	unsigned short MemoIndex;
	char SendName[10];
	char RecvName[10];
	char Date[30];
	char Subject[60];
	unsigned char read;
};

struct MEMO_SEND_HEADER
{
	char Name[10];
	char ToName[10];
	char Subject[60];
	unsigned char Dir;
	unsigned char Action;
};

struct MEMO_READ
{
	unsigned char Dir;
	unsigned char Action;
	char Memo[1000];
};


struct FHP_FRIEND_CHATROOM_CREATE_REQ
{

	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0x10>*/ /*|0xa|*/ char fName[10];
};
// <size 0x1a>


struct FHP_FRIEND_CHATROOM_CREATE_RESULT
{
	PBMSG_HEAD h;	//	
	unsigned char Result;	//	3
	short Number;	//	4
	char Name[10];	//	6
	char FriendName[10];	//	10
	char ServerIp[15];	//	1A
	unsigned short RoomNumber;	//	2A
	unsigned long Ticket;	//	2C
	unsigned char Type;	//	30
};


struct FCHP_CHATROOM_CREATE_REQ
{
	PBMSG_HEAD h;
	char Name[10];
	char FriendName[10];
	BYTE Type;
	short Number;
	short ServerId;
	short FriendNumber;
	short FriendServerId;
};


struct FCHP_CHATROOM_CREATE_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;
	short RoomNumber;
	char Name[10];
	char FriendName[10];
	short Number;
	short ServerId;
	DWORD Ticket;
	DWORD Trash;
	BYTE Type;
};


struct FHP_FRIEND_INVITATION_REQ
{

	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x4>*/ /*|0x2|*/ short Number;
	/*<thisrel this+0x6>*/ /*|0xa|*/ char Name[10];
	/*<thisrel this+0x10>*/ /*|0xa|*/ char FriendName[10];
	/*<thisrel this+0x1a>*/ /*|0x2|*/ unsigned short RoomNumber;
	/*<thisrel this+0x1c>*/ /*|0x4|*/ unsigned long WindowGuid;
};
// <size 0x20>


struct FHP_FRIEND_INVITATION_RET
{
	PBMSG_HEAD h;
	unsigned char Result;	// 3
	short Number;	// 4
	char Name[10];	// 6
	DWORD WindowGuid;	// 10
};


struct FCHP_CHATROOM_INVITATION_REQ
{
	PBMSG_HEAD h;
	short RoomNumber;
	char Name[10];
	short Number;
	short ServerId;
	BYTE Type;
};