// attempt 1
// not passed
// 1 - OK
// 2 - OK
// 3 - OK
// 4 - OK
// 5 - OK
// 6 - OK
// 7 - OK
// 8 - WA

int mystrcmp(const char *str1, const char *str2)
{
    const char *point1 = str1;
    const char *point2 = str2;
    while(*point1 && *point2) {
        if(*point1 < *point2) {
            return -1;
        } else if (*point1 > *point2) {
            return 1;
        }
        point1 += 1;
        point2 += 1;
    }
    if (*point1) {
        return 1;
    } else if (*point2) {
        return -1;
    } else {
        return 0;
    }
}
