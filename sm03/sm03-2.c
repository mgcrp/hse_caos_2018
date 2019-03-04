#include <stdint.h>

int32_t satsum(int32_t v1, int32_t v2)
{
    int32_t result;
    if (__builtin_add_overflow(v1, v2, &result)) {
        uint32_t max_uint = 0U - 1U;
        if (v1 < 0 && v2 < 0) {
            return (int32_t)(max_uint / 2 + 1);
        } else {
            return (int32_t)(max_uint / 2);
        }
    } else {
        return result;
    }
}
