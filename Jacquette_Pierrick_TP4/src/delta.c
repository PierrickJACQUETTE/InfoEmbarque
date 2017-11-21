// JACQUETTE Pierrick Tp4

#include "delta.h"

/**
* Effectue deltaTime(), deltaGettimeofday() puis deltaClockGettime()
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int delta(){
    int error;
    error = deltaTime();
    ERROR_SYS(error, "Erreur deltaTime() dans delta : delta.c");
    error = deltaGettimeofday();
    ERROR_SYS(error, "Erreur deltaGettimeofday() dans delta : delta.c");
    error = deltaClockGettime();
    ERROR_SYS(error, "Erreur deltaClockGettime() dans delta : delta.c");
    return EXIT_SUCCESS;
}

/**
* Affiche le plus petit intervalle de temps mesurables de time();
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int deltaTime(){
    time_t t = time(NULL);
    ERROR_SYS(t, "Erreur t dans deltaTime : delta.c");
    time_t t2 = time(NULL);
    ERROR_SYS(t, "Erreur t2 dans deltaTime : delta.c");
    while (t2 - t == 0) {    //avoir une difference entre deux relevés de mesure
        t = t2;
        t2 = time(NULL);
        ERROR_SYS(t, "Erreur t2 dans deltaTime : delta.c");
    }
    printf("Delta time : %d sec\n", (int)(t2 -t));
    return EXIT_SUCCESS;
}

/**
* Affiche le plus petit intervalle de temps mesurables de gettimeofday();
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int deltaGettimeofday(){
    int error;
    struct timeval start, stop;
    error = gettimeofday(&start, NULL);
    ERROR_SYS(error, "Erreur start dans deltaGettimeofday : delta.c");
    error = gettimeofday(&stop, NULL);
    ERROR_SYS(error, "Erreur stop dans deltaGettimeofday : delta.c");
    //avoir une difference entre deux relevés de mesure
    while ((stop.tv_sec - start.tv_sec == 0) && (stop.tv_usec - start.tv_usec == 0)){
        start.tv_sec = stop.tv_sec;
        start.tv_usec = stop.tv_usec;
        error = gettimeofday(&stop, NULL);
        ERROR_SYS(error, "Erreur stop dans deltaGettimeofday : delta.c");
    }
    printf("Delta gettimeofday : %ld sec - %ld usec\n", stop.tv_sec - start.tv_sec, stop.tv_usec - start.tv_usec);
    return EXIT_SUCCESS;
}

/**
* Affiche le plus petit intervalle de temps mesurables de clock_gettime();
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int deltaClockGettime(){
    int error;
    struct timespec start, stop;
    error = clock_gettime(CLOCK_MONOTONIC, &start);
    ERROR_SYS(error, "Erreur start dans deltaClockGettime : delta.c");
    error = clock_gettime(CLOCK_MONOTONIC, &stop);
    ERROR_SYS(error, "Erreur stop dans deltaClockGettime : delta.c");
    //avoir une difference entre deux relevés de mesure
    while ((stop.tv_sec - start.tv_sec == 0) && (stop.tv_nsec - start.tv_nsec == 0)) {
        start.tv_sec = stop.tv_sec;
        start.tv_nsec = stop.tv_nsec;
        error = clock_gettime(CLOCK_MONOTONIC, &stop);
        ERROR_SYS(error, "Erreur stop dans deltaClockGettime : delta.c");
    }
    printf("Delta gettime : %ld sec - %ld nsec\n", stop.tv_sec - start.tv_sec, stop.tv_nsec - start.tv_nsec);
    return EXIT_SUCCESS;
}
