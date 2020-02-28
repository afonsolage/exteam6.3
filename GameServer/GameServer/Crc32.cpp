#include "stdafx.h"
#include "Crc32.h"

CCrc32 g_Crc32;

CCrc32::CCrc32()
{
	::memset(&this->Addr, NULL, sizeof(this->Addr));
	
	for(int i = 0; i <= 255; i++)
	{
		this->Addr[i]	= this->Set(i, 8) << 24;
		
		for(int y = 0; y < 8; y++)
		{
			Addr[i]		= (Addr[i] << 1) ^ (Addr[i] & (1 << 31) ? 0x04C11DB7 : 0);
		}

		Addr[i]			= this->Set(Addr[i], 32);
	}
}

CCrc32::~CCrc32()
{
}

unsigned long CCrc32::Set(unsigned long Replace, char szMsg)
{
	unsigned long Res	= 0;

	for(int i = 1; i < (szMsg + 1); i++)
	{
		if(Replace & 1) Res |= 1 << (szMsg - i); Replace >>= 1;
	}

	return Res;
}

void CCrc32::Repl(unsigned long * szBytes, unsigned char * szBuff, unsigned long Length)
{
	while(Length--)
	{
		*szBytes = (*szBytes >> 8) ^ this->Addr[(*szBytes & 0xFF) ^ *szBuff++];
	}
}

unsigned long CCrc32::Get(const char * szFile)
{
	unsigned long Buff			= 0xFFFFFFFF;
	FILE * FilePath				= NULL;
	int ReadBytes				= NULL;

	unsigned char szBuff[1024]	= {0};	

	if((FilePath = fopen(szFile, "rb")) == NULL)
	{
		return 0xFFFFFFFF;
	}

	do
	{
		ReadBytes = fread(szBuff, sizeof(char), 1024, FilePath);
		
		this->Repl(&Buff, szBuff, ReadBytes);
	}
	while(ReadBytes == 1024);
	
	fclose(FilePath);
	
	return(Buff ^ 0xFFFFFFFF);
}
