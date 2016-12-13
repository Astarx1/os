#include <iostream>
#include <stdlib.h>
#include "mvector.h"

int main () {
	void * (* f_malloc)(size_t) = &malloc;
	void (* f_free)(void *) = &free;

	std::cout << "Test my_malloc" << std::endl;

	mvector m;
	int * a = (int *) m.my_malloc(sizeof(int));
	int * b = (int *) m.my_malloc(sizeof(int));
	*a = 80;
	std::cout << "a [" << a << "] : " << *a << std::endl;

	melement * h = (((melement *) a)-1);

	std::cout << "Prev : [" << h->prev << "] - [" << h->adr << "]/[" << h << "] - Next : [" << h->next << "]" << std::endl;
	std::cout << "Taille : " << h->bloc_s << "\n\n" << std::endl;
	
	m.my_free(a);
	m.my_free(b);

	m.show();

	return 0;
}