#include "stdafx.h"
#include "User.h"
#include "NewPartyBuff.h"
#include "TMemory.h"
#include "Import.h"
#include "Object.h"
#include "Controller.h"
#include "Interface.h"
#include "NewParty.h"
// -----------------------------------------------------------------------------------------------

NewPartyBuff g_NewPartyBuff;
// -----------------------------------------------------------------------------------------------

void NewPartyBuff::Load()
{
	this->High	= 10.5;
	this->Whith = 7.5;

	SetOp((LPVOID)0x0084C022, this->DrawPtIcon, ASM::CALL);

	ZeroMemory(&this->AllBuff,sizeof(this->AllBuff));
	ZeroMemory(&this->PartyUser,sizeof(this->PartyUser));

	this->BindBuff(AT_INCREASE_ATTACK);
	this->BindBuff(AT_INCREASE_DEFENSE);
	this->BindBuff(AT_NPC_HELP);
	this->BindBuff(AT_WIZARD_DEFENSE);
	this->BindBuff(AT_INCREASE_CRITICAL_DMG);
	this->BindBuff(AT_INFINITY_ARROW);
	this->BindBuff(AT_SWELL_LIFE);
	this->BindBuff(AT_POISON);
	this->BindBuff(AT_ICE);
	this->BindBuff(AT_ICE_ARROW);
	this->BindBuff(AT_REDUCE_DEFENSE);
	this->BindBuff(AT_STUN);
	this->BindBuff(AT_DAMAGE_REFLECTION);
	this->BindBuff(AT_SLEEP);
	this->BindBuff(AT_BERSERKER);
	this->BindBuff(AT_EXPANSION_WIZARDRY);
	
	this->BindBuff(BUFF_IGNORE_DEFENSE);
	this->BindBuff(BUFF_INCREASE_VIT);
	this->BindBuff(BUFF_INCREASE_DEFRATE);
	this->BindBuff(BUFF_DECREASE_DEFRATE);
	this->BindBuff(BUFF_SWELL_LIFE2);
	this->BindBuff(BUFF_SWELL_LIFE3);
	this->BindBuff(BUFF_EXP_WIZARDRY2);
	this->BindBuff(BUFF_EXP_WIZARDRY3);
	this->BindBuff(BUFF_MANASHIELD2);
	this->BindBuff(BUFF_BERSERKER2);
	this->BindBuff(BUFF_BERSERKER3);
	this->BindBuff(BUFF_BERSERKER4);
	this->BindBuff(BUFF_INCREASE_DEFRATE2);
	this->BindBuff(BUFF_INCREASE_DEFRATE3);
	this->BindBuff(BUFF_INCREASE_VIT2);
	this->BindBuff(BUFF_IGNORE_DEFENSE2);
	
}
// -----------------------------------------------------------------------------------------------

void NewPartyBuff::DrawPtIcon(DWORD a1, float a2, float a3, float a4, float a5)
{
	g_NewPartyBuff.DrawX = a2;
	pDrawGUI(a1, a2, a3, a4, a5);
}
// -----------------------------------------------------------------------------------------------

void NewPartyBuff::BindBuff(int BuffIndex)
{
	this->AllBuff[BuffIndex] = true; 
}
// -----------------------------------------------------------------------------------------------

void NewPartyBuff::RecvBuff(PMSG_BUFFLIST_SEND_PARTY * Recv)
{
#if _NEW_PARTY_SYSTEM_ == TRUE
	for(int i = 0; i < g_Party.PartyMemberCount; i++)
#else
	for(int i = 0; i < pPartyMemberCount; i++)
#endif
	{
#if _NEW_PARTY_SYSTEM_ == TRUE
		//PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * i);

		if(!strcmp(g_Party.PartyData[i].Name ,Recv->szName))
		{
			memcpy(this->PartyUser[i].szName,Recv->szName, 10);
			this->PartyUser[i].btBuffCount = Recv->btBuffCount;

			for(int a = 0; a < this->PartyUser[i].btBuffCount; a++)
			{
				this->PartyUser[i].iBuffList[a] = Recv->iBuffList[a];
			}
		}
#else
		PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * i);

		if(!strcmp(PartyMember.Name ,Recv->szName))
		{
			memcpy(this->PartyUser[i].szName,Recv->szName, 10);
			this->PartyUser[i].btBuffCount = Recv->btBuffCount;

			for(int a = 0; a < this->PartyUser[i].btBuffCount; a++)
			{
				this->PartyUser[i].iBuffList[a] = Recv->iBuffList[a];
			}
		}
#endif
	}
}
// -----------------------------------------------------------------------------------------------

void NewPartyBuff::DrawBuff()
{
	/* if( gInterface.CheckWindow(ObjWindow::CashShop) || 
		gInterface.CheckWindow(ObjWindow::FullMap)  || 
		gInterface.CheckWindow(ObjWindow::SkillTree) )
	{
		return;
	} */

#if _NEW_PARTY_SYSTEM_	== TRUE
	if(!g_Party.PartyShow)
	{
		return;
	}
#endif

	for(int i = 0; i < g_Party.PartyMemberCount; i++)
	{
#if _NEW_PARTY_SYSTEM_ == TRUE
		g_NewPartyBuff.DrawX = g_Party.CoordX(i);
#endif

		float X = g_NewPartyBuff.DrawX - Whith;

		float Y = 15 + ( 24 * i );

		for(int n = 0; n < this->PartyUser[i].btBuffCount; n++)
		{
			int BuffIndex =	this->PartyUser[i].iBuffList[n];

			if(this->AllBuff[BuffIndex] == true)
			{
				this->DrawBuffParty(BuffIndex, X, Y);

				if(n == 0 || n == 2 || n == 4 || n == 6 || n == 8)
				{
					Y += High;	
				}
				else
				{
					X -= Whith;	
					Y -= High;
				}		
			}
		}
	}
}
// -----------------------------------------------------------------------------------------------

void NewPartyBuff::DrawBuffParty(int BuffIndex, int X, int Y)
{
	int Model = 0;
	int  v6 = 0;

	if( BuffIndex > 0 && BuffIndex <= 80)
	{
		Model = 31725;
		v6 = (BuffIndex - 1) % 80;
	}
	else if (BuffIndex > 80 && BuffIndex <= 160)
	{
		Model = 0x7BEE;
		v6 = (BuffIndex - 81) % 80;
	}
	else
	{
		Model = 0x7BEF;
		v6 = (BuffIndex - 161) % 80;
	}
    
    float CritX = (double)(v6 % 10) * this->Whith / 96;
	float CritY = (double)(v6 / 10) * this->High / 96;

	float standartWhith = this->Whith / 96;
	float standartHight = this->High / 96;

	pDrawGUFULL(Model, X, Y, this->Whith, this->High, CritX, CritY, standartWhith, standartHight, 1, 1, 0.0);
}
// -----------------------------------------------------------------------------------------------