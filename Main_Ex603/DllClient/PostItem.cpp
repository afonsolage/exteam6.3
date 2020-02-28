#include "stdafx.h"
#include "Object.h"
#include "PostItem.h"
#include "Interface.h"
#include "Protocol.h"
#include "TMemory.h"
#include "ExText.h"
#include <string>
#include "Item.h"
#include "Console.h"
#include "PersonalShopEx.h"
#include "DeBug.h"
#include "DeBug.h"
// -----------------------------------------------------------------------------

#if(CUSTOM_POSTITEM)

PostItem gPostItem;
#define pCurrentViewingItemName (*(DWORD *) (0x007E43D8 + 2))
#define CharacterHeadChatTextFirst(x) ((char *) ((x) + 0x194))
#define CharacterHeadChatTextLast(x) ((char *) ((x) + 0x194 - 0x100))
// -----------------------------------------------------------------------------

PostItem::PostItem () 
{
    list_counter_ = 0;
    last_tickcount_post_ = 0;
    current_item_post_ = &gInterface.item_post_;
    last_tickcount_view_ = &gInterface.last_tickcount_view_;
    draw_character_head_chat_text_ = false;
    PostItemColor = 7;//GetPrivateProfileInt ( "PostItem", "Color", 9, ".\\config.ini" );

    if(PostItemColor < 1 || PostItemColor > 9) 
	{ 
		PostItemColor = 7;
	}

    Hook();
}
// -----------------------------------------------------------------------------

PostItem::~PostItem() 
{
}
// -----------------------------------------------------------------------------

void PostItem::Hook() 
{
    SetOp((LPVOID)0x007DCE80, PostItemToWorldChatChannel, ASM::JMP); // On mouse over item
    SetOp((LPVOID)0x00789677, BuildChatDataLong, ASM::JMP);
    SetOp((LPVOID)0x0078A956, ViewPostItem, ASM::JMP);

	SetRange( ( LPVOID ) 0x00599183, 6, ASM::NOP );
	SetOp( ( LPVOID ) 0x00599183, ProcessCharacterHeadChatText, ASM::JMP);
}
// -----------------------------------------------------------------------------

bool PostItem::RecvPostItem(PMSG_POSTITEM * msg) 
{
    void * item_post = PostItem::AddItem ( &msg->item_data[0] );

    if ( item_post == nullptr ) { return false; }

    char Name[11] = { '\0' };
    char Messase[91] = { '\0' };
    char Messase_API[70] = { '\0' };
    memcpy_s ( &Name[0], 10, &msg->chatid[0], 10 );
    memcpy_s ( &Messase[0], 90, &msg->chatmsg[0], 90 );
    int len = strlen ( Messase );
    // ----
    // Cắt text Excillent

    if ( ( BYTE ) Messase[0] == 0xC4 &&
            ( BYTE ) Messase[1] == 0x90 &&
            ( BYTE ) Messase[2] == 0xE1 &&
            ( BYTE ) Messase[3] == 0xBB &&
            ( BYTE ) Messase[4] == 0x93 &&
            ( BYTE ) Messase[5] == 0x20 &&
            ( BYTE ) Messase[6] == 0x68 &&
            ( BYTE ) Messase[7] == 0x6F &&
            ( BYTE ) Messase[8] == 0xC3 &&
            ( BYTE ) Messase[9] == 0xA0 &&
            ( BYTE ) Messase[10] == 0x6E &&
            ( BYTE ) Messase[11] == 0x20 &&
            ( BYTE ) Messase[12] == 0x68 &&
            ( BYTE ) Messase[13] == 0xE1 &&
            ( BYTE ) Messase[14] == 0xBA &&
            ( BYTE ) Messase[15] == 0xA3 &&
            ( BYTE ) Messase[16] == 0x6F &&
            ( BYTE ) Messase[17] == 0x20 ) {
        strcpy_s ( &Messase[0], 91, &Messase[18] );
    }

    // ----
    // Cắt bớt tên item nếu quá dài
    if ( len > 35 ) {
        for ( int i = 30; i < len; ++i ) {
            if ( isalpha ( Messase[i] ) || Messase[i] == ' ' ) {
                Messase[i] = '.';
                Messase[i + 1] = '.';
                Messase[i + 2] = '.';
                Messase[i + 3] = '\0';
            }
        }
    }
	//рисует чат над головой
    sprintf_s ( Messase_API, "%s %s_[%08X]", g_ExText.GetText(121), Messase, ( DWORD ) item_post );
    gPostItem.draw_character_head_chat_text_ = true;
    Interface::DrawChat ( gPostItem.PostItemColor, &Name[0], &Messase_API[0] );
    // ----

    if ( !gPostItem.draw_character_head_chat_text_ ) { // đã lấy được base_address
        // xử lý đoạn chat trên đầu nhân vật
        char message[256] = { 0 };
        char * chat_text_first = CharacterHeadChatTextFirst ( gPostItem.draw_character_head_chat_text_base_address_ );
        char * chat_text_last = CharacterHeadChatTextLast ( gPostItem.draw_character_head_chat_text_base_address_ );
        unsigned long msgfirst_len = strlen ( chat_text_first );
        unsigned long msglast_len = strlen ( chat_text_last );
        strcpy_s ( message, sizeof ( message ), chat_text_first );
        strcat_s ( message, chat_text_last );
        unsigned long message_len = strlen ( message );

        if ( message[message_len - 1 - 8 - 2] != '_' ||
                message[message_len - 1 - 8 - 1] != '[' ||
                message[message_len - 1] != ']' ) {
        }
        else {
            message[message_len - 1 - 8 - 2] = '\0';  // cắt bỏ đoạn đuôi

            // copy lại
            if ( msgfirst_len ) {
                memcpy_s ( chat_text_first, 0x80, message, msgfirst_len );
                chat_text_first[msgfirst_len] = '\0';
            }

            if ( msglast_len ) {
                memcpy_s ( chat_text_last, 0x80, &message[msgfirst_len], msglast_len );
                chat_text_last[msglast_len] = '\0';
            }
        }
    }

    return true;
}

