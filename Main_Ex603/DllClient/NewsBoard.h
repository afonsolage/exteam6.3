#pragma once
// -------------------------------------------------------------------------------
#include "stdafx.h"
#include "Protocol.h"

#if(CUSTOM_NEWS==TRUE)
// -------------------------------------------------------------------------------

#define MAX_NEWS_LIST			12
#define	MIN_NEWS_REFRESH		10
#define	MIN_NEWS_REFRESH_PAGE	60
// -------------------------------------------------------------------------------

#pragma pack(push, 1)
struct NEWS_TITLE
{
	char	Date[12];
	char	Time[7];
	char	Text[70];
};
#pragma pack(pop)
// -------------------------------------------------------------------------------

#pragma pack(push, 1)
struct NEWS_DATA
{
	NEWS_TITLE Title;
	char	Text[1024];		//700
	DWORD	LastRefreshTick;
	int		LastRefreshMin;
};
#pragma pack(pop)
// -------------------------------------------------------------------------------

#pragma pack(push, 1)
struct NEWS_ANS_TITLES
{
	PWMSG_HEAD h;
	BYTE	RealCount;
	NEWS_TITLE Titles[MAX_NEWS_LIST];
};
#pragma pack(pop)
// -------------------------------------------------------------------------------

#pragma pack(push, 1)
struct NEWS_REQ_NEWS
{
	PBMSG_HEAD	h;
	BYTE		ID;
};
#pragma pack(pop)
// -------------------------------------------------------------------------------

#pragma pack(push, 1)
struct NEWS_ANS_NEWS
{
	PWMSG_HEAD h;
	BYTE	ID;
	NEWS_DATA News;
};
#pragma pack(pop)
// -------------------------------------------------------------------------------

class NewsBoard
{
public:
			NewsBoard();
			~NewsBoard();
	// ----
	void	Init(BYTE ID);
	// ----
	void	ReqOpenMain();
	void	OpenMain(NEWS_ANS_TITLES * Answer);
	void	ReqOpenItem(BYTE ID);
	void	OpenItem(NEWS_ANS_NEWS * Answer);
	// ----
	void	DrawNewsWindow();
	bool	EventNewsWindow_Main(DWORD Event);
	// ----
	int		m_LoadedCount;
	NEWS_DATA m_Data[MAX_NEWS_LIST];
	DWORD	m_LastRefreshTick;
	int		m_LastRefreshMin;
};
extern NewsBoard g_NewsBoard;
// -------------------------------------------------------------------------------
#endif