section .data
	str1 resb 20
	str2 resb 20
	msg_equal db 'Strings are equal', 0
	msg_not_equal db 'Strings are not equal', 0
	
section .text
	global _start
	
_start:
	mov eax, 3
	mov ebx, 0
	mov ecx, str1
	mov edx, 20
	int 0x80
	mov esi, str1
	
	mov eax, 3
	mov ebx, 0
	mov ecx, str2
	mov edx, 20
	int 0x80
	mov edi, str2
	
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
	mov ecx, msg_not_equal
	mov edx, 23
	int 0x80
	jmp exit_program
	
strings_equal:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg_equal
	mov edx, 20
	int 0x80
	
exit_program:
	mov eax, 1
	xor ebx, ebx
	int 0x80
