#include "stdafx.h"
#include <Windows.h>

unsigned int* MINE_COUNT = (unsigned int*)0x01005194;
unsigned int* PHEIGHT = (unsigned int*)0x01005338;
unsigned int* PWIDTH = (unsigned int*)0x01005334;

constexpr unsigned int X_STEP = 0x01; //adress offset of x-coordinate
constexpr unsigned int Y_STEP = 0x20; //adress offset of y-coordinate
unsigned int* FIELD_BEGIN = (unsigned int*)0x01005361;

typedef int(__stdcall *click_tile)(unsigned int, unsigned int);//function for choosing field

BOOL is_bomb(unsigned int x, unsigned int y) {
	unsigned int* tile_adress = FIELD_BEGIN + x + y * 0x20;

	if (*tile_adress == 0x8F) {
		return TRUE;
	}

	return FALSE;
}


BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
                click_tile choose_tile = (click_tile)0x1003512;
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

