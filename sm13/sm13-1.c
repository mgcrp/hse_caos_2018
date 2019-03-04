#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

enum {
    DAY_IN_SECONDS = 86400,
    BUF_SIZE = 20
};

int main() {
    int32_t days_in;
    time_t temp_delta_time;
    time_t temp_final_time;
    while (scanf("%" SCNd32, &days_in) == 1) {
        time_t current_time = time(NULL);
        if (__builtin_mul_overflow(days_in, DAY_IN_SECONDS, &temp_delta_time)) {
            printf("OVERFLOW\n");
            continue;
        }
        if (__builtin_add_overflow(current_time, temp_delta_time, &temp_final_time)) {
            printf("OVERFLOW\n");
            continue;
        }
        char buf[BUF_SIZE];
        strftime(buf, BUF_SIZE, "%F", localtime(&temp_final_time));
        printf("%s\n", buf);
    }
    return 0;
}
