bits 32 

global start        

extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf

segment data use32 class=data
    ;Read two numbers a and b (in base 10) from the keyboard and calculate a/b. 
    ;This value will be stored in a variable called "result" (defined in the data segment). 
    ;The values are considered in signed representation.
    
    a dd 0
    b dw 0
    result resw 1
    message  db "n=", 0  ; char strings for C functions must terminate with 0(value, not char)
	formatd  db "%d", 0  ; %d <=> a decimal number (base 10)
	formatc  db "%c", 0  ; %d <=> a decimal number (base 10)
	formatq  db "%lld", 0  ; %d <=> a decimal number (base 10)
    
segment code use32 class=code
    start:
        
        push dword a       ; ! addressa of n, not value
        push dword formatd
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
        
        push dword b       ; ! addressa of n, not value
        push dword formatd
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
        
        mov ax, [a]
        mov dx, [a + 2]
        mov bx, [b]
        idiv bx ; dx:ax / bx - > result in ax
        
        mov [result], ax
        
        push    dword 0      
        call    [exit]       
