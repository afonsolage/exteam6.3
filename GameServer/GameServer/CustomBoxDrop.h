#pragma once

#include "CustomDrop.h"
#include "..\common\zzzitem.h"
#include "user.h"

class CCustomBoxDrop : public CCustomDrop
{
public:
	CCustomBoxDrop(void);
	virtual ~CCustomBoxDrop(void);
	void DropBoxItem(LPOBJ lpObj);
};

