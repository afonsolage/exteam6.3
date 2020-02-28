#include "stdafx.h"
#include "RageSystem.h"
#include "Interface.h"
#include "Control.h"
#include "TMemory.h"
//#include "readscript.h"
#include "Console.h"
#include "User.h"
#include "Controller.h"
#include "VisualFix.h"
#include "ExLicense.h"

//#if(exRAGESYSTEM)

RageSystem gRageSystem;


RageSystem::RageSystem()
{
	this->Enable = true;
	this->NextExp = 0;
}

void RageSystem::LoadSkill(int ID, char *cName, int a1, int a2, int NextPoint, bool Percent)
{
	strcpy(this->rSkill[ID].Name,cName);
	this->rSkill[ID].StartDamage = a1;
	this->rSkill[ID].MaxPoint = a2;
	this->rSkill[ID].PointNext = NextPoint;
	this->rSkill[ID].Percent = Percent;
}

void RageSystem::Load()
{
	this->m_ResetRageForWCoin = false;
	this->m_ResetRageForCredit = false;
	this->m_ResetRageWCoin = 0;
	this->m_ResetRageCredit = 0;

	gInterface.BindObject(eRageSystem, 30849, 57, 17, 0, 390);

	gInterface.BindObject(eRageTable,  30850, 640, 480, 20, 20);
	gInterface.BindObject(eRageClose,  308536, 36, 29, 600, 10);
	gInterface.BindObject(eRagePointTable, 308537, 100, 100, 500, 70);
	gInterface.BindObject(eRageIcon1,  30851, 40, 40, 105, 60);
	gInterface.BindObject(eRageIcon2,  30852, 40, 40, 80+25, 120);
	gInterface.BindObject(eRageIcon3,  30853, 40, 40, 80+25, 180);
	gInterface.BindObject(eRageIcon4,  30854, 40, 40, 80+25, 240);
	gInterface.BindObject(eRageIcon5,  30855, 40, 40, 80+25, 300);
	gInterface.BindObject(eRageIcon6,  30856, 40, 40, 80+25, 360);
	gInterface.BindObject(eRageIcon10, 308510, 40, 40, 140+25, 240);
	gInterface.BindObject(eRageIcon11, 308511, 40, 40, 140+25, 300);
	gInterface.BindObject(eRageIcon12, 308512, 40, 40, 140+25, 360);
	gInterface.BindObject(eRageIcon13, 308513, 40, 40, 200+25, 60);
	gInterface.BindObject(eRageIcon14, 308514, 40, 40, 200+25, 120);
	gInterface.BindObject(eRageIcon15, 308515, 40, 40, 200+25, 180);
	gInterface.BindObject(eRageIcon16, 308516, 40, 40, 200+25, 240);
	gInterface.BindObject(eRageIcon17, 308517, 40, 40, 200+25, 300);
	gInterface.BindObject(eRageIcon18, 308518, 40, 40, 200+25, 360);	
	gInterface.BindObject(eRageIcon21, 308521, 40, 40, 260+25, 180);
	gInterface.BindObject(eRageIcon22, 308522, 40, 40, 260+25, 240);
	gInterface.BindObject(eRageIcon23, 308523, 40, 40, 260+25, 300);
	gInterface.BindObject(eRageIcon24, 308524, 40, 40, 260+25, 360);
	gInterface.BindObject(eRageIcon25, 308525, 40, 40, 320+25, 60);
	gInterface.BindObject(eRageIcon26, 308526, 40, 40, 320+25, 120);
	gInterface.BindObject(eRageIcon27, 308527, 40, 40, 320+25, 180);
	gInterface.BindObject(eRageIcon28, 308528, 40, 40, 320+25, 240);
	gInterface.BindObject(eRageIcon29, 308529, 40, 40, 320+25, 300);
	gInterface.BindObject(eRageIcon30, 308530, 40, 40, 320+25, 360);	
	gInterface.BindObject(eRageIcon32, 308532, 40, 40, 380+25, 120);
	gInterface.BindObject(eRageIcon33, 308533, 40, 40, 525, 180);
	gInterface.BindObject(eRageIcon34, 308534, 40, 40, 525, 240);
	gInterface.BindObject(eRageIcon35, 308535, 40, 40, 525, 300);
	gInterface.BindObject(eRageIcon7,  30857, 40, 40, 465, 300);
	gInterface.BindObject(eRageIcon8,  30858, 40, 40, 465, 360);
	gInterface.BindObject(eRageIcon9,  30859, 40, 40, 405, 360);
	gInterface.BindObject(eRageIcon31, 308531, 40, 40, 380+25, 180);
	gInterface.BindObject(eRageIcon19, 308519, 40, 40, 440+25, 180);
	gInterface.BindObject(eRageIcon20, 308520, 40, 40, 440+25, 240);

	gInterface.BindObject(eRageTeleport, 30849, 57, 17, 37, 70);
	gInterface.BindObject(eRagePet, 30849,		57, 17, 37, 100);

	gInterface.BindObject(eRageReset, 30849,	57, 17, 37, 130);

	//------------

	gInterface.BindObject(eRAGERESET_MAIN, 0x7A5A, 222, 140, -1, -1);
	gInterface.BindObject(eRAGERESET_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eRAGERESET_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eRAGERESET_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eRAGERESET_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eRAGERESET_OK, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eRAGERESET_CLOSE, 0x7A5F, 62, 27, -1, -1);

	gInterface.BindObject(eRAGERESET_POINT1, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eRAGERESET_CHECK1, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eRAGERESET_LINE1, 0x7B67, 154, 3, -1, -1);

	gInterface.BindObject(eRAGERESET_POINT2, 0x7B68, 10, 10, -1, -1);
	gInterface.BindObject(eRAGERESET_CHECK2, 0x7B69, 15, 15, -1, -1);
	gInterface.BindObject(eRAGERESET_LINE2, 0x7B67, 154, 3, -1, -1);

	this->Enable = true;
}

