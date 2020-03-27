#include "stdafx.h"
#include "TrayMode.h"
#include "Other.h"
#include "Controller.h"
#include "TMemory.h"
#include "resource.h"
#include "User.h"
#include "Graphics.h"

// ----------------------------------------------------------------------------------------------

TrayMode gTrayMode;
// ----------------------------------------------------------------------------------------------

void TrayMode::Load()
{
	this->TempWindowProc	= NULL;
	this->TempIconProc		= NULL;
	this->InTray			= false;
}
// ----------------------------------------------------------------------------------------------

bool prevGlowState = false;
void TrayMode::SwitchState()
{
	if (!gObjUser.IsVIP()) return;

	if( IsWindowVisible(pGameWindow) )
	{
		ShowWindow(pGameWindow, SW_HIDE);
		UpdateWindow(pGameWindow);
		this->ShowNotify(true);
		this->ShowMessage(NIIF_INFO, 500, "LC MU Online", "Minimized");
		prevGlowState = g_bGlowGraphic;
		g_bGlowGraphic = false;
	}
	else
	{
		ShowWindow(pGameWindow, SW_SHOW);
		UpdateWindow(pGameWindow);
		this->ShowNotify(false);
		g_bGlowGraphic = prevGlowState;
	}
}
// ----------------------------------------------------------------------------------------------

void TrayMode::ShowNotify(bool Mode)
{
	this->InTray = Mode;
	NOTIFYICONDATA Icon		= { 0 };
	// ----
	Icon.cbSize				= sizeof(NOTIFYICONDATA);
	Icon.uID				= TRAYMODE_ICON_ID;
	Icon.uFlags				= NIF_ICON|NIF_MESSAGE|NIF_TIP;
	Icon.hIcon				= (HICON)LoadImage(gController.Instance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	this->TempIconProc		= Icon.hIcon;
	Icon.hWnd				= pGameWindow;
	Icon.uCallbackMessage	= TRAYMODE_ICON_MESSAGE;
	// ----
	strcpy_s(Icon.szTip, sizeof(Icon.szTip), "LC MU Online");
	// ----
	if(pPlayerState == GameProcess )
	{
		lpCharObj lpPlayer			= pUserObjectStruct;
		char Text[120];
		sprintf(Text, "\n=====================\nCharacter: %s\nLevel: %d \n",lpPlayer->Name,lpPlayer->Level);
		strcat_s(Icon.szTip, Text);
	}
	// ----
	if( Mode )
	{
		Shell_NotifyIcon(NIM_ADD, &Icon);
	}
	else
	{
		Shell_NotifyIcon(NIM_DELETE, &Icon);
	}
	// ----
	DeleteObject(Icon.hIcon);
}
// ----------------------------------------------------------------------------------------------

void TrayMode::ShowMessage(DWORD Type, int Time, char * Title, char * Message)
{
	if (!gObjUser.IsVIP()) return;

	NOTIFYICONDATA Icon		= { 0 };
	// ----
	Icon.cbSize				= sizeof(NOTIFYICONDATA);
	Icon.uID				= TRAYMODE_ICON_ID;
	Icon.hWnd				= pGameWindow;
	Icon.uFlags				= NIF_ICON | NIF_MESSAGE | NIF_INFO;
	Icon.hIcon				= this->TempIconProc;
	Icon.uCallbackMessage	= TRAYMODE_ICON_MESSAGE;
	Icon.dwInfoFlags		= Type;
	Icon.uTimeout			= Time;
	// ----
	strcpy(Icon.szInfo, Message);
	strcpy(Icon.szInfoTitle, Title);
	// ----
	Shell_NotifyIcon(NIM_MODIFY, &Icon);
}
// ----------------------------------------------------------------------------------------------

void TrayMode::Work()
{
	if (!gObjUser.IsVIP()) return;

	if (!this->InTray) return;

	//Reduce CPU usage;
	Sleep(200);
}