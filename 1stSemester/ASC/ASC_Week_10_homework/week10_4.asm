; The following code will create an empty file called "ana.txt" in the current folder,
; and it will write a text to this file.

; The program will use:
; - the function fopen() to open/create the file
; - the function fprintf() to write a text to file
; - the function fclose() to close the created file.

; Because the program uses the file access mode "w", if a file with the same name already
; exists, its contents will be discarded and the file will be treated as a new empty file.
; For details about the file access modes see the section "Theory".

bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll   

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "numere_7.txt", 0   ; filename to be created
    access_mode db "w", 0       ; file access mode:
                                ; w - creates an empty file for writing
    file_descriptor dd -1       ; variable to hold the file descriptor
    text db ", ", 0  ; text to be write to file
    formatd  db "%d", 0  ; %d <=> a decimal number (base 10)
    a dd 0

; our code starts here
segment code use32 class=code
    start:
        ; call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final

        ; write the text to file using fprintf()
        ; fprintf(file_descriptor, text)
        
        read:
        pushad
        push dword a       ; ! addressa of n, not value
        push dword formatd
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
        cmp dword [a], 0
        je here
        
        mov ax, [a]
        mov dx, [a+2]
        mov bx, 7
        div bx
        cmp dx, 0
        
        popad
        jne not_equal
        
        push dword [a]
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*2
        ;push dword text
        ;push dword [file_descriptor]
        ;call [fprintf]
        ;add esp, 4*2
        not_equal:
        
        jmp read
        here:
        
        
        
        
        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

      final:

        ; exit(0)
        push dword 0      
        call [exit]