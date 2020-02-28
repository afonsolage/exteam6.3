#include "stdafx.h"
#include "BuffIcon.h"
#include "Interface.h"
#include "Console.h"
#include "Settings.h"
#include "VisualFix.h"
#include "TMemory.h"
#include "ReadScript.h"

// ------------------------------------------------------------------------------
#if(USER_BUFF_ICON_EX==TRUE)

BuffIcon g_BuffIcon;
// ------------------------------------------------------------------------------

BuffIcon::BuffIcon()
{
	this->Init();
	this->hThread = (HANDLE)_beginthreadex(NULL, 0, this->Timer, 0, 0, NULL);
}
// ------------------------------------------------------------------------------

BuffIcon::~BuffIcon()
{
	CloseHandle(this->hThread);
}
// ------------------------------------------------------------------------------
void BuffIcon::Init()
{
	this->LoadBuffCount = 0;
	this->UserBuffCount = 0;
	this->User2BuffCount = 0;
	ZeroMemory(&this->DataBuff, sizeof(DataBuff));
	ZeroMemory(&this->UserBuff, sizeof(UserBuff));
	ZeroMemory(&this->UserExBuff, sizeof(UserExBuff));
}
// ------------------------------------------------------------------------------

void DRBF()
{
	g_BuffIcon.Draw();
}
// ------------------------------------------------------------------------------

void BuffIcon::Load()
{
	this->Init();

	this->Read(".\\Data\\Custom\\Configs\\BuffEffect.txt");

	//SetRange((LPVOID)0x00777C78, 5, ASM::NOP); //Icon Disable , Need Info DIsable

	SetRange((LPVOID)0x00777B40, 5, ASM::NOP);
	SetRange((LPVOID)0x00777B4A, 5, ASM::NOP);

	SetOp((LPVOID)0x00777B4A, DRBF, ASM::CALL);

	return;

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
	this->BindIcon(AT_LORABATTLE_BUFF, "Lorencia Battle Buff", "Experience: +7%% / Damage: +3%% / Wizard Damage: +3%% / Defence: +3%% / Drop Zen: +30%%");
	
	//this->BindIcon(NULL, "", ""); //
}
// ------------------------------------------------------------------------------

bool BuffIcon::Read(char * filename)
{
	//this->Init();

	if ( (SMDFile = fopen(filename, "r")) == NULL )
	{
		return false;
	}

	SMDToken Token;
	int iIndex = 0;
	BYTE btIndex = 0;
	BYTE btViewPortIndex = 0;
	BYTE btItemType = 0;
	BYTE btItemIndex = 0;
	BYTE btType = 0;
	BYTE btNotification = 0;
	BYTE btClearType = 0;
	char szBuffName[20];
	char szBuffInfo[100];

	while ( TRUE )
	{
		Token = GetToken();

		if ( Token == END )
		{
			break;
		}
		
		if ( Token == NUMBER )
		{
			iIndex = (int)TokenNumber;

			while ( TRUE )
			{
				Token = GetToken();

				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				btIndex			= (BYTE)TokenNumber; Token = GetToken();
				btViewPortIndex	= (BYTE)TokenNumber; Token = GetToken();
				btItemType		= (BYTE)TokenNumber; Token = GetToken();
				btItemIndex		= (BYTE)TokenNumber; Token = GetToken();

				memcpy(szBuffName, TokenString, sizeof(szBuffName));

				Token = GetToken();

				btType			= (BYTE)TokenNumber; Token = GetToken();
				btNotification	= (BYTE)TokenNumber; Token = GetToken();
				btClearType		= (BYTE)TokenNumber; Token = GetToken();

				memcpy(szBuffInfo, TokenString, sizeof(szBuffInfo));

				this->BindIcon(btIndex, szBuffName, szBuffInfo);
				//this->Insert(btIndex, btViewPortIndex, btItemType, btItemIndex, szBuffName, btType, btNotification, btClearType, szBuffInfo);
			}
		}
	}

	fclose(SMDFile);

	return true;
}

