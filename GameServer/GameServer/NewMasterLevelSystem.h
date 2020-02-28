//-> Decompiled by DarkSim | 18.02.2013 | 1.01.00 GS-N (All names are original)
// -------------------------------------------------------------------------------

#pragma once
// -------------------------------------------------------------------------------

#include "user.h"
// -------------------------------------------------------------------------------

//#define MASTER_MAX_POINT	200	MAX_MASTER_LEVEL
#define MAX_MASTER_LEVEL	200
#define MASTER_MAX_POINT	200
#define MASTER_ZEN_DEC		4
#define MASTER_MAX_LIST		200
// -------------------------------------------------------------------------------

struct MLP_ANS_MASTERLEVEL_INFO	//-> 100%
{
	PBMSG_HEAD	h;
	// ----
	BYTE		btResult;
	int			iUserIndex;
	char		szCharName[MAX_IDSTRING + 1];
	short		nMLevel;
	__int64		i64MLExp;
	__int64		i64NextMLExp;
	short		nMLPoint;
};
// -------------------------------------------------------------------------------

struct MLP_REQ_MASTERLEVEL_INFO	//-> 100%
{
    PBMSG_HEAD	h;
	// ----
    int			iUserIndex;
    char		szCharName[MAX_IDSTRING + 1];
};
// -------------------------------------------------------------------------------

struct MLP_REQ_MASTERLEVEL_INFOSAVE	//-> 100%
{
    PBMSG_HEAD	h;
	// ----
    char		szCharName[MAX_IDSTRING + 1];
    short		nMLevel;
    __int64		i64MLExp;
    __int64		i64NextMLExp;
    short		nMLPoint;
};
// -------------------------------------------------------------------------------

struct PMSG_MASTERLEVEL_INFO	//-> 100%
{
    PBMSG_HEAD	h;
	// ----
    BYTE		subcode;
    short		nMLevel;
    BYTE		btMLExp1;
    BYTE		btMLExp2;
    BYTE		btMLExp3;
    BYTE		btMLExp4;
    BYTE		btMLExp5;
    BYTE		btMLExp6; 
    BYTE		btMLExp7;
    BYTE		btMLExp8;
    BYTE		btMLNextExp1;
    BYTE		btMLNextExp2;
    BYTE		btMLNextExp3;
    BYTE		btMLNextExp4;
    BYTE		btMLNextExp5;
    BYTE		btMLNextExp6;
    BYTE		btMLNextExp7;
    BYTE		btMLNextExp8;
    short		nMLPoint;
    WORD		wMaxLife;
    WORD		wMaxMana;
    WORD		wMaxShield;
    WORD		wMaxBP;
};
// -------------------------------------------------------------------------------

struct PMSG_MASTERLEVEL_UP	//-> 100%
{
    PBMSG_HEAD	h;
	// ----
    BYTE		subcode;
    short		nMLevel;
    short		nAddMLPoint;
    short		nMLPoint;
    short		nMaxMLPoint;
    WORD		wMaxLife;
    WORD		wMaxMana;
    WORD		wMaxShield;
    WORD		wMaxBP;
};
// -------------------------------------------------------------------------------

class CMasterLevelSystem	//-> Complete
{
public:
					CMasterLevelSystem();
	virtual			~CMasterLevelSystem();
	// ----
	void			ReadCommonServerInfo();
	void			ReadMonsterList(char * File);
	void			SetExperienceTable();
	void			gObjNextMLExpCal(LPOBJ lpObj);
	int				MasterLevelUp(LPOBJ lpObj, __int64& iAddExp, bool bEventMapReward, int iMonsterType);
	int				CheckIsMasterLevelCharacter(LPOBJ lpObj);	//Remove
	int				CheckMinMonsterLevel(LPOBJ lpObj, LPOBJ lpTargetObj);
	__int64			GetLevelExperienceTable(int iMasterLevel);
	int				CheckMasterLevelCharacterPkLevel(LPOBJ lpObj);
	int				CheckMasterLevelCharacterMoneyLevel(LPOBJ lpObj);
	// ----
	void			GDReqMasterLevelInfo(LPOBJ lpObj);
	void			DGRequestMasterLevelInfoLoad(BYTE * aRecv);
	void			GDRequestMasterLevelInfoSave(LPOBJ lpObj);
	void			GCSendMasterLevelWindowStatus(LPOBJ lpObj);
	void			GCMasterLevelUpInfo(LPOBJ lpObj);
	// ----

	int				m_CharacterLevel;
	int				m_CharacterReset;
	int				m_CharacterGrand;

private:
	__int64			MLExpTlb[MAX_MASTER_LEVEL + 1];
    int				m_iMinMonsterKillLevel;
    float			m_fAddExpRate;
	bool			m_UseMonsterList;	//Custom
	int				m_MonsterList[MASTER_MAX_LIST];
	// ----
}; extern CMasterLevelSystem g_MasterLevelSystem;
// -------------------------------------------------------------------------------