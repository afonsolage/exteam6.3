#include "StdAfx.h"
#include "PartySearch.h"
#include "GameMain.h"
#include "..\\common\\winutil.h"
#include "user.h"
#include "logproc.h"
#include "ExLicense.h"
#include "ExFunction.h"
#if(CUSTOM_PARTY_SEARCH==TRUE)
// ----------------------------------------------------------------------------------------------

PartySearch g_PartySearch;
// ----------------------------------------------------------------------------------------------

void PartySearch::Init()
{
	this->ActiveSystem = false;	//Active System
	ZeroMemory(&this->Party,sizeof(this->Party));
}
// ----------------------------------------------------------------------------------------------

void PartySearch::Load()
{
	if(g_ExLicense.user.PartySearch == false)
	{
		return;
	}
	this->Init();

	this->Read(gDirPath.GetNewPath("ExData\\PartySearch.txt"));
}
// ----------------------------------------------------------------------------------------------

void PartySearch::Read(char* File)
{
	CheckFile(File);

	this->ActiveSystem = GetPrivateProfileInt("Common", "ActiveSystem", 0, File);

	this->NPC_CLASS = GetPrivateProfileInt("Common", "NPC_CLASS", 0, File);
	this->NPC_MAP = GetPrivateProfileInt("Common", "NPC_MAP", 0, File);
	this->NPC_X = GetPrivateProfileInt("Common", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("Common", "NPC_Y", 0, File);
}
// ----------------------------------------------------------------------------------------------

bool PartySearch::NPC_Dialod(int aIndex, int aNpcIndex)
{
	return false;
	/*
	if(!this->ActiveSystem)
	{
 		return false;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNpcIndex];

	if(		lpNpc->Class		== this->NPC_CLASS 
		&&	lpNpc->MapNumber	== this->NPC_MAP
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{
		this->Search(lpUser->m_Index);
		return true;
	}
	// ----
	return false;
	*/
}
// ----------------------------------------------------------------------------------------------

void PartySearch::Search(int aIndex)
{
	if(!this->ActiveSystem)
	{
		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	if(lpUser->OffTrade != 0 || lpUser->OffExp!=0)
	{
		return;
	}

	BYTE SendBuff[5000];
	int datasize = 6;
	BYTE icount = 0;

	for(int n=OBJ_STARTUSERINDEX;n<OBJMAX;n++)
	{
		LPOBJ lpSearch = &gObj[n];
		if(lpSearch->Connected < PLAYER_PLAYING || !lpSearch->pt_Active) 
		{
			continue;
		}

		int partynum = lpSearch->PartyNumber;
		if(partynum >= 0)
		{
			if( !gParty.Isleader(gObj[n].PartyNumber, n, gObj[n].DBNumber) )
			{
				continue;
			}
		}
		

		AutoParty_DATA ap;
		ap.Index = n;
		strncpy(ap.Name, lpSearch->Name, 10);
		ap.Level = lpSearch->pt_MaxLevel;
		ap.X = lpSearch->X;
		ap.Y = lpSearch->Y;
		ap.Map = lpSearch->MapNumber;
		//int partynum = lpSearch->PartyNumber;
		ap.Count = gParty.GetCount(partynum);

		/*if(lpSearch->pt_bAllClass)
		{
			// -> All Class
			ap.dw = true;
			ap.dk = true;
			ap.ee = true;
			ap.mg = true;
			ap.dl = true;
			ap.su = true;
		}
		else*/ if(lpSearch->pt_bOnlyOneClass)
		{
			// -> Gold Party
			ap.dw = true;
			ap.dk = true;
			ap.ee = true;
			ap.mg = true;
			ap.dl = true;
			ap.su = true;
			ap.rf = true;

			if(partynum >= 0)
			{
				
				for(int p = 0; p < MAX_USER_IN_PARTY; p++)
				{
					int number = gParty.m_PartyS[partynum].Number[p];

					if(number >= 0)
					{
						LPOBJ lpPartyObj = &gObj[number];

						if(lpPartyObj->Class == 0)
						{
							ap.dw = false;
						}
						else if(lpPartyObj->Class == 1)
						{
							ap.dk = false;
						}
						else if(lpPartyObj->Class == 2)
						{
							ap.ee = false;
						}
						else if(lpPartyObj->Class == 3)
						{
							ap.mg = false;
						}
						else if(lpPartyObj->Class == 4)
						{
							ap.dl = false;
						}
						else if(lpPartyObj->Class == 5)
						{
							ap.su = false;
						}
						else if(lpPartyObj->Class == 6)
						{
							ap.rf = false;
						}
					}
				}
			}
			else 
			{
				if(lpSearch->Class == 0)
				{
					ap.dw = false;
				}
				else if(lpSearch->Class == 1)
				{
					ap.dk = false;
				}
				else if(lpSearch->Class == 2)
				{
					ap.ee = false;
				}
				else if(lpSearch->Class == 3)
				{
					ap.mg = false;
				}
				else if(lpSearch->Class == 4)
				{
					ap.dl = false;
				}
				else if(lpSearch->Class == 5)
				{
					ap.su = false;
				}
				else if(lpSearch->Class == 6)
				{
					ap.rf = false;
				}
			}
		}
		else
		{
			// -> Other Char
			ap.dw = lpSearch->pt_bDarkWizard;
			ap.dk = lpSearch->pt_bDarkKnight;
			ap.ee = lpSearch->pt_bElf;
			ap.mg = lpSearch->pt_bMagicGladiator;
			ap.dl = lpSearch->pt_bDarkLord;
			ap.su = lpSearch->pt_bSummoner;
			ap.rf = lpSearch->pt_bAllClass;
		}

		memcpy(&SendBuff[datasize],&ap,sizeof(ap));
		datasize += sizeof(ap);

		icount++;

		if(icount >= 200)
		{
			break;		
		}
	}

	//if(icount > 0)
	{
		SendBuff[0]=0xC2;	// packet header
		SendBuff[1]=SET_NUMBERH(datasize);
		SendBuff[2]=SET_NUMBERL(datasize);
		SendBuff[3]=0xFA;
		SendBuff[4]=0x08;
		SendBuff[5]=icount;
		DataSend(aIndex,SendBuff,datasize);
	}
}
// ----------------------------------------------------------------------------------------------

void PartySearch::CG_RecvInfo(int aIndex, CG_AutoPartyInfo* Recv)
{
	if(!this->ActiveSystem)
	{
		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	lpUser->pt_Active = Recv->ActiveSystem;
	lpUser->pt_MaxLevel = Recv->MaxLevel;
	lpUser->pt_bAllClass = Recv->bAllClass;
	lpUser->pt_bOnlyOneClass = Recv->bOnlyOneClass;
	lpUser->pt_bDarkWizard = Recv->bDarkWizard;
	lpUser->pt_bDarkKnight = Recv->bDarkKnight;
	lpUser->pt_bElf = Recv->bElf;
	lpUser->pt_bMagicGladiator = Recv->bMagicGladiator;
	lpUser->pt_bDarkLord = Recv->bDarkLord;
	lpUser->pt_bSummoner = Recv->bSummoner;
}
// ----------------------------------------------------------------------------------------------

void PartySearch::CG_RecvPartyUser(int aIndex, CG_PartyRecv* Recv)
{
	if(!this->ActiveSystem)
	{
		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	int TargetIndex = Recv->UserIndex;

	if(!gObjIsConnectedEx(TargetIndex))
	{
		return;
	}

	if(aIndex == TargetIndex)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	LPOBJ lpTarget = &gObj[TargetIndex];

	if(!lpTarget->pt_Active)
	{
		return;
	}

	int partynum = lpTarget->PartyNumber;

	BYTE AtributeON = true;

	if(aIndex == TargetIndex)
	{
		AtributeON = false;
	}
	if(lpUser->PartyNumber > 0)
	{
		AtributeON = false;
	}
	if(lpUser->Level > lpTarget->pt_MaxLevel)
	{
		AtributeON = false;
	}
	
	if(/*!lpTarget->pt_bAllClass &&*/ !lpTarget->pt_bOnlyOneClass)
	{
		if(lpUser->Class == CLASS_WIZARD && lpTarget->pt_bDarkWizard == false)
		{
			AtributeON = false;
		}
		if(lpUser->Class == CLASS_KNIGHT && lpTarget->pt_bDarkKnight == false)
		{
			AtributeON = false;
		}
		if(lpUser->Class == CLASS_ELF && lpTarget->pt_bElf == false)
		{
			AtributeON = false;
		}
		if(lpUser->Class == CLASS_MAGUMSA && lpTarget->pt_bMagicGladiator == false)
		{
			AtributeON = false;
		}
		if(lpUser->Class == CLASS_DARKLORD && lpTarget->pt_bDarkLord == false)
		{
			AtributeON = false;
		}
		if(lpUser->Class == CLASS_SUMMONER && lpTarget->pt_bSummoner == false)
		{
			AtributeON = false;
		}
		if(lpUser->Class == CLASS_MONK && lpTarget->pt_bAllClass == false)
		{
			AtributeON = false;
		}
	}

	// -> Gold Party
	if(lpTarget->pt_bOnlyOneClass)
	{
		if(partynum >= 0)
		{
			for(int p = 0; p < MAX_USER_IN_PARTY; p++)
			{
				int number = gParty.m_PartyS[partynum].Number[p];

				if(number >= 0)
				{
					LPOBJ lpPartyObj = &gObj[number];

					if(lpPartyObj->Class == lpUser->Class)
					{
						AtributeON = false;
					}
				}
			}
		}
		else
		{
			if(lpUser->Class == lpTarget->Class)
			{
				AtributeON = false;
			}
		}
	}
				

	if(!AtributeON)
	{
		return;
	}

	int pnumber = -1;

	if ( gObj[TargetIndex].PartyNumber < 0 )
	{
		gObj[TargetIndex].PartyNumber = gParty.Create(TargetIndex, gObj[TargetIndex].DBNumber, gObj[TargetIndex].Level);
	}

	if ( gObj[TargetIndex].PartyNumber >= 0  && gObj[aIndex].PartyNumber == -1)
	{
		if( !gParty.Isleader(gObj[TargetIndex].PartyNumber, TargetIndex, gObj[TargetIndex].DBNumber) )
		{
			return;
		}

		if( gParty.GetCount(gObj[TargetIndex].PartyNumber) >= MAX_USER_IN_PARTY )
		{
			return;
		}

		pnumber = gObj[TargetIndex].PartyNumber;

		int iPartyPos = gParty.Add(gObj[TargetIndex].PartyNumber, aIndex, gObj[aIndex].DBNumber, gObj[aIndex].Level);

		if ( iPartyPos >= 0 )
		{
			gObj[aIndex].PartyNumber = gObj[TargetIndex].PartyNumber;

			gParty.Paint(pnumber);
		}
		else if ( iPartyPos == -1 )
		{
			return;
		}
		else if ( iPartyPos == -2 )
		{
			return;
		}
	}

	if ( pnumber >= 0 )
	{
		CGPartyListAll(pnumber);
		this->Search(aIndex);
	}
}
// ----------------------------------------------------------------------------------------------

void PartySearch::SaveBinary(int aIndex, LPBYTE buf)
{
	if(!this->ActiveSystem)
	{
		return;
	}

	if(!gObjIsConnectedEx(aIndex))
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];
	WORD Level = lpUser->pt_MaxLevel;

	//Active
	buf[0] =  lpUser->pt_Active;
	
	// level
	buf[1] = SET_NUMBERH(Level);
	buf[2] = SET_NUMBERL(Level);

	buf[3] = lpUser->pt_bAllClass;
	buf[4] = lpUser->pt_bOnlyOneClass;

	buf[5] = lpUser->pt_bDarkWizard;
	buf[6] = lpUser->pt_bDarkKnight;
	buf[7] = lpUser->pt_bElf;
	buf[8] = lpUser->pt_bMagicGladiator;
	buf[9] = lpUser->pt_bDarkLord;
	buf[10] = lpUser->pt_bSummoner;

}
// ----------------------------------------------------------------------------------------------

void PartySearch::LoadBinary(int aIndex, LPBYTE buf)
{
	if(!this->ActiveSystem)
	{
		return;
	}
	if ( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("error : %s %d", __FILE__, __LINE__);
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if ( lpObj->Connected < PLAYER_LOGGED )
	{
		return;
	}
	LPOBJ lpUser = &gObj[aIndex];

	lpUser->pt_Active = buf[0];

	lpUser->pt_MaxLevel = MAKE_NUMBERW(buf[1], buf[2]);

	lpUser->pt_bAllClass = buf[3];
	lpUser->pt_bOnlyOneClass = buf[4];

	lpUser->pt_bDarkWizard = buf[5];
	lpUser->pt_bDarkKnight = buf[6];
	lpUser->pt_bElf = buf[7];
	lpUser->pt_bMagicGladiator = buf[8];
	lpUser->pt_bDarkLord = buf[9];
	lpUser->pt_bSummoner = buf[10];


	this->GC_InfoSend(aIndex);
}
// ----------------------------------------------------------------------------------------------

void PartySearch::GC_InfoSend(int aIndex)
{
	if(!this->ActiveSystem)
	{
		return;
	}

	LPOBJ lpUser = &gObj[aIndex];

	CG_AutoPartyInfo pSend;

	pSend.h.set((LPBYTE)&pSend, 0xFB, 0x1B, sizeof(pSend));
	pSend.ActiveSystem = lpUser->pt_Active;
	pSend.MaxLevel = lpUser->pt_MaxLevel;
	pSend.bAllClass = lpUser->pt_bAllClass;
	pSend.bOnlyOneClass = lpUser->pt_bOnlyOneClass;
	pSend.bDarkWizard = lpUser->pt_bDarkWizard;
	pSend.bDarkKnight = lpUser->pt_bDarkKnight;
	pSend.bElf = lpUser->pt_bElf;
	pSend.bMagicGladiator = lpUser->pt_bMagicGladiator;
	pSend.bDarkLord = lpUser->pt_bDarkLord;
	pSend.bSummoner = lpUser->pt_bSummoner;
	DataSend(aIndex, (LPBYTE)&pSend, pSend.h.size);
}
// ----------------------------------------------------------------------------------------------

#endif