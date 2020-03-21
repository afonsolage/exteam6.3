#include "stdafx.h"
#include "AddPoints.h"
#include "User.h"
#include "Interface.h"
#include "User.h"
#include "VisualFix.h"
#include "Protocol.h"
#include "Console.h"
#include "TMemory.h"
#include "ExLicense.h"
#include "ExText.h"
#include "StatsAdvance.h"

#if(CUSTOM_ADD_POINTS==TRUE)

CAddPoints g_AddPoints;

CAddPoints::CAddPoints()
{
	this->Init();
}

CAddPoints::~CAddPoints()
{
}

void CAddPoints::Init()
{
	ZeroMemory(this->StrengthText,sizeof(this->StrengthText));
	ZeroMemory(this->DexterityText,sizeof(this->DexterityText));
	ZeroMemory(this->VitalityText,sizeof(this->VitalityText));
	ZeroMemory(this->EnergyText,sizeof(this->EnergyText));
	ZeroMemory(this->CommandText,sizeof(this->CommandText));

	sprintf(this->StrengthText,"0");
	sprintf(this->DexterityText,"0");
	sprintf(this->VitalityText,"0");
	sprintf(this->EnergyText,"0");
	sprintf(this->CommandText,"0");

	this->ActivePage = 0;
	this->ActiveSend = 0;
	this->FreePoint = 0;
	this->Click = false;
	this->PointX = -230;
	this->m_MaxStats = 65535;

	this->m_Loaded = false;
	this->m_Enabled = false;
}

void CAddPoints::Load()
{
	this->Init();
	this->m_Enabled = true;

	this->ResetStatsPriceBonus = 0;
	this->ResetStatsPriceCredit = 0;

	/*
	SetOp((LPVOID)0x0077FBA6,  (LPVOID)this->CharacterInfo, ASM::CALL);
	SetRange((LPVOID)0x0077FD14, 5, ASM::NOP);//0077FD14 -- exp
	SetRange((LPVOID)0x0077FF2B, 5, ASM::NOP);//0077FF2B
	SetRange((LPVOID)0x0077FF91, 5, ASM::NOP);//0077FF91

	SetRange((LPVOID)0x0077FC98, 5, ASM::NOP);//0077FC98
	*/
	this->m_Loaded = true;
	
}

