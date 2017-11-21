// JACQUETTE Pierrick Tp4

#ifndef __CORE_H__
#define __CORE_H__

#define _GNU_SOURCE


#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

/**
* structure pour reprensenter toutes les variables necessaires pour avoir
* des temps
*/
struct time{
    double max;             // temps maximum
    double min;             // temps minimum
    double somme;           // somme des temps
    struct timespec start;  // temps de depart
    struct timespec stop;   // temps de fin
};

/**
* structure pour le passage d'argument a la fonction si on utilise les threads
*/
struct varContextThread {
    int explicite;  // changement de context explicite 1 ou implicite 0
    int policity;   // changement de politique
    int indice;     // indice permettant de savoir quelle est le thread courant
    int nbMesure;   // permet de passer la valeur en argument au thread
    int nbFois;		// permet de passer la valeur en argument au thread
    sem_t* sem1;    // semaphore 1
    sem_t* sem2;    // semaphore 2
    struct time* chrono;     // struct pour le temps
};

/**
* structure pour le passage d'argument a la fonction si on utilise plusieurs processus
*/
struct varContextProcessus {
    int explicite;         // changement de context explicite 1 ou implicite 0
    sem_t sem1;            // semaphore 1
    sem_t sem2;            // semaphore 2
    struct time chrono;    // struct pour le temps
};

/**
* permet de verifier les différents erreurs possibles
* afficher un message d'erreur et retourne une valeur indiquant qu'une erreur a eu lieu
*/
#define ERROR_MAP(a,str) if (a == MAP_FAILED || a == NULL) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_MUMMAP(a,str) if (a == -1) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_NULL(a,str) if (a == NULL) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_SEM(a,str) if (a == -1) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_STF(a,str) if (a == -1) {fprintf(stderr, "\n%s\n\n", str); return (void*)EXIT_FAILURE;}
#define ERROR_SYS(a,str) if (a < 0) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_THREAD(a,str) if (a != 0) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_USER(a,str) if (a != 0) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}
#define ERROR_WAIT(a,str) if (a == -1) {fprintf(stderr, "\n%s\n\n", str); return EXIT_FAILURE;}

#endif
