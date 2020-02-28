#include "StdAfx.h"
#ifdef _POST_CONFIG_
#include "Message.h"
#include "GMMng.h"

#define POST_CONFIG_DIR	"..\\Data\\ExData\\Post.ini"


class cPostConfig
{
	
		char CommandPost[100];	//Post
		int PostLevel;
		int PostMoney;
		char PostPrist[100];
		int PostColor;
		int PostPCPoint;
		int MoneyType;

public:
	void Load();
	void SetCommand();
	void StartCommand(int);



};
extern cPostConfig PostConfig;

#endif