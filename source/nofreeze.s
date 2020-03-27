repl_0209DC30_ov_00:			@Prevent most Actors from freezing upon level completion
@NOPE! repl_020A26B8_ov_00:		@Prevent Spin Block and Star Coin from freezing upon level completion
	BX		LR

repl_0218EAB8_ov_76:
	BX		LR					@Prevent Actor 210 (Carry-through-wall platform) from pausing the remaining actors

repl_0218E6F8_ov_76:
	LDR		R1, =0x20CA880
	MOV		R2, #0
	STRB	R2, [R1, #0x18]		@Prevent the timer from pausing when Actor 210 is acting
	ADD		R1, R4, #0x500
	BX		LR
	
repl_0211FDDC_ov_0A:
	MOV		R1, #1
	STRB	R1, [R0]			@Prevent particles from being frozen on power-change (on load)
	MOV		R1, #0x28
	BX		LR
	
repl_021207F4_ov_0A:
	MOV		R1, #1
	STRB	R1, [R0]			@Prevent particles from being frozen on death
	ADD		SP, SP, #4
	BX		LR

repl_0211F904_ov_0A:
	STMFD	SP!, {LR}
	BL		.CheckLevelClear
	LDMEQFD	SP!, {PC}			@If the level is cleared this patch will prevent a glitch when Mega
	LDR		R4, =0x203A784
	LDR		R4, [R4]
	LDR		R4, [R4, #0x2F8]
	ADD		R4, R4, #0x760
	LDR		R1, [R4, #0x4C]
	CMP		R1, #0				@Check if a power change is happening
	ADDEQ	PC, PC, #0x1C		@If not return
	LDR		R1, [R4, #8]
	CMP		R1, #0x2000			@Check if Mario is above his Super height (Mega)
	MOVGT	R1, #0x2000
	STRGT	R1, [R4, #8]		@If he is make him 'Super Mario' height instantly
	MOVGT	R1, #0
	STRGT	R1, [R4, #0x4C]		@Prevent flagpole-stalling when Mega-Mario powers down (this one may be not needed)
	ADDGT	R4, R4, #0x400
	STRGTB	R1, [R4, #0x57]		@Prevent flagpole-stalling when Mega-Mario powers down (this one is a must)
	LDMFD	SP!, {PC}

repl_0211F974_ov_0A:
	STMFD	SP!, {LR}
	LDR		R0, =0x203CF80
	MOV		R4, #1
	STRB	R4, [R0]			@Prevent particles from being paused on power-change (afterwards)
	BL		.CheckLevelClear
	LDMEQFD	SP!, {PC}
	LDR		R4, =0x203A784
	LDR		R4, [R4]
	LDR		R4, [R4, #0x2F8]
	ADD		R4, R4, #0x760
	MOV		R1, #0
	STR		R1, [R4, #0x4C]		@Drop power-change 2nd phase remaining frames to 0
	ADD		R4, R4, #0x400
	STRB	R1, [R4, #0x57]		@Drop power-change 1st phase remaining frames to 0
	LDMFD	SP!, {PC}

repl_0211F92C_ov_0A:
repl_021207B8_ov_0A:
	MOV		R0, #0
	BX		LR
	
repl_0212C13C_ov_0B:
	MOV		R1, #0
	BX		LR

.CheckLevelClear:
	STMFD	SP!, {LR}
	LDR		R0, [R0]
	LDR		R4, =0x20CA2C0
	LDR		R4, [R4]
	CMP		R4, #0				@Check if level is not cleared (flag is 0x100 when the level is completed)
	MOVEQ	R0, #0				@If true then apply the no-freeze patch
	LDMFD	SP!, {PC}