# JACQUETTE Pierrick Tp4

CC = gcc
CFLAGS = -Wall -pthread -m32
EXEC  = tp4
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

tp4: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)
	mkdir -p Graph

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

install:
	sudo apt-get install gnuplot gnuplot-x11

run:all
	sudo ./tp4

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)
	rm -f *.gch
	rm -f *.a
	rm -f ~*
	rm -f .[a-Z]*
	rm -f .*.ods
	rm -f output.dat
