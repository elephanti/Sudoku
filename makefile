CC = gcc
OBJS = main.o game.o solver.o mainaux.o parser.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: main.c game.h parser.h solver.h mainaux.h
	$(CC) $(COMP_FLAG) -c $*.c
game.o: game.c game.h solver.h mainaux.h
	$(CC) $(COMP_FLAG) -c $*.c
solver.o: solver.c solver.h mainaux.h
	$(CC) $(COMP_FLAG) -c $*.c
mainaux.o: mainaux.c mainaux.h
	$(CC) $(COMP_FLAG) -c $*.c
parser.o: parser.c parser.h mainaux.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
