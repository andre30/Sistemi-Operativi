#include "start.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "start.h"
#include <time.h>

#define NPROC 4
int main(){
	key_t key_sem, key_shm;
	pid_t pid_ex, pid;
	int semid,shmid;

	key_sem=ftok(PATH_SEM, CHAR_SEM);
	key_shm=ftok(PATH_SHM, CHAR_SHM);

	semid=semget(key_sem, 4, IPC_CREAT | 0664);
	shmid=shmget(key_shm,sizeof(matrice), IPC_CREAT | 0664);

	semctl(semid,MUTEX_L,SETVAL,1);
	semctl(semid,MUTEX_S,SETVAL,1);
	semctl(semid,MUTEX,SETVAL,1);
	semctl(semid,SYNCH,SETVAL,1);
	matrice * mat=(matrice*) shmat(shmid,0,0);
	srand(time(NULL));
	mat->riemp=(3+rand()%5);
	mat->flag=0;
	for(int i=0;i<NPROC;i++){
	pid=fork();
	if(pid==0){
		if(i==0){
			execl("./generatore","./generatore",NULL);
		}
		else if(i==1 || i==2){
			execl("./analizzatore","./analizzatore",NULL);
		}
		else
			execl("./elaboratore","./elaboratore",NULL);

	_exit(0);
	}

	}

	sleep(30);
	mat->flag=1;
	shmctl(shmid,IPC_RMID,0);
	semctl(semid,0,IPC_RMID);

}
