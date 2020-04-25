@ JUMP HIT =========================================

@Mario can not make Luigi fall
nsub_02109B30_ov_0A:
	B       0x02109B84

@Luigi can not make Mario fall
nsub_02109A14_ov_0A:
	B       0x02109A68

@Set some animations for Mario jump
repl_02109BB0_ov_0A:
	MOV     R1, #1
	LDR     R0, =JumpedOnPlayer
	STRB    R1, [R0]
	MOV     R1, #0 @Restore R1
	BX      LR

@Set some animations for Luigi jump
repl_02109A94_ov_0A:
	MOV     R1, #1
	LDR     R0, =JumpedOnPlayer
	STRB    R1, [R0]
	MOV     R1, #0 @Restore R1
	BX      LR

@Allow animation to be used
nsub_021144C8_ov_0A:
	LDR     R0, =JumpedOnPlayer
	LDRB    R0, [R0]
	CMP     R0, #0
	BNE     .JumpedOnPlayer
	ADD     R0, R5, #0xB00
	LDRSB   R0, [R0,#0xA1]
	B       0x21144CC
.JumpedOnPlayer:
	MOV     R2, #0
	LDR     R1, =JumpedOnPlayer
	STRB    R2, [R1]
	MOV     R0, #0x1000 @AnimSpeed
	MOV     R1, #0x60 @AnimID
	B       0x21144F4

.data
.balign 1
JumpedOnPlayer:
	.byte 0x0