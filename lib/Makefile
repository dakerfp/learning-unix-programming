
libargs:
	gcc -c -fPIC args.c -o args.o
	gcc -shared -Wl,-soname,libargs.so.1 -o libargs.so.1.0.1 args.o


clean:
	rm *~
	rm *.o