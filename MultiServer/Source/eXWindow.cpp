#include "stdafx.h"
#include "eXWindow.h"
#include "zMultiServer.h"
#include "Server.h"
// ----------------------------------------------------------------------------------------------

CWindow g_WindowEx;
// ----------------------------------------------------------------------------------------------

CWindow::CWindow()
{
	this->m_WindowID = NULL;
	memset(this->m_WinTitle, 0, sizeof(this->m_WinTitle));
	memset(this->m_WinClass, 0, sizeof(this->m_WinClass));
	this->m_MenuID = NULL;
	this->m_StatusID = NULL;
	this->m_Instance = NULL;
	this->m_BrushDrakGray = NULL;
	this->m_FontName = NULL;
	this->m_FontLog = NULL;
	int m_CountLog = 0;
	memset(this->m_Log, 0, sizeof(this->m_Log));
}
// ----------------------------------------------------------------------------------------------

CWindow::~CWindow()
{
	this->CloseTray();
}
// ----------------------------------------------------------------------------------------------

void CWindow::Load()
{
	memcpy(this->m_WinTitle, WINDOW_TITLE, strlen(WINDOW_TITLE));
	memcpy(this->m_WinClass, WINDOW_CLASS, strlen(WINDOW_CLASS));

	this->m_BrushDrakGray = CreateSolidBrush(RGB(30, 30, 30));

	this->m_FontName = CreateFont(40, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Times");

	this->m_FontLog = CreateFont(15, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Tahoma");
}
// ----------------------------------------------------------------------------------------------

int CWindow::CreateMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	this->Load();

	WNDCLASSEX wcex		= { 0 };
	wcex.cbSize			= sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)WINDOW_ICO_ID);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)this->m_BrushDrakGray;
	wcex.lpszMenuName	= this->m_WinTitle;
	wcex.lpszClassName	= this->m_WinClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON2);
	RegisterClassEx(&wcex);

	this->m_Instance = hInstance;

	this->m_WindowID = CreateWindowEx(0, this->m_WinClass, this->m_WinTitle, 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2, 
		WINDOW_WIDTH, WINDOW_HEIGHT, 
		NULL, NULL, hInstance, NULL);

	if(!this->m_WindowID)
	{
		return 0;
	}

	ShowWindow(this->m_WindowID, nCmdShow);
	UpdateWindow(this->m_WindowID);

	this->CreateSystemMenu();
	this->CreateStatusBar();
	this->CreateTray();
	this->CreateTimer();

	ServersInit();

	this->Paint();

	MSG msg;

	HACCEL hAccelTable = LoadAccelerators(hInstance, (LPCSTR)WINDOW_ACCELERATOR);

	while(GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
		    TranslateMessage(&msg);
		    DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}
// ----------------------------------------------------------------------------------------------

void CWindow::CloseMain()
{
	if(MessageBox(this->m_WindowID, "Close?", this->m_WinTitle, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		return;
	}

	if(this->m_FontName != NULL)
	{
		DeleteObject(this->m_FontName);
	}

	if(this->m_FontLog != NULL)
	{
		DeleteObject(this->m_FontLog);
	}

	DestroyWindow(this->m_WindowID);
}
// ----------------------------------------------------------------------------------------------

bool CWindow::CreateSystemMenu()
{
    HMENU hMenubar = CreateMenu();
    HMENU hMenu = CreateMenu();
	HMENU hMenu2 = CreateMenu();
	HMENU hMenu3 = CreateMenu();

	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR) hMenu, "File");
    AppendMenu(hMenu, MF_STRING, WM_MENU_EXIT, "Exit");

	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR) hMenu2, "Reload");
    AppendMenu(hMenu2, MF_SEPARATOR, 0, NULL);
    AppendMenu(hMenu2, MF_STRING, WM_MENU_RELOAD, "Option");

  	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR) hMenu3, "Help");
	AppendMenu(hMenu3, MF_STRING, WM_MENU_ABOUT, "About");

	SetMenu(this->m_WindowID, hMenubar);

	return true;
}
// ----------------------------------------------------------------------------------------------

bool CWindow::CreateStatusBar()
{
    InitCommonControls();

	this->m_StatusID = CreateStatusWindowA(WS_CHILD | WS_VISIBLE, NULL, this->m_WindowID, 0); 

	if(!this->m_StatusID)
	{
		return false;
	}
 
	RECT rcClient;
    GetClientRect(this->m_WindowID, &rcClient);
 
	int pParts[STATUS_MAXCOLUMN];  
	int nWidth = rcClient.right / STATUS_MAXCOLUMN;
	int rightEdge = nWidth;

    for(int i = 0; i < STATUS_MAXCOLUMN; i++) 
	{ 
       pParts[i] = rightEdge;
       rightEdge += nWidth;
    }

	SendMessage(this->m_StatusID, SB_SETPARTS, STATUS_MAXCOLUMN, (LPARAM)pParts);

    UpdateWindow(this->m_StatusID);

    return true;
}   
// ----------------------------------------------------------------------------------------------

