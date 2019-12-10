all: parse.o pipes.o main.o
	gcc -o myshell parse.o pipes.o main.o

parse.o: parse.c parse.h pipes.h
	gcc -c parse.c

pipes.o: pipes.c pipes.h
	gcc -c pipes.c

main.o: main.c parse.h
	gcc -c main.c

run:
	./myshell

clean:
	rm *.o
	rm myshell
	rm *.gch
