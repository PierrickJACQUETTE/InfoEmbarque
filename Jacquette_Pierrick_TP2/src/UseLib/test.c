// JACQUETTE Pierrick Tp1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "../colimacon.h"

#define ERROR(a,str) if (a < 3) {errno = 1; perror(str); exit(EXIT_FAILURE);}

int main(int argc, char const *argv[]) {
    int affichage = 1;  // par defaut affichage
    int ligne, colonne, retour;
    ERROR(argc, "Il faut au moins 2 arguments !");     // macro permettant de verifier les erreurs

    ligne = atoi(argv[1]);
    colonne = atoi(argv[2]);

    // si l'utilisateur dit qu'il veut pas d'affichage
    if(argc >= 4 && atoi(argv[3])== 0){
        affichage = 0;
    }

    int* tab;
    //remplissant le tableau
    if (argc >= 5 && atoi(argv[4])==1){
        retour = colimaconThread(&tab, ligne, colonne);        // fonction avec thread
    }else{
        retour = colimacon(&tab, ligne, colonne);            // fonction sans thread
    }
    if(retour < 0){                                         // test le retour de ma fonction
        exit(EXIT_FAILURE);
    }

    if(affichage==1){
        affiche(tab, ligne, colonne);                    // fonction d'affichage
    }

    free(tab);                                // liberation du tableau

    return 0;
}