void CWindow::UpdateStatusBar(int Column, char* Text, ...)
{
	if(!this->m_StatusID)
	{
		return;
	}

	char szArg[512] = { 0 };

	va_list pArguments;
	va_start(pArguments, Text);
	vsprintf_s(szArg , Text , pArguments);
	va_end(pArguments);

	SendMessage(this->m_StatusID, SB_SETTEXT, Column, (LPARAM)szArg); 

    UpdateWindow(this->m_StatusID);
}
// ----------------------------------------------------------------------------------------------

void CWindow::CreateTimer()
{
	SetTimer(this->m_WindowID, WM_TIMER_PAINT, 2000, NULL);
}
// ----------------------------------------------------------------------------------------------

void CWindow::CreateTray()
{
#if(ENABLE_WINDOW_TRAY)

	NOTIFYICONDATA Icon		= { 0 };
	Icon.cbSize				= sizeof(NOTIFYICONDATA);
	Icon.uID				= WINDOW_ICO_ID;
	Icon.uFlags				= NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	Icon.hIcon				= LoadIcon(this->m_Instance, (LPCTSTR)WINDOW_ICO_ID);
	Icon.hWnd				= this->m_WindowID;
	Icon.uCallbackMessage	= WM_TRAY_ICON_MSG;
	Icon.dwInfoFlags		= NIIF_INFO;

	_snprintf_s(Icon.szTip, sizeof(Icon.szTip)-1, "%s", WINDOW_TITLE);

	Shell_NotifyIcon(NIM_ADD, &Icon);

#endif
}
// ----------------------------------------------------------------------------------------------

void CWindow::CloseTray()
{
#if(ENABLE_WINDOW_TRAY)

	NOTIFYICONDATA Icon		= { 0 };
	Icon.cbSize				= sizeof(NOTIFYICONDATA);
	Icon.uID				= WINDOW_ICO_ID;
	Icon.uFlags				= NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	Icon.hIcon				= LoadIcon(this->m_Instance, (LPCTSTR)WINDOW_ICO_ID);
	Icon.hWnd				= this->m_WindowID;
	Icon.uCallbackMessage	= WM_TRAY_ICON_MSG;
	Icon.dwInfoFlags		= NIIF_INFO;

	Shell_NotifyIcon(NIM_DELETE, &Icon);

#endif
}
// ----------------------------------------------------------------------------------------------

void CWindow::CreateTrayMenu()
{
#if(ENABLE_WINDOW_TRAY)

	POINT pt;
	GetCursorPos(&pt);
	HMENU hPopMenu = CreatePopupMenu();

	InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, WM_TRAY_ABOUT, "About");
	InsertMenu(hPopMenu, 0xFFFFFFFF, MF_SEPARATOR, WM_TRAY_SEP, "SEP");				
	InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, WM_TRAY_EXIT, "Exit");			

	SetForegroundWindow(this->m_WindowID);
	TrackPopupMenu(hPopMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, pt.x, pt.y, 0, this->m_WindowID, NULL);
	DestroyMenu(hPopMenu);

#endif
}
// ----------------------------------------------------------------------------------------------

void CWindow::SwitchStateTray()
{
#if(ENABLE_WINDOW_TRAY)

	if(IsWindowVisible(this->m_WindowID))
	{
		ShowWindow(this->m_WindowID, SW_HIDE);
		UpdateWindow(this->m_WindowID);
	}
	else
	{
		ShowWindow(this->m_WindowID, SW_SHOW);
		UpdateWindow(this->m_WindowID);
		this->Paint();
	}

#endif
}
// ----------------------------------------------------------------------------------------------

void CWindow::MessageTray(DWORD Type, char* Title, char* Message, DWORD TimeOut)
{
#if(ENABLE_WINDOW_TRAY)

	NOTIFYICONDATA nIcon = { 0 };

	nIcon.cbSize			= sizeof(nIcon);
	nIcon.uID				= WINDOW_ICO_ID;
	nIcon.hWnd				= this->m_WindowID;
	nIcon.uFlags			= NIF_ICON | NIF_MESSAGE | NIF_INFO;
	nIcon.hIcon				= LoadIcon(this->m_Instance, (LPCTSTR)WINDOW_ICO_ID);
	nIcon.uCallbackMessage	= WM_TRAY_ICON_MSG;
	nIcon.dwInfoFlags		= Type;
	nIcon.uTimeout			= TimeOut;

	memset(nIcon.szInfoTitle, 0, sizeof(nIcon.szInfoTitle));
	memset(nIcon.szInfo, 0, sizeof(nIcon.szInfo));

	memcpy(nIcon.szInfoTitle, Title, sizeof(nIcon.szInfoTitle)-1);
	memcpy(nIcon.szInfo, Message, sizeof(nIcon.szInfo)-1);

	Shell_NotifyIcon(NIM_MODIFY, &nIcon);

#endif
}
// ----------------------------------------------------------------------------------------------

