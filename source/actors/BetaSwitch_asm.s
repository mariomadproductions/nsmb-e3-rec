BetaSwitch_ctor:
	STMFD	SP!, {R4, LR}
	LDR     R0, =BetaSwitch_ActorSize			@struct size
	LDR     R0, [R0]
	BL		NSMB_AllocFromGameHeap
	MOVS	R4, R0
	BEQ		BetaSwitch_ctor_end
	BL		EnemyActor_ctor
	LDR		R0, =BetaSwitch_vtable
	STR		R0, [R4]

BetaSwitch_ctor_end:
	MOV		R0, R4
	LDMFD	SP!, {R4, PC}

BetaSwitch_null:
	BX		LR

BetaSwitch_beforeDraw:
	B		enemyActor_beforeDraw
	BX		LR

BetaSwitch_init:
	STMFD	SP!, {R4, LR}
	MOV		R4, R0

	LDR		R2, =mainHeapHandle
	LDR		R2, [R2]
	MOV		R1, #0x40
	LDR		R3, [R0]
	LDR		R3, [R3, #0x34]
	BLX		R3

	MOV	R0, R4
	BL		BetaSwitch_OnCreate

	MOV	R0, #1
	LDMFD	SP!, {R4, PC}

BetaSwitch_beforeDelete:
	B		actor_beforeDelete

@BetaSwitch_delete:
@	B		base_onDelete

BetaSwitch_vtable:
	.long BetaSwitch_init
	.long actor_beforeCreate
	.long actor_afterCreate
	.long BetaSwitch_OnDelete
	.long BetaSwitch_beforeDelete
	.long actor_afterDelete
	.long BetaSwitch_OnExecute
	.long enemyActor_beforeExecute
	.long enemyActor_afterExecute
	.long BetaSwitch_OnDraw
	.long enemyActor_beforeDraw
	.long actor_afterDraw
	.long base_willBeDeleted
	.long base_moreHeapShit
	.long base_createHeap
	.long base_heapCreated
	.long unknown_dtor
	.long unknown_dtorFree
	.long actor_getSomething
	.long actor_incrementSomething
	.long enemyActor_executeState0 @ r0=1 (blarg?)
	.long enemyActor_isInvisible
	.long enemyActor_executeState1
	.long enemyActor_executeState2
	.long enemyActor_executeState3
	.long enemyActor_executeState4
	.long enemyActor_executeState5
	.long enemyActor_executeState6
	.long enemyActor_executeState7
	.long enemyActor_executeState8
	.long enemyActor_executeState9
	.long BetaSwitch_null	@Unknown
	.long enemyActor_virt32		@Nothing?
	.long enemyActor_virt33		@Nothing?
	.long enemyActor_virt34		@Nothing?
	.long enemyActor_virt35		@Active physics stuff - Makes enemy unable to hurt mario - sets callback to OnlyEnemiesGetHurtCallback (oeghCallback)
	.long enemyActor_virt36		@Nothing?
	.long enemyActor_virt37		@Makes enemy a bit too fast - When stomped on returns to normal - Triggers virt38
	.long enemyActor_virt38		@Makes enemy stompable twice - When stomped triggers virt39
	.long enemyActor_virt39		@Nothing?
	.long enemyActor_executeAllStates
	.long enemyActor_virt41		@Block from underneath Callback
	.long enemyActor_virt42		@Other enemy Callback (shell, spiked ball, explosion, bob-omb thrown at)
	.long enemyActor_virt43		@Fireball Callback
	.long enemyActor_virt44		@Star Callback
	.long enemyActor_virt45		@Sliding Callback
	.long enemyActor_virt46		@Mega Mario Callback
	.long enemyActor_virt47		@Makes enemy fly - for real
	.long enemyActor_virt48		@Similar to Shell Mario Callback
	.long enemyActor_virt49		@Stomp, Drill, Mini Mario GP Callback	@null
	.long enemyActor_virt50		@Ground Pound Callback
	.long enemyActor_virt51		@Shell Marios shell Callback
	.long enemyActor_virt52		@Makes enemy fly - similar to Mega Mario Callback
	.long enemyActor_virt53		@Mega Mario Ground Pound Callback
	.long BetaSwitch_null	@End Of Level Callback aka EOL
	.long enemyActor_virt55		@Lava Callback
	.long enemyActor_virt56		@Makes enemy jump
	.long BetaSwitch_null	@Nothing?
	.long enemyActor_virt58		@Stop from walking but not from jumping and other animations
	.long enemyActor_virt59		@@Collision with Mario - Always - Doesnt seem to be active physics related
	.long BetaSwitch_null	@@Collision with another enemy - Doesnt trigger virt64 or virt65
	.long enemyActor_virt61		@@Collision with Mario - Only if enemy doesnt get killed or killed by drill -- weird with virt38, virt36, virt34, virt33
	.long enemyActor_virt62		@@Killed by star, shell, slide, fireball, enemy, stomp, NOT by EOL, Mega Mario, Lava
	.long enemyActor_virt63		@@Killed by Mega Mario
	.long enemyActor_virt64		@Removes active physics callback
	.long enemyActor_virt65		@Change Direction - sets ap callback to EnemyCollisionCallback
	.long enemyActor_virt66		@Mario jumps after stomp or is propelled up (drill)
	
BetaSwitch_Profile:
	.int   BetaSwitch_ctor
	.short 0xFF
	.short 0x5C
	.int   BetaSwitch_loadFiles
	.int   0
	.int   0