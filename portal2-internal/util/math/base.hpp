#pragma once

// https://gist.github.com/es3n1n/1601c7b74d03abe36ee2cc5790409ccc
namespace util::math {
    constexpr auto e = 2.71828182845904523536f;
    constexpr auto pi = 3.14159265358979323846f;
    constexpr auto radpi = 180.f / pi;
    constexpr auto sqrpi = pi * pi;
    constexpr auto round_error = 0.5;

    double __forceinline deg2rad(double x) {
        return x * (static_cast<double>(pi) / 180.0);
    }

    double __forceinline rad2deg(double x) {
        return x * (180.0 / static_cast<double>(pi));
    }

    double __forceinline __declspec(naked) __fastcall sin(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fsin
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall asin(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld		st
			fabs
			fcom		dword ptr[ round_error ]
			fstsw		ax
			sahf
			jbe		asin_cont
			fld1
			fsubrp	st( 1 ), st( 0 )
			fld		st
			fadd		st( 0 ), st( 0 )
			fxch		st( 1 )
			fmul		st( 0 ), st( 0 )
			fsubp		st( 1 ), st( 0 )
			jmp		asin_exit

			asin_cont :

			fstp		st( 0 )
				fld		st( 0 )
				fmul		st( 0 ), st( 0 )
				fld1
				fsubrp	st( 1 ), st( 0 )

				asin_exit:

			fsqrt
				fpatan
				ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall sinh(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fldl2e
			fmulp		st( 1 ), st
			fld1
			fld		st( 1 )
			fprem
			f2xm1
			faddp		st( 1 ), st
			fscale
			fxch
			fstp		st
			fld1
			fdiv		st, st( 1 )
			fsubp		st( 1 ), st
			mov		eax, 0x3F000000
			push		eax
			fld		dword ptr[ esp ]
			fmulp		st( 1 ), st
			pop		eax
			ret		8
        }
    }

    // warn: comparing to math.h: (1.) (util::math)0.88137358701954294 vs (math.h)0.88137358701954305
    double __forceinline __declspec(naked) __fastcall asinh(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld		st
			fmul		st, st
			fld1
			faddp		st( 1 ), st
			fsqrt
			faddp		st( 1 ), st
			fldln2
			fxch
			fyl2x
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall cos(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fcos
			ret		8
        }
    }

    // warn: comparing to math.h: (.5) (util::math)1.0471975511965976 vs (math.h)1.0471975511965979
    double __forceinline __declspec(naked) __fastcall acos(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld1
			fchs
			fcomp		st( 1 )
			fstsw		ax
			je			skip

			fld		st( 0 )
			fld1
			fsubrp	st( 1 ), st( 0 )
			fxch		st( 1 )
			fld1
			faddp		st( 1 ), st( 0 )
			fdivp		st( 1 ), st( 0 )
			fsqrt
			fld1
			jmp		end

			skip :

			fld1
				fldz

				end :

			fpatan
				fadd		st( 0 ), st( 0 )
				ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall cosh(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fldl2e
			fmulp		st( 1 ), st
			fld1
			fld		st( 1 )
			fprem
			f2xm1
			faddp		st( 1 ), st
			fscale
			fxch
			fstp		st
			fld1
			fdiv		st, st( 1 )
			faddp		st( 1 ), st
			mov		eax, 0x3F000000
			push		eax
			fld		dword ptr[ esp ]
			fmulp		st( 1 ), st
			pop		eax
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall acosh(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld		st
			fmul		st, st
			fld1
			fsubp		st( 1 ), st
			fsqrt
			faddp		st( 1 ), st
			fldln2
			fxch
			fyl2x
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall tan(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fptan
			fstp		st( 0 )
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall atan(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld1
			fpatan
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall atan2(double x, double y) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld		qword ptr[ esp + 12 ]
			fpatan
			ret		16
        }
    }

    double __forceinline __declspec(naked) __fastcall tanh(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld		st
			mov		eax, 0x40000000
			push		eax
			fld		dword ptr[ esp ]
			fmul		st, st( 1 )
			fldl2e
			fmulp		st( 1 ), st
			fld1
			fld		st( 1 )
			fprem
			f2xm1
			faddp		st( 1 ), st
			fscale
			fxch
			fstp		st
			fld1
			fsub		st, st( 1 )
			fchs
			fld1
			faddp		st( 2 ), st
			fdivrp	st( 1 ), st
			pop		eax
			ret		8
        }
    }

    // warn: comparing to math.h: (.4) (util::math)0.42364893019360178 vs (math.h)0.42364893019360184
    double __forceinline __declspec(naked) __fastcall atanh(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld1
			fsub		st, st( 1 )
			fld1
			faddp		st( 2 ), st
			fdivrp	st( 1 ), st
			fldln2
			fxch
			fyl2x
			mov		eax, 0xBF000000
			push		eax
			fld		dword ptr[ esp ]
			fmulp		st( 1 ), st
			pop		eax
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall exp(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fldl2e
			fmulp		st( 1 ), st
			fld1
			fld		st( 1 )
			fprem
			f2xm1
			faddp		st( 1 ), st
			fscale
			fxch
			fstp		st
			ret		8
        }
    }

    // warn: comparing to math.h: (.8) (util::math)1.7411011265922482 vs (math.h)1.7411011265922485
    double __forceinline __declspec(naked) __fastcall exp2(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld1
			fld		st( 1 )
			fprem
			f2xm1
			faddp		st( 1 ), st
			fscale
			fxch
			fstp		st
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall log(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fldln2
			fxch
			fyl2x
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall log2(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld1
			fxch
			fyl2x
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall fabs(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fabs
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall pow(double x, double y) {
        __asm {
			fld		qword ptr[ esp + 12 ]
			fld		qword ptr[ esp + 4 ]
			ftst
			fstsw		ax
			sahf
			jz			skip

			fyl2x
			fld1
			fld		st( 1 )
			fprem
			f2xm1
			faddp		st( 1 ), st( 0 )
			fscale

			skip :

			fstp		st( 1 )
				ret		16
        }
    }

    double __forceinline __declspec(naked) __fastcall ceil(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fchs
			fld1
			fld		st( 1 )
			fprem
			sub		esp, 4
			fst		dword ptr[ esp ]
			fxch		st( 2 )
			mov		eax, [ esp ]
			cmp		eax, 0x80000000
			jbe		skip
			fsub		st, st( 1 )

			skip:

			fsub		st, st( 2 )
				fstp		st( 1 )
				fstp		st( 1 )
				fchs
				pop		eax
				ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall floor(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fld1
			fld		st( 1 )
			fprem
			sub		esp, 4
			fst		dword ptr[ esp ]
			fxch		st( 2 )
			mov		eax, [ esp ]
			cmp		eax, 0x80000000
			jbe		floor_exit
			fsub		st, st( 1 )

			floor_exit:

			fsub		st, st( 2 )
				fstp		st( 1 )
				fstp		st( 1 )
				pop		eax
				ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall fmod(double x, double y) {
        __asm {
			fld		qword ptr[ esp + 12 ]
			fld		qword ptr[ esp + 4 ]
			fprem
			fxch
			fstp		st
			ret		16
        }
    }

    double __forceinline __declspec(naked) __fastcall sqrt(double x) {
        __asm {
			fld		qword ptr[ esp + 4 ]
			fsqrt
			ret		8
        }
    }

    double __forceinline __declspec(naked) __fastcall hypot(double x, double y) {
        __asm {
			fld		qword ptr[ esp + 12 ]
			fld		qword ptr[ esp + 4 ]
			fmul		st, st
			fxch
			fmul		st, st
			faddp		st( 1 ), st
			fsqrt
			ret		16
        }
    }
} // namespace util::math
