#include "args.h"

char*
args_handle_options(struct args_options_scheme *options_scheme, int argc, char **argv)
{
    int index = 1;

    while (index < argc) {
        struct args_option_handler *option_handler;

        // If has option prefix
        if (argv[index][0] == '-') {
            // Try to get option handler
            char *arg = &argv[index][1];
            int i = 0;
            while ((option_handler = &options_scheme->handlers[i++]) && option_handler->option_argc != 0) {
                if (strcmp(arg, option_handler->option_name) == 0)
                    break;
            }

            // If doesn't exist use default handler
            if (option_handler->option_argc == 0)
                option_handler = &options_scheme->default_handler;
            else
                index += 1;

        } else {
            option_handler = &options_scheme->default_handler;
        }

        // Check if is possible to call
        int opt_argc = option_handler->option_argc;
        if (argc - index < opt_argc) {
            return option_handler->error_message;
        }

        bool (*handler_function) (int, char**) = option_handler->handler;

        // Call handler
        if (!(*handler_function)(opt_argc, &argv[index]))
            return false;

        index += opt_argc;
    }

    return NULL;
}
