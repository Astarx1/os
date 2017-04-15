#include <stdlib.h>
#include <stdio.h>
size_t *ptr;

void function(int a, int b, int c) {
	char buffer1[4];
	for(a = 0 ; a < 6 ; a++) {
		ptr = buffer1 + a;
		printf("%p, %p\n", ptr, *ptr);
		*ptr = function;
	}
}

void main() {
	int x;
	function(1,2,3);
}