void RageSystem::LoadImages()
{
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\RageButton.tga", 30849, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\RageTable.tga", 30850, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon1.tga",  30851, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon2.tga",  30852, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon3.tga",  30853, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon4.tga",  30854, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon5.tga",  30855, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon6.tga",  30856, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon7.tga",  30857, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon8.tga",  30858, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon9.tga",  30859, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon10.tga", 308510, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon11.tga", 308511, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon12.tga", 308512, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon13.tga", 308513, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon14.tga", 308514, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon15.tga", 308515, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon16.tga", 308516, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon17.tga", 308517, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon18.tga", 308518, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon19.tga", 308519, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon20.tga", 308520, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon21.tga", 308521, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon22.tga", 308522, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon23.tga", 308523, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon24.tga", 308524, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon25.tga", 308525, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon26.tga", 308526, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon27.tga", 308527, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon28.tga", 308528, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon29.tga", 308529, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon30.tga", 308530, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon31.tga", 308531, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon32.tga", 308532, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon33.tga", 308533, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon34.tga", 308534, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\icon35.tga", 308535, 0x2601, 0x2900, 1);

	gInterface.LoadImages("Custom\\Interface\\RageSystem\\mini_map_ui_cancel.tga", 308536, 0x2601, 0x2900, 1);
	gInterface.LoadImages("Custom\\Interface\\RageSystem\\newui_Figure_kantru.tga", 308537, 0x2601, 0x2900, 1);
	
	
}

