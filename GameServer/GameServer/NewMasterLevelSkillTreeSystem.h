#pragma once 

#include "MuLua.h"
#include "user.h"



#define MAX_SKILLTREE_TYPE	3
#define MAX_SKILLTREE_RANK	9
#define MAX_SKILLTREE_POS	4
#define MAX_SKILLTREE_CLASS	7
#define MAX_SKILLTREE_LEVEL	20

enum eMasterSkillType
{
	// DK MSKILL
	AT_MSKILL_DK_CYCLONE1			= 326,
	AT_MSKILL_DK_SLASH1				= 327,
	AT_MSKILL_DK_FALLINGSLASH1		= 328,
	AT_MSKILL_DK_LUNGE1				= 329,
	AT_MSKILL_DK_TWISTINGSLASH1		= 330,
	AT_MSKILL_DK_RAGEFULBLOW1		= 331,
	AT_MSKILL_DK_TWISTINGSLASH2		= 332,
	AT_MSKILL_DK_RAGEFULBLOW2		= 333,
	AT_MSKILL_DK_DEATHSTAB1			= 336,
	AT_MSKILL_DK_DEATHSTAB2			= 339,
	AT_MSKILL_DK_DEATHSTAB3			= 342,
	AT_MSKILL_DK_DESTRUCTION1		= 337,
	AT_MSKILL_DK_DESTRUCTION2		= 340,
	AT_MSKILL_DK_BLOODSTORM			= 344,
	AT_MSKILL_DK_BLOODSTORM1		= 346,
	AT_MSKILL_DK_DESTRUCTION3		= 343,
	AT_MSKILL_DK_SWELLLIFE1			= 356,
	AT_MSKILL_DK_SWELLLIFE2			= 360,
	AT_MSKILL_DK_SWELLLIFE3			= 363,
	// DW MSKILL
	AT_MSKILL_DW_FLAME1				= 378,
	AT_MSKILL_DW_LIGHTNING1			= 379,
	AT_MSKILL_DW_EXPWIZARDRY1		= 380,
	AT_MSKILL_DW_INFERNO1			= 381,
	AT_MSKILL_DW_BLAST1				= 382,
	AT_MSKILL_DW_EXPWIZARDRY2		= 383,
	AT_MSKILL_DW_POISON1			= 384,
	AT_MSKILL_DW_EVILSPIRIT1		= 385,
	AT_MSKILL_DW_DECAY1				= 387,
	AT_MSKILL_DW_HELLFIRE1			= 388,
	AT_MSKILL_DW_ICE1				= 389,
	AT_MSKILL_DW_METEORIT1			= 390,
	AT_MSKILL_DW_ICESTORM1			= 391,
	AT_MSKILL_DW_NOVA1				= 392,
	AT_MSKILL_DW_ICESTORM2			= 393,
	AT_MSKILL_DW_METEORIT2			= 394,
	AT_MSKILL_DW_MANASHIELD1		= 403,
	AT_MSKILL_DW_MANASHIELD2		= 404,
	AT_MSKILL_DW_MANASHIELD3		= 406,
	AT_MSKILL_DW_EARTHPRISON		= 495,
	AT_MSKILL_DW_EARTHPRISON1		= 497,
	// FE MSKILL
	AT_MSKILL_FE_HEAL1				= 413,
	AT_MSKILL_FE_TRIPLESHOT1		= 414,
	AT_MSKILL_FE_PENETRATION1		= 416,
	AT_MSKILL_FE_DEFENSEBUFF1		= 417,
	AT_MSKILL_FE_TRIPLESHOT2		= 418,
	AT_MSKILL_FE_ATTACKBUFF1		= 420,
	AT_MSKILL_FE_ATTACKBUFF2		= 422,
	AT_MSKILL_FE_DEFENSEBUFF2		= 423,
	AT_MSKILL_FE_ICEARROW1			= 424,
	AT_MSKILL_FE_CURE				= 425,
	AT_MSKILL_FE_PARTYHEAL			= 426,
	AT_MSKILL_FE_PARTYHEAL1			= 429,
	AT_MSKILL_FE_POISONARROW		= 427,
	AT_MSKILL_FE_POISONARROW1		= 434,
	AT_MSKILL_FE_BLESS				= 430,
	AT_MSKILL_FE_BLESS1				= 433,
	AT_MSKILL_FE_MULTISHOT1			= 411,
	AT_MSKILL_FE_MULTISHOT2			= 431,
	AT_MSKILL_FE_SUMMONSATYROS		= 432,
	AT_MSKILL_FE_INFINITY1			= 441,
	// SUM MSKILL
	AT_MSKILL_SUM_SLEEP1			= 454,
	AT_MSKILL_SUM_CHAINLIGHTNING1	= 455,
	AT_MSKILL_SUM_LIGHTNSHOCK1		= 456,
	AT_MSKILL_SUM_DRAINLIFE1		= 458,
	AT_MSKILL_SUM_DRAINLIFE2		= 462,
	AT_MSKILL_SUM_WEAKNESS1			= 459,
	AT_MSKILL_SUM_INNOVATION1		= 460,
	AT_MSKILL_SUM_BLIND				= 461,
	AT_MSKILL_SUM_BLIND1			= 463,
	AT_MSKILL_SUM_BERSERK1			= 469,
	AT_MSKILL_SUM_BERSERK2			= 470,
	AT_MSKILL_SUM_BERSERK3			= 472,
	// MG MSKILL
	AT_MSKILL_MG_CYCLONE1			= 479,
	AT_MSKILL_MG_LIGHTNING1			= 480,
	AT_MSKILL_MG_TWISTINGSLASH1		= 481,
	AT_MSKILL_MG_POWERSLASH1		= 482,
	AT_MSKILL_MG_FLAME1				= 483,
	AT_MSKILL_MG_BLAST1				= 484,
	AT_MSKILL_MG_INFERNO1			= 486,
	AT_MSKILL_MG_EVILSPIRIT1		= 487,
	AT_MSKILL_MG_ICE1				= 489,
	AT_MSKILL_MG_ICE2				= 491,
	AT_MSKILL_MG_FIRESLASH1			= 490,
	AT_MSKILL_MG_FIRESLASH2			= 493,
	AT_MSKILL_MG_FLAMESTRIKE1		= 492,
	AT_MSKILL_MG_FLAMESTRIKE2		= 494,
	AT_MSKILL_MG_GIGANTICSTORM1		= 496,
	// DL MSKILL
	AT_MSKILL_DL_FIREBURST1			= 508,
	AT_MSKILL_DL_FORCEWAVE1			= 509,
	AT_MSKILL_DL_CRITICALDAMAGE1	= 511,
	AT_MSKILL_DL_EARTHSHAKE1		= 512,
	AT_MSKILL_DL_FIREBURST2			= 514,
	AT_MSKILL_DL_CRITICALDAMAGE2	= 515,
	AT_MSKILL_DL_EARTHSHAKE2		= 516,
	AT_MSKILL_DL_CRITICALDAMAGE3	= 517,
	AT_MSKILL_DL_FIRESCREAM1		= 518,
	AT_MSKILL_DL_ELECTRICSPARK1		= 519,
	AT_MSKILL_DL_FIRESCREAM2		= 520,
	AT_MSKILL_DL_IRONDEFENSE		= 521,
	AT_MSKILL_DL_IRONDEFENSE1		= 524,
	AT_MSKILL_DL_CRITICALDAMAGE4	= 522,
	AT_MSKILL_DL_CHAOTICDESEAR1		= 523,
	// RF SKILL
	AT_MSKILL_RF_KILLBLOW1			= 551,
	AT_MSKILL_RF_KILLBLOW2			= 554,
	AT_MSKILL_RF_UPERCUT1			= 552,
	AT_MSKILL_RF_UPERCUT2			= 555,
	AT_MSKILL_RF_CHAINDRIVE1		= 558,
	AT_MSKILL_RF_CHAINDRIVE2		= 562,
	AT_MSKILL_RF_DARKSIDE1			= 559,
	AT_MSKILL_RF_DARKSIDE2			= 563,
	AT_MSKILL_RF_DRAGONRORE1		= 560,
	AT_MSKILL_RF_DRAGONRORE2		= 561,
	AT_MSKILL_RF_DRAGONSLASH1		= 564,
	AT_MSKILL_RF_DRAGONSLASH2		= 565,
	AT_MSKILL_RF_DEFRATE1			= 569,
	AT_MSKILL_RF_DEFRATE2			= 572,
	AT_MSKILL_RF_FITNESS1			= 573,
#if(LANCER_SKILL==TRUE)
	AT_MSKILL_GL_LUNGE1				= 329,
	AT_MSKILL_GL_SPIN_STEP1			= 687,
	AT_MSKILL_GL_SPIN_STEP2			= 690,
	AT_MSKILL_GL_HARSH_STRIKE1		= 688,
	AT_MSKILL_GL_HARSH_STRIKE2		= 691,
	AT_MSKILL_GL_OBSIDIAN1			= 693,
	AT_MSKILL_GL_MAGIC_PIN1			= 692,
	AT_MSKILL_GL_MAGIC_PIN2			= 694,
	AT_MSKILL_GL_MAGIC_PIN3			= 695,
	AT_MSKILL_GL_BRECHE1			= 696,
	AT_MSKILL_GL_BRECHE2			= 697,
	AT_MSKILL_GL_BRECHE3			= 698,
	AT_MSKILL_GL_SHINING_PEAK1      = 699,
	AT_MSKILL_GL_BURST1				= 700,
	AT_MSKILL_GL_BURST2				= 701,
	AT_MSKILL_WRATH1				= 708,
	AT_MSKILL_WRATH2				= 709,
	AT_MSKILL_WRATH3				= 710,
	AT_MSKILL_CIRCLESHIELD1			= 703,
	AT_MSKILL_CIRCLESHIELD2			= 706,
	// Next Buff
#endif
};

