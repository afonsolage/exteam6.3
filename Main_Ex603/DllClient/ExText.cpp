#include "stdafx.h"
#include "ExText.h"

#if(CUSTOM_EXTEXT)

CExText g_ExText;

CExText::CExText()
{
	this->Init();
}

CExText::~CExText()
{
}

void CExText::Init()
{
	memset(this->m_Text, 0, sizeof(this->m_Text));
}

void CExText::Load()
{
	this->Init();
	this->Read(".\\Data\\Custom\\Configs\\Text.dat");
}

void CExText::Read(char* filename)
{
	GetPrivateProfileString("Config", "Text0", "Open Menu", this->m_Text[0], 128, filename);
	GetPrivateProfileString("Config", "Text1", "3D Camera [Reset]", this->m_Text[1], 128, filename);
	GetPrivateProfileString("Config", "Text2", "3D Camera [Switch]", this->m_Text[2], 128, filename);
	GetPrivateProfileString("Config", "Text3", "JewelsBank", this->m_Text[3], 128, filename);
	GetPrivateProfileString("Config", "Text4", "Graphics Effect", this->m_Text[4], 128, filename);
	GetPrivateProfileString("Config", "Text5", "Party Hp Bar", this->m_Text[5], 128, filename);
	GetPrivateProfileString("Config", "Text6", "User Hp Bar", this->m_Text[6], 128, filename);
	GetPrivateProfileString("Config", "Text7", "Monster Hp Bar", this->m_Text[7], 128, filename);
	GetPrivateProfileString("Config", "Text8", "Rage System", this->m_Text[8], 128, filename);
	GetPrivateProfileString("Config", "Text9", "Offline Attack", this->m_Text[9], 128, filename);

	GetPrivateProfileString("Config", "Text10", "Top 100 Player", this->m_Text[10], 128, filename);
	GetPrivateProfileString("Config", "Text11", "Events Timer", this->m_Text[11], 128, filename);
	GetPrivateProfileString("Config", "Text12", "Party Show", this->m_Text[12], 128, filename);
	GetPrivateProfileString("Config", "Text13", "Auto Party", this->m_Text[13], 128, filename);
	GetPrivateProfileString("Config", "Text14", "Party Search List", this->m_Text[14], 128, filename);
	GetPrivateProfileString("Config", "Text15", "Close Menu", this->m_Text[15], 128, filename);
	GetPrivateProfileString("Config", "Text16", "Local:", this->m_Text[16], 128, filename);
	GetPrivateProfileString("Config", "Text17", "L:%d HP:%d", this->m_Text[17], 128, filename);
	GetPrivateProfileString("Config", "Text18", "HP: %d", this->m_Text[18], 128, filename);
	GetPrivateProfileString("Config", "Text19", "L:%d R:%d G:%d", this->m_Text[19], 128, filename);
	GetPrivateProfileString("Config", "Text20", "HP : %d0%%", this->m_Text[20], 128, filename);

	GetPrivateProfileString("Config", "Text21", "Lvl:%d | R:%d | GR:%d", this->m_Text[21], 128, filename);
	GetPrivateProfileString("Config", "Text22", "Level: %d | Reset: %d", this->m_Text[22], 128, filename);
	GetPrivateProfileString("Config", "Text23", "Auto Party List", this->m_Text[23], 128, filename);
	GetPrivateProfileString("Config", "Text24", "Close", this->m_Text[24], 128, filename);
	GetPrivateProfileString("Config", "Text25", "Hello Player", this->m_Text[25], 128, filename);
	GetPrivateProfileString("Config", "Text26", "It is a system to search for the party", this->m_Text[26], 128, filename);
	GetPrivateProfileString("Config", "Text27", "N", this->m_Text[27], 128, filename);
	GetPrivateProfileString("Config", "Text28", "Player", this->m_Text[28], 128, filename);
	GetPrivateProfileString("Config", "Text29", "Level", this->m_Text[29], 128, filename);

	GetPrivateProfileString("Config", "Text30", "Map", this->m_Text[30], 128, filename);
	GetPrivateProfileString("Config", "Text31", "X", this->m_Text[31], 128, filename);
	GetPrivateProfileString("Config", "Text32", "Y", this->m_Text[32], 128, filename);
	GetPrivateProfileString("Config", "Text33", "Count", this->m_Text[33], 128, filename);
	GetPrivateProfileString("Config", "Text34", "Page: %d/%d", this->m_Text[34], 128, filename);
	GetPrivateProfileString("Config", "Text35", "Blood Castle:", this->m_Text[35], 128, filename);
	GetPrivateProfileString("Config", "Text36", "Devil Square:", this->m_Text[36], 128, filename);
	GetPrivateProfileString("Config", "Text37", "Chaos Castle:", this->m_Text[37], 128, filename);
	GetPrivateProfileString("Config", "Text38", "Golden Dragon:", this->m_Text[38], 128, filename);
	GetPrivateProfileString("Config", "Text39", "White Wizard:", this->m_Text[39], 128, filename);

	GetPrivateProfileString("Config", "Text40", "Premium:", this->m_Text[40], 128, filename);
	GetPrivateProfileString("Config", "Text41", "Chaos:", this->m_Text[41], 128, filename);
	GetPrivateProfileString("Config", "Text42", "Bless:", this->m_Text[42], 128, filename);
	GetPrivateProfileString("Config", "Text43", "Soul:", this->m_Text[43], 128, filename);
	GetPrivateProfileString("Config", "Text44", "Life:", this->m_Text[44], 128, filename);
	GetPrivateProfileString("Config", "Text45", "Createon:", this->m_Text[45], 128, filename);
	GetPrivateProfileString("Config", "Text46", "Credit:", this->m_Text[46], 128, filename);
	GetPrivateProfileString("Config", "Text47", "Zen:", this->m_Text[47], 128, filename);

	GetPrivateProfileString("Config", "Text48", "(N)", this->m_Text[48], 128, filename);
	GetPrivateProfileString("Config", "Text49", "Name", this->m_Text[49], 128, filename);
	GetPrivateProfileString("Config", "Text50", "Class", this->m_Text[50], 128, filename);
	GetPrivateProfileString("Config", "Text51", "Level", this->m_Text[51], 128, filename);
	GetPrivateProfileString("Config", "Text52", "Reset", this->m_Text[52], 128, filename);
	GetPrivateProfileString("Config", "Text53", "Grand", this->m_Text[53], 128, filename);
	GetPrivateProfileString("Config", "Text54", "Strength", this->m_Text[54], 128, filename);
	GetPrivateProfileString("Config", "Text55", "Agility", this->m_Text[55], 128, filename);
	GetPrivateProfileString("Config", "Text56", "Vitality", this->m_Text[56], 128, filename);
	GetPrivateProfileString("Config", "Text57", "Energy", this->m_Text[57], 128, filename);
	GetPrivateProfileString("Config", "Text58", "Command", this->m_Text[58], 128, filename);
	GetPrivateProfileString("Config", "Text59", "Guild", this->m_Text[59], 128, filename);

	GetPrivateProfileString("Config", "Text60", "Dark Wizard", this->m_Text[60], 128, filename);
	GetPrivateProfileString("Config", "Text61", "Soul Master", this->m_Text[61], 128, filename);
	GetPrivateProfileString("Config", "Text62", "Grand Master", this->m_Text[62], 128, filename);
	GetPrivateProfileString("Config", "Text63", "Dark Knight", this->m_Text[63], 128, filename);
	GetPrivateProfileString("Config", "Text64", "Blade Knight", this->m_Text[64], 128, filename);
	GetPrivateProfileString("Config", "Text65", "Blade Master", this->m_Text[65], 128, filename);
	GetPrivateProfileString("Config", "Text66", "Fairy Elf", this->m_Text[66], 128, filename);
	GetPrivateProfileString("Config", "Text67", "Muse Elf", this->m_Text[67], 128, filename);
	GetPrivateProfileString("Config", "Text68", "High Elf", this->m_Text[68], 128, filename);
	GetPrivateProfileString("Config", "Text69", "Magic Gladiator", this->m_Text[69], 128, filename);
	GetPrivateProfileString("Config", "Text70", "Duel Master", this->m_Text[70], 128, filename);
	GetPrivateProfileString("Config", "Text71", "Dark Lord", this->m_Text[71], 128, filename);
	GetPrivateProfileString("Config", "Text72", "Lord Emperial", this->m_Text[72], 128, filename);
	GetPrivateProfileString("Config", "Text73", "Summoner", this->m_Text[73], 128, filename);
	GetPrivateProfileString("Config", "Text74", "Bloody Summoner", this->m_Text[74], 128, filename);
	GetPrivateProfileString("Config", "Text75", "Dimension Master", this->m_Text[75], 128, filename);
	GetPrivateProfileString("Config", "Text76", "Rage Fighter", this->m_Text[76], 128, filename);
	GetPrivateProfileString("Config", "Text77", "Fist Master", this->m_Text[77], 128, filename);

	GetPrivateProfileString("Config", "Text78", "News", this->m_Text[78], 128, filename);
	GetPrivateProfileString("Config", "Text79", "Back", this->m_Text[79], 128, filename);

	GetPrivateProfileString("Config", "Text80", "Life: %d/%d", this->m_Text[80], 128, filename);
	GetPrivateProfileString("Config", "Text81", "Mana: %d/%d", this->m_Text[81], 128, filename);
	GetPrivateProfileString("Config", "Text82", "SD: %d/%d", this->m_Text[82], 128, filename);
	GetPrivateProfileString("Config", "Text83", "AG: %d/%d", this->m_Text[83], 128, filename);

	GetPrivateProfileString("Config", "Text84", "Ignor opponent's defensive power by %d%%", this->m_Text[84], 128, filename);
	GetPrivateProfileString("Config", "Text85", "Return's the enemy's attack power in %d%%", this->m_Text[85], 128, filename);
	GetPrivateProfileString("Config", "Text86", "Complete recoy of life in %d%% rate", this->m_Text[86], 128, filename);
	GetPrivateProfileString("Config", "Text87", "Complete reco of Mana in %d%% rate", this->m_Text[87], 128, filename);

	GetPrivateProfileString("Config", "Text88", "Sell Price: %s Zen", this->m_Text[88], 128, filename);
	GetPrivateProfileString("Config", "Text89", "Sell Price: %s Credit", this->m_Text[89], 128, filename);
	GetPrivateProfileString("Config", "Text90", "Sell Price: %s WCoin", this->m_Text[90], 128, filename);
	GetPrivateProfileString("Config", "Text91", "Sell Price: %s WCoin(P)", this->m_Text[91], 128, filename);
	GetPrivateProfileString("Config", "Text92", "Sell Price: %s Goblin Point", this->m_Text[92], 128, filename);

	GetPrivateProfileString("Config", "Text93", "Buy Price: %s Zen", this->m_Text[93], 128, filename);
	GetPrivateProfileString("Config", "Text94", "Buy Price: %d Zen", this->m_Text[94], 128, filename);
	GetPrivateProfileString("Config", "Text95", "Buy Price: %d,%03d Zen", this->m_Text[95], 128, filename);
	GetPrivateProfileString("Config", "Text96", "Buy Price: %d,%03d,%03d Zen", this->m_Text[96], 128, filename);
	GetPrivateProfileString("Config", "Text97", "Buy Price: %d,%03d,%03d,%03d Zen", this->m_Text[97], 128, filename);

	GetPrivateProfileString("Config", "Text98", "Buy Price: %d Credit", this->m_Text[98], 128, filename);
	GetPrivateProfileString("Config", "Text99", "Buy Price: %d,%03d Credit", this->m_Text[99], 128, filename);
	GetPrivateProfileString("Config", "Text100", "Buy Price: %d,%03d,%03d Credit", this->m_Text[100], 128, filename);
	GetPrivateProfileString("Config", "Text101", "Buy Price: %d,%03d,%03d,%03d Credit", this->m_Text[101], 128, filename);

	GetPrivateProfileString("Config", "Text102", "Buy Price: %d WCoin", this->m_Text[102], 128, filename);
	GetPrivateProfileString("Config", "Text103", "Buy Price: %d,%03d WCoin", this->m_Text[103], 128, filename);
	GetPrivateProfileString("Config", "Text104", "Buy Price: %d,%03d,%03d WCoin", this->m_Text[104], 128, filename);
	GetPrivateProfileString("Config", "Text105", "Buy Price: %d,%03d,%03d,%03d WCoin", this->m_Text[105], 128, filename);

	GetPrivateProfileString("Config", "Text106", "Buy Price: %d WCoin(P)", this->m_Text[106], 128, filename);
	GetPrivateProfileString("Config", "Text107", "Buy Price: %d,%03d WCoin(P)", this->m_Text[107], 128, filename);
	GetPrivateProfileString("Config", "Text108", "Buy Price: %d,%03d,%03d WCoin(P)", this->m_Text[108], 128, filename);
	GetPrivateProfileString("Config", "Text109", "Buy Price: %d,%03d,%03d,%03d WCoin(P)", this->m_Text[109], 128, filename);

	GetPrivateProfileString("Config", "Text106", "Buy Price: %d Goblin Points", this->m_Text[110], 128, filename);
	GetPrivateProfileString("Config", "Text107", "Buy Price: %d,%03d Goblin Points", this->m_Text[111], 128, filename);
	GetPrivateProfileString("Config", "Text108", "Buy Price: %d,%03d,%03d Goblin Points", this->m_Text[112], 128, filename);
	GetPrivateProfileString("Config", "Text109", "Buy Price: %d,%03d,%03d,%03d Goblin Points", this->m_Text[113], 128, filename);

	GetPrivateProfileString("Config", "Text114", "Reconnecting...", this->m_Text[114], 128, filename);
	GetPrivateProfileString("Config", "Text115", "Relogin...", this->m_Text[115], 128, filename);

	//

	GetPrivateProfileString("Config", "Text116", "Active System", this->m_Text[116], 128, filename);
	GetPrivateProfileString("Config", "Text117", "Max Level", this->m_Text[117], 128, filename);
	GetPrivateProfileString("Config", "Text118", "Auto Party", this->m_Text[118], 128, filename);
	GetPrivateProfileString("Config", "Text119", "Only One Class (Gold)", this->m_Text[119], 128, filename);
	GetPrivateProfileString("Config", "Text120", "Ok", this->m_Text[120], 128, filename);

	GetPrivateProfileString("Config", "Text121", "[SELL]", this->m_Text[121], 128, filename);

	GetPrivateProfileString("Config", "Text122", "Add Points", this->m_Text[122], 128, filename);
	GetPrivateProfileString("Config", "Text123", "Free Points:", this->m_Text[123], 128, filename);
	GetPrivateProfileString("Config", "Text124", "Strength:", this->m_Text[124], 128, filename);
	GetPrivateProfileString("Config", "Text125", "Agility:", this->m_Text[125], 128, filename);
	GetPrivateProfileString("Config", "Text126", "Vitality:", this->m_Text[126], 128, filename);
	GetPrivateProfileString("Config", "Text127", "Energy:", this->m_Text[127], 128, filename);
	GetPrivateProfileString("Config", "Text128", "Command:", this->m_Text[128], 128, filename);
	GetPrivateProfileString("Config", "Text129", "Cancel", this->m_Text[129], 128, filename);
	GetPrivateProfileString("Config", "Text130", "Grand Reset", this->m_Text[130], 128, filename);
	GetPrivateProfileString("Config", "Text131", "Quick add stats", this->m_Text[131], 128, filename);
	GetPrivateProfileString("Config", "Text132", "Reset Stats", this->m_Text[132], 128, filename);

	GetPrivateProfileString("Config", "Text133", "Reset stats Premium free", this->m_Text[133], 128, filename);
	GetPrivateProfileString("Config", "Text134", "Reset stats for %d WCoin", this->m_Text[134], 128, filename);
	GetPrivateProfileString("Config", "Text135", "Reset stats for %d Credits", this->m_Text[135], 128, filename);
	GetPrivateProfileString("Config", "Text136", "Reward Stats", this->m_Text[136], 128, filename);
	GetPrivateProfileString("Config", "Text137", "Accept", this->m_Text[137], 128, filename);

	GetPrivateProfileString("Config", "Text138", "Personal Shop Search", this->m_Text[138], 128, filename);
	GetPrivateProfileString("Config", "Text139", "Price", this->m_Text[139], 128, filename);
	GetPrivateProfileString("Config", "Text140", "Wcoin:", this->m_Text[140], 128, filename);
	GetPrivateProfileString("Config", "Text141", "Party Search", this->m_Text[141], 128, filename);
	GetPrivateProfileString("Config", "Text142", "join", this->m_Text[142], 128, filename);
	GetPrivateProfileString("Config", "Text143", "Need to Party:", this->m_Text[143], 128, filename);
	GetPrivateProfileString("Config", "Text144", "Dark Wizard", this->m_Text[144], 128, filename);
	GetPrivateProfileString("Config", "Text145", "Dark Knight", this->m_Text[145], 128, filename);
	GetPrivateProfileString("Config", "Text146", "Elf", this->m_Text[146], 128, filename);
	GetPrivateProfileString("Config", "Text147", "Magic Gladiator", this->m_Text[147], 128, filename);
	GetPrivateProfileString("Config", "Text148", "Dark Lord", this->m_Text[148], 128, filename);
	GetPrivateProfileString("Config", "Text149", "Summoner", this->m_Text[149], 128, filename);
	GetPrivateProfileString("Config", "Text150", "Rage Fighter", this->m_Text[150], 128, filename);

	GetPrivateProfileString("Config", "Text151", "Premium System", this->m_Text[151], 128, filename);
	GetPrivateProfileString("Config", "Text152", "Premium Status:", this->m_Text[152], 128, filename);
	GetPrivateProfileString("Config", "Text153", "Premium Time:", this->m_Text[153], 128, filename);
	GetPrivateProfileString("Config", "Text154", "Bronze Premium Buff", this->m_Text[154], 128, filename);
	GetPrivateProfileString("Config", "Text155", "Silver Premium Buff", this->m_Text[155], 128, filename);
	GetPrivateProfileString("Config", "Text156", "Gold Premium Buff", this->m_Text[156], 128, filename);
	GetPrivateProfileString("Config", "Text157", "Premium Day", this->m_Text[157], 128, filename);
	GetPrivateProfileString("Config", "Text158", "Required WCoin:", this->m_Text[158], 128, filename);
	GetPrivateProfileString("Config", "Text159", "Premium Day", this->m_Text[159], 128, filename);
	GetPrivateProfileString("Config", "Text160", "Buy Premium", this->m_Text[160], 128, filename);
	GetPrivateProfileString("Config", "Text161", "Level: %d", this->m_Text[161], 128, filename);

	GetPrivateProfileString("Config", "Text162", "Bronze", this->m_Text[162], 128, filename);
	GetPrivateProfileString("Config", "Text163", "Silver", this->m_Text[163], 128, filename);
	GetPrivateProfileString("Config", "Text164", "Gold", this->m_Text[164], 128, filename);
	GetPrivateProfileString("Config", "Text165", "No", this->m_Text[165], 128, filename);
	GetPrivateProfileString("Config", "Text166", "Day: %2d Hour: %2d Minutes: %2d Seconds: %2d", this->m_Text[166], 128, filename);
	GetPrivateProfileString("Config", "Text167", "Day: %2d Hour: %2d Min: %2d", this->m_Text[167], 128, filename);
	GetPrivateProfileString("Config", "Text168", "Day: %2d Hour: %2d", this->m_Text[168], 128, filename);
	GetPrivateProfileString("Config", "Text169", "Hour: %2d Minutes: %2d Seconds: %2d", this->m_Text[169], 128, filename);
	GetPrivateProfileString("Config", "Text170", "Hour: %2d Min: %2d", this->m_Text[170], 128, filename);
	GetPrivateProfileString("Config", "Text171", "Hour: %2d", this->m_Text[171], 128, filename);
	GetPrivateProfileString("Config", "Text172", "Minutes: %2d Seconds: %2d", this->m_Text[172], 128, filename);
	GetPrivateProfileString("Config", "Text173", "Min: %2d", this->m_Text[173], 128, filename);
	GetPrivateProfileString("Config", "Text174", "Seconds: %2d", this->m_Text[174], 128, filename);
	GetPrivateProfileString("Config", "Text175", "Sec: %2d", this->m_Text[175], 128, filename);

	GetPrivateProfileString("Config", "Text176", "Price: %s Zen", this->m_Text[176], 128, filename);
	GetPrivateProfileString("Config", "Text177", "Price: %d Credit", this->m_Text[177], 128, filename);
	GetPrivateProfileString("Config", "Text178", "Price: %d WCoin", this->m_Text[178], 128, filename);
	GetPrivateProfileString("Config", "Text179", "Price: %d Bless", this->m_Text[179], 128, filename);
	GetPrivateProfileString("Config", "Text180", "Price: %d Soul", this->m_Text[180], 128, filename);
	GetPrivateProfileString("Config", "Text181", "Price: %d Chaos", this->m_Text[181], 128, filename);
	GetPrivateProfileString("Config", "Text182", "Price: %d Life", this->m_Text[182], 128, filename);

	GetPrivateProfileString("Config", "Text183", "Cash Shop", this->m_Text[183], 128, filename);

	//Achievements
	GetPrivateProfileString("Config", "Text184", "Achievements System", this->m_Text[184], 128, filename);
	GetPrivateProfileString("Config", "Text185", "Monster Kill", this->m_Text[185], 128, filename);
	GetPrivateProfileString("Config", "Text186", "Monster 100lvl Kill", this->m_Text[186], 128, filename);
	GetPrivateProfileString("Config", "Text187", "Pheonix Kill", this->m_Text[187], 128, filename);
	GetPrivateProfileString("Config", "Text188", "Hell Main Kill", this->m_Text[188], 128, filename);
	GetPrivateProfileString("Config", "Text189", "Kill Erohim", this->m_Text[189], 128, filename);
	GetPrivateProfileString("Config", "Text190", "Kalima Monser Kill", this->m_Text[190], 128, filename);
	GetPrivateProfileString("Config", "Text191", "Kundun Kill", this->m_Text[191], 128, filename);
	GetPrivateProfileString("Config", "Text192", "Red Dragon Kill", this->m_Text[192], 128, filename);
	GetPrivateProfileString("Config", "Text193", "Golden Kill", this->m_Text[193], 128, filename);
	GetPrivateProfileString("Config", "Text194", "Selupan Kill", this->m_Text[194], 128, filename);
	GetPrivateProfileString("Config", "Text195", "Kanturu Monster Kill", this->m_Text[195], 128, filename);
	GetPrivateProfileString("Config", "Text196", "Kanturu Boss Kill", this->m_Text[196], 128, filename);
	GetPrivateProfileString("Config", "Text197", "Kill gate BC", this->m_Text[197], 128, filename);
	GetPrivateProfileString("Config", "Text198", "Kill Statue BC", this->m_Text[198], 128, filename);
	GetPrivateProfileString("Config", "Text199", "Complete BC", this->m_Text[199], 128, filename);
	GetPrivateProfileString("Config", "Text200", "Take part in CC", this->m_Text[200], 128, filename);
	GetPrivateProfileString("Config", "Text201", "Winning the CC", this->m_Text[201], 128, filename);
	GetPrivateProfileString("Config", "Text202", "White Wizard Kill", this->m_Text[202], 128, filename);
	GetPrivateProfileString("Config", "Text203", "Orc Kill", this->m_Text[203], 128, filename);
	GetPrivateProfileString("Config", "Text204", "CryWolf Event Monster", this->m_Text[204], 128, filename);
	GetPrivateProfileString("Config", "Text205", "Pick up Zen", this->m_Text[205], 128, filename);
	GetPrivateProfileString("Config", "Text206", "Pick up Exellent", this->m_Text[206], 128, filename);
	GetPrivateProfileString("Config", "Text207", "Pick up Ancent", this->m_Text[207], 128, filename);
	GetPrivateProfileString("Config", "Text208", "Pick up Jewels", this->m_Text[208], 128, filename);
	GetPrivateProfileString("Config", "Text209", "Used Jewels", this->m_Text[209], 128, filename);
	GetPrivateProfileString("Config", "Text210", "Level up", this->m_Text[210], 128, filename);
	GetPrivateProfileString("Config", "Text211", "Reset up", this->m_Text[211], 128, filename);
	GetPrivateProfileString("Config", "Text212", "Online Time", this->m_Text[212], 128, filename);
	GetPrivateProfileString("Config", "Text213", "Party noob level up", this->m_Text[213], 128, filename);
	GetPrivateProfileString("Config", "Text214", "Offline Attack Time", this->m_Text[214], 128, filename);
	GetPrivateProfileString("Config", "Text215", "Success Chaos Mix", this->m_Text[215], 128, filename);
	GetPrivateProfileString("Config", "Text216", "Failed Chaos Mix", this->m_Text[216], 128, filename);
	GetPrivateProfileString("Config", "Text217", "Pick up Rena", this->m_Text[217], 128, filename);
	GetPrivateProfileString("Config", "Text218", "Pick up sing of lord", this->m_Text[218], 128, filename);
	GetPrivateProfileString("Config", "Text219", "Win Siege", this->m_Text[219], 128, filename);
	GetPrivateProfileString("Config", "Text220", "Kill Castle Siege NPC", this->m_Text[220], 128, filename);
	GetPrivateProfileString("Config", "Text221", "Kill player Castle Siege", this->m_Text[221], 128, filename);
	GetPrivateProfileString("Config", "Text222", "Move player from Switch", this->m_Text[222], 128, filename);
	GetPrivateProfileString("Config", "Text223", "Withstand Switch 10 min", this->m_Text[223], 128, filename);
	GetPrivateProfileString("Config", "Text224", "Move player from Crown", this->m_Text[224], 128, filename);
	GetPrivateProfileString("Config", "Text225", "Player Kill", this->m_Text[225], 128, filename);
	GetPrivateProfileString("Config", "Text226", "Kill in self-defense", this->m_Text[226], 128, filename);
	GetPrivateProfileString("Config", "Text227", "Phonoman Kill", this->m_Text[227], 128, filename);
	GetPrivateProfileString("Config", "Text228", "Duel Win", this->m_Text[228], 128, filename);
	GetPrivateProfileString("Config", "Text229", "Guild War Win", this->m_Text[229], 128, filename);

}

char* CExText::GetText(int number)
{
	if(number < 0 || number >= MAX_EXTEXT)
	{
		return "Error";
	}

	return this->m_Text[number];
}


/*
g_ExText.GetText(number)
*/

#endif