section .data
	msg1 db 'Enter the string:', 0xa
	len1 equ $ - msg1
	msg2 db 'Enter the character:', 0xa
	len2 equ $ - msg2
	msg3 db 'Character count:', 0xa
	len3 equ $ - msg3
	
section .bss
	str1 resb 100
	chr resb 1
	count resb 10
	
section .text
	global _start
_start:
	mov eax, 4
	mov ebx, 1
	lea ecx, [msg1]
	mov edx, len1
	int 0x80
	
	mov eax, 3
	mov ebx, 0
	lea ecx, [str1]
	mov edx, 100
	int 0x80
	
	mov byte[str1 + eax - 1], 0
	
	mov eax, 4
	mov ebx, 1
	lea ecx, [msg2]
	mov edx, len2
	int 0x80
	
	mov eax, 3
	mov ebx, 0
	lea ecx, [chr]
	mov edx, 1
	int 0x80
	
	xor ecx, ecx
	lea esi, [str1]
	mov al, [chr]
	
count_loop:
	mov bl, [esi]
	cmp bl, 0
	je done
	cmp bl, al
	jne next_char
	inc ecx
	
next_char:
	inc esi
	jmp count_loop
	
done:
	mov [count], ecx
	
	mov eax, 4
	mov ebx, 1
	lea ecx, [msg3]
	mov edx, len3
	int 0x80
	
	mov eax, [count]
	add eax, '0'
	mov [count], al
	
	mov eax, 4
	mov ebx, 1
	lea ecx, [count]
	mov edx, 1
	int 0x80
	
	mov eax, 1
	xor ebx, ebx
	int 0x80
