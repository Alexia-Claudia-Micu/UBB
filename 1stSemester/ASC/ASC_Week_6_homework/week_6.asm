bits 32
global start

extern exit
import exit msvcrt.dll  

segment data use32 class=data
    
    ; ex 2: Given the words A and B, compute the doubleword C as follows:
    ;the bits 0-3 of C are the same as the bits 5-8 of B
    ;the bits 4-8 of C are the same as the bits 0-4 of A
    ;the bits 9-15 of C are the same as the bits 6-12 of A
    ;the bits 16-31 of C are the same as the bits of B
    
    a1 dw 0111_0111_0101_0111b
    b1 dw 1001_1011_1011_1110b
    c1 dd 0b
    
    ; ex 17: Given the word A and the byte B, compute the doubleword C:
    ;the bits 0-3 of C have the value 1
    ;the bits 4-7 of C are the same as the bits 0-3 of A
    ;the bits 8-13 of C have the value 0
    ;the bits 14-23 of C are the same as the bits 4-13 of A
    ;the bits 24-29 of C are the same as the bits 2-7 of B
    ;the bits 30-31 have the value 1
    
    a2 dw 0111_0111_0101_0111b
    b2 db 1011_1110b
    c2 dd 0b
        
segment code use32 class=code
start:

    ; ex 2
    
    mov ebx, 0 ; we compute the result in bx
    
    mov ax, [b1] ; we isolate the bits 5-8 of B
    and ax, 0000_0001_1110_0000b
    mov cl, 5
    ror ax, cl ; we rotate 5 positions to the right
    or bx, ax ; we put the bits into the result
    
    mov ax, [a1] ; we isolate the bits 0-4 of A
    and ax, 0000_0000_0001_1111b
    mov cl, 4
    rol ax, cl ; we rotate 4 positions to the left
    or bx, ax ; we put the bits into the result
    
    mov ax, [a1] ; we isolate the bits 6-12 of A
    and ax, 0001_1111_1100_0000b
    mov cl, 3
    rol ax, cl ; we rotate 3 positions to the left
    or bx, ax ; we put the bits into the result
    
    mov eax, 0 ; we move the bits of B on the latter half of a dw
    mov ax, [b1]
    mov cl, 16
    rol eax, cl ; we rotate 16 positions to the left
    or ebx, eax ; we put the bits into the result
    
    mov [c1], ebx ; we move the result from the register to the result variable
    
    ; ex 17
    
    mov ebx, 0 ; we compute the result in bx
    
    or bx, 0000_0000_0000_1111b ; make bits 0-3 have the value 1
    
    mov ax, [a2] ; we isolate the bits 0-3 of A
    and ax, 0000_0000_0000_1111b
    mov cl, 4
    rol ax, cl ; we rotate 4 positions to the left
    or bx, ax ; we put the bits into the result
    
    and bx, 0000_0000_1111_1111b ; make bits 8-(13)15 have the value 0
    
    mov eax, 0
    mov ax, [a2] ; we isolate the bits 4-13 of A
    and ax, 0011_1111_1111_0000b
    mov cl, 10
    rol eax, cl ; we rotate 10 positions to the left
    or ebx, eax ; we put the bits into the result
    
    mov eax, 0
    mov ax, [b2] ; we isolate the bits 2-7 of B
    and ax, 0000_0000_1111_1100b
    mov cl, 22
    rol eax, cl ; we rotate 22 positions to the left
    or ebx, eax ; we put the bits into the result
    
    or ebx, 1100_0000_0000_0000_0000_0000_0000_0000b ; make bits 30-31 have the value 1
    
    mov [c2], ebx ; we move the result from the register to the result variable
    
    push dword 0
    call [exit]