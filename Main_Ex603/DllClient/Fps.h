#pragma once

#if(DEBUG_FPS)

//=======================================================================================================

#define sub_542EF0	((int(*)()) 0x542EF0)		//int sub_542EF0()
#define sub_500E80	((void *(*)()) 0x500E80)	//void *sub_500E80()
#define sub_40BC80	((char(__thiscall*)(BYTE *This)) 0x40BC80)	//char __thiscall sub_40BC80(_BYTE *this)
#define sub_482B70	((void *(*)()) 0x482B70)	//void *sub_482B70()
#define sub_790FB0	((void *(*)()) 0x790FB0)	//void *sub_790FB0()
#define sub_484A10	((DWORD *(__thiscall*)(DWORD *This, int a2, int a3)) 0x484A10)	//_DWORD *__thiscall sub_484A10(_DWORD *this, int a2, int a3)
#define sub_791020	((char(__thiscall*)(BYTE *This)) 0x791020)	//char __thiscall sub_791020(_BYTE *this)
#define sub_95C1C0	((double(__thiscall*)(DWORD *This)) 0x95C1C0)	//double __thiscall sub_95C1C0(_DWORD *this)
#define sub_95C260	((DWORD(__thiscall*)(LARGE_INTEGER *This)) 0x95C260)	//DWORD __thiscall sub_95C260(LARGE_INTEGER *this)
#define sub_407B20	((void *(*)()) 0x407B20)	//void *sub_407B20()
#define sub_407C70	((HWND(__thiscall*)(HWND This)) 0x407C70)	//HWND __thiscall sub_407C70(HWND this)
#define sub_482B70	((void*(*)()) 0x482B70)	//void *sub_482B70()
#define sub_4845E0	((int(__fastcall*)(int a1, int a2, double a3)) 0x4845E0)	//int __fastcall sub_4845E0(int a1, int a2, double a3)
#define sub_4D7730	((char(*)()) 0x4D7730)	//char sub_4D7730()
#define sub_4D6E70	((void(*)()) 0x4D6E70)	//void sub_4D6E70()
#define sub_4D8FD0	((int(*)()) 0x4D8FD0)	//int sub_4D8FD0()
#define sub_51FDF0	((int(__thiscall*)(char *This, float a2)) 0x51FDF0)	//int __thiscall sub_51FDF0(char *this, float a2)
#define sub_5977A0	((int(*)()) 0x5977A0)	//int sub_5977A0()
#define sub_596A70	((char(__cdecl*)(int a1)) 0x596A70)	//char __cdecl sub_596A70(int a1)
#define sub_4FC520	((int(__thiscall*)(char *This)) 0x4FC520)	//int __thiscall sub_4FC520(char *this)
#define sub_6D6F10	((int(*)()) 0x6D6F10)	//int sub_6D6F10()

//#define sub_9CF52A	((signed int(*)(BYTE *a1, int a2, ...)) 0x9CF52A)	//signed int sub_9CF52A(_BYTE *a1, int a2, ...)
#define sub_9CF52A	((int(*)(int a1, const char *a2, ...)) 0x9CF52A)	//int sub_9CF52A(int a1, const char *a2, ...)

//#define sub_402320	((int(__thiscall*)(char *This, int a1)) 0x402320)	//int __thiscall sub_402320(char *this, int a1)
#define sub_402320	((int(__stdcall*)(int a1)) 0x402320)	//int __stdcall sub_402320(int a1)

#define sub_953790	((void *(*)()) 0x953790)	//void *sub_953790()
#define sub_954190	((int(__thiscall*)(char *This)) 0x954190)	//int __thiscall sub_954190(char *this)
#define sub_9CF3C0	((char *(__cdecl*)(char *a1, BYTE *a2)) 0x9CF3C0)	//char *__cdecl sub_9CF3C0(char *a1, _BYTE *a2)
#define sub_790F40	((int(__cdecl*)(int a1)) 0x790F40)	//int __cdecl sub_790F40(int a1)
#define sub_409A50	((int(__thiscall*)(void *This, int a2)) 0x409A50)	//int __thiscall sub_409A50(void *this, int a2)
#define sub_860FC0	((void *(*)()) 0x860FC0)	//void *sub_860FC0()
#define sub_861030	((int(__thiscall*)(DWORD *This)) 0x861030)	//int __thiscall sub_861030(_DWORD *this)
#define sub_789390	((int(__thiscall*)(char *This, int a2, int a3, int a4, int a5)) 0x789390)	//int __thiscall sub_789390(char *this, int a2, int a3, int a4, int a5)
#define sub_409AD0	((int(__thiscall*)(DWORD *This)) 0x409AD0)	//int __thiscall sub_409AD0(_DWORD *this)
#define sub_4DB1C0	((bool(__cdecl*)(signed int a1)) 0x4DB1C0)	//bool __cdecl sub_4DB1C0(signed int a1)
#define sub_4E65A0	((bool(__cdecl*)(signed int a1)) 0x4E65A0)	//bool __cdecl sub_4E65A0(signed int a1)
#define sub_4DB0E0	((BOOL(__cdecl*)(int a1)) 0x4DB0E0)	//BOOL __cdecl sub_4DB0E0(int a1)
#define sub_4DB0F0	((bool(__cdecl*)(float *a1)) 0x4DB0F0)	//bool __cdecl sub_4DB0F0(float *a1)

