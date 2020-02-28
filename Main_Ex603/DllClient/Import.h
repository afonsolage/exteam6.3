#pragma once

#define oNpcName				0x8119F68
#define pSendChatSay			((int(__cdecl*)(char * Name, char * Text, lpViewObj lpObject, int Type, int NameColor)) 0x5996A0)
#define pShowMonster			((double(__cdecl*)(int MonsterID, int X, int Y, int a4)) 0x580FC0)

#define pGetTextLine			((char*(__thiscall*)(LPVOID This, int LineNumber)) 0x402320)
#define pTextLineThis			((LPVOID(*)()) 0x8128ADC)
#define pMapName				((char*(__cdecl*)(signed int mapNumber)) 0x5D2C10)
#define pDrawMapObject			((void(__cdecl*)(DWORD, float, float, float, float, float, float, float, float, float, float, float, float, DWORD)) 0x638400)


//->Other
#define VIRTUAL_ADDRESS			0x00402F4A
#define pPlayerState			*(int*)0x0E609E8
#define IP_ADDRESS				0x00E611B2
#define SERIAL_MAIN				0x0E61F70
#define VERSION_MAIN			0x0E61F68
#define pGameWindow				*(HWND*)0x0E8C578
// ----------------------------------------------------------------------------------------------

//Game Windows
#define pGameLoad				((int(__cdecl*)()) 0x004D0FC0)
#define pGameResolutionMode		*(int*)0x0E8C240
#define pWinWidth				*(GLsizei*)0x0E61E58
#define pWinHeight				*(GLsizei*)0x0E61E5C
#define pWinFontHeight			*(int*)0x81C0380//
#define pWinWidthReal			*(float*)0xE7C3D4
#define pWinHeightReal			*(float*)0xE7C3D8
#define pMoveListInit			((void(__thiscall*)(LPVOID This, int Arg1, int Arg2)) 0x830AC0)
#define oWindowsProc			(0x004D0E14+3)
#define pWindowsProc			((WNDPROC(__stdcall*)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)) 0x4D0030)
// ----------------------------------------------------------------------------------------------

#define oCam_Zoom				0x0D27BFC	//1037DB0
#define oCam_PosZ				0x0D255AC	//1031A64
#define oCam_RotZ				0x87933D8	//8B4ACC8
#define oCam_RotZDef			0x0D27B78	//1033AB0
#define oCam_RotY				0x0D27B88	//1033AC0
#define oCam_PosZDef			0x0D255AC	// Restore PosZ
#define oCam_PosZ				0x0D255A0	// PosZ
#define oCam_ClipX				0x0D2C848	//1038D28
#define oCam_ClipY				0x0D2C894	//1033A78
#define oCam_ClipZ				0x0D2C8B8	//1038D78
#define oCam_ClipXCS			0x0D2C898	//1038D58
#define oCam_ClipYCS			0x0D2C8A8	//1038D68
#define oCam_ClipX2				0x0D2C878	//1038D38
#define oCam_ClipY2				0x0D2C880	//1038D40
#define oCam_ClipZ2				0x0D2B94C	//1037DA4
#define oCam_ClipGL				0x0D2570C	//1031BCC
#define oCam_Clip1				0x00D27BCC
#define oCam_Clip2				0x00D2C8A8
// ----------------------------------------------------------------------------------------------

//->Grafics
#define pSelectDraw				((int(__cdecl*)(DWORD)) 0x0041FE10)
#define oSelectDraw_Call		0x00405A32
#define pFpsTime1				*(int*)0x0E8CB30
#define pFpsTime2				*(int*)0x0E8CB50
// --------------------------------------------------------------------------------------------

//->Chat
#define oNewCall				0x009CFF45
#define oFixSysMsg1_Hook		0x00789617
#define oFixSysMsg1_TRUE		0x007896D4
#define oFixSysMsg2_Hook		0x00789913
#define oFixSysMsg2_TRUE		0x00789A0A
#define oFixSysMsg3_Hook		0x00789C5C
#define oFixSysMsg3_TRUE		0x00789D1F
#define oShowChatMessage_Call	0x0078AF6C
#define pWhisperChatRecv		((void(__cdecl*)(CHAT_WHISPER_EX * pRequest)) 0x006400C0)
#define pShowChatMessage		((bool(__thiscall*)(LPVOID This)) 0x00788930)
#define pSetChatMessageType		((int(__thiscall*)(LPVOID This, int Type)) 0x0078B720)
#define oWhisperChat_Call		0x00663F9E
// --------------------------------------------------------------------------------------------

