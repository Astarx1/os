#include <iostream>
#include <stdlib.h>
#include "mvector.h"

int main () {
	void * (* f_malloc)(size_t) = &malloc;
	void (* f_free)(void *) = &free;

	std::cout << "Test my_malloc" << std::endl;

	mvector m;
	int * a = (int *) m.my_malloc(25*sizeof(int));
	int * b = (int *) m.my_malloc(sizeof(int));
	
	m.my_free (a);
	m.my_free (b);

	m.show();

	int * c = (int *) m.my_malloc(sizeof(int));
	
	m.show();

	m.my_free (c);
	
	m.show();

	return 0;
}