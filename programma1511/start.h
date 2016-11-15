#ifndef _start
#define _start

#define N 5

typedef struct {
	int m[N][N];
	int riemp;
	int numLettori;
	int numScrittori;
	int flag;
}matrice;

#define PATH_SHM "."
#define CHAR_SHM 'a'
#define PATH_SEM "."
#define CHAR_SEM 'b'

#define MUTEX 0
#define SYNCH 1
#define MUTEX_L 2
#define MUTEX_S 3


void inizio_lettura(int, matrice*);
void inizio_scrittura(int, matrice*);
void fine_lettura(int, matrice*);
void fine_scrittura(int, matrice*);

void wait_sem(int, int, int);
void signal_sem(int, int, int);

void genera(matrice*);
void elabora(matrice*);
void analizza(matrice*);

#endif
