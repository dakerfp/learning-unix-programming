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
};

struct args_options_scheme {
    struct args_option_handler *handlers;
    struct args_option_handler default_handler;
};

#define args_end_of_handler_list {.option_name = "", .option_argc = 0, .handler = NULL}
#define args_empty_handler_list { {.option_name = "", .option_argc = 0, .handler = NULL} }

#define args_verbose_handler {.option_name = "v", .option_argc = 0, .handler = args_set_verbose}

bool args_handle_options(struct args_options_scheme *options_scheme, int argc, char **argv);

static bool __args_verbose_mode = false;
bool args_set_verbose(int argc, char **argv) {
    __args_verbose_mode = true;
    return true;
}
bool args_verbose_mode(void) { return __args_verbose_mode; }

#endif //ARGS_LIB_H
