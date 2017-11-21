// JACQUETTE Pierrick Tp4

#ifndef __MESURETIME_H__
#define __MESURETIME_H__

extern int fisrtPrint;


#include "graph.h"

/**
* Permet de creer la structure
* @param chrono l'adresse où là stocker
*/
void* createStructTime(struct time* chrono);

/**
* Permet de mettre les champs de la structure à des valeurs par defaults
* @param chrono l'adresse où là stocker
*/
void initStructTime(struct time* chrono);


/**
* Permet de conserver un temps de depart (cet instant)
* @param  chrono structure de stockage
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int startTime(struct time* chrono);

/**
* Permet de conserver un temps de fin (cet instant)
* met a jour les variables max, min et somme de la structure
* @param  chrono structure de stockage
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int stopTime(struct time* chrono);

/**
* Permet d'avoir un pourcentage de progression pour chaque calcul
* @param  position d'avancement dans les calculs
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int progressTime(int position, int nbFois);

/**
* Permet d'afficher en console les resultat obtenues
* @param  chrono   structure de stockage
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @param  quoi     chaine de caractere pour preciser l'affichage
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int resultatTime(struct time* chrono, int nbMesure, int nbFois, char* quoi);

/**
* Permet de liberer la memoire
* @param chrono structure a liberer
*/
void destroyStructTime(void* chrono);

#endif
