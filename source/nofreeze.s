@ Clear freezing flag
repl_02006E00:
	MOV     R6, #0
	BX      LR

@ Prevent freezing flag being set on level load
repl_02006AE8:
	BX      LR