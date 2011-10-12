#ifndef ARGS_LIB_H
#define ARGS_LIB_H

#include <string.h>
#ifndef __cplusplus
    #include <stdbool.h> /* C99 Only */
#endif

struct args_option_handler {
    char * option_name;
    int option_argc;
    bool (*handler) (int, char**);
    char *error_message;
};

struct args_options_scheme {
    struct args_option_handler *handlers;
    struct args_option_handler default_handler;
};

#define args_end_of_handler_list {.option_name = "", .option_argc = 0, .handler = NULL, .error_message= ""}

char *args_handle_options(struct args_options_scheme *options_scheme, int argc, char **argv);

#endif //ARGS_LIB_H
