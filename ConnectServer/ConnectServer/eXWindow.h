#pragma once
// ----------------------------------------------------------------------------------------------

#define ENABLE_WINDOW_MENU		TRUE
#define ENABLE_WINDOW_STATUS	TRUE
#define ENABLE_WINDOW_TRAY		FALSE
// ----------------------------------------------------------------------------------------------

#define WINDOW_TITLE			"Connect Server"
#define WINDOW_CLASS			"ConnectServerClass"
#define PAINT_TITLE				"[- Connect Server -]"
#define WINDOW_WIDTH			600	//650
#define WINDOW_HEIGHT			350	//420	//350
#define STATUS_MAXCOLUMN		4

#define WINDOW_ICO_ID			IDI_SMALL//	IDC_MYICON
#define WINDOW_ACCELERATOR		NULL
#define WM_TIMER_PAINT			0x30
#define WM_TIMER_UPDATE			0x31
#define WM_MENU_EXIT			0x11
#define WM_MENU_RELOAD			0x12
#define WM_MENU_ABOUT			0x13
#define WM_TRAY_ICON_MSG		0x4A1
#define WM_TRAY_EXIT			0x4A2
#define WM_TRAY_ABOUT			0x4A3
#define WM_TRAY_SEP				0x4A4

#define LOG_TEXT_LINE_MAX		15
#define LOG_TEXT_SIZE_MAX		100
// ----------------------------------------------------------------------------------------------

enum eLogColor
{
	LOG_DEFAULT = 0,
	LOG_WHITE	= 1,
	LOG_RED		= 2,
	LOG_GREEN	= 3,
	LOG_BLUE	= 4,
	LOG_ORANGE	= 5,
};
// ----------------------------------------------------------------------------------------------

struct LOG_DISPLAY_INFO
{
	int Color;
	char Text[LOG_TEXT_SIZE_MAX];
};
// ----------------------------------------------------------------------------------------------

class CWindow
{
public:
		CWindow();
		~CWindow();

	void Load();
	int CreateMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	void CloseMain();
	bool CreateSystemMenu();
	bool CreateStatusBar();
	void UpdateStatusBar(int Column, char* Text, ...);
	void PaintInfoStatusBar();
	void CreateTimer();
	void CreateTray();
	void CloseTray();
	void CreateTrayMenu();
	void SwitchStateTray();
	void MessageTray(DWORD Type, char* Title, char* Message, DWORD TimeOut);
	void Paint();
	void UpdateInfo();
	void LogAdd(int Color, char* Text, ...);
	void SetTitle(HWND Window, char * Text, ...);
	LRESULT ProcessMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND m_WindowID;
	HINSTANCE m_Instance;

private:
	char m_WinTitle[128];
	char m_WinClass[128];
	HWND m_MenuID;
	HWND m_StatusID;	
	HBRUSH m_BrushDrakGray;
	HFONT m_FontName;
	HFONT m_FontLog;
	int m_CountLog;
	LOG_DISPLAY_INFO m_Log[LOG_TEXT_LINE_MAX];
};
// ----------------------------------------------------------------------------------------------

extern CWindow g_WindowEx;
// ----------------------------------------------------------------------------------------------


BOOL CALLBACK ProcessAbout(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);