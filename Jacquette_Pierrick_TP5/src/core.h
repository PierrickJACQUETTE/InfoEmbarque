// JACQUETTE Pierrick Tp5

#ifndef __CORE_H__
#define __CORE_H__

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

/**
* structure pour le passage d'argument a la fonction si on utilise les threads
*/
struct varThread {
    int* inversion;	            // permet de savoir si il y a eu inversion
    sem_t* semA;                // semaphore A
    sem_t* semB;                // semaphore B
    sem_t* semC;                // semaphore C
    pthread_mutex_t* mutex;     // mutex pour synchroniser le plus prioritaire et le moins prioritaire
    int* resultat;              // 1 si inversion et 0 sinon
};

/**
* permet de verifier les différents erreurs possibles
* afficher un message d'erreur et retourne une valeur indiquant qu'une erreur a eu lieu
*/
#define ERROR_NULL(a,str) if (a == NULL) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_SEM(a,str) if (a == -1) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_STF(a,str) if (a == -1) {fprintf(stderr, "\n%s\n\n", str); return (void*)EXIT_FAILURE;}
#define ERROR_SYS(a,str) if (a < 0) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_DIFFZERO(a,str) if (a != 0) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_DIFFZEROS(a,str) if (a != 0) {fprintf(stderr, "\n%s\n\n", str); return (void*)EXIT_FAILURE;}

#endif
