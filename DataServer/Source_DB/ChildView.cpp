// ChildView.cpp : implementation of the CChildView class
// Decompilation Completed -> All Same as WebZen

#include "stdafx.h"
#include "DataServer.h"
#include "ChildView.h"
#include "giocp.h"
#include "MainFrm.h"
#include "ServerManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView


CChildView::CChildView()
{
	
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}
#if(NEW_WIN)
static char * StatusMsg[2] = 
{
	"Standy mode",
	"Active mode",
};
static char * DeveloperMessage[2] = 
{
	"Royal Network",
	"https://royalnetwork.org"
};
char chText[256];
#endif

void CChildView::OnPaint()
{
#if(NEW_WIN)

	RECT rect;
	CBrush bk(COLORREF(RGB(30,30,30)));
	CPaintDC dc(this);
	GetClientRect(&rect);
	dc.SelectObject(&bk);
	dc.FillRect(&rect, &bk); 
	LogTextPaint(m_hWnd);
	char chText[256] = "";
	dc.SetBkMode(TRANSPARENT);
	
	int infoX = 50;
	int infoY = 65;

	dc.SetTextColor(RGB(123, 123, 250));
	dc.TextOutA(infoX, infoY, m_szQueueSizeText);
	infoX += 130;
	dc.TextOutA(infoX, infoY, m_szQueueSizeText2);
	infoX += 130;
	dc.TextOutA(infoX, infoY, m_szQueueSizeText3);
	infoX += 130;
	dc.TextOutA(infoX, infoY, m_szQueueSizeText4);
	infoX += 130;
	dc.TextOutA(infoX, infoY, m_szQueueSizeText5);

	dc.SetTextColor(RGB(0, 255, 0));
	infoX = 50 + 95;
	dc.TextOutA(infoX, infoY, m_szQueueSizeNum);
	infoX += 130;
	dc.TextOutA(infoX, infoY, m_szQueueSizeNum2);
	infoX += 130;
	dc.TextOutA(infoX, infoY, m_szQueueSizeNum3);
	infoX += 130;
	dc.TextOutA(infoX, infoY, m_szQueueSizeNum4);
	infoX += 130;
	dc.TextOutA(infoX, infoY, m_szQueueSizeNum5);

	infoX = 10;
	infoY = 400;
	sprintf(chText, "DNS: [%s] :: Port: [%d] :: Connected: [%d]", szDbConnectDsn, g_DSPort, g_DSConnected); 
	dc.SetTextColor(RGB(245, 237, 88));
	dc.TextOutA(infoX, infoY, chText);

	infoX = 605;
	infoY = 5;
	dc.SetTextColor(RGB(255, 255, 255));
	dc.TextOutA(infoX, infoY, DeveloperMessage[0]);
	infoY = 20;
	dc.TextOutA(infoX, infoY, DeveloperMessage[1]);

	infoX = 440;
	infoY = 400;
	dc.SetTextColor(RGB(123, 123, 250));
	dc.TextOutA(infoX, infoY, "Game Server:");

	infoX += 95;

#if(ENABLE_SOCKET_MANAGER)
	if(gServerCount >= 1)
#else
	if(g_DSConnected >= 1) 
#endif
	{
		dc.SetTextColor(RGB(0, 255,0));
		dc.TextOutA(infoX, infoY, "Online");
	}
	else
	{
		dc.SetTextColor(RGB(255, 0,0));
		dc.TextOutA(infoX, infoY, "Offline");
	}

	infoX += 60;
	dc.SetTextColor(RGB(123, 123, 250));
	dc.TextOutA(infoX, infoY, "Status:");

	infoX += 51;
	if(cAM.GetMode()==AM_ACTIVE)
	{
		dc.SetTextColor(RGB(0, 255,0));
		dc.TextOutA(infoX, infoY, StatusMsg[1]);
	}
	else
	{
		dc.SetTextColor(RGB(130, 170, 190));
		dc.TextOutA(infoX, infoY, StatusMsg[0]);
	}

	CFont fnBold;
	HFONT pOldFont = 0;
	TEXTMETRICA tm;
	LOGFONT lf;
	CString strFont;
	memset(&lf, 0, sizeof(lf));
	dc.GetTextMetrics(&tm);
	lf.lfHeight = 50;
	lf.lfWeight = 0;
	lf.lfUnderline = 0;
	strncpy(lf.lfFaceName, "Times", sizeof(lf.lfFaceName));
	fnBold.CreateFontIndirect(&lf);
	pOldFont = (HFONT)dc.SelectObject(&fnBold);
	CRect rcText;
	GetClientRect(&rcText);

	infoX = 150;
	infoY = 5;
	dc.SetTextColor(RGB(33, 200, 219) );
	dc.TextOutA(infoX, infoY, "Data Server");

#else

	RECT rect;
	CBrush bk(GetSysColor(COLOR_WINDOW));
	CPaintDC dc(this);
	GetClientRect(&rect);
	dc.SelectObject(&bk);
	dc.FillRect(&rect, &bk);
	LogTextPaint(m_hWnd);
	char tmpQueueSizeTxt[256] = "";
	wsprintf(tmpQueueSizeTxt, m_szQueueSizeText);
	strcat(tmpQueueSizeTxt, m_szQueueSizeText2);
	strcat(tmpQueueSizeTxt, m_szQueueSizeText3);
	strcat(tmpQueueSizeTxt, m_szQueueSizeText4);
	dc.TextOut(20, 50, tmpQueueSizeTxt);

	CFont fnBold;
	HFONT pOldFont = 0;
	TEXTMETRICA tm;
	LOGFONT lf;
	CString strFont;
	memset(&lf, 0, sizeof(lf));
	dc.GetTextMetrics(&tm);
	lf.lfHeight = 50;
	lf.lfWeight = 0;
	lf.lfUnderline = 0;
	strncpy(lf.lfFaceName, "Times", sizeof(lf.lfFaceName));
	fnBold.CreateFontIndirect(&lf);
	pOldFont = (HFONT)dc.SelectObject(&fnBold);
	CRect rcText;
	GetClientRect(&rcText);

	dc.SetBkMode(TRANSPARENT);
	if(cAM.GetMode() == AM_ACTIVE)
	{
		dc.FillSolidRect(0, 0, rcText.right, 50, RGB(110, 250, 120));
		dc.SetTextColor( RGB(250, 250, 250) );
		dc.DrawText("ACTIVE MODE", -1, (LPRECT)rcText, 5);
	}
	else
	{
		dc.FillSolidRect(0, 0, rcText.right, 50, RGB(100, 100, 100));
		dc.SetTextColor( RGB(190, 190, 190) );
		dc.DrawText("STANDBY MODE", -1, (LPRECT)rcText, 5);
	}

#endif
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch( nIDEvent )
	{
	case 1001 :
		{
			ShowDbQueueSize();
		}
		//LogTextPaint(m_hWnd);
		break;
	}
	CWnd ::OnTimer(nIDEvent);
}