struct _TreeData_SkillInfo
{
	int m_iIndex;
	BYTE m_btPoint;
	BYTE m_btMaxPoint;

	int m_iParentSkill1;
	int m_iParentSkill2;
	int m_iSkillID;
};

struct _TreeData
{
	int m_iUnk0;
	_TreeData_SkillInfo m_SkillInfo[MAX_SKILLTREE_TYPE][MAX_SKILLTREE_RANK][MAX_SKILLTREE_POS];
};

typedef struct 
{
	PBMSG_HEAD		head;				// 0
	BYTE			subcode;			// 3
	int				AddSkill;	// 4

} PMSG_REQ_MASTERLEVEL_SKILL, *LPPMSG_REQ_MASTERLEVEL_SKILL;
// --------------------------------------------------------------------------------------------


class CMasterLevelSkillTreeSystem
{
public:
	CMasterLevelSkillTreeSystem();
	virtual ~CMasterLevelSkillTreeSystem();

	void Init();
	void Load(char const * lpszFileName);
	void ClearPassiveSkill(LPOBJ lpObj);
	void AddPassiveSkill(LPOBJ lpObj,int iMLSkill,int iSkillLevel);
	int CheckSkillCondition(LPOBJ lpObj,int iMLSkill,int iSkillLevel);
	int CheckCompleteBrandOfSkill(LPOBJ lpObj,int iMLSkill);
	int CheckRequireStatus(int iMLSkill);
	int CheckPrimarySkill(LPOBJ lpObj,int iSkill);
	int GetBaseMasterLevelSkill(int iMLSkill);
	int gObjMagicAdd_MLS(LPOBJ lpObj,int iMLSkill,int iSkillLevel);
	void CGReqGetMasterLevelSkillTree(int aIndex);
	void CGReqGetMasterLevelSkill(PMSG_REQ_MASTERLEVEL_SKILL * lpMsg,int aIndex);
	int RunningSkill(LPOBJ lpObj,int aTargetIndex,CMagicInf* lpMagic,int bCombo,BYTE x,BYTE y, BYTE dir, BYTE aTargetPos);
	void MLS_WizardMagicDefense(LPOBJ lpObj,int aTargetIndex,CMagicInf * lpMagic);
	void MLS_Healing(LPOBJ lpObj,int aTargetIndex,CMagicInf * lpMagic);
	void MLS_Wheel(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex,int isCombo);
	void MLS_SkillSword4(LPOBJ lpObj,CMagicInf * lpMagic,int aTargetIndex,int isCombo);
	void MLS_SkillSword4_Magumsa(LPOBJ lpObj,CMagicInf * lpMagic,int aTargetIndex,int isCombo);
	void MLS_SkillSword5(LPOBJ lpObj,CMagicInf * lpMagic,int aTargetIndex,int isCombo);
	void MLS_SkillSword1(LPOBJ lpObj,CMagicInf * lpMagic,int aTargetIndex,int isCombo);
	void MLS_SkillSword2(LPOBJ lpObj,CMagicInf * lpMagic,int aTargetIndex,int isCombo);
	int MLS_SkillStrengthenDesruction(LPOBJ lpObj,CMagicInf *lpMagic,BYTE x,BYTE y,int aTargetIndex,int isCombo);
	void MLS_KnightSkillAddLife(LPOBJ lpObj,CMagicInf *lpMagic);
	void MLS_SkillFulKnightSkillAddLife(LPOBJ lpObj,CMagicInf *lpMagic);
	void MLS_SkillMasteryKnightSkillAddLife(LPOBJ lpObj,CMagicInf *lpMagic);
	int MLS_SkillStrengthenMagicPower(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex);
	int MLS_SkillSkillfulMagicPower(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex);
	void MLS_SkillStrengthenFlame(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex);
	void MLS_SkillStrengthenThunder(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex);
	void MLS_SkillMeteorit(LPOBJ lpObj,int aTargetIndex,CMagicInf* lpMagic);
	void MLS_SkillStrengthenPoison(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex);
	void MLS_SkillStrengthenExPoison(int aIndex,CMagicInf *lpMagic,BYTE x,BYTE y,int aTargetIndex);
	void MLS_SkillStrengthenIce(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex);
	void MLS_SkillWizardMagicDefense(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex);
	void MLS_SkillWizardMagicDefenseMastery(LPOBJ lpObj,CMagicInf *lpMagic,int aTargetIndex);

