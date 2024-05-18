; this code uses files
bits 32

global start

extern exit, fread, fprintf, scanf, printf, fopen, fclose
import exit msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    n dd 0
    file_name_r db "text.txt", 0
    file_name_w db "ana.txt", 0    
    access_mode_r db "r", 0
    access_mode_w db "w", 0
    file_descriptor dd -1
    
    len equ 100
    text times (len+1) db 0
    format_m db "char read :%d, text is: %s", 0
    format_d db "%d", 0

segment code use32 class=code
    start:
    push dword access_mode_r
    push dword file_name_r
    call [fopen]
    add esp, 4*2
    
    mov [file_descriptor], eax
    cmp eax, 0
    je final
    
    push dword [file_descriptor]
    push dword len
    push dword 1
    push dword text
    push dword format_d
    call [fread]
    add esp, 4*5
    
    pushad
    
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    push dword access_mode_w
    push dword file_name_w
    call [fopen]
    add esp, 4*2
    
    mov [file_descriptor], eax
    cmp eax, 0
    je final
    
    popad
    push dword [text]
    push dword format_d
    push dword [file_descriptor]
    call [fprintf]
    add esp, 4*4
    
    push dword [file_descriptor]
    call [fclose]   
    

    final:
    push dword 0
    call [exit]