#include <stdio.h>

void myhypot(double x, double y, double *r);

int main() {
	double r;
	myhypot(3.0, 4.0, &r);
	printf("%lf\n", r);
	return 0;
}
