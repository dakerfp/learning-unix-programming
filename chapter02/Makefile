INCS=-I../lib
LIBS=-L../lib -largs

all: tee

tee:
	gcc -Wall $(INCS) $(LIBS) tee.c -o tee

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf tee