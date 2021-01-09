
@Debug screen SWITCH!

repl_02005C20:
repl_02005C2C:
	push {LR}
		ldr r0, gotoRamViewer
		ldr r1, =0x04000130
		ldr r1, [r1]
		tst r1, #4
		moveq r0, #0
		tst r1, #8
		moveq r0, #1
		str r0, gotoRamViewer
		cmp r0, #0
		beq normal
		bl _Z20debugScreenRamViewerv
		pop {PC}
normal:
		ldr r0, =0x02005EB0
		blx r0
	pop {PC}
	
repl_02005C30:

	push {LR}
		ldr r0, gotoRamViewer
		cmp r0, #0
		popne {PC}
		ldr r0, =0x020061E4
		blx r0
	pop {PC}
	
gotoRamViewer:
	.word 1