// -----------------------------------------------------------------------------
void __declspec ( naked ) PostItem::PostItemToWorldChatChannel() {
    static DWORD register_ecx = 0;
    static DWORD register_edx = 0;
    static DWORD mem = 0;

    _asm {
        MOV register_ecx, ECX;
        MOV register_edx, EDX;
        MOV ECX, DWORD PTR SS : [EBP - 0x10];
        MOV EDX, DWORD PTR DS : [ECX + 0x54];
        MOV mem, EDX;
    }
    PostItemToWorldChatChannelImp ( ( void * ) mem);
    _asm {
        MOV ECX, register_ecx;
        MOV EDX, register_edx;
        MOV mem, 0x007DCF4D;
        JMP mem;
    }
}

// -----------------------------------------------------------------------------

#define p0x599F10			((int(*)())0x599F10)	

void PostItem::PostItemToWorldChatChannelImp ( void * item_data ) 
{
    // check window, not allow for shop, inventory, warehouse, etc
    if ( gInterface.CheckWindow ( Trade ) ||
            gInterface.CheckWindow ( Warehouse ) ||
            gInterface.CheckWindow ( Shop ) ||
            gInterface.CheckWindow ( Store ) ||
            gInterface.CheckWindow ( OtherStore ) ||
            gInterface.CheckWindow ( CashShop ) ||
            gInterface.CheckWindow ( ExpandWarehouse ) ) {
        return;
    }

    if ( GetTickCount() <= gPostItem.last_tickcount_post_ + 2000 ) { return; }

    if ( GetKeyState ( VK_RBUTTON ) & 0x8000 && GetKeyState ( VK_CONTROL ) & 0x8000 ) {
        PMSG_POSTITEM iMsg = { '\0' };
        strcpy_s ( iMsg.chatmsg, ( char* ) pCurrentViewingItemName );
        memcpy_s ( &iMsg.chatid[0], 10, ( char* ) oUserObjectStruct_, 10 );
        memcpy_s ( &iMsg.item_data[0], 107, item_data, 107 );
        iMsg.h.set ( ( LPBYTE ) &iMsg, 0x78, sizeof ( iMsg ) );
        gProtocol.DataSend ( ( LPBYTE ) &iMsg, iMsg.h.size );
        gPostItem.last_tickcount_post_ = GetTickCount();
    }
}
// -----------------------------------------------------------------------------

void * PostItem::AddItem ( void * item_data ) {
    LinkNode<ItemPost> * item = new ItemPost ( item_data );
    gPostItem.list_.Append ( item );

    if ( gPostItem.list_counter_ >= MAX_CHAT_MESSAGE ) {
        LinkNode<ItemPost> * node = gPostItem.list_.head();
        node->Free();
    }
    else {
        gPostItem.list_counter_++;
    }

    return item;
}
// -----------------------------------------------------------------------------

void __declspec ( naked ) PostItem::BuildChatDataLong() {
    static void * chat_data_pointer = nullptr;
    static DWORD mem = 0;
    _asm {
        MOV chat_data_pointer, ECX;
        MOV mem, 0x0078BE90;
        CALL mem;
    }
    BuildChatData ( chat_data_pointer );
    _asm {
        MOV mem, 0x0078967C;
        JMP mem;
    }
}
// -----------------------------------------------------------------------------

void __declspec ( naked ) PostItem::BuildChatDataShort() {
    static void * chat_data_pointer = nullptr;
    static DWORD mem = 0;
    _asm {
        MOV chat_data_pointer, ECX;
        MOV mem, 0x0078BE90;
        CALL mem;
    }
    BuildChatData ( chat_data_pointer );
    _asm {
        MOV mem, 0x00789CC7;
        JMP mem;
    }
}
// -----------------------------------------------------------------------------

