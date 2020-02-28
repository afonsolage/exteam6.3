#include "StdAfx.h"
#include "ExLicenseProtocol.h"
#include "ExLicense.h"
#include "ExLicenseClient.h"
#include "GameMain.h"
#include "Message.h"
#include "Configs.h"
#include "ConnectEx.h"
#include "DBSockMng.h"
#include "..\\common\\winutil.h"
#include "CashItemPeriodSystem.h"
#include "logproc.h"

#if(EXLICENSE_SERVER)

CExLicenseProtocol g_ExLicenseProtocol;

void CExLicenseProtocol::ProtocolCore(BYTE head, BYTE* lpMsg, int size)
{
	switch(head)
	{
		case 0x00:
			this->LGAnsUser((PMSG_ANS_LICENSECHECK*)lpMsg);
			break;
		default:
			g_ExLicenseClient.Disconnect();
			break;
	}
}

void CExLicenseProtocol::GLReqUser()
{
	PMSG_REQ_LICENSECHECK pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0x00, sizeof(pMsg));

	DWORD dwHWID;
	GetVolumeInformationA("c:\\",0,0,&dwHWID,0,0,0,0); 

	sprintf(pMsg.hwid, "%08X", dwHWID);

	unsigned char btMac[6];
	UUID uuid;
	UuidCreateSequential(&uuid);
	for(int i = 0; i < 6; i++) 
	{
		btMac[i] = uuid.Data4[i+2];
	}
	sprintf(pMsg.mac, "%02X-%02X-%02X-%02X-%02X-%02X", btMac[0], btMac[1], btMac[2], btMac[3], btMac[4], btMac[5]);

	g_ExLicenseClient.DataSend((BYTE*)&pMsg,pMsg.h.size);
}

void CExLicenseProtocol::LGAnsUser(PMSG_ANS_LICENSECHECK* lpMsg)
{
	if(!lpMsg->result)
	{
		// -- need add theard message close
		MessageBox(NULL, "No License User", "ExLicense", NULL);
		ExitProcess(0);
	}

	//g_ExLicense.ActiveUser = lpMsg->Number;

	g_ExLicense.AddList();
	g_ExLicense.CheckLicense();

	g_ExLicense.SelectLicense(lpMsg->Number);

	g_ExLicense.m_WaitLicense = true;
}

void CExLicenseProtocol::Run()
{
	
}

#endif