//->Reconnect
#define pOnLine					*(DWORD*)0x8793704
#define pPartyMemberCount		*(DWORD*)0x81F6B6C
#define oGetAccountInfo			0x0040B903
#define oDisconnectEvent		0x004D035A
#define oMenuExit				0x007A889B
#define pPShopThis1				((LPVOID(__cdecl*)()) 0x860FC0)
#define pPShopThis2				((LPVOID(__thiscall*)(LPVOID This)) 0x8612B0)
#define pPShopSet				((void(__thiscall*)(LPVOID This, BYTE Mode)) 0x840E20)
#define pPShopRefresh			((void(__cdecl*)(int Preview)) 0x00668460)
// --------------------------------------------------------------------------------------------

//->Interface
#define pDrawLogoDraw			((char(__cdecl*)()) 0x4D7970)
#define oDrawLogoDraw_Call		0x004DA2AC
#define oDrawInterface_Call		0x0080F6AE
#define oLoadSomeForm_Call		0x00776D5E
#define pDrawInterface			((void(__cdecl*)()) 0x0080F790)
#define pLoadImage				((int(__cdecl*)(char * Folder, int Code, int Arg3, int Arg4, int Arg5, int Arg6)) 0x007721E0)
#define pLoadSomeForm			((void(__cdecl*)()) 0x00777440)
#define pWindowThis				((LPVOID(*)()) 0x860FC0)
#define pCheckWindow			((bool(__thiscall*)(LPVOID This, int Code)) 0x0085EAD0)
#define pDrawGUI				((void(__cdecl*)(DWORD, float, float, float, float)) 0x00790A00)
#define pDrawColorText			((int(__cdecl*)(LPCTSTR Text, int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align)) 0x7D0380)
#define pDrawToolTip			((int(__cdecl*)(int X, int Y, LPCSTR Text)) 0x00597220)
#define pDrawColorButton		((void(__cdecl*)(DWORD, float, float, float, float, float, float, DWORD)) 0x00790DD0)
#define pDrawExtraColor			((void(__cdecl*)(DWORD, float, float, float, float, float, float, float, float, DWORD)) 0x637A60)
#define	pCursorX				*(int*)0x879340C
#define	pCursorY				*(int*)0x8793410
#define pSetCursorFocus			*(DWORD*)0xE8CB3C
#define pAllowGUI				((bool(__cdecl*)()) 0x7D4100)
#define oAllowGUI_Call1			0x007D363E
#define oAllowGUI_Call2			0x00811AF2
#define NEWUI_BAR_SWITCH01		0x7A65
#define NEWUI_BAR_SWITCH02		0x7A66
#define pMakeColor				((DWORD(__cdecl*)(BYTE, BYTE, BYTE, BYTE)) 0x00412D20)
#define MAX_OBJECT				1000
#define MAX_WIN_WIDTH			640
#define MAX_WIN_HEIGHT			480
#define pOpenWindow				((int(__thiscall*)(LPVOID This, int Code)) 0x0085EB00)
#define pCloseWindow			((int(__thiscall*)(LPVOID This, int Code)) 0x0085F850)

#define pDrawGUFULL				((int(__cdecl*)(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)) 0x637C60)
#define pDrawButton				((void(__cdecl*)(DWORD, float, float, float, float, float, float)) 0x00790CF0)

#define pGetMoneyFormat			((int(__cdecl*)(double Value, char * Buff, int Arg3)) 0x5C1170)
#define MAX_BUFF_INDEX			255

#define pCashShopCheck			((char(*)())0x944CD0)
#define pCashShopThis			((LPVOID(*)())0x93F220)
#define pCashShopCheck2			((bool(__thiscall*)(LPVOID This))0x93FB20)
#define pCashShopCheck3			((char(__thiscall*)(LPVOID This))0x93F4B0)
//bool __thiscall sub_93FB90(int this)
#define sub_93FB90				((bool(__thiscall*)(LPVOID This))0x93FB90)
//char __thiscall sub_93F7E0(int this)
#define sub_93F7E0				((char(__thiscall*)(LPVOID This))0x93F7E0)
//int __thiscall sub_940EB0(int this)
#define sub_940EB0				((LPVOID(__thiscall*)(LPVOID This))0x940EB0)
//int __thiscall sub_940E80(int this)
#define sub_940E80				((LPVOID(__thiscall*)(LPVOID This))0x940E80)
//char __thiscall sub_811A60(char *this)
#define sub_811A60				((char(__thiscall*)(char* This))0x811A60)
//int __thiscall sub_861090(int this)
#define sub_861090				((int(__thiscall*)(LPVOID This))0x861090)
//int __thiscall sub_814FE0(char *this, int a2, char a3)
#define sub_814FE0				((int(__thiscall*)(char* This, int a2, char a3))0x814FE0)

