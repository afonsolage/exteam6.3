#pragma once

#include <set>
#include "protocol.h"

#define INI_PATH "Custom\\PCControl.ini"

typedef std::set<int> IndexSet;
typedef std::map<DWORD, IndexSet> PCMap;
typedef std::map<BYTE, PCMap> GSMap;

class OBJECTSTRUCT;

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

	void Init();
	void Load();

	int GetPCConnectedCount();
	int GetPCConnectedCount(DWORD PCID, int gameServer = -1);
	void AddPCID(BYTE gameServer, DWORD PCID, int index);
	void RemovePCID(BYTE gameServer, DWORD PCID, int index);
	void GSDisconnected(BYTE gameServer);
	void GSConnected(BYTE gameServer);
	void SyncPCIDs();
	GSSet* FindGS(BYTE gameServer);
	PCIDSet* FindPCIDSet(GSSet* lpSet, DWORD PCID);
	void UserConnect(int aIndex);
	bool ShouldSkipPlayer(OBJECTSTRUCT* lpObj);
#if(GS_CS)
	bool CheckCSLimit(int aIndex);
#endif

	void SecondProc();
private:
	std::vector<GSSet> m_GSList;

	int m_PCLimitCount;
	int m_nextCheck;
#if(GS_CS)
	int m_CSLimit;
#endif
	int m_SyncInterval;
	int m_nextSync;
};

extern CPCControl gPCControl;