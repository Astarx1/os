#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct shared_roxes {
	int start;
	int stop;
	roxe_t r[256];
} shared_roxes_t;

int main_server() (int argc, char ** argv) {
	int key, shmid;
	shared_roxes_t *shared;
	
	if ((shmid=shmget(key,sizeof(shared_roxes_t,IPC\_CREAT+0666))==-1) {
		perror ("shmget");
		exit(1);
	}

	if ((semid=semget((key_t)10,1,IPC_CREAT+0777))==-1) {
		perror("semget");
		exit(1); 
	}

	while (1) {
		take S1
		int start = shared->start;
		for (int i = start; i < min(start, shared->stop); ++i) {
			printf("corrige");
			shared->start += 1;
		}
		give S1
		take S1
		if (shared->start != 0) {
			memcpy (shared->r + shared->start, shared->r, stop-start);
			s->stop -= s->start, s->start();
		}
		give S1
	}

	shmdt (shared);
}

main_client() {
	int key, shmid;
	shared_roxe_t * shared;
	id = shmget(key,0,0);
	shared = shmat(id, 0,0);

	take S1
	shared->r[shared->stop];
	shared->stop += 1;
	give S1

	shmdt(shared);
}