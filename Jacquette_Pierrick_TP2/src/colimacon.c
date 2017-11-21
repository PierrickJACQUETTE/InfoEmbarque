// JACQUETTE Pierrick Tp2

#include "colimacon.h"

/**
 * fonction permettant de remplir le tableau
 * @param  tab     pointeur du tableau
 * @param  ligne   nombre de ligne du tableau
 * @param  colonne nombre de colonne du tableau
 * @param  vmin    valeur minimale de la case
 * @param  vmax    vameur maximale de la case
 * @param  i       position du coin haut gauche du tableau => permet de paralleliser
 */
void spirale(int* tab, int ligne, int colonne, int vmin, int vmax, int i){
    int j=i;
    /*
    * compteur : nombre de case que jai deja rempli sur la direction courante
    * direction : permet de connaitre la direction dans laquelle je dois remplir : commence par aller à droite
    * imax : nombre de case en i que je dois parcourir pour la ligne courante, depend de la ligne que je dois remplir
    * jmax : nombre de case en j que je dois parcourir pour la colonne courante, depend de la colonne que je dois remplir
    * valeur : valeur de la case dans le tableau
    */
    int compteur = 1, valeur;
    int imax =ligne-1-2*i, jmax = colonne-2*j, direction = DROITE;
    compteur = (jmax == 1)? 0 : compteur;
    // je parcours chaque valeur
    for(valeur = vmin; valeur <= vmax; valeur++){
        tab[i*colonne+j] = valeur;     // initialise la valeur dans le tableau
        compteur++;             // donc une case de plus de rempli
        switch(direction){
            case DROITE :
                j++;                    // je vais a droite dans j++
                if(compteur == jmax){   // si ma ligne est rempli alors je vais changer de direction
                    direction = BAS;
                    compteur = 0;       // reset pour la direction suivante
                    jmax--;             // un j de moins pour la prochaine ligne
                    if(jmax == 0 && vmin==valeur){
                        i++;
                        j--;
                    }
                }
                break;
            case BAS :
                i++;
                if(compteur == imax){
                    direction = GAUCHE;
                    compteur = 0;
                    imax--;
                }
                break;
            case GAUCHE :
                j--;
                if(compteur == jmax){
                    direction = HAUT;
                    compteur = 0;
                    jmax--;
                }
                break;
            case HAUT:
                i--;
                if(compteur == imax){
                    direction = DROITE;
                    compteur = 0;
                    imax--;
                }
                break;
            default:
                printf("Je n'ai aucune direction pour cette entree... Oups");
                break;
        }
    }
}

/**
* fonction permettant d'exectuer la fonction spirale pour chaque thread avec leur
* propre argument recuperer dans la strture passee en argument
 * @param s struct spirale contenant les informations pour remplir le tableau
 */
void* fonctionThread(void * s){
    struct spirale * sp = (struct spirale*) s;
    spirale(sp->pt, sp->ligne, sp->colonne, sp->vmin, sp->vmax, sp->i);
    free(s);
    return NULL;

}

/**
 * fonction permettant de verifiant les arguments transmis par l'utilisateur, de
 * déclencher des erreurs si necessaire et dans le cas contraire d'initialiser
 * @param  tab     pointeur du tableau
 * @param  ligne   nombre de ligne du tableau
 * @param  colonne nombre de colonne du tableau
 * @return         int : 0 si tout ce passe bien et -1 en cas d'erreur
 */
int* init(int** tab, int ligne, int colonne){
    if(ligne < 1 || colonne < 1){
        errno =1;
        perror("Il faut une taille positive de ligne et colonne, si est trop grand => devient negatif, init dans colimacon.c");
        return NULL;
    }
    int total = ligne*colonne;
    if(total/ligne!=colonne){
        errno = 1;
        perror("Taille de tableau est trop grande!, init dans colimacon.c");
        return NULL;
    }
    if(tab == NULL){
        errno = 1;
        perror("Pointeur donnee en argument vaut NULL");
        return NULL;
    }
    int* pt = (int*) malloc(total*sizeof(int));
    if(pt == NULL && errno != 0){
        perror("malloc pour le tableau, init dans colimacon.c");
    }
    return pt;
}

