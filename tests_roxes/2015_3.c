#include <stdio.h>
#include <unistd.h>

/* A executer sous la forme :
 * ./2015_3.exe ./2015_3.exe
 */

int main (int argc, char ** argv) {
	printf ("%s\n", argv[0]);
	if (argc >= 1)
		execl (argv[1], argv[0], argv[0], NULL);
	else
		printf("Bug, nombre insuffisant d'arguments\n");
	return 0;
}
