#include "StdAfx.h"
#include "ExLicense.h"
// ----------------------------------------------------------------------------------------------

#if(EX_LICENSE==TRUE)

CExLicense g_ExLicense;
// ----------------------------------------------------------------------------------------------

CExLicense::CExLicense()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

CExLicense::~CExLicense()
{
}
// ----------------------------------------------------------------------------------------------

void CExLicense::Init()
{
	this->Enable = true;

	this->TEXTXoR[0] = 0x03;
	this->TEXTXoR[1] = 0x05;
	this->TEXTXoR[2] = 0x08;

	this->URLXoR[0] = 0xA9;
	this->URLXoR[1] = 0xB3;
	this->URLXoR[2] = 0x18;

	this->ActiveUser = -1;
}
// ----------------------------------------------------------------------------------------------

void CExLicense::Load()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

void CExLicense::GDLicenseUser(PMSG_LICENSE_DATA* aRecv)
{
	this->ActiveUser = aRecv->LicenseUser;
	memcpy(&this->user,&aRecv->base,sizeof(this->user));
	memcpy(&this->config,&aRecv->config,sizeof(this->config));
}
// ----------------------------------------------------------------------------------------------

bool CExLicense::CheckUser(int NeedUser)
{
	if(this->ActiveUser == NeedUser)
	{
		return true;
	}
	return false;
}
// ----------------------------------------------------------------------------------------------

char* CExLicense::GetDecText(char* EncodeChar)
{
	int len = strlen(EncodeChar);	
	char* Line = new char[len+1];
	for(int i = 0; i < len; i++)
	{
		Line[i] = char(EncodeChar[i] ^ this->TEXTXoR[i % 3]);
	}
	Line[len] = 0;
	return Line;
}
// ----------------------------------------------------------------------------------------------

#endif