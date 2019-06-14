#include <math.h>

double func0(double x)
{
    return (x + 1.0) * 1.00001;
}

double func1(double x)
{
    return sin(x);
}

double func2(double x)
{
    return pow(fabs(x), 1.0001);
}

double func3(double x)
{
    return sqrt(fabs(x) + 1);
}
