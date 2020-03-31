#include "stdafx.h"
#include "TMemory.h"
//#include "ToolKit.h"

#include "Other.h"
#include "Console.h"
#include "Defines.h"
#include "Interface.h"
#include "Camera.h"
#include "Import.h"
#include "Configs.h"
#include "detours.h"


Start gStart;

int exWinWidth;
int exWinHeight;

int InGameEffects		= GetPrivateProfileIntA("Graphics","FixGraphics",1,".\\Settings.ini");
int Anisotropy			= GetPrivateProfileIntA("Graphics","Anisotropy",1,".\\Settings.ini");
int MaxAnisotropy		= GetPrivateProfileIntA("Graphics","MaxAnisotropy",1,".\\Settings.ini");
int Linear				= GetPrivateProfileIntA("Graphics","Linear",1,".\\Settings.ini");

//-----------------
//OGL Function Prototypes
void (WINAPI *glEnable_original)(GLenum cap) = glEnable;
void (WINAPI *glClearColor_original)(GLclampf r,GLclampf g,GLclampf b,GLclampf a) = glClearColor;
int g_nMaxAnisotropy = MaxAnisotropy;

void WINAPI glEnable_hook(GLenum mode)
{
	// ---
	if(InGameEffects != 0)
	{
		if(Anisotropy != 0)
		{
			glGetIntegerv(0x84FF,&g_nMaxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy-0.1);
		}
		if(Linear != 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	else
	{
		if(Anisotropy != 0)
		{
			glGetIntegerv(0x84FF,&g_nMaxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy-0.1);
		}
		if(Linear != 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	glEnable_original(mode);
}

void Start::InitOGLHook()
{	
	//---- glEnable
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID &)glEnable_original,glEnable_hook);
	DetourTransactionCommit();

}


#ifdef DEBUG_DRAW__
#define sub_636420 ((double (__cdecl *)(float)) 0x636420)
#define sub_636450 ((double (__cdecl *)(float)) 0x636450)

double Start::Crack_sub_636420(float a1)
{
	//return 640.0;
	return (float)((double)(unsigned int)/*width*/exWinWidth * a1 / exWinWidth);//640
}

double Start::Crack_sub_636450(float a1)
{
	//return 480.0;
	 return (float)((double)(unsigned int)/*height*/exWinHeight * a1 / exWinHeight);	//480
}

//double __cdecl sub_636420(float a1)

//double __cdecl sub_636450(float a1)

void Start::Init_sub_636420_sub_636450()
{

//		Address   Command                                  Comments
		SetOp((LPVOID)0x006378B3, (LPVOID)Crack_sub_636420, ASM::CALL);//006378B3  CALL 00636420
		SetOp((LPVOID)0x006378D7, (LPVOID)Crack_sub_636420, ASM::CALL);//006378D7  CALL 00636420
		SetOp((LPVOID)0x00637A6D, (LPVOID)Crack_sub_636420, ASM::CALL);//00637A6D  CALL 00636420
		//SetOp((LPVOID)0x00637A91, (LPVOID)Crack_sub_636420, ASM::CALL);//00637A91  CALL 00636420
		//SetOp((LPVOID)0x00637C75, (LPVOID)Crack_sub_636420, ASM::CALL);//00637C75  CALL 00636420	//cursor
		//SetOp((LPVOID)0x00637CA1, (LPVOID)Crack_sub_636420, ASM::CALL);//00637CA1  CALL 00636420
		SetOp((LPVOID)0x00637E90, (LPVOID)Crack_sub_636420, ASM::CALL);//00637E90  CALL 00636420
		SetOp((LPVOID)0x00637EB4, (LPVOID)Crack_sub_636420, ASM::CALL);//00637EB4  CALL 00636420
		SetOp((LPVOID)0x00638140, (LPVOID)Crack_sub_636420, ASM::CALL);//00638140  CALL 00636420
		SetOp((LPVOID)0x00638164, (LPVOID)Crack_sub_636420, ASM::CALL);//00638164  CALL 00636420
		SetOp((LPVOID)0x00638417, (LPVOID)Crack_sub_636420, ASM::CALL);//00638417  CALL 00636420
		SetOp((LPVOID)0x0063843B, (LPVOID)Crack_sub_636420, ASM::CALL);//0063843B  CALL 00636420
		SetOp((LPVOID)0x0063845F, (LPVOID)Crack_sub_636420, ASM::CALL);//0063845F  CALL 00636420
		SetOp((LPVOID)0x00638918, (LPVOID)Crack_sub_636420, ASM::CALL);//00638918  CALL 00636420
		SetOp((LPVOID)0x00638955, (LPVOID)Crack_sub_636420, ASM::CALL);//00638955  CALL 00636420
		SetOp((LPVOID)0x00638E9D, (LPVOID)Crack_sub_636420, ASM::CALL);//00638E9D  CALL 00636420
		SetOp((LPVOID)0x00638EC1, (LPVOID)Crack_sub_636420, ASM::CALL);//00638EC1  CALL 00636420


		SetOp((LPVOID)0x006378C5, (LPVOID)Crack_sub_636450, ASM::CALL);//006378B3  CALL 00636420
		SetOp((LPVOID)0x006378E9, (LPVOID)Crack_sub_636450, ASM::CALL);//006378D7  CALL 00636420
		SetOp((LPVOID)0x00637A7F, (LPVOID)Crack_sub_636450, ASM::CALL);//00637A6D  CALL 00636420
		//SetOp((LPVOID)0x00637AA3, (LPVOID)Crack_sub_636450, ASM::CALL);//00637A91  CALL 00636420
		//SetOp((LPVOID)0x00637C87, (LPVOID)Crack_sub_636450, ASM::CALL);//00637C75  CALL 00636420
		//SetOp((LPVOID)0x00637CB3, (LPVOID)Crack_sub_636450, ASM::CALL);//00637CA1  CALL 00636420
		SetOp((LPVOID)0x00637EA2, (LPVOID)Crack_sub_636450, ASM::CALL);//00637E90  CALL 00636420
		SetOp((LPVOID)0x00637EC6, (LPVOID)Crack_sub_636450, ASM::CALL);//00637EB4  CALL 00636420
		SetOp((LPVOID)0x00638152, (LPVOID)Crack_sub_636450, ASM::CALL);//00638140  CALL 00636420
		SetOp((LPVOID)0x00638176, (LPVOID)Crack_sub_636450, ASM::CALL);//00638164  CALL 00636420
		SetOp((LPVOID)0x00638429, (LPVOID)Crack_sub_636450, ASM::CALL);//00638417  CALL 00636420
		SetOp((LPVOID)0x0063844D, (LPVOID)Crack_sub_636450, ASM::CALL);//0063843B  CALL 00636420
		SetOp((LPVOID)0x00638471, (LPVOID)Crack_sub_636450, ASM::CALL);//0063845F  CALL 00636420
		SetOp((LPVOID)0x0063892A, (LPVOID)Crack_sub_636450, ASM::CALL);//00638918  CALL 00636420
		SetOp((LPVOID)0x00638967, (LPVOID)Crack_sub_636450, ASM::CALL);//00638955  CALL 00636420
		SetOp((LPVOID)0x00638EAF, (LPVOID)Crack_sub_636450, ASM::CALL);//00638E9D  CALL 00636420
		SetOp((LPVOID)0x00638ED3, (LPVOID)Crack_sub_636450, ASM::CALL);//00638EC1  CALL 00636420

		//Search - References to constant 00636450
		//	Address   Command                                  Comments
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450
		//	  CALL 00636450


}
#endif
//-----------------




DWORD dwAllowTabSwitchLoginJMP = 0x0040B16F;
Naked(AllowTabSwitchLogin)
{
	_asm
	{
		PUSH 0
		MOV EAX, DWORD PTR SS : [EBP - 0x38]
		MOV ECX, DWORD PTR DS : [EAX + 0x350]
		MOV EDX, DWORD PTR SS : [EBP - 0x38]
		MOV EAX, DWORD PTR DS : [EDX + 0x350]
		MOV EDX, DWORD PTR DS : [EAX]
		CALL DWORD PTR DS : [EDX + 0x30]
		// ----
		MOV EAX, DWORD PTR SS : [EBP-0x38]
		MOV ECX, DWORD PTR DS : [EAX+0x354]
		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x38]
		MOV ECX, DWORD PTR DS : [EDX + 0x350]
		MOV EAX, DWORD PTR SS : [EBP - 0x38]
		MOV EDX, DWORD PTR DS : [EAX + 0x350]
		MOV EAX, DWORD PTR DS : [EDX]
		CALL DWORD PTR DS : [EAX + 0x58]
		// ----
		MOV ECX, DWORD PTR SS : [EBP - 0x38]
		MOV EDX, DWORD PTR DS : [ECX + 0x350]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x38]
		MOV ECX, DWORD PTR DS : [EAX + 0x354]
		MOV EDX, DWORD PTR SS : [EBP - 0x38]
		MOV EAX, DWORD PTR DS : [EDX + 0x354]
		MOV EDX, DWORD PTR DS : [EAX]
		CALL DWORD PTR DS : [EDX + 0x58]
		// ----
		PUSH 0
		MOV ECX, DWORD PTR SS : [EBP - 0x38]
		MOV EDX, DWORD PTR DS : [ECX + 0x354]
		MOV EAX, DWORD PTR SS : [EBP - 0x38]
		MOV ECX, DWORD PTR DS : [EAX + 0x354]
		MOV EDX, DWORD PTR DS : [EDX]
		MOV EAX, DWORD PTR DS : [EDX + 0x30]
		CALL EAX
			// ----
		JMP dwAllowTabSwitchLoginJMP
	}
}

