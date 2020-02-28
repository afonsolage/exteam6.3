#include "stdafx.h"

#if(exCHATWND)

#if(v103K)
#define oGetDisplayMsgType		0x6F7FE0 
#define oSetDisplayMsgType		0x6F7F95
#define oShowChatMsgs			0x6F5584
#define oShowChatMsgsCall_Hook  0x6F7927
#define oNewCallChat			0x8510BA
#define oFixSysMsg1_Hook		0x6F60AC    
#define oFixSysMsg1_TRUE		0x6F6165
#define oFixSysMsg2_Hook		0x6F63B3
#define oFixSysMsg2_TRUE		0x6F64B6
#define oFixSysMsg3_Hook		0x6F6715
#define oFixSysMsg3_TRUE		0x6F67DA
#endif

#if(v103Y)

#define oGetDisplayMsgType		0x0072F794 
#define oSetDisplayMsgType		0x0072F749
#define oShowChatMsgs			0x0072CD38
#define oShowChatMsgsCall_Hook  0x0072F0DB
#define oNewCallChat			0x008C81C5
#define oFixSysMsg1_Hook		0x0072D860    
#define oFixSysMsg1_TRUE		0x0072D919
#define oFixSysMsg2_Hook		0x0072DB67
#define oFixSysMsg2_TRUE		0x0072DC6A
#define oFixSysMsg3_Hook		0x0072DEC9
#define oFixSysMsg3_TRUE		0x0072DF8E

//#define GetDisplayMsgType = 0x0072F794;
//#define SetDisplayMsgType = 0x0072F749;
//#define ShowChatMsgs = 0x0072CD38;
//#define ShowChatMsgsCall_Hook = 0x0072F0DB;
//#define NewCall = 0x008C81C5;
//#define FixSysMsg1_Hook = 0x0072D860;
//#define FixSysMsg1_FALSE = FixSysMsg1_Hook+5; 
//#define FixSysMsg1_TRUE = 0x0072D919;
//#define FixSysMsg2_Hook = 0x0072DB67;
//#define FixSysMsg2_FALSE = FixSysMsg2_Hook+5; 
//#define FixSysMsg2_TRUE = 0x0072DC6A;
//#define FixSysMsg3_Hook = 0x0072DEC9;
//#define FixSysMsg3_FALSE = FixSysMsg3_Hook+5; 
//#define FixSysMsg3_TRUE = 0x0072DF8E;
#endif

const int GetDisplayMsgType = oGetDisplayMsgType;  
const int SetDisplayMsgType = oSetDisplayMsgType;
const int ShowChatMsgs = oShowChatMsgs;
const int ShowChatMsgsCall_Hook = oShowChatMsgsCall_Hook;
const int NewCallChat = oNewCallChat;
const int FixSysMsg1_Hook = oFixSysMsg1_Hook;      
const int FixSysMsg1_FALSE = FixSysMsg1_Hook+5; 
const int FixSysMsg1_TRUE = oFixSysMsg1_TRUE;
const int FixSysMsg2_Hook = oFixSysMsg2_Hook;
const int FixSysMsg2_FALSE = FixSysMsg2_Hook+5; 
const int FixSysMsg2_TRUE = oFixSysMsg2_TRUE;
const int FixSysMsg3_Hook = oFixSysMsg3_Hook;
const int FixSysMsg3_FALSE = FixSysMsg3_Hook+5; 
const int FixSysMsg3_TRUE = oFixSysMsg3_TRUE;



void ChatWndHooks(); 


#endif