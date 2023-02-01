// E3 Beta Mushroom Platform by TheGameratorT

// Change height
asm(R"(
ncp_call_ov 0x0217F4D4, 90
	LDRB    R0, [R5,#0x6FD]
	CMP     R0, #0
	MOVNE   R0, #0x4000
	MOVEQ   R0, #0x8000
	BX      LR

ncp_call_ov 0x0217F518, 90
	LDRB    R0, [R5,#0x6FD]
	CMP     R0, #0
	ADDNE   R0, R9, #0x4000
	ADDEQ   R0, R9, #0x8000
	BX      LR

ncp_call_ov 0x0217F608, 90
	LDRB    R2, [R5,#0x6FD]
	CMP     R2, #0
	ADDNE   R2, R9, #0x4000
	ADDEQ   R2, R9, #0x8000
	BX      LR
)");

// Stretch collision size
ncp_repl(0x0217F504, 90, "ADD R1, R0, #0x20000")

// Mushroom color
ncp_repl(0x0217DD88, 90, "NOP")

asm(R"(
ncp_call_ov 0x0217DD94, 90
	// Get actor to R0
	LDR     R0, =0x548
	SUB     R0, R4, R0
	// Class Check
	LDR     R3, [R0,#0xC]
	CMP     R3, #189
	MOVNE   R3, #0
	BNE     .SkipClass1
	// Palette Check
	LDR     R3, [R0,#8]
	ANDS    R3, R3, #0x1000000
	MOVEQ   R3, #0
	MOVNE   R3, #1
.SkipClass1:
	// Set values and return
	STR     R3, [SP]  // Pal Number
	MOV     R3, #0    // Tex Number
	MOV     R0, R4
	BX      LR
)");

// Mushroom stem
asm(R"(
ncp_call_ov 0x02160BF4, 54
	// Get actor to R1
	LDR     R1, =0x560
	SUB     R1, R0, R1
	// Class Check
	LDR     R3, [R1,#0xC]
	CMP     R3, #195
	MOVEQ   R3, #0
	BXEQ    LR
	// Texture Check
	LDR     R3, [R1,#8]
	ANDS    R3, R3, #0x10000000
	MOVEQ   R3, #0
	MOVNE   R3, #1
	BX      LR
)");

ncp_repl(0x0217F5A0, 90, "NOP") // Do not setup corner 1
ncp_repl(0x0217F5EC, 90, "NOP") // Do not setup corner 2
ncp_repl(0x0217F6CC, 90, "NOP") // Do not register corner 1
ncp_repl(0x0217F6D4, 90, "NOP") // Do not register corner 2
ncp_repl(0x0217F3E0, 90, "B 0x0217F400") // Do not update corner collision
ncp_repl(0x0217FDB4, 90, "B 0x0217FDD4") // Do not update corner collision (horizontally moving mushroom)