void Start::Load()
{
#ifdef DEBUG_DRAW__
	Init_sub_636420_sub_636450();
#endif
#if(ENABLE_IP_ADDRESS)
	strcpy(this->IP,TEXT_IP_ADDRESS);
#else
	strcpy(this->IP,gConfig.MyIp);
#endif
#ifdef _SERIAL_
	strcpy(this->Serial,_SERIAL_);
#elif DEBUG
	strcpy(this->Serial,gConfig.Serial);
#endif
#ifdef _VERSION_
	strcpy(this->Version,_VERSION_);	//1.03.25
#elif DEBUG
	strcpy(this->Version,gConfig.Version);
#endif

	SetRange((LPVOID)0x0040B154, 5, ASM::NOP);
	SetOp((LPVOID)0x0040B154, AllowTabSwitchLogin, ASM::JMP);

	this->Connect();
	this->Fix();
	this->InitOGLHook();
}

void Start::Connect()
{
	WriteMemory((LPDWORD)IP_ADDRESS, this->IP, sizeof(this->IP));
#if (_SERIAL_ || DEBUG)
	WriteMemory((PDWORD)SERIAL_MAIN, this->Serial, sizeof(this->Serial));
#endif
#if (_VERSION_ || DEBUG)
	WriteMemory((PDWORD)VERSION_MAIN, this->Version, sizeof(this->Version));
#endif
}

