#pragma once
#include <Windows.h>

class c_base_player;

namespace g {
	inline HANDLE dll_handle = nullptr;
	inline c_base_player* localplayer = nullptr;
	inline HWND win = nullptr;
	inline bool running = true;
}
