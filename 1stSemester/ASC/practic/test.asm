bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fread, fopen, fclose, printf              
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fclose msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fread msvcrt.dll    
import printf msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    descriptor times 30 db 0
    file_name db "read.txt", 0
    access_mode db "r", 0
    char dd 0
    vocale db "aeiouAEIOU", 0
    nr_voc dd 0
    format dd "Number of vocals: %d, they are: %s", 0
    text times 100 db 0
    
; our code starts here
segment code use32 class=code
    start:
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [descriptor], eax
        cmp eax, 0
        je final
        
        cld
        mov edi, text
        
        read:
            push dword [descriptor]
            push dword 1
            push dword 1
            push dword char
            call [fread]
            add esp, 4*4
            
            mov eax, [char]
            cmp eax, '!'
            je file_done
            
            cld
            mov esi, vocale
            mov ecx, 10
            iterate_vocals:
            
                lodsb
                cmp al, [char]
                jne not_voc
                    add dword [nr_voc], 1
                    stosb
                not_voc:
            loop iterate_vocals
            
        jmp read
        
        file_done:
            push dword [descriptor]
            call [fclose]
        
        push dword text
        push dword [nr_voc]
        push dword format
        call [printf]
        add esp, 4*2

        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
