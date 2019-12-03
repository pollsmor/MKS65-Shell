all: functions.o main.o
	gcc -o shell functions.o main.o

parse.o: parse.c parse.h redirect.h pipes.h
	gcc -c parse.c

redirect.o: redirect.c redirect.h
	gcc -c redirect.c

pipes.c: pipes.c pipes.h
	gcc -c pipes.c

main.o: main.c parse.h
	gcc -c main.c

run:
	./shell

clean:
	rm *.o
	rm shell
