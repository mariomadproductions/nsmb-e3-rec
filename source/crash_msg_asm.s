
@Debug screen SWITCH!

repl_02005C20:
repl_02005C2C:
	PUSH    {LR}
	LDR     R0, gotoRamViewer
	LDR     R1, =0x04000130
	LDR     R1, [R1]
	TST     R1, #4
	MOVEQ   R0, #0
	TST     R1, #8
	MOVEQ   R0, #1
	STR     R0, gotoRamViewer
	CMP     R0, #0
	BEQ     normal
	BL      _Z20debugScreenRamViewerv
	POP     {PC}
normal:
	BL      0x02005EB0
	POP     {PC}
	
repl_02005C30:
	PUSH    {LR}
	LDR     R0, gotoRamViewer
	CMP     R0, #0
	POPNE   {PC}
	BL      0x020061E4
	POP     {PC}
	
gotoRamViewer:
	.word 1

