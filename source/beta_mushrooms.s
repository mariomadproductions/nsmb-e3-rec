@ BETA MUSHROOM PLATFORM BY THEGAMERATORT

@ Change height
repl_0217F4D4_ov_5A:
	LDRB    R0, [R5,#0x6FD]
	CMP     R0, #0
	MOVNE   R0, #0x4000
	MOVEQ   R0, #0x8000
	BX      LR

repl_0217F518_ov_5A:
	LDRB    R0, [R5,#0x6FD]
	CMP     R0, #0
	ADDNE   R0, R9, #0x4000
	ADDEQ   R0, R9, #0x8000
	BX      LR

repl_0217F608_ov_5A:
	LDRB    R2, [R5,#0x6FD]
	CMP     R2, #0
	ADDNE   R2, R9, #0x4000
	ADDEQ   R2, R9, #0x8000
	BX      LR

@ Stretch collision size
repl_0217F504_ov_5A:
	ADD     R1, R0, #0x20000
	BX      LR

@ Mushroom color
repl_0217DD88_ov_5A:
	BX      LR
repl_0217DD94_ov_5A:
	LDR     R0, =0x548
	SUB     R0, R4, R0
	LDR     R3, [R0,#0xC]
	CMP     R3, #195
	MOVEQ   R3, #0
	BEQ     .SkipClass1
	LDR     R3, [R0,#8]
	ANDS    R3, R3, #0x1000000
	MOVEQ   R3, #0
	MOVNE   R3, #1
.SkipClass1:
	STR     R3, [SP]  @Pal Number
	MOV     R3, #0    @Tex Number
	MOV     R0, R4
	BX      LR

@ Mushroom stem
repl_02160BF4_ov_36:
	@Get actor to R1
	LDR     R1, =0x560
	SUB     R1, R0, R1
	@Class Check
	LDR     R3, [R1,#0xC]
	CMP     R3, #195
	MOVEQ   R3, #0
	BXEQ    LR
	@Texture Check
	LDR     R3, [R1,#8]
	ANDS    R3, R3, #0x10000000
	MOVEQ   R3, #0
	MOVNE   R3, #1
	BX      LR

repl_0217F5A0_ov_5A: @Do not setup corner 1
repl_0217F5EC_ov_5A: @Do not setup corner 2
repl_0217F6CC_ov_5A: @Do not register corner 1
repl_0217F6D4_ov_5A: @Do not register corner 2
	BX      LR