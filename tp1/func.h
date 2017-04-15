#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void question1_1 () {
	int pid; 
	int status; 

	if ((pid = fork()) > 0) {
		printf("Processus pere\n");
		wait(&status);
		printf("Fin des process\n");
	}
	else {
		printf("Processus fils\n");
		sleep(5);
	}
}

void spig () {
	printf ("Extinction\n");
	exit(1);
}

void question1_2 () {
	int pid; 
	int status; 

	if ((pid = fork()) > 0) {
		printf("Processus pere\n");
		sleep (2);
		printf("Reactivation du pere\n");
		kill(pid,SIGUSR1);
		wait(&status);
		printf("Fin des process\n");
	}
	else {
		printf("Processus fils\n");
		signal(SIGUSR1,spig);
		pause();
		sleep(5);
	}
}

void question1_3 () {
	int pid; 

	if ((pid = fork()) > 0) {
		printf("Processus pere\n");
		sleep (2);
		printf("Reactivation du pere\n");
		kill(pid,SIGUSR1);
		printf("Fin des process\n");
	}
	else {
		printf("Processus fils\n");
		signal(SIGUSR1,spig);
		pause();
		sleep(5);
	}
}

void question1_4 () {
	int pid; 
	int status; 

	if ((pid = fork()) > 0) {
		signal(SIGUSR1,spig);
		printf("Processus pere\n");
		pause();
		wait(&status);
		printf("Fin des process\n");
	}
	else {
		printf("Processus fils\n");
		sleep (2);
		printf("Reactivation du fils\n");
		kill(pid,SIGUSR1);
	}
}

void question2 (int nb_process) {
	int i, pid, status, err; 
	for (i = 0; i < nb_process; ++i) {
		if ((pid = fork()) == 0) {
			printf ("Fils %d (%d)\n", i, getpid());
			sleep (i);
			exit(0);
		} 
	}
	while ((err = wait(&status)) > 0) {
		printf ("Fin du processus %d - %d\n", err, status);
	}
}

void question3 (int max, int affichage) {
	int i, pid;
	for (i = 0; i < max || max < 0; ++i) {
		if ((pid = fork()) == 0) {
			if (affichage > 0)
			if (i % affichage == 0)
				printf ("Fils %d\n", i); 
			
			pause();
			exit(0);
		}
	}
}

void question4 (int argc, const char ** argv) {
	char str[100];
	int i, pid; 
	printf ("On a %d commandes\n", argc);
	for (i = 1; i < argc; ++i) {
		strcpy (str, argv[i]);
		printf ("\"%s\"\n", str);
		if ((pid = fork()) == 0) {
			execlp(argv[i], argv[i], (char *)NULL);
			sleep (1);
			exit(0);
		}
	}
}

void question5() {
	int fd[2], pid, status;
	pipe(fd);
	if ((pid = fork()) > 0) {
		close(fd[0]);
		char h[10];
		fgets(h, 10, stdin); 
		write(fd[1], h, (strlen(h)+1));
	}
	else {
		close(fd[1]);
		char h [10];
		read(fd[0], h, sizeof(h));
		printf("%s", h);
	}
}