#pragma once

#include "stdafx.h"

#if(CUSTOM_POSTITEM)
// -----------------------------------------------------------------------------

#include "linked_list.h"
#include "Protocol.h"
// -----------------------------------------------------------------------------

#define MAX_CHAT_MESSAGE						200
#define pDrawInterface2							((void(__cdecl*)()) 0x00860FC0)
#define oDrawInterface2_Call					0x0080F85B
#define ChatBoxMuObjectChatDataPtrArray         ((MuObjectChatData **) (*(DWORD *) ((*(DWORD *) (0x09867090 + 0x10)) + 0x1C)))
#define ChatBoxMuObjectChatDataPtrFreeSlot      ((MuObjectChatData *)  (*(DWORD *) ((*(DWORD *) (0x09867090 + 0x10)) + 0x20)))
#define ChatBoxMuObjectChatDataPtrLastSlot      ((MuObjectChatData *)  (*(DWORD *) ((*(DWORD *) (0x09867090 + 0x10)) + 0x24)))
#define ChatBoxMuObjectChatDataPtrArrayLength   ((DWORD) (((DWORD) ChatBoxMuObjectChatDataPtrFreeSlot - (DWORD) ChatBoxMuObjectChatDataPtrArray) / sizeof(DWORD)))
#define ChatBoxMuObjectChatDataPtrArraySize		((DWORD) ((((DWORD) ChatBoxMuObjectChatDataPtrLastSlot - (DWORD) ChatBoxMuObjectChatDataPtrArray) / sizeof(DWORD)) + 1))
#define pHandlePacketChatData					((void(__cdecl*)(const void * chat_msg)) 0x0063F850)
// -----------------------------------------------------------------------------

struct PBMSG_CHATPOSTITEM 
{
    PBMSG_HEAD h;
    char character_[10];  //  3
    char message_[89];  //  D
};
// -----------------------------------------------------------------------------

struct PMSG_POSTITEM 
{
    PBMSG_HEAD h;
    char chatid[10];    //  3
    char chatmsg[90];   //  D
    char item_data[107];
};
// -----------------------------------------------------------------------------

__pragma(pack(push, 1))
struct MuObjectChatData 
{
    char * message() {
        if ( is_external_message() ) {
            return long_message_;
        }
        else {
            return short_message_;
        }
    }

    void set_message ( const char * msg ) {
        if ( is_external_message() ) {
            long_message_ = ( char * ) msg;
        }
        else {
            int len = strlen ( msg );
            len = ( len < 16 ) ? len : 15;
            memcpy_s ( short_message_, sizeof ( short_message_ ), msg, len );
            short_message_[len] = '\0';
        }
    }

    unsigned long message_len() { return message_len_; }

    bool is_external_message() { return external_message_ > 0xF; }

  public:
    char unknow1_[4];
    char account_[11];
    char unknow2_[5];
    unsigned long account_len_;
    char unknow3_[8];
    union {
        char short_message_[16];
        char * long_message_;
    };
    unsigned long message_len_;
    unsigned long external_message_;  // >= 0x10
    unsigned long chat_type_;  // [1..9]
    char unknow4_[36];
};
__pragma(pack(pop))
// -----------------------------------------------------------------------------

__pragma(pack(push, 1))
struct MuObjectItemData 
{  //-> Complete (size: 107)
  public:
    unsigned char level() {
        return ( Level >> 3 ) & 0x0F;
    }

  public:
    /*+00*/  short            ItemID;
    /*+02*/  int              Level;
    /*+06*/  char             Unknown6;
    /*+07*/  char             Unknown7;
    /*+08*/  char             Unknown8;
    /*+09*/  short            DamageMin;
    /*+11*/  short            DamageMax;
    /*+13*/  char             Unknown13;
    /*+14*/  short            Unknown14;
    /*+16*/  short            Unknown16;
    /*+18*/  char             Unknown18;
    /*+19*/  char             Unknown19;
    /*+20*/  short            Unknown20;
    /*+22*/  char             Durability;
    /*+23*/  char             ExcellentOption;
    /*+24*/  char             AncientOption;
    /*+25*/  short            ReqStrenght;
    /*+27*/  short            ReqDextirity;
    /*+29*/  short            ReqEnergy;
    /*+31*/  short            ReqVitality;
    /*+33*/  short            ReqCommand;
    /*+35*/  short            ReqLevel;
    /*+37*/  char             SpecialCount;
    /*+38*/  unsigned short   SpecialType[8];
    /*+54*/  unsigned char    SpecialValue[8];
    /*+62*/  int              UniqueID;
    /*+66*/  char             CurrentActiveSlotIndex;
    /*+67*/  char             PosX;
    /*+68*/  char             PosY;
    /*+69*/  unsigned short   HarmonyType;
    /*+71*/  short            HarmonyValue;
    /*+73*/  char             Is380Item;
    /*+74*/  char             SocketOption[5];
    /*+79*/  char             Unknown79;
    /*+80*/  char             SocketSeedIndex[5];
    /*+85*/  char             SocketSphereLevel[5];
    /*+90*/  char             SocketSet;
    /*+91*/  unsigned char    gap01[5];
    /*+96*/  char             DurabilityState;
    /*+97*/  char             PeriodItem;
    /*+98*/  char             ExpiredItem;
    /*+99*/  int              ExpireDateConvert;
    /*+103*/ int              MaybeRefCount;
};
__pragma(pack(pop))
// -----------------------------------------------------------------------------

struct ItemPost : public LinkNode<ItemPost> 
{
  public:
    ItemPost ( void * item_data ) {
        memcpy_s ( &item_, sizeof ( item_ ), item_data, sizeof ( MuObjectItemData ) );
        chat_ = nullptr;
    }
    virtual ~ItemPost() {}

  public:
    MuObjectChatData * chat_;
    MuObjectItemData item_;

  private:
    DISALLOW_COPY_AND_ASSIGN ( ItemPost );
};
// -----------------------------------------------------------------------------

class PostItem 
{
  public:
    PostItem ();
    virtual ~PostItem();

    void Hook();
    bool RecvPostItem ( PMSG_POSTITEM * msg );

    static void PostItemToWorldChatChannel();
    static void PostItemToWorldChatChannelImp ( void * item_data /*, int inv_number*/);
    static void * AddItem ( void * item_data );
    static void BuildChatDataLong();  // long message
    static void BuildChatDataShort();  // short message
    static void BuildChatData ( void * chat_data_pointer );
    static void ProcessCharacterHeadChatText();
    static void ProcessCharacterHeadChatTextImp ( char * base_address, char * chat_text );
    static void ViewPostItem();
    static void ViewPostItemImp ( void * chat_data_pointer );

    int PostItemColor;

  private:
    LinkedList<ItemPost> list_;
    unsigned long list_counter_;

    DWORD last_tickcount_post_;

    void ** current_item_post_;
    DWORD * last_tickcount_view_;

    bool draw_character_head_chat_text_;
    char * draw_character_head_chat_text_base_address_;

}; extern PostItem gPostItem;
// -----------------------------------------------------------------------------
#endif