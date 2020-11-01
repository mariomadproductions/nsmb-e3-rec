@ If FX_DivS32 is present in the game, remove it and link the symbol instead.
@ It is not present in NSMB, that is why it is included.

.global FX_DivS32
.global __aeabi_idivmod
.global __aeabi_idiv
.global __aeabi_uidivmod
.global __aeabi_uidiv

.global __aeabi_ldivmod
.global __aeabi_ldiv

/* 32-bit */

FX_DivS32:
	LDR     R2, =0x4000280
	MOV     R3, #0
	STRH    R3, [R2]
	STR     R0, [R2,#0x10]
	STR     R1, [R2,#0x18]
	MOV     R0, R3
	STR     R0, [R2,#0x1C]
.loop1:
	LDRH    R0, [R2]
	TST     R0, #0x8000
	BNE     .loop1
	LDR     R0, =0x40002A0
	LDR     R0, [R0]
	BX      LR

__aeabi_idivmod:
	PUSH    {LR}
	BL      FX_DivS32
	LDR     R1, =0x40002A8
	LDR     R1, [R1]
	POP     {PC}

__aeabi_idiv:
	B       FX_DivS32

__aeabi_uidivmod:
	STMFD   SP!, {LR}
	MOV     R2, R1
	MOV     R1, #0
	MOV     R3, #0
	BL      __aeabi_ldivmod
	MOV     R1, R2
	LDMFD   SP!, {PC}

__aeabi_uidiv:
	B       __aeabi_uidivmod
	
/* 64-bit */

__aeabi_ldivmod:
	STMFD   SP!, {R4,R5}
	MOV     R3, #0
	MOV     R5, R1
	MOV     R4, R0
	MOV     R12, #1
	LDR     R1, =0x4000200
	STRD    R4, [R1,#0x90]
	STRD    R2, [R1,#0x98]
	STRH    R12, [R1,#0x80]
.loop2:
	LDRH    R3, [R1,#0x80]
	TST     R3, #0x8000
	BNE     .loop2
	LDRD    R0, [R1,#0xA0]
	LDRD    R2, [R1,#0xA8]
	LDMFD   SP!, {R4,R5}
	BX      LR
	
__aeabi_ldiv:
	B       __aeabi_ldivmod
