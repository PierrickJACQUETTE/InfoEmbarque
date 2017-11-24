//JACQUETTE Pierrick Tp5

#include "check_priority.h"
#include "../annexe.h"

int main(int argc, char const *argv[]){
    int error = superUtilisateur();
    ERROR_DIFFZERO(error, "Vous etes qu'utilisateur : check_main.c");

	nb = 1000;
	if(argc > 1){
		if((nb = atoi(argv[1])) <= 0){
			fprintf(stderr, "Merci de rentrer un nombre positif\n");
			return EXIT_FAILURE;
		}
	}
    int number_failed;                               // nombre d'erreur
    Suite * s = init_suiteThread();                 // suite de test pour les threads
    SRunner *sr = srunner_create(s);                // creer la suite de test
    srunner_run_all(sr, CK_VERBOSE);                // imprime le résumé et un message par test (réussi ou échoué)
    number_failed = srunner_ntests_failed(sr);      //Récupérer le nombre de tests échoués
    srunner_free(sr);                               // liberer la memoire
    return (number_failed == 0) ? EXIT_SUCCESS: EXIT_FAILURE;
}
