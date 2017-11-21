// JACQUETTE Pierrick Tp4

#include "processus.h"
#include "thread.h"
#include "memoire.h"
#include "delta.h"

/**
* fonction permettant d'afficher toutes les options possibles
* @param  error help car erreur ou demande par utilisateur
*/
int help(int error){
    printf("%s\n\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n",\
    "Options disponibles : ", "--help ou -h : Affiche la liste des options disponibles.",\
    "--processus ou -p : Affiche les mesures de temps pour les processus.",\
    "--thread ou -t : Affiche les mesures de temps pour les threads.",\
    "--delta ou -d : Affiche le plus petit intervalle de temps mesurables.",\
    "--memoire ou -m : Affiche les mesures de temps d'allocation memoire.",\
    "--nbMesure X ou -n X : Specifie le nombre d'opération par mesure X>99.",\
    "--nbFois X ou -f X : Specifie le nombre de mesure souhaite X>9.",\
    "--create ou -v : Affiche les mesures de temps de creation.",\
    "--context ou -c : Affiche les mesures de temps de changement de context.",\
    "--graph ou -g : Ajoute les mesures de temps dans le fichier output.dat.",\
    "--all ou -a : Effectue tout ce qui est possible sauf les graphiques.",\
    " par defaut tout est effectué avec nbMesure vaut 700 et nbFois vaut 100.");
    return error;
}

/**
* fonction main, le point d'entree du programme
* @param  argc nombre d'argument
* @param  argv tableau des arguments
* @return int : 0 si tout ce passe bien et -1 en cas d'erreur
*/
int main(int argc, char const *argv[]) {
    int nbMesure = 700, nbFois = 100, thread = 0, processus = 0, memoire = 0;
    int create = 0, deltaTime = 0, context = 0, nbHelp = 0, all = 0, error;
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    error = sched_setaffinity(getpid(), sizeof(set), &set);
    ERROR_SYS(error, "Error sched_setaffinity in main : main.c");
    if(argc > 1){
        int i;
        // je regarde ce que l'utilisateur a tapé comme argument
        for(i = 1; i < argc; i++){
            if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
                return help(0);
            }else if(strcmp(argv[i], "--delta") == 0 || strcmp(argv[i], "-d") == 0){
                deltaTime = 1;
            }else if(strcmp(argv[i], "--thread") == 0 || strcmp(argv[i], "-t") == 0){
                thread = 1;
            }else if(strcmp(argv[i], "--processus") == 0 || strcmp(argv[i], "-p") == 0){
                processus = 1;
            }else if(strcmp(argv[i], "--memoire") == 0 || strcmp(argv[i], "-m") == 0){
                memoire = 1;
            }else if(strcmp(argv[i], "--context") == 0 || strcmp(argv[i], "-c") == 0){
                context = 1;
            }else if(strcmp(argv[i], "--create") == 0 || strcmp(argv[i], "-v") == 0){
                create = 1;
            }else if(strcmp(argv[i], "--nbMesure") == 0 || strcmp(argv[i], "-n") == 0){
                if(argv[i+1] != NULL && atoi(argv[i+1]) > 99){
                    i++;
                    nbMesure = atoi(argv[i]);
                }else{
                    error = fprintf(stderr, "Erreur pour synthaxe pour l'argument --nbMesure ou -n\n");
                    ERROR_SYS(error, "Error fprintf nbMesure : main in main.c");
                    return help(1);
                }
            }else if(strcmp(argv[i], "--nbFois") == 0 || strcmp(argv[i], "-f") == 0){
                if(argv[i+1] != NULL && atoi(argv[i+1]) > 9){
                    i++;
                    nbFois = atoi(argv[i]);
                }else{
                    error = fprintf(stderr, "Erreur pour synthaxe pour l'argument --nbFois ou -f\n");
                    ERROR_SYS(error, "Error fprintf nbFois : main in main.c");
                    return help(1);
                }
            }else if(strcmp(argv[i], "--graph") == 0 || strcmp(argv[i], "-g") == 0){
                graph = 1;
            }else if(strcmp(argv[i], "--all") == 0 || strcmp(argv[i], "-a") == 0){
				all = 1;
            }else{
                error = fprintf(stderr, "Erreur pour synthaxe pour l'argument %s\n", argv[i]);
                ERROR_SYS(error, "Error fprintf : main in main.c");
                return help(1);
            }
        }
    }
    if(argc == 1 || all == 1){  //par default toutes les options sont actives
        thread = 1;
        processus = 1;
        memoire = 1;
        context = 1;
        create = 1;
        deltaTime = 1;
    }
    //pour verifier que l'on soit en mode superUtilisateur
    if(context == 1 && getuid() != 0){
        error = fprintf(stderr, "\nPour obtenir les resultats pour differents ordonnancements merci de passer en mode superUtilisateur\n \t sudo ./tp4 [options] \n\n");
        ERROR_SYS(error, "Error fprintf : main in main.c");
		if(graph == 1){
			return EXIT_FAILURE;
		}
    }
    // je decide quelle(s) fonction(s) appelée(s) en fonction des choix de l'utilisateur
    if(deltaTime == 1){
        nbHelp = 1;
        error = delta();
        ERROR_SYS(error, "Error delta in main : main.c");
    }
    if(memoire == 1){
        nbHelp = 1;
        error = memoireCreate(nbMesure, nbFois);
        ERROR_SYS(error, "Error memoireCreate in main : main.c");
    }
    if(thread == 1 && context == 1){
        nbHelp = 1;
        error = threadContext(nbMesure, nbFois);
        ERROR_SYS(error, "Error threadContext in main : main.c");
    }
    if(processus == 1 && context == 1){
        nbHelp = 1;
        error = processusContext(nbMesure, nbFois);
        ERROR_SYS(error, "Error processusContext in main : main.c");
    }
    if(thread == 1 && create == 1){
        nbHelp = 1;
        error = threadCreate(nbMesure, nbFois);
        ERROR_SYS(error, "Error threadCreate in main : main.c");
    }
    if(processus == 1 && create == 1){
        nbHelp = 1;
        error = processusCreate(nbMesure, nbFois);
        ERROR_SYS(error, "Error processusCreate in main : main.c");
    }
    if(graph == 1 && nbHelp == 1){
        error = generateGraph();
        ERROR_SYS(error, "Error generateGraph in main : main.c");
    }
    if(nbHelp == 0){
        return help(0);
    }
    return EXIT_SUCCESS;
}
