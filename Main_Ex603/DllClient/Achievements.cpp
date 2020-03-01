#include "StdAfx.h"
#include "Achievements.h"
#include "Interface.h"
#include "Console.h"
#include "Protocol.h"
#include "ExText.h"

#if(SYSTEM_ACHIEVEMENTS)

CAchievements  g_Achievements;

CAchievements::CAchievements()
{
	this->Init();
}

CAchievements::~CAchievements()
{
}

void CAchievements::Init()
{
	this->bActive = false;
	memset(&this->m_config, 0, sizeof(this->m_config));
	memset(&this->m_user, 0, sizeof(this->m_user));

	this->m_Damage = 0;
	this->m_DamageMax = 0;
	this->m_Defence = 0;
	this->m_DefenceMax = 0;
	this->m_Life = 0;
	this->m_LifeMax = 0;
	this->m_ExellentDamage = 0;
	this->m_ExellentDamageMax = 0;
	this->m_CriticalDamage = 0;
	this->m_CriticalDamageMax = 0;
}

void CAchievements::Load()
{
	this->Init();
}

void CAchievements::LoadImages()
{
	pLoadImage("Custom\\Interface\\Achievements\\arch_bg.tga", eImgID_ACHIEVEMENTS_MAIN, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\HP_BG.jpg", eImgID_ACHIEVEMENTS_PROGRESS_BG, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\SD.jpg", eImgID_ACHIEVEMENTS_PROGRESS_LINE, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission1.tga", eImgID_ACHIEVEMENTS_MISSION_1, GL_LINEAR, GL_CLAMP, 1, 0);

	pLoadImage("Custom\\Interface\\Achievements\\ach_mission1.tga", eImgID_ACHIEVEMENTS_MISSION_1, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission2.tga", eImgID_ACHIEVEMENTS_MISSION_2, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission3.tga", eImgID_ACHIEVEMENTS_MISSION_3, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission4.tga", eImgID_ACHIEVEMENTS_MISSION_4, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission5.tga", eImgID_ACHIEVEMENTS_MISSION_5, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission6.tga", eImgID_ACHIEVEMENTS_MISSION_6, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission7.tga", eImgID_ACHIEVEMENTS_MISSION_7, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission8.tga", eImgID_ACHIEVEMENTS_MISSION_8, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission9.tga", eImgID_ACHIEVEMENTS_MISSION_9, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission10.tga", eImgID_ACHIEVEMENTS_MISSION_10, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission11.tga", eImgID_ACHIEVEMENTS_MISSION_11, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission12.tga", eImgID_ACHIEVEMENTS_MISSION_12, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission13.tga", eImgID_ACHIEVEMENTS_MISSION_13, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission14.tga", eImgID_ACHIEVEMENTS_MISSION_14, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission15.tga", eImgID_ACHIEVEMENTS_MISSION_15, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission16.tga", eImgID_ACHIEVEMENTS_MISSION_16, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission17.tga", eImgID_ACHIEVEMENTS_MISSION_17, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission18.tga", eImgID_ACHIEVEMENTS_MISSION_18, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission19.tga", eImgID_ACHIEVEMENTS_MISSION_19, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission20.tga", eImgID_ACHIEVEMENTS_MISSION_20, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission21.tga", eImgID_ACHIEVEMENTS_MISSION_21, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission22.tga", eImgID_ACHIEVEMENTS_MISSION_22, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission23.tga", eImgID_ACHIEVEMENTS_MISSION_23, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission24.tga", eImgID_ACHIEVEMENTS_MISSION_24, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission25.tga", eImgID_ACHIEVEMENTS_MISSION_25, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission26.tga", eImgID_ACHIEVEMENTS_MISSION_26, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission27.tga", eImgID_ACHIEVEMENTS_MISSION_27, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission28.tga", eImgID_ACHIEVEMENTS_MISSION_28, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission29.tga", eImgID_ACHIEVEMENTS_MISSION_29, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission30.tga", eImgID_ACHIEVEMENTS_MISSION_30, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission31.tga", eImgID_ACHIEVEMENTS_MISSION_31, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission32.tga", eImgID_ACHIEVEMENTS_MISSION_32, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission33.tga", eImgID_ACHIEVEMENTS_MISSION_33, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission34.tga", eImgID_ACHIEVEMENTS_MISSION_34, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission35.tga", eImgID_ACHIEVEMENTS_MISSION_35, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission36.tga", eImgID_ACHIEVEMENTS_MISSION_36, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission37.tga", eImgID_ACHIEVEMENTS_MISSION_37, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission38.tga", eImgID_ACHIEVEMENTS_MISSION_38, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission39.tga", eImgID_ACHIEVEMENTS_MISSION_39, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission40.tga", eImgID_ACHIEVEMENTS_MISSION_40, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission41.tga", eImgID_ACHIEVEMENTS_MISSION_41, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission42.tga", eImgID_ACHIEVEMENTS_MISSION_42, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission43.tga", eImgID_ACHIEVEMENTS_MISSION_43, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission44.tga", eImgID_ACHIEVEMENTS_MISSION_44, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission45.tga", eImgID_ACHIEVEMENTS_MISSION_45, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission46.tga", eImgID_ACHIEVEMENTS_MISSION_46, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission47.tga", eImgID_ACHIEVEMENTS_MISSION_47, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission48.tga", eImgID_ACHIEVEMENTS_MISSION_48, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission49.tga", eImgID_ACHIEVEMENTS_MISSION_49, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_mission50.tga", eImgID_ACHIEVEMENTS_MISSION_50, GL_LINEAR, GL_CLAMP, 1, 0);

	pLoadImage("Custom\\Interface\\Achievements\\ach_add2\\ach_panel.tga", eImgID_ACHIEVEMENTS_PANEL, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_add2\\ach_dmg.tga", eImgID_ACHIEVEMENTS_DAMAGE, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_add2\\ach_def.tga", eImgID_ACHIEVEMENTS_DEFENCE, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_add2\\ach_hp.tga", eImgID_ACHIEVEMENTS_LIFE, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_add2\\ach_exl.tga", eImgID_ACHIEVEMENTS_EXELENT, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Achievements\\ach_add2\\ach_crit.tga", eImgID_ACHIEVEMENTS_CRITICAL, GL_LINEAR, GL_CLAMP, 1, 0);
}

void CAchievements::BindImages()
{
	gInterface.BindObject(eACHIEVEMENTS_MAIN, eImgID_ACHIEVEMENTS_MAIN, 640, 480, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_PROGRESS_BG, eImgID_ACHIEVEMENTS_PROGRESS_BG, 80, 6, -1, -1);

	gInterface.BindObject(eACHIEVEMENTS_MISSION_1, eImgID_ACHIEVEMENTS_MISSION_1, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_2, eImgID_ACHIEVEMENTS_MISSION_2, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_3, eImgID_ACHIEVEMENTS_MISSION_3, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_4, eImgID_ACHIEVEMENTS_MISSION_4, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_5, eImgID_ACHIEVEMENTS_MISSION_5, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_6, eImgID_ACHIEVEMENTS_MISSION_6, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_7, eImgID_ACHIEVEMENTS_MISSION_7, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_8, eImgID_ACHIEVEMENTS_MISSION_8, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_9, eImgID_ACHIEVEMENTS_MISSION_9, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_10, eImgID_ACHIEVEMENTS_MISSION_10, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_11, eImgID_ACHIEVEMENTS_MISSION_11, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_12, eImgID_ACHIEVEMENTS_MISSION_12, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_13, eImgID_ACHIEVEMENTS_MISSION_13, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_14, eImgID_ACHIEVEMENTS_MISSION_14, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_15, eImgID_ACHIEVEMENTS_MISSION_15, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_16, eImgID_ACHIEVEMENTS_MISSION_16, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_17, eImgID_ACHIEVEMENTS_MISSION_17, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_18, eImgID_ACHIEVEMENTS_MISSION_18, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_19, eImgID_ACHIEVEMENTS_MISSION_19, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_20, eImgID_ACHIEVEMENTS_MISSION_20, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_21, eImgID_ACHIEVEMENTS_MISSION_21, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_22, eImgID_ACHIEVEMENTS_MISSION_22, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_23, eImgID_ACHIEVEMENTS_MISSION_23, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_24, eImgID_ACHIEVEMENTS_MISSION_24, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_25, eImgID_ACHIEVEMENTS_MISSION_25, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_26, eImgID_ACHIEVEMENTS_MISSION_26, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_27, eImgID_ACHIEVEMENTS_MISSION_27, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_28, eImgID_ACHIEVEMENTS_MISSION_28, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_29, eImgID_ACHIEVEMENTS_MISSION_29, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_30, eImgID_ACHIEVEMENTS_MISSION_30, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_31, eImgID_ACHIEVEMENTS_MISSION_31, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_32, eImgID_ACHIEVEMENTS_MISSION_32, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_33, eImgID_ACHIEVEMENTS_MISSION_33, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_34, eImgID_ACHIEVEMENTS_MISSION_34, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_35, eImgID_ACHIEVEMENTS_MISSION_35, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_36, eImgID_ACHIEVEMENTS_MISSION_36, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_37, eImgID_ACHIEVEMENTS_MISSION_37, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_38, eImgID_ACHIEVEMENTS_MISSION_38, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_39, eImgID_ACHIEVEMENTS_MISSION_39, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_40, eImgID_ACHIEVEMENTS_MISSION_40, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_41, eImgID_ACHIEVEMENTS_MISSION_41, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_42, eImgID_ACHIEVEMENTS_MISSION_42, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_43, eImgID_ACHIEVEMENTS_MISSION_43, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_44, eImgID_ACHIEVEMENTS_MISSION_44, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_45, eImgID_ACHIEVEMENTS_MISSION_45, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_46, eImgID_ACHIEVEMENTS_MISSION_46, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_47, eImgID_ACHIEVEMENTS_MISSION_47, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_48, eImgID_ACHIEVEMENTS_MISSION_48, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_49, eImgID_ACHIEVEMENTS_MISSION_49, 32, 32, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_MISSION_50, eImgID_ACHIEVEMENTS_MISSION_50, 32, 32, -1, -1);

	gInterface.BindObject(eACHIEVEMENTS_PANEL, eImgID_ACHIEVEMENTS_PANEL, 260, 360, -1, -1);	//310	500
	gInterface.BindObject(eACHIEVEMENTS_DAMAGE, eImgID_ACHIEVEMENTS_DAMAGE, 43, 42, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_DEFENCE, eImgID_ACHIEVEMENTS_DEFENCE, 43, 42, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_LIFE, eImgID_ACHIEVEMENTS_LIFE, 43, 42, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_EXELENT, eImgID_ACHIEVEMENTS_EXELENT, 43, 42, -1, -1);
	gInterface.BindObject(eACHIEVEMENTS_CRITICAL, eImgID_ACHIEVEMENTS_CRITICAL, 43, 42, -1, -1);
}

void CAchievements::Draw()
{
	if(!this->bActive)
	{
		return;
	}
#if(ACH_PANEL)
	this->DrawPanel();
#endif
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievements))
	{
		return;
	}

	pSetCursorFocus = true;

	gInterface.DrawGUI(eACHIEVEMENTS_MAIN, 0, 0);
	gInterface.DrawFormat(eGold, 260, 23, 100, 3, g_ExText.GetText(184));

	ACHIEVEMENTS_DATA * pConfig = &this->m_config;
	ACHIEVEMENTS_DATA * pUser = &this->m_user;

	// -> mission
	float RightX = 22;
	float DownY = 66;
	this->DrawMission(eACHIEVEMENTS_MISSION_1, RightX, DownY, g_ExText.GetText(185), pUser->i1_MonsterKill, pConfig->i1_MonsterKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_23, RightX, DownY, g_ExText.GetText(186), pUser->i23_Monster100LvlKill, pConfig->i23_Monster100LvlKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_36, RightX, DownY, g_ExText.GetText(187), pUser->i36_PheonixKill, pConfig->i36_PheonixKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_27, RightX, DownY, g_ExText.GetText(188), pUser->i27_HellMainKill, pConfig->i27_HellMainKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_44, RightX, DownY, g_ExText.GetText(189), pUser->i44_KillErohim, pConfig->i44_KillErohim);


	// -> 2
	RightX = 22;
	DownY += 35;
	this->DrawMission(eACHIEVEMENTS_MISSION_3, RightX, DownY, g_ExText.GetText(190), pUser->i3_KalimaMonserKill, pConfig->i3_KalimaMonserKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_30, RightX, DownY, g_ExText.GetText(191), pUser->i30_KundunKill, pConfig->i30_KundunKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_6, RightX, DownY, g_ExText.GetText(192), pUser->i6_RedDragonKill, pConfig->i6_RedDragonKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_2, RightX, DownY, g_ExText.GetText(193), pUser->i2_GoldenKill, pConfig->i2_GoldenKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_29, RightX, DownY, g_ExText.GetText(194), pUser->i29_SelupanKill, pConfig->i29_SelupanKill);
	

	// -> 3
	RightX = 22;
	DownY += 35;
	this->DrawMission(eACHIEVEMENTS_MISSION_37, RightX, DownY, g_ExText.GetText(195), pUser->i37_KanturuMonsterKill, pConfig->i37_KanturuMonsterKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_22, RightX, DownY,g_ExText.GetText(196), pUser->i22_KanturuBossKill, pConfig->i22_KanturuBossKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_8, RightX, DownY, g_ExText.GetText(197), pUser->i8_KillGateBC, pConfig->i8_KillGateBC);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_31, RightX, DownY, g_ExText.GetText(198), pUser->i31_KillStatueBC, pConfig->i31_KillStatueBC);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_32, RightX, DownY, g_ExText.GetText(199), pUser->i32_CompleteBC, pConfig->i32_CompleteBC);

	// -> 4
	RightX = 22;
	DownY += 35;
	this->DrawMission(eACHIEVEMENTS_MISSION_9, RightX, DownY, g_ExText.GetText(200), pUser->i9_TakePartInCC, pConfig->i9_TakePartInCC);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_10, RightX, DownY, g_ExText.GetText(201), pUser->i10_WinningTheCC, pConfig->i10_WinningTheCC);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_4, RightX, DownY, g_ExText.GetText(202), pUser->i4_WhiteWizardKill, pConfig->i4_WhiteWizardKill);	
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_7, RightX, DownY, g_ExText.GetText(203), pUser->i7_OrcKill, pConfig->i7_OrcKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_26, RightX, DownY, g_ExText.GetText(204), pUser->i26_CryWolfEventMonster, pConfig->i26_CryWolfEventMonster);
	

	// -> 5
	RightX = 22;
	DownY += 35;
	this->DrawMission(eACHIEVEMENTS_MISSION_16, RightX, DownY, g_ExText.GetText(205), pUser->i16_PickUpZen, pConfig->i16_PickUpZen);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_17, RightX, DownY, g_ExText.GetText(206), pUser->i17_PickUpExellent, pConfig->i17_PickUpExellent);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_18, RightX, DownY, g_ExText.GetText(207), pUser->i18_PickUpAncent, pConfig->i18_PickUpAncent);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_12, RightX, DownY, g_ExText.GetText(208), pUser->i12_PickUpJewels, pConfig->i12_PickUpJewels);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_13, RightX, DownY, g_ExText.GetText(209), pUser->i13_UsedJewels, pConfig->i13_UsedJewels);

	
	// -> 6
	RightX = 22;
	DownY += 35;
	this->DrawMission(eACHIEVEMENTS_MISSION_20, RightX, DownY, g_ExText.GetText(210), pUser->i20_LevelUp, pConfig->i20_LevelUp);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_21, RightX, DownY, g_ExText.GetText(211), pUser->i21_ResetUp, pConfig->i21_ResetUp);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_11, RightX, DownY, g_ExText.GetText(212), pUser->i11_OnlineTime, pConfig->i11_OnlineTime);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_47, RightX, DownY, g_ExText.GetText(213), pUser->i47_PartyNoobLevelUp, pConfig->i47_PartyNoobLevelUp);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_50, RightX, DownY, g_ExText.GetText(214), pUser->i50_OfflineAttackTime, pConfig->i50_OfflineAttackTime);

	// - 7
	RightX = 22;
	DownY += 35;
	this->DrawMission(eACHIEVEMENTS_MISSION_14, RightX, DownY, g_ExText.GetText(215), pUser->i14_SuccessChaosMix, pConfig->i14_SuccessChaosMix);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_15, RightX, DownY, g_ExText.GetText(216), pUser->i15_FailedChaosMix, pConfig->i15_FailedChaosMix);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_48, RightX, DownY, g_ExText.GetText(217), pUser->i48_PickUpRena, pConfig->i48_PickUpRena);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_49, RightX, DownY, g_ExText.GetText(218), pUser->i49_PickUpLuckyCoins, pConfig->i49_PickUpLuckyCoins);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_41, RightX, DownY, g_ExText.GetText(219), pUser->i41_WinSiege, pConfig->i41_WinSiege);

	
	// -> 8
	RightX = 22;
	DownY += 35;
	this->DrawMission(eACHIEVEMENTS_MISSION_42, RightX, DownY, g_ExText.GetText(220), pUser->i42_KillCastleSiegeNPC, pConfig->i42_KillCastleSiegeNPC);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_43, RightX, DownY, g_ExText.GetText(221), pUser->i43_KillPlayerCastleSiege, pConfig->i43_KillPlayerCastleSiege);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_38, RightX, DownY, g_ExText.GetText(222), pUser->i38_MovePlayerFromSwitch, pConfig->i38_MovePlayerFromSwitch);
	RightX += 120;											   
	this->DrawMission(eACHIEVEMENTS_MISSION_39, RightX, DownY, g_ExText.GetText(223), pUser->i39_WithstandSwitch10min, pConfig->i39_WithstandSwitch10min);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_40, RightX, DownY, g_ExText.GetText(224), pUser->i40_MovePlayerFromCrown, pConfig->i40_MovePlayerFromCrown);
	

	// -> 9
	RightX = 22;
	DownY += 35;
	this->DrawMission(eACHIEVEMENTS_MISSION_5, RightX, DownY, g_ExText.GetText(225), pUser->i5_PlayerKill, pConfig->i5_PlayerKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_28, RightX, DownY, g_ExText.GetText(226), pUser->i28_KillInSelf_Defense, pConfig->i28_KillInSelf_Defense);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_25, RightX, DownY, g_ExText.GetText(227), pUser->i25_PhonomanKill, pConfig->i25_PhonomanKill);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_19, RightX, DownY, g_ExText.GetText(228), pUser->i19_DuelWin, pConfig->i19_DuelWin);
	RightX += 120;
	this->DrawMission(eACHIEVEMENTS_MISSION_46, RightX, DownY, g_ExText.GetText(229), pUser->i46_GuildWarWin, pConfig->i46_GuildWarWin);
	
	
	// -> 10
	//RightX = 22;
	//DownY += 35;
	//this->DrawMission(eACHIEVEMENTS_MISSION_45, RightX, DownY, "Buy Donate Shop Item", pUser->i45_BuyDonateShopItem, pConfig->i45_BuyDonateShopItem);
	//RightX += 120;
	//this->DrawMission(eACHIEVEMENTS_MISSION_24, RightX, DownY, "Mootop vote", pUser->i24_MootopVote, pConfig->i24_MootopVote);
	//RightX += 120;
	//this->DrawMission(eACHIEVEMENTS_MISSION_33, RightX, DownY, "Grand Reset up", pUser->i33_GrandResetUp, pConfig->i33_GrandResetUp);
	//RightX += 120;
	//this->DrawMission(eACHIEVEMENTS_MISSION_34, RightX, DownY, "Blue Rabbit Killer", pUser->i34_BlueRabbitKiller, pConfig->i34_BlueRabbitKiller);
	//RightX += 120;
	//this->DrawMission(eACHIEVEMENTS_MISSION_35, RightX, DownY, "Happy Pouches Killer", pUser->i35_HappyPouchesKiller, pConfig->i35_HappyPouchesKiller);
}