void Start::Fix()
{
#if(TEST_WIN10)

	if(gConfig.LauncherActive != 2)
	{
		SetByteEx((DWORD)0x004D1E69, 0xEB);			//-> Disable MU.exe call
	}

	SetByteEx((DWORD)0x004D2246, 0xEB);			//-> Disable Config.ini

	// ----
	SetWord((PVOID)(0x0040B4BA + 2), 0x350);	//-> Disable CMStarter
	SetWord((PVOID)(0x0040B4C3 + 2), 0x350);	//-> Disable CMStarter
	SetByteEx((DWORD)(0x0040B4CD + 2), 0x18);		//-> Disable CMStarter
	// ----
	SetByteEx((DWORD)0x004D9D24, 0xEB);			//-> Disable web check
	SetByteEx((DWORD)(0x0040AF09 + 1), 0x00);		//-> Enable account field

	// ----
	SetByteEx((DWORD)0x004D559C, 0xEB);
	SetByteEx((DWORD)0x00633F7A, 0xEB);
	SetByteEx((DWORD)0x00634403, 0xEB);
	SetByteEx((DWORD)0x0063E6C4, 0xEB);
	SetRange((PVOID)0x004D556F, 5, ASM::NOP);	//-> Disable ResourceGuard Call
	SetRange((PVOID)0x00633F4D, 5, ASM::NOP);	//-> Disable ResourceGuard Call
	SetRange((PVOID)0x006343D6, 5, ASM::NOP);	//-> Disable ResourceGuard Call
	SetRange((PVOID)0x0063E697, 5, ASM::NOP);	//-> Disable ResourceGuard Call

#else

	if(gConfig.LauncherActive != 2)
	{
		SetByte((PVOID)0x004D1E69, 0xEB);			//-> Disable MU.exe call
	}

	SetByte((PVOID)0x004D2246, 0xEB);			//-> Disable Config.ini

	// ----
	SetWord((PVOID)(0x0040B4BA + 2), 0x350);	//-> Disable CMStarter
	SetWord((PVOID)(0x0040B4C3 + 2), 0x350);	//-> Disable CMStarter
	SetByte((PVOID)(0x0040B4CD + 2), 0x18);		//-> Disable CMStarter
	// ----
	SetByte((PVOID)0x004D9D24, 0xEB);			//-> Disable web check
	SetByte((PVOID)(0x0040AF09 + 1), 0x00);		//-> Enable account field

	// ----
	SetByte((PVOID)0x004D559C, 0xEB);
	SetByte((PVOID)0x00633F7A, 0xEB);
	SetByte((PVOID)0x00634403, 0xEB);
	SetByte((PVOID)0x0063E6C4, 0xEB);
	SetRange((PVOID)0x004D556F, 5, ASM::NOP);	//-> Disable ResourceGuard Call
	SetRange((PVOID)0x00633F4D, 5, ASM::NOP);	//-> Disable ResourceGuard Call
	SetRange((PVOID)0x006343D6, 5, ASM::NOP);	//-> Disable ResourceGuard Call
	SetRange((PVOID)0x0063E697, 5, ASM::NOP);	//-> Disable ResourceGuard Call

#endif

	//-> Money transfer limit
	SetByte((PVOID)(0x007AF025 + 1), 9);
	SetByte((PVOID)(0x007AF2C5 + 1), 9);
	SetByte((PVOID)(0x007AF645 + 1), 9);
	SetByte((PVOID)(0x007B01C5 + 1), 9);

	//-> MuHelper Info
	SetByte((PVOID)(0x0064CBCE + 2), 0);

	//-> MuHelper All Levels
	SetByte((PVOID)(0x0095CD6D+2),0);

#ifdef ANTI_CTRL
	SetByte((PVOID)(0x0052101A+1), 0x02);
#endif
	
#if(FULL_HD==1)
	SetOp((LPVOID)0x004D2180, (LPVOID)this->GameLoad, ASM::CALL);
	SetOp((LPVOID)0x00830A56, (LPVOID)this->MoveListInit, ASM::CALL);
	SetOp((LPVOID)0x00832D88, (LPVOID)this->MoveListInit, ASM::CALL);
#endif

	static char * LogName		= "Data\\InfoLog\\Error.log";
	static char * LogName2		= "Data\\InfoLog\\Error_%d.log";
	static char * DumpName		= "Data\\InfoLog\\Error.dmp";
	static char * ScreenName	= "ScreenShots\\Screen(%02d_%02d-%02d_%02d)-%04d.jpg";
	// ----
	SetDword((PVOID)(0x0096A8C8+1), (DWORD)LogName);
	SetDword((PVOID)(0x0096A94F+1), (DWORD)LogName);
	SetDword((PVOID)(0x0096A9DB+1), (DWORD)LogName2);
	SetDword((PVOID)(0x004D1D0B+1), (DWORD)DumpName);
	SetDword((PVOID)(0x004D9F54+1), (DWORD)ScreenName);

	//SpeedBug Fix?
#if(SPEED_BUG_FIX)
	SetByte((PVOID)(0x00649E24 + 3), 14);	//-> 1 Method
	SetByte((PVOID)(0x00556C32 + 6), 2);	//-> 2 Method
#endif

	SetByte((PVOID)oVulcanusMove, 0);

	this->SpeedCalc();
	
	//remaining second 
	SetRange((PVOID)0x005B9E6A, 5, ASM::NOP);
	SetRange((PVOID)0x005B9EBA, 5, ASM::NOP);

	 // Fix Check .map files
	 SetByte((LPVOID)0x0062EBF8, 0xEB);
	 SetByte((LPVOID)0x0062EBFE, 0xEB);
	 // Fix Check .att files
	 SetByte((LPVOID)0x0062EE42, 0xEB);
	 SetByte((LPVOID)0x0062EE48, 0xEB);
	 // Fix Check .obj files
	 SetByte((LPVOID)0x0062EEE5, 0xEB);
	 SetByte((LPVOID)0x0062EEEB, 0xEB);

	 // Fix Buff Limit 
	 SetByte((LPVOID)(0x00777D74+2), 0xFF);
	 SetByte((LPVOID)(0x004ADD59+3), 0xFF);
	 SetByte((LPVOID)(0x00644F74+3), 0xFF);
	 SetByte((LPVOID)(0x004ADCC0+3), 0xFF);

	 //TerrainHeight
	 //TerrainLight

	 #if(DEV_FPS)
	 //SetByte((LPVOID)(0x004DA3AC + 3), 0x28);	 // -> fps  0x1F
	 #endif
	 
}


