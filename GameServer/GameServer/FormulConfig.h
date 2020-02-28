#include "StdAfx.h"

#ifdef FORMUL_CONFIG

#define FORMUL_CONFIG_DIR	"..\\Data\\ExData\\FormulConfig.ini"
#define LENGHT_STR 30

class cFormulConfig
{
public:

		void Load();

	//Dark Knight/ Blade Knight/ Blade Master
		float MinDmg1;// = STR/6
		float MaxDmg1;// = STR/4
		float ComboBase1;// = (STR+AGI+ENE)/2
		float Speed1;// = AGI/15
		float Defense1;// = AGI/3
		float PvMDefenseRate1;// = AGI/3
		float PvMAttackRate1;// = LVL*5+(AGI*3)/2+STR/4
		float PvMAttackRate2;// = LVL*5+(AGI*3)/2+STR/4
		float PvMAttackRate3;// = LVL*5+(AGI*3)/2+STR/4
		float PvMAttackRate4;// = LVL*5+(AGI*3)/2+STR/4
		float PvPDefenseRate1;// = LVL*2+AGI*0.5
		float PvPDefenseRate2;// = LVL*2+AGI*0.5
		float PvPAttackRate1;// = LVL*3+AGI*4.5
		float PvPAttackRate2;// = LVL*3+AGI*4.5
		float HP1;// = 110+(LvL+mLvL)*2)+((VIT-25)*4.5) new
		float HP2;// = 110+(LvL+mLvL)*2)+((VIT-25)*4.5) new
		float HP3;// = 110+(LvL+mLvL)*2)+((VIT-25)*4.5) new
		float HP4;// = 110+(LvL+mLvL)*2)+((VIT-25)*4.5) new
						
		float Mana1;// = 10+(LVL-1)*0.5+ENE
			float Mana2;// = 10+(LVL-1)*0.5+ENE
		float Mana3;// = 10+(LVL-1)*0.5+ENE
		float ManaReg;// = mana/27.5
		float SD1;// = (STR+AGI+VIT+ENE)*1.2+defense/2+(LVL*LVL)/30
		float SD2;// = (STR+AGI+VIT+ENE)*1.2+defense/2+(LVL*LVL)/30
		float SD3;// = (STR+AGI+VIT+ENE)*1.2+defense/2+(LVL*LVL)/30
		float AG1;// = ENE+VIT*0.3+AGI*0.2+STR*0.15
		float AG2;// = ENE+VIT*0.3+AGI*0.2+STR*0.15
		float AG3;// = ENE+VIT*0.3+AGI*0.2+STR*0.15
		float AGReg1;// = 2+AG/20
		float AGReg2;// = 2+AG/20
		float SkillProc1;// = 200+ENE/10
		float SkillProc2;// = 200+ENE/10
		float FortitudeProc1;// = 12+VIT/300+ENE/60
		float FortitudeProc2;// = 12+VIT/300+ENE/60
		float FortitudeProc3;// = 12+VIT/300+ENE/60

	//Dark Wizard/Soul Master/Grand Master

		Min wiz dmg = ENE/9
		Max wiz dmg = ENE/4
		Speed = AGI/10
		Defense = AGI/4
		PvM defense rate = AGI/3
		PvM attack rate = LVL*5+(AGI*3)/2+STR/4
		PvP defense rate = LVL*2+AGI*0.25
		PvP attack rate = LVL*3+AGI*4
		HP = 30+(LVL-1)+VIT*2
		Mana = (LVL-1)*2+ENE*2
		Mana regen = mana/27.5
		SD = (STR+AGI+VIT+ENE)*1.2+defense/2+(LVL*LVL)/30
		AG = ENE*0.2+VIT*0.3+AGI*0.4+STR*0.2
		AG regen = 2+AG/33.3
		Soul barrier %(without Skill Tree) = 10+AGI/820+ENE/1640
		Soul barrier %(Skill Tree) = 10+AGI/3250+ENE/6500
		Soul barrier % = Soul barrier % + Soul barrier %(Skill Tree)
		Nova max spell dmg = 1320+STR/2
		Fenrir base min dmg = 60+STR/5+AGI/5+VIT/7+ENE/3
		Fenrir base max dmg = 90+STR/5+AGI/5+VIT/7+ENE/3


	//Fairy Elf/Muse Elf/High Elf