void CAddPoints::ImageLoad()
{
	if (!m_Enabled) return;

	pLoadImage("Custom\\Interface\\newui_cha_textbox03.tga", ex_ADDPOINT_BOX, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\Title.tga", ex_ADDPOINT_FRAME, 0x2601, 0x2900, 1, 0);
}
// ----------------------------------------------------------------------------------------------

void CAddPoints::BindImage()
{
	if (!m_Enabled) return;

	gInterface.BindObject(eADDPOINT_MAIN, 0x7A5A, 222, 225, -1, -1);
	gInterface.BindObject(eADDPOINT_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eADDPOINT_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eADDPOINT_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eADDPOINT_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eADDPOINT_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eADDPOINT_CLOSE, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eADDPOINT_INFOBG, ex_ADDPOINT_BOX, 170, 21, -1, -1);
	gInterface.BindObject(eADDPOINT_INFOBG1, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eADDPOINT_INFOBG2, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eADDPOINT_INFOBG3, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eADDPOINT_INFOBG4, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eADDPOINT_INFOBG5, 0x7AA3, 170, 21, -1, -1);
	gInterface.BindObject(eADDPOINT_POINTUP, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eADDPOINT_RESET, 0x7AA4, 15, 15, -1, -1);
	gInterface.BindObject(eADDPOINT_TABLE, ex_ADDPOINT_FRAME, 50, 16, -1, -1);
	gInterface.BindObject(eADDPOINT_TABLE2, ex_ADDPOINT_FRAME, 50, 16, -1, -1);
	gInterface.BindObject(eADDPOINT_TABLE3, ex_ADDPOINT_FRAME, 50, 16, -1, -1);

	gInterface.BindObject(eADDPOINTRESET_MAIN, 0x7A5A, 222, 140, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eADDPOINTRESET_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_LINE1, 0x7B67, 154, 3, -1, -1);

	gInterface.BindObject(eADDPOINTRESET_POINT2, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eADDPOINTRESET_LINE2, 0x7B67, 154, 3, -1, -1);
}

void CAddPoints::Draw()
{
	if (!m_Enabled) return;

	this->DrawResetStats();

#if(ADD_ADD_POINT==0)
	return;
#endif

	if(!gInterface.CheckWindowEx(exWinAddPoints))
	{
		return;
	}

	pSetCursorFocus = true;

	// ----
	if(this->Click == true)
	{
		if(this->PointX < 0)
		{
			this->PointX += 20;
			if(this->PointX > 0)
			{
				this->PointX = 0;
			}
		}
	}
	else
	{
		if(this->PointX > -230)
		{
			this->PointX -= 20;
			if(this->PointX <= -230)
			{
				this->PointX = -230;
				gInterface.CloseWindowEx(exWinAddPoints);
				return;
			}
		}
	}
	// ----
	float StartX = PointX;
	float StartY = 230;
	int wRep = 6;
	int wH = 200;

	if(gObjUser.GetClass() == CLASS_DARKLORD)
	{
		StartY -= 25;
		wH += 25;
		wRep = 8;
		
	}

	float ContentX = StartX + 30;
	float ContentY = StartY + 30;
	// ----
	gInterface.BindObject(eADDPOINT_MAIN, 0x7A5A, 222, wH, -1, -1);
	gInterface.DrawGUI(eADDPOINT_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eADDPOINT_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eADDPOINT_FRAME, StartX, StartY + 67.0, wRep);
	gInterface.DrawGUI(eADDPOINT_FOOTER, StartX, StartY);

	gInterface.DrawFormat(eGold, StartX + 10, ContentY - 20, 210, 3, g_ExText.GetText(122));
	// -> Content
	gInterface.DrawGUI(eADDPOINT_INFOBG, ContentX, ContentY);
	gInterface.DrawFormat(eAncient, ContentX + 15, ContentY + 5, 50, 3, g_ExText.GetText(123));
	gInterface.DrawFormat(eWhite, ContentX + 95, ContentY + 5, 50, 3, "%d", this->FreePoint);
	
	ContentY += 25;
	gInterface.DrawGUI(eADDPOINT_INFOBG1, ContentX, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15, ContentY + 5, 50, 3, g_ExText.GetText(124));
	gInterface.DrawFormat(eWhite, ContentX + 95, ContentY + 5, 50, 3, this->StrengthText);

	ContentY += 25;
	gInterface.DrawGUI(eADDPOINT_INFOBG2, ContentX, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15, ContentY + 5, 50, 3, g_ExText.GetText(125));
	gInterface.DrawFormat(eWhite, ContentX + 95, ContentY + 5, 50, 3, this->DexterityText);

	ContentY += 25;
	gInterface.DrawGUI(eADDPOINT_INFOBG3, ContentX, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15, ContentY + 5, 50, 3, g_ExText.GetText(126));
	gInterface.DrawFormat(eWhite, ContentX + 95, ContentY + 5, 50, 3, this->VitalityText);

	ContentY += 25;
	gInterface.DrawGUI(eADDPOINT_INFOBG4, ContentX, ContentY);
	gInterface.DrawFormat(eYellow, ContentX + 15, ContentY + 5, 50, 3, g_ExText.GetText(127));
	gInterface.DrawFormat(eWhite, ContentX + 95, ContentY + 5, 50, 3, this->EnergyText);

	if(gObjUser.GetClass() == CLASS_DARKLORD)
	{
		ContentY += 25;
		gInterface.DrawGUI(eADDPOINT_INFOBG5, ContentX, ContentY);
		gInterface.DrawFormat(eYellow, ContentX + 15, ContentY + 5, 50, 3, g_ExText.GetText(128));
		gInterface.DrawFormat(eWhite, ContentX + 95, ContentY + 5, 50, 3, this->CommandText);
	}

	if(this->ActivePage == 0)
	{
		gInterface.DrawColoredGUI(eADDPOINT_INFOBG1, gInterface.Data[eADDPOINT_INFOBG1].X, gInterface.Data[eADDPOINT_INFOBG1].Y, eGray100);
	}
	if(this->ActivePage == 1)
	{
		gInterface.DrawColoredGUI(eADDPOINT_INFOBG2, gInterface.Data[eADDPOINT_INFOBG2].X, gInterface.Data[eADDPOINT_INFOBG2].Y, eGray100);
	}
	if(this->ActivePage == 2)
	{
		gInterface.DrawColoredGUI(eADDPOINT_INFOBG3, gInterface.Data[eADDPOINT_INFOBG3].X, gInterface.Data[eADDPOINT_INFOBG3].Y, eGray100);
	}
	if(this->ActivePage == 3)
	{
		gInterface.DrawColoredGUI(eADDPOINT_INFOBG4, gInterface.Data[eADDPOINT_INFOBG4].X, gInterface.Data[eADDPOINT_INFOBG4].Y, eGray100);
	}
	if(this->ActivePage == 4)
	{
		gInterface.DrawColoredGUI(eADDPOINT_INFOBG5, gInterface.Data[eADDPOINT_INFOBG5].X, gInterface.Data[eADDPOINT_INFOBG5].Y, eGray100);
	}
	// End

	gInterface.DrawGUI(eADDPOINT_OK, StartX+30, StartY);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+10, 50, 3, g_ExText.GetText(120));

	if(!this->ActiveSend)
	{
		gInterface.Data[eADDPOINT_OK].Attribute = false;
		gInterface.DrawColoredGUI(eADDPOINT_OK, gInterface.Data[eADDPOINT_OK].X, gInterface.Data[eADDPOINT_OK].Y, eGray150);
	}
	else
	{
		gInterface.Data[eADDPOINT_OK].Attribute = true;
		if( gInterface.IsWorkZone(eADDPOINT_OK) )
		{
			DWORD Color = eGray100;
			if( gInterface.Data[eADDPOINT_OK].OnClick )
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eADDPOINT_OK, gInterface.Data[eADDPOINT_OK].X, gInterface.Data[eADDPOINT_OK].Y, Color);
		}
	}
	gInterface.DrawGUI(eADDPOINT_CLOSE, StartX + 70 + 62, StartY  );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+10, 50, 3, g_ExText.GetText(129));
	if( gInterface.IsWorkZone(eADDPOINT_CLOSE) )
	{
		DWORD Color = eGray100;
		if( gInterface.Data[eADDPOINT_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eADDPOINT_CLOSE, gInterface.Data[eADDPOINT_CLOSE].X, gInterface.Data[eADDPOINT_CLOSE].Y, Color);
	}
}

