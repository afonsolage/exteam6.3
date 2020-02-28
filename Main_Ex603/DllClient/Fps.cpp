#include "stdafx.h"
#include "Fps.h"
#include "stdafx.h"
#include "Fps.h"
#include "Console.h"
#include "Controller.h"
//#include "Import.h"
//#include "PersonalShopEx.h"
//#include "NewParty.h"
#include "Interface.h"
//#include "Fix.h"
#include "DeBug.h"
#include "Camera.h"
#include "TMemory.h"

#if(DEBUG_FPS)

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

void init()
{
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&lastCPU, &ftime, sizeof(FILETIME));

    self = GetCurrentProcess();
    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
    memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

double getCurrentValue()
{
    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) +
        (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent * 100;
}

#define sub_5965E0		((int(__cdecl*)(int a1)) 0x5965E0)

int sub_542EF0Hook()
{
  int result; // eax
  double v1; // [esp+4h] [ebp-2Ch]
  double v2; // [esp+18h] [ebp-18h]
  int v3; // [esp+2Ch] [ebp-4h]

  if ( !*(DWORD*)0x5EF5A3C )
  {
    *(DWORD*)0x5EF5A38 = 0;
    *(DWORD*)0x5EF5A34 = GetTickCount();
    *(DWORD*)0x5EF5A3C = 1;
  }
  ++*(DWORD*)0x5EF5A38;
  ++*(DWORD*)0x5EF5A30;
  *(float*)0x5EF5A1C = (double)GetTickCount();
  *(DWORD*)0x5EF5A2C = GetTickCount();
  v3 = *(DWORD*)0x5EF5A2C - *(DWORD*)0x5EF5A28;
  v2 = (double)(*(DWORD*)0x5EF5A2C - *(DWORD*)0x5EF5A34) / 1000.0;
  if ( 0.0 == v2 )
    v1 = -1.0;
  else
    v1 = (double)*(DWORD*)0x5EF5A38 / v2;
  if ( v2 > 2.0 && *(DWORD*)0x5EF5A38 > 10 )
  {
    *(DWORD*)0x5EF5A34 = *(DWORD*)0x5EF5A24;
    *(DWORD*)0x5EF5A38 = *(DWORD*)0x5EF5A30;
    *(DWORD*)0x5EF5A24 = GetTickCount();
    *(DWORD*)0x5EF5A30 = 0;
  }
  result = *(DWORD*)0x5EF5A2C - *(DWORD*)0x5EF5A28;
  *(float*)0xE61610 = (double)(*(DWORD*)0x5EF5A2C - *(DWORD*)0x5EF5A28) / 1000.0;
  if ( *(DWORD*)0x5EF5A2C == *(DWORD*)0x5EF5A28 )
    *(float*)0xE61610 = 0.0001;
  *(float*)0x5EF5A18 = v1;
  *(DWORD*)0x5EF5A28 = *(DWORD*)0x5EF5A2C;
  if ( *(DWORD*)0xE609E8 == 5 )
    result = sub_5965E0(v3);
  return result;
}


static HWND CreateWindowExA_Hook(    
	DWORD dwExStyle,
    LPCSTR lpClassName,
    LPCSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam)
{
	X = 75;
	Y = 150;	//-19;	//150;

	//X = 1920 - 320 - 50;
	//Y = 1080 - 240 - 50; 
	
	//nWidth = 320;
	//nHeight = 240;

  //  return CreateWindowEx(  
		//WS_EX_TOPMOST,	//dwExStyle,	//WS_EX_TOPMOST ,
  //      lpClassName,
  //      lpWindowName,
  //      WS_POPUP | WS_VISIBLE, //dwStyle, // WS_POPUP | WS_VISIBLE     ,
  //      X, Y, nWidth, nHeight,
  //      hWndParent, hMenu, hInstance, lpParam);

    return CreateWindowEx(  
		dwExStyle,
        lpClassName,
        lpWindowName,
        dwStyle,
        X, Y, nWidth, nHeight,
        hWndParent, hMenu, hInstance, lpParam);
}

int iHeightFont = 12;

static HFONT FontRet1()
{
	return CreateFont(iHeightFont, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE, "Gulim" );	//Gulim
}

static HFONT FontRet2()
{
	return CreateFont(iHeightFont, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE, NULL );
}

static HFONT FontRet3()
{
	return CreateFont(iHeightFont, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE, NULL );
}

static HFONT FontRet4()
{
	return CreateFont(iHeightFont, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE, NULL );	//text.bmd?
}

static HFONT FontRet5()
{
	return CreateFontA(iHeightFont, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE, NULL );
}

//int __cdecl sub_4DAD00(HDC a1)
#define sub_4DAD00		((int(__cdecl*)(HDC a1)) 0x4DAD00)



bool CreateRender = false;

void RenderThread(LPVOID lpThreadParameter) 
{ 
	//HDC a1 = (HDC)lpThreadParameter;
	while(true)
	{
		if(!CreateRender)
		{
			continue;
		}
		//sub_4DAD00(a1);
		sub_4DAD00(*(HDC*)0x00E8C580);
		//Sleep(40);
	}
}



void cBlueEvent__InsideTrigger(void * lpParam)
{
	//Sleep(BlueEvent.Minutes * 60000);

	//HDC a1 = *(HDC*)lpParam;

	while(1)
	{
	sub_4DAD00(0);

	Sleep(1);
	}

	//_endthread();
}


int __cdecl hook_4DAD00(HDC a1)
{
	if(!CreateRender)
	{
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RenderThread, a1, 0, 0);
	//	_beginthread( cBlueEvent__InsideTrigger, 0, a1  );
		
		CreateRender = 1;

		return 1;//sub_4DAD00(a1);
	}
//
//	return 1;

	return sub_4DAD00(a1);
}



CFps g_Fps;



void CFps::Load()
{
	init();

	this->m_iFPSTime = 40;

	this->m_iTimeSecond = 0;
	this->m_iCount = 0;
	this->m_iDelay = 40;

	//SetOp((LPVOID)0x004D349F, (LPVOID)hook_4DAD00, ASM::CALL);
	//SetOp((LPVOID)0x004D34BE, (LPVOID)hook_4DAD00, ASM::CALL);
	//SetRange((LPVOID)0x004D349F, 5, ASM::NOP);
	//SetRange((LPVOID)0x004D34BE, 5, ASM::NOP);

	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RenderThread, 0, 0, 0);
	//SetTimer(pGameWindow, WM_EX_TIMER, 40, NULL);

	SetOp((LPVOID)0x004DADA4, (LPVOID)&this->Render, ASM::CALL);
	//SetOp((LPVOID)0x004DADA4, (LPVOID)&this->RenderHook, ASM::CALL);
	//SetOp((LPVOID)0x004DADA4, (LPVOID)&this->RenderDebug, ASM::CALL);
	//this->SetDelay(this->m_iDelay);

	//this->CameraLoad();

	//this->Clear();

	g_Fps.m_iCount = 0;
	g_Fps.m_TickCount = GetTickCount();
	g_Fps.m_iLastCount = 0;
	g_Fps.m_iLastTick = 0;

	this->m_StopWatchStart = false;
	this->m_StopWatchTime = 0;

	memset(this->m_Disable, 0, sizeof(this->m_Disable));

	pFpsTime1 = GetTickCount();
	pFpsTime2 = 0;

	return;

	//SetRange((LPVOID)0x004D0F28, 6, ASM::NOP);
	//SetOp((LPVOID)0x004D0F28, (LPVOID)&CreateWindowExA_Hook, ASM::CALL);

	//SetRange((LPVOID)0x004D0F76, 6, ASM::NOP);
	//SetOp((LPVOID)0x004D0F76, (LPVOID)&CreateWindowExA_Hook, ASM::CALL);

	//SetRange((LPVOID)0x004D0FAE, 6, ASM::NOP);
	//SetOp((LPVOID)0x004D0FAE, (LPVOID)&CreateWindowExA_Hook, ASM::CALL);
	
	// -> TextOutA	
	//SetOp((LPVOID)0x00420BC1, (LPVOID)&g_Ch.sub_9592F0, ASM::CALL);	//0x004208BA -> Start -> TextOut

	// -> GetTextExtentPoint32 (0x0095928C)
	//SetOp((LPVOID)0x004208BA, (LPVOID)&g_Ch.sub_959230, ASM::CALL);	//0x004208BA -> Start -> GetTextExtentPoint32

	// -> CreateFontW
	//DWORD OffSetCall = 0x004060D0;	//1
	//SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
	//SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet1, ASM::CALL);
	//
	//OffSetCall = 0x004D2882;	//2
	//SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
	//SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet2, ASM::CALL);

	//OffSetCall = 0x004D28EB;	//3
	//SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
	//SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet3, ASM::CALL);

	//OffSetCall = 0x004D2957;	//4
	//SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
	//SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet4, ASM::CALL);

	//OffSetCall = 0x004D29C1;	//5
	//SetRange((LPVOID)OffSetCall, 6, ASM::NOP);
	//SetOp((LPVOID)OffSetCall, (LPVOID)&FontRet5, ASM::CALL);
	
	//g_Ch.Load();

	//SetByte((LPVOID)(0x004D339D + 6), 0xFF);
	//SetByte((LPVOID)(0x004D33B7 + 6), 0xFF);
}

int RenderTick = 0;
int iFrameTime = 0;

int CFps::Render(HDC a1)
{
	SYSTEMTIME tt1;
	GetLocalTime(&tt1);

	int iFrameTick = GetTickCount();

	int Result = g_Fps.RenderDev(a1);

	iFrameTime = (GetTickCount() - iFrameTick);	

	g_Fps.m_iCount++;

	if(g_Fps.m_StopWatchStart)
	{
		g_Fps.m_StopWatchTime =  (GetTickCount() - g_Fps.m_StopWatchTick);
	}

	int iTickMsec = (GetTickCount() - g_Fps.m_TickCount);

	if(iTickMsec >= 1000)
	{		
		RenderTick = iTickMsec / g_Fps.m_iCount;

		g_Fps.m_dCPU = getCurrentValue();

		gConsole.Output(cGREEN, "FPS: %02d --- TIME: %d (%d) --- SWATCH %d CPU: %f", 
			g_Fps.m_iCount, RenderTick, iFrameTime, g_Fps.m_StopWatchTime, g_Fps.m_dCPU);

		g_Fps.m_TickCount = GetTickCount();
		g_Fps.m_iLastCount = g_Fps.m_iCount;
		g_Fps.m_iLastTick = RenderTick;
		g_Fps.m_iCount = 0;
	}

	return Result;
}

void CFps::SetDelay(BYTE btTick)
{
	SetByte((LPVOID)(0x004DA3DD+3), btTick);
	SetByte((LPVOID)(0x004DA3B2+1), btTick);
	SetByte((LPVOID)(0x004DA3AC+3), btTick);
	SetByte((LPVOID)(0x004D9D45+6), btTick);
	SetByte((LPVOID)(0x004D9F02+2), btTick);	

	gConsole.Output(cGREEN, "SetDelay: %d", btTick);
}