#define sub_4D7970	((char(*)()) 0x4D7970)	//char sub_4D7970()
#define sub_4D70E0	((char(*)()) 0x4D70E0)	//char sub_4D70E0()
#define sub_4D95E0	((char(*)()) 0x4D95E0)	//char sub_4D95E0()
#define sub_51FEF0	((int(__thiscall*)(char *This)) 0x51FEF0)	//int __thiscall sub_51FEF0(char *this)
#define sub_635770	((int(*)()) 0x635770)	//int sub_635770()
#define sub_63A2B0	((int(__thiscall*)(DWORD *This)) 0x63A2B0)	//int __thiscall sub_63A2B0(_DWORD *this)
#define sub_96AD90	((int(*)(int a1, int a2, ...)) 0x96AD90)	//int sub_96AD90(int a1, int a2, ...)
#define sub_96B040	((int(__stdcall*)(int a1)) 0x96B040)	//int __stdcall sub_96B040(int a1)
#define sub_4DB260	((DWORD *(__thiscall*)(DWORD *This)) 0x4DB260)	//_DWORD *__thiscall sub_4DB260(_DWORD *this)
#define sub_4DB310	((char(__cdecl*)(int *a1)) 0x4DB310)	//char __cdecl sub_4DB310(int *a1)
#define sub_4DB280	((int(__thiscall*)(void *This)) 0x4DB280)	//int __thiscall sub_4DB280(void *this)

#define sub_6D6D00	((int(__cdecl*)(int a1, int a2)) 0x6D6D00)	//int __cdecl sub_6D6D00(int a1, int a2)
#define sub_6D6AD0	((signed int(__cdecl*)(int a1, int a2, int a3)) 0x6D6AD0)	//signed int __cdecl sub_6D6AD0(int a1, int a2, int a3)
#define sub_9CFA0D	((int(*)()) 0x9CFA0D)	//int sub_9CFA0D()
#define sub_4E65E0	((bool(*)()) 0x4E65E0)	//bool sub_4E65E0()
#define sub_90FC10	((bool(*)()) 0x90FC10)	//bool sub_90FC10()
#define sub_4CF000	((void(__cdecl*)(int a1, int a2)) 0x4CF000)	//void __cdecl sub_4CF000(int a1, int a2)
#define sub_4CF050	((int(__cdecl*)(int a1, int a2)) 0x4CF050)	//int __cdecl sub_4CF050(int a1, int a2)


#define sub_8D3270	((void(__cdecl*)(int a1)) 0x8D3270)	//void __cdecl sub_8D3270(int a1)
#define sub_8B5080	((void(__cdecl*)(int a1)) 0x8B5080)	//void __cdecl sub_8B5080(int a1)
#define sub_8ACA90	((void(*)()) 0x8ACA90)	//void sub_8ACA90()
#define sub_89C9B0	((int *(*)()) 0x89C9B0)	//int *sub_89C9B0()
#define sub_89DDF0	((void(__thiscall*)(void *This)) 0x89DDF0)	//void __thiscall sub_89DDF0(void *this)
#define sub_91C880	((int *(*)()) 0x91C880)	//int *sub_91C880()
#define sub_4DB1F0	((bool(*)()) 0x4DB1F0)	//bool sub_4DB1F0()
#define sub_920AE0	((void(__thiscall*)(DWORD *This)) 0x920AE0)	//void __thiscall sub_920AE0(_DWORD *this)

