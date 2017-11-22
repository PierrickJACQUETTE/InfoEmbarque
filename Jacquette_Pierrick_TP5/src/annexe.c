// JACQUETTE Pierrick Tp5
 
#include "annexe.h"

/**
* fixer le programme sur un cpu
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int fixerCpu(){
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    int error = sched_setaffinity(getpid(), sizeof(set), &set);
    ERROR_SYS(error, "Error sched_setaffinity in fixerCpu : annexe.c");
    return EXIT_SUCCESS;
}

/**
* verfie que le programme est exécuté en mode super Utilisateur
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int superUtilisateur(){
    int error = getuid();
    ERROR_DIFFZERO(error, "Merci de passer en mode superUtilisateur\n \t sudo ./tp5 [option]");
    return EXIT_SUCCESS;
}

/**
* parse les arguments donne en ligne de commande
* @param  argc nombre d'argument
* @param  argv tableau des arguments
* @param heritage adresse où inscrire la valeur d'heritage 0 ou 1
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int parseArgument(int argc, char const *argv[], int* heritage){
    if(argc >= 2){
        (*heritage) = atoi(argv[1]);
    }
    return EXIT_SUCCESS;
}