void CFps::Button(DWORD Key)
{
	if(Key == VK_OEM_MINUS)
	{
		if(this->m_iFPSTime > 0)
		{
			this->m_iFPSTime--;
		}
	}
	else if(Key == VK_OEM_PLUS)
	{
		if(this->m_iFPSTime < 255)
		{
			this->m_iFPSTime++;
		}
	}
	else if(Key == VK_F8)
	{
		if(this->m_StopWatchStart)
		{
			this->m_StopWatchStart = false;
			this->m_StopWatchTime =  (GetTickCount() - g_Fps.m_StopWatchTick);
		}
		else
		{
			this->m_StopWatchStart = true;
			this->m_StopWatchTime = 0;
			this->m_StopWatchTick = GetTickCount();
		}
	}
	else if(Key == VK_1)
	{
		this->m_Disable[1] = !this->m_Disable[1];
	}
	else if(Key == VK_2)
	{
		this->m_Disable[2] = !this->m_Disable[2];
	}
	else if(Key == VK_3)
	{
		this->m_Disable[3] = !this->m_Disable[3];
	}
	else if(Key == VK_4)
	{
		this->m_Disable[4] = !this->m_Disable[4];
	}
	else if(Key == VK_5)
	{
		this->m_Disable[5] = !this->m_Disable[5];
	}
	else if(Key == VK_6)
	{
		this->m_Disable[6] = !this->m_Disable[6];
	}
	else if(Key == VK_7)
	{
		this->m_Disable[7] = !this->m_Disable[7];
	}
	else if(Key == VK_8)
	{
		this->m_Disable[8] = !this->m_Disable[8];
	}
	else if(Key == VK_9)
	{
		this->m_Disable[9] = !this->m_Disable[9];
	}
	else if(Key == VK_0)
	{
		this->m_Disable[0] = !this->m_Disable[0];
	}
	else if(Key == VK_OEM_4)
	{
		MoveWindow(pGameWindow, 100, 100, 800, 600, 0);

		pWinWidth		= 800;
		pWinHeight		= 600;

		pWinWidthReal	= (float)pWinWidth / MAX_WIN_WIDTH;
		pWinHeightReal	= (float)pWinHeight / MAX_WIN_HEIGHT;

		//UpdateWindow(pGameWindow);

		//*(HFONT*)0x00E8C588 = FontRet2();
		//*(HFONT*)0x00E8C58C = FontRet3();
		//*(HFONT*)0x00E8C590 = FontRet4();
		//*(HFONT*)0x00E8C594 = FontRet5();

	}
	else if(Key == VK_OEM_6)
	{
		int iX = 1920 - 320 - 50;
		int iY = 1080 - 240 - 50; 

		MoveWindow(pGameWindow, iX, iY, 320, 240, 0);

		pWinWidth		= 320;
		pWinHeight		= 240;

		pWinWidthReal	= (float)pWinWidth / MAX_WIN_WIDTH;
		pWinHeightReal	= (float)pWinHeight / MAX_WIN_HEIGHT;

		HFONT hFontSend = CreateFontW(iHeightFont, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE, NULL );

		//SendMessage(pGameWindow, WM_SETFONT, (WPARAM)hFontSend, NULL);
	}	
	else if(Key == VK_OEM_5)
	{
		int iX = 0;
		int iY = 0; 

		MoveWindow(pGameWindow, iX, iY, 1920, 1080, 0);
		//SetWindowPos(pGameWindow, 0, 0, 0, 1920, 1080, SWP_SHOWWINDOW);

		pWinWidth		= 1920;
		pWinHeight		= 1080;

		pWinWidthReal	= (float)pWinWidth / MAX_WIN_WIDTH;
		pWinHeightReal	= (float)pWinHeight / MAX_WIN_HEIGHT;

		//UpdateWindow(pGameWindow);

		/**(HFONT*)0x00E8C588 = FontRet2();
		*(HFONT*)0x00E8C58C = FontRet3();
		*(HFONT*)0x00E8C590 = FontRet4();
		*(HFONT*)0x00E8C594 = FontRet5();**/



		//POINT point;
		//point.x = iX;
		//point.y = iY;
		//GetCursorPos(&point);
		//ScreenToClient(pGameWindow, &point);

		//int v5 = (int)sub_407B20();
		//sub_407B90((int)v5, (int)pGameWindow, pWinWidth, (int)pWinHeight);

		 
		//SendMessage( (HWND) HWND_BROADCAST, WM_FONTCHANGE, (WPARAM) NULL, (LPARAM) NULL);
	}

	this->CameraButton(Key);
}

void CFps::CameraLoad()
{
return;
	this->m_flZ1 = 1000.0;
	this->m_flZ2 = 1000.0;
	this->m_flGL = 2000.0;
	this->m_flY = 2400.0;
	this->m_flX = 1190.0;

	//this->m_flZ1 = 1500.0;
	//this->m_flZ2 = 1500.0;
	//this->m_flGL = 3000.0;
	//this->m_flY = 3500.0;
	//this->m_flX = 3000.0;

	//this->m_flZ1 = 1000.0;
	//this->m_flZ2 = 1000.0;
	//this->m_flGL = 2000.0;
	//this->m_flY = 3500.0;
	//this->m_flX = 3000.0;


	
	SetRange((LPVOID)0x004045D5, 6, ASM::NOP);	// -> Zoom Nop 1
	SetRange((LPVOID)0x004D6A31, 6, ASM::NOP);	// -> Zoom Nop 2
	SetRange((LPVOID)0x004D850C, 6, ASM::NOP);	// -> Zoom Nop 3
	SetRange((LPVOID)0x004D851A, 6, ASM::NOP);	// -> Zoom Nop 4
	SetRange((LPVOID)0x004D8802, 6, ASM::NOP);	// -> GL Ex
	SetRange((LPVOID)0x004D8E7C, 49, ASM::NOP);	// -> Map Draw Ex

	SetOp((LPVOID)0x004D8D16, (LPVOID)0x004D8E83, ASM::JMP);
	SetOp((LPVOID)0x005DB208, (LPVOID)0x005DB408, ASM::JMP);	//Vulcan
	SetOp((LPVOID)0x004D8707, (LPVOID)0x004D878D, ASM::JMP);	//Map fix
	SetOp((LPVOID)0x005DB21C, (LPVOID)0x005DB408, ASM::JMP);	//Map fix
	SetOp((LPVOID)0x004D88E9, (LPVOID)0x004D897C, ASM::JMP);	//Map fix
	

}

void CFps::CameraButton(DWORD Event)
{
return;
	if(pPlayerState != 5)
	{
		return;
	}

	switch(Event)
	{
		case VK_LEFT:		this->m_flGL -= 100;	break;
		case VK_RIGHT:		this->m_flGL += 100;	break;
		case VK_DOWN:		this->m_flZ1 -= 100;	break;
		case VK_UP:			this->m_flZ1 += 100;	break;		
		case VK_NUMPAD2:	this->m_flY -= 100;		break;
		case VK_NUMPAD8:	this->m_flY += 100;		break;
		case VK_NUMPAD4:	this->m_flX -= 100;		break;
		case VK_NUMPAD6:	this->m_flX += 100;		break;
		case VK_ADD:		this->m_flZ2 += 100;	break;
		case VK_SUBTRACT:	this->m_flZ2 -= 100;	break;
		default: break;	
	}	

	*(float*)0xE61E3C = this->m_flGL;	// -> GL Map Draw
	*(float*)0xE60B50 = this->m_flZ1;	// -> W Map Draw
	*(float*)0xE8CB6C = this->m_flZ2;	// -> H Map draw

	SetDouble((LPVOID)oCam_ClipX, this->m_flX);	// -> X
	SetFloat((LPVOID)oCam_ClipY, this->m_flY);	// -> Y?

	//gConsole.Output(cYELLOW, "GL:%f :: W:%f :: H:%f", *(float*)0xE61E3C, *(float*)0xE60B50, *(float*)0xE8CB6C);
	//gConsole.Output(cMAGENTA, "GL2: %f :: ClipX: %f :: ClipY: %f", *(float*)0xE61E38, *(double*)oCam_ClipX, *(float*)oCam_ClipY);
}

void CFps::CameraMain(float Zoom)
{return;
	if(pPlayerState != 5)
	{
		return;
	}

	this->CameraLoad();

	*(float*)0xE61E40 = Zoom;
	*(float*)0xE61E3C = this->m_flGL;	// -> GL Map Draw
	*(float*)0xE60B50 = this->m_flZ1;	// -> W Map Draw
	*(float*)0xE8CB6C = this->m_flZ2;	// -> Map draw

	SetFloat((LPVOID)oCam_ClipY, this->m_flY);	// -> Y?
	SetDouble((LPVOID)oCam_ClipX, this->m_flX);	// -> X		
}

void CFps::Clear()
{
	memset(this->m_szFPSName, 0, sizeof(this->m_szFPSName));
	memset(this->m_iFPSNeed, 0, sizeof(this->m_iFPSNeed));
	this->m_iFPSCount = 0;
	this->m_iFPSTick = GetTickCount();
}

void CFps::NeedTime(char* InfoText)
{
	if(this->m_iFPSCount >= 10)
	{
		return;
	}

	int iTickMsec = (GetTickCount() - this->m_iFPSTick);
	this->m_iFPSTick = GetTickCount();

	memcpy(this->m_szFPSName[this->m_iFPSCount], InfoText, sizeof(this->m_szFPSName[this->m_iFPSCount]));
	this->m_iFPSNeed[this->m_iFPSCount] = iTickMsec;

	this->m_iFPSCount++;
}

void CFps::Draw()
{
	float  flDrawX = 0;
	float flDrawY = 0;
	
	gInterface.DrawMiniBar(flDrawX, flDrawY, 30);

	flDrawX = 15;
	flDrawY = 5;
	gInterface.DrawFormat(eExcellent, flDrawX, flDrawY, 300, 1, 
		"[ CPU: %0.1f ] [ FPS: %02d ] [ TIME: %02d ] [ NUM: %02d ] [ SWATCH: %d ] [ ZOOM: %d ]", 
		(float)g_Fps.m_dCPU,
		g_Fps.m_iLastCount, 
		g_Fps.m_iLastTick, 
		g_Fps.m_iFPSTime, 
		g_Fps.m_StopWatchTime/1000,
		(int)gCamera.ZoomPercent
		);


	flDrawX = 275;
	flDrawY = 5;
	gInterface.DrawFormat(eAncient, flDrawX, flDrawY, 200, 1, 
		"[ A1: %f ] [ A2: %f ] [ A3: %d ] [ A4: %d ]", 
		*(float*)0x5EF5A1C,
		*(float*)0xE8C808,
		*(BYTE*)0x87933F8,
		*(BYTE*)0xE8C571);
		

	flDrawX = 475;
	flDrawY = 5;
	for(int i = 0; i < 5; i++)
	{
		DWORD dwColor = eRed;

		if(g_Fps.m_Disable[i])
		{
			dwColor = eExcellent;
		}

		gInterface.DrawFormat(dwColor, flDrawX + i * 30, flDrawY, 50, 1, "[ D%d: %d ]", i,g_Fps.m_Disable[i]);
	}
}

