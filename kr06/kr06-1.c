#include <stdio.h>
#include <time.h>

enum { DAY_IN_SECONDS = 86400 };

int main(int argc, char * argv[]) {
    if (agrc < 3) {
        return 1
    }

    int year_in = strtol(argv[1], NULL, 10);
    int month_in = strtol(argv[2], NULL, 10);
    int work_hours = 0;

    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    timeinfo->tm_year = year_in - 1900;
    timeinfo->tm_mon = month_in - 1;
    timeinfo->tm_mday = 1;

    mktime(timeinfo);

    while (timeinfo->tm_mon == month_in - 1) {
        if (timeinfo->tm_wday >= 1 && timeinfo->tm_wday <= 4) {
            work_hours += 8;
        } else if (timeinfo->tm_wday == 5) {
            work_hours += 6;
        }
        rawtime += DAY_IN_SECONDS;
        timeinfo = localtime(&rawtime);
    }

    printf("%d\n", work_hours);
    return 0;
}
