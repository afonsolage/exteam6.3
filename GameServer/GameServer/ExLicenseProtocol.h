#pragma once

#include "StdAfx.h"
#include "ExLicense.h"
#include "ExLicenseProtocolDefine.h"

#if(EXLICENSE_SERVER)

struct PMSG_REQ_LICENSECHECK
{
	LPBMSG_HEAD h;
	char hwid[20];
	char mac[18];
};

struct PMSG_ANS_LICENSECHECK
{
	LPBMSG_HEAD h;
	bool result;
	int  Number;
};


class CExLicenseProtocol
{
public:
	void ProtocolCore(BYTE head, BYTE* lpMsg, int size);

	void GLReqUser();
	void LGAnsUser(PMSG_ANS_LICENSECHECK* lpMsg);

	void Run();

};

extern CExLicenseProtocol g_ExLicenseProtocol;

#endif