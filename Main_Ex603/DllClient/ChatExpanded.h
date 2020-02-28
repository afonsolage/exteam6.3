#pragma once
// ----------------------------------------------------------------------------------------------

#include "Protocol.h"
#include "Import.h"
// ----------------------------------------------------------------------------------------------

const int NewCall				= oNewCall;
const int FixSysMsg1_Hook		= oFixSysMsg1_Hook;   
const int FixSysMsg1_FALSE		= oFixSysMsg1_Hook+5; 
const int FixSysMsg1_TRUE		= oFixSysMsg1_TRUE;
const int FixSysMsg2_Hook		= oFixSysMsg2_Hook;
const int FixSysMsg2_FALSE		= oFixSysMsg2_Hook+5; 
const int FixSysMsg2_TRUE		= oFixSysMsg2_TRUE;
const int FixSysMsg3_Hook		= oFixSysMsg3_Hook;
const int FixSysMsg3_FALSE		= oFixSysMsg3_Hook+5; 
const int FixSysMsg3_TRUE		= oFixSysMsg3_TRUE; 

// ----------------------------------------------------------------------------------------------

#define MAX_CHAT_TYPE	10
// ----------------------------------------------------------------------------------------------

namespace MUChatTypeName
{
	enum T
	{
		Default		= 0,
		TalkNormal	= 1,
		Info		= 2,
		SystemInfo	= 3,
		Warning		= 4,
		Party		= 5,
		Guild		= 6,
		Alliance	= 7,
		TalkGM		= 8,
		Gens		= 9,
	};
};
// ----------------------------------------------------------------------------------------------

//9867090 - структура чата ?

struct MUChatType	//-> 24
{
/*+12*/	DWORD	Unknown12;
/*+16*/	DWORD	Unknown16;
/*+20*/	DWORD	Unknown20;
};
// ----------------------------------------------------------------------------------------------

class MUChat
{
/*+4*/		DWORD	Unknown4;
/*+12*/		DWORD	Unknown12;
/*+16*/		MUChatType ChatType[MAX_CHAT_TYPE];
/*+256*/	bool	IsActiveChatType[MAX_CHAT_TYPE];
/*+268*/	//SomeType LPVOID;
/*+292*/	DWORD	Unknown292;
/*+296*/	DWORD	WindowPosY;
/*+300*/	DWORD	Unknown300;
/*+304*/	DWORD	Unknown304;
/*+308*/	DWORD	Unknown308;
/*+312*/	DWORD	WindowHeight;
/*+316*/	DWORD	WindowLineCount;
/*+320*/	DWORD	MessageType;
/*+324*/	BYTE	Unknown324;
/*+328*/	DWORD	WindowScrollPos;
/*+336*/	float	Unknown336;
/*+340*/	DWORD	Unknown340;
/*+344*/	BYTE	Unknown344;
/*+345*/	BYTE	Unknown345;
/*+348*/	DWORD	Unknown348;
};
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct CHAT_WHISPER_EX
{
	PBMSG_HEAD	Head;
	char		Name[10];
	char		Message[90];
	BYTE		Type;
};
#pragma pack(pop)

#define MAX_CHAT_LEN 89

struct PMSG_CHATDATA
{
	PBMSG_HEAD h;	//	
	char chatid[10];	//	3
	char chatmsg[MAX_CHAT_LEN];	//	D
};

struct PMSG_CHATDATA_WHISPER
{
	PBMSG_HEAD h;	// C1:02
	char id[10];	// 3
	char chatmsg[MAX_CHAT_LEN];	// D  
};
// ----------------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------------

class ChatExpanded
{
public:
	static bool ShowChatMessage(LPVOID This, LPVOID EDX);
	static void WhisperChatRecv(CHAT_WHISPER_EX * pRequest);
	void GCChatData(PMSG_CHATDATA* Recv);
	void GCChatDataPrivate(PMSG_CHATDATA_WHISPER * Recv);
	// ----
	void	Load();
	// ----
	void	SetInstance(LPVOID Instance);	
	void	Restore();
	void	Switch();
	// ----
	void	SetPosY(DWORD PosY)				{ *(DWORD*)((int)this->Instance + 296) = PosY; };
	DWORD	GetPosY()						{ return *(DWORD*)((int)this->Instance + 296); };
	void	SetHeight(DWORD Height)			{ *(DWORD*)((int)this->Instance + 312) = Height; };
	DWORD	GetHeight()						{ return *(DWORD*)((int)this->Instance + 312); };
	void	SetMessageCount(DWORD Count)	{ *(DWORD*)((int)this->Instance + 316) = Count; };
	DWORD	GetMessageCount()				{ return *(DWORD*)((int)this->Instance + 316); };
	void	SetMessageType(DWORD Type)		{ *(DWORD*)((int)this->Instance + 320) = Type; };
	DWORD	GetMessageType()				{ return *(DWORD*)((int)this->Instance + 320); };
	void	SetScrollPos(DWORD Pos)			{ *(DWORD*)((int)this->Instance + 328) = Pos; };
	DWORD	GetScrollPos()					{ return *(DWORD*)((int)this->Instance + 328); };
	// ----
public:
	LPVOID	Instance;
	DWORD	PosYBuff;
	DWORD	HeightBuff;
	DWORD	MessageCountBuff;
	DWORD	MessageTypeBuff;
	DWORD	ScrollPosBuff;
	bool	IsActive;
	// ----
	HFONT	m_hFont;
	// ----
	void	LoadChatEx();
}; extern ChatExpanded gChatExpanded;
// ----------------------------------------------------------------------------------------------