#ifndef MVECTOR_H
#define MVECTOR_H

 #include <unistd.h> 
typedef struct S_MemElem {
public:
	struct S_MemElem * next;
	struct S_MemElem * prev;

	size_t bloc_s;

	void * adr;

	long magic_number;
} melement;

class mvector {
public:
	void * my_malloc (size_t);
	void my_free (void * adr);
	void show();

	mvector() { free_f = NULL; }
private:
	melement * free_f;
};

void * mvector::my_malloc(size_t t) {
	// On check d'abord si on aurait pas un peu de place en mémoire
	melement * cur = free_f;

	while (cur != NULL) { 
		if (cur->bloc_s >= t) {
			if (cur->bloc_s > t + sizeof(melement)) {
				melement * nh = (melement *) (((char*)cur->adr)+t+sizeof(melement));

				if (cur->next != NULL)
					cur->next->prev = nh;
				if (cur->prev != NULL)
					cur->prev->next = nh;
				else
					free_f = nh;

				nh->next = cur->next;
				nh->prev = cur->prev;

				nh->bloc_s = cur->bloc_s-t-sizeof(melement);
				nh->adr = (void *) nh;
				nh->magic_number = 0x12345678;
				std::cout 	<< "mvector::my_malloc : Reallocation " << t + sizeof(melement) << "/" << cur->bloc_s 
							<< " - [" << cur->adr << ", header]" << std::endl;	

				cur->bloc_s = t;
				return (((melement *) cur->adr)+1);
			}
			else {
				if (cur->next != NULL) 
					cur->next->prev = cur->prev;
				if (cur->prev != NULL) 
					cur->prev->next = cur->next;
				else 
					free_f = cur->next;

				std::cout 	<< "mvector::my_malloc : Reallocation entiere - [" << cur->adr << ", header]" << std::endl;	

				return (((melement *) cur->adr)+1);
			}
		}

		cur = free_f->next;
	}

	melement * a = (melement*) sbrk(t+sizeof(melement));	
	std::cout << "mvector::my_malloc : Allocation " << t + sizeof(melement) << " - [" << a << "]" << std::endl;
	a->prev = NULL;
	a->next = NULL;
	a->bloc_s = t;
	a->adr = a;
	a->magic_number = 0x12345678;
	return (void*) (a+1);
}

void mvector::my_free (void * adr) {
	melement * cur = free_f;
	melement * h = (((melement*) adr)-1);
	std::cout << "Free [" << h << "] - header - pour une adr [" << h->adr << "]\n" << std::endl;

	if (cur != NULL) {
		while (cur->next != NULL) { 
			if (cur->adr < adr) {	// Aggregation venant de la droite
				if (((char*) cur->adr) + cur->bloc_s + sizeof(melement) == (char *) h->adr) {
					std::cout << "Agglomeration venant de la droite detectee !" << std::endl;
					cur->bloc_s += h->bloc_s + sizeof(melement);
					return;
				}
			}
			else { // Ou de la gauche
				if (((char *) h->adr) + h->bloc_s + sizeof(melement) == (char *) cur->adr) {
					std::cout << "Agglomeration venant de la gauche detectee !" << std::endl;				
					if (cur->next != NULL)
						cur->next->prev = h;
					if (cur->prev != NULL)
						cur->prev->next = h;
					else
						free_f = h;

					h->next = cur->next;
					h->prev = cur->prev;
					h->bloc_s += cur->bloc_s+sizeof(melement);
					return;
				}
			}
			cur = cur->next;
		}

		cur->next = h;
		h->prev = cur;
	}
	else {
		free_f = h;
	}
}

void mvector::show() {
	melement * cur = free_f;
	std::cout << "Pile de memoire libre : " << std::endl; 
	while (cur != NULL) {
		std::cout << "Prev : [" << cur->prev << "] - [" << (void*) cur->adr << "] - Next : [" << cur->next << "]" << std::endl;
		std::cout << "Taille : " << cur->bloc_s << "\n\n" << std::endl;
		cur = cur->next;
	}
} 
#endif