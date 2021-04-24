#pragma once

struct vec2_t {
public:
	float x;
	float y;
};

struct vec3_t {
public:
	float x;
	float y;
	float z;

	float length_2d( ) {
		float root = 0.0f;
		float sqst = x * x + y * y;

		__asm {
			sqrtss xmm0, sqst
			movss root, xmm0
		}

		return root;
	}

	float length( ) {
		float root = 0.0f;
		float sqst = x * x + y * y + z * z;

		__asm {
			sqrtss xmm0, sqst
			movss root, xmm0
		}
		
		return root;
	}
};
