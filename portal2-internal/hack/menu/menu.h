#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"


namespace hack::menu {
	inline bool opened = true;

	void render( );
	void toggle( );
	void setup( );
}
