#include "StdAfx.h"
#include "PCControl.h"
#include <algorithm>
#include "logproc.h"
#include "GameMain.h"
#include "SProtocol.h"
#include "Message.h"
#include "ConnectEx.h"
#include "MUHelperOffline.h"

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
	m_PCLimitCount = GetPrivateProfileInt("PCControl", "PCLimitCount", 999, gDirPath.GetNewPath(INI_PATH));
	m_SyncInterval = GetPrivateProfileInt("PCControl", "SyncInterval", 60, gDirPath.GetNewPath(INI_PATH));

	if (m_SyncInterval > 0)
		m_nextSync = GetTickCount() + (m_SyncInterval * ONE_SECOND);
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

	return NULL;
}

void CPCControl::AddPCID(BYTE gameServer, DWORD PCID, int index)
{
	if (PCID == 0)
	{
		LOG_ERROR("Invalid PCID received.");
		return;
	}

	auto lpGS = FindGS(gameServer);

	if (lpGS == NULL)
	{
		GSSet set = { gameServer, std::vector<PCIDSet>() };
		m_GSList.emplace_back(set);
		lpGS = FindGS(gameServer);
	}

	auto lpPCIDs = FindPCIDSet(lpGS, PCID);

	if (lpPCIDs == NULL)
	{
		PCIDSet set = { PCID, std::vector<int>() };
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

	while (it != m_GSList.end())
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
					GSPCInfo info = { innerIt->PCID, *pcIt };
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

void CPCControl::SyncPCIDs()
{
	PMSG_GSSyncPCInfo syncInfo = { 0 };

	syncInfo.SenderChannel = gGameServerCode;
	int count = 0;

	std::vector<GSPCInfo> pcInfos;

	for (auto it = g_PlayerMaps.begin(); it != g_PlayerMaps.end(); it++)
	{
		if (it->second.empty()) continue;

		for (auto iIt = it->second.begin(); iIt != it->second.end(); iIt++)
		{
			auto aIndex = *iIt;

			if (!gObjIsConnected(aIndex)) continue;

			LPOBJ lpObj = &gObj[aIndex];

			if (lpObj->AccountSecurity.ClientPCID <= 0) continue;

			GSPCInfo info = { lpObj->AccountSecurity.ClientPCID, lpObj->m_Index };
			pcInfos.emplace_back(info);

			count++;
		}
	}

	syncInfo.Count = count;
	int totalSize = sizeof(syncInfo) + (sizeof(GSPCInfo) * count);
	std::vector<BYTE> buffer = std::vector<BYTE>(totalSize);

	memcpy(&buffer[0], &syncInfo, sizeof(syncInfo));
	memcpy(&buffer[sizeof(syncInfo)], &pcInfos[0], (sizeof(GSPCInfo) * count));

	syncInfo.h.set(&buffer[0], 0xD5, buffer.size());

	wsJServerCli.DataSend((char*)&buffer[0], buffer.size());
}

void CPCControl::UserConnect(int aIndex)
{
	if (OBJMAX_RANGE(aIndex) == FALSE)
	{
		LogAdd("error : %s %d", __FILE__, __LINE__);
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if (lpUser->Connected < PLAYER_PLAYING)
	{
		return;
	}

	if (ShouldSkipPlayer(lpUser))
		return;

	if (GetPCConnectedCount(lpUser->AccountSecurity.ClientPCID) + 1 > m_PCLimitCount)
	{
		MessageChat(lpUser->m_Index, "[PCControl] Maximum connections!");
		MessageChat(lpUser->m_Index, "[PCControl] You'll be disconnected in 15 seconds.");
		lpUser->m_PCCloseWait = 15;
		LOG_INFO("Disconnecting %s due to maximum connections.", lpUser->AccountID);
	}
	else
	{
		GJPCConnected(lpUser->AccountSecurity.ClientPCID, aIndex);
		lpUser->m_PCCloseWait = 0;
	}
}

bool CPCControl::ShouldSkipPlayer(OBJECTSTRUCT* lpUser)
{
	if (lpUser->Level <= 10 && lpUser->Reset == 0)
		return true;

	if (lpUser->AccountSecurity.ClientPCID == 0)
	{
		LOG_INFO("Invalid PC ID on user %s. Skipping it.", lpUser->AccountID);
		return true;
	}

	return false;
}

void CPCControl::SecondProc()
{
	if (m_SyncInterval > 0)
	{
		auto now = GetTickCount();

		if (now > m_nextSync)
		{
			SyncPCIDs();
			m_nextSync = m_nextSync + (m_SyncInterval * ONE_SECOND);
		}
	}

	for (auto it = g_PlayerMaps.begin(); it != g_PlayerMaps.end(); it++)
	{
		if (it->second.empty()) continue;

		for (auto pIt = it->second.begin(); pIt != it->second.end(); pIt++)
		{
			auto lpObj = &gObj[*pIt];

			if (lpObj->Connected > PLAYER_CONNECTED
				&& lpObj->Live != 0
				&& lpObj->AccountSecurity.ClientPCID
				&& lpObj->m_PCCloseWait > 0
				&& lpObj->CloseCount == -1)
			{
				lpObj->m_PCCloseWait--;

				if (lpObj->m_PCCloseWait == 10
					|| lpObj->m_PCCloseWait > 0 && lpObj->m_PCCloseWait <= 5)
				{
					MessageChat(lpObj->m_Index, "[PCControl] You will be disconnected in %d second(s)", lpObj->m_PCCloseWait);
				}
				else if (lpObj->m_PCCloseWait <= 0)
				{
					if (g_MUHelperOffline.IsOffline(lpObj->m_Index))
					{
						g_MUHelperOffline.CloseOfflineUser(lpObj->m_Index);
					}
					else
					{
						g_ConnectEx.SendClose(lpObj->m_Index, NORM_DC);
					}
				}
			}
		}
	}
}