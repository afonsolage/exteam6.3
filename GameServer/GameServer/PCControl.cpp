#include "StdAfx.h"
#include "PCControl.h"
#include <algorithm>
#include "logproc.h"
#include "GameMain.h"
#include "SProtocol.h"
#include "Message.h"
#include "ConnectEx.h"

CPCControl gPCControl;

CPCControl::CPCControl(void)
{
	
}


CPCControl::~CPCControl(void)
{

}

void CPCControl::Init()
{
	m_PCLimitCount = 0;
}

void CPCControl::Load()
{
	Init();
	m_PCLimitCount = GetPrivateProfileInt("PCControl","PCLimitCount",999, gDirPath.GetNewPath(INI_PATH) );
}

int CPCControl::GetPCConnectedCount()
{
	int count = 0;

	for (auto it = m_GSList.begin(); it != m_GSList.end(); it++)
	{
		for (auto innerIt = it->PCIDs.begin(); innerIt != it->PCIDs.end(); innerIt++)
		{
			if (innerIt->Indices.size() > 0)
				count++;
		}
	}

	return count;
}

int CPCControl::GetPCConnectedCount(DWORD PCID)
{
	int count = 0;

	for (auto it = m_GSList.begin(); it != m_GSList.end(); it++)
	{
		for (auto innerIt = it->PCIDs.begin(); innerIt != it->PCIDs.end(); innerIt++)
		{
			if (innerIt->PCID == PCID && innerIt->Indices.size() > 0)
				count += innerIt->Indices.size();
		}
	}

	return count;
}

GSSet* CPCControl::FindGS(BYTE gameServer)
{
	for (auto it = m_GSList.begin(); it != m_GSList.end(); it++)
	{
		if (it->GameServer == gameServer)
			return it._Ptr;
	}

	return NULL;
}

PCIDSet* CPCControl::FindPCIDSet(GSSet* lpSet, DWORD PCID)
{
	for (auto it = lpSet->PCIDs.begin(); it != lpSet->PCIDs.end(); it++)
	{
		if (it->PCID == PCID)
			return it._Ptr;
	}
}

void CPCControl::AddPCID(BYTE gameServer, DWORD PCID, int index)
{
	auto lpGS = FindGS(gameServer);

	if (lpGS == NULL)
	{
		GSSet set = {gameServer, std::vector<PCIDSet>()};
		m_GSList.emplace_back(set);
		lpGS = FindGS(gameServer);
	}

	auto lpPCIDs = FindPCIDSet(lpGS, PCID);

	if (lpPCIDs == NULL)
	{
		PCIDSet set = {PCID, std::vector<int>()};
		lpGS->PCIDs.emplace_back(set);
		lpPCIDs = FindPCIDSet(lpGS, PCID);
	}

	lpPCIDs->Indices.emplace_back(index);

	LogAddC(7, "[PCControl] Adding [%u][%u][%u]", gameServer, PCID, index);
}

void CPCControl::RemovePCID(BYTE gameServer, DWORD PCID, int index)
{
	auto lpGS = FindGS(gameServer);

	if (lpGS == NULL)
	{
		LogAddC(2, "[PCControl] Failed to remove [%u][%u][%u]. GS Not Found", gameServer, PCID, index);
		return;
	}

	auto lpPCIDs = FindPCIDSet(lpGS, PCID);

	if (lpPCIDs == NULL)
	{
		LogAddC(2, "[PCControl] Failed to remove [%u][%u][%u]. PCIDSet Not Found", gameServer, PCID, index);
		return;
	}

	if (lpPCIDs->Indices.size() == 0)
		return;

	auto accIt = lpPCIDs->Indices.begin();

	while (accIt != lpPCIDs->Indices.end())
	{
		if (*accIt == index)
		{
			accIt = lpPCIDs->Indices.erase(accIt);
		}
		else
		{
			accIt++;
		}
	}

	LogAddC(7, "[PCControl] Removing [%u][%u][%u]", gameServer, PCID, index);
}

