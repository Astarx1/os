#include "fonction.h"

extern int a;
extern pthread_mutex_t lock;

extern "C" {
void Calcul(int NbIteration) {
	int b = a;
	pthread_mutex_lock (&lock);
	a = a + 1;
	affiche (a, b);
	a = b;
	pthread_mutex_unlock (&lock);
}

void * routineCalcul (void * NbIteration) {
	int status = 0;
	int * iter = (int *) NbIteration;
	Calcul(*iter);
	pthread_exit(&status);
}

}