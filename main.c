// main.c

#include "header.h"

int main() {

    FILE *file_operation = fopen("../txt/temps.txt", "r");
    Sommet sommets[MAX_TACHES];
    Graphe g;
    Station stations[NB_MAX_ETAPES];
    int nbStations = 0;
    int nombreSommets = 0;
    float temps_max;

    if (file_operation == NULL) {
        perror("Erreur lors de l'ouverture du fichier temps.txt");
        exit(1);
    }

    // Lire le temps maximum du fichier rcycle.txt
    temps_max = lireTempsMax();

    // Lecture du fichier temps.txt et stockage dans le tableau sommets
    while (nombreSommets < MAX_TACHES && fscanf(file_operation, "%d %f", &sommets[nombreSommets].tache, &sommets[nombreSommets].temps) != EOF) {
        sommets[nombreSommets].station = 0;
        nombreSommets++;
    }

    // Trier les sommets
    trierSommets(sommets, nombreSommets);

    // Attribuer des stations aux tâches
    attribuerStations(sommets, nombreSommets, temps_max);




    initGraphe(&g, NB_MAX_ETAPES);
    lireContraintes(&g, "../txt/contrainte_precedente.txt");

    printf("\n\n\n");
    assignerStations(&g, stations, sommets, nombreSommets, &nbStations);



    /* Vérification de chaque attribut de la structure sommet
    for (int i = 0; i < MAX_TACHES; i++){
        printf("%d / %d / %f / %d\n", sommets[i].tache, sommets[i].station, sommets[i].temps,sommets[i].grp_ordonencement);
    } */



    // Appeler le sous-programme pour classer les tâches par station
    classerTachesParStation(sommets, nombreSommets, temps_max);

    printf("=============================================================\n");
    printf("Temps max par station: %f\n", temps_max);
    // Afficher les résultats groupés par station
    int stationActuelle = 0;

    for (int i = 0; i < nombreSommets; i++) {
        if (sommets[i].station != stationActuelle) {
            if (stationActuelle != 0) {
                printf("\n"); // Sauter une ligne entre les stations
            }
            stationActuelle = sommets[i].station;
            printf("Station %d: ", stationActuelle);
        }
        printf("%d ", sommets[i].tache);
    }
    printf("\n"); // Sauter une ligne à la fin de l'affichage
    printf("=============================================================");

    fclose(file_operation);

    printf("\n\n\n");


// Déclaration d'un pointeur pour stocker les paires d'exclusion
    PaireExclusion paires[MAX_PAIRS];

    // Allocation dynamique de la structure graphe
    graphe_val *gra = (graphe_val *)malloc(sizeof(graphe_val));
    if (gra == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    int nb_ops = 35;
    // Initialisation du graphe avec le pointeur
    initialisation_graphe(gra, nb_ops);

    // Lecture des paires d'exclusion à partir du fichier
    int nbPaires = lireExclusions("../txt/exclu.txt", paires);
    // Vérifier si la lecture a échoué
    if (nbPaires < 0) {
        // Libération de la mémoire avant de quitter en cas d'erreur
        free(gra);
        return 1;
    }


    // Ajout des arêtes au graphe en fonction des paires d'exclusion
    for (int i = 0; i < nbPaires; i++) {
        ajouter_Arete(gra, paires[i].op1, paires[i].op2);
    }

    // Coloration du graphe
    colorergraphe(gra);

    // Libération de la mémoire allouée pour le graphe
    free(gra);
}
