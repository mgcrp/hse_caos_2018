#include <stdio.h>

int main()
{
    float x, y;
    scanf("%f\n%f", &x, &y);

    if (x < 2 || x > 5 || y < 1 || y > 7) {
        printf("0\n");
        return 0;
    } else {
        if (x <= 3 && y > 5 + x - 2) {
            printf("0\n");
            return 0;
        } else if (x <= 4) {
            if (y > 6 + x - 3 || y < 1 + x - 3) {
                printf("0\n");
                return 0;
            }
        } else if (x <= 5 && y < x - 2) {
                printf("0\n");
                return 0;
        }
    }
    printf("1\n");
    return 0;
}