void CAchievements::DrawMission(int ObjectID, float X, float Y, char* Name, int iStart, int iNeed)
{
	if(iStart > iNeed)
	{
		iStart = iNeed;
	}

	gInterface.DrawGUI(ObjectID, X, Y);

	float DrawX = X + gInterface.Data[ObjectID].Width + 3;
	float DrawY = Y;

	gInterface.DrawFormat(eWhite, DrawX, DrawY, 100, 1, Name);

	DrawY += 13;
	gInterface.DrawFormat(eYellow, DrawX, DrawY, 100, 1, "%d / %d", iStart, iNeed);

	DrawX = X + gInterface.Data[ObjectID].Width + 2;
	DrawY = Y + 26;
	gInterface.DrawGUI(eACHIEVEMENTS_PROGRESS_BG, DrawX, DrawY);

	DrawX += 2;
	DrawY = Y + 27.5;
	float LineStart = ( iStart * 76.5 ) / iNeed;

	pDrawGUI(eImgID_ACHIEVEMENTS_PROGRESS_LINE, DrawX, DrawY, LineStart, 3.0);
}

void CAchievements::Button(DWORD Event)
{
	if(gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievements))
	{
		if(gInterface.IsWorkZone(630, 0, 640, 10) && Event == WM_LBUTTONUP)
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinAchievements);
		}
	}

	if(gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievementsPower))
	{
		gConsole.Output(cGREEN, "%d %d", pCursorX, pCursorY);
		if(gInterface.IsWorkZone(343, 372, 428, 395) && Event == WM_LBUTTONUP)
		{
			gInterface.CloseWindowEx(ObjWindowsEx::exWinAchievementsPower);
		}
	}
}

