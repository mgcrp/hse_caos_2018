#include <stdio.h>

unsigned int satsum(unsigned int a, unsigned int b);

int main() {
	unsigned int res = satsum(4294967290, 20);
	printf("%u\n", res);
	return 0;
}
