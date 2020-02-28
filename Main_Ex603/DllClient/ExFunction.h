#pragma once

bool CheckSimbolEng(char String);
bool CursorZoneButton(float X, float Y, float MaxX, float MaxY);
bool Ex_IsBadFileLine(char *FileLine, int &Flag);
char * CharacterCode (int a);
void MessageBoxError(char *szlog, ...);
void CheckFixMinMaxNumber(int &Number, int Min, int Max);