int Start::GameLoad()
{
	pGameLoad();
	// ----
	//pGameResolutionMode = 7;
	switch(pGameResolutionMode)
	{
	case 0:
		pWinWidth		= 640;
		pWinHeight		= 480;
		break;
		// --
	case 1:
		pWinWidth		= 800;
		pWinHeight		= 600;
		break;
		// --
	case 2:
		pWinWidth		= 1024;
		pWinHeight		= 768;
		break;
		// --
	case 3:
		pWinWidth		= 1152;
		pWinHeight		= 864;
		break;
		// --
	case 4:
		pWinWidth		= 1280;
		pWinHeight		= 768;
		break;
		// --
	case 5:
		pWinWidth		= 1280;
		pWinHeight		= 800;
		break;
		// --
	case 6:
		pWinWidth		= 1280;
		pWinHeight		= 960;
		break;
		// --
	case 7:
		pWinWidth		= 1280;
		pWinHeight		= 1024;
		break;
		// --
	case 8:
		pWinWidth		= 1366;
		pWinHeight		= 768;
		break;
		// --
	case 9:
		pWinWidth		= 1440;
		pWinHeight		= 900;
		break;
		// --
	case 10:
		pWinWidth		= 1600;
		pWinHeight		= 900;
		break;
		// --
	case 11:
		pWinWidth		= 1600;
		pWinHeight		= 1200;
		break;
		// --
	case 12:
		pWinWidth		= 1680;
		pWinHeight		= 1050;
		break;
		// --
	case 13:
		pWinWidth		= 1920;
		pWinHeight		= 1080;
		break;
		// --
	case 14:
		pWinWidth		= 1920;
		pWinHeight		= 1200;
		break;
		// --
	case 15:
		pWinWidth		= 1024;
		pWinHeight		= 600;
		break;
		// --
	case 16:
		pWinWidth		= 1910;
		pWinHeight		= 970;
		break;
		// --
	case 17:
		pWinWidth		= 1350;
		pWinHeight		= 650;
		break;
		// --
	}
	// ----
	pWinFontHeight	= 15;
	pWinWidthReal	= (float)pWinWidth / MAX_WIN_WIDTH;
	pWinHeightReal	= (float)pWinHeight / MAX_WIN_HEIGHT;
	SetDouble((LPVOID)oCam_ClipX, gCamera.Default.ClipX + 500);
	SetFloat((LPVOID)oCam_ClipGL, gCamera.Default.ClipGL + 200);
	// ----

	exWinWidth  = pWinWidth;
	exWinHeight = pWinHeight;

	return 1;
}
// ----------------------------------------------------------------------------------------------

