#include "StdAfx.h"
#include "PCControl.h"
#include <algorithm>
#include "Window.h"

CPCControl gPCControl;

CPCControl::CPCControl(void)
{

}


CPCControl::~CPCControl(void)
{

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
				count++;
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

	g_Window.PrintLog("[PCControl] Adding [%u][%u]", PCID, index);
}

void CPCControl::RemovePCID(BYTE gameServer, DWORD PCID, int index)
{
	auto lpGS = FindGS(gameServer);

	if (lpGS == NULL)
	{
		g_Window.PrintLog("[PCControl] Failed to remove [%u][%u]. GS Not Found", PCID, index);
		return;
	}

	auto lpPCIDs = FindPCIDSet(lpGS, PCID);

	if (lpPCIDs == NULL)
	{
		g_Window.PrintLog("[PCControl] Failed to remove [%u][%u]. PCIDSet Not Found", PCID, index);
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

	g_Window.PrintLog("[PCControl] Removing [%u][%u]", PCID, index);
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