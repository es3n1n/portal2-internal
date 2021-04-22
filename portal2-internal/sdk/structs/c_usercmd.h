#pragma once
#include "../misc/ang_t.h"


class c_usercmd {
public:
	char pad_0000[ 4 ]; // destructor
	int32_t m_number; // for matching server and client commands for debugging
	int32_t m_tickcount; // the tick the client created this command
	ang_t m_viewangles; // player instantaneous view angles
	float m_forwardmove; //	forward velocity
	float m_sidemove; //  sideways velocity
	float m_upmove; //  upward velocity
	int32_t m_buttons; // attack button states
	char impulse; // impulse command issued
	int32_t m_weaponselect; // current weapon id
	int32_t m_weaponsubtype; // current weapon subtype
	int32_t m_randomseed; // for shared random functions
	int16_t m_mousedx; // mouse accum in x from create move
	int16_t m_mousedy; // mouse accum in y from create move
	bool m_predicted; // tracks whether we've predicted this command at least once
};

class c_verified_usercmd {
public:
	c_usercmd* m_command;
	util::valve::crc::crc32_t m_crc32;
};

