#pragma once

#include <set>

typedef std::set<int> IndexSet;
typedef std::map<DWORD, IndexSet> PCMap;
typedef std::map<BYTE, PCMap> GSMap;

typedef struct 
{
	DWORD PCID;
	std::vector<int> Indices;
} PCIDSet;

typedef struct
{
	BYTE GameServer;
	std::vector<PCIDSet> PCIDs;
} GSSet;

class CPCControl
{
public:
	CPCControl(void);
	~CPCControl(void);

	int GetPCConnectedCount();
	int GetPCConnectedCount(DWORD PCID);
	void AddPCID(BYTE gameServer, DWORD PCID, int index);
	void RemovePCID(BYTE gameServer, DWORD PCID, int index);
	void GSDisconnected(BYTE gameServer);
	GSSet* FindGS(BYTE gameServer);
	PCIDSet* FindPCIDSet(GSSet* lpSet, DWORD PCID);

private:
	std::vector<GSSet> m_GSList;
};

extern CPCControl gPCControl;