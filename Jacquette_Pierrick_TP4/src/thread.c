// JACQUETTE Pierrick Tp4

#include "thread.h"

/**
* Terminer immédiatement
*/
void* threadFonctionCreate(){
    return NULL;
}

/**
* Creer nbMesure thread pour mesure le temps de creation
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int threadCreate(int nbMesure, int nbFois){
    int error, i, j;
    pthread_t thread1;
    struct time chrono;
    void* pChrono = createStructTime(&chrono);
    ERROR_NULL(pChrono, "Error chrono createStructTime in threadCreate in thread.c");
    initStructTime(&chrono);
    for(j=0; j<nbFois; j++){ // faire nbFois la mesure
        error = startTime(&chrono);
        ERROR_SYS(error, "Error chrono startTime in threadCreate in thread.c");
        for(i=0; i<nbMesure; i++){ //faire la mesure pour nb create
            error =  pthread_create(&thread1, NULL, threadFonctionCreate, NULL); //creation du thread
            ERROR_THREAD(error, "Error pthread_create in threadCreate : thread.c");
            pthread_join(thread1, NULL); // depart de tous les threads
            ERROR_THREAD(error, "Error pthread_join in threadCreate : thread.c");
        }
        error = stopTime(&chrono);
        ERROR_SYS(error, "Error chrono stopTime in threadCreate in thread.c");
        error = progressTime(j, nbFois);
        ERROR_SYS(error, "Error progressTime in threadCreate in thread.c");
    }
    error = resultatTime(&chrono, nbMesure, nbFois, "Thread Create\t");
    ERROR_SYS(error, "Error resultatTime in threadCreate in thread.c");
    destroyStructTime(pChrono);
    return EXIT_SUCCESS;
}

/**
* Forcer un changement de context afin de mesure le temps
* code effectué par chaque thread
* les semaphores permettent de definir une section critique
* @param c structure contenant les variables partagées entre les threads
*/
void* threadFonctionContext(void* c){
    struct varContextThread * context = (struct varContextThread*) c;
    int error;
    if(context->indice == 0){
        int j, i;
        for(j=0; j<context->nbFois; j++){ // faire nbFois la mesure
            error = startTime(context->chrono);
            ERROR_STF(error, "Error chrono startTime in threadFonctionContext in thread.c");
            for(i=0; i<(context->nbMesure); i++){    //faire la mesure pour nb changement de context
                if(context->explicite == 1){
                    error = sem_wait(context->sem1);
                    ERROR_STF(error, "Error sem1 sem_wait in threadFonctionContext : thread.c");
                    error = sem_post(context->sem2);
                    ERROR_STF(error, "Error sem2 sem_post in threadFonctionContext : thread.c");
                }else{
                    error = sched_yield();
                    ERROR_STF(error, "Error father sched_yield in threadFonctionContext : thread.c");
                }
            }
        }
    }else if(context->indice == 1){
        int j, i;
        for(j=0; j<context->nbFois; j++){ // faire nbFois la mesure
            for(i=0; i<(context->nbMesure); i++){    //faire la mesure pour nb changement de context
                if(context->explicite == 1){
                    error = sem_wait(context->sem2);
                    ERROR_STF(error, "Error sem2 sem_wait in threadFonctionContext : thread.c");
                    error = sem_post(context->sem1);
                    ERROR_STF(error, "Error sem1 sem_post in threadFonctionContext : thread.c");
                }else{
                    error = sched_yield();
                    ERROR_STF(error, "Error father sched_yield in threadFonctionContext : thread.c");
                }
            }
            error = stopTime(context->chrono);
            ERROR_STF(error, "Error chrono stopTime in threadFonctionContext in thread.c");
            error = progressTime(j, context->nbFois);
            ERROR_STF(error, "Error progressTime in threadFonctionContext in thread.c");
        }
        if(context->explicite == 1 && context->policity == SCHED_OTHER){
            error = resultatTime(context->chrono, context->nbMesure, context->nbFois, "Thread Context ETP");
        }else if(context->explicite == 1 && context->policity == SCHED_FIFO){
            error = resultatTime(context->chrono, context->nbMesure, context->nbFois, "Thread Context EFIFO");
        }else if(context->explicite == 0 && context->policity == SCHED_FIFO){
            error = resultatTime(context->chrono, context->nbMesure, context->nbFois, "Thread Context IFIFO");
        }else if(context->explicite == 1 && context->policity == SCHED_RR){
            error = resultatTime(context->chrono, context->nbMesure, context->nbFois, "Thread Context ERR");
        }else if(context->explicite == 0 && context->policity == SCHED_RR){
            error = resultatTime(context->chrono, context->nbMesure, context->nbFois, "Thread Context IRR");
        }
        ERROR_STF(error, "Error resultatTime in threadFonctionContext in thread.c");
    }
    free(context);
    return NULL;
}