void CAddPoints::Button(DWORD Event)
{
	if (!m_Enabled) return;

	if(gInterface.CheckWindow(Character))
	{
#if(ADD_ADD_POINT==1)
		if(gInterface.ButtonEx(Event, eADDPOINT_POINTUP, false))
		{
			if(gInterface.CheckWindowEx(exWinAddPoints))
			{
				this->Close();
			}
			else
			{
				this->Open(1);
			}
		}
#endif

		//if( g_ExLicense.CheckUser(eExUB::Local) ||
		//	g_ExLicense.CheckUser(eExUB::Gredy) ||
		//	g_ExLicense.CheckUser(eExUB::Gredy2) ||
		//	g_ExLicense.CheckUser(eExUB::GredyLocal) ||
		//	g_ExLicense.CheckUser(eExUB::MU2Play) ||
		//	g_ExLicense.CheckUser(eExUB::SILVER1) ||
		//	g_ExLicense.CheckUser(eExUB::SILVER2) ||
		//	g_ExLicense.CheckUser(eExUB::EpicMU) ||
		//	THINNAKORN_MAC == 1 ||
		//	g_ExLicense.CheckUser(eExUB::Escalate) || g_ExLicense.CheckUser(eExUB::eternalmu) ||
		//	g_ExLicense.CheckUser(eExUB::Artem) ||
		//	g_ExLicense.CheckUser(eExUB::Artem2) ||
		//	g_ExLicense.CheckUser(eExUB::RevoMU) ||
		//	g_ExLicense.CheckUser(eExUB::masonX) || g_ExLicense.CheckUser(eExUB::masonX2) ||
		//	g_ExLicense.CheckUser(eExUB::GloryMU) || g_ExLicense.CheckUser(eExUB::ArcMu) ||
		//	g_ExLicense.CheckUser(eExUB::MedoniAndrei) || 
		//	g_ExLicense.CheckUser(eExUB::mu4you) ||
		//	g_ExLicense.CheckUser(eExUB::NSGames))
		{
			if(gInterface.ButtonEx(Event, eADDPOINT_RESET, false))
			{
				if(gInterface.CheckWindowEx(exWinAddResetPoint))
				{
					gInterface.CloseWindowEx(exWinAddResetPoint);
				}
				else
				{
					gInterface.OpenWindowEx(exWinAddResetPoint);
				}
			}
		}
	}
#if(ADD_ADD_POINT==1)
	if(gInterface.CheckWindowEx(exWinAddPoints))
	{
		if(gInterface.ButtonEx(Event, eADDPOINT_OK, true))
		{
			if(this->Result(false))
			{
				return;
			}
		}
		if(gInterface.ButtonEx(Event, eADDPOINT_CLOSE, 0))
		{
			this->Close();
			return;
		}
		if(gInterface.ButtonEx(Event, eADDPOINT_INFOBG1, 0))
		{
			this->ActivePage = 0;
		}
		else if(gInterface.ButtonEx(Event, eADDPOINT_INFOBG2, 0))
		{
			this->ActivePage = 1;
		}
		else if(gInterface.ButtonEx(Event, eADDPOINT_INFOBG3, 0))
		{
			this->ActivePage = 2;
		}
		else if(gInterface.ButtonEx(Event, eADDPOINT_INFOBG4, 0))
		{
			this->ActivePage = 3;
		}
		else if(gInterface.ButtonEx(Event, eADDPOINT_INFOBG5, 0) && gObjUser.GetClass() == CLASS_DARKLORD)
		{
			this->ActivePage = 4;
		}
	}
#endif

	//if( g_ExLicense.CheckUser(eExUB::Local) ||
	//	g_ExLicense.CheckUser(eExUB::Gredy) ||
	//	g_ExLicense.CheckUser(eExUB::Gredy2) ||
	//	g_ExLicense.CheckUser(eExUB::GredyLocal) ||
	//	g_ExLicense.CheckUser(eExUB::MU2Play) ||
	//	g_ExLicense.CheckUser(eExUB::SILVER1) ||
	//	g_ExLicense.CheckUser(eExUB::SILVER2) ||
	//	g_ExLicense.CheckUser(eExUB::EpicMU) ||
	//	THINNAKORN_MAC == 1 ||
	//	g_ExLicense.CheckUser(eExUB::Escalate) || g_ExLicense.CheckUser(eExUB::eternalmu) ||
	//	g_ExLicense.CheckUser(eExUB::Artem) ||
	//	g_ExLicense.CheckUser(eExUB::Artem2)||
	//	g_ExLicense.CheckUser(eExUB::RevoMU)||
	//	g_ExLicense.CheckUser(eExUB::masonX) || g_ExLicense.CheckUser(eExUB::masonX2) ||
	//	g_ExLicense.CheckUser(eExUB::GloryMU) || g_ExLicense.CheckUser(eExUB::ArcMu) ||
	//	g_ExLicense.CheckUser(eExUB::MedoniAndrei) ||
	//	g_ExLicense.CheckUser(eExUB::mu4you) ||
	//	g_ExLicense.CheckUser(eExUB::NSGames))
	{
		if(gInterface.CheckWindowEx(exWinAddResetPoint))
		{
			if(gInterface.Button(Event, exWinAddResetPoint, eADDPOINTRESET_CHECK1, 0))
			{
				if(	g_ExLicense.CheckUser(eExUB::SILVER1) ||
					g_ExLicense.CheckUser(eExUB::SILVER2) )
				{
					if(gObjUser.Premium)
					{
						if(!this->ResetStatsForBonus)
						{
							this->ResetStatsForBonus = true;
							this->ResetStatsForCredit = false;
						}
					}
				}
				else
				{
					if(!this->ResetStatsForBonus)
					{
						this->ResetStatsForBonus = true;
						this->ResetStatsForCredit = false;
					}
				}
			}
			if(gInterface.Button(Event, exWinAddResetPoint, eADDPOINTRESET_CHECK2, 0))
			{
				if(!this->ResetStatsForCredit)
				{
					this->ResetStatsForCredit = true;
					this->ResetStatsForBonus = false;			
				}
			}
			if(gInterface.ButtonEx(Event, eADDPOINTRESET_CLOSE, 0))
			{
				gInterface.CloseWindowEx(exWinAddResetPoint);
			}
			if(gInterface.ButtonEx(Event, eADDPOINTRESET_OK, true))
			{
				PMSG_ADD_POINTSRESET pMsg;
				pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x26, sizeof(pMsg));

				pMsg.Result = 0;
				if(this->ResetStatsForCredit == true)
				{
					pMsg.Result = 1;
				}
			
				gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
				gInterface.CloseWindowEx(exWinAddResetPoint);
				this->ResetStatsForBonus = false;
				this->ResetStatsForCredit = false;
			}
		}
	}
}