void Start::MoveListInit(LPVOID This, LPVOID EDX, int Arg1, int Arg2)
{
	GLsizei TempWidth = pWinWidth;
	pWinWidth = 1280;
	pMoveListInit(This, Arg1, Arg2);
	pWinWidth = TempWidth;
}

void Start::SpeedCalc()
{
#ifdef EX_SPEED_CALC
	
	//Default
	SetByte((PVOID)(0x00593C4D + 1), 20);	//00593C4D + 1 -> str Speed -> 20
	SetByte((PVOID)(0x00593C60 + 1), 10);	//00593C60 + 1 -> Mag Speed -> 10
	//Class 6
	SetByte((PVOID)(0x00593C25 + 1), 9);	//00593C25 + 1 -> str Speed -> 9
	SetByte((PVOID)(0x00593C38 + 1), 9);	//00593C38 + 1 -> Mag Speed -> 9

	// Class 5
	SetByte((PVOID)(0x00593BF7 + 1), 20);	//00593BF7 + 1 -> str Speed -> 20
	SetByte((PVOID)(0x00593C0A + 1), 20);	//00593C0A + 1 -> Mag Speed -> 20

	//Class 4
	SetByte((PVOID)(0x00593BC6 + 1), 10);	//00593BC6 + 1 -> str Speed -> 10
	SetByte((PVOID)(0x00593BD9 + 1), 10);	//00593BD9 + 1 -> Mag Speed -> 10

	//Class 2
	SetByte((PVOID)(0x00593B5E + 1), 50);	//00593B5E + 1 -> str Speed -> 50
	SetByte((PVOID)(0x00593B71 + 1), 50);	//00593B71 + 1 -> Mag Speed -> 50

	//Class 1 & 3
	SetByte((PVOID)(0x00593B95 + 1), 15);	//00593B95 + 1 -> str Speed -> 15
	SetByte((PVOID)(0x00593BA8 + 1), 20);	//00593BA8 + 1 -> Mag Speed -> 20
	
#endif
}