#include <string.h>
#include <stdio.h>
#include <time.h>
#include "../lib/ec.h"

int main(int argc, char **argv)
{
    enum errors {ArgcError, MallocError, TimeError};

EC_TRY_E(enum errors)

    EC_NEQ_E(argc, 1, ArgcError);

    time_t *current_time = (time_t *) malloc(sizeof(time_t));
    EC_NULL_E(current_time, MallocError);

    time(current_time);
    EC_EQ_E((*current_time), -1, TimeError);

    struct tm *tm_time = localtime(current_time);
    EC_NULL_E(tm_time, TimeError);

    char *str_time = ctime(current_time);
    EC_NULL_E(str_time, TimeError);

    char *str1 = (char *) malloc(sizeof(char) * 20);
    EC_NULL_E(str1, MallocError);

    memset(str1, 0, 20);
    strncpy(str1, str_time, 19);

    tzset();

    printf("%s %s %d\n", str1, tzname[0], 1900 + tm_time->tm_year);

    return 0;

EC_EXCEPT_BGN
    EC_CATCH(ArgcError) {
        fprintf(stderr, "No support for command-line args\n");

        return -1;
    }
    EC_CATCH(MallocError) {
        fprintf(stderr, "Memory allocation error\n");

        return -1;
    }
    EC_CATCH(TimeError) {
        fprintf(stderr, "Maybe you shouldn't know the time\n");

        return -1;
    }
EC_EXCEPT_END
}
