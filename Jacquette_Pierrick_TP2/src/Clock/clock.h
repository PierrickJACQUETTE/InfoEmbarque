// JACQUETTE Pierrick Tp1

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

/* fonction permettant de lancer un fois le remplissage du tableau est calculant
* la moyenne du temps global
* ligne : nombre de ligne du tableau
* colonne : nombre de colonne du tableau
* thread : thread? 0 non, 1 oui
* nombreDeFois: nombre de fois où l'on va executer le remplissage du tableau
*/
void myclock(int ligne, int colonne, int nb, int thread);

#endif
