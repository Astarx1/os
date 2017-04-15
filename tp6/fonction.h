#ifndef FONCTION_H
#define FONCTION_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int a = 10;
pthread_mutex_t lock;

extern void affiche (int x, int y);
/*extern void Calcul(int NbIteration);
extern void * routineCalcul(void * NbIteration);
*/
#endif

/*
*/