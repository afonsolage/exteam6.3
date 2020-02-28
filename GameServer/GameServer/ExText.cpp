#include "StdAfx.h"
#include "ExText.h"
#include "GameMain.h"

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
	memset(this->m_Path, 0, sizeof(this->m_Text));
	memset(this->m_Text, 0, sizeof(this->m_Text));
}

void CExText::Load()
{
	this->Init();
	this->Read(gDirPath.GetNewPath("ExData\\ExTextS.dat"));
	this->LoadText();
}

void CExText::Read(char* filename)
{
	memcpy(this->m_Path, filename, sizeof(this->m_Path));
}

void CExText::LoadText()
{
	this->SetText(0, "[Reset]: %d");
	this->SetText(1, "[GReset]: %d");
	this->SetText(2, "[Online]: %d");
	this->SetText(3, "[Reset]: Started In %s");
	this->SetText(4, "[Reset]: Interface Disable");
	this->SetText(5, "[Reset]: Max Reset %d");
	this->SetText(6, "[Reset]: You need above %d Level to Reset");
	this->SetText(7, "[Reset]: You need above %d Wcoin to Reset");
	this->SetText(8, "[Reset]: You need above %d Credits to Reset");
	this->SetText(9, "[Reset]: You need above %d Zen to Reset");
	this->SetText(10, "[Reset]: You need Empty Inventory to Reset");
	this->SetText(11, "[Reset]: Need Reset Items %d");
	this->SetText(12, "[GReset]: Started In Lorencia");
	this->SetText(13, "[GReset]: Interface Disable");
	this->SetText(14, "[GReset]: Max Grand Reset %d");
	this->SetText(15, "[GReset]: You need above %d Reset to GReset");
	this->SetText(16, "[GReset]: You need above %d Level to GReset");
	this->SetText(17, "[GReset]: You need above %d Zen to GReset");
	this->SetText(18, "[GReset]: You need Empty Inventory to GReset");
	this->SetText(19, "[Jewels] Max %d Exellent Option");
	this->SetText(20, "[Jewels] Need Item Exellent Status");
	this->SetText(21, "[Jewels] Max Item Level %d");
	this->SetText(22, "[Jewels] Min Item Level %d");
	this->SetText(23, "[Jewels] Need Item Accessory");
	this->SetText(24, "[Jewels] Is Set to Luck");
	this->SetText(25, "[Jewels] No use item luck");
	this->SetText(26, "[Jewels] Is Weapon to Skill");
	this->SetText(27, "[Jewels] No use item skill");
	this->SetText(28, "[Jewels] Max Level Item %d");
	this->SetText(29, "[Jewels] Min Level Item %d");
	this->SetText(30, "[Jewels] No use item Level");
	this->SetText(31, "[Jewels] Item Exellent status");
	this->SetText(32, "[Jewels] No use item");
	this->SetText(33, "[Jewels] No Use Item Ancent");
	this->SetText(34, "[Jewels] Item is Ancent");
	this->SetText(35, "[Jewels] Max Option to Item");
	this->SetText(36, "[Jewels] No Use Item PvP");
	this->SetText(37, "[Jewels] Item is PvP");
	this->SetText(38, "[Jewels] Max Socket option %d");
	this->SetText(39, "[Jewels] No Use Item Socket");
	this->SetText(40, "[Jewels] Max %d Exellent Option");
	this->SetText(41, "[Jewels] Item Exellent Status");
	this->SetText(42, "[OfflineMode] Disable in Castle siege map");
	this->SetText(43, "[OffTrade] OffTrade work only Loren Market");
	this->SetText(44,"[OfflineTrade][%s]");
	this->SetText(45, "[OffTrade] OffTrade work only Loren Market");
	this->SetText(46, "[OffTrade] Disable in Castle siege map");
	this->SetText(47, "[OffTrade] Need Open Shop");
	this->SetText(48, "[OffTrade][%s] Lorencia %d %d");
	this->SetText(49, "[OffTrade][%s] Devias %d %d");
	this->SetText(50, "[OffTrade][%s] Noria %d %d");
	this->SetText(51, "[OffTrade][%s] Emblend %d %d");
	this->SetText(52, "[OffTrade][%s] Loren %d %d");
	this->SetText(53, "[Offline Trade] work only special maps");
	this->SetText(54, ".::ZEN SHOP::.");
	this->SetText(55, ".::CREDIT SHOP::.");
	this->SetText(56, ".::WCOIN SHOP::.");
	this->SetText(57, ".::WCOIN(P) SHOP::.");
	this->SetText(58, ".::GOBLIN SHOP::.");
	this->SetText(59, ".::CHAOS SHOP::.");
	this->SetText(60, ".::BLESS SHOP::.");
	this->SetText(61, ".::SOUL SHOP::.");
	this->SetText(62, ".::LIFE SHOP::.");
	this->SetText(63, "[%s][%s] Lorencia %d %d");
	this->SetText(64, "[%s][%s] Devias %d %d");
	this->SetText(65, "[%s][%s] Noria %d %d");
	this->SetText(66, "[%s][%s] Emblend %d %d");
	this->SetText(67, "[%s][%s] Loren %d %d");
	this->SetText(68, "[OffTrade] work only special maps");
	this->SetText(69, "[OffTrade] Need %d PcPoint");
	this->SetText(70, "[OffTrade] Need %d WCoinC");
	this->SetText(71, "[OffTrade] Need %d WCoinP");
	this->SetText(72, "[OffTrade] Need %d WCoinG");
	this->SetText(73, "[OffTrade] Need %d Chaos Bank");
	this->SetText(74, "[OffTrade] Need %d Bless Bank");
	this->SetText(75, "[OffTrade] Need %d Soul Bank");
	this->SetText(76, "[OffTrade] Need %d Life Bank");
	this->SetText(77, "In %s Max Zen In Inventory");
	this->SetText(78, "Max Zen In Inventory");
	this->SetText(79, "[Buy] Need %d Zen");
	this->SetText(80, "[Buy] Need %d Credit");
	this->SetText(81, "[Buy] Price %d Credit");
	this->SetText(82, "[Buy] Need %d WCoinC");
	this->SetText(83, "[Buy] Price %d WCoinC");
	this->SetText(84, "[Buy] Need %d WCoinP");
	this->SetText(85, "[Buy] Need %d WCoinP");
	this->SetText(86, "[Buy] Need %d Goblin");
	this->SetText(87, "[Buy] Price %d Goblin");
	this->SetText(88, "~[WCoinC]: Online Bonus: %d");
	this->SetText(89, "~[WCoinP]: Online Bonus: %d");
	this->SetText(90, "~[Goblin]: Online Bonus: %d");
	this->SetText(91, "~[Credit]: Online Bonus: %d");
	this->SetText(92, "[Evangelion] Lorencia Win %s!");
	this->SetText(93, "[Evangelion] In Noria!");
	this->SetText(94, "[Evangelion] Noria Win %s!");
	this->SetText(95, "[Evangelion] In Devias!");
	this->SetText(96, "[Evangelion] Devias Win %s!");
	this->SetText(97, "[Evangelion] In Lorencia!");
	this->SetText(98, "[Evangelion] End!");
	this->SetText(99, "[Happy Hour] Event Started!");
	this->SetText(100, "[Happy Hour] Exp: +%d%%%% Drop: +%d%%%%%");
	this->SetText(101, "[Happy Hour] Event Close!");
	this->SetText(102, "@[%s]: Mission: %d");
	this->SetText(103, "@[%s]: Mission accomplished!");
	this->SetText(104, "@[%s]: FreePoints %d!");
	this->SetText(105, "@[%s]: ExCred %d!");
	this->SetText(106, "@[%s]: WCoinC %d!");
	this->SetText(107, "@[%s]: WCoinP %d!");
	this->SetText(108, "@[%s]: Goblin Points %d!");
	this->SetText(109, "[Monster Bonus]: +%d Credits");
	this->SetText(110, "[Monster Bonus]: +%d WcoinC");
	this->SetText(111, "[Monster Bonus]: +%d WcoinP");
	this->SetText(112, "[Monster Bonus]: +%d Goblin Points");
	this->SetText(113, "[Credit Donate]:Buy Wcoin Multiple of 100");
	this->SetText(114, "[Credit Donate]:Buy Wcoin Need %d");
	this->SetText(115, "[Credit Donate]:Buy Wcoin(P) Multiple of 100");
	this->SetText(116, "[Credit Donate]:Buy Wcoin(P) Need %d");
	this->SetText(117, "[Credit Donate]:Buy Goblin Multiple of 100");
	this->SetText(118, "[Credit Donate]:Buy Goblin Need %d");
	this->SetText(119, "[Credit Donate]:Buy Premium Need %d");
	this->SetText(120, "[Credit Donate]: Need to make space in the inventory (%dx%d)");
	this->SetText(121, "[Credit Donate]: Need %d Credits");
	this->SetText(122, "[Credit Donate]: Buy: %s, Price: %d");
	this->SetText(123, "[Credit Donate]: Sell %.2f Credits");
	this->SetText(124, "[Change Class]: You need Empty Inventory");
	this->SetText(125, "[Change Class]: Need %d Credit");
	this->SetText(126, "[Add] Need %d zen");
	this->SetText(127, "[Add] Need %d level");
	this->SetText(128, "[PkClear] Need %d Level");
	this->SetText(129, "[PkClear] Need %d Zen");
	this->SetText(130, "/offzen");
	this->SetText(131, "/offcredit");
	this->SetText(132, "/offwcoinc");
	this->SetText(133, "/offwcoinp");
	this->SetText(134, "/offgoblin");
	this->SetText(135, "/offchaos");
	this->SetText(136, "/offbless");
	this->SetText(137, "/offsoul");
	this->SetText(138, "/offlife");
	this->SetText(139, "/sendchaosbank");
	this->SetText(140, "/sendblessbank");
	this->SetText(141, "/sendsoulbank");
	this->SetText(142, "/sendlifebank");
	this->SetText(143, "/recvchaosbank");
	this->SetText(144, "/recvblessbank");
	this->SetText(145, "/recvsoulbank");
	this->SetText(146, "/recvlifebank");
	this->SetText(147, "[JewelsBank] Need %d Chaos");
	this->SetText(148, "[JewelsBank] Send %d Chaos");
	this->SetText(149, "[JewelsBank] Need %d Bless");
	this->SetText(150, "[JewelsBank] Send %d Bless");
	this->SetText(151, "[JewelsBank] Need %d Soul");
	this->SetText(152, "[JewelsBank] Send %d Soul");
	this->SetText(153, "[JewelsBank] Need %d Life");
	this->SetText(154, "[JewelsBank] Send %d Life");
	this->SetText(155, "[JewelsBank] No %d Chaos");
	this->SetText(156, "[JewelsBank] Inventory %d");
	this->SetText(157, "[JewelsBank] Recv %d Chaos");
	this->SetText(158, "[JewelsBank] No %d Bless");
	this->SetText(159, "[JewelsBank] Recv %d Bless");
	this->SetText(160, "[JewelsBank] No %d Soul");
	this->SetText(161, "[JewelsBank] Recv %d Soul");
	this->SetText(162, "[JewelsBank] No %d Life");
	this->SetText(163, "[JewelsBank] Recv %d Life");
	this->SetText(164, "Lorencia");
	this->SetText(165, "Dungeon");
	this->SetText(166, "Devias");
	this->SetText(167, "Noria");
	this->SetText(168, "LostTower");
	this->SetText(169, "Arena");
	this->SetText(170, "Atlans");
	this->SetText(171, "Tarkan");
	this->SetText(172, "DevilSquare");
	this->SetText(173, "Icarus");
	this->SetText(174, "Blood Castle 1");
	this->SetText(175, "Blood Castle 2");
	this->SetText(176, "Blood Castle 3");
	this->SetText(177, "Blood Castle 4");
	this->SetText(178, "Blood Castle 5");
	this->SetText(179, "Blood Castle 6");
	this->SetText(180, "Blood Castle 7");
	this->SetText(181, "Chaos Castle 1");
	this->SetText(182, "Chaos Castle 2");
	this->SetText(183, "Chaos Castle 3");
	this->SetText(184, "Chaos Castle 4");
	this->SetText(185, "Chaos Castle 5");
	this->SetText(186, "Chaos Castle 6");
	this->SetText(187, "Kalima 1");
	this->SetText(188, "Kalima 2");
	this->SetText(189, "Kalima 3");
	this->SetText(190, "Kalima 4");
	this->SetText(191, "Kalima 5");
	this->SetText(192, "Kalima 6");
	this->SetText(193, "Castle");
	this->SetText(194, "Land Of Trial");
	this->SetText(195, "Aida");
	this->SetText(196, "Cry Wolf");
	this->SetText(197, "Cry Wolf");
	this->SetText(198, "Kalima 7");
	this->SetText(199, "Kanturu");
	this->SetText(200, "Kanturu Relic");
	this->SetText(201, "Kanturu Boss");
	this->SetText(202, "Balgas Baraks");
	this->SetText(203, "Balgas Refuge");
	this->SetText(204, "Illusion Temple 1");
	this->SetText(205, "Illusion Temple 2");
	this->SetText(206, "Illusion Temple 3");
	this->SetText(207, "Illusion Temple 4");
	this->SetText(208, "Illusion Temple 5");
	this->SetText(209, "Illusion Temple 6");
	this->SetText(210, "Elblend");
	this->SetText(211, "Blood Castle 8");
	this->SetText(212, "Chaos Castle 7");
	this->SetText(213, "Devil Squere 7");
	this->SetText(214, "Swamp Of Calmness");
	this->SetText(215, "Raklion");
	this->SetText(216, "Raklion Boss");
	this->SetText(217, "Santa Town");
	this->SetText(218, "Vulcan");
	this->SetText(219, "Vulcan Room");
	this->SetText(220, "Double Goer 1");
	this->SetText(221, "Double Goer 2");
	this->SetText(222, "Double Goer 3");
	this->SetText(223, "Double Goer 4");
	this->SetText(224, "Imperial 1");
	this->SetText(225, "Imperial 2");
	this->SetText(226, "Imperial 3");
	this->SetText(227, "Imperial 4");
	this->SetText(228, "Loren Market");
	this->SetText(229, "Karutan");
	this->SetText(230, "Karutan 2");
	this->SetText(231, "[Buy] Need %d Zen");
	this->SetText(232, "[Buy] Need %d Bonus");
	this->SetText(233, "[Buy] Need %d Credits");
	this->SetText(234, "[Buy] Need %d Zen");
	this->SetText(235, "[Buy] Need %d Bonus");
	this->SetText(236, "[Buy] %d Wcoin");
	this->SetText(237, "[Buy] Need %d Credits");
	this->SetText(238, "[Buy] %d Credits");
	this->SetText(239, "[OffExp] Need %d Zen");
	this->SetText(240, "[OffExp] Need %d Credit");
	this->SetText(241, "[OffExp] Need %d WCoinC");
	this->SetText(242, "[OffExp] Need %d WCoinP");
	this->SetText(243, "[OffExp] Need %d Goblin");
	this->SetText(244, "[OffExp] Works just outside of town");
	this->SetText(245, "GM Map");
	this->SetText(246, "@[PREMIUM] Experience: +%d%%");
	this->SetText(247, "@[PREMIUM] Drop Zen: +%d%%");
	this->SetText(248, "@[PREMIUM] Damage: +%d%%");
	this->SetText(249, "@[PREMIUM] Wizard Damage: +%d%%");
	this->SetText(250, "@[PREMIUM] Defence: +%d%%");
	this->SetText(251, "@[PREMIUM] Min: %d");
	this->SetText(252, "@[PREMIUM] Time is over");
	this->SetText(253, "No Jewels");
	this->SetText(254, "[Drop Event] Started!");

	this->SetText(255, "[Need Level]: %d");
	this->SetText(256, "[Need Reset]: %d");
	this->SetText(257, "[Need GReset]: %d");
	this->SetText(258, "[Need Premium]: Status %d rank");
	this->SetText(259, "[Need Premium]: Status");
	this->SetText(260, "[Need Zen]: %d");
	this->SetText(261, "[Need ExCred]: %d");
	this->SetText(262, "[Need WCoinC]: %d");
	this->SetText(263, "[Need WCoinP]: %d");
	this->SetText(264, "[Need Goblin]: %d");
	this->SetText(265, "[Max Reset]: %d");
	this->SetText(266, "[Max GReset]: %d");
	
}

void CExText::SetText(int number, char* Text)
{
	if(number < 0 || number >= MAX_EXTEXT)
	{
		return;
	}

	char szTextNumber[256] = { 0 };
	sprintf(szTextNumber, "Text%d", number);
	GetPrivateProfileString("ExTeam", szTextNumber, Text, this->m_Text[number], 128, this->m_Path);
}

char* CExText::GetText(int number)
{
	if(number < 0 || number >= MAX_EXTEXT)
	{
		return "Error";
	}

	return this->m_Text[number];
}

#endif