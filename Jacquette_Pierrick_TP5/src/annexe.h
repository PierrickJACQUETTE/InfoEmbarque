// JACQUETTE Pierrick Tp5

#ifndef __ANNEXE_H__
#define __ANNEXE_H__

#include "core.h"
#include "annexe.h"

/**
* fixer le programme sur un cpu
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int fixerCpu();

/**
* verfie que le programme est exécuté en mode super Utilisateur
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int superUtilisateur();

/**
* parse les arguments donne en ligne de commande
* @param  argc nombre d'argument
* @param  argv tableau des arguments
* @param heritage adresse où inscrire la valeur d'heritage 0 ou 1
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int parseArgument(int argc, char const *argv[], int* heritage);

#endif
