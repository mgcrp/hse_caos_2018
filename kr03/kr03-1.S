	.data
A:	.int	0
B:	.int	0
C:	.int	0

	.text
	.global process, A, B, C

process:
	pushl	%ebp		// Prologue
	movl	%esp,	%ebp

	movl	A,	%eax	// eax = A
	mull	X		// eax = A * X
	mull	X		// eax = A * X * X
	mull	X		// eax = A * X * X * X
	movl 	%eax,	%ecx	// ecx = eax
				// ---
	movl	B,	%eax	// eax = B
	mull	X		// eax = B * X
	mull	X		// eax = B * X * X
	shll	$1,	%eax	// eax = 2 * B * X * X
	subl	%eax,	%ecx	// ecx = A*X*X*X - 2*B*X*X

	addl	C,	%ecx	// ecx = A*X*X*X - 2*B*X*X + C

	movl	%ecx,	%eax	// eax = ecx = result

	popl	%ebp		// Epilogue
	ret