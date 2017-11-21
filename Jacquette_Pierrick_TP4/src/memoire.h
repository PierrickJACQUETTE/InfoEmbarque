// JACQUETTE Pierrick Tp4

#ifndef __MEMOIRE_H__
#define __MEMOIRE_H__

#include "mesureTime.h"

/**
* Alloue nbMesure fois 1 256 1024 4096 128000 octets
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int memoireCreate(int nbMesure, int nbFois);

#endif
