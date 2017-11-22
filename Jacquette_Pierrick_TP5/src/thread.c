// JACQUETTE Pierrick Tp5

#include "thread.h"

/**
* Thread le plus prioritaire
* @param c structure contenant les variables partagées entre les threads
*/
void* threadA(void* c){
    struct varThread* varThread = (struct varThread*) c;
    int error;
    error = sem_wait(varThread->semA);
    ERROR_STF(error, "Error semA sem_wait in threadA : thread.c");
    error = sem_post(varThread->semB);
    ERROR_STF(error, "Error semB sem_post in threadA : thread.c");
    error = pthread_mutex_lock(varThread->mutex);
    ERROR_DIFFZEROS(error, "Error  mutex pthread_mutex_lock in threadA : thread.c");
    error = pthread_mutex_unlock(varThread->mutex);
    ERROR_DIFFZEROS(error, "Error  mutex pthread_mutex_unlock in threadA : thread.c");
    *(varThread->resultat) = (*(varThread->inversion) == 1)? 1 : 0;
    free(varThread);
    return NULL;
}

/**
* Thread avec une priorite moyenne
* @param c structure contenant les variables partagées entre les threads
*/
void* threadB(void* c){
    struct varThread* varThread = (struct varThread*) c;
    int error;
    error = sem_wait(varThread->semB);
    ERROR_STF(error, "Error semB sem_wait in threadB : thread.c");
    *(varThread->inversion) = 1;
    free(varThread);
    return NULL;
}

/**
* Thread le moins prioritaire
* @param c structure contenant les variables partagées entre les threads
*/
void* threadC(void* c){
    struct varThread* varThread = (struct varThread*) c;
    int error;
    error = sem_wait(varThread->semC);
    ERROR_STF(error, "Error semC premier sem_wait in threadC : thread.c");
    error = pthread_mutex_lock(varThread->mutex);
    ERROR_DIFFZEROS(error, "Error  mutex pthread_mutex_lock in threadC : thread.c");
    error = sem_post(varThread->semA);
    ERROR_STF(error, "Error semA sem_post in threadC : thread.c");
    error = pthread_mutex_unlock(varThread->mutex);
    ERROR_DIFFZEROS(error, "Error  mutex pthread_mutex_unlock in threadC : thread.c");
    free(varThread);
    return NULL;
}

/**
* Creer les threads et  les lancer
* @param heritage valeur de l'heritage 0 ou 1
* @return int : 0 si tout ce passe bien et pas inversion,
*               1 si tout ce passe bien et inversion
*               -1 en cas d'erreur
*/
int thread(int* heritage){
    int nbThread = 3, i , error, policity = SCHED_FIFO, inversion = 0, resultat = -1;
    struct varThread * varThread;
    pthread_t tabThread[nbThread]; // tableau des threads
    pthread_t th;
    sem_t semA, semB, semC;
    pthread_attr_t attr;
    pthread_mutexattr_t m_attr;
    pthread_mutex_t mutex;

    error = fixerCpu();
    ERROR_DIFFZERO(error, "Error fixerCpu in thread : thread.c");

    error = pthread_mutexattr_init(&m_attr);
    ERROR_DIFFZERO(error, "Error pthread_mutexattr_init in thread : thread.c");
    if((*heritage)==1){
        error = pthread_mutexattr_setprotocol(&m_attr, PTHREAD_PRIO_INHERIT);
        ERROR_DIFFZERO(error, "Error  m_attr pthread_mutexattr_setprotocol in thread : thread.c");
    }
    error = pthread_attr_init(&attr);
    ERROR_DIFFZERO(error, "Error  attr pthread_attr_init in thread : thread.c");
    error = sem_init(&semA, 0, 0);
    ERROR_SEM(error, "Error semA sem_init in thread : thread.c");
    error = sem_init(&semB, 0, 0);
    ERROR_SEM(error, "Error semB sem_init in thread : thread.c");
    error = sem_init(&semC, 0, 1);
    ERROR_SEM(error, "Error semC sem_init in thread : thread.c");
    error = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    ERROR_DIFFZERO(error, "Error  attr pthread_attr_setinheritsched in thread : thread.c");
    error = pthread_attr_setschedpolicy(&attr, policity);
    ERROR_DIFFZERO(error, "Error  attr pthread_attr_setschedpolicy in thread : thread.c");
    error = pthread_mutex_init(&mutex, &m_attr);
    ERROR_DIFFZERO(error, "Error pthread_mutex_init in thread : thread.c");
    struct sched_param sched;
    int priority = (sched_get_priority_max(policity) - sched_get_priority_min(policity)) /2;
    for(i=0; i<nbThread; i++){
        varThread = malloc (sizeof (struct varThread));
        ERROR_NULL(varThread, "Error malloc struct in thread : thread.c");
        varThread->semA = &semA;
        varThread->semB = &semB;
        varThread->semC = &semC;
        varThread->mutex = &mutex;
        varThread->inversion = &inversion;
        varThread->resultat = &resultat;
        sched.sched_priority = (i==0)? sched_get_priority_max(policity) : (i==1)? priority : priority/2;
        error = pthread_attr_setschedparam(&attr, &sched);
        ERROR_DIFFZERO(error, "Error  attr pthread_attr_setschedparam in thread : thread.c");
        void* fonction = NULL;
        fonction = (i==0)? threadA : (i==1)? threadB : threadC;
        error = pthread_create(&th, &attr, fonction, (void*)varThread);
        ERROR_DIFFZERO(error, "Error pthread_create in thread : thread.c");
        tabThread[i] = th;
    }
    for(i=0; i < nbThread; i++){
        pthread_join(tabThread[i], NULL);
        ERROR_DIFFZERO(error, "Error pthread_join in thread : thread.c");
    }
    error = sem_destroy(&semA);
    ERROR_SEM(error, "Error semA sem_destroy in thread : thread.c");
    error = sem_destroy(&semB);
    ERROR_SEM(error, "Error semB sem_destroy in thread : thread.c");
    error = sem_destroy(&semC);
    ERROR_SEM(error, "Error semC sem_destroy in thread : thread.c");
    error = pthread_attr_destroy(&attr);
    ERROR_DIFFZERO(error, "Error  attr pthread_attr_destroy in thread : thread.c");
    return resultat;
}
