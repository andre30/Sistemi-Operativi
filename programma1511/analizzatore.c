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

int main(){

        key_t key_sem, key_shm;

        int semid,shmid;

        key_sem=ftok(PATH_SEM, CHAR_SEM);
        key_shm=ftok(PATH_SHM, CHAR_SHM);

        semid=semget(key_sem, 0, IPC_CREAT | 0664);
        shmid=shmget(key_shm,0, IPC_CREAT | 0664);

        matrice * mat=(matrice*) shmat(shmid,0,0);

        while(mat->flag==0){
                inizio_lettura(semid, mat);
                analizza(mat);
                fine_lettura(semid,mat);
                sleep(1);
        }

}


