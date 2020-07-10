#include "StdAfx.h"
#include "PCControl.h"
#include <algorithm>
#include "logproc.h"
#include "GameMain.h"
#include "SProtocol.h"
#include "Message.h"
#include "ConnectEx.h"
#include "MUHelperOffline.h"
#include "GameServer.h"

CPCControl gPCControl;

CPCControl::CPCControl(void)
{
	InitializeCriticalSection(&m_exceptionCrit);
}


CPCControl::~CPCControl(void)
{

}

void CPCControl::Init()
{
	m_PCLimitCount = 0;
	m_nextCheck = 30;


	EnterCriticalSection(&m_exceptionCrit);
	m_exceptionList.clear();
	LeaveCriticalSection(&m_exceptionCrit);
}

void CPCControl::Load()
{
	Init();
	m_PCLimitCount = GetPrivateProfileInt("PCControl", "PCLimitCount", 999, gDirPath.GetNewPath(INI_PATH));
	m_MapLimit = GetPrivateProfileInt("PCControl", "MapLimit", 1, gDirPath.GetNewPath(INI_PATH));
	m_SyncInterval = GetPrivateProfileInt("PCControl", "SyncInterval", 60, gDirPath.GetNewPath(INI_PATH));

	if (m_SyncInterval > 0)
		m_nextSync = GetTickCount() + (m_SyncInterval * ONE_SECOND);

	auto path = gDirPath.GetNewPath("Custom\\PCControlExceptions.txt");

	FILE *file = fopen(path, "r");

	if (file == NULL)
	{
		MessageBoxA(0, "Custom\\PCControlExceptions.txt", "CRITICAL ERROR", 0);
		return;
	}

	EnterCriticalSection(&m_exceptionCrit);
	char Buff[1024];
	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff, 256, file);

		if (Buff[0] == '/' && Buff[1] == '/')
			continue;

		char accountId[256];
		sscanf(Buff, "%s", &accountId);

		this->m_exceptionList.emplace_back(std::string(accountId));
	}
	fclose(file);
	LeaveCriticalSection(&m_exceptionCrit);
}

int CPCControl::GetPCConnectedCount()
{
	int count = 0;

	for (auto it = m_GSList.begin(); it != m_GSList.end(); it++)
	{
		for (auto innerIt = it->PCIDs.begin(); innerIt != it->PCIDs.end(); innerIt++)
		{
			if (innerIt->Chars.size() > 0)
				count++;
		}
	}

	return count;
}