void RageSystem::rDrawInterface()
{

	//if( gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::CashShop)
	//	|| gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::SkillTree)
	//	|| gInterface.CheckWindow(ObjWindow::MoveList)/*|| gObjUser.m_MapNumber == 34 || gObjUser.m_MapNumber == 30*/ )
	//{
	//	return;
	//}
	////pSetCursorFocus = false;
	//gConsole.Output(cGREEN,"pSetCursorFocus: %d",pSetCursorFocus);
	//gInterface.DrawGUI(eRageSystem);

	//DWORD Delay = (GetTickCount() - gInterface.Data[eRageSystem].EventTick);

	//if(gInterface.IsWorkZoneObj(eRageSystem))
	//{
	//	//gConsole.Output(cGREEN,"1");
	//	pSetCursorFocus = true;
	//	if(gController.wMouse == WM_LBUTTONDOWN && Delay > 500)
	//	{
	//		gInterface.Data[eRageSystem].OnClick = true;
	//		gInterface.Data[eRageSystem].EventTick = GetTickCount();

	//		if(gInterface.Data[eRageTable].OnShow)
	//		{
	//			gInterface.Data[eRageTable].OnShow = false;
	//		}
	//		else
	//		{
	//			gInterface.Data[eRageTable].OnShow = true;
	//		}
	//	}
	//	gInterface.Data[eRageSystem].OnClick = false;
	//	gInterface.DrawFormat(eShinyGreen, gInterface.Data[eRageSystem].X+20, gInterface.Data[eRageSystem].Y+3, 50, 1, "Rage");
	//}
	//else
	//{
	//	//gConsole.Output(cGREEN,"2");
	//	pSetCursorFocus = false;
	//	gInterface.DrawFormat(eGold, gInterface.Data[eRageSystem].X+20, gInterface.Data[eRageSystem].Y+3, 50, 1, "Rage");
	//}

	////gConsole.Output(cGREEN,"pSetCursorFocus: %d",pSetCursorFocus);

	//if( gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::CashShop)
	//	|| gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::SkillTree)
	//	|| gInterface.CheckWindow(ObjWindow::MoveList) /*|| gObjUser.m_MapNumber == 34 || gObjUser.m_MapNumber == 30*/ )
	//{
	//	gInterface.Data[eRageTable].OnShow = false;
	//	return;
	//}

	if(!gInterface.Data[eRageTable].OnShow)
	{
		//pSetCursorFocus = false;
		this->ResetRageDraw();
		return;
	}

	pSetCursorFocus = true;

	gInterface.DrawGUI(eRageTable);
	gInterface.DrawGUI(eRageClose);
	gInterface.DrawGUI(eRagePointTable);

	gInterface.DrawFormat(eShinyGreen, gInterface.Data[eRagePointTable].X+15, gInterface.Data[eRagePointTable].Y+11, 100, 1, "Rage Level:");
	gInterface.DrawFormat(eYellow, gInterface.Data[eRagePointTable].X+65, gInterface.Data[eRagePointTable].Y+11, 100, 1, "%d",this->rUser.rLevel);

	gInterface.DrawFormat(eShinyGreen, gInterface.Data[eRagePointTable].X+15, gInterface.Data[eRagePointTable].Y+33, 100, 1, "Rage Point:");
	gInterface.DrawFormat(eYellow, gInterface.Data[eRagePointTable].X+65, gInterface.Data[eRagePointTable].Y+33, 100, 1, "%d",this->rUser.rPoints);

	gInterface.DrawFormat(eShinyGreen, gInterface.Data[eRagePointTable].X+15, gInterface.Data[eRagePointTable].Y+55, 100, 1, "Rage Exp:");
	int ProcExp = 0;
	if(this->NextExp>0)
	{
		ProcExp = (this->rUser.rExperience*100)/this->NextExp;
	}
	gInterface.DrawFormat(eYellow, gInterface.Data[eRagePointTable].X+65, gInterface.Data[eRagePointTable].Y+55, 100, 1, "%d%%",ProcExp);

	if(gInterface.IsWorkZoneObj(eRageClose))
	{
		gInterface.DrawToolTip(gInterface.Data[eRageClose].X + 5, gInterface.Data[eRageClose].Y + 25, "Close");
		if(gController.wMouse == WM_LBUTTONDOWN)
		{
			gInterface.Data[eRageTable].OnShow = false;
			return;
		}
	}
	
	this->DrawButtonActive(eRageTeleport,"Teleport",this->rUser.Teleport,eSkill8);
	this->DrawButtonActive(eRagePet,"Summon Pet",this->rUser.SummonPet,eSkill3);

	if( g_ExLicense.CheckUser(eExUB::Gredy) || g_ExLicense.CheckUser(eExUB::Gredy2) || g_ExLicense.CheckUser(eExUB::GredyLocal) )
	{
		this->DrawButtonActive(eRageReset,"Rage reset",1,eSkillReset);
	}
	
	//------------

	this->DrawDirection(gInterface.Data[eRageIcon1].X+20, gInterface.Data[eRageIcon1].Y+20, 3, 300);
	this->DrawDirection(gInterface.Data[eRageIcon4].X+20, gInterface.Data[eRageIcon4].Y+20, 50, 3);
	this->DrawDirection(gInterface.Data[eRageIcon10].X+20, gInterface.Data[eRageIcon10].Y+20, 3, 100);
	this->DrawDirection(gInterface.Data[eRageIcon12].X+20, gInterface.Data[eRageIcon12].Y+20, 50, 3);

	this->DrawDirection(gInterface.Data[eRageIcon33].X+20, gInterface.Data[eRageIcon33].Y+20, 3, 100);

	this->DrawDirection(gInterface.Data[eRageIcon13].X+20, gInterface.Data[eRageIcon13].Y+20, 3, 250);
	this->DrawDirection(gInterface.Data[eRageIcon16].X+20, gInterface.Data[eRageIcon16].Y+20, 50, 3);
	this->DrawDirection(gInterface.Data[eRageIcon22].X+20, gInterface.Data[eRageIcon22].Y+20, 3, 100);
	this->DrawDirection(gInterface.Data[eRageIcon7].X+20, gInterface.Data[eRageIcon7].Y+20, 50, 3);
	this->DrawDirection(gInterface.Data[eRageIcon7].X+20, gInterface.Data[eRageIcon7].Y+20, 3, 50);

	this->DrawDirection(gInterface.Data[eRageIcon25].X+20, gInterface.Data[eRageIcon25].Y+20, 3, 300);
	this->DrawDirection(gInterface.Data[eRageIcon26].X+20, gInterface.Data[eRageIcon26].Y+20, 50, 3);
	this->DrawDirection(gInterface.Data[eRageIcon30].X+20, gInterface.Data[eRageIcon30].Y+20, 50, 3);
	this->DrawDirection(gInterface.Data[eRageIcon21].X+20, gInterface.Data[eRageIcon21].Y+20, 200, 3);
	this->DrawDirection(gInterface.Data[eRageIcon19].X+20, gInterface.Data[eRageIcon19].Y+20, 3, 50);

	//------------
	int Next = -1;

	this->DrawIcon(eRageIcon1,eSkill1,this->rUser.Damage,-1,Next);	//1
	this->DrawIcon(eRageIcon2,eSkill2,this->rUser.FreePoints,this->rUser.Damage,this->rSkill[eSkill1].PointNext);
	this->DrawIcon(eRageIcon3,eSkill3,this->rUser.SummonPet,this->rUser.FreePoints,this->rSkill[eSkill2].PointNext);
	this->DrawIcon(eRageIcon4,eSkill4,this->rUser.WingsDamagePlus,this->rUser.SummonPet,this->rSkill[eSkill3].PointNext);
	this->DrawIcon(eRageIcon5,eSkill5,this->rUser.FinalMana,this->rUser.WingsDamagePlus,this->rSkill[eSkill4].PointNext);
	this->DrawIcon(eRageIcon6,eSkill6,this->rUser.IgnoreDefence,this->rUser.FinalMana,this->rSkill[eSkill5].PointNext);

	this->DrawIcon(eRageIcon7,eSkill7,this->rUser.ResetLevel,this->rUser.CriticalDamage,this->rSkill[eSkill35].PointNext);
	this->DrawIcon(eRageIcon8,eSkill8,this->rUser.Teleport,this->rUser.ResetLevel,this->rSkill[eSkill7].PointNext);
	this->DrawIcon(eRageIcon9,eSkill9,this->rUser.CriticalDamageRate,this->rUser.IceDamage,this->rSkill[eSkill30].PointNext);
	this->DrawIcon(eRageIcon10,eSkill10,this->rUser.AbsordDamage,this->rUser.WingsDamagePlus,this->rSkill[eSkill4].PointNext);	//1
	this->DrawIcon(eRageIcon11,eSkill11,this->rUser.PetDamageBonus,this->rUser.AbsordDamage,this->rSkill[eSkill10].PointNext);
	this->DrawIcon(eRageIcon12,eSkill12,this->rUser.FinalLife,this->rUser.PetDamageBonus,this->rSkill[eSkill11].PointNext);

	this->DrawIcon(eRageIcon13,eSkill13,this->rUser.Strength,-1,Next);	//2
	this->DrawIcon(eRageIcon14,eSkill14,this->rUser.DefenceRate,this->rUser.Strength,this->rSkill[eSkill13].PointNext);
	this->DrawIcon(eRageIcon15,eSkill15,this->rUser.FireDamage,this->rUser.DefenceRate,this->rSkill[eSkill14].PointNext);
	this->DrawIcon(eRageIcon16,eSkill16,this->rUser.Energy,this->rUser.FireDamage,this->rSkill[eSkill15].PointNext);
	this->DrawIcon(eRageIcon17,eSkill17,this->rUser.Agility,this->rUser.Energy,this->rSkill[eSkill16].PointNext);
	this->DrawIcon(eRageIcon18,eSkill18,this->rUser.DoubleDamage,this->rUser.FinalLife,this->rSkill[eSkill12].PointNext);	//1

	this->DrawIcon(eRageIcon19,eSkill19,this->rUser.FinalSD,this->rUser.DistanceAttack,this->rSkill[eSkill31].PointNext);
	this->DrawIcon(eRageIcon20,eSkill20,this->rUser.FinalDefence,this->rUser.FinalSD,this->rSkill[eSkill19].PointNext);
	this->DrawIcon(eRageIcon21,eSkill21,this->rUser.ZenDrop,this->rUser.Experience,this->rSkill[eSkill27].PointNext);
	this->DrawIcon(eRageIcon22,eSkill22,this->rUser.GuildBonus,this->rUser.Energy,this->rSkill[eSkill16].PointNext);	//2
	this->DrawIcon(eRageIcon23,eSkill23,this->rUser.ReflectDamage,this->rUser.GuildBonus,this->rSkill[eSkill22].PointNext);
	this->DrawIcon(eRageIcon24,eSkill24,this->rUser.ExellentDamageRate,this->rUser.ReflectDamage,this->rSkill[eSkill23].PointNext);

	this->DrawIcon(eRageIcon25,eSkill25,this->rUser.PvPBonusPlus,-1,Next);	//3
	this->DrawIcon(eRageIcon26,eSkill26,this->rUser.MinDefence,this->rUser.PvPBonusPlus,this->rSkill[eSkill25].PointNext);
	this->DrawIcon(eRageIcon27,eSkill27,this->rUser.Experience,this->rUser.MinDefence,this->rSkill[eSkill26].PointNext);
	this->DrawIcon(eRageIcon28,eSkill28,this->rUser.StartSD,this->rUser.Experience,this->rSkill[eSkill27].PointNext);
	this->DrawIcon(eRageIcon29,eSkill29,this->rUser.PartyBonus,this->rUser.StartSD,this->rSkill[eSkill28].PointNext);
	this->DrawIcon(eRageIcon30,eSkill30,this->rUser.IceDamage,this->rUser.PartyBonus,this->rSkill[eSkill29].PointNext);

	this->DrawIcon(eRageIcon31,eSkill31,this->rUser.DistanceAttack,this->rUser.Experience,this->rSkill[eSkill27].PointNext);
	this->DrawIcon(eRageIcon32,eSkill32,this->rUser.AttackRate,this->rUser.MinDefence,this->rSkill[eSkill26].PointNext);	//3
	this->DrawIcon(eRageIcon33,eSkill33,this->rUser.WeaponBonus,-1,Next);	//4
	this->DrawIcon(eRageIcon34,eSkill34,this->rUser.ExellentDamage,this->rUser.WeaponBonus,this->rSkill[eSkill33].PointNext);
	this->DrawIcon(eRageIcon35,eSkill35,this->rUser.CriticalDamage,this->rUser.ExellentDamage,this->rSkill[eSkill34].PointNext);

	//------------

	this->rDrawInfoText(eRageIcon1, eSkill1, this->rUser.Damage);
	this->rDrawInfoText(eRageIcon2, eSkill2, this->rUser.FreePoints);
	this->rDrawInfoText(eRageIcon3, eSkill3, this->rUser.SummonPet);
	this->rDrawInfoText(eRageIcon4, eSkill4, this->rUser.WingsDamagePlus);
	this->rDrawInfoText(eRageIcon5, eSkill5, this->rUser.FinalMana);
	this->rDrawInfoText(eRageIcon6, eSkill6, this->rUser.IgnoreDefence);

	this->rDrawInfoText(eRageIcon7, eSkill7, this->rUser.ResetLevel);
	this->rDrawInfoText(eRageIcon8, eSkill8, this->rUser.Teleport);
	this->rDrawInfoText(eRageIcon9, eSkill9, this->rUser.CriticalDamageRate);
	this->rDrawInfoText(eRageIcon10, eSkill10, this->rUser.AbsordDamage);
	this->rDrawInfoText(eRageIcon11, eSkill11, this->rUser.PetDamageBonus);
	this->rDrawInfoText(eRageIcon12, eSkill12, this->rUser.FinalLife);

	this->rDrawInfoText(eRageIcon13, eSkill13, this->rUser.Strength);
	this->rDrawInfoText(eRageIcon14, eSkill14, this->rUser.DefenceRate);
	this->rDrawInfoText(eRageIcon15, eSkill15, this->rUser.FireDamage);
	this->rDrawInfoText(eRageIcon16, eSkill16, this->rUser.Energy);
	this->rDrawInfoText(eRageIcon17, eSkill17, this->rUser.Agility);
	this->rDrawInfoText(eRageIcon18, eSkill18, this->rUser.DoubleDamage);

	this->rDrawInfoText(eRageIcon19, eSkill19, this->rUser.FinalSD);
	this->rDrawInfoText(eRageIcon20, eSkill20, this->rUser.FinalDefence);
	this->rDrawInfoText(eRageIcon21, eSkill21, this->rUser.ZenDrop);
	this->rDrawInfoText(eRageIcon22, eSkill22, this->rUser.GuildBonus);
	this->rDrawInfoText(eRageIcon23, eSkill23, this->rUser.ReflectDamage);
	this->rDrawInfoText(eRageIcon24, eSkill24, this->rUser.ExellentDamageRate);

	this->rDrawInfoText(eRageIcon25, eSkill25, this->rUser.PvPBonusPlus);
	this->rDrawInfoText(eRageIcon26, eSkill26, this->rUser.MinDefence);
	this->rDrawInfoText(eRageIcon27, eSkill27, this->rUser.Experience);
	this->rDrawInfoText(eRageIcon28, eSkill28, this->rUser.StartSD);
	this->rDrawInfoText(eRageIcon29, eSkill29, this->rUser.PartyBonus);
	this->rDrawInfoText(eRageIcon30, eSkill30, this->rUser.IceDamage);

	this->rDrawInfoText(eRageIcon31, eSkill31, this->rUser.DistanceAttack);
	this->rDrawInfoText(eRageIcon32, eSkill32, this->rUser.AttackRate);

	this->rDrawInfoText(eRageIcon33, eSkill33, this->rUser.WeaponBonus);	//4
	this->rDrawInfoText(eRageIcon34, eSkill34, this->rUser.ExellentDamage);
	this->rDrawInfoText(eRageIcon35, eSkill35, this->rUser.CriticalDamage);
}

