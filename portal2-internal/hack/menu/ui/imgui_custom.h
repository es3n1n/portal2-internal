#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"


namespace ImGui {
	// really hot tho
	bool Hotkey( const char* label, int* k, const ImVec2& size_arg = ImVec2( 0, 0 ) );
}
