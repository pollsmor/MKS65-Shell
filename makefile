all: parse.o redirect.o pipes.o main.o
	gcc -o shell parse.o redirect.o pipes.o main.o

parse.o: parse.c parse.h redirect.h pipes.h
	gcc -c parse.c

redirect.o: redirect.c redirect.h
	gcc -c redirect.c

pipes.o: pipes.c pipes.h
	gcc -c pipes.c

main.o: main.c parse.h
	gcc -c main.c

run:
	./shell

clean:
	rm *.o
	rm shell
