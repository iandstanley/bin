CC=clang
CFLAGS=-g -pthread
BINS=server
OBJS=myqueue.o server.o
TESTFILES=/tmp/testfiles


all: $(BINS)

server: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS)  -o $@ -c $^

clean:
	- rm *.o  $(BINS)

testfiles:
	- mkdir $(TESTFILES)
	cp server.c $(TESTFILES)/1.c
	cp server.c $(TESTFILES)/2.c
	cat server.c >> $(TESTFILES)/2.c
	cat server.c >> $(TESTFILES)/2.c
	cat server.c >> $(TESTFILES)/2.c
	cp server.c $(TESTFILES)/3.c
	cp server.c $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cat server.c >> $(TESTFILES)/4.c
	cp server.c $(TESTFILES)/5.c
	ls -la $(TESTFILES)
