#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define cle 		(key_t)3
#define seg_dispo 	0
#define seg_init  	1
#define res_ok    	2
#define maxval   	100

typedef struct shmseg
{
   int tty;
   int req;
   long tab[maxval];
   long result;
} segment;

#define segsize sizeof(segment)

void init_rand();
long getrand();
int ntty();

void wait_sem(int,int);
void acq_sem(int,int);
void lib_sem(int,int);

void own_wait () {
	
}

long double ma (long double a) {
	return a >= 0 ? a : -a;
}
long rd (long double a) {
	int i;
	a = ma (a);
	i = 0;
	while (i < a) ++i;
	return i;
}