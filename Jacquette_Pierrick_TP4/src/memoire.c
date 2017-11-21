// JACQUETTE Pierrick Tp4

#include "memoire.h"

/**
* Alloue nbMesure fois 1 256 1024 4096 128000 octets
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int memoireCreate(int nbMesure, int nbFois){
    void* erreur;
    int error, i, j, k;
    size_t tab[5] = {1, 256, 1024, 4096, 128000};
    struct time chrono;
    void* pChrono = createStructTime(&chrono);
    ERROR_NULL(pChrono, "Error chrono createStructTime in memoireCreate in memoire.c");
    initStructTime(&chrono);
    for(i=0; i< sizeof(tab)/sizeof(size_t); i++){   //pour chaque valeur a tester
        initStructTime(&chrono);
        for(k=0; k<nbFois; k++){ // faire nbFois la mesure
            error = startTime(&chrono);
            ERROR_SYS(error, "Error chrono startTime in memoireCreate in memoire.c");
            for(j=0; j<nbMesure; j++){  // je fais nbMesure
                erreur = malloc(tab[i]);
                ERROR_NULL(erreur, "Error malloc octet in memoireCreate: memoire.c");
                free(erreur);
            }
            error = stopTime(&chrono);
            ERROR_SYS(error, "Error chrono stopTime in memoireCreate in memoire.c");
            error = progressTime(k, nbFois);
            ERROR_SYS(error, "Error progressTime in memoireCreate in memoire.c");
        }
        char* str = malloc(sizeof(char)*15);
        sprintf(str, "Memoire %d\t", (int)tab[i]);
        error = resultatTime(&chrono, nbMesure, nbFois, str);
        ERROR_SYS(error, "Error resultatTime in memoireCreate in memoire.c");
        free(str);
    }
    destroyStructTime(pChrono);
    return 0;
}
