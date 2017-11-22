# JACQUETTE Pierrick Tp5

CC = gcc
CFLAGS = -Wall -pthread -m32
EXEC  = tp5
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

tp5: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

run:all
	sudo ./tp5

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)
	rm -f *.gch
	rm -f *.a
	rm -f ~*
	rm -f .[a-Z]*
	rm -f .*.ods