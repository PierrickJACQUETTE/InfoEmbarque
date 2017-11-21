// JACQUETTE Pierrick Tp2

#ifndef __SPIRALE_H__
#define __SPIRALE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

/**
* structure pour le passage d'argument a la fonction si on utilise les threads
*/
struct spirale {
    int* pt;        // pointeur du tableau
    int ligne;      // nombre de ligne du tableau
    int colonne;    // nombre de colonne du tableau
    int vmin;       // valeur de la case minimal pour ce thread
    int vmax;       // valeur de la case maximal pour ce thread
    int i;          // postition de la case en haut a gauche du tour de ce thread
};

// enum des directions pour le tremplissage
enum{GAUCHE, HAUT, DROITE, BAS};

/**
* fonction permettant  de remplir le tableau en le parcourant en colimacon avec thread
* @param  tab     pointeur du tableau
* @param  ligne   nombre de ligne du tableau
* @param  colonne nombre de colonne du tableau
* @return         int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int colimaconThread(int **tab, int ligne, int colonne);

/**
* fonction permettant  de remplir le tableau en le parcourant en colimacon
* @param  tab     pointeur du tableau
* @param  ligne   nombre de ligne du tableau
* @param  colonne nombre de colonne du tableau
* @return         int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int colimacon(int** tab, int ligne, int colonne);

/**
* fonction permettant  d'afficher le tableau
* @param  tab     pointeur du tableau
* @param  ligne   nombre de ligne du tableau
* @param  colonne nombre de colonne du tableau
* @return         int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
void affiche(const int* tab, int ligne, int colonne);

#endif
