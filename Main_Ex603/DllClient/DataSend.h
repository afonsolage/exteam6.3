#pragma once
#include "Protocol.h"

struct OFFLINEATTACK_REQ
{
	PBMSG_HEAD2 h;
	BYTE		Result;
};

struct CG_AUTOPARTYLIST
{
	PBMSG_HEAD2 h;
	BYTE		Result;
};

struct CG_MINIMAP_PARTY
{
	PBMSG_HEAD2 h;
	BYTE MiniMap;
};

class cDataSend
{
public:
	void SendOfflineAttack();
	void SendOpenAutoPartyList();
	void SendConfig();


};
extern cDataSend gDataSend;