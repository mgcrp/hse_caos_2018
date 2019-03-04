	.section	.rodata
format:	.string	"%llu\n"

	.text
	.global process

process:
	pushl	%ebp			// Prologue
	movl	%esp,	%ebp
	pushl	%esi
	pushl	%edi

	movl	$A,	%edx		// copy A to edx (we are not allowed to modify it); [ecx][eax]
	movl	(%edx),	%eax		// placing a half of bytes to eax;
	movl	4(%edx),	%ecx	// and the other half - to ecx;
	shll	$1,	%eax		// shifting the last half to the left, saving the very left byte to Carry Flag;
	rcll	$1, %ecx		// shifting the first half to the left,
					// adding the Carry Flag value as the very right byte;

	movl	$B, 	%edx		// copy A to edx (we are not allowed to modify it); [edi][esi]
	movl	(%edx),	%esi		// placing a half of bytes to esi;
	movl	4(%edx),	%edi	// and the other half - to edi;
	shrl	$1,	%edi		// shifting the first half to the right, saving the very right byte to Carry Flag;
	rcrl	$1,	%esi		// shifting the last half to the right,
					// adding the Carry Flag value as the very left byte;

	subl	%esi,	%eax		// eax -= esi
	sbbl	%edi,	%ecx		// ecx -= edi (having in mind Carry Flag value from the previous operation)

	pushl	%ecx			// [ecx]
	pushl	%eax			// [eax][ecx]
	pushl	$format			// [format][eax][ecx]
	call	printf			// printing values from stack
	addl	$12,	%esp

	popl	%edi			// Epilogue
	popl	%esi
	popl	%ebp
	ret