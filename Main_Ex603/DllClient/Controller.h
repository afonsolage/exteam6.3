#pragma once
// ----------------------------------------------------------------------------------------------

#include "Protocol.h"

#define VK_0 	0x30 //	0 key
#define VK_1 	0x31 //	1 key
#define VK_2 	0x32 //	2 key
#define VK_3 	0x33 // 3 key
#define VK_4 	0x34 //	4 key
#define VK_5 	0x35 //	5 key
#define VK_6 	0x36 //	6 key
#define VK_7 	0x37 //	7 key
#define VK_8 	0x38 //	8 key
#define VK_9 	0x39 //	9 key 
// ----------------------------------------------------------------------------------------------

#define UPDATE_KB		FALSE

#if(ADD_CTRL_KEY)
struct PMSG_CONTROLLER_CTRL
{
	PBMSG_HEAD2 h;
	BYTE CtrlKey;
};
#endif

class Controller
{
public:
	bool	Load();
	// ----
	static	LRESULT WINAPI Mouse(int Code, WPARAM wParam, LPARAM lParam);
	static	LRESULT WINAPI Keyboard(int Code, WPARAM wParam, LPARAM lParam);
	static	LRESULT WINAPI Window(HWND Window, DWORD Message, WPARAM wParam, LPARAM lParam);
	static  LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// ----
	HINSTANCE	Instance;
	// ----
	WPARAM wMouse;
	WPARAM wKeyBord;
	// ----
#if(CUSTOM_EMULATOR_KEY)
	void ThreadhMouseAutoKey();
	bool m_AutoMouseLeft;
	bool m_AutoMouseRight;
#endif
#if(ADD_CTRL_KEY)
	void		CGCtrlKey();
	bool		CtrlKey;
#endif
private:
	HHOOK		MouseHook;
	HHOOK		KeyboardHook;
	// ----
}; extern Controller gController;
// ----------------------------------------------------------------------------------------------