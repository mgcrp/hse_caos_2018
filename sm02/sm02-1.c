#include <stdio.h>

int main()
{
    int max_1 = -1, max_2 = -1, temp_int;
    while (scanf("%d", &temp_int) != EOF) {
        if (temp_int > max_1) {
            max_2 = max_1;
            max_1 = temp_int;
        } else if (temp_int > max_2) {
            max_2 = temp_int;
        }
    }
    printf("%d\n", max_1 * max_2);
    return 0;
}
