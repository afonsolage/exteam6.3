#pragma once

#ifndef TOOL
#include "stdafx.h"
#endif

#if(ENABLE_ENCODER)

class CEncDec
{
public:
		CEncDec();
		~CEncDec();

	void Init();
	void Load();

	void Main(char* filename);
	void GetBuffer(char* filename);
	void SetBuffer(char* filename);
	void PackBuffer();
	void ClearBuffer();

	BYTE m_XoR[3];
	HANDLE m_File;
	DWORD m_WriteFileSize;
	char* m_PackBuff;
	DWORD m_PackSize;
};

extern CEncDec g_EncDec;

#endif