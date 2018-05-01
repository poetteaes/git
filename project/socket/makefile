CC = gcc
CFLAG = -g -c  -Wall

all: server client


%.o:%.c
	$(CC) $(CFLAG) -c $*.c
	
server:server.o
		$(CC) -o $@ $<

client:client.o
		$(CC) -o $@ $<	

clean:
	rm -f *.o

 