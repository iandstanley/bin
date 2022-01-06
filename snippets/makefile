

CC=cc
CFLAGS=-g -Wall
OBJS=*.o
BIN = main

all: $(BIN)

main:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) main *.o


