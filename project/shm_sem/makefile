CC = gcc
CFLAG = -g -c  -Wall

all: server client


%.o:%.c
	$(CC) $(CFLAG) -c $*.c shm_sem.h
	
server:server.o pubfun.o
		$(CC) -o $@ server.o pubfun.o

client:client.o pubfun.o
		$(CC) -o $@ client.o pubfun.o	

clean:
	rm -f *.o

 