/**
 * fonction permettant  de remplir le tableau en le parcourant en colimacon avec thread
 * @param  tab     pointeur du tableau
 * @param  ligne   nombre de ligne du tableau
 * @param  colonne nombre de colonne du tableau
 * @return         int : 0 si tout ce passe bien et -1 en cas d'erreur
 */
int colimaconThread(int **tab, int ligne, int colonne){
    int* pt = init(tab, ligne, colonne);     // initialisation du tableau
    if(pt == NULL){
        return -1;
    }
    int nbThread = (ligne>colonne)? colonne :ligne;
    nbThread = (nbThread%2==0)? nbThread/2 : (nbThread+1)/2; // calcul du nombre de thread a lancé, le plus petit des cotes / 2
    pthread_t tabThread[nbThread]; // tableau des threads
    pthread_t th;
    struct spirale * sp;
    int vmin=1, vmax=0;             // valeur minimale et maximale de chaque thread
    int s=1, i=0;                   // compteur
    for(i=0; i<nbThread; i++){
        sp = malloc (sizeof (struct spirale));  // allocation de la structure de chaque thread
	    if(sp == NULL && errno != 0){
	       perror("malloc struct, colimaconThread dans colimacon.c");
			return -1;
	    }
        vmax += 2*(ligne-s)+2*(colonne-s);      // calcul de la valeur maximale c'est une suite
        vmax = (vmin > vmax)? vmin : vmax;
        vmax = (vmax > ligne*colonne)? ligne*colonne : vmax; // permet de la gestion du thread
        sp->pt =pt;                             // initialisation de la structure
        sp->ligne =ligne;
        sp->colonne = colonne;
        sp->vmin = vmin;
        sp->vmax = vmax;
        sp->i = i;
        if(pthread_create(&th, NULL, fonctionThread, (void*)sp)){       //creation du thread
            perror("pthread create");
        }
        tabThread[i] = th;          //stocke dans le tableau
        s+=2;
        vmin = vmax + 1;
    }
    for(i=0; i < nbThread; i++){
        pthread_join(tabThread[i], NULL);       // depart de tous les threads
    }
    *tab = pt;
    return 0;
}

/**
 * fonction permettant  de remplir le tableau en le parcourant en colimacon
 * @param  tab     pointeur du tableau
 * @param  ligne   nombre de ligne du tableau
 * @param  colonne nombre de colonne du tableau
 * @return         int : 0 si tout ce passe bien et -1 en cas d'erreur
 */
int colimacon(int** tab, int ligne, int colonne){
    int* pt = init(tab, ligne, colonne);     // initialisation du tableau
    if(pt == NULL){
        return -1;
    }
    // fonction qui fait le remplissage du pointeur du tableau(pt) de dimension (ligne, colonne)
    // les valeurs de remplissage vont de 1 à ligne*colonne en commencant
    // en haut à gauche du tableau donc en 0 0
    spirale(pt, ligne, colonne, 1, ligne*colonne, 0);
    *tab = pt;
    return 0;
}

/**
 * fonction permettant  d'afficher le tableau
 * @param  tab     pointeur du tableau
 * @param  ligne   nombre de ligne du tableau
 * @param  colonne nombre de colonne du tableau
 * @return         int : 0 si tout ce passe bien et -1 en cas d'erreur
 */
void affiche(const int* tab, int ligne, int colonne){
    int i;
    for(i = 0; i <ligne*colonne; i++){      // parcours le tableau
        printf("%4d ", tab[i]);             // affiche une case
        if( i%colonne == colonne-1){        // pour que l'affiche soit plus esthetique
            printf("\n");
    	}
	}
}
