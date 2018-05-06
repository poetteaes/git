/**************************************
 * shm sem test
 * pubfun.c
 * created by CAO Fei
 * date: 2018-04-29
 *************************************/
 
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h> 
#include <errno.h> 
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/sem.h> 

/*sem P*/ 
int sem_p(int semid, int semnum)    
{
	/*int semop(int semid, struct sembuf semoparray[], size_t cnts); */
	struct sembuf semOpr ;
	
	semOpr.sem_num = semnum;
	semOpr.sem_op  = -1;
	semOpr.sem_flg = SEM_UNDO;
	
	return semop(semid, &semOpr, 1);
}

/*sem V*/ 
int sem_v(int semid, int semnum)
{
	/*int semop(int semid, struct sembuf semoparray[], size_t cnts); */
	struct sembuf semOpr ;
	
	semOpr.sem_num = semnum;
	semOpr.sem_op  = 1;
	semOpr.sem_flg = SEM_UNDO;
	
	return semop(semid, &semOpr, 1);
}

/*get semval*/ 
int get_semval(int semid, int semnum)
{
	return semctl(semid, semnum, GETVAL);
}