void RageSystem::DrawIcon(int ID1, int SkillID, int &ClickCount, int Tree, int NextShow)
{
	DWORD Delay = (GetTickCount() - gInterface.Data[ID1].EventTick);

	int PNext = this->rSkill[SkillID].PointNext;

	if(gInterface.IsWorkZoneObj(ID1))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && 
			Delay > 1000 && 
			this->rUser.rPoints > 0 && 
			this->rSkill[SkillID].MaxPoint > ClickCount && 
			(Tree==-1||Tree>=NextShow))
		{
			gInterface.Data[ID1].OnClick = true;
			gInterface.Data[ID1].EventTick = GetTickCount();

			this->RageSend(SkillID);
		}
		else
		{
			gInterface.Data[ID1].OnClick = false;
		}
			
		gInterface.DrawGUI(ID1, gInterface.Data[ID1].X, gInterface.Data[ID1].Y);

	}
	else
	{
		if(ClickCount>0 || Tree==-1 || Tree >= NextShow)
		{
			gInterface.DrawGUI(ID1, gInterface.Data[ID1].X, gInterface.Data[ID1].Y);
		}
		else
		{
			gInterface.DrawColoredGUI(ID1, (int)Color4f(100, 100, 100, 255));
		}
	}

	gInterface.DrawFormat(eShinyGreen, gInterface.Data[ID1].X+20, gInterface.Data[ID1].Y+40, 40, 3, "%d",ClickCount);
}

