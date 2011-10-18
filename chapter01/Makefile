INCS=-I../lib
LIBS=-L../lib -largs

all: example01 example02 example03

example01:
	gcc -Wall $(INCS) $(LIBS) example01.c -o example01

example02:
	gcc -Wall $(INCS) $(LIBS) example02.c -o example02

example03:
	gcc -Wall $(INCS) $(LIBS) example03.c -o example03

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf example01
	rm -rf example02
	rm -rf example03
