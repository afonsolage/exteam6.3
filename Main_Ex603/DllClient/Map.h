#pragma once

#include "stdafx.h"

#if(CUSTOM_NEW_MAP)


#define sub_5EC0E0				((char(__cdecl*)(int a1))0x5EC0E0)
#define sub_6D8F20 ((void(__cdecl*)(int a1,  DWORD * a2, int a3, int a4, int a5, int a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, float a11, __int16 a12))0x6D8F20)
//void __cdecl sub_6D8F20(int a1, int a2, int a3, int a4, int a5, int a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, float a11, __int16 a12)

//int __thiscall sub_545030(float *this, int a2, int a3, int a4, char a5)
#define sub_545030				((char(__thiscall*)(float *This, int a2, int a3, int a4, char a5))0x545030)

#define sub_72D060	((void(__cdecl*)(int a1, int a2, int a3, int a4, int a5, int a6, float a7, __int16 a8, __int16 a9, char a10, int a11, int a12, __int16 a13))0x72D060)
//void __cdecl sub_72D060(int a1, int a2, int a3, int a4, int a5, int a6, float a7, __int16 a8, __int16 a9, char a10, int a11, int a12, __int16 a13)
//0x7D92 - Effect\clouds.jpg

		 /*

		if(v2 == 93)	
			for (int m = 0; m < 20; ++m )
                pPlayDynamicEffect(32293, (DWORD *)(a1 + 252), (int )(a1 + 264), &v62, 1, *(float *)(a1 + 96), a1);

		 96
		 90
		 101
		 92
		 93
		 98
		 102
		 103
		 */

class CMap
{
public:
	void Load();
	static void NewMap();
	static void NewMapWellcome();
	static char* GetNewMapName(int MapNumber);
	static void NewMapName();
	static void NewMapEffect(int a1);
};
extern CMap g_Map;


#endif