void RageSystem::rDrawInfoText(int ID, int SkillID, int Point)
{
	if(gInterface.IsWorkZoneObj(ID))
	{
		int X = gInterface.Data[ID].X;
		int Y = gInterface.Data[ID].Y;

		if(X+45+100 > MAX_WIN_WIDTH)
		{
			pDrawColorButton(NEWUI_BAR_SWITCH02, X-105, Y+7, 100, 50, 0, 0, Color4f(0, 0, 0, 200));
			gInterface.DrawFormat(eSocket, X-105, Y+10, 100, 3, this->rSkill[SkillID].Name);
			gInterface.DrawFormat(eYellow, X-105, Y+20, 100, 3, "Distributed point: %d/%d",Point,this->rSkill[SkillID].MaxPoint);
			if(this->rSkill[SkillID].Percent)
			{
				gInterface.DrawFormat(eAncient, X-105, Y+30, 100, 3, "Increase: %d %%",this->rSkill[SkillID].StartDamage * (Point));
				if(Point >= this->rSkill[SkillID].MaxPoint)
				{
					gInterface.DrawFormat(eAncient, X-105, Y+40, 100, 3, "Next Increase: Finish");
				}
				else
				{
					gInterface.DrawFormat(eAncient, X-105, Y+40, 100, 3, "Next Increase: %d %%",this->rSkill[SkillID].StartDamage * (Point+1));
				}
			}
			else
			{
				gInterface.DrawFormat(eAncient, X-105, Y+30, 100, 3, "Increase: %d",this->rSkill[SkillID].StartDamage * (Point));
				if(Point >= this->rSkill[SkillID].MaxPoint)
				{
					gInterface.DrawFormat(eAncient, X-105, Y+40, 100, 3, "Next Increase: Finish");
				}
				else
				{
					gInterface.DrawFormat(eAncient, X-105, Y+40, 100, 3, "Next Increase: %d",this->rSkill[SkillID].StartDamage * (Point+1));
				}
			}
		}
		else
		{
			pDrawColorButton(NEWUI_BAR_SWITCH02, X+45, Y+7, 100, 50, 0, 0, Color4f(0, 0, 0, 200));
			gInterface.DrawFormat(eSocket, X+45, Y+10, 100, 3, this->rSkill[SkillID].Name);
			gInterface.DrawFormat(eYellow, X+45, Y+20, 100, 3, "Distributed point: %d/%d",Point,this->rSkill[SkillID].MaxPoint);

			if(this->rSkill[SkillID].Percent)
			{
				gInterface.DrawFormat(eAncient, X+45, Y+30, 100, 3, "Increase: %d %%",this->rSkill[SkillID].StartDamage * (Point));
				if(Point >= this->rSkill[SkillID].MaxPoint)
				{
					gInterface.DrawFormat(eAncient, X+45, Y+40, 100, 3, "Next Increase: Finish");
				}
				else
				{
					gInterface.DrawFormat(eAncient, X+45, Y+40, 100, 3, "Next Increase: %d %%",this->rSkill[SkillID].StartDamage * (Point+1));
				}
			}
			else
			{
				gInterface.DrawFormat(eAncient, X+45, Y+30, 100, 3, "Increase: %d",this->rSkill[SkillID].StartDamage * (Point));
				if(Point >= this->rSkill[SkillID].MaxPoint)
				{
					gInterface.DrawFormat(eAncient, X+45, Y+40, 100, 3, "Next Increase: Finish",this->rSkill[SkillID].StartDamage * (Point+1));
				}
				else
				{
					gInterface.DrawFormat(eAncient, X+45, Y+40, 100, 3, "Next Increase: %d",this->rSkill[SkillID].StartDamage * (Point+1));
				}
			}
			
		}
	}
}

