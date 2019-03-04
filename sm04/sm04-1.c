#include <stdio.h>
#include <stdint.h>

enum
{
    SGN = 1,
    EXP = 8,
    MAN = 23
};

union Number
{
    float f;
    uint32_t i;
};

uint32_t get_bits(uint32_t number, int shift, int mask) {
    number = number >> shift;
    return number & mask;
}

int main() {
    union Number number;
    while (scanf("%f", &number.f) == 1) {
        int tmp = get_bits(number.i, EXP + MAN, 1);
        printf("%d ", tmp);
        tmp = get_bits(number.i, MAN, (1 << EXP) - 1);
        printf("%d ", tmp);
        tmp = get_bits(number.i, 0, (1 << MAN) - 1);
        printf("%x\n", tmp);
    }
    return 0;
}
