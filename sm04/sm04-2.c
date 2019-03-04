#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

// Мантиса числа типа float - 23 бита;
// В float можно точно представить числа, мантиса которых умещается в 24 бита;
enum { MAX_FIT_SIZE = 24 };

bool canBePresentedAsFloat(uint32_t number) {
    int bits_counter = 0;
    bool flag = false;
    while (number != 0) {
        if (number << 1 < number) {
            flag = true;
        }
        if (flag) {
            bits_counter += 1;
        }
        number <<= 1;
    }
    return bits_counter <= MAX_FIT_SIZE;
}

int main() {
    uint32_t number;
    while (scanf("%" PRIu32, &number) == 1) {
        if (canBePresentedAsFloat(number)) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
    return 0;
}