void CAddPoints::Keybord(DWORD Event)
{
	if (!m_Enabled) return;

#if(ADD_ADD_POINT==0)
	return;
#endif
	if(!gInterface.CheckWindowEx(exWinAddPoints))
	{
		return;
	}
	// ----
	if(Event == VK_TAB)
	{
		this->ActivePage++;
		if(gObjUser.GetClass() == CLASS_DARKLORD)
		{
			if(this->ActivePage >= 5)
			{
				this->ActivePage = 0;
			}
		}
		else
		{
			if(this->ActivePage >= 4)
			{
				this->ActivePage = 0;
			}
		}
	}
	// ----
	if(Event == VK_RETURN && this->ActiveSend == true)
	{
		if(this->Result(false))
		{
			return;
		}
	}
	// ----
	if(this->ActivePage == 0)
	{
		int oldpoint = atoi(this->StrengthText);
		gInterface.KeyBoxEvent(Event, this->StrengthText, 5);
		this->CheckMaxStats(this->StrengthText);
		int point = atoi(this->StrengthText);
		if(point > this->FreePoint && point > oldpoint)
		{
			sprintf(this->StrengthText, "%d", (this->FreePoint + oldpoint));
		}
	}
	if(this->ActivePage == 1)
	{
		int oldpoint = atoi(this->DexterityText);
		gInterface.KeyBoxEvent(Event, this->DexterityText, 5);
		this->CheckMaxStats(this->DexterityText);
		int point = atoi(this->DexterityText);
		if(point > this->FreePoint && point > oldpoint)
		{
			sprintf(this->DexterityText, "%d", (this->FreePoint + oldpoint));
		}
	}
	if(this->ActivePage == 2)
	{
		int oldpoint = atoi(this->VitalityText);
		gInterface.KeyBoxEvent(Event, this->VitalityText, 5);
		this->CheckMaxStats(this->VitalityText);
		int point = atoi(this->VitalityText);
		if(point > this->FreePoint && point > oldpoint)
		{
			sprintf(this->VitalityText, "%d", (this->FreePoint + oldpoint));
		}
	}
	if(this->ActivePage == 3)
	{
		int oldpoint = atoi(this->EnergyText);
		gInterface.KeyBoxEvent(Event, this->EnergyText, 5);
		this->CheckMaxStats(this->EnergyText);
		int point = atoi(this->EnergyText);
		if(point > this->FreePoint && point > oldpoint)
		{
			sprintf(this->EnergyText, "%d", (this->FreePoint + oldpoint));
		}
	}
	if(this->ActivePage == 4 && gObjUser.GetClass() == CLASS_DARKLORD)
	{
		int oldpoint = atoi(this->CommandText);
		gInterface.KeyBoxEvent(Event, this->CommandText, 5);
		this->CheckMaxStats(this->CommandText);
		int point = atoi(this->CommandText);
		if(point > this->FreePoint && point > oldpoint)
		{
			sprintf(this->CommandText, "%d", (this->FreePoint + oldpoint));
		}
	}
	// ----
	int Str = atoi(this->StrengthText);
	int Agi = atoi(this->DexterityText);
	int Vit = atoi(this->VitalityText);
	int Ene = atoi(this->EnergyText);
	int Cmd = atoi(this->CommandText);

	int TotalPoint = Str + Agi + Vit + Ene + Cmd;

	if(TotalPoint > gVisualFix.UpPoint || gVisualFix.UpPoint == 0 || TotalPoint == 0)
	{
		this->ActiveSend = false;
	}
	else
	{
		this->ActiveSend = true;
		this->FreePoint = gVisualFix.UpPoint - TotalPoint;
	}
}

void CAddPoints::GCPoints()
{
	PMSG_ADD_POINTS pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x1A, sizeof(pMsg));
	pMsg.Strength = atoi(this->StrengthText);
	pMsg.Dexterity = atoi(this->DexterityText);
	pMsg.Vitality = atoi(this->VitalityText);
	pMsg.Energy = atoi(this->EnergyText);
	pMsg.Leadership = atoi(this->CommandText);
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CAddPoints::Open(int type)
{
	if (!m_Enabled) return;

	this->Init();
	this->Click = true;
	this->FreePoint = gVisualFix.UpPoint;
	if(type > 0)
	{
		gInterface.OpenWindow(Character);
		if(type == 2)
		{
			gInterface.OpenWindow(Inventory);
		}
	}
	gInterface.OpenWindowEx(exWinAddPoints);
}

void CAddPoints::Close()
{
	this->Click = false;
}

