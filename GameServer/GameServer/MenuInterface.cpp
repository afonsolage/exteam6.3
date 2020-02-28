#include "StdAfx.h"
#include "MenuInterface.h"
#include "ExFunction.h"
#ifdef _MENU_INTERFACE_
cMenuInterface gMenuInterface;


	//void DataButtonRecv(ButtonRecv * aRecv, int aIndex)
	//{
	//	
	//			
	//			//ChangeClassSend rSend;
	//			////rSend.h.set((LPBYTE)&rSend, 0xFC, 0x02, sizeof(rSend));
	//			//rSend.NextLevel = 1;
	//			//rSend.RewardPoint = 200;
	//			//rSend.NeedWcoin = 10;
	//			//rSend.RewardWcoinP = 12;
	//			//DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
	//		
	//	
	//	

	//}
//
//
void cMenuInterface::DataRecv(ButtonSend * aRecv, int aIndex)
{
	int Button = aRecv->Button;
	ChangeClassSend rSend;
	rSend.h.set((LPBYTE)&rSend, 0xFB, 0x22, sizeof(rSend));
	rSend.NextLevel = 1;
				rSend.RewardPoint = 200;
				rSend.NeedWcoin = 10;
				rSend.RewardWcoinP = 12;
				DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));

		/*this->rUser[aIndex].rPoints--;
		this->FilterSkill(aIndex,iSkill);

		ClickSend rSend;
		rSend.h.set((LPBYTE)&rSend, 0xFB, 1, sizeof(rSend));
		rSend.Click = 1;
		rSend.SkillID = aRecv->SkillID;
		DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
		gObjCalCharacter(aIndex);*/
	
}

//void cMenuInterface::ConfigSend(int aIndex)
//{
//		RecvConfigChange rSend;
//		rSend.h.set((LPBYTE)&rSend, 0xFB, 0x21, sizeof(rSend));
//		rSend.NextLvl = 1;
//		rSend.RewardPoint = 200;
//		rSend.NeedValue = 1;
//		DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
//	
//}

#endif