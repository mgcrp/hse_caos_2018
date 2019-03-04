// attempt 2
// not passed
// 1 - OK
// 2 - OK
// 3 - WA
// 4 - WA
// 5 - WA
// 6 - WA
// 7 - WA
// 8 - OK

int mystrcmp(const char *str1, const char *str2)
{
    const unsigned char *point1 = (unsigned char *) str1;
    const unsigned char *point2 = (unsigned char *) str2;
    while (*point1 && (*point1 == *point2)) {
        ++point1;
        ++point2;
    }
    return (unsigned char) *str1 - (unsigned char) *str2;
}
