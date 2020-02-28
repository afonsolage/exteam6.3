#include "stdafx.h"
#include "Interface.h"
#include "Import.h"
#include "ExText.h"

bool CheckSimbolEng(char String)
{
	switch(String)
	{
		case 'a': return true; break;
		case 'b': return true ; break;
		case 'c': return true ; break;
		case 'd': return true ; break;
		case 'e': return true ; break;
		case 'f': return true ; break;
		case 'g': return true ; break;
		case 'h': return true ; break;
		case 'i': return true ; break;
		case 'j': return true ; break;
		case 'k': return true ; break;
		case 'l': return true ; break;
		case 'm': return true ; break;
		case 'n': return true ; break;
		case 'o': return true ; break;
		case 'p': return true ; break;
		case 'q': return true ; break;
		case 'r': return true ; break;
		case 's': return true ; break;
		case 't': return true ; break;
		case 'u': return true ; break;
		case 'v': return true ; break;
		case 'w': return true ; break;
		case 'x': return true ; break;
		case 'y': return true ; break;
		case 'z': return true ; break;
		case 'A': return true ; break;
		case 'B': return true ; break;
		case 'C': return true ; break;
		case 'D': return true ; break;
		case 'E': return true ; break;
		case 'F': return true ; break;
		case 'G': return true ; break;
		case 'H': return true ; break;
		case 'I': return true ; break;
		case 'J': return true ; break;
		case 'K': return true ; break;
		case 'L': return true ; break;
		case 'M': return true ; break;
		case 'N': return true ; break;
		case 'O': return true ; break;
		case 'P': return true ; break;
		case 'Q': return true ; break;
		case 'R': return true ; break;
		case 'S': return true ; break;
		case 'T': return true ; break;
		case 'U': return true ; break;
		case 'V': return true ; break;
		case 'W': return true ; break;
		case 'X': return true ; break;
		case 'Y': return true ; break;
		case 'Z': return true ; break;
		case '0': return true ; break;
		case '1': return true ; break;
		case '2': return true ; break;
		case '3': return true ; break;
		case '4': return true ; break;
		case '5': return true ; break;
		case '6': return true ; break;
		case '7': return true ; break;
		case '8': return true ; break;
		case '9': return true ; break;
		case '@': return true ; break;
		case '~': return true ; break;
		default: return false;
	}
}

bool CursorZoneButton(float X, float Y, float MaxX, float MaxY)
{
	if( (pCursorX < X || pCursorX > MaxX) || (pCursorY < Y || pCursorY > MaxY) )
	{
		return false;
	}
	// ----
	return true;
}

bool Ex_IsBadFileLine(char *FileLine, int &Flag)
{
	if(Flag == 0)
	{
		if(isdigit(FileLine[0]))
		{
			Flag = FileLine[0] - 48;
			return true;
		}
	}
	else if(Flag < 0 || Flag > 9)	//Old 9
	{
		Flag = 0;
	}

	if(!strncmp(FileLine, "end", 3))
	{
		Flag = 0;
		return true;
	}

	if(FileLine[0] == '/' || FileLine[0] == '\n')
		return true;

	for(UINT i = 0; i < strlen(FileLine); i++)
	{
		if(isalnum(FileLine[i]))
			return false;
	}
	return true;
}

char * CharacterCode (int a)
{
	switch(a)
	{
	case 0:  return g_ExText.GetText(60);
		case 1:  return g_ExText.GetText(61);
		case 2:  return g_ExText.GetText(62);
		case 3:  return g_ExText.GetText(62);
		case 16: return g_ExText.GetText(63);
		case 17: return g_ExText.GetText(64);
		case 18: return g_ExText.GetText(65);
		case 19: return g_ExText.GetText(65);
		case 32: return g_ExText.GetText(66);
		case 33: return g_ExText.GetText(67);
		case 34: return g_ExText.GetText(68);
		case 35: return g_ExText.GetText(68);
		case 48: return g_ExText.GetText(69);
		case 50: return g_ExText.GetText(70);
		case 66: return g_ExText.GetText(71);
		case 67: return g_ExText.GetText(71);
		case 64: return g_ExText.GetText(71);
		case 65: return g_ExText.GetText(71);
		case 68: return g_ExText.GetText(72);
		case 80: return g_ExText.GetText(73);
		case 81: return g_ExText.GetText(74);
		case 82: return g_ExText.GetText(75);
		case 83: return g_ExText.GetText(75);
		case 96: return g_ExText.GetText(76);
		case 97: return g_ExText.GetText(77);		
		case 98: return g_ExText.GetText(77);		
	}
	return "unknown";
}

void MessageBoxError(char *szlog, ...)
{
	char szBuffer[512] = "";
	va_list pArguments;
	va_start(pArguments, szlog);
	vsprintf(szBuffer, szlog, pArguments);
	va_end(pArguments);
	MessageBox(NULL, szBuffer, "error", MB_OK | MB_APPLMODAL);
}

void CheckFixMinMaxNumber(int &Number, int Min, int Max)
{
	if (Number > Max)
	{
		Number = Max;
	}
	else if (Number < Min)
	{
		Number = Min;
	}
}