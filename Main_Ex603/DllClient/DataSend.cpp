#include "stdafx.h"
#include "DataSend.h"
#include "Interface.h"
#include "Object.h"
#include "Configs.h"

cDataSend gDataSend;

void cDataSend::SendOfflineAttack()
{
	lpViewObj lpViewPlayer		= &*(ObjectPreview*)oUserPreviewStruct;

	if(	gInterface.CheckWindow(CashShop)
		||	gInterface.CheckWindow(SkillTree)
		||	gInterface.CheckWindow(FullMap)  
		||  gInterface.CheckWindow(Inventory) 
		||  gInterface.CheckWindow(Character)
		||  gInterface.CheckWindow(CommandWindow)
		||  gInterface.CheckWindow(Party)
		||  gInterface.CheckWindow(Guild) 
		||  gInterface.CheckWindow(GensInfo) 
		||  lpViewPlayer->InSafeZone )
	{
		return;
	}

	OFFLINEATTACK_REQ pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 11, sizeof(pRequest));
	pRequest.Result	= 1;// = gObjUser.GetActiveSkill();
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);

}

void cDataSend::SendOpenAutoPartyList()
{
	lpViewObj lpViewPlayer		= &*(ObjectPreview*)oUserPreviewStruct;

	//if(	gInterface.CheckWindow(CashShop)
	//	||	gInterface.CheckWindow(SkillTree)
	//	||	gInterface.CheckWindow(FullMap)  
	//	||  gInterface.CheckWindow(Inventory) 
	//	||  gInterface.CheckWindow(Character)
	//	||  gInterface.CheckWindow(CommandWindow)
	//	||  gInterface.CheckWindow(Party)
	//	||  gInterface.CheckWindow(Guild) 
	//	||  gInterface.CheckWindow(GensInfo) 
	//	||  lpViewPlayer->InSafeZone )
	//{
	//	return;
	//}

	CG_AUTOPARTYLIST pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 16, sizeof(pRequest));
	pRequest.Result	= 1;// = gObjUser.GetActiveSkill();
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);

}

void cDataSend::SendConfig()
{
	CG_MINIMAP_PARTY pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xD7, sizeof(pMsg));
	pMsg.MiniMap = gMiniMap;
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}