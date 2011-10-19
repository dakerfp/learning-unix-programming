INCS=-I../lib
LIBS=-L../lib -largs

all: test_args

test_args:
	gcc -Wall $(INCS) $(LIBS) test_args.c -o test_args

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf test_args