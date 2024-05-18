bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions

; our variables are declared here (the segment is called data) 
segment data use32 class=data

; additions subtractions
; a - byte, b - word, c - double word, d - qword - Unsigned representation
; eg 2: (b+b)+(c-a)+d

a1 db 10h
b1 dw 1302h
c1 dd 128028h
d1 dq 2192371087979h

; Multiplications, divisions - Unsigned representation and signed representation
; ex 2: 2/(a+b*c-9)+e-d; a,b,c-byte; d-doubleword; e-qword

a2 db 79h
b2 db 32h
c2 db 123h
d2 dd 92332890h
e2 dq 12345678987654h

a3 db -79h
b3 db -32h
c3 db 123h
d3 dd 10332890h
e3 dq 12345678987654h

; ex 17: x-(a*a+b)/(a+c/a)
; a,c-byte; b-doubleword; x-qword
; unsigned

a4 db 56h
b4 dd 12345432h
c4 db 12h
x4 dq 1122334455667788h

a5 db -5h
b5 dd -232h
c5 db -12h
x5 dq 1122334455667788h

segment code use32 class=code
start:

    ; additions subtractions
    ; a - byte, b - word, c - double word, d - qword - Unsigned representation
    ; ex 2: (b+b)+(c-a)+d
    
    ;mov ebx, 0
    ;mov bx, [b1]
    ;add bx, [b1] ; bx = (b+b)
    
    ;mov ecx, [c1]
    ;mov eax, 0
    ;mov al, [a1]
    ;cbw
    ;cwd
    ;sub ecx, eax ; ecx = (c-a)
    
    ;add ebx, ecx ; ebx = (b+b)+(c-a)
    ;mov eax, [d1]
    ;mov ecx, [d1+4]
    ;add ebx, eax
    ;adc ecx, 0
    
    ; ex 17: (c+c-a)-(d+d)-b
    
    ;mov eax, 0
    ;mov eax, [c1]
    ;add eax, [c1]
    ;mov ebx, 0
    ;mov bl, [a1]
    ;sub eax, ebx ; eax = (c + c - a)
    
    ;mov ebx, [d1]
    ;mov edx, [d1+4] ;edx:ebx=d
    ;add ebx, [d1]
    ;adc edx, [d1+4] 
    ; edx:ebx = d+d1
    ;mov ecx,0
   
    ;sub eax,ebx
    ;sbb ecx,edx ; eax:ecx = (c+c-a)-(d+d)
    
    ;sub cx, [b1]
    ;sbb eax, 0
    
    ; a - byte, b - word, c - double word, d - qword - Signed representation
    ; ex 2: (c+b)-a-(d+d)
    
    ;mov eax, [c1]
    ;mov ebx, 0
    ;mov bx, [b1]
    ;add eax, ebx ; eax = c + b
    ;mov ebx, 0
    ;mov bl, [a1]
    ;sub eax, ebx ; eax = (c+b) - a
    ;mov ebx, [d1]
    ;mov ecx, [d1+4]
    ;add ebx, [d1]
    ;adc ecx, [d1+4] ; ecx:ebx = (d+d)
    ;mov edx, 0
    ;sub eax, ebx
    ;sbb edx, ecx ; eax:edx = (c+b)-a-(d+d)
    
    ; ex 17: (c+d-a)-(d-c)-b
    
    ;mov eax, [c1]
    ;mov ebx, 0
    ;add eax, [d1]
    ;adc ebx, [d1+4] ; ebx:eax = (c+d)
    
    ;mov ecx, 0
    ;mov cl, [a1]
    ;add eax, ecx
    ;adc ebx, 0 ; ebx:eax = (c+d-a)
    
    ;mov ecx, [d1]
    ;mov edx, [d1+4]
    ;sub ecx, [c1]
    ;sbb edx, 0 ; edx:ecx = (d-c)
    
    ;sub eax, ecx
    ;sbb ebx, edx ; ebx:eac = (c+d-a)-(d-c)
    
    ;mov ecx, 0
    ;mov cx, [b1]
    ;sub eax, ecx
    ;sbb ebx, 0 ; ebx:eax = (c+d-a)-(d-c)-b
    
    ;Multiplications, divisions - Unsigned representation and signed representation
    ; ex 2: 2/(a+b*c-9)+e-d
    ; a,b,c-byte; d-doubleword; e-qword
    ;unsigned
    
    ;mov eax, 0
    ;mov al, [b2]
    ;mul byte [c2] ; ax = b*c - word
    ;mov bx, 0
    ;mov bl, [a2]
    ;add ax, bx ; ax = a+b*c
    ;sub ax, 9 ; ax = a+b*c-9 - word
    
    ;mov bx, ax ; bx = a+b*c-9
    ;mov dx, 0
    ;mov ax, 2h ; need to divide a double word (dx:ax) by a word
    ;div word bx ; eax/bx -> ax = 2/(a+b*c-9)
    
    ;mov ebx, 0
    ;mov bx, ax ; bx = 2/(a+b*c-9)
    ;mov eax, 0
    ;add ebx, [e2]
    ;adc eax, [e2+4] ; eax:ebx = 2/(a+b*c-9) + e
    ;sub ebx, [d2]
    ;sbb eax, 0 ; eax:ebx = 2/(a+b*c-9)+e-d
    
    ; ex 2: 2/(a+b*c-9)+e-d
    ; a,b,c-byte; d-doubleword; e-qword
    ; signed
    
    ;mov ax, 0
    ;mov al, [b3]
    ;imul byte [c3] ; ax = b*c -> word
    
    ;mov bx, ax ; bx = b*c
    ;mov eax, 0
    ;mov al, [a3]
    ;cbw ; ax = a
    ;add ax, bx ; ax = a+b*c
    ;sub ax, 9 ; ax = a+b*c-9
    ;mov bx, ax ; bx = a+b*c-9
    
    ;mov dx, 0
    ;mov ax, 2h ; need to divide double word dx:ax to word bx
    ;idiv word bx ; dx:ax = 2/(a+b*c-9) -> the result is word ax
    ;cwd
    ;cdq ; result is in edx:eax
    ;add eax, [e3]
    ;adc edx, [e3+4] ; edx+eax = 2/(a+b*c-9)+e
    ;mov ebx, eax
    ;mov ecx, edx ; ecx:ebx = 2/(a+b*c-9)+e
    ;mov eax, [d3] 
    ;cdq ; edx:eax = d
    ;sub ebx, eax
    ;sbb ecx, edx
    
    ; ex 17: x-(a*a+b)/(a+c/a)
    ; a,c-byte; b-doubleword; x-qword
    ; unsigned
    
    ;mov ax, 0
    ;mov al, [c4] ; c from byte to word
    ;div byte [a4] ; al = c/a -> result is a byte
    ;add al, [a4] ; al = a +c/a
    ;mov cx, 0
    ;mov cl, al
    
    ;mov eax, 0
    ;mov al, [a4]
    ;mul byte [a4] ; ax = a*a -> result is a word
    ;add eax, ebx ; eax = a*a +b 
    ;push eax
    ;pop ax
    ;pop dx; eax is split on dx:ax
    ;div word cx ; ax = dx:ax / cx => ax = (a*a+b)/(a+c/a)
    
    ;mov ebx, 0
    ;mov bx, ax
    ;mov eax, [x4]
    ;mov edx, [x4+4]
    ;sub eax, ebx
    ;sbb edx, 0
    
    ; ex 17: x-(a*a+b)/(a+c/a)
    ; a,c-byte; b-doubleword; x-qword
    ; signed
    mov al, [c5]
    cbw
    idiv byte [a5] ; al = c/a
    add al, [a5] ; al = a+c/a
    cbw ; ax = a+c/a
    mov cx, ax ; cx = a+c/a
    
    mov al, [a5]
    imul byte [a5] ; ax = a*a
    cwd ; dx:ax = a*a
    push dx
    push ax
    pop eax ; eax = a*a
    add eax, [b5]
    push eax
    mov eax, 0
    mov edx, 0
    pop ax
    pop dx ; dx:ax = a*a+b
    idiv word cx ; ax = (a*a+b)/(a+c/a)
    cwd
    cdq ; edx:eax = (a*a+b)/(a+c/a)
    mov ebx, [x4]
    mov ecx, [x4+4] ;ecx:ebx = x
    sub ebx, eax
    sbb ecx, edx ; ecx:ebx = x-(a*a+b)/(a+c/a)
    
    
    
    
    
    
    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program