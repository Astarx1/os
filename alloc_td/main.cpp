#include <iostream>
#include <stdlib.h>
#include "mvector.h"

int main () {
	void * (* f_malloc)(size_t) = &malloc;
	void (* f_free)(void *) = &free;

	mvector m;
	m.malloc(10);
	m.show();
	
	return 0;
}