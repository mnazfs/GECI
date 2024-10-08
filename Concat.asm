section .bss
    str1 resb 20
    str2 resb 20
    result resb 40

section .text
    global _start

_start:
    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 20
    int 0x80

    mov esi, str1
    call remove_newline

    mov esi, str1
    mov edi, result
    call copy_string

    mov eax, 3
    mov ebx, 0
    mov ecx, str2
    mov edx, 20
    int 0x80

    mov esi, str2
    call remove_newline

    mov esi, str2
    call copy_string

    sub edi, result
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, edi
    int 0x80

    mov eax, 1
    xor ebx, ebx
    int 0x80

copy_string:
    next_char:
        lodsb
        stosb
        test al, al
        jnz next_char
    dec edi
    ret

remove_newline:
    find_newline:
        lodsb
        cmp al, 10
        je replace_newline
        test al, al
        jz end_newline
        jmp find_newline
    replace_newline:
        dec esi
        mov byte [esi], 0
    end_newline:
        ret

