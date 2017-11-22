// JACQUETTE Pierrick Tp5

#ifndef __THREAD_H__
#define __THREAD_H__

#include "core.h"
#include "annexe.h"

/**
* Creer les threads et  les lancer
* @param heritage valeur de l'heritage 0 ou 1
* @return int : 0 si tout ce passe bien et pas inversion,
*               1 si tout ce passe bien et inversion
*               -1 en cas d'erreur
*/
int thread(int* heritage);

#endif
