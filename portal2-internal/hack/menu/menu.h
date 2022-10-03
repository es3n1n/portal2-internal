#pragma once
#include "ui/imgui_custom.h"


namespace hack::menu {
	inline bool opened = false;

	void render( );
	void toggle( );
	void setup( );
}
