
all: liball testall chapter01all chapter02all
	echo "Success"

liball:
	cd lib; make all

testall: liball
	cd test; make all

chapter01all: liball
	cd chapter01; make all

chapter02all: liball
	cd chapter02; make all

clean:
	cd lib; make clean
	cd test; make clean
	cd chapter01; make clean
	cd chapter02; make clean


