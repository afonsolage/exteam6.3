#pragma once

class CMiniMap
{
public:
	void Load();

	bool static MiniMapTabKey(int a1);
	bool static MiniMapCheck(int a1);

	bool Show;
};
extern CMiniMap g_MiniMap;
