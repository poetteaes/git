# ifndef _SHM_SEM_H
# define _SHM_SEM_H

# define SHM_KEY 38111
# define SEM_KEY 38222
# define SHM_SIZE 2048
# define SEM_NUM  2

int sem_p(int semid, int semnum);
int sem_v(int semid, int semnum);
int get_semval(int semid, int semnum);

union semun
{
	int val;                 /*for SETVAL*/
	struct semid_ds *buf;    /*for IPC_STAT  ans  IPC_SET*/
	unsigned short *array;   /*for GETALL  ans  SET_ALL*/
};


# endif