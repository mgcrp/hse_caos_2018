	.text
	.global	print_fib

print_fib:
	pushl	%ebp		# Prologue
	movl	%esp,	%ebp

	movl	A,	%eax	# eax = A
	addl	B,	%eax	# eax = A + B = fib1
	movl	B,	%ecx	# ecx = B
	addl	%eax,	%ecx	# ecx = B + (A + B) = fib2
	movl	%eax,	%edx	# edx = (A + B)
	addl	%ecx,	%edx	# edx = (A + B) + (B + (A + B)) = fib3
	push	%edx		# fib3 to stack
	push	%ecx		# fib2 to stack
	push	%eax		# fib1 to stack
	push	$format		# add format to stack
	call	printf		# print all above
	addl	$16,	%esp

	popl	%ebp		# Epilogue
	ret

format:	.string	"%d %d %d\n"