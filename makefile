CC = gcc
OBJS = solver.o mainaux.o parser.o
EXEC = solver
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: solver.c solver.h mainaux.h
	$(CC) $(COMP_FLAG) -c $*.c
mainaux.o: mainaux.c mainaux.h
	$(CC) $(COMP_FLAG) -c $*.c
parser.o: parser.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
