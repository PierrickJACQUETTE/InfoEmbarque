// JACQUETTE Pierrick Tp1

#include "clock.h"

/* fonction permettant de lancer un fois le remplissage du tableau est calculant
* la moyenne du temps global
* ligne : nombre de ligne du tableau
* colonne : nombre de colonne du tableau
* thread : thread? 0 non, 1 oui
* nombreDeFois: nombre de fois où l'on va executer le remplissage du tableau
*/
void myclock(int ligne, int colonne, int nb, int thread){
    struct timespec start, stop;        //definition des structures pour calculer le temps
    memset(&start, 0, sizeof(start));
    memset(&stop, 0, sizeof(stop));
    char* buff = malloc(sizeof(char)*6);    // buffer pour afficher le temps
    memset(buff, 0, 7);
    char* sys = malloc(sizeof(char)*26);    // buffer pour lancer l'executable avec les bons arguments
    memset(buff, 0, 27);
    sprintf(sys, "%s %d %d 0 %d", "./colimacon", ligne, colonne, thread);
    if( clock_gettime( CLOCK_REALTIME, &start) < 0 ) {  //temps de depart
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    int i;
    for(i=0; i<nb; i++){            //execute nb fois le remplissage
        system(sys);
    }
    if( clock_gettime( CLOCK_REALTIME, &stop) < 0 ) {   //temps de fin
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    //calcul de la difference de temps
    sprintf(buff,"%.3lf", ((stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec )/1E9)/nb);
    printf("float value : %s s\n", buff);   // affiche le resultat
}

/* ./clock ligne colonne thread nombreDeFois
* argument optionnel valeur par defaut
* ligne : nombre de ligne du tableau
* colonne : nombre de colonne du tableau
* thread : thread? 0 non, 1 oui
* nombreDeFois: nombre de fois où l'on va executer le remplissage du tableau
*/
int main(int argc, char const *argv[]) {
    int ligne = 1, colonne = 1, thread = 0, nb = 1;
    if(argc >= 2){
        ligne = atoi(argv[1]);
    }
    if(argc >= 3){
        colonne = atoi(argv[2]);
    }
    if(argc >= 4){
        thread = atoi(argv[3]);
    }
    if(argc >= 5){
        nb = atoi(argv[4]);
    }
    myclock(ligne, colonne, nb, thread);
    return 0;
}
