#include "segdef.h"

int main() {
	int shmid, semid, i; /* IPC_CREAT+0777 */
	segment * shm;
	void * tmp_shm;
	long t[maxval];
	double moy;

	/* Initalisation */
	if ((semid=semget((key_t) cle,1,0))<0) {
		perror("semget\n");
		exit(1); 
	}
	printf("Id semaphore recupere=%d\n",semid);


	if ((shmid=shmget((key_t) cle,1,0))<0) {
		perror("shmget\n");
		exit(1); 
	}
	if ((tmp_shm = shmat(shmid,0,0))== (char *)-1) {
		perror("semat\n");
		exit(1);
	}
	shm = (segment *) tmp_shm;
	printf("%s%d\n","Id memory recupere=",semid);

	init_rand();

	acq_sem(semid, seg_dispo);

	shm->tty = ntty();
	shm->req = 0;
	moy = 0;
	for (i = 0; i < 100; ++i) {
		t[i] = getrand()%100;
		moy += (double) t[i]/100;
		(shm->tab)[i] = t[i];
	}
	shm->result = moy;

	acq_sem(semid,seg_init);
	wait_sem(semid, res_ok);
	lib_sem(semid, seg_init);
	lib_sem(semid, seg_dispo);

	shmdt(shm);
	printf ("Resultat client : %lf \n", moy);

	while(1);
	
	return 0;
}