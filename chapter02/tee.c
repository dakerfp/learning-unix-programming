// TODO close files when other errors occur

#include <unistd.h>
#include <ec.h>
#include <stdlib.h>
#include <stdio.h>
#include <args.h>

#define TEE_STD_BUFFER_SIZE 1024

static char *tee_input_filename = NULL;
static FILE *tee_input_file = NULL;
static FILE **tee_output_files = NULL;
static int tee_files_index = 0;
static bool tee_use_stdout = true;
static int tee_buffer_size = 0;

bool
tee_input_from_file(int argc, char **argv)
{
EC_TRY

    static bool already_selected_file = false;

    if (already_selected_file) {
        fprintf(stderr,"Only one input file is allowed as tee input");
        exit(EXIT_FAILURE);
    }

    tee_input_filename = argv[0];
    EC_NULL(tee_input_file = fopen(tee_input_filename, "r"));
    already_selected_file = true;

    return true;

EC_EXCEPT

    fprintf(stderr, "Unable to read from file: %s \n", tee_input_filename);
    exit(EXIT_FAILURE);
}

bool
tee_new_output_file(int argc, char **argv)
{
EC_TRY
    EC_NULL(tee_output_files[tee_files_index++] = fopen(argv[0], "w"));

    return true;

EC_EXCEPT
    fprintf(stderr, "Unable to write on file: %s\n", argv[0]);
    exit(EXIT_FAILURE);
}

bool
tee_dont_use_stdout(int argc, char **argv)
{
    tee_use_stdout = false;
    return true;
}

bool
tee_set_buffer_size(int argc, char **argv)
{
    // TODO handle possible error here
    sscanf(argv[0], "%d", &tee_buffer_size);
    return true;
}

void tee_close_opened_files(void)
{
EC_TRY
    // Close input file
    if (tee_input_file != stdin)
        EC_SYSCALL(fclose(tee_input_file));

    // Close output files
    int i;
    for (i = 0; i < tee_files_index; i++) {
        FILE *file = tee_output_files[i];
        if (file != stdout) {
            EC_SYSCALL(fclose(file));
        }
    }

    return;

EC_EXCEPT
    fprintf(stderr, "Couldn't close one of the files\n");
    exit(EXIT_FAILURE);
}

struct args_option_handler tee_args_handlers[] = {
    {
        .option_name="i",
        .option_argc=1,
        .handler= tee_input_from_file,
    },
    {
        .option_name="f",
        .option_argc=0,
        .handler= tee_dont_use_stdout,
    },
    {
        .option_name="b",
        .option_argc=1,
        .handler= tee_set_buffer_size,
    },
    args_end_of_handler_list
};

struct args_options_scheme tee_args_scheme = {
    .handlers = tee_args_handlers,
    .default_handler = {
        .option_name="",
        .option_argc=1,
        .handler= tee_new_output_file,
    }
};

int
main(int argc, char **argv)
{
    char *buffer;

    enum errors {ArgsError, WriteError, ReadError, BufferMallocError, FileListMallocError};

EC_TRY_E(enum errors)

    // Read options and open output files
    EC_NULL_E(tee_output_files = (FILE**) malloc(sizeof(FILE*) * (argc)), FileListMallocError); // May not use all the allocated memory
    EC_EQ_E(args_handle_options(&tee_args_scheme, argc, argv), false, ArgsError);

    // Try using std (in/out)puts
    if (tee_use_stdout)
        tee_output_files[tee_files_index++] = stdout;

    if (!tee_input_file)
        tee_input_file = stdin;

    // Creating buffer
    if (!tee_buffer_size)
        tee_buffer_size = TEE_STD_BUFFER_SIZE;

    EC_NULL_E(buffer = (char *) malloc(sizeof(char) * tee_buffer_size), BufferMallocError);

    // Reading data
    while (!feof(tee_input_file)) {
        size_t read_block_size;
        EC_SYSCALL_E(read_block_size = fread(buffer, 1, tee_buffer_size, tee_input_file), ReadError);

        int i;
        for (i = 0; i < tee_files_index; i++) {
            EC_SYSCALL_E(fwrite(buffer, 1, read_block_size, tee_output_files[i]), WriteError);
        }
    }

    // Closing files
    tee_close_opened_files();

    return EXIT_SUCCESS;

EC_EXCEPT_BGN
    EC_CATCH(ArgsError) {
        fprintf(stderr, "The args are malformed\n");
        exit(EXIT_FAILURE);
    }
    // TODO: improve
    EC_CATCH(ReadError) {
        fprintf(stderr, "Unable to read from input\n");
        exit(EXIT_FAILURE);
    }
    // TODO: improve
    EC_CATCH(WriteError) {
        fprintf(stderr, "Unable to write on file\n");
        exit(EXIT_FAILURE);
    }
    EC_CATCH(BufferMallocError) {
        fprintf(stderr, "Unable to allocate buffer\n");
        exit(EXIT_FAILURE);
    }
    EC_CATCH(FileListMallocError) {
        fprintf(stderr, "Unable to write on this ammount of files\n");
        exit(EXIT_FAILURE);
    }
EC_EXCEPT_END

    return EXIT_FAILURE;
}