#define pGetTextNumber			((int(__cdecl*)(int a1))0x009CFF45)	


#define FULL_X_IN_GAME_X(x)		 ( ( MAX_WIN_WIDTH * x ) / pWinWidth )
#define FULL_Y_IN_GAME_Y(y)		 ( ( MAX_WIN_HEIGHT * y ) / pWinHeight )

#define GAME_X_IN_FULL_X(x)		 ( ( pWinWidth * x ) / MAX_WIN_WIDTH )
#define GAME_Y_IN_FULL_Y(y)		 ( ( pWinHeight * y ) / MAX_WIN_HEIGHT )


#define pGLEnable				((void(__cdecl*)()) 0x637A30)
#define pSetBGColor				((int(__thiscall*)(LPVOID This, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)) 0x4200B0)

// --------------------------------------------------------------------------------------------

//->Item

#define oLoadModel				0x00633FCB
#define oLoadTexture			0x00633FE3
#define pInitModelData			((void(__cdecl*)()) 0x00617D30)
#define pInitTextureData		((void(__cdecl*)()) 0x0061AED0)	
#define pLoadModel				((void(__cdecl*)(DWORD ResourceID, char * Path, char * File, int Arg4)) 0x00614D10)
#define pLoadTexture			((void(__cdecl*)(int TextureID, char * Folder, int GLREPEAT, int GLNEAREST, int GLTRUE)) 0x614710)
#define ITEM_INTER				1171
#define ITEM(x, y)				((x * 512) + y)
#define ITEM2(x, y)				((x * 512) + y + ITEM_INTER)
#define oItemName				*(DWORD*)(0x8128AC0 + 84)
#define pAllowStaticEffect		((void(__thiscall*)(LPVOID This, DWORD * Arg1, DWORD Arg2, int Arg3, int Arg4)) 0x544E60)
#define pPlayStaticEffect		((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, float Scale, float * Color, int Model, float a6, int a7)) 0x7711C0)
#define pPlayDynamicEffect		((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, int Arg2, float * Color, int Arg4, float Arg5, int Arg6)) 0x74CBE0)
#define pIsWings				((int(__thiscall*)(LPVOID This, DWORD ItemID)) 0x7E7720)
#define pIsUpgradeItem			((bool(__thiscall*)(LPVOID This, ObjectItem * lpSource, ObjectItem * lpTarget)) 0x7DD970)
#define pAllowRepairWings		((bool(__cdecl*)(ObjectItem * lpItem)) 0x5C9DA0)
#define pSetItemOption			((void(__cdecl*)(ObjectItem * lpItem, BYTE Option, BYTE Special, BYTE Value)) 0x58B910)
#define pSetItemEffect			((void(__cdecl*)(int Arg1, int ModelID, VAngle Angle, int Arg4, int ItemLevel, char Arg6, int Arg7, int Arg8, int Arg9)) 0x609E70)
#define pGetMaxDurability		((short(__cdecl*)(ObjectItem * lpItem, int ScriptStruct, int Level)) 0x5C2170)
#define OriginalGlow			((signed int (__cdecl *)(DWORD, DWORD, DWORD, FRGB&, BYTE)) 0x5F8C50)
#define pShowPrice				((int(*)(int a1, const char *a2, ...)) 0x9CF52A)
#define pSetItemPrice           ((__int64(__cdecl*)(ObjectItem * lpItem, int Mode)) 0x58E3B0)
#define pSetItemTextLine		((void(__cdecl*)(int Line, LPSTR Text, ...)) 0x9CF52A)
#define pSetItemOptionText		((void(__cdecl*)(int ItemID, int Line, WORD OptionID, BYTE Arg4, int Arg5)) 0x5C2F70)

#define pCustomEffGet                   ((int(__thiscall*)(int This, int a2, int *a3, MU3Float *a4, char a5)) 0x00545030)
// ----------------------------------------------------------------------------------------------