/**
* Creer deux threads et effectue nbMesure de changement de context
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @param  explicite permet de savoir si l'on veut un changement explicite ou implicite
* @param  policity politique a appliquer
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int threadContextJob(int nbMesure, int nbFois, int explicite, int policity){
    int nbThread = 2, i , error;
    struct varContextThread * context;
    struct time chrono;
    pthread_t tabThread[nbThread]; // tableau des threads
    pthread_t th;
    sem_t sem1, sem2;
    pthread_attr_t attr;
    error = pthread_attr_init(&attr);
    ERROR_THREAD(error, "Error  attr pthread_attr_init in threadContext : thread.c");
    if(explicite == 1){
        error = sem_init(&sem1, 0, 1);
        ERROR_SEM(error, "Error sem1 sem_init in threadContext : thread.c");
        error = sem_init(&sem2, 0, 0);
        ERROR_SEM(error, "Error sem2 sem_init in threadContext : thread.c");
    }
    if(policity != SCHED_OTHER){
        struct sched_param sched;
        int priority = (sched_get_priority_max(policity) - sched_get_priority_min(policity)) /2;
        sched.sched_priority = priority;
        // dans le cas dun changement de context implicite la fonction sched_yield() ne fonctionne pas avec pthread_explicit_sched
        if(explicite == 1){
        	error = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        }else{
        	error = pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
        }
        ERROR_THREAD(error, "Error  attr pthread_attr_setinheritsched in threadContext : thread.c");
        error = pthread_attr_setschedpolicy(&attr, policity);
        ERROR_THREAD(error, "Error  attr pthread_attr_setschedpolicy in threadContext : thread.c");
        error = pthread_attr_setschedparam(&attr, &sched);
        ERROR_THREAD(error, "Error  attr pthread_attr_setschedparam in threadContext : thread.c");
    }
    void* pChrono = createStructTime(&chrono);
    ERROR_NULL(pChrono, "Error chrono createStructTime in threadContext in thread.c");
    initStructTime(&chrono);
    for(i=0; i<nbThread; i++){
        // allocation de la structure de chaque thread puis des champs
        context = malloc (sizeof (struct varContextThread));
        ERROR_NULL(context, "Error malloc struct in threadContext: thread.c");
        if(explicite == 1){
            context->sem1 = &sem1;
            context->sem2 = &sem2;
        }
        context->indice = i;
        context->nbMesure = nbMesure;
        context->nbFois = nbFois;
        context->chrono = &chrono;
        context->explicite = explicite;
        context->policity = policity;
        error = pthread_create(&th, &attr, threadFonctionContext, (void*)context);      //creation du thread
        ERROR_THREAD(error, "Error pthread_create in threadContext : thread.c");
        tabThread[i] = th;          //stocke in le tableau
    }
    for(i=0; i < nbThread; i++){
        pthread_join(tabThread[i], NULL);       // depart de tous les threads
        ERROR_THREAD(error, "Error pthread_join in threadContext : thread.c");
    }
    destroyStructTime(pChrono);     //liberer la memoire
    if(explicite == 1){
        error = sem_destroy(&sem1);
        ERROR_SEM(error, "Error sem1 sem_destroy in threadContext : thread.c");
        error = sem_destroy(&sem2);
        ERROR_SEM(error, "Error sem2 sem_destroy in threadContext : thread.c");
    }
    if(policity != SCHED_OTHER){
        error = pthread_attr_destroy(&attr);
    }
    ERROR_THREAD(error, "Error  attr pthread_attr_destroy in threadContext : thread.c");
    return EXIT_SUCCESS;
}

/**
* Creer deux threads et effectue nbMesure de changement de context
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int threadContext(int nbMesure, int nbFois){
    int error;
    if(getuid()==0){
        error = threadContextJob(nbMesure, nbFois, 0, SCHED_FIFO);
        ERROR_SYS(error, "Error threadContext  fifo implicit in threadContext : thread.c");
        error = threadContextJob(nbMesure, nbFois, 0, SCHED_RR);
        ERROR_SYS(error, "Error threadContext  round-robin implicit in threadContext : thread.c");
        error = threadContextJob(nbMesure, nbFois, 1, SCHED_FIFO);
        ERROR_SYS(error, "Error threadContext  fifo explicit in threadContext : thread.c");
        error = threadContextJob(nbMesure, nbFois, 1, SCHED_RR);
        ERROR_SYS(error, "Error threadContext  round-robin explicit in threadContext : thread.c");
    }
    error = threadContextJob(nbMesure, nbFois, 1, SCHED_OTHER);
    ERROR_SYS(error, "Error threadContext temps partage in threadContext : thread.c");
    return EXIT_SUCCESS;
}
