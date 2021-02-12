@ DS division support for GCC.
@ By TheGameratorT

/*
	Unsigned divisions functions are directly mapped to the
	game's software unsigned division functions since the
	DS hardware doesn't provide unsigned division support.

	symbols.x:
		__aeabi_uidiv = <address of _u32_div_f>;
		__aeabi_uidivmod = <address of _u32_div_f>;
		__aeabi_uldiv = <address of _ull_div>;
		__aeabi_uldivmod = <address of _ull_div>;

	If you use this to make a new DS game and need
	unsigned division, include lib GCC when linking.
*/

@ s32 __aeabi_idiv(s32 numerator, s32 denominator)
.global __aeabi_idiv
__aeabi_idiv:
	LDR     R3, =0x4000200
	STR     LR, [SP,#-4]!
	MOV     R12, #0
	MOV     LR, #0x4000000
	MOV     R2, R3
	STR     R0, [LR,#0x290]
	STR     R1, [R3,#0x98]
	STRH    R12, [R3,#0x80]
	STR     R12, [R3,#0x9C]

wait_div1:
	LDRH    R3, [R2,#0x80]
	TST     R3, #0x8000
	BNE     wait_div1
	MOV     R3, #0x4000000
	LDR     R0, [R3,#0x2A0]
	LDR     PC, [SP],#4

@ struct { s32 quot, s32 rem } _aeabi_idivmod(s32 numerator, s32 denominator)
.global __aeabi_idivmod
__aeabi_idivmod:
	LDR     R3, =0x4000200
	STR     LR, [SP,#-4]!
	MOV     R12, #0
	MOV     LR, #0x4000000
	MOV     R2, R3
	STR     R0, [LR,#0x290]
	STR     R1, [R3,#0x98]
	STRH    R12, [R3,#0x80]
	STR     R12, [R3,#0x9C]

wait_div2:
	LDRH    R3, [R2,#0x80]
	TST     R3, #0x8000
	BNE     wait_div2
	MOV     R3, #0x4000000
	LDR     R0, [R3,#0x2A0]
	LDR     R1, [R3,#0x2A8]
	LDR     PC, [SP],#4

@ s64 _aeabi_ldiv(s64 numerator, s64 denominator)
.global __aeabi_ldiv
__aeabi_ldiv:
	STMFD   SP!, {R4-R7}
	MOV     R7, R1
	MOV     R5, R3
	MOV     R6, R0
	MOV     R4, R2
	LDR     R3, =0x4000200
	MOV     R12, #2
	MOV     R1, R3
	STRD    R6, [R3,#0x90]
	STRD    R4, [R3,#0x98]
	STRH    R12, [R3,#0x80]

wait_div3:
	LDRH    R3, [R1,#0x80]
	TST     R3, #0x8000
	BNE     wait_div3
	LDRD    R0, [R1,#0xA0]
	LDMFD   SP!, {R4-R7}
	BX      LR

@ struct { s64 quot, s64 rem } _aeabi_ldivmod(s64 numerator, s64 denominator)
.global __aeabi_ldivmod
__aeabi_ldivmod:
	STMFD   SP!, {R4-R7}
	MOV     R7, R1
	MOV     R5, R3
	MOV     R6, R0
	MOV     R4, R2
	LDR     R3, =0x4000200
	MOV     R1, #2
	MOV     R12, R3
	STRD    R6, [R3,#0x90]
	STRD    R4, [R3,#0x98]
	STRH    R1, [R3,#0x80]

wait_div4:
	LDRH    R3, [R12,#0x80]
	TST     R3, #0x8000
	BNE     wait_div4
	LDRD    R0, [R12,#0xA0]
	LDRD    R2, [R12,#0xA8]
	LDMFD   SP!, {R4-R7}
	BX      LR

/* division.c */

@ #include "nitro.h"
@ 
@ typedef s32 s32x2 __attribute__((vector_size(8)));
@ typedef s64 s64x2 __attribute__((vector_size(16)));
@ 
@ /* ================ 32 BITS ================ */
@ 
@ /* 32 bit signed */
@ 
@ s32 __aeabi_idiv(s32 numerator, s32 denominator)
@ {
@   CP_SetDiv32_32(numerator, denominator);
@   return CP_GetDivResult32();
@ }
@ 
@ s32x2 __aeabi_idivmod(s32 numerator, s32 denominator)
@ {
@   s32 quot = __aeabi_idiv(numerator, denominator);
@   s32 rem = CP_GetDivRemainderImm32();
@   return (s32x2){ quot, rem };
@ }
@ 
@ /* ================ 64 BITS ================ */
@ 
@ /* 64 bit signed */
@ 
@ s64 __aeabi_ldiv(s64 numerator, s64 denominator)
@ {
@   CP_SetDiv64_64(numerator, denominator);
@   return CP_GetDivResult64();
@ }
@ 
@ s64x2 __aeabi_ldivmod(s64 numerator, s64 denominator)
@ {
@   s64 quot = __aeabi_ldiv(numerator, denominator);
@   s64 rem = CP_GetDivRemainderImm64();
@   return (s64x2){ quot, rem };
@ }
