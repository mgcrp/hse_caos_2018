	.text
	.global _start

_start:
	subl	$4,	%esp

read:
	movl	$3,	%eax
	movl	$0,	%ebx
	leal	(%esp),	%ecx
	movl	$1,	%edx
	int	$0x80
	cmpl	$0,	%eax
	je	stop
	cmpl	$'0',	(%esp)
	jl	write
	cmpl	$'9',	(%esp)
	jg	write

	movl	$'0',	(%esp)
write:
	movl	$4,	%eax
	movl	$1,	%ebx
	leal	(%esp),	%ecx
	movl	$1,	%edx
	int	$0x80
	jmp	read

stop:
	movl	$1,	%eax
	movl	$0,	%ebx
	int	$0x80