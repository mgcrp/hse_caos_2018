// attempt 1
// not passed


// int getchar(char *c) {
// 	int res;
// 	__asm__ (
// 		"int	$0x80\n\t"
// 		:"=a"(res)
// 		:"a"(3),"b"(0),"c"(c),"d"(1)
// 	);
// 	return res;
// }

char getchar() {
	char res;
	int count:
	__asm__ (
		"movl	%[read],	%%eax\n\t"
		"movl	$0,		%%ebx\n\t"
		"leal	%[res],		%%ecx\n\t"
		"movl	$1,		%%edx\n\t"
		"int	$0x80\n\t"
		"movl 	%%eax,		%[count]"
		:[count]"=m"(count), [res]"=m"(res)
		:[read]"i"(__NR_read)
	);
	if (count == 0) {
		exit(0);
	}
	return res;
}

int putchar(char c) {
	int res;
	__asm__ (
		"int	$0x80\n\t"
		:"=a"(res)
		:"a"(4),"b"(1),"c"(c),"d"(1)
	);
	return res;
}

void _start() {
	char c;
	while ((c = getchar()) != 0) {
		if (('a' <= c) && (c <= 'z')) {
			c += 'A' - 'a';
		}
	}
	putchar(c);

	__asm__ (
		"movl	$1,	%eax\n\t"
		"movl	$0,	%ebx\n\t"
		"int	0x80\n\t"
	);
}