bool CAddPoints::Result(bool type)
{
	if(type == true)
	{
		this->FreePoint = gVisualFix.UpPoint;
	}
	else
	{
		int Str = atoi(this->StrengthText);
		int Agi = atoi(this->DexterityText);
		int Vit = atoi(this->VitalityText);
		int Ene = atoi(this->EnergyText);
		int Cmd = atoi(this->CommandText);

		int TotalPoint = Str + Agi + Vit + Ene + Cmd;

		if(TotalPoint > gVisualFix.UpPoint)
		{
			return false;
		}

		this->GCPoints();
		this->FreePoint = gVisualFix.UpPoint - TotalPoint;

		sprintf(this->StrengthText,"0");
		sprintf(this->DexterityText,"0");
		sprintf(this->VitalityText,"0");
		sprintf(this->EnergyText,"0");
		sprintf(this->CommandText,"0");

		this->ActivePage = 0;
		this->ActiveSend = 0;

		if(this->FreePoint == 0)
		{
			this->Close();
		}
	}

	return true;
}

void CAddPoints::CharacterInfo(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
	g_AddPoints.CharX = PosX;
	g_AddPoints.CharY = PosY;

	//#if(DEV_STATS_ADVANCE)
	//g_StatsAdvance.m_CharX = PosX;
	//g_StatsAdvance.m_CharY = PosY;
	//#endif

	/*
	lpCharObj lpPlayer			= pUserObjectStruct;

	int drawUP = 0;
	float plusY = 0;
	// ----
	gInterface.DrawFormat(eYellow, PosX, PosY, 100, 1, "Level: %d", lpPlayer->Level);
	gInterface.DrawFormat(eRed, PosX + 50, PosY, 100, 1, "Reset: %d", gObjUser.Reset);
	gInterface.DrawFormat(eExcellent, PosX + 90, PosY, 100, 1, "Grand Reset: %d", gObjUser.GReset);
	// ----
	plusY = 17; 
	if(gInterface.Data[eADDPOINT_POINTUP].OnClick)
	{
		drawUP = 1;
	}
	gInterface.DrawGUIY(eADDPOINT_POINTUP, PosX, PosY + plusY, drawUP);
	gInterface.DrawFormat(eYellow, PosX + 20, PosY + plusY + 2, 100, 1, "Quick add stats");
	gInterface.DrawGUI(eADDPOINT_TABLE, PosX + 101, PosY + plusY);
	gInterface.DrawFormat(eAncient, PosX + 76, PosY + plusY + 3, 100, 3, "%d", gVisualFix.UpPoint);
	// ----
	plusY = 35; 
	int drawUP2 = 0;
	if(gInterface.Data[eADDPOINT_RESET].OnClick)
	{
		drawUP2 = 1;
	}
	gInterface.DrawGUIY(eADDPOINT_RESET, PosX, PosY + plusY, drawUP2);
	gInterface.DrawFormat(eYellow, PosX + 20, PosY + plusY + 2, 100, 1, "Reset Stats");
	gInterface.DrawGUI(eADDPOINT_TABLE2, PosX + 101, PosY + plusY);
	gInterface.DrawFormat(eAncient, PosX + 76, PosY + plusY + 3, 100, 3, "%d", g_AddPoints.ReturnTotalPoint());
	*/
}