void CPCControl::GSDisconnected(BYTE gameServer)
{
	auto it = m_GSList.begin();

	while(it != m_GSList.end())
	{
		if (it->GameServer == gameServer)
		{
			it = m_GSList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void CPCControl::GSConnected(BYTE gameServer)
{
	PMSG_GSPCInfo gsInfo;

	gsInfo.SenderChannel = gGameServerCode;
	gsInfo.DestChannel = gameServer;
	int count = 0;

	std::vector<GSPCInfo> pcInfos;

	for (auto it = m_GSList.begin(); it != m_GSList.end(); it++)
	{
		if (gGameServerCode != it->GameServer)
			continue;

		for (auto innerIt = it->PCIDs.begin(); innerIt != it->PCIDs.end(); innerIt++)
		{
			if (innerIt->Indices.size() > 0)
			{
				for (auto pcIt = innerIt->Indices.begin(); pcIt != innerIt->Indices.end(); pcIt++)
				{
					GSPCInfo info = {innerIt->PCID, *pcIt};
					pcInfos.emplace_back(info);

					count++;
				}
			}
		}
	}

	gsInfo.Count = count;
	int totalSize = sizeof(gsInfo) + (sizeof(GSPCInfo) * count);
	std::vector<BYTE> buffer = std::vector<BYTE>(totalSize);

	memcpy(&buffer[0], &gsInfo, sizeof(gsInfo));
	memcpy(&buffer[sizeof(gsInfo)], &pcInfos[0], (sizeof(GSPCInfo) * count));

	gsInfo.h.set(&buffer[0], 0xD4, buffer.size());

	wsJServerCli.DataSend((char*)&buffer[0], buffer.size());
}

void CPCControl::UserConnect(int aIndex)
{
	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__ );
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if (ShouldSkipPlayer(lpUser))
		return;

	int connectedCount = GetPCConnectedCount(lpUser->AccountSecurity.ClientPCID);

	if (CheckPlayerAllowed(lpUser, true))
	{
		GJPCConnected(lpUser->AccountSecurity.ClientPCID, aIndex);
		lpUser->m_PCCloseWait = 0;
	}
}

bool CPCControl::ShouldSkipPlayer(OBJECTSTRUCT* lpUser)
{
	if (lpUser->Level <= 6 && lpUser->Reset == 0)
		return true;

	return false;
}

bool CPCControl::CheckPlayerAllowed(OBJECTSTRUCT* lpUser, bool newConnection)
{
	int add = (newConnection) ? 1 : 0;

	if (GetPCConnectedCount(lpUser->AccountSecurity.ClientPCID) + add > m_PCLimitCount)
	{
		MessageChat(lpUser->m_Index, "Número máximo de conexões por PC atingido!");
		MessageChat(lpUser->m_Index, "Você será desconectado em 15 segundos.");
		lpUser->m_PCCloseWait = 15;
		return false;
	}
	else
	{
		return true;		
	}
}

void CPCControl::SecondProc()
{
	for (int n=OBJ_STARTUSERINDEX ; n<OBJMAX ; n++ )
	{
		auto lpObj = &gObj[n];

		if ( lpObj->Connected > PLAYER_CONNECTED && lpObj->Live != 0 && lpObj->AccountSecurity.ClientPCID && lpObj->m_PCCloseWait > 0 )
		{
			lpObj->m_PCCloseWait--;

			if (lpObj->m_PCCloseWait == 10)
			{
				MessageChat(lpObj->m_Index, "Você será desconectado em 10 segundos.");
			}
			else if (lpObj->m_PCCloseWait == 5)
			{
				MessageChat(lpObj->m_Index, "Você será desconectado em 5 segundos.");
			}
			else if (lpObj->m_PCCloseWait == 4)
			{
				MessageChat(lpObj->m_Index, "Você será desconectado em 4 segundos.");
			}
			else if (lpObj->m_PCCloseWait == 3)
			{
				MessageChat(lpObj->m_Index, "Você será desconectado em 3 segundos.");
			}
			else if (lpObj->m_PCCloseWait == 2)
			{
				MessageChat(lpObj->m_Index, "Você será desconectado em 2 segundos.");
			}
			else if (lpObj->m_PCCloseWait == 1)
			{
				MessageChat(lpObj->m_Index, "Você será desconectado em 1 segundos.");
			}
			else if (lpObj->m_PCCloseWait <= 0)
			{
				g_ConnectEx.SendClose(lpObj->m_Index, NORM_DC);
			}
		}
	}
}