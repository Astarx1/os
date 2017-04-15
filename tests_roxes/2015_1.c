#include <stdio.h>
#include <unistd.h>

void secret(int a) {
	if (a>0) {
		printf("get %d\n", a);
		if (fork())
			secret(a-1);
		else
			secret(a-2);
	}
}

int main() {
	secret(5);
	return 0;
}
