#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct_game {
	environ_t *env;
	agent_t *agent;
	action_t* action;
	int result;
} game_t;

action_t* compute_best_action(agent_t *, environ_t *);
pthread_mutex_t mutex1, mutex2, mutex3, mutex4, mutex5;
pthread_cond_t cond1, cond2, cond3, cond4, cond5;
game_t game;

void* engine_thread(void* arg) {
	pthread_mutex_lock(mutex1);
	while(1) {
		pthread_cond_wait(cond1, mutex1);
		game->result = solve(game->env, game->agent, game->action);
	}
	pthread_mutex_unlock(mutex1);
}

/* Le problème avec cette option, c'est que l'on peut travailler et envoyer des actions qui ne sont pas en lien avec l'environnement actuel (modification après une action d'un autre agent_thread). Mais on dit dans le sujet "De même, toute modification de l’environnement fausse les calculs de coup optimal en cours, ce qu’on ignorera complètement" 
Du coup le seul vrai problème vient de la variable partagée que l'on modifie des deux cotés*/
void* agent_thread_pas_bon(void* arg) {
	agent_t *this; // récupéré depuis arg

	while(1) {
		action_t *a = compute_best_action(this, game->env);
		game->action = a; // Important pour que l'action soit prise en compte
		pthread_cond_signal(cond1);
	}
}

/* Du coup, pour que les modifs soient vraiment soient vraiment exclusives, on doit rajouter ça : */
void* agent_thread(void* arg) {
	agent_t *this; // récupéré depuis arg

	while(1) {
		action_t *a = compute_best_action(this, game->env);

		pthread_mutex_lock(mutex1);
		// Si on n'avait pas "c’est le prix à payer pour aller plus vite" on rajouterait un test de validite ici ...
		game->action = a;
		pthread_cond_signal(cond1);
		pthread_mutex_unlock(mutex1);
	}
}


/* Et je pense que tu peux même essayer : */

void* engine_thread_bof(void* arg) {
	pthread_mutex_lock(mutex1);
	while(1) {
		pthread_cond_wait(cond1, mutex1);
		game->result = solve(game->env, game->agent, game->action);

		pthread_mutex_lock(mutex2);
		pthread_cond_signal(cond2);
		pthread_mutex_unlock(mutex2);
	}
	pthread_mutex_unlock(mutex1);
}

void* agent_thread_bof(void* arg) {
	agent_t *this; // récupéré depuis arg

	while(1) {
		action_t *a = compute_best_action(this, game->env);

		pthread_mutex_lock(mutex1);
		// Si on n'avait pas "c’est le prix à payer pour aller plus vite" on rajouterait un test de validite ici ...
		game->action = a;
		pthread_cond_signal(cond1);
		pthread_mutex_unlock(mutex1);

		pthread_mutex_lock(mutex2);	// C'est là où j'ai un doute du coup, parce que les clients pourraient "s'accumuler" ici, et 
		// ne pas tous calculer une solution de temps, ce qui pour moi invalide cette solution
		pthread_cond_wait(cond2, mutex2);
		pthread_mutex_unlock(mutex2);
	}
}