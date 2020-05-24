#pragma once

#include "CQuery.h"

struct strCmp2
{
	bool operator()( const std::string s1, const std::string s2 ) const 
	{
		return strcmp( s1.data(), s2.data() ) < 0;
	}
};


struct NAME
{
	char m_szName[11];
	NAME()
	{
		ZeroMemory(this, sizeof(*this));
	}
	NAME(char *szName)
	{
		ZeroMemory(this, sizeof(*this));
		strncpy(m_szName, szName, 10);
	}
};

typedef struct _FRIEND_MASTER
{
	int m_iGUID;
	int m_iMemoTotal;
	int m_iNumber;
	BYTE m_btState;
	int m_iServer;
	std::vector<NAME> m_vecFriends;

	_FRIEND_MASTER()
	{
		m_iGUID = -1;
		m_iMemoTotal = 0;
		m_iNumber = -1;
		m_btState = -1;
		m_iServer = -1;
		m_vecFriends.clear();
	}
}FRIEND_MASTER, *LPFRIEND_MASTER;

typedef struct _REQUEST_CMD
{
	int m_aIndex;
	BYTE m_btData[1024];
	_REQUEST_CMD()
	{
		ZeroMemory(this, sizeof(*this));
	}
}REQUEST_CMD, *LPREQUEST_CMD;
#pragma pack()

class CFriendSystem
{
public:

	CFriendSystem();
	~CFriendSystem();

	BOOL FriendDBConnect();

	void FriendListRequest(int aIndex, FHP_FRIENDLIST_REQ* lpMsg);
	void FriendStateClientRecv(int aIndex, FHP_FRIEND_STATE_C* lpMsg);
	void FriendAddRequest(int aIndex, FHP_FRIEND_ADD_REQ* lpMsg);
	void WaitFriendAddRequest(int aIndex, FHP_WAITFRIEND_ADD_REQ* lpMsg);
	void FriendDelRequest(int aIndex, FHP_FRIEND_ADD_REQ* lpMsg);

	void FriendMemoSend(int aIndex, FHP_FRIEND_MEMO_SEND* lpMsg);
	void FriendMemoListReq(int aIndex, FHP_FRIEND_MEMO_LIST_REQ *lpMsg);
	void FriendMemoReadReq(int aIndex, FHP_FRIEND_MEMO_RECV_REQ* lpMsg);
	void FriendMemoDelReq(int aIndex, FHP_FRIEND_MEMO_DEL_REQ* lpMsg);

	int ExDBGetIndexByCode(int iServerCode);

	BOOL UserGuidDBCreate(char *szName);
	BOOL GetDBGuidAndMemoTotal(char *szName, int& guid, int& memo_total);
	BOOL GetDBFriendList(char *szMaster);


	BOOL FriendExists(char *szMaster, char *szFriend);
	int GetFriendGuid(char *szMaster);
	BYTE GetFriendState(char *szMaster);
	int GetFriendServer(char *szMaster);
	int GetFriendNumber(char *szMaster);


	void FriendListSend(int aIndex, char *szMaster);

	BOOL GetDBWaitFriend(char *szMaster, OUT char *szWaitFriend);
	BOOL FriendWaitSend(int aIndex, char *szMaster);

	void SendState(int aIndex, char *szMaster, int iNumber, char *szName, BYTE btState);
	void SendStateToAllFriends(int aIndex, char *szMaster);

	BOOL AddFriend(char *szMaster, char *szFriend);
	BOOL DelFriend(char *szMaster, char *szFriend);
	int AddDBWaitFriend(char *szMaster, char *szFriend);
	int DelDBWaitFriend(char *szMaster, char *szFriend);


	int WaitFriendAdd(char *szMaster, char *szFriend);
	BOOL AddDBFriend(char *szMaster, char *szFriend);
	BOOL DelDBFriend(char *szMaster, char *szFriend);

	void FriendClose(int aIndex, LPBYTE lpMsg);

	BOOL CreateFriendMaster(char *szMaster);
	BOOL CreateFriendMaster(char *szMaster, int iNumber, int iServer);
	BOOL DeleteFriendMaster(char *szMaster);

	LPFRIEND_MASTER GetFriendMaster(char *szMaster);

	void MemoHeaderSend(int aIndex, WORD wNumber, MEMO_HEADER * lpMemoHead );
	void MemoListSend(int aIndex, WORD wNumber, char *szName);

	int DBWriteMail(MEMO_SEND_HEADER * lpMemoSendHdr, LPBYTE Photo, BYTE btPhotoSize, char *sMemo, int memo_size);
	int DBReadMail(int iMemoId, int iGuid, MEMO_READ * lpMemoRead, LPDWORD lpdwMemoSize, LPBYTE lpPhoto, LPBYTE lpPhotoSize);
	int DBDelMail(char *szName, int iMemoId);

	CRITICAL_SECTION m_csMapFriendMaster;

private:

	std::map<std::string, FRIEND_MASTER, strCmp2> m_MapFriendManager;
	CQuery m_MailDB;
	CQuery m_FriendDB;
	int m_iMaxFriends;

};
