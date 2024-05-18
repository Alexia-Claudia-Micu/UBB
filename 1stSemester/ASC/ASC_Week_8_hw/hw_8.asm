bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 dw 1432h, 8675h, 0ADBCh
    lenS1 equ $ - s1
    d times lenS1 dd 0
    lenS2 equ 4
    s2 times lenS2 db 0
    b equ 4
    p equ 8
    aux db 0
    c_len_d dd 0
    x1 dd 0
    x2 dd 0
    x3 dd 0
    
; our code starts here
segment code use32 class=code
    start:
        
        mov esi, s1
        cld
        mov ecx, lenS1
        
        iterate_s:
        
            mov [x1], ecx
            mov ecx, 100
            mov ebx, 0
            lodsw
            get_digits:            
                mov edx, 0
                or dx, 0000_0000_0000_1111b
                and dx, ax
                mov [s2 + ebx], dx
                ror ax, 4
                inc ebx
                cmp ebx, 4
                je stop_digits
            loop get_digits
            stop_digits:
            mov ebx, 0
            mov edx, 0
            cmp edx, 0
            je sort_i
            out_sort_i:
            mov ebx, [c_len_d]
            mov eax, [s2]
            mov [d+ebx], eax
            add ebx, 4
            mov [c_len_d], ebx
            mov ecx, [x1]
            dec ecx
        loop iterate_s
        mov edx, 0
        cmp edx, 0
        je finish
        sort_i:
            mov ebx, edx
            add ebx, 1
            mov al, [s2+edx]
            sort_j:
                mov ah, [s2+ebx]
                cmp al, ah
                ja dont_switch    
                mov [s2+ebx], al
                mov [s2+edx], ah
                ror ax, p
                dont_switch:
                inc ebx
                cmp ebx, 4
                je out_sort_j
            loop sort_j  
            out_sort_j:
            add edx, 1
            cmp edx, 3
            je out_sort_i
        loop sort_i
        finish:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
