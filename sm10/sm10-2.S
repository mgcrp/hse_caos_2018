	.text
	.global myhypot

myhypot:
	pushl	%ebp			// Prologue
	movl	%esp,	%ebp

	movsd	8(%ebp),	%xmm0	// copy first double to xmm0
	movsd	%xmm0,	%xmm1		// xmm1 = xmm0
	movsd	16(%ebp),	%xmm2	// copy second double to xmm2
	movsd	%xmm2,	%xmm3		// xmm3 = xmm2
	mulsd	%xmm1,	%xmm0		// xmm0 = xmm0 * xmm1
	mulsd	%xmm3,	%xmm2		// xmm2 = xmm2 * xmm3
	addsd	%xmm2,	%xmm0		// xmm0 = xmm0 + xmm2
	sqrtsd	%xmm0,	%xmm0		// xmm0 = sqrt(xmm0)
	movl	24(%ebp),	%eax	// eax = &r
	movsd	%xmm0,	(%eax)		// *r = xmm0

	popl	%ebp			// Epilogue
	ret