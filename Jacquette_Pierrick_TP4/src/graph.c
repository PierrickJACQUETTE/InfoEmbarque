// JACQUETTE Pierrick Tp4

#include "graph.h"

int graph = 0;

/**
* Permet d'initialiser le fichier avec une entete si il est vide
* @param  nbMesure nombre de fois execute par releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int initFile(int nbMesure){
    int error, newFile = 0;
    struct stat st;
    FILE *fd = NULL;
    if(stat(NAMEFILE, &st) < 0){
        newFile = 1;
    }
    fd = fopen(NAMEFILE, "a");
    ERROR_NULL(fd, "Error fopen : initFile in graph.c");
    if(newFile == 1){
        error = fprintf(fd, "What?\t1octet\t256octets\t1024octets\t4096octets\
        \t12800octets\tThreadImpliciteFIFO\tThreadImpliciteRR\tThreadExpliciteFIFO\
        \tThreadExpliciteRR\tThreadExpliciteTP\tProcessusExpliciteTP\
        \tProcessusImpliciteFIFO\tProcessusImpliciteRR\tProcessusExpliciteFIFO\
        \tProcessusExpliciteRR\tThread\tProcessus");
        ERROR_SYS(error, "Error fprintf : resultatTime in mesureTime.c");
    }
    error = fprintf(fd, "\n%d", nbMesure);
    ERROR_SYS(error, "Error fprintf nbMesure : initFile in graph.c");
    error = fclose(fd);
    ERROR_USER(error, "Error fclose : initFile in graph.c");
    return EXIT_SUCCESS;
}

/**
* Permet d'écrire dans le fichier le resultat
* @param  chrono   structure de stockage
* @param  nbMesure nombre de fois execute par releve de temps
* @param  nbFois 	nombre de fois où l'on fait releve de temps
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int writeFile(struct time* chrono, int nbMesure, int nbFois){
    int error;
    FILE *fd = fopen(NAMEFILE, "a");
    ERROR_NULL(fd, "Error fopen : writeFile in graph.c");
    error = fprintf(fd, "\t%.11lf", (chrono->somme/nbFois)/nbMesure);
    ERROR_SYS(error, "Error fprintf : writeFile in graph.c");
    error = fclose(fd);
    ERROR_USER(error, "Error fclose : writeFile in graph.c");
    return EXIT_SUCCESS;
}

/**
* Permet de creer des fichiers svg contenant les differents graphiques
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int generateGraph(){
	int error;
	FILE* gp = popen(GNUPLOT_PATH, "w");
	ERROR_NULL(gp, "Error popen : generateGraph in graph.c");
	error = fprintf(gp, "load \"config_graph\"\n");
	ERROR_SYS(error, "Error fprintf congig_graph : generateGraph in graph.c");
    error = fflush(gp);
	ERROR_USER(error, "Error fflush : generateGraph in graph.c");
    error = pclose(gp);
	ERROR_SYS(error, "Error pclose : generateGraph in graph.c");
    return EXIT_SUCCESS;
}