void CChildView::ShowDbQueueSize()
{
#if(NEW_WIN)

  wsprintfA(m_szQueueSizeText,  "Queue1 Size:");
  wsprintfA(m_szQueueSizeText2, "Queue2 Size:");
  wsprintfA(m_szQueueSizeText3, "Queue3 Size:");
  wsprintfA(m_szQueueSizeText4, "Queue4 Size:");
  #if(THREAD_FIFTH)
  wsprintfA(m_szQueueSizeText5, "Queue5 Size:");
  #endif

  wsprintfA(m_szQueueSizeNum,  "%d", WzRecvQ.GetCount_NoLock());
  wsprintfA(m_szQueueSizeNum2, "%d", WzRecvQ2.GetCount_NoLock());
  wsprintfA(m_szQueueSizeNum3, "%d", WzRecvQ3.GetCount_NoLock());
  wsprintfA(m_szQueueSizeNum4, "%d", WzRecvQ4.GetCount_NoLock());
  #if(THREAD_FIFTH)
  wsprintfA(m_szQueueSizeNum5, "%d", WzRecvQ5.GetCount_NoLock());
  #endif
#else
  wsprintfA(m_szQueueSizeText, "[Q1 Size : %d], ", WzRecvQ.GetCount_NoLock());
  wsprintfA(m_szQueueSizeText2, "[Q2 Size : %d], ", WzRecvQ2.GetCount_NoLock());
  wsprintfA(m_szQueueSizeText3, "[Q3(serial) Size : %d] ", WzRecvQ3.GetCount_NoLock());
  wsprintfA(m_szQueueSizeText4, "[Q4 Size : %d] ", WzRecvQ4.GetCount_NoLock());
#endif
  Invalidate(FALSE);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetTimer(1001, 1000, NULL);

	memset(m_szQueueSizeText, 0, sizeof(m_szQueueSizeText));
	memset(m_szQueueSizeText2, 0, sizeof(m_szQueueSizeText2));
	memset(m_szQueueSizeText3, 0, sizeof(m_szQueueSizeText3));
	memset(m_szQueueSizeText4, 0, sizeof(m_szQueueSizeText4));
	#if(THREAD_FIFTH)
	memset(m_szQueueSizeText5, 0, sizeof(m_szQueueSizeText5));
	#endif
#if(NEW_WIN)
	memset(m_szQueueSizeNum, 0, sizeof(m_szQueueSizeNum));
	memset(m_szQueueSizeNum2, 0, sizeof(m_szQueueSizeNum2));
	memset(m_szQueueSizeNum3, 0, sizeof(m_szQueueSizeNum3));
	memset(m_szQueueSizeNum4, 0, sizeof(m_szQueueSizeNum4));
	#if(THREAD_FIFTH)
	memset(m_szQueueSizeNum5, 0, sizeof(m_szQueueSizeNum5));
	#endif
#endif
	return 0;
}
