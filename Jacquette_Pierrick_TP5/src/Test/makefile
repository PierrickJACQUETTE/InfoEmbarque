#JACQUETTE Pierrick Tp5

CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS =  $(shell pkg-config --libs check)
EXEC 	  = check_main

all: $(EXEC)

check_main: check_main.o ../thread.o ../annexe.o check_priority.o

check_priority:

clean:
	rm -f check_*.o

mrproper: clean
		rm -f $(EXEC)
		rm -f *.gch
