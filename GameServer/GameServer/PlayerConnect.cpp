#include "StdAfx.h"
#include "user.h"
#include "PlayerConnect.h"
#include "Reset.h"
#include "Message.h"
#include "Configs.h"
#include "ExLicense.h"
#ifdef _UPDATE8_
#include "ShowOnline.h"
#endif
#include "ConnectEx.h"
#include "ExText.h"

void ExPlayerConnectSystem(int aIndex)
{	
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->MapNumber == 10){
	
	}

#ifdef TWO_IP_CONNECT_OFF
	if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::Local) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		int CountIpAddress;
		CountIpAddress = 0;
		for ( int n = OBJ_STARTUSERINDEX ; n < OBJMAX ; n++)
		{
				if ( gObj[n].Type == OBJ_USER && gObj[n].Connected == PLAYER_PLAYING )
				{
					if (lpObj->m_Index == gObj[n].m_Index)
					{
						continue;
					}
						if(!strcmp(lpObj->Ip_addr, gObj[n].Ip_addr))
						{
							CountIpAddress++;
								
						}
						
				}
		}
		if(CountIpAddress >= 2)
		{
			g_ConnectEx.SendClose(aIndex, NORM_DC);
			return;
		}
			
	}
#endif

	if(g_ExLicense.CheckUser(eExUB::ulasevich) || g_ExLicense.CheckUser(eExUB::Local3) || g_ExLicense.CheckUser(eExUB::ulasevich2))
	{
		if(ExConfig.PlayerConnect.ShowNameAll == 1)
		{
			MessageSendAllEx(ExConfig.PlayerConnect.ShowNameColor,"[System]", "%s Online" , lpObj->Name);
		}
		if ( CheckAuthorityCondition(98, lpObj) == true) //season4 changed
		{
			if(ExConfig.PlayerConnect.ShowGMAll == 1)
			{
				MessaageAllGlobal("[%s]:Online", lpObj->Name);
			}
		}
	}
	if(!ExConfig.PlayerConnect.EnablePlayerConnectSystem)
		return;

#ifdef _UPDATE8_
	if(ExConfig.PlayerConnect.ShowOnline)	MsgNormal(aIndex, g_ExText.GetText(2), getShowOnline());
#endif
	if(ExConfig.PlayerConnect.ShowReset) MsgNormal(aIndex, g_ExText.GetText(0), lpObj->Reset);
	if(ExConfig.PlayerConnect.ShowGReset) MsgNormal(aIndex, g_ExText.GetText(1), lpObj->GReset);
}