int CFps::RenderHook(HDC a1)
{
  BYTE *v1; // eax
  DWORD *v2; // eax
  BYTE *v3; // eax
  HWND v4; // eax
  void *v5; // eax
  int v6; // edx
  int result; // eax
  const char * v8; // eax
  int blue_4; // ST18_4
  char *v10; // eax
  int v11; // eax
  DWORD *v12; // eax
  char *v13; // eax
  void *v14; // ecx
  DWORD *v15; // eax
  char *v16; // eax
  int *v17; // ST20_4
  void *v18; // eax
  DWORD *v19; // eax
  BYTE *v20; // eax
  void *v21; // eax
  DWORD *v22; // eax
  void *v23; // eax
  void *v24; // eax
  void *v25; // eax
  void *v26; // eax
  double v27; // [esp+20h] [ebp-208h]
  char v28; // [esp+28h] [ebp-200h]
  char v29; // [esp+2Ch] [ebp-1FCh]
  char v30; // [esp+48h] [ebp-1E0h]
  char v31; // [esp+64h] [ebp-1C4h]
  char v32; // [esp+80h] [ebp-1A8h]
  DWORD dwMilliseconds; // [esp+9Ch] [ebp-18Ch]
  int j; // [esp+A0h] [ebp-188h]
  double v35; // [esp+A4h] [ebp-184h]
  int i; // [esp+B0h] [ebp-178h]
  __m128i v37[16]; // [esp+B4h] [ebp-174h]
  int v38; // [esp+1B4h] [ebp-74h]
  char v39; // [esp+1BBh] [ebp-6Dh]
  int v40; // [esp+1BCh] [ebp-6Ch]
  int v41; // [esp+1C0h] [ebp-68h]
  struct _SYSTEMTIME SystemTime; // [esp+1C4h] [ebp-64h]
  CHAR v43; // [esp+1D4h] [ebp-54h]
  int v44; // [esp+218h] [ebp-10h]
  int v45; // [esp+224h] [ebp-4h]

  sub_542EF0();
  v1 = (BYTE*)sub_500E80();
  if ( !sub_40BC80(v1) )
  {
    v2 = (DWORD*)sub_482B70();
    //sub_484A10(v2, 170, 0);
  }
  for ( i = *(DWORD*)0xE8CB50; i >= 40; i -= 40 )
  {
    v3 = (BYTE*)sub_790FB0();
    sub_791020(v3);
    if ( *(DWORD*)0xE609E8 == 2 || *(DWORD*)0xE609E8 == 4 )
    {
      v35 = sub_95C1C0((DWORD *)*(DWORD*)0xE8C598);
      if ( v35 >= 200.0 )
      {
        v27 = 200.0;
      }
      else
      {
        v27 = v35;
      }
      v35 = v27;
      sub_95C260((LARGE_INTEGER *)*(DWORD*)0xE8C598);
      v4 = (HWND)sub_407B20();
      sub_407C70(v4);
      v5 = sub_482B70();
      sub_4845E0((int)v5, v6, v27);
    }
    *(DWORD*)0xE7C3E4 = 0;
    switch ( *(DWORD*)0xE609E8 )
    {
      case 2:

        sub_4D7730();
        break;
      case 4:
        sub_4D6E70();
        break;
      case 5:
        sub_4D8FD0();
        break;
    }
    for ( j = 0; j < 5; ++j )
    {
      sub_51FDF0((char *)0xE8CB5C, 0.0049999999);
    }
    sub_5977A0();
    if ( sub_596A70(44) )
    {
      *(BYTE*)0x87933FA = *(BYTE*)0x87933FA == 0;
    }
    if ( *(DWORD*)0x8793728 > 0 )
    {
      --*(DWORD*)0x8793728;
    }
    if ( *(DWORD*)0x81C0404 > 0 )
    {
      --*(DWORD*)0x81C0404;
    }
    ++*(DWORD*)0x8787AA8;
    *(DWORD*)0x8787AA8 %= 32;
    ++*(DWORD*)0xE8CB20;
  }
  result = (unsigned __int8)*(BYTE*)0xE8C571;
  if ( !*(BYTE*)0xE8C571 )
  {
    sub_4FC520((char*)0x9816AA0);
    sub_6D6F10();
    GetLocalTime(&SystemTime);
    sub_9CF52A(
      (int)(BYTE*)0x8793278,
      "Images\\\\Screen(%02d_%02d-%02d_%02d)-%04d.jpg",
      SystemTime.wMonth,
      SystemTime.wDay,
      SystemTime.wHour,
      SystemTime.wMinute,
      *(DWORD*)0x8793404);
   // disable v8 = dec_402320(459);//sub_402320((char *)0x8128ADC, 459);	//sub_402320(459);
	//v8 = (const char *)sub_402320(459);
	//gConsole.Output(cGREEN, "[%s]", v8);
   // sub_9CF52A((int)(BYTE*)v37, v8, (DWORD*)0x8793278);
   sub_9CF52A((int)(BYTE*)v37, " %s: Screenshot Saved", (DWORD*)0x8793278);
    blue_4 = *(DWORD*)(0x7BC4F04 + 56);	//<<
    v10 = (char *)sub_953790();
    v11 = sub_954190(v10);
    wsprintfA(&v43, " [%s / %s]", v11, blue_4);
    sub_9CF3C0((char *)v37, (BYTE*)&v43);
    v44 = 1;
    if ( sub_790F40(16) == 1 )
    {
      v44 = 1 - v44;
    }
    if ( *(BYTE*)0x87933FA && v44 == 1 )
    {
      sub_409A50(&v32, (int)v37);
      v45 = 0;
      sub_409A50(&v31, (int)&*(BYTE*)0xD2713E);
	  v45 = 1;	//	LOBYTE(v45) = 1;
      v12 = (DWORD*)sub_860FC0();
      v13 = (char *)sub_861030(v12);
      sub_789390(v13, (int)&v31, (int)&v32, 3, 0);
      v45 = 0;	//LOBYTE(v45) = 0;
      sub_409AD0((LPDWORD)v31);
      v45 = -1;
      sub_409AD0((LPDWORD)v32);
    }
    if ( *(DWORD*)0xE61E18 == 10 )
    {
      glClearColor(0.01171875, 0.09765625, 0.171875, 1.0);
    }
    else if ( *(DWORD*)0xE61E18 != 73 && *(DWORD*)0xE61E18 != 74 )
    {
      if ( sub_4DB1C0(*(DWORD*)0xE61E18) )
      {
        glClearColor(0.1171875, 0.15625, 0.15625, 1.0);
      }
      else if ( sub_4E65A0(*(DWORD*)0xE61E18) == 1 )
      {
        glClearColor(0.0, 0.0, 0.0, 1.0);
      }
      else if ( (unsigned __int8)sub_4DB0E0(*(DWORD*)0xE61E18) && sub_4DB0F0((float *)(*(DWORD*)(0x7BC4F04 + 1028))) )
      {
        glClearColor(0.0, 0.0, 0.0, 1.0);
      }
      else if ( *(DWORD*)0xE61E18 < 45 || *(DWORD*)0xE61E18 > 50 )
      {
        if ( *(DWORD*)0xE61E18 == 51 )
        {
          glClearColor(0.6953125, 0.6953125, 0.6953125, 1.0);
        }
        else if ( *(DWORD*)0xE61E18 == 65 )
        {
          glClearColor(0.578125, 0.69921875, 0.87109375, 1.0);
        }
        else
        {
          glClearColor(0.0, 0.0, 0.0, 1.0);
        }
      }
      else
      {
        glClearColor(0.03515625, 0.03125, 0.12890625, 1.0);
      }
    }
    else
    {
      glClearColor(0.0, 0.0, 0.0, 1.0);
    }
    glClear(0x4100u);
    v41 = 0;
    v38 = *(DWORD*)0xE8CB30;
    *(DWORD*)0xE8CB30 = GetTickCount();
    v39 = 0;
    switch ( *(DWORD*)0xE609E8 )
    {
      case 2:
        v39 = sub_4D7970();	//sub_4D7970(v14);
        break;
      case 4:
        v39 = sub_4D70E0();	//sub_4D70E0(a1);
        break;
      case 5:
        v39 = sub_4D95E0();	//sub_4D95E0(v14);
        break;
    }
    sub_51FEF0((char *)0xE8CB5C);
    if ( *(BYTE*)0x87933FA )
    {
      sub_635770();
    }
    if ( *(BYTE*)0x87933FA && !v44 )
    {
      sub_409A50(&v30, (int)v37);
      v45 = 2;
      sub_409A50(&v29, (int)&*(BYTE*)0xD2713F);
      v45 = 3;	//LOBYTE(v45) = 3;
      v15 = (DWORD*)sub_860FC0();
      v16 = (char *)sub_861030(v15);
      sub_789390(v16, (int)&v29, (int)&v30, 3, 0);
      v45 = 2;	//LOBYTE(v45) = 2;
      sub_409AD0((LPDWORD)v29);
      v45 = -1;
      sub_409AD0((LPDWORD)v30);
    }
    *(BYTE*)0x87933FA = 0;
    if ( v39 )
    {
      glFlush();
      SwapBuffers(a1);
    }
    v41 = *(DWORD*)0xE8CB30 - v38;
    if ( *(DWORD*)0xE8CB30 - v38 < 40 )
    {
      dwMilliseconds = 40 - v41;
      Sleep(40 - v41);
      *(DWORD*)0xE8CB30 += dwMilliseconds;
      v41 = 40;
    }
    v40 = v41 + i;
    if ( *(BYTE*)0xE8CB1F && *(DWORD*)0xE609E8 == 5 && sub_63A2B0((DWORD*)0x8793750) == -1 && !*(DWORD*)0xE8CB70 )
    {
      *(DWORD*)0xE8CB70 = 1;
      sub_96AD90((int)*(DWORD*)0xE8C5D8, (int)"> Connection closed. ");
      sub_96B040(1);
      v17 = (int*)sub_4DB260((LPDWORD)v28);
      v45 = 4;
      sub_4DB310(v17);
      v45 = -1;
      sub_4DB280(&v28);
    }
    if ( *(DWORD*)0xE609E8 == 5 )
    {
      switch ( *(DWORD*)0xE61E18 )
      {
        case 0:
          if ( *(DWORD*)0x81C0394 == 4 )
          {
            sub_6D6D00(0, 1);
            sub_6D6D00(1, 1);
          }
          else
          {
            sub_6D6AD0(0, 0, 1);
            if ( *(DWORD*)0x9761A2C > 0 )
            {
              sub_6D6AD0(1, 0, 1);
            }
          }
          break;
        case 1:
          sub_6D6AD0(3, 0, 1);
          break;
        case 2:
          if ( *(DWORD*)0x81C0394 != 3 && *(DWORD*)0x81C0394 < 10 )
          {
            sub_6D6AD0(0, 0, 1);
          }
          else
          {
            sub_6D6D00(0, 1);
          }
          break;
        case 3:
          sub_6D6AD0(0, 0, 1);
          if ( !((signed int)sub_9CFA0D() % 512) )
          {
            sub_6D6AD0(2, 0, 0);
          }
          break;
        case 4:
          sub_6D6AD0(5, 0, 1);
          break;
        case 7:
          sub_6D6AD0(6, 0, 1);
          break;
        case 8:
          sub_6D6AD0(7, 0, 1);
          break;
        case 10:
          sub_6D6AD0(20, 0, 1);
          if ( (signed int)sub_9CFA0D() % 100 )
          {
            sub_9CFA0D();
          }
          break;
        case 58:
          sub_6D6AD0(0, 0, 1);
          break;
        case 79:
          sub_6D6AD0(0, 0, 1);
          sub_6D6AD0(1, 0, 1);
          break;
        case 80:
          sub_6D6AD0(980, 0, 1);
          break;
        case 81:
          if ( *(DWORD*)0x81C0394 == 12 )
          {
            sub_6D6D00(980, 1);
            sub_6D6AD0(982, 0, 1);
          }
          else
          {
            sub_6D6D00(982, 1);
            sub_6D6AD0(980, 0, 1);
          }
          break;
        default:
          break;
      }
      if ( *(DWORD*)0xE61E18 && *(DWORD*)0xE61E18 != 2 && *(DWORD*)0xE61E18 != 3 && *(DWORD*)0xE61E18 != 58 && *(DWORD*)0xE61E18 != 79 )
      {
        sub_6D6D00(0, 1);
      }
      if ( *(DWORD*)0xE61E18 && !(unsigned __int8)sub_4E65E0() && *(DWORD*)0xE61E18 != 79 )
      {
        sub_6D6D00(1, 1);
      }
      if ( *(DWORD*)0xE61E18 != 1 )
      {
        sub_6D6D00(3, 1);
      }
      if ( *(DWORD*)0xE61E18 != 3 )
      {
        sub_6D6D00(2, 1);
      }
      if ( *(DWORD*)0xE61E18 != 4 )
      {
        sub_6D6D00(5, 1);
      }
      if ( *(DWORD*)0xE61E18 != 7 )
      {
        sub_6D6D00(6, 1);
      }
      if ( *(DWORD*)0xE61E18 != 8 )
      {
        sub_6D6D00(7, 1);
      }
      if ( *(DWORD*)0xE61E18 != 10 )
      {
        sub_6D6D00(20, 1);
      }
      if ( *(DWORD*)0xE61E18 != 51 )
      {
        sub_6D6D00(781, 1);
        sub_6D6D00(782, 1);
        sub_6D6D00(783, 1);
        sub_6D6D00(784, 1);
        sub_6D6D00(785, 1);
        sub_6D6D00(786, 1);
        sub_6D6D00(787, 1);
      }
      if ( !sub_90FC10() )
      {
        sub_6D6D00(980, 1);
      }
      if ( *(DWORD*)0xE61E18 != 80 )
      {
        sub_6D6D00(981, 1);
      }
      if ( *(DWORD*)0xE61E18 != 81 )
      {
        sub_6D6D00(982, 1);
      }
      if ( *(DWORD*)0xE61E18 )
      {
        sub_4CF000((int)0xE609F0, 0);
        sub_4CF000((int)0xE60A44, 0);
      }
      else if ( *(BYTE *)(0x7BC4F04 + 14) )
      {
        if ( *(DWORD*)0x81C0394 == 4 )
        {
          sub_4CF050((int)0xE609F0, 0);
        }
        else
        {
          sub_4CF050((int)0xE60A44, 0);
        }
      }
      if ( *(DWORD*)0xE61E18 == 2 )
      {
        if ( *(BYTE *)*(DWORD*)(0x7BC4F04 + 14) )	// <<
        {
          if ( *(DWORD *)(0x7BC4F04 + 172) < 205
            || *(DWORD *)(0x7BC4F04 + 172) > 214
            || *(DWORD *)(0x7BC4F04 + 176) < 13
            || *(DWORD *)(0x7BC4F04 + 176) > 31 )
          {
            sub_4CF050((int)0xE609FC, 0);
          }
          else
          {
            sub_4CF050((int)0xE609F8, 0);
          }
        }
      }
      else
      {
        sub_4CF000((int)0xE609F8, 0);
        sub_4CF000((int)0xE609FC, 0);
      }
      if ( *(DWORD*)0xE61E18 == 3 )
      {
        if ( *(BYTE *)(0x7BC4F04 + 14) )
        {
          sub_4CF050((int)0xE60A00, 0);
        }
      }
      else
      {
        sub_4CF000((int)0xE60A00, 0);
      }
      if ( *(DWORD*)0xE61E18 != 1 && *(DWORD*)0xE61E18 != 5 )
      {
        sub_4CF000((int)0xE60A04, 0);
      }
      else
      {
        sub_4CF050((int)0xE60A04, 0);
      }
      if ( *(DWORD*)0xE61E18 == 7 )
      {
        sub_4CF050((int)0xE60A08, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A08, 0);
      }
      if ( *(DWORD*)0xE61E18 == 10 )
      {
        sub_4CF050((int)0xE60A0C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A0C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 8 )
      {
        sub_4CF050((int)0xE60A10, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A10, 0);
      }
      if ( *(DWORD*)0xE61E18 == 4 )
      {
        sub_4CF050((int)0xE60A14, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A14, 0);
      }
      if ( sub_4DB1C0(*(DWORD*)0xE61E18) )
      {
        sub_4CF050((int)0xE60A1C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A1C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 31 )
      {
        sub_4CF050((int)0xE60A2C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A2C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 33 )
      {
        sub_4CF050((int)0xE60A30, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A30, 0);
      }
      sub_8D3270(*(DWORD*)0xE61E18);
      sub_8B5080(*(DWORD*)0xE61E18);
      if ( *(DWORD*)0xE61E18 == 37 )
      {
        sub_4CF050((int)0xE60A48, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A48, 0);
      }
      sub_8ACA90();
      v18 = sub_89C9B0();
      sub_89DDF0(v18);
      sub_91C880();
      if ( sub_4DB1F0() )
      {
        v19 = (DWORD*)sub_91C880();
        sub_920AE0(v19);
      }
      if ( *(DWORD*)0xE61E18 == 51 )
      {
        sub_4CF050((int)0xE60A6C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A6C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 56 )
      {
        sub_4CF050((int)0xE60A74, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A74, 0);
      }
      v20 = (BYTE *)sub_4DB390(57);
      sub_8C4500(v20);
      v21 = (void *)sub_4DB3C0(62);
      sub_914AB0(v21);
      void* v46 = (void *)sub_4DB3F0(63);
      sub_8B8E90(v46);
      v22 = (DWORD *)sub_4DB420(65);
      sub_8DE660(v22);
      v23 = (void *)sub_4DB450(69);
      sub_8F03F0(v23);
      v24 = (void *)sub_4DB480(70);
      sub_8F4630(v24);
      v25 = (void *)sub_4DB4B0(71);
      sub_8F9110(v25);
      v26 = (void *)sub_4DB4E0(72);
      sub_8FEA40(v26);
      sub_4DB510(79);
      sub_91C1A0();
      sub_4DB540(80);
      sub_90FBA0();
    }
    result = v40;
    *(DWORD*)0xE8CB50 = v40;
  }
  return result;
}

int CFps::RenderDebug(HDC a1)
{
  BYTE *v1; // eax
  DWORD *v2; // eax
  BYTE *v3; // eax
  HWND v4; // eax
  void *v5; // eax
  int v6; // edx
  int result; // eax
  const char * v8; // eax
  int blue_4; // ST18_4
  char *v10; // eax
  int v11; // eax
  DWORD *v12; // eax
  char *v13; // eax
  void *v14; // ecx
  DWORD *v15; // eax
  char *v16; // eax
  int *v17; // ST20_4
  void *v18; // eax
  DWORD *v19; // eax
  BYTE *v20; // eax
  void *v21; // eax
  DWORD *v22; // eax
  void *v23; // eax
  void *v24; // eax
  void *v25; // eax
  void *v26; // eax
  double v27; // [esp+20h] [ebp-208h]
  char v28; // [esp+28h] [ebp-200h]
  char v29; // [esp+2Ch] [ebp-1FCh]
  char v30; // [esp+48h] [ebp-1E0h]
  char v31; // [esp+64h] [ebp-1C4h]
  char v32; // [esp+80h] [ebp-1A8h]
  DWORD dwMilliseconds; // [esp+9Ch] [ebp-18Ch]
  int j; // [esp+A0h] [ebp-188h]
  double v35; // [esp+A4h] [ebp-184h]
  int i; // [esp+B0h] [ebp-178h]
  __m128i v37[16]; // [esp+B4h] [ebp-174h]
  int v38; // [esp+1B4h] [ebp-74h]
  char v39; // [esp+1BBh] [ebp-6Dh]
  int v40; // [esp+1BCh] [ebp-6Ch]
  int v41; // [esp+1C0h] [ebp-68h]
  struct _SYSTEMTIME SystemTime; // [esp+1C4h] [ebp-64h]
  CHAR v43; // [esp+1D4h] [ebp-54h]
  int v44; // [esp+218h] [ebp-10h]
  int v45; // [esp+224h] [ebp-4h]

  //system("cls");
  //GetLocalTime(&SystemTime);
  //g_Fps.Clear();

  //g_Fps.NeedTime("START");

  //sub_542EF0();
  //v1 = (BYTE*)sub_500E80();
  //if ( !sub_40BC80(v1) )
  //{
  //  v2 = (DWORD*)sub_482B70();
  //  sub_484A10(v2, 170, 0);
  //}
  
	/*SYSTEMTIME tt1;
	GetLocalTime(&tt1);

	int iTickMsec = (GetTickCount() - g_Fps.m_TickCount);

	if(iTickMsec >= 1000)
	{	
		gConsole.Output(cGREEN, "FPS: %02d --- TIME: %d)", g_Fps.m_iCount, pFpsTime2);

		g_Fps.m_TickCount = GetTickCount();
		g_Fps.m_iLastCount = g_Fps.m_iCount;
		g_Fps.m_iLastTick = pFpsTime2;
		g_Fps.m_iCount = 0;
	}*/

  
 for ( i = *(DWORD*)0xE8CB50; i >= g_Fps.m_iFPSTime; i -= g_Fps.m_iFPSTime )
 {
    v3 = (BYTE*)sub_790FB0();
    sub_791020(v3);
    if ( *(DWORD*)0xE609E8 == 2 || *(DWORD*)0xE609E8 == 4 )
    {
      v35 = sub_95C1C0((DWORD *)*(DWORD*)0xE8C598);
      if ( v35 >= 200.0 )
      {
        v27 = 200.0;
      }
      else
      {
        v27 = v35;
      }
      v35 = v27;
      sub_95C260((LARGE_INTEGER *)*(DWORD*)0xE8C598);
      v4 = (HWND)sub_407B20();
      sub_407C70(v4);
      v5 = sub_482B70();
      sub_4845E0((int)v5, v6, v27);
    }
    *(DWORD*)0xE7C3E4 = 0;
    switch ( *(DWORD*)0xE609E8 )
    {
      case 2:
        sub_4D7730();
        break;
      case 4:
        sub_4D6E70();
        break;
      case 5:
		if(!g_Fps.m_Disable[1])
		{
			sub_4D8FD0();
		}
        break;
    }

	if(!g_Fps.m_Disable[2])
	{
		for ( j = 0; j < 5; ++j )
		{
		  sub_51FDF0((char *)0xE8CB5C, 0.0049999999);
		}
		sub_5977A0();
		if ( sub_596A70(44) )
		{
		  *(BYTE*)0x87933FA = *(BYTE*)0x87933FA == 0;
		}
		if ( *(DWORD*)0x8793728 > 0 )
		{
		  --*(DWORD*)0x8793728;
		}
		if ( *(DWORD*)0x81C0404 > 0 )
		{
		  --*(DWORD*)0x81C0404;
		}
		++*(DWORD*)0x8787AA8;
		*(DWORD*)0x8787AA8 %= 32;
		++*(DWORD*)0xE8CB20;
	}
  }
  
  result = (unsigned __int8)*(BYTE*)0xE8C571;

  if ( !*(BYTE*)0xE8C571 )
  {
    sub_4FC520((char*)0x9816AA0);
    sub_6D6F10();
    GetLocalTime(&SystemTime);
    sub_9CF52A(
      (int)(BYTE*)0x8793278,
      "Images\\\\Screen(%02d_%02d-%02d_%02d)-%04d.jpg",
      SystemTime.wMonth,
      SystemTime.wDay,
      SystemTime.wHour,
      SystemTime.wMinute,
      *(DWORD*)0x8793404);
   // disable v8 = dec_402320(459);//sub_402320((char *)0x8128ADC, 459);	//sub_402320(459);
	//v8 = (const char *)sub_402320(459);
	//gConsole.Output(cGREEN, "[%s]", v8);
   // sub_9CF52A((int)(BYTE*)v37, v8, (DWORD*)0x8793278);
   sub_9CF52A((int)(BYTE*)v37, " %s: Screenshot Saved", (DWORD*)0x8793278);
    blue_4 = *(DWORD*)(0x7BC4F04 + 56);	//<<
    v10 = (char *)sub_953790();
    v11 = sub_954190(v10);
    wsprintfA(&v43, " [%s / %s]", v11, blue_4);
    sub_9CF3C0((char *)v37, (BYTE*)&v43);
    v44 = 1;
    if ( sub_790F40(16) == 1 )
    {
      v44 = 1 - v44;
    }
    if ( *(BYTE*)0x87933FA && v44 == 1 )
    {
      sub_409A50(&v32, (int)v37);
      v45 = 0;
      sub_409A50(&v31, (int)&*(BYTE*)0xD2713E);
	  v45 = 1;	//	LOBYTE(v45) = 1;
      v12 = (DWORD*)sub_860FC0();
      v13 = (char *)sub_861030(v12);
      sub_789390(v13, (int)&v31, (int)&v32, 3, 0);
      v45 = 0;	//LOBYTE(v45) = 0;
      sub_409AD0((PDWORD)&v31);
      v45 = -1;
      sub_409AD0((PDWORD)&v32);
    }
    if ( *(DWORD*)0xE61E18 == 10 )
    {
      glClearColor(0.01171875, 0.09765625, 0.171875, 1.0);
    }
    else if ( *(DWORD*)0xE61E18 != 73 && *(DWORD*)0xE61E18 != 74 )
    {
      if ( sub_4DB1C0(*(DWORD*)0xE61E18) )
      {
        glClearColor(0.1171875, 0.15625, 0.15625, 1.0);
      }
      else if ( sub_4E65A0(*(DWORD*)0xE61E18) == 1 )
      {
        glClearColor(0.0, 0.0, 0.0, 1.0);
      }
      else if ( (unsigned __int8)sub_4DB0E0(*(DWORD*)0xE61E18) && sub_4DB0F0((float *)(0x7BC4F04 + 1028)) )
      {
        glClearColor(0.0, 0.0, 0.0, 1.0);
      }
      else if ( *(DWORD*)0xE61E18 < 45 || *(DWORD*)0xE61E18 > 50 )
      {
        if ( *(DWORD*)0xE61E18 == 51 )
        {
          glClearColor(0.6953125, 0.6953125, 0.6953125, 1.0);
        }
        else if ( *(DWORD*)0xE61E18 == 65 )
        {
          glClearColor(0.578125, 0.69921875, 0.87109375, 1.0);
        }
        else
        {
          glClearColor(0.0, 0.0, 0.0, 1.0);
        }
      }
      else
      {
        glClearColor(0.03515625, 0.03125, 0.12890625, 1.0);
      }
    }
    else
    {
      glClearColor(0.0, 0.0, 0.0, 1.0);
    }
    glClear(0x4100u);
    v41 = 0;
    v38 = *(DWORD*)0xE8CB30;
    *(DWORD*)0xE8CB30 = GetTickCount();
	DWORD z117 = GetTickCount();	///
    v39 = 0;
    switch ( *(DWORD*)0xE609E8 )
    {
      case 2:
        v39 = sub_4D7970();	//sub_4D7970(v14);
        break;
      case 4:
        v39 = sub_4D70E0();	//sub_4D70E0(a1);
        break;
      case 5:
		if(!g_Fps.m_Disable[3])
		{
			v39 = sub_4D95E0();	//sub_4D95E0(v14);
		}
        break;
    }

	if(!g_Fps.m_Disable[9])
	{
		Sleep(50);
	}
	
	if(!g_Fps.m_Disable[4])
	{
		sub_51FEF0((char *)0xE8CB5C);
	}
	if(!g_Fps.m_Disable[5])
	{
		if ( *(BYTE*)0x87933FA )
		{
		  sub_635770();
		}
	}
    if ( *(BYTE*)0x87933FA && !v44 )
    {
      sub_409A50(&v30, (int)v37);
      v45 = 2;
      sub_409A50(&v29, (int)&*(BYTE*)0xD2713F);
      v45 = 3;	//LOBYTE(v45) = 3;
      v15 = (DWORD*)sub_860FC0();
      v16 = (char *)sub_861030(v15);
      sub_789390(v16, (int)&v29, (int)&v30, 3, 0);
      v45 = 2;	//LOBYTE(v45) = 2;
      sub_409AD0((LPDWORD)v29);
      v45 = -1;
      sub_409AD0((LPDWORD)v30);
    }
    
	if(!g_Fps.m_Disable[6])
	{
		*(BYTE*)0x87933FA = 0;
		if ( v39 )
		{
		  glFlush();
		  SwapBuffers(a1);	//a1
		}
	}
	/*************************************************/
   /* v41 = *(DWORD*)0xE8CB30 - v38;
    if ( v41 < g_Fps.m_iFPSTime )
    {
      dwMilliseconds = g_Fps.m_iFPSTime - v41;
	  Sleep(dwMilliseconds);	
	  *(DWORD*)0xE8CB30 += dwMilliseconds;
      v41 = g_Fps.m_iFPSTime;
    }
	 v40 = v41 + i;*/
	/*************************************************/
	/*int n;
    for ( n = GetTickCount() - z117; n < 40; n = GetTickCount() - z117 )
		{Sleep(40-n);}	//10
	  v40 = n;//v40 += n;
	  *(DWORD*)0xE8CB50 = n;//*(DWORD*)0xE8CB50 += n;*/
	/*************************************************/  
    v41 = *(DWORD*)0xE8CB30 - v38;
	v40 = v41 + i;
	/*************************************************/  
    //v41 = *(DWORD*)0xE8CB30 - v38;
	//if(g_Fps.m_iLastCount < 25 && *(DWORD*)0xE609E8 == 5)
	//{
		//if ( v41 < g_Fps.m_iFPSTime )
		//{
		//  dwMilliseconds = g_Fps.m_iFPSTime - v41;
		//  Sleep(dwMilliseconds);	
		//  *(DWORD*)0xE8CB30 += dwMilliseconds;
		//  v41 = g_Fps.m_iFPSTime;
		//}
	//}else
	//{
	//	gConsole.Output(cGREY, "g_Fps.m_iLastCount: %02d", g_Fps.m_iLastCount);
	//}
	 //v40 = v41 + i;
	/*************************************************/  
   
   if(!g_Fps.m_Disable[7])
   {
		if ( *(BYTE*)0xE8CB1F && *(DWORD*)0xE609E8 == 5 && sub_63A2B0((DWORD*)0x8793750) == -1 && !*(DWORD*)0xE8CB70 )
		{
		  *(DWORD*)0xE8CB70 = 1;
		  sub_96AD90((int)*(DWORD*)0xE8C5D8, (int)"> Connection closed. ");
		  sub_96B040(1);
		  v17 = (int*)sub_4DB260((LPDWORD)v28);
		  v45 = 4;
		  sub_4DB310(v17);
		  v45 = -1;
		  sub_4DB280(&v28);
		}
	}

	if(!g_Fps.m_Disable[8])
	{
		if ( *(DWORD*)0xE609E8 == 5 )
		{
		  switch ( *(DWORD*)0xE61E18 )
		  {
			case 0:
			  if ( *(DWORD*)0x81C0394 == 4 )
			  {
				sub_6D6D00(0, 1);
				sub_6D6D00(1, 1);
			  }
			  else
			  {
				sub_6D6AD0(0, 0, 1);
				if ( *(DWORD*)0x9761A2C > 0 )
				{
				  sub_6D6AD0(1, 0, 1);
				}
			  }
			  break;
			case 1:
			  sub_6D6AD0(3, 0, 1);
			  break;
			case 2:
			  if ( *(DWORD*)0x81C0394 != 3 && *(DWORD*)0x81C0394 < 10 )
			  {
				sub_6D6AD0(0, 0, 1);
			  }
			  else
			  {
				sub_6D6D00(0, 1);
			  }
			  break;
			case 3:
			  sub_6D6AD0(0, 0, 1);
			  if ( !((signed int)sub_9CFA0D() % 512) )
			  {
				sub_6D6AD0(2, 0, 0);
			  }
			  break;
			case 4:
			  sub_6D6AD0(5, 0, 1);
			  break;
			case 7:
			  sub_6D6AD0(6, 0, 1);
			  break;
			case 8:
			  sub_6D6AD0(7, 0, 1);
			  break;
			case 10:
			  sub_6D6AD0(20, 0, 1);
			  if ( (signed int)sub_9CFA0D() % 100 )
			  {
				sub_9CFA0D();
			  }
			  break;
			case 58:
			  sub_6D6AD0(0, 0, 1);
			  break;
			case 79:
			  sub_6D6AD0(0, 0, 1);
			  sub_6D6AD0(1, 0, 1);
			  break;
			case 80:
			  sub_6D6AD0(980, 0, 1);
			  break;
			case 81:
			  if ( *(DWORD*)0x81C0394 == 12 )
			  {
				sub_6D6D00(980, 1);
				sub_6D6AD0(982, 0, 1);
			  }
			  else
			  {
				sub_6D6D00(982, 1);
				sub_6D6AD0(980, 0, 1);
			  }
			  break;
			default:
			  break;
		  }
		  if ( *(DWORD*)0xE61E18 && *(DWORD*)0xE61E18 != 2 && *(DWORD*)0xE61E18 != 3 && *(DWORD*)0xE61E18 != 58 && *(DWORD*)0xE61E18 != 79 )
		  {
			sub_6D6D00(0, 1);
		  }
		  if ( *(DWORD*)0xE61E18 && !(unsigned __int8)sub_4E65E0() && *(DWORD*)0xE61E18 != 79 )
		  {
			sub_6D6D00(1, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 1 )
		  {
			sub_6D6D00(3, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 3 )
		  {
			sub_6D6D00(2, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 4 )
		  {
			sub_6D6D00(5, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 7 )
		  {
			sub_6D6D00(6, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 8 )
		  {
			sub_6D6D00(7, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 10 )
		  {
			sub_6D6D00(20, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 51 )
		  {
			sub_6D6D00(781, 1);
			sub_6D6D00(782, 1);
			sub_6D6D00(783, 1);
			sub_6D6D00(784, 1);
			sub_6D6D00(785, 1);
			sub_6D6D00(786, 1);
			sub_6D6D00(787, 1);
		  }
		  if ( !sub_90FC10() )
		  {
			sub_6D6D00(980, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 80 )
		  {
			sub_6D6D00(981, 1);
		  }
		  if ( *(DWORD*)0xE61E18 != 81 )
		  {
			sub_6D6D00(982, 1);
		  }
		  if ( *(DWORD*)0xE61E18 )
		  {
			sub_4CF000((int)0xE609F0, 0);
			sub_4CF000((int)0xE60A44, 0);
		  }
		  else if ( *(BYTE *)(0x7BC4F04 + 14) )
		  {
			if ( *(DWORD*)0x81C0394 == 4 )
			{
			  sub_4CF050((int)0xE609F0, 0);
			}
			else
			{
			  sub_4CF050((int)0xE60A44, 0);
			}
		  }
		  if ( *(DWORD*)0xE61E18 == 2 )
		  {
			if ( *(BYTE *)(0x7BC4F04 + 14) )	// <<
			{
			  if ( *(DWORD *)(0x7BC4F04 + 172) < 205
				|| *(DWORD *)(0x7BC4F04 + 172) > 214
				|| *(DWORD *)(0x7BC4F04 + 176) < 13
				|| *(DWORD *)(0x7BC4F04 + 176) > 31 )
			  {
				sub_4CF050((int)0xE609FC, 0);
			  }
			  else
			  {
				sub_4CF050((int)0xE609F8, 0);
			  }
			}
		  }
		  else
		  {
			sub_4CF000((int)0xE609F8, 0);
			sub_4CF000((int)0xE609FC, 0);
		  }
		  if ( *(DWORD*)0xE61E18 == 3 )
		  {
			if ( *(BYTE *)(0x7BC4F04 + 14) )
			{
			  sub_4CF050((int)0xE60A00, 0);
			}
		  }
		  else
		  {
			sub_4CF000((int)0xE60A00, 0);
		  }
		  if ( *(DWORD*)0xE61E18 != 1 && *(DWORD*)0xE61E18 != 5 )
		  {
			sub_4CF000((int)0xE60A04, 0);
		  }
		  else
		  {
			sub_4CF050((int)0xE60A04, 0);
		  }
		  if ( *(DWORD*)0xE61E18 == 7 )
		  {
			sub_4CF050((int)0xE60A08, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A08, 0);
		  }
		  if ( *(DWORD*)0xE61E18 == 10 )
		  {
			sub_4CF050((int)0xE60A0C, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A0C, 0);
		  }
		  if ( *(DWORD*)0xE61E18 == 8 )
		  {
			sub_4CF050((int)0xE60A10, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A10, 0);
		  }
		  if ( *(DWORD*)0xE61E18 == 4 )
		  {
			sub_4CF050((int)0xE60A14, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A14, 0);
		  }
		  if ( sub_4DB1C0(*(DWORD*)0xE61E18) )
		  {
			sub_4CF050((int)0xE60A1C, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A1C, 0);
		  }
		  if ( *(DWORD*)0xE61E18 == 31 )
		  {
			sub_4CF050((int)0xE60A2C, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A2C, 0);
		  }
		  if ( *(DWORD*)0xE61E18 == 33 )
		  {
			sub_4CF050((int)0xE60A30, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A30, 0);
		  }
		  sub_8D3270(*(DWORD*)0xE61E18);
		  sub_8B5080(*(DWORD*)0xE61E18);
		  if ( *(DWORD*)0xE61E18 == 37 )
		  {
			sub_4CF050((int)0xE60A48, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A48, 0);
		  }
		  sub_8ACA90();
		  v18 = sub_89C9B0();
		  sub_89DDF0(v18);
		  sub_91C880();
		  if ( sub_4DB1F0() )
		  {
			v19 = (DWORD*)sub_91C880();
			sub_920AE0(v19);
		  }
		  if ( *(DWORD*)0xE61E18 == 51 )
		  {
			sub_4CF050((int)0xE60A6C, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A6C, 0);
		  }
		  if ( *(DWORD*)0xE61E18 == 56 )
		  {
			sub_4CF050((int)0xE60A74, 0);
		  }
		  else
		  {
			sub_4CF000((int)0xE60A74, 0);
		  }
		  v20 = (BYTE *)sub_4DB390(57);
		  sub_8C4500(v20);
		  v21 = (void *)sub_4DB3C0(62);
		  sub_914AB0(v21);
		  void* v46 = (void *)sub_4DB3F0(63);
		  sub_8B8E90(v46);
		  v22 = (DWORD *)sub_4DB420(65);
		  sub_8DE660(v22);
		  v23 = (void *)sub_4DB450(69);
		  sub_8F03F0(v23);
		  v24 = (void *)sub_4DB480(70);
		  sub_8F4630(v24);
		  v25 = (void *)sub_4DB4B0(71);
		  sub_8F9110(v25);
		  v26 = (void *)sub_4DB4E0(72);
		  sub_8FEA40(v26);
		  sub_4DB510(79);
		  sub_91C1A0();
		  sub_4DB540(80);
		  sub_90FBA0();
		}
	}
    result = v40;
    *(DWORD*)0xE8CB50 = v40;
  }

  return result;
}

int CFps::RenderHookEx(HDC a1)
{
  BYTE *v1; // eax
  DWORD *v2; // eax
  BYTE *v3; // eax
  HWND v4; // eax
  void *v5; // eax
  int v6; // edx
  int result; // eax
  const char * v8; // eax
  int blue_4; // ST18_4
  char *v10; // eax
  int v11; // eax
  DWORD *v12; // eax
  char *v13; // eax
  void *v14; // ecx
  DWORD *v15; // eax
  char *v16; // eax
  int *v17; // ST20_4
  void *v18; // eax
  DWORD *v19; // eax
  BYTE *v20; // eax
  void *v21; // eax
  DWORD *v22; // eax
  void *v23; // eax
  void *v24; // eax
  void *v25; // eax
  void *v26; // eax
  double v27; // [esp+20h] [ebp-208h]
  char v28; // [esp+28h] [ebp-200h]
  char v29; // [esp+2Ch] [ebp-1FCh]
  char v30; // [esp+48h] [ebp-1E0h]
  char v31; // [esp+64h] [ebp-1C4h]
  char v32; // [esp+80h] [ebp-1A8h]
  DWORD dwMilliseconds; // [esp+9Ch] [ebp-18Ch]
  int j; // [esp+A0h] [ebp-188h]
  double v35; // [esp+A4h] [ebp-184h]
  int i; // [esp+B0h] [ebp-178h]
  __m128i v37[16]; // [esp+B4h] [ebp-174h]
  int v38; // [esp+1B4h] [ebp-74h]
  char v39; // [esp+1BBh] [ebp-6Dh]
  int v40; // [esp+1BCh] [ebp-6Ch]
  int v41; // [esp+1C0h] [ebp-68h]
  struct _SYSTEMTIME SystemTime; // [esp+1C4h] [ebp-64h]
  CHAR v43; // [esp+1D4h] [ebp-54h]
  int v44; // [esp+218h] [ebp-10h]
  int v45; // [esp+224h] [ebp-4h]

  //sub_542EF0();
  /*LPVOID p1 = sub_500E80();
  if ( !sub_40BC80((BYTE*)p1) )
  {
    LPVOID p2 = sub_482B70();
    //sub_484A10((DWORD*)p2, 170, 0);
  }
  */
  //for ( i = *(DWORD*)0xE8CB50; i >= 40; i -= 40 )
  while ( *(DWORD*)0xE8CB50 >= g_Fps.m_iFPSTime )
  {
    v3 = (BYTE*)sub_790FB0();
    sub_791020(v3);
    if ( *(DWORD*)0xE609E8 == 2 || *(DWORD*)0xE609E8 == 4 )
    {
      v35 = sub_95C1C0((DWORD *)*(DWORD*)0xE8C598);
      if ( v35 >= 200.0 )
      {
        v27 = 200.0;
      }
      else
      {
        v27 = v35;
      }
      v35 = v27;
      sub_95C260((LARGE_INTEGER *)*(DWORD*)0xE8C598);
      v4 = (HWND)sub_407B20();
      sub_407C70(v4);
      v5 = sub_482B70();
      sub_4845E0((int)v5, v6, v27);
    }
    *(DWORD*)0xE7C3E4 = 0;
    switch ( *(DWORD*)0xE609E8 )
    {
      case 2:
        sub_4D7730();
        break;
      case 4:
        sub_4D6E70();
        break;
      case 5:
        sub_4D8FD0();
        break;
    }
    for ( j = 0; j < 5; ++j )
    {
      sub_51FDF0((char *)0xE8CB5C, 0.0049999999);
    }
    sub_5977A0();
    if ( sub_596A70(44) )
    {
      *(BYTE*)0x87933FA = *(BYTE*)0x87933FA == 0;
    }
    if ( *(DWORD*)0x8793728 > 0 )
    {
      --*(DWORD*)0x8793728;
    }
    if ( *(DWORD*)0x81C0404 > 0 )
    {
      --*(DWORD*)0x81C0404;
    }
    ++*(DWORD*)0x8787AA8;
    *(DWORD*)0x8787AA8 %= 32;
    ++*(DWORD*)0xE8CB20;

	*(DWORD*)0xE8CB50 -= g_Fps.m_iFPSTime;
  }
  result = (unsigned __int8)*(BYTE*)0xE8C571;
  if ( !*(BYTE*)0xE8C571 )
  {
    sub_4FC520((char*)0x9816AA0);
    sub_6D6F10();
    GetLocalTime(&SystemTime);
    sub_9CF52A(
      (int)(BYTE*)0x8793278,
      "Images\\\\Screen(%02d_%02d-%02d_%02d)-%04d.jpg",
      SystemTime.wMonth,
      SystemTime.wDay,
      SystemTime.wHour,
      SystemTime.wMinute,
      *(DWORD*)0x8793404);
   // disable v8 = dec_402320(459);//sub_402320((char *)0x8128ADC, 459);	//sub_402320(459);
	//v8 = (const char *)sub_402320(459);
	//gConsole.Output(cGREEN, "[%s]", v8);
   // sub_9CF52A((int)(BYTE*)v37, v8, (DWORD*)0x8793278);
   sub_9CF52A((int)(BYTE*)v37, " %s: Screenshot Saved", (DWORD*)0x8793278);
    blue_4 = *(DWORD*)(0x7BC4F04 + 56);	//<<
    v10 = (char *)sub_953790();
    v11 = sub_954190(v10);
    wsprintfA(&v43, " [%s / %s]", v11, blue_4);
    sub_9CF3C0((char *)v37, (BYTE*)&v43);
    v44 = 1;
    if ( sub_790F40(16) == 1 )
    {
      v44 = 1 - v44;
    }
    if ( *(BYTE*)0x87933FA && v44 == 1 )
    {
      sub_409A50(&v32, (int)v37);
      v45 = 0;
      sub_409A50(&v31, (int)&*(BYTE*)0xD2713E);
	  v45 = 1;	//	LOBYTE(v45) = 1;
      v12 = (DWORD*)sub_860FC0();
      v13 = (char *)sub_861030(v12);
      sub_789390(v13, (int)&v31, (int)&v32, 3, 0);
      v45 = 0;	//LOBYTE(v45) = 0;
      sub_409AD0((LPDWORD)v31);
      v45 = -1;
      sub_409AD0((LPDWORD)v32);
    }
    if ( *(DWORD*)0xE61E18 == 10 )
    {
      glClearColor(0.01171875, 0.09765625, 0.171875, 1.0);
    }
    else if ( *(DWORD*)0xE61E18 != 73 && *(DWORD*)0xE61E18 != 74 )
    {
      if ( sub_4DB1C0(*(DWORD*)0xE61E18) )
      {
        glClearColor(0.1171875, 0.15625, 0.15625, 1.0);
      }
      else if ( sub_4E65A0(*(DWORD*)0xE61E18) == 1 )
      {
        glClearColor(0.0, 0.0, 0.0, 1.0);
      }
      else if ( (unsigned __int8)sub_4DB0E0(*(DWORD*)0xE61E18) && sub_4DB0F0((float *)(*(DWORD*)(0x7BC4F04 + 1028))) )
      {
        glClearColor(0.0, 0.0, 0.0, 1.0);
      }
      else if ( *(DWORD*)0xE61E18 < 45 || *(DWORD*)0xE61E18 > 50 )
      {
        if ( *(DWORD*)0xE61E18 == 51 )
        {
          glClearColor(0.6953125, 0.6953125, 0.6953125, 1.0);
        }
        else if ( *(DWORD*)0xE61E18 == 65 )
        {
          glClearColor(0.578125, 0.69921875, 0.87109375, 1.0);
        }
        else
        {
          glClearColor(0.0, 0.0, 0.0, 1.0);
        }
      }
      else
      {
        glClearColor(0.03515625, 0.03125, 0.12890625, 1.0);
      }
    }
    else
    {
      glClearColor(0.0, 0.0, 0.0, 1.0);
    }
    glClear(0x4100u);
    v41 = 0;
    //v38 = *(DWORD*)0xE8CB30;
    //*(DWORD*)0xE8CB30 = GetTickCount();
	DWORD z55 = GetTickCount();
    v39 = 0;
    switch ( *(DWORD*)0xE609E8 )
    {
      case 2:
        v39 = sub_4D7970();	//sub_4D7970(v14);
        break;
      case 4:
        v39 = sub_4D70E0();	//sub_4D70E0(a1);
        break;
      case 5:
        v39 = sub_4D95E0();	//sub_4D95E0(v14);
        break;
    }
    sub_51FEF0((char *)0xE8CB5C);
    if ( *(BYTE*)0x87933FA )
    {
      sub_635770();
    }
    if ( *(BYTE*)0x87933FA && !v44 )
    {
      sub_409A50(&v30, (int)v37);
      v45 = 2;
      sub_409A50(&v29, (int)&*(BYTE*)0xD2713F);
      v45 = 3;	//LOBYTE(v45) = 3;
      v15 = (DWORD*)sub_860FC0();
      v16 = (char *)sub_861030(v15);
      sub_789390(v16, (int)&v29, (int)&v30, 3, 0);
      v45 = 2;	//LOBYTE(v45) = 2;
      sub_409AD0((LPDWORD)v29);
      v45 = -1;
      sub_409AD0((LPDWORD)v30);
    }
    *(BYTE*)0x87933FA = 0;
    if ( v39 )
    {
      glFlush();
      SwapBuffers(a1);
    }

    /*v41 = *(DWORD*)0xE8CB30 - v38;
    if ( *(DWORD*)0xE8CB30 - v38 < 40 )
    {
      dwMilliseconds = 40 - v41;
      Sleep(40 - v41);
      *(DWORD*)0xE8CB30 += dwMilliseconds;
      v41 = 40;
    }
    v40 = v41 + i;*/

	//Sleep(10);


	// =====================

    /*DWORD z30 = GetTickCount();
    int z31 = LODWORD(z55);
    for ( result = (z30 - z55); (signed int)result < g_Fps.m_iFPSTime; result = (GetTickCount() - z31) )
	{
		//Sleep(10);
	}
    
    int z32 = (int)result + *(DWORD*)0xE8CB50;
    //result = *(BYTE*)0xE8CB1F;
	result = z32;
    *(DWORD*)0xE8CB50 = z32;*/

	// =====================

	int n = 0;

    for ( n = GetTickCount() - z55; n < 40; n = GetTickCount() - z55 )
	{
		Sleep(10);
	}

	*(DWORD*)0xE8CB50 += n;

	// =====================

    if ( *(BYTE*)0xE8CB1F && *(DWORD*)0xE609E8 == 5 && sub_63A2B0((DWORD*)0x8793750) == -1 && !*(DWORD*)0xE8CB70 )
    {
      *(DWORD*)0xE8CB70 = 1;
      sub_96AD90((int)*(DWORD*)0xE8C5D8, (int)"> Connection closed. ");
      sub_96B040(1);
      v17 = (int*)sub_4DB260((LPDWORD)v28);
      v45 = 4;
      sub_4DB310(v17);
      v45 = -1;
      sub_4DB280(&v28);
    }
    if ( *(DWORD*)0xE609E8 == 5 )
    {
      switch ( *(DWORD*)0xE61E18 )
      {
        case 0:
          if ( *(DWORD*)0x81C0394 == 4 )
          {
            sub_6D6D00(0, 1);
            sub_6D6D00(1, 1);
          }
          else
          {
            sub_6D6AD0(0, 0, 1);
            if ( *(DWORD*)0x9761A2C > 0 )
            {
              sub_6D6AD0(1, 0, 1);
            }
          }
          break;
        case 1:
          sub_6D6AD0(3, 0, 1);
          break;
        case 2:
          if ( *(DWORD*)0x81C0394 != 3 && *(DWORD*)0x81C0394 < 10 )
          {
            sub_6D6AD0(0, 0, 1);
          }
          else
          {
            sub_6D6D00(0, 1);
          }
          break;
        case 3:
          sub_6D6AD0(0, 0, 1);
          if ( !((signed int)sub_9CFA0D() % 512) )
          {
            sub_6D6AD0(2, 0, 0);
          }
          break;
        case 4:
          sub_6D6AD0(5, 0, 1);
          break;
        case 7:
          sub_6D6AD0(6, 0, 1);
          break;
        case 8:
          sub_6D6AD0(7, 0, 1);
          break;
        case 10:
          sub_6D6AD0(20, 0, 1);
          if ( (signed int)sub_9CFA0D() % 100 )
          {
            sub_9CFA0D();
          }
          break;
        case 58:
          sub_6D6AD0(0, 0, 1);
          break;
        case 79:
          sub_6D6AD0(0, 0, 1);
          sub_6D6AD0(1, 0, 1);
          break;
        case 80:
          sub_6D6AD0(980, 0, 1);
          break;
        case 81:
          if ( *(DWORD*)0x81C0394 == 12 )
          {
            sub_6D6D00(980, 1);
            sub_6D6AD0(982, 0, 1);
          }
          else
          {
            sub_6D6D00(982, 1);
            sub_6D6AD0(980, 0, 1);
          }
          break;
        default:
          break;
      }
      if ( *(DWORD*)0xE61E18 && *(DWORD*)0xE61E18 != 2 && *(DWORD*)0xE61E18 != 3 && *(DWORD*)0xE61E18 != 58 && *(DWORD*)0xE61E18 != 79 )
      {
        sub_6D6D00(0, 1);
      }
      if ( *(DWORD*)0xE61E18 && !(unsigned __int8)sub_4E65E0() && *(DWORD*)0xE61E18 != 79 )
      {
        sub_6D6D00(1, 1);
      }
      if ( *(DWORD*)0xE61E18 != 1 )
      {
        sub_6D6D00(3, 1);
      }
      if ( *(DWORD*)0xE61E18 != 3 )
      {
        sub_6D6D00(2, 1);
      }
      if ( *(DWORD*)0xE61E18 != 4 )
      {
        sub_6D6D00(5, 1);
      }
      if ( *(DWORD*)0xE61E18 != 7 )
      {
        sub_6D6D00(6, 1);
      }
      if ( *(DWORD*)0xE61E18 != 8 )
      {
        sub_6D6D00(7, 1);
      }
      if ( *(DWORD*)0xE61E18 != 10 )
      {
        sub_6D6D00(20, 1);
      }
      if ( *(DWORD*)0xE61E18 != 51 )
      {
        sub_6D6D00(781, 1);
        sub_6D6D00(782, 1);
        sub_6D6D00(783, 1);
        sub_6D6D00(784, 1);
        sub_6D6D00(785, 1);
        sub_6D6D00(786, 1);
        sub_6D6D00(787, 1);
      }
      if ( !sub_90FC10() )
      {
        sub_6D6D00(980, 1);
      }
      if ( *(DWORD*)0xE61E18 != 80 )
      {
        sub_6D6D00(981, 1);
      }
      if ( *(DWORD*)0xE61E18 != 81 )
      {
        sub_6D6D00(982, 1);
      }
      if ( *(DWORD*)0xE61E18 )
      {
        sub_4CF000((int)0xE609F0, 0);
        sub_4CF000((int)0xE60A44, 0);
      }
      else if ( *(BYTE *)(0x7BC4F04 + 14) )
      {
        if ( *(DWORD*)0x81C0394 == 4 )
        {
          sub_4CF050((int)0xE609F0, 0);
        }
        else
        {
          sub_4CF050((int)0xE60A44, 0);
        }
      }
      if ( *(DWORD*)0xE61E18 == 2 )
      {
        if ( *(BYTE *)(0x7BC4F04 + 14) )	// <<
        {
          if ( *(DWORD *)(0x7BC4F04 + 172) < 205
            || *(DWORD *)(0x7BC4F04 + 172) > 214
            || *(DWORD *)(0x7BC4F04 + 176) < 13
            || *(DWORD *)(0x7BC4F04 + 176) > 31 )
          {
            sub_4CF050((int)0xE609FC, 0);
          }
          else
          {
            sub_4CF050((int)0xE609F8, 0);
          }
        }
      }
      else
      {
        sub_4CF000((int)0xE609F8, 0);
        sub_4CF000((int)0xE609FC, 0);
      }
      if ( *(DWORD*)0xE61E18 == 3 )
      {
        if ( *(BYTE *)(0x7BC4F04 + 14) )
        {
          sub_4CF050((int)0xE60A00, 0);
        }
      }
      else
      {
        sub_4CF000((int)0xE60A00, 0);
      }
      if ( *(DWORD*)0xE61E18 != 1 && *(DWORD*)0xE61E18 != 5 )
      {
        sub_4CF000((int)0xE60A04, 0);
      }
      else
      {
        sub_4CF050((int)0xE60A04, 0);
      }
      if ( *(DWORD*)0xE61E18 == 7 )
      {
        sub_4CF050((int)0xE60A08, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A08, 0);
      }
      if ( *(DWORD*)0xE61E18 == 10 )
      {
        sub_4CF050((int)0xE60A0C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A0C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 8 )
      {
        sub_4CF050((int)0xE60A10, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A10, 0);
      }
      if ( *(DWORD*)0xE61E18 == 4 )
      {
        sub_4CF050((int)0xE60A14, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A14, 0);
      }
      if ( sub_4DB1C0(*(DWORD*)0xE61E18) )
      {
        sub_4CF050((int)0xE60A1C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A1C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 31 )
      {
        sub_4CF050((int)0xE60A2C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A2C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 33 )
      {
        sub_4CF050((int)0xE60A30, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A30, 0);
      }
      sub_8D3270(*(DWORD*)0xE61E18);
      sub_8B5080(*(DWORD*)0xE61E18);
      if ( *(DWORD*)0xE61E18 == 37 )
      {
        sub_4CF050((int)0xE60A48, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A48, 0);
      }
      sub_8ACA90();
      v18 = sub_89C9B0();
      sub_89DDF0(v18);
      sub_91C880();
      if ( sub_4DB1F0() )
      {
        v19 = (DWORD*)sub_91C880();
        sub_920AE0(v19);
      }
      if ( *(DWORD*)0xE61E18 == 51 )
      {
        sub_4CF050((int)0xE60A6C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A6C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 56 )
      {
        sub_4CF050((int)0xE60A74, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A74, 0);
      }
      v20 = (BYTE *)sub_4DB390(57);
      sub_8C4500(v20);
      v21 = (void *)sub_4DB3C0(62);
      sub_914AB0(v21);
      void* v46 = (void *)sub_4DB3F0(63);
      sub_8B8E90(v46);
      v22 = (DWORD *)sub_4DB420(65);
      sub_8DE660(v22);
      v23 = (void *)sub_4DB450(69);
      sub_8F03F0(v23);
      v24 = (void *)sub_4DB480(70);
      sub_8F4630(v24);
      v25 = (void *)sub_4DB4B0(71);
      sub_8F9110(v25);
      v26 = (void *)sub_4DB4E0(72);
      sub_8FEA40(v26);
      sub_4DB510(79);
      sub_91C1A0();
      sub_4DB540(80);
      sub_90FBA0();
    }
    //result = v40;
    //*(DWORD*)0xE8CB50 = v40;
  }
  return result;
}

int iProcNum2 = 0;
int iProcNum3 = 0;
int iProcNum4 = 0;
int iProcNum5 = 0;

bool getProcNum2()
{
	iProcNum2++;
	if(iProcNum2 >= 2)
	{
		iProcNum2 = 0;
		return true;
	}
	return false;
}

bool getProcNum3()
{
	iProcNum3++;
	if(iProcNum3 >= 3)
	{
		iProcNum3 = 0;
		return true;
	}
	return false;
}

bool getProcNum4()
{
	iProcNum4++;
	if(iProcNum4 >= 4)
	{
		iProcNum4 = 0;
		return true;
	}
	return false;
}

bool getProcNum5()
{
	iProcNum5++;
	if(iProcNum5 >= 5)
	{
		iProcNum5 = 0;
		return true;
	}
	return false;
}


  BYTE *v1; // eax
  DWORD *v2; // eax
  BYTE *v3; // eax
  HWND v4; // eax
  void *v5; // eax
  int v6; // edx
  int result; // eax
  const char * v8; // eax
  int blue_4; // ST18_4
  char *v10; // eax
  int v11; // eax
  DWORD *v12; // eax
  char *v13; // eax
  void *v14; // ecx
  DWORD *v15; // eax
  char *v16; // eax
  int *v17; // ST20_4
  void *v18; // eax
  DWORD *v19; // eax
  BYTE *v20; // eax
  void *v21; // eax
  DWORD *v22; // eax
  void *v23; // eax
  void *v24; // eax
  void *v25; // eax
  void *v26; // eax
  double v27; // [esp+20h] [ebp-208h]
  char v28; // [esp+28h] [ebp-200h]
  char v29; // [esp+2Ch] [ebp-1FCh]
  char v30; // [esp+48h] [ebp-1E0h]
  char v31; // [esp+64h] [ebp-1C4h]
  char v32; // [esp+80h] [ebp-1A8h]
  DWORD dwMilliseconds; // [esp+9Ch] [ebp-18Ch]
  int j; // [esp+A0h] [ebp-188h]
  double v35; // [esp+A4h] [ebp-184h]
  int i; // [esp+B0h] [ebp-178h]
  __m128i v37[16]; // [esp+B4h] [ebp-174h]
  int v38; // [esp+1B4h] [ebp-74h]
  char v39; // [esp+1BBh] [ebp-6Dh]
  int v40; // [esp+1BCh] [ebp-6Ch]
  int v41; // [esp+1C0h] [ebp-68h]
  struct _SYSTEMTIME SystemTime; // [esp+1C4h] [ebp-64h]
  CHAR v43; // [esp+1D4h] [ebp-54h]
  int v44; // [esp+218h] [ebp-10h]
  int v45; // [esp+224h] [ebp-4h]

  int iEx;

void CFps::Scene1()
{
  sub_542EF0();
  v1 = (BYTE*)sub_500E80();
  if ( !sub_40BC80(v1) )
  {
    v2 = (DWORD*)sub_482B70();
    //sub_484A10(v2, 170, 0);
  }
}

void CFps::Scene2()
{

 // for ( i = *(DWORD*)0xE8CB50; i >= 40; i -= 40 )	//40
  {
    v3 = (BYTE*)sub_790FB0();
    sub_791020(v3);
    if ( *(DWORD*)0xE609E8 == 2 || *(DWORD*)0xE609E8 == 4 )
    {
      double v35 = sub_95C1C0((DWORD *)*(DWORD*)0xE8C598);
      if ( v35 >= 200.0 )
      {
        v27 = 200.0;
      }
      else
      {
        v27 = v35;
      }
      v35 = v27;
      sub_95C260((LARGE_INTEGER *)*(DWORD*)0xE8C598);
      v4 = (HWND)sub_407B20();
      sub_407C70(v4);
      v5 = sub_482B70();
      sub_4845E0((int)v5, v6, v27);
    }
    *(DWORD*)0xE7C3E4 = 0;
    switch ( *(DWORD*)0xE609E8 )
    {
      case 2:
        sub_4D7730();
        break;
      case 4:
        sub_4D6E70();
        break;
      case 5:
        sub_4D8FD0();
        break;
    }
    for ( j = 0; j < 5; ++j )
    {
      sub_51FDF0((char *)0xE8CB5C, 0.0049999999);
    }
    sub_5977A0();
    if ( sub_596A70(44) )
    {
      *(BYTE*)0x87933FA = *(BYTE*)0x87933FA == 0;
    }
    if ( *(DWORD*)0x8793728 > 0 )
    {
      --*(DWORD*)0x8793728;
    }
    if ( *(DWORD*)0x81C0404 > 0 )
    {
      --*(DWORD*)0x81C0404;
    }
    ++*(DWORD*)0x8787AA8;
    *(DWORD*)0x8787AA8 %= 32;
    ++*(DWORD*)0xE8CB20;
  }
}

void CFps::Scene3()
{


    sub_4FC520((char*)0x9816AA0);
    sub_6D6F10();
    GetLocalTime(&SystemTime);
    sub_9CF52A(
      (int)(BYTE*)0x8793278,
      "Images\\\\Screen(%02d_%02d-%02d_%02d)-%04d.jpg",
      SystemTime.wMonth,
      SystemTime.wDay,
      SystemTime.wHour,
      SystemTime.wMinute,
      *(DWORD*)0x8793404);
   // disable v8 = dec_402320(459);//sub_402320((char *)0x8128ADC, 459);	//sub_402320(459);
	//v8 = (const char *)sub_402320(459);
	//gConsole.Output(cGREEN, "[%s]", v8);
   // sub_9CF52A((int)(BYTE*)v37, v8, (DWORD*)0x8793278);
   sub_9CF52A((int)(BYTE*)v37, " %s: Screenshot Saved", (DWORD*)0x8793278);
    blue_4 = *(DWORD*)(0x7BC4F04 + 56);	//<<
    v10 = (char *)sub_953790();
    v11 = sub_954190(v10);
    wsprintfA(&v43, " [%s / %s]", v11, blue_4);
    sub_9CF3C0((char *)v37, (BYTE*)&v43);
    v44 = 1;
    if ( sub_790F40(16) == 1 )
    {
      v44 = 1 - v44;
    }
    if ( *(BYTE*)0x87933FA && v44 == 1 )
    {
      sub_409A50(&v32, (int)v37);
      v45 = 0;
      sub_409A50(&v31, (int)&*(BYTE*)0xD2713E);
	  v45 = 1;	//	LOBYTE(v45) = 1;
      v12 = (DWORD*)sub_860FC0();
      v13 = (char *)sub_861030(v12);
      sub_789390(v13, (int)&v31, (int)&v32, 3, 0);
      v45 = 0;	//LOBYTE(v45) = 0;
      sub_409AD0((LPDWORD)v31);
      v45 = -1;
      sub_409AD0((LPDWORD)v32);
    }
    if ( *(DWORD*)0xE61E18 == 10 )
    {
      glClearColor(0.01171875, 0.09765625, 0.171875, 1.0);
    }
    else if ( *(DWORD*)0xE61E18 != 73 && *(DWORD*)0xE61E18 != 74 )
    {
      if ( sub_4DB1C0(*(DWORD*)0xE61E18) )
      {
        glClearColor(0.1171875, 0.15625, 0.15625, 1.0);
      }
      else if ( sub_4E65A0(*(DWORD*)0xE61E18) == 1 )
      {
        glClearColor(0.0, 0.0, 0.0, 1.0);
      }
      else if ( (unsigned __int8)sub_4DB0E0(*(DWORD*)0xE61E18) && sub_4DB0F0((float *)(0x7BC4F04 + 1028)) )
      {
        glClearColor(0.0, 0.0, 0.0, 1.0);
      }
      else if ( *(DWORD*)0xE61E18 < 45 || *(DWORD*)0xE61E18 > 50 )
      {
        if ( *(DWORD*)0xE61E18 == 51 )
        {
          glClearColor(0.6953125, 0.6953125, 0.6953125, 1.0);
        }
        else if ( *(DWORD*)0xE61E18 == 65 )
        {
          glClearColor(0.578125, 0.69921875, 0.87109375, 1.0);
        }
        else
        {
          glClearColor(0.0, 0.0, 0.0, 1.0);
        }
      }
      else
      {
        glClearColor(0.03515625, 0.03125, 0.12890625, 1.0);
      }
    }
    else
    {
      glClearColor(0.0, 0.0, 0.0, 1.0);
    }
    glClear(0x4100u);

    v41 = 0;
    v38 = *(DWORD*)0xE8CB30;
    *(DWORD*)0xE8CB30 = GetTickCount();
   
	/**/



}

void CFps::Scene4()
{
	if(g_Fps.m_iDelay >= 40)
	//if(getProcNum2())
	//if(i >= 40)
	{
		switch ( *(DWORD*)0xE609E8 )
		{
		case 2:
			v39 = sub_4D7970();
			break;
		case 4:
			v39 = sub_4D70E0();
			break;
		case 5:
			v39 = sub_4D95E0();
			break;
		}
		
	//}

		sub_51FEF0((char *)0xE8CB5C);

		if(*(BYTE*)0x87933FA)
		{
			sub_635770();
		}

		if(*(BYTE*)0x87933FA && !v44)
		{
			sub_409A50(&v30, (int)v37);
			v45 = 2;
			sub_409A50(&v29, (int)&*(BYTE*)0xD2713F);
			v45 = 3;	//LOBYTE(v45) = 3;
			v15 = (DWORD*)sub_860FC0();
			v16 = (char *)sub_861030(v15);
			sub_789390(v16, (int)&v29, (int)&v30, 3, 0);
			v45 = 2;	//LOBYTE(v45) = 2;
			sub_409AD0((LPDWORD)v29);
			v45 = -1;
			sub_409AD0((LPDWORD)v30);
		}
	}
	
}

void CFps::Scene5()
{
    if ( *(BYTE*)0xE8CB1F && *(DWORD*)0xE609E8 == 5 && sub_63A2B0((DWORD*)0x8793750) == -1 && !*(DWORD*)0xE8CB70 )
    {
      *(DWORD*)0xE8CB70 = 1;
      sub_96AD90((int)*(DWORD*)0xE8C5D8, (int)"> Connection closed. ");
      sub_96B040(1);
      v17 = (int*)sub_4DB260((LPDWORD)v28);
      v45 = 4;
      sub_4DB310(v17);
      v45 = -1;
      sub_4DB280(&v28);
    }
}

void CFps::Scene6()
{
    if ( *(DWORD*)0xE609E8 == 5 )	//5
    {
      switch ( *(DWORD*)0xE61E18 )
      {
        case 0:
          if ( *(DWORD*)0x81C0394 == 4 )
          {
            sub_6D6D00(0, 1);
            sub_6D6D00(1, 1);
          }
          else
          {
            sub_6D6AD0(0, 0, 1);
            if ( *(DWORD*)0x9761A2C > 0 )
            {
              sub_6D6AD0(1, 0, 1);
            }
          }
          break;
        case 1:
          sub_6D6AD0(3, 0, 1);
          break;
        case 2:
          if ( *(DWORD*)0x81C0394 != 3 && *(DWORD*)0x81C0394 < 10 )
          {
            sub_6D6AD0(0, 0, 1);
          }
          else
          {
            sub_6D6D00(0, 1);
          }
          break;
        case 3:
          sub_6D6AD0(0, 0, 1);
          if ( !((signed int)sub_9CFA0D() % 512) )
          {
            sub_6D6AD0(2, 0, 0);
          }
          break;
        case 4:
          sub_6D6AD0(5, 0, 1);
          break;
        case 7:
          sub_6D6AD0(6, 0, 1);
          break;
        case 8:
          sub_6D6AD0(7, 0, 1);
          break;
        case 10:
          sub_6D6AD0(20, 0, 1);
          if ( (signed int)sub_9CFA0D() % 100 )
          {
            sub_9CFA0D();
          }
          break;
        case 58:
          sub_6D6AD0(0, 0, 1);
          break;
        case 79:
          sub_6D6AD0(0, 0, 1);
          sub_6D6AD0(1, 0, 1);
          break;
        case 80:
          sub_6D6AD0(980, 0, 1);
          break;
        case 81:
          if ( *(DWORD*)0x81C0394 == 12 )
          {
            sub_6D6D00(980, 1);
            sub_6D6AD0(982, 0, 1);
          }
          else
          {
            sub_6D6D00(982, 1);
            sub_6D6AD0(980, 0, 1);
          }
          break;
        default:
          break;
      }
      if ( *(DWORD*)0xE61E18 && *(DWORD*)0xE61E18 != 2 && *(DWORD*)0xE61E18 != 3 && *(DWORD*)0xE61E18 != 58 && *(DWORD*)0xE61E18 != 79 )
      {
        sub_6D6D00(0, 1);
      }
      if ( *(DWORD*)0xE61E18 && !(unsigned __int8)sub_4E65E0() && *(DWORD*)0xE61E18 != 79 )
      {
        sub_6D6D00(1, 1);
      }
      if ( *(DWORD*)0xE61E18 != 1 )
      {
        sub_6D6D00(3, 1);
      }
      if ( *(DWORD*)0xE61E18 != 3 )
      {
        sub_6D6D00(2, 1);
      }
      if ( *(DWORD*)0xE61E18 != 4 )
      {
        sub_6D6D00(5, 1);
      }
      if ( *(DWORD*)0xE61E18 != 7 )
      {
        sub_6D6D00(6, 1);
      }
      if ( *(DWORD*)0xE61E18 != 8 )
      {
        sub_6D6D00(7, 1);
      }
      if ( *(DWORD*)0xE61E18 != 10 )
      {
        sub_6D6D00(20, 1);
      }
      if ( *(DWORD*)0xE61E18 != 51 )
      {
        sub_6D6D00(781, 1);
        sub_6D6D00(782, 1);
        sub_6D6D00(783, 1);
        sub_6D6D00(784, 1);
        sub_6D6D00(785, 1);
        sub_6D6D00(786, 1);
        sub_6D6D00(787, 1);
      }
      if ( !sub_90FC10() )
      {
        sub_6D6D00(980, 1);
      }
      if ( *(DWORD*)0xE61E18 != 80 )
      {
        sub_6D6D00(981, 1);
      }
      if ( *(DWORD*)0xE61E18 != 81 )
      {
        sub_6D6D00(982, 1);
      }
      if ( *(DWORD*)0xE61E18 )
      {
        sub_4CF000((int)0xE609F0, 0);
        sub_4CF000((int)0xE60A44, 0);
      }
      else if ( *(BYTE *)(0x7BC4F04 + 14) )
      {
        if ( *(DWORD*)0x81C0394 == 4 )
        {
          sub_4CF050((int)0xE609F0, 0);
        }
        else
        {
          sub_4CF050((int)0xE60A44, 0);
        }
      }
      if ( *(DWORD*)0xE61E18 == 2 )
      {
        if ( *(DWORD*)(0x7BC4F04 + 14) )	// <<
        {
          if ( *(DWORD *)(0x7BC4F04 + 172) < 205
            || *(DWORD *)(0x7BC4F04 + 172) > 214
            || *(DWORD *)(0x7BC4F04 + 176) < 13
            || *(DWORD *)(0x7BC4F04 + 176) > 31 )
          {
            sub_4CF050((int)0xE609FC, 0);
          }
          else
          {
            sub_4CF050((int)0xE609F8, 0);
          }
        }
      }
      else
      {
        sub_4CF000((int)0xE609F8, 0);
        sub_4CF000((int)0xE609FC, 0);
      }
      if ( *(DWORD*)0xE61E18 == 3 )
      {
        if ( *(BYTE *)(0x7BC4F04 + 14) )
        {
          sub_4CF050((int)0xE60A00, 0);
        }
      }
      else
      {
        sub_4CF000((int)0xE60A00, 0);
      }
      if ( *(DWORD*)0xE61E18 != 1 && *(DWORD*)0xE61E18 != 5 )
      {
        sub_4CF000((int)0xE60A04, 0);
      }
      else
      {
        sub_4CF050((int)0xE60A04, 0);
      }
      if ( *(DWORD*)0xE61E18 == 7 )
      {
        sub_4CF050((int)0xE60A08, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A08, 0);
      }
      if ( *(DWORD*)0xE61E18 == 10 )
      {
        sub_4CF050((int)0xE60A0C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A0C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 8 )
      {
        sub_4CF050((int)0xE60A10, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A10, 0);
      }
      if ( *(DWORD*)0xE61E18 == 4 )
      {
        sub_4CF050((int)0xE60A14, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A14, 0);
      }
      if ( sub_4DB1C0(*(DWORD*)0xE61E18) )
      {
        sub_4CF050((int)0xE60A1C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A1C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 31 )
      {
        sub_4CF050((int)0xE60A2C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A2C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 33 )
      {
        sub_4CF050((int)0xE60A30, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A30, 0);
      }
      sub_8D3270(*(DWORD*)0xE61E18);
      sub_8B5080(*(DWORD*)0xE61E18);
      if ( *(DWORD*)0xE61E18 == 37 )
      {
        sub_4CF050((int)0xE60A48, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A48, 0);
      }
      sub_8ACA90();
      v18 = sub_89C9B0();
      sub_89DDF0(v18);
      sub_91C880();
      if ( sub_4DB1F0() )
      {
        v19 = (DWORD*)sub_91C880();
        sub_920AE0(v19);
      }
      if ( *(DWORD*)0xE61E18 == 51 )
      {
        sub_4CF050((int)0xE60A6C, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A6C, 0);
      }
      if ( *(DWORD*)0xE61E18 == 56 )
      {
        sub_4CF050((int)0xE60A74, 0);
      }
      else
      {
        sub_4CF000((int)0xE60A74, 0);
      }
      v20 = (BYTE *)sub_4DB390(57);
      sub_8C4500(v20);
      v21 = (void *)sub_4DB3C0(62);
      sub_914AB0(v21);
      void* v46 = (void *)sub_4DB3F0(63);
      sub_8B8E90(v46);
      v22 = (DWORD *)sub_4DB420(65);
      sub_8DE660(v22);
      v23 = (void *)sub_4DB450(69);
      sub_8F03F0(v23);
      v24 = (void *)sub_4DB480(70);
      sub_8F4630(v24);
      v25 = (void *)sub_4DB4B0(71);
      sub_8F9110(v25);
      v26 = (void *)sub_4DB4E0(72);
      sub_8FEA40(v26);
      sub_4DB510(79);
      sub_91C1A0();
      sub_4DB540(80);
      sub_90FBA0();
    }
}

int CFps::RenderDev(HDC a1)
{
	g_Fps.Scene1();

	for ( i = *(DWORD*)0xE8CB50; i >= 40; i -= 40 )	//40
	{
		g_Fps.Scene2();

		//break;
	}

  result = (unsigned __int8)*(BYTE*)0xE8C571;

  if ( !*(BYTE*)0xE8C571)
  {

	g_Fps.Scene3();

	v39 = 0;

	g_Fps.Scene4();

	*(BYTE*)0x87933FA = 0;

    if ( v39 )
    {
      glFlush();
      SwapBuffers(a1);
    }

	Sleep(1);
	v40 = *(DWORD*)0xE8CB30 - v38 + i;

	g_Fps.Scene5();

	g_Fps.Scene6();

    result = v40;
    *(DWORD*)0xE8CB50 = v40;

	g_Fps.m_iDelay = v40;
  }
  return result;
}

#endif