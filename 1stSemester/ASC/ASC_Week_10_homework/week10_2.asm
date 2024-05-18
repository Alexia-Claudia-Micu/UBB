bits 32 

global start        

extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf

segment data use32 class=data
    ; Read a number in base 10 from the keyboard and display the value of that number in base 16
    
    a dd 0
    b dw 0
    result resw 1
    message  db "n=", 0  ; char strings for C functions must terminate with 0(value, not char)
	formatd  db "%d", 0  ; %d <=> a decimal number (base 10)
	formatx  db "%x", 0  ; %d <=> a decimal number (base 10)
	formatq  db "%lld", 0  ; %d <=> a decimal number (base 10)
    
segment code use32 class=code
    start:
        
        push dword a       ; ! addressa of n, not value
        push dword formatd
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
        
        push dword [a]
        push dword formatx
        call [printf]
        add esp, 4 * 2
        
        push    dword 0      
        call    [exit]       