//->Protocol
#define oXORFilterStart			0x00404C99
#define oDataRecv_Call			0x0065FD79	
#define pDataRecv				((void(*)(DWORD Type, LPBYTE Data, int Len, int aIndex)) 0x006639D0)
#define pActiveSocket			*(SOCKET*)(*(DWORD*)0x0E61F84 + 0x0c)
#define PROTOCOL_MOVE			0xD4
#define PROTOCOL_POSITION		0x15
#define PROTOCOL_ATTACK			0x11
#define PROTOCOL_BEATTACK		0xDB
#define SET_NUMBERH(x)			( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x)			( (BYTE)((DWORD)(x) & 0xFF) )
#define SET_NUMBERHW(x)			( (WORD)((DWORD)(x)>>(DWORD)16) )
#define SET_NUMBERLW(x)			( (WORD)((DWORD)(x) & 0xFFFF) )
#define SET_NUMBERHDW(x)		( (DWORD)((unsigned __int64)(x)>>(DWORD)32) )
#define SET_NUMBERLDW(x)		( (DWORD)((unsigned __int64)(x) & 0xFFFFFFFF) )
#define MAKE_NUMBERW(x,y)		( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )
#define MAKE_NUMBERQW(x,y)		( (unsigned __int64)(((DWORD)((y)&0xFFFFFFFF)) | ((DWORD)((x)&0xFFFFFFFF)<<32))  )
#define MAKE_NUMBERDW(x,y)		( (DWORD)(((WORD)((y)&0xFFFF)) | ((WORD)((x)&0xFFFF)<<16))  )
#define MAKEQWORD(a, b)			((__int64)(((DWORD)((__int64)(a) & 0xffffffff)) | ((__int64)((DWORD)((__int64)(b) & 0xffffffff))) << 32))  
#define LODWORD(h)				((DWORD)(__int64(h) & __int64(0xffffffff)))   
#define HIDWORD(h)				((DWORD)(__int64(h) >> __int64(32)))
#ifdef VIEW_MONSTER
#if(ENABLE_DEV)
#define MAX_VIEWPORT			400
#else
#define MAX_VIEWPORT			75
#endif
#else
#define MAX_VIEWPORT			75
#endif
// --------------------------------------------------------------------------------------------

//->User
#define MAX_CHARACTER_LEVEL     400
#define pDrawInterfaceNumBer   ((double(__stdcall*)(float X, float Y, int num, float size)) 0x00854E90) //00854E90  /$ 55             PUSH EBP
#define MAIN_SCREEN_STATE        0x0E609E8
#define MAIN_CHARACTER_STRUCT   0x8128AC8


#define pPlayerState			*(int*)0x0E609E8
#define pMapNumber				*(int*)0x0E61E18
#define pIsMaster				((bool(__cdecl*)(BYTE Class)) 0x5878E0)
#define oUserObjectStruct		*(int*)0x8128AC8
#define oUserObjectStruct_		*(int*)0x8128AC4
#define pUserObjectStruct		&*(ObjectCharacter*)oUserObjectStruct
#define oUserPreviewStruct		*(int*)0x7BC4F04
#define pGameIndex				*(DWORD*)0x87935A8
#define oIsBattleServer_Call1	0x005D303A
#define oIsBattleServer_Call2	0x00831501
#define pPreviewCharSet			((void(__cdecl*)(int ObjectIndex, BYTE * CharSet, lpViewObj Object, int Mode)) 0x57FD90)
#define pGetMapName				((char*(__cdecl*)(int MapNumber)) 0x5D2C10)
// --------------------------------------------------------------------------------------------

//->Hp Bar
#define oNpcName				0x8119F68
#define pPartyListStruct        *(PartyList*)0x81CB4E8
#define pGetPreviewStruct        ((DWORD(__thiscall*)(LPVOID This, int ViewportID)) 0x96A340)
#define pPreviewThis            ((LPVOID(*)()) 0x402BC0)
#define pGetPosFromAngle        ((void(__cdecl*)(VAngle * Angle, int * PosX, int * PosY)) 0x635B00)
#define pSetTextColor            ((void(__thiscall*)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h)) 
#define pTextThis                ((LPVOID(*)()) 0x0041FE10)
#define pDrawText                ((int(__thiscall*)(LPVOID This, int PosX, int PosY, char * Text, int Arg4, int Arg5, int * Arg6, int Arg7)) 0x00420150)
#define pSetBlend                ((void(__cdecl*)(BYTE Mode)) 0x635FD0)
#define pDrawBarForm            ((void(__cdecl*)(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)) 0x6378A0)
#define pGLSwitchBlend            ((void(__cdecl*)()) 0x636070)
#define pGLSwitch                ((void(__cdecl*)()) 0x635F50)
#define	pViewAttackTargetID		*(int*)0xE61730
#define CheckBattleCursor        ((bool(__cdecl*)()) 0x59A8B0)

//->Sound
#define pLoadWavSound            ((int(__cdecl*)(int SoundID,char * Folder,int Arg3,bool State))0x006D66B0)
#define pPlayWavSound            ((int(__cdecl*)(int SoundID,int Arg2,int Arg3))0x006D6AD0)

