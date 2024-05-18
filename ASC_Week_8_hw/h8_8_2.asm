bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 DD 12345678h, 1256ABCDh, 12AB4344h
    len equ $ - s1
    s2 times len dd 0
    b equ 4
    p equ 8
    c_len_d dd 0
    x1 dd 0
    lenS1 db 0
    two db 2
    
; our code starts here
segment code use32 class=code
    start:
        
        mov ax, 0
        mov ax, len
        div byte [two]
        mov [lenS1], al
        
        mov esi, s1
        cld
        
        mov ecx, 0
        mov cl, [lenS1]
        mov ebx, 0
        
        get_low: 
            lodsd
            mov edx, 0
            or edx, 1111_1111_1111_1111b
            and edx, eax
            mov [s2 + ebx], edx
            inc ebx
            inc ebx
            cmp bl, byte [lenS1]
            je stop_get_low
        loop get_low
        stop_get_low:
        
        mov edx, 0
        mov ebx, 0
        sort_i:
            cmp dl, byte [lenS1]
            ja out_sort_i
            mov ebx, edx
            add ebx, 2
            mov ax, [s2+edx]
            sort_j:
                mov cx, [s2+ebx]
                cmp ax, cx
                ja dont_switch    
                mov [s2+ebx], ax
                mov [s2+edx], cx
                mov [x1], ax
                mov ax, cx
                mov cx, [x1]
                dont_switch:
                inc ebx
                inc ebx
                cmp bl, byte [lenS1]
                je out_sort_j
            loop sort_j  
            out_sort_j:
            add edx, 2
            cmp bl, byte [lenS1]
            je out_sort_i
        loop sort_i
        out_sort_i:
        
        mov esi, s2
        mov edi, s1
        mov ecx, 0
        mov cl, byte [lenS1]
        cld
        change:
            movsw
            sub ecx, 2
            add edi, 2
        loop change
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
