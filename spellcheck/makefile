all: test

test: hashtable.o spellcheck.o
	gcc -o test hashtable.o spellcheck.o

hashtable.o:
	gcc -c hashtable.c
spellcheck.o:
	gcc -c spellcheck.c

clean: 
	rm *.o