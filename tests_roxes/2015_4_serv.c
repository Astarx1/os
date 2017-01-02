#include "2015_4_inc.h"

int main (int argc, char ** argv) {
	int key, id, i;
	shared_roxes_t * shared;

	int shmid, v;
	roxe_t tmp;

	v = 0;
	for (key = 0; v == 0 && key < 3000; key++)
	if ((shmid=shmget((key_t) key,sizeof(shared_roxes_t), 0644 | IPC_CREAT))==-1) {
		printf("shmget error - %d\n", key);
		//exit (1);
		continue;
	}
	else {
		break;
	}
	if (shmid == -1) {
		printf ("No key value available - exit\n\n");
		exit(1);
	}
	printf("\n\nSHMID : %d - Key : %d\n\n", shmid, key);
	if ((shared = shmat(shmid, 0,0)) == (char *) -1) {
		printf("shmat\n");
		exit (1);
	}

	while (1) {
		if (shared->start != shared->stop) {
			tmp = shared->r[shared->start];
			// Inserer le traitement de la roxe
			shared->start += 1;
			if (shared->start == 255)
				shared->start = 0;
		}
	}

	shmdt(shared);
	return 0;
}
