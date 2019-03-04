# version 1

	.text
	.global	print_fib

print_fib:
	pushl	%ebp
	movl	%esp,	%ebp

	movl	A,	%eax
	addl	B,	%eax
	movl	B,	%ecx
	addl	%eax,	%ecx
	movl	%eax,	%edx
	addl	%ecx,	%edx
	push	%edx
	push	%ecx
	push	%eax
	push	$str
	call	printf
	addl	$16,	%esp

	popl	%ebp
	ret

str:	.string	"%d %d %d\n"

# version 2

.section .rodata
	format:	.string	"%d %d %d\n"

	.text
	.global	print_fib

print_fib:
	pushl	%ebp
	movl	%esp,	%ebp

	movl	A,	%ebx
	addl	B,	%ebx
	pushl	%ebx
	movl	%ebx,	%edi
	addl	B,	%ebx
	pushl	%ebx
	addl	%edi,	%ebx
	pushl	%ebx
	pushl	format
	call	printf

	movl	%ebp,	%esp
	ret