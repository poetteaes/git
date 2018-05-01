CC = gcc
CFLAG = -g -c  -Wall

all: MsgServer MsgClient


%.o:%.c
	$(CC) $(CFLAG) -c $*.c shm.h
	
MsgServer:MsgServer.o
		$(CC) -o $@ $<

MsgClient:MsgClient.o
		$(CC) -o $@ $<	

clean:
	rm -f *.o

 