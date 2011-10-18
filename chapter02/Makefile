INCS=-I../lib
LIBS=-L../lib -largs

all: tee mv

tee:
	gcc -Wall $(INCS) $(LIBS) tee.c -o tee

mv:
	gcc -Wall $(INCS) $(LIBS) mv.c -o mv

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf tee
	rm -rf mv
