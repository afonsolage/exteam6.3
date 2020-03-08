#include "stdafx.h"
#include "EncDec.h"
#include "Import.h"

#if(ENABLE_ENCODER)

CEncDec g_EncDec;

CEncDec::CEncDec()
{
	this->Init();
}

CEncDec::~CEncDec()
{
}

void CEncDec::Init()
{
	this->m_XoR[0] = 0x0D;
	this->m_XoR[1] = 0x1A;
	this->m_XoR[2] = 0x15;

	this->m_File = NULL;
	this->m_WriteFileSize = 0;
	this->m_PackBuff = NULL;
	this->m_PackSize = 0;
}

void CEncDec::Load()
{
	this->Init();
}

void CEncDec::Main(char* filename)
{
	this->GetBuffer(filename);
	this->PackBuffer();
	this->SetBuffer(filename);

#ifndef TOOL
	MessageBox(pGameWindow, "file encryption completed successfully", WINDOW_TITLE, MB_OK|MB_ICONINFORMATION);
#endif
}

void CEncDec::GetBuffer(char* filename)
{
	this->m_File = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0x80, NULL);

	if(this->m_File == INVALID_HANDLE_VALUE)
	{
#ifndef TOOL
		MessageBox(pGameWindow, "error opening the file for reading", WINDOW_TITLE, MB_OK|MB_ICONERROR);
#endif
		ExitProcess(0);
	}

	int filesize = GetFileSize(this->m_File, NULL);
	this->m_PackBuff = (char*)malloc(filesize+1);
	this->m_PackBuff[filesize] = 0;

	ReadFile(this->m_File, this->m_PackBuff, filesize, &this->m_PackSize, 0);

	CloseHandle(this->m_File);

	if(!this->m_PackSize)
	{
#ifndef TOOL
		MessageBox(pGameWindow, "error reading the file buffer", WINDOW_TITLE, MB_OK|MB_ICONERROR);
#endif
		ExitProcess(0);
	}
}

void CEncDec::SetBuffer(char* filename)
{
	this->m_File = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0x80, NULL);

	if(this->m_File == INVALID_HANDLE_VALUE)
	{
#ifndef TOOL
		MessageBox(pGameWindow, "error opening a file for writing", WINDOW_TITLE, MB_OK|MB_ICONERROR);
#endif
		ExitProcess(0);
	}

	WriteFile(this->m_File, this->m_PackBuff, this->m_PackSize, &this->m_WriteFileSize, 0);

	CloseHandle(this->m_File);

	if(!this->m_WriteFileSize)
	{
#ifndef TOOL
		MessageBox(pGameWindow, "error writing a buffer to a file", WINDOW_TITLE, MB_OK|MB_ICONERROR);
#endif
		ExitProcess(0);
	}
}

void CEncDec::PackBuffer()
{
	for(int i = 0; i < this->m_PackSize; i++)
	{
		this->m_PackBuff[i] = this->m_PackBuff[i] ^ this->m_XoR[i % 3];
	}
}

void CEncDec::ClearBuffer()
{
	this->m_File = NULL;
	this->m_WriteFileSize = 0;
	free(this->m_PackBuff);
	this->m_PackSize = 0;
}

#endif