// main.c
#include "header.h"

int main() {
    FILE *file_operation = fopen("../txt/temps.txt", "r");
    Sommet sommets[MAX_TACHES];
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

    // Affichage des stations et de leurs tâches
    for (int i = 1; i <= sommets[nombreSommets - 1].station; i++) {
        printf("Station %d: ", i);
        for (int j = 0; j < nombreSommets; j++) {
            if (sommets[j].station == i) {
                printf("%d ", sommets[j].tache);
            }
        }
        printf("\n");
    }



    for (int i = 0; i < MAX_TACHES; i++){
        printf("%d / %d / %f \n", sommets[i].tache, sommets[i].station, sommets[i].temps);
    }
    printf("%f", temps_max);
    fclose(file_operation);
    return 0;
}

