INCS=-I../lib
LIBS=-L../lib -largs

all: tee cp

tee:
	gcc -Wall $(INCS) $(LIBS) tee.c -o tee

cp:
	gcc -Wall $(INCS) $(LIBS) cp.c -o cp

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf tee
	rm -rf cp