void BuffIcon::BindIcon(BYTE Index, char* Name, char* Text)
{
	this->DataBuff[this->LoadBuffCount].Index = Index;
	strncpy(this->DataBuff[this->LoadBuffCount].Name, Name, 20);	//50
	strncpy(this->DataBuff[this->LoadBuffCount].Text, Text, 200);

	this->LoadBuffCount++;
}
// ------------------------------------------------------------------------------

void BuffIcon::Draw()
{
	/*if(!g_Settings.BuffIcon)
	{
		return;
	}*/

	float High	= 28.0;
	float Whith = 20.0;

	int DataIndex = 0;
	int InfoIndex = 0;
	float InfoX = 0;
	float InfoY = 0;

	int BuffDraw = 0;

	float drbY = 25;	//15

	int ut = 0;

	//float DisplayX = 0;
	float X = GAME_X_IN_FULL_X(200);

	for(int i = 0; i < MAX_STATE_COUNT; i++)	
	{
		if(this->UserExBuff[i].Index == NULL)
		{
			continue;
		}

		BuffDraw++;
		
		float Y = drbY;	//20

		//X = pWinWidth / 2 + ( (Whith + 2) * BuffDraw) ;
		//X -= (this->UserBuffCount + this->User2BuffCount) * Whith / 2 - 1;
		//X = GAME_X_IN_FULL_X(200);
		X += Whith + 2;// * BuffDraw + 2;
		//DisplayX = X;
		// ----
		int BuffIndex = this->UserExBuff[i].Index;
		// ----
		int Model = 0;
		int v6 = 0;
		// ----
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
		// ----
		float CritX = (double)(v6 % 10) * Whith / 256;
		float CritY = (double)(v6 / 10) * High / 256;

		float standartWhith = Whith / 256;
		float standartHight = High / 256;

		pDrawGUFULL(Model, X, Y, Whith, High, CritX, CritY, standartWhith, standartHight, NULL, NULL, 0.0);
		// ----
		float LineX = FULL_X_IN_GAME_X(X); // 640 * X / pWinWidth;
		float LineY =  FULL_Y_IN_GAME_Y((Y+High));	/* 480 * (Y + High) / pWinHeight;*/
		float LineWind = FULL_X_IN_GAME_X(Whith);// 640 * Whith / pWinWidth ;

		int pBuffHp = 100;
	
		if(this->UserExBuff[i].MaxTime > 0 && this->UserExBuff[i].Time > 0)
		{
			pBuffHp = (this->UserExBuff[i].Time * 100) / this->UserExBuff[i].MaxTime;
		}
		//LineX +=1;
		pDrawColorButton(0x7880, LineX, LineY, LineWind, 1.0, 0, 0,  Color4f(0, 0, 0, 255));	
		pDrawExtraColor(0x7880, LineX, LineY, LineWind * pBuffHp / 100, 0.5, 0, 0, 0, 0, Color4f(0, 255, 0, 255));	//(Wind * pHP) / 100
		// ----
		if(gInterface.IsWorkZone(X, Y, X + Whith, Y + High))
		{
			DataIndex = this->UserExBuff[i].Index;
			InfoIndex = i;
			InfoX = X;
			InfoY = Y;
			ut = 0;
		}
	}

	// ----

	//float X = DisplayX;

	for(int i = 0; i < MAX_STATE_COUNT; i++)	
	{
		if(this->UserBuff[i].Index == NULL)
		{
			continue;
		}

		BuffDraw++;
		
		float Y = drbY;	//20

		//X = pWinWidth / 2 + ( (Whith + 2) * BuffDraw) ;
		//X -= (this->UserBuffCount + this->User2BuffCount) * Whith / 2 - 1;

		//X = GAME_X_IN_FULL_X(200);
		//X += GAME_X_IN_FULL_X(Whith);//Whith; * BuffDraw + 2;

		//X = DisplayX;
		X += Whith + 2;
		// ----
		int BuffIndex = this->UserBuff[i].Index;
		// ----
		int Model = 0;
		int v6 = 0;
		// ----
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
		// ----
		float CritX = (double)(v6 % 10) * Whith / 256;
		float CritY = (double)(v6 / 10) * High / 256;

		float standartWhith = Whith / 256;
		float standartHight = High / 256;

		pDrawGUFULL(Model, X, Y, Whith, High, CritX, CritY, standartWhith, standartHight, NULL, NULL, 0.0);
		// ----
		float LineX = FULL_X_IN_GAME_X(X); // 640 * X / pWinWidth;
		float LineY =  FULL_Y_IN_GAME_Y((Y+High));	/* 480 * (Y + High) / pWinHeight;*/
		float LineWind = FULL_X_IN_GAME_X(Whith);// 640 * Whith / pWinWidth ;

		int pBuffHp = 100;
	
		if(this->UserBuff[i].MaxTime > 0 && this->UserBuff[i].Time > 0)
		{
			pBuffHp = (this->UserBuff[i].Time * 100) / this->UserBuff[i].MaxTime;
		}
		//LineX +=1;
		pDrawColorButton(0x7880, LineX, LineY, LineWind, 1.0, 0, 0,  Color4f(0, 0, 0, 255));	
		pDrawExtraColor(0x7880, LineX, LineY, LineWind * pBuffHp / 100, 0.5, 0, 0, 0, 0, Color4f(0, 255, 0, 255));	//(Wind * pHP) / 100
		// ----
		if(gInterface.IsWorkFullZone(X, Y, X + Whith, Y + High))
		{
			DataIndex = this->UserBuff[i].Index;
			InfoIndex = i;
			InfoX = X;
			InfoY = Y;
			ut = 1;
		}
	}
	// ----
	if(gInterface.IsWorkFullZone(InfoX, InfoY, InfoX + Whith, InfoY + High))
	{
		pSetBlend(true);

		int DrawInfoX = FULL_X_IN_GAME_X(InfoX); // 640 * InfoX / pWinWidth;
		int DrawInfoY = InfoY + 20;
		
		this->DrawBuffInfo(DataIndex, InfoIndex, DrawInfoX, DrawInfoY, ut);
	}
	// ----
	pGLSwitch();
}
// ------------------------------------------------------------------------------

