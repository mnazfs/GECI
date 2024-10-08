section .data:
    prompt1 db "Enter string: ", 0
    l1 equ $ - prompt1
    prompt2 db "String is palindrome", 0xa
    l2 equ $ - prompt2
    prompt3 db "String is not palindrome", 0xa
    l3 equ $ - prompt3

section .bss
	original resb 20
	reversed resb 20

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
	mov edx, 20
	int 0x80
	
	mov esi, original
	
	mov ecx, 20
	xor eax, eax
	
find_length:
	cmp byte [esi+ecx-1], 0
	jnz found_length
	loop find_length
	
found_length:
	sub ecx, 1

loop1:
	mov al, [esi+ecx]
	mov [edi], al
	inc edi
	dec ecx
	jns loop1

	mov byte [edi], 0

	mov edi, reversed

compare_loop:
	mov al, [esi]
	mov bl, [edi]
	cmp al, bl
	jne strings_not_equal
	
	test al, al
	jz strings_equal
	
	inc esi
	inc edi
	jmp compare_loop
	
strings_not_equal:
	mov eax, 4
	mov ebx, 1
	mov ecx, prompt3
	mov edx, l3
	int 0x80
	jmp exit
	
strings_equal:
	mov eax, 4
	mov ebx, 1
	mov ecx, prompt2
	mov edx, l2
	int 0x80

exit:
	mov eax, 1
	xor ebx, ebx
	int 0x80
