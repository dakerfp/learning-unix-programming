
libargs:
	gcc -Wall -c -fPIC args.c -o args.o
	gcc -Wall -shared -Wl,-soname,libargs.so.1 -o libargs.so.1.0.1 args.o # Creates version 1.0.1 of libargs
	ln -f -s libargs.so.1.0.1 libargs.so.1.0 # Forces libargs version 1.0 to 1.0.1
	ln -f -s libargs.so.1.0 libargs.so.1 # Forces libargs version 1 to 1.0
	ln -f -s libargs.so.1 libargs.so # Forces libargs version to 1

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf *.so*