#include <stdio.h>

int main()
{
    int a, b, n;
    int i, j;
    scanf("%d %d %d", &a, &b, &n);
    printf("%*c", n, ' ');
    for (i = a; i < b; ++i) {
        printf(" %*d", n, i);
    }
    printf("\n");
    for (i = a; i < b; ++i) {
        printf("%*d", n, i);
        for (j = a; j < b; ++j) {
            printf(" %*lli", n, (long long)i * j);
        }
        printf("\n");
    }
    return 0;
}
