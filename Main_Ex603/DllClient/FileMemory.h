#pragma once

#include "stdafx.h"

#if(ENABLE_FILEMEMORY)

#define pTerrainLoad		((signed int(__cdecl*)(char* filename)) 0x5D6810)

#define pFileOpen		((FILE* (__cdecl*)(char* filename, LPVOID param)) 0x9CFEC0)
#define pFileEncrypt	((int(__cdecl*)(LPVOID type, LPVOID buffer, int size)) 0x54D9F0)

void FileMemoryLoad();

#endif