int CPCControl::GetPCConnectedCount(DWORD PCID, int gameServer)
{
	int count = 0;

	for (auto it = m_GSList.begin(); it != m_GSList.end(); it++)
	{
		for (auto innerIt = it->PCIDs.begin(); innerIt != it->PCIDs.end(); innerIt++)
		{
			if (innerIt->PCID == PCID && innerIt->Chars.size() > 0 && (gameServer == -1 || gameServer == gGameServerCode))
				count += innerIt->Chars.size();
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

void CPCControl::AddPCID(BYTE gameServer, DWORD PCID, int index, char* accountId, char* name)
{
	if (PCID == 0)
	{
		LOG_ERROR("Invalid PCID received.");
		return;
	}

	if (accountId == NULL)
	{
		LOG_ERROR("Invalid AccountID received.");
		return;
	}

	if (name == NULL)
	{
		LOG_ERROR("Invalid Name received.");
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
		PCIDSet set = { PCID, std::vector<CINFO>() };
		lpGS->PCIDs.emplace_back(set);
		lpPCIDs = FindPCIDSet(lpGS, PCID);
	}

	CINFO info = { 0 };
	info.Index = index;
	memcpy(info.AccountID, accountId, MAX_IDSTRING);
	memcpy(info.Name, name, MAX_IDSTRING);

	//Avoid duplicate entries
	for (auto gsIt = m_GSList.begin(); gsIt != m_GSList.end(); gsIt++)
	{
		for (auto pcsIt = gsIt->PCIDs.begin(); pcsIt != gsIt->PCIDs.end(); pcsIt++)
		{
			for (auto it = pcsIt->Chars.begin(); it != pcsIt->Chars.end(); it++)
			{
				if (info.Index == it->Index
					&& memcmp(info.AccountID, it->AccountID, MAX_IDSTRING) == 0
					&& memcmp(info.Name, it->Name, MAX_IDSTRING) == 0)
				{

					if (gsIt->GameServer != gameServer && gsIt->GameServer == gGameServerCode)
					{
						LOG_ERROR("Duplicated login for [%u][%u][%u][%s][%s]", gameServer, PCID, index, accountId, name);
						CloseClient(it->Index);
						return;
					}
					else
					{
						LOG_ERROR("Duplicated entry for [%u][%u][%u][%s][%s]", gameServer, PCID, index, accountId, name);
					}

					return;
				}
			}
		}
	}

	lpPCIDs->Chars.push_back(info);

	LogAddC(7, "[PCControl] Adding [%u][%u][%u][%s][%s]", gameServer, PCID, index, accountId, name);
}

void CPCControl::RemovePCID(BYTE gameServer, DWORD PCID, int index, char* accountId, char* name)
{
	auto lpGS = FindGS(gameServer);

	if (lpGS == NULL)
	{
		LogAddC(2, "[PCControl] Failed to remove [%u][%u][%u][%s][%s]. GS Not Found", gameServer, PCID, index, accountId, name);
		return;
	}

	auto lpPCIDs = FindPCIDSet(lpGS, PCID);

	if (lpPCIDs == NULL)
	{
		LogAddC(2, "[PCControl] Failed to remove [%u][%u][%u][%s][%s]. PCIDSet Not Found", gameServer, PCID, index, accountId, name);
		return;
	}

	if (lpPCIDs->Chars.size() == 0)
		return;

	auto accIt = lpPCIDs->Chars.begin();

	while (accIt != lpPCIDs->Chars.end())
	{
		if (accIt->Index == index)
		{
			accIt = lpPCIDs->Chars.erase(accIt);
		}
		else
		{
			accIt++;
		}
	}

	LogAddC(7, "[PCControl] Removing [%u][%u][%u][%s][%s]", gameServer, PCID, index, accountId, name);
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
	PMSG_GSPCInfo gsInfo = { 0 };

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
			if (innerIt->Chars.size() > 0)
			{
				for (auto pcIt = innerIt->Chars.begin(); pcIt != innerIt->Chars.end(); pcIt++)
				{
					GSPCInfo info = { 0 };
					info.index = pcIt->Index;
					info.PCID = innerIt->PCID;
					memcpy(info.AccountID, pcIt->AccountID, MAX_IDSTRING);
					memcpy(info.Name, pcIt->Name, MAX_IDSTRING);

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

			if (ShouldSkipPlayer(lpObj)) continue;

			GSPCInfo info = { 0 };
			info.PCID = lpObj->AccountSecurity.ClientPCID;
			info.index = aIndex;
			memcpy(info.AccountID, lpObj->AccountID, MAX_IDSTRING);
			memcpy(info.Name, lpObj->Name, MAX_IDSTRING);

			pcInfos.emplace_back(info);

			count++;
		}
	}

	if (count == 0)
		return;

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

	GJPCConnected(lpUser->AccountSecurity.ClientPCID, aIndex, lpUser->AccountID, lpUser->Name);
	lpUser->m_PCCloseWait = 0;
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

	if (lpUser->Authority == 8 || lpUser->Authority == 32)
	{
		return true;
	}

	EnterCriticalSection(&m_exceptionCrit);
	for (auto it = m_exceptionList.begin(); it != m_exceptionList.end(); it++)
	{
		if (strnicmp(lpUser->AccountID, it->c_str(), MAX_IDSTRING) == 0)
			return true;

	}
	LeaveCriticalSection(&m_exceptionCrit);

	return false;
}

bool CPCControl::CheckMapLimit(int aIndex)
{
	if (m_MapLimit == 0)
		return false;

	if (OBJMAX_RANGE(aIndex) == FALSE)
	{
		LogAdd("error : %s %d", __FILE__, __LINE__);
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if (lpUser->Connected < PLAYER_PLAYING)
	{
		return false;
	}

	if (ShouldSkipPlayer(lpUser))
		return false;

	if (lpUser->MapNumber != MAP_INDEX_CASTLESIEGE && lpUser->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
		return false;

	auto it = g_PlayerMaps.find(lpUser->MapNumber);

	for (auto iIt = it->second.begin(); iIt != it->second.end(); iIt++)
	{
		auto otherIndex = *iIt;

		if (otherIndex == aIndex) continue;
		if (!gObjIsConnected(otherIndex)) continue;

		auto lpOther = &gObj[otherIndex];

		if (ShouldSkipPlayer(lpOther)) continue;

		if (lpOther->m_PCCloseWait > 0) continue; //Already disconnecting

		if (lpUser->AccountSecurity.ClientPCID == lpOther->AccountSecurity.ClientPCID)
		{
			MessageChat(lpUser->m_Index, "[PCControl] Maximum CS connections!");
			MessageChat(lpUser->m_Index, "[PCControl] You'll be disconnected in 5 seconds.");
			lpUser->m_PCCloseWait = 5;
			LOG_INFO("Disconnecting %s due to maximum CS connections.", lpUser->AccountID);
			return true;
		}
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

	m_nextCheck--;
	bool check = m_nextCheck < 0;

	if (check)
	{
		m_nextCheck = 30;
	}

	std::set<DWORD> skipPCIDs;

	for (auto it = g_PlayerMaps.begin(); it != g_PlayerMaps.end(); it++)
	{
		if (it->second.empty()) continue;

		for (auto pIt = it->second.begin(); pIt != it->second.end(); pIt++)
		{
			auto lpObj = &gObj[*pIt];

			if (lpObj->Connected > PLAYER_CONNECTED
				&& lpObj->Live != 0
				&& lpObj->AccountSecurity.ClientPCID
				&& lpObj->CloseCount == -1)
			{

				if (check && skipPCIDs.find(lpObj->AccountSecurity.ClientPCID) == skipPCIDs.end())
				{
					if (GetPCConnectedCount(lpObj->AccountSecurity.ClientPCID) > m_PCLimitCount)
					{
						MessageChat(lpObj->m_Index, "[PCControl] Maximum connections!");
						MessageChat(lpObj->m_Index, "[PCControl] You'll be disconnected in 15 seconds.");
						lpObj->m_PCCloseWait = 15;
						LOG_INFO("Disconnecting %s due to maximum connections.", lpObj->AccountID);
						skipPCIDs.insert(lpObj->AccountSecurity.ClientPCID);
						continue;
					}
					else if (CheckMapLimit(lpObj->m_Index))
					{
						skipPCIDs.insert(lpObj->AccountSecurity.ClientPCID);
						continue;
					}
				}

				if (lpObj->m_PCCloseWait > 0)
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

						g_MUHelperOffline.ClearState(lpObj->m_Index);
					}
				}
			}
		}
	}
}