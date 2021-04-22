#pragma once

// @note: es3n1n: parsed from source engine (csgo) source code, might be wrong
enum e_cmd_buttons : int32_t {
	in_attack = ( 1 << 0 ),
	in_jump = ( 1 << 1 ),
	in_duck = ( 1 << 2 ),
	in_forward = ( 1 << 3 ),
	in_back = ( 1 << 4 ),
	in_use = ( 1 << 5 ),
	in_cancel = ( 1 << 6 ),
	in_left = ( 1 << 7 ),
	in_right = ( 1 << 8 ),
	in_moveleft = ( 1 << 9 ),
	in_moveright = ( 1 << 10 ),
	in_attack2 = ( 1 << 11 ),
	in_run = ( 1 << 12 ),
	in_reload = ( 1 << 13 ),
	in_alt1 = ( 1 << 14 ),
	in_alt2 = ( 1 << 15 ),
	in_score = ( 1 << 16 ), //  Used by client.dll for when scoreboard is held down
	in_speed = ( 1 << 17 ), //  Player is holding the speed key
	in_walk = ( 1 << 18 ), //  Player holding walk key
	in_zoom = ( 1 << 19 ), //  Zoom key for HUD zoom
	in_weapon1 = ( 1 << 20 ), //  weapon defines these bits
	in_weapon2 = ( 1 << 21 ), //  weapon defines these bits
	in_bullrush = ( 1 << 22 ),
	in_grenade1 = ( 1 << 23 ), //  grenade 1
	in_grenade2 = ( 1 << 24 ), //  grenade 2
	in_attack3 = ( 1 << 25 ),
};
