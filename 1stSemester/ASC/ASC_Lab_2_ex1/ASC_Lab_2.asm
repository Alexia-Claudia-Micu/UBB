bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions

; our variables are declared here (the segment is called data) 
segment data use32 class=data
; ... 
    a db 5;
    b db 1125h;
    a1 dw 6688h;
    b2 dq 1_23_45_67_89_01_23h;

; the program code will be part of a segment called code
segment code use32 class=code
start:
; ... 
    
    mov al, 3;
    mov eax, 7;
    mov al, 256;
    mov eax, 256;
    mov al, 5;
    add ax, a;
    mov al, 5;
    add al, [a];
    
    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program