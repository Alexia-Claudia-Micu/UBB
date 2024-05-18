bits 32 

global start        

extern exit             
import exit msvcrt.dll    

segment data use32 class=data
;Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate caracterele speciale (!@#$%^&*) din sirul S.

s db '+', '2', '@', 'a', '4', '3', '$', '*'
lenS equ $ - s
d times lenS db 0
sc db '!','@','#','$','%','^','&','*'
lenSC equ $ - sc
c dw 0
s1 dd 0
s2 dd 0

;Se dau 2 siruri de octeti S1 si S2 de aceeasi lungime. 
;Sa se construiasca sirul D astfel incat fiecare element
; din D sa reprezinte maximul dintre elementele de pe
;pozitiile corespunzatoare din S1 si S2.

sir1 db 1,3,6,2,3,7
sir2 db 6,3,8,1,2,5
lenSir equ $ - sir2
d1 times lenSir db 0

segment code use32 class=code
    start:
        
        mov ecx, 0
        mov cx, lenS
        mov esi, 0
        mov edx, 0
        jcxz sf
        iterate_string:
            mov al, [s+esi]
           
            mov [c], cx
            mov cx, lenSC
            mov [s1], esi
            mov esi, 0
            
            iterate_special_char:
                mov bl, [sc+esi]
                cmp al, bl
                
                jnz dont_add
                    mov [s2], esi
                    mov esi, edx
                    mov [d+esi], al
                    mov esi, [s2]
                    add edx, 1
                    
                dont_add:
                inc esi
                
            loop iterate_special_char            
            
            mov esi, [s1]
            mov cx, [c]
                            
            inc esi
        loop iterate_string
        sf:
        
        mov ecx, 0
        mov cx, lenSir
        mov esi, 0
        jecxz sf1
        iterate_array:
            mov al, [sir1+esi]
            mov ah, [sir2+esi]
            cmp al, ah
            jae move_al
            mov al, ah
            move_al:
            mov [d1+esi], al            
            inc esi
        loop iterate_array
        sf1:
        
        push    dword 0   
        call    [exit]    
