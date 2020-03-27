.global GX_SetBankForSubOBJExtPltt
GX_SetBankForSubOBJExtPltt:
                STMFD           SP!, {R4,LR}
                MOV             R4, R0
                MOV             R0, R4,LSL#16
                MOV             R0, R0,LSR#16
                @BL              GxCheckExclusive
                LDR             R0, =0x02094248 @gGXState
                MVN             R3, R4
                LDRH            R2, [R0]
                LDRH            R1, [R0,#0x18]
                CMP             R4, #0
                ORR             R1, R2, R1
                AND             R1, R3, R1
                STRH            R1, [R0]
                STRH            R4, [R0,#0x18]
                BEQ             loc_1EEC
                CMP             R4, #0x100
                BNE             loc_1EFC
                LDR             R3, =0x4001000
                LDR             R0, =0x4000249
                LDR             R2, [R3]
                MOV             R1, #0x83
                ORR             R2, R2, #0x80000000
                STR             R2, [R3]
                STRB            R1, [R0]
                B               loc_1EFC

loc_1EEC:
                LDR             R1, =0x4001000
                LDR             R0, [R1]
                BIC             R0, R0, #0x80000000
                STR             R0, [R1]

loc_1EFC:
                LDR             R0, =0x02094248 @gGXState
                LDRH            R0, [R0]
                BL              0x02061D7C @GX_VRAMCNT_SetLCDC_
                LDMFD           SP!, {R4,PC}