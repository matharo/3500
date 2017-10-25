#compile with gcc -m32 abs.s -o abs

.text
.global main

main:
	movl	($0x1100),	%eax
	movl	($0x1104),	%ebx
	movl	%eax,		($0x1104)
	movl	%ebx,		($0x1100)

	leave
	ret
