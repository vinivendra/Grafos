	
all: main

main: common.o stack.o graph.o 7991103.o
	gcc -Wall -pedantic -std=c99 -g 7991103.o stack.o common.o graph.o -o blocks

7991103.o: 7991103.c
	gcc -Wall -pedantic -std=c99 -g -c 7991103.c

stack.o: stack.c
	gcc -Wall -pedantic -std=c99 -g -c stack.c

common.o: common.c
	gcc -Wall -pedantic -std=c99 -g -c common.c

graph.o: graph.c
	gcc -Wall -pedantic -std=c99 -g -c graph.c

clean: 
	rm *.o blocks
