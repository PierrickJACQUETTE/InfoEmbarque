// JACQUETTE Pierrick Tp4

#ifndef __GRAPH_H__
#define __GRAPH_H__

#define NAMEFILE "output.dat"
#define GNUPLOT_PATH "/usr/bin/gnuplot"

#include "core.h"

extern int graph;

/**
* Permet d'initialiser le fichier avec une entete si il est vide
* @param  nbMesure nombre de fois execute par releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int initFile(int nbMesure);

/**
* Permet d'écrire dans le fichier le resultat
* @param  chrono   structure de stockage
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois 	nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int writeFile(struct time* chrono, int nbMesure, int nbFois);

/**
* Permet de creer des fichiers svg contenant les differents graphiques
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int generateGraph();

#endif
