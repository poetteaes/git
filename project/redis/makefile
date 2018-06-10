CC = gcc
CFLAG = -g -c  -Wall

INCLUDE_PATH=-I/usr/local/include/hiredis/
LIB_PATH=-L/usr/local/lib -lhiredis  -L/media/sf_share/git/project/redis

all:  libredisopr.so redisTest


%.o:%.c
	$(CC) $(CFLAG) -fPIC   $(INCLUDE_PATH) $(LIB_PATH) -c $*.c
	
libredisopr.so:redisOpr.o
		$(CC) -o $@ $< -fPIC -shared  $(INCLUDE_PATH) $(LIB_PATH)
	
redisTest:redisTest.o
		$(CC) -o $@ $<  $(INCLUDE_PATH) $(LIB_PATH)  -lredisopr
		
clean:
	rm -f *.o

 