#include "fonction.h"

#define NB_THREADS 100

extern int a;
extern pthread_mutex_t lock;

void affiche (int a, int b) {
	printf ("affiche : a=%i, b=%i\n", a, b);
}

void Calcul(int NbIteration) {
	int b = a;
	a = a + 1;
	affiche (a, b);
	a = b;
}

void * routineCalcul(void * NbIteration) {
	int status = 0;
	int * iter = (int *) NbIteration;
	Calcul(*iter);
	pthread_exit(&status);
}

int main() {	
	pthread_t ts [NB_THREADS];
	int status[NB_THREADS];
	int i; 
	int j = NB_THREADS;

	void * handle_lib;
	void * (*Calcul_lib)(void *);
	char * error;

	pthread_mutex_init(&lock, NULL);

	handle_lib = dlopen("./libfunc.so", RTLD_LAZY | RTLD_GLOBAL);
	if (!handle_lib) {
		fprintf(stderr, " 1 : %s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	dlerror();    /* Clear any existing error */

	*(void **) (&Calcul_lib) = dlsym(handle_lib, "routineCalcul");

    if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "2 : %s\n", error);
		exit(EXIT_FAILURE);
    }

	for (i = 0; i < NB_THREADS; ++i) {
		int * val = &j;
		pthread_create((pthread_t *)&(ts[i]), NULL, *Calcul_lib, (void *) val);
	}
	for (i = 0; i < NB_THREADS; ++i) {
		pthread_join(ts[i], (void **)&status);
		printf ("Thread %d terminé\n", i);
	}

	dlclose(handle_lib);

	pthread_mutex_destroy(&lock);

	return 0;
}