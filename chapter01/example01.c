/*
  This example show how to use the EC exceptions
 */

#include <stdlib.h>
#include <stdio.h>
#include "ec.h"

int main(int argc, char **argv)
{
    enum errors {ArgcError, MallocError};

EC_TRY(enum errors)

    EC_NEQ_E(argc, 2, ArgcError);

    int *array = NULL;
    // Probably will break:
    // EC_NULL_E(array = (int*) malloc(sizeof(int) * 999999999), MallocError);
    EC_NULL_E(array = (int *) malloc(sizeof(int) * 1024), MallocError);

    printf("Arg count: %d\n", argc);
    printf("First param: %s\n", argv[1]);

    return 0;

EC_EXCEPT_BGN
    EC_EXCEPT(ArgcError) {
        printf("Wrong arg count: %d\n", argc);

        return -1;
    }
    EC_EXCEPT(MallocError) {
        printf("Too long array\n");

        return -1;
    }
EC_EXCEPT_END
}
