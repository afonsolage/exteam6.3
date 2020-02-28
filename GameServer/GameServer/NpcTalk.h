#ifndef NPCTALK_H
#define NPCTALK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_NPC_PHANTOM_BUFFER	220

//Season 5 Gens
struct GC_ANS_NPC_TALK_V3
{
	PBMSG_HEAD2		h;		// C3:F9:01
	WORD		NpcType;
	WORD		Index;
	DWORD		Points;
};

struct GC_ANS_NPC_TALK_V1
{
	PHEADB	PHeader;	// C3:30
	BYTE NpcNumber;
	BYTE Param1;
	BYTE Param2;
	BYTE Param3;
	BYTE Param4;
};

struct GC_ANS_NPC_TALK_V2
{
	PHEADB	PHeader;	// C3:30
	BYTE NpcNumber;
	BYTE Param1;
	BYTE Param2;
	BYTE Param3;
	BYTE Param4;
	BYTE Param5;
	BYTE Param6;
};

struct PMSG_ANS_DIG_NPC_CLICK // 1.01.00
{
	PBMSG_HEAD2 h;
	WORD	wNPCIndex;
	DWORD	dwContributePoint;
};

BOOL NpcTalk(LPOBJ lpNpc, LPOBJ lpObj);

int NpcBattleAnnouncer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcFasi(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcGuildMasterTalk(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRolensiaGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcChaosGoblelin(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRusipher(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcPosionGirl(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWizard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWareHousemen(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcWarehouse(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcNoriaRara(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasMadam(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcEventChipNPC(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRorensiaSmith(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcNoriJangIn(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcQuestCheck(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcServerDivision(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRoadMerchant(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcAngelKing(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcAngelMessanger(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRolensiaMadam(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWeapon(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDarkSpiritTrainer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcJewelMixDealer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSiegeMachine_Attack(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSiegeMachine_Defense(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcElderCircle(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleGateLever(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleCrown(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleSwitch(LPOBJ lpNpc, LPOBJ lpObj);

//#if(GS_CASTLE==1)
BOOL NpcCastleHuntZoneGuard(LPOBJ lpNpc, LPOBJ lpObj);
//#endif

BOOL NpcShadowPhantom(LPOBJ lpNpc, LPOBJ lpObj);

//#if(GS_CASTLE==1)
BOOL NpcCrywolfAltar(LPOBJ lpNpc, LPOBJ lpObj);
//#endif

//#if(GS_CASTLE==0)
BOOL NpcMainatenceMachine(LPOBJ lpNpc, LPOBJ lpObj);
//#endif

BOOL NpcReira(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcChaosCardMaster(LPOBJ lpNpc, LPOBJ lpObj);

//NPCS New
BOOL NpcPamelaSupplier(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcAngelaSupplier(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcFirecrackerMerchant(LPOBJ lpNpc, LPOBJ lpObj);

//Illusion Temple
BOOL NpcIllusionStatue(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcIllusionYellowPedestal(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcIllusionBluePedestal(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcIllusionMirage(LPOBJ lpNpc, LPOBJ lpObj);

//Season3
BOOL NpcSilviaSupplier(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRheaMerchant(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcMarceWizard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCherryBlossomSpirit(LPOBJ lpNpc, LPOBJ lpObj);

//Season4
BOOL NpcSeedMaster(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSeedResearcher(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcLuckyCoinExchanger(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcXMasSantaClaus(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSnowMan(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcLittleSantaBuffer(LPOBJ lpNpc, LPOBJ lpObj,int BuffEffect);
//Season4.6
bool NpcTitusGatekeeper(LPOBJ lpNpc, LPOBJ lpObj);
bool NpcMoss(LPOBJ lpNpc, LPOBJ lpObj);
//Season 5.3
BOOL NpcJuliaTalk(LPOBJ lpNpc, LPOBJ lpObj);
BOOL SartigantheAngel(OBJECTSTRUCT *lpNpc, OBJECTSTRUCT *lpObj);
BOOL NpcSilverBox(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcGoldBox(LPOBJ lpNpc, LPOBJ lpObj);
bool NpcJerint(LPOBJ lpNpc, LPOBJ lpObj);	//Season 5 ImperialFort
bool Npc_Dialog(LPOBJ lpNpc, LPOBJ lpObj); //-> Complete
bool NpcDabide(LPOBJ lpNpc, LPOBJ lpObj);
#endif