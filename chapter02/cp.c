#include <args.h>
#include <ec.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFSIZE 512

int
main(int argc, char **argv)
{
    enum errors {NumArgsError, FromFileError, ToFileError, WriteError, CloseFileError};

EC_TRY_E(enum errors)

    EC_NEQ_E(argc, 3, NumArgsError);

    char *from = argv[1];
    char *to = argv[2];

    int fd_from;
    int fd_to;

    EC_CHECK_E((fd_from = open(from, O_RDONLY, 0)) > 0, FromFileError);
    EC_CHECK_E((fd_to = open(to, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) > 0, ToFileError);

    char buffer[BUFFSIZE];
    int nread = 0;
    int nwrite;
    int n;

    while ((nread = read(fd_from, buffer, sizeof(buffer))) > 0) {
        nwrite = 0;
        do {
            EC_CHECK_E((n = write(fd_to, &buffer[nwrite], nread - nwrite)) >= 0, WriteError);
            nwrite += n;
        } while (nwrite < nread);
    }

    EC_CHECK_E(close(fd_from) >= 0, CloseFileError);
    EC_CHECK_E(close(fd_to) >= 0, CloseFileError);

    exit(EXIT_SUCCESS);

EC_EXCEPT_BGN
    EC_CATCH(NumArgsError) {
	    fprintf(stderr, "mv needs exactly 2 arguments\n");

        exit(EXIT_FAILURE);
    }

    EC_CATCH(FromFileError) {
        fprintf(stderr, "error while opening %s file\n", from);

        exit(EXIT_FAILURE);
    }

    EC_CATCH(ToFileError) {
        fprintf(stderr, "cannot write into '%s\' file\n", to);
    	(void)close(fd_from);

        exit(EXIT_FAILURE);
    }

    EC_CATCH(WriteError) {
        fprintf(stderr, "n: %d\n", n);
        fprintf(stderr, "error while writing in '%s' file\n", to);
        (void)close(fd_from);
        (void)close(fd_to);

        exit(EXIT_FAILURE);
    }

    EC_CATCH(CloseFileError) {
        fprintf(stderr, "error while terminating the file copy\n");
    }
EC_EXCEPT_END

    return 0;
}
