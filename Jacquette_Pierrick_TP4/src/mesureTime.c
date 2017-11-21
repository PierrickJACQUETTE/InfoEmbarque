// JACQUETTE Pierrick Tp4

#include "mesureTime.h"

int fisrtPrint = 1;

/**
* Permet de creer la structure
* @param chrono l'adresse où là stocker
*/
void* createStructTime(struct time* chrono){
    chrono = (struct time*) malloc(sizeof(struct time));
    if( chrono == NULL){
        fprintf(stderr, "Error malloc struct in createStructTime: mesureTime.c");
        return NULL;
    }
    return chrono;
}

/**
* Permet de mettre les champs de la structure à des valeurs par defaults
* @param chrono l'adresse où là stocker
*/
void initStructTime(struct time* chrono){
    chrono->min = DBL_MAX;
    chrono->somme = 0;
    chrono->max = 0;
}

/**
* Permet de conserver un temps de depart (cet instant)
* @param  chrono structure de stockage
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int startTime(struct time* chrono){
    int error = clock_gettime(CLOCK_MONOTONIC, &chrono->start);
    ERROR_SYS(error, "Error start : clock_gettime in startTime: mesureTime.c");
    return EXIT_SUCCESS;
}

/**
* Permet de conserver un temps de fin (cet instant)
* calcul la difference entre stop et start en seconde (en gardant de la precision)
* met a jour les variables max, min et somme de la structure
* @param  chrono structure de stockage
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int stopTime(struct time* chrono){
    int error = clock_gettime(CLOCK_MONOTONIC, &chrono->stop);
    ERROR_SYS(error, "Error stop : clock_gettime in stopTime: mesureTime.c");
    double mesure = (chrono->stop.tv_sec - chrono->start.tv_sec)*1E6 + (chrono->stop.tv_nsec - chrono->start.tv_nsec)/1E3;
    chrono->max = (mesure>chrono->max)? mesure : chrono->max;
    chrono->min = (mesure<chrono->min)? mesure : chrono->min;
    chrono->somme += mesure;
    return EXIT_SUCCESS;
}

/**
* Permet d'avoir un pourcentage de progression pour chaque calcul
* @param  position d'avancement dans les calculs
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int progressTime(int position, int nbFois){
    int error = printf("\r%d %%", (int)(((double)position/(double)nbFois)*100));
    ERROR_SYS(error, "Error printf : progressTime in mesureTime.c");
    error = fflush(stdout);
    ERROR_USER(error, "Error fflush : progressTime : mesureTime.c ");
    return EXIT_SUCCESS;
}

/**
* Permet d'afficher en console les resultat obtenues
* @param  chrono   structure de stockage
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois 	nombre de fois où l'on fait releve de temps
* @param  quoi     chaine de caractere pour preciser l'affichage
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int resultatTime(struct time* chrono, int nbMesure, int nbFois, char* quoi){
    int error;
    // ecrire l'entete du fichier si il n'existe pas
    if(graph == 1 && fisrtPrint == 1){
        error = initFile(nbMesure);
        ERROR_SYS(error, "Error initFile : resultatTime : mesureTime.c");
    }
    //ecrire l'entete du tableau si on est les premiers
    if(fisrtPrint == 1){
        error = printf("\r        \nLegende : \nETP : explicite temps partagé\
        \nEFIFO : explicite fifo\nIFIFO : implicite fifo\
        \nERR : explicite round-robin\nIRR : implicite round-robin\
        \n\n%d\t\t\t%s\t%s\t%s\n", nbMesure, "Avg (en usec)", "Min (en usec)",  "Max (en usec)");
        ERROR_SYS(error, "Error printf : resultatTime in mesureTime.c");
        fisrtPrint = 0;
    }
    //ecrire sur la sortie standard le resultat
    error = printf("\r%s\t%.11lf\t%.11lf\t%.11lf\n", quoi, (chrono->somme/nbFois)/nbMesure, chrono->min/nbMesure, chrono->max/nbMesure);
    ERROR_SYS(error, "Error resultat : printf : resultatTime in mesureTime.c");
    //ecrire dans le fichier le resultat
    if(graph == 1){
        error = writeFile(chrono, nbFois, nbMesure);
        ERROR_SYS(error, "Error writeFile : resultatTime : mesureTime.c");
    }
    return EXIT_SUCCESS;
}

/**
* Permet de liberer la memoire
* @param chrono structure a liberer
*/
void destroyStructTime(void* chrono){
    free(chrono);
}
