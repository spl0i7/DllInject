// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <windows.h>
typedef int(__stdcall *D_CheckBox)(unsigned int, unsigned int);

unsigned int *HEIGHT = (unsigned int *)0x1005338;
unsigned int *WIDTH = (unsigned int *)0x1005334;

int isBomb(unsigned int i, unsigned int j) {
	unsigned int *tile = (unsigned int *)(0x1005340 + i + j);
	if ((BYTE)*tile == 0x0F)	return 1;
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved)
{
	D_CheckBox CheckBox = (D_CheckBox)0x1003512;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//Now we're inside target process

		unsigned int i, j;
		for (i = 1; i <= *WIDTH; i++) {
			for (j = 1; j <= *HEIGHT; j++) {
				if (isBomb(i, j))	CheckBox(i, j);
			}
		}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