void RageSystem::DrawDirection(int X, int Y, int Width, int Height)
{
	gInterface.DrawColorGUI(NEWUI_BAR_SWITCH02, X, Y, Width, Height, eBlack);
}

void RageSystem::FilterSkill(int SkillID)
{
	switch(SkillID)
	{
	case eSkill1:  this->rUser.Damage++;		break;
	case eSkill2:  this->rUser.FreePoints++;		break;
	case eSkill3:  this->rUser.SummonPet++;		break;
	case eSkill4:  this->rUser.WingsDamagePlus++;		break;
	case eSkill5:  this->rUser.FinalMana++;		break;
	case eSkill6:  this->rUser.IgnoreDefence++;		break;
	case eSkill7:  this->rUser.ResetLevel++;		break;
	case eSkill8:  this->rUser.Teleport++;		break;
	case eSkill9:  this->rUser.CriticalDamageRate++;		break;
	case eSkill10: this->rUser.AbsordDamage++;	break;
	case eSkill11: this->rUser.PetDamageBonus++;	break;
	case eSkill12: this->rUser.FinalLife++;	break;
	case eSkill13: this->rUser.Strength++;	break;
	case eSkill14: this->rUser.DefenceRate++;	break;
	case eSkill15: this->rUser.FireDamage++;	break;
	case eSkill16: this->rUser.Energy++;	break;
	case eSkill17: this->rUser.Agility++;	break;
	case eSkill18: this->rUser.DoubleDamage++;	break;
	case eSkill19: this->rUser.FinalSD++;	break;
	case eSkill20: this->rUser.FinalDefence++;	break;
	case eSkill21: this->rUser.ZenDrop++;	break;
	case eSkill22: this->rUser.GuildBonus++;	break;
	case eSkill23: this->rUser.ReflectDamage++;	break;
	case eSkill24: this->rUser.ExellentDamageRate++;	break;
	case eSkill25: this->rUser.PvPBonusPlus++;	break;
	case eSkill26: this->rUser.MinDefence++;	break;
	case eSkill27: this->rUser.Experience++;	break;
	case eSkill28: this->rUser.StartSD++;	break;
	case eSkill29: this->rUser.PartyBonus++;	break;
	case eSkill30: this->rUser.IceDamage++;	break;
	case eSkill31: this->rUser.DistanceAttack++;	break;
	case eSkill32: this->rUser.AttackRate++;	break;
	case eSkill33: this->rUser.WeaponBonus++;	break;
	case eSkill34: this->rUser.ExellentDamage++;	break;
	case eSkill35: this->rUser.CriticalDamage++;	break;
	}

//	lpCharObj pPlayer = pUserObjectStruct;
//
//	if(SkillID == eSkill13)
//	{
//		pPlayer->Strength += this->rSkill[eSkill13].StartDamage;
//	}
//	else if(SkillID == eSkill16)
//	{
//		pPlayer->Energy += this->rSkill[eSkill16].StartDamage;
//	}
//	else if(SkillID == eSkill17)
//	{
//		pPlayer->Dexterity += this->rSkill[eSkill17].StartDamage;
//	}
//	else if(SkillID == eSkill2)
//	{
//		pPlayer->LevelPoint += this->rSkill[eSkill2].StartDamage;
//#ifdef exVISUALFIX
//		gVisualFix.UpPoint += this->rSkill[eSkill2].StartDamage;
//#endif
//	}
}

