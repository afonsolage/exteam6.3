#include "stdafx.h"
#include "ComputerIdentity.h"

CComputerIdentity gCompIdentity;

CComputerIdentity::CComputerIdentity(void)
{

}


CComputerIdentity::~CComputerIdentity(void)
{
	
}

void CComputerIdentity::CGSendPCID()
{
	PMSG_PCID pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0x02, sizeof(pMsg));

	GetVolumeInformationA("c:\\", 0, 0, &pMsg.ID, 0, 0, 0, 0);

	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size, false);
}