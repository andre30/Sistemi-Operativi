
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include "header.h"


int main(){
	int id_sem,id_shm;
	pid_t pid;
	key_t semkey,shmkey;
	shmkey=ftok(PATH_SHM,CHAR_SHM);
	id_shm= shmget(shmkey,sizeof(matrice),IPC_CREAT |0664);

	semkey=ftok(PATH_SEM,CHAR_SEM);
	id_sem= semget(semkey,4,IPC_CREAT |0664);
	semctl(id_sem,MUTEXL,SETVAL,1);
	semctl(id_sem,MUTEXS,SETVAL,1);
	semctl(id_sem,MUTEX,SETVAL,1);
	semctl(id_sem,SYNCH,SETVAL,1);
	matrice* mat=(matrice*)shmat(id_shm,0,0);
srand(time(NULL));
mat->riemp=(3+rand()%5);
	(mat->flag)=0;
	for(int i=0; i<4; i++){
	pid=fork();
	if(pid==0){
		if(i==0 || i==1){
		execl("./analizzatore.c","./analizzatore.c",NULL);
		}
		else if(i==2){
		execl("./elaboratore.c","./elaboratore.c",NULL);
		}
		else if(i==3){
		execl("./generatore.c","./generatore.c",NULL);
		}
	_exit(0);
	}
	
	}

	sleep(15);
	(mat->flag) = 1;
	shmctl(id_shm,IPC_RMID,0);
	semctl(id_sem,0,IPC_RMID);
	
	
}
