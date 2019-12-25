// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "pch.h"
#include <Windows.h>

/*
unsigned int* MINE_COUNT = (unsigned int*)0x01005194;
unsigned int* PHEIGHT = (unsigned int*)0x01005338;
unsigned int* PWIDTH = (unsigned int*)0x01005334;

constexpr unsigned int X_STEP = 0x01; //adress offset of x-coordinate
constexpr unsigned int Y_STEP = 0x20; //adress offset of y-coordinate
unsigned int* FIELD_BEGIN = (unsigned int*)0x01005361;

typedef int(__stdcall *click)(unsigned int, unsigned int);//function for choosing field

BOOL is_bomb(unsigned int x, unsigned int y) {
	unsigned int* tile_adress = FIELD_BEGIN + x + y * 0x20;

	if (*tile_adress == 0x8F) {
		return TRUE;
	}

	return FALSE;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		click choose_tile = (click)0x1003512;
		choose_tile(1, 1);
		for (unsigned int y = 1; y < *PHEIGHT; ++y) {
			for (unsigned int x = 1; x < *PWIDTH; ++x) {
				if (!is_bomb(x, y)) {
					choose_tile(x + 1, y + 1);
				}
			}
		}

	}
	return TRUE;
}
*/

typedef int(__stdcall* D_CheckBox)(unsigned int, unsigned int);

unsigned int* HEIGHT = (unsigned int*)0x1005338;
unsigned int* WIDTH = (unsigned int*)0x1005334;

int isBomb(unsigned int i, unsigned int j) {
	unsigned int* tile = (unsigned int*)(0x1005340 + i + j);
	if ((BYTE)*tile == 0x0F)	return 1;
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
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