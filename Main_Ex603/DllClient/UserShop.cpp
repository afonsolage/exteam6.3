#include "stdafx.h"
#include "UserShop.h"
#include "Import.h"
#include "Interface.h"

#if(DEV_USERSHOP)

CUserShop g_UserShop;

CUserShop::CUserShop()
{
}

CUserShop::~CUserShop()
{
}

void CUserShop::Load()
{
}

void CUserShop::Bind()
{
}

void CUserShop::Draw()
{
	float flDrawX = 0;
	float flDrawY = 0;

	gInterface.DrawGUI(eACHIEVEMENTS_MAIN, flDrawX, flDrawY);
	gInterface.DrawFormat(eGold, 260, 23, 100, 3, "User Shop");

	// ----

	flDrawX = 20;
	flDrawY += 50;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);
	gInterface.DrawGUI(eUSERSHOP_BT1, flDrawX + 100, flDrawY + 50);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	// ----

	flDrawX = 20;
	flDrawY += 125;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	// ----

	flDrawX = 20;
	flDrawY += 125;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);

	flDrawX += 150;
	this->DrawItem(flDrawX, flDrawY, 8, 30, 15);
}

void CUserShop::DrawItem(int X, int Y, int Type, int Index, int Level)
{
	float ContentX = X;
	float ContentY = Y;
	const int WidthValue = 24;
	const int HeightValue = 26;

	gInterface.DrawGUI(eSMITHY_ITEM_BG, ContentX, ContentY);

	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(ITEM(Type, Index));

	float barWidth = WidthValue * ItemInfo->ItemWidth;
	float barHeight = HeightValue * ItemInfo->ItemHeight;
	float flDrawItemX = ContentX + ( 152 / 2 ) - ( WidthValue * ItemInfo->ItemWidth / 2 );
	float flDrawItemY = ContentY + ( 124 / 2 ) - ( HeightValue * ItemInfo->ItemHeight / 2 );

	gInterface.DrawItem(
		flDrawItemX,
		flDrawItemY,
		barWidth,
		barHeight,
		ITEMGET(Type,Index),
		SET_ITEMOPT_LEVEL(Level),
		1,0,0);
}

void CUserShop::Button(DWORD Event)
{

}

#endif