#define sub_4DB390	((int(__cdecl*)(int a1)) 0x4DB390)	//int __cdecl sub_4DB390(int a1)
#define sub_8C4500	((void(__thiscall*)(BYTE *This)) 0x8C4500)	//void __thiscall sub_8C4500(_BYTE *this)
#define sub_4DB3C0	((int(__cdecl*)(int a1)) 0x4DB3C0)	//int __cdecl sub_4DB3C0(int a1)
#define sub_914AB0	((int(__thiscall*)(void *This)) 0x914AB0)	//int __thiscall sub_914AB0(void *this)
#define sub_4DB3F0	((int(__cdecl*)(int a1)) 0x4DB3F0)	//int __cdecl sub_4DB3F0(int a1)
#define sub_8B8E90	((void(__thiscall*)(void *This)) 0x8B8E90)	//void __thiscall sub_8B8E90(void *this)
#define sub_4DB420	((int(__cdecl*)(int a1)) 0x4DB420)	//int __cdecl sub_4DB420(int a1)
#define sub_8DE660	((void(__thiscall*)(DWORD *This)) 0x8DE660)	//void __thiscall sub_8DE660(_DWORD *this)
#define sub_4DB450	((int(__cdecl*)(int a1)) 0x4DB450)	//int __cdecl sub_4DB450(int a1)
#define sub_8F03F0	((void(__thiscall*)(void *This)) 0x8F03F0)	//void __thiscall sub_8F03F0(void *this)
#define sub_4DB480	((int(__cdecl*)(int a1)) 0x4DB480)	//int __cdecl sub_4DB480(int a1)
#define sub_8F4630	((void(__thiscall*)(void *This)) 0x8F4630)	//void __thiscall sub_8F4630(void *this)
#define sub_4DB4B0	((int(__cdecl*)(int a1)) 0x4DB4B0)	//int __cdecl sub_4DB4B0(int a1)


#define sub_8F9110	((void(__thiscall*)(void *This)) 0x8F9110)	//void __thiscall sub_8F9110(void *this)
#define sub_4DB4E0	((int(__cdecl*)(int a1)) 0x4DB4E0)	//int __cdecl sub_4DB4E0(int a1)
#define sub_8FEA40	((void(__thiscall*)(void *This)) 0x8FEA40)	//void __thiscall sub_8FEA40(void *this)
#define sub_4DB510	((int(__cdecl*)(int a1)) 0x4DB510)	//int __cdecl sub_4DB510(int a1)
#define sub_91C1A0	((void(*)()) 0x91C1A0)	//void sub_91C1A0()
#define sub_4DB540	((int(__cdecl*)(int a1)) 0x4DB540)	//int __cdecl sub_4DB540(int a1)
#define sub_90FBA0	((void(*)()) 0x90FBA0)	//void sub_90FBA0()


/// -> Decompile Function
#define dec_402320		((int(__stdcall*)(int a1)) 0x402320)
//=======================================================================================================
#define sub_407B90	((char(__thiscall*)(int This, int a2, int a3, int a4)) 0x407B90)	//char __thiscall sub_407B90(int this, int a2, int a3, int a4)

//=======================================================================================================

#define pFpsTime1	*(int*)0x0E8CB30
#define pFpsTime2	*(int*)0x0E8CB50
#define p4D9CF0		((int(__cdecl*)(HDC a1)) 0x4D9CF0)
#define p542EF0		((int(*)()) 0x542EF0)

#define FPS_TIME_COUNT	40

int __cdecl hook_4DAD00(HDC a1);

class CFps
{
public:
	void Load();
	static int Render(HDC a1);
	void SetDelay(BYTE btTick);
	void Button(DWORD Key);
	void NeedTime(char* InfoText);
	void Draw();

	void CameraLoad();
	void CameraButton(DWORD Event);
	void CameraMain(float Zoom);

	void Clear();

	static int RenderHook(HDC a1);
	static int RenderDebug(HDC a1);
	static int RenderHookEx(HDC a1);
	static int RenderDev(HDC a1);

	static void Scene1();
	static void Scene2();
	static void Scene3();
	static void Scene4();
	static void Scene5();
	static void Scene6();

	int m_FrameCount;
	int m_TickCount;
	int m_iTimeSecond;
	int m_iCount;
	int m_iLastCount;
	int m_iLastTick;
	int m_iDelay;


//private:
	float m_flZ1;
	float m_flZ2;
	float m_flGL;
	float m_flY;
	float m_flX;

	int m_iFPSTime;

	int m_iFPSTick;
	char m_szFPSName[10][32];
	int m_iFPSNeed[10];
	int m_iFPSCount;

	bool m_StopWatchStart;
	int m_StopWatchTime;
	int m_StopWatchTick;

	bool m_Disable[10];
	DWORD m_Adress[5];

	double m_dCPU;
};

extern CFps g_Fps;





#endif