void BuffIcon::DrawBuffInfo(int BuffIndex, int InfoIndex, float iX, float iY, int uType)
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

	if(DrawBuffIndexData == -1)
	{
		return;
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

	if(this->UserExBuff[InfoIndex].Time > 0 && uType == 0)
	{
		time_t t = UserExBuff[InfoIndex].Time;
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

		Br += 1;
	}
	else if(this->UserBuff[InfoIndex].Time > 0 && uType == 1)
	{
		time_t t = UserBuff[InfoIndex].Time;
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

		Br += 1;
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
		int _20 = 10;
		//int _20 = 20;

		//if(this->UserExBuff[InfoIndex].Time < 0)
		//{
		//	_20 = 10;
		//}
		//else if(this->UserBuff[InfoIndex].Time < 0)
		//{
		//	_20 = 10;
		//}

		pDrawColorButton(0x7880, iX, iY, Wind, _20 + Br * 10,
			0, 0, Color4f(0, 0, 0, 200));	

		gInterface.DrawFormatEx(eBlue, iX, iY, Wind, 3, BuffName);

		posYEx+=10;

		posYEx = gInterface.DrawFormat_Ex(eWhite, iX, posYEx, Wind, 3, BuffText);
		//posYEx += 10 * Br;
		if(this->UserExBuff[InfoIndex].Time > 0)
		{
			gInterface.DrawFormatEx(eSocket, iX, posYEx, Wind, 3, BuffDate);
		}
		else if(this->UserBuff[InfoIndex].Time > 0)
		{
			gInterface.DrawFormatEx(eSocket, iX, posYEx, Wind, 3, BuffDate);
		}
	}
}
// ------------------------------------------------------------------------------

