#ifndef _HEADER
#define __HEADER

#define N 5
#define PATH_SHM "."
#define CHAR_SHM 'a'
#define PATH_SEM "."
#define CHAR_SEM 'b'

//semafori
#define MUTEXL 0
#define MUTEXS 1
#define MUTEX 2
#define SYNCH 3

typedef struct{
	int m[N][N];
	int riemp;
	int num_lettori;
	int num_scrittori;
	int flag;
}matrice;


void Wait_Sem( int , int);
void Signal_Sem(int, int);
void inizio_lettura(int, matrice*);
void inizio_scrittura(int, matrice*);
void fine_lettura(int, matrice*);
void fine_scrittura(int, matrice*);
void elabora(matrice*); //lettore
void analizza(matrice*);//lettore
void genera( matrice*); //scrittore

#endif
