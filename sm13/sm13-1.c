#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <stdint.h>

int main() {
    int32_t ttime;
    time_t unixt;

    while (scanf("%" SCNd32, &ttime) == 1) {
        time_t cur = time(NULL);
        if (__builtin_mul_overflow(ttime, 24*3600, &unixt) || __builtin_add_overflow(cur, unixt, &cur)) {
            printf("OVERFLOW\n");
            continue;
        }
        char buf[20];
        strftime(&buf, 20, "%F", localtime(&cur));
        printf("%s\n", buf);
    }

    return 0;
}