//00788E1C;00788A1E - росто€ние между строками чата

//00788F96 - рисуетс€ текст логов
//00788F54 - рисует золотой чат
//00788D64 - цвет золотого чата
//00788D46 - цвет фона золотого чата



//00788D41 - перехват и проверка

//78BF00 - функци€ возвращ€ет код цвета

// EBP 0x0018E4B8
// 00995637

//00788DD9 - прыгает если нет данной категории



/*
	00788D5D      68 FF000000   PUSH 0FF	-насышенность
	00788D62      68 FF000000   PUSH 0FF	-синий
	00788D67      6A 00         PUSH 0		-зеленый
	00788D69      68 FF000000   PUSH 0FF	-красный
*/

#define oVulcanusMove			(0x00831A5C + 2)
// --------------------------------------------------------------------------------------------

//->Visual Fix
#define oDrawDamageHP			0x006443F1	//Done
#define oDrawDamageSD			0x00644465	//Done
#define oDrawHp					0x0080FDD8	//Done
#define oDrawMp					0x0080FF6B	//Done
#define oDrawAg					0x00810239	//Done
#define oDrawSd					0x00810509	//Done
#define oDrawTabHP				0x0080FE57	//Done			
#define oDrawTabMP				0x0080FFEA	//Done	
#define oDrawTabSD				0x0081059A	//Done
#define oDrawTabAG				0x008102B8	//Done
#define oInfoHp					0x00782C93	//Done	
#define oInfoHpM				0x00782CC9	//Done
#define oInfoMp					0x0078306C	//Done
#define oInfoMpM				0x007830A3	//Done
#define oInfoPoint				0x0077FC06	//Done
#define oDrawCircleHp			0x0080FD06
#define oDrawCircleHp2			0x0080FD9F	//Done
#define oDrawCircleMp			0x0080FF33	//Done	
#define oDrawCircleAg			0x00810204	//Done	
#define oDrawCircleSd			0x008104D4	//Done
#define ModelID_HP				0x7A41	//Done
#define ModelID_HP2				0x7A42	//Done
#define ModelID_MP				0x7A40	//Done
#define ModelID_AG				0x7A43	//Done
#define ModelID_SD				0x7A44	//Done
#define pDrawDamage				((void(__cdecl*)(int a1, int a2, int a3, float a4, char a5, char a6)) 0x770B50)
#define pDrawBar				((double(__cdecl*)(float a1, float a2, int a3, float a4)) 0x790EB0)
#define pDrawTab				((int(__cdecl*)(signed int a1, signed int a2, LPCSTR lpMultiByteStr)) 0x597220)
#define pInfo					((int(*)(int a1, const char *a2, ...)) 0x50D100)
#define pDrawCircle				((void(__cdecl*)(DWORD ModelID, float Arg2, float Arg3, float Arg4, float Arg5, float Arg6, float Arg7, float Arg8, float Arg9, bool Arg10, bool Arg11, float Arg12)) 0x637C60)
#define pUserStat				((LPVOID(*)()) 0x588D70)
#define pUpdateUserStat			((void(__thiscall*)(LPVOID This, int Value, int Code)) 0x4EA460)
// --------------------------------------------------------------------------------------------

// -> Interface draw Item 
#define pDrawItemModel			((int(__cdecl*)(float PosX, float PosY, float Width, float Height, int ItemID, int a6, int a7, float a8, char a9)) 0x5CF310)
#define sub_636720_Addr ((int(*)())0x636720)
#define sub_6363D0_Addr ((void(__cdecl*)(GLint x, int a2, GLsizei width, GLsizei height)) 0x6363D0)
#define sub_6358A0_Addr ((int(__cdecl*)(float a1, float a2, float a3, float a4)) 0x6358A0)
#define sub_635830_Addr ((void(__cdecl*)(LPVOID a1)) 0x635830)
#define sub_635DE0_Addr ((void(*)()) 0x635DE0)
#define sub_635E40_Addr ((void(*)()) 0x635E40)
#define sub_637770_Addr ((void(*)()) 0x637770)
#define MAIN_RESOLUTION_X	0x00E61E58
#define MAIN_RESOLUTION_Y	0x00E61E5C
#define pGetItemBmdStruct(ItemId)   (ItemBmdStruct*)(*(DWORD*)0x8128AC0 + sizeof(ItemBmdStruct) * ItemId)
#define SET_ITEMOPT_LEVEL(x)  (x << 3)
// ----------------------------------------------------------------------------------------------
/*
005528E8 - dl ref
JNE SHORT 005528F5
JMP 00552CD8
*/