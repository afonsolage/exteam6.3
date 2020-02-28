#include "stdafx.h"
#include "BufferSystem.h"
#include "Interface.h"
//#include "BuffIcon.h"
#include "Protocol.h"
#include "Console.h"

#if(CUSTOM_NPC_BUFFER==TRUE)

BufferSystem g_BufferSystem;
// ----------------------------------------------------------------------------------------------

void BufferSystem::Init()
{
	this->Buff1_Result = 0;
	this->Buff1_ZenMoney = 0;
	this->Buff1_JewelOfBless = 0;
	this->Buff1_JewelOfSoul = 0;
	this->Buff1_Bonus = 0;

	this->Buff2_Result = 0;
	this->Buff2_ZenMoney = 0;
	this->Buff2_JewelOfBless = 0;
	this->Buff2_JewelOfSoul = 0;
	this->Buff2_Bonus = 0;

	this->Buff3_Result = 0;
	this->Buff3_ZenMoney = 0;
	this->Buff3_JewelOfBless = 0;
	this->Buff3_JewelOfSoul = 0;
	this->Buff3_Bonus = 0;

	this->Buff4_Result = 0;
	this->Buff4_ZenMoney = 0;
	this->Buff4_JewelOfBless = 0;
	this->Buff4_JewelOfSoul = 0;
	this->Buff4_Bonus = 0;

	this->Buff5_Result = 0;
	this->Buff5_ZenMoney = 0;
	this->Buff5_JewelOfBless = 0;
	this->Buff5_JewelOfSoul = 0;
	this->Buff5_Bonus = 0;

	this->Buff6_Result = 0;
	this->Buff6_ZenMoney = 0;
	this->Buff6_JewelOfBless = 0;
	this->Buff6_JewelOfSoul = 0;
	this->Buff6_Bonus = 0;	

	this->LoadBuffCount = 0;
	ZeroMemory(&this->DataBuff, sizeof(this->DataBuff));

	this->BindIcon(AT_INCREASE_ATTACK, "Increase Attack Power", "Attack power increases.");
	this->BindIcon(AT_INCREASE_DEFENSE, "Increase Defense", "Defensibility increases.");
	this->BindIcon(AT_NPC_HELP, "Shadow Phantom effect", "Attack power and Defensibility increases");
	this->BindIcon(AT_ICE, "Ice", "Mobility speed decreases.");
	this->BindIcon(AT_WIZARD_DEFENSE, "Soul Barrier", "Manna absorbs the damage.");
	this->BindIcon(AT_INCREASE_CRITICAL_DMG, "Critical Damage increase", "Critical damage increases.");
	this->BindIcon(AT_INFINITY_ARROW, "Infinity Arrow", "Arrows do not become consumed.");
	this->BindIcon(AT_INCREASE_AG_SPEED, "AG recovery speed increase", "");
	this->BindIcon(AT_SWELL_LIFE, "Swell Life", "Health stat increases to maximum.");
	this->BindIcon(AT_SWELL_MANA, "Swell Mana", "Mana stat increases to maximum.");
	this->BindIcon(AT_POTION_OF_BLESS, "Potion of Blessing", "Attack power +20%% increase");

	this->BindIcon(AT_POTION_OF_SOUL, "Potion of Soul", "AG recovery speed increase +8/Lightning and Ice resistance increase/attack speed increase +20");
	this->BindIcon(12, "Abolish Magic", "");
	this->BindIcon(13, "Gate Open/Close Status", "");
	this->BindIcon(14, "Watchtower", "");
	this->BindIcon(15, "Besiegement Guild1", "");
	this->BindIcon(16, "Besiegement Guild2", "");
	this->BindIcon(17, "Besiegement Guild3", "");
	this->BindIcon(18, "Invisibility", "");
	this->BindIcon(19, "Dark Rod Battle Skill", "");
	this->BindIcon(20, "Crown Registration Status", "");//

	this->BindIcon(21, "Altar of Wolf contract enabled", "");//Altar of Wolf contract enabled
	this->BindIcon(22, "Altar of Wolf contract enabled", "");//Altar of Wolf contract disabled
	this->BindIcon(23, "Altar of Wolf contract enabled", "");//Altar of Wolf contract Status
	this->BindIcon(24, "Altar of Wolf contract enabled", "");//Altar of Wolf contract attempt
	this->BindIcon(25, "Altar of Wolf contract enabled", "");//Altar of Wolf besiegement Status
	this->BindIcon(26, "Altar of Wolf contract enabled", "");//Altar of Wolf hero contract Status
	this->BindIcon(27, "Altar of Wolf contract enabled", "");//Cry Wolf NPC transparency
	this->BindIcon(28, "GM", "");
	this->BindIcon(29, "Seal of Ascension", "EXP gain increase 150%%");
	this->BindIcon(30, "Seal of Wealth", "EXP gain increase 150%%/item gain increase 200%%");//

	this->BindIcon(31, "Seal of Wealth", "EXP gain disabled");//
	this->BindIcon(32, "Temple - Spell of Quickness", "");//Temple - Spell of Quickness
	this->BindIcon(33, "Temple - Spell of Sublimation", "");//Temple - Spell of Sublimation
	this->BindIcon(34, "Spell of Protection", "Damage absorbed at 100%%.");//Spell of Protection
	this->BindIcon(35, "Jack O'Lantern Blessings", "Attack speed increase +10");//Jack O'Lantern Blessings
	this->BindIcon(36, "Jack O'Lantern Wrath", "Attack power increase +25");//Jack O'Lantern Wrath
	this->BindIcon(37, "Jack O'Lantern Cry", "Defensibility increase +100");//Jack O'Lantern Cry
	this->BindIcon(38, "Jack O'Lantern Food", "Maximum Life increase +500");//Jack O'Lantern Food
	this->BindIcon(39, "Jack O'Lantern Drink", "Maximum Mana increase +500");//Jack O'Lantern Drink
	this->BindIcon(40, "Seal of Ascension", "EXP gain increase 150%%");//Seal of Ascension

	this->BindIcon(41, "Seal of Wealth", "EXP gain increase 200%%/Item gain increase 150%%"); //Seal of Wealth	0	0	1	EXP gain increase 200%%/Item gain increase 150%%
	this->BindIcon(42, "Seal of Sustenance", "EXP gain disabled"); //Seal of Sustenance	0	0	1	EXP gain disabled
	this->BindIcon(43, "Seal of Mobility", "Mobility enabled"); //Seal of Mobility	0	0	1	Mobility enabled
	this->BindIcon(44, "Scroll of Quickness", "Attack speed increase +15"); //Scroll of Quickness	0	1	1	Attack speed increase +15
	this->BindIcon(45, "Scroll of Defense", "Defensibility increase +60"); //Scroll of Defense	0	1	1	Defensibility increase +60
	this->BindIcon(46, "Scroll of Wrath", "Attack power increase +30"); //Scroll of Wrath	0	1	1	Attack power increase +30
	this->BindIcon(47, "Scroll of Wizardry", "Wizardry increase +30"); //Scroll of Wizardry	0	1	1	Wizardry increase +30
	this->BindIcon(48, "Scroll of Health", " increase +200"); //Scroll of Health	0	1	1	HP
	this->BindIcon(49, "Scroll of Mana", "Mana increase +300"); //	0	1	1	
	this->BindIcon(50, "Elixir of Strength", "Strength Status +50"); //	0	1	1	

	this->BindIcon(51, "Elixir of Agility", "Agility Status +50"); //	0	1	1	
	this->BindIcon(52, "Elixir of Health", "Health Status +50"); //	0	1	1	
	this->BindIcon(53, "Elixir of Energy", "Energy Status +50"); //	0	1	1	
	this->BindIcon(54, "Elixir of Control", "Control Status +50"); //	0	1	1	
	this->BindIcon(AT_POISON, "Poison", "Poisoned status of condition"); //	1	1	1	
	this->BindIcon(AT_ICE, "Ice", "Mobility speed decreases.");
	this->BindIcon(AT_ICE_ARROW, "Iced Arrow", "Mobility disabled"); //Iced Arrow	1	1	1	Mobility disabled
	this->BindIcon(58, "Defensibility reduction", "Random defensibility decreases at 10%%."); //	1	1	1	
	this->BindIcon(59, "Attack power reduction", ""); //	1	0	1	
	this->BindIcon(60, "Wizardry increase reduction", ""); //	1	0	1	


	this->BindIcon(61, "Stun", "Mobility disabled"); //	1	1	1	
	this->BindIcon(62, "Magic Defense", ""); //	1	0	1	
	this->BindIcon(63, "Monster Magic Attack Resistance", ""); //	1	1	1	
	this->BindIcon(64, "Monster Chemistry Attack Resistance", ""); //	1	1	1	
	this->BindIcon(65, "Spell of Restriction", "Mobility disabled"); //	1	1	1	
	this->BindIcon(66, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(67, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(68, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(69, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(70, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	

	this->BindIcon(AT_DAMAGE_REFLECTION, "Damage Reflection", "Partial damage reflected out."); //	0	1	1	
	this->BindIcon(AT_SLEEP, "Sleep", "Short period of nap"); //	1	1	1	
	this->BindIcon(AT_BLIND, "Blind", "Shortened view and the attack accuracy decreases."); //	1	1	1	
	this->BindIcon(AT_REQUIEM, "Requiem", "Summoner Neil attack"); //	1	1	1	
	this->BindIcon(AT_EXPLOSION, "Explosion", "Summoner Shamut attack"); //	1	1	1	
	this->BindIcon(AT_WEAKNESS, "Weakness", "Attack power reduction"); //	1	1	1	
	this->BindIcon(AT_INNOVATION, "Innovation", "Defensibility reduction"); //	1	1	1	
	this->BindIcon(78, "Cherry Blossom Wine", "Maximum Mana increase +700"); //	0	0	1	
	this->BindIcon(79, "Cherry Blossom Rice Cake", "Maximum Life increase +700"); //	0	0	1	
	this->BindIcon(80, "Cherry Blossom Flower Petal", "Cherry Blossom Flower Petal"); //	0	0	1	x

	this->BindIcon(AT_BERSERKER, "Berserker", "Curse spell, Wizardry/Attack power and Maximum Mana increases/Defense and Maximum Life decreases"); //	0	1	1	
	this->BindIcon(AT_EXPANSION_WIZARDRY, "Expansion of Wizardry", "Minimum Wizardry increases."); //Expansion of Wizardry	0	1	1	
	this->BindIcon(83, "Flame Strike", ""); //	1	1	1	
	this->BindIcon(84, "Gigantic Storm", ""); //	1	1	1	
	this->BindIcon(85, "Lightning Shock", ""); //	1	1	1	
	this->BindIcon(86, "Cold", "Detrimental cold reduces /the mobility speed."); //Cold	1	1	1	
	this->BindIcon(87, "Seal of Healing", "EXP gain increase 150%%/Automatic Life recovery at 5%%"); //	0	0	1	
	this->BindIcon(88, "Seal of Divinity", "Item gain increase at 150%%/Automatic Mana recovery at 5%%"); //	0	0	1	
	this->BindIcon(89, "Scroll of Battle", "Critical damage increase at 20%%"); //	0	1	1	
	this->BindIcon(90, "Scroll of Strength", "Excellent damage increase at 20%%"); //	0	1	1	

	this->BindIcon(91, "Blessing of Christmas", ""); //	0	1	1	Attack power and Defensibility increases
	this->BindIcon(92, "Santa Healing", "Maximum Life increase +500"); //	0	1	1	
	this->BindIcon(93, "Santa Protection", "Maximum Mana increase +500"); //	0	1	1	
	this->BindIcon(94, "Santa Strengthener", "Attack power +30"); //	0	1	1	
	this->BindIcon(95, "Santa Defense", "Defensibility +100"); //	0	1	1	
	this->BindIcon(96, "Santa Quickness", "Attack speed +15"); //	0	1	1	
	this->BindIcon(97, "Santa Fortune", "AG recovery speed increase +10"); //	0	1	1	
	this->BindIcon(98, "Watch", "You may enter and watch a duel in Arena."); //	0	0	1	
	this->BindIcon(99, "Talisman of Guardian", "No penalty for dying."); //	0	0	1	

	// -> ExTeam Buff

	this->BindIcon(112, "Platinum Party", "Exp: +10%% / DropZen: +10%% / Damage: +3%% / Defence: +3%% / Wizard Damage: +3%%" ); 

	this->BindIcon(129, "Ignore Enemy's Defense", "Increases 5%% chance to ignore enemy's defense and inflict damage." ); 

	this->BindIcon(171, "Bronze Vip", "Exp: +15%% / DropZen: +5%% / Damage: +5%% / Defence: +5%% / Wizard Damage: +5%%"); //
	this->BindIcon(172, "Silver Vip", "Exp: +25%% / DropZen: +10%% / Damage: +10%% / Defence: +10%% / Wizard Damage: +10%%"); //
	this->BindIcon(173, "Gold Vip", "Exp: +35%% / DropZen: +15%% / Damage: +15%% / Defence: +15%% / Wizard Damage: +15%%"); //

	this->BindIcon(AT_GUILD_BUFF, "Guild Buff", "No Bonus Effect");

	this->BindIcon(AT_NPC_BUFF_EXP, "Experience Buff", "Experience: + 15%%");
	this->BindIcon(AT_NPC_BUFF_DAMAGE, "Damage Buff", "Damage: +10%%/Wizard Damage: +10%%");
	this->BindIcon(AT_NPC_BUFF_DEFENCE, "Defence Buff", "Defence: +10%%");
	this->BindIcon(AT_NPC_BUFF_EXL_CRIT, "Battle Buff", "Exellent Damage Rate: +5%%/Critical Damage Rate: +5%%");
	this->BindIcon(AT_NPC_BUFF_DROP, "Drop Buff", "Zen Drop: +50%%/Jewel Drop: +150%%");
	this->BindIcon(AT_NPC_BUFF_DOUBLE, "Double Buff", "Double Damage: +5%%");

	this->BindIcon(AT_NOOB_BUFF, "NooB Buff", "Experience: + 30%% / Damage: +15%% / Defence: +15%% / Wizard Damage: +15%% /  Defence: +15%%");
	this->BindIcon(AT_QUEST_BUFF, "Quest Buff", "no Quest");
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::Load()
{
	this->Init();
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::GC_OpenWindow()
{
	gInterface.OpenWindowEx(exWinNPCBuffer);
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::BindImages()
{
	gInterface.BindObject(eNPC_BUFF_MAIN, 0x7A5A, 222, 303, -1, -1);
	gInterface.BindObject(eNPC_BUFF_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(eNPC_BUFF_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(eNPC_BUFF_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(eNPC_BUFF_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(eNPC_BUFF_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(eNPC_BUFF_LINE, 0x7B67, 154, 3, -1, -1);
	gInterface.BindObject(eNPC_BUFF_BT1, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eNPC_BUFF_BT2, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eNPC_BUFF_BT3, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eNPC_BUFF_BT4, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eNPC_BUFF_BT5, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eNPC_BUFF_BT6, 0x7A5F, 62, 27, -1, -1);
	gInterface.BindObject(eNPC_BUFF_BT7, 0x7A5F, 62, 27, -1, -1);
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::Draw()
{
	if(!gInterface.CheckWindowEx(exWinNPCBuffer))
	{
		return;
	}

	pSetCursorFocus = true;

	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100;	//100
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentX          = StartX;
	float ContentY			= StartY;

	// ----
	gInterface.DrawGUI(eNPC_BUFF_MAIN, StartX, StartY + 2);
	gInterface.DrawGUI(eNPC_BUFF_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eNPC_BUFF_FRAME, StartX, StartY + 67.0, 13);
	gInterface.DrawGUI(eNPC_BUFF_FOOTER, StartX, StartY);
	gInterface.DrawGUI(eNPC_BUFF_CLOSE, StartX + MainWidth - gInterface.Data[eNPC_BUFF_CLOSE].Width, ContentY);
	// ----
	if( gInterface.IsWorkZone(eNPC_BUFF_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eNPC_BUFF_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eNPC_BUFF_CLOSE, gInterface.Data[eNPC_BUFF_CLOSE].X, gInterface.Data[eNPC_BUFF_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[eNPC_BUFF_CLOSE].X + 5, gInterface.Data[eNPC_BUFF_CLOSE].Y + 25, "Close");
	}
	// ----

	gInterface.DrawFormat(eGold, ContentX + 10, ContentY + 10, 210, 3, "Buffer");

	// -> Content

	ContentX += 20 + 15;
	ContentY += 30;

	int res = true;

	gInterface.DrawGUI(eNPC_BUFF_LINE, ContentX,  ContentY + 40);
	gInterface.DrawButtonMini(eNPC_BUFF_BT1, ContentX+100, ContentY+5, this->Buff1_Result, "Buy");
	gInterface.DrawPrice(ContentX+10, ContentY, this->Buff1_ZenMoney, NULL, this->Buff1_JewelOfBless, this->Buff1_JewelOfSoul, NULL, this->Buff1_Bonus, NULL);
	this->BuffDraw(176,ContentX, ContentY+5);

	ContentY += 45;

	// ----
	
	gInterface.DrawGUI(eNPC_BUFF_LINE, ContentX,  ContentY + 40);
	gInterface.DrawButtonMini(eNPC_BUFF_BT2, ContentX+100, ContentY+5, this->Buff2_Result, "Buy");
	gInterface.DrawPrice(ContentX+10, ContentY, this->Buff2_ZenMoney, NULL, this->Buff2_JewelOfBless, this->Buff2_JewelOfSoul, NULL, this->Buff2_Bonus, NULL);
	this->BuffDraw(177, ContentX, ContentY+5);
	ContentY += 45;

	// ----

	gInterface.DrawGUI(eNPC_BUFF_LINE, ContentX,  ContentY + 40);
	gInterface.DrawButtonMini(eNPC_BUFF_BT3, ContentX+100, ContentY+5, this->Buff3_Result, "Buy");
	gInterface.DrawPrice(ContentX+10, ContentY, this->Buff3_ZenMoney, NULL, this->Buff3_JewelOfBless, this->Buff3_JewelOfSoul, NULL, this->Buff3_Bonus, NULL);
	this->BuffDraw(178, ContentX, ContentY+5);
	ContentY += 45;

	// ----

	gInterface.DrawGUI(eNPC_BUFF_LINE, ContentX,  ContentY + 40);
	gInterface.DrawButtonMini(eNPC_BUFF_BT4, ContentX+100, ContentY+5, this->Buff4_Result, "Buy");
	gInterface.DrawPrice(ContentX+10, ContentY, this->Buff4_ZenMoney, NULL, this->Buff4_JewelOfBless, this->Buff4_JewelOfSoul, NULL, this->Buff4_Bonus, NULL);
	this->BuffDraw(179, ContentX, ContentY+5);
	ContentY += 45;

	// ----

	gInterface.DrawGUI(eNPC_BUFF_LINE, ContentX,  ContentY + 40);
	gInterface.DrawButtonMini(eNPC_BUFF_BT5, ContentX+100, ContentY+5, this->Buff5_Result, "Buy");
	gInterface.DrawPrice(ContentX+10, ContentY, this->Buff5_ZenMoney, NULL, this->Buff5_JewelOfBless, this->Buff5_JewelOfSoul, NULL, this->Buff5_Bonus, NULL);
	this->BuffDraw(180, ContentX, ContentY+5);
	ContentY += 45;

	// ----
	
	//gInterface.DrawGUI(eNPC_BUFF_LINE, ContentX,  ContentY + 40);
	gInterface.DrawButtonMini(eNPC_BUFF_BT6, ContentX+100, ContentY+5, this->Buff6_Result, "Buy");
	gInterface.DrawPrice(ContentX+10, ContentY, this->Buff6_ZenMoney, NULL, this->Buff6_JewelOfBless, this->Buff6_JewelOfSoul, NULL, this->Buff6_Bonus, NULL);
	this->BuffDraw(181, ContentX, ContentY+5);
	ContentY += 45;

}
// ----------------------------------------------------------------------------------------------

void BufferSystem::BuffDraw(int BuffID, int X, int Y)
{
	//int X = 50;
	//int Y = 50;

	float High	= 28.0;
	float Whith = 20.0;

	int BuffIndex = BuffID;	//BuffID

	int Model = 0;
	int v6 = 0;

	if( BuffIndex > 0 && BuffIndex <= 80)
	{
		Model = 0x7BED;
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
    
	float CritX = (double)(v6 % 10) * Whith / 256;
	float CritY = (double)(v6 / 10) * High / 256;

	float standartWhith = Whith / 256;
	float standartHight = High / 256;

	pDrawGUFULL(Model, X, Y, Whith, High, CritX, CritY, standartWhith, standartHight, TRUE, TRUE, 0.0);

	// ----

	if(gInterface.IsWorkZone(X, Y, X + Whith, Y + High))
	{
		//gBuffIcon.DrawBuffInfoEx(BuffID, X, Y, 86400);
		this->DrawBuffInfoEx(BuffID, X, Y, 86400);
		
	}
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::RecvData(GC_BuffNpcOpen* aRecv)
{
	

	this->Buff1_Result = aRecv->Result1;
	this->Buff1_ZenMoney = aRecv->Zen1;
	this->Buff1_JewelOfBless = aRecv->Bless1;
	this->Buff1_JewelOfSoul = aRecv->Soul1;
	this->Buff1_Bonus = aRecv->Bonus1;

	this->Buff2_Result = aRecv->Result2;
	this->Buff2_ZenMoney = aRecv->Zen2;
	this->Buff2_JewelOfBless = aRecv->Bless2;
	this->Buff2_JewelOfSoul = aRecv->Soul2;
	this->Buff2_Bonus = aRecv->Bonus2;

	this->Buff3_Result = aRecv->Result3;
	this->Buff3_ZenMoney = aRecv->Zen3;
	this->Buff3_JewelOfBless = aRecv->Bless3;
	this->Buff3_JewelOfSoul = aRecv->Soul3;
	this->Buff3_Bonus = aRecv->Bonus3;

	this->Buff4_Result = aRecv->Result4;
	this->Buff4_ZenMoney = aRecv->Zen4;
	this->Buff4_JewelOfBless = aRecv->Bless4;
	this->Buff4_JewelOfSoul = aRecv->Soul4;
	this->Buff4_Bonus = aRecv->Bonus4;

	this->Buff5_Result = aRecv->Result5;
	this->Buff5_ZenMoney = aRecv->Zen5;
	this->Buff5_JewelOfBless = aRecv->Bless5;
	this->Buff5_JewelOfSoul = aRecv->Soul5;
	this->Buff5_Bonus = aRecv->Bonus5;

	this->Buff6_Result = aRecv->Result6;
	this->Buff6_ZenMoney = aRecv->Zen6;
	this->Buff6_JewelOfBless = aRecv->Bless6;
	this->Buff6_JewelOfSoul = aRecv->Soul6;
	this->Buff6_Bonus = aRecv->Bonus6;

	if(!gInterface.CheckWindowEx(exWinNPCBuffer))
	{
		gInterface.OpenWindowEx(exWinNPCBuffer);
	}
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::ButtonEvent(DWORD Event)
{
	if(!gInterface.CheckWindowEx(exWinNPCBuffer))
	{
		return;
	}

	if( gInterface.ButtonEx(Event, eNPC_BUFF_CLOSE, false ) )
	{
		gInterface.CloseWindowEx(exWinNPCBuffer);
		return;
	}

	if( gInterface.ButtonEx(Event, eNPC_BUFF_BT1, true ) )
	{
		this->CG_SendResult(1);
		return;
	}

	if( gInterface.ButtonEx(Event, eNPC_BUFF_BT2, true ) )
	{
		this->CG_SendResult(2);
		return;
	}

	if( gInterface.ButtonEx(Event, eNPC_BUFF_BT3, true ) )
	{
		this->CG_SendResult(3);
		return;
	}

	if( gInterface.ButtonEx(Event, eNPC_BUFF_BT4, true ) )
	{
		this->CG_SendResult(4);
		return;
	}

	if( gInterface.ButtonEx(Event, eNPC_BUFF_BT5, true ) )
	{
		this->CG_SendResult(5);
		return;
	}

	if( gInterface.ButtonEx(Event, eNPC_BUFF_BT6, true ) )
	{
		this->CG_SendResult(6);
		return;
	}
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::CG_SendResult(int id)
{
	CG_BuffNpcResult pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x20, sizeof(pRequest));
	pRequest.Result = (BYTE)id;
	gProtocol.DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

void BufferSystem::BindIcon(BYTE Index, char* Name, char* Text)
{
	this->DataBuff[this->LoadBuffCount].Index = Index;
	strncpy(this->DataBuff[this->LoadBuffCount].Name, Name, 50);
	strncpy(this->DataBuff[this->LoadBuffCount].Text, Text, 200);

	this->LoadBuffCount++;
}
// ------------------------------------------------------------------------------

void BufferSystem::DrawBuffInfoEx(int BuffIndex, float iX, float iY, int iTime)
{
	int posYEx = iY;
	int Wind =  100;

	int DrawBuffIndexData = -1;

	for(int b = 0; b < this->LoadBuffCount; b++)
	{
		if( this->DataBuff[b].Index == BuffIndex)
		{
			DrawBuffIndexData = b;
			break;
		}
	}

	// ----

	int Br = 0;

	int LenBuff = 0;
	int LenName = 0;
	int LenText = 0;
	int LenData = 0;

	char Buff[256] = { 0 };
	char BuffName[256] = { 0 };
	char BuffText[256] = { 0 };
	char BuffDate[256] = { 0 };

	strncpy(BuffName, this->DataBuff[DrawBuffIndexData].Name, 50);
	strncpy(BuffText, this->DataBuff[DrawBuffIndexData].Text, 200);

	strncpy(Buff, this->DataBuff[DrawBuffIndexData].Text, 200);

	char * Line = strtok(Buff, "/");

	while( Line != NULL )
	{
		LenText = strlen(Line);

		if(LenText > LenBuff)
		{
			LenBuff = LenText;
		}
		Br += 1;
		Line = strtok(NULL, "/");
	}
	// --
	if(iTime > 0)
	{
		time_t t = iTime;
		tm* m = gmtime(&t);

		if(m->tm_yday > 0)
		{
			sprintf(BuffDate, "Day: %2d Hour: %2d Minutes: %2d Seconds: %2d",m->tm_yday,m->tm_hour,m->tm_min,m->tm_sec);
		}
		else if(m->tm_hour > 0)
		{
			sprintf(BuffDate, "Hour: %2d Minutes: %2d Seconds: %2d",m->tm_hour,m->tm_min,m->tm_sec);
		}
		else if(m->tm_min > 0)
		{
			sprintf(BuffDate, "Minutes: %2d Seconds: %2d",m->tm_min,m->tm_sec);
		}
		else if(m->tm_sec > 0)
		{
			sprintf(BuffDate, "Seconds: %2d",m->tm_sec);
		}

		LenData = strlen(BuffDate);
	}

	LenName = strlen(BuffName);
	LenText = LenBuff;

	//gConsole.Output(cGREEN, "LenData: %d | LenText: %d", LenData, LenText );

	if(LenText == NULL || LenName > LenText)
	{
		LenText = LenName;
	}
	if( LenData > LenText )
	{
		LenText = LenData;
	}

	Wind = LenText * 4;

	if(pGameResolutionMode > 5)
	{
		Wind = LenText * 3;
	}

	// -----

	if(DrawBuffIndexData >= 0 && DrawBuffIndexData < MAX_BUFF_INDEX)
	{
		int _20 = 20;

		if(iTime < 0)
		{
			_20 = 10;
		}

		pDrawColorButton(0x7880, iX, iY, Wind, _20 + Br * 10, NULL, NULL, Color4f(0, 0, 0, 255));	

		gInterface.DrawFormatEx(eBlue, iX, iY, Wind, 3, BuffName);

		posYEx+=10;

		posYEx = gInterface.DrawFormat_Ex(eWhite, iX, posYEx, Wind, 3, BuffText);
		//posYEx += 10 * Br;
		if(iTime > 0)
		{
			gInterface.DrawFormatEx(eSocket, iX, posYEx, Wind, 3, BuffDate);
		}
	}
}
// ------------------------------------------------------------------------------
#endif