void CAddPoints::CharInfoDraw()
{
	if (!m_Enabled) return;

	if(!gInterface.CheckWindow(Character))
	{
		return;
	}

	//pSetCursorFocus = true;

	//if( !g_ExLicense.CheckUser(eExUB::Local) &&
	//	!g_ExLicense.CheckUser(eExUB::Gredy) &&
	//	!g_ExLicense.CheckUser(eExUB::Gredy2) &&
	//	!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
	//	!g_ExLicense.CheckUser(eExUB::MU2Play) &&
	//	!g_ExLicense.CheckUser(eExUB::SILVER1) &&
	//	!g_ExLicense.CheckUser(eExUB::SILVER2) &&
	//	!g_ExLicense.CheckUser(eExUB::EpicMU) &&
	//	!THINNAKORN_MAC &&
	//	!g_ExLicense.CheckUser(eExUB::Escalate)&&
	//	!g_ExLicense.CheckUser(eExUB::eternalmu) &&
	//	!g_ExLicense.CheckUser(eExUB::Artem) &&
	//	!g_ExLicense.CheckUser(eExUB::Artem2) &&
	//	!g_ExLicense.CheckUser(eExUB::RevoMU) &&
	//	!g_ExLicense.CheckUser(eExUB::masonX) && 
	//	!g_ExLicense.CheckUser(eExUB::masonX2) &&
	//	!g_ExLicense.CheckUser(eExUB::GloryMU) && 
	//	!g_ExLicense.CheckUser(eExUB::ArcMu) &&
	//	!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
	//	!g_ExLicense.CheckUser(eExUB::mu4you) &&
	//	!g_ExLicense.CheckUser(eExUB::NSGames))
	//{
	//	return;
	//}

	lpCharObj lpPlayer = pUserObjectStruct;

	float PosX = g_AddPoints.CharX;
	float PosY = g_AddPoints.CharY;

	int drawUP = 0;
	float plusY = 0;
	// ----
	gInterface.DrawFormat(eYellow, PosX, PosY, 100, 1, "%s: %d", g_ExText.GetText(51),  lpPlayer->Level);
	gInterface.DrawFormat(eRed, PosX + 50, PosY, 100, 1, "%s: %d", g_ExText.GetText(52), gObjUser.Reset);
	gInterface.DrawFormat(eExcellent, PosX + 90, PosY, 100, 1, "%s: %d", g_ExText.GetText(130), gObjUser.GReset);
	// ----
	plusY = 17; 
#if(ADD_ADD_POINT==1)
	if(gInterface.Data[eADDPOINT_POINTUP].OnClick)
	{
		drawUP = 1;
	}
	gInterface.DrawGUIY(eADDPOINT_POINTUP, PosX, PosY + plusY, drawUP);
	gInterface.DrawFormat(eYellow, PosX + 20, PosY + plusY + 2, 100, 1, g_ExText.GetText(131));
#endif
	gInterface.DrawGUI(eADDPOINT_TABLE, PosX + 101, PosY + plusY);
	gInterface.DrawFormat(eAncient, PosX + 76, PosY + plusY + 3, 100, 3, "%d", gVisualFix.UpPoint);

	// ----
	plusY = 35; 
	int drawUP2 = 0;
	if(gInterface.Data[eADDPOINT_RESET].OnClick)
	{
		drawUP2 = 1;
	}
	gInterface.DrawGUIY(eADDPOINT_RESET, PosX, PosY + plusY, drawUP2);
	gInterface.DrawFormat(eYellow, PosX + 20, PosY + plusY + 2, 100, 1, g_ExText.GetText(132));
	gInterface.DrawGUI(eADDPOINT_TABLE2, PosX + 101, PosY + plusY);
	gInterface.DrawFormat(eAncient, PosX + 76, PosY + plusY + 3, 100, 3, "%d", g_AddPoints.ReturnTotalPoint());

	// ---- EVOMU ----

	if(/*g_ExLicense.CheckUser(eExUB::Local) ||*/
	   g_ExLicense.CheckUser(eExUB::Gredy) ||
	   g_ExLicense.CheckUser(eExUB::Gredy2) ||
	   g_ExLicense.CheckUser(eExUB::GredyLocal))
	{
		lpCharObj lpPlayer = pUserObjectStruct;
		
		int iStrDamage = 0;
		int iVitDamage = 0;
		int iEneDamage = 0;

		if(gObjUser.GetClass() == CLASS_WIZARD)
		{
			iStrDamage = ( lpPlayer->Strength / 100 ) * 1.32;
			iVitDamage = ( lpPlayer->Stamina / 100 ) * 1.32;
			iEneDamage = ( lpPlayer->Energy / 100 ) * 1.32;

			plusY = 95;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "STRDamage: %d", iStrDamage);

			plusY = 215;
			gInterface.DrawFormat(eYellow, PosX - 20, PosY + plusY + 3, 100, 3, "VITDamage: %d", iVitDamage);

			plusY = 255;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "ENEDamage: %d", iEneDamage);
		}
		else if(gObjUser.GetClass() == CLASS_KNIGHT)
		{
			iStrDamage = ( lpPlayer->Strength / 100 ) * 1.32;
			iVitDamage = ( lpPlayer->Stamina / 100 ) * 1.32;
			iEneDamage = ( lpPlayer->Energy / 100 ) * 1.32;

			plusY = 95;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "STRDamage: %d", iStrDamage);

			plusY = 215;
			gInterface.DrawFormat(eYellow, PosX - 20, PosY + plusY + 3, 100, 3, "VITDamage: %d", iVitDamage);

			plusY = 255;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "ENEDamage: %d", iEneDamage);
		}
		else if(gObjUser.GetClass() == CLASS_ELF)
		{
			iStrDamage = ( lpPlayer->Strength / 100 ) * 1.32;
			iVitDamage = ( lpPlayer->Stamina / 100 ) * 1.32;
			iEneDamage = ( lpPlayer->Energy / 100 ) * 1.32;

			plusY = 95;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "STRDamage: %d", iStrDamage);

			plusY = 215;
			gInterface.DrawFormat(eYellow, PosX - 20, PosY + plusY + 3, 100, 3, "VITDamage: %d", iVitDamage);

			plusY = 255;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "ENEDamage: %d", iEneDamage);
		}
		else if(gObjUser.GetClass() == CLASS_MAGUMSA)
		{
			iStrDamage = ( lpPlayer->Strength / 100 ) * 1.32;
			iVitDamage = ( lpPlayer->Stamina / 100 ) * 1.32;
			iEneDamage = ( lpPlayer->Energy / 100 ) * 1.32;

			plusY = 95;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "STRDamage: %d", iStrDamage);

			plusY = 215;
			gInterface.DrawFormat(eYellow, PosX - 20, PosY + plusY + 3, 100, 3, "VITDamage: %d", iVitDamage);

			plusY = 255;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "ENEDamage: %d", iEneDamage);	
		}
		else if(gObjUser.GetClass() == CLASS_DARKLORD)
		{
				iStrDamage = ( lpPlayer->Strength / 100 ) * 1.32;
			iVitDamage = ( lpPlayer->Stamina / 100 ) * 1.32;
			iEneDamage = ( lpPlayer->Energy / 100 ) * 1.32;

			plusY = 95;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "STRDamage: %d", iStrDamage);

			plusY = 215;
			gInterface.DrawFormat(eYellow, PosX - 20, PosY + plusY + 3, 100, 3, "VITDamage: %d", iVitDamage);

			plusY = 255;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "ENEDamage: %d", iEneDamage);		
		}		
		else if(gObjUser.GetClass() == CLASS_SUMMONER)
		{
			iStrDamage = ( lpPlayer->Strength / 100 ) * 1.32;
			iVitDamage = ( lpPlayer->Stamina / 100 ) * 1.32;
			iEneDamage = ( lpPlayer->Energy / 100 ) * 1.32;

			plusY = 95;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "STRDamage: %d", iStrDamage);

			plusY = 215;
			gInterface.DrawFormat(eYellow, PosX - 20, PosY + plusY + 3, 100, 3, "VITDamage: %d", iVitDamage);

			plusY = 255;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "ENEDamage: %d", iEneDamage);			
		}
		else if(gObjUser.GetClass() == CLASS_MONK)
		{
			iStrDamage = ( lpPlayer->Strength / 100 ) * 1.32;
			iVitDamage = ( lpPlayer->Stamina / 100 ) * 1.32;
			iEneDamage = ( lpPlayer->Energy / 100 ) * 1.32;

			plusY = 95;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "STRDamage: %d", iStrDamage);

			plusY = 215;
			gInterface.DrawFormat(eYellow, PosX - 20, PosY + plusY + 3, 100, 3, "VITDamage: %d", iVitDamage);

			plusY = 255;
			gInterface.DrawFormat(eYellow, PosX + 76, PosY + plusY + 3, 100, 3, "ENEDamage: %d", iEneDamage);			
		}
	}
}

