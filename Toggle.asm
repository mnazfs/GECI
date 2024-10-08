section .data
	ql: db "Enter the string:"
	lq1 equ $-ql
section .bss
	string resb 20
section .text
	global _start
	_start:
		mov eax, 4
		mov ebx, 1
		mov ecx, ql
		mov edx, lq1
		int 0x80
		
		mov eax, 3
		mov ebx, 0
		mov ecx, string
		mov edx, 20
		int 0x80
		
		mov byte [ string + eax ], 0
		
		xor ecx, ecx
	toggle:
		mov al, [string + ecx]
		cmp al, 0
		je print
		cmp al, 10
		je store
		cmp al, 'A'
		jl check_lower
		cmp al, 'Z'
		jle convert_lower
		jmp check_lower
		
	convert_lower:
		add al, 32
		mov [string + ecx], al
		jmp store
		
	check_lower:
		cmp al, 'a'
		jl store
		cmp al, 'z'
		jle convert_upper
		jmp store
		
	convert_upper:
		sub al, 32
		mov [string + ecx], al
		jmp store
		
	store:
		inc ecx
		jmp toggle
		
	print:
		mov edx, ecx
		sub edx, string
		
		mov eax, 4
		mov ebx, 1
		mov ecx, string
		int 0x80
		
		mov eax, 1
		xor ebx, ebx
		int 0x80
