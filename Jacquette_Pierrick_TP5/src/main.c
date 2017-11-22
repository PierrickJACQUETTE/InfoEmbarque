// JACQUETTE Pierrick Tp5

#include "annexe.h"
#include "thread.h"

/**
* fonction main, le point d'entree du programme
* @param  argc nombre d'argument
* @param  argv tableau des arguments
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int main(int argc, char const *argv[]) {
    int error;
    int heritage = 0;
    error = superUtilisateur();
    ERROR_DIFFZERO(error, "Vous etes qu'utilisateur : main.c");
    error = parseArgument(argc, argv, &heritage);
    ERROR_DIFFZERO(error, "Error parseArgument in main : main.c");
    error = thread(&heritage);
    ERROR_SYS(error, "Error thread in main : main.c");
    char* reponse = (error == 1)? "Inversion detectee" : "Inversion non detectee";
    printf("%s\n",reponse );
    return EXIT_SUCCESS;
}
