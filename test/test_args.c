#include <stdio.h>
#include <args.h>

bool
print_arg(int argc, char **argv)
{
    printf("Print Arg %s \n", argv[0]);
    return true;
}

bool
yield(int argc, char **argv)
{
    printf("YIELD %s \n", argv[0]);
    return true;
}

bool
yield2(int argc, char **argv)
{
    printf("YIELD2 %s %s \n", argv[0], argv[1]);
    return true;
}

struct args_option_handler args_scheme_example_handlers[] = {
    {
        .option_name = "y",
        .option_argc = 1,
        .handler = yield,
        .error_message = "yield failed"
    },
    {
        .option_name = "y2",
        .option_argc = 2,
        .handler = yield2,
        .error_message = "yield2 failed"
    },
    args_end_of_handler_list
};

struct args_options_scheme args_scheme_example = {
    .handlers = args_scheme_example_handlers,
    .default_handler = {
        .option_name = "Default handler",
        .option_argc = 1,
        .handler = print_arg,
        .error_message = "Default handler failed"
    }
};

int
main(int argc, char **argv) {
    char *error_message = args_handle_options(&args_scheme_example, argc, argv);
    if (error_message)
        printf("%s\n",error_message);
    return 0;
}