void CWindow::Paint()
{
	RECT rect;
	GetClientRect(this->m_WindowID, &rect);
	rect.bottom -= 20;
	HDC hdc = GetDC(this->m_WindowID);

	FillRect(hdc, &rect, this->m_BrushDrakGray);

	// -> info

	int iOldBkMode = SetBkMode(hdc, TRANSPARENT);
	HFONT pOldFont = (HFONT)SelectObject(hdc, this->m_FontName);

	SetTextColor(hdc, RGB(33, 200, 219));
	char AppName[] = PAINT_TITLE;
	TextOut(hdc, 70, 3, AppName, strlen(AppName));	//120

	// -> log

	iOldBkMode = SetBkMode(hdc, TRANSPARENT);
	pOldFont = (HFONT)SelectObject(hdc, this->m_FontLog);

	int n = this->m_CountLog;
	int total = LOG_TEXT_LINE_MAX;

	while(total-- != 0)
	{
		switch(this->m_Log[n].Color)
		{
			case LOG_WHITE:
				SetTextColor(hdc, RGB(200, 200, 200));
				break;
			case LOG_RED:
				SetTextColor(hdc, RGB(180, 30, 30));
				break;
			case LOG_GREEN:
				SetTextColor(hdc, RGB(20, 154, 60));
				break;
			case LOG_BLUE:
				SetTextColor(hdc, RGB(60, 90, 200));
				break;
			case LOG_ORANGE:
				SetTextColor(hdc, RGB(180, 127, 0));
				break;
			default:
				SetTextColor(hdc, RGB(128, 170, 187));
				break;
		}

		if(strlen(this->m_Log[n].Text) > 1)
		{
			TextOut(hdc, 5, total * 15 + 50, this->m_Log[n].Text, strlen(this->m_Log[n].Text)); 
		}

		n--;

		if(n < 0)
		{
			n = LOG_TEXT_LINE_MAX-1;
		}
	}

	SelectObject(hdc, pOldFont);
	SetBkMode(hdc, iOldBkMode);

	// -> end

	ReleaseDC(this->m_WindowID, hdc);
}
// ----------------------------------------------------------------------------------------------

void CWindow::LogAdd(int Color, char* Text, ...)
{
	char szArg[4096] = { 0 };
	char szText[4096] = { 0 };
	SYSTEMTIME Time;
	GetLocalTime(&Time);

	va_list pArguments;
	va_start(pArguments, Text);
	vsprintf_s(szArg , Text , pArguments);
	va_end(pArguments);

	sprintf_s(szText , "[%02d:%02d:%02d] %s", Time.wHour, Time.wMinute, Time.wSecond, szArg);

	int Size = strlen(szText);

	if(Size >= LOG_TEXT_SIZE_MAX)
	{
		Size = LOG_TEXT_SIZE_MAX - 1;
	}

	this->m_CountLog++;

	if(this->m_CountLog >= LOG_TEXT_LINE_MAX)
	{
		this->m_CountLog = 0;
	}

	this->m_Log[this->m_CountLog].Color = Color;
	memset(this->m_Log[this->m_CountLog].Text, 0, sizeof(this->m_Log[this->m_CountLog].Text));
	memcpy(this->m_Log[this->m_CountLog].Text, szText, Size);
}
// ----------------------------------------------------------------------------------------------

LRESULT CWindow::ProcessMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_COMMAND:
			switch(wParam)
			{
			case WM_TRAY_ABOUT:
				// ----
				break;
			case WM_TRAY_EXIT:
				this->CloseMain();
				break;
			case WM_MENU_RELOAD:
				
				break;
			}
			break;
			// --
		case WM_TIMER:
			switch(wParam)
			{
			case WM_TIMER_PAINT:
				this->Paint();
				break;
			}
			break;
			// --
		case WM_TRAY_ICON_MSG:
			switch(lParam)
			{
			case WM_LBUTTONDBLCLK:
				this->SwitchStateTray();
				break;
			case WM_RBUTTONDOWN:
				this->CreateTrayMenu();
				break;
			}
			break;
			// --
		case WM_CLOSE:
			this->CloseMain();
			break;
			// --
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
			// --
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	// --
	return false;
}
// ----------------------------------------------------------------------------------------------

