#include "fork.h"

void spig (int sig) {
	printf("Signal %d recu\n", sig);
}
int main() {
	int a;
	int * statut = &a;
	int f;

	if ((f = fork())) {
		sleep(5);
		kill(f, SIGINT);
		printf("Je suis le processus pere %d\n", f);
		wait (statut);
		exit(0);
	}
	else {
		signal(SIGINT,spig);
		printf("Je suis le processus fils %d\n",f);
		pause();		
		printf("Fin du processus fils\n");
		exit(1);
	}
	return 0;
}