void RageSystem::RageSend(short Skill)
{
	ClickSend rSend;
	rSend.h.set((LPBYTE)&rSend, 0xFB, 1, sizeof(rSend));
	rSend.Click = 1;
	rSend.SkillID = Skill;
	gProtocol.DataSend((LPBYTE)&rSend, rSend.h.size);
}

void RageSystem::RageRecv(ClickSend *Recv)
{
	this->rUser.rPoints--;
	this->FilterSkill(Recv->SkillID);
}

void RageSystem::RecvStart(sRageUserSend * Recv)
{
	this->rUser.rLevel = Recv->rLevel;
	this->rUser.rPoints = Recv->rPoints;
	this->rUser.rExperience = Recv->rExperience;

	this->rUser.Damage = Recv->Damage;
	this->rUser.FreePoints = Recv->FreePoints;
	this->rUser.SummonPet = Recv->SummonPet;
	this->rUser.WingsDamagePlus = Recv->WingsDamagePlus;
	this->rUser.FinalMana = Recv->FinalMana;
	this->rUser.IgnoreDefence = Recv->IgnoreDefence;
	this->rUser.ResetLevel = Recv->ResetLevel;
	this->rUser.Teleport = Recv->Teleport;
	this->rUser.CriticalDamageRate = Recv->CriticalDamageRate;
	this->rUser.AbsordDamage = Recv->AbsordDamage;
	this->rUser.PetDamageBonus = Recv->PetDamageBonus;
	this->rUser.FinalLife = Recv->FinalLife;
	this->rUser.Strength = Recv->Strength;
	this->rUser.DefenceRate = Recv->DefenceRate;
	this->rUser.FireDamage = Recv->FireDamage;
	this->rUser.Energy = Recv->Energy;
	this->rUser.Agility = Recv->Agility;
	this->rUser.DoubleDamage = Recv->DoubleDamage;
	this->rUser.FinalSD = Recv->FinalSD;
	this->rUser.FinalDefence = Recv->FinalDefence;
	this->rUser.ZenDrop = Recv->ZenDrop;
	this->rUser.GuildBonus = Recv->GuildBonus;
	this->rUser.ReflectDamage = Recv->ReflectDamage;
	this->rUser.ExellentDamageRate = Recv->ExellentDamageRate;
	this->rUser.PvPBonusPlus = Recv->PvPBonusPlus;
	this->rUser.MinDefence = Recv->MinDefence;
	this->rUser.Experience = Recv->Experience;
	this->rUser.StartSD = Recv->StartSD;
	this->rUser.PartyBonus = Recv->PartyBonus;
	this->rUser.IceDamage = Recv->IceDamage;
	this->rUser.DistanceAttack = Recv->DistanceAttack;
	this->rUser.AttackRate = Recv->AttackRate;
	this->rUser.WeaponBonus = Recv->WeaponBonus;
	this->rUser.ExellentDamage = Recv->ExellentDamage;
	this->rUser.CriticalDamage = Recv->CriticalDamage;

	this->NextExp = Recv->NextExp;

	//lpCharObj pPlayer = pUserObjectStruct;
	//pPlayer->Strength += this->rUser.Strength * rSkill[eSkill13].StartDamage;
	//pPlayer->Dexterity += this->rUser.Agility * rSkill[eSkill17].StartDamage;
	//pPlayer->Energy += this->rUser.Energy * rSkill[eSkill16].StartDamage;
}

void RageSystem::RecvExp(RageExpSend * Recv)
{
	this->rUser.rLevel = Recv->Level;
	this->rUser.rPoints = Recv->Point;
	this->rUser.rExperience = Recv->Exp;
	this->NextExp = Recv->NextExp;
}

void RageSystem::DrawButtonActive(int ID, char * Text, int Poin, int SkID)
{
	gInterface.DrawGUI(ID);

	DWORD Delay = (GetTickCount() - gInterface.Data[ID].EventTick);

	if(gInterface.IsWorkZoneObj(ID))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 2000 && Poin > 0)
		{
			gInterface.Data[ID].OnClick = true;
			gInterface.Data[ID].EventTick = GetTickCount();

			this->RageTabSend(SkID);
		}
		else
		{
			gInterface.Data[ID].OnClick = false;
		}

		if(Poin>0)
		{
			gInterface.DrawFormat(eYellow, gInterface.Data[ID].X+5, gInterface.Data[ID].Y+3, 50, 3, Text);
		}
		else
		{
			gInterface.DrawFormat(eWhite, gInterface.Data[ID].X+5, gInterface.Data[ID].Y+3, 50, 3, Text);
		}
		
	}
	else
	{
		gInterface.DrawFormat(eWhite, gInterface.Data[ID].X+5, gInterface.Data[ID].Y+3, 50, 3, Text);
	}		
}

void RageSystem::RageTabSend(short index)
{
	sRageTabSend rSend;
	rSend.h.set((LPBYTE)&rSend, 0xFB, 4, sizeof(rSend));
	rSend.Num = index;
	gProtocol.DataSend((LPBYTE)&rSend, rSend.h.size);

	//if(index == eSkillReset)
	//{
	//	gInterface.CloseWindowEx(exWinPremium);
	//}
}

