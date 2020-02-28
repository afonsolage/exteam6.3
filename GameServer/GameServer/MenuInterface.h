#include "StdAfx.h"
#include "user.h"

#ifdef _MENU_INTERFACE_


struct ButtonSend
{
	PBMSG_HEAD2 h;
	WORD Button;
};

struct ChangeClassSend{
	PBMSG_HEAD2 h;
	int NextLevel;
	int NeedWcoin;
	int RewardPoint;
	int RewardWcoinP;
};

struct ClassSend
{
	PBMSG_HEAD2 h;
	BYTE Click;
	WORD Class;
};
struct RecvConfigChange
{
	PBMSG_HEAD2 h;
	int NextLvl;
	int RewardPoint;
	/*int RewardPrice;
	int RewardValue;
	int NeedPrice;*/
	int NeedValue;
};

class cMenuInterface{
public:
	//void DataButtonRecv(ButtonRecv * aRecv, int aIndex);
	void DataRecv(ButtonSend *aRecv, int aIndex);
	void ConfigSend(int aIndex);

};

extern cMenuInterface gMenuInterface;

#endif