#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "../lib/ec.h"

int main(int argc, char **argv)
{
    enum errors {SysconfError};

EC_TRY_E(enum errors)

    int pjcontrol;

    // sysconf arg values defined in /usr/include/bits/confname.h
    EC_EQ_E(pjcontrol = sysconf(_SC_ARG_MAX), 0, SysconfError);

    printf("_SC_ARG_MAX: %d\n", pjcontrol);

    return 0;

EC_EXCEPT_BGN
    EC_CATCH(SysconfError) {
        fprintf(stderr, "Error on _SC_ARG_MAX sysconf reading.\n");

        return -1;
    }
EC_EXCEPT_END
}
