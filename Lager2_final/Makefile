CC=gcc
CFLAGS=-Wall -std=c11 -ggdb

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all -v ./main

all: clean main

main: main.c io.o tree.o ware.o shelves_list.o string_op.o
	$(CC) $(CFLAGS) $^ -o $@

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $^

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c $^

ware.o: ware.c ware.h
	$(CC) $(CFLAGS) -c $^

shelves_list.o: shelves_list.c shelves_list.h
	$(CC) $(CFLAGS) -c $^ 

string_op.o: string_op.c string_op.h
	$(CC) $(CFLAGS) -c $^ 

clean:
	@echo All cleaned up!
	@rm -f *.o *.gch *~
	@rm -rf *.dSYM
	@rm -f main
