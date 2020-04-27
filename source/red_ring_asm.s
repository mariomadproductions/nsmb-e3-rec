@ RED RING ===========================

repl_02153110_ov_36:
	LDRH    R0, [R4,#0xC]
	CMP     R0, #0x97
	BNE     .Return
	LDRB    R0, [R4,#0x4ED]
	LDR     R1, =ColorStack
	STRB    R0, [R1]
.Return:
	ADD     R0, R4, #0x3F4
	BX      LR

@ NSBTP DRAW HOOK ===========================
	
repl_0205A6E0:
	LDR     R4, =ColorStack
	LDRB    R5, [R4]
	CMP     R5, #0
	BEQ     .ReturnNSBTP
	SUB     R2, R5, #1
	MOV     R5, #0
	STRB    R5, [R4]
.ReturnNSBTP:
	ADD     R0, R3, R2, LSL #2
	BX      LR
	
.data
.balign 1
ColorStack:
	.byte 0x0