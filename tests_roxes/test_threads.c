#include <pthread.h>

typedef struct Spile {
	struct Spile * next;
	int val;
} pile;

static pile * head;
static pthread_mutex_t list_mutex;
static phtread_cond_t list_cond;

void * producer (void * arg) {
	while(1) {
		int a = 0;
		phtread_mutex_lock(list_mutex);
		pile * tmp = head;
		if (head != NULL) {
			for (; tmp->next != NULL; ++a)
				tmp = tmp->next;
			tmp->next = (pile *) malloc(sizeof(pile));
			tmp->next->val = head.val + 1;
			tmp->next->next = NULL;
		}
		else {
			pthread_mutex_lock(list_mutex);
			head = malloc (sizeof(pile));
			head->val = 0;
		}
		phtread_mutex_unlock(list_mutex);
	}
}

void * consumer (void * arg) {
	while (1) {
		pile * tmp;
		pthread_mutex_lock (list_mutex);
		while (head != NULL) {
			tmp = head;
			printf ("On recupere la valeur : %d", tmp->val);
			head = head->next;
		}
		pthread_mutex_unlock (list_mutex);
	}
}

int main () {
	
}
