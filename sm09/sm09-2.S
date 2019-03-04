	.text
	.global satsum

satsum:
	push	%ebp			# Prologue
	movl	%esp,	%ebp

	movl	8(%ebp),	%eax	# eax = first
	addl	12(%ebp),	%eax	# eax = first + second
	jnc	end			# if (Carry Flag == 0): ok, go end
	movl	$0,	%eax		# else: eax = 0
	notl	%eax			# eax = ~0 == MAX_INT

end:
	popl	%ebp			# Epilogue
	ret