void CAddPoints::DrawResetStats()
{
	if (!m_Enabled) return;

	//if( !g_ExLicense.CheckUser(eExUB::Local) &&
	//	!g_ExLicense.CheckUser(eExUB::Gredy) &&
	//	!g_ExLicense.CheckUser(eExUB::Gredy2) &&
	//	!g_ExLicense.CheckUser(eExUB::GredyLocal) &&
	//	!g_ExLicense.CheckUser(eExUB::MU2Play) &&
	//	!g_ExLicense.CheckUser(eExUB::SILVER1) &&
	//	!g_ExLicense.CheckUser(eExUB::SILVER2) &&
	//	!g_ExLicense.CheckUser(eExUB::EpicMU) &&
	//	!THINNAKORN_MAC &&
	//	!g_ExLicense.CheckUser(eExUB::Escalate)&&
	//	!g_ExLicense.CheckUser(eExUB::eternalmu) &&
	//	!g_ExLicense.CheckUser(eExUB::Artem)&&
	//	!g_ExLicense.CheckUser(eExUB::Artem2) &&
	//	!g_ExLicense.CheckUser(eExUB::RevoMU) &&
	//	!g_ExLicense.CheckUser(eExUB::masonX) && !g_ExLicense.CheckUser(eExUB::masonX2) &&
	//	!g_ExLicense.CheckUser(eExUB::GloryMU) && !g_ExLicense.CheckUser(eExUB::ArcMu) && 
	//	!g_ExLicense.CheckUser(eExUB::MedoniAndrei) &&
	//	!g_ExLicense.CheckUser(eExUB::mu4you) &&
	//	!g_ExLicense.CheckUser(eExUB::NSGames))
	//{
	//	return;
	//}

	if(!gInterface.CheckWindowEx(exWinAddResetPoint))
	{
		return;
	}

	pSetCursorFocus = true;

	DWORD Color = eGray100;
	char szText[128];
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ContentX			= StartX;
	float ContentY			= StartY;

	gInterface.DrawGUI(eADDPOINTRESET_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eADDPOINTRESET_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eADDPOINTRESET_FRAME, StartX, StartY + 67.0, 2);
	gInterface.DrawGUI(eADDPOINTRESET_FOOTER, StartX, StartY);
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, g_ExText.GetText(132));

	if( g_ExLicense.CheckUser(eExUB::SILVER1) || 
		g_ExLicense.CheckUser(eExUB::SILVER2) )
	{
		ContentY += 35;
		sprintf(szText, g_ExText.GetText(133));
		gInterface.DrawCheckLine(this->ResetStatsForBonus, eADDPOINTRESET_POINT1, eADDPOINTRESET_CHECK1, eADDPOINTRESET_LINE1, ContentX, ContentY, eWhite, szText);
	}
	else
	{
		ContentY += 35;
		sprintf(szText, g_ExText.GetText(134), this->ResetStatsPriceBonus);
		gInterface.DrawCheckLine(this->ResetStatsForBonus, eADDPOINTRESET_POINT1, eADDPOINTRESET_CHECK1, eADDPOINTRESET_LINE1, ContentX, ContentY, eWhite, szText);
	}
	ContentY += 20;
	sprintf(szText, g_ExText.GetText(135), this->ResetStatsPriceCredit);
	gInterface.DrawCheckLine(this->ResetStatsForCredit, eADDPOINTRESET_POINT2, eADDPOINTRESET_CHECK2, eADDPOINTRESET_LINE2, ContentX, ContentY, eWhite, szText);

	ContentY += 19;
	int pX = 10;
	gInterface.DrawFormat(eYellow, ContentX + 50 + pX, ContentY + 3, 100, 1, g_ExText.GetText(136));
	gInterface.DrawGUI(eADDPOINT_TABLE2, ContentX + 101 + pX, ContentY);
	gInterface.DrawFormat(eAncient, ContentX + 77 + pX, ContentY + 3, 100, 3, "%d", this->ReturnTotalPoint());

	gInterface.DrawGUI(eADDPOINTRESET_OK, StartX+30, StartY - 5);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5, 50, 3, g_ExText.GetText(137));

	if(!this->ResetsTatsCheckAccept())
	{
		gInterface.Data[eADDPOINTRESET_OK].Attribute = false;
		gInterface.DrawColoredGUI(eADDPOINTRESET_OK, gInterface.Data[eADDPOINTRESET_OK].X, gInterface.Data[eADDPOINTRESET_OK].Y, eGray150);
	}
	else
	{
		gInterface.Data[eADDPOINTRESET_OK].Attribute = true;
		if( gInterface.IsWorkZone(eADDPOINTRESET_OK) )
		{
			Color = eGray100;
			if( gInterface.Data[eADDPOINTRESET_OK].OnClick )
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eADDPOINTRESET_OK, gInterface.Data[eADDPOINTRESET_OK].X, gInterface.Data[eADDPOINTRESET_OK].Y, Color);
		}
	}
	gInterface.DrawGUI(eADDPOINTRESET_CLOSE, StartX + 70 + 62, StartY - 5 );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5, 50, 3, g_ExText.GetText(129));
	if( gInterface.IsWorkZone(eADDPOINTRESET_CLOSE) )
	{
		Color = eGray100;
		if( gInterface.Data[eADDPOINTRESET_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eADDPOINTRESET_CLOSE, gInterface.Data[eADDPOINTRESET_CLOSE].X, gInterface.Data[eADDPOINTRESET_CLOSE].Y, Color);
	}
}

