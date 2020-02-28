#pragma pack(push, 1)

#if(DEV_EFFECT2)



#define pQuickPlayStaticEffect ((int(__cdecl*)(LPVOID Model, int ModelID, int Joint, float size, vec3_t Color, int ObjModel)) 0x565560)//ok sub_565560
#define pAllowPlayEffect ((void(__thiscall*)(LPVOID This, vec3_t Bone1, int lpModel, signed int joint, int a5)) 0x544E60)
#define oUserPreviewStruct *(int*)0x7BC4F04
//#define pSetItemEffect ((void(__cdecl*)(int lpModel, int ItemID, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int a10, int a11, int RenderType)) 0x00609E70)z
//#define pModelThis ((LPVOID(*)())0x004CDA10)//ok
//#define pGetModel ((LPVOID(__thiscall*)(LPVOID This, signed int a2)) 0x00969C50)//ok

// -------------------


#define pSetItemEffect	((void(__cdecl*)(int lpModel, int ItemID, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int Arg7, int Arg8, int RenderType)) 0x609E70)
#define pModelThis	((LPVOID(*)())0x4CDA10)
#define pGetModel ((LPVOID(__thiscall*)(LPVOID This, signed int a2)) 0x969AD0)

// ===================================

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
//Main 1.04C: 0x8905508
//Main 1.04D/1.04E: 0x8907508
//#define CreateEffect ((void(__cdecl*)(int Type, vec3_t a5, vec3_t Angle, vec3_t Light, int SubType, int Owner, short PKKey, BYTE Skill, float Scale, BYTE SkillSerial, vec3_t SkillAngle, BYTE SkillHotKey))0x6D9070)
#define CreateEffect ((void(__cdecl*)(int Type, vec3_t a5, vec3_t Angle, vec3_t Light, int SubType, int Owner, short PKKey, BYTE Skill, float Scale, BYTE SkillSerial, vec3_t SkillAngle, BYTE SkillHotKey))0x6D8F20)


class cCreateEffect
{
public:
	void Load();
	int DynamicEffectEx(DWORD ModelID, vec3_t VecPos, vec3_t WorldPos, vec3_t Color, int SubEffectID, float Scale, ObjectModel* lpModel);
};
extern cCreateEffect gCreateEffect;

#endif