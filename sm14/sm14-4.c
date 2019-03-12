#include <stdio.h>

int main() {
    long long int answer = 0;
    unsigned long long start, finish;
    // reading two ull's as HEX, then skipping all symbols until '/n'
    while (scanf("%llx-%llx %*[^\n]", &start, &finish) == 2) {
        answer += finish - start;
    }
    printf("%lld\n", answer);
    return 0;
}
