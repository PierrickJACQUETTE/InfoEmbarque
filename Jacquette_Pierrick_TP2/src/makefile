# JACQUETTE Pierrick Tp2

CC = gcc
CFLAGS = -Wall -pthread -m32
LFLAGS = -Llib -lcolimacon
STAT = libcolimacon.a
DYN = libcolimacon.so
EXEC = clock colimacon
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
DIR = lib

all: $(EXEC)

colimacon: $(OBJECTS)
	$(CC) -fPIC -c colimacon.c $(CFLAGS)
	$(CC) -o $(DYN) -Wl,-soname,$(DIR)/$(DYN) -shared colimacon.o $(CFLAGS)
	mkdir -p $(DIR)
	mv $(DYN) $(DIR)/
	$(CC) -o colimaconSO UseLib/test.c $(LFLAGS) $(CFLAGS)
	ar -cvq $(STAT) $^
	mkdir -p $(DIR)
	mv $(STAT) $(DIR)/
	$(CC) -o colimaconA UseLib/test.c $(LFLAGS) $(CFLAGS) -Wl,$(DIR)/$(STAT) -static
	$(CC) -o $@ $^ $(CFLAGS)

clock: Clock/clock.o
	$(CC) -o clock Clock/clock.c $(CFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f Clock/*.o

mrproper: clean
	rm -f $(EXEC) $(STAT) $(DYN) colimaconA colimaconSO col
	rm -f *.gch
	rm -f Clock/*.gch
	rm -f *.a
	rm -f ~*
	rm -f *.o
	rm -fR $(DIR)
