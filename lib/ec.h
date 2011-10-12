/*
  Exception utilitary function
 */

#include <stdlib.h>
#include <errno.h>
#ifndef __cplusplus
    #include <stdbool.h> /* C99 Only */
#endif

#define EC_TRY(errors_types) \
    errors_types __ec_errors_type__; \
    bool __ec_handling_error__ = false;

#define __GOTO_EC__ { \
        if (__ec_handling_error__) { \
            exit(-1); \
        } else { \
            goto __ec_label__; \
        } \
    }

#define EC_EQ(a, b) { \
        if (((a) == (b))) \
            __GOTO_EC__;  \
    }

#define EC_SYSCALL(command) { \
        errno = 0; \
        command; \
        if (errno) \
            __GOTO_EC__; \
    }

#define EC_SYSCALL_E(command, error_type) {                    \
        errno = 0; \
        command; \
        if (errno) { \
            __ec_errors_type__ = error_type; \
            __GOTO_EC__; \
        } \
    }

#define EC_EQ_E(a, b, error_type) { \
        errno = 0; \
        if (((a) == (b))) { \
            __ec_errors_type__ = error_type ; \
            __GOTO_EC__; \
        } \
        if (errno) { \
            __ec_errors_type__ = error_type; \
            __GOTO_EC__; \
        } \
    }

#define EC_NEQ(a, b) { \
        if ((a) != (b)) \
            __GOTO_EC__; \
    }

#define EC_NEQ_E(a, b, error_type) { \
        if (a != b) { \
            __ec_errors_type__ = error_type; \
            __GOTO_EC__; \
        } \
    }

#define EC_NULL(v) EC_EQ((void *) (v), NULL)
#define EC_NNULL(v) EC_NEQ((void *) (v), NULL)

#define EC_NULL_E(v, error_type) EC_EQ_E((void*) (v), NULL, error_type)
#define EC_NNULL_E(v, error_type) EC_NEQ_E((void*) (v), NULL, error_type)

#define EC_EXCEPT \
    __ec_label__:

#define EC_EXCEPT_BGN \
    __ec_label__: { \
    __ec_handling_error__ = true; \
    switch (__ec_errors_type__) {

#define EC_CATCH(error) \
    case error:

#define EC_EXCEPT_END } }
