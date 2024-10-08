section .data
    prompt1 db "Enter string: ", 0
    l1 equ $ - prompt1
    prompt2 db "String is palindrome", 0xa
    l2 equ $ - prompt2
    prompt3 db "String is not palindrome", 0xa
    l3 equ $ - prompt3

section .bss
    original resb 100
    reversed resb 100

section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt1
    mov edx, l1
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, original
    mov edx, 100
    int 0x80

    dec eax
    cmp byte [original + eax], 10
    jne skip_newline
    mov byte [original + eax], 0
    dec eax

skip_newline:
    mov esi, original
    mov edi, reversed
    mov ecx, eax

reverse:
    cmp ecx, 0
    jl done_reversing
    mov al, [esi + ecx]
    mov [edi], al
    inc edi
    dec ecx
    jmp reverse

done_reversing:
    mov byte [edi], 0

    mov esi, original
    mov edi, reversed
    mov ecx, eax

	mov eax, 4
	mov ebx, 1
	mov ecx, reversed
	mov edx, 100
	int 0x80

check_palindrome:
    cmp ecx, 0
    jl is_palindrome
    mov al, [esi]
    mov bl, [edi]
	mov eax, 4
	mov ebx, 1
	mov ecx, esi
	mov edx, 1
	int 0x80
	mov eax, 4
	mov ebx, 1
	mov ecx, edi
	mov edx, 1
	int 0x80
    cmp al, bl
    jne not_palindrome
    inc esi
    inc edi
    dec ecx
    jmp check_palindrome

not_palindrome:
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt3
    mov edx, l3
    int 0x80
    jmp exit

is_palindrome:
    mov eax, 4
    mov ebx, 1
    mov ecx, prompt2
    mov edx, l2
    int 0x80

exit:
    mov eax, 1
    xor ebx, ebx
    int 0x80
