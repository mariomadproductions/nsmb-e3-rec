@ RED RING ===========================

repl_02153110_ov_36:
	LDRH    R0, [R4, #0xC]
	CMP     R0, #0x97
	BNE     .Return
	LDR     R0, =RedRingColor
	LDR     R0, [R0]
	LDR     R1, =ColorStack
	STRB    R0, [R1]
.Return:
	ADD     R0, R4, #0x3F4
	BX      LR
	
repl_02153124_ov_36:
	MOV     R0, #0
	LDR     R1, =ColorStack
	STRB    R0, [R1]
	LDR     R1, =0x20391F8
	BX      LR

@ NSBTP DRAW HOOK ===========================
	
repl_0205A6E0:
	LDR     R4, =ColorStack
	LDRB    R5, [R4]
	CMP     R5, #0
	BEQ     .Return2
	SUB     R2, R5, #1
	MOV     R5, #0
	STRB    R5, [R4]
.Return2:
	ADD     R0, R3, R2, LSL #2
	BX      LR
	
.data
.balign 1
.global RedRingColor
RedRingColor:
	.byte 0x0
ColorStack:
	.byte 0x0