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

void inizio_lettura(int semid, matrice* mat){
	wait_sem(semid, MUTEX_L, 1);
	mat->numLettori++;
	if(mat->numLettori==1) wait_sem(semid, SYNCH, 1);
	signal_sem(semid, MUTEX_L, 1);
}
void inizio_scrittura(int semid, matrice* mat){
	wait_sem(semid, MUTEX_S,1);
	mat->numScrittori++;
	if(mat->numScrittori==1) wait_sem(semid, SYNCH,1);
	signal_sem(semid, MUTEX_S, 1);
	wait_sem(semid, MUTEX,1);
}

void fine_lettura(int semid, matrice* mat){
	 wait_sem(semid, MUTEX_L, 1);
        mat->numLettori--;
        if(mat->numLettori==0) signal_sem(semid, SYNCH, 1);
        signal_sem(semid, MUTEX_L, 1);
}
void fine_scrittura(int semid, matrice* mat){
	signal_sem(semid, MUTEX,1);
	wait_sem(semid, MUTEX_S,1);
	mat->numScrittori--;
	if(mat->numScrittori==0) signal_sem(semid, SYNCH,1);
	signal_sem(semid, MUTEX_S, 1);
}
void wait_sem(int semid, int semnum, int n){
	struct sembuf sem_buf;
	sem_buf.sem_op=-n;
	sem_buf.sem_flg=0;
	sem_buf.sem_num=semnum;
	semop(semid, &sem_buf, 1);
}

void signal_sem(int semid, int semnum, int n){
	struct sembuf sem_buf;
        sem_buf.sem_op=n;
        sem_buf.sem_flg=0;
        sem_buf.sem_num=semnum;
        semop(semid, &sem_buf, 1);
}

void genera(matrice* mat){

	printf("\n inizio generazione \n");
	srand(time(NULL));
	int riemp=mat->riemp;
	for(int i=0; i<riemp; i++)
		for(int j=0; j<riemp; j++)
			(mat->m)[i][j]=(0+rand()%9);
	sleep(1);

	for(int i=0; i<riemp; i++){
	printf("\n");
		for(int j=0; j<riemp; j++)
			printf(" %d ", (mat->m)[i][j]);
	}
	printf("\n fine generazione \n");
}

void elabora(matrice* mat){

	printf("\n inizio elaborazione \n");
	int riemp=mat->riemp;
	for(int i=0; i<riemp; i++){
	printf("\n");
		for(int j=0; j<riemp; j++){
			int numero=(mat->m)[i][j];
			numero=numero*2;
			printf(" %d ", numero);
	}}
	printf("\n fine elaborazione \n");
}

void analizza(matrice* mat){
	printf("\n inizio analisi \n");
	int riemp=mat->riemp;
	int elementi=riemp*riemp;
	int somma=0, media=0;
	for(int i=0; i<riemp; i++){
	printf("\n");
		for(int j=0; j<riemp; j++){
		somma+=(mat->m)[i][j];
	}}
	media=somma/elementi;
	printf("media:  %d ", media);
	printf("\n fine analisi \n");
}