void RageSystem::RecvConfig(sConfigStruct * Recv)
{
	if(Recv->SkillID > R_MAX_SKILL) return;
	this->LoadSkill(Recv->SkillID,Recv->Name,Recv->Damage,	Recv->MaxPoint,	Recv->PointNext, Recv->Percent);
}

void RageSystem::ResetRageDraw()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinResetRage))
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

	gInterface.DrawGUI(eRAGERESET_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eRAGERESET_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eRAGERESET_FRAME, StartX, StartY + 67.0, 2);
	gInterface.DrawGUI(eRAGERESET_FOOTER, StartX, StartY);
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, "Reset rage system");


	ContentY += 35;
	sprintf(szText, "Reset rage for %d WCoin", this->m_ResetRageWCoin);
	gInterface.DrawCheckLine(this->m_ResetRageForWCoin, eRAGERESET_POINT1, eRAGERESET_CHECK1, eRAGERESET_LINE1, ContentX, ContentY, eWhite, szText);
	

	ContentY += 20;
	sprintf(szText, "Reset rage for %d Credits", this->m_ResetRageCredit);
	gInterface.DrawCheckLine(this->m_ResetRageForCredit, eRAGERESET_POINT2, eRAGERESET_CHECK2, eRAGERESET_LINE2, ContentX, ContentY, eWhite, szText);

	/*
	ContentY += 19;
	int pX = 10;
	gInterface.DrawFormat(eYellow, ContentX + 50 + pX, ContentY + 3, 100, 1, "Reward Stats");
	gInterface.DrawGUI(eADDPOINT_TABLE2, ContentX + 101 + pX, ContentY);
	gInterface.DrawFormat(eAncient, ContentX + 77 + pX, ContentY + 3, 100, 3, "%d", this->ReturnTotalPoint());
	*/

	gInterface.DrawGUI(eRAGERESET_OK, StartX+30, StartY - 5);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5, 50, 3, "Accept");

	if(!this->ResetRageCheckAccept())
	{
		gInterface.Data[eRAGERESET_OK].Attribute = false;
		gInterface.DrawColoredGUI(eRAGERESET_OK, gInterface.Data[eRAGERESET_OK].X, gInterface.Data[eRAGERESET_OK].Y, eGray150);
	}
	else
	{
		gInterface.Data[eRAGERESET_OK].Attribute = true;
		if( gInterface.IsWorkZone(eRAGERESET_OK) )
		{
			Color = eGray100;
			if( gInterface.Data[eRAGERESET_OK].OnClick )
			{
				Color = eGray150;
			}
			gInterface.DrawColoredGUI(eRAGERESET_OK, gInterface.Data[eRAGERESET_OK].X, gInterface.Data[eRAGERESET_OK].Y, Color);
		}
	}
	gInterface.DrawGUI(eRAGERESET_CLOSE, StartX + 70 + 62, StartY - 5 );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5, 50, 3, "Cancel");
	if( gInterface.IsWorkZone(eRAGERESET_CLOSE) )
	{
		Color = eGray100;
		if( gInterface.Data[eRAGERESET_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		gInterface.DrawColoredGUI(eRAGERESET_CLOSE, gInterface.Data[eRAGERESET_CLOSE].X, gInterface.Data[eRAGERESET_CLOSE].Y, Color);
	}
}

bool RageSystem::ResetRageCheckAccept()
{
	bool Result = false;

	if(this->m_ResetRageForWCoin == true)
	{

		if(gObjUser.WCoinC >= this->m_ResetRageWCoin)
		{
			Result = true;
		}
	}
	else if(this->m_ResetRageForCredit == true)
	{
		if(gObjUser.ExCred >= this->m_ResetRageCredit)
		{
			Result = true;
		}
	}

	return Result;
}

void RageSystem::GCRageReset(PMSG_REQ_RESETRAGE* lpMsg)
{
	this->m_ResetRageWCoin = lpMsg->ResetRageWCoin;
	this->m_ResetRageCredit = lpMsg->ResetRageCredit;

	gInterface.OpenWindowEx(ObjWindowsEx::exWinResetRage);
}

void RageSystem::Button(DWORD Event)
{
	if(gInterface.CheckWindowEx(ObjWindowsEx::exWinResetRage))
	{
		if(gInterface.ButtonEx(Event, eRAGERESET_CHECK1, 0))
		{
			if(!this->m_ResetRageForWCoin)
			{
				this->m_ResetRageForWCoin = true;
				this->m_ResetRageForCredit = false;
			}
		}
		if(gInterface.ButtonEx(Event, eRAGERESET_CHECK2, 0))
		{
			if(!this->m_ResetRageForCredit)
			{
				this->m_ResetRageForCredit = true;
				this->m_ResetRageForWCoin = false;			
			}
		}
		if(gInterface.ButtonEx(Event, eRAGERESET_CLOSE, 0))
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinResetRage);
		}
		if(gInterface.ButtonEx(Event, eRAGERESET_OK, true))
		{
			PMSG_ANS_RESETRAGE pMsg;
			pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0x95, sizeof(pMsg));
			pMsg.Result = 0;

			if(this->m_ResetRageForWCoin == true)
			{
				pMsg.Result = 1;
			}
			else if(this->m_ResetRageForCredit == true)
			{
				pMsg.Result = 2;
			}
			
			gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
			gInterface.CloseWindowEx(ObjWindowsEx::exWinResetRage);
			this->m_ResetRageForWCoin = false;
			this->m_ResetRageForCredit = false;
		}
	}
}

//#endif