unsigned int BuffIcon::Timer(void *Args)
{
	while(true)
	{
		for(int i = 0; i < MAX_STATE_COUNT; i++)
		{
			if(g_BuffIcon.UserBuff[i].Index != NULL)
			{
				if(g_BuffIcon.UserBuff[i].Time > 0)
				{
					g_BuffIcon.UserBuff[i].Time--;
					if(g_BuffIcon.UserBuff[i].Time <= 0)
					{
						g_BuffIcon.UserBuff[i].Index = NULL;
						g_BuffIcon.UserBuff[i].Time = 0;
						g_BuffIcon.UserBuff[i].MaxTime = 0;
						//g_BuffIcon.UserBuffCount--;
					}
				}
			}
			// ----
			if(g_BuffIcon.UserExBuff[i].Index != NULL)
			{
				if(g_BuffIcon.UserExBuff[i].Time > 0)
				{
					g_BuffIcon.UserExBuff[i].Time--;
					if(g_BuffIcon.UserExBuff[i].Time <= 0)
					{
						g_BuffIcon.UserExBuff[i].Index = NULL;
						g_BuffIcon.UserExBuff[i].Time = 0;
						g_BuffIcon.UserExBuff[i].MaxTime = 0;
						//g_BuffIcon.User2BuffCount--;
					}
				}
			}
			// ----
			Sleep(1);
		}
		Sleep(999);
	} 

	return 0;
}
// ------------------------------------------------------------------------------

void BuffIcon::Recv(PMSG_SEND_BUFF_ICON* DataRecv)
{
	if(DataRecv->byEffectOption == 0)
	{
		for( int i = 0; i < MAX_STATE_COUNT; i++ )
		{
			if(this->UserBuff[i].Index == NULL || this->UserBuff[i].Index == DataRecv->btEffectIndex)
			{
				if(this->UserBuff[i].Index == NULL)
				{
					this->UserBuffCount++;
				}
				this->UserBuff[i].Index = DataRecv->btEffectIndex;
				this->UserBuff[i].Time = DataRecv->iLeftTime;
				this->UserBuff[i].MaxTime = DataRecv->iLeftTime;
				return;
			}
		}
	}
	else
	{
		for( int i = 0; i < MAX_STATE_COUNT; i++ )
		{
			if(this->UserBuff[i].Index == DataRecv->btEffectIndex)
			{
				this->UserBuff[i].Index = NULL;
				this->UserBuff[i].Time = 0;
				this->UserBuff[i].MaxTime = 0;

				this->UserBuffCount--;
				return;
			}
		}
	}
}
// ------------------------------------------------------------------------------

void BuffIcon::DeleteAllBuff()
{
	this->UserBuffCount = 0;
	for( int i = 0; i < MAX_STATE_COUNT; i++ )
	{
		this->UserBuff[i].Index = NULL;
		this->UserBuff[i].Time = 0;
		this->UserBuff[i].MaxTime = 0;
	}

	this->User2BuffCount = 0;
	for( int i = 0; i < MAX_STATE_COUNT; i++ )
	{
		this->UserExBuff[i].Index = NULL;
		this->UserExBuff[i].Time = 0;
		this->UserExBuff[i].MaxTime = 0;
	}
}
// ------------------------------------------------------------------------------

void BuffIcon::DrawBuffInfoEx(int BuffIndex, float iX, float iY, int iTime)
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