void CAchievements::GCConfigData(PMSG_GC_ACH_SETTINGS_DATA* aRecv)
{
	memcpy(&this->m_config, &aRecv->cfg, sizeof(this->m_config));
}

void CAchievements::GCPlayerData(PMSG_GC_ACH_PLAYER_DATA* aRecv)
{
	memcpy(&this->m_user, &aRecv->usr, sizeof(this->m_user));
	this->bActive = true;

	if(!aRecv->bWinOpen)
	{
		return;
	}

	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievements))
	{
		gInterface.OpenWindowEx(ObjWindowsEx::exWinAchievements);
	}
}

void CAchievements::CGWindowOpen()
{
	if(gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievements))
	{
		gInterface.CloseWindowEx(ObjWindowsEx::exWinAchievements);
		return;
	}

	PMSG_CG_ACH_WINOPEN pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, ACH_PROTOCOL1, sizeof(pMsg));
	gProtocol.DataSend((LPBYTE)&pMsg, pMsg.h.size);
}

void CAchievements::DrawPanel()
{
	if(!gInterface.CheckWindowEx(ObjWindowsEx::exWinAchievementsPower))
	{
		return;
	}

	pSetCursorFocus = true;

	float StartX = 190;
	float StartY = 50;
	float LineStart = 0;

	int iStart = 100;
	int iNeed = 100;

	gInterface.DrawGUI(eACHIEVEMENTS_PANEL, StartX, StartY);
	gInterface.DrawFormat(eGold, StartX+80, StartY+19, 100, 3, "Achievements Power");
	
	StartX += 50;
	StartY += 60;
	this->DrawPower(eACHIEVEMENTS_DAMAGE, StartX, StartY, "Damage", this->m_Damage, this->m_DamageMax);

	StartY += 50;
	this->DrawPower(eACHIEVEMENTS_DEFENCE, StartX, StartY, "Defence", this->m_Defence, this->m_DefenceMax);

	StartY += 50;
	this->DrawPower(eACHIEVEMENTS_LIFE, StartX, StartY, "Life", this->m_Life, this->m_LifeMax);

	StartY += 50;
	this->DrawPower(eACHIEVEMENTS_EXELENT, StartX, StartY, "Exellent Damage", this->m_ExellentDamage, this->m_ExellentDamageMax);

	StartY += 50;
	this->DrawPower(eACHIEVEMENTS_CRITICAL, StartX, StartY, "Critical Damage", this->m_CriticalDamage, this->m_CriticalDamageMax);

	StartY += 52;
	gInterface.DrawFormat(eGold, StartX+95, StartY+19, 100, 3, "Ok");
}

