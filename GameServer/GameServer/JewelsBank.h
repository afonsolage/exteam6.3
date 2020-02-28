#pragma once
#include "StdAfx.h"
#include "DSProtocol.h"

#define JEWELSBANK_DIR	"..\\Data\\ExData\\JewelsBank.ini"

struct PMSG_JEWELBANK
{
	PBMSG_HEAD2 h;
	int Result;
};

class JewelsBank
{
private: 
	bool Enable;
	
	int ExChaosTeen;
	int ExChaosTwenty;
	int ExChaosThirty;
	int ExChaosForty;
	int ExChaosFifty;
	int ExChaosHundred;

	int ExBlessTeen;
	int ExBlessTwenty;
	int ExBlessThirty;
	int ExBlessForty;
	int ExBlessFifty;
	int ExBlessHundred;

	int ExSoulTeen;
	int ExSoulTwenty;
	int ExSoulThirty;
	int ExSoulForty;
	int ExSoulFifty;
	int ExSoulHundred;

	int ExLifeTeen;
	int ExLifeTwenty;
	int ExLifeThirty;
	int ExLifeForty;
	int ExLifeFifty;
	int ExLifeHundred;

	int ExCreateonTeen;
	int ExCreateonTwenty;
	int ExCreateonThirty;
	int ExCreateonForty;
	int ExCreateonFifty;
	int ExCreateonHundred;

	/**/
	int ExGuardianTeen;
	int ExGuardianTwenty;
	int ExGuardianThirty;
	int ExGuardianForty;
	int ExGuardianFifty;
	int ExGuardianHundred;

	int ExHarmonyTeen;
	int ExHarmonyTwenty;
	int ExHarmonyThirty;
	int ExHarmonyForty;
	int ExHarmonyFifty;
	int ExHarmonyHundred;

	int ExLowStoneTeen;
	int ExLowStoneTwenty;
	int ExLowStoneThirty;
	int ExLowStoneForty;
	int ExLowStoneFifty;
	int ExLowStoneHundred;

	int ExHighStoneTeen;
	int ExHighStoneTwenty;
	int ExHighStoneThirty;
	int ExHighStoneForty;
	int ExHighStoneFifty;
	int ExHighStoneHundred;

	int ExGemStoneTeen;
	int ExGemStoneTwenty;
	int ExGemStoneThirty;
	int ExGemStoneForty;
	int ExGemStoneFifty;
	int ExGemStoneHundred;
	/**/

	int ExForty;

	int CountExChaos;
	int CountExBless;
	int CountExSoul;
	int CountExLife;
	int CountExCreateon;

public:
	void Load();

	void sendchaosbank(int aIndex, int Count);
	void sendblessbank(int aIndex, int Count);
	void sendsoulbank(int aIndex, int Count);
	void sendlifebank(int aIndex, int Count);
	void sendcreateonbank(int aIndex, int Count);

	void recvchaosbank(int aIndex, int Count);
	void recvblessbank(int aIndex, int Count);
	void recvsoulbank(int aIndex, int Count);
	void recvlifebank(int aIndex, int Count);
	void recvcreateonbank(int aIndex, int Count);
	
#ifdef PRIVATE_MODULE
#if _CONFLICT_
	void exchaos(int aIndex, int Count);
	void exbless(int aIndex, int Count);
	void exsoul(int aIndex, int Count);
	void exlife(int aIndex, int Count);
	void excreateon(int aIndex, int Count);

	void exGuardian(int aIndex, int Count);
	void exHarmony(int aIndex, int Count);
	void exLowStone(int aIndex, int Count);
	void exHighStone(int aIndex, int Count);
	void exGemStone(int aIndex, int Count);
#endif
#endif
	
	void sendzen(int aIndex, int Count);
	void recvzen(int aIndex, int Count);
	void sendGuardianBank(int aIndex, int Count);
	void sendHarmonyBank(int aIndex, int Count);
	void sendLowStoneBank(int aIndex, int Count);
	void sendHighStoneBank(int aIndex, int Count);
	void sendGemStoneBank(int aIndex, int Count);
	void recvGuardianBank(int aIndex, int Count);
	void recvHarmonyBank(int aIndex, int Count);
	void recvLowStoneBank(int aIndex, int Count);
	void recvHighStoneBank(int aIndex, int Count);
	void recvGemStoneBank(int aIndex, int Count);
	void Packet(int aIndex, PMSG_JEWELBANK* lpMsg);
};
extern JewelsBank gJewelsBank;