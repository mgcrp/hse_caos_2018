#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

enum
{
    BASE = 7,
    ZERO_CHAR_CODE = 48
};

int main()
{
    int input_char;
    double result = 0, afterpoint_denominator;
    bool is_input_empty = true, is_point_passed = false, is_number_printed = false;

    while ((input_char = getchar()) != EOF) {
        if (isspace(input_char)) {
            if (!is_input_empty && !is_number_printed) {
                is_point_passed = false;
                is_number_printed = true;
                printf("%.10g\n", result);
                result = 0;
            }
        } else {
            is_input_empty = false;
            is_number_printed = false;
            if (input_char == '.') {
                is_point_passed = true;
                afterpoint_denominator = BASE;
            } else {
                if (is_point_passed) {
                    result += (input_char - ZERO_CHAR_CODE) * (1 / afterpoint_denominator);
                    afterpoint_denominator *= BASE;
                } else {
                    result *= BASE;
                    result += (input_char - ZERO_CHAR_CODE);
                }
            }
        }
    }
    if (!is_input_empty && !is_number_printed) {
        printf("%.10g\n", result);
    }

    return 0;
}
