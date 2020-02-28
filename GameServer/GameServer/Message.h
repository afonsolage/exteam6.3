//#pragma pack(push, 1)
//struct CHAT_WHISPER_EX
//{
//	PBMSG_HEAD	Head;
//	char		Name[10];
//	char		Message[90];
//	BYTE		Type;
//};
//#pragma pack(pop)

void MsgNormal(int aIndex,char* szMsg,...);
void MessageChat(int aIndex,char* szMsg,...);
void MessageAllChat(int aIndex,char* szMsg,...);
void MessaageAllGlobal(char* szMsg,...);
void ChatMessageTwo(int aIndex, char * msg, ...);
void ChatMessageOne(int aIndex, char * msg, ...);

void MessageSendEx(int aIndex, int Type, char * Sender, char * Message, ...);
void MessageSendAllEx(int Type, char * Sender, char * Message, ...);