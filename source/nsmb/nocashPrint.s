
@=================================
@ Function for printing stuff from C/C++

.global nocashPrint
.global nocashPrint1
.global nocashPrint2
.global nocashPrint3
.global nocashPrint4

nocashPrint:
nocashPrint1:
nocashPrint2:
nocashPrint3:
nocashPrint4:
	PUSH    {R4-R9}
	LDR     R4, =msgData
	MOV     R5, #0

loop:
	LDRB    R6, [R0]
	CMP     R6, #0
	BEQ     fill

	CMP     R5, #120
	BEQ     printMsg
	STRB    R6, [R4]

	ADD     R0, R0, #0x1
	ADD     R4, R4, #0x1
	ADD     R5, R5, #0x1
	B       loop

fill:
	MOV     R6, #0
	STRB    R6, [R4]
	CMP     R5, #120
	MOVEQ   R5, #0
	BEQ     printMsg
	ADD     R5, R5, #0x1
	B       fill

printMsg:
	MOV     R0, R1
	MOV     R1, R2
	MOV     R2, R3
    
	MOV     R12,R12
	B       continue83
	.word  0x6464

msgData:
	.fill 120
	.byte  0  @ Ending zero (normally not required, see below)
	.align 4  @ Align following code (use align 2 in thumb mode)

continue83:
	POP     {R4-R9}
	BX      LR


@=================================
@ Macro for printing stuff from ASM code

.macro print txt
	MOV r12,r12
	B 1f
	.word 0x6464
	.ascii "\txt"
	.byte 0
	.align 4
1:
.endm

@ You can print out stuff like this to output console.
@ For example the code below will log every time OpenFileFast is called.

@hook_0206A480:
@	print   "OpenFileFast %r0% %r1% %r2%"
@	BX      LR