#pragma once

enum e_ent_flags : int32_t {
	fl_onground = ( 1 << 0 ), 	// At rest / on the ground
	fl_ducking = ( 1 << 1 ),		// Player flag -- Player is fully crouched
	fl_waterjump = ( 1 << 2 ),	// player jumping out of water
	fl_ontrain = ( 1 << 3 ),		// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
	fl_inrain = ( 1 << 4 ),		// Indicates the entity is standing in rain
	fl_frozen = ( 1 << 5 ),		// Player is frozen for 3rd person camera
	fl_atcontrols = ( 1 << 6 ),	// Player can't move, but keeps key inputs for controlling another entity
	fl_client = ( 1 << 7 ),		// Is a player
	fl_fakeclient = ( 1 << 8 ),	// Fake client, simulated server side; don't send network messages to them
	fl_inwater = ( 1 << 10 ),		// In water
};
