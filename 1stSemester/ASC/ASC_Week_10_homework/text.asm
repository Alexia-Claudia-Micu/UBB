; The following code will open a file called "ana.txt" from current folder,
; it will read maximum 100 characters from this file,
; and it will display to the console the number of chars and the text we've read.

; The program will use:
; - the function fopen() to open/create the file
; - the function fread() to read from file
; - the function printf() to display a text
; - the function fclose() to close the created file.

; Because the fopen() call uses the file access mode "r", the file will be open for
; reading. The file must exist, otherwise the fopen() call will fail.
; For details about the file access modes see the section "Theory".

; Any string used by printf() must be null-terminated ('\0').

bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf, scanf, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)z
segment data use32 class=data
    file_name db "print.txt", 0   ; filename to be read
    access_mode db "a", 0       ; file access mode:
                                ; r - opens a file for reading. The file must exist.
    file_descriptor dd -1       ; variable to hold the file descriptor
    len equ 100                 ; maximum number of characters to read
    text times 100 dd 0    ; string to hold the text which is read from file
    format db "We've read %d chars from file. The text is: %s", 0
    formats  db "%s", 0
    formatd  db "%d", 0

; our code starts here
segment code use32 class=code
    start:
        read:
        push dword text
        push dword formatd
        call [scanf]
        add esp, 4*2
        
        cmp dword[text], 0
        je final
        
        mov ax, [text]
        mov dx, [text+2]
        mov bx, 7
        div bx
        cmp dx, 0
        jz print_nr
        jmp read
        
        jmp final
        print_nr:
        pushad
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
        push dword text
        push dword formats
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        popad
        jmp read

      final:

        ; exit(0)
        push dword 0
        call [exit]