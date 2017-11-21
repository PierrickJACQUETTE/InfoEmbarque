// JACQUETTE Pierrick Tp4

#ifndef __DELTA_H__
#define __DELTA_H__

#include "core.h"

/**
* Effectue deltaTime(), deltaGettimeofday() puis deltaClockGettime()
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int delta();

/**
* Affiche le plus petit intervalle de temps mesurables de time();
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int deltaTime();

/**
* Affiche le plus petit intervalle de temps mesurables de gettimeofday();
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int deltaGettimeofday();

/**
* Affiche le plus petit intervalle de temps mesurables de clock_gettime();
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int deltaClockGettime();

#endif
