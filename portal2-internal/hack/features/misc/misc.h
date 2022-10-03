#pragma once
#include "../../../sdk/portal.h"


namespace hack::features::misc {
	void bhop( c_usercmd* cmd );

	inline void create_move( c_usercmd* cmd ) {
		bhop( cmd );
	}
}