void PostItem::BuildChatData ( void * chat_data_pointer ) {
    MuObjectChatData * chat = ( MuObjectChatData * ) chat_data_pointer;

	//g_ConsoleEx.Output(cGREEN, "BuildChatData %d %d", chat->is_external_message(), gPostItem.list_counter_);
    if ( !chat->is_external_message() || !gPostItem.list_counter_ ) {
        return;
    }

    char * message = chat->message();
    unsigned long message_len = chat->message_len();
	
	//g_ConsoleEx.Output(cGREEN, "[%d] %s", message_len, message);
    // _APIxxXXXXxxAPI
    if ( message[message_len - 1 - 8 - 2] != '_' ||
            message[message_len - 1 - 8 - 1] != '[' ||
            message[message_len - 1] != ']' ) {
        return;
    }

    LinkNode<ItemPost> * item_node = nullptr;
	__try {
		sscanf_s ( &message[message_len - 1 - 8], "%08X", ( DWORD * ) &item_node );
		ItemPost * item_post = item_node->value();
		item_post->chat_ = chat;
		message[message_len - 1 - 8 - 2] = '\0';
		message[message_len - 1 - 8 + 0] = '_';
		message[message_len - 1 - 8 + 1] = '_';
		message[message_len - 1 - 8 + 6] = '_';
		message[message_len - 1 - 8 + 7] = '_';    // _[0CDE1234]   \0__DE12__
		* ( unsigned long * ) &message[message_len - 1 - 8 + 2] = ( unsigned long ) item_node;
	}   __except (EXCEPTION_EXECUTE_HANDLER)
	{
		item_node = nullptr;
	}
	
	//g_ConsoleEx.Output(cGREEN, "[%d] %s %08X", message_len, message, message[message_len - 1 - 8]);
}
// -----------------------------------------------------------------------------

void __declspec ( naked ) PostItem::ProcessCharacterHeadChatText() 
{
    static DWORD mem = 0;
    static DWORD base_address;
    static DWORD chat_text;
    _asm {
        MOV mem, EAX;
        MOV EAX, DWORD PTR SS : [EBP + 0x08];
        MOV base_address, EAX;
        MOV EAX, DWORD PTR SS : [EBP + 0x0C];
        MOV chat_text, EAX;
        MOV EAX, mem;
    }
    PostItem::ProcessCharacterHeadChatTextImp ( ( char * ) base_address, ( char * ) chat_text );
    _asm {
        PUSH -1;
        PUSH 0x00CD2FC3;
        MOV mem, 0x0059918A;
        JMP mem;
    }
}
// -----------------------------------------------------------------------------

void PostItem::ProcessCharacterHeadChatTextImp ( char * base_address, char * chat_text ) 
{
    if ( gPostItem.draw_character_head_chat_text_ ) {
        // xử lý đoạn chat trên đầu nhân vật
        unsigned long len = strlen ( chat_text );

        if ( chat_text[len - 1 - 8 - 2] != '_' ||
                chat_text[len - 1 - 8 - 1] != '[' ||
                chat_text[len - 1] != ']' ) {
            // do nothing
        }
        else {
            gPostItem.draw_character_head_chat_text_base_address_ = base_address;
        }

        gPostItem.draw_character_head_chat_text_ = false;
    }
}
// -----------------------------------------------------------------------------

void __declspec ( naked ) PostItem::ViewPostItem() {
    static void * chat_data_pointer = nullptr;
    static DWORD mem = 0;
    _asm {
        MOV mem, 0x0078BED0;
        CALL mem;
        MOV chat_data_pointer, EAX;
    }

	ViewPostItemImp ( chat_data_pointer );

    _asm {
        MOV EAX, chat_data_pointer;
        MOV mem, 0x0078A95B;
        JMP mem;
    }
}
// -----------------------------------------------------------------------------

void PostItem::ViewPostItemImp ( void * chat_data_pointer ) {
    MuObjectChatData * chat = ( MuObjectChatData * ) chat_data_pointer;

    if ( !chat->is_external_message() || !gPostItem.list_counter_ || pCursorX > 76) {
        *gPostItem.current_item_post_ = nullptr;
        return;
    }

    char * message = chat->message();
    unsigned long message_len = chat->message_len();
    unsigned long real_len = strlen ( message );

    if ( message_len == real_len ) {
        *gPostItem.current_item_post_ = nullptr;
        return;
    }

    // _API__XXXX__API
    if ( message[message_len - 1 - 8 - 2] != '\0' ||
            message[message_len - 1 - 8 - 1] != '[' ||
            message[message_len - 1] != ']' ) {
        *gPostItem.current_item_post_ = nullptr;
        return;
    }

	__try {
		LinkNode<ItemPost> * item_node = ( LinkNode<ItemPost> * ) * ( unsigned long * ) &message[message_len - 1 - 8 + 2];
		ItemPost * item_post = item_node->value();
		ObjectItem * item_data = ( ObjectItem * ) &item_post->item_;
		// set show item tool tip
		*gPostItem.last_tickcount_view_ = GetTickCount();
		*gPostItem.current_item_post_ = item_data;
	}  __except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}
#endif