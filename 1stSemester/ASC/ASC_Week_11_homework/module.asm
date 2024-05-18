bits 32                         
segment code use32 public code
global convert

convert:
	mov ecx, 16
    mov edx, 0
    mov ah, 0
	
	repeat: 
		lodsb
        
	loop repeat
	ret 4 ; in this case, 4 represents the number of bytes that need to be cleared from the stack (the parameter of the function)