char* BuffIcon::GetBuffName(int ID)
{
	int BuffIndexData = -1;

	for(int i = 0; i < this->LoadBuffCount; i++)
	{
		if( this->DataBuff[i].Index == ID)
		{
			return this->DataBuff[i].Name;
		}
	}

	return NULL;
}
// ------------------------------------------------------------------------------

char* BuffIcon::GetAddedBuffName(int buff)
{
	if(buff == eAddExp)
	{
		return this->GetBuffName(AT_NPC_BUFF_EXP);
	}
	else if(buff == eAddDamage)
	{
		return this->GetBuffName(AT_NPC_BUFF_DAMAGE);
	}
	else if(buff == eAddDefence)
	{
		return this->GetBuffName(AT_NPC_BUFF_DEFENCE);
	}
	else if(buff == eAddBattle)
	{
		return this->GetBuffName(AT_NPC_BUFF_EXL_CRIT);
	}
	else if(buff == eAddDrop)
	{
		return this->GetBuffName(AT_NPC_BUFF_DROP);
	}
	else if(buff == eAddDouble)
	{
		return this->GetBuffName(AT_NPC_BUFF_DOUBLE);
	}

	return NULL;
}
// ------------------------------------------------------------------------------

void BuffIcon::GC_BuffInfo(PMSG_SEND_BUFF_ICON_EX* aRecv)
{
	int BuffIndex = aRecv->btEffectIndex;
	int DataIndex = -1;

	for(int b = 0; b < this->LoadBuffCount; b++)
	{
		if( this->DataBuff[b].Index == BuffIndex)
		{
			DataIndex = b;
			break;
		}
	}

	if(DataIndex == -1)
	{
		return;
	}

	int iEffect[5];
	int iValue[5];

	for(int i = 0; i < 5; i++)
	{
		iEffect[i] = aRecv->btEffectType[i];
		iValue[i] =  aRecv->iValue[i];
	}

	bool bDraw = false;
	char szName[20];
	char szInfo[5][200];

	ZeroMemory(&szName, sizeof(szName));
	ZeroMemory(&szInfo, sizeof(szInfo));

	memcpy(szName,	aRecv->szBuffName, sizeof(aRecv->szBuffName));

	if( BuffIndex == AT_VIP_SILVER )
	{
		// --
	}
	else if( BuffIndex == AT_VIP_GOLD )
	{
		// --
	}
	else if( BuffIndex == AT_VIP_PLATINUM )
	{
		// --
	}
	else if( BuffIndex == AT_PARTY_EXP_BONUS_EX )
	{
		// --
	}
	else if( BuffIndex == AT_GUILD_BUFF )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_EXP )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_DAMAGE )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_DEFENCE )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_EXL_CRIT )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_DROP )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_DOUBLE )
	{
		// --
	}
	else if( BuffIndex == AT_NOOB_BUFF )
	{
		// --
	}
	else if( BuffIndex == AT_QUEST_BUFF )
	{
		// --
	}
	else if( BuffIndex == AT_LORABATTLE_BUFF )
	{
		// --
	}
	else
	{
		for(int i = 0; i < 5; i++)
		{
			switch( iEffect[i] )
			{
			case ADD_OPTION_SPEED:
				sprintf(szInfo[i], "Attack Speed: +%d", iValue[i]);
				break;
			case ADD_OPTION_ATTACK_DAMAGE:
					sprintf(szInfo[i], "Damage: +%d", iValue[i]);
				break;
			case ADD_OPTION_DEFENSE:
				sprintf(szInfo[i], "Defence: +%d", iValue[i]);
				break;
			case ADD_OPTION_LIFE:
				sprintf(szInfo[i], "Life: +%d", iValue[i]);
				break;
			case ADD_OPTION_MANA:
				sprintf(szInfo[i], "Mana: +%d", iValue[i]);
				break;
			case ADD_OPTION_STRENGTH:
				sprintf(szInfo[i], "Strength: +%d", iValue[i]);
				break;
			case ADD_OPTION_DEXTERITY:
				sprintf(szInfo[i], "Dexterity: +%d", iValue[i]);
				break;
			case ADD_OPTION_VITALITY:
				sprintf(szInfo[i], "Vitality: +%d", iValue[i]);
				break;
			case ADD_OPTION_ENERGY:
				sprintf(szInfo[i], "Energy: +%d", iValue[i]);
				break;
			case ADD_OPTION_LEADERSHIP:
				sprintf(szInfo[i], "Command: +%d", iValue[i]);
				break;
			case ADD_OPTION_WIZARD_DEFENSE:
				sprintf(szInfo[i], "Absord: +%d%%%%", iValue[i]);
				break;
			case ADD_OPTION_MAGIC_DEFENSE:
				sprintf(szInfo[i], "Magic Defence: +%d%%%%", iValue[i]);
				break;
			case ADD_OPTION_REFLECT:
				sprintf(szInfo[i], "Reflect: +%d%%%%", iValue[i]);
				break;
			case ADD_OPTION_ATTACK_RATE:
				sprintf(szInfo[i], "Attack Rate: -%d", iValue[i]);
				break;
			case ADD_OPTION_CRITICAL_DAMAGE:
				sprintf(szInfo[i], "Critical Damage: +%d", iValue[i]);
				break;
			case ADD_OPTION_EXCELLENT_DAMAGE:
				sprintf(szInfo[i], "Excelent Damage: +%d", iValue[i]);
				break;
			case ADD_OPTION_BERSERKMANA:
				sprintf(szInfo[i], "Mana: -%d", iValue[i]);
				break;
			case ADD_OPTION_BERSERKLIFE:
				{
					int fAddLife = 0;
					float fPer = (((float)(40.0f) - (float)(iValue[i]))/100.0f);
					fPer = (fPer > 0.1f)?fPer:0.1f;
					fAddLife = fPer *gVisualFix.MaxLife;
					sprintf(szInfo[i], "Life: -%d", fAddLife);
				}
				break;
			case ADD_OPTION_MAGICDAMAGEMIN:
				sprintf(szInfo[i], "Wizard Damage: +%d", iValue[i]);
				break;
			case ADD_OPTION_XMASATTACK:
				sprintf(szInfo[i], "Damage: +%d", iValue[i]);
				break;
			case ADD_OPTION_XMASDEFENSE:
				sprintf(szInfo[i], "Defence: +%d", iValue[i]);
				break;
			case ADD_OPTION_IGNOREDEFENSE:
				sprintf(szInfo[i], "Ignore Defence: +%d%%%%", iValue[i]);
				break;
			case ADD_OPTION_BERSAKER_DEFENCE:
				sprintf(szInfo[i], "Defence: -%d%%%%", iValue[i]);
				break;
			case ADD_OPTION_BERSAKER_DAMAGE:
				sprintf(szInfo[i], "Wizard Damage: +%d%%%%", iValue[i]);
				break;
			case ADD_OPTION_CRITICAL_DMG:
				sprintf(szInfo[i], "Critical Damage: +%d", iValue[i]);
				break;
			}
		}

		for(int i = 0; i < 5; i++)
		{
			if(szInfo[i][0] != 0)
			{
				bDraw = true;
			}
		}

		if(bDraw == true)
		{
			ZeroMemory(&this->DataBuff[DataIndex].Text, sizeof(this->DataBuff[DataIndex].Text));
			for(int i = 0; i < 5; i++)
			{
				if(szInfo[i][0] != 0)
				{
					strcat(szInfo[i], "/");
					strcat(this->DataBuff[DataIndex].Text, szInfo[i]);
				}
			}	
		}
	}
}
// ------------------------------------------------------------------------------

