#pragma once
#include "../misc/ang_t.h"

struct c_usercmd {
public:
	char pad_0000[ 4 ]; //0x0000
	int32_t m_number; //0x0004
	int32_t m_tickcount; //0x0008
	ang_t m_viewangles; //0x000C
	float m_forwardmove; //0x0018
	float m_sidemove; //0x001C
	float m_upmove; //0x0020
	int32_t m_buttons; //0x0024
	char pad_0028[ 12 ]; //0x0028
	int32_t m_randomseed; //0x0034
	int16_t m_mousedx; //0x0038
	int16_t m_mousedy; //0x003A
	bool m_predicted; //0x003C
};

struct c_verified_usercmd {
public:
	c_usercmd m_command;
	unsigned int m_crc32;
};
