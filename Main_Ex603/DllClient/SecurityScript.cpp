#include "stdafx.h"
#include "SecurityScript.h"
#include "TMemory.h"

#if(SECURITY_SCRIPT==TRUE)

SecurityScript g_SecurityScript;

//HANDLE		m_hFile= INVALID_HANDLE_VALUE;;

BYTE XorTableLock[]	= { 0xD4, 0x7B, 0x2B };

SecurityScript::SecurityScript()
{
	this->m_pBuffer			= NULL;
	this->m_iBufferSize		= 0;
	//this->m_hFile			= INVALID_HANDLE_VALUE;
}
// -----------------------------------------------------------------------

SecurityScript::~SecurityScript()
{
	Close();
}
// -----------------------------------------------------------------------

void SecurityScript::Encode(char* buffer, int size)
{
	for (int i=0;i<size; i++)
	{
		buffer[i]=buffer[i]^XorTableLock[i%3];	
	}
}

void SecurityScript::SetScriptBuffer( char* buffer, int size)
{
	this->m_pBuffer = buffer;
	this->m_iBufferSize = size;
}

void SecurityScript::Close()
{
	if ( this->m_pBuffer != 0)
	{
		free( this->m_pBuffer );
		m_iBufferSize = 0;
	}
}



int SecurityScript::ReadScript(char * File)
{
	//if( m_hFile != INVALID_HANDLE_VALUE )
	//{
	//	CloseHandle(m_hFile);
	//}

	HANDLE m_hFile = CreateFile(File, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0x80, NULL);
	// ----
	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		return 0;
	}
	// ----
	int filesize = GetFileSize(m_hFile, NULL);
	// ----
	char* pBuffer = (char*)malloc(filesize);
	// ----
	DWORD iReadFileSize;
	// ----
	ReadFile(m_hFile, pBuffer, filesize, &iReadFileSize, 0);
	// ----
	if(iReadFileSize == 0)
	{
		this->Close();
	}
	// ----
	Encode(pBuffer, iReadFileSize);
	// ----
	SetScriptBuffer(pBuffer, iReadFileSize);
	// ----
	CloseHandle(m_hFile);
	// ----
	return 1;
}

int SecurityScript::WriteScript(char * File)
{
	//if( m_hFile != INVALID_HANDLE_VALUE )
	//{
	//	CloseHandle(m_hFile);
	//}

	HANDLE m_hFile = CreateFile(File, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0x80, NULL);
	// ----
	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		return 0;
	}
	// ----
	//Encode(m_pBuffer, m_iBufferSize);
	// ----
	DWORD iReadFileSize;
	// ----
	WriteFile(m_hFile, m_pBuffer, m_iBufferSize, &iReadFileSize, 0);
	// ----
	if(iReadFileSize == 0)
	{
		Close();
	}
	// ----
	CloseHandle(m_hFile);
	// ----
	return 1;
}


#define sub_5D6810				((signed int(__cdecl*)(char* a1)) 0x5D6810)
#define sub_5D6E50				((signed int(__cdecl*)(char* a1)) 0x5D6E50	)
#define sub_5F33F0				((signed int(__cdecl*)(char* a1)) 0x5F33F0	)	//Obj

signed int  _sub_5F33F0(char* a1)
{
	int Result = 0;
	bool Packed = false;

	if(!strcmp(a1,"Data\\World1\\EncTerrain1.obj"))
	{
		Packed = true;
	}

	if(Packed==true)
	{
		g_SecurityScript.ReadScript(a1);
		g_SecurityScript.WriteScript(a1);
	}

	Result = sub_5F33F0(a1);

	if(Packed==true)
	{
		g_SecurityScript.ReadScript(a1);
		g_SecurityScript.WriteScript(a1);
	}

	return Result;
}



//signed int __cdecl sub_5D6E50(int a1)
signed int  _sub_5D6E50(char* a1)
{
	int Result = 0;
	bool Packed = false;

	if(!strcmp(a1,"Data\\World1\\EncTerrain1.map"))
	{
		Packed = true;
	}

	if(Packed==true)
	{
		g_SecurityScript.ReadScript(a1);
		g_SecurityScript.WriteScript(a1);
	}

	Result = sub_5D6E50(a1);

	if(Packed==true)
	{
		g_SecurityScript.ReadScript(a1);
		g_SecurityScript.WriteScript(a1);
	}

	return Result;
}




#define sub_5D6810				((signed int(__cdecl*)(char* a1)) 0x5D6810)
//hock 0062EE31
//signed int __cdecl sub_5D6810(int a1)





signed int _sub_5D6810(char* a1)
{
	int Result = 0;
	bool Packed = false;

	if(!strcmp(a1,"Data\\World1\\EncTerrain1.att"))
	{
		Packed = true;
	}

	if(Packed==true)
	{
		g_SecurityScript.ReadScript(a1);
		g_SecurityScript.WriteScript(a1);
	}

	Result = sub_5D6810(a1);

	if(Packed==true)
	{
		g_SecurityScript.ReadScript(a1);
		g_SecurityScript.WriteScript(a1);
	}

	return Result;
}



void SecurityScript::Test()
{
	
		SetOp((LPVOID)0x0062EED4, (LPVOID)_sub_5F33F0, ASM::CALL);
		SetOp((LPVOID)0x0062EBE7, (LPVOID)_sub_5D6E50, ASM::CALL);	//Map Hock
	SetOp((LPVOID)0x0062EE31, (LPVOID)_sub_5D6810, ASM::CALL);	//ATT


	//char * File = "ITEM.txt";

	//ReadScript(File);
	//printf("%d", m_pBuffer[0]);
	//WriteScript(File);

}


#endif