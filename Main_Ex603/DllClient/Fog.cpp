#include "stdafx.h"
#include "Fog.h"
#include "Controller.h"
#include "Import.h"
enum ObjState{
 SelectServer = 2,
 SwitchCharacter = 4,
 GameProcess  = 5,
};
#pragma comment(lib, "detours.lib")
#include "detours.h"
// ----------------------------------------------------------------------------------------------

Fog g_Fog;
// ----------------------------------------------------------------------------------------------

unsigned int Textures[5];

void APIENTRY glEnable_Hooked(GLenum); 
typedef void (APIENTRY *ptr_glEnable)(GLenum);
ptr_glEnable glEnable_Real = (ptr_glEnable)&glEnable;

void APIENTRY glClearColor_Hooked(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (APIENTRY *ptr_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
ptr_glClearColor glClearColor_Real = (ptr_glClearColor)&glClearColor;
// ----------------------------------------------------------------------------------------------

void APIENTRY glEnable_Hooked(GLenum cap)
{		
	//if (pPlayerState == SelectServer)
	//	glDisable(GL_FOG);

	//if (pPlayerState == SwitchCharacter)
	//	glDisable(GL_FOG);

	if (pPlayerState == GameProcess)
	{
		RGBAStruct rgb = g_Fog.MapColor(pMapNumber); 

		GLfloat rgba[4] = { rgb.r, rgb.g, rgb.b, rgb.a };

		// —глаживание текстур: проблема с прорисовкой
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (cap == GL_BLEND || cap == GL_TEXTURE_2D || cap == GL_DEPTH_TEST)
		{
			glDisable(GL_FOG);  
		}

		// ----------
		glEnable_Real(GL_FOG);
		// ----------

		 glFogi(GL_FOG_MODE, GL_LINEAR);
		 glFogf(GL_FOG_DENSITY, 0.25f);
		 glFogfv(GL_FOG_COLOR, rgba);
		 glFogf(GL_FOG_START, 1500.0f);
		 glFogf(GL_FOG_END, 3000.0f);

		 glHint(GL_FOG_HINT, GL_NICEST);

		if (cap == GL_BLEND || cap == GL_TEXTURE_2D || cap == GL_DEPTH_TEST)   
		{
			glDisable(GL_FOG);  
		}
	}

	// ----------
	glEnable_Real(cap);
	// ---------- 
} 
// ----------------------------------------------------------------------------------------------

void APIENTRY glClearColor_Hooked(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	RGBAStruct rgb = g_Fog.MapColor(pMapNumber); 

	if (pPlayerState == SelectServer)
	{ 
		//glBindTexture(GL_TEXTURE_2D, *Textures);
		//glClearColor_Real(0.0f, 0.0f, 0.0f, 0.0f);  
	}

	if (pPlayerState == SwitchCharacter)
	{ 
		glBindTexture(GL_TEXTURE_2D, *Textures);
		glClearColor_Real(0.0f, 0.0f, 0.0f, 0.0f);  
	}

	if (pPlayerState == GameProcess)
	{ 
		glBindTexture(GL_TEXTURE_2D, *Textures); 
		glClearColor_Real(rgb.r, rgb.g, rgb.b, 0.0f);   
	}
} 
// ----------------------------------------------------------------------------------------------

RGBAStruct Fog::MapColor(int Map)
{
	RGBAStruct rgb;

	switch (Map)
	{
	case 0x0: // Lorencia
		{
			/*
			rgb.r = 0.2337f; rgb.g = 0.3f; rgb.b = 0.198f; rgb.a = 1.0f;
			*/
			rgb.r = 0.85f; rgb.g = 0.8025f; rgb.b = 0.2805f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1: // Dungeon
		{
			rgb.r = 0.83f; rgb.g = 0.7581f; rgb.b = 0.6142f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x2: // Devias
		{
			rgb.r = 0.6643f; rgb.g = 0.8158f; rgb.b = 0.91f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x3: // Noria
		{
			rgb.r = 0.3689f; rgb.g = 0.58f; rgb.b = 0.2552f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x4: // Losttower
		{
			rgb.r = 0.0f; rgb.g = 0.0f; rgb.b = 0.0f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x6: // Stadium
		{
			//rgb.r = 0.6643f; rgb.g = 0.8158f; rgb.b = 0.91f; rgb.a = 1.0f; 
			rgb.r = 0.56f; rgb.g = 0.4424f; rgb.b = 0.308f; rgb.a = 1.0f; return rgb;
		}

	case 0x7: // Atlans
		{
			rgb.r = 0.451f; rgb.g = 0.6478f; rgb.b = 0.82f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x8: // Tarkan
		{
			rgb.r = 0.83f; rgb.g = 0.667f; rgb.b = 0.3154f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0xA: // Icarus
		{
			rgb.r = 0.077f; rgb.g = 0.1318f; rgb.b = 0.22f; rgb.a = 1.0f; return rgb;
		} 
		break; 

	case 0x19: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break; 

	case 0x1A: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break; 

	case 0x1B: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1C: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1D: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1E: // Kalima
		{
			rgb.r = 0.1736f; rgb.g = 0.3475f; rgb.b = 0.56f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x1F: // Valley of Loren
		{
			rgb.r = 0.39f; rgb.g = 0.3156f; rgb.b = 0.1872f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x20: // Land of Trial
		{
			rgb.r = 0.0f; rgb.g = 0.0f; rgb.b = 0.0f; rgb.a = 1.0f; return rgb;
		} 
		break; 

	case 0x21: // Aida
		{
			rgb.r = 0.3403f; rgb.g = 0.47f; rgb.b = 0.3008f; rgb.a = 1.0f; return rgb;
		} 
		break; 


	case 0x22: // CryWolf
		{
			rgb.r = 0.39f; rgb.g = 0.3156f; rgb.b = 0.1872f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x25: // Kanturu
		{
			rgb.r = 0.4f; rgb.g = 0.3364f; rgb.b = 0.188f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x26: // Kanturu
		{
			rgb.r = 0.18f; rgb.g = 0.1708f; rgb.b = 0.1494f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x2A: // Balgas Barrack
		{
			rgb.r = 0.47f; rgb.g = 0.1363f; rgb.b = 0.1363f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x33: // Elbeland
		{
			rgb.r = 0.76f; rgb.g = 0.76f; rgb.b = 0.76f; rgb.a = 1.0f; return rgb;
		} 
		break;  

	case 0x39: // Raklion
		{
			rgb.r = 0.6643f; rgb.g = 0.8158f; rgb.b = 0.91f; rgb.a = 1.0f; return rgb;
		} 
		break;

	case 0x3E: // Santa town
		{
			rgb.r = 0.6643f; rgb.g = 0.8158f; rgb.b = 0.91f; rgb.a = 1.0f; return rgb;
		}
		break;

	case 0x28: // Silent
		{
			//rgb.r = 0.6643f; rgb.g = 0.8158f; rgb.b = 0.91f; rgb.a = 1.0f; return rgb;
			rgb.r = 1.0f; rgb.g = 1.0f; rgb.b = 1.0f; rgb.a = 1.0f; return rgb;
		}
		break;

	default:
		{
			rgb.r = 0.0f; rgb.g = 0.0f; rgb.b = 0.0f; rgb.a = 1.0f; return rgb;
		} 
		break;
	}
}
// ----------------------------------------------------------------------------------------------

void Fog::Load()
{
	DisableThreadLibraryCalls(gController.Instance);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)glEnable_Real, glEnable_Hooked);
	//DetourAttach(&(PVOID&)glClearColor_Real, glClearColor_Hooked);
	DetourTransactionCommit();
}
// ----------------------------------------------------------------------------------------------

void Fog::End()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)glEnable_Real, glEnable_Hooked); 
	//DetourDetach(&(PVOID&)glClearColor_Real, glClearColor_Hooked);
	DetourTransactionCommit();
}
// ----------------------------------------------------------------------------------------------