void CAchievements::DrawPower(int ObjectID, float X, float Y, char* Name, int iStart, int iNeed)
{
	if(iStart > iNeed)
	{
		iStart = iNeed;
	}

	float StartX = X;
	float StartY = Y;
	float LineStart = ( iStart * 76.5 ) / iNeed;

	gInterface.DrawFormat(eWhite, StartX+60, StartY+5-1, 100, 3, Name);
	gInterface.DrawFormat(eYellow, StartX+60, StartY+20-1, 100, 3, "%d / %d", iStart, iNeed);
	gInterface.DrawGUI(ObjectID, StartX, StartY);
	gInterface.DrawGUI(eACHIEVEMENTS_PROGRESS_BG, StartX+70-1, StartY+35);
	pDrawGUI(eImgID_ACHIEVEMENTS_PROGRESS_LINE, StartX+72-1, StartY+36.5, LineStart, 3.0);
}

void CAchievements::GCCalculatorPower(PMSG_GC_ACH_POWER* aRecv)
{
	this->m_Damage = aRecv->iDamage;
	this->m_DamageMax = aRecv->iDamageMax;
	this->m_Defence = aRecv->iDefence;
	this->m_DefenceMax = aRecv->iDefenceMax;
	this->m_Life = aRecv->iLife;
	this->m_LifeMax = aRecv->iLifeMax;
	this->m_ExellentDamage = aRecv->iExellentDamage;
	this->m_ExellentDamageMax = aRecv->iExellentDamageMax;
	this->m_CriticalDamage = aRecv->iCriticalDamage;
	this->m_CriticalDamageMax = aRecv->iCriticalDamageMax;
}

#endif