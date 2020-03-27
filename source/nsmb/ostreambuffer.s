.global _ZN7ostream13stream_bufferEj
.global _ZN7ostream13stream_bufferEy
_ZN7ostream13stream_bufferEj:
_ZN7ostream13stream_bufferEy:
	mov   r12,r12   
	b     skip      
	.word 0x00006464
	.fill 120       
	.word 0         
skip:           
	bx    lr
.global _ZN7ostream14buffer_arr_u32E
.global _ZN7ostream15buffer_arr_charE
_ZN7ostream14buffer_arr_u32E  = _ZN7ostream13stream_bufferEj + 12
_ZN7ostream15buffer_arr_charE = _ZN7ostream13stream_bufferEj + 12