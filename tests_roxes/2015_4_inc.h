#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

typedef char roxe_t;

typedef struct shared_roxes {
	int start;
	int stop;
	roxe_t r[256];
} shared_roxes_t;
