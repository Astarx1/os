#include <iostream>
#include <stdlib.h>
#include "mvector.h"

int main () {
	void * (* f_malloc)(size_t) = &malloc;
	void (* f_free)(void *) = &free;

	std::cout << "Test my_malloc" << std::endl;

	mvector m;
	int * a = (int *) m.my_malloc(sizeof(int));
	melement * h = (melement *) a - sizeof(melement);

	std::cout << "Prev : [" << h->prev << "] - [" << h->adr-sizeof(melement) << "] - Next : [" << h->next << "]" << std::endl;
	std::cout << "Taille : " << h->bloc_s << "\n\n" << std::endl;
	
	m.show();

	return 0;
}