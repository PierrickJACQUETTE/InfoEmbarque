CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS =  $(shell pkg-config --libs check)
EXEC 	  = check_main

all: $(EXEC)

check_main: check_main.o ../colimacon.o check_colimacon.o

check_colimacon:

clean:
	rm -f check_*.o

mrproper: clean
		rm -f $(EXEC)
		rm -f *.gch
