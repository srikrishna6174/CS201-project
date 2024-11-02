all: main

main: main.o splay_tree.o plot.o
	gcc -o main main.o splay_tree.o plot.o -lm

main.o: main.c
	gcc -c main.c

splay_tree.o: splay_tree.c
	gcc -c splay_tree.c

plot.o: plot.c
	gcc -c plot.c

clean: 
	rm -f *.o main
