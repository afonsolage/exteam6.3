#pragma once
// -----------------------------------------------------------------------

#define ENABLE_NEW_WINDOW		1
// -----------------------------------------------------------------------

//#define VMPROTECT
#define MAX_JS_RECVQ_LIMIT		150
#define MAX_SERVER_LIST			400
#define ENABLE_SERVERTYPE		1
// -----------------------------------------------------------------------

#define APP_NAME		"ConnectServer"
#define	APP_VERSION_T	"1.0.0.0"
#define	APP_VERSION_N	1, 0, 0, 0
#define	APP_DES			"ConnectServer"
// -----------------------------------------------------------------------

#include "targetver.h"
// -----------------------------------------------------------------------

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
// -----------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
// -----------------------------------------------------------------------

#include <windows.h>
//#include <winsock2.h>
// -----------------------------------------------------------------------

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <atlstr.h>
#include <time.h>
#include <vector>
#include <map>
#include <commctrl.h>
#include <ShellAPI.h>
// -----------------------------------------------------------------------

#pragma comment(lib, "ws2_32.lib")
#pragma comment (lib, "comctl32.lib")
// -----------------------------------------------------------------------

#include "resource.h"
#include "VMProtectSDK.h"
// -----------------------------------------------------------------------