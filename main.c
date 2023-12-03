#include "header.h"




int main() {
///DECLARER LES VARIABLES
    premierpage();
    int choix, choixquit;
    int station = 1;
    while (1) {
//int choix, choixquit;
        float tempsMaxCycle;

        Sommet sommets[MAX_TACHES];
        initSommets(sommets, MAX_TACHES);

        lireTempsMaxCycle("../rcycle.txt", &tempsMaxCycle);
        lireTempsTaches("../temps.txt", sommets, MAX_TACHES);


        int exclusions[MAX_EXCLUSIONS][2]; // Assurez-vous que cela a une taille suffisante
        int nbExclusions = lireExclusions("../exclu.txt", exclusions);


        assignerStationsET(sommets, MAX_TACHES, tempsMaxCycle, exclusions, nbExclusions);


        Graphe g;
        Station stations[MAX_EXCLUSIONS];
        int nbStations = 0;
// Trier les sommets
        trierSommets(sommets, MAX_TACHES);
        attribuerStations(sommets, MAX_TACHES, tempsMaxCycle);
        initGraphe(&g, MAX_TACHES);
        lirePrecedence(&g, "../prece.txt");

        assignerStations(&g, stations, sommets, MAX_TACHES, &nbStations);
        classerTachesParStation(sommets, MAX_TACHES, tempsMaxCycle);


        //nettoyer l'ecran
        system("cls");
        do {
            ///----------------BOUCLE POUR AFFICHER MENU ET LA SAISIE SI INCORRECTE-------------------------
            do {
                color(9, 0);
                ///AFFICHER MENU
                printf("\n\n\t\t\t\t\t\t                                         \n"
                       "\t\t\t\t\t                                       \n"
                       "\t\t\t\t\t  _ __ ___     ___   _ __    _   _    \n"
                       "\t\t\t\t\t | '_ ` _ \\   / _ \\ | '_ \\  | | | |      \n"
                       "\t\t\t\t\t | | | | | | |  __/ | | | | | |_| |    \n"
                       "\t\t\t\t\t |_| |_| |_|  \\___| |_| |_|  \\__,_|   \n");
                printf("\t\t\t\t\t\t                                         \n\n");

                printf("\n\t\t\t\t\t 1- Exclusion + Precedence\n\n");
                printf("\t\t\t\t\t 2- Exclusion + Temps de cycle\n\n");
                printf("\t\t\t\t\t 3- Precedence + Temps de cycle\n\n");
                printf("\t\t\t\t\t 4- Optimisation max\n\n");
                printf("\t\t\t\t\t 5- Quitter\n\n");

                ///SASIR LE MENU VOULU
                scanf("%d", &choix);


            } while (choix != 0 && choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 &&
                     choix != 7);
            color(0, 9);
            printf("vous avez choisi %d\n\n", choix);

            switch (choix) {
                case 1:///1
                    color(15, 0);
                    printf("choix 1 !\n");
                    printf("Repartition des taches par station :\n");
                    int x=0;

                    for (int j = 0; j < MAX_TACHES; j++) { // Parcourir toutes les stations

                        //printf("Station %d : ", j);
                        bool stationVide = true;

                        for (int i = 1; i < MAX_TACHES; i++) { // Chercher les tâches assignées à cette station
                            if (sommets[i].station == j) {
                                //printf(" %d ", sommets[i].tache);
                                stationVide = false;
                            }
                        }

                        if (stationVide){
                            //printf("%d",x);
                            for (int m = 1; m < x; ++m) {
                                printf("Station %d : ", m);
                                bool stationVide = true;

                                for (int i = 1; i < MAX_TACHES; i++) { // Chercher les tâches assignées à cette station
                                    if (sommets[i].station == m) {
                                        printf(" %d  ", sommets[i].tache);
                                        bool stationVide = false;
                                    }
                                }
                                printf("\n");
                            }
                            break;
                        }

                        x++;

                        //printf("\n");
                    }
                    Sleep(3000);
                    break;

                case 2:///2
                    color(15, 0);
                    printf("Choix 2\n");
                    printf("Temps max par station: %f\n", tempsMaxCycle);
                    // Afficher les résultats groupés par station
                    int stationActuelle = 0;
                    for (int i = 1; i < MAX_TACHES; i++) {
                        if (sommets[i].station != stationActuelle) {
                            if (stationActuelle != 0) {
                                printf("\n"); // Sauter une ligne entre les stations
                            }
                            stationActuelle = sommets[i].station;
                            printf("Station %d : ", stationActuelle);
                        }
                        printf(" %d ", sommets[i].tache);
                    }
                    printf("\n"); // Sauter une ligne à la fin de l'affichage
                    Sleep(3000);
                    break;

                case 3:///3
                    color(15, 0);
                    printf("choix 3 !\n");
                    assignerStationsET(sommets, MAX_TACHES, 15.00, exclusions, nbExclusions);
                    attribuerStations(sommets, MAX_TACHES, 15.00);
                    classerTachesParStation(sommets, MAX_TACHES, 15.00);
                    station = 1;
                    for (int i = 0; i < MAX_TACHES; i++) {
                        bool tacheAjoutee = false;
                        if ( sommets[i].assignee != 1){
                            for (int j = 0; j < MAX_TACHES; j++) {
                                if ((sommets[i].exclu == sommets[j].exclu) && (sommets[i].prece == sommets[j].prece)) {



                                    if (!tacheAjoutee ) {
                                        printf("Station %d: ", station);
                                        tacheAjoutee = true;
                                    }

                                    if (sommets[j].tache != 0 ){
                                        printf("%d ", sommets[j].tache);
                                    }
                                    sommets[j].assignee = 1;

                                }
                            }

                            if (tacheAjoutee) {
                                printf("\n");
                                station++;
                            }
                        }

                    }
                    Sleep(3000);
                    break;

                case 4:///4
                    color(15, 0);
                    printf("choix 4 !\n");
                    station = 1;
                    for (int i = 0; i < MAX_TACHES; i++) {
                        bool tacheAjoutee = false;
                        if ( sommets[i].assignee != 1){
                            for (int j = 0; j < MAX_TACHES; j++) {
                                // Utilisez '==' pour comparer
                                if ((sommets[i].exclu == sommets[j].exclu) && (sommets[i].prece == sommets[j].prece)) {



                                    if (!tacheAjoutee ) {
                                        printf("Station %d: ", station);
                                        tacheAjoutee = true;
                                    }
                                    if (sommets[j].tache != 0 ){
                                        printf("%d ", sommets[j].tache);
                                    }
                                    sommets[j].assignee = 1;

                                }
                            }

                            if (tacheAjoutee) {
                                printf("\n");
                                station++;
                            }
                        }

                    }
                    Sleep(3000);
                    break;

                case 5: ///quitter
                    break;

                default:
                    printf("ERREUR DE SAISIE\n");
                    system("CLS");

                    break;
            }
        } while (choixquit == 2);
        system("PAUSE");
    }
}