	int MLS_SkillInfinityArrow(int aIndex,int aTargetIndex,CMagicInf *lpMagic);
	int MLS_SkillStrengthenBerserker(int aIndex,CMagicInf *lpMagic);
	int MLS_SkillSkillfulBerserker(int aIndex,CMagicInf *lpMagic);
	int MLS_SkillMasteryBerserker(int aIndex,CMagicInf *lpMagic);
	void MLS_SkillStrendthenAddCriticalDamage(int aIndex,int skill_level,CMagicInf *lpMagic);
	void MLS_SkillSkillFulAddCriticalDamage(int aIndex,int skill_level,CMagicInf *lpMagic);
	void MLS_SkillMasteryAddCriticalDamage(int aIndex,int skill_level,CMagicInf *lpMagic);
	int MLS_DarkHorseAttack(LPOBJ lpObj,int aTargetIndex,CMagicInf * lpMagic);
	int MLS_FireBurst(LPOBJ lpObj,int aTargetIndex,CMagicInf * lpMagic);
	int MLS_SkillStrengthenSpear(int aIndex,int aTargetIndex,CMagicInf *lpMagic);
	int MLS_SkillAreaMonsterAttack(int aIndex,CMagicInf *lpMagic,BYTE x,BYTE y,int aTargetIndex,int aDistance,int bPVP,int nSuccessRate,int nDelay);
	int MLS_SuddenIce(int aIndex,CMagicInf * lpMagic,BYTE x,BYTE y,int aTargetIndex);
	int MLS_CalDistance(int x,int y,int x1,int y1);
	int MLS_GetAngle(int x,int y,int tx,int ty);
	void MLS_SkillFrustrum(int aIndex,float fangle,float tx,float ty);
	int MLS_KnightBlow(int aIndex,int aTargetIndex,CMagicInf *lpMagic,int isCombo);
	int MLS_KnightBlowStrength(int aIndex,int aTargetIndex,CMagicInf *lpMagic,int isCombo);
	void MLS_SkillBlowOfFury(int aIndex,CMagicInf *lpMagic,BYTE x,BYTE y,int aTargetIndex,int isCombo);
	void MLS_SkillDefense(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	void MLS_SkillAttack(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	void MLS_SkillStrengthenAttack(int aIndex,int aTargetIndex,CMagicInf *lpMagic);
	void MLS_SkillStrengthenDefense(int aIndex,int aTargetIndex,CMagicInf *lpMagic);
	void MLS_MaGumSkillDefenseDown(int aIndex,int aTargetIndex);
	void MLS_PowerSlash(int aIndex,CMagicInf *lpMagic,BYTE x,BYTE y,BYTE Targetangle,int aTargetIndex);
	int MLS_FireScream(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	int WeaponMagicDel(LPOBJ lpObj,BYTE aSkill,BYTE Level);
	int WeaponMagicAdd(LPOBJ lpObj,BYTE aSkill,BYTE Level);
	int GetWeaponMagicSearch(LPOBJ lpObj,int nCount);
	int MLS_SkillSleep(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	int MLS_SkillChainLightning(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	int MLS_SkillLightningShock(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	int MLS_SkillDrainLife(int aIndex,int aTargetIndex,CMagicInf * lpMagic);
	int MLS_SkillHellFire2(int aIndex, int aTargetIndex, CMagicInf * lpMagic);
	int MLS_SkillHellFire2Start(int aIndex, CMagicInf * lpMagic);
	void MLS_SkillEarthPrison(int aIndex,int aTargetIndex,CMagicInf* lpMagic);
	int MLS_SkillCure(int aIndex,int aTargetIndex,CMagicInf* lpMagic);
	void MLS_SkillMultiShot(int aIndex,CMagicInf* lpMagic,BYTE targetpos,int aTargetIndex);
	int MLS_SkillBless(int aIndex,int aTargetIndex,CMagicInf* lpMagic);
	void MLS_MaGumSkillDefenseDownMastery(int aIndex,int aTargetIndex,CMagicInf* lpMagic);
	void MLS_SkillGiganticStorm(int aIndex,CMagicInf* lpMagic,BYTE x,BYTE y,int aTargetIndex);
	void MLS_SkillFlameStrike(int aIndex, CMagicInf * lpMagic,BYTE targetangle, int aTargetIndex);
	int MLS_SkillWeakness(int aIndex,CMagicInf* lpMagic,BYTE x,BYTE y,int aTargetIndex);
	int MLS_SkillInnovation(int aIndex,CMagicInf* lpMagic,BYTE x,BYTE y,int aTargetIndex);
	int MLS_SkillBlind(int aIndex,int aTargetIndex,CMagicInf* lpMagic);
	void MLS_SkillFulMasteryAddCriticalDamage(int aIndex,int aTargetIndex,CMagicInf *lpMagic);
	void MLS_SkillElectricSpark(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	void MLS_SkillChaoticDesier(int aIndex, CMagicInf * lpMagic, BYTE TargetPos, int aTargetIndex);
	void MLS_SkillIronDefense(int aIndex,int aTargetIndex,CMagicInf* lpMagic);
	void MLS_SkillMonkBarrageJustOneTarget(int aIndex,CMagicInf * lpMagic,int aTargetIndex);
	void MLS_SkillMonkBarrageJustOneTargetMastery(int aIndex,CMagicInf * lpMagic,int aTargetIndex);
	int MLS_SkillMonkBuffApplyParty(int aIndex,CMagicInf * lpMagic);
	int MLS_SkillMonkBuffApplyPartyMastery(int aIndex,CMagicInf * lpMagic);
	void MLS_SkillPartyHeal(int aIndex,int aTargetIndex,CMagicInf* lpMagic);

	int GetSkillReqMLPoint(int iClass,int iSkill);
	int GetMaxPointOfMasterSkill(int iClass,int iSkill);
	float GetMasterSkillValue(int iType,int iPoint);
	float GetMasterSkillManaIncRate(int iPoint);
	float GetBrandOfMasterSkillValue(LPOBJ lpObj,int iSkill,int iStep);
	int CheckSkillLevel(LPOBJ lpObj,int iSkill);
	int CheckPreviousRankSkill(LPOBJ lpObj,int iSkill,int iLevel);
	int GetMasterSkillUIIndex(int iClass,int iSkill);
	int GetParentSkill1(int iClass,int iSkill);
	int GetParentSkill2(int iClass,int iSkill);
	void SetItemMLPassiveSkill(LPOBJ lpObj,int iType);
	void SetPetItemMLPassiveSkill(LPOBJ lpObj,int iType);
	int GetCurSkillLevel(LPOBJ lpObj,int iSkill);
	float RoundValue(double dbValue,int iPos);
	float GetSkillAttackDamage(LPOBJ lpObj,int iSkill);
	void MLS_SkillFrustrum3(int aIndex,BYTE aTargetPos,float f1,float f2,float f3,float f4);
	
private:

	_TreeData m_SkillTreeData[MAX_SKILLTREE_CLASS];
	float m_fValue[81][MAX_SKILLTREE_LEVEL+1];
#ifdef _LUA_
	MULua m_Lua;
#endif
	bool IsLoaded;

}; extern CMasterLevelSkillTreeSystem g_MasterSkillSystem;