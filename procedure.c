

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


void Wait_Sem(int sem_id , int numsem){
struct sem_buf sembuf;
sembuf.sem_num= numsem;
sembuf.sem_flg=0;
sembuf.sem_op= -1;
semop(sem_id,&sembuf,1);
}

void Signal_Sem(int sem_id , int numsem){
struct sembuf sem_buf;
sem_buf.sem_num= numsem;
sem_buf.sem_flg=0;
sem_buf.sem_op= 1;
semop(sem_id,&sem_buf,1);
}

void inizio_lettura(int sem, matrice* mat){
Wait_Sem(sem , MUTEXL);
mat->num_lettori=mat->num_lettori++;

if(mat->num_lettori==1)
Wait_Sem(sem, SYNCH);

Signal_Sem(sem, MUTEXL);
}

void fine_lettura(int sem, matrice* mat){
Wait_Sem(sem, MUTEXL);
mat->num_lettori=mat->num_lettori--;

if(mat->num_lettori==0)
Signal_Sem(sem, SYNCH);

Signal_Sem(sem,MUTEXL);
}


void inizio_scrittura(int sem, matrice* mat){

Wait_Sem(sem , MUTEXS);
(mat)->num_scrittori=(mat)->num_scrittori++;

if((mat)->num_scrittori==1)
Wait_Sem(sem, SYNCH);

Signal_Sem(sem, MUTEXS);
Wait_Sem(sem, MUTEX);
}


void fine_scrittura(int sem, matrice* mat){
Signal_Sem(sem,MUTEX);
Wait_Sem(sem, MUTEXS);
(mat)->num_scrittori=(mat)->num_scrittori--;

if((mat)->num_scrittori==0)
Signal_Sem(sem, SYNCH);

Signal_Sem(sem,MUTEXS);

}

void genera(matrice* mat){
srand(time(NULL)); //fa si che si generino sempre numeri diversi a ogni esecuzione gaetano docet
sleep(1);
int r= (mat)->riemp
for(int i=0; i<(mat)->r;i++){
	for(int j=0; j<(mat)->;j++){
	(mat)->m[i][j]=(1+rand()%10);
	}
}
for(int i=0; i<r;i++){
printf("\n");
	for(int j=0; j<r;j++){
	printf("%d ", (mat)->m[i][j]);
	}
}

}


void elabora( matrice* mat){
int val;
	for(int i=0; i<r;i++){
	printf("\n");
		for(int j=0; j<(mat)->riemp;j++){
	            val=(mat)->m[i][j];
		val = 2*val;
		printf("%d ",val);
		}
	}
}


void analizza(matrice* mat){
int media;
int somma=0;
int dim=(mat)->riemp;
	for(int i=0; i<(mat)->riemp;i++){
	printf("\n");
		for(int j=0; j<(mat)->riemp;j++){
		somma=somma+(mat)->m[i][j];
		}
	}
media=somma/(dim*dim);
printf("Ciaone la media è: %d ," media);
}


		














