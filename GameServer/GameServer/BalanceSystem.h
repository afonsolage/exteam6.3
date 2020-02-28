#include "StdAfx.h"
#include "user.h"
#include "ExLicense.h"

#ifdef _BALANS_SYSTEM_

#define BALANCESYSTEM_DIR ".\\ExData\\BalanceSystem.ini"

struct BALANS_RESET_DAMAGE
{
	int ResetNumber;
	int DWDamagePercent;
	int DKDamagePercent;
	int FEDamagePercent;
	int MGDamagePercent;
	int DLDamagePercent;
	int SUDamagePercent;
	int RFDamagePercent;
};

class cBalanceSystem
{
public:
	cBalanceSystem();
	virtual ~cBalanceSystem();

	void Load();
	void Init();
	void ReadConfigs(char * File);
	void ReadResetDamage(char* filename);

	void Main(LPOBJ lpObj, LPOBJ lpTarget, int & AttackDamage);
	void Refflect(LPOBJ lpObj);

private:
	bool Enable;

	int DKvsDK;
	int DKvsDW;
	int DKvsELF;
	int DKvsSUM;
	int DKvsMG;
	int DKvsDL;
	int DKvsRF;

	int DWvsDW;
	int DWvsDK;
	int DWvsELF;
	int DWvsSUM;
	int DWvsMG;
	int DWvsDL;
	int DWvsRF;

	int ELFvsELF;
	int ELFvsDK;
	int ELFvsDW;
	int ELFvsSUM;
	int ELFvsMG;
	int ELFvsDL;
	int ELFvsRF;

	int SUMvsSUM;
	int SUMvsDK;
	int SUMvsDW;
	int SUMvsELF;
	int SUMvsMG;
	int SUMvsDL;
	int SUMvsRF;

	int MGvsMG;
	int MGvsDK;
	int MGvsDW;
	int MGvsELF;
	int MGvsSUM;
	int MGvsDL;
	int MGvsRF;

	int DLvsDL;
	int DLvsDK;
	int DLvsDW;
	int DLvsELF;
	int DLvsSUM;
	int DLvsMG;
	int DLvsRF;

	int RFvsRF;
	int RFvsDK;
	int RFvsDW;
	int RFvsELF;
	int RFvsSUM;
	int RFvsMG;
	int RFvsDL;

	bool m_EnableMonster;
	int m_DKvsMonster;
	int m_DWvsMonster;
	int m_ELFvsMonster;
	int m_SUMvsMonster;
	int m_MGvsMonster;
	int m_DLvsMonster;
	int m_RFvsMonster;

	int m_DKFenrirDamagePercent;

	bool m_EnableRefflect;
	int m_DWRefflectPercent;
	int m_DKRefflectPercent;
	int m_FERefflectPercent;
	int m_MGRefflectPercent;
	int m_DLRefflectPercent;
	int m_SURefflectPercent;
	int m_RFRefflectPercent;

	int m_EnableDamagePercent;
	std::vector<BALANS_RESET_DAMAGE> m_vResetDamage;
};

extern cBalanceSystem gBalanceSystem;

#endif