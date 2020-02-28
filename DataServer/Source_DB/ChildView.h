// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__D67B35A0_6AD1_4F70_8530_D0DC7939A9F1__INCLUDED_)
#define AFX_CHILDVIEW_H__D67B35A0_6AD1_4F70_8530_D0DC7939A9F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildView();

	char m_szQueueSizeText[64];
	char m_szQueueSizeText2[64];
	char m_szQueueSizeText3[64];
	char m_szQueueSizeText4[64];
	#if(THREAD_FIFTH)
	char m_szQueueSizeText5[64];
	#endif
#if(NEW_WIN)
	char m_szQueueSizeNum[32];
	char m_szQueueSizeNum2[32];
	char m_szQueueSizeNum3[32];
	char m_szQueueSizeNum4[32];
	#if(THREAD_FIFTH)
	char m_szQueueSizeNum5[32];
	#endif
#endif
	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void ShowDbQueueSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__D67B35A0_6AD1_4F70_8530_D0DC7939A9F1__INCLUDED_)
