#pragma once
// -----------------------------------------------------------------

#include "Sprodef.h"
#include ".\\DbSet\\DBConBase.h"
// -----------------------------------------------------------------

#define MAX_WIN_QUEST		10

#define BYNARY_WINQUEST		1
#define MAX_BYNARYQUEST		280

#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )
#define SET_NUMBERHW(x) ( (WORD)((DWORD)(x)>>(DWORD)16) )
#define SET_NUMBERLW(x) ( (WORD)((DWORD)(x) & 0xFFFF) )

#define MAKE_NUMBERW(x,y)  ( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )
#define MAKE_NUMBERDW(x,y) ( (DWORD)(((WORD)((y)&0xFFFF)) | ((WORD)((x)&0xFFFF)<<16))  )
#define MAKE_NUMBERQW(x,y) ( (unsigned __int64)(((DWORD)((y)&0xFFFFFFFF)) | ((DWORD)((x)&0xFFFFFFFF)<<32))  )

struct GDSelectQuest
{
	PBMSG_HEAD2 h;
	short aIndex;
	char Name[10];
};

struct GDQuestUser
{
	PBMSG_HEAD2 h;	// C1:XX
	char Name[10];
	short Start[MAX_WIN_QUEST];
	short Num[MAX_WIN_QUEST];
	short Count[MAX_WIN_QUEST][5];
	// ----
	int Damage;
	int Defence;
	int Life;
	int SD;
	int Crit;
	int Exel;
	int Double;
	int Ignore;
	int Ref;
	int Exp;
	int Drop;
};

struct DGQuestUserInfo
{
	PBMSG_HEAD2 h;	// C1:XX
	short aIndex;
	char Name[10];
	short Start[MAX_WIN_QUEST];
	short Num[MAX_WIN_QUEST];
	short Count[MAX_WIN_QUEST][5];
	// ----
	int Damage;
	int Defence;
	int Life;
	int SD;
	int Crit;
	int Exel;
	int Double;
	int Ignore;
	int Ref;
	int Exp;
	int Drop;
};

class cWinQuest//: public CDBConBase
{
public:
	cWinQuest();
	virtual ~cWinQuest();

	bool Connect();

	void GetMemberInfo(GDSelectQuest *Recv, int aIndex);
	void UpdateMemberInfo(GDQuestUser *Recv);

	#if(BYNARY_WINQUEST)
	bool ConnectEx();
	void GetMemberInfoEx(GDSelectQuest *Recv, int aIndex);
	void UpdateMemberInfoEx(GDQuestUser *Recv);
	int int_binary(int a, int b, LPBYTE buf);
	int bynary_int(int& a, int b, LPBYTE buf);
	CQuery	m_DBQuery;
	#endif

};
