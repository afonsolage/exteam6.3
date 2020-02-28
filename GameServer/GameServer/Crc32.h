#pragma once

#include "stdafx.h"

class CCrc32
{
public:
	CCrc32();
	~CCrc32();

	unsigned long Get(const char * szFile);	
	void		  Repl(unsigned long * szBytes, unsigned char * szBuff, unsigned long Length);
	unsigned long Set(unsigned long Replace, char szMsg);

	unsigned long Addr[256];
}; 
extern CCrc32 g_Crc32;