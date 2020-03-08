// ExEncDec.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "..\DllClient\EncDec.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 1)
	{
		printf("Invalid usage, you must drag into this application the file to encode or decode.\r\n");
		system("PAUSE");
		return 0;
	}

	printf("Decoding: %s\r\n", argv[1]);

	g_EncDec.Load();
	g_EncDec.GetBuffer(argv[1]);
	g_EncDec.PackBuffer();
	g_EncDec.SetBuffer(argv[1]);

	printf("Done!\r\n", argv[1]);
	return 0;
}

