// JACQUETTE Pierrick Tp4

#ifndef __THREAD_H__
#define __THREAD_H__

#include "mesureTime.h"

/**
* Creer nbMesure thread pour mesure le temps de creation
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int threadCreate(int nbMesure, int nbFois);

/**
* Creer deux threads et effectue nbMesure de changement de context
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int threadContext(int nbMesure, int nbFois);

#endif
