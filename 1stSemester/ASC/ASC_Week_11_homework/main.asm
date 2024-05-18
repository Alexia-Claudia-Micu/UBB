bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
extern convert
                          
segment data use32 class=data
	n dd  0       ; in this variable we'll store the value read from the keyboard
    ; char strings are of type byte
	message  db "string=", 0  ; char strings for C functions must terminate with 0(value, not char)
	format  db "%s", 0  ; %d <=> a decimal number (base 10)
    
segment code use32 class=code
    start:
       
        ; will call printf(message) => will print "n="
        ; place parameters on stack
        push dword message ; ! on the stack is placed the address of the string, not its value
        call [printf]      ; call function printf for printing
        add esp, 4*1       ; free parameters on the stack; 4 = size of dword; 1 = number of parameters
                                                   
        ; will call scanf(format, n) => will read a number in variable n
        ; place parameters on stack from right to left
        push dword format
        call [scanf]       ; call function scanf for reading
        call [convert]
        
        ; exit(0)
        push dword 0      ; place on stack parameter for exit
        call [exit]       ; call exit to terminate the program