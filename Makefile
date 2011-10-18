
all: lib test chapter01 chapter02

lib:
	cd lib && make

test:
	cd test && make

chapter01:
	cd chapter01 && make

chapter02:
	cd chapter02 && make

clean:
	cd lib && make clean
	cd ..
	cd test && make clean
	cd ..
	cd chapter01 && make clean
	cd ..
	cd chapter02 && make clean
	cd ..