void BuffIcon::GC_ExBuffData(GC_PMSG_ExBuff* aRecv)
{
	this->User2BuffCount = 0;
	ZeroMemory(&this->UserExBuff, sizeof(UserExBuff));

	this->User2BuffCount = aRecv->ExBuffCount;

	for(int i=0; i<MAX_STATE_COUNT;i++)
	{
		this->UserExBuff[i].Index = aRecv->ex_buff[i].BuffIndex;
		this->UserExBuff[i].Time = aRecv->ex_buff[i].BuffTime;
		this->UserExBuff[i].MaxTime = aRecv->ex_buff[i].BuffMaxTime;
	}
}
// ------------------------------------------------------------------------------

void BuffIcon::GC_GuildBuffRecv(PMSG_GC_GUILDBUFF* aRecv)
{
	int DataIndex = -1;

	for(int b = 0; b < this->LoadBuffCount; b++)
	{
		if( this->DataBuff[b].Index == AT_GUILD_BUFF)
		{
			DataIndex = b;
			break;
		}
	}

	if(DataIndex == -1)
	{
		return;
	}

	if(aRecv->AddExp > 0 || aRecv->AddZen > 0 || aRecv->AddMix > 0 || aRecv->AddDmgDef )
	{
		ZeroMemory(&this->DataBuff[DataIndex].Text, sizeof(this->DataBuff[DataIndex].Text));
	}
	else
	{
		sprintf(this->DataBuff[DataIndex].Text, "No Bonus Effect");
		return;
	}

	char Buffer[64] = { 0 };

	if(aRecv->AddExp > 0)
	{
		sprintf(Buffer, "Experience: +%d%%%%/", aRecv->AddExp);
		strcat(this->DataBuff[DataIndex].Text, Buffer);
	}

	if(aRecv->AddZen > 0)
	{
		sprintf(Buffer, "Drop Zen: +%d%%%%/", aRecv->AddZen);
		strcat(this->DataBuff[DataIndex].Text, Buffer);
	}

	if(aRecv->AddMix > 0)
	{
		sprintf(Buffer, "Chaos Mix Rate: +%d%%%%/", aRecv->AddMix);
		strcat(this->DataBuff[DataIndex].Text, Buffer);
	}

	if(aRecv->AddDmgDef > 0)
	{
		sprintf(Buffer, "Damage: +%d%%%%/Defence: +%d%%%%", aRecv->AddDmgDef, aRecv->AddDmgDef);
		strcat(this->DataBuff[DataIndex].Text, Buffer);
	}
}
// ------------------------------------------------------------------------------