int CAddPoints::ReturnTotalPoint()
{
	lpCharObj lpPlayer = pUserObjectStruct;

	int TotalPoint = lpPlayer->Strength + lpPlayer->Dexterity + lpPlayer->Vitality + lpPlayer->Energy + lpPlayer->Leadership + gVisualFix.UpPoint;
	int Class = gObjUser.Class;

	TotalPoint -= gObjUser.DefClass[Class].Strength;
	TotalPoint -= gObjUser.DefClass[Class].Dexterity;
	TotalPoint -= gObjUser.DefClass[Class].Energy;
	TotalPoint -= gObjUser.DefClass[Class].Vitality;
	TotalPoint -= gObjUser.DefClass[Class].Leadership;

	return TotalPoint;
}

void CAddPoints::GCResetPointRecv(GC_RESET_POINT_CFG * aRecv)
{
	//gConsole.Output(cGREEN, "%d %d", aRecv->iResetStatsPriceBonus, aRecv->iResetStatsPriceCredit);
	this->ResetStatsPriceBonus = aRecv->iResetStatsPriceBonus;
	this->ResetStatsPriceCredit = aRecv->iResetStatsPriceCredit;
}

bool CAddPoints::ResetsTatsCheckAccept()
{
	bool Result = false;

	if(this->ResetStatsForBonus == true)
	{
		if(g_ExLicense.CheckUser(eExUB::SILVER1) || g_ExLicense.CheckUser(eExUB::SILVER2))
		{
			if(gObjUser.Premium)
			{
				Result = true;
			}
		}
		else
		{
			if(gObjUser.WCoinC >= this->ResetStatsPriceBonus)
			{
				Result = true;
			}
		}
	}
	else if(this->ResetStatsForCredit == true)
	{
		if(gObjUser.ExCred >= this->ResetStatsPriceCredit)
		{
			Result = true;
		}
	}

	return Result;
}

void CAddPoints::CheckMaxStats(char* TextStats)
{
	int iStats = atoi(TextStats);
	lpCharObj lpPlayer = pUserObjectStruct;

	if(this->ActivePage == 0)
	{
		if(lpPlayer->Strength + iStats > this->m_MaxStats)
		{
			sprintf(TextStats, "%d", (this->m_MaxStats - lpPlayer->Strength));
		}
	}
	if(this->ActivePage == 1)
	{
		if(lpPlayer->Dexterity + iStats > this->m_MaxStats)
		{
			sprintf(TextStats, "%d", (this->m_MaxStats - lpPlayer->Dexterity));
		}
	}
	if(this->ActivePage == 2)
	{
		if(lpPlayer->Vitality + iStats > this->m_MaxStats)
		{
			sprintf(TextStats, "%d", (this->m_MaxStats - lpPlayer->Vitality));
		}
	}	
	if(this->ActivePage == 3)
	{
		if(lpPlayer->Energy + iStats > this->m_MaxStats)
		{
			sprintf(TextStats, "%d", (this->m_MaxStats - lpPlayer->Energy));
		}
	}	
	if(this->ActivePage == 4)
	{
		if(lpPlayer->Leadership + iStats > this->m_MaxStats)
		{
			sprintf(TextStats, "%d", (this->m_MaxStats - lpPlayer->Leadership));
		}
	}
}

void CAddPoints::CheckMaxStatsEx(int &Stats)
{
	lpCharObj lpPlayer = pUserObjectStruct;

	if(this->ActivePage == 0)
	{
		if(lpPlayer->Strength + Stats > this->m_MaxStats)
		{
			Stats = this->m_MaxStats - lpPlayer->Strength;
		}
	}
	if(this->ActivePage == 1)
	{
		if(lpPlayer->Dexterity + Stats > this->m_MaxStats)
		{
			Stats = this->m_MaxStats - lpPlayer->Dexterity;
		}
	}
	if(this->ActivePage == 2)
	{
		if(lpPlayer->Vitality + Stats > this->m_MaxStats)
		{
			Stats = this->m_MaxStats - lpPlayer->Vitality;
		}
	}	
	if(this->ActivePage == 3)
	{
		if(lpPlayer->Energy + Stats > this->m_MaxStats)
		{
			Stats = this->m_MaxStats - lpPlayer->Energy;
		}
	}	
	if(this->ActivePage == 4)
	{
		if(lpPlayer->Leadership + Stats > this->m_MaxStats)
		{
			Stats = this->m_MaxStats - lpPlayer->Leadership;
		}
	}
}

#endif