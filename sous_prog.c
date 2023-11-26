// sousprog.c

#include "header.h" //Valentine test

float lireTempsMax() {
    FILE *fichier = fopen("../txt/rcycle.txt", "r");
    float temps_max;

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier rcycle.txt");
        exit(1);
    }

    if (fscanf(fichier, "%f", &temps_max) != 1) {
        perror("Erreur lors de la lecture du fichier rcycle.txt");
        fclose(fichier);
        exit(1);
    }

    fclose(fichier);
    return temps_max;
}

void trierSommets(Sommet sommets[], int nombreSommets) {
    // Implémentez ici votre algorithme de tri, par exemple un tri par insertion
}

void attribuerStations(Sommet sommets[], int nombreSommets, float temps_max) {
    float tempsCumule = 0.0;
    int stationActuelle = 1;

    for (int i = 0; i < nombreSommets; i++) {
        if (tempsCumule + sommets[i].temps > temps_max) {
            stationActuelle++;
            tempsCumule = 0.0;
        }
        sommets[i].station = stationActuelle;
        tempsCumule += sommets[i].temps;

    }
}
