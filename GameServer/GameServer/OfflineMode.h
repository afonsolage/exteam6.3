#include "StdAfx.h"
#include "..\\include\\prodef.h"
#include "DSProtocol.h"

#if(OFFLINE_MODE==TRUE)
// ----------------------------------------------------------------------------------------------

#define OFFMAXTIME_FOR_BUFF		20	

#define OFFLINE_MODE_RESTORE	1
#define OFFLINEMODE_DBMAX		8
#define OFFLINEMODE_DBPRICE		544
#define OFFLINEMODE_DBCREDIT	128

struct CG_OFFMODE_RESULT
{
	PBMSG_HEAD2 h;
	WORD Result;
	BYTE BuffResult;
#if(ADD_OFFMODE_PICKUP==TRUE)
	BYTE bPickZen;
	BYTE bPickJewel;
	BYTE bPickExel;
	BYTE bPickAnc;
#endif
	#if(ADD_OFFMODE_TIMER)
	DWORD TimerMax;
	#endif
};
// ----------------------------------------------------------------------------------------------

struct GC_OFFMODE_CONFIG
{
	PBMSG_HEAD2 h;
	int PriceZen;
	int PriceWcoin;
	int iHourCredit;
	#if(ADD_OFFMODE_TIMER)
	int StandartPlayerTime;
	int OtherPlayerMaxTime;
	int PremiumPlayerMaxTime;
	#endif
};
// ----------------------------------------------------------------------------------------------

#if(OFFLINE_MODE_RESTORE)
struct PMSG_DGANS_OFFMODE_START
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Password[11];
	char Name[11];
	DWORD TickCount;
};

struct PMSG_GDREQ_OFFMODE_CHAR
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	short Number;
};

struct PMSG_GDLOAD_OFFMODE_DATA
{
	PWMSG_HEAD h;
	short Number;
	BYTE AttackData[OFFLINEMODE_DBMAX];
	bool PShopOpen;
	char PShopText[36];
	BYTE PriceData[OFFLINEMODE_DBPRICE];
	BYTE CreditData[OFFLINEMODE_DBCREDIT];
};

struct PMSG_GDSAVE_OFFMODE_DATA
{
	PWMSG_HEAD h;
	char Name[11];
	bool Status;
	BYTE AttackData[OFFLINEMODE_DBMAX];
	bool PShopOpen;
	char PShopText[36];
	BYTE PriceData[OFFLINEMODE_DBPRICE];
	BYTE CreditData[OFFLINEMODE_DBCREDIT];
};

struct PMSG_GDREQ_OFFMODE_STATUS
{
	PBMSG_HEAD2 h;
	char Name[11];
	BYTE Status;	
};
#endif

struct OFFMODE_BLOCK_MAP
{
	int MapNumber;
};

class OfflineMode
{
public:
	OfflineMode();
	~OfflineMode();

	void Load();
	void Read(char* filename);

	void Start(CG_OFFMODE_RESULT* aRecv, int UserIndex);
	void Attack(int UserIndex);
	void DarkKnight(int UserIndex);
	void DarkWizard(int UserIndex);
	void FairyElf(int UserIndex);
	void MagicGladiator(int UserIndex);
	void DarkLord(int UserIndex);
	void Summoner(int UserIndex);
	void Fighter(int UserIndex);

	int SearchTarget(int UserIndex, int maxdis);
	bool OffTimer(int UserIndex, int DivTime);
#if(ADD_OFFMODE_PICKUP==TRUE)
	void PickUP(int aIndex);
#endif
	#if(OFFLINE_MODE_RESTORE)
	short AddIndexPlayer();
	void GDReqAllPlayer();	//need queue
	void DGAnsAccauntPassword(PMSG_DGANS_OFFMODE_START* Data);
	void GDReqOffCharacter(int aIndex);
	void DGAnsOffCharacter(SDHP_DBCHAR_INFORESULT* lpMsg);
	void DGPSelectData(PMSG_GDLOAD_OFFMODE_DATA* lpMsg);//need type offexp and reconnect
	void GDUpdateData(int aIndex);
	void GDReqUpdateStatus(int aIndex);
	bool m_bQueenQuery;
	#endif

	int StartBonusPay;
	int HourZenPay;

	int PriceZen;
	int PriceWcoin;
	int HourCredit;
	int PriceTime;
	int ZenFeePerc;
	bool bOnlyLorenMarket;
	void GCConfig(int aIndex);
	bool CheckBlockMap(int Map);

	bool m_bLoadedDB;

	#if(ADD_OFFMODE_TIMER)
	int m_StandartPlayerTime;
	int m_OtherPlayerMaxTime;
	int m_PremiumPlayerMaxTime;
	#endif

	std::vector<OFFMODE_BLOCK_MAP> m_BlockMap;
};
// ----------------------------------------------------------------------------------------------
extern OfflineMode g_OfflineMode;
// ----------------------------------------------------------------------------------------------
#endif
