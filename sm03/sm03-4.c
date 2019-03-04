#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

union Number
{
    uint8_t in[4];
    uint32_t out;
};

int main()
{
    int block_shift;
    while (scanf("%x", &block_shift) == 1) {
        int i, j;
        // 4 блока по 32 бита
        for (i = 0; i < 4; ++i) {
            union Number data;
            // Для каждого блока
            for (j = 0; j < 4; ++j) {
                // Одновременно происходит запись (в обратном порядке)
                // и проверка того, что данные полные
                if (scanf("%hhx", &data.in[3-j]) == EOF) {
                    return 0;
                }
            }
            printf("%" PRIu32, data.out);
            printf("\n");
        }
    }
    return 0;
}
