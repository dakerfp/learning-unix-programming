#include <args.h>
#include <stdunix.h>

#define BUFFSIZE 512

int
main(int argc, char **argv)
{
    enum errors {NumArgsError, FromFileError, ToFileError};

EC_TRY_E(enum errors)

    EC_NEQ_E(argc, 3, NumArgsError);

    int fd_from;
    int fd_to;

    char *from = argv[1];
    char *to = argv[2];

    EC_EQ_E( fd_from = open(from, O_RDONLY, 0), -1, FromFileError);
    EC_EQ_E( fd_to = open(to, O_WRONLY, 0), -1, ToFileError);

    char buffer[BUFFSIZE];

    // TODO: READ WRITE LOOP

    return 0;

EC_EXCEPT_BGN
    EC_CATCH(NumArgsError) {
	fprintf(stderr, "mv needs exactly 2 arguments\n");
	exit(EXIT_ERROR);
    }

    EC_CATCH(FromFileError) {
	fprintf(stderr, "error while opening %s file\n", from);
	exit(EXIT_ERROR);
    }

    EC_CATCH(ToFileError) {
    	close(fd_from); // TODO check this out
	fprintf(stderr, "error while writing in %s file\n", to);
	exit(EXIT_ERROR);
    }
EC_EXCEPT_END
}
