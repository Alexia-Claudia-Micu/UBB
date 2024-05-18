; this uses the keyboard - reading and printing

; need to import the scanf function

bits 32 ; nr of bits on which the processor works

global start ; import start function

extern exit ; import external function
extern scanf
extern printf

import exit msvcrt.dll ; tell the assembler where to find the exit function
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    message db "read> ", 0
    format_c db "%c", 0
    format_d db "%d", 0
    format_u db "%u", 0
    format_x db "%x", 0
    format_s db "%s", 0
    format_lld db "%lld", 0
    output db "eax: %d, text: %s, char: %c", 0
    n dq 0

    
segment code use32 class=code
    start:
    
    push dword message
    push dword format_s
    call [printf]
    add esp, 4*2
    
    push dword n
    push dword format_s
    call [scanf]
    add esp, 4*2
    
    push dword [n]
    push dword n
    mov eax, 17
    push dword eax
    push dword output
    call [printf]
    add esp, 4*4

    
    push dword 0
    call [exit]