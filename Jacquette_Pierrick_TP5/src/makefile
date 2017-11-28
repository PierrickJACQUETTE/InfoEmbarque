# JACQUETTE Pierrick Tp5

CC = gcc
CFLAGS = -Wall -pthread
LDFLAGS = $(CFLAGS)
LDLIBS =  $(shell pkg-config --libs check)
EXEC  = tp5
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
TEST_DIR = Test

all: $(EXEC)

tp5: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

check: $(TEST_DIR)/check_main.o thread.o annexe.o $(TEST_DIR)/check_priority.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

check_priority:

run:all
	sudo ./tp5

runCheck:
	sudo ./check

install:
	sudo apt-get install check

clean:
	rm -f *.o $(TEST_DIR)/*.o

mrproper: clean
	rm -f $(EXEC) check
	rm -f *.gch
	rm -f *.a
	rm -f ~*
	rm -f .[a-Z]*
	rm -f .*.ods