		Min dmg = STR/10+AGI/5
		Max dmg = STR/6+AGI/2
		Speed = AGI/50
		Defense = AGI/7
		PvM defense rate = AGI/4
		PvM attack rate = LVL*5+(AGI*3)/2+STR/4
		PvP defense rate = LVL*2+AGI*0.1
		PvP attack rate = LVL*3+AGI*0.6
		HP = 40+(LVL-1)+VIT*2
		Mana = 6+(LVL*1.5)+(ENE*1.5)
		Mana regen = mana/27.5
		SD = (STR+AGI+VIT+ENE)*1.2+defense/2+(LVL*LVL)/30
		AG = ENE*0.2+VIT*0.3+AGI*0.2+STR*0.3
		AG regen = 2+AG/33.33
		Damage buff = ENE/7+3
		Defense buff = ENE/8+2
		Heal buff = ENE/5+5


	//Magic Gladiator/Duel Master

		Min dmg = STR/4+ENE/10
		Max dmg = STR/2+ENE/6
		Min wiz dmg = ENE/8
		Max wiz dmg = ENE/3
		Speed = AGI/15
		Defense = AGI/4
		PvM defense rate = AGI/3
		PvM attack rate = LVL*5+(AGI*3)/2+STR/4
		PvP defense rate = LVL*2+AGI*0.25
		PvP attack rate = LVL*3+AGI*3.5
		HP = 58+(LVL-1)+VIT*2
		Mana = 8+(LVL-1)+ENE*2
		Mana regen = mana/27.5
		SD = (STR+AGI+VIT+ENE)*1.2+defense/2+(LVL*LVL)/30
		AG = ENE*0.15+VIT*0.3+AGI*0.25+STR*0.2
		AG regen = 1.9+AG/33


	//Dark Lord/Lord Emperor

		Min dmg = STR/7+ENE/14
		Max dmg = STR/5+ENE/10
		Speed = AGI/10
		Defense = AGI/6
		PvM defense rate = AGI/7
		PvM attack rate = LVL*5+(AGI*5)/2+STR/6+CMD/10
		PvP defense rate = LVL*2+AGI*0.5
		PvP attack rate = LVL*3+AGI*4
		HP = 50+(LVL-1)*1.5+VIT*2
		Mana = 40+(LVL-1)+(ENE-15)*1.5
		Mana regen = mana/27.5
		SD = (STR+AGI+VIT+ENE+CMD)*1.2+defense/2+(LVL*LVL)/30
		AG = ENE*0.15+VIT*0.1+AGI*0.2+STR*0.3+CMD*0.3
		AG regen = 1.9+AG/33
		Skill % = 200+ENE/20
		Critical dmg = CMD/25+ENE/30
		Fireburst bonus min dmg = 100+STR/25+ENE/50
		Fireburst bonus max dmg = 150+STR/25+ENE/50
		Horse bonus dmg = 100+horseLVL*10+LVL*2.5+STR/10+CMD/5
		Raven speed = 20+(ravenLVL*4)/5+CMD/50
		Raven min dmg = 180+ravenLVL*15+CMD/8
		Raven max dmg = 200+ravenLVL*15+CMD/4
		Guild size = LVL/10+CMD/10


	//Summoner/Bloody Summoner/Dimension Master

		Min wiz dmg = ENE/9
		Max wiz dmg = ENE/4
		Speed = AGI/20
		Defense = AGI/3
		PvM defense rate = AGI/4
		Curse Spell Min dmg = ENE/9
		Curse Spell Max dmg = ENE/4
		Reflect % (self) = 20+ENE/1310
		Reflect % (other) = 20+ENE/1310
		WEAKNESS % = ENE/930+3
		WEAKNESS Time= ENE/500+3
		INNOVATION % = ENE/330+12
		INNOVATION Time = ENE/600+5
		SLEEP % = ENE/370+15
		SLEEP Time = ENE/1500+3
		Berserker % = ENE/60



	//Rage Fighter/FistMaster
		Min dmg = VIT/ 22+STR/10
		Max dmg = VIT/18+STR/8
		Speed = AGI/9
		Defense = AGI/8
		PvP defense rate = (LVL*1.5)+(AGI/5)
		PvP attack rate = LVL*2.6+(AGI*36)/10
		DARK SIDE % = (100 + (AGI/8+ENE/10)) / 100 new
		Dragon Roar % = 50 + (ENE/10))/100 new
		Dragon Slasher PvP % = 50 + (ENE/10))/100 new
		Dragon Slasher PvM % = (50 + (ENE/10))/100) + 100)*3 new
		Chain Drive % = (50 + VIT/10)/100 new


	
};
extern cFormulConfig FormulConfig;

#endif
