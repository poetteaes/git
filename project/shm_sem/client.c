/**************************************
 * shm sem test
 * client
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
#include <sys/shm.h> 
#include <sys/sem.h> 

#include "shm_sem.h"

/************************
 * client
 * P(sem[1])
 * read
 * V(sem[0])
 ************************/
int main(void)
{
	int ret;
	int shmid;
	int semid;
	void *ptrShm = NULL;
	struct shmid_ds shm_ds;
	struct semid_ds sem_ds;
	char buf[1024] = {0};
	union semun arg;
	unsigned short semvalArr[SEM_NUM];
		
	memset(&shm_ds, 0x00, sizeof(shm_ds));
	memset(&sem_ds, 0x00, sizeof(sem_ds));
	
	/*semget*/
	semid = semget((key_t)SEM_KEY, SEM_NUM, 0660|IPC_CREAT|IPC_EXCL);   /*int semget(key_t key, int nsems, int flag);*/
	if(semid == -1)
	{
		if(errno == EEXIST) /*no need to init sem*/
		{
			printf("semget() warning: %s\n", strerror(errno));
			semid = semget((key_t)SEM_KEY, 0, 0660|IPC_CREAT); /*nsems can be 0 when semid already exists*/
			if(semid == -1)
			{
				printf("semget() error: %s\n", strerror(errno));
				return -1;
			}
			printf("semget() success. semid=[%d]\n", semid);
		}
		else
		{
			printf("semget() error: %s\n", strerror(errno));
			return -1;
		}
	}
	else  /*need to init sem*/
	{
		printf("semget() success. semid=[%d]\n", semid);
				
		/*semctl(): init sem, set semvalArr[0]=1 semvalArr[1]=0*/
		semvalArr[0]= (unsigned short)1 ;
		semvalArr[1]= (unsigned short)0 ;
        arg.array = semvalArr;		
		ret = semctl(semid, 0, SETALL, arg);  /*int semctl(int semid, int semnm, int cmd [, union semun arg]); semnum between 0~nsems-1*/ 
		if(ret == -1)
		{
			printf("semctl() SETALL error: %s\n", strerror(errno));
			printf("init sem error.\n");
			
		   /*semctl IPC_RMID*/
	       ret = semctl(semid, 0, IPC_RMID);
	       if(ret == -1)
	       {
	       	printf("semctl() error: %s\n", strerror(errno));
	       }
	       printf("semctl() success. Sem is deleted.\n"); 
		   return -1;
		   
		}
		printf("semget() success.\n");
		
	}
	printf("semval[0]=[%d] semval[1]=[%d].\n", get_semval(semid, 0), get_semval(semid, 1));
	
	/*shmget*/
	shmid = shmget((key_t)SHM_KEY, SHM_SIZE, 0660|IPC_CREAT|IPC_EXCL);   /*int shmget(key_t key, size_t size, int flag);*/
	if(shmid == -1)
	{
		if(errno == EEXIST)
		{
			printf("shmget() warning: %s\n", strerror(errno));
			shmid = shmget((key_t)SHM_KEY, SHM_SIZE, 0660|IPC_CREAT);
			if(shmid == -1)
			{
				printf("shmget() error: %s\n", strerror(errno));
				return -1;
			}
		}
		else
		{
			printf("shmget() error: %s\n", strerror(errno));
			return -1;
		}
	}
	printf("shmget() success. shmid=[%d]\n", shmid);   
	
	/*shmat*/
	ptrShm = shmat(shmid, NULL, SHM_RDONLY);   /*void *shmat(int shmid, const void *shmarr,  int flag);*/
	if(ptrShm == NULL)
	{
		printf("shmat() error: %s\n", strerror(errno));
		goto FAILED;
	}
	printf("shmat() success.\n"); 
	printf("Begin to read shared memory.\n"); 
	
	/*##########################################*/
	/*!!! This is very import if client starts before server. Otherwise, there will be a dead loop !!!!! */
	while(1)
	{
		/*test semvalArr[0]*/
		ret = get_semval(semid, 1);
		if(ret < 0) /**/
		{
			printf("get_semval() error.\n");
			goto FAILED;
		}
		else if(ret == 0)   /*It suggests that the server hasn't start yet*/
			continue;
		else
			break;
	}
	/*##########################################*/
	
	/*Begin to read*/
	while(1)
	{
		/*P*/
		ret = sem_p(semid, 1);
		if(ret == -1)
		{
			printf("sem_p() error\n");
			goto FAILED;
			
		}
		
	    /*read shm*/
		memset(&buf, 0x00, sizeof(buf));
		memcpy(buf, (char*)ptrShm, sizeof(buf));
		
		
		/*V*/
		ret = sem_v(semid, 0);
		if(ret == -1)
		{
			printf("sem_v() error\n");
			goto FAILED;
			
		}
		//printf("semval[0]=[%d] semval[1]=[%d].\n", get_semval(semid, 0), get_semval(semid, 1));
		
		printf("client: %s", buf);
		if(buf[0]=='\0')
			printf("\n");
			
		if(memcmp(buf, "exit", 4) == 0)
		{
			break;
		}
		
	}
	
	
	/*shmdt*/
	ret = shmdt(ptrShm);
	if(ret == -1)
	{
		printf("shmdt() error: %s\n", strerror(errno));
	}
	printf("shmdt() success.\n"); 
	
	/*shmctl IPC_RMID*/
	ret = shmctl(shmid, IPC_RMID, &shm_ds);
	if(ret == -1)
	{
		printf("shmctl() error: %s\n", strerror(errno));
	}
	printf("shmctl() success. Shm is deleted.\n"); 
	
	/*semctl IPC_RMID*/
	ret = semctl(semid, 0, IPC_RMID);
	if(ret == -1)
	{
		printf("semctl() error: %s\n", strerror(errno));
	}
	printf("semctl() success. Sem is deleted.\n"); 
	
	return 0;
	
FAILED:
	/*shmctl IPC_RMID*/
	ret = shmctl(shmid, IPC_RMID, &shm_ds);
	if(ret == -1)
	{
		printf("shmctl() error: %s\n", strerror(errno));
	}
	printf("shmctl() success. Shm is deleted.\n"); 
	
	/*semctl IPC_RMID*/
	ret = semctl(semid, 0, IPC_RMID);
	if(ret == -1)
	{
		printf("semctl() error: %s\n", strerror(errno));
	}
	printf("semctl() success. Sem is deleted.\n"); 
	
	return -1;
}
