// JACQUETTE Pierrick Tp4

#ifndef __PROCESSUS_H__
#define __PROCESSUS_H__

#include "mesureTime.h"

/**
* Creer un processus fils puis le termine, elle effectue cette opération
* nbMesure fois afin de mesurer le temps
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int processusCreate(int nbMesure, int nbFois);

/**
*Creer un processus fils et effectue nbMesure de changement de
* context entre le fils et le pere
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int processusContext(int nbMesure, int nbFois);

#endif
