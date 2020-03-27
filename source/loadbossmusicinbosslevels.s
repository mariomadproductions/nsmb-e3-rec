nsub_020AD01C_ov_00:
LDR 	R0, =0x02085A9C	
LDR 	R0, [R0]
CMP     R0, #0xD
BEQ     .true
CMP     R0, #0xE
BEQ     .true
CMP     R0, #0x15
BEQ     .true
CMP     R0, #0x16
BEQ     .true
MOV     R0, #0
BX      LR

.true:
MOV   R0, #1
BX    LR