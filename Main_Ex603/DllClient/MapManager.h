#pragma once

#if(CUSTOM_MAP_MANAGER)

class CMapManager
{
public:
		CMapManager();
		~CMapManager();

	void Load();

	static void NewMap();

	static bool MapEffectAdded();

	static void MapLightingEffect3();

	static void MapRainEffect1();
	static void MapRainEffect2();
	static void MapRainEffect3();
	static void MapRainEffect4();
	static void MapRainEffect5();
	static void MapRainEffect6();

	static bool MapDrawAlphaRock6();

	bool m_Enable;
};

extern CMapManager g_MapManager;

#endif