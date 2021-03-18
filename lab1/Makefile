all: lab1p1 lab1p2 lab1.zip

lab1p1: lab1p1.c
	gcc -ansi -pedantic lab1p1.c -o lab1p1

lab1p2: lab1p2.c
	gcc -ansi -pedantic lab1p2.c -o lab1p2

lab1.zip: *.c Makefile
	zip lab1 *.c Makefile

clean:
	rm -rf lab1p1 lab1p2 lab1.zip
