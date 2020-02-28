#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "..\\common\winutil.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_RETURNSPOT==TRUE)
// ----------------------------------------------------------------------------------------------

#define STATUSMAXTIME	20
// ----------------------------------------------------------------------------------------------

enum eSpotReturn
{
	eStatusNormal = 0,
	eStatusKill   = 1,
	eStatusKlick  = 2,
};
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

	void Init();
	void Load();
	void Read(char* File);

	void StatusTime();
	void GDStatus(int aUserIndex);
	void DGStatus(PMSG_DG_SPOTSTATUS* lpMsg);
	void GDStatusUpdate(int aIndex, BYTE eStatus);
	void StatusSave(int aUserIndex);

	bool Enable;
	int CheckTimeStatus;

};
// ----------------------------------------------------------------------------------------------
extern SpotReturn g_SpotReturn;
// ----------------------------------------------------------------------------------------------

#endif