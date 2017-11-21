// JACQUETTE Pierrick Tp4

#include "processus.h"

/**
* Creer un processus fils puis le termine, elle effectue cette opération
* nbMesure fois afin de mesurer le temps
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int processusCreate(int nbMesure, int nbFois){
    int error, i, j;
    struct time chrono;
    void* pChrono = createStructTime(&chrono);
    ERROR_NULL(pChrono, "Error chrono createStructTime in processusCreate in processus.c");
    initStructTime(&chrono);
    for(j=0; j<nbFois; j++){ // faire nbFois la mesure
        error = startTime(&chrono);
        ERROR_SYS(error, "Error chrono startTime in processusCreate in processus.c");
        for(i=0; i<nbMesure; i++){  //faire la mesure pour nb fork
            pid_t pid = fork();
            if(pid < 0){
                fprintf(stderr, "Error fork in processusCreate : processus.c");
                return EXIT_FAILURE;
            }else if(pid == 0){     //fils
                exit(EXIT_SUCCESS);
            }else{
                error = waitpid(pid, NULL, 0);
                ERROR_SYS(error, "Error waitpid in processusCreate : processus.c");
            }
        }
        error = stopTime(&chrono);
        ERROR_SYS(error, "Error chrono stopTime in processusCreate in processus.c");
        error = progressTime(j, nbFois);
        ERROR_SYS(error, "Error progressTime in processusCreate in processus.c");
    }
    error = resultatTime(&chrono, nbMesure, nbFois, "Processus Create");
    ERROR_SYS(error, "Error resultatTime in processusCreate in processus.c");
    destroyStructTime(pChrono);
    return EXIT_SUCCESS;
}

/**
*Creer un processus fils et effectue nbMesure de changement de
* context entre le fils et le pere
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @param  explicite permet de savoir si l'on veut un changement explicite ou implicite
* @param  policity politique a appliquer
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int processusContextJob(int nbMesure, int nbFois, int explicite, int policity){
    int error;
    struct varContextProcessus* context;
    // initialiser une zone memoire pour la partagé entre plusieurs processus
    context = mmap(NULL, sizeof(struct varContextProcessus), PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    ERROR_MAP(context, "Error malloc struct in processusContext: processus.c");
    if(explicite == 1){
        error = sem_init(&context->sem1, 1, 1);
        ERROR_SEM(error, "Error sem1 sem_init in processusContext : processus.c");
        error = sem_init(&context->sem2, 1, 0);
        ERROR_SEM(error, "Error sem2 sem_init in processusContext : processus.c");
    }
    void* pChrono = createStructTime(&context->chrono);
    ERROR_NULL(pChrono, "Error chrono createStructTime in processusContext in processus.c");
    initStructTime(&context->chrono);
    if(policity != SCHED_OTHER){
        struct sched_param sched;
        int priority = (sched_get_priority_max(policity) - sched_get_priority_min(policity)) /2;
        sched.sched_priority = priority;
        error = sched_setscheduler(getpid(), policity, &sched);
        ERROR_SYS(error, "Error sched_setscheduler in processusContext in processus.c");
    }
    pid_t pid = fork();
    if(pid < 0){
        fprintf(stderr, "Error fork in processusContext : processus.c");
        return EXIT_FAILURE;
    }else if(pid == 0){ //fils
        int j, i;
        for(j=0; j<nbFois; j++){ // faire nbFois la mesure
            error = startTime(&context->chrono);
            ERROR_SYS(error, "Error chrono startTime in processusContext in processus.c");
            for(i=0; i<nbMesure; i++){ //faire la mesure pour nb changement de context
                if(explicite == 1){
                    error = sem_wait(&context->sem1);
                    ERROR_SEM(error, "Error sem1 sem_wait in processusContext : processus.c");
                    error = sem_post(&context->sem2);
                    ERROR_SEM(error, "Error sem2 sem_post in processusContext : processus.c");
                }else{
                    error = sched_yield();
                    ERROR_SYS(error, "Error child sched_yield in processusContext : processus.c");
                }
            }
        }
        exit(EXIT_SUCCESS);
    }else{
        int j, i;
        for(j=0; j<nbFois; j++){// faire nbFois la mesure
            for(i=0; i<nbMesure; i++){ //faire la mesure pour nb changement de context
                if(explicite == 1){
                    error = sem_wait(&context->sem2);
                    ERROR_SEM(error, "Error sem2 sem_wait in processusContext : processus.c");
                    error = sem_post(&context->sem1);
                    ERROR_SEM(error, "Error sem1 sem_post in processusContext : processus.c");
                }else{
                    error = sched_yield();
                    ERROR_SYS(error, "Error father sched_yield in processusContext : processus.c");
                }
            }
            error = stopTime(&context->chrono);
            ERROR_SYS(error, "chrono stopTime in processusContext in processus.c");
            error = progressTime(j, nbFois);
            ERROR_SYS(error, "Error progressTime in processusContext in processus.c");
        }
        error = waitpid(pid,  NULL, 0);
        ERROR_SEM(error, "Error waitpid in processusContext : processus.c");
    }
    if(explicite == 1 && policity == SCHED_OTHER){
        error = resultatTime(&context->chrono, nbMesure, nbFois, "Processus Context ETP");
    }else if(explicite == 1 && policity == SCHED_FIFO){
        error = resultatTime(&context->chrono, nbMesure, nbFois, "Processus Context EFIFO");
    }else if(explicite == 0 && policity == SCHED_FIFO){
        error = resultatTime(&context->chrono, nbMesure, nbFois, "Processus Context IFIFO");
    }else if(explicite == 1 && policity == SCHED_RR){
        error = resultatTime(&context->chrono, nbMesure, nbFois, "Processus Context ERR");
    }else if(explicite == 0 && policity == SCHED_RR){
        error = resultatTime(&context->chrono, nbMesure, nbFois, "Processus Context IRR");
    }
    ERROR_SYS(error, "Error resultatTime in processusContext in processus.c");
    destroyStructTime(pChrono);    // liberer la memoire
    if(explicite==1){
        error = sem_destroy(&context->sem1);
        ERROR_SEM(error, "Error sem1 sem_destroy in processusContext : processus.c");
        error = sem_destroy(&context->sem2);
        ERROR_SEM(error, "Error sem2 sem_destroy in processusContext : processus.c");
    }
    error = munmap(context, sizeof(struct varContextProcessus));
    ERROR_MUMMAP(error, "Error munmap in processusContext : processus.c");
    return EXIT_SUCCESS;
}

/**
*Creer un processus fils et effectue nbMesure de changement de
* context entre le fils et le pere
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int processusContext(int nbMesure, int nbFois){
    int error;
    error = processusContextJob(nbMesure, nbFois, 1, SCHED_OTHER);
    ERROR_SYS(error, "Error processusContext temps partage in processusContext : processus.c");
    if(getuid()==0){
        error = processusContextJob(nbMesure, nbFois, 0, SCHED_FIFO);
        ERROR_SYS(error, "Error fifo implicit in processusContext : processus.c");
        error = processusContextJob(nbMesure, nbFois, 0, SCHED_RR);
        ERROR_SYS(error, "Error round-robin implicit in processusContext : processus.c");
        error = processusContextJob(nbMesure, nbFois, 1, SCHED_FIFO);
        ERROR_SYS(error, "Error fifo explicit in processusContext : processus.c");
        error = processusContextJob(nbMesure, nbFois, 1, SCHED_RR);
        ERROR_SYS(error, "Error round-robin explicit in processusContext : processus.c");
    }
    return EXIT_SUCCESS;
}
