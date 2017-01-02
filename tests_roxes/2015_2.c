#include <stdio.h>
#include <unistd.h>

/* Ce code a un probleme. Lors du premier appel, fait via le shell
 * ledit shell ajoute le nom du programme au début, pas très grave
 * mais du coup on ne respecte pas vraiment l'idée ... */

int main (int argc, char * argv[]) {
	int i = 0;

	printf("Exec : \n");

	for (i = 0; i < argc; i++) {
		printf ("%s ", argv[i]);
	}

	printf("\n");

	if (argc > 1)
		execv("./2015_2.exe", argv+1);
}
