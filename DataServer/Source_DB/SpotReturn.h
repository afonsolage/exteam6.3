#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "protocol.h"
#include "./DbSet/DBConBase.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_RETURNSPOT==TRUE)
// ----------------------------------------------------------------------------------------------

struct PMSG_GD_SPOTSTATUS
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	WORD Number;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_DG_SPOTSTATUS
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	WORD Number;
	BYTE GetStatus;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_GD_SPOTSTATUS_UPDATE
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	BYTE GetStatus;
};
// ----------------------------------------------------------------------------------------------

class SpotReturn
{
public:
	SpotReturn();
	~SpotReturn();

	bool Connect();

	void GDStatus(PMSG_GD_SPOTSTATUS* lpMsg, int pIndex);
	void GDStatusUpdate(PMSG_GD_SPOTSTATUS_UPDATE* lpMsg);

	CQuery m_DBQuery;
};
// ----------------------------------------------------------------------------------------------
extern SpotReturn g_SpotReturn;
// ----------------------------------------------------------------------------------------------
#endif