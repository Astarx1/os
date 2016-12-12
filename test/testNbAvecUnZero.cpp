#include <iostream>

int count_zeros () {
	int nb = 0;
	for (int i = 0; i < 10000; ++i) {
		bool b = false;

		int j = i;
		while (j > 0) {
			if (j % 10 == 0) {
				nb ++;
				std::cout << i << " correspond" << std::endl;
				break;
			}
			j /= 10;
		}
	}
	return nb;
}

int main() {
	std::cout << "Au final, on trouve " << count_zeros() << std::endl;
	std::cout << (4 * 0.1 + 6 * 0.01*(1-4*0.1) + 11*0.0001) * 10000 << " par le calcul" << std::endl;
}