void BuffIcon::GC_QuestBuffRecv(PMSG_GC_QUESTBUFF* aRecv)
{
	int DataIndex = -1;

	for(int b = 0; b < this->LoadBuffCount; b++)
	{
		if( this->DataBuff[b].Index == AT_QUEST_BUFF)
		{
			DataIndex = b;
			break;
		}
	}

	if(DataIndex == -1)
	{
		return;
	}

	WORD num1 = aRecv->Count1;
	WORD num2 = aRecv->Count2;
	WORD num3 = aRecv->Count3;

	if(num1 > 0 || num2 > 0 || num3 > 0)
	{
		ZeroMemory(&this->DataBuff[DataIndex].Text, sizeof(this->DataBuff[DataIndex].Text));
	}
	else
	{
		sprintf(this->DataBuff[DataIndex].Text, "No Quest");
		return;
	}

	char Buffer[64] = { 0 };

	if(num1 > 0)
	{
		sprintf(Buffer, "Master Killer: %d/", num1);
		strcat(this->DataBuff[DataIndex].Text, Buffer);
	}

	if(num2 > 0)
	{
		sprintf(Buffer, "Treasure Hunt: %d/", num2);
		strcat(this->DataBuff[DataIndex].Text, Buffer);
	}

	if(num3 > 0)
	{
		sprintf(Buffer, "Craft Way: %d/", num3);
		strcat(this->DataBuff[DataIndex].Text, Buffer);
	}
}
// ------------------------------------------------------------------------------
#endif