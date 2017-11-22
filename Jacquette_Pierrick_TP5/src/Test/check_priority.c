//JACQUETTE Pierrick Tp5

#include "check_priority.h"

/**
* Vérifie que les deux valeurs soit identiques
* @param heritage pour le test souhaite
* @param resultatSouhaite resultat que l'on doit obtenir
*/
void checkThread(int * heritage, int* resultatSouhaite){
	int i;
	for(i=0; i<NB; i++){
		int resultatObtenu = thread(heritage);	// tableau du resultat de la fonction
		ck_assert_int_eq(resultatObtenu, *resultatSouhaite);
	}
}

START_TEST(heritage_0){
	int heritage = 0, resultat = 1;
	checkThread(&heritage, &resultat);
}END_TEST

START_TEST(heritage_1){
	int heritage = 1, resultat = 0;
	checkThread(&heritage, &resultat);
}END_TEST

/**
* creer la suite de test
* @return  la suite de test
*/
Suite* init_suiteThread(void){

	Suite* s= suite_create("Thread");
	TCase *tc= tcase_create("StandardThread");
	tcase_add_test(tc, heritage_1);
	tcase_add_test(tc, heritage_0);
	suite_add_tcase(s, tc) ;
	return s;
}
