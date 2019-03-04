#include <stdio.h>
#include <ctype.h>

int main()
{
    int c, sum = 0;
    while ((c = getchar_unlocked()) != EOF) {
        if (isdigit(c)) {
            sum += c - 48;
        }
    }
    printf("%d\n", sum);
    return 0;
}
