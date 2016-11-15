
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

	matrice* mat=(matrice*)shmat(id_shm,0,0);
	
	while((mat->flag) == 0){
	inizio_lettura(id_sem, mat);
	analizza(mat);
	fine_lettura(id_sem, mat);
	sleep(2);
	}
	
	if((mat->flag)==1){
	shmctl(id_shm,IPC_RMID,0);
	semctl(id_sem,0,IPC_RMID);
		
	}
}
