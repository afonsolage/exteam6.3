#pragma once

#if(DEV_EFFECT)

#pragma pack(push, 1)
struct DYNAMIC_EFFECT_INFO    //(size: 132)
{
    /*+0*/  bool    Enable; //int
    BYTE gap1[3];
    /*+4*/  DWORD    EffectID;
    /*+8*/  DWORD    TextureID;
    /*+12*/  int  SubEffectID;
    /*+16*/  float    Scale;
    /*+20*/  VAngle    VecPos;
    /*+32*/  VAngle    WorldPos;
    /*+44*/  VAngle    Color;
    /*+56*/  float    Unknown56; //Alpha
    /*+60*/  DWORD    Unknown60;
    /*+64*/  ObjectModel    * m_Owner;
    /*+68*/  float    Unknown68; //
    /*+72*/  DWORD    Unknown72;
    /*+76*/  BYTE    Unknown76; //int
    BYTE Gap01[3];
    /*+80*/  float    Unknown80;
    /*+84*/  VAngle    Unknown84;
    /*+96*/  VAngle    Color2;
    /*+108*/    VAngle    VecPos2;
    BYTE Gap02[12];
};
#pragma pack(pop)

class cEffect 
{
public:
	void Load();
	static int DynamicEffectEx(DWORD ModelID, vec3_t VecPos, vec3_t WorldPos, vec3_t Color, int SubEffectID, float Scale, ObjectModel* lpModel);
